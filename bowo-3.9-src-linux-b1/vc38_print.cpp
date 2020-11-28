/*
#define  STRICT
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

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "vc_bowo.h"

extern class bw_print        bw_print1;
extern class bw_link         bw_link1;
extern class bw_main         bw_main1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_dialog       bw_dialog1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;




//----------------------------------------------
//
// define for gc_win32emulator.cpp
//
//----------------------------------------------
#include <locale.h>
#include <iconv.h>

extern iconv_t cd ;

#define CLASS_NUM        1000
#define PIPE_NUM         5000
#define STRING_SIZE       3000
#define MAX_WIN_NUM_4LNX   32
#define LIN_NUM_4LNX       80
#define COL_NUM_4LNX       300
#define MAX_WIN_CI_4LNX  1000

class lnx
{
  private:
  
   char paint_buff[MAX_WIN_NUM_4LNX][LIN_NUM_4LNX][COL_NUM_4LNX];
   char paint_buff2[LIN_NUM_4LNX][COL_NUM_4LNX];

   char lnx_win_class_name[CLASS_NUM][STRING_SIZE];
   char lnx_win_class_menu[CLASS_NUM][STRING_SIZE];
   int  lnx_win_class_proc[CLASS_NUM];

   char  lnx_win_handle_name[MAX_WIN_NUM_4LNX][STRING_SIZE];
   char  lnx_win_handle_menu[MAX_WIN_NUM_4LNX][STRING_SIZE];
   char lnx_win_handle_topic[MAX_WIN_NUM_4LNX][STRING_SIZE];
   int   lnx_win_handle_proc[MAX_WIN_NUM_4LNX];
   int  lnx_win_handle_inuse[MAX_WIN_NUM_4LNX];

   int  pipe_buff[PIPE_NUM][4];

   int   lnx_win_ci_buff[MAX_WIN_CI_4LNX][11];
   char  lnx_win_ci_name[MAX_WIN_CI_4LNX][STRING_SIZE];
   char lnx_win_ci_topic[MAX_WIN_CI_4LNX][STRING_SIZE];

   int  lnx_cursor[MAX_WIN_NUM_4LNX][2];

  public:
  
   int  lnx_focus_pp;
   int  lnx_exit;





   int  lnx_win_class_pp;
   
   int  pipe_pp1;
   int  pipe_pp2;
   
   int  lnx_xchar;
   int  lnx_ychar;

   char lnx_msg[STRING_SIZE];

   int  lnx_lang;

   int  lnx_xwin;
   int  lnx_ywin;

  public:
   
   int show_cursor(void);

   int ini_win_class(void);
//   int reg_win_class(char * ,int ,char *);
   int find_win_class(char *,char *);

   int ini_win_handle(void);
   int add_win_handle(char *,char *);

   int ini_msg_pipe(void);
   int add_msg_to_pipe(int p1,int p2,int p3,int p4);
   int exec_msg(void);
   int exec_win_proc(int j,int n1,int n2,int n3,int n4);
   int exec_win_ci_proc(int n1,int n2,int n3,int n4);

   int ini_win_ci(void);
   
   int add_win_ci(char *h1,char *h2,int h3,int h4,int h5,int h6,int h7,int h8,int h9,int h10,int h11,int h12);
   
   int paint_focus_win(void);

   int paint_focus_win_ci(void);

   int set_win_focus(int );
   
   int ini_charsize(void);
   
   int char2int(char *string,int p1,int p2);

   int del_win_ci(int pp);

   int last_win_pp(void);

   int dsp_menu(char *);

   
   int dsp_menu_rm_1(char *,int);
   int dsp_menu_rm_2(char *,int);
   int dsp_menu_add_1(char *,int);
   int dsp_menu_cpy(char *,char *,int);
   int get_setup(void);
   int strtrim(char *str);
   int strpcut(char *s1,int p1,int p2,char *s2);
   
   int strfind(const char *,const char *);
   int upper(char );

   int change_win_ci(void);
   int find_win_ci_by_cur(int l,int c);
   int find_win_ci_by_string1(char *s1);
   int find_win_ci_by_string2(char *s1);
   int find_win_ci_by_string3(char *s1);
   int clear_radio_ci(int pp,char *str);

  public:

   int gets_lnx_win_class_menu(int p1,char *v1);
   int sets_lnx_win_class_menu(int p1,char *v1);
   int gets_lnx_win_class_name(int p1,char *v1);
   int sets_lnx_win_class_name(int p1,char *v1);
   int set_lnx_win_class_proc(int p1,int v1);
   int get_lnx_win_class_proc(int p1);

   int gets_lnx_win_handle_name(int p1,char *v1);
   int gets_lnx_win_handle_menu(int p1,char *v1);
   int gets_lnx_win_handle_topic(int p1,char *v1);



   int sets_lnx_win_handle_name(int p1,char *v1);
   int sets_lnx_win_handle_menu(int p1,char *v1);
   int sets_lnx_win_handle_topic(int p1,char *v1);

   int get_lnx_win_handle_proc(int p1);
   int get_lnx_win_handle_inuse(int p1);
   
   int set_lnx_win_handle_proc(int p1,int v1);
   int set_lnx_win_handle_inuse(int p1,int v1);

   int get_paint_buff(int p1,int p2,int p3);
   int set_paint_buff(int p1,int p2,int p3,int v1);

   int set_pipe_buff(int p1,int p2,int v1);
   int get_pipe_buff(int p1,int p2);

   int gets_lnx_win_ci_name(int p1,char *v1);
   int gets_lnx_win_ci_topic(int p1,char *v1);

   int sets_lnx_win_ci_name(int p1,char *v1);
   int sets_lnx_win_ci_topic(int p1,char *v1);

   int set_lnx_win_ci_buff(int p1,int p2,int v1);
   int get_lnx_win_ci_buff(int p1,int p2);
   
   int set_lnx_cursor(int p1,int p2,int v1);
   int get_lnx_cursor(int p1,int p2);
   
//   int pre_paint_focus_win(void);

   int str_gb18030_to_utf8_ini(void);
   int str_gb18030_to_utf8(char *inbuffer,char *outbuffer,int outbufferlen);
   int str_gb18030_to_utf8_close(void);

   int str_utf8_to_gb18030_ini(void);
   int str_utf8_to_gb18030(char *inbuffer,char *outbuffer,int outbufferlen);
   int str_utf8_to_gb18030_close(void);

   char line_trans_buff[300][20];
   int  line_trans_pp;

   int line_trans_init(void);
   int line_trans(char *p_str1,char *p_str2);
};

extern class  lnx   lnx1;
// --------------------- end define --------------------




int bw_print::w_open_print_file(char *p_s1,int p_s1_size)
{
  char str2[FN_SIZE];
  int  i,j;

  if (p_s1_size<FN_SIZE) j=p_s1_size;
  else  j=FN_SIZE;
  if (j<1) j=1;
  p_s1[j-1]=0;

  strcpy(str2,p_s1);
  i=bw_inkey1.strlocc(str2,FN_SIZE,'.');
  str2[i]=0;
  strcat(str2,".txt");
  txt_out_fp1=fopen(str2,"w");
  if (txt_out_fp1==NULL) return(1);
  else return(0);
}
int bw_print::w_close_print_file(void)
{
  fclose(txt_out_fp1);
  return(0);
}
int bw_print::w_read_page(char *p_fn2,int p_fn2_size,int page)
{
  FILE *s_fp1;
  int  p1,p2,p8,same,ends;
  int  state1,state2,state3;
  int  state4,state5,state6;
  char s_tmps2[PAGE_COLU];
  char str3[FN_SIZE];
  int  i,j,n;
  int  lcnt,cmd;

  strcpy(texts1,"usetable=  ");
  strcpy(texts2,"enddefine  ");
  strcpy(texts3,"screenseg  ");
  strcpy(texts4,"endscreen  ");
  strcpy(texts5,"readvatype ");
  strcpy(texts6,"findfile=  ");
  strcpy(texts7,"findbase=  ");
  strcpy(texts8,"switchbmp  ");

  if (p_fn2_size<FN_SIZE) j=p_fn2_size;
  else  j=FN_SIZE;
  if (j<1) j=1;
  p_fn2[j-1]=0;

  strcpy(str3,p_fn2);
  bw_inkey1.strtrim(str3,FN_SIZE);
  i=bw_inkey1.strlocc(str3,FN_SIZE,'.');
  if (i<0) i=strlen(str3);
  str3[i]=0;
  strcat(str3,".sc0");

  s_fp1=fopen(str3,"r");    /* fetch page format from page file */
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1(str3);
    return(1);
  }

  p8=page;

  while (p8>1)  // if more than one page
  {
    fgets(s_tmps2,PAGE_COLU,s_fp1);
    if (feof(s_fp1)) break;
    if (strncmp(s_tmps2,"&screenseg",10)==0) p8--;
    if (strncmp(s_tmps2,"&pageseg",8)==0) p8--;
  }

  if (feof(s_fp1))
  {  
    fclose(s_fp1);
    return(1);
  }

  for (i=0;i<PAGE_LINE;i++)
  {
    for (j=0;j<PAGE_COLU;j++)
    {
      set_t6_pagefile(i,j,' ');
    }
  }

  lcnt=0;

  for (i=0;i<PAGE_LINE+10;i++)
  {
    cmd=0;
    for (n=0;n<PAGE_COLU;n++) s_tmps2[n]=' ';

    fgets(s_tmps2,PAGE_COLU,s_fp1);

    if (feof(s_fp1))
    {
      ends=1;
      break;
    }

    p1=0;
    p2=0;
    ends=0;
    state1=0;
    state2=0;
    state3=0;
    state4=0;
    state5=0;
    state6=0;
    j=0;

    while (p1<PAGE_COLU)  /* scan this line */
    {
      for (j=j;j<PAGE_COLU;j++)
      {
        if (s_tmps2[j]=='&') break; /* locate for '&' */
      }

      j++;
      p1=j;
      if (p1>=PAGE_COLU) break;

      // find findbase name
      same=1;
      for (p2=p1;p2<=p1+11-1;p2++)  
      {
	if (texts6[p2-p1]==' ') break;
	if (s_tmps2[p2]!=texts6[p2-p1])
        {
          same=0;
          break;
        }
      }
      if (same==1)
      {
        state6=1;
      }
      
      same=1;
      for (p2=p1;p2<=p1+11-1;p2++)  /* recnigze keywords */
      {
	if (texts1[p2-p1]==' ') break;
	if (s_tmps2[p2]!=texts1[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1)
      {
	state1=1;  /* there is keyword "usetable" */
	same=1;
      }

      same=1;
      for (p2=p1;p2<=p1+11-1;p2++)  /* recnigze keywords */
      {
	if (texts5[p2-p1]==' ') break;
	if (s_tmps2[p2]!=texts5[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1)
      {
	state5=1;
      }

      same=1;
      for (p2=p1;p2<=p1+11-1;p2++)
      {
	if (texts2[p2-p1]==' ') break;
	if (s_tmps2[p2]!=texts2[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state2=1; /* enddefine */

      same=1;
      for (p2=p1;p2<=p1+11-1;p2++)
      {
	if (texts3[p2-p1]==' ') break;
	if (s_tmps2[p2]!=texts3[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state3=1;  /* screenseg */

      same=1;
      for (p2=p1;p2<=p1+11-1;p2++)
      {
	if (texts4[p2-p1]==' ') break;
	if (s_tmps2[p2]!=texts4[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state4=1;  /* endscreen */

      if (state1==1) cmd=1; /* screentype */
      if (state5==1) cmd=1; /* screentype */
      if (state6==1) cmd=1; /* find file  */
      if (state2==1) cmd=1; /* enddefine  */
      if (state3==1)
      {
	ends=1;
	break; /* screenseg */
      }
      if (state4==1) /* endscreen */
      {
	ends=1;
	break;
      }
    }
    if (ends==1) break;
    if (cmd==0) lcnt++;
    else
    {
      cmd=0;
      continue;
    }

    for (j=0;j<PAGE_COLU;j++)
    {
      if ((s_tmps2[j]<' ')&&(s_tmps2[j]>=0)) s_tmps2[j]=' ';
      set_t6_pagefile(lcnt,j,s_tmps2[j]);
    }

    if (feof(s_fp1))
    {
      ends=1;
      break;
    }
  }

  fclose(s_fp1);
  bw_main1.win_page_line_num=lcnt+1;

  return(0);
}

int bw_print::tst_p1()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=1;i<=24;i++)
  {
    get_s_t6_pagefile(i,str,SMG_SIZE);

    TextOut(hdc,0,i*20,str,70);
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_print::w_page_field1()
{
  int  p1,p2,p3,p4,p5,p6;
  int  state1;
  int  i,j;
  int  ptr1;

  ptr1=0;

  for (i=0;i<FLD_IN_PAGE;i++)
  {
    set_t6_linecol(i,0,0);
    set_t6_linecol(i,1,0);
    set_t6_linecol(i,2,0);
  }

  for (i=0;i<PAGE_LINE;i++)
  {
    p1=PAGE_COLU;
    p2=0;

    for (j=0;j<PAGE_COLU;j++)   /* scan for line widght */
    {
      if ((get_t6_pagefile(i,j)>' ')||(get_t6_pagefile(i,j)<0))
      {
	p1=j;
	break;
      }
    }

    for (j=PAGE_COLU-1;j>=0;j--)
    {
      if ((get_t6_pagefile(i,j)>' ')||(get_t6_pagefile(i,j)<0))
      {
	p2=j;
	break;
      }
    }

    if (p2<p1) continue; /* if empty line don't display */

    state1=0;
    p3=0;
    p4=0;
    p5=0;
    p6=0;

    for (j=p1;j<=p2;j++)  /* field name to var and table line to screen */
    {
      if (get_t6_pagefile(i,j)=='&')
      {
	if (p5==1) set_t6_fldlen(ptr1,j-1-p6);
	ptr1++;
	if (get_t6_pagefile(i,j+1)=='#')
	{
	  set_t6_linecol(ptr1,0,i);
	  set_t6_linecol(ptr1,1,j+1);
	  set_t6_linecol(ptr1,2,ptr1);
	}
	else
	{
	  set_t6_linecol(ptr1,0,i);
	  set_t6_linecol(ptr1,1,j);
	  set_t6_linecol(ptr1,2,ptr1);
	}
	p3++;
	p4=0;
	state1=1;
	p5=1;
	p6=j;
      }
      else
      {
	if (get_t6_pagefile(i,j)<=' ')
	{
	  state1=0;
	  if (get_t6_pagefile(i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      set_t6_fldlen(ptr1,j-p6);
	      p5=0;
	    }
	  }
	  else
	  {
	    state1=0;
	  }
	}
	else
	{
	  if (state1==1)
	  {
	    if ((p4==0)&&(get_t6_pagefile(i,j-1)=='%'))
	    {
	      set_t6c_fldname(ptr1,p4,'%');
	      p4++;
	    }
	    set_t6c_fldname(ptr1,p4+0,get_t6_pagefile(i,j));
	    set_t6c_fldname(ptr1,p4+1,0);
	    set_t6_fldtype(ptr1,'c');
	    p4++;
	  }
	  else
	  {
	    if (p5==1)
	    {
	      set_t6_fldlen(ptr1,j-p6);
	      p5=0;
	    }
	  }
	}
      }
    }
  }

  t6_ptr1=ptr1;

  return(0);
}

int bw_print::tst_p2()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<=25;i++)
  {
    get_t6_fldname(i,sfn,SMG_SIZE);

    sprintf(str,"name=%s,type=%c,len=%d,"
       ,sfn
       ,get_t6_fldtype(i)
       ,get_t6_fldlen(i));

    TextOut(hdc,0,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_print::w_page_field2(int p_wptr)
{
  int  i,k,l,m;
  int  ptr1;
  int  exist;
  int  basep;
  char c1[SMG_SIZE];
  char c2[SMG_SIZE];
  char s_fldtable[SMG_SIZE];
  char s_fldname[SMG_SIZE];
  long s_fldrecno;
  char s_tmps2[SMG_SIZE];
  char s_tmps3[SMG_SIZE];
  int  s_tmpn1;
  char sfn[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);
  else basep=i;

  for (i=0;i<FLD_IN_PAGE;i++)
  {
    set_t6_fldbase(i,0);
    set_t6_fldedit(i,0);
    set_t6_fldseri(i,0);
  }
		      
  for (i=0;i<FLD_IN_SCRN;i++) set_t7_fldseri(i,0);

  ptr1=basep; /* default base point  */

  for (k=0;k<=t6_ptr1;k++)
  {
    i=get_t6_linecol(k,0);

    s_fldtable[0]=0;
    s_fldrecno=0;
    s_fldname[0]=0;

    get_t6_fldname(k,sfn,SMG_SIZE);

    if ((bw_win1.w_field_type(sfn)==6)
      ||(bw_win1.w_field_type(sfn)==7)
      ||(bw_win1.w_field_type(sfn)==8))
    {
      c1[0]=get_t6c_fldname(k,0);
      c1[1]=0;

      get_t6_fldname(k,s_tmps2,SMG_SIZE);

      if (s_tmps2[0]=='%')
      {
	s_tmpn1=1; /* read field */
	bw_inkey1.cut_string(s_tmps2,1,strlen(s_tmps2)-1,SMG_SIZE,s_tmps3,SMG_SIZE);
      }
      else
      {
	s_tmpn1=0; /* edit field */
	bw_inkey1.cut_string(s_tmps2,1,strlen(s_tmps2)-1,SMG_SIZE,s_tmps3,SMG_SIZE);
      }

      bw_win1.w_fetch_fld_style(s_tmps3,SMG_SIZE
                   ,s_fldtable,SMG_SIZE
		   ,&s_fldrecno
		   ,s_fldname,SMG_SIZE
		   ,p_wptr);

      if ((bw_inkey1.strempty(s_fldtable)==0)
	&&(bw_inkey1.strempty(s_fldname)==0))
      {
	set_t6_fldname(k,s_tmps2,SMG_SIZE);
      }
      else
      {
	strcpy(c2,c1);
        strcat(c2,s_fldname);
	set_t6_fldname(k,c2,SMG_SIZE);
      }

      ptr1=bw_win1.w_fld_set_base(s_fldtable,SMG_SIZE,ptr1,p_wptr);
      set_t6_fldbase(k,ptr1);

      if (bw_inkey1.strempty(s_fldname)==0)
      {
	set_t6_fldseri(k,1);
	set_t6_fldedit(k,1);
	continue;
      }

      l=0;
      for (m=k-1;m>0;m--)
      {
        get_t7_fldname(m,sfn,SMG_SIZE);

	if ((strcmp(s_fldname,sfn)==0)
	  &&(ptr1==get_t6_fldbase(m))
	  &&(s_fldrecno==0))
	{
	  l=1;
          set_t7_fldseri(m,get_t7_fldseri(m)+1);
	  set_t6_fldseri(k,get_t7_fldseri(m));
	}
      }

      if (l==1) set_c_t7_fldname(k,0,0);
      else
      {
	set_t7_fldname(k,s_fldname,10);
	set_t7_fldseri(k,get_t7_fldseri(k)+1);
	set_t6_fldseri(k,get_t7_fldseri(k));
      }

      if (s_tmpn1==1)
	set_t6_fldedit(k,1);
      else
	set_t6_fldedit(k,w_fld_set_edit(s_fldname,SMG_SIZE));

    }
  }

  return(0);
}

int bw_print::w_fld_set_edit(char *p_fldname,int p_fldname_size)
{
  if (bw_inkey1.strempty(p_fldname)==0) return(0);
  else return(1);
}

int bw_print::tst_p3()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<25;i++)
  {
    get_t6_fldname(i,sfn,SMG_SIZE);

    sprintf(str,"base=%d,seri=%d,edit=%d,name=%s,"
	  ,get_t6_fldbase(i)
	  ,get_t6_fldseri(i)
	  ,get_t6_fldedit(i)
	  ,sfn);

    TextOut(hdc,0,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}
/*
int bw_print::w_open_memo_print(char *p_s1,int p_s1_size)
{
  char s2[FN_SIZE];
//  char s3[FN_SIZE];
  //char s_fn4[FN_SIZE];
  int  i,j;

  strcpy(s2,p_s1);
  bw_inkey1.strtrim(s2,FN_SIZE);
  i=bw_inkey1.strlocc(s2,FN_SIZE,'.');
  if (i<0) i=strlen(s2);
  s2[i]=0;
  strcat(s2,".mem");

  j=bw_inkey1.upper(s2[0])-'A';
  txt_out_fp2[j]=fopen(s2,"r");
  if (txt_out_fp2[j]==NULL) return(1);
  else return(0);
}
int bw_print::w_fetch_memo_size(int l,int c)
{
  int i,j;
//  int exist;

  j=0;
  for (i=c;i<PAGE_COLU;i++)
  {
    if ((get_t6_pagefile(l,i)>' ')||(get_t6_pagefile(l,i)<0)) break;
    else j=1;
  }

  if (j==1)
  {
    win_memo_left=c;
    win_memo_leng=i-c;
    return(0);
  }
  else return(1);
}
int bw_print::w_read_memo(char *p_s1,int p_s1_size,int m5)
{
  int i,j;
  char tc1[SMG_SIZE];

  if (feof(txt_out_fp2[m5])) return(1);
  else
  {
    fgets(tc1,SMG_SIZE,txt_out_fp2[m5]);

    if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
    else i=p_s1_size;
    for (j=0;j<i-1;j++)
    {
      p_s1[j]=tc1[j];
    }
    if (i-1<0) p_s1[0]=0;
    else  p_s1[i-1]=0;

    return(0);
  }
}
int bw_print::w_put_memo_char(int l,char *p_s1,int p_s1_size)
{
  int  i,j;
  //char s_fn4[SMG_SIZE];

  j=strlen(p_s1);
  for (i=win_memo_left;i<=win_memo_left+win_memo_leng-1;i++)
  {
    if (i-win_memo_left>=j) set_t6_tmps2(l,i,' ');
    else set_t6_tmps2(l,i,p_s1[i-win_memo_left]);
  }
  return(0);
}
int bw_print::w_close_memo_print(int m5)
{
  fclose(txt_out_fp2[m5]);
  return(0);
}
*/
/*
int bw_print::w_save_print()
{
  t6_page_num=0;

  win_savep_hnd=CreateWindow("bowo_savep",
      		"Save Print Data",
		WS_CAPTION|WS_VISIBLE|WS_MINIMIZEBOX|
		WS_SYSMENU|WS_CLIPSIBLINGS|WS_THICKFRAME,
		50,50,300,100,
		bw_main1.win_hwnd1,
		0,
		bw_main1.win_ins,
		NULL);

  return(0);
}
*/
/*
long  PASCAL w_savep_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
//  HFONT          holdfont,hfont;
  HDC            hdc;
  TEXTMETRIC     tm;
//  RECT           rt;
//  HWND           hbutton;

  int  i,j;
//  char c1,c2;
//  char p_fn1[FN_SIZE];
//  char p_var1[SMG_SIZE];
  int  exist;
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

  bw_main1.win_wp=wp;
  bw_main1.win_msg=msg;
  bw_main1.win_lp=lp;

  switch(msg)
  {
    case WM_CREATE:

      hdc=GetDC(hwnd);
      GetTextMetrics(hdc,&tm);
      bw_print1.win_print_xchar=tm.tmAveCharWidth;
      bw_print1.win_print_ychar=tm.tmHeight+tm.tmExternalLeading;
      ReleaseDC(hwnd,hdc);

      if (bw_main1.win_lang==1)
      {
        CreateWindow("button","Cancel"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,50
		      ,50
		      ,50
                      ,50
		      ,hwnd
		      ,(HMENU)301
		      ,bw_main1.win_ins
		      ,NULL);
      }
      else
      {
	CreateWindow("button","中断"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,50
		      ,50
		      ,50
                      ,50
		      ,hwnd
		      ,(HMENU)301
		      ,bw_main1.win_ins
		      ,NULL);
      }

      break;

    case WM_PAINT:

     bw_print1.w_print_echo1(hwnd);

     break;

    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:

      bw_main1.win_wp=wp;
      bw_main1.win_msg=msg;

      i=bw_inkey1.inkey();

      if (i==1)
      {
	SendMessage(hwnd,WM_COMMAND,1002,(LPARAM)str);
        return(0);
      }

      break;

    case WM_COMMAND:
    {
      if (wp==1050)
      {
        bw_main1.win_key=ESC_KEY;
	wp=1002;
      }
      if (wp==1002)
      {
        DestroyWindow(hwnd);
        return(0);
      }
      if (wp==1005)
      {
	bw_print1.w_print_echo1(hwnd);
      }
      if (wp==1006)
      {
        bw_print1.t6_page_num++;

        bw_print1.w_print_echo1(hwnd);

        for (i=1;i<=bw_main1.win_page_size;i++)
        {
	  for (j=0;j<PAGE_COLU;j++)
          {
	    if ((bw_print1.get_t6_tmps2(i,j)<' ')&&(bw_print1.get_t6_tmps2(i,j)>=0)) bw_print1.set_t6_tmps2(i,j,' ');
	  }

	  exist=0;

          for (j=PAGE_COLU-1;j>=0;j--)
          {
	    if ((bw_print1.get_t6_tmps2(i,j)>' ')||(bw_print1.get_t6_tmps2(i,j)<0))
	    {
	      bw_print1.set_t6_tmps2(i,j+1,0);
	      exist=1;
	      break;
	    }
          }

	  if (exist==0) bw_print1.set_t6_tmps2(i,0,0);

          bw_print1.get_s_t6_tmps2(i,sfn,SMG_SIZE);
          fputs(sfn,bw_print1.txt_out_fp1);
          fputs("\n",bw_print1.txt_out_fp1);
        }
      }
      if (wp==1007)
      {
        DestroyWindow(hwnd);
	return(0);
      }
      if (wp==1901)
      {
        DestroyWindow(hwnd);
	return(0);
      }
    }
  }
  return DefWindowProc(hwnd,msg,wp,lp);
}
*/
/*
int bw_print::w_print_echo1(HWND hwnd)
{
  HDC  hdc;
  char str[SMG_SIZE];

  if (bw_main1.win_lang==1)
  {
    sprintf(str,"%s,%d,","Pages been printed:",t6_page_num);
    hdc=GetDC(hwnd);
    TextOut(hdc,20,20,str,strlen(str));
    ReleaseDC(hwnd,hdc);
  }
  else
  {
    sprintf(str,"%s,%d,","已打印的页数:",t6_page_num);
    hdc=GetDC(hwnd);
    TextOut(hdc,20,20,str,strlen(str));
    ReleaseDC(hwnd,hdc);
  }

  return(0);
}
*/
/*
int bw_print::w_save_memo()
{
  int  i,j;
  int  exist;
  char sfn[SMG_SIZE];

  for (i=1;i<=bw_main1.win_page_size;i++)
  {
    for (j=0;j<PAGE_COLU;j++)
      if ((get_t6_tmps2(i,j)<' ')&&(get_t6_tmps2(i,j)>=0)) set_t6_tmps2(i,j,' ');

    exist=0;

    for (j=PAGE_COLU-1;j>=0;j--)
    {
      if ((get_t6_tmps2(i,j)>' ')||(get_t6_tmps2(i,j)<0))
      {
	set_t6_tmps2(i,j+1,0);
	exist=1;
	break;
      }
    }

    if (exist==0) set_t6_tmps2(i,0,0);

    get_s_t6_tmps2(i,sfn,SMG_SIZE);
    fputs(sfn,txt_out_fp1);
    fputs("\n",txt_out_fp1);
  }
  return(0);
}
*/
/*
int bw_print::w_out_print(char *p_s1,int p_s1_size)
{
  int  i,j;
//  int  ptr1;
//  char c1,c2;
//  char s2[SMG_SIZE];
//  char p_fn1[SMG_SIZE];
  //char s_fn4[FN_SIZE];
//  char p_var1[SMG_SIZE];
//  char s_tmpc1[PAGE_COLU];
//  int  exist;
//  int  s_state;

  set_win_print_fname(p_s1,p_s1_size);

  t6_page_num=0;

  win_outp_hnd=CreateWindow("bowo_outp",
		"Out Print Data",
		WS_CAPTION|WS_VISIBLE|WS_MINIMIZEBOX|
		WS_SYSMENU|WS_CLIPSIBLINGS|WS_THICKFRAME,
		150,150,400,150,
		bw_main1.win_hwnd1,
		0,
		bw_main1.win_ins,
		NULL);

  return(0);
}
*/
/*
long  PASCAL w_outp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
//  HFONT      holdfont,hfont;
  HDC        hdc;
  TEXTMETRIC tm;
//  RECT       rt;

  int i;
//  char c1,c2;
//  char p_fn1[SMG_SIZE];
//  char p_var1[SMG_SIZE];
//  int  exist;
  char str[SMG_SIZE];

  bw_main1.win_wp=wp;
  bw_main1.win_msg=msg;
  bw_main1.win_lp=lp;

  switch(msg)
  {
    case WM_CREATE:

      hdc=GetDC(hwnd);
      GetTextMetrics(hdc,&tm);
      bw_print1.win_print_xchar=tm.tmAveCharWidth;
      bw_print1.win_print_ychar=tm.tmHeight+tm.tmExternalLeading;
      ReleaseDC(hwnd,hdc);

      bw_print1.win_page_num=0;

      if (bw_main1.win_lang==1)
      {
        CreateWindow("button","Next Page"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,25
		      ,50
		      ,100
                      ,25
		      ,hwnd
		      ,(HMENU)302
		      ,bw_main1.win_ins
		      ,NULL);

        CreateWindow("button","Prev Page"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,150
		      ,50
		      ,100
                      ,25
		      ,hwnd
		      ,(HMENU)303
		      ,bw_main1.win_ins
		      ,NULL);

        CreateWindow("button","Cancel"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,275
		      ,50
		      ,100
                      ,25
		      ,hwnd
		      ,(HMENU)304
		      ,bw_main1.win_ins
		      ,NULL);
      }
      else
      {
	CreateWindow("button","打印下页"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,25
		      ,50
		      ,100
                      ,25
		      ,hwnd
		      ,(HMENU)302
		      ,bw_main1.win_ins
		      ,NULL);

        CreateWindow("button","打印上页"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,150
		      ,50
		      ,100
                      ,25
		      ,hwnd
		      ,(HMENU)303
		      ,bw_main1.win_ins
		      ,NULL);

        CreateWindow("button","中断"
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,275
		      ,50
		      ,100
                      ,25
		      ,hwnd
		      ,(HMENU)304
		      ,bw_main1.win_ins
		      ,NULL);
      }

      break;

    case WM_PAINT:

      bw_print1.w_print_echo2(hwnd);

      break;

    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:

      bw_main1.win_wp=wp;
      bw_main1.win_msg=msg;

      i=bw_inkey1.inkey();

      if (i==1)
      {
	SendMessage(hwnd,WM_COMMAND,1002,(LPARAM)str);
        return(0);
      }

      break;

    case WM_COMMAND:
    {
      if (wp==1051)
      {
	bw_main1.win_key=ESC_KEY;
	wp=1002;
      }
      if (wp==1052)
      {
	bw_print1.win_page_num++;
	bw_print1.w_out_win_print();
      }
      if (wp==1053)
      {
	bw_print1.win_page_num--;
        bw_print1.w_out_win_print();
      }

      if (wp==1002)
      {
	if ((bw_main1.win_key==274)&&(bw_print1.p1>0)) bw_print1.p1--;
	if ((bw_main1.win_key==275)&&(bw_print1.p1<3)) bw_print1.p1++;
	if ((bw_main1.win_key==276)&&(bw_print1.p1>0)) bw_print1.p1--;
	if ((bw_main1.win_key==277)&&(bw_print1.p1<3)) bw_print1.p1++;

	if ((bw_main1.win_key==10)||(bw_main1.win_key==32)||(bw_main1.win_key==401))
	{
          if (bw_print1.p1==3)
          {
            DestroyWindow(hwnd);
	    return(0);
          }
          if (bw_print1.p1==1)
          {
            bw_print1.win_page_num++;
            bw_print1.w_out_win_print();
          }
          if (bw_print1.p2==2)
          {
            bw_print1.win_page_num--;
            bw_print1.w_out_win_print();
          }
	}

	if (bw_main1.win_key==ESC_KEY)
        {
          DestroyWindow(hwnd);
	  return(0);
        }
      }

      if ((wp==1751)||(wp==304))
      {
        DestroyWindow(hwnd);
        return(0);
      }

      if ((wp==1752)||(wp==302))
      {
        bw_print1.win_page_num++;
        bw_print1.w_out_win_print();
      }

      if ((wp==1753)||(wp==303))
      {
        bw_print1.win_page_num--;
        bw_print1.w_out_win_print();
      }

      bw_print1.w_print_echo2(hwnd);

    }
  }
  return DefWindowProc(hwnd,msg,wp,lp);
}
*/
/*
int bw_print::w_print_echo2(HWND hwnd)
{
  HDC  hdc;
  char str[SMG_SIZE];

  if (bw_main1.win_lang==1)
  {
    sprintf(str,"%s,%d,","Pages been printed:",t6_page_num);
    hdc=GetDC(hwnd);
    TextOut(hdc,20,20,str,strlen(str));
    ReleaseDC(win_savep_hnd,hdc);
  }
  else
  {
    sprintf(str,"%s,%d,","正在打印的页数:",t6_page_num);
    hdc=GetDC(hwnd);
    TextOut(hdc,20,20,str,strlen(str));
    ReleaseDC(hwnd,hdc);
  }

  return(0);
}
*/
/*
int bw_print::w_out_win_print()
{
  int  exist;
  int  i,j;
  int  s_end;
  int  s_started;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char ssd[SMG_SIZE];
  char sdev[SMG_SIZE];
  char sdri[SMG_SIZE];
  char sport[SMG_SIZE];
  FILE       *s_fp2;
  HDC        hdc;
  TEXTMETRIC tm;
  HFONT      holdfont,hfont;

  get_win_print_fname(str2,SMG_SIZE);

  i=bw_inkey1.strlocc(str2,SMG_SIZE,'.');
  str2[i]=0;
  strcat(str2,".txt");

  s_fp2=fopen(str2,"r");
  if (s_fp2==NULL)
  {
    bw_win1.w_atten1(str2);
    return(1);
  }

  s_end=0;
  s_started=0;
*//*
  if (win_page_num>1)
  {
    for (i=1;i<=(win_page_num-1)*bw_main1.win_page_size;i++)
    {
      fgets(str1,SMG_SIZE,s_fp2);
      if (feof(s_fp2))
      {
	fclose(s_fp2);
	return(1);
      }
    }
  }
*//*
  GetProfileString("windows","device",",,,",ssd,SMG_SIZE);

  for (i=0;i<(int)strlen(ssd);i++)
  {
    if (ssd[i]==',') break;
  }
  bw_inkey1.cut_string(ssd,0,i,SMG_SIZE,sdev,SMG_SIZE);
  sdev[i]=0;

  j=i+1;
  for (i=j;i<(int)strlen(ssd);i++)
  {
    if (ssd[i]==',') break;
  }
  bw_inkey1.cut_string(ssd,j,i-j,SMG_SIZE,sdri,SMG_SIZE);
  sdri[i-j]=0;

  j=i+1;
  for (i=j;i<(int)strlen(ssd);i++)
  {
    if (ssd[i]==',') break;
  }
  bw_inkey1.cut_string(ssd,j,strlen(ssd)-j,SMG_SIZE,sport,SMG_SIZE);
  sport[strlen(ssd)-j]=0;

  hdc=CreateDC(sdri,sdev,sport,NULL);
  //hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  //holdfont=(HFONT)SelectObject(hdc,hfont);

  if (hdc==NULL)
  {
    fclose(s_fp2);
    return(1);
  }

  i=StartDoc(hdc,&win_print_inf);
  if (i<=0)
  {
    DeleteDC(hdc);
    fclose(s_fp2);
    return(1);
  }
*//*
  i=StartPage(hdc);
  if (i<=0)
  {
    DeleteDC(hdc);
    fclose(s_fp2);
    return(1);
  }
*//*
  GetTextMetrics(hdc,&tm);
  win_print_xchar=tm.tmAveCharWidth;
  win_print_ychar=tm.tmHeight+tm.tmExternalLeading;

  while(1)
  {
    for (i=1;i<=bw_main1.win_page_size;i++)
    {
      fgets(str1,SMG_SIZE,s_fp2);

      if (feof(s_fp2))
      {
        fclose(s_fp2);
        s_end=1;
        break;
      }

      if (s_started==0)
      {
        s_started=1;

        j=StartPage(hdc);
        if (j<=0)
        {
          DeleteDC(hdc);
          fclose(s_fp2);
          break;
        }
      }

      exist=0;

      for (j=strlen(str1);j>=0;j--)
      {
        if ((str1[j]>' ')||(str1[j]<0))
        {
	  exist=1;
	  break;
        }
      }

      if (exist==1) str1[j+1]=0;
      else str1[0]=0;

      j=win_print_ychar*i;
      TextOut(hdc,1,j,str1,strlen(str1));
*//*
      if (feof(s_fp2))
      {
        s_end=1;
        break;
      }
*//*
    }

    if (s_started!=0)
    {
      s_started=0;

      i=EndPage(hdc);
      if (i<0)
      {
        DeleteDC(hdc);
        fclose(s_fp2);
        s_end=1;
        break;;
      }
    }

    if (s_end!=0) break;
  }

  i=EndDoc(hdc);
  if (i<0)
  {
    DeleteDC(hdc);
    fclose(s_fp2);
    return(1);
  }

  DeleteDC(hdc);

  fclose(s_fp2);

  return(s_end);
}
*/

int bw_print::w_out_linux_print()
{
  int  i,j;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];
  char str4[SMG_SIZE*2];
  char str5[SMG_SIZE*2];
  FILE       *s_fp1;
  FILE       *s_fp2;

  //char *args[]={"lp","lp","to_my_printer.utf8.txt",NULL}; 
  int   pid;

  get_win_print_fname(str1,SMG_SIZE);

  i=bw_inkey1.strlocc(str1,SMG_SIZE,'.');
  str1[i]=0;
  strcat(str1,".txt");
  strcpy(str2,"to_my_printer.utf8.txt");

  s_fp1=fopen(str1,"r");
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1(str1);
    return(1);
  }

  s_fp2=fopen(str2,"w");
  if (s_fp2==NULL)
  {
    bw_win1.w_atten1(str2);
    return(1);
  }

  while(!feof(s_fp1))
  {
    for (i=0;i<SMG_SIZE;i++) str3[i]=0;
    fgets(str3,SMG_SIZE,s_fp1);
    for (i=strlen(str3)-1;i>=0;i--)
    {
      if ((str3[i]>0)&&(str3[i]<' ')) str3[i]=0;
      else break;
    }

    lnx1.line_trans_init();
    lnx1.line_trans(str3,str4);

    lnx1.str_gb18030_to_utf8_ini();
    lnx1.str_gb18030_to_utf8(str4,str5,SMG_SIZE*2);
    lnx1.str_gb18030_to_utf8_close();

    fputs(str5,s_fp2);
    fputs("\n",s_fp2);
  }

  fclose(s_fp1);
  fclose(s_fp2);

  pid=fork();
  if (pid<0) return(0);
  else if (pid==0)
  {
    j=execlp("lp","lp","to_my_printer.utf8.txt",NULL);
    if (j<0) exit(0);
  }

  return(0);
}

int bw_print::w_cnt_pageline(int basep,int ln)
{
  int i,k;

  k=0;

  for (i=0;i<=t6_ptr1;i++) /* find first screen field */
  {
    if (get_t6_fldbase(i)==basep)
    {
      if (get_t6_linecol(i,0)<=ln)
      {
	if (k<get_t6_fldseri(i)) k=get_t6_fldseri(i);
      }
    }
  }

  return(k);
}

//int bw_print::w_find_pagefld(int i,int j)

int bw_print::w_find_pagefld(int p1,int p2)
{
  int k,l;
  int exist;

  exist=0;

  for (k=0;k<=t6_ptr1;k++)
  {
    if ((get_t6_linecol(k,0)==p1)&&(get_t6_linecol(k,1)==p2))
    {
      exist=1;
      l=get_t6_linecol(k,2);
    }
  }

  if (exist==1) return(l);
  else return(-1);
}

int bw_print::w_print_page(int page,int form,int p_wptr)
{
  long s_recno[STRU_NUM];
  int  i,j,k,l,m,n,o,p,q,s,u,w,x;
  int  exist;
  char logic;
  int  s_tmpn5[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  s_end[STRU_NUM];
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

//win_state7[win_fcnt][win_ptr_win_mark]=win_print_state1;

  for (i=0;i<PAGE_LINE;i++)
    for (j=0;j<PAGE_COLU;j++)
      set_t6_tmps2(i,j,get_t6_pagefile(i,j));

  exist=0;

  if (page==1)
  {
    for (i=0;i<STRU_NUM;i++)
    {
      if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)==0))
      {
        exist=1;
        break;
      }
    }
  }
  else exist=1;

  if (exist==0) return(1);

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)==0)) 
    {
      s_recno[i]=get_t6_recno(i,1);
      s_tmpn5[i]=0;
      s_end[i]=get_t6_eof(i,1); 
    }
  }

  for (k=0;k<STRU_NUM;k++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(k,p_wptr)!=1)||(bw_xbase1.get_win_lnktab(k)!=0)) continue;

    for (l=1;l<=w_cnt_pageline(k,PAGE_LINE);l++)
    {
      for (m=0;m<=t6_ptr1;m++)
      {
	if (get_t6_fldbase(m)!=k) continue;
	if (get_t6_fldseri(m)!=l) continue;

	i=get_t6_linecol(m,0);
	j=get_t6_linecol(m,1);

	if ((get_t6c_fldname(m,0)==':')||(get_t6c_fldname(m,0)=='%'))
	{
	  if (s_tmpn5[k]!=get_t6_fldseri(m))
	  {
	    s_recno[k]=bw_mbase1.w_down_rec(k,p_wptr,s_recno[k]);
	    s_tmpn5[k]=get_t6_fldseri(m);
	    if (bw_xbase1.win_state_dbf_err!=0) s_end[k]=1;
	    //else s_end[k]=0;
	  }

	  get_t6_fldname(m,sfn,SMG_SIZE);
          bw_inkey1.cut_string(sfn,1,strlen(sfn)-1,SMG_SIZE,s_fldname,SMG_SIZE);
			     /* fetch win_field number */
	  n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (n==1)
	  {
	    for (n=1;n<=get_t6_fldlen(m);n++)
	    {
	      set_t6_tmps2(i,j+n-1,' ');
	    }

	    continue;
          }

	  p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_SIZE,k);
	  q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,k);

	  s=bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,k);

          str[0]=0;

	  for (o=1;o<=q;o++)
          {
            str[o-1+0]=bw_xbase1.get_win_recvar(p+o-1);
            str[o-1+1]=0;
          }

	  str[q]=0;
	  str[get_t6_fldlen(m)]=0;

          if (get_t6_fldlen(m)<q) x=get_t6_fldlen(m);
          else x=q;
          w=bw_inkey1.w_chs_string_cut(str,x);
          str[w]=0;

          while (w<x)
          {
            strcat(str," ");
            w++;
          }

	  if (s=='l')
          {
            logic=bw_inkey1.upper(str[0]);

            if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
            else logic='F';

	    if (bw_xbase1.win_state_dbf_err!=0) str[0]=' ';
            else str[0]=logic;
	    str[1]=0;
	  }
			     /* len of echo */
	  if ((s=='c')||(s=='n')||(s=='l'))
	  {
	    for (n=1;n<=get_t6_fldlen(m);n++)
	    {
	      if (n>(int)strlen(str)) set_t6_tmps2(i,j+n-1,' ');
	      else  set_t6_tmps2(i,j+n-1,str[n-1]);
            }
	  }
	  else
	  {
	    for (n=1;n<=get_t6_fldlen(m);n++)
	    {
	      set_t6_tmps2(i,j+n-1,' ');
            }

//	    w_cpy_var();
//	    m5=w_memo_seri(t2_fldname[win_field_num]);
//	    win_scrnvar[0]='A'+m5;
//	    m1=w_open_memo_print(win_scrnvar);
//	    m2=0;

//	    if (m1==0)
//	    {
//	      m2=1;
//	      for (m1=i;m1<=win_page_size;m1++)
//	      {
//		if (m1!=i) m3=w_fetch_memo_size(m1,j);
//		else
//		{
//		  m3=0;
//		  win_memo_left=j;
//		  win_memo_leng=t6_fldlen[m];
//		}

//		if (m3==1) break;
//		m4=w_read_memo(str,m5);
//		if (m4==1)
//		{
//		  m2=0;
//		  win_memo_print[m5]=0;
//		}
//		else
//		{
//		  win_memo_print[m5]=1;
//		  w_put_memo_char(m1,str);
//		}
//	      }
//	      if (m2==0) w_close_memo_print(m5);
//	    }
	  }

	  n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (n==0)
	  {
            u=bw_fldstru1.win_field_num;

	    w_save_pv(p_wptr
			,k
			,u-bw_fldstru1.get_t2_fldpoin(k,0)
			,get_t6_fldseri(m)
			,bw_fldstru1.get_t2_fldposi(u)
			,bw_fldstru1.get_t2_fldlen(u));
          }
	}
	else
	{
	  for (n=1;n<=get_t6_fldlen(m);n++)
	  {
	    set_t6_tmps2(i,j+n-1,' ');
	  }
	}
      }                                   
    }
  }

  /* save imp var */
  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)==0)) {
      //set_t6_recno(i,form,s_recno[i]);

      j=bw_mbase1.w_down_rec(i,p_wptr,s_recno[i]);
      if (bw_xbase1.win_state_dbf_err!=0) s_end[i]=1;
      //else s_end[i]=0;

      if (s_end[i]!=0) set_t6_eof(i,1,1); }
  }

  return(0);
}
/*
int bw_print::w_print_memo(int o)
{
  int  i,j;
  int  m1,m4;
  char str[SMG_SIZE];

  for (i=0;i<PAGE_LINE;i++)
    for (j=0;j<PAGE_COLU;j++)
  {
    set_t6_tmps2(i,j,' ');
    set_t6_pagefile(i,j,' ');
  }

  for (m1=1;m1<=bw_main1.win_page_size;m1++)
  {
    win_memo_left=1;
    win_memo_leng=PAGE_COLU-1;
    m4=w_read_memo(str,SMG_SIZE,o);
    if (m4==1)
    {
      set_win_memo_print(o,0);
      break;
    }
    else
    {
      set_win_memo_print(o,1);
      w_put_memo_char(m1,str,SMG_SIZE);
    }
  }

  return(0);
}
*/
int bw_print::w_print_lnk(int p_wptr) /* echo win rec where modified */
{
//  HDC  hdc1;
  long s_recno[STRU_NUM];
  int  s_seri[STRU_NUM];
  int  s_end[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x;
  int  exist;
  char str1[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)>0))
    {
        if (bw_xbase1.get_win_lnktab(i)==1) s_recno[i]=get_t6_recno(i,1);
        else s_recno[i]=0;

	if (bw_xbase1.get_win_lnktab(i)==1) s_end[i]=get_t6_eof(i,1);
        else s_end[i]=0;

	//bw_xbase1.set_win_recno(i,p_wptr,0,0);
        s_seri[i]=0;
        exist=1;
    }
  }

  if (exist==0) return(0);

  for (r=0;r<COND_NUM;r++)
  {
    if (bw_link1.get_win_bslink(r,2)!=p_wptr) continue;
    k=bw_link1.get_win_bslink(r,1);
    s=bw_link1.get_win_bslink(r,0);

    if (bw_win1.get_win_ptr_wins_dbf(k,p_wptr)!=1) continue;

    if (bw_win1.get_win_ptr_wins_dbf(s,p_wptr)!=1) continue;

    bw_link1.w_link_modi_mark(p_wptr,s,-1,-1);

    if (bw_link1.w_link_modified(p_wptr,s)!=1) continue;

    bw_link1.w_link_modi_unmark(p_wptr,s,-1,-1);

    bw_link1.w_link_modi_mark(p_wptr,k,-1,-1);

    for (l=1;l<=w_cnt_pageline(k,PAGE_LINE);l++)
    {
      for (v=0;v<=t6_ptr1;v++)
      {
	i=get_t6_linecol(v,0);
	j=get_t6_linecol(v,1);

	if (get_t6_fldedit(v)==1)
	{
          m=v;

	  if ((get_t6c_fldname(m,0)!=':')&&(get_t6c_fldname(m,0)!='%'))
          {
	    for (o=1;o<=get_t6_fldlen(m);o++)
	    {
	      set_t6_tmps2(i,j+o-1,' ');
	    }
            continue;
	  }

	  if (get_t6_fldbase(m)!=k) continue;
	  if (get_t6_fldseri(m)!=l) continue;

	  get_t6_fldname(m,str1,SMG_SIZE);
          bw_inkey1.cut_string(str1,1,strlen(str1)-1,SMG_SIZE,s_fldname,SMG_SIZE);

	  if (s_seri[k]!=get_t6_fldseri(m))
	  {

//	    win_tst1=0;

	    while (1)
	    {
	      s_recno[k]=bw_mbase1.w_down_rec(k,p_wptr,s_recno[k]);

	      /*if (bw_xbase1.get_win_lnktab(k)==3) u=1;
	      else*/ u=get_t6_fldseri(m);

	      if (w_print_link_cond_ok(r,p_wptr,k,u,1)==1) break;
	      if (bw_xbase1.win_state_dbf_err==1) break;
	    }
	    s_seri[k]=get_t6_fldseri(m);
	    if (bw_xbase1.win_state_dbf_err==0) bw_xbase1.set_win_enseri(k,p_wptr,l);
          }

		 /* fetch win_field number */
	  n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (n==1)
	  {
	    for (o=1;o<=get_t6_fldlen(m);o++)
	    {
	      set_t6_tmps2(i,j+o-1,' ');
	    }
            continue;
          }

//	  sprintf(str2,"%d,%ld,",bw_xbase1.win_state_dbf_err,s_recno[k]);
//	  win_tst1++;
//	  hdc1=GetDC(bw_main1.win_hwnd1);
//	  TextOut(hdc1,1,win_tst1*20,str2,strlen(str2));
//          ReleaseDC(bw_main1.win_hwnd1,hdc1);

	  p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_SIZE,k);
	  q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,k);

          str1[0]=0;

	  for (o=1;o<=q;o++)
          {
            str1[o-1+0]=bw_xbase1.get_win_recvar(p+o-1);
            str1[o-1+1]=0;
          }

	  str1[q]=0;
	  str1[get_t6_fldlen(m)]=0;

          if (get_t6_fldlen(m)<q) x=get_t6_fldlen(m);
          else x=q;
          w=bw_inkey1.w_chs_string_cut(str1,x);
          str1[w]=0;

          while (w<x)
          {
            strcat(str1," ");
            w++;
          }

	  for (o=1;o<=get_t6_fldlen(m);o++)
	  {
	    if (o>(int)strlen(str1)) set_t6_tmps2(i,j+o-1,' ');
	    else  set_t6_tmps2(i,j+o-1,str1[o-1]);
          }

	  t=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (t==0)
	  {
	    t=bw_fldstru1.win_field_num;

	    w_save_pv(p_wptr
	                ,k
			,t-bw_fldstru1.get_t2_fldpoin(k,0)
			,get_t6_fldseri(m)
                        ,bw_fldstru1.get_t2_fldposi(t)
			,bw_fldstru1.get_t2_fldlen(t));
	  }
	}
      }                                   
    }
  }

  /* save imp var */
  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)>0))
    {
      if (bw_xbase1.get_win_lnktab(i)==1)
      {
        r=bw_link1.w_link_number(p_wptr,i);
        while (1)
        {
          s_recno[i]=bw_mbase1.w_down_rec(i,p_wptr,s_recno[i]);
          u=1;
          if (w_print_link_cond_ok(r,p_wptr,i,u,1)==1) break;
          if (bw_xbase1.win_state_dbf_err==1) break;
        }

        if (bw_xbase1.win_state_dbf_err==1) s_end[i]=1;
        if (s_end[i]!=0) set_t6_eof(i,1,1);
      }
      else
      {
        set_t6_eof(i,1,0);
      }
    }
  }

  return(0);
}

