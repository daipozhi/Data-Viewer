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
extern class bw_getread      bw_getread1;



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



int bw_print::w_open_print_file(char *p_fn,int p_fn_size)
{
  char str1[FN_SIZE];
  int  i,j;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(str1,p_fn);
  i=bw_inkey1.str_seek_char_last(str1,FN_SIZE,'.');
  str1[i]=0;
  strcat(str1,".txt");
  txt_out_fp1=fopen(str1,"w");
  if (txt_out_fp1==NULL) return(1);
  
  return(0);
}
int bw_print::w_close_print_file(void)
{
  fclose(txt_out_fp1);
  return(0);
}
int bw_print::w_read_page(char *p_fn,int p_fn_size)
{
  FILE *s_fp1;
  int   p1,p2,same,end;
  int   state1,state2,state3,state4,state5,state6;
  char  str1[PAGE_COLU];
  char  s_fn[FN_SIZE];
  int   i,j,n;
  int   lcntr,cmd;
  char  c1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(ms_texts1,"usetable=");
  strcpy(ms_texts2,"enddefine");
  strcpy(ms_texts3,"screenseg");
  strcpy(ms_texts4,"endscreen");
  strcpy(ms_texts5,"readvatype");
  strcpy(ms_texts6,"findfile=");
  strcpy(ms_texts7,"findbase=");
  strcpy(ms_texts8,"switchbmp");

  strcpy(s_fn,p_fn);
  bw_inkey1.strtrim(s_fn,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(s_fn,FN_SIZE,'.');
  s_fn[i]=0;
  strcat(s_fn,".sc0");

  s_fp1=fopen(s_fn,"r");    /* fetch page format from page file */
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.mn_hwnd1,s_fn);
    return(1);
  }

  for (i=0;i<PAGE_LINE;i++)
  {
    for (j=0;j<PAGE_COLU;j++)
    {
      set_t6_pagefile(i,j,' ');
    }
  }

  lcntr=0;

  for (i=0;i<PAGE_LINE+10;i++)
  {
    if (feof(s_fp1))
    {
      end=1;
      break;
    }

    str1[0]=0;

    fgets(str1,PAGE_COLU,s_fp1);

    cmd=0;
    p1=0;
    p2=0;
    end=0;
    state1=0;
    state2=0;
    state3=0;
    state4=0;
    state5=0;
    state6=0;

    for (j=0;j<strlen(str1);j++)
    {
      if (str1[j]=='&') break; /* locate for '&' */
    }

    j++;
    p1=j;

    if (p1<strlen(str1))
    {
      same=1;  //use table
      for (p2=p1;p2<=p1+strlen(ms_texts1)-1;p2++)  /* recnigze keywords */
      {
	if ((ms_texts1[p2-p1]>=0)&&(ms_texts1[p2-p1]<=' ')) break;
	if (str1[p2]!=ms_texts1[p2-p1])
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

      same=1;  // end define
      for (p2=p1;p2<=p1+strlen(ms_texts2)-1;p2++)
      {
	if ((ms_texts2[p2-p1]>=0)&&(ms_texts2[p2-p1]<=' ')) break;
	if (str1[p2]!=ms_texts2[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state2=1; /* enddefine */

      same=1;  //screen seg
      for (p2=p1;p2<=p1+strlen(ms_texts3)-1;p2++)
      {
	if ((ms_texts3[p2-p1]>=0)&&(ms_texts3[p2-p1]<=' ')) break;
	if (str1[p2]!=ms_texts3[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state3=1;  /* screenseg */

      same=1;  //end screen
      for (p2=p1;p2<=p1+strlen(ms_texts4)-1;p2++)
      {
	if ((ms_texts4[p2-p1]>=0)&&(ms_texts4[p2-p1]<=' ')) break;
	if (str1[p2]!=ms_texts4[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state4=1;  /* endscreen */

      same=1; // read var type
      for (p2=p1;p2<=p1+strlen(ms_texts5)-1;p2++)  /* recnigze keywords */
      {
	if ((ms_texts5[p2-p1]>=0)&&(ms_texts5[p2-p1]<=' ')) break;
	if (str1[p2]!=ms_texts5[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1)
      {
	state5=1;
      }

      // find findbase name
      same=1;
      for (p2=p1;p2<=p1+strlen(ms_texts6)-1;p2++)  
      {
	if ((ms_texts6[p2-p1]>=0)&&(ms_texts6[p2-p1]<=' ')) break;
	if (str1[p2]!=ms_texts6[p2-p1])
        {
          same=0;
          break;
        }
      }
      if (same==1)
      {
        state6=1;
      }
      
      if (state1==1) cmd=1; /* screentype */
      if (state2==1) cmd=1; /* enddefine  */
      if (state3==1)
      {
	end=1;
	//break; /* screenseg */
      }
      if (state4==1) /* endscreen */
      {
	end=1;
	//break;
      }
      if (state5==1) cmd=1; /* screentype */
      if (state6==1) cmd=1; /* find file  */
    }

    if (end==1) break;
    if (cmd!=0) continue;

    for (j=0;j<PAGE_COLU;j++)
    {
      if (  (j>=strlen(str1))  ||  ((str1[j]>=0)&&(str1[j]<' '))  ) c1=' ';
      else c1=str1[j];
      
      set_t6_pagefile(lcntr,j,c1);
    }

    lcntr++;
  }

  fclose(s_fp1);

  bw_main1.mn_page_line_num=lcntr;

  return(0);
}

int bw_print::tst_p1()
{
  int  i;
  char str[SMG_SIZE];

  bw_getread1.deb_record("bw_print::tst_p1()");

  for (i=0;i<24;i++)
  {
    get_s_t6_pagefile(i,str,SMG_SIZE);

    bw_getread1.deb_record(str);
  }

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
    p4=0;
    p5=0;
    p6=0;

    for (j=p1;j<=p2;j++)  /* field name to var and table line to screen */
    {
      if (get_t6_pagefile(i,j)=='&')
      {
	if (p5==1)
	{
	  set_t6_fldlen(ptr1,j-1-p6);
	  p5=0;
	  ptr1++;
	}
	
	//ptr1++;
	
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
	      ptr1++;
	    }
	  }

	}
	else
	{
	  if (state1==1)
	  {
	    if ((p4==0)&&(get_t6_pagefile(i,j-1)=='%'))
	    {
	      set_c_t6_fldname(ptr1,p4,'%');
	      p4++;
	    }
	    set_c_t6_fldname(ptr1,p4+0,get_t6_pagefile(i,j));
	    set_c_t6_fldname(ptr1,p4+1,0);
	    set_t6_fldtype(ptr1,'c');
	    p4++;
	  }
	  else
	  {
	    if (p5==1)
	    {
	      set_t6_fldlen(ptr1,j-p6);
	      p5=0;
	      ptr1++;
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
  int  i;
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

  bw_getread1.deb_record("bw_print::tst_p2()");

  for (i=0;i<25;i++)
  {
    get_t6_fldname(i,sfn,SMG_SIZE);

    sprintf(str,"ptr=%d,fldname=%s,type=%c,len=%d,"
       ,i,sfn
       ,get_t6_fldtype(i)
       ,get_t6_fldlen(i));

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_print::w_page_field2(int p_wptr)
{
  int  i,k,l,m;
  int  ptr1;
  int  exist;
  int  basep;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];
  char str4[SMG_SIZE];
  char s_fldtable[SMG_SIZE];
  char s_fldname[SMG_SIZE];
  int  n_fldrecno;
  int  n1;
  char sfn[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  basep=i;

  for (i=0;i<FLD_IN_PAGE;i++)
  {
    set_t6_fldbase(i,0);
    set_t6_fldedit(i,0);
    set_t6_fldseri(i,0);
  }
		      
  for (i=0;i<FLD_IN_SCRN;i++) set_t7_fldseri(i,0);

  ptr1=basep; /* default base pntr  */

  for (k=0;k<t6_ptr1;k++)
  {
    i=get_t6_linecol(k,0);

    s_fldtable[0]=0;
    n_fldrecno=0;
    s_fldname[0]=0;

    get_t6_fldname(k,sfn,SMG_SIZE);

    if ((bw_win1.w_field_type(sfn)==6)
      ||(bw_win1.w_field_type(sfn)==7)
      ||(bw_win1.w_field_type(sfn)==8))
    {
      str1[0]=get_c_t6_fldname(k,0);
      str1[1]=0;

      get_t6_fldname(k,str4,SMG_SIZE);

      if (str4[0]=='%')
      {
	n1=1; /* read field */
	bw_inkey1.cut_string(str4,1,strlen(str4)-1,SMG_SIZE,str3,SMG_SIZE);
      }
      else
      {
	n1=0; /* edit field */
	bw_inkey1.cut_string(str4,1,strlen(str4)-1,SMG_SIZE,str3,SMG_SIZE);
      }

      bw_win1.w_fetch_fld_style(str3,SMG_SIZE
                   ,s_fldtable,SMG_SIZE
		   ,&n_fldrecno
		   ,s_fldname,SMG_SIZE
		   ,p_wptr);

      if ((bw_inkey1.strempty(s_fldtable,SMG_SIZE)==0)
	&&(bw_inkey1.strempty(s_fldname,SMG_SIZE)==0))
      {
	set_t6_fldname(k,str4,SMG_SIZE);
      }
      else
      {
	strcpy(str2,str1);
        strcat(str2,s_fldname);
	set_t6_fldname(k,str2,SMG_SIZE);
      }

      ptr1=bw_win1.w_fld_set_base(s_fldtable,SMG_SIZE,ptr1,p_wptr);
      set_t6_fldbase(k,ptr1);

      if (bw_inkey1.strempty(s_fldname,SMG_SIZE)==0)
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
	  &&(n_fldrecno==0))
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

      if (n1==1)
	set_t6_fldedit(k,1);
      else
	set_t6_fldedit(k,w_fld_set_edit(s_fldname,SMG_SIZE));

    }
  }

  return(0);
}

int bw_print::w_fld_set_edit(char *p_fldname,int p_fldname_size)
{
  if (bw_inkey1.strempty(p_fldname,p_fldname_size)==0) return(0);
  else return(1);
}

int bw_print::tst_p3()
{
  int  i;
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

  bw_getread1.deb_record("bw_print::tst_p3()");

  for (i=0;i<25;i++)
  {
    get_t6_fldname(i,sfn,SMG_SIZE);

    sprintf(str,"ptr=%d,fldbase=%d,seri=%d,edit=%d,name=%s,"
	  ,i,get_t6_fldbase(i)
	  ,get_t6_fldseri(i)
	  ,get_t6_fldedit(i)
	  ,sfn);

    bw_getread1.deb_record(str);
  }

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
  i=bw_inkey1.str_seek_char_last(s2,FN_SIZE,'.');
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
    mn_memo_left=c;
    mn_memo_leng=i-c;
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
  for (i=mn_memo_left;i<=mn_memo_left+mn_memo_leng-1;i++)
  {
    if (i-mn_memo_left>=j) set_t6_prtbuff(l,i,' ');
    else set_t6_prtbuff(l,i,p_s1[i-mn_memo_left]);
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
int bw_print::w_save_memo()
{
  int  i,j;
  int  exist;
  char sfn[SMG_SIZE];

  for (i=1;i<=bw_main1.mn_page_size;i++)
  {
    for (j=0;j<PAGE_COLU;j++)
      if ((get_t6_prtbuff(i,j)<' ')&&(get_t6_prtbuff(i,j)>=0)) set_t6_prtbuff(i,j,' ');

    exist=0;

    for (j=PAGE_COLU-1;j>=0;j--)
    {
      if ((get_t6_prtbuff(i,j)>' ')||(get_t6_prtbuff(i,j)<0))
      {
	set_t6_prtbuff(i,j+1,0);
	exist=1;
	break;
      }
    }

    if (exist==0) set_t6_prtbuff(i,0,0);

    get_s_t6_prtbuff(i,sfn,SMG_SIZE);
    fputs(sfn,txt_out_fp1);
    fputs("\n",txt_out_fp1);
  }
  return(0);
}
*/
/*
int bw_print::w_out_win_print()
{
  int  exist;
  int  i,j;
  int  n_end;
  int  n_started;
  char str1[SMG_SIZE];
  char s_fn[SMG_SIZE];
  char ssd[SMG_SIZE];
  char sdev[SMG_SIZE];
  char sdri[SMG_SIZE];
  char sport[SMG_SIZE];
  FILE       *s_fp;
  HDC        hdc;
  TEXTMETRIC tm;
  HFONT      holdfont,hfont;

  get_ms_print_fname(s_fn,SMG_SIZE);

  i=bw_inkey1.str_seek_char_last(s_fn,SMG_SIZE,'.');
  s_fn[i]=0;
  strcat(s_fn,".txt");

  s_fp=fopen(s_fn,"r");
  if (s_fp==NULL)
  {
    bw_win1.w_atten1(bw_main1.mn_hwnd1,s_fn);
    return(1);
  }

  n_end=0;
  n_started=0;

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
    fclose(s_fp);
    return(1);
  }

  i=StartDoc(hdc,&mn_print_inf);
  if (i<=0)
  {
    DeleteDC(hdc);
    fclose(s_fp);
    return(1);
  }

  GetTextMetrics(hdc,&tm);
  mn_print_xchar=tm.tmAveCharWidth;
  mn_print_ychar=tm.tmHeight+tm.tmExternalLeading;

  while(1)
  {
    for (i=0;i<bw_main1.mn_page_size;i++)
    {
      fgets(str1,SMG_SIZE,s_fp);

      if (feof(s_fp))
      {
        fclose(s_fp);
        n_end=1;
        break;
      }

      if (n_started==0)
      {
        n_started=1;

        j=StartPage(hdc);
        if (j<=0)
        {
          DeleteDC(hdc);
          fclose(s_fp);
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

      j=mn_print_ychar*i;
      TextOut(hdc,1,j,str1,strlen(str1));
*//*
      if (feof(s_fp))
      {
        n_end=1;
        break;
      }
*//*
    }

    if (n_started!=0)
    {
      n_started=0;

      i=EndPage(hdc);
      if (i<0)
      {
        DeleteDC(hdc);
        fclose(s_fp);
        n_end=1;
        break;;
      }
    }

    if (n_end!=0) break;
  }

  i=EndDoc(hdc);
  if (i<0)
  {
    DeleteDC(hdc);
    fclose(s_fp);
    return(1);
  }

  DeleteDC(hdc);

  fclose(s_fp);

  return(n_end);
}
*/

//------------------------
// todo:
//   use "system()"
//------------------------

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

  get_ms_print_fname(str1,SMG_SIZE);

  i=bw_inkey1.str_seek_char_last(str1,SMG_SIZE,'.');
  str1[i]=0;
  strcat(str1,".txt");
  strcpy(str2,"to_my_printer.utf8.txt");

  s_fp1=fopen(str1,"r");
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.mn_hwnd1,str1);
    return(1);
  }

  s_fp2=fopen(str2,"w");
  if (s_fp2==NULL)
  {
    bw_win1.w_atten1(bw_main1.mn_hwnd1,str2);
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

  for (i=0;i<t6_ptr1;i++) /* find first screen field */
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
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<t6_ptr1;i++)
  {
    if ((get_t6_linecol(i,0)==p1)&&(get_t6_linecol(i,1)==p2))
    {
      exist=1;
      j=get_t6_linecol(i,2);
    }
  }

  if (exist==1) return(j);
  
  return(-1);
}

int bw_print::w_print_page(int p_wptr)
{
  int  n_recno[STRU_NUM];
  int  i,j,k,l,m,n,o,p,q,s,u,w,x;
  int  exist;
  char logic;
  int  n_fldseri[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  n_end[STRU_NUM];
  char s_fldval[SMG_SIZE];
  char s_tabfld[SMG_SIZE];

  for (i=0;i<PAGE_LINE;i++)
    for (j=0;j<PAGE_COLU;j++)
      set_t6_prtbuff(i,j,get_t6_pagefile(i,j));

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i)==0))
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i)==0)) 
    {
      n_recno[i]=get_t6_recno(i,1);
      n_fldseri[i]=0;
      n_end[i]=get_t6_eof(i,1); 
    }
  }

  for (k=0;k<STRU_NUM;k++)
  {
    if ((bw_win1.get_mn_ptr_wins_dbf(k,p_wptr)!=1)||(bw_xbase1.get_mn_lnktab(k)!=0)) continue;

    for (l=1;l<=w_cnt_pageline(k,PAGE_LINE);l++)
    {
      for (m=0;m<t6_ptr1;m++)
      {
	if (get_t6_fldbase(m)!=k) continue;
	if (get_t6_fldseri(m)!=l) continue;

	i=get_t6_linecol(m,0);
	j=get_t6_linecol(m,1);

	if ((get_c_t6_fldname(m,0)==':')||(get_c_t6_fldname(m,0)=='%'))
	{
	  if (n_fldseri[k]!=get_t6_fldseri(m))
	  {
	    n_recno[k]=bw_mbase1.w_down_rec(k,p_wptr,n_recno[k]);
	    n_fldseri[k]=get_t6_fldseri(m);
	    if (bw_xbase1.mn_state_dbf_err!=0) n_end[k]=1;
	    //else n_end[k]=0;
	  }

	  get_t6_fldname(m,s_tabfld,SMG_SIZE);
          bw_inkey1.cut_string(s_tabfld,1,strlen(s_tabfld)-1,SMG_SIZE,s_fldname,SMG_SIZE);
			     /* fetch mn_field number */
	  bw_fldstru1.mn_field_num=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (bw_fldstru1.mn_field_num<0)
	  {
	    for (n=1;n<=get_t6_fldlen(m);n++)
	    {
	      set_t6_prtbuff(i,j+n-1,' ');
	    }

	    continue;
          }

	  //p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_SIZE,k);
	  q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,k);
	  s=bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,k);

          bw_xbase1.w_fld_cpy(k,s_fldname,SMG_SIZE,s_fldval,SMG_SIZE);  //read from dbf
          
          if (get_t6_fldlen(m)<q) x=get_t6_fldlen(m);
          else x=q;
          
          w=bw_inkey1.w_chs_string_cut(s_fldval,x);
          s_fldval[w]=0;

          while (w<x)
          {
            strcat(s_fldval," ");
            w++;
          }

	  if (s=='l')
          {
            logic=bw_inkey1.upper(s_fldval[0]);

            if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
            else logic='F';

	    if (bw_xbase1.mn_state_dbf_err!=0) s_fldval[0]=' ';
            else s_fldval[0]=logic;
	    s_fldval[1]=0;
	  }
			     /* len of echo */
	  if ((s=='c')||(s=='n')||(s=='l'))
	  {
	    for (n=0;n<get_t6_fldlen(m);n++)
	    {
	      if (n+1>(int)strlen(s_fldval)) set_t6_prtbuff(i,j+n,' ');
	      else  set_t6_prtbuff(i,j+n,s_fldval[n]);
            }
	  }
	  else
	  {
	    for (n=0;n<get_t6_fldlen(m);n++)
	    {
	      set_t6_prtbuff(i,j+n,' ');
            }

//	    w_cpy_var();
//	    m5=w_memo_seri(t2_fldname[mn_field_num]);
//	    mn_scrnvar[0]='A'+m5;
//	    m1=w_open_memo_print(mn_scrnvar);
//	    m2=0;

//	    if (m1==0)
//	    {
//	      m2=1;
//	      for (m1=i;m1<=mn_page_size;m1++)
//	      {
//		if (m1!=i) m3=w_fetch_memo_size(m1,j);
//		else
//		{
//		  m3=0;
//		  mn_memo_left=j;
//		  mn_memo_leng=t6_fldlen[m];
//		}

//		if (m3==1) break;
//		m4=w_read_memo(s_fldval,m5);
//		if (m4==1)
//		{
//		  m2=0;
//		  mn_memo_print[m5]=0;
//		}
//		else
//		{
//		  mn_memo_print[m5]=1;
//		  w_put_memo_char(m1,s_fldval);
//		}
//	      }
//	      if (m2==0) w_close_memo_print(m5);
//	    }
	  }

	  bw_fldstru1.mn_field_num=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (bw_fldstru1.mn_field_num>=0)
	  {
            u=bw_fldstru1.mn_field_num;

	    w_save_pv(p_wptr
			,k
			,u-bw_fldstru1.get_t2_fldpntr(k,0)
			,get_t6_fldseri(m)
			,bw_fldstru1.get_t2_fldposi(u)
			,bw_fldstru1.get_t2_fldlen(u));
          }
	}
	else
	{
	  for (n=0;n<get_t6_fldlen(m);n++)
	  {
	    set_t6_prtbuff(i,j+n,' ');
	  }
	}
      }                                   
    }
  }

  /* save imp var */
  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i)==0)) 
    {
      //set_t6_recno(i,form,n_recno[i]);

      j=bw_mbase1.w_down_rec(i,p_wptr,n_recno[i]);
      if (bw_xbase1.mn_state_dbf_err!=0) n_end[i]=1;
      //else n_end[i]=0;

      if (n_end[i]!=0) set_t6_eof(i,1,1); 
    }
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
    set_t6_prtbuff(i,j,' ');
    set_t6_pagefile(i,j,' ');
  }

  for (m1=1;m1<=bw_main1.mn_page_size;m1++)
  {
    mn_memo_left=1;
    mn_memo_leng=PAGE_COLU-1;
    m4=w_read_memo(str,SMG_SIZE,o);
    if (m4==1)
    {
      set_mn_memo_print(o,0);
      break;
    }
    else
    {
      set_mn_memo_print(o,1);
      w_put_memo_char(m1,str,SMG_SIZE);
    }
  }

  return(0);
}
*/
int bw_print::w_print_lnk(int p_wptr) /* echo win rec where modified */
{
  int  n_recno[STRU_NUM];
  int  n_seri[STRU_NUM];
  int  n_end[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x;
  int  exist;
  char s_tabfld[SMG_SIZE];
  char s_fldval[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i)>0))
    {
        if (bw_xbase1.get_mn_lnktab(i)==1) n_recno[i]=get_t6_recno(i,1);
        else n_recno[i]=0;

	if (bw_xbase1.get_mn_lnktab(i)==1) n_end[i]=get_t6_eof(i,1);
        else n_end[i]=0;

	//bw_xbase1.set_mn_recno(i,p_wptr,0,0);
        n_seri[i]=0;
        exist=1;
    }
  }

  if (exist==0) return(0);

  for (r=0;r<COND_NUM;r++)
  {
    if (bw_link1.get_mn_bslink(r,2)!=p_wptr) continue;
    k=bw_link1.get_mn_bslink(r,1);
    s=bw_link1.get_mn_bslink(r,0);

    if (bw_win1.get_mn_ptr_wins_dbf(k,p_wptr)!=1) continue;

    if (bw_win1.get_mn_ptr_wins_dbf(s,p_wptr)!=1) continue;

    bw_link1.w_link_modi_mark(p_wptr,s,-1,-1);

    if (bw_link1.w_link_modified(p_wptr,s)!=1) continue;

    bw_link1.w_link_modi_unmark(p_wptr,s,-1,-1);

    bw_link1.w_link_modi_mark(p_wptr,k,-1,-1);

    for (l=1;l<=w_cnt_pageline(k,PAGE_LINE);l++)
    {
      for (v=0;v<t6_ptr1;v++)
      {
	i=get_t6_linecol(v,0);
	j=get_t6_linecol(v,1);

	if (get_t6_fldedit(v)==1)
	{
          m=v;

	  if ((get_c_t6_fldname(m,0)!=':')&&(get_c_t6_fldname(m,0)!='%'))
          {
	    for (o=1;o<=get_t6_fldlen(m);o++)
	    {
	      set_t6_prtbuff(i,j+o-1,' ');
	    }
            continue;
	  }

	  if (get_t6_fldbase(m)!=k) continue;
	  if (get_t6_fldseri(m)!=l) continue;

	  get_t6_fldname(m,s_tabfld,SMG_SIZE);
          bw_inkey1.cut_string(s_tabfld,1,strlen(s_tabfld)-1,SMG_SIZE,s_fldname,SMG_SIZE);

	  if (n_seri[k]!=get_t6_fldseri(m))
	  {
	    while (1)
	    {
	      n_recno[k]=bw_mbase1.w_down_rec(k,p_wptr,n_recno[k]);

	      /*if (bw_xbase1.get_mn_lnktab(k)==3) u=1;
	      else*/ u=get_t6_fldseri(m);

	      if (w_print_link_cond_ok(r,p_wptr,k,u,1)==1) break;
	      if (bw_xbase1.mn_state_dbf_err==1) break;
	    }
	    n_seri[k]=get_t6_fldseri(m);
	    if (bw_xbase1.mn_state_dbf_err==0) bw_xbase1.set_mn_enseri(k,p_wptr,l);
          }

		 /* fetch mn_field number */
	  bw_fldstru1.mn_field_num=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (bw_fldstru1.mn_field_num<0)
	  {
	    for (o=0;o<get_t6_fldlen(m);o++)
	    {
	      set_t6_prtbuff(i,j+o,' ');
	    }
            continue;
          }

	  //p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_SIZE,k);
	  q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,k);

          bw_xbase1.w_fld_cpy(k,s_fldname,SMG_SIZE,s_fldval,SMG_SIZE);  //read from dbf

          if (get_t6_fldlen(m)<q) x=get_t6_fldlen(m);
          else x=q;
          
          w=bw_inkey1.w_chs_string_cut(s_fldval,x);
          s_fldval[w]=0;

          while (w<x)
          {
            strcat(s_fldval," ");
            w++;
          }

	  for (o=0;o<get_t6_fldlen(m);o++)
	  {
	    if (o+1>(int)strlen(s_fldval)) set_t6_prtbuff(i,j+o,' ');
	    else  set_t6_prtbuff(i,j+o,s_fldval[o]);
          }

	  bw_fldstru1.mn_field_num=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (bw_fldstru1.mn_field_num>=0)
	  {
	    t=bw_fldstru1.mn_field_num;

	    w_save_pv(p_wptr
	                ,k
			,t-bw_fldstru1.get_t2_fldpntr(k,0)
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
    if ((bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i)>0))
    {
      if (bw_xbase1.get_mn_lnktab(i)==1)
      {
        r=bw_link1.w_link_number(p_wptr,i);
        while (1)
        {
          n_recno[i]=bw_mbase1.w_down_rec(i,p_wptr,n_recno[i]);
          u=1;
          if (w_print_link_cond_ok(r,p_wptr,i,u,1)==1) break;
          if (bw_xbase1.mn_state_dbf_err==1) break;
        }

        if (bw_xbase1.mn_state_dbf_err==1) n_end[i]=1;
        if (n_end[i]!=0) set_t6_eof(i,1,1);
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
  unsigned int s_recp;
  int           i,j,k,l,m;
  int state;
  int n1,n2;
  int n3,n4;
  int n7,n8;
  int n9,n10;
  int n11,n12;
  int n13;
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
    mn_fcnt=t6_fldbase[ptr1];

    if (t6_fldname[ptr1][0]=='%')
      cut_string(t6_fldname[ptr1],1,strlen(t6_fldname[ptr1])-1,s_fldname);
    else
      strcpy(s_fldname,t6_fldname[ptr1]);

    if (strempty(s_fldname)==1)
    {
      w_find_fldnum(s_fldname);
      if ((w_in_calc_var(t6_fldbase[ptr1],mn_field_num
			,t6_fldseri[ptr1])>=0)&&
	  (w_calc_modi_var(t6_fldbase[ptr1]
			,mn_field_num
			,t6_fldseri[ptr1])==1))
      {
	if (t6_fldseri[ptr1]>mn_enseri[mn_ptr_mn_mark][t6_fldbase[ptr1]]) continue;
	w_fetch_rec(ptr4,t6_fldseri[ptr1],ptr3,t6_fldbase[ptr1]);
	ptr3=t6_fldbase[ptr1];
	ptr4=t6_fldseri[ptr1];

	mn_state6=w_calc_var(t6_fldbase[ptr1],mn_field_num
		       ,t2_fldlen[mn_field_num],t6_fldseri[ptr1]);

	if (mn_state6==1) mn_state_dbf_modi[ptr3]=1;

	n2=w_find_fldnum(s_fldname);
	if (n2==1) continue;

	if (t6_fldlen[ptr1]>t2_fldlen[mn_field_num])
	  l=t2_fldlen[mn_field_num];
	else
	  l=t6_fldlen[ptr1];

	for (k=1;k<=l;k++)
	  t6_prtbuff[i][j+k-1]=ms_recvar[t2_fldposi[mn_field_num]+k-1];

	w_save_sv(mn_fcnt,mn_field_num-t2_fldpntr[mn_fcnt][0]
			,t6_fldseri[ptr1]
			,t2_fldposi[mn_field_num]
			,t2_fldlen[mn_field_num]);

      }
    }
  }

  return(0);
}
*/
int bw_print::w_print_read()
{
  int  i,j,k,l,m;
  int  exist;
  char str1[30][50];
  char str2[SMG_SIZE];
  int  n1;
  char sfn[SMG_SIZE];

  strcpy(str1[1] ,"*y");
  strcpy(str1[2] ,"*m");
  strcpy(str1[3] ,"*d");
  strcpy(str1[4] ,"*yr");
  strcpy(str1[5] ,"*o");
  strcpy(str1[6] ,"*time");
  strcpy(str1[7] ,"*usr");
  strcpy(str1[8] ,"*recno");
  strcpy(str1[9] ,"*recnum");
  strcpy(str1[10],"*fldlen");
  strcpy(str1[11],"*date");

  n1=11;

  for (k=0;k<t6_ptr1;k++)
  {
    i=get_t6_linecol(k,0);
    j=get_t6_linecol(k,1);

    if (get_c_t6_fldname(k,0)=='*')
    {
      exist=0;

      for (m=1;m<=n1;m++)
      {
	get_t6_fldname(k,sfn,SMG_SIZE);
        if (strcmp(sfn,str1[m])==0)
        {
	  exist=1;
	  break;
	}
      }

      if (exist==0) continue;

      if (m== 1)  bw_dialog1.w_get_yy(str2,SMG_SIZE);
      if (m== 2)  bw_dialog1.w_get_mm(str2,SMG_SIZE);
      if (m== 3)  bw_dialog1.w_get_dd(str2,SMG_SIZE);
      if (m== 4)  bw_dialog1.w_get_year(str2,SMG_SIZE);
      if (m== 5)  bw_dialog1.w_get_mon(str2,SMG_SIZE);
      if (m== 6)  bw_dialog1.w_get_time(str2,SMG_SIZE);
      if (m== 7)  bw_dialog1.w_get_usr(str2,SMG_SIZE);
      if (m== 8)  bw_inkey1.int2str(0,str2,SMG_SIZE);
      if (m== 9)  bw_inkey1.int2str(0,str2,SMG_SIZE);
      if (m==10)  strcpy(str2,"");
      if (m==11)  bw_dialog1.w_get_date(str2,SMG_SIZE);

      for (l=0;l<get_t6_fldlen(k);l++)
      {
        if (l+1>(int)strlen(str2)) set_t6_prtbuff(i,j+l,' ');
        else set_t6_prtbuff(i,j+l,str2[l]);
      }
    }
  }

  return(0);
}

int bw_print::w_scan_pv(int p_wptr)
{
  int  i,k,p;
  int  p1,p2;            /* p1 scrn var content pntr,p2 scrn var num pntr */
  int  exist;
  char str1[FN_SIZE];
  char str2[FN_SIZE];

  p1=0;
  p2=0;

  for (p=0;p<t6_ptr1;p++)
  {
    if (get_t6_fldedit(p)==1)
    {
      get_t6_fldname(p,str2,FN_SIZE);
      if (strlen(str2)>1) bw_inkey1.cut_string(str2,1,strlen(str2)-1,FN_SIZE,str1,FN_SIZE);
      else continue;

      k=bw_link1.w_name_in_tab(str1,FN_SIZE,get_t6_fldbase(p));
      if (k<0) continue;

      set_mn_pvpntr(p2,0,p1);
      set_mn_pvbase(p2,get_t6_fldbase(p));
      set_mn_pvseri(p2,k);
      set_mn_pvrecn(p2,get_t6_fldseri(p));
      set_mn_pvwind(p2,p_wptr);
                                                
      p1=p1+bw_fldstru1.get_t2_fldlen(k+bw_fldstru1.get_t2_fldpntr(get_t6_fldbase(p),0));

      set_mn_pvpntr(p2,1,p1);
      set_mn_pvused(p2,1);

      p1++;
      if (p1>=VAR_IN_PAGE)
      {
        bw_win1.w_atten12(bw_main1.get_mn_hwnd(p_wptr));
        return(1);
      }

      p2++;
      if (p2>=PRT_VAR_NUM)
      {
        bw_win1.w_atten11(bw_main1.get_mn_hwnd(p_wptr));
        return(1);
      }
    }
  }

  return(0);
}

int bw_print::w_save_pv(int p_wptr,int p_dbptr,int seri,int recn,int posi,int len)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<PRT_VAR_NUM;i++)
  {
    if ((get_mn_pvwind(i)==p_wptr)&&(get_mn_pvbase(i)==p_dbptr)&&(get_mn_pvseri(i)==seri)&&(get_mn_pvrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  for (j=0;j<len;j++) set_ms_pv(get_mn_pvpntr(i,0)+j,bw_xbase1.get_ms_recvar(posi+j));

  return(0);
}

int bw_print::w_get_pv(int p_wptr,int p_dbptr,int seri,int recn,char *p_str,int p_str_size)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  p_str[0]=0;

  exist=0;

  for (i=0;i<PRT_VAR_NUM;i++)
  {
    if ((get_mn_pvwind(i)==p_wptr)&&(get_mn_pvbase(i)==p_dbptr)&&(get_mn_pvseri(i)==seri)&&(get_mn_pvrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  for (j=get_mn_pvpntr(i,0);j<get_mn_pvpntr(i,1);j++)
  {
    if (j-get_mn_pvpntr(i,0)<p_str_size-1)
    {
      p_str[j-get_mn_pvpntr(i,0)+0]=get_ms_pv(j);
      p_str[j-get_mn_pvpntr(i,0)+1]=0;
    }
  }

  return(0);
}

int bw_print::get_ms_pv(int ptr)
{
  if ((ptr<0)||(ptr>=VAR_IN_PAGE)) return(0);
  return(ms_pv[ptr]);
}
int bw_print::set_ms_pv(int ptr,char val)
{
  if ((ptr<0)||(ptr>=VAR_IN_PAGE)) return(0);
  ms_pv[ptr]=val;
  return(0);
}
int bw_print::get_mn_pvused(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(mn_pvused[vptr]);
}
int bw_print::set_mn_pvused(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  mn_pvused[vptr]=val;
  return(0);
}
int bw_print::get_mn_pvpntr(int vptr,int p01)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(mn_pvpntr[vptr][p01]);
}
int bw_print::set_mn_pvpntr(int vptr,int p01,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  mn_pvpntr[vptr][p01]=val;
  return(0);
}
int bw_print::get_mn_pvseri(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(mn_pvseri[vptr]);
}
int bw_print::set_mn_pvseri(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  mn_pvseri[vptr]=val;
  return(0);
}
int bw_print::get_mn_pvrecn(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(mn_pvrecn[vptr]);
}
int bw_print::set_mn_pvrecn(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  mn_pvrecn[vptr]=val;
  return(0);
}
int bw_print::get_mn_pvbase(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(mn_pvbase[vptr]);
}
int bw_print::set_mn_pvbase(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  mn_pvbase[vptr]=val;
  return(0);
}
int bw_print::get_mn_pvwind(int vptr)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  return(mn_pvwind[vptr]);
}
int bw_print::set_mn_pvwind(int vptr,int val)
{
  if ((vptr<0)||(vptr>=PRT_VAR_NUM)) return(0);
  mn_pvwind[vptr]=val;
  return(0);
}

int bw_print::w_print(int p_wptr,char *p_fn,int p_fn_size)
{

  int  i,j,k,l,m,o;
  int  i2,j2,k2,l2,m2,n2,o2,r2;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char s_fn[FN_SIZE];
  int  err,err2;
  int  exist;
  float f1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  get_setup_print();

  strcpy(s_fn,p_fn);
  i=w_open_print_file(s_fn,FN_SIZE);
  if (i!=0) return(1);

  t6_page_num=0;
  f1=bw_main1.mn_page_size;
  err2=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_mn_ptr_wins_dbf(i,p_wptr)!=1) continue;

    set_t6_recno(i,1,0);
    set_t6_eof(i,1,0);
  }

  t6_wdir=0;

  while (1)
  {
    i=w_read_page(s_fn,FN_SIZE);
    if (i!=0) break;

    w_page_field1();
    w_page_field2(p_wptr);

    w_scan_pv(p_wptr);
  
    w_print_page(p_wptr);
    w_print_read();
    w_print_lnk(p_wptr);

    // i,j...i2,j2...
    t6_page_num++;

    if (f1<bw_main1.mn_page_line_num)
    {
      for (o=0;o<(int)f1;o++) fputs("\n",txt_out_fp1);
      f1=f1-(int)f1+bw_main1.mn_page_size;
      if (f1<bw_main1.mn_page_line_num)
      {
        err2=1;
        break;
      }
    }

    for (i2=0;i2<bw_main1.mn_page_line_num;i2++)
    {
      for (j2=0;j2<PAGE_COLU;j2++)
      {
        if ((get_t6_prtbuff(i2,j2)<' ')&&(get_t6_prtbuff(i2,j2)>=0)) set_t6_prtbuff(i2,j2,' ');
      }

      exist=0;

      for (j2=PAGE_COLU-1;j2>=0;j2--)
      {
	if ((get_t6_prtbuff(i2,j2)>' ')||(get_t6_prtbuff(i2,j2)<0))
	{
	  set_t6_prtbuff(i2,j2+1,0);
	  exist=1;
	  break;
	}
      }

      if (exist==0) set_t6_prtbuff(i2,0,0);

      get_s_t6_prtbuff(i2,str2,SMG_SIZE);
      fputs(str2,txt_out_fp1);
      fputs("\n",txt_out_fp1);
    }

    f1=f1-bw_main1.mn_page_line_num;

    if (err2==1) break;

    //if not eof continue else break....
    j2=0;
    m2=0;

    for (i2=0;i2<STRU_NUM;i2++) {
      if ((bw_win1.get_mn_ptr_wins_dbf(i2,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i2)>0 ))  j2++;   // link database num
      if ((bw_win1.get_mn_ptr_wins_dbf(i2,p_wptr)==1)&&(bw_xbase1.get_mn_lnktab(i2)==0))  m2=i2;  // main database
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
        if (bw_link1.get_mn_bslink(r2,2)!=p_wptr) continue;

        k2=bw_link1.get_mn_bslink(r2,1);
        l2=bw_link1.get_mn_bslink(r2,0);

        if (bw_win1.get_mn_ptr_wins_dbf(k2,p_wptr)!=1) err=1;
        if (bw_win1.get_mn_ptr_wins_dbf(l2,p_wptr)!=1) err=1;
        if (bw_xbase1.get_mn_lnktab(k2)!=1) o2=2; // type 2,3 of link table
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
        if (bw_link1.get_mn_bslink(r2,2)!=p_wptr) continue;

        k2=bw_link1.get_mn_bslink(r2,1);
        l2=bw_link1.get_mn_bslink(r2,0);

        if (bw_win1.get_mn_ptr_wins_dbf(k2,p_wptr)!=1) err=1;
        if (bw_win1.get_mn_ptr_wins_dbf(l2,p_wptr)!=1) err=1;
        if (bw_xbase1.get_mn_lnktab(k2)!=1) o2=2; // type 1 of link table
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

  if (i!=0) return(0);
  if (err2!=0) return(0);

  set_ms_print_fname(s_fn,FN_SIZE);

  t6_page_num=0;
  mn_page_num=0;

  w_out_linux_print();

  return(0);

}

int bw_print::get_setup_print()
{
  int  exist;
  int  i,j,k;
  int  p1,p2;
  int  n1;
  int  n2;
  char str1[SMG_SIZE];
  char str2[20][20];
  char str3[20][20];
  char str4[SMG_SIZE];
  char str5[SMG_SIZE];
  char str6[SMG_SIZE];
  char str7[SMG_SIZE];
  char str8[SMG_SIZE];
  FILE *s_fp1;
  float f1;

  n1=12;
  strcpy(str2[0],"COLOR");
  strcpy(str2[1],"PRINTER");
  strcpy(str2[2],"CONFIRM");
  strcpy(str2[3],"PAGE");
  strcpy(str2[4],"PASSWORD");
  strcpy(str2[5],"DIR");
  strcpy(str2[6],"SIZE");
  strcpy(str2[7],"POSITION");
  strcpy(str2[8],"LANG");
  strcpy(str2[9] ,"DISPLAY1");
  strcpy(str2[10],"DISPLAY2");
  strcpy(str2[11],"WELL");
  n2=11;
  strcpy(str3[0],"EPSON");
  strcpy(str3[1],"STAR");
  strcpy(str3[2],"LQ_1600K");
  strcpy(str3[3],"LQ-1600K");
  strcpy(str3[4],"AR_3240");
  strcpy(str3[5],"AR-3240");
  strcpy(str3[6],"AR_2463");
  strcpy(str3[7],"AR-2463");
  strcpy(str3[8],"ENGLISH");
  strcpy(str3[9] ,"800*600");
  strcpy(str3[10],"IBM_S3");

  s_fp1=fopen("bowo_set.tb0","r");
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1(bw_main1.mn_hwnd1,"bowo_set.tb0");
    return(1);
  }

  while (!feof(s_fp1))
  {
    fgets(str1,SMG_SIZE,s_fp1);
    if ((str1[0]=='/')&&(str1[1]=='/')) continue;
    bw_inkey1.strtrim(str1,SMG_SIZE);
    for (i=0;i<(int)strlen(str1);i++) str1[i]=bw_inkey1.upper(str1[i]);
    strcpy(str8,"=");
    i=bw_inkey1.strfind(str1,SMG_SIZE,str8,SMG_SIZE);
    if (i>=0)
    {
      bw_inkey1.cut_string(str1,  0,              i,SMG_SIZE,str4,SMG_SIZE);
      bw_inkey1.cut_string(str1,i+1,strlen(str1)-i-1,SMG_SIZE,str5,SMG_SIZE);
    }
    else
    {
      str4[0]=0;
      str5[0]=0;
    }
/*
    loc(20,1);
    printf("%s,%s,",str4,str5);
    inkey();
*/
    j=strlen(str4);
    p1=(-1);
    p2=(-1);
    if (i>=0)
    {
      exist=0;
      for (k=0;k<=n1-1;k++)
      {
	if (strncmp(str2[k],str4,j)==0)
	{
	  exist=1;
	  break;
	}
      }
      if (exist==1) p1=k;

      j=strlen(str5);
      exist=0;
      for (k=0;k<=n2-1;k++)
      {
	if (strncmp(str3[k],str5,j)==0)
	{
	  exist=1;
	  break;
	}
      }
      if (exist==1) p2=k;
    }

    if (p1==3)
    {
      bw_main1.mn_page_size=66;
      f1=bw_inkey1.str2float(str5,strlen(str5)+1);
      if (f1>0) bw_main1.mn_page_size=f1;
    }

  }
  fclose(s_fp1);
/*
  loc(21,1);
  printf("color=%d,confirm=%d,print=%d,size=%d,"
	 ,mn_color,mn_confirm,mn_print,mn_page_size);
  inkey();
*/
  return(0);
}

int bw_print::w_print_page_down(int p_dbptr,int p_wptr)
{
  int  i,j,k,l;
  int  n1,n2;
  int  r1,r2;

  if (bw_xbase1.get_mn_lnktab(p_dbptr)>1) return(1);

  if (bw_xbase1.get_mn_lnktab(p_dbptr)==0)
  {
    n1=w_cnt_pageline(p_dbptr,PAGE_LINE);
    //n2=n1+1;

    for (i=0;i<n1;i++)  // move
    {
      set_t6_recno(p_dbptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,get_t6_recno(p_dbptr,1)));
      if (bw_xbase1.mn_state_dbf_err==1) break;
    }

    if (bw_xbase1.mn_state_dbf_err==1) return(1);
    else return(0);
  }
  else
  {
    n1=w_cnt_pageline(p_dbptr,PAGE_LINE);
    //n2=n1+1;

    for (i=0;i<n1;i++)  // move
    {
      while (1)
      {
	set_t6_recno(p_dbptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,get_t6_recno(p_dbptr,1)));
          /*j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pcolu);
          if (j>0) k=bw_win1.get_t_fldseri(j);
          else*/ k=1;
        l=bw_link1.w_link_number(p_wptr,p_dbptr);
        if (w_print_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
        if (bw_xbase1.mn_state_dbf_err==1) break;
      }
      if (bw_xbase1.mn_state_dbf_err==1) break;
    }

    if (bw_xbase1.mn_state_dbf_err==1) return(1);
    else return(0);
  }

}

int bw_print::w_print_link_cond_ok(int condnum,int p_wptr,int p_dbptr,int recn,int page)
{
  int  i,j,k;
  int  exist;
  int  p2;
  int  ptr1,ptr2,ptr3,ptr4;
  int  state;
  char str_tn[SMG_SIZE];
  char str_fn[SMG_SIZE];
  char str1[SMG_SIZE];
  int  tr;
  char str_tab[FN_SIZE];
  char str_v1[SMG_SIZE];
  char str_v2[SMG_SIZE];

  i=condnum;

  exist=0;

  if ((bw_link1.get_mn_bslink(i,1)==p_dbptr)&&(bw_link1.get_mn_bslink(i,2)==p_wptr))
  {
    exist=1;
  }

  if (exist==0) return(0);

  ptr1=(-1);  /* base pntr */
  ptr2=(-1);  /* fld  seri */
  ptr3=(-1);  /* buff pntr */
  ptr4=(-1);  /* calc char pntr */
  state=0;
  p2=bw_link1.get_mn_bspntr(i,0);     /* load condition */

  while (1)
  {
    p2=bw_link1.w_fetch_link_var2(i,p2,str1,SMG_SIZE);
    if (p2<0) break;

    if (bw_link1.w_is_calc(str1) == 1)
    {
      if (state != 1) continue;
      state = 0;
      ptr4++;
      bw_link1.set_mn_bb2(ptr4, str1[0]);
      continue;
    }

    bw_win1.w_fetch_fld_style(str1,SMG_SIZE,str_tn,SMG_SIZE,&tr,str_fn,SMG_SIZE,p_wptr);

    state=1;
    if (bw_inkey1.strempty(str_tn,SMG_SIZE)==0)  // table name
    {
      bw_win1.w_atten13(bw_main1.get_mn_hwnd(p_wptr),str1);
      return(0);
    }
    else
    {
      for (j=0;j<STRU_NUM;j++)
      {
	if (bw_win1.get_mn_ptr_wins_dbf(j,p_wptr)==1)
        {
	  bw_win1.get_ms_tabname(1,j,str_tab,FN_SIZE);

	  if (strcmp(str_tab,str_tn)==0) break;
        }
      }
      if (j>=STRU_NUM) return(0);
      else ptr1=j;
    }

    if (bw_inkey1.strempty(str_fn,SMG_SIZE)==0)  // field name
    {
      bw_win1.w_atten14(bw_main1.get_mn_hwnd(p_wptr),str1);
      return(0);
    }
    else
    {
      exist=bw_link1.w_name_in_tab(str_fn,SMG_SIZE,ptr1);
      if (exist<0)
      {
        bw_win1.w_atten14(bw_main1.get_mn_hwnd(p_wptr),str1);
        return(0);
      }
      else ptr2=exist;
    }

    if (ptr1==p_dbptr)
    {
      ptr3++;              // get field val
      if (ptr3>=VAL_NUM)
      {
        bw_win1.w_atten12(bw_main1.get_mn_hwnd(p_wptr));
        return(0);
      }

      for (j=1;j<=bw_fldstru1.get_t2_fldlen(ptr2+bw_fldstru1.get_t2_fldpntr(ptr1,0));j++)
      {
	bw_link1.set_mn_cbb1(ptr3,j-1,bw_xbase1.get_ms_recvar(bw_fldstru1.get_t2_fldposi(ptr2+bw_fldstru1.get_t2_fldpntr(ptr1,0))+j-1));
	bw_link1.set_mn_cbb1(ptr3,j-0,0);
      }
      bw_link1.set_mn_bb3(ptr3,bw_fldstru1.get_t2_fldtype(ptr2+bw_fldstru1.get_t2_fldpntr(ptr1,0)));

    }
    else
    {
      exist=0; // sv to pv ... // get pv val

      for (j=0;j<PRT_VAR_NUM;j++)
      {
	if ((get_mn_pvwind(j)==p_wptr)&&(get_mn_pvbase(j)==ptr1)&&(get_mn_pvseri(j)==ptr2))
        {
	  if (bw_xbase1.get_mn_lnktab(p_dbptr)<=1)
          {
            exist=1;
	    break;
          }
          else
          {
	    if (get_mn_pvrecn(j)==recn)
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
        bw_win1.w_atten12(bw_main1.get_mn_hwnd(p_wptr));
        return(0);
      }

      for (k=get_mn_pvpntr(j,0);k<get_mn_pvpntr(j,1);k++)
      {
	bw_link1.set_mn_cbb1(ptr3,k-get_mn_pvpntr(j,0)+0,get_ms_pv(k));
	bw_link1.set_mn_cbb1(ptr3,k-get_mn_pvpntr(j,0)+1,0);
      }
      bw_link1.set_mn_bb3(ptr3,bw_fldstru1.get_t2_fldtype(ptr2+bw_fldstru1.get_t2_fldpntr(ptr1,0)));
    }

    if (ptr3>=1) break;
  }

  bw_link1.get_ms_bb1(0,str_v1,SMG_SIZE);
  bw_link1.get_ms_bb1(1,str_v2,SMG_SIZE);

  bw_inkey1.strtrim(str_v1,SMG_SIZE);
  bw_inkey1.strtrim(str_v2,SMG_SIZE);

  bw_inkey1.strltrim(str_v1,SMG_SIZE);
  bw_inkey1.strltrim(str_v2,SMG_SIZE);

  if (str_v1[0]==0) return(0);
  if (str_v2[0]==0) return(0);

//  sprintf(str2,"%s,%s,",str_v1,str_v2);
//  mn_tst1++;
//  hdc=GetDC(bw_main1.mn_hwnd1);
//  TextOut(hdc,1,mn_tst1*20,str2,strlen(str2));
//  ReleaseDC(bw_main1.mn_hwnd1,hdc);

  if ((bw_link1.get_mn_bb3(0)=='c')&&(bw_link1.get_mn_bb3(1)=='c')&&(bw_link1.get_mn_bb2(0)=='='))
  {
    if (strcmp(str_v1,str_v2)==0) return(1);
    else return(0);
  }
  else return(0);
}




int bw_print::get_t6_linecol(int fldptr,int p02) 
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(t6_linecol[fldptr][p02]);
}
int bw_print::set_t6_linecol(int fldptr,int p02,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  t6_linecol[fldptr][p02]=val;
  return(0);
}
int bw_print::get_c_t6_fldname(int fldptr,int ptr1)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  if ((ptr1<0)||(ptr1>21)) return(0);
  return(t6_fldname[fldptr][ptr1]);
}
int bw_print::set_c_t6_fldname(int fldptr,int ptr1,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  if ((ptr1<0)||(ptr1>21)) return(0);
  t6_fldname[fldptr][ptr1]=val;
  return(0);
}
int bw_print::get_t6_fldname(int fldptr,char *p_s,int p_s_size)
{
  int i,j;

  p_s[0]=0;

  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);

  if (p_s_size>21) i=21;
  else i=p_s_size;

  for (j=0;j<i-1;j++)
  {
    p_s[j+0]=t6_fldname[fldptr][j];
    p_s[j+1]=0;
  }

  return(0);
}
int bw_print::set_t6_fldname(int fldptr,char *p_s,int p_s_size)
{
  int i,j;

  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);

  if (p_s_size>21) i=21;
  else i=p_s_size;

  t6_fldname[fldptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t6_fldname[fldptr][j+0]=p_s[j];
    t6_fldname[fldptr][j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_fldtype(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldtype[fldptr]);
}
int bw_print::set_t6_fldtype(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t6_fldtype[fldptr]=val;
  return(0);
}
int bw_print::get_t6_fldedit(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldedit[fldptr]);
}
int bw_print::set_t6_fldedit(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t6_fldedit[fldptr]=val;
  return(0);
}
int bw_print::get_t6_fldbase(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldbase[fldptr]);
}
int bw_print::set_t6_fldbase(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t6_fldbase[fldptr]=val;
  return(0);
}
int bw_print::get_t6_fldseri(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldseri[fldptr]);
}
int bw_print::set_t6_fldseri(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t6_fldseri[fldptr]=val;
  return(0);
}
int bw_print::get_t6_fldlen(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t6_fldlen[fldptr]);
}
int bw_print::set_t6_fldlen(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t6_fldlen[fldptr]=val;
  return(0);
}
int bw_print::get_t6_flddec(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t6_flddec[fldptr]);
}
int bw_print::set_t6_flddec(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t6_flddec[fldptr]=val;
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
int bw_print::get_s_t6_pagefile(int lptr,char *p_s,int p_s_size)
{
  int i,j;

  p_s[0]=0;

  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);

  if (p_s_size>PAGE_COLU) i=PAGE_COLU;
  else i=p_s_size;

  for (j=0;j<i-1;j++)
  {
    p_s[j+0]=t6_pagefile[lptr][j];
    p_s[j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_prtbuff(int lptr,int cptr)
{
  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);
  if ((cptr<0)||(cptr>=PAGE_COLU)) return(0);
  return(t6_prtbuff[lptr][cptr]);
}
int bw_print::set_t6_prtbuff(int lptr,int cptr,int val)
{
  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);
  if ((cptr<0)||(cptr>=PAGE_COLU)) return(0);
  t6_prtbuff[lptr][cptr]=val;
  return(0);
}
int bw_print::get_s_t6_prtbuff(int lptr,char *p_s,int p_s_size)
{
  int i,j;

  p_s[0]=0;

  if ((lptr<0)||(lptr>=PAGE_LINE)) return(0);

  if (p_s_size>PAGE_COLU) i=PAGE_COLU;
  else i=p_s_size;

  for (j=0;j<i-1;j++)
  {
    p_s[j+0]=t6_prtbuff[lptr][j];
    p_s[j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_recno(int p_dbptr,int form)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  return(t6_recno[p_dbptr][form]);
}
int bw_print::set_t6_recno(int p_dbptr,int form,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  t6_recno[p_dbptr][form]=val;
  return(0);
}            
int bw_print::get_t6_eof(int p_dbptr,int form)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  return(t6_eof[p_dbptr][form]);
}
int bw_print::set_t6_eof(int p_dbptr,int form,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((form<0)||(form>=PRINT_FORM_NUM)) return(0);
  t6_eof[p_dbptr][form]=val;
  return(0);
}            
int bw_print::get_t7_fldname(int fldptr,char *p_s,int p_s_size)
{
  int i,j;

  p_s[0]=0;

  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);

  if (p_s_size>10) i=10;
  else i=p_s_size;

  for (j=0;j<i-1;j++)
  {
    p_s[j+0]=t7_fldname[fldptr][j];
    p_s[j+1]=0;
  }

  return(0);
}
int bw_print::set_t7_fldname(int fldptr,char *p_s,int p_s_size)
{
  int i,j;

  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);

  if (p_s_size>10) i=10;
  else i=p_s_size;

  t7_fldname[fldptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t7_fldname[fldptr][j+0]=p_s[j];
    t7_fldname[fldptr][j+1]=0;
  }

  return(0);
}
int bw_print::set_c_t7_fldname(int fldptr,int cptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  if ((cptr<0)||(cptr>=10)) return(0);
  t7_fldname[fldptr][cptr]=val;
  return(0);
}
int bw_print::get_t7_fldseri(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t7_fldseri[fldptr]);
}
int bw_print::set_t7_fldseri(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t7_fldseri[fldptr]=val;
  return(0);
}
int bw_print::get_t7_fldbase(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t7_fldbase[fldptr]);
}
int bw_print::set_t7_fldbase(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t7_fldbase[fldptr]=val;
  return(0);
}
int bw_print::get_t7_fldrecn(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  return(t7_fldrecn[fldptr]);
}
int bw_print::set_t7_fldrecn(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_PAGE)) return(0);
  t7_fldrecn[fldptr]=val;
  return(0);
}
int bw_print::get_mn_memo_print(int mptr)
{
  if ((mptr<0)||(mptr>=MEMO_NUM)) return(0);
  return(mn_memo_print[mptr]);
}
int bw_print::set_mn_memo_print(int mptr,int val)
{
  if ((mptr<0)||(mptr>=MEMO_NUM)) return(0);
  mn_memo_print[mptr]=val;
  return(0);
}
int bw_print::get_ms_print_fname(char *p_s,int p_s_size)
{
  int i,j;

  if (p_s_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s_size;

  p_s[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s[j+0]=ms_print_fname[j];
    p_s[j+1]=0;
  }

  return(0);
}
int bw_print::set_ms_print_fname(char *p_s,int p_s_size)
{
  int i,j;

  if (p_s_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s_size;

  ms_print_fname[0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_print_fname[j+0]=p_s[j];
    ms_print_fname[j+1]=0;
  }

  return(0);
}

