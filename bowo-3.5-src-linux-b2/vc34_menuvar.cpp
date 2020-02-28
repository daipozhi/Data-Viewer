/*
#define STRICT
*/
#include "windows.h"
/*
#include <commdlg.h>
*/
#include <stdio.h>
/*
#include <math.h>
#include <direct.h>
#include <dos.h>
#include <io.h>
#include <conio.h>
#include <process.h>
*/
#include <string.h>
/*
#include <time.h>
*/
#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_switch       bw_switch1;
extern class bw_buff         bw_buff1;
extern class bw_xbase        bw_xbase1;
extern class bw_getread      bw_getread1;
extern class bw_dialog       bw_dialog1;
extern class bw_choose       bw_choose1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;
extern class bw_menuvar      bw_menuvar1;

#define DEBUG_MV 0

int bw_menuvar::w_menu_find_seri(int p1)
{
  return(get_t5_m_wind(p1));
}

int bw_menuvar::w_read_mdc(char *p_fn1,int p_fn1_size,int p_win)
{
  int  i,j;
  int  p1,p2,p3,p4,p5,p6,p7,p8,same;
//  int  state3;
//  int  state5;
  int  pp1;
  char sfn1[FN_SIZE];
  //char sfn2[FN_SIZE];
  char tmpc2[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  int  exist;
  FILE *fp1;

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.strlocc(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb1");

  exist=0;

  for (i=0;i<MENU_NUM_MN;i++)
  {
    if (get_t5_m_wind(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  pp1=i;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    for (i=0;i<SMG_SIZE;i++) tmpc2[i]=0;

    fgets(tmpc2,SMG_SIZE,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      p_win++;
      continue;
    }

    for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>=0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_SIZE) break;
    p1=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for menuname*/
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p2=i-1;
					 /* scan for space after menuname*/
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for button  */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p4=i-1;
					  /* scan for space after button  */
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for command */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p6=i-1;

    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    p7=i;

    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for command */
    p8=i-1;

    for (j=p1;j<=p2;j++)
    {
      if (tmpc2[j]==' ') break;
      setc_t5_m_name(pp1,j-p1,tmpc2[j]);
      setc_t5_m_name(pp1,j-p1+1,0);
    }

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      setc_t5_m_button(pp1,j-p3,tmpc2[j]);
      setc_t5_m_button(pp1,j-p3+1,0);
    }

    get_t5_m_button(pp1,sb1,SMG_SIZE);

    same=0;
    if (strncmp("button=",sb1,7)==0) same=1;
    if (strncmp("bitmap=",sb1,7)==0) same=1;
    if (same==0)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }

    for (j=p5;j<=p6;j++)
    {
      if (tmpc2[j]==' ') break;
      setc_t5_m_comm(pp1,j-p5+0,tmpc2[j]);
      setc_t5_m_comm(pp1,j-p5+1,0);
    }

    get_t5_m_comm(pp1,so1,SMG_SIZE);

    same=0;
    if (strncmp("com=",so1,4)==0) same=1;
    if (strncmp("do=",so1,3)==0) same=1;
    if (same==0)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }

    for (j=p7;j<=p8;j++)
    {
      if (tmpc2[j]==' ') break;
      setc_t5_m_focus(pp1,j-p7,tmpc2[j]);
      setc_t5_m_focus(pp1,j-p7+1,0);
    }

    set_t5_m_wind(pp1,p_win);

    pp1++;
  }

  t5_m_pp1=pp1-1;

  fclose(fp1);
/*
  for (i=0;i<=t5_m_pp1;i++)
  {
    loc(i+1,1);
    printf("%s,%s,%s,"
	   ,t5_m_name[i]
	   ,t5_m_button[i]
	   ,t5_m_comm[i]);
  }
  inkey();
*/
  return(0);
}