/*
int bw_print::w_print_cal()
{
  unsigned long s_recp;
  int           i,j,k,l,m;
  int state;
  int s_tmpn1,s_tmpn2;
  int s_tmpn3,s_tmpn4;
  int s_tmpn7,s_tmpn8;
  int s_tmpn9,s_tmpn10;
  int s_tmpn11,s_tmpn12;
  int s_tmpn13;
  int ptr1,ptr2,ptr3,ptr4;
  int ptr0,ptr5,ptr6;
  char s_fldname[10];

		 
  for (m=0;m<=t6_ptr1;m++)
  {
    if ((t6_fldname[m][0]!='%')&&
	(t6_fldedit[m]!=1)) continue;

    i=t6_linecol[m][0];
    j=t6_linecol[m][1];

    ptr1=m;
    win_fcnt=t6_fldbase[ptr1];

    if (t6_fldname[ptr1][0]=='%')
      cut_string(t6_fldname[ptr1],1,strlen(t6_fldname[ptr1])-1,s_fldname);
    else
      strcpy(s_fldname,t6_fldname[ptr1]);

    if (strempty(s_fldname)==1)
    {
      w_find_fldnum(s_fldname);
      if ((w_in_calc_var(t6_fldbase[ptr1],win_field_num
			,t6_fldseri[ptr1])>=0)&&
	  (w_calc_modi_var(t6_fldbase[ptr1]
			,win_field_num
			,t6_fldseri[ptr1])==1))
      {
	if (t6_fldseri[ptr1]>win_enseri[win_ptr_win_mark][t6_fldbase[ptr1]]) continue;
	w_fetch_rec(ptr4,t6_fldseri[ptr1],ptr3,t6_fldbase[ptr1]);
	ptr3=t6_fldbase[ptr1];
	ptr4=t6_fldseri[ptr1];

	win_state6=w_calc_var(t6_fldbase[ptr1],win_field_num
		       ,t2_fldlen[win_field_num],t6_fldseri[ptr1]);

	if (win_state6==1) win_state_dbf_modi[ptr3]=1;

	s_tmpn2=w_find_fldnum(s_fldname);
	if (s_tmpn2==1) continue;

	if (t6_fldlen[ptr1]>t2_fldlen[win_field_num])
	  l=t2_fldlen[win_field_num];
	else
	  l=t6_fldlen[ptr1];

	for (k=1;k<=l;k++)
	  t6_tmps2[i][j+k-1]=win_recvar[t2_fldposi[win_field_num]+k-1];

	w_save_sv(win_fcnt,win_field_num-t2_fldpoin[win_fcnt][0]
			,t6_fldseri[ptr1]
			,t2_fldposi[win_field_num]
			,t2_fldlen[win_field_num]);

      }
    }
  }

  return(0);
}
*/

