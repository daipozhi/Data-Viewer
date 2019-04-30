#define _CRT_SECURE_NO_WARNINGS

//#define STRICT
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

//#include <time.h>

#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_main_bua     bw_main_bua1;
extern class bw_menuvar_bua  bw_menuvar_bua1;
extern class bw_choose_bua   bw_choose_bua1;
extern class bw_switch_bua   bw_switch_bua1;
extern class bw_dialog_bua   bw_dialog_bua1;
extern class bw_xbase_bua    bw_xbase_bua1;
extern class bw_win_bua      bw_win_bua1;
extern class bw_buff         bw_buff1;
extern class bw_xbase        bw_xbase1;
extern class bw_getread      bw_getread1;
extern class bw_dialog       bw_dialog1;
extern class bw_choose       bw_choose1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;
extern class bw_menuvar      bw_menuvar1;

int bw_menuvar::w_menu_find_seri(int p1)
{
  return(bw_menuvar_bua1.get_t5_m_wind(p1));
}

int bw_menuvar::w_read_mdc(char *p_fn1,int len,int p_win)
{
  int  i,j;
  int  p1,p2,p3,p4,p5,p6,p7,p8,same;
//  int  state3;
//  int  state5;
  int  pp1;
  char sfn1[FN_SIZE];
  //char sfn2[FN_SIZE];
  char tmpc2[SMG_LEN];
  char sb1[SMG_LEN];
  char so1[SMG_LEN];
  int  exist;
  FILE *fp1;
/*
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++) sfn2[j]=p_fn1[j];
  if (i>0) sfn2[i-1]=0;
  else sfn2[0]=0;
*/
  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1);
  i=bw_inkey1.strlocc(sfn1,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb1");

  exist=0;
  for (i=0;i<MENU_NUM_MN;i++)
  {
    if (bw_menuvar_bua1.get_t5_m_wind(i)==0)
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
    for (i=0;i<SMG_LEN;i++) tmpc2[i]=0;
    fgets(tmpc2,SMG_LEN,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      p_win++;
      continue;
    }

    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_LEN) break;
    p1=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for menuname*/
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p2=i-1;
					 /* scan for space after menuname*/
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for button  */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p4=i-1;
					  /* scan for space after button  */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for command */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p6=i-1;

    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    p7=i;

    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for command */
    p8=i-1;

    for (j=p1;j<=p2;j++)
    {
      if (tmpc2[j]==' ') break;
      bw_menuvar_bua1.setc_t5_m_name(pp1,j-p1,tmpc2[j]);
      bw_menuvar_bua1.setc_t5_m_name(pp1,j-p1+1,0);
    }

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      bw_menuvar_bua1.setc_t5_m_butt(pp1,j-p3,tmpc2[j]);
      bw_menuvar_bua1.setc_t5_m_butt(pp1,j-p3+1,0);
    }

    bw_menuvar_bua1.get_t5_m_butt(pp1,sb1,SMG_LEN);

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
      bw_menuvar_bua1.setc_t5_m_comm(pp1,j-p5,tmpc2[j]);
      bw_menuvar_bua1.setc_t5_m_comm(pp1,j-p5+1,0);
    }

    bw_menuvar_bua1.get_t5_m_comm(pp1,so1,SMG_LEN);

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
      bw_menuvar_bua1.setc_t5_m_focus(pp1,j-p7,tmpc2[j]);
      bw_menuvar_bua1.setc_t5_m_focus(pp1,j-p7+1,0);
    }

    bw_menuvar_bua1.set_t5_m_wind(pp1,p_win);

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
	   ,t5_m_butt[i]
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
  char str[SMG_LEN];
  char sm1[SMG_LEN];
  char sb1[SMG_LEN];
  char so1[SMG_LEN];
  char sf1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    bw_menuvar_bua1.get_t5_m_name(i,sm1,SMG_LEN);
    bw_menuvar_bua1.get_t5_m_butt(i,sb1,SMG_LEN);
    bw_menuvar_bua1.get_t5_m_comm(i,so1,SMG_LEN);
    bw_menuvar_bua1.get_t5_m_focus(i,sf1,SMG_LEN);

    sprintf(str,"%d,%d,%d,%s,%s,%s,%s,"
				 ,bw_menuvar_bua1.get_t5_m_wind(i)
                                 ,bw_menuvar_bua1.get_t5_m_mcnt(i)
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
  char sm1[SMG_LEN];
  char sb1[SMG_LEN];
  char so1[SMG_LEN];
  char sf1[SMG_LEN];

  p1=(-1);  /* begin pp*/ 
  p2=(-1);  /* end pp*/  
  p3=0;  /* end big win pp*/
  p4=0;  /* mn cnt*/
  p5=0;
  p6=0;

  for (i=0;i<=t5_m_pp1;i++)
  {
    if ((bw_menuvar_bua1.get_t5_m_wind(i)>=wp1)&&(bw_menuvar_bua1.get_t5_m_wind(i)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (bw_menuvar_bua1.get_t5_m_wind(i)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (bw_menuvar_bua1.get_t5_m_wind(i)>wp2)
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
      bw_menuvar_bua1.set_t5_m_wind(i,bw_menuvar_bua1.get_t5_m_wind(i)-wp2+wp1-1);
    }
  }
  else
  {
    if (p3>=p2)
    {
      for (i=p2;i<=p3;i++)
      {
	bw_menuvar_bua1.get_t5_m_name(i,sm1,SMG_LEN);
        bw_menuvar_bua1.set_t5_m_name(p1+i-p2,sm1,SMG_LEN);

	bw_menuvar_bua1.get_t5_m_butt(i,sb1,SMG_LEN);
	bw_menuvar_bua1.set_t5_m_butt(p1+i-p2,sb1,SMG_LEN);

	bw_menuvar_bua1.get_t5_m_comm(i,so1,SMG_LEN);
	bw_menuvar_bua1.set_t5_m_comm(p1+i-p2,so1,SMG_LEN);

	bw_menuvar_bua1.get_t5_m_focus(i,sf1,SMG_LEN);
	bw_menuvar_bua1.set_t5_m_focus(p1+i-p2,sf1,SMG_LEN);

	bw_menuvar_bua1.set_t5_m_mcnt(p1+i-p2,bw_menuvar_bua1.get_t5_m_mcnt(i));
	bw_menuvar_bua1.set_t5_m_wind(p1+i-p2,bw_menuvar_bua1.get_t5_m_wind(i)-wp2+wp1-1);
      }

      for (i=p1+p3-p2+1;i<=t5_m_pp1;i++)
      {
	bw_menuvar_bua1.setc_t5_m_name(i,0,0);
	bw_menuvar_bua1.setc_t5_m_butt(i,0,0);
	bw_menuvar_bua1.setc_t5_m_comm(i,0,0);
	bw_menuvar_bua1.setc_t5_m_focus(i,0,0);
	bw_menuvar_bua1.set_t5_m_mcnt(i,0);
	bw_menuvar_bua1.set_t5_m_wind(i,0);
      }

      t5_m_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=t5_m_pp1;i++)
      {
	bw_menuvar_bua1.setc_t5_m_name(i,0,0);
        bw_menuvar_bua1.setc_t5_m_butt(i,0,0);
	bw_menuvar_bua1.setc_t5_m_comm(i,0,0);
	bw_menuvar_bua1.setc_t5_m_focus(i,0,0);
	bw_menuvar_bua1.set_t5_m_mcnt(i,0);
	bw_menuvar_bua1.set_t5_m_wind(i,0);
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
  char s1[SMG_LEN];
  char s2[SMG_LEN];
  char s3[50][30];
  char s4[SMG_LEN];

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


  chs=26;
  t5_m_pp2=0;
  t5_m_como[0]=0;
  if (state==0) bw_menuvar_bua1.get_t5_m_comm(p1,s1,SMG_LEN);
  else bw_menuvar_bua1.get_t5_m_focus(p1,s1,SMG_LEN);

  if (strncmp("com=",s1,4)==0)
  {
    bw_inkey1.strpcut(s1,4,strlen(s1)-4,SMG_LEN,s2,SMG_LEN);

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
      bw_inkey1.strpcut(s2,strlen(s3[i]),strlen(s2)-strlen(s3[i]),SMG_LEN,s4,SMG_LEN);
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
	  bw_inkey1.strpcut(s4,1,i-1,SMG_LEN,t5_m_como,SMG_LEN);
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
int bw_menuvar::w_menu_poin(char *p_s1,int len,int p1)
{
  int  i,j;
  int  exist;
  char sm1[SMG_LEN];
  //char sc1[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sc1[j]=s1[j];
  if (i>0) sc1[i-1]=0;
  else sc1[0]=0;
*/
  //bw_main1.set_string(sc1,SMG_LEN,s1,len);

  exist=0;
  for (i=0;i<=t5_m_pp1;i++)
  {
    bw_menuvar_bua1.get_t5_m_name(i,sm1,SMG_LEN);

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
    bw_choose_bua1.set_win_choose(i,0,0);
    bw_choose_bua1.setc_win_choose_name(i,0,0);
  }

  return(0);
}

int bw_choose::w_read_cdc(char *p_fn1,int len,int wpp)
{
  int  i,j,k,l,o;
  int  p1,p2,p3,p4,p5,p6;
//  int  state2,state3;
//  int  state4,state5;
  int  pp1;
  char sfn1[FN_SIZE];
  char tmpc2[SMG_LEN];
  char str[SMG_LEN];
  char sc1[SMG_LEN];
  //char sd1[SMG_LEN];
  int  exist;
  FILE *fp1;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=p_fn1[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,p_fn1,len);

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1);
  i=bw_inkey1.strlocc(sfn1,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb6");

  exist=0;
  for (i=0;i<MENU_NUM_CHS;i++)
  {
    if (bw_choose_bua1.get_win_choose(i,0)==0)
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
    for (i=0;i<SMG_LEN;i++) tmpc2[i]=0;
    fgets(tmpc2,SMG_LEN,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      wpp++;
      continue;
    }

    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_LEN) break;
    p1=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for menuname*/
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p2=i-1;
					 /* scan for space after menuname*/
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for button  */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p4=i-1;
					  /* scan for space after button  */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for command */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p6=i-1;

    o=bw_inkey1.char2int(tmpc2,p1+1,p2);
    k=pp1;
    bw_choose_bua1.set_win_choose(k,0,1);
    bw_choose_bua1.set_win_choose(k,2,o);
    bw_choose_bua1.set_win_choose(k,3,wpp);

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      bw_choose_bua1.setc_win_choose_name(k,j-p3,tmpc2[j]);
      bw_choose_bua1.setc_win_choose_name(k,j-p3+1,0);
    }

    l=bw_inkey1.char2int(tmpc2,p5,p6);
    bw_choose_bua1.set_win_choose(k,1,l);

    bw_choose_bua1.get_win_choose_name(k,sc1,SMG_LEN);

    if (bw_dialog1.w_mv_exist(sc1,SMG_LEN,0)==1)
    {
      bw_dialog1.w_mv_fet_val(sc1,SMG_LEN,0,str,SMG_LEN);
      bw_choose_bua1.set_win_choose(k,1,bw_inkey1.char2int(str,0,4));
    }

    pp1++;
  }

  win_choose_pp1=pp1-1;

  fclose(fp1);

  return(0);
}

int bw_choose::tst_choose()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char sc1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    bw_choose_bua1.get_win_choose_name(i,sc1,SMG_LEN);

    sprintf(str,"%d,%d,%d,%d,%s,%d,",bw_choose_bua1.get_win_choose(i,0)
				    ,bw_choose_bua1.get_win_choose(i,1)
				    ,bw_choose_bua1.get_win_choose(i,2)
				    ,bw_choose_bua1.get_win_choose(i,3)
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
  char sc1[SMG_LEN];

  p1=(-1);  /* begin pp*/
  p2=(-1);  /* end pp*/  
  p3=0;     /* end big win pp*/
  p4=0;     /* mn cnt*/
  p5=0;
  p6=0;

  for (i=0;i<=win_choose_pp1;i++)
  {
    if ((bw_choose_bua1.get_win_choose(i,3)>=wp1)&&(bw_choose_bua1.get_win_choose(i,3)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (bw_choose_bua1.get_win_choose(i,3)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (bw_choose_bua1.get_win_choose(i,3)>wp2)
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
      bw_choose_bua1.set_win_choose(i,3,bw_choose_bua1.get_win_choose(i,3)-wp2+wp1-1);
    }
  }
  else
  {
    if (p3>=p2)
    {
      for (i=p2;i<=p3;i++)
      {
	bw_choose_bua1.get_win_choose_name(i,sc1,SMG_LEN);
	bw_choose_bua1.set_win_choose_name(p1+i-p2,sc1,SMG_LEN);

	bw_choose_bua1.set_win_choose(p1+i-p2,0,bw_choose_bua1.get_win_choose(i,0));
	bw_choose_bua1.set_win_choose(p1+i-p2,1,bw_choose_bua1.get_win_choose(i,1));
	bw_choose_bua1.set_win_choose(p1+i-p2,2,bw_choose_bua1.get_win_choose(i,2));
	bw_choose_bua1.set_win_choose(p1+i-p2,3,bw_choose_bua1.get_win_choose(i,3)-wp2+wp1-1);
      }

      for (i=p1+p3-p2+1;i<=win_choose_pp1;i++)
      {
	bw_choose_bua1.setc_win_choose_name(i,0,0);
	bw_choose_bua1.set_win_choose(i,0,0);
	bw_choose_bua1.set_win_choose(i,1,0);
	bw_choose_bua1.set_win_choose(i,2,0);
	bw_choose_bua1.set_win_choose(i,3,0);
      }
      win_choose_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_choose_pp1;i++)
      {
	bw_choose_bua1.setc_win_choose_name(i,0,0);
	bw_choose_bua1.set_win_choose(i,0,0);
	bw_choose_bua1.set_win_choose(i,1,0);
	bw_choose_bua1.set_win_choose(i,2,0);
	bw_choose_bua1.set_win_choose(i,3,0);
      }
      win_choose_pp1=p1;
    }
  }

  return(0);

}
int bw_choose::w_save_choose(int wpp)
{
  int  i,j;
  char str[SMG_LEN];
  char sc1[SMG_LEN];

  for (j=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0);j<=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),2);j++)
  {
    for (i=0;i<=win_choose_pp1;i++)
    {
      if (bw_choose_bua1.get_win_choose(i,3)==j)
      {
	bw_inkey1.int2char(bw_choose_bua1.get_win_choose(i,1),str);

        bw_choose_bua1.get_win_choose_name(i,sc1,SMG_LEN);

	bw_dialog1.w_save_mem(sc1,SMG_LEN,0,str,strlen(str));
      }
    }
  }
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
    if ((bw_choose_bua1.get_win_choose(i,2)==link)&&(bw_choose_bua1.get_win_choose(i,3)==wpp))
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    if (bw_choose_bua1.get_win_choose(i,1)==1) bw_choose_bua1.set_win_choose(i,1,0);
    else bw_choose_bua1.set_win_choose(i,1,1);

    return(i);
  }
  else return(-1);
}

int bw_choose::w_clr_recvar_chs(int wpp)
{
  int i;
//  char str[SMG_LEN];

  for (i=0;i<MENU_NUM_CHS;i++)
  {
    if ((bw_choose_bua1.get_win_choose(i,0)==1)&&(bw_choose_bua1.get_win_choose(i,3)==wpp)) bw_choose_bua1.set_win_choose(i,1,0);
  }

  return(0);
}

int bw_choose::w_echo_winrec_chs(int wpp)
{
  int i,j,k,l,n,o;
  char str[SMG_LEN];

  bw_win1.pline =1;
  bw_win1.pfield=1;

  while (1)
  {
    i=bw_win1.pline;
    j=bw_win1.pfield;

    bw_win1.w_next_afield(wpp);

    if ((i==bw_win1.pline)&&(j==bw_win1.pfield)) break;

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

    if (str[0]=='[')
    {
      n=bw_inkey1.char2int(str,1,strlen(str)-1);

      for (k=0;k<MENU_NUM_CHS;k++)
      {
	if ((bw_choose_bua1.get_win_choose(k,2)==n)&&(bw_choose_bua1.get_win_choose(k,3)==wpp))
        {
	  l=bw_choose_bua1.get_win_choose(k,1);

	  o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);

	  if (l>0)
	  {
	    SendMessage(bw_win_bua1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)str);
	  }
	  else
	  {
	    SendMessage(bw_win_bua1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)str);
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
    bw_switch_bua1.set_win_switch(i,0,0);
    bw_switch_bua1.setc_win_switch_name(i,0,0);
  }

  return(0);
}

int bw_switch::w_read_sdc(char *p_fn1,int len,int wpp)
{
  int  i,j,k,l,o;
  int  p1,p2,p3,p4,p5,p6;
//  int  state2,state3;
//  int  state4,state5;
  int  pp1;
  char sfn1[FN_SIZE];
  char st1[SMG_LEN];
  //char sd1[SMG_LEN];
  char tmpc2[SMG_LEN];
  char str[SMG_LEN];
  int  exist;
  FILE *fp1;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=p_fn1[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,p_fn1,len);

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1);
  i=bw_inkey1.strlocc(sfn1,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb5");

  exist=0;
  for (i=0;i<MENU_NUM_RA;i++)
  {
    if (bw_switch_bua1.get_win_switch(i,0)==0)
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
    for (i=0;i<SMG_LEN;i++) tmpc2[i]=0;
    fgets(tmpc2,SMG_LEN,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      wpp++;
      continue;
    }

    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_LEN) break;
    p1=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for menuname*/
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p2=i-1;
					 /* scan for space after menuname*/
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for button  */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p4=i-1;
					  /* scan for space after button  */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for command */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten37(sfn1);
      return(1);
    }
    p6=i-1;

    k=pp1;
    o=bw_inkey1.char2int(tmpc2,p1+1,p2);
    bw_switch_bua1.set_win_switch(k,0,1);
    bw_switch_bua1.set_win_switch(k,2,o);
    bw_switch_bua1.set_win_switch(k,3,wpp);

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      bw_switch_bua1.setc_win_switch_name(k,j-p3,tmpc2[j]);
      bw_switch_bua1.setc_win_switch_name(k,j-p3+1,0);
    }

    l=bw_inkey1.char2int(tmpc2,p5,p6);
    bw_switch_bua1.set_win_switch(k,1,l);

    bw_switch_bua1.get_win_switch_name(k,st1,SMG_LEN);

    if (bw_dialog1.w_mv_exist(st1,SMG_LEN,0)==1)
    {
      bw_dialog1.w_mv_fet_val(st1,SMG_LEN,0,str,SMG_LEN);
      bw_switch_bua1.set_win_switch(k,1,bw_inkey1.char2int(str,0,4));
    }

    pp1++;
  }

  win_switch_pp1=pp1-1;

  fclose(fp1);

  return(0);
}