int bw_menuvar::tst_menu()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];
  char sm1[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  char sf1[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    get_t5_m_name(i,sm1,SMG_SIZE);
    get_t5_m_button(i,sb1,SMG_SIZE);
    get_t5_m_comm(i,so1,SMG_SIZE);
    get_t5_m_focus(i,sf1,SMG_SIZE);

    sprintf(str,"%d,%d,%d,%s,%s,%s,%s,"
				 ,get_t5_m_wind(i)
                                 ,get_t5_m_mcnt(i)
				 ,t5_m_pp1
				 ,sm1
			         ,sb1
				 ,so1
                                 ,sf1
				 );
    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_menuvar::w_dele_menu(int wp1,int wp2)
{
  int  i;
  int  p1,p2,p3,p4,p5,p6;
  char sm1[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  char sf1[SMG_SIZE];

  p1=(-1);  /* begin pp*/ 
  p2=(-1);  /* end pp*/  
  p3=0;  /* end big win pp*/
  p4=0;  /* mn cnt*/
  p5=0;
  p6=0;

  for (i=0;i<=t5_m_pp1;i++)
  {
    if ((get_t5_m_wind(i)>=wp1)&&(get_t5_m_wind(i)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (get_t5_m_wind(i)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (get_t5_m_wind(i)>wp2)
    {
      p3=i;
    }
  }
  if (p2<0)
  {
    p2=t5_m_pp1+1;
    p3=p2-1;
  }

  if ((p1<0)||(p4==0))
  {
    for (i=p2;i<=p3;i++)
    {
      set_t5_m_wind(i,get_t5_m_wind(i)-wp2+wp1-1);
    }
  }
  else
  {
    if (p3>=p2)
    {
      for (i=p2;i<=p3;i++)
      {
	get_t5_m_name(i,sm1,SMG_SIZE);
        set_t5_m_name(p1+i-p2,sm1,SMG_SIZE);

	get_t5_m_button(i,sb1,SMG_SIZE);
	set_t5_m_button(p1+i-p2,sb1,SMG_SIZE);

	get_t5_m_comm(i,so1,SMG_SIZE);
	set_t5_m_comm(p1+i-p2,so1,SMG_SIZE);

	get_t5_m_focus(i,sf1,SMG_SIZE);
	set_t5_m_focus(p1+i-p2,sf1,SMG_SIZE);

	set_t5_m_mcnt(p1+i-p2,get_t5_m_mcnt(i));
	set_t5_m_wind(p1+i-p2,get_t5_m_wind(i)-wp2+wp1-1);
      }

      for (i=p1+p3-p2+1;i<=t5_m_pp1;i++)
      {
	setc_t5_m_name(i,0,0);
	setc_t5_m_button(i,0,0);
	setc_t5_m_comm(i,0,0);
	setc_t5_m_focus(i,0,0);
	set_t5_m_mcnt(i,0);
	set_t5_m_wind(i,0);
      }

      t5_m_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=t5_m_pp1;i++)
      {
	setc_t5_m_name(i,0,0);
        setc_t5_m_button(i,0,0);
	setc_t5_m_comm(i,0,0);
	setc_t5_m_focus(i,0,0);
	set_t5_m_mcnt(i,0);
	set_t5_m_wind(i,0);
      }

      t5_m_pp1=p1;
    }
  }

  return(0);
}
int bw_menuvar::w_menu_comm(int p1,int state)
{
  int  i;
  int  exist;
  int  chs;
  char s1[SMG_SIZE];
  char s2[SMG_SIZE];
  char s3[50][30];
  char s4[SMG_SIZE];

  if (p1<0)
  {
    t5_m_como[0]=0;
    t5_m_pp2=0;
    return(1);
  }

  strcpy(s3[0],"get_tab(");
  strcpy(s3[1],"get_edit(");
  strcpy(s3[2],"get_menu(");
  strcpy(s3[3],"get_choose(");
  strcpy(s3[4],"get_switch(");
  strcpy(s3[5],"get_mchoose(");
  strcpy(s3[6],"setup_sys(");
  strcpy(s3[7],"return(");
  strcpy(s3[8],"setup(");
  strcpy(s3[9],"get_tab_read(");
  strcpy(s3[10],"get_pwd(");
  strcpy(s3[11],"get_pwd_chg(");
  strcpy(s3[12],"get_exec(");
  strcpy(s3[13],"exit");
  strcpy(s3[14],"cancel");
  strcpy(s3[15],"page_up");
  strcpy(s3[16],"page_down");
  strcpy(s3[17],"insert_rec");
  strcpy(s3[18],"delete_rec");
  strcpy(s3[19],"rollback");
  strcpy(s3[20],"commit");
  strcpy(s3[21],"linkwindow");
  strcpy(s3[22],"findcondition");
  strcpy(s3[23],"beginfind");
  strcpy(s3[24],"endfind");
  strcpy(s3[25],"echo_bmp(");
  strcpy(s3[26],"add_rec");
  strcpy(s3[27],"up_line");
  strcpy(s3[28],"down_line");


  chs=28;
  t5_m_pp2=0;
  t5_m_como[0]=0;
  if (state==0) get_t5_m_comm(p1,s1,SMG_SIZE);
  else get_t5_m_focus(p1,s1,SMG_SIZE);

  if (strncmp("com=",s1,4)==0)
  {
    bw_inkey1.strpcut(s1,4,strlen(s1)-4,SMG_SIZE,s2,SMG_SIZE);

    exist=0;

    for (i=0;i<=chs;i++)
    {
      if (strncmp(s3[i],s2,strlen(s3[i]))==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      t5_m_pp2=i+1;
      bw_inkey1.strpcut(s2,strlen(s3[i]),strlen(s2)-strlen(s3[i]),SMG_SIZE,s4,SMG_SIZE);
      if (s4[0]=='"')
      {
	exist=0;
	for (i=1;i<(int)strlen(s4);i++)
	{
	  if (s4[i]=='"')
	  {
	    exist=1;
	    break;
	  }
	}
	if (exist==0)
	{
	  t5_m_pp2=0;
	  t5_m_como[0]=0;
	}
	else
	{
	  bw_inkey1.strpcut(s4,1,i-1,SMG_SIZE,t5_m_como,SMG_SIZE);
	}
      }
      else t5_m_como[0]=0; /* mem var */
    }
    else
    {
      t5_m_pp2=0;
      t5_m_como[0]=0;
    }
  }
  else
  {
    t5_m_pp2=0;
    t5_m_como[0]=0;
  }

  return(0);
}
int bw_menuvar::w_menu_poin(char *p_s1,int p_s1_size,int p1)
{
  int  i;
  int  exist;
  char sm1[SMG_SIZE];
  //char sc1[SMG_SIZE];

  exist=0;

  for (i=0;i<=t5_m_pp1;i++)
  {
    get_t5_m_name(i,sm1,SMG_SIZE);

    if ((strcmp(p_s1,sm1)==0)&&(p1==w_menu_find_seri(i)))
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    t5_m_pp3=i;
    return(0);
  }
  else
  {
    t5_m_pp3=(-1);
    return(1);
  }
}

int bw_choose::w_choose_ini()
{
  int i;

  for (i=0;i<MENU_NUM_CHS;i++)
  {
    bw_choose1.set_win_choose(i,0,0);
    bw_choose1.setc_win_choose_name(i,0,0);
  }

  win_choose_pp1=0;

  return(0);
}

int bw_choose::w_read_cdc(char *p_fn1,int p_fn1_size,int wpp)
{
  int  i,j,k,l,o;
  int  p1,p2,p3,p4,p5,p6;
//  int  state2,state3;
//  int  state4,state5;
  int  pp1;
  char sfn1[FN_SIZE];
  char tmpc2[SMG_SIZE];
  char str[SMG_SIZE];
  char str2[SMG_SIZE];//--
  char sc1[SMG_SIZE];
  //char sd1[SMG_SIZE];
  int  exist;
  FILE *fp1;

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.strlocc(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb6");

  exist=0;

  for (i=0;i<MENU_NUM_CHS;i++)
  {
    if (bw_choose1.get_win_choose(i,0)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  pp1=i;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    for (i=0;i<SMG_SIZE;i++) tmpc2[i]=0;
    fgets(tmpc2,SMG_SIZE,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      wpp++;
      continue;
    }

    for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>=0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_SIZE) break;
    p1=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for menuname*/
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p2=i-1;
					 /* scan for space after menuname*/
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for button  */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p4=i-1;
					  /* scan for space after button  */
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for command */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p6=i-1;

    bw_inkey1.strpcut(tmpc2,p1+1,p2-p1-1+1,SMG_SIZE,str2,SMG_SIZE);
    o=bw_inkey1.str2int(str2,SMG_SIZE);
    k=pp1;
    bw_choose1.set_win_choose(k,0,1);
    bw_choose1.set_win_choose(k,2,o);
    bw_choose1.set_win_choose(k,3,wpp);

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      bw_choose1.setc_win_choose_name(k,j-p3+0,tmpc2[j]);
      bw_choose1.setc_win_choose_name(k,j-p3+1,0);
    }

    bw_inkey1.strpcut(tmpc2,p5,p6-p5+1,SMG_SIZE,str2,SMG_SIZE);
    l=bw_inkey1.str2int(str2,SMG_SIZE);
    bw_choose1.set_win_choose(k,1,l);

    bw_choose1.get_win_choose_name(k,sc1,SMG_SIZE);

    if (bw_dialog1.w_mv_exist(sc1,SMG_SIZE,wpp)==1)
    {
      bw_dialog1.w_mv_fet_val(sc1,SMG_SIZE,0,str,SMG_SIZE);
      //bw_inkey1.strpcut(str,0,strlen(str)-1-0+1,SMG_SIZE,str2,SMG_SIZE);
      bw_choose1.set_win_choose(k,1,bw_inkey1.str2int(str,SMG_SIZE));
    }

    pp1++;
  }

  win_choose_pp1=pp1;

  fclose(fp1);

  return(0);
}

int bw_choose::tst_choose()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];
  char sc1[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    bw_choose1.get_win_choose_name(i,sc1,SMG_SIZE);

    sprintf(str,"%d,%d,%d,%d,%s,%d,",bw_choose1.get_win_choose(i,0)
				    ,bw_choose1.get_win_choose(i,1)
				    ,bw_choose1.get_win_choose(i,2)
				    ,bw_choose1.get_win_choose(i,3)
				    ,sc1
				    ,win_choose_pp1);
    TextOut(hdc,1,i*20,str,strlen(str));

  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}


int bw_choose::w_dele_choose(int wp1,int wp2)
{
  int  i;
  int  p1,p2,p3,p4,p5,p6;
  char sc1[SMG_SIZE];
/*
  p1=(-1);  // begin pp
  p2=(-1);  // end pp
  p3=0;     // end big win pp
  p4=0;     // mn cnt
  p5=0;
  p6=0;

  for (i=0;i<=win_choose_pp1;i++)
  {
    if ((bw_choose1.get_win_choose(i,3)>=wp1)&&(bw_choose1.get_win_choose(i,3)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (bw_choose1.get_win_choose(i,3)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (bw_choose1.get_win_choose(i,3)>wp2)
    {
      p3=i;
    }
  }
  if (p2<0)
  {
    p2=win_choose_pp1+1;
    p3=p2-1;
  }

  if ((p1<0)||(p4==0))
  {
    for (i=p2;i<=p3;i++)
    {
      bw_choose1.set_win_choose(i,3,bw_choose1.get_win_choose(i,3)-wp2+wp1-1);
    }
  }
  else
  {
    if (p3>=p2)
    {
      for (i=p2;i<=p3;i++)
      {
	bw_choose1.get_win_choose_name(i,sc1,SMG_SIZE);
	bw_choose1.set_win_choose_name(p1+i-p2,sc1,SMG_SIZE);

	bw_choose1.set_win_choose(p1+i-p2,0,bw_choose1.get_win_choose(i,0));
	bw_choose1.set_win_choose(p1+i-p2,1,bw_choose1.get_win_choose(i,1));
	bw_choose1.set_win_choose(p1+i-p2,2,bw_choose1.get_win_choose(i,2));
	bw_choose1.set_win_choose(p1+i-p2,3,bw_choose1.get_win_choose(i,3)-wp2+wp1-1);
      }

      for (i=p1+p3-p2+1;i<=win_choose_pp1;i++)
      {
	bw_choose1.setc_win_choose_name(i,0,0);
	bw_choose1.set_win_choose(i,0,0);
	bw_choose1.set_win_choose(i,1,0);
	bw_choose1.set_win_choose(i,2,0);
	bw_choose1.set_win_choose(i,3,0);
      }
      win_choose_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_choose_pp1;i++)
      {
	bw_choose1.setc_win_choose_name(i,0,0);
	bw_choose1.set_win_choose(i,0,0);
	bw_choose1.set_win_choose(i,1,0);
	bw_choose1.set_win_choose(i,2,0);
	bw_choose1.set_win_choose(i,3,0);
      }
      win_choose_pp1=p1;
    }
  }
*/
  return(0);

}
int bw_choose::w_save_choose(int wpp)
{
  int  i,j;
  char str[SMG_SIZE];
  char sc1[SMG_SIZE];

  //for (j=bw_win1.get_win_pp_grp_pp(bw_win1.get_win_pp_grp_id(wpp),0);j<=bw_win1.get_win_pp_grp_pp(bw_win1.get_win_pp_grp_id(wpp),2);j++)
  //{
    for (i=0;i<win_choose_pp1;i++)
    {
      //if (bw_choose1.get_win_choose(i,3)==wpp)
      //{
	bw_inkey1.int2str(bw_choose1.get_win_choose(i,1),str,SMG_SIZE);
        bw_choose1.get_win_choose_name(i,sc1,SMG_SIZE);
	bw_dialog1.w_mv_save_mem(sc1,SMG_SIZE,wpp,str,strlen(str));
      //}
    }
  //}
  return(0);
}

int bw_choose::w_echo_chs_change(int link,int wpp)
{
//  int s_tmpn1,s_tmpn2;
//  int s_tmpn3,s_tmpn4;
//  char link2;
  int i;
  int exist;

  exist=0;

  for (i=0;i<MENU_NUM_CHS;i++)
  {
    if ((bw_choose1.get_win_choose(i,2)==link)&&(bw_choose1.get_win_choose(i,3)==wpp))
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    if (bw_choose1.get_win_choose(i,1)==1) bw_choose1.set_win_choose(i,1,0);
    else bw_choose1.set_win_choose(i,1,1);

    return(i);
  }
  else return(-1);
}

int bw_choose::w_clr_recvar_chs(int wpp)
{
  int i;

  for (i=0;i<MENU_NUM_CHS;i++)
  {
    bw_choose1.set_win_choose(i,0,0);
    bw_choose1.setc_win_choose_name(i,0,0);
  }

  win_choose_pp1=0;

  return(0);
}

int bw_choose::w_echo_winrec_chs(int wpp)
{
  int i,j,k,l,n,o;
  char str[SMG_SIZE];
  char str2[SMG_SIZE];

  bw_win1.pline =1;
  bw_win1.pfield=1;

  while (1)
  {
    i=bw_win1.pline;
    j=bw_win1.pfield;

    bw_win1.w_next_afield(wpp);

    if ((i==bw_win1.pline)&&(j==bw_win1.pfield)) break;

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_SIZE);

    if (str[0]=='[')
    {
      bw_inkey1.strpcut(str,1,strlen(str)-1-1+1,SMG_SIZE,str2,SMG_SIZE);
      n=bw_inkey1.str2int(str2,SMG_SIZE);

      for (k=0;k<MENU_NUM_CHS;k++)
      {
	if ((bw_choose1.get_win_choose(k,2)==n)&&(bw_choose1.get_win_choose(k,3)==wpp))
        {
	  l=bw_choose1.get_win_choose(k,1);

	  o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);

	  if (l>0)
	  {
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)str);
	  }
	  else
	  {
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)str);
	  }
	  break;
        }
      }
    }
  }
  return(0);
}