int bw_print::w_print_read()
{
  int  i,j,k,l,m;
  int  s_tmpn3;
  int  exist;
  char s_tmps1[30][50];
  char s_tmps2[SMG_SIZE];
  char sfn[SMG_SIZE];

  strcpy(s_tmps1[1] ,"*y");
  strcpy(s_tmps1[2] ,"*m");
  strcpy(s_tmps1[3] ,"*d");
  strcpy(s_tmps1[4] ,"*yr");
  strcpy(s_tmps1[5] ,"*o");
  strcpy(s_tmps1[6] ,"*time");
  strcpy(s_tmps1[7] ,"*usr");
  strcpy(s_tmps1[8] ,"*recno");
  strcpy(s_tmps1[9] ,"*recnum");
  strcpy(s_tmps1[10],"*fldlen");
  strcpy(s_tmps1[11] ,"*date");

  s_tmpn3=11;

  for (k=0;k<=t6_ptr1;k++)
  {
    i=get_t6_linecol(k,0);
    j=get_t6_linecol(k,1);

    if (get_t6c_fldname(k,0)=='*')
    {
      exist=0;

      for (m=1;m<=s_tmpn3;m++)
      {
	get_t6_fldname(k,sfn,SMG_SIZE);
        if (strcmp(sfn,s_tmps1[m])==0)
        {
	  exist=1;
	  break;
	}
      }

      if (exist==0) continue;

      if (m== 1)  bw_dialog1.w_get_yy(s_tmps2,SMG_SIZE);
      if (m== 2)  bw_dialog1.w_get_mm(s_tmps2,SMG_SIZE);
      if (m== 3)  bw_dialog1.w_get_dd(s_tmps2,SMG_SIZE);
      if (m== 4)  bw_dialog1.w_get_year(s_tmps2,SMG_SIZE);
      if (m== 5)  bw_dialog1.w_get_mon(s_tmps2,SMG_SIZE);
      if (m== 6)  bw_dialog1.w_get_time(s_tmps2,SMG_SIZE);
      if (m== 7)  bw_dialog1.w_get_usr(s_tmps2,SMG_SIZE);
      if (m== 8)  bw_inkey1.long2str(0,s_tmps2,SMG_SIZE);
      if (m== 9)  bw_inkey1.long2str(0,s_tmps2,SMG_SIZE);
      if (m==10)  strcpy(s_tmps2,"");
      if (m==11)  bw_dialog1.w_get_date(s_tmps2,SMG_SIZE);

      for (l=1;l<=get_t6_fldlen(k);l++)
      {
        if (l>(int)strlen(s_tmps2)) set_t6_tmps2(i,j+l-1,' ');
        else set_t6_tmps2(i,j+l-1,s_tmps2[l-1]);
      }
    }
  }

  return(0);
}