int bw_switch::w_save_switch(int wpp)
{
  int  i,j;
  char str[SMG_LEN];
  char st1[SMG_LEN];

  for (j=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0);j<=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),2);j++)
  {
    for (i=0;i<=win_switch_pp1;i++)
    {
      if (bw_switch_bua1.get_win_switch(i,3)>=j)
      {
	bw_inkey1.int2char(bw_switch_bua1.get_win_switch(i,1),str);
	bw_switch_bua1.get_win_switch_name(i,st1,SMG_LEN);
	bw_dialog1.w_save_mem(st1,SMG_LEN,0,str,strlen(str));
      }
    }
  }

  return(0);
}

int bw_switch::tst_switch()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char st1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    bw_switch_bua1.get_win_switch_name(i,st1,SMG_LEN);

    sprintf(str,"%d,%d,%d,%d,%s,%d,",bw_switch_bua1.get_win_switch(i,0)
				    ,bw_switch_bua1.get_win_switch(i,1)
				    ,bw_switch_bua1.get_win_switch(i,2)
				    ,bw_switch_bua1.get_win_switch(i,3)
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
  char st1[SMG_LEN];

  p1=(-1);  /* begin pp */
  p2=(-1);  /* end pp */  
  p3=0;     /* end big win pp*/
  p4=0;     /* mn cnt */
  p5=0;
  p6=0;

  for (i=0;i<=win_switch_pp1;i++)
  {
    if ((bw_switch_bua1.get_win_switch(i,3)>=wp1)&&(bw_switch_bua1.get_win_switch(i,3)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (bw_switch_bua1.get_win_switch(i,3)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (bw_switch_bua1.get_win_switch(i,3)>wp2)
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
      bw_switch_bua1.set_win_switch(i,3,bw_switch_bua1.get_win_switch(i,3)-wp2+wp1-1);
    }
  }
  else
  {
    for (i=p2;i<=p3;i++)
    {
      bw_switch_bua1.get_win_switch_name(i,st1,SMG_LEN);
      bw_switch_bua1.set_win_switch_name(p1+i-p2,st1,SMG_LEN);
      
      bw_switch_bua1.set_win_switch(p1+i-p2,0,bw_switch_bua1.get_win_switch(i,0));
      bw_switch_bua1.set_win_switch(p1+i-p2,1,bw_switch_bua1.get_win_switch(i,1));
      bw_switch_bua1.set_win_switch(p1+i-p2,2,bw_switch_bua1.get_win_switch(i,2));
      bw_switch_bua1.set_win_switch(p1+i-p2,3,bw_switch_bua1.get_win_switch(i,3)-wp2+wp1-1);
    }

    if (p3>=p2)
    {
      for (i=p1+p3-p2+1;i<=win_switch_pp1;i++)
      {
	bw_switch_bua1.setc_win_switch_name(i,0,0);
	bw_switch_bua1.set_win_switch(i,0,0);
	bw_switch_bua1.set_win_switch(i,1,0);
	bw_switch_bua1.set_win_switch(i,2,0);
	bw_switch_bua1.set_win_switch(i,3,0);
      }
      win_switch_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_switch_pp1;i++)
      {
	bw_switch_bua1.setc_win_switch_name(i,0,0);
	bw_switch_bua1.set_win_switch(i,0,0);
	bw_switch_bua1.set_win_switch(i,1,0);
	bw_switch_bua1.set_win_switch(i,2,0);
	bw_switch_bua1.set_win_switch(i,3,0);
      }
      win_switch_pp1=p1;
    }
  }

  return(0);

}

int bw_switch::w_set_radio_var(int l,int c,int p,int wpp)
{
  int  i,j,k,m,o,t1,t2;
  int  t3;
  char str[SMG_LEN];

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

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

    if (str[0]=='(')
    {
      o=bw_inkey1.char2int(str,1,strlen(str)-1);
      if (o==p)
      {
	k++;
	if ((bw_win1.pline==l)&&(bw_win1.pfield==c))
        {
          for (m=0;m<MENU_NUM_RA;m++)
          {
	    if ((bw_switch_bua1.get_win_switch(m,2)==p)&&(bw_switch_bua1.get_win_switch(m,3)==wpp))
	    {
	      bw_switch_bua1.set_win_switch(m,1,k);
              t3=m;
	      break;
	    }
          }
	  o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	  SendMessage(bw_win_bua1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)str);
	}
	else
	{
          o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	  SendMessage(bw_win_bua1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)str);
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
  char str[SMG_LEN];

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

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

    if (str[0]=='(')
    {
      o=bw_inkey1.char2int(str,1,strlen(str)-1);
      arr[o]++;

      for (m=0;m<MENU_NUM_RA;m++)
      {
	if ((bw_switch_bua1.get_win_switch(m,2)==o)&&(bw_switch_bua1.get_win_switch(m,3)==wpp))
	{
	  if (bw_switch_bua1.get_win_switch(m,1)==arr[o])
          {
            o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	    SendMessage(bw_win_bua1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)str);
          }
          else
          {
            o=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	    SendMessage(bw_win_bua1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)str);
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
    if (bw_switch_bua1.get_win_switch(i,3)==wpp)
    {
      bw_switch_bua1.set_win_switch(i,1,1);
    }
  }
  return(0);
}

int bw_dialog::w_read_ddc(char *p_fn1,int len,int wpp)
{
  int  i,j,k,l;
  int  p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
//  int  state2,state3;
//  int  state4,state5;
  int  pp1;
//  int  exist;
  char sfn1[FN_SIZE];
  char s_tmpc1[SMG_LEN];
  char s_tmpc2[SMG_LEN];
  char s_tmpc3[SMG_LEN];
  char s_tmpc4[SMG_LEN];
  char tmpc2[SMG_LEN];
  char str[SMG_LEN];
//  char str1[SMG_LEN];
  //char sd1[SMG_LEN];
  int  wpp2;
  FILE *fp1;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=p_fn1[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,p_fn1,len);

  wpp2=wpp;

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1);
  i=bw_inkey1.strlocc(sfn1,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb2");

  pp1=win_mv_pp1;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
	 for (i=0;i<SMG_LEN;i++) tmpc2[i]=0;
	 fgets(tmpc2,SMG_LEN,fp1);

	 if (strncmp(tmpc2,"&screenseg",7)==0)
	 {
	   wpp2++;
	   continue;
         }

	 for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>=0)) tmpc2[i]=' ';
						  /* scan for pre space */
	 for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
	 if (i>=299) break;
	 p1=i;
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for memvarname*/
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p2=i-1;
					 /* scan for space after memvarname*/
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_LEN)
	 {
           fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p3=i;
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for dtype   */
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p4=i-1;
					  /* scan for space after dtype   */
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p5=i;
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for type    */
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p6=i-1;
					  /* scan for space after type   */
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p7=i;

	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for len */
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p8=i-1;
					  /* scan for space after len */
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p9=i;

	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for dec */
	 if (i>=SMG_LEN)
	 {
	   fclose(fp1);
	   bw_win1.w_atten38(sfn1);
	   return(1);
	 }
	 p10=i-1;
					  /* scan for space after dec   */
	 for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
	 if ((i>=SMG_LEN)||(tmpc2[i]!='"'))
	 {
	   p11=0;
	   p12=0;
	 }
	 else
	 {
	   p11=i;
	   for (i=i+1;i<SMG_LEN;i++) if (tmpc2[i]=='"') break; /* scan for val */
	   if (i>=SMG_LEN)
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
	   s_tmpc1[j-p1]=tmpc2[j];
	   s_tmpc1[j-p1+1]=0;
	 }
	 if (w_mv_exist(s_tmpc1,SMG_LEN,wpp2)==0) k=w_mv_add_name(s_tmpc1,SMG_LEN);
	 else k=w_mv_seri(s_tmpc1,SMG_LEN,wpp2);

	 if (k>=0)
	 {
	   if (p3==p4)
	   {
	     if (tmpc2[p3]=='e')  bw_dialog_bua1.set_win_mv_type(k,0,2);
	     else
	     {
	       if (tmpc2[p3]=='d') bw_dialog_bua1.set_win_mv_type(k,0,1);
	       else bw_dialog_bua1.set_win_mv_type(k,0,2);
	     }
	   }

	   if (p6==p5)
	   {
	     bw_dialog_bua1.set_win_mv_type(k,1,tmpc2[p5]);
	   }

	   l=bw_inkey1.char2int(tmpc2,p7,p8);
	   bw_dialog_bua1.set_win_mv_type(k,2,l);
	   l=bw_inkey1.char2int(tmpc2,p9,p10);
	   bw_dialog_bua1.set_win_mv_type(k,3,l);
	   bw_dialog_bua1.set_win_mv_type(k,4,wpp2);

	   if (p11==0)
	   {
             s_tmpc4[0]=0;
	     w_mv_add_val(s_tmpc1,SMG_LEN,wpp2,s_tmpc4,SMG_LEN);
	   }
	   else
	   {
	     if ((tmpc2[p11]=='"')&&(tmpc2[p12]=='"'))
	     {
	       for (j=p11;j<=p12;j++)
	       {
		 s_tmpc2[j-p11]=tmpc2[j];
		 s_tmpc2[j-p11+1]=0;
	       }
	       bw_inkey1.strpcut(s_tmpc2,1,strlen(s_tmpc2)-2,SMG_LEN,s_tmpc3,SMG_LEN);
	       w_mv_add_val(s_tmpc1,SMG_LEN,wpp2,s_tmpc3,SMG_LEN);
	     }
	     else
	     {
               s_tmpc4[0]=0;
	       w_mv_add_val(s_tmpc1,SMG_LEN,wpp2,s_tmpc4,SMG_LEN);
	     }
	   }

           if (w_mv_exist(s_tmpc1,SMG_LEN,0)==1)
           {
             w_mv_fet_val(s_tmpc1,SMG_LEN,0,str,SMG_LEN);
             w_mv_add_val(s_tmpc1,SMG_LEN,wpp2,str,SMG_LEN);
	   }

	   pp1++;
	 }

  }

  fclose(fp1);

  win_mv_pp1=pp1;

  return(0);
}