int bw_switch::w_switch_ini()
{
  int i;

  for (i=0;i<MENU_NUM_RA;i++)
  {
    set_win_switch(i,0,0);
    setc_win_switch_name(i,0,0);
  }

  win_switch_pp1=0;

  return(0);
}

int bw_switch::w_read_sdc(char *p_fn1,int p_fn1_size,int wpp)
{
  int  i,j,k,l,o;
  int  p1,p2,p3,p4,p5,p6;
//  int  state2,state3;
//  int  state4,state5;
  int  pp1;
  char sfn1[FN_SIZE];
  char st1[SMG_SIZE];
  //char sd1[SMG_SIZE];
  char tmpc2[SMG_SIZE];
  char str[SMG_SIZE];
  char str2[SMG_SIZE];
  int  exist;
  FILE *fp1;

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.strlocc(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb5");

  exist=0;

  for (i=0;i<MENU_NUM_RA;i++)
  {
    if (get_win_switch(i,0)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  pp1=i;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    for (i=0;i<SMG_SIZE;i++) tmpc2[i]=0;
    fgets(tmpc2,SMG_SIZE,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      wpp++;
      continue;
    }

    for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>=0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_SIZE) break;
    p1=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for menuname*/
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p2=i-1;
					 /* scan for space after menuname*/
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for button  */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p4=i-1;
					  /* scan for space after button  */
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for command */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p6=i-1;

    k=pp1;
    bw_inkey1.strpcut(tmpc2,p1+1,p2-p1-1+1,SMG_SIZE,str2,SMG_SIZE);
    o=bw_inkey1.str2int(str2,SMG_SIZE);
    set_win_switch(k,0,1);
    set_win_switch(k,2,o);
    set_win_switch(k,3,wpp);

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      setc_win_switch_name(k,j-p3+0,tmpc2[j]);
      setc_win_switch_name(k,j-p3+1,0);
    }

    bw_inkey1.strpcut(tmpc2,p5,p6-p5+1,SMG_SIZE,str2,SMG_SIZE);
    l=bw_inkey1.str2int(str2,SMG_SIZE);
    set_win_switch(k,1,l);

    get_win_switch_name(k,st1,SMG_SIZE);

    if (bw_dialog1.w_mv_exist(st1,SMG_SIZE,wpp)==1)
    {
      bw_dialog1.w_mv_fet_val(st1,SMG_SIZE,0,str,SMG_SIZE);
      //bw_inkey1.strpcut(str,0,strlen(str)-1-0+1,SMG_SIZE,str2,SMG_SIZE);
      set_win_switch(k,1,bw_inkey1.str2int(str,SMG_SIZE));
    }

    pp1++;
  }

  win_switch_pp1=pp1;

  fclose(fp1);

  return(0);
}

int bw_switch::w_save_switch(int wpp)
{
  int  i,j;
  char str[SMG_SIZE];
  char st1[SMG_SIZE];

  //for (j=bw_win1.get_win_pp_grp_pp(bw_win1.get_win_pp_grp_id(wpp),0);j<=bw_win1.get_win_pp_grp_pp(bw_win1.get_win_pp_grp_id(wpp),2);j++)
  //{
    for (i=0;i<win_switch_pp1;i++)
    {
      //if (get_win_switch(i,3)>=j)
      //{
	bw_inkey1.int2str(get_win_switch(i,1),str,SMG_SIZE);
	get_win_switch_name(i,st1,SMG_SIZE);
	bw_dialog1.w_mv_save_mem(st1,SMG_SIZE,wpp,str,strlen(str));
      //}
    }
  //}

  return(0);
}

int bw_switch::tst_switch()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];
  char st1[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    get_win_switch_name(i,st1,SMG_SIZE);

    sprintf(str,"%d,%d,%d,%d,%s,%d,",get_win_switch(i,0)
				    ,get_win_switch(i,1)
				    ,get_win_switch(i,2)
				    ,get_win_switch(i,3)
				    ,st1
				    ,win_switch_pp1);
    TextOut(hdc,1,i*20,str,strlen(str));

  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_switch::w_dele_switch(int wp1,int wp2)
{
  int  i;
  int  p1,p2,p3,p4,p5,p6;
  char st1[SMG_SIZE];
/*
  p1=(-1);  // begin pp 
  p2=(-1);  // end pp 
  p3=0;     // end big win pp
  p4=0;     // mn cnt 
  p5=0;
  p6=0;

  for (i=0;i<=win_switch_pp1;i++)
  {
    if ((get_win_switch(i,3)>=wp1)&&(get_win_switch(i,3)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (get_win_switch(i,3)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (get_win_switch(i,3)>wp2)
    {
      p3=i;
    }
  }
  if (p2<0)
  {
    p2=win_switch_pp1+1;
    p3=p2-1;
  }

  if ((p1<0)||(p4==0))
  {
    for (i=p2;i<=p3;i++)
    {
      set_win_switch(i,3,get_win_switch(i,3)-wp2+wp1-1);
    }
  }
  else
  {
    for (i=p2;i<=p3;i++)
    {
      get_win_switch_name(i,st1,SMG_SIZE);
      set_win_switch_name(p1+i-p2,st1,SMG_SIZE);
      
      set_win_switch(p1+i-p2,0,get_win_switch(i,0));
      set_win_switch(p1+i-p2,1,get_win_switch(i,1));
      set_win_switch(p1+i-p2,2,get_win_switch(i,2));
      set_win_switch(p1+i-p2,3,get_win_switch(i,3)-wp2+wp1-1);
    }

    if (p3>=p2)
    {
      for (i=p1+p3-p2+1;i<=win_switch_pp1;i++)
      {
	setc_win_switch_name(i,0,0);
	set_win_switch(i,0,0);
	set_win_switch(i,1,0);
	set_win_switch(i,2,0);
	set_win_switch(i,3,0);
      }
      win_switch_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_switch_pp1;i++)
      {
	setc_win_switch_name(i,0,0);
	set_win_switch(i,0,0);
	set_win_switch(i,1,0);
	set_win_switch(i,2,0);
	set_win_switch(i,3,0);
      }
      win_switch_pp1=p1;
    }
  }
*/
  return(0);
}

int bw_switch::w_set_radio_var(int l,int c,int p,int wpp)
{
  int  i,j,k,m,o,t1,t2;
  int  t3;
  char str[SMG_SIZE];
  char str2[SMG_SIZE];

  t1=bw_win1.pline;
  t2=bw_win1.pfield;
  t3=(-1);

  bw_win1.pline =1;
  bw_win1.pfield=1;

  k=0;

  while (1)
  {
    i=bw_win1.pline;
    j=bw_win1.pfield;

    bw_win1.w_next_afield(wpp);

    if ((i==bw_win1.pline)&&(j==bw_win1.pfield)) break;

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_SIZE);

    if (str[0]=='(')
    {
      bw_inkey1.strpcut(str,1,strlen(str)-1-1+1,SMG_SIZE,str2,SMG_SIZE);
      o=bw_inkey1.str2int(str2,SMG_SIZE);
      if (o==p)
      {
	k++;
	if ((bw_win1.pline==l)&&(bw_win1.pfield==c))
        {
          for (m=0;m<MENU_NUM_RA;m++)
          {
	    if ((get_win_switch(m,2)==p)&&(get_win_switch(m,3)==wpp))
	    {
	      set_win_switch(m,1,k);
              t3=m;
	      break;
	    }
          }
	  o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	  SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)str);
	}
	else
	{
          o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	  SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)str);
	}
      }
    }
  }

  bw_win1.pline =t1;
  bw_win1.pfield=t2;

  return(t3);
}
int bw_switch::w_echo_winrec_radio(int wpp)
{
  int  i,j,o,m;
//  int  exist;
  int  arr[MENU_NUM_RA];
  char str[SMG_SIZE];
  char str2[SMG_SIZE];
//  char str3[SMG_SIZE];

  for (i=0;i<MENU_NUM_RA;i++) arr[i]=0;

  bw_win1.pline=1;
  bw_win1.pfield=1;

  i=0;
  j=0;

  while ((i!=bw_win1.pline)||(j!=bw_win1.pfield))
  {
    i=bw_win1.pline;
    j=bw_win1.pfield;

    bw_win1.w_next_afield(wpp);

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_SIZE);

    if (str[0]=='(')
    {

      bw_inkey1.strpcut(str,1,strlen(str)-1-1+1,SMG_SIZE,str2,SMG_SIZE);

      o=bw_inkey1.str2int(str2,SMG_SIZE);
      arr[o]++;

      for (m=0;m<MENU_NUM_RA;m++)
      {

	if ((get_win_switch(m,2)==o)&&(get_win_switch(m,3)==wpp))
	{
	  if (get_win_switch(m,1)==arr[o])
          {
            o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)str);
          }
          else
          {
            o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)str);
	  }
	  break;
	}
      }
    }
  }
  return(0);
}
int bw_switch::w_clr_recvar_radio(int wpp)
{
  int i;

  for (i=0;i<MENU_NUM_RA;i++)
  {
    set_win_switch(i,0,0);
    setc_win_switch_name(i,0,0);
  }

  win_switch_pp1=0;

  return(0);
}