int bw_print::w_scan_pv(int p_wptr)
{
  int  i,k,p;
  int  p1,p2;            /* p1 scrn var content poin,p2 scrn var num poin */
  int  exist;
  char str2[FN_SIZE];
  char str1[FN_SIZE];

  p1=0;
  p2=0;

  for (p=0;p<=t6_ptr1;p++)
  {
    if (get_t6_fldedit(p)==1)
    {
      get_t6_fldname(p,str2,FN_SIZE);
      if (strlen(str2)>1) bw_inkey1.cut_string(str2,1,strlen(str2)-1,FN_SIZE,str1,FN_SIZE);
      else continue;

      k=bw_link1.w_name_t1_t2(str1,get_t6_fldbase(p));
      if (k<0) continue;

      set_win_pvpoin(p2,0,p1);
      set_win_pvbase(p2,get_t6_fldbase(p));
      set_win_pvseri(p2,k);
      set_win_pvrecn(p2,get_t6_fldseri(p));
      set_win_pvwind(p2,p_wptr);
                                                
      p1=p1+bw_fldstru1.get_t2_fldlen(k+bw_fldstru1.get_t2_fldpoin(get_t6_fldbase(p),0));

      set_win_pvpoin(p2,1,p1);
      set_win_pvused(p2,1);

      p1++;
      if (p1>=VAR_IN_PAGE)
      {
        bw_win1.w_atten12();
        return(1);
      }

      p2++;
      if (p2>=PRT_VAR_NUM)
      {
        bw_win1.w_atten11();
        return(1);
      }
    }
  }

  return(0);
}

