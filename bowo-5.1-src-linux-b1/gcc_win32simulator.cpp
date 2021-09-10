
/* error 1: WM_CREATE should have break/return */

/* error 2: att to this func(char *s); s[n]=NULL;func(""); */

/*
 vax error 1: fseek() don't clear feof() ,use clearerr()
*/
/*
 vax error 2: there is error when program continue fputc 300 times,
	      use fputs
*/
/*
  motorola unix system V
   1.  when define extern function do not use param
   2.  when define function param, not allow ss(int i,int j)
       must like this
	 ss(i,j)
	 int i,j;
*/

/*
#define STRICT
*/
#define _CRT_SECURE_NO_WARNINGS

#include "windows.h"
/*
#include <commdlg.h>
*/
#include <stdio.h>
/*
#include <math.h>
#include <dir.h>
#include <dos.h>
#include <bios.h>
#include <conio.h>
#include <process.h>
*/
#include <string.h>
/*
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>
#include <sys/io.h>
*/

//----------------------------------------------
//
// define for gc_win32emulator.cpp
//
//----------------------------------------------

#include <locale.h>
#include <iconv.h>

iconv_t cd ;

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

   int cpy_string(char *p_s1,int p_s1_size,char *p_s2,int p_s2_size);
};

       class  lnx         lnx1;

       char   lnx_win_ci_text[STRING_SIZE];
       int    lnx_win_ci_p1;
       int    lnx_win_ci_p2;

//extern long   w_acm_calc_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_bmp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
//extern long   w_sdsc_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
//extern long   w_sdsc_fun_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
//extern long   w_acm_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
//extern long   w_asm_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
//extern long   w_acm_fun_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_main_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_menu_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_edit_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_savep_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_outp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long   w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LPARAM lp);
extern long   w_menu2_ci_wp(HWND hwnd,WORD msg,WORD wp,LPARAM lp);
extern long   w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LPARAM lp);





int main(void)
{
  lnx1.ini_win_class();
  lnx1.ini_win_handle();
  lnx1.ini_win_ci();
  lnx1.ini_msg_pipe();
  lnx1.ini_charsize();
  
  lnx1.get_setup();

  lnx1.lnx_exit=0;

  WinMain(0,0,(char*)NULL,0);
  
  return(0);
}

int lnx::ini_charsize(void)
{
  lnx_xchar=25;
  lnx_ychar=30;
  return(0);
}

int lnx::ini_win_class(void)
{
  lnx_win_class_pp=0;
  return(0);
}

int reg_win_class(char *ps1,int pn1,char *ps2)
{
  int i;

  i=lnx1.lnx_win_class_pp;
  lnx1.sets_lnx_win_class_name(i,ps1);
  lnx1.sets_lnx_win_class_menu(i,ps2);
  lnx1.set_lnx_win_class_proc(i,pn1);
  lnx1.lnx_win_class_pp=lnx1.lnx_win_class_pp+1;
  return(0);
}

int lnx::find_win_class(char *ps1,char *ps2)
{
  int  i,j;
  char str1[STRING_SIZE];
  char str2[STRING_SIZE];

  j=(-1);
  for (i=0;i<lnx_win_class_pp;i++)
  {
    gets_lnx_win_class_name(i,str1);
    if (strcmp(ps1,str1)==0)
    {
      j=i;
      break;
    }
  }

  if (j<0)
  {

    ps2[0]=0;
    return(0);
  }
  else
  {
    gets_lnx_win_class_menu(i,str2);
    strcpy(ps2,str2);
    return(get_lnx_win_class_proc(i));
  }
}

int lnx::ini_win_handle(void)
{
  int i;
  for (i=0;i<MAX_WIN_NUM_4LNX;i++)
  {
    set_lnx_win_handle_inuse(i,0);
  }
  return(0);
}

int lnx::add_win_handle(char *ps1,char *ps2)
{
  char str1[STRING_SIZE];
  int  n1;
  int  i,j;

  n1=find_win_class(ps1,str1);

  j=(-1);
  for (i=0;i<MAX_WIN_NUM_4LNX;i++)
  {
    if (get_lnx_win_handle_inuse(i)==0)
    {
      j=i;
      set_lnx_win_handle_inuse(i,1);
      set_lnx_win_handle_proc(i,n1);
      sets_lnx_win_handle_name(i,ps1);
      sets_lnx_win_handle_menu(i,str1);
      sets_lnx_win_handle_topic(i,ps2);
      break;
    }
  }

  return(j);
}

int lnx::ini_msg_pipe(void)
{
  pipe_pp1=0;
  pipe_pp2=0;
  return(0);
}

int lnx::add_msg_to_pipe(int p1,int p2,int p3,int p4)
{
  set_pipe_buff(pipe_pp2,0,p1);
  set_pipe_buff(pipe_pp2,1,p2);
  set_pipe_buff(pipe_pp2,2,p3);
  set_pipe_buff(pipe_pp2,3,p4);

  pipe_pp2++;
  if (pipe_pp2>=PIPE_NUM) pipe_pp2=0;

  return(0);
}

int lnx::exec_msg(void)
{
  int i,j,k,l;
  int n1,n2,n3,n4;

  while (pipe_pp1!=pipe_pp2)
  {
    n1=get_pipe_buff(pipe_pp1,0);
    n2=get_pipe_buff(pipe_pp1,1);
    n3=get_pipe_buff(pipe_pp1,2);
    n4=get_pipe_buff(pipe_pp1,3);
        
    if (n1<MAX_WIN_NUM_4LNX)
    {
        j=get_lnx_win_handle_proc(n1);

        if (n2==WM_PAINT)
        {
          for (k=0;k<LIN_NUM_4LNX;k++)
          {
            for (l=0;l<COL_NUM_4LNX;l++)
            {
              set_paint_buff(n1,k,l,' ');
            }
          }
        }

        j=get_lnx_win_handle_proc(n1);

    	exec_win_proc(j,n1,n2,n3,n4);
    }
    else
    {
        exec_win_ci_proc(n1,n2,n3,n4);
    }

//    printf("msg proc=%d,hwnd=%d,msg=%d,wp=%d,lp=%d,\n",j,n1,n2,n3,n4);

    pipe_pp1++;
    if (pipe_pp1>=PIPE_NUM) pipe_pp1=0;
  }

  return(0);
}

int lnx::exec_win_proc(int pp,int n1,int n2,int n3,int n4)
{

//  if (pp==1)      w_asm_wp(n1,n2,n3,n4);
//  if (pp==2)      w_acm_wp(n1,n2,n3,n4);
//  if (pp==3)  w_acm_fun_wp(n1,n2,n3,n4);
//  if (pp==4) w_acm_calc_wp(n1,n2,n3,n4);
//  if (pp==5)     w_sdsc_wp(n1,n2,n3,n4);
  if (pp==6)      w_bmp_wp(n1,n2,n3,n4);
//  if (pp==7) w_sdsc_fun_wp(n1,n2,n3,n4);
  if (pp==8)     w_main_wp(n1,n2,n3,n4);
  if (pp==9)     w_menu_wp(n1,n2,n3,n4);
  if (pp==10)    w_edit_wp(n1,n2,n3,n4);
  //if (pp==11)   w_savep_wp(n1,n2,n3,n4);
  //if (pp==12)    w_outp_wp(n1,n2,n3,n4);

  return(0);
}