int bw_dialog::w_read_ddc(char *p_fn1,int p_fn1_size,int wpp)
{
  int  i,j,k,l;
  int  p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
//  int  state2,state3;
//  int  state4,state5;
  int  pp1;
//  int  exist;
  char sfn1[FN_SIZE];
  char s_tmpc1[SMG_SIZE];
  char s_tmpc2[SMG_SIZE];
  char s_tmpc3[SMG_SIZE];
  char s_tmpc4[SMG_SIZE];
  char tmpc2[SMG_SIZE];
  char str[SMG_SIZE];
  char str2[SMG_SIZE];//--
  //char sd1[SMG_SIZE];
  int  wpp2;
  FILE *fp1;

  wpp2=wpp;

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.strlocc(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb2");

  //pp1=win_mv_pp1;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
	 for (i=0;i<SMG_SIZE;i++) tmpc2[i]=0;
	 fgets(tmpc2,SMG_SIZE,fp1);

	 if (strncmp(tmpc2,"&screenseg",7)==0)
	 {
	   wpp2++;
	   continue;
         }

	 for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>=0)) tmpc2[i]=' ';
						  /* scan for pre space */
	 for (i=0;i<SMG_SIZE;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
	 if (i>=SMG_SIZE) break;
	 p1=i;
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for memvarname*/
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p2=i-1;
					 /* scan for space after memvarname*/
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_SIZE)
	 {
           fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p3=i;
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for dtype   */
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p4=i-1;
					  /* scan for space after dtype   */
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p5=i;
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for type    */
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p6=i-1;
					  /* scan for space after type   */
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p7=i;

	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for len */
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p8=i-1;
					  /* scan for space after len */
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p9=i;

	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]==' ') break; /* scan for dec */
	 if (i>=SMG_SIZE)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p10=i-1;
					  /* scan for space after dec   */
	 for (i=i;i<SMG_SIZE;i++) if (tmpc2[i]!=' ') break;
	 if ((i>=SMG_SIZE)||(tmpc2[i]!='"'))
	 {
	   p11=0;
	   p12=0;
	 }
	 else
	 {
	   p11=i;
	   for (i=i+1;i<SMG_SIZE;i++) if (tmpc2[i]=='"') break; /* scan for val */
	   if (i>=SMG_SIZE)
	   {
	     fclose(fp1);
	     bw_win1.w_atten38(sfn1);
	     return(1);
	   }
	   p12=i;
	 }

	 for (j=p1;j<=p2;j++)
	 {
	   if (tmpc2[j]==' ') break;
	   s_tmpc1[j-p1+0]=tmpc2[j];
	   s_tmpc1[j-p1+1]=0;
	 }
	 if (w_mv_exist(s_tmpc1,SMG_SIZE,0)==0) k=w_mv_add_name(s_tmpc1,SMG_SIZE);
	 else k=w_mv_seri(s_tmpc1,SMG_SIZE,0);

	 if (k>=0)
	 {
	   if (p3==p4)
	   {
	     if (tmpc2[p3]=='e')  set_win_mv_type(k,0,2);
	     else
	     {
	       if (tmpc2[p3]=='d') set_win_mv_type(k,0,1);
	       else set_win_mv_type(k,0,2);
	     }
	   }

	   if (p6==p5)
	   {
	     set_win_mv_type(k,1,tmpc2[p5]);
	   }

	   bw_inkey1.strpcut(tmpc2,p7,p8-p7+1,SMG_SIZE,str2,SMG_SIZE);
	   l=bw_inkey1.str2int(str2,SMG_SIZE);
	   set_win_mv_type(k,2,l);

	   bw_inkey1.strpcut(tmpc2,p9,p10-p9+1,SMG_SIZE,str2,SMG_SIZE);
	   l=bw_inkey1.str2int(str2,SMG_SIZE);
	   set_win_mv_type(k,3,l);
	   set_win_mv_type(k,4,0);

	   if (p11==0)
	   {
             s_tmpc4[0]=0;
	     w_mv_add_val(s_tmpc1,SMG_SIZE,wpp2,s_tmpc4,SMG_SIZE);
	   }
	   else
	   {
	     if ((tmpc2[p11]=='"')&&(tmpc2[p12]=='"'))
	     {
	       for (j=p11;j<=p12;j++)
	       {
		 s_tmpc2[j-p11+0]=tmpc2[j];
		 s_tmpc2[j-p11+1]=0;
	       }
	       bw_inkey1.strpcut(s_tmpc2,1,strlen(s_tmpc2)-2,SMG_SIZE,s_tmpc3,SMG_SIZE);
	       w_mv_add_val(s_tmpc1,SMG_SIZE,wpp2,s_tmpc3,SMG_SIZE);
	     }
	     else
	     {
               s_tmpc4[0]=0;
	       w_mv_add_val(s_tmpc1,SMG_SIZE,wpp2,s_tmpc4,SMG_SIZE);
	     }
	   }

           if (w_mv_exist(s_tmpc1,SMG_SIZE,wpp2)==1)
           {
             w_mv_fet_val(s_tmpc1,SMG_SIZE,   0,str,SMG_SIZE);
             w_mv_add_val(s_tmpc1,SMG_SIZE,wpp2,str,SMG_SIZE);
	   }

	   //pp1++;
	 }

  }

  fclose(fp1);

  //win_mv_pp1=pp1;  //bug , can't modify win_mv_pp1 

  return(0);
}

int bw_dialog::w_save_dialog(int wpp)
{
  int  i,j,k,l;
  char str[SMG_SIZE];
  char sv1[SMG_SIZE];
/*
  for (j=bw_win1.get_win_pp_grp_pp(bw_win1.get_win_pp_grp_id(wpp),0);j<=bw_win1.get_win_pp_grp_pp(bw_win1.get_win_pp_grp_id(wpp),2);j++)
  {
    for (i=0;i<=win_mv_pp1;i++)
    {
      if (get_win_mv_type(i,4)==j)
      {
        get_win_mv_name(i,sv1,SMG_SIZE);
	k=w_mv_fet_val(sv1,SMG_SIZE,j,str,SMG_SIZE);
        l=get_win_mv_type(i,2);
	if (k==0) w_mv_save_mem(sv1,SMG_SIZE,wpp,str,l);
      }
    }
  }
*/
  return(0);
}

int bw_dialog::w_mv_save_mem(char *p_str,int p_str_size,int wpp,char *val,int val_size)
{
  int  i,k;
  char sd1[1000];
  char sv1[SMG_SIZE];

  wpp=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_save_mem(),p_str=%s,p_str_size=%d,wpp=%d,val=%s,val_size=%d,",p_str,p_str_size,wpp,val,val_size);
    bw_getread1.deb_record(sd1);
  }

  bw_main1.set_string(sv1,SMG_SIZE,val,val_size);

  val_size=(int)strlen(sv1);

  if (val_size<=0) // set empty string
  {
	  sv1[0]=' ';
	  sv1[1]=0;
	  val_size=1;
  }

  if (w_mv_exist(p_str,p_str_size,wpp)==0)
  {
    k=w_mv_add_name(p_str,p_str_size);
    if (k>=0)
    {
      set_win_mv_type(k,0,2);            /* edit able   */
      set_win_mv_type(k,1,'c');          /* var type    */
      set_win_mv_type(k,2,val_size);     /* var len     */      //remember
      set_win_mv_type(k,3,0);            /* dec is zero */
      set_win_mv_type(k,4,wpp);          /* free window var */
    }
  }
  else
  {
    k=w_mv_seri(p_str,p_str_size,wpp);
    if (k>=0)
    {
      set_win_mv_type(k,2,val_size);         /* var len */      //remember
    }
  }

  w_mv_add_val(p_str,p_str_size,wpp,sv1,val_size);

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_save_mem(),win_mv_pp1=%d,win_mv_pp2=%d,",win_mv_pp1,win_mv_pp2);
    bw_getread1.deb_record(sd1);
  }

  return(0);
}                 