int bw_print::w_save_pv(int p_wptr,int base,int seri,int recn,int posi,int len)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<PRT_VAR_NUM;i++)
  {
    if ((get_win_pvwind(i)==p_wptr)&&(get_win_pvbase(i)==base)&&(get_win_pvseri(i)==seri)&&(get_win_pvrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  for (j=1;j<=len;j++) set_win_pv(get_win_pvpoin(i,0)+j-1,bw_xbase1.get_win_recvar(posi+j-1));
/*
  loc(20,1);
  printf("%d,",win_svpoin[exist]);
  for (i=1;i<=len;i++)
    putchar(win_svar[win_svpoin[exist]+i-1]);
  inkey();
*/
  return(0);
}

int bw_print::w_get_pv(int p_wptr,int base,int seri,int recn,char *p_str,int p_str_size)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<PRT_VAR_NUM;i++)
  {
    if ((get_win_pvwind(i)==p_wptr)&&(get_win_pvbase(i)==base)&&(get_win_pvseri(i)==seri)&&(get_win_pvrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  p_str[0]=0;

  for (j=get_win_pvpoin(i,0);j<get_win_pvpoin(i,1);j++)
  {
    if (j-get_win_pvpoin(i,0)<p_str_size-1)
    {
      p_str[j-get_win_pvpoin(i,0)+0]=get_win_pv(j);
      p_str[j-get_win_pvpoin(i,0)+1]=0;
    }
  }

/*
  loc(20,1);
  printf("%d,",win_svpoin[exist]);
  for (i=1;i<=p_str_len;i++)
    putchar(win_svar[win_svpoin[exist]+i-1]);
  inkey();
*/
  return(0);
}

int bw_print::get_win_pv(int ptr)
{
  if ((ptr<0)||(ptr>=VAR_IN_PAGE)) return(0);
  return(win_pv[ptr]);
}
int bw_print::set_win_pv(int ptr,int val)
{
  if ((ptr<0)||(ptr>=VAR_IN_PAGE)) return(0);
  win_pv[ptr]=val;
  return(0);
}
int bw_print::get_win_pvused(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(win_pvused[vptr]);
}
int bw_print::set_win_pvused(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  win_pvused[vptr]=val;
  return(0);
}
int bw_print::get_win_pvpoin(int vptr,int p01)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_pvpoin[vptr][p01]);
}
int bw_print::set_win_pvpoin(int vptr,int p01,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_pvpoin[vptr][p01]=val;
  return(0);
}
int bw_print::get_win_pvseri(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(win_pvseri[vptr]);
}
int bw_print::set_win_pvseri(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  win_pvseri[vptr]=val;
  return(0);
}
int bw_print::get_win_pvrecn(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(win_pvrecn[vptr]);
}
int bw_print::set_win_pvrecn(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  win_pvrecn[vptr]=val;
  return(0);
}
int bw_print::get_win_pvbase(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(win_pvbase[vptr]);
}
int bw_print::set_win_pvbase(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  win_pvbase[vptr]=val;
  return(0);
}
int bw_print::get_win_pvwind(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(win_pvwind[vptr]);
}
int bw_print::set_win_pvwind(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  win_pvwind[vptr]=val;
  return(0);
}

int bw_print::w_print(int p_wptr,char *p_s1,int p_s1_size)
{

  int  i,j,k,l,m,o;
  int  i2,j2,k2,l2,m2,n2,o2,r2;
  char str2[FN_SIZE];
  char str1[SMG_SIZE];
  char sfn[SMG_SIZE];
  int  err,err2;
  int  exist;
  float f1;

  if (p_s1_size<FN_SIZE) j=p_s1_size;
  else  j=FN_SIZE;
  if (j<1) j=1;
  p_s1[j-1]=0;

  get_setup_print();

  strcpy(str2,p_s1);
  i=w_open_print_file(str2,FN_SIZE);
  if (i!=0) return(1);

  //w_save_print();

  t6_page_num=0;
  f1=bw_main1.win_page_size;
  err2=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(i,p_wptr)!=1) continue;

    set_t6_recno(i,1,0);
    set_t6_eof(i,1,0);
  }

  t6_wdir=0;
  k=0;

  while (1)
  {
    k++; //* page printed 
    j=0;
    while (1)
    {
      j++;  //* form seri 
      i=w_read_page(str2,FN_SIZE,j);
      if (i!=0) break;

      w_page_field1();
      w_page_field2(p_wptr);

      w_scan_pv(p_wptr);
  
      w_print_page(k,j,p_wptr);
      w_print_read();
      w_print_lnk(p_wptr);

      // i,j...i2,j2...
      t6_page_num++;

      if (f1<bw_main1.win_page_line_num)
      {
        for (o=1;o<=(int)f1;o++) fputs("\n",txt_out_fp1);
        f1=f1-(int)f1+bw_main1.win_page_size;
        if (f1<bw_main1.win_page_line_num)
        {
          err2=1;
          break;
        }
      }

      for (i2=0;i2<bw_main1.win_page_line_num;i2++)
      {
	for (j2=0;j2<PAGE_COLU;j2++)
        {
	  if ((get_t6_tmps2(i2,j2)<' ')&&(get_t6_tmps2(i2,j2)>=0)) set_t6_tmps2(i2,j2,' ');
	}

	exist=0;

        for (j2=PAGE_COLU-1;j2>=0;j2--)
        {
	  if ((get_t6_tmps2(i2,j2)>' ')||(get_t6_tmps2(i2,j2)<0))
	  {
	    set_t6_tmps2(i2,j2+1,0);
	    exist=1;
	    break;
	  }
        }

	if (exist==0) set_t6_tmps2(i2,0,0);

        get_s_t6_tmps2(i2,sfn,SMG_SIZE);
        fputs(sfn,txt_out_fp1);
        fputs("\n",txt_out_fp1);
      }

      f1=f1-bw_main1.win_page_line_num;

//      for (o=0;o<MEMO_NUM;o++)
//      {
//	if (win_memo_print[o]==1)
//	{
//	  while (win_memo_print[o]==1)
//	  {
//	    w_print_memo(o);
//	    w_save_memo();
//	  }
//	}
//      }
    }

    if ((j==1)&&(i!=0)) break;   // empty file
    if (err2==1) break;

    //if not eof continue else break....
    j2=0;
    m2=0;

    for (i2=0;i2<STRU_NUM;i2++) {
      if ((bw_win1.get_win_ptr_wins_dbf(i2,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i2)>0 ))  j2++;   // link database num
      if ((bw_win1.get_win_ptr_wins_dbf(i2,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i2)==0))  m2=i2;  // main database
    }

    if (j2==0)    {   // 1 database file
      if (get_t6_eof(m2,1)==0) {
        n2=w_print_page_down(m2,p_wptr);
        if (n2!=0) break;      }
      else break; }
    else if (j2==1) { // 2 database files ,linked table ,type 1,2

      err=0;
      o2=1;

      for (r2=0;r2<COND_NUM;r2++)
      {
        if (bw_link1.get_win_bslink(r2,2)!=p_wptr) continue;

        k2=bw_link1.get_win_bslink(r2,1);
        l2=bw_link1.get_win_bslink(r2,0);

        if (bw_win1.get_win_ptr_wins_dbf(k2,p_wptr)!=1) err=1;
        if (bw_win1.get_win_ptr_wins_dbf(l2,p_wptr)!=1) err=1;
        if (bw_xbase1.get_win_lnktab(k2)!=1) o2=2; // type 2,3 of link table
        if (get_t6_eof(k2,1)==1) err=1; // eof,not print link table
      }

      if (err==0)        {                                 // k2 not eof
        if (o2==1)          {                                             // link type 1
          n2=w_print_page_down(k2,p_wptr); 
          if (n2!=0) break; }
        else if (get_t6_eof(l2,1)==0) {                                   // link type 2,3
          set_t6_recno(k2,1,0);
          set_t6_eof(k2,1,0);
          n2=w_print_page_down(l2,p_wptr); 
          if (n2!=0) break;           }
        else break;      }
      else if (get_t6_eof(l2,1)==0) {                      // k2 eof,l2 not eof
        set_t6_recno(k2,1,0);
        set_t6_eof(k2,1,0);
        n2=w_print_page_down(l2,p_wptr);
        if (n2!=0) break;           }
      else break; }                                        // k2 l2 all eof
    else if (j2>1) { // 3 or more database files ,type 2,3

      err=0;
      o2=1;

      for (r2=0;r2<COND_NUM;r2++)
      {
        if (bw_link1.get_win_bslink(r2,2)!=p_wptr) continue;

        k2=bw_link1.get_win_bslink(r2,1);
        l2=bw_link1.get_win_bslink(r2,0);

        if (bw_win1.get_win_ptr_wins_dbf(k2,p_wptr)!=1) err=1;
        if (bw_win1.get_win_ptr_wins_dbf(l2,p_wptr)!=1) err=1;
        if (bw_xbase1.get_win_lnktab(k2)!=1) o2=2; // type 1 of link table
        if (get_t6_eof(k2,1)==1) err=1; // eof,not print link table

        break; // only get one
      }

      if (err==0)        {                                 // k2 not eof
        if (o2==1)          {                                             // link type 1
          n2=w_print_page_down(k2,p_wptr); 
          if (n2!=0) break; }
        else if (get_t6_eof(l2,1)==0) {                                   // link type 2,3
          set_t6_recno(k2,1,0);
          set_t6_eof(k2,1,0);
          n2=w_print_page_down(l2,p_wptr); 
          if (n2!=0) break;           }
        else break;      }
      else if (get_t6_eof(l2,1)==0) {                      // k2 eof,l2 not eof
        set_t6_recno(k2,1,0);
        set_t6_eof(k2,1,0);
        n2=w_print_page_down(l2,p_wptr);
        if (n2!=0) break;           }
      else break; }                                        // k2 l2 all eof
    else break; 

  }

  w_close_print_file();

  if ((j==1)&&(i!=0)) return(0);
  if (err2!=0) return(0);

  t6_wdir=0;

  set_win_print_fname(str2,FN_SIZE);

  t6_page_num=0;
  win_page_num=0;

  //w_out_win_print();
  w_out_linux_print();

  return(0);

}