int lnx::exec_win_ci_proc(int h1,int h2,int h3,int h4)
{
  int i,j,k;

  if ((h1>MAX_WIN_NUM_4LNX)&&(h2==BM_SETCHECK))
  {
      i=h1-MAX_WIN_NUM_4LNX-1;

      if (h3==11)  lnx1.set_lnx_win_ci_buff(i,10,1);
      else  lnx1.set_lnx_win_ci_buff(i,10,0);
  }

  return(0);
}

/*
int lnx::pre_paint_focus_win(void)
{
  int  i,j,k,l,m;
//  char c1;
//  char str[STRING_SIZE];

  i=lnx_focus_pp;

  l=0;
  for (j=0;j<LIN_NUM_4LNX;j++)
  {
    for (k=0;k<COL_NUM_4LNX;k++)
    {
      if ((get_paint_buff(i,j,k)>' ')||(get_paint_buff(i,j,k)<0))
      {
         l=1;
         lnx_ywin=j;
         break;
      }
    }
    if (l==1) break;
  }

  l=0;
  for (j=0;j<COL_NUM_4LNX;j++)
  {
    for (k=0;k<LIN_NUM_4LNX;k++)
    {
      if ((get_paint_buff(i,k,j)>' ')||(get_paint_buff(i,k,j)<0))
      {
         l=1;
         lnx_xwin=j;
         break;
      }
    }
    if (l==1) break;
  }


  printf("xwin=%d,ywin=%d,\n",lnx_xwin,lnx_ywin);
  
  return(0);
}
*/
int lnx::paint_focus_win(void)
{
  int  i,j,k,l,m;
  char c1;
  char str[STRING_SIZE];
  char str2[STRING_SIZE];
  char str3[STRING_SIZE];

  i=lnx_focus_pp;
  if ((i<0)||(i>=MAX_WIN_NUM_4LNX)) return(0);
  
  for (j=0;j<LIN_NUM_4LNX;j++)
  {
    l=0;
    for (k=0;k<COL_NUM_4LNX;k++)
    {
      if ((paint_buff2[j][k]>' ')||(paint_buff2[j][k]<0)) l=1;
    }

    if (l==1)
    {
      for (m=COL_NUM_4LNX-1;m>=0;m--)
      {
        if ((paint_buff2[j][m]>' ')||(paint_buff2[j][m]<0)) break;
      }
      
      for (k=0;k<=m;k++)
      {
        c1=paint_buff2[j][k];
        if ((c1>=0)&&(c1<' ')) c1=' ';
        str[k+0]=c1;
        str[k+1]=0;
      }

      //printf("%s\n",str);

      line_trans_init();
      line_trans(str,str2);

      str_gb18030_to_utf8_ini();
      str_gb18030_to_utf8(str2,str3,STRING_SIZE);
      str_gb18030_to_utf8_close();

      printf("%s\n",str3);

    }
  }

  return(0);
}

int lnx::line_trans_init(void)
{
  char str[300];
  int  i;
  FILE *s_fp1;

  s_fp1=fopen("line-trans.txt","r");
  if (s_fp1==NULL)
  {
	printf("Open file line-trans.txt error .\n");
	return(1);
  }
  else
  {
    line_trans_pp=0;
    
    while (!feof(s_fp1))
    {
      fgets(str,300,s_fp1);

      for (i=0;i<6;i++)
      {
        line_trans_buff[line_trans_pp][i+0]=str[i];
        line_trans_buff[line_trans_pp][i+1]=0;
      }

      line_trans_pp++;

      if ((str[0]>=0)&&(str[0]<=' ')) break;
    }

    fclose(s_fp1);

    return(0);
  }
}

int lnx::line_trans(char *p_str1,char *p_str2)
{
  char s1[10];
  char s2[10];
  int i,j,k;

  i=0;
  p_str2[0]=0;

  while(i<strlen(p_str1))
  {
    if (p_str1[i]>=0)
    {
      s1[0]=p_str1[i];
      s1[1]=0;

      strcpy(s2,s1);

      i++;
    }
    else
    {
      s1[0]=p_str1[i+0];
      s1[1]=p_str1[i+1];
      s1[2]=0;

      k=0;
      for (j=0;j<line_trans_pp;j++)
      {
        if ((s1[0]==line_trans_buff[j][0])&&(s1[1]==line_trans_buff[j][1]))
        {
          k=1;
          break;
        }
      }

      if (k==1)
      {
        s2[0]=line_trans_buff[j][2];
        s2[1]=line_trans_buff[j][3];
        s2[2]=line_trans_buff[j][4];
        s2[3]=line_trans_buff[j][5];
        s2[4]=0;

        if (s2[2]==' ') s2[3]=0;
      }
      else strcpy(s2,s1);

      i=i+2;
    }

    strcat(p_str2,s2);
  }

  return(0);
}
/*
int lnx::str_gb18030_to_utf8_ini(void)
{
  cd = iconv_open("utf-8","gb18030//TRANSLIT");  
}

int lnx::str_gb18030_to_utf8(char *inbuffer,char *outbuffer,int outbufferlen)
{
    int i;

    for (i=0;i<outbufferlen;i++) outbuffer[i]=0;

    int inbufferlen = strlen(inbuffer);   
    char* inbuffertmp  = inbuffer;  
    char* outbuffertmp = outbuffer;
    size_t ret = iconv(cd, &inbuffertmp, (size_t *)&inbufferlen, &outbuffertmp, (size_t *)&outbufferlen);  

    return(0);  
}

int lnx::str_gb18030_to_utf8_close(void)
{
    iconv_close(cd);  
}
*/





int lnx::cpy_string(char *p_s1,int p_s1_size,char *p_s2,int p_s2_size)
{
  int i;

  p_s1[0]=0;

  for (i=0;i<p_s2_size;i++)
  {
    if (i+1>=p_s1_size) continue;
    else
    {
      if (p_s2[i]==0) break;
      else
      {
        p_s1[i+0]=p_s2[i];
        p_s1[i+1]=0;
      }
    }
  }

  return(0);
}

int lnx::str_gb18030_to_utf8_ini(void)
{
  cd = iconv_open("utf-8","gb18030//TRANSLIT");  
}

static char cmmn08_str1[9000];
static char cmmn08_str2[9000];
static char cmmn08_str3[9000];
  
int lnx::str_gb18030_to_utf8(char *in_buffer,char *out_buffer,int out_buffer_len)
{
    int i,j;
    char* in_buffer_tmp[]= { cmmn08_str1,NULL };
    int in_buffer_tmp_len;   
    char* out_buffer_tmp[]= { cmmn08_str2,cmmn08_str3,NULL };;
    int out_buffer_tmp_len;

    strcpy(cmmn08_str1,in_buffer);  
    in_buffer_tmp_len=strlen(in_buffer);

    j=in_buffer_tmp_len*3+1;
    if (j<1)       j=1;
    if (j>9000) j=9000;

    for (i=0;i<j;i++)
    {
      cmmn08_str2[i]=0;
      cmmn08_str3[i]=0;
    }

    //out_buffer_tmp[] = { cmmn08_str2,cmmn08_str3 };
    out_buffer_tmp_len = 9000;

    iconv(cd, in_buffer_tmp, (size_t *)&in_buffer_tmp_len, out_buffer_tmp, (size_t *)&out_buffer_tmp_len);  

    cpy_string(out_buffer,out_buffer_len,cmmn08_str2,9000);    

    return(0);  
}