int bw_dialog::w_dele_dialog(int wp1,int wp2)
{
  char sv1[SMG_SIZE];
//  char str[SMG_SIZE];
  int  i;
  int  p1,p2,p3,p4,p5,p6,p7,p8,p9;
/*
  p1=(-1);  // begin pp
  p2=(-1);  // end pp
  p3=0;     // end big win pp
  p4=0;     // mn cnt
  p5=0;
  p6=0;
  p7=(-1);
  p8=(-1);
  p9=0;

  for (i=0;i<=win_mv_pp1;i++)
  {
    if ((get_win_mv_type(i,4)>=wp1)&&(get_win_mv_type(i,4)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if ((get_win_mv_type(i,4)>wp2)||(get_win_mv_type(i,4)<wp1))
    {
      if ((p6==0)&&(p1>=0)) // first after p1+p4 item 
      {
	p2=i;
	p6=1;
      }
    }
    if ((get_win_mv_type(i,4)>wp2)||(get_win_mv_type(i,4)<wp1))
    {
      if ((p1>=0)&&(get_win_mv_type(i,0)!=0))
      {
	p3=i;
      }
    }
    if (get_win_mv_type(i,4)>wp2)
    {
      if (p9==0) 
      {
	p7=i;
	p9=1;
      }
    }
    if (get_win_mv_type(i,4)>wp2)
    {
      p8=i;
    }
  }

  if ((p1<0)||(p4==0))
  {
    p2=p7;
    p3=p8;

    if (p2>=0)
    {
      for (i=p2;i<=p3;i++)
      {
	if (get_win_mv_type(i,4)!=0) set_win_mv_type(i,4,get_win_mv_type(i,4)-wp2+wp1-1);
      }
    }
  }
  else
  {
    if ((p2>=0)&&(p3>=p2))
    {
      p7=get_win_mv_posi(p1,0);
      p8=get_win_mv_posi(p2,0);
      p9=get_win_mv_posi(p3,0)+get_win_mv_posi(p3,1)-1;

      for (i=p8;i<=p9;i++)
      {
        set_win_mv_stor(p7+i-p8,get_win_mv_stor(i));
      }

      win_mv_pp2=p7+p9-p8+1;

      for (i=p2;i<=p3;i++)
      {
	get_win_mv_name(i,sv1,SMG_SIZE);
        set_win_mv_name(p1+i-p2,sv1,SMG_SIZE);

	set_win_mv_type(p1+i-p2,0,get_win_mv_type(i,0));
	set_win_mv_type(p1+i-p2,1,get_win_mv_type(i,1));
	set_win_mv_type(p1+i-p2,2,get_win_mv_type(i,2));
	set_win_mv_type(p1+i-p2,3,get_win_mv_type(i,3));

	if (get_win_mv_type(i,4)==0) set_win_mv_type(p1+i-p2,4,0);
	else set_win_mv_type(p1+i-p2,4,get_win_mv_type(i,4)-wp2+wp1-1);

	set_win_mv_type(p1+i-p2,5,get_win_mv_type(i,5));

	if (get_win_mv_posi(i,0)==0) set_win_mv_posi(p1+i-p2,0,0);
	else set_win_mv_posi(p1+i-p2,0,get_win_mv_posi(i,0)-p8+p7);

	set_win_mv_posi(p1+i-p2,1,get_win_mv_posi(i,1));
      }

      for (i=p1+p3-p2+1;i<=win_mv_pp1;i++)
      {
	setc_win_mv_name(i,0,0);

	set_win_mv_type(i,0,0);
	set_win_mv_type(i,1,0);
	set_win_mv_type(i,2,0);
	set_win_mv_type(i,3,0);
	set_win_mv_type(i,4,0);
	set_win_mv_type(i,5,0);

	set_win_mv_posi(i,0,0);
	set_win_mv_posi(i,1,0);
      }
      win_mv_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_mv_pp1;i++)
      {
	setc_win_mv_name(i,0,0);
	set_win_mv_type(i,0,0);
	set_win_mv_type(i,1,0);
	set_win_mv_type(i,2,0);
	set_win_mv_type(i,3,0);
	set_win_mv_type(i,4,0);
	set_win_mv_type(i,5,0);

	set_win_mv_posi(i,0,0);
	set_win_mv_posi(i,1,0);
      }
      win_mv_pp1=p1;
    }
  }
*/
  return(0);
}

int bw_dialog::w_clr_recvar_dialog(int wpp)
{
  int i;

  win_mv_pp1=0;
  win_mv_pp2=0;

  return(0);
}


int bw_dialog::tst_mem()
{
  HDC  hdc;
  char str[SMG_SIZE*2];
  char sv1[SMG_SIZE];
  int  i,j;

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    TextOut(hdc,1,i*20,sv1,20);

    sprintf(str,"type024=%5d,%5d,%5d,",get_win_mv_type(i,0),get_win_mv_type(i,2),get_win_mv_type(i,4));
    TextOut(hdc,100,i*20,str,strlen(str));

    sprintf(str,"posi01=%5d,%5d,",get_win_mv_posi(i,0),get_win_mv_posi(i,1));
    TextOut(hdc,300,i*20,str,strlen(str));

//    bw_inkey1.strpcut(win_mv_stor,get_win_mv_posi(i,0),get_win_mv_posi(i,1),str);

    str[0]=0;
    for (j=get_win_mv_posi(i,0);j<get_win_mv_posi(i,0)+get_win_mv_posi(i,1);j++)
    {
      str[j-get_win_mv_posi(i,0)]=get_win_mv_stor(j);
      str[j-get_win_mv_posi(i,0)+1]=0;
    }

    TextOut(hdc,444,i*20,str,strlen(str));

    sprintf(str,"pp1=%d,",win_mv_pp1);
    TextOut(hdc,500,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_dialog::w_mv_add_val(char *p_s1,int p_s1_size,int wpp,char *p_s2,int p_s2_size)
{
  int  i,j,k,l;
  int  exist;
  char s3[SMG_SIZE];
  char sv1[SMG_SIZE];
  //char s5[SMG_SIZE];
  char sd1[1000];

  wpp=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_add_val(),p_s1=%s,p_s1_size=%d,wpp=%d,p_s2=%s,p_s2_size=%d,",p_s1,p_s1_size,wpp,p_s2,p_s2_size);
    bw_getread1.deb_record(sd1);
  }

  strcpy(s3,p_s2);

  exist=0;

  for (i=0;i<win_mv_pp1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);
    if ((strcmp(p_s1,sv1)==0)&&(get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }

  if (exist==0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_add_val(),exist=%d,win_mv_pp1=%d,win_mv_pp2=%d,",exist,win_mv_pp1,win_mv_pp2);
      bw_getread1.deb_record(sd1);
    }

    return(1);
  }

  if (i<=0) set_win_mv_posi(i,0,0);
  //else set_win_mv_posi(i,0,get_win_mv_posi(i-1,0)+get_win_mv_posi(i-1,1));

  for (j=strlen(s3);j<get_win_mv_type(i,2);j++)
  {
    s3[j+0]=' ';
    s3[j+1]=0;
  }
  //s3[get_win_mv_type(i,2)]=0;

  k=get_win_mv_type(i,2);
  j=get_win_mv_posi(i,1)-k;
  l=0;

  if (j<0) l=w_mv_move_aft(0-j,i);
  if (j>0) l=w_mv_move_bef(  j,i);
  if (l!=0) 
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_add_val(),move bef or aft error,win_mv_pp1=%d,win_mv_pp2=%d,",exist,win_mv_pp1,win_mv_pp2);
      bw_getread1.deb_record(sd1);
    }

    return(1);
  }

  set_win_mv_posi(i,1,k);

  for (j=0;j<k;j++)
  {
    set_win_mv_stor(get_win_mv_posi(i,0)+j,s3[j]);
  }

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_add_val(),win_mv_pp1=%d,win_mv_pp2=%d,posi(i,0)(mvar_pp)=%d,posi(i,1)(mvar_len)=%d,",win_mv_pp1,win_mv_pp2,get_win_mv_posi(i,0),get_win_mv_posi(i,1));
    bw_getread1.deb_record(sd1);
  }

  return(0);
}

int bw_dialog::w_mv_fet_val(char *p_s1,int p_s1_size,int wpp,char *p_s2,int p_s2_size)
{
  int  i,j;
  int  exist;
  char sd1[1000];
  char sv1[SMG_SIZE];

  wpp=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_fet_val(),p_s1=%s,p_s1_size=%d,wpp=%d,",p_s1,p_s1_size,wpp);
    bw_getread1.deb_record(sd1);
  }

  p_s2[0]=0;

  exist=0;

  for (i=0;i<win_mv_pp1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    if ((strcmp(p_s1,sv1)==0)&&(get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }

  if (exist==0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_fet_val(),exist==0,");
      bw_getread1.deb_record(sd1);
    }

    return(1);
  }

  for (j=0;j<get_win_mv_posi(i,1);j++)
  {
    if (j<p_s2_size-1)
    {
      p_s2[j+0]=get_win_mv_stor(get_win_mv_posi(i,0)+j);
      p_s2[j+1]=0;
    }
  }

/*
  if (get_win_mv_posi(i,1)<p_s2_size)
  {
    p_s2[get_win_mv_posi(i,1)]=0;
  }
  else
  {
    p_s2[p_s2_size-1]=0;
  }
*/

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_fet_val(),return val=%s,posi(i,0)(mvar_pp)=%d,posi(i,1)(mvar_len)=%d,",p_s2,get_win_mv_posi(i,0),get_win_mv_posi(i,1));
    bw_getread1.deb_record(sd1);
  }

  return(0);
}

