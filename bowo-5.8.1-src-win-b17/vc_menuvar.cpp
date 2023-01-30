
#define  STRICT
#include <windows.h>
#include <commdlg.h>
 
#include <stdio.h>
#include <math.h>
#include <direct.h>
#include <dos.h>
#include <io.h>
#include <conio.h>
#include <process.h>
#include <string.h>

#include <time.h>

#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_rabox        bw_rabox1;
extern class bw_buff         bw_buff1;
extern class bw_xbase        bw_xbase1;
extern class bw_getread      bw_getread1;
extern class bw_dialog       bw_dialog1;
extern class bw_chkbox       bw_chkbox1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;
extern class bw_buttonvar    bw_buttonvar1;

#define DEBUG_MV 0

int bw_buttonvar::w_button_find_seri(int p1)
{
  return(get_t5_btn_wind(p1));
}

int bw_buttonvar::w_read_btndc(char *p_fn,int p_fn_size,int p_wptr)
{
  int  i,j;
  int  p1,p2,p3,p4,p5,p6,p7,p8,same;
  int  ptr1;
  char sfn1[FN_SIZE];
  char tmps2[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  int  exist;
  FILE *fp1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(sfn1,p_fn);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb1");

  exist=0;

  for (i=0;i<BUTTON_NUM_BTN;i++)
  {
    if (get_t5_btn_wind(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  ptr1=i;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.get_win_hwnd(p_wptr),sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    tmps2[0]=0;

    fgets(tmps2,SMG_SIZE,fp1);
						  /* scan for pre space */
    for (i=0;i<=strlen(tmps2);i++) if ((tmps2[i]<0)||(tmps2[i]>' ')) break;
    if (i>strlen(tmps2)) break;
    p1=i;

    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]>=0)&&(tmps2[i]<=' ')) break; /* scan for buttonname*/
    if (i>strlen(tmps2))
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p2=i;
	                     /* scan for space after buttonname*/
    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]<0)||(tmps2[i]>' ')) break;
    if (i>strlen(tmps2))
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p3=i;

    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]>=0)&&(tmps2[i]<=' ')) break; /* scan for button  */
    if (i>strlen(tmps2))
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p4=i;
					  /* scan for space after button  */
    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]<0)||(tmps2[i]>' ')) break;
    if (i>strlen(tmps2))
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p5=i;

    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]>=0)&&(tmps2[i]<=' ')) break; /* scan for command */
    if (i>strlen(tmps2))
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p6=i;

    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]<0)||(tmps2[i]>' ')) break;
    p7=i;

    for (i=i;i<=strlen(tmps2);i++) if ((tmps2[i]>=0)&&(tmps2[i]<=' ')) break; /* scan for command */
    p8=i;

    set_c_t5_btn_name(ptr1,0,0);

    for (j=p1;j<p2;j++)
    {
      if ((tmps2[j]>=0)&&(tmps2[j]<=' ')) break;
      set_c_t5_btn_name(ptr1,j-p1+0,tmps2[j]);
      set_c_t5_btn_name(ptr1,j-p1+1,0);
    }

    set_c_t5_btn_button(ptr1,0,0);

    for (j=p3;j<p4;j++)
    {
      if ((tmps2[j]>=0)&&(tmps2[j]<=' ')) break;
      set_c_t5_btn_button(ptr1,j-p3+0,tmps2[j]);
      set_c_t5_btn_button(ptr1,j-p3+1,0);
    }

    get_t5_btn_button(ptr1,sb1,SMG_SIZE);

    same=0;
    if (strncmp("button=",sb1,7)==0) same=1;
    if (strncmp("bitmap=",sb1,7)==0) same=1;
    if (same==0)
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }

    set_c_t5_btn_comm(ptr1,0,0);

    for (j=p5;j<p6;j++)
    {
      if ((tmps2[j]>=0)&&(tmps2[j]<=' ')) break;
      set_c_t5_btn_comm(ptr1,j-p5+0,tmps2[j]);
      set_c_t5_btn_comm(ptr1,j-p5+1,0);
    }

    get_t5_btn_comm(ptr1,so1,SMG_SIZE);

    same=0;
    if (strncmp("com=",so1,4)==0) same=1;
    if (strncmp("do=",so1,3)==0) same=1;
    if (same==0)
    {
      fclose(fp1);
      bw_win1.w_atten36(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }

    set_c_t5_btn_focus(ptr1,0,0);

    for (j=p7;j<p8;j++)
    {
      if ((tmps2[j]>=0)&&(tmps2[j]<=' ')) break;
      set_c_t5_btn_focus(ptr1,j-p7,tmps2[j]);
      set_c_t5_btn_focus(ptr1,j-p7+1,0);
    }

    set_t5_btn_wind(ptr1,p_wptr);

    ptr1++;
  }

  t5_btn_ptr1=ptr1;

  fclose(fp1);
/*
  for (i=0;i<t5_btn_ptr1;i++)
  {
    loc(i+1,1);
    printf("%s,%s,%s,"
	   ,t5_btn_name[i]
	   ,t5_btn_button[i]
	   ,t5_btn_comm[i]);
  }
  inkey();
*/
  return(0);
}