int bw_dialog::w_save_dialog(int wpp)
{
  int  i,j,k,l;
  char str[SMG_LEN];
  char sv1[SMG_LEN];

  for (j=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0);j<=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),2);j++)
  {
    for (i=0;i<=win_mv_pp1;i++)
    {
      if (bw_dialog_bua1.get_win_mv_type(i,4)==j)
      {
        bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);
	k=w_mv_fet_val(sv1,SMG_LEN,j,str,SMG_LEN);
        l=bw_dialog_bua1.get_win_mv_type(i,2);
	if (k==0) w_save_mem(sv1,SMG_LEN,0,str,l);
      }
    }
  }

  return(0);
}

int bw_dialog::w_save_mem(char *p_str,int len1,int wpp,char *val,int len2)
{
  int  i,j,k;
  char sd1[SMG_LEN];
/*
  if (len1>SMG_LEN) i=SMG_LEN;
  else i=len1;
  for (j=0;j<i-1;j++) sd1[j]=str[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  bw_main1.set_string(sd1,SMG_LEN,val,len2);

  if (len2<=0)
  {
	  sd1[0]=' ';
	  sd1[1]=0;
	  len2=1;
  }

  if (w_mv_exist(p_str,len1,wpp)==0)
  {
    k=w_mv_add_name(p_str,len1);
    i=0;
  }
  else
  {
    k=w_mv_seri(p_str,len1,wpp);
    i=1;
  }

  if (k>=0)
  {
    if (i==0)
    {
      bw_dialog_bua1.set_win_mv_type(k,0,2);            /* edit able */
      bw_dialog_bua1.set_win_mv_type(k,1,'c');          /* var type */
      bw_dialog_bua1.set_win_mv_type(k,2,len2);         /* var len */      //remember
      bw_dialog_bua1.set_win_mv_type(k,3,0);            /* dec is zero */
      bw_dialog_bua1.set_win_mv_type(k,4,wpp);          /* free window var */
    }
	else 
	{
      bw_dialog_bua1.set_win_mv_type(k,2,len2);         /* var len */      //remember
	}
    
	w_mv_add_val(p_str,len1,wpp,sd1,len2);
  }

  return(0);
}                 