int bw_dialog::w_mv_exist(char *p_s1,int p_s1_size,int wpp)
{
  int  i;
  int  exist;
  char sd1[1000];
  char sv1[SMG_SIZE];

  wpp=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_exist(),p_s1=%s,p_s1_size=%d,wpp=%d,",p_s1,p_s1_size,wpp);
    bw_getread1.deb_record(sd1);
  }

  exist=0;

  for (i=0;i<win_mv_pp1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    if ((strcmp(p_s1,sv1)==0)&&(get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_exist(),exist=%d,",exist);
    bw_getread1.deb_record(sd1);
  }

  return(exist);
}
int bw_dialog::w_mv_add_name(char *p_s1,int p_s1_size)
{
  char sd1[1000];
  char str[SMG_SIZE];
  int  i;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_add_name(),p_s1=%s,p_s1_size=%d,",p_s1,p_s1_size);
    bw_getread1.deb_record(sd1);
  }

  set_win_mv_name(win_mv_pp1,p_s1,p_s1_size);

  if (win_mv_pp1<=0)// ---bug ok---
  {
    set_win_mv_posi(win_mv_pp1,0,0);
    set_win_mv_posi(win_mv_pp1,1,0);

    if (DEBUG_MV)
    {
      sprintf(sd1,"===set posi(i,0) val , win_mv_pp1=%d,posi(i,0)(mvar_pp)=%d,",win_mv_pp1,get_win_mv_posi(win_mv_pp1,0));
      bw_getread1.deb_record(sd1);
    }
  }
  else
  {
    set_win_mv_posi(win_mv_pp1,0,get_win_mv_posi(win_mv_pp1-1,0)+get_win_mv_posi(win_mv_pp1-1,1));
    set_win_mv_posi(win_mv_pp1,1,0);

    if (DEBUG_MV)
    {
      sprintf(sd1,"===set posi(i,0) val , win_mv_pp1=%d,posi(i,0)(mvar_pp)=%d,",win_mv_pp1,get_win_mv_posi(win_mv_pp1,0));
      bw_getread1.deb_record(sd1);
    }
  }

  i=win_mv_pp1;

  win_mv_pp1++; /* point empty array */
  if (win_mv_pp1>=MEM_VAR) win_mv_pp1--;

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_add_name(),return val=%d,",i);
    bw_getread1.deb_record(sd1);
  }

  return(i);
}
int bw_dialog::w_mv_seri(char *p_s1,int p_s1_size,int wpp)
{
  int  i,j;
  int  exist;
  char sd1[1000];
  char sv1[SMG_SIZE];

  wpp=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_seri(),p_s1=%s,p_s1_size=%d,wpp=%d,",p_s1,p_s1_size,wpp);
    bw_getread1.deb_record(sd1);
  }

  exist=0;

  for (i=0;i<win_mv_pp1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    if ((strcmp(p_s1,sv1)==0)&&(get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }

  if (exist==1) j=i;
  else j=(-1);

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_seri(),return val=%d,",j);
    bw_getread1.deb_record(sd1);
  }

  if (exist==1) return(i);
  else return(-1);
}
int bw_dialog::w_mv_move_aft(int dd,int num)
{
  int  i,j;
  char sd1[1000];

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_move_aft(),dd(range)=%d,num(mvar_pp)=%d,",dd,num);
    bw_getread1.deb_record(sd1);
  }

  if (dd<=0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_move_aft(),dd(range)<=0,");
      bw_getread1.deb_record(sd1);
    }
    return(0);
  }

  if (win_mv_pp2+dd>=MEM_LEN)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_move_aft(),win_mv_pp2>=MEM_LEN,");
      bw_getread1.deb_record(sd1);
    }
    return(1);
  }
  else win_mv_pp2=win_mv_pp2+dd;

  for (i=win_mv_pp1-1;i>num;i--)
  {
/*  ---bug---
    for (j=get_win_mv_posi(i,0);j<get_win_mv_posi(i,0)+get_win_mv_posi(i,1);j++)
    {
      set_win_mv_stor(j+dd,get_win_mv_stor(j));
    }
*/
    for (j=get_win_mv_posi(i,0)+get_win_mv_posi(i,1)-1;j>=get_win_mv_posi(i,0);j--)
    {
      set_win_mv_stor(j+dd,get_win_mv_stor(j));
    }

    if (DEBUG_MV)
    {
      sprintf(sd1,"---move aft i=%d,posi(i,0)=%d,dd(range)=%d,",i,get_win_mv_posi(i,0),dd);
      bw_getread1.deb_record(sd1);
    }

    set_win_mv_posi(i,0,get_win_mv_posi(i,0)+dd);

    if (DEBUG_MV)
    {
      sprintf(sd1,"---move aft new posi(i,0)=%d,",get_win_mv_posi(i,0));
      bw_getread1.deb_record(sd1);
    }
  }

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_move_aft(),");
    bw_getread1.deb_record(sd1);
  }

  return(0);
}
int bw_dialog::w_mv_move_bef(int dd,int num)
{
  int  i,j;
  char sd1[1000];

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_move_bef(),dd(range)=%d,num(mvar_pp)=%d,",dd,num);
    bw_getread1.deb_record(sd1);
  }

  if (dd<=0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_move_bef(),dd(range)<=0,");
      bw_getread1.deb_record(sd1);
    }
    return(0);
  }

  if (win_mv_pp2-dd<0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_move_bef(),win_mv_pp2<0,");
      bw_getread1.deb_record(sd1);
    }
    return(1);
  }
  else win_mv_pp2=win_mv_pp2-dd;

  for (i=num+1;i<win_mv_pp1;i++)
  {
    for (j=get_win_mv_posi(i,0);j<get_win_mv_posi(i,0)+get_win_mv_posi(i,1);j++)
    {
      set_win_mv_stor(j-dd,get_win_mv_stor(j));
    }

    if (DEBUG_MV)
    {
      sprintf(sd1,"---move bef i=%d,posi(i,0)=%d,dd(range)=%d,",i,get_win_mv_posi(i,0),dd);
      bw_getread1.deb_record(sd1);
    }

    set_win_mv_posi(i,0,get_win_mv_posi(i,0)-dd);

    if (DEBUG_MV)
    {
      sprintf(sd1,"---move bef new posi(i,0)=%d,",get_win_mv_posi(i,0));
      bw_getread1.deb_record(sd1);
    }
  }

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_move_bef(),");
    bw_getread1.deb_record(sd1);
  }

  return(0);
}

int bw_dialog::w_mv_sav_var(char *p_s1,int p_s1_size,int wpp)
{
//  HDC    hdc;
  char   sm1[SMG_SIZE];
  //char   sd1[SMG_SIZE];
  int    i,j;

  if (w_mv_exist(p_s1,p_s1_size,wpp)!=1) return(1);

  i=w_mv_seri(p_s1,p_s1_size,wpp);

  j=get_win_mv_type(i,2);

  setc_win_mv_getv(wpp,j,0);

  get_win_mv_getv(wpp,sm1,SMG_SIZE);

  w_mv_add_val(p_s1,p_s1_size,wpp,sm1,SMG_SIZE);

  return(0);
}

int bw_dialog::w_mv_get_var(char *p_s1,int p_s1_size,int wpp)
{
//  HDC    hdc;
  char   sm1[SMG_SIZE];
  //char   sd1[SMG_SIZE];
  //int    i,j;

  w_mv_fet_val(p_s1,p_s1_size,wpp,sm1,SMG_SIZE);

  set_win_mv_getv(wpp,sm1,SMG_SIZE);

  return(0);
}

int bw_dialog::w_echo_winrec_var(int wpp)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  HWND  hnd;
  int  i,j,k,l,q;
  char str[SMG_SIZE];
  char str2[SMG_SIZE];
  int  len,len2,len3;

  hdc=GetDC(bw_main1.win_hwnd);

  if (bw_win1.get_win_ci_mode(wpp)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  HideCaret(bw_main1.win_hwnd);

  bw_win1.pline=1;
  bw_win1.pfield=1;

  while (1)
  {
    i=bw_win1.pline;
    j=bw_win1.pfield;

    bw_win1.w_next_afield(wpp);

    if ((i==bw_win1.pline)&&(j==bw_win1.pfield)) break;

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_SIZE);

    if ((str[0]=='?')||(str[0]=='-'))
    {
      if (w_mv_exist(str,SMG_SIZE,wpp)!=1) continue;

      k=w_mv_seri(str,SMG_SIZE,wpp);
      if (k>=0)
      {
	if (get_win_mv_type(k,0)!=2)
	  bw_win1.w_set_winfedit(wpp,bw_win1.pline,bw_win1.pfield,1);

        w_mv_fet_val(str,SMG_SIZE,wpp,str2,SMG_SIZE);

	len =get_win_mv_type(k,2);

	len2=bw_win1.w_find_winflen(wpp,bw_win1.pline,bw_win1.pfield);

        len3=strlen(str2);

	if (len2>len) l=len;
        else  l=len2;

	set_win_mv_type(k,5,l);

        if (len3<l) l=len3;

	if (str[0]=='?')
        {
	  if (bw_win1.get_win_ci_mode(wpp)==0)
          {
	    TextOut(hdc
		   ,(int)((bw_win1.pfield-bw_win1.get_win_con(wpp,0))*bw_main1.win_edit_xchar)
		   ,(int)((bw_win1.pline-bw_win1.get_win_con(wpp,1))*bw_main1.win_edit_ychar)
		   ,str2,l);
	  }
	  else
	  {
	    TextOut(hdc
		   ,(int)((bw_win1.pfield-bw_win1.get_win_con(wpp,0))*bw_main1.win_xchar)
		   ,(int)((bw_win1.pline-bw_win1.get_win_con(wpp,1))*bw_main1.win_ychar)
		   ,str2,l);
	  }
	}
	else
	{
	  q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	  if (q!=0)
	  {
            hnd=bw_win1.get_win_hnd(q);
	    SetWindowText(hnd,str2);
          }
        }
      }
    }
  }

  ShowCaret(bw_main1.win_hwnd);

  if (bw_win1.get_win_ci_mode(wpp)==0)
  {
    SelectObject(hdc,holdfont);
  }

  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}