int bw_buttonvar::tst_button()
{
  int  i;
  char str[SMG_SIZE];
  char sn1[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  char sf1[SMG_SIZE];

  bw_getread1.deb_record("bw_buttonvar::tst_button()");

  for (i=0;i<60;i++)
  {
    get_t5_btn_name(i,sn1,SMG_SIZE);
    get_t5_btn_button(i,sb1,SMG_SIZE);
    get_t5_btn_comm(i,so1,SMG_SIZE);
    get_t5_btn_focus(i,sf1,SMG_SIZE);

    sprintf(str,"ptr=%d,wind=%d,mcntr=%d,ptr1=%d,name=%s,button=%s,comm=%s,focus=%s,"
				 ,i,get_t5_btn_wind(i)
                                 ,get_t5_btn_mcntr(i)
				 ,t5_btn_ptr1
				 ,sn1
			         ,sb1
				 ,so1
                                 ,sf1
				 );

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_buttonvar::w_dele_button(int wptr)
{
  int  i;
  int  p1,p2,p3,p4,p5,p6;
  char sn1[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  char sf1[SMG_SIZE];

  p1=(-1);  /* begin ptr*/ 
  p2=(-1);  /* end ptr*/  
  p3=0;     /* end big win ptr*/
  p4=0;     /* mn cntr*/
  p5=0;
  p6=0;

  for (i=0;i<t5_btn_ptr1;i++)
  {
    if (get_t5_btn_wind(i)==wptr)
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (get_t5_btn_wind(i)>wptr)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
      p3=i;
    }
  }

  if (p2<0)
  {
    p2=t5_btn_ptr1;
    p3=p2-1;
  }

  if ((p1<0)||(p4==0))
  {
    for (i=p2;i<=p3;i++)
    {
      set_t5_btn_wind(i,get_t5_btn_wind(i)-1);
    }
  }
  else
  {
    if (p3>=p2)
    {
      for (i=p2;i<=p3;i++)
      {
	get_t5_btn_name(i,sn1,SMG_SIZE);
        set_t5_btn_name(p1+i-p2,sn1,SMG_SIZE);

	get_t5_btn_button(i,sb1,SMG_SIZE);
	set_t5_btn_button(p1+i-p2,sb1,SMG_SIZE);

	get_t5_btn_comm(i,so1,SMG_SIZE);
	set_t5_btn_comm(p1+i-p2,so1,SMG_SIZE);

	get_t5_btn_focus(i,sf1,SMG_SIZE);
	set_t5_btn_focus(p1+i-p2,sf1,SMG_SIZE);

	set_t5_btn_mcntr(p1+i-p2,get_t5_btn_mcntr(i));
	set_t5_btn_wind(p1+i-p2,get_t5_btn_wind(i)-1);
      }

      for (i=p1+p3-p2+1;i<t5_btn_ptr1;i++)
      {
	set_c_t5_btn_name(i,0,0);
	set_c_t5_btn_button(i,0,0);
	set_c_t5_btn_comm(i,0,0);
	set_c_t5_btn_focus(i,0,0);
	set_t5_btn_mcntr(i,0);
	set_t5_btn_wind(i,0);
      }

      t5_btn_ptr1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<t5_btn_ptr1;i++)
      {
	set_c_t5_btn_name(i,0,0);
        set_c_t5_btn_button(i,0,0);
	set_c_t5_btn_comm(i,0,0);
	set_c_t5_btn_focus(i,0,0);
	set_t5_btn_mcntr(i,0);
	set_t5_btn_wind(i,0);
      }

      t5_btn_ptr1=p1;
    }
  }

  return(0);
}

int bw_buttonvar::tst_button2()
{
  int  i;
  char str[3000];
  char sn1[SMG_SIZE];
  char sb1[SMG_SIZE];
  char so1[SMG_SIZE];
  char sf1[SMG_SIZE];

  bw_getread1.deb_record("bw_buttonvar::tst_button2()");

  sprintf(str,"t5_btn_ptr1=%d,BUTTON_NUM_BTN=%d,",t5_btn_ptr1,BUTTON_NUM_BTN);
  bw_getread1.deb_record(str);

  for (i=0;i<100;i++)
  {
    get_t5_btn_name(i,sn1,SMG_SIZE);
    get_t5_btn_button(i,sb1,SMG_SIZE);
    get_t5_btn_comm(i,so1,SMG_SIZE);
    get_t5_btn_focus(i,sf1,SMG_SIZE);

    sprintf(str,"ptr=%d,wind=%d,mcntr=%d,name=%s,button=%s,comm=%s,focus=%s,"
				 ,i
                                 ,get_t5_btn_wind(i)
                                 ,get_t5_btn_mcntr(i)
				 ,sn1
			         ,sb1
				 ,so1
                                 ,sf1
				 );

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_buttonvar::w_button_comm(int p1,int state)
{
  int  i;
  int  exist;
  int  tot;
  char s1[SMG_SIZE];
  char s2[SMG_SIZE];
  char s3[50][30];
  char s4[SMG_SIZE];

  if (p1<0)
  {
    t5_btn_com_str[0]=0;
    t5_btn_ptr2=0;
    return(1);
  }

  strcpy(s3[ 0],"get_tab(");
  strcpy(s3[ 1],"get_edit(");
  strcpy(s3[ 2],"get_menu(");
  strcpy(s3[ 3],"get_chkbox(");
  strcpy(s3[ 4],"get_rabox(");
  strcpy(s3[ 5],"get_mchkbox(");
  strcpy(s3[ 6],"setup_sys(");
  strcpy(s3[ 7],"return(");
  strcpy(s3[ 8],"setup(");
  strcpy(s3[ 9],"get_tab_read(");
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


  tot=28;
  t5_btn_ptr2=0;
  t5_btn_com_str[0]=0;
  if (state==0) get_t5_btn_comm(p1,s1,SMG_SIZE);
  else get_t5_btn_focus(p1,s1,SMG_SIZE);

  if (strncmp("com=",s1,4)==0)
  {
    bw_inkey1.cut_string(s1,4,strlen(s1)-4,SMG_SIZE,s2,SMG_SIZE);

    exist=0;

    for (i=0;i<=tot;i++)
    {
      if (strncmp(s3[i],s2,strlen(s3[i]))==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      t5_btn_ptr2=i+1;
      bw_inkey1.cut_string(s2,strlen(s3[i]),strlen(s2)-strlen(s3[i]),SMG_SIZE,s4,SMG_SIZE);
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
	  t5_btn_ptr2=0;
	  t5_btn_com_str[0]=0;
	}
	else
	{
	  bw_inkey1.cut_string(s4,1,i-1,SMG_SIZE,t5_btn_com_str,SMG_SIZE);
	}
      }
      else t5_btn_com_str[0]=0; /* mem var */
    }
    else
    {
      t5_btn_ptr2=0;
      t5_btn_com_str[0]=0;
    }
  }
  else
  {
    t5_btn_ptr2=0;
    t5_btn_com_str[0]=0;
  }

  return(0);
}

int bw_buttonvar::w_button_pntr(char *p_str,int p_str_size,int p1)
{
  int  i;
  int  exist;
  char sn1[SMG_SIZE];

  exist=0;

  for (i=0;i<t5_btn_ptr1;i++)
  {
    get_t5_btn_name(i,sn1,SMG_SIZE);

    if ((strcmp(p_str,sn1)==0)&&(p1==w_button_find_seri(i)))
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    t5_btn_ptr3=i;
    return(0);
  }
  else
  {
    t5_btn_ptr3=(-1);
    return(1);
  }
}

int bw_chkbox::w_chkbox_ini()
{
  int i;

  for (i=0;i<BUTTON_NUM_CHS;i++)
  {
    bw_chkbox1.set_win_chkbox(i,0,0);
    bw_chkbox1.set_c_win_chkbox_name(i,0,0);
  }

  win_chkbox_ptr1=0;

  return(0);
}

int bw_chkbox::w_read_chkdc(char *p_fn,int p_fn_size,int p_wptr)
{
  int  i,j,k,l,o;
  int  p1,p2,p3,p4,p5,p6;
  int  ptr1;
  char sfn1[FN_SIZE];
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];
  char str4[SMG_SIZE];
  int  exist;
  FILE *fp1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(sfn1,p_fn);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb6");

  exist=0;

  for (i=0;i<BUTTON_NUM_CHS;i++)
  {
    if (bw_chkbox1.get_win_chkbox(i,0)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  ptr1=i;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.get_win_hwnd(p_wptr),sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    str4[0]=0;

    fgets(str4,SMG_SIZE,fp1);
						  /* scan for pre space */
    for (i=0;i<=strlen(str4);i++) if ((str4[i]<0)||(str4[i]>' ')) break;
    if (i>strlen(str4)) break;
    p1=i;

    for (i=i;i<=strlen(str4);i++) if ((str4[i]>=0)&&(str4[i]<=' ')) break; /* scan for menuname*/
    if (i>strlen(str4))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p2=i;
					 /* scan for space after menuname*/
    for (i=i;i<=strlen(str4);i++) if ((str4[i]<0)||(str4[i]>' ')) break;
    if (i>strlen(str4))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p3=i;

    for (i=i;i<=strlen(str4);i++) if ((str4[i]>=0)&&(str4[i]<=' ')) break; /* scan for button  */
    if (i>strlen(str4))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p4=i;
					  /* scan for space after button  */
    for (i=i;i<=strlen(str4);i++) if ((str4[i]<0)||(str4[i]>' ')) break;
    if (i>strlen(str4))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p5=i;

    for (i=i;i<=strlen(str4);i++) if ((str4[i]>=0)&&(str4[i]<=' ')) break; /* scan for command */
    if (i>strlen(str4))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p6=i;

    bw_inkey1.cut_string(str4,p1+1,p2-p1-1,SMG_SIZE,str2,SMG_SIZE);
    o=bw_inkey1.str2int(str2,SMG_SIZE);

    bw_chkbox1.set_win_chkbox(ptr1,0,1);
    bw_chkbox1.set_win_chkbox(ptr1,2,o);
    bw_chkbox1.set_win_chkbox(ptr1,3,p_wptr);

    bw_chkbox1.set_c_win_chkbox_name(ptr1,0,0);

    for (j=p3;j<p4;j++)
    {
      if ((str4[j]>=0)&&(str4[j]<=' ')) break;
      
      bw_chkbox1.set_c_win_chkbox_name(ptr1,j-p3+0,str4[j]);
      bw_chkbox1.set_c_win_chkbox_name(ptr1,j-p3+1,0);
    }

    bw_inkey1.cut_string(str4,p5,p6-p5,SMG_SIZE,str2,SMG_SIZE);
    l=bw_inkey1.str2int(str2,SMG_SIZE);
    bw_chkbox1.set_win_chkbox(ptr1,1,l);

    bw_chkbox1.get_win_chkbox_name(ptr1,str3,SMG_SIZE);

    if (bw_dialog1.w_mv_exist(str3,SMG_SIZE,p_wptr)==1)
    {
      bw_dialog1.w_mv_fet_val(str3,SMG_SIZE,0,str1,SMG_SIZE);
      
      bw_chkbox1.set_win_chkbox(ptr1,1,bw_inkey1.str2int(str1,SMG_SIZE));
    }

    ptr1++;
  }

  win_chkbox_ptr1=ptr1;

  fclose(fp1);

  return(0);
}

int bw_chkbox::tst_chkbox()
{
  int  i;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  bw_getread1.deb_record("bw_chkbox::tst_chkbox()");

  for (i=0;i<60;i++)
  {
    bw_chkbox1.get_win_chkbox_name(i,str1,SMG_SIZE);

    sprintf(str2,"ptr=%d,chkbox0123,name,ptr1=%d,%d,%d,%d,%s,%d,",i,bw_chkbox1.get_win_chkbox(i,0)
				    ,bw_chkbox1.get_win_chkbox(i,1)
				    ,bw_chkbox1.get_win_chkbox(i,2)
				    ,bw_chkbox1.get_win_chkbox(i,3)
				    ,str1
				    ,win_chkbox_ptr1);

    bw_getread1.deb_record(str2);
  }

  return(0);
}


int bw_chkbox::w_dele_chkbox(int wp1,int wp2)
{
  int  i;
  int  p1,p2,p3,p4,p5,p6;
  char str1[SMG_SIZE];
/*
  p1=(-1);  // begin ptr
  p2=(-1);  // end ptr
  p3=0;     // end big win ptr
  p4=0;     // mn cntr
  p5=0;
  p6=0;

  for (i=0;i<=win_chkbox_ptr1;i++)
  {
    if ((bw_chkbox1.get_win_chkbox(i,3)>=wp1)&&(bw_chkbox1.get_win_chkbox(i,3)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (bw_chkbox1.get_win_chkbox(i,3)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (bw_chkbox1.get_win_chkbox(i,3)>wp2)
    {
      p3=i;
    }
  }
  if (p2<0)
  {
    p2=win_chkbox_ptr1+1;
    p3=p2-1;
  }

  if ((p1<0)||(p4==0))
  {
    for (i=p2;i<=p3;i++)
    {
      bw_chkbox1.set_win_chkbox(i,3,bw_chkbox1.get_win_chkbox(i,3)-wp2+wp1-1);
    }
  }
  else
  {
    if (p3>=p2)
    {
      for (i=p2;i<=p3;i++)
      {
	bw_chkbox1.get_win_chkbox_name(i,str1,SMG_SIZE);
	bw_chkbox1.set_win_chkbox_name(p1+i-p2,str1,SMG_SIZE);

	bw_chkbox1.set_win_chkbox(p1+i-p2,0,bw_chkbox1.get_win_chkbox(i,0));
	bw_chkbox1.set_win_chkbox(p1+i-p2,1,bw_chkbox1.get_win_chkbox(i,1));
	bw_chkbox1.set_win_chkbox(p1+i-p2,2,bw_chkbox1.get_win_chkbox(i,2));
	bw_chkbox1.set_win_chkbox(p1+i-p2,3,bw_chkbox1.get_win_chkbox(i,3)-wp2+wp1-1);
      }

      for (i=p1+p3-p2+1;i<=win_chkbox_ptr1;i++)
      {
	bw_chkbox1.set_c_win_chkbox_name(i,0,0);
	bw_chkbox1.set_win_chkbox(i,0,0);
	bw_chkbox1.set_win_chkbox(i,1,0);
	bw_chkbox1.set_win_chkbox(i,2,0);
	bw_chkbox1.set_win_chkbox(i,3,0);
      }
      win_chkbox_ptr1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_chkbox_ptr1;i++)
      {
	bw_chkbox1.set_c_win_chkbox_name(i,0,0);
	bw_chkbox1.set_win_chkbox(i,0,0);
	bw_chkbox1.set_win_chkbox(i,1,0);
	bw_chkbox1.set_win_chkbox(i,2,0);
	bw_chkbox1.set_win_chkbox(i,3,0);
      }
      win_chkbox_ptr1=p1;
    }
  }
*/
  return(0);

}
int bw_chkbox::w_save_chkbox(int p_wptr)
{
  int  i,j;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  for (i=0;i<win_chkbox_ptr1;i++)
  {
    bw_inkey1.int2str(bw_chkbox1.get_win_chkbox(i,1),str2,SMG_SIZE);
    bw_chkbox1.get_win_chkbox_name(i,str1,SMG_SIZE);
    bw_dialog1.w_mv_save_mem(str1,SMG_SIZE,p_wptr,str2,strlen(str2));
  }

  return(0);
}

int bw_chkbox::w_echo_chk_change(int link,int p_wptr)
{
  int i;
  int exist;

  exist=0;

  for (i=0;i<BUTTON_NUM_CHS;i++)
  {
    if ((bw_chkbox1.get_win_chkbox(i,2)==link)&&(bw_chkbox1.get_win_chkbox(i,3)==p_wptr))
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    if (bw_chkbox1.get_win_chkbox(i,1)==1) bw_chkbox1.set_win_chkbox(i,1,0);
    else bw_chkbox1.set_win_chkbox(i,1,1);

    return(i);
  }
  
  return(-1);
}

int bw_chkbox::w_clr_recvar_chkbox(int p_wptr)
{
  int i;

  for (i=0;i<BUTTON_NUM_CHS;i++)
  {
    bw_chkbox1.set_win_chkbox(i,0,0);
    bw_chkbox1.set_c_win_chkbox_name(i,0,0);
  }

  win_chkbox_ptr1=0;

  return(0);
}

int bw_chkbox::w_echo_winrec_chkbox(int p_wptr)
{
  int i,j,k,l,n,o;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  bw_win1.set_fld_l(p_wptr,1);
  bw_win1.set_fld_c(p_wptr,1);

  while (1)
  {
    i=bw_win1.get_fld_l(p_wptr);
    j=bw_win1.get_fld_c(p_wptr);

    bw_win1.w_next_afield(p_wptr);

    if ((i==bw_win1.get_fld_l(p_wptr))&&(j==bw_win1.get_fld_c(p_wptr))) break;

    bw_win1.w_find_winfname(p_wptr,bw_win1.get_fld_l(p_wptr),bw_win1.get_fld_c(p_wptr),str1,SMG_SIZE);

    if (str1[0]=='[')
    {
      bw_inkey1.cut_string(str1,1,strlen(str1)-1-1+1,SMG_SIZE,str2,SMG_SIZE);
      n=bw_inkey1.str2int(str2,SMG_SIZE);

      for (k=0;k<BUTTON_NUM_CHS;k++)
      {
	if ((bw_chkbox1.get_win_chkbox(k,2)==n)&&(bw_chkbox1.get_win_chkbox(k,3)==p_wptr))
        {
	  l=bw_chkbox1.get_win_chkbox(k,1);

	  o=bw_win1.w_find_hnd(p_wptr,bw_win1.get_fld_c(p_wptr),bw_win1.get_fld_l(p_wptr));

	  if (l>0)
	  {
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)0);
	  }
	  else
	  {
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)0);
	  }
	  break;
        }
      }
    }
  }

  return(0);
}