int bw_print::get_setup_print()
{
  int  exist;
  int  i,j,k;
  int  p1,p2;
  int  tn1;
  int  tn2;
  char tc1[SMG_SIZE];
  char tc2[20][20];
  char tc3[20][20];
  char tc4[SMG_SIZE];
  char tc5[SMG_SIZE];
  char tc6[SMG_SIZE];
  char tc7[SMG_SIZE];
  FILE *s_fp1;
  float f1;

  tn1=12;
  strcpy(tc2[0],"COLOR");
  strcpy(tc2[1],"PRINTER");
  strcpy(tc2[2],"CONFIRM");
  strcpy(tc2[3],"PAGE");
  strcpy(tc2[4],"PASSWORD");
  strcpy(tc2[5],"DIR");
  strcpy(tc2[6],"SIZE");
  strcpy(tc2[7],"POSITION");
  strcpy(tc2[8],"LANG");
  strcpy(tc2[9] ,"DISPLAY1");
  strcpy(tc2[10],"DISPLAY2");
  strcpy(tc2[11],"WELL");
  tn2=11;
  strcpy(tc3[0],"EPSON");
  strcpy(tc3[1],"STAR");
  strcpy(tc3[2],"LQ_1600K");
  strcpy(tc3[3],"LQ-1600K");
  strcpy(tc3[4],"AR_3240");
  strcpy(tc3[5],"AR-3240");
  strcpy(tc3[6],"AR_2463");
  strcpy(tc3[7],"AR-2463");
  strcpy(tc3[8],"ENGLISH");
  strcpy(tc3[9] ,"800*600");
  strcpy(tc3[10],"IBM_S3");

  s_fp1=fopen("bowo_set.tb0","r");
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1("bowo_set.tb0");
    return(1);
  }

  while (!feof(s_fp1))
  {
    fgets(tc1,SMG_SIZE,s_fp1);
    if ((tc1[0]=='/')&&(tc1[1]=='/')) continue;
    bw_inkey1.strtrim(tc1,SMG_SIZE);
    for (i=0;i<(int)strlen(tc1);i++) tc1[i]=bw_inkey1.upper(tc1[i]);
    i=bw_inkey1.strfind(tc1,"=");
    if (i>=0)
    {
      bw_inkey1.cut_string(tc1,  0,              i,SMG_SIZE,tc4,SMG_SIZE);
      bw_inkey1.cut_string(tc1,i+1,strlen(tc1)-i-1,SMG_SIZE,tc5,SMG_SIZE);
    }
    else
    {
      tc4[0]=0;
      tc5[0]=0;
    }
/*
    loc(20,1);
    printf("%s,%s,",tc4,tc5);
    inkey();
*/
    j=strlen(tc4);
    p1=(-1);
    p2=(-1);
    if (i>=0)
    {
      exist=0;
      for (k=0;k<=tn1-1;k++)
      {
	if (strncmp(tc2[k],tc4,j)==0)
	{
	  exist=1;
	  break;
	}
      }
      if (exist==1) p1=k;

      j=strlen(tc5);
      exist=0;
      for (k=0;k<=tn2-1;k++)
      {
	if (strncmp(tc3[k],tc5,j)==0)
	{
	  exist=1;
	  break;
	}
      }
      if (exist==1) p2=k;
    }

    if (p1==3)
    {
      bw_main1.win_page_size=66;
      f1=bw_inkey1.str2float(tc5,strlen(tc5)+1);
      if (f1>0) bw_main1.win_page_size=f1;
    }

  }
  fclose(s_fp1);