int lnx::str_gb18030_to_utf8_close(void)
{
    iconv_close(cd);  
}





int lnx::paint_focus_win_ci(void)
{
  int  i,j,k,l,m,n;
  char str[STRING_SIZE];
  char c1;
  
  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==lnx_focus_pp))
    {
      j=get_lnx_win_ci_buff(i,2)/lnx_xchar;
      k=get_lnx_win_ci_buff(i,3)/lnx_ychar;
      
      gets_lnx_win_ci_topic(i,str);
      l=(int)strlen(str);

      n=get_lnx_win_ci_buff(i,10);
      if (n==1) c1='*';
      else c1=' ';

      for (m=0;m<l;m++)
      {
        if (str[m]==' ')
        {
          str[m]=c1;
          break;
        }
      }

//      printf("paint win ci pp=%d,ci=%s,\n",lnx_focus_pp,str);
      
      for (m=0;m<l;m++)
      {
        set_paint_buff(lnx_focus_pp,k,j+m,str[m]);
      }
    }
  }
  return(0);
}

int lnx::ini_win_ci(void)
{
  int i;
  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    set_lnx_win_ci_buff(i,0,0);
  }
  return(0);
}

int lnx::add_win_ci(char *h1,char *h2,int h3,int h4,int h5,int h6,int h7,int h8,int h9,int h10,int h11,int h12)
{
  int i,j;
  
  //j=(-1);

  
  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if (get_lnx_win_ci_buff(i,0)==0)
    {
      set_lnx_win_ci_buff(i,0 ,1  );
      set_lnx_win_ci_buff(i,1 ,h3 );
      set_lnx_win_ci_buff(i,2 ,h4 );
      set_lnx_win_ci_buff(i,3 ,h5 );
      set_lnx_win_ci_buff(i,4 ,h6 );
      set_lnx_win_ci_buff(i,5 ,h7 );
      set_lnx_win_ci_buff(i,6 ,h8 );
      set_lnx_win_ci_buff(i,7 ,h9 );
      set_lnx_win_ci_buff(i,8 ,h10);
      set_lnx_win_ci_buff(i,9 ,h11);
      set_lnx_win_ci_buff(i,10,h12);

      sets_lnx_win_ci_name(i,h1);
      sets_lnx_win_ci_topic(i,h2);

      //j=0;

      break;
    }
  }
  
  return(i+MAX_WIN_NUM_4LNX+1);
}
      
int lnx::del_win_ci(int pp)
{
  int  i;
  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==pp))
    {
      set_lnx_win_ci_buff(i,0,0);
    }
  }
  return(0);
}

int set_cursor(int pp,int l,int c)
{
  lnx1.set_lnx_cursor(pp,0,l);
  lnx1.set_lnx_cursor(pp,1,c);
  return(0);
}

int lnx::show_cursor(void)
{
  int  i,j;
  int  l,c;
  char str[STRING_SIZE];

  for (i=0;i<LIN_NUM_4LNX;i++)
  {
    for (j=0;j<COL_NUM_4LNX;j++)
    {
      if ((lnx_focus_pp<0)||(lnx_focus_pp>=MAX_WIN_NUM_4LNX)) continue;
      paint_buff2[i][j]=paint_buff[lnx_focus_pp][i][j];
    }
  }

  strcpy(str,"+>+>+>");
  j=(int)strlen(str);

  l=get_lnx_cursor(lnx_focus_pp,0);
  c=get_lnx_cursor(lnx_focus_pp,1);
  
  for (i=0;i<j;i++)
  {
    //if ((lnx_focus_pp<0)||(lnx_focus_pp>=MAX_WIN_NUM_4LNX)) continue;
    if ((l<0)||(l>=LIN_NUM_4LNX)) continue;
    if ((c+i-1<0)||(c+i-1>=COL_NUM_4LNX)) continue;
    paint_buff2[l][c+i-1]=str[i];
  }

  return(0);
}

int lnx::change_win_ci(void)
{
  int  i,j;
  int  l,c;
  char str[STRING_SIZE];

  l=get_lnx_cursor(lnx_focus_pp,0)-1;
  c=get_lnx_cursor(lnx_focus_pp,1)-2;

  i=find_win_ci_by_cur(l,c);

  if (i>=0)

  {
    gets_lnx_win_ci_topic(i,str);

//    printf("find ci=%s,\n",str);

    if (str[0]=='(')
    {
      clear_radio_ci(lnx_focus_pp,str);
      set_lnx_win_ci_buff(i,10,1);
    }
    
    if (str[0]=='[')
    {
      j=get_lnx_win_ci_buff(i,10);

      if (j==1) set_lnx_win_ci_buff(i,10,0);
      else  set_lnx_win_ci_buff(i,10,1);
    }

  }
  return(0);
}

int lnx::clear_radio_ci(int pp,char *s1)
{
  int  i;
  char str[STRING_SIZE];

  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==pp))
    {
      gets_lnx_win_ci_topic(i,str);
      if (strcmp(str,s1)==0)
      {
        set_lnx_win_ci_buff(i,10,0);
      }
    }
  }
  
  return(0);
}

int lnx::find_win_ci_by_cur(int l,int c)
{
  int  i,j,k,m;
  char str[STRING_SIZE];

  m=(-1);
  
  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==lnx_focus_pp))
    {
      j=get_lnx_win_ci_buff(i,2)/lnx_xchar;
      k=get_lnx_win_ci_buff(i,3)/lnx_ychar;

      if ((k==l)&&(j==c))
      {
        m=i;
        break;
      }
      
      if ((k==l)&&(j+1==c))
      {
        m=i;
        break;
      }

      if ((k==l)&&(j-1==c))
      {
        m=i;
        break;
      }

//      printf("find win ci line=%d,%d,c=%d,%d,\n",l,k,c,j);
    }
  }
  return(m);
}

int lnx::find_win_ci_by_string1(char *s1)
{
  int  i,j,k,m;
  char str[STRING_SIZE];

  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==lnx_focus_pp))
    {
      gets_lnx_win_ci_topic(i,str);

//      printf("strncmp %s,%s,\n",s1,str);
      
      if (strncmp(s1,str,2)==0)
      {
        lnx_win_ci_p1=get_lnx_win_ci_buff(i,2)/lnx_xchar-3;
        lnx_win_ci_p2=get_lnx_win_ci_buff(i,3)/lnx_ychar+1;
        break;
      }

    }
  }

  return(0);
}

int lnx::find_win_ci_by_string2(char *s1)
{
  int  i,j,k,m,l;
  char str[STRING_SIZE];
  char  s2[STRING_SIZE];

  strcpy(s2,s1);
  
  i=(int)strlen(s2);
  for (j=i-1;j>=0;j--)
  {
    if ((s2[j]<=' ')&&(s2[j]>0)) s2[j]=0;

    else break;
  }

  strcat(s2," ");
  
  l=(int)strlen(s2);

  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==lnx_focus_pp))
    {
      gets_lnx_win_ci_topic(i,str);

//      printf("strncmp %s,%s,\n",s2,str);

      if (strncmp(s2,str,l)==0)
      {
        lnx_win_ci_p1=get_lnx_win_ci_buff(i,2)/lnx_xchar-3;

        lnx_win_ci_p2=get_lnx_win_ci_buff(i,3)/lnx_ychar+1;
        break;
      }

    }
  }

  return(0);
}