int bw_rabox::w_rabox_ini()
{
  int i;

  for (i=0;i<BUTTON_NUM_RA;i++)
  {
    set_win_rabox(i,0,0);
    set_c_win_rabox_name(i,0,0);
  }

  win_rabox_ptr1=0;

  return(0);
}

int bw_rabox::w_read_radc(char *p_fn,int p_fn_size,int p_wptr)
{
  int  i,j,k,l,o;
  int  p1,p2,p3,p4,p5,p6;
  int  ptr1;
  char sfn1[FN_SIZE];
  char st1[SMG_SIZE];
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];
  int  exist;
  FILE *fp1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(sfn1,p_fn);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb5");

  exist=0;

  for (i=0;i<BUTTON_NUM_RA;i++)
  {
    if (get_win_rabox(i,0)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  ptr1=i;

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.get_win_hwnd(p_wptr),sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    str3[0]=0;

    fgets(str3,SMG_SIZE,fp1);
						  /* scan for pre space */
    for (i=0;i<=strlen(str3);i++) if ((str3[i]<0)||(str3[i]>' ')) break;
    if (i>strlen(str3)) break;
    p1=i;

    for (i=i;i<=strlen(str3);i++) if ((str3[i]>=0)&&(str3[i]<=' ')) break; /* scan for menuname*/
    if (i>strlen(str3))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p2=i;
					 /* scan for space after menuname*/
    for (i=i;i<=strlen(str3);i++) if ((str3[i]<0)||(str3[i]>' ')) break;
    if (i>strlen(str3))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p3=i;

    for (i=i;i<=strlen(str3);i++) if ((str3[i]>=0)&&(str3[i]<=' ')) break; /* scan for button  */
    if (i>strlen(str3))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p4=i;
					  /* scan for space after button  */
    for (i=i;i<=strlen(str3);i++) if ((str3[i]<0)||(str3[i]>' ')) break;
    if (i>strlen(str3))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p5=i;

    for (i=i;i<=strlen(str3);i++) if ((str3[i]>=0)&&(str3[i]<=' ')) break; /* scan for command */
    if (i>strlen(str3))
    {
      fclose(fp1);
      bw_win1.w_atten37(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p6=i;

    bw_inkey1.cut_string(str3,p1+1,p2-p1-1,SMG_SIZE,str2,SMG_SIZE);
    o=bw_inkey1.str2int(str2,SMG_SIZE);
    set_win_rabox(ptr1,0,1);
    set_win_rabox(ptr1,2,o);
    set_win_rabox(ptr1,3,p_wptr);

    set_c_win_rabox_name(ptr1,0,0);

    for (j=p3;j<p4;j++)
    {
      if ((str3[j]>=0)&&(str3[j]<=' ')) break;
      
      set_c_win_rabox_name(ptr1,j-p3+0,str3[j]);
      set_c_win_rabox_name(ptr1,j-p3+1,0);
    }

    bw_inkey1.cut_string(str3,p5,p6-p5,SMG_SIZE,str2,SMG_SIZE);
    l=bw_inkey1.str2int(str2,SMG_SIZE);
    set_win_rabox(ptr1,1,l);

    get_win_rabox_name(ptr1,st1,SMG_SIZE);

    if (bw_dialog1.w_mv_exist(st1,SMG_SIZE,p_wptr)==1)
    {
      bw_dialog1.w_mv_fet_val(st1,SMG_SIZE,0,str1,SMG_SIZE);
      
      set_win_rabox(ptr1,1,bw_inkey1.str2int(str1,SMG_SIZE));
    }

    ptr1++;
  }

  win_rabox_ptr1=ptr1;

  fclose(fp1);

  return(0);
}

int bw_rabox::w_save_rabox(int p_wptr)
{
  int  i,j;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  for (i=0;i<win_rabox_ptr1;i++)
  {
    bw_inkey1.int2str(get_win_rabox(i,1),str2,SMG_SIZE);
    get_win_rabox_name(i,str1,SMG_SIZE);
    bw_dialog1.w_mv_save_mem(str1,SMG_SIZE,p_wptr,str2,strlen(str2));
  }

  return(0);
}

int bw_rabox::tst_rabox()
{
  int  i;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  bw_getread1.deb_record("bw_rabox::tst_rabox()");

  for (i=0;i<60;i++)
  {
    get_win_rabox_name(i,str1,SMG_SIZE);

    sprintf(str2,"ptr=%d,rabox0123,name,ptr1=%d,%d,%d,%d,%s,%d,",i,get_win_rabox(i,0)
				    ,get_win_rabox(i,1)
				    ,get_win_rabox(i,2)
				    ,get_win_rabox(i,3)
				    ,str1
				    ,win_rabox_ptr1);

    bw_getread1.deb_record(str2);
  }

  return(0);
}

int bw_rabox::w_dele_rabox(int wp1,int wp2)
{
  int  i;
  int  p1,p2,p3,p4,p5,p6;
  char str1[SMG_SIZE];
/*
  p1=(-1);  // begin ptr 
  p2=(-1);  // end ptr 
  p3=0;     // end big win ptr
  p4=0;     // mn cntr 
  p5=0;
  p6=0;

  for (i=0;i<=win_rabox_ptr1;i++)
  {
    if ((get_win_rabox(i,3)>=wp1)&&(get_win_rabox(i,3)<=wp2))
    {
      if (p5==0)
      {
	p1=i;
	p5=1;
      }
      p4++;
    }
    if (get_win_rabox(i,3)>wp2)
    {
      if (p6==0)
      {
	p2=i;
	p6=1;
      }
    }
    if (get_win_rabox(i,3)>wp2)
    {
      p3=i;
    }
  }
  if (p2<0)
  {
    p2=win_rabox_ptr1+1;
    p3=p2-1;
  }

  if ((p1<0)||(p4==0))
  {
    for (i=p2;i<=p3;i++)
    {
      set_win_rabox(i,3,get_win_rabox(i,3)-wp2+wp1-1);
    }
  }
  else
  {
    for (i=p2;i<=p3;i++)
    {
      get_win_rabox_name(i,str1,SMG_SIZE);
      set_win_rabox_name(p1+i-p2,str1,SMG_SIZE);
      
      set_win_rabox(p1+i-p2,0,get_win_rabox(i,0));
      set_win_rabox(p1+i-p2,1,get_win_rabox(i,1));
      set_win_rabox(p1+i-p2,2,get_win_rabox(i,2));
      set_win_rabox(p1+i-p2,3,get_win_rabox(i,3)-wp2+wp1-1);
    }

    if (p3>=p2)
    {
      for (i=p1+p3-p2+1;i<=win_rabox_ptr1;i++)
      {
	set_c_win_rabox_name(i,0,0);
	set_win_rabox(i,0,0);
	set_win_rabox(i,1,0);
	set_win_rabox(i,2,0);
	set_win_rabox(i,3,0);
      }
      win_rabox_ptr1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_rabox_ptr1;i++)
      {
	set_c_win_rabox_name(i,0,0);
	set_win_rabox(i,0,0);
	set_win_rabox(i,1,0);
	set_win_rabox(i,2,0);
	set_win_rabox(i,3,0);
      }
      win_rabox_ptr1=p1;
    }
  }
*/
  return(0);
}

int bw_rabox::w_set_radio_var(int l,int c,int p,int p_wptr)
{
  int  i,j,k,m,o,t1,t2;
  int  t3;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  t1=bw_win1.get_fld_l(p_wptr);
  t2=bw_win1.get_fld_c(p_wptr);
  t3=(-1);

  bw_win1.set_fld_l(p_wptr,1);
  bw_win1.set_fld_c(p_wptr,1);

  k=0;

  while (1)
  {
    i=bw_win1.get_fld_l(p_wptr);
    j=bw_win1.get_fld_c(p_wptr);

    bw_win1.w_next_afield(p_wptr);

    if ((i==bw_win1.get_fld_l(p_wptr))&&(j==bw_win1.get_fld_c(p_wptr))) break;

    bw_win1.w_find_winfname(p_wptr,bw_win1.get_fld_l(p_wptr),bw_win1.get_fld_c(p_wptr),str1,SMG_SIZE);

    if (str1[0]=='(')
    {
      bw_inkey1.cut_string(str1,1,strlen(str1)-1-1+1,SMG_SIZE,str2,SMG_SIZE);
      o=bw_inkey1.str2int(str2,SMG_SIZE);
      if (o==p)
      {
	k++;
	if ((bw_win1.get_fld_l(p_wptr)==l)&&(bw_win1.get_fld_c(p_wptr)==c))
        {
          for (m=0;m<BUTTON_NUM_RA;m++)
          {
	    if ((get_win_rabox(m,2)==p)&&(get_win_rabox(m,3)==p_wptr))
	    {
	      set_win_rabox(m,1,k);
              t3=m;
	      break;
	    }
          }
	  o=bw_win1.w_find_hnd(p_wptr,bw_win1.get_fld_c(p_wptr),bw_win1.get_fld_l(p_wptr));
	  SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)0);
	}
	else
	{
          o=bw_win1.w_find_hnd(p_wptr,bw_win1.get_fld_c(p_wptr),bw_win1.get_fld_l(p_wptr));
	  SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)0);
	}
      }
    }
  }

  bw_win1.set_fld_l(p_wptr,t1);
  bw_win1.set_fld_c(p_wptr,t2);

  return(t3);
}