/*
  loc(21,1);
  printf("color=%d,confirm=%d,print=%d,size=%d,"
	 ,win_color,win_confirm,win_print,win_page_size);
  inkey();
*/
  return(0);
}

int bw_print::w_print_page_down(int p_fptr,int p_wptr)
{
  int  i,j,k,l;
  int  s_tmpn1,s_tmpn2;
  int r1,r2;

  if (bw_xbase1.get_win_lnktab(p_fptr)>1) return(1);

  if (bw_xbase1.get_win_lnktab(p_fptr)==0)
  {
    s_tmpn1=w_cnt_pageline(p_fptr,PAGE_LINE);
    //s_tmpn2=s_tmpn1+1;

    for (i=1;i<=s_tmpn1;i++)  // move
    {
      set_t6_recno(p_fptr,1,bw_mbase1.w_down_rec(p_fptr,p_wptr,get_t6_recno(p_fptr,1)));
      if (bw_xbase1.win_state_dbf_err==1) break;
    }

    if (bw_xbase1.win_state_dbf_err==1) return(1);
    else return(0);
  }
  else
  {
    s_tmpn1=w_cnt_pageline(p_fptr,PAGE_LINE);
    //s_tmpn2=s_tmpn1+1;

    for (i=1;i<=s_tmpn1;i++)  // move
    {
      while (1)
      {
	set_t6_recno(p_fptr,1,bw_mbase1.w_down_rec(p_fptr,p_wptr,get_t6_recno(p_fptr,1)));
          /*j=bw_buff1.get_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
          if (j>0) k=bw_win1.get_1fldseri(j);
          else*/ k=1;
        l=bw_link1.w_link_number(p_wptr,p_fptr);
        if (w_print_link_cond_ok(l,p_wptr,p_fptr,k,1)==1) break;
        if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1) break;
    }

    if (bw_xbase1.win_state_dbf_err==1) return(1);
    else return(0);
  }

}