int bw_dialog::w_mv_get_read_paint(char *p_str,int p_str_size,int wpp,char comm)
{
  HWND hnd;
  int  i,j,q;
  char sm1[SMG_SIZE];
  //char sd1[SMG_SIZE];

  if ((p_str[0]!='?')&&(p_str[0]!='-')) return(1);

  if (w_mv_exist(p_str,p_str_size,wpp)!=1) return(1);

  w_mv_get_var(p_str,p_str_size,wpp);

  i=w_mv_seri(p_str,p_str_size,wpp);

  get_win_mv_getv(wpp,sm1,SMG_SIZE);

  if (p_str[0]=='?')
  {
    j=bw_getread1.get_read(bw_win1.pline-bw_win1.get_win_con(wpp,1)+1,
		       bw_win1.pfield-bw_win1.get_win_con(wpp,0)+1,
		       "",
		       sm1,
		       get_win_mv_type(i,5),
		       get_win_mv_type(i,1),
		       comm,
		       get_win_mv_type(i,2),
		       get_win_mv_type(i,3),
		       1,1,
		       get_win_mv_getp(wpp),
		       bw_win1.get_win_pp_get_rd(wpp));

  }
  else
  {
    q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
    if (q!=0)
    {
      hnd=bw_win1.get_win_hnd(q);
      SetWindowText(hnd,sm1);
    }
  }

  return(j);
}
int bw_dialog::w_mv_get_read_g(char *p_str,int p_str_size,int wpp,char comm)
{
  HWND hnd;
  int  i,j,q;
  char sm1[SMG_SIZE];
  //char sd1[SMG_SIZE];

  if ((p_str[0]!='?')&&(p_str[0]!='-')) return(1);

  if (w_mv_exist(p_str,p_str_size,wpp)!=1) return(1);

  w_mv_get_var(p_str,p_str_size,wpp);

  i=w_mv_seri(p_str,p_str_size,wpp);

  get_win_mv_getv(wpp,sm1,SMG_SIZE);

  if (p_str[0]=='?')
  {
    j=bw_getread1.get_read(bw_win1.pline-bw_win1.get_win_con(wpp,1)+1,
		       bw_win1.pfield-bw_win1.get_win_con(wpp,0)+1,
		       "",
		       sm1,
		       get_win_mv_type(i,5),
		       get_win_mv_type(i,1),
		       comm,
		       get_win_mv_type(i,2),
		       get_win_mv_type(i,3),
		       1,1,
		       get_win_mv_getp(wpp),
		       bw_win1.get_win_pp_get_rd(wpp));

    if ((GetFocus()==bw_win1.get_win_phh(wpp))||(bw_win1.get_ci_mhnd(GetFocus())==bw_win1.get_win_phh(wpp)))
    {
      SetFocus(bw_win1.get_win_phh(wpp));
    }
  }
  else
  {
    q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
    if (q!=0)
    {
      hnd=bw_win1.get_win_hnd(q);
      SetWindowText(hnd,sm1);
      if (bw_main1.win_key!=401) SetFocus(hnd);
    }
  }

  return(j);
}
int bw_dialog::w_mv_get_read_r(char *p_str,int p_str_size,int wpp,char comm)
{
  int  i,j;
  char sm1[SMG_SIZE];
  //char sd1[SMG_SIZE];

  if (p_str[0]!='?') return(1);

  if (w_mv_exist(p_str,p_str_size,wpp)!=1) return(1);

  i=w_mv_seri(p_str,p_str_size,wpp);

  get_win_mv_getv(wpp,sm1,SMG_SIZE);

  j=bw_getread1.get_read(bw_win1.pline-bw_win1.get_win_con(wpp,1)+1,
		       bw_win1.pfield-bw_win1.get_win_con(wpp,0)+1,
		       "",
		       sm1,
		       get_win_mv_type(i,5),
		       get_win_mv_type(i,1),
		       comm,
		       get_win_mv_type(i,2),
		       get_win_mv_type(i,3),
		       1,1,
		       get_win_mv_getp(wpp),
		       bw_win1.get_win_pp_get_rd(wpp));

  return(j);
}

int bw_dialog::w_echo_winrec_read(int p_fcnt,int wpp,int mark)
{
  HFONT  holdfont,hfont;
  HDC    hdc;

//  long s_fldrecno;
  int  i,j,k,l,m,n,o;
  int  exist;
//  int  s_state1;
  int  s_tmpn3;
//  int  pp1,pp2;
  char s_tmpc1[30][30];
  int  s_tmpn2[30];
  char s_tmpc2[SMG_SIZE];
//  char s_fldtable[SMG_SIZE];
//  char s_fldname[SMG_SIZE];
  char str[FLD_NAME_LEN];

  strcpy(s_tmpc1[1],"*y");
  s_tmpn2[1]=2;
  strcpy(s_tmpc1[2],"*m");
  s_tmpn2[2]=2;
  strcpy(s_tmpc1[3],"*d");
  s_tmpn2[3]=2;
  strcpy(s_tmpc1[4],"*yr");
  s_tmpn2[4]=4;
  strcpy(s_tmpc1[5],"*o");
  s_tmpn2[5]=3;
  strcpy(s_tmpc1[6],"*time");
  s_tmpn2[6]=8;
  strcpy(s_tmpc1[7],"*usr");
  s_tmpn2[7]=10;
  strcpy(s_tmpc1[8],"*recno");
  s_tmpn2[8]=6;
  strcpy(s_tmpc1[9],"*recnum");
  s_tmpn2[9]=6;

  s_tmpn3=10;

  hdc=GetDC(bw_main1.win_hwnd);
  if (bw_win1.get_win_ci_mode(wpp)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(wpp,i,j)!=0)
      {
	k=bw_buff1.get_linecol(wpp,i,j);

	bw_win1.get_1fldname(k,str,FLD_NAME_LEN);

	if (str[0]=='*')
	{
          exist=0;
	  for (m=1;m<=s_tmpn3;m++)
	  {
	    if (strcmp(str,s_tmpc1[m])==0)
	    {
	      exist=1;
	      break;
	    }
	  }

	  if (exist==0) continue;

	  if ((mark<10)&&((m==1)||(m==2)||(m==3)||(m==4)||(m==5)||(m==7))) continue;

	  if (m==1)  w_get_yy(s_tmpc2,30);
	  if (m==2)  w_get_mm(s_tmpc2,30);
	  if (m==3)  w_get_dd(s_tmpc2,30);
	  if (m==4)  w_get_year(s_tmpc2,30);
	  if (m==5)  w_get_mon(s_tmpc2,30);
	  if (m==6)  w_get_time(s_tmpc2,30);
	  if (m==7)  w_get_usr(s_tmpc2,30);
	  if (m==8)  bw_inkey1.long2str(bw_xbase1.get_win_recno(p_fcnt,wpp,0),s_tmpc2,SMG_SIZE);
	  if (m==9)  bw_inkey1.long2str(bw_xbase1.get_win_rcnt(p_fcnt),s_tmpc2,SMG_SIZE);

	  if (strlen(str)>strlen(s_tmpc2)) l=strlen(s_tmpc2);
	  else l=bw_win1.get_1fldlen(k);

	  if (bw_win1.get_1fldlen(k)>s_tmpn2[m]) n=s_tmpn2[m];
	  else n=bw_win1.get_1fldlen(k);

	  if (n>l)
	  {
	    for (o=l;o<n;o++) s_tmpc2[o]=' ';
            s_tmpc2[n]=0;
          }

	  if (bw_win1.get_win_ci_mode(wpp)==0)
	      TextOut(hdc
		     ,(int)((j-bw_win1.get_win_con(wpp,0))*bw_main1.win_edit_xchar)
			 ,(int)((i-bw_win1.get_win_con(wpp,1))*bw_main1.win_edit_ychar)
			 ,s_tmpc2,n);
	  else
	      TextOut(hdc
		     ,(int)((j-bw_win1.get_win_con(wpp,0))*bw_main1.win_xchar)
			 ,(int)((i-bw_win1.get_win_con(wpp,1))*bw_main1.win_ychar)
			 ,s_tmpc2,n);

	}
      }
    }
  }

  if (bw_win1.get_win_ci_mode(wpp)==0)
  {
    SelectObject(hdc,holdfont);
  }
  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}

int bw_dialog::w_get_yy(char *p_s1,int p_s1_size)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_SIZE];
  if (p_s1_size<10) return(0);
  for (i=0;i<3;i++) p_s1[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_s1[0]=s_tmpc3[22];
  p_s1[1]=s_tmpc3[23];
*/
  return(0);
}