int bw_rabox::w_echo_winrec_rabox(int p_wptr)
{
  int  i,j,o,m;
  int  arr[BUTTON_NUM_RA];
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  for (i=0;i<BUTTON_NUM_RA;i++) arr[i]=0;

  bw_win1.set_fld_l(p_wptr,1);
  bw_win1.set_fld_c(p_wptr,1);

  i=0;
  j=0;

  while ((i!=bw_win1.get_fld_l(p_wptr))||(j!=bw_win1.get_fld_c(p_wptr)))
  {
    i=bw_win1.get_fld_l(p_wptr);
    j=bw_win1.get_fld_c(p_wptr);

    bw_win1.w_next_afield(p_wptr);

    bw_win1.w_find_winfname(p_wptr,bw_win1.get_fld_l(p_wptr),bw_win1.get_fld_c(p_wptr),str1,SMG_SIZE);

    if (str1[0]=='(')
    {

      bw_inkey1.cut_string(str1,1,strlen(str1)-1-1+1,SMG_SIZE,str2,SMG_SIZE);

      o=bw_inkey1.str2int(str2,SMG_SIZE);
      arr[o]++;

      for (m=0;m<BUTTON_NUM_RA;m++)
      {

	if ((get_win_rabox(m,2)==o)&&(get_win_rabox(m,3)==p_wptr))
	{
	  if (get_win_rabox(m,1)==arr[o])
          {
            o=bw_win1.w_find_hnd(p_wptr,bw_win1.get_fld_c(p_wptr),bw_win1.get_fld_l(p_wptr));
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,11,(LPARAM)0);
          }
          else
          {
            o=bw_win1.w_find_hnd(p_wptr,bw_win1.get_fld_c(p_wptr),bw_win1.get_fld_l(p_wptr));
	    SendMessage(bw_win1.get_win_hnd(o),BM_SETCHECK,0,(LPARAM)0);
	  }
	  break;
	}
      }
    }
  }

  return(0);
}

int bw_rabox::w_clr_recvar_rabox(int p_wptr)
{
  int i;

  for (i=0;i<BUTTON_NUM_RA;i++)
  {
    set_win_rabox(i,0,0);
    set_c_win_rabox_name(i,0,0);
  }

  win_rabox_ptr1=0;

  return(0);
}

int bw_dialog::w_read_diadc(char *p_fn,int p_fn_size,int p_wptr)
{
  int  i,j,k,l;
  int  p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
  int  ptr1;
  char sfn1[FN_SIZE];
  char s_tmps1[SMG_SIZE];
  char s_tmps2[SMG_SIZE];
  char s_tmps3[SMG_SIZE];
  char s_tmps4[SMG_SIZE];
  char s_tmps5[SMG_SIZE];
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  FILE *fp1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(sfn1,p_fn);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb2");

  fp1=fopen(sfn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.get_win_hwnd(p_wptr),sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    s_tmps5[0]=0;

    fgets(s_tmps5,SMG_SIZE,fp1);
						  /* scan for pre space */
    for (i=0;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]<0)||(s_tmps5[i]>' ')) break;
    if (i>strlen(s_tmps5)) break;
    p1=i;

    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]>=0)&&(s_tmps5[i]<=' ')) break; /* scan for memvarname*/
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p2=i;
					 /* scan for space after memvarname*/
    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]<0)||(s_tmps5[i]>' ')) break;
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p3=i;

    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]>=0)&&(s_tmps5[i]<=' ')) break; /* scan for dtype   */
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p4=i;
					  /* scan for space after dtype   */
    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]<0)||(s_tmps5[i]>' ')) break;
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p5=i;

    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]>=0)&&(s_tmps5[i]<=' ')) break; /* scan for type    */
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p6=i;
					  /* scan for space after type   */
    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]<0)||(s_tmps5[i]>' ')) break;
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p7=i;

    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]>=0)&&(s_tmps5[i]<=' ')) break; /* scan for len */
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p8=i;
					  /* scan for space after len */
    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]<0)||(s_tmps5[i]>' ')) break;
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p9=i;

    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]>=0)&&(s_tmps5[i]<=' ')) break; /* scan for dec */
    if (i>strlen(s_tmps5))
    {
      fclose(fp1);
      bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
      return(1);
    }
    p10=i;
					  /* scan for space after dec   */
    for (i=i;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]<0)||(s_tmps5[i]>' ')) break;
    if ((i>strlen(s_tmps5))||(s_tmps5[i]!='"'))
    {
      p11=0;
      p12=0;
    }
    else
    {
      p11=i;
      for (i=i+1;i<=strlen(s_tmps5);i++) if ((s_tmps5[i]=='"')||((s_tmps5[i]>=0)&&(s_tmps5[i]<=' '))) break; /* scan for val */
      if (i>strlen(s_tmps5))
      {
        fclose(fp1);
        bw_win1.w_atten38(bw_main1.get_win_hwnd(p_wptr),sfn1);
        return(1);
      }
      p12=i;
    }

    s_tmps1[0]=0;

    for (j=p1;j<p2;j++)
    {
      if ((s_tmps5[j]>=0)&&(s_tmps5[j]<=' ')) break;
      
      s_tmps1[j-p1+0]=s_tmps5[j];
      s_tmps1[j-p1+1]=0;
    }
    if (w_mv_exist(s_tmps1,SMG_SIZE,0)==0) k=w_mv_add_name(s_tmps1,SMG_SIZE);
    else k=w_mv_seri(s_tmps1,SMG_SIZE,0);

    if (k>=0)
    {
      if (p3==p4-1)
      {
        if (s_tmps5[p3]=='e')  set_win_mv_type(k,0,2);
        else if (s_tmps5[p3]=='d') set_win_mv_type(k,0,1);
        else set_win_mv_type(k,0,2);
      }

      if (p5==p6-1)
      {
        set_win_mv_type(k,1,s_tmps5[p5]);
      }

      bw_inkey1.cut_string(s_tmps5,p7,p8-p7,SMG_SIZE,str2,SMG_SIZE);
      l=bw_inkey1.str2int(str2,SMG_SIZE);
      set_win_mv_type(k,2,l);

      bw_inkey1.cut_string(s_tmps5,p9,p10-p9,SMG_SIZE,str2,SMG_SIZE);
      l=bw_inkey1.str2int(str2,SMG_SIZE);
      set_win_mv_type(k,3,l);
      set_win_mv_type(k,4,0);

      if (p11==0)
      {
        s_tmps4[0]=0;
        w_mv_add_val(s_tmps1,SMG_SIZE,p_wptr,s_tmps4,SMG_SIZE);
      }
      else
      {
        if ((s_tmps5[p11]=='"')&&(s_tmps5[p12]=='"'))
        {
          for (j=p11;j<=p12;j++)
          {
	    s_tmps2[j-p11+0]=s_tmps5[j];
	    s_tmps2[j-p11+1]=0;
          }
          bw_inkey1.cut_string(s_tmps2,1,strlen(s_tmps2)-2,SMG_SIZE,s_tmps3,SMG_SIZE);
          w_mv_add_val(s_tmps1,SMG_SIZE,p_wptr,s_tmps3,SMG_SIZE);
        }
        else
        {
          s_tmps4[0]=0;
          w_mv_add_val(s_tmps1,SMG_SIZE,p_wptr,s_tmps4,SMG_SIZE);
        }
      }

      if (w_mv_exist(s_tmps1,SMG_SIZE,p_wptr)==1)
      {
        w_mv_fet_val(s_tmps1,SMG_SIZE,    0,str1,SMG_SIZE);
        w_mv_add_val(s_tmps1,SMG_SIZE,p_wptr,str1,SMG_SIZE);
      }
    }
  }

  fclose(fp1);

  return(0);
}