int lnx::find_win_ci_by_string3(char *s1)
{
  int  i,j,k,l,m,n,o,p;
  char str[STRING_SIZE];
  char  s2[STRING_SIZE];

  strcpy(s2,s1);

  i=(int)strlen(s2);
  for (j=i-1;j>=0;j--)
  {
    if ((s2[j]<=' ')&&(s2[j]>0)) s2[j]=0;
    else break;
  }

  strcat(s2," ");

  l=(int)strlen(s2);
  n=0;
  o=0;

  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==lnx_focus_pp))
    {
      gets_lnx_win_ci_topic(i,str);

//      printf("strncmp %s,%s,\n",s2,str);

      if (strncmp(s2,str,l)==0)
      {
        n++;
        if (get_lnx_win_ci_buff(i,10)==1) o=n;
      }

    }
  }

  p=o+1;
  if (p>n) p=1;

  n=0;
  
  for (i=0;i<MAX_WIN_CI_4LNX;i++)
  {
    if ((get_lnx_win_ci_buff(i,0)==1)&&(get_lnx_win_ci_buff(i,6)==lnx_focus_pp))
    {
      gets_lnx_win_ci_topic(i,str);

//      printf("strncmp 2 %s,%s,\n",s2,str);

      if (strncmp(s2,str,l)==0)
      {
        n++;
        if (n==p)
        {
          lnx_win_ci_p1=get_lnx_win_ci_buff(i,2)/lnx_xchar-3;
          lnx_win_ci_p2=get_lnx_win_ci_buff(i,3)/lnx_ychar+1;
          break;
        }
      }

    }
  }

  return(0);
}

int lnx::set_win_focus(int pp)
{
  int  i,j;

  i=pp-1;
  if (i<0) i=MAX_WIN_NUM_4LNX-1;
  
  while (i!=pp)
  {
    if (get_lnx_win_handle_inuse(i)==1)
    {
      lnx_focus_pp=i;
      return(0);
    }
    else
    {
      i--;
      if (i<0) i=MAX_WIN_NUM_4LNX-1;
    }
  }

  return(0);
}

int lnx::last_win_pp(void)
{
  int  i,j;

  i=MAX_WIN_NUM_4LNX-1;

  while (i>=1)
  {
    if (get_lnx_win_handle_inuse(i)==1)
    {
      lnx_focus_pp=i;
      return(0);
    }
    else i--;
  }

  lnx_focus_pp=0;
  return(0);
}

int lnx::dsp_menu(char *p1)
{
  FILE *fp1;
  char  s1[STRING_SIZE];
  char  s2[STRING_SIZE];
  char  s3[STRING_SIZE];
  char  s4[STRING_SIZE];
  char  s5[STRING_SIZE];
  char  s6[STRING_SIZE];
  int   i,j,k,l;
  int   len;

  char  s_menu_buff[50][3000];
  int   s_menu_pp=0;

  for (i=0;i<(int)strlen(p1);i++) p1[i]=upper(p1[i]);
  strcpy(s2,p1);
  strcpy(s3,p1);
  strcat(s2," MENU");
  strcat(s3," END");
  strcpy(s4,"MENUITEM");

//  printf("in dsp menu =%s,\n",s2);
//  printf("in dsp menu =%s,\n",s3);
//  printf("in dsp menu =%s,\n",s4);
  
  fp1=fopen("vc3_make1.rc","r");
  if (fp1==NULL)
  {
    printf("Open file vc3_make1.rc error .\n");
    return(0);
  }

//  printf("open rc file ok,\n");
  
  j=0;
  k=0;
  while (!feof(fp1))
  {
    fgets(s1,STRING_SIZE-3,fp1);

    if (strfind(s1,s2)>=0)
    {
      if (k==0)
      {
        j=1;
      }
    }
    else
    {
      if (strfind(s1,s3)>=0)
      {
        if (j==1)
        {
          k=1;
          j=0;
        }
      }
    }

    if ((j==1)&&(k==0))
    {
      if (strfind(s1,s4)>=0)
      {
         len=(int)strlen(s1);
         dsp_menu_rm_1(s1,len);
         dsp_menu_rm_2(s1,len);
         dsp_menu_add_1(s1,len);
         dsp_menu_cpy(s1,s5,len+1);
         sprintf(s_menu_buff[s_menu_pp],"%s",s5);
		 s_menu_pp++;
      }
    }
  }

  fclose(fp1);

  strcpy(s_menu_buff[s_menu_pp+0],"                    ");
  strcpy(s_menu_buff[s_menu_pp+1],"                    ");

  //printf("aaa\n");

  i=(s_menu_pp+1)/2;
  for (j=0;j<i;j++)
  {
    //printf("%s",s_menu_buff[j]);

    str_gb18030_to_utf8_ini();

    //printf("bbb\n");

    str_gb18030_to_utf8(s_menu_buff[j],s6,STRING_SIZE);

    //printf("ccc\n");

    str_gb18030_to_utf8_close();

    //printf("ddd\n");

    printf("%s",s6);

    printf("          ");

    //printf("%s\n",s_menu_buff[j+i]);

    str_gb18030_to_utf8_ini();
    str_gb18030_to_utf8(s_menu_buff[j+i],s6,STRING_SIZE);
    str_gb18030_to_utf8_close();

    printf("%s\n",s6);

  }

  return(0);
}

int lnx::dsp_menu_rm_1(char *s1,int len)
{
  int i,j,k;
  k=0;
  i=len;
  for (j=0;j<i-8;j++)
  {
    if ((s1[j+0]=='M')&&
        (s1[j+1]=='E')&&
        (s1[j+2]=='N')&&
        (s1[j+3]=='U'))
    {
      k=1;
      break;
    }
  }
  if (k==1)
  {
    s1[j+0]=0;
    s1[j+1]=0;
    s1[j+2]=0;
    s1[j+3]=0;
    s1[j+4]=0;
    s1[j+5]=0;
    s1[j+6]=0;
    s1[j+7]=0;
  }
  return(0);
}

int lnx::dsp_menu_rm_2(char *s1,int len)
{
  int i,j,k;
  k=0;
  i=len;
  for (j=0;j<i;j++)
  {
    if (s1[j]=='&')
    {
      //k=1;
      //break;
		s1[j]=0;
    }
	if ((s1[j]>0)&&(s1[j]<' '))
	{
		s1[j]=0;
	}
  }
  //if (k==1)
  //{
   // s1[j]=0;
  //}
  return(0);
}

int lnx::dsp_menu_add_1(char *s1,int len)
{
  int i,j,k,l;
  k=0;
  i=len;
  for (j=0;j<i-3;j++)
  {
    if ((s1[j+0]<=' ')&&(s1[j+0]>0)&&
        (s1[j+1]>='0')&&(s1[j+1]<='9')&&
        (s1[j+2]>='0')&&(s1[j+2]<='9'))
    {
      k=1;
      break;
    }
  }
  if (k==1)
  {
    for (l=len-1;l>=j+1;l--)
    {
      s1[l+1]=s1[l];
    }
    s1[j+1]='m';
  }
  return(0);
}

int lnx::dsp_menu_cpy(char *s1,char *s5,int len)
{
  int i,j,k;
  i=0;
  for (j=0;j<len;j++)
  {
    if (s1[j]!=0)
    {
      s5[i+0]=s1[j];
      s5[i+1]=0;
      i++;
    }
  }
  return(0);
}