int bw_dialog::w_get_mm(char *p_s1,int p_s1_size)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_SIZE];
  char s_tmpc4[4];
  char s_tmpc5[SMG_SIZE];
  if (p_s1_size<10) return(0);
  for (i=0;i<3;i++) p_s1[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  s_tmpc4[0]=s_tmpc3[4];
  s_tmpc4[1]=s_tmpc3[5];
  s_tmpc4[2]=s_tmpc3[6];
  s_tmpc4[3]=0;
  i=0;
  if (strcmp(s_tmpc4,"Jan")==0) i=1;
  if (strcmp(s_tmpc4,"Feb")==0) i=2;
  if (strcmp(s_tmpc4,"Mar")==0) i=3;
  if (strcmp(s_tmpc4,"Apr")==0) i=4;
  if (strcmp(s_tmpc4,"May")==0) i=5;
  if (strcmp(s_tmpc4,"Jun")==0) i=6;
  if (strcmp(s_tmpc4,"Jul")==0) i=7;
  if (strcmp(s_tmpc4,"Aug")==0) i=8;
  if (strcmp(s_tmpc4,"Sep")==0) i=9;
  if (strcmp(s_tmpc4,"Oct")==0) i=10;
  if (strcmp(s_tmpc4,"Nov")==0) i=11;
  if (strcmp(s_tmpc4,"Dec")==0) i=12;
  bw_inkey1.int2str(i,s_tmpc5,SMG_SIZE);
  p_s1[0]=s_tmpc5[ 9];
  p_s1[1]=s_tmpc5[10];
*/
  return(0);
}

int bw_dialog::w_get_dd(char *p_s1,int p_s1_size)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_SIZE];
  if (p_s1_size<10) return(0);
  for (i=0;i<3;i++) p_s1[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_s1[0]=s_tmpc3[8];
  p_s1[1]=s_tmpc3[9];
*/
  return(0);
}

int bw_dialog::w_get_year(char *p_s1,int p_s1_size)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_SIZE];
  if (p_s1_size<10) return(0);
  for (i=0;i<4;i++) p_s1[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_s1[0]=s_tmpc3[20];
  p_s1[1]=s_tmpc3[21];
  p_s1[2]=s_tmpc3[22];
  p_s1[3]=s_tmpc3[23];
*/
  return(0);
}

int bw_dialog::w_get_mon(char *p_s1,int p_s1_size)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_SIZE];
  if (p_s1_size<10) return(0);
  for (i=0;i<3;i++) p_s1[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_s1[0]=s_tmpc3[4];
  p_s1[1]=s_tmpc3[5];
  p_s1[2]=s_tmpc3[6];
*/
  return(0);
}

int bw_dialog::w_get_time(char *p_s1,int p_s1_size)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_SIZE];
  if (p_s1_size<10) return(0);
  for (i=0;i<8;i++) p_s1[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_s1[0]=s_tmpc3[11];
  p_s1[1]=s_tmpc3[12];
  p_s1[2]=s_tmpc3[13];
  p_s1[3]=s_tmpc3[14];
  p_s1[4]=s_tmpc3[15];
  p_s1[5]=s_tmpc3[16];
  p_s1[6]=s_tmpc3[17];
  p_s1[7]=s_tmpc3[18];
*/
  return(0);
}

int bw_dialog::w_get_usr(char *p_s1,int p_s1_size)
{
  int i;
  if (p_s1_size<30) return(0);
  for (i=0;i<30;i++) p_s1[i]=' ';
  strcpy(p_s1,"DaiPoZhi");
  return(0);
}





int bw_dialog::get_win_mv_stor(int mlpp)
{
  if ((mlpp<0)||(mlpp>=MEM_LEN)) return(0);
  return(win_mv_stor[mlpp]);
}
int bw_dialog::get_win_mv_posi(int mvpp,int p01)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_mv_posi[mvpp][p01]);
}
int bw_dialog::get_win_mv_type(int mvpp,int p05)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p05<0)||(p05>5)) return(0);
  return(win_mv_type[mvpp][p05]);
}
int * bw_dialog::get_win_mv_getp(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(&win_mv_getp[wpp]);
}
int bw_dialog::getv_win_mv_getp(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_mv_getp[wpp]);
}

int bw_dialog::set_win_mv_stor(int mlpp,int val)
{
  if ((mlpp<0)||(mlpp>=MEM_LEN)) return(0);
  win_mv_stor[mlpp]=val;
  return(0);
}
int bw_dialog::set_win_mv_posi(int mvpp,int p01,int val)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_mv_posi[mvpp][p01]=val;
  return(0);
}
int bw_dialog::set_win_mv_type(int mvpp,int p05,int val)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p05<0)||(p05>5)) return(0);
  win_mv_type[mvpp][p05]=val;
  return(0);
}
int bw_dialog::set_win_mv_getp(int wpp ,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_mv_getp[wpp]=val;
  return(0);
}

int bw_dialog::get_win_mv_name(int mvpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mv_name[mvpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_dialog::set_win_mv_name(int mvpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  win_mv_name[mvpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mv_name[mvpp][j+0]=p_s1[j];
    win_mv_name[mvpp][j+1]=0;
  }

  return(0);
}
int bw_dialog::setc_win_mv_name(int mvpp,int p0a,int val)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_mv_name[mvpp][p0a]=val;
  return(0);
}

int bw_dialog::get_win_mv_getv(int wpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mv_getv[wpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_dialog::set_win_mv_getv(int wpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  win_mv_getv[wpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mv_getv[wpp][j+0]=p_s1[j];
    win_mv_getv[wpp][j+1]=0;
  }

  return(0);
}
int bw_dialog::setc_win_mv_getv(int wpp,int pp1,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  win_mv_getv[wpp][pp1]=val;
  return(0);
}

int bw_switch::get_win_switch(int mpp,int p03)
{
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_switch[mpp][p03]);
}
int bw_switch::set_win_switch(int mpp,int p03,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_switch[mpp][p03]=val;
  return(0);
}
int bw_switch::get_win_switch_name(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_switch_name[mpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_switch::set_win_switch_name(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  win_switch_name[mpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_switch_name[mpp][j+0]=p_s1[j];
    win_switch_name[mpp][j+1]=0;
  }

  return(0);
}
int bw_switch::setc_win_switch_name(int mpp,int p0a,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_switch_name[mpp][p0a]=val;
  return(0);
}

int bw_choose::get_win_choose(int cpp,int p03)
{
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_choose[cpp][p03]);
}
int bw_choose::set_win_choose(int cpp,int p03,int val)
{
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_choose[cpp][p03]=val;
  return(0);
}
int bw_choose::get_win_choose_name(int cpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_choose_name[cpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_choose::set_win_choose_name(int cpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  win_choose_name[cpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_choose_name[cpp][j+0]=p_s1[j];
    win_choose_name[cpp][j+1]=0;
  }

  return(0);
}
int bw_choose::setc_win_choose_name(int cpp,int p0a,int val)
{
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_choose_name[cpp][p0a]=val;
  return(0);
}

int bw_menuvar::get_t5_m_wind(int mpp)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  return(t5_m_wind[mpp]);
}
int bw_menuvar::get_t5_m_mcnt(int mpp)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  return(t5_m_mcnt[mpp]);
}
int bw_menuvar::set_t5_m_wind(int mpp,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  t5_m_wind[mpp]=val;
  return(0);
}
int bw_menuvar::set_t5_m_mcnt(int mpp,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  t5_m_mcnt[mpp]=val;
  return(0);
}
int bw_menuvar::get_t5_m_name(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_m_name[mpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_menuvar::set_t5_m_name(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  t5_m_name[mpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_m_name[mpp][j+0]=p_s1[j];
    t5_m_name[mpp][j+1]=0;
  }

  return(0);
}
int bw_menuvar::setc_t5_m_name(int mpp,int p0a,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  t5_m_name[mpp][p0a]=val;
  return(0);
}

int bw_menuvar::get_t5_m_button(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_m_button[mpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_menuvar::set_t5_m_button(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  t5_m_button[mpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_m_button[mpp][j+0]=p_s1[j];
    t5_m_button[mpp][j+1]=0;
  }

  return(0);
}
int bw_menuvar::setc_t5_m_button(int mpp,int pp1,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((pp1<0)||(pp1>80)) return(0);
  t5_m_button[mpp][pp1]=val;
  return(0);
}

int bw_menuvar::get_t5_m_comm(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_m_comm[mpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_menuvar::set_t5_m_comm(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  t5_m_comm[mpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_m_comm[mpp][j+0]=p_s1[j];
    t5_m_comm[mpp][j+1]=0;
  }

  return(0);
}
int bw_menuvar::setc_t5_m_comm(int mpp,int pp1,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((pp1<0)||(pp1>80)) return(0);
  t5_m_comm[mpp][pp1]=val;
  return(0);
}

int bw_menuvar::get_t5_m_focus(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_m_focus[mpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_menuvar::set_t5_m_focus(int mpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  t5_m_focus[mpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_m_focus[mpp][j+0]=p_s1[j];
    t5_m_focus[mpp][j+1]=0;
  }

  return(0);
}
int bw_menuvar::setc_t5_m_focus(int mpp,int pp1,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((pp1<0)||(pp1>80)) return(0);
  t5_m_focus[mpp][pp1]=val;
  return(0);
}