int bw_dialog::w_save_dialog(int p_wptr)
{
  int  i,j,k,l;
  char str[SMG_SIZE];
  char sv1[SMG_SIZE];
/*
  for (j=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),0);j<=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),2);j++)
  {
    for (i=0;i<=win_mv_ptr1;i++)
    {
      if (get_win_mv_type(i,4)==j)
      {
        get_win_mv_name(i,sv1,SMG_SIZE);
	k=w_mv_fet_val(sv1,SMG_SIZE,j,str,SMG_SIZE);
        l=get_win_mv_type(i,2);
	if (k==0) w_mv_save_mem(sv1,SMG_SIZE,p_wptr,str,l);
      }
    }
  }
*/
  return(0);
}

int bw_dialog::w_mv_save_mem(char *p_vname,int p_vname_size,int p_wptr,char *val,int val_size)
{
  int  i,k;
  char sd1[1000];
  char sv1[SMG_SIZE];

  p_wptr=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_save_mem(),p_vname=%s,p_vname_size=%d,p_wptr=%d,val=%s,val_size=%d,",p_vname,p_vname_size,p_wptr,val,val_size);
    bw_getread1.deb_record(sd1);
  }

  bw_inkey1.cpy_string(sv1,SMG_SIZE,val,val_size);

  val_size=(int)strlen(sv1);

  if (val_size<=0) // set empty string
  {
	  sv1[0]=' ';
	  sv1[1]=0;
	  val_size=1;
  }

  if (w_mv_exist(p_vname,p_vname_size,p_wptr)==0)
  {
    k=w_mv_add_name(p_vname,p_vname_size);
    if (k>=0)
    {
      set_win_mv_type(k,0,2);            /* edit able   */
      set_win_mv_type(k,1,'c');          /* var type    */
      set_win_mv_type(k,2,val_size);     /* var len     */      //remember
      set_win_mv_type(k,3,0);            /* dec is zero */
      set_win_mv_type(k,4,p_wptr);          /* free window var */
    }
  }
  else
  {
    k=w_mv_seri(p_vname,p_vname_size,p_wptr);
    if (k>=0)
    {
      set_win_mv_type(k,2,val_size);         /* var len */      //remember
    }
  }

  w_mv_add_val(p_vname,p_vname_size,p_wptr,sv1,val_size);

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_save_mem(),win_mv_ptr1=%d,win_mv_ptr2=%d,",win_mv_ptr1,win_mv_ptr2);
    bw_getread1.deb_record(sd1);
  }

  return(0);
}                 

int bw_dialog::w_dele_dialog(int wp1,int wp2)
{
  char sv1[SMG_SIZE];
  int  i;
  int  p1,p2,p3,p4,p5,p6,p7,p8,p9;
/*
  p1=(-1);  // begin ptr
  p2=(-1);  // end ptr
  p3=0;     // end big win ptr
  p4=0;     // mn cntr
  p5=0;
  p6=0;
  p7=(-1);
  p8=(-1);
  p9=0;

  for (i=0;i<=win_mv_ptr1;i++)
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

      win_mv_ptr2=p7+p9-p8+1;

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

      for (i=p1+p3-p2+1;i<=win_mv_ptr1;i++)
      {
	set_c_win_mv_name(i,0,0);

	set_win_mv_type(i,0,0);
	set_win_mv_type(i,1,0);
	set_win_mv_type(i,2,0);
	set_win_mv_type(i,3,0);
	set_win_mv_type(i,4,0);
	set_win_mv_type(i,5,0);

	set_win_mv_posi(i,0,0);
	set_win_mv_posi(i,1,0);
      }
      win_mv_ptr1=p1+p3-p2+1;
    }
    else
    {
      for (i=p1;i<=win_mv_ptr1;i++)
      {
	set_c_win_mv_name(i,0,0);
	set_win_mv_type(i,0,0);
	set_win_mv_type(i,1,0);
	set_win_mv_type(i,2,0);
	set_win_mv_type(i,3,0);
	set_win_mv_type(i,4,0);
	set_win_mv_type(i,5,0);

	set_win_mv_posi(i,0,0);
	set_win_mv_posi(i,1,0);
      }
      win_mv_ptr1=p1;
    }
  }
*/
  return(0);
}

int bw_dialog::w_clr_recvar_dialog(int p_wptr)
{
  int i;

  win_mv_ptr1=0;
  win_mv_ptr2=0;

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

//    bw_inkey1.cut_string(win_mv_stor,get_win_mv_posi(i,0),get_win_mv_posi(i,1),str);

    str[0]=0;
    for (j=get_win_mv_posi(i,0);j<get_win_mv_posi(i,0)+get_win_mv_posi(i,1);j++)
    {
      str[j-get_win_mv_posi(i,0)]=get_win_mv_stor(j);
      str[j-get_win_mv_posi(i,0)+1]=0;
    }

    TextOut(hdc,444,i*20,str,strlen(str));

    sprintf(str,"ptr1=%d,",win_mv_ptr1);
    TextOut(hdc,500,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_dialog::w_mv_add_val(char *p_vname,int p_vname_size,int p_wptr,char *p_val,int p_val_size)
{
  int  i,j,k,l;
  int  exist;
  char str3[SMG_SIZE];
  char sv1[SMG_SIZE];
  char sd1[1000];

  p_wptr=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_add_val(),p_vname=%s,p_vname_size=%d,p_wptr=%d,p_val=%s,p_val_size=%d,",p_vname,p_vname_size,p_wptr,p_val,p_val_size);
    bw_getread1.deb_record(sd1);
  }

  strcpy(str3,p_val);

  exist=0;

  for (i=0;i<win_mv_ptr1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);
    if ((strcmp(p_vname,sv1)==0)&&(get_win_mv_type(i,4)==p_wptr))
    {
      exist=1;
      break;
    }
  }

  if (exist==0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_add_val(),exist=%d,win_mv_ptr1=%d,win_mv_ptr2=%d,",exist,win_mv_ptr1,win_mv_ptr2);
      bw_getread1.deb_record(sd1);
    }

    return(1);
  }

  if (i<=0) set_win_mv_posi(i,0,0);
  //else set_win_mv_posi(i,0,get_win_mv_posi(i-1,0)+get_win_mv_posi(i-1,1));

  for (j=strlen(str3);j<get_win_mv_type(i,2);j++)
  {
    str3[j+0]=' ';
    str3[j+1]=0;
  }
  //str3[get_win_mv_type(i,2)]=0;

  k=get_win_mv_type(i,2);
  j=get_win_mv_posi(i,1)-k;
  l=0;

  if (j<0) l=w_mv_move_aft(0-j,i);
  if (j>0) l=w_mv_move_bef(  j,i);
  if (l!=0) 
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_add_val(),move bef or aft error,exist=%d,,win_mv_ptr1=%d,win_mv_ptr2=%d,",exist,win_mv_ptr1,win_mv_ptr2);
      bw_getread1.deb_record(sd1);
    }

    return(1);
  }

  set_win_mv_posi(i,1,k);

  for (j=0;j<k;j++)
  {
    set_win_mv_stor(get_win_mv_posi(i,0)+j,str3[j]);
  }

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_add_val(),win_mv_ptr1=%d,win_mv_ptr2=%d,posi(i,0)(mvar_ptr)=%d,posi(i,1)(mvar_len)=%d,"
               ,win_mv_ptr1,win_mv_ptr2,get_win_mv_posi(i,0),get_win_mv_posi(i,1));
    bw_getread1.deb_record(sd1);
  }

  return(0);
}

int bw_dialog::w_mv_fet_val(char *p_vname,int p_vname_size,int p_wptr,char *p_val,int p_val_size)
{
  int  i,j;
  int  exist;
  char sd1[1000];
  char sv1[SMG_SIZE];

  p_wptr=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_fet_val(),p_vname=%s,p_vname_size=%d,p_wptr=%d,",p_vname,p_vname_size,p_wptr);
    bw_getread1.deb_record(sd1);
  }

  p_val[0]=0;

  exist=0;

  for (i=0;i<win_mv_ptr1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    if ((strcmp(p_vname,sv1)==0)&&(get_win_mv_type(i,4)==p_wptr))
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
    if (j<p_val_size-1)
    {
      p_val[j+0]=get_win_mv_stor(get_win_mv_posi(i,0)+j);
      p_val[j+1]=0;
    }
  }

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_fet_val(),return val=%s,posi(i,0)(mvar_ptr)=%d,posi(i,1)(mvar_len)=%d,",p_val,get_win_mv_posi(i,0),get_win_mv_posi(i,1));
    bw_getread1.deb_record(sd1);
  }

  return(0);
}