int lnx::strfind(const char *p1,const char *p2)
{
  int i,j;
  int len1,len2;
  int state;
  len1=(int)strlen(p1);
  len2=(int)strlen(p2);
  state=1;
  for (i=1;i<=len1-len2+1;i++)
  {
    state=0;
    for (j=1;j<=len2;j++)
    {
      if (p1[i-1+j-1]!=p2[j-1])
      {
        state=1;
        break;
      }
    }
    if (state==0) break;
  }
  if (state==1) return(-1);
  else return(i-1);
}

int lnx::upper(char c1)
{
  if ((c1>='a')&&(c1<='z')) return((c1-'a'+'A'));
  else return(c1);
}

int set_win_ci_text(char *v1)
{
  strcpy(lnx_win_ci_text,v1);
  return(0);
}

int get_win_ci_text(char *v1)
{
  strcpy(v1,lnx_win_ci_text);
  return(0);
}

int   GetDC(int h1)
{
  return(h1);
}

int   TextOut(int h1,int h2,int h3,char *h4,int h5)
{
  int i,j;
  int line,col;

  line=(int)(h3/30);
  col =(int)(h2/25);
  j=(int)strlen(h4);
  if (h5<j) j=h5;

  for (i=0;i<j;i++)
  {
    lnx1.set_paint_buff(h1,line,col+i,h4[i]);
  }

  return(0);
}
int   ReleaseDC(int h1,int h2)
{
  return(0);
}
int   GetStockObject(int h1)
{
  return(0);
}
int   SelectObject(int h1,int h2)
{
  return(0);
}
int   HideCaret(int h1)
{
  return(0);
}
int   ShowCaret(int h1)
{
  return(0);
}
int   SetWindowText(int h1,char *h2)
{
  return(0);  
}
int   SetFocus(int h1)
{
//  if ((h1>=0)&&(h1<MAX_WIN_NUM_4LNX))
//  {
//    lnx_focus_pp=h1;
//  }
  return(0);
}
int   GetFocus(void)
{
//  return(lnx_focus_pp);
  return(0);
}
int   CreateWindow(char *h1,char *h2,int h3,int h4,int h5,int h6,int h7,int h8,int h9,int h10,int h11)
{
  int  i;

  if ((h3&WS_CHILD)==0)
  {
  
    i=lnx1.add_win_handle(h1,h2);

    if (i>=0)
    {
      //step1 add WM_CREATE & WM_PAINT to message pipe
      SendMessage(i,WM_CREATE,0,0);
      SendMessage(i,WM_PAINT,0,0);
    
      //step2 set focus window
      lnx1.lnx_focus_pp=i;

//      printf("createwindow lnx_focus_pp=%d,\n",lnx1.lnx_focus_pp);
    }
  }
  else
  {
    i=MAX_WIN_NUM_4LNX+1;

    if ((h3&BS_PUSHBUTTON)==BS_PUSHBUTTON)
    {
       i=lnx1.add_win_ci(h1,h2,BS_PUSHBUTTON,h4,h5,h6,h7,h8,h9,h10,h11,0);

//       printf("create button topic=%s, pp=%d,\n",h2,h8);
    }
    if ((h3&BS_RADIOBUTTON)==BS_RADIOBUTTON)
    {
       i=lnx1.add_win_ci(h1,h2,BS_RADIOBUTTON,h4,h5,h6,h7,h8,h9,h10,h11,0);

//       printf("create radio topic=%s, pp=%d,\n",h2,h8);
    }
    if ((h3&BS_CHECKBOX)==BS_CHECKBOX)
    {
       i=lnx1.add_win_ci(h1,h2,BS_CHECKBOX,h4,h5,h6,h7,h8,h9,h10,h11,0);

//       printf("create check topic=%s, pp=%d,\n",h2,h8);
    }
  }
  
  return(i);
}

int   GetClientRect(int h1,int *h2)
{
  return(0);
}

int   SendMessage(int h1,int h2,int h3,int h4)
{
  lnx1.add_msg_to_pipe(h1,h2,h3,h4);
  return(0);
}
int   MoveWindow(int h1,int h2,int h3,int h4,int h5,int h6)
{
  return(0);
}
int   GetWindowText(int h1,char *h2,int h3)
{
  return(0);
}
int   GetWindowTextLength(int h1)
{
  return(0);
}
int   DestroyWindow(int h1)
{
  if ((h1>=0)&&(h1<MAX_WIN_NUM_4LNX))
  {
    lnx1.set_lnx_win_handle_inuse(h1,0);
    lnx1.del_win_ci(h1);
    lnx1.last_win_pp();
  }
  return(0);
}
int   DefWindowProc(int h1,int h2,int h3,int h4)
{
  return(0);
}
int   SetCaretPos(int h1,int h2)
{
  return(0);
}
int   SetTimer(int h1,int h2,int h3,int h4)
{
  return(0);
}
int   KillTimer(int hwnd,int id)
{
  return(0);
}
int   CreateCaret(int h1,int h2,int h3,int h4)
{
  return(0);
}
int   InvalidateRect(int h1,int h2,int h3)
{
  return(0);
}
int   LoadCursor(int h1,int h2)
{
  return(0);
}
int   SetCursor(int h1)
{
  return(0);
}
int   GetWindowLong(int h1,int h2)
{
  return(0);
}
int   CallWindowProc(int h1,int h2,int h3,int h4,int h5)
{
  return(0);
}
int   LoadMenu(int h1,char *h2)
{
  return(0);
}
int   GetWindowRect(int h1,int h2)
{
  return(0);
}
int   DrawFocusRect(int h1,int h2)
{
  return(0);
}
int   IsZoomed(int h1)
{
  return(0);
}
int   IsIconic(int h1)
{
  return(0);
}
int   MessageBox(int h1,const char *h2,const char *h3,int h4)
{
  char s1[STRING_SIZE];
  int  s2;
  char str1[300];
  char str2[300];

  while (1)
  {

    if (h4==MB_OK)
    {
      strcpy(s1,"a--OK,");
      s2=1;
    }
  
    if (h4==MB_OKCANCEL)
    {
      strcpy(s1,"a--OK,b--CANCEL,");
      s2=2;
    }
    
    if (h4==MB_YESNO)
    {
      strcpy(s1,"a--YES,b--NO,");
      s2=2;
    }

    if (h4==MB_RETRYCANCEL)
    {
      strcpy(s1,"a--RETRY,b--CANCEL,");
      s2=2;
    }
  
  
    if (h4==MB_YESNOCANCEL)
    {
      strcpy(s1,"a--YES,b--NO,c--CANCEL,");
      s2=3;
    }

    sprintf(str1," Message Box \n Topic=%s, \n Content=%s, \n %s, \n Please press one key and enter ...",h3,h2,s1);

    lnx1.str_gb18030_to_utf8_ini();
    lnx1.str_gb18030_to_utf8(str1,str2,300);
    lnx1.str_gb18030_to_utf8_close();

    printf("%s",str2);

    s1[0]=0;
    scanf("%1s",s1);
    printf("\n");
    printf("\n");
  
    if (h4==MB_OK)
    {
      if (s1[0]=='a') return(IDOK);
    }

    if (h4==MB_OKCANCEL)
    {
      if (s1[0]=='a') return(IDOK);
      if (s1[0]=='b') return(IDCANCEL);
    }

    if (h4==MB_YESNO)
    {
      if (s1[0]=='a') return(IDYES);
      if (s1[0]=='b') return(IDNO);
    }

    if (h4==MB_RETRYCANCEL)
    {
      if (s1[0]=='a') return(IDRETRY);
      if (s1[0]=='b') return(IDCANCEL);
    }

    if (h4==MB_YESNOCANCEL)
    {
      if (s1[0]=='a') return(IDYES);
      if (s1[0]=='b') return(IDNO);
      if (s1[0]=='c') return(IDCANCEL);
    }
  }
}