int bw_dialog::w_dele_dialog(int wp1,int wp2)
{
  char sv1[SMG_LEN];
//  char str[SMG_LEN];
  int  i;
  int  p1,p2,p3,p4,p5,p6,p7,p8,p9;

  p1=(-1);  /* begin pp*/
  p2=(-1);  /* end pp*/
  p3=0;     /* end big win pp*/
  p4=0;     /* mn cnt*/
  p5=0;
  p6=0;
  p7=(-1);
  p8=(-1);
  p9=0;

  for (i=0;i<=win_mv_pp1;i++)
  {
    if ((bw_dialog_bua1.get_win_mv_type(i,4)>=wp1)&&(bw_dialog_bua1.get_win_mv_type(i,4)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if ((bw_dialog_bua1.get_win_mv_type(i,4)>wp2)||(bw_dialog_bua1.get_win_mv_type(i,4)<wp1))
    {
      if ((p6==0)&&(p1>=0)) /* first after p1+p4 item */
      {
	p2=i;
	p6=1;
      }
    }
    if ((bw_dialog_bua1.get_win_mv_type(i,4)>wp2)||(bw_dialog_bua1.get_win_mv_type(i,4)<wp1))
    {
      if ((p1>=0)&&(bw_dialog_bua1.get_win_mv_type(i,0)!=0))
      {
	p3=i;
      }
    }
    if (bw_dialog_bua1.get_win_mv_type(i,4)>wp2)
    {
      if (p9==0) 
      {
	p7=i;
	p9=1;
      }
    }
    if (bw_dialog_bua1.get_win_mv_type(i,4)>wp2)
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
	if (bw_dialog_bua1.get_win_mv_type(i,4)!=0) bw_dialog_bua1.set_win_mv_type(i,4,bw_dialog_bua1.get_win_mv_type(i,4)-wp2+wp1-1);
      }
    }
  }
  else
  {
    if ((p2>=0)&&(p3>=p2))
    {
      p7=bw_dialog_bua1.get_win_mv_posi(p1,0);
      p8=bw_dialog_bua1.get_win_mv_posi(p2,0);
      p9=bw_dialog_bua1.get_win_mv_posi(p3,0)+bw_dialog_bua1.get_win_mv_posi(p3,1)-1;

      for (i=p8;i<=p9;i++)
      {
        bw_dialog_bua1.set_win_mv_stor(p7+i-p8,bw_dialog_bua1.get_win_mv_stor(i));
      }

      win_mv_pp2=p7+p9-p8+1;

      for (i=p2;i<=p3;i++)
      {
	bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);
        bw_dialog_bua1.set_win_mv_name(p1+i-p2,sv1,SMG_LEN);

	bw_dialog_bua1.set_win_mv_type(p1+i-p2,0,bw_dialog_bua1.get_win_mv_type(i,0));
	bw_dialog_bua1.set_win_mv_type(p1+i-p2,1,bw_dialog_bua1.get_win_mv_type(i,1));
	bw_dialog_bua1.set_win_mv_type(p1+i-p2,2,bw_dialog_bua1.get_win_mv_type(i,2));
	bw_dialog_bua1.set_win_mv_type(p1+i-p2,3,bw_dialog_bua1.get_win_mv_type(i,3));

	if (bw_dialog_bua1.get_win_mv_type(i,4)==0) bw_dialog_bua1.set_win_mv_type(p1+i-p2,4,0);
	else bw_dialog_bua1.set_win_mv_type(p1+i-p2,4,bw_dialog_bua1.get_win_mv_type(i,4)-wp2+wp1-1);

	bw_dialog_bua1.set_win_mv_type(p1+i-p2,5,bw_dialog_bua1.get_win_mv_type(i,5));

	if (bw_dialog_bua1.get_win_mv_posi(i,0)==0) bw_dialog_bua1.set_win_mv_posi(p1+i-p2,0,0);
	else bw_dialog_bua1.set_win_mv_posi(p1+i-p2,0,bw_dialog_bua1.get_win_mv_posi(i,0)-p8+p7);

	bw_dialog_bua1.set_win_mv_posi(p1+i-p2,1,bw_dialog_bua1.get_win_mv_posi(i,1));
      }

      for (i=p1+p3-p2+1;i<=win_mv_pp1;i++)
      {
	bw_dialog_bua1.setc_win_mv_name(i,0,0);

	bw_dialog_bua1.set_win_mv_type(i,0,0);
	bw_dialog_bua1.set_win_mv_type(i,1,0);
	bw_dialog_bua1.set_win_mv_type(i,2,0);
	bw_dialog_bua1.set_win_mv_type(i,3,0);
	bw_dialog_bua1.set_win_mv_type(i,4,0);
	bw_dialog_bua1.set_win_mv_type(i,5,0);

	bw_dialog_bua1.set_win_mv_posi(i,0,0);
	bw_dialog_bua1.set_win_mv_posi(i,1,0);
      }
      win_mv_pp1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_mv_pp1;i++)
      {
	bw_dialog_bua1.setc_win_mv_name(i,0,0);
	bw_dialog_bua1.set_win_mv_type(i,0,0);
	bw_dialog_bua1.set_win_mv_type(i,1,0);
	bw_dialog_bua1.set_win_mv_type(i,2,0);
	bw_dialog_bua1.set_win_mv_type(i,3,0);
	bw_dialog_bua1.set_win_mv_type(i,4,0);
	bw_dialog_bua1.set_win_mv_type(i,5,0);

	bw_dialog_bua1.set_win_mv_posi(i,0,0);
	bw_dialog_bua1.set_win_mv_posi(i,1,0);
      }
      win_mv_pp1=p1;
    }
  }

  return(0);
}