int bw_dialog::w_mv_exist(char *p_vname,int p_vname_size,int p_wptr)
{
  int  i;
  int  exist;
  char sd1[1000];
  char sv1[SMG_SIZE];

  p_wptr=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_exist(),p_vname=%s,p_vname_size=%d,p_wptr=%d,",p_vname,p_vname_size,p_wptr);
    bw_getread1.deb_record(sd1);
  }

  exist=0;

  for (i=0;i<win_mv_ptr1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    if ((strcmp(p_vname,sv1)==0)&&(get_win_mv_type(i,4)==p_wptr))
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

int bw_dialog::w_mv_add_name(char *p_vname,int p_vname_size)
{
  char sd1[1000];
  //char str[SMG_SIZE];
  int  i;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_add_name(),p_vname=%s,p_vname_size=%d,",p_vname,p_vname_size);
    bw_getread1.deb_record(sd1);
  }

  set_win_mv_name(win_mv_ptr1,p_vname,p_vname_size);

  if (win_mv_ptr1<=0)// ---bug ok---
  {
    set_win_mv_posi(win_mv_ptr1,0,0);
    set_win_mv_posi(win_mv_ptr1,1,0);

    if (DEBUG_MV)
    {
      sprintf(sd1,"===set posi(i,0) val , win_mv_ptr1=%d,posi(i,0)(mvar_ptr)=%d,",win_mv_ptr1,get_win_mv_posi(win_mv_ptr1,0));
      bw_getread1.deb_record(sd1);
    }
  }
  else
  {
    set_win_mv_posi(win_mv_ptr1,0,get_win_mv_posi(win_mv_ptr1-1,0)+get_win_mv_posi(win_mv_ptr1-1,1));
    set_win_mv_posi(win_mv_ptr1,1,0);

    if (DEBUG_MV)
    {
      sprintf(sd1,"===set posi(i,0) val , win_mv_ptr1=%d,posi(i,0)(mvar_ptr)=%d,",win_mv_ptr1,get_win_mv_posi(win_mv_ptr1,0));
      bw_getread1.deb_record(sd1);
    }
  }

  i=win_mv_ptr1;

  win_mv_ptr1++; /* pntr empty array */
  if (win_mv_ptr1>=MEM_VAR_NUM) win_mv_ptr1--;

  if (DEBUG_MV)
  {
    sprintf(sd1,")))return from w_mv_add_name(),return val=%d,",i);
    bw_getread1.deb_record(sd1);
  }

  return(i);
}

int bw_dialog::w_mv_seri(char *p_vname,int p_vname_size,int p_wptr)
{
  int  i,j;
  int  exist;
  char sd1[1000];
  char sv1[SMG_SIZE];

  p_wptr=0;

  if (DEBUG_MV)
  {
    sprintf(sd1,"(((into w_mv_seri(),p_vname=%s,p_vname_size=%d,p_wptr=%d,",p_vname,p_vname_size,p_wptr);
    bw_getread1.deb_record(sd1);
  }

  exist=0;

  for (i=0;i<win_mv_ptr1;i++)
  {
    get_win_mv_name(i,sv1,SMG_SIZE);

    if ((strcmp(p_vname,sv1)==0)&&(get_win_mv_type(i,4)==p_wptr))
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
    sprintf(sd1,"(((into w_mv_move_aft(),dd(range)=%d,num(mvar_ptr)=%d,",dd,num);
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

  if (win_mv_ptr2+dd>=MEM_VAR_SIZE)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_move_aft(),win_mv_ptr2>=MEM_VAR_SIZE,");
      bw_getread1.deb_record(sd1);
    }
    return(1);
  }
  else win_mv_ptr2=win_mv_ptr2+dd;