int   GetMessage(int *n1,int n2,int n3,int n4)
{
  char str[STRING_SIZE];
  char str2[STRING_SIZE];
  char str3[STRING_SIZE];
  int  i;

  //printf("111\n");

  lnx1.exec_msg();

  //printf("222\n");

  lnx1.gets_lnx_win_handle_menu(lnx1.lnx_focus_pp,str);
  
  //printf("333\n");

  lnx1.dsp_menu(str);

  //printf("444\n");

  SendMessage(lnx1.lnx_focus_pp,WM_PROGRAM3,0,0);
  
  lnx1.exec_msg();

  //printf("555\n");

  lnx1.paint_focus_win_ci();

//  lnx1.pre_paint_focus_win();
  
  //printf("666\n");

  lnx1.show_cursor();

  //printf("777\n");

  lnx1.paint_focus_win();
  
  //printf("888\n");

  if (lnx1.lnx_exit==1) return(0);

  if (lnx1.lnx_lang==1)
  {
    printf("(s)SwtWin,(m1234)MnuCmd,(t1234)InputText,(r)RghtFld,(l)LftFld\n");
    printf("(u)UpFld,(d)DwnFld,(c)ClickOnItem,PleaseInputCommand:");
  }
  else
  {
    //printf("(s)切换窗口,(m1234)菜单命令,(t1234)输入文本,(r)光标右移,(l)光标左移\n");

    strcpy(str2,"(s)切换窗口,(m1234)菜单命令,(t1234)输入文本,(r)光标右移,(l)光标左移");

    lnx1.str_gb18030_to_utf8_ini();
    lnx1.str_gb18030_to_utf8(str2,str3,STRING_SIZE);
    lnx1.str_gb18030_to_utf8_close();

    printf("%s\n",str3);

    //printf("(u)光标上移,(d)光标下移,(c)点击对象,请输入命令:");

    strcpy(str2,"(u)光标上移,(d)光标下移,(c)点击对象,请输入命令:");

    lnx1.str_gb18030_to_utf8_ini();
    lnx1.str_gb18030_to_utf8(str2,str3,STRING_SIZE);
    lnx1.str_gb18030_to_utf8_close();

    printf("%s\n",str3);

  }
  
  //printf("999\n");

  //strcpy(lnx1.lnx_msg,"");
  for (i=0;i<STRING_SIZE;i++) lnx1.lnx_msg[i]=0;  

  //scanf("%500s",lnx1.lnx_msg);

  scanf("%500s",str2);

  lnx1.str_utf8_to_gb18030_ini();
  lnx1.str_utf8_to_gb18030(str2,str3,STRING_SIZE);
  lnx1.str_utf8_to_gb18030_close();

  strcpy(lnx1.lnx_msg,str3);

  //printf("000\n");

  printf("\n");
  printf("\n");

  return(1);
}
/*
int lnx::str_utf8_to_gb18030_ini(void)
{
    cd = iconv_open("gb18030//TRANSLIT", "utf-8");  
    return(0);
}

int lnx::str_utf8_to_gb18030(char *inbuffer,char *outbuffer,int outbufferlen)
{
    int i,j;

    j=(int)strlen(inbuffer);
    if (j<10) j=10;
    j=j+10;

    for (i=0;i<j;i++) outbuffer[i]=0;

    int inbufferlen = strlen(inbuffer);   
    char* inbuffertmp  = inbuffer;  
    char* outbuffertmp = outbuffer;
    size_t ret = iconv(cd, &inbuffertmp, (size_t *)&inbufferlen, &outbuffertmp, (size_t *)&outbufferlen);  

    return(0);  
}

int lnx::str_utf8_to_gb18030_close(void)
{
    iconv_close(cd);  
    return(0);
}
*/




int lnx::str_utf8_to_gb18030_ini(void)
{
  cd = iconv_open("gb18030//TRANSLIT","utf-8");  
}

static char cmmn07_str1[9000];
static char cmmn07_str2[9000];
static char cmmn07_str3[9000];
  
int lnx::str_utf8_to_gb18030(char *in_buffer,char *out_buffer,int out_buffer_len)
{
    int i,j;
    char* in_buffer_tmp[]= { cmmn07_str1,NULL };
    int in_buffer_tmp_len;   
    char* out_buffer_tmp[]= { cmmn07_str2,cmmn07_str3,NULL };;
    int out_buffer_tmp_len;

    strcpy(cmmn07_str1,in_buffer);  
    in_buffer_tmp_len=strlen(in_buffer);

    j=in_buffer_tmp_len+1;
    if (j<1)       j=1;
    if (j>9000) j=9000;

    for (i=0;i<j;i++)
    {
      cmmn07_str2[i]=0;
      cmmn07_str3[i]=0;
    }

    //out_buffer_tmp[] = { cmmn07_str2,cmmn07_str3 };
    out_buffer_tmp_len = 9000;

    iconv(cd, in_buffer_tmp, (size_t *)&in_buffer_tmp_len, out_buffer_tmp, (size_t *)&out_buffer_tmp_len);  

    cpy_string(out_buffer,out_buffer_len,cmmn07_str2,9000);    

    return(0);  
}

int lnx::str_utf8_to_gb18030_close(void)
{
    iconv_close(cd);  
}