int bw_dialog::tst_mem()
{
  HDC  hdc;
  char str[SMG_LEN*2];
  char sv1[SMG_LEN];
  int  i,j;

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);

    TextOut(hdc,1,i*20,sv1,20);

    sprintf(str,"type024=%5d,%5d,%5d,",bw_dialog_bua1.get_win_mv_type(i,0),bw_dialog_bua1.get_win_mv_type(i,2),bw_dialog_bua1.get_win_mv_type(i,4));
    TextOut(hdc,100,i*20,str,strlen(str));

    sprintf(str,"posi01=%5d,%5d,",bw_dialog_bua1.get_win_mv_posi(i,0),bw_dialog_bua1.get_win_mv_posi(i,1));
    TextOut(hdc,300,i*20,str,strlen(str));

//    bw_inkey1.strpcut(win_mv_stor,bw_dialog_bua1.get_win_mv_posi(i,0),bw_dialog_bua1.get_win_mv_posi(i,1),str);

    str[0]=0;
    for (j=bw_dialog_bua1.get_win_mv_posi(i,0);j<bw_dialog_bua1.get_win_mv_posi(i,0)+bw_dialog_bua1.get_win_mv_posi(i,1);j++)
    {
      str[j-bw_dialog_bua1.get_win_mv_posi(i,0)]=bw_dialog_bua1.get_win_mv_stor(j);
      str[j-bw_dialog_bua1.get_win_mv_posi(i,0)+1]=0;
    }

    TextOut(hdc,444,i*20,str,strlen(str));

    sprintf(str,"pp1=%d,",win_mv_pp1);
    TextOut(hdc,500,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_dialog::w_mv_add_val(char *p_s1,int len1,int wpp,char *p_s2,int len2)
{
  int  i,j,k,l;
  int  exist;
  char s3[SMG_LEN];
  //char s4[SMG_LEN];
  //char s5[SMG_LEN];
  char sv1[SMG_LEN];
/*
  if (len1>SMG_LEN) i=SMG_LEN;
  else i=len1;
  for (j=0;j<i-1;j++) s4[j]=s1[j];
  if (i>0) s4[i-1]=0;
  else s4[0]=0;
*/
  //bw_main1.set_string(s4,SMG_LEN,s1,len1);
/*
  if (len2>SMG_LEN) i=SMG_LEN;
  else i=len2;
  for (j=0;j<i-1;j++) s5[j]=s2[j];
  if (i>0) s5[i-1]=0;
  else s5[0]=0;
*/
  //bw_main1.set_string(s5,SMG_LEN,s2,len2);

  strcpy(s3,p_s2);

  exist=0;
  for (i=0;i<win_mv_pp1;i++)
  {
    bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);
    if ((strcmp(p_s1,sv1)==0)&&(bw_dialog_bua1.get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }
  if (exist==0) return(1);

  if (i<=0) bw_dialog_bua1.set_win_mv_posi(i,0,0);
  else bw_dialog_bua1.set_win_mv_posi(i,0,bw_dialog_bua1.get_win_mv_posi(i-1,0)+bw_dialog_bua1.get_win_mv_posi(i-1,1));

  for (j=strlen(s3);j<bw_dialog_bua1.get_win_mv_type(i,2);j++)
  {
    s3[j]=' ';
  }
  s3[bw_dialog_bua1.get_win_mv_type(i,2)]=0;
  k=bw_dialog_bua1.get_win_mv_type(i,2);
  j=bw_dialog_bua1.get_win_mv_posi(i,1)-k;
  l=0;
  if (j<0) l=w_mv_move_aft(0-j,i);
  if (j>0) l=w_mv_move_bef(j,i);
  if (l!=0) return(1);
  bw_dialog_bua1.set_win_mv_posi(i,1,k);
  for (j=0;j<k;j++)
  {
    bw_dialog_bua1.set_win_mv_stor(bw_dialog_bua1.get_win_mv_posi(i,0)+j,s3[j]);
  }
  return(0);
}

int bw_dialog::w_mv_fet_val(char *p_s1,int len1,int wpp,char *p_s2,int len2)
{
  int  i,j;
  int  exist;
  char sv1[SMG_LEN];
  //char s3[SMG_LEN];
/*
  if (len1>SMG_LEN) i=SMG_LEN;
  else i=len1;
  for (j=0;j<i-1;j++) s3[j]=s1[j];
  if (i>0) s3[i-1]=0;
  else s3[0]=0;
*/
  //bw_main1.set_string(s3,SMG_LEN,s1,len1);

  exist=0;
  for (i=0;i<win_mv_pp1;i++)
  {
    bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);

    if ((strcmp(p_s1,sv1)==0)&&(bw_dialog_bua1.get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }
  if (exist==0) return(1);

  for (j=0;j<bw_dialog_bua1.get_win_mv_posi(i,1);j++)
  {
    if (j<len2)
    {
      p_s2[j]=bw_dialog_bua1.get_win_mv_stor(bw_dialog_bua1.get_win_mv_posi(i,0)+j);
    }
  }

  if (bw_dialog_bua1.get_win_mv_posi(i,1)<len2)
  {
    p_s2[bw_dialog_bua1.get_win_mv_posi(i,1)]=0;
  }
  else
  {
    p_s2[len2-1]=0;
  }

  return(0);
}

int bw_dialog::w_mv_exist(char *p_s1,int len,int wpp)
{
  int  i,j;
  int  exist;
  char sv1[SMG_LEN];
  //char s3[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) s3[j]=s1[j];
  if (i>0) s3[i-1]=0;
  else s3[0]=0;
*/
  //bw_main1.set_string(s3,SMG_LEN,s1,len);

  exist=0;
  for (i=0;i<win_mv_pp1;i++)
  {
    bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);

    if ((strcmp(p_s1,sv1)==0)&&(bw_dialog_bua1.get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }
  return(exist);
}
int bw_dialog::w_mv_add_name(char *p_tmpc1,int len)
{
  //char s3[SMG_LEN];
  int  i,j;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) s3[j]=s_tmpc1[j];
  if (i>0) s3[i-1]=0;
  else s3[0]=0;
*/
  //bw_main1.set_string(s3,SMG_LEN,s_tmpc1,len);

  bw_dialog_bua1.set_win_mv_name(win_mv_pp1,p_tmpc1,len);
  bw_dialog_bua1.set_win_mv_posi(win_mv_pp1,0,0);
  bw_dialog_bua1.set_win_mv_posi(win_mv_pp1,1,0);
  i=win_mv_pp1;
  win_mv_pp1++; /* point empty array */
  if (win_mv_pp1>=MEM_VAR) win_mv_pp1--;
  return(i);
}
int bw_dialog::w_mv_seri(char *p_tmpc1,int len,int wpp)
{
  int  i,j;
  int  exist;
  char sv1[SMG_LEN];
  //char sd1[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=s_tmpc1[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,s_tmpc1,len);

  exist=0;
  for (i=0;i<win_mv_pp1;i++)
  {
    bw_dialog_bua1.get_win_mv_name(i,sv1,SMG_LEN);

    if ((strcmp(p_tmpc1,sv1)==0)&&(bw_dialog_bua1.get_win_mv_type(i,4)==wpp))
    {
      exist=1;
      break;
    }
  }
  if (exist==1) return(i);
  else return(-1);
}
int bw_dialog::w_mv_move_aft(int dd,int num)
{
  int i,j;
  if (dd<=0) return(0);
  if (win_mv_pp2+dd>=MEM_LEN) return(1);
  else win_mv_pp2=win_mv_pp2+dd;
  for (i=win_mv_pp1-1;i>num;i--)
  {
    for (j=bw_dialog_bua1.get_win_mv_posi(i,0);j<bw_dialog_bua1.get_win_mv_posi(i,0)+bw_dialog_bua1.get_win_mv_posi(i,1);j++)
    {
      bw_dialog_bua1.set_win_mv_stor(j+dd,bw_dialog_bua1.get_win_mv_stor(j));
    }
    bw_dialog_bua1.set_win_mv_posi(i,0,bw_dialog_bua1.get_win_mv_posi(i,0)+dd);
  }
  return(0);
}
int bw_dialog::w_mv_move_bef(int dd,int num)
{
  int i,j;
  if (dd<=0) return(0);
  if (win_mv_pp2-dd<0) return(1);
  else win_mv_pp2=win_mv_pp2-dd;
  for (i=num+1;i<win_mv_pp1;i++)
  {
    for (j=bw_dialog_bua1.get_win_mv_posi(i,0);j<bw_dialog_bua1.get_win_mv_posi(i,0)+bw_dialog_bua1.get_win_mv_posi(i,1);j++)
    {
      bw_dialog_bua1.set_win_mv_stor(j-dd,bw_dialog_bua1.get_win_mv_stor(j));
    }
    bw_dialog_bua1.set_win_mv_posi(i,0,bw_dialog_bua1.get_win_mv_posi(i,0)-dd);
  }
  return(0);
}

int bw_dialog::w_mv_sav_var(char *p_s1,int len,int wpp)
{
//  HDC    hdc;
  char   sm1[SMG_LEN];
  //char   sd1[SMG_LEN];
  int    i,j;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=s1[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,s1,len);

  if (w_mv_exist(p_s1,len,wpp)!=1) return(1);

  i=w_mv_seri(p_s1,len,wpp);

  j=bw_dialog_bua1.get_win_mv_type(i,2);

  bw_dialog_bua1.setc_win_mv_getv(wpp,j,0);

  bw_dialog_bua1.get_win_mv_getv(wpp,sm1,SMG_LEN);

  w_mv_add_val(p_s1,len,wpp,sm1,SMG_LEN);

  return(0);
}

int bw_dialog::w_mv_get_var(char *p_s1,int len,int wpp)
{
//  HDC    hdc;
  char   sm1[SMG_LEN];
  //char   sd1[SMG_LEN];
  int    i,j;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=s1[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,s1,len);

  w_mv_fet_val(p_s1,len,wpp,sm1,SMG_LEN);

  bw_dialog_bua1.set_win_mv_getv(wpp,sm1,SMG_LEN);

  return(0);
}

int bw_dialog::w_echo_winrec_var(int wpp)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  HWND  hnd;
  int  i,j,k,l,q;
  char str[SMG_LEN];
  char str2[SMG_LEN];
  int  len,len2,len3;

  hdc=GetDC(bw_main1.win_hwnd);

  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
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

    bw_win1.w_find_winfname(wpp,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

    if ((str[0]=='?')||(str[0]=='-'))
    {
      if (w_mv_exist(str,SMG_LEN,wpp)!=1) continue;

      k=w_mv_seri(str,SMG_LEN,wpp);
      if (k>=0)
      {
	if (bw_dialog_bua1.get_win_mv_type(k,0)!=2)
	  bw_win1.w_set_winfedit(wpp,bw_win1.pline,bw_win1.pfield,1);

        w_mv_fet_val(str,SMG_LEN,wpp,str2,SMG_LEN);

	len =bw_dialog_bua1.get_win_mv_type(k,2);

	len2=bw_win1.w_find_winflen(wpp,bw_win1.pline,bw_win1.pfield);

        len3=strlen(str2);

	if (len2>len) l=len;
        else  l=len2;

	bw_dialog_bua1.set_win_mv_type(k,5,l);

        if (len3<l) l=len3;

	if (str[0]=='?')
        {
	  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
          {
	    TextOut(hdc
		   ,(int)((bw_win1.pfield-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_edit_xchar)
		   ,(int)((bw_win1.pline-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_edit_ychar)
		   ,str2,l);
	  }
	  else
	  {
	    TextOut(hdc
		   ,(int)((bw_win1.pfield-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_xchar)
		   ,(int)((bw_win1.pline-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_ychar)
		   ,str2,l);
	  }
	}
	else
	{
	  q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
	  if (q!=0)
	  {
            hnd=bw_win_bua1.get_win_hnd(q);
	    SetWindowText(hnd,str2);
          }
        }
      }
    }
  }

  ShowCaret(bw_main1.win_hwnd);

  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
  {
    SelectObject(hdc,holdfont);
  }

  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}
int bw_dialog::w_mv_get_read_paint(char *p_str,int len,int wpp,char comm)
{
  HWND hnd;
  int  i,j,q;
  char sm1[SMG_LEN];
  //char sd1[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=str[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,str,len);

  if ((p_str[0]!='?')&&(p_str[0]!='-')) return(1);

  if (w_mv_exist(p_str,len,wpp)!=1) return(1);

  w_mv_get_var(p_str,len,wpp);

  i=w_mv_seri(p_str,len,wpp);

  bw_dialog_bua1.get_win_mv_getv(wpp,sm1,SMG_LEN);

  if (p_str[0]=='?')
  {
    j=bw_getread1.get_read(bw_win1.pline-bw_win_bua1.get_win_con(wpp,1)+1,
		       bw_win1.pfield-bw_win_bua1.get_win_con(wpp,0)+1,
		       "",
		       sm1,
		       bw_dialog_bua1.get_win_mv_type(i,5),
		       bw_dialog_bua1.get_win_mv_type(i,1),
		       comm,
		       bw_dialog_bua1.get_win_mv_type(i,2),
		       bw_dialog_bua1.get_win_mv_type(i,3),
		       1,1,
		       bw_dialog_bua1.get_win_mv_getp(wpp),
		       bw_win_bua1.get_win_pp11(wpp));

  }
  else
  {
    q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
    if (q!=0)
    {
      hnd=bw_win_bua1.get_win_hnd(q);
      SetWindowText(hnd,sm1);
    }
  }

  return(j);
}
int bw_dialog::w_mv_get_read(char *p_str,int len,int wpp,char comm)
{
  HWND hnd;
  int  i,j,q;
  char sm1[SMG_LEN];
  //char sd1[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=str[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,str,len);

  if ((p_str[0]!='?')&&(p_str[0]!='-')) return(1);

  if (w_mv_exist(p_str,len,wpp)!=1) return(1);

  w_mv_get_var(p_str,len,wpp);

  i=w_mv_seri(p_str,len,wpp);

  bw_dialog_bua1.get_win_mv_getv(wpp,sm1,SMG_LEN);

  if (p_str[0]=='?')
  {
    j=bw_getread1.get_read(bw_win1.pline-bw_win_bua1.get_win_con(wpp,1)+1,
		       bw_win1.pfield-bw_win_bua1.get_win_con(wpp,0)+1,
		       "",
		       sm1,
		       bw_dialog_bua1.get_win_mv_type(i,5),
		       bw_dialog_bua1.get_win_mv_type(i,1),
		       comm,
		       bw_dialog_bua1.get_win_mv_type(i,2),
		       bw_dialog_bua1.get_win_mv_type(i,3),
		       1,1,
		       bw_dialog_bua1.get_win_mv_getp(wpp),
		       bw_win_bua1.get_win_pp11(wpp));

    if ((GetFocus()==bw_win_bua1.get_win_phh(wpp))||(bw_win_bua1.get_ci_mhnd(GetFocus())==bw_win_bua1.get_win_phh(wpp)))
    {
      SetFocus(bw_win_bua1.get_win_phh(wpp));
    }
  }
  else
  {
    q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
    if (q!=0)
    {
      hnd=bw_win_bua1.get_win_hnd(q);
      SetWindowText(hnd,sm1);
      if (bw_main1.win_key!=401) SetFocus(hnd);
    }
  }

  return(j);
}
int bw_dialog::w_mv_get_read1(char *p_str,int len,int wpp,char comm)
{
  int  i,j;
  char sm1[SMG_LEN];
  //char sd1[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) sd1[j]=str[j];
  if (i>0) sd1[i-1]=0;
  else sd1[0]=0;
*/
  //bw_main1.set_string(sd1,SMG_LEN,str,len);

  if (p_str[0]!='?') return(1);

  if (w_mv_exist(p_str,len,wpp)!=1) return(1);

  i=w_mv_seri(p_str,len,wpp);

  bw_dialog_bua1.get_win_mv_getv(wpp,sm1,SMG_LEN);

  j=bw_getread1.get_read(bw_win1.pline-bw_win_bua1.get_win_con(wpp,1)+1,
		       bw_win1.pfield-bw_win_bua1.get_win_con(wpp,0)+1,
		       "",
		       sm1,
		       bw_dialog_bua1.get_win_mv_type(i,5),
		       bw_dialog_bua1.get_win_mv_type(i,1),
		       comm,
		       bw_dialog_bua1.get_win_mv_type(i,2),
		       bw_dialog_bua1.get_win_mv_type(i,3),
		       1,1,
		       bw_dialog_bua1.get_win_mv_getp(wpp),
		       bw_win_bua1.get_win_pp11(wpp));

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
  char s_tmpc2[SMG_LEN];
//  char s_fldtable[SMG_LEN];
//  char s_fldname[SMG_LEN];
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
  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
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

	bw_win_bua1.get_1fldname(k,str,FLD_NAME_LEN);

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
	  if (m==8)  bw_inkey1.long2char(bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0),s_tmpc2);
	  if (m==9)  bw_inkey1.long2char(bw_xbase_bua1.get_win_rcnt(p_fcnt),s_tmpc2);

	  if (strlen(str)>strlen(s_tmpc2)) l=strlen(s_tmpc2);
	  else l=bw_win_bua1.get_1fldlen(k);

	  if (bw_win_bua1.get_1fldlen(k)>s_tmpn2[m]) n=s_tmpn2[m];
	  else n=bw_win_bua1.get_1fldlen(k);

	  if (n>l)
	  {
	    for (o=l;o<n;o++) s_tmpc2[o]=' ';
            s_tmpc2[n]=0;
          }

	  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
	      TextOut(hdc
		     ,(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_edit_xchar)
			 ,(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_edit_ychar)
			 ,s_tmpc2,n);
	  else
	      TextOut(hdc
		     ,(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_xchar)
			 ,(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_ychar)
			 ,s_tmpc2,n);

	}
      }
    }
  }

  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
  {
    SelectObject(hdc,holdfont);
  }
  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}

int bw_dialog::w_get_yy(char *p_tmpc2,int len)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_LEN];
  if (len<10) return(0);
  for (i=0;i<3;i++) p_tmpc2[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_tmpc2[0]=s_tmpc3[22];
  p_tmpc2[1]=s_tmpc3[23];
*/
  return(0);
}