/* --- bug 1---
  for (i=num+1;i<win_mv_ptr1;i++)
*/
  for (i=win_mv_ptr1-1;i>num;i--)
  {
/* --- bug 2---
    for (j=get_win_mv_posi(i,0);j<get_win_mv_posi(i,0)+get_win_mv_posi(i,1);j++)
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
    sprintf(sd1,"(((into w_mv_move_bef(),dd(range)=%d,num(mvar_ptr)=%d,",dd,num);
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

  if (win_mv_ptr2-dd<0)
  {
    if (DEBUG_MV)
    {
      sprintf(sd1,")))return from w_mv_move_bef(),win_mv_ptr2<0,");
      bw_getread1.deb_record(sd1);
    }
    return(1);
  }
  else win_mv_ptr2=win_mv_ptr2-dd;

  for (i=num+1;i<win_mv_ptr1;i++)
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

int bw_dialog::w_mv_sav_var(char *p_vname,int p_vname_size,int p_wptr)
{
  char   sm1[SMG_SIZE];
  int    i,j;

  if (w_mv_exist(p_vname,p_vname_size,p_wptr)!=1) return(1);

  i=w_mv_seri(p_vname,p_vname_size,p_wptr);

  j=get_win_mv_type(i,2);

  set_c_win_mv_getv(p_wptr,j,0);

  get_win_mv_getv(p_wptr,sm1,SMG_SIZE);

  w_mv_add_val(p_vname,p_vname_size,p_wptr,sm1,SMG_SIZE);

  return(0);
}

int bw_dialog::w_mv_get_var(char *p_vname,int p_vname_size,int p_wptr)
{
  char   sm1[SMG_SIZE];

  w_mv_fet_val(p_vname,p_vname_size,p_wptr,sm1,SMG_SIZE);

  set_win_mv_getv(p_wptr,sm1,SMG_SIZE);

  return(0);
}

int bw_dialog::w_echo_winrec_var(int p_wptr)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  HWND  hnd;
  int  i,j,k,l,q;
  char s_tabfld[SMG_SIZE];
  char s_fldval[SMG_SIZE];
  int  len,len2,len3;

  hdc=GetDC(bw_main1.get_win_hwnd(p_wptr));

  if (bw_win1.get_win_ci_mode(p_wptr)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  HideCaret(bw_main1.get_win_hwnd(p_wptr));

  bw_win1.set_fld_l(p_wptr,1);
  bw_win1.set_fld_c(p_wptr,1);

  while (1)
  {
    i=bw_win1.get_fld_l(p_wptr);
    j=bw_win1.get_fld_c(p_wptr);

    bw_win1.w_next_afield(p_wptr);

    if ((i==bw_win1.get_fld_l(p_wptr))&&(j==bw_win1.get_fld_c(p_wptr))) break;

    bw_win1.w_find_winfname(p_wptr,bw_win1.get_fld_l(p_wptr),bw_win1.get_fld_c(p_wptr),s_tabfld,SMG_SIZE);

    if ((s_tabfld[0]=='?')||(s_tabfld[0]=='-'))
    {
      if (w_mv_exist(s_tabfld,SMG_SIZE,p_wptr)!=1) continue;

      k=w_mv_seri(s_tabfld,SMG_SIZE,p_wptr);
      if (k>=0)
      {
	if (get_win_mv_type(k,0)!=2)
	  bw_win1.w_set_winfedit(p_wptr,bw_win1.get_fld_l(p_wptr),bw_win1.get_fld_c(p_wptr),1);

        w_mv_fet_val(s_tabfld,SMG_SIZE,p_wptr,s_fldval,SMG_SIZE);

	len =get_win_mv_type(k,2);

	len2=bw_win1.w_find_winflen(p_wptr,bw_win1.get_fld_l(p_wptr),bw_win1.get_fld_c(p_wptr));

        len3=strlen(s_fldval);

	if (len2>len) l=len;
        else  l=len2;

	set_win_mv_type(k,5,l);

        if (len3<l) l=len3;

	if (s_tabfld[0]=='?')
        {
	  if (bw_win1.get_win_ci_mode(p_wptr)==0)
          {
	    TextOut(hdc
		   ,(int)((bw_win1.get_fld_c(p_wptr)-bw_win1.get_win_con(p_wptr,0))*bw_main1.win_edit_xchar)
		   ,(int)((bw_win1.get_fld_l( p_wptr)-bw_win1.get_win_con(p_wptr,1))*bw_main1.win_edit_ychar)
		   ,s_fldval,l);
	  }
	  else
	  {
	    TextOut(hdc
		   ,(int)((bw_win1.get_fld_c(p_wptr)-bw_win1.get_win_con(p_wptr,0))*bw_main1.win_xchar)
		   ,(int)((bw_win1.get_fld_l( p_wptr)-bw_win1.get_win_con(p_wptr,1))*bw_main1.win_ychar)
		   ,s_fldval,l);
	  }
	}
	else
	{
	  q=bw_win1.w_find_hnd(p_wptr,bw_win1.get_fld_c(p_wptr),bw_win1.get_fld_l(p_wptr));
	  if (q!=0)
	  {
            hnd=bw_win1.get_win_hnd(q);
	    SetWindowText(hnd,s_fldval);
          }
        }
      }
    }
  }

  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

  if (bw_win1.get_win_ci_mode(p_wptr)==0)
  {
    SelectObject(hdc,holdfont);
  }

  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);

  return(0);
}
/*
int bw_dialog::w_mv_get_read_paint(char *p_str,int p_str_size,int p_wptr,char comm)
{
  HWND hnd;
  int  i,j,q;
  char sm1[SMG_SIZE];

  if ((p_str[0]!='?')&&(p_str[0]!='-')) return(1);

  if (w_mv_exist(p_str,p_str_size,p_wptr)!=1) return(1);

  w_mv_get_var(p_str,p_str_size,p_wptr);

  i=w_mv_seri(p_str,p_str_size,p_wptr);

  get_win_mv_getv(p_wptr,sm1,SMG_SIZE);

  if (p_str[0]=='?')
  {
    j=bw_getread1.get_read(bw_win1.fld_l-bw_win1.get_win_con(p_wptr,1)+1,
		       bw_win1.fld_c-bw_win1.get_win_con(p_wptr,0)+1,
		       "",
		       sm1,
		       get_win_mv_type(i,5),
		       get_win_mv_type(i,1),
		       comm,
		       get_win_mv_type(i,2),
		       get_win_mv_type(i,3),
		       1,1,
		       get_win_mv_getp(p_wptr),
		       bw_win1.get_win_ptr_get_rd(p_wptr));

  }
  else
  {
    q=bw_win1.w_find_hnd(p_wptr,bw_win1.fld_c,bw_win1.fld_l);
    if (q!=0)
    {
      hnd=bw_win1.get_win_hnd(q);
      SetWindowText(hnd,sm1);
    }
  }

  return(j);
}
*/
int bw_dialog::w_mv_get_read_g(char *p_str,int p_str_size,int p_wptr,char comm)
{
  HWND hnd;
  int  i,k=0,q;
  char sm1[SMG_SIZE];

  if ((p_str[0]!='?')&&(p_str[0]!='-')) return(1);

  if (w_mv_exist(p_str,p_str_size,p_wptr)!=1) return(1);

  if (bw_getread1.get_smg_modi(bw_win1.get_win_ptr_get_rd(p_wptr))==1)
  {
    bw_getread1.get_smg_string(bw_win1.get_win_ptr_get_rd(p_wptr),sm1,SMG_SIZE);
    set_win_mv_getv(p_wptr,sm1,SMG_SIZE);
  }
  else
  {
    w_mv_get_var(p_str,p_str_size,p_wptr);
  }

  i=w_mv_seri(p_str,p_str_size,p_wptr);

  get_win_mv_getv(p_wptr,sm1,SMG_SIZE);

  if (p_str[0]=='?')
  {
    k=bw_getread1.get_read(p_wptr,
                       bw_win1.get_pline(p_wptr)-bw_win1.get_win_con(p_wptr,1),
		       bw_win1.get_pcolu(p_wptr)-bw_win1.get_win_con(p_wptr,0),
		       "",
		       sm1,
		       get_win_mv_type(i,5),
		       get_win_mv_type(i,1),
		       comm,
		       get_win_mv_type(i,2),
		       get_win_mv_type(i,3),
		       1,1,
		       bw_getread1.get_smg_posi(p_wptr),
		       bw_win1.get_win_ptr_get_rd(p_wptr));

    if ((GetFocus()==bw_win1.get_win_phh(p_wptr))||(bw_win1.get_ci_mhnd(GetFocus())==bw_win1.get_win_phh(p_wptr)))
    {
      SetFocus(bw_win1.get_win_phh(p_wptr));
    }
  }
  else
  {
    q=bw_win1.w_find_hnd(p_wptr,bw_win1.get_pcolu(p_wptr),bw_win1.get_pline(p_wptr));
    if (q!=0)
    {
      hnd=bw_win1.get_win_hnd(q);
      SetWindowText(hnd,sm1);
      if (bw_main1.win_key!=401) SetFocus(hnd);
    }
  }

  return(k);
}

int bw_dialog::w_mv_get_read_r(char *p_str,int p_str_size,int p_wptr,char comm)
{
  int  i,k;
  char sm1[SMG_SIZE];

  if (p_str[0]!='?') return(1);

  if (w_mv_exist(p_str,p_str_size,p_wptr)!=1) return(1);

  i=w_mv_seri(p_str,p_str_size,p_wptr);

  get_win_mv_getv(p_wptr,sm1,SMG_SIZE);

  k=bw_getread1.get_read(p_wptr,
                       bw_win1.get_pline(p_wptr)-bw_win1.get_win_con(p_wptr,1),
		       bw_win1.get_pcolu(p_wptr)-bw_win1.get_win_con(p_wptr,0),
		       "",
		       sm1,
		       get_win_mv_type(i,5),
		       get_win_mv_type(i,1),
		       comm,
		       get_win_mv_type(i,2),
		       get_win_mv_type(i,3),
		       1,1,
		       bw_getread1.get_smg_posi(p_wptr),
		       bw_win1.get_win_ptr_get_rd(p_wptr));

  return(k);
}

int bw_dialog::w_echo_winrec_read(int p_dbptr,int p_wptr,int mark)
{
  HFONT  holdfont,hfont;
  HDC    hdc;
  int  i,j,k,l,m,n,o;
  int  exist;
  char s_tmps1[30][30];
  int  s_tmpn1;
  int  s_tmpn2[30];
  char s_tabfld[FLD_NAME_SIZE];
  char s_fldval[SMG_SIZE];

  strcpy(s_tmps1[ 1],"*y");
  s_tmpn2[1]=2;
  strcpy(s_tmps1[ 2],"*m");
  s_tmpn2[2]=2;
  strcpy(s_tmps1[ 3],"*d");
  s_tmpn2[3]=2;
  strcpy(s_tmps1[ 4],"*yr");
  s_tmpn2[4]=4;
  strcpy(s_tmps1[ 5],"*o");  // month
  s_tmpn2[5]=3;
  strcpy(s_tmps1[ 6],"*time");
  s_tmpn2[6]=8;
  strcpy(s_tmps1[ 7],"*usr");
  s_tmpn2[7]=10;
  strcpy(s_tmps1[ 8],"*recno");
  s_tmpn2[8]=6;
  strcpy(s_tmps1[ 9],"*recnum");
  s_tmpn2[9]=6;
  strcpy(s_tmps1[10],"*date");
  s_tmpn2[10]=10;

  s_tmpn1=10;

  hdc=GetDC(bw_main1.get_win_hwnd(p_wptr));
  if (bw_win1.get_win_ci_mode(p_wptr)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  for (i=0;i<LIN_NUM;i++)
  {
    for (j=0;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(p_wptr,i,j)!=0)
      {
	k=bw_buff1.get_t3_linecol(p_wptr,i,j);

	bw_win1.get_t_fldname(k,s_tabfld,FLD_NAME_SIZE);

	if (s_tabfld[0]=='*')
	{
          exist=0;

	  for (m=1;m<=s_tmpn1;m++)
	  {
	    if (strcmp(s_tabfld,s_tmps1[m])==0)
	    {
	      exist=1;
	      break;
	    }
	  }

	  if (exist==0) continue;

	  if ((mark<10)&&((m==1)||(m==2)||(m==3)||(m==4)||(m==5)||(m==7))) continue;

	  if (m== 1)  w_get_yy(s_fldval,30);
	  if (m== 2)  w_get_mm(s_fldval,30);
	  if (m== 3)  w_get_dd(s_fldval,30);
	  if (m== 4)  w_get_year(s_fldval,30);
	  if (m== 5)  w_get_mon(s_fldval,30);
	  if (m== 6)  w_get_time(s_fldval,30);
	  if (m== 7)  w_get_usr(s_fldval,30);
	  if (m== 8)  bw_inkey1.long2str(bw_xbase1.get_win_recno(p_dbptr,p_wptr,0),s_fldval,SMG_SIZE);
	  if (m== 9)  bw_inkey1.long2str(bw_xbase1.get_win_rec_cntr(p_dbptr),s_fldval,SMG_SIZE);
	  if (m==10)  w_get_date(s_fldval,30);

	  if (strlen(s_tabfld)>strlen(s_fldval)) l=strlen(s_fldval);
	  else l=bw_win1.get_t_fldlen(k);

	  if (bw_win1.get_t_fldlen(k)>s_tmpn2[m]) n=s_tmpn2[m];
	  else n=bw_win1.get_t_fldlen(k);

	  if (n>l)
	  {
	    for (o=l;o<n;o++) s_fldval[o]=' ';
            s_fldval[n]=0;
          }

	  if (bw_win1.get_win_ci_mode(p_wptr)==0)
	      TextOut(hdc
		     ,(int)((j-bw_win1.get_win_con(p_wptr,0))*bw_main1.win_edit_xchar)
			 ,(int)((i-bw_win1.get_win_con(p_wptr,1))*bw_main1.win_edit_ychar)
			 ,s_fldval,n);
	  else
	      TextOut(hdc
		     ,(int)((j-bw_win1.get_win_con(p_wptr,0))*bw_main1.win_xchar)
			 ,(int)((i-bw_win1.get_win_con(p_wptr,1))*bw_main1.win_ychar)
			 ,s_fldval,n);

	}
      }
    }
  }

  if (bw_win1.get_win_ci_mode(p_wptr)==0)
  {
    SelectObject(hdc,holdfont);
  }
  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);

  return(0);
}