int   TranslateMessage(int *n1)
{
  int  i,j,k,l,m,n;
  char s1[STRING_SIZE];
  char s2[STRING_SIZE];
  char s3[STRING_SIZE];
  long rl;

  for (i=0;i<STRING_SIZE;i++)
  {
    s1[i]=0;
    s2[i]=0;
    s3[i]=0;
  }

  strcpy(s1,lnx1.lnx_msg);
  i=(int)strlen(s1);
  k=0;
  for (j=0;j<i;j++)
  {
    if (s1[j]!=' ')
    {
       k=1;
       break;
    }
  }

  if (k==0) return(0);

  s3[0]=0;
  
  for (l=j;l<i;l++)
  {
    s3[l-j+0]=s1[l];
    s3[l-j+1]=0;
  }

  if (s3[0]=='s')
  {
    lnx1.set_win_focus(lnx1.lnx_focus_pp);
//    SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);
  }
  
  if (s3[0]=='m')
  {
    i=1;
    while ((s3[i]<='9')&&(s3[i]>='0')&&(i<STRING_SIZE-1))
    {
      i++;
    }


    s2[0]=0;
    for (j=1;j<i;j++)
    {
      s2[j-1]=s3[j];
      s2[j-0]=0;
    }


    k=lnx1.char2int(s2,0,i-1);

    //printf("menu message %d,%d,%d,%d,%d,\n",j,lnx_focus_pp,WM_COMMAND,k,0);
    
    SendMessage(lnx1.lnx_focus_pp,WM_COMMAND,k,0);
//    SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);
  }

  if (s3[0]=='u')
  {
     SendMessage(lnx1.lnx_focus_pp,WM_CHAR ,274,0);
     //SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0  ,0);
  }
  
  if (s3[0]=='d')
  {
     SendMessage(lnx1.lnx_focus_pp,WM_CHAR ,275,0);
     //SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0  ,0);
  }

  if (s3[0]=='l')
  {
     SendMessage(lnx1.lnx_focus_pp,WM_CHAR,276,0);
//     SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);
  }

  if (s3[0]=='r')
  {
     SendMessage(lnx1.lnx_focus_pp,WM_CHAR,277,0);
//     SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);
  }

  if (s3[0]=='c')
  {
     SendMessage(lnx1.lnx_focus_pp,WM_CHAR,32,0);
//     SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);
     lnx1.change_win_ci();
  }

  if (s3[0]=='<')
  {
    lnx1.find_win_ci_by_string1(s3);

    SendMessage(lnx1.lnx_focus_pp,WM_PROGRAM2,lnx_win_ci_p1,lnx_win_ci_p2);

    SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);

    SendMessage(lnx1.lnx_focus_pp,WM_CHAR,32,0);

    //lnx1.change_win_ci();
  }

  if (s3[0]=='[')
  {
    lnx1.find_win_ci_by_string2(s3);

    SendMessage(lnx1.lnx_focus_pp,WM_PROGRAM2,lnx_win_ci_p1,lnx_win_ci_p2);

    SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);

    lnx1.exec_msg();

    SendMessage(lnx1.lnx_focus_pp,WM_CHAR,32,0);

    lnx1.change_win_ci();
  }

  if (s3[0]=='(')
  {
    lnx1.find_win_ci_by_string3(s3);

    SendMessage(lnx1.lnx_focus_pp,WM_PROGRAM2,lnx_win_ci_p1,lnx_win_ci_p2);

    SendMessage(lnx1.lnx_focus_pp,WM_PAINT,0,0);

    lnx1.exec_msg();

    SendMessage(lnx1.lnx_focus_pp,WM_CHAR,32,0);

    lnx1.change_win_ci();
  }

  if (s3[0]=='t')
  {
    i=1;
    while ((s3[i]!=0)&&(i<STRING_SIZE-1))
    {
      i++;
    }

    s2[0]=0;
    for (j=1;j<i;j++)
    {
      s2[j-1]=s3[j];
      s2[j-0]=0;
    }

    set_win_ci_text(s2);
    
    SendMessage(lnx1.lnx_focus_pp,WM_PROGRAM1,0,0);
    
    SendMessage(lnx1.lnx_focus_pp,WM_CHAR,13,0);
  }

  return(0);
}
int   DispatchMessage(int *n1)
{
  return(0);
}


int   chdir(char *fn)
{
  return(0);
}

int   PostQuitMessage(int msg)
{
  lnx1.lnx_exit=1;
  
  return(0);
}

int   LOWORD(int lp)
{
  return(lp);
}

int   HIWORD(int lp)
{
  return(lp);
}

int   chsize(int h1,long h2)
{
  return(0);
}

int   GlobalFree(int n1)
{
  return(0);
}

int   ShowWindow(int n1,int n2)
{
  return(0);
}

int   UpdateWindow(int n1)
{
  return(0);
}

int lnx::set_paint_buff(int p1,int p2,int p3,int v1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  if ((p2<0)||(p2>=LIN_NUM_4LNX)) return(0);
  if ((p3<0)||(p3>=COL_NUM_4LNX)) return(0);
  paint_buff[p1][p2][p3]=v1;
  return(0);
}

int lnx::get_paint_buff(int p1,int p2,int p3)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  if ((p2<0)||(p2>=LIN_NUM_4LNX)) return(0);
  if ((p3<0)||(p3>=COL_NUM_4LNX)) return(0);
  return(paint_buff[p1][p2][p3]);
}

int lnx::sets_lnx_win_class_name(int p1,char *v1)
{
  int i,j;
  
  if ((p1<0)||(p1>=CLASS_NUM)) return(0);

  lnx_win_class_name[p1][0]=0;
  
  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_class_name[p1][j+0]=v1[j];
    lnx_win_class_name[p1][j+1]=0;
  }

  return(0);
}

int lnx::gets_lnx_win_class_name(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=CLASS_NUM)) return(0);


  v1[0]=0;

  i=(int)strlen(lnx_win_class_name[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_class_name[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::sets_lnx_win_class_menu(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=CLASS_NUM)) return(0);

  lnx_win_class_menu[p1][0]=0;

  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_class_menu[p1][j+0]=v1[j];
    lnx_win_class_menu[p1][j+1]=0;
  }

  return(0);
}

int lnx::gets_lnx_win_class_menu(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=CLASS_NUM)) return(0);

  v1[0]=0;

  i=(int)strlen(lnx_win_class_menu[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_class_menu[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::set_lnx_win_class_proc(int p1,int v1)
{
  if ((p1<0)||(p1>=CLASS_NUM)) return(0);
  lnx_win_class_proc[p1]=v1;
  return(0);
}  

int lnx::get_lnx_win_class_proc(int p1)
{
  if ((p1<0)||(p1>=CLASS_NUM)) return(0);
  return(lnx_win_class_proc[p1]);
}


int lnx::gets_lnx_win_handle_name(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);

  v1[0]=0;

  i=(int)strlen(lnx_win_handle_name[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_handle_name[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::gets_lnx_win_handle_menu(int p1,char *v1)
{
  int i,j;


  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);

  v1[0]=0;

  i=(int)strlen(lnx_win_handle_menu[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_handle_menu[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::gets_lnx_win_handle_topic(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);

  v1[0]=0;

  i=(int)strlen(lnx_win_handle_topic[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_handle_topic[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::sets_lnx_win_handle_name(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);

  lnx_win_handle_name[p1][0]=0;

  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_handle_name[p1][j+0]=v1[j];
    lnx_win_handle_name[p1][j+1]=0;
  }

  return(0);
}

int lnx::sets_lnx_win_handle_menu(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);

  lnx_win_handle_menu[p1][0]=0;

  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_handle_menu[p1][j+0]=v1[j];
    lnx_win_handle_menu[p1][j+1]=0;
  }

  return(0);
}

int lnx::sets_lnx_win_handle_topic(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);

  lnx_win_handle_topic[p1][0]=0;

  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_handle_topic[p1][j+0]=v1[j];
    lnx_win_handle_topic[p1][j+1]=0;
  }

  return(0);
}

int lnx::set_lnx_win_handle_proc(int p1,int v1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  lnx_win_handle_proc[p1]=v1;
  return(0);
}

int lnx::set_lnx_win_handle_inuse(int p1,int v1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  lnx_win_handle_inuse[p1]=v1;
  return(0);
}

int lnx::get_lnx_win_handle_proc(int p1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  return(lnx_win_handle_proc[p1]);
}

int lnx::get_lnx_win_handle_inuse(int p1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  return(lnx_win_handle_inuse[p1]);
}
/*
int lnx::set_lnx_win_handle_inuse(int p1,int v1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  lnx_win_handle_inuse[p1]=v1;
  return(0);
}
*/
/*
int lnx::get_lnx_win_handle_inuse(int p1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  return(lnx_win_handle_inuse[p1]);
}
*/
int lnx::set_pipe_buff(int p1,int p2,int v1)
{
  if ((p1<0)||(p1>=PIPE_NUM)) return(0);
  if ((p2<0)||(p2>=4)) return(0);
  pipe_buff[p1][p2]=v1;
  return(0);
}

int lnx::get_pipe_buff(int p1,int p2)
{
  if ((p1<0)||(p1>=PIPE_NUM)) return(0);
  if ((p2<0)||(p2>=4)) return(0);
  return(pipe_buff[p1][p2]);
}

int lnx::set_lnx_win_ci_buff(int p1,int p2,int v1)
{
  if ((p1<0)||(p1>=MAX_WIN_CI_4LNX)) return(0);
  if ((p2<0)||(p2>=11)) return(0);
  lnx_win_ci_buff[p1][p2]=v1;
  return(0);
}

int lnx::get_lnx_win_ci_buff(int p1,int p2)
{
  if ((p1<0)||(p1>=MAX_WIN_CI_4LNX)) return(0);
  if ((p2<0)||(p2>=11)) return(0);
  return(lnx_win_ci_buff[p1][p2]);
}

int lnx::sets_lnx_win_ci_name(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_CI_4LNX)) return(0);

  lnx_win_ci_name[p1][0]=0;

  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_ci_name[p1][j+0]=v1[j];
    lnx_win_ci_name[p1][j+1]=0;
  }

  return(0);
}

int lnx::sets_lnx_win_ci_topic(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_CI_4LNX)) return(0);

  lnx_win_ci_topic[p1][0]=0;

  i=(int)strlen(v1);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    lnx_win_ci_topic[p1][j+0]=v1[j];
    lnx_win_ci_topic[p1][j+1]=0;
  }

  return(0);
}