int bw_print::w_print_link_cond_ok(int condnum,int p_wptr,int basep,int recn,int page)
{
//  HDC  hdc;
  int  i,j,k;
  int  exist;
  int  p2;
  int  ptr1,ptr2,ptr3,ptr4;
  int  state;
  char tn[SMG_SIZE];
  char fn[SMG_SIZE];
  char str1[SMG_SIZE];
  long tr;
  char stn[FN_SIZE];
  char sv1[SMG_SIZE];
  char sv2[SMG_SIZE];

  i=condnum;

  exist=0;

  if ((bw_link1.get_win_bslink(i,1)==basep)&&(bw_link1.get_win_bslink(i,2)==p_wptr))
  {
    exist=1;
  }

  if (exist==0) return(0);

  ptr1=(-1);  /* base poin */
  ptr2=(-1);  /* fld  seri */
  ptr3=(-1);  /* buff poin */
  ptr4=(-1);  /* calc char poin */
  state=0;
  p2=bw_link1.get_win_bspoin(i,0);     /* load condition */

  while (1)
  {
    p2=bw_link1.w_fetch_link_var2(i,p2,str1,SMG_SIZE);
    if (p2<0) break;

    if (bw_link1.w_is_calc(str1) == 1)
    {
      if (state != 1) continue;
      state = 0;
      ptr4++;
      bw_link1.set_win_bb2(ptr4, str1[0]);
      continue;
    }

    bw_win1.w_fetch_fld_style(str1,SMG_SIZE,tn,SMG_SIZE,&tr,fn,SMG_SIZE,p_wptr);

    state=1;
    if (bw_inkey1.strempty(tn)==0)  // table name
    {
      bw_win1.w_atten13(str1);
      return(0);
    }
    else
    {
      for (j=0;j<STRU_NUM;j++)
      {
	if (bw_win1.get_win_ptr_wins_dbf(j,p_wptr)==1)
        {
	  bw_win1.get_win_tabname(1,j,stn,FN_SIZE);

	  if (strcmp(stn,tn)==0) break;
        }
      }
      if (j>=STRU_NUM) return(0);
      else ptr1=j;
    }

    if (bw_inkey1.strempty(fn)==0)  // field name
    {
      bw_win1.w_atten14(str1);
      return(0);
    }
    else
    {
      exist=bw_link1.w_name_t1_t2(fn,ptr1);
      if (exist<0)
      {
        bw_win1.w_atten14(str1);
        return(0);
      }
      else ptr2=exist;
    }

    if (ptr1==basep)
    {
      ptr3++;              // get field val
      if (ptr3>=VAL_NUM)
      {
        bw_win1.w_atten12();
        return(0);
      }

      for (j=1;j<=bw_fldstru1.get_t2_fldlen(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0));j++)
      {
	bw_link1.set_win_cbb1(ptr3,j-1,bw_xbase1.get_win_recvar(bw_fldstru1.get_t2_fldposi(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0))+j-1));
	bw_link1.set_win_cbb1(ptr3,j-0,0);
      }
      bw_link1.set_win_bb3(ptr3,bw_fldstru1.get_t2_fldtype(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0)));

    }
    else
    {
      exist=0; // sv to pv ... // get pv val

      for (j=0;j<PRT_VAR_NUM;j++)
      {
	if ((get_win_pvwind(j)==p_wptr)&&(get_win_pvbase(j)==ptr1)&&(get_win_pvseri(j)==ptr2))
        {
	  if (bw_xbase1.get_win_lnktab(basep)<=1)
          {
            exist=1;
	    break;
          }
          else
          {
	    if (get_win_pvrecn(j)==recn)
            {
              exist=1;  
              break;
            }
          }
        }
      }

      if (exist==0) return(0);

      ptr3++;
      if (ptr3>=VAL_NUM)
      {
        bw_win1.w_atten12();
        return(0);
      }

      for (k=get_win_pvpoin(j,0);k<get_win_pvpoin(j,1);k++)
      {
	bw_link1.set_win_cbb1(ptr3,k-get_win_pvpoin(j,0)+0,get_win_pv(k));
	bw_link1.set_win_cbb1(ptr3,k-get_win_pvpoin(j,0)+1,0);
      }
      bw_link1.set_win_bb3(ptr3,bw_fldstru1.get_t2_fldtype(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0)));
    }

    if (ptr3>=1) break;
  }

  bw_link1.get_win_bb1(0,sv1,SMG_SIZE);
  bw_link1.get_win_bb1(1,sv2,SMG_SIZE);

  bw_inkey1.strtrim(sv1,SMG_SIZE);
  bw_inkey1.strtrim(sv2,SMG_SIZE);

  bw_inkey1.strltrim(sv1,SMG_SIZE);
  bw_inkey1.strltrim(sv2,SMG_SIZE);

  if (sv1[0]==0) return(0);
  if (sv2[0]==0) return(0);

//  sprintf(str2,"%s,%s,",sv1,sv2);
//  win_tst1++;
//  hdc=GetDC(bw_main1.win_hwnd1);
//  TextOut(hdc,1,win_tst1*20,str2,strlen(str2));
//  ReleaseDC(bw_main1.win_hwnd1,hdc);

  if ((bw_link1.get_win_bb3(0)=='c')&&(bw_link1.get_win_bb3(1)=='c')&&(bw_link1.get_win_bb2(0)=='='))
  {
    if (strcmp(sv1,sv2)==0) return(1);
    else return(0);
  }
  else return(0);
}




int bw_print::get_t6_linecol(int fptr,int p02) 
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(t6_linecol[fptr][p02]);
}
int bw_print::set_t6_linecol(int fptr,int p02,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  t6_linecol[fptr][p02]=val;
  return(0);
}
int bw_print::get_t6c_fldname(int fptr,int ptr1)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  if ((ptr1<0)||(ptr1>21)) return(0);
  return(t6_fldname[fptr][ptr1]);
}
int bw_print::set_t6c_fldname(int fptr,int ptr1,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  if ((ptr1<0)||(ptr1>21)) return(0);
  t6_fldname[fptr][ptr1]=val;
  return(0);
}
int bw_print::get_t6_fldname(int fptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>21) i=21;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t6_fldname[fptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::set_t6_fldname(int fptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>21) i=21;
  else i=p_s1_size;

  t6_fldname[fptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t6_fldname[fptr][j+0]=p_s1[j];
    t6_fldname[fptr][j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_fldtype(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldtype[fptr]);
}
int bw_print::set_t6_fldtype(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t6_fldtype[fptr]=val;
  return(0);
}
int bw_print::get_t6_fldedit(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldedit[fptr]);
}
int bw_print::set_t6_fldedit(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t6_fldedit[fptr]=val;
  return(0);
}
int bw_print::get_t6_fldbase(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldbase[fptr]);
}
int bw_print::set_t6_fldbase(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t6_fldbase[fptr]=val;
  return(0);
}
int bw_print::get_t6_fldseri(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldseri[fptr]);
}
int bw_print::set_t6_fldseri(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t6_fldseri[fptr]=val;
  return(0);
}
int bw_print::get_t6_fldlen(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldlen[fptr]);
}
int bw_print::set_t6_fldlen(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t6_fldlen[fptr]=val;
  return(0);
}
int bw_print::get_t6_flddec(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t6_flddec[fptr]);
}
int bw_print::set_t6_flddec(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t6_flddec[fptr]=val;
  return(0);
}
int bw_print::get_t6_pagefile(int lptr,int cptr)
{
  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);
  if ((cptr<0)||(cptr>=PAGE_COLU)) return(0);
  return(t6_pagefile[lptr][cptr]);
}
int bw_print::set_t6_pagefile(int lptr,int cptr,int val)
{
  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);
  if ((cptr<0)||(cptr>=PAGE_COLU)) return(0);
  t6_pagefile[lptr][cptr]=val;
  return(0);
}
int bw_print::get_s_t6_pagefile(int lptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);

  if (p_s1_size>PAGE_COLU) i=PAGE_COLU;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t6_pagefile[lptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_tmps2(int lptr,int cptr)
{
  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);
  if ((cptr<0)||(cptr>=PAGE_COLU)) return(0);
  return(t6_tmps2[lptr][cptr]);
}
int bw_print::set_t6_tmps2(int lptr,int cptr,int val)
{
  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);
  if ((cptr<0)||(cptr>=PAGE_COLU)) return(0);
  t6_tmps2[lptr][cptr]=val;
  return(0);
}
int bw_print::get_s_t6_tmps2(int lptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);

  if (p_s1_size>PAGE_COLU) i=PAGE_COLU;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t6_tmps2[lptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
long bw_print::get_t6_recno(int p_fptr,int form)
{
  if ((p_fptr<0)||(p_fptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  return(t6_recno[p_fptr][form]);
}
int bw_print::set_t6_recno(int p_fptr,int form,long val)
{
  if ((p_fptr<0)||(p_fptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  t6_recno[p_fptr][form]=val;
  return(0);
}            
int bw_print::get_t6_eof(int p_fptr,int form)
{
  if ((p_fptr<0)||(p_fptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  return(t6_eof[p_fptr][form]);
}
int bw_print::set_t6_eof(int p_fptr,int form,int val)
{
  if ((p_fptr<0)||(p_fptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  t6_eof[p_fptr][form]=val;
  return(0);
}            
int bw_print::get_t7_fldname(int fptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>10) i=10;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t7_fldname[fptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::set_t7_fldname(int fptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>10) i=10;
  else i=p_s1_size;

  t7_fldname[fptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t7_fldname[fptr][j+0]=p_s1[j];
    t7_fldname[fptr][j+1]=0;
  }

  return(0);
}
int bw_print::set_c_t7_fldname(int fptr,int cptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  if ((cptr<0)||(cptr>=10)) return(0);
  t7_fldname[fptr][cptr]=val;
  return(0);
}
int bw_print::get_t7_fldseri(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t7_fldseri[fptr]);
}
int bw_print::set_t7_fldseri(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t7_fldseri[fptr]=val;
  return(0);
}
int bw_print::get_t7_fldbase(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t7_fldbase[fptr]);
}
int bw_print::set_t7_fldbase(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t7_fldbase[fptr]=val;
  return(0);
}
int bw_print::get_t7_fldrecn(int fptr)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  return(t7_fldrecn[fptr]);
}
int bw_print::set_t7_fldrecn(int fptr,int val)
{
  if ((fptr<0)||(fptr>=FLD_IN_PAGE)) return(0);
  t7_fldrecn[fptr]=val;
  return(0);
}
int bw_print::get_win_memo_print(int mptr)
{
  if ((mptr<0)||(mptr>=MEMO_NUM)) return(0);
  return(win_memo_print[mptr]);
}
int bw_print::set_win_memo_print(int mptr,int val)
{
  if ((mptr<0)||(mptr>=MEMO_NUM)) return(0);
  win_memo_print[mptr]=val;
  return(0);
}
int bw_print::get_win_print_fname(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_print_fname[j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::set_win_print_fname(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  win_print_fname[0]=0;

  for (j=0;j<i-1;j++)
  {
    win_print_fname[j+0]=p_s1[j];
    win_print_fname[j+1]=0;
  }

  return(0);
}