int bw_dialog::w_get_yy(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  p_str[0]=0;
  if (p_str_size<10) return(0);
  for (i=0;i<3;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  p_str[0]=s_tmps3[22];
  p_str[1]=s_tmps3[23];
  p_str[2]=0;
  return(0);
}

int bw_dialog::w_get_mm(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  char s_tmps4[4];
  char s_tmps5[SMG_SIZE];
  p_str[0]=0;
  if (p_str_size<10) return(0);
  for (i=0;i<3;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  s_tmps4[0]=s_tmps3[4];
  s_tmps4[1]=s_tmps3[5];
  s_tmps4[2]=s_tmps3[6];
  s_tmps4[3]=0;
  i=0;
  if (strcmp(s_tmps4,"Jan")==0) i=1;
  if (strcmp(s_tmps4,"Feb")==0) i=2;
  if (strcmp(s_tmps4,"Mar")==0) i=3;
  if (strcmp(s_tmps4,"Apr")==0) i=4;
  if (strcmp(s_tmps4,"May")==0) i=5;
  if (strcmp(s_tmps4,"Jun")==0) i=6;
  if (strcmp(s_tmps4,"Jul")==0) i=7;
  if (strcmp(s_tmps4,"Aug")==0) i=8;
  if (strcmp(s_tmps4,"Sep")==0) i=9;
  if (strcmp(s_tmps4,"Oct")==0) i=10;
  if (strcmp(s_tmps4,"Nov")==0) i=11;
  if (strcmp(s_tmps4,"Dec")==0) i=12;
  bw_inkey1.int2str(i,s_tmps5,SMG_SIZE);
  p_str[0]=s_tmps5[ 9];
  p_str[1]=s_tmps5[10];
  p_str[2]=0;
  return(0);
}

int bw_dialog::w_get_dd(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  p_str[0]=0;
  if (p_str_size<10) return(0);
  for (i=0;i<3;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  p_str[0]=s_tmps3[8];
  p_str[1]=s_tmps3[9];
  p_str[2]=0;
  return(0);
}

int bw_dialog::w_get_date(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  char s_tmps4[SMG_SIZE];
  char s_tmps5[SMG_SIZE];

  p_str[0]=0;
  if (p_str_size<11) return(0);
  for (i=0;i<10;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  p_str[0]=s_tmps3[20];
  p_str[1]=s_tmps3[21];
  p_str[2]=s_tmps3[22];
  p_str[3]=s_tmps3[23];
  p_str[4]='-';

  s_tmps4[0]=s_tmps3[4];
  s_tmps4[1]=s_tmps3[5];
  s_tmps4[2]=s_tmps3[6];
  s_tmps4[3]=0;
  i=0;
  if (strcmp(s_tmps4,"Jan")==0) i=1;
  if (strcmp(s_tmps4,"Feb")==0) i=2;
  if (strcmp(s_tmps4,"Mar")==0) i=3;
  if (strcmp(s_tmps4,"Apr")==0) i=4;
  if (strcmp(s_tmps4,"May")==0) i=5;
  if (strcmp(s_tmps4,"Jun")==0) i=6;
  if (strcmp(s_tmps4,"Jul")==0) i=7;
  if (strcmp(s_tmps4,"Aug")==0) i=8;
  if (strcmp(s_tmps4,"Sep")==0) i=9;
  if (strcmp(s_tmps4,"Oct")==0) i=10;
  if (strcmp(s_tmps4,"Nov")==0) i=11;
  if (strcmp(s_tmps4,"Dec")==0) i=12;
  bw_inkey1.int2str(i,s_tmps5,SMG_SIZE);
  p_str[5]=s_tmps5[ 9];
  p_str[6]=s_tmps5[10];
  p_str[7]='-';

  p_str[ 8]=s_tmps3[8];
  p_str[ 9]=s_tmps3[9];
  p_str[10]=0;

  return(0);
}

int bw_dialog::w_get_year(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  p_str[0]=0;
  if (p_str_size<10) return(0);
  for (i=0;i<4;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  p_str[0]=s_tmps3[20];
  p_str[1]=s_tmps3[21];
  p_str[2]=s_tmps3[22];
  p_str[3]=s_tmps3[23];
  p_str[4]=0;
  return(0);
}

int bw_dialog::w_get_mon(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  p_str[0]=0;
  if (p_str_size<10) return(0);
  for (i=0;i<3;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  p_str[0]=s_tmps3[4];
  p_str[1]=s_tmps3[5];
  p_str[2]=s_tmps3[6];
  p_str[3]=0;
  return(0);
}

int bw_dialog::w_get_time(char *p_str,int p_str_size)
{
  time_t t;
  int i;
  char s_tmps3[SMG_SIZE];
  p_str[0]=0;
  if (p_str_size<10) return(0);
  for (i=0;i<8;i++) p_str[i]=' ';
  time(&t);
  strcpy(s_tmps3,ctime(&t));
  p_str[0]=s_tmps3[11];
  p_str[1]=s_tmps3[12];
  p_str[2]=s_tmps3[13];
  p_str[3]=s_tmps3[14];
  p_str[4]=s_tmps3[15];
  p_str[5]=s_tmps3[16];
  p_str[6]=s_tmps3[17];
  p_str[7]=s_tmps3[18];
  p_str[8]=0;
  return(0);
}

int bw_dialog::w_get_usr(char *p_str,int p_str_size)
{
  int i;
  p_str[0]=0;
  if (p_str_size<30) return(0);
  //for (i=0;i<30;i++) p_str[i]=' ';
  strcpy(p_str,"Daipozhi");
  return(0);
}





int bw_dialog::get_win_mv_stor(int mlptr)
{
  if ((mlptr<0)||(mlptr>=MEM_VAR_SIZE)) return(0);
  return(win_mv_stor[mlptr]);
}
int bw_dialog::get_win_mv_posi(int mvptr,int p01)
{
  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_mv_posi[mvptr][p01]);
}
int bw_dialog::get_win_mv_type(int mvptr,int p05)
{
  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);
  if ((p05<0)||(p05>5)) return(0);
  return(win_mv_type[mvptr][p05]);
}
/*
int * bw_dialog::get_win_mv_getp(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(&win_mv_getp[p_wptr]);
}
*/
/*
int bw_dialog::get_v_win_mv_getp(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_mv_getp[p_wptr]);
}
int bw_dialog::set_v_win_mv_getp(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_mv_getp[p_wptr]=val;
  return(0);
}
*/
int bw_dialog::set_win_mv_stor(int mlptr,int val)
{
  if ((mlptr<0)||(mlptr>=MEM_VAR_SIZE)) return(0);
  win_mv_stor[mlptr]=val;
  return(0);
}
int bw_dialog::set_win_mv_posi(int mvptr,int p01,int val)
{
  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_mv_posi[mvptr][p01]=val;
  return(0);
}
int bw_dialog::set_win_mv_type(int mvptr,int p05,int val)
{
  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);
  if ((p05<0)||(p05>5)) return(0);
  win_mv_type[mvptr][p05]=val;
  return(0);
}
/*
int bw_dialog::set_win_mv_getp(int p_wptr ,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_mv_getp[p_wptr]=val;
  return(0);
}
*/
int bw_dialog::get_win_mv_name(int mvptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mv_name[mvptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_dialog::set_win_mv_name(int mvptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  win_mv_name[mvptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mv_name[mvptr][j+0]=p_s1[j];
    win_mv_name[mvptr][j+1]=0;
  }

  return(0);
}
int bw_dialog::set_c_win_mv_name(int mvptr,int p0a,int val)
{
  if ((mvptr<0)||(mvptr>=MEM_VAR_NUM)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_mv_name[mvptr][p0a]=val;
  return(0);
}

int bw_dialog::get_win_mv_getv(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mv_getv[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_dialog::set_win_mv_getv(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  win_mv_getv[p_wptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mv_getv[p_wptr][j+0]=p_s1[j];
    win_mv_getv[p_wptr][j+1]=0;
  }

  return(0);
}
int bw_dialog::set_c_win_mv_getv(int p_wptr,int ptr1,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  win_mv_getv[p_wptr][ptr1]=val;
  return(0);
}

int bw_rabox::get_win_rabox(int mptr,int p03)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_RA)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_rabox[mptr][p03]);
}
int bw_rabox::set_win_rabox(int mptr,int p03,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_RA)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_rabox[mptr][p03]=val;
  return(0);
}
int bw_rabox::get_win_rabox_name(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((mptr<0)||(mptr>=BUTTON_NUM_RA)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_rabox_name[mptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_rabox::set_win_rabox_name(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mptr<0)||(mptr>=BUTTON_NUM_RA)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  win_rabox_name[mptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_rabox_name[mptr][j+0]=p_s1[j];
    win_rabox_name[mptr][j+1]=0;
  }

  return(0);
}
int bw_rabox::set_c_win_rabox_name(int mptr,int p0a,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_RA)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_rabox_name[mptr][p0a]=val;
  return(0);
}

int bw_chkbox::get_win_chkbox(int cptr,int p03)
{
  if ((cptr<0)||(cptr>=BUTTON_NUM_CHS)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_chkbox[cptr][p03]);
}
int bw_chkbox::set_win_chkbox(int cptr,int p03,int val)
{
  if ((cptr<0)||(cptr>=BUTTON_NUM_CHS)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_chkbox[cptr][p03]=val;
  return(0);
}
int bw_chkbox::get_win_chkbox_name(int cptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((cptr<0)||(cptr>=BUTTON_NUM_CHS)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_chkbox_name[cptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_chkbox::set_win_chkbox_name(int cptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((cptr<0)||(cptr>=BUTTON_NUM_CHS)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  win_chkbox_name[cptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_chkbox_name[cptr][j+0]=p_s1[j];
    win_chkbox_name[cptr][j+1]=0;
  }

  return(0);
}
int bw_chkbox::set_c_win_chkbox_name(int cptr,int p0a,int val)
{
  if ((cptr<0)||(cptr>=BUTTON_NUM_CHS)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_chkbox_name[cptr][p0a]=val;
  return(0);
}

int bw_buttonvar::get_t5_btn_wind(int mptr)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  return(t5_btn_wind[mptr]);
}
int bw_buttonvar::get_t5_btn_mcntr(int mptr)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  return(t5_btn_mcntr[mptr]);
}
int bw_buttonvar::set_t5_btn_wind(int mptr,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  t5_btn_wind[mptr]=val;
  return(0);
}
int bw_buttonvar::set_t5_btn_mcntr(int mptr,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  t5_btn_mcntr[mptr]=val;
  return(0);
}
int bw_buttonvar::get_t5_btn_name(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_btn_name[mptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_t5_btn_name(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  t5_btn_name[mptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_btn_name[mptr][j+0]=p_s1[j];
    t5_btn_name[mptr][j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_c_t5_btn_name(int mptr,int p0a,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  t5_btn_name[mptr][p0a]=val;
  return(0);
}

int bw_buttonvar::get_t5_btn_button(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_btn_button[mptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_t5_btn_button(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  t5_btn_button[mptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_btn_button[mptr][j+0]=p_s1[j];
    t5_btn_button[mptr][j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_c_t5_btn_button(int mptr,int ptr1,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  if ((ptr1<0)||(ptr1>80)) return(0);
  t5_btn_button[mptr][ptr1]=val;
  return(0);
}

int bw_buttonvar::get_t5_btn_comm(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_btn_comm[mptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_t5_btn_comm(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  t5_btn_comm[mptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_btn_comm[mptr][j+0]=p_s1[j];
    t5_btn_comm[mptr][j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_c_t5_btn_comm(int mptr,int ptr1,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  if ((ptr1<0)||(ptr1>80)) return(0);
  t5_btn_comm[mptr][ptr1]=val;
  return(0);
}

int bw_buttonvar::get_t5_btn_focus(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t5_btn_focus[mptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_t5_btn_focus(int mptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);

  if (p_s1_size>81) i=81;
  else i=p_s1_size;

  t5_btn_focus[mptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t5_btn_focus[mptr][j+0]=p_s1[j];
    t5_btn_focus[mptr][j+1]=0;
  }

  return(0);
}
int bw_buttonvar::set_c_t5_btn_focus(int mptr,int ptr1,int val)
{
  if ((mptr<0)||(mptr>=BUTTON_NUM_BTN)) return(0);
  if ((ptr1<0)||(ptr1>80)) return(0);
  t5_btn_focus[mptr][ptr1]=val;
  return(0);
}