int bw_dialog::w_get_mm(char *p_tmpc2,int len)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_LEN];
  char s_tmpc4[4];
  char s_tmpc5[SMG_LEN];
  if (len<10) return(0);
  for (i=0;i<3;i++) p_tmpc2[i]=' ';
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
  bw_inkey1.int2char(i,s_tmpc5);
  p_tmpc2[0]=s_tmpc5[3];
  p_tmpc2[1]=s_tmpc5[4];
*/
  return(0);
}

int bw_dialog::w_get_dd(char *p_tmpc2,int len)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_LEN];
  if (len<10) return(0);
  for (i=0;i<3;i++) p_tmpc2[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_tmpc2[0]=s_tmpc3[8];
  p_tmpc2[1]=s_tmpc3[9];
*/
  return(0);
}

int bw_dialog::w_get_year(char *p_tmpc2,int len)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_LEN];
  if (len<10) return(0);
  for (i=0;i<4;i++) p_tmpc2[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_tmpc2[0]=s_tmpc3[20];
  p_tmpc2[1]=s_tmpc3[21];
  p_tmpc2[2]=s_tmpc3[22];
  p_tmpc2[3]=s_tmpc3[23];
*/
  return(0);
}

int bw_dialog::w_get_mon(char *p_tmpc2,int len)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_LEN];
  if (len<10) return(0);
  for (i=0;i<3;i++) p_tmpc2[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_tmpc2[0]=s_tmpc3[4];
  p_tmpc2[1]=s_tmpc3[5];
  p_tmpc2[2]=s_tmpc3[6];
*/
  return(0);
}

int bw_dialog::w_get_time(char *p_tmpc2,int len)
{
/*
  time_t t;
  int i;
  char s_tmpc3[SMG_LEN];
  if (len<10) return(0);
  for (i=0;i<8;i++) p_tmpc2[i]=' ';
  time(&t);
  strcpy(s_tmpc3,ctime(&t));
  p_tmpc2[0]=s_tmpc3[11];
  p_tmpc2[1]=s_tmpc3[12];
  p_tmpc2[2]=s_tmpc3[13];
  p_tmpc2[3]=s_tmpc3[14];
  p_tmpc2[4]=s_tmpc3[15];
  p_tmpc2[5]=s_tmpc3[16];
  p_tmpc2[6]=s_tmpc3[17];
  p_tmpc2[7]=s_tmpc3[18];
*/
  return(0);
}

int bw_dialog::w_get_usr(char *p_tmpc2,int len)
{
  int i;
  if (len<30) return(0);
  for (i=0;i<30;i++) p_tmpc2[i]=' ';
  strcpy(p_tmpc2,"DaiPoZhi");
  return(0);
}