int lnx::gets_lnx_win_ci_topic(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_CI_4LNX)) return(0);


  v1[0]=0;

  i=(int)strlen(lnx_win_ci_topic[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_ci_topic[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::gets_lnx_win_ci_name(int p1,char *v1)
{
  int i,j;

  if ((p1<0)||(p1>=MAX_WIN_CI_4LNX)) return(0);

  v1[0]=0;

  i=(int)strlen(lnx_win_ci_name[p1]);
  if (i>=STRING_SIZE) i=STRING_SIZE-1;

  for (j=0;j<i;j++)
  {
    v1[j+0]=lnx_win_ci_name[p1][j];
    v1[j+1]=0;
  }

  return(0);
}

int lnx::set_lnx_cursor(int p1,int p2,int v1)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  if ((p2<0)||(p2>=2)) return(0);
  lnx_cursor[p1][p2]=v1;
  return(0);
}

int lnx::get_lnx_cursor(int p1,int p2)
{
  if ((p1<0)||(p1>=MAX_WIN_NUM_4LNX)) return(0);
  if ((p2<0)||(p2>=2)) return(0);
  return(lnx_cursor[p1][p2]);
}

int lnx::char2int(char *string,int p1,int p2)
{
  int val;
  int i;
  int sin;
  int num;
  
  val=0;
  sin=1;
  num=0;
  
  for (i=p1;i<=p2;i++)
  {
   if (*(string+i)<=' ') continue;
   if (*(string+i)=='-')
   {
     if (num==0)
     {
       sin= -1;
       continue;
     }
     else
     {
       val=0;
       break;
     }
   }
   if (*(string+i)=='+')
   {
     if (num==0)
     {
       sin=1;
       continue;
     }
     else
     {
       val=0;
       break;
     }
   }
   if ((*(string+i)>='0')&&(*(string+i)<='9'))
   {
     num=1;
     val=val*10+(*(string+i)-48)*sin;
     continue;
   }
   val=0;
   break;
  }
  return(val);
}

int lnx::get_setup()
{
  int  exist;
  int  i,j,k;
  int  p1,p2;
  int  tn1;
  int  tn2;
  char tc1[STRING_SIZE];
  char tc2[20][20];
  char tc3[20][20];
  char tc4[STRING_SIZE];
  char tc5[STRING_SIZE];
  char tc6[STRING_SIZE];
  char tc7[STRING_SIZE];
  FILE *s_fp1;

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
    return(1);
  }

  while (!feof(s_fp1))
  {
    fgets(tc1,STRING_SIZE,s_fp1);
    strtrim(tc1);
    for (i=0;i<(int)strlen(tc1);i++) tc1[i]=upper(tc1[i]);
    i=strfind(tc1,"=");
    if (i>=0)
    {
      strpcut(tc1,0,i,tc4);
      strpcut(tc1,i+1,strlen(tc1)-i-1,tc5);
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
/*
    if (p1==0)
    {
      if ((bw_inkey1.upper(tc5[0])=='1')||(bw_inkey1.upper(tc5[0])=='Y')||(bw_inkey1.upper(tc5[0])=='T'))
      {
        win_color=1;
      }
      else win_color=0;
    }

    if (p1==4)
    {
      if ((bw_inkey1.upper(tc5[0])=='1')||(bw_inkey1.upper(tc5[0])=='Y')||(bw_inkey1.upper(tc5[0])=='T'))
      {
        win_pwd_mrk=1;
      }
      else win_pwd_mrk=0;
    }

    if (p1==5)
    {
      strcpy(win_home_dir,tc5);
    }

    if (p1==11)
    {
      strcpy(win_well_dir,tc5);
    }

    if (p1==2)
    {
      if ((bw_inkey1.upper(tc5[0])=='1')||(bw_inkey1.upper(tc5[0])=='Y')||(bw_inkey1.upper(tc5[0])=='T'))
      {
        win_confirm=1;
      }
      else win_confirm=0;
    }

    if (p1==1)
    {
      win_print=0;
      if ((p2==1)||(p2==4)||(p2==5)||(p2==6)||(p2==7))
      {
        win_print=1;
      }
    }

    if (p1==3)
    {
      win_page_size=66;
      p2=bw_inkey1.char2int(tc5,0,strlen(tc5)-1);
      if (p2>0) win_page_size=p2;
    }

    if (p1==6)
    {
      i=bw_inkey1.strlocc(tc5,',');
      bw_inkey1.strpcut(tc5,0,i,tc6);
      bw_inkey1.strpcut(tc5,i+1,strlen(tc5)-i-1,tc7);
      win_main_xsize=bw_inkey1.char2int(tc6,0,strlen(tc6)-1);
      win_main_ysize=bw_inkey1.char2int(tc7,0,strlen(tc7)-1);
    }

    if (p1==7)
    {
      i=bw_inkey1.strlocc(tc5,',');
      bw_inkey1.strpcut(tc5,0,i,tc6);
      bw_inkey1.strpcut(tc5,i+1,strlen(tc5)-i-1,tc7);
      win_main_xposi=bw_inkey1.char2int(tc6,0,strlen(tc6)-1);
      win_main_yposi=bw_inkey1.char2int(tc7,0,strlen(tc7)-1);
    }
*/

    if (p1==8)
    {
      if (p2==8) lnx_lang=1;
      else lnx_lang=0;
    }
/*
    if (p1==9)
    {
      if (p2==9) win_800=1;
    }

    if (p1==10)
    {
      if (p2==10) win_ibm_s3=1;
    }
*/
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

int lnx::strtrim(char *str)
{
  int i;
  for (i=strlen(str)-1;i>=0;i--)
  {
    if ((str[i]>' ')||(str[i]<0)) break;
    else str[i]=0;
  }
  return(0);
}

int lnx::strpcut(char *s1,int p1,int p2,char *s2)
{
  int i;
  for (i=p1;i<=p1+p2-1;i++) s2[i-p1]=s1[i];
  s2[i-p1]=0;
  return(1);
}
