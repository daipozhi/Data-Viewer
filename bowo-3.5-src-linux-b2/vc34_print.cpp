/*
#define   STRICT
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

//int       win_tst1;

int bw_print::w_open_print(char *p_s1,int p_s1_size)
{
  char s2[FN_SIZE];
  //char s_fn4[FN_SIZE];
  int  i,j;

  strcpy(s2,p_s1);
  i=bw_inkey1.strlocc(s2,FN_SIZE,'.');
  s2[i]=0;
  strcat(s2,".txt");
  ts_fp1=fopen(s2,"w");
  if (ts_fp1==NULL) return(1);
  else return(0);
}
int bw_print::w_close_print(void)
{
  fclose(ts_fp1);
  return(0);
}
int bw_print::w_read_page(char *p_fn2,int p_fn2_size,int page)
{
  FILE *s_fp1;
  int  p1,p2,p8,same,ends;
  int  state1,state2,state3;
  int  state4,state5,state6;
  char tmpc2[PAGE_COLU];
  char s3[FN_SIZE];
  //char s_fn4[FN_SIZE];
  int  i,j,n;
  int  lcnt,cmd;
//  int  scrn_type;
//  int  read_type;

  strcpy(texts1,"usetable= ");
  strcpy(texts2,"enddefine ");
  strcpy(texts3,"screenseg ");
  strcpy(texts4,"endscreen ");
  strcpy(texts5,"readvatype");
  strcpy(texts6,"findfile= ");
  strcpy(texts7,"findbase= ");
  strcpy(texts8,"switchbmp ");

  strcpy(s3,p_fn2);
  bw_inkey1.strtrim(s3,FN_SIZE);
  i=bw_inkey1.strlocc(s3,FN_SIZE,'.');
  if (i<0) i=strlen(s3);
  s3[i]=0;
  strcat(s3,".sc0");

  s_fp1=fopen(s3,"r");    /* fetch page of screen format from screen file */
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1(s3);
    return(1);
  }

  p8=page;
  while (p8>1)
  {
    fgets(tmpc2,PAGE_COLU,s_fp1);
    if (feof(s_fp1)) break;
    if (strncmp(tmpc2,"&screenseg",10)==0) p8--;
    if (strncmp(tmpc2,"&pageseg",8)==0) p8--;
  }

  if (feof(s_fp1))
  {  
    fclose(s_fp1);
    return(1);
  }

  for (i=1;i<PAGE_LINE;i++) for (j=1;j<PAGE_COLU;j++) set_t6_pagefile(i,j,' ');
  lcnt=0;
  for (i=1;i<PAGE_LINE+10;i++)
  {
    cmd=0;
    for (n=0;n<PAGE_COLU;n++) tmpc2[n]=' ';
    fgets(tmpc2,PAGE_COLU,s_fp1);
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
      for (j=j;j<PAGE_COLU;j++) if (tmpc2[j]=='&') break; /* locate for '&' */
      j++;
      p1=j;
      if (p1>=PAGE_COLU) break;

      // find findbase name
      same=1;
      for (p2=p1;p2<=p1+9-1;p2++)  
      {
	if (texts6[p2-p1]==' ') break;
	if (tmpc2[p2]!=texts6[p2-p1])
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
      for (p2=p1;p2<=p1+9-1;p2++)  /* recnigze keywords */
      {
	if (texts1[p2-p1]==' ') break;
	if (tmpc2[p2]!=texts1[p2-p1])
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
      for (p2=p1;p2<=p1+10-1;p2++)  /* recnigze keywords */
      {
	if (texts5[p2-p1]==' ') break;
	if (tmpc2[p2]!=texts5[p2-p1])
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
      for (p2=p1;p2<=p1+10-1;p2++)
      {
	if (texts2[p2-p1]==' ') break;
	if (tmpc2[p2]!=texts2[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state2=1; /* enddefine */

      same=1;
      for (p2=p1;p2<=p1+10-1;p2++)
      {
	if (texts3[p2-p1]==' ') break;
	if (tmpc2[p2]!=texts3[p2-p1])
	{
	  same=0;
	  break;
	}
      }
      if (same==1) state3=1;  /* screenseg */

      same=1;
      for (p2=p1;p2<=p1+10-1;p2++)
      {
	if (texts4[p2-p1]==' ') break;
	if (tmpc2[p2]!=texts4[p2-p1])
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
      if ((tmpc2[j]<' ')&&(tmpc2[j]>=0)) tmpc2[j]=' ';
      set_t6_pagefile(lcnt,j,tmpc2[j]);
    }

    if (feof(s_fp1))
    {
      ends=1;
      break;
    }
  }

  fclose(s_fp1);

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
    get_t6s_pagefile(i,str,SMG_SIZE);

    TextOut(hdc,0,i*20,str,70);
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_print::w_page_field1()
{
  int  p1,p2,p3,p4,p5,p6;
  int  state1;
//  int  state4;
  int  i,j;
  int  pp1;

  pp1=0;

  for (i=0;i<FLD_IN_PAGE;i++)
  {
    set_t6_linecol(i,0,0);
    set_t6_linecol(i,1,0);
    set_t6_linecol(i,2,0);
  }

  for (i=1;i<PAGE_LINE;i++)
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
	if (p5==1) set_t6_fldlen(pp1,j-1-p6);
	pp1++;
	if (get_t6_pagefile(i,j+1)=='#')
	{
	  set_t6_linecol(pp1,0,i);
	  set_t6_linecol(pp1,1,j+1);
	  set_t6_linecol(pp1,2,pp1);
	}
	else
	{
	  set_t6_linecol(pp1,0,i);
	  set_t6_linecol(pp1,1,j);
	  set_t6_linecol(pp1,2,pp1);
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
	      set_t6_fldlen(pp1,j-p6);
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
	      set_t6c_fldname(pp1,p4,'%');
	      p4++;
	    }
	    set_t6c_fldname(pp1,p4+0,get_t6_pagefile(i,j));
	    set_t6c_fldname(pp1,p4+1,0);
	    set_t6_fldtype(pp1,'c');
	    p4++;
	  }
	  else
	  {
	    if (p5==1)
	    {
	      set_t6_fldlen(pp1,j-p6);
	      p5=0;
	    }
	  }
	}
      }
    }
  }
  t6_pp1=pp1;

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

int bw_print::w_page_field2(int wpp)
{
  int  i,k,l,m;
  int  pp1;
  int  exist;
  int  basep;
  char c1[SMG_SIZE];
  char c2[SMG_SIZE];
//  char ts_tmpc1[SMG_SIZE];
  char ts_fldtable[SMG_SIZE];
  char ts_fldname[SMG_SIZE];
  long ts_fldrecno;
  char ts_tmpc2[SMG_SIZE];
  char ts_tmpc3[SMG_SIZE];
  int  ts_tmpn1;
  char sfn[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp_wins_dbf(i,wpp)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==1) basep=i;
  else return(1);

  for (i=0;i<=FLD_IN_PAGE-1;i++)
  {
    set_t6_fldbase(i,0);
    set_t6_fldedit(i,0);
    set_t6_fldseri(i,0);
  }
		      
  for (i=0;i<=FLD_IN_SCRN-1;i++) set_ts_fldseri(i,0);

  pp1=basep; /* default base point  */

  for (k=0;k<=t6_pp1;k++)
  {
    i=get_t6_linecol(k,0);

    ts_fldtable[0]=0;
    ts_fldrecno=0;
    ts_fldname[0]=0;

    get_t6_fldname(k,sfn,SMG_SIZE);

    if ((bw_win1.w_field_type(sfn)==6)
      ||(bw_win1.w_field_type(sfn)==7)
      ||(bw_win1.w_field_type(sfn)==8))
    {
      c1[0]=get_t6c_fldname(k,0);
      c1[1]=0;

      get_t6_fldname(k,ts_tmpc2,SMG_SIZE);

      if (ts_tmpc2[0]=='%')
      {
	ts_tmpn1=1; /* read field */
	bw_inkey1.strpcut(ts_tmpc2,1,strlen(ts_tmpc2)-1,SMG_SIZE,ts_tmpc3,SMG_SIZE);
      }
      else
      {
	ts_tmpn1=0; /* edit field */
	bw_inkey1.strpcut(ts_tmpc2,1,strlen(ts_tmpc2)-1,SMG_SIZE,ts_tmpc3,SMG_SIZE);
      }

      bw_win1.w_fetch_fld_style(ts_tmpc3,SMG_SIZE
                   ,ts_fldtable,SMG_SIZE
		   ,&ts_fldrecno
		   ,ts_fldname,SMG_SIZE
		   ,wpp);

      if ((bw_inkey1.strempty(ts_fldtable)==0)
	&&(bw_inkey1.strempty(ts_fldname)==0))
      {
	set_t6_fldname(k,ts_tmpc2,SMG_SIZE);
      }
      else
      {
	strcpy(c2,c1);
        strcat(c2,ts_fldname);
	set_t6_fldname(k,c2,SMG_SIZE);
      }

      pp1=bw_win1.w_fld_set_base(ts_fldtable,SMG_SIZE,pp1,wpp);
      set_t6_fldbase(k,pp1);

      if (bw_inkey1.strempty(ts_fldname)==0)
      {
	set_t6_fldseri(k,1);
	set_t6_fldedit(k,1);
	continue;
      }

      l=0;
      for (m=k-1;m>0;m--)
      {
        get_ts_field(m,sfn,SMG_SIZE);

	if ((strcmp(ts_fldname,sfn)==0)
	  &&(pp1==get_t6_fldbase(m))
	  &&(ts_fldrecno==0))
	{
	  l=1;
          set_ts_fldseri(m,get_ts_fldseri(m)+1);
	  set_t6_fldseri(k,get_ts_fldseri(m));
	}
      }

      if (l==1) set_ts_fieldc(k,0,0);
      else
      {
	set_ts_field(k,ts_fldname,10);
	set_ts_fldseri(k,get_ts_fldseri(k)+1);
	set_t6_fldseri(k,get_ts_fldseri(k));
      }

      if (ts_tmpn1==1)
	set_t6_fldedit(k,1);
      else
	set_t6_fldedit(k,w_fld_set_edit(ts_fldname,SMG_SIZE));

    }
  }

  return(0);
}

int bw_print::w_fld_set_edit(char *p_fldname,int p_fldname_size)
{
//  int i,j;
  //char s_fn4[SMG_SIZE];

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
  ts_fp2[j]=fopen(s2,"r");
  if (ts_fp2[j]==NULL) return(1);
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

  if (feof(ts_fp2[m5])) return(1);
  else
  {
    fgets(tc1,SMG_SIZE,ts_fp2[m5]);

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
    if (i-win_memo_left>=j) set_t6_tmpc2(l,i,' ');
    else set_t6_tmpc2(l,i,p_s1[i-win_memo_left]);
  }
  return(0);
}
int bw_print::w_close_memo_print(int m5)
{
  fclose(ts_fp2[m5]);
  return(0);
}
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

long  /*PASCAL*/ w_savep_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
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
/*
      hdc=GetDC(hwnd);
      GetTextMetrics(hdc,&tm);
      bw_print1.win_print_xchar=tm.tmAveCharWidth;
      bw_print1.win_print_ychar=tm.tmHeight+tm.tmExternalLeading;
      ReleaseDC(hwnd,hdc);
*/
      bw_print1.win_print_xchar=25;
      bw_print1.win_print_ychar=30;
/*
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
*/
      break;

    case WM_PAINT:

     //bw_print1.w_print_echo1(hwnd);

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
	    if ((bw_print1.get_t6_tmpc2(i,j)<' ')&&(bw_print1.get_t6_tmpc2(i,j)>=0)) bw_print1.set_t6_tmpc2(i,j,' ');
	  }

	  exist=0;

          for (j=PAGE_COLU-1;j>=0;j--)
          {
	    if ((bw_print1.get_t6_tmpc2(i,j)>' ')||(bw_print1.get_t6_tmpc2(i,j)<0))
	    {
	      bw_print1.set_t6_tmpc2(i,j+1,0);
	      exist=1;
	      break;
	    }
          }

	  if (exist==0) bw_print1.set_t6_tmpc2(i,0,0);

          bw_print1.get_t6s_tmpc2(i,sfn,SMG_SIZE);
          fputs(sfn,bw_print1.ts_fp1);
          fputs("\n",bw_print1.ts_fp1);
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

int bw_print::w_save_memo()
{
  int  i,j;
  int  exist;
  char sfn[SMG_SIZE];

  for (i=1;i<=bw_main1.win_page_size;i++)
  {
    for (j=0;j<PAGE_COLU;j++)
      if ((get_t6_tmpc2(i,j)<' ')&&(get_t6_tmpc2(i,j)>=0)) set_t6_tmpc2(i,j,' ');

    exist=0;

    for (j=PAGE_COLU-1;j>=0;j--)
    {
      if ((get_t6_tmpc2(i,j)>' ')||(get_t6_tmpc2(i,j)<0))
      {
	set_t6_tmpc2(i,j+1,0);
	exist=1;
	break;
      }
    }

    if (exist==0) set_t6_tmpc2(i,0,0);

    get_t6s_tmpc2(i,sfn,SMG_SIZE);
    fputs(sfn,ts_fp1);
    fputs("\n",ts_fp1);
  }
  return(0);
}

int bw_print::w_out_print(char *p_s1,int p_s1_size)
{
  int  i,j;
//  int  pp1;
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

long  /*PASCAL*/ w_outp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
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
/*
      hdc=GetDC(hwnd);
      GetTextMetrics(hdc,&tm);
      bw_print1.win_print_xchar=tm.tmAveCharWidth;
      bw_print1.win_print_ychar=tm.tmHeight+tm.tmExternalLeading;
      ReleaseDC(hwnd,hdc);
*/
      bw_print1.win_print_xchar=25;
      bw_print1.win_print_ychar=30;

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

      //bw_print1.w_print_echo2(hwnd);

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
	bw_print1.w_out_wprint();
      }
      if (wp==1053)
      {
	bw_print1.win_page_num--;
        bw_print1.w_out_wprint();
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
            bw_print1.w_out_wprint();
          }
          if (bw_print1.p2==2)
          {
            bw_print1.win_page_num--;
            bw_print1.w_out_wprint();
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
        bw_print1.w_out_wprint();
      }

      if ((wp==1753)||(wp==303))
      {
        bw_print1.win_page_num--;
        bw_print1.w_out_wprint();
      }

      bw_print1.w_print_echo2(hwnd);

    }
  }
  return DefWindowProc(hwnd,msg,wp,lp);
}

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

int bw_print::w_out_wprint()
{
/*
  int  exist;
  int  i,j;
//  int  pp1,pp2;
  char s1[SMG_SIZE];
  char s2[SMG_SIZE];
  char ssd[SMG_SIZE];
  char sdev[SMG_SIZE];
  char sdri[SMG_SIZE];
  char sport[SMG_SIZE];

  FILE       *s_fp2;
  HDC        hdc;
  TEXTMETRIC tm;

  get_win_print_fname(s2,SMG_SIZE);

  i=bw_inkey1.strlocc(s2,SMG_SIZE,'.');
  s2[i]=0;
  strcat(s2,".txt");
  s_fp2=fopen(s2,"r");
  if (s_fp2==NULL)
  {
    bw_win1.w_atten1(s2);
    return(1);
  }

  if (win_page_num>1)
  {
    for (i=1;i<=(win_page_num-1)*bw_main1.win_page_size;i++)
    {
      fgets(s1,SMG_SIZE,s_fp2);
      if (feof(s_fp2))
      {
	fclose(s_fp2);
	return(1);
      }
    }
  }

  GetProfileString("windows","device",",,,",ssd,SMG_SIZE);

  for (i=0;i<(int)strlen(ssd);i++)
  {
    if (ssd[i]==',') break;
  }
  bw_inkey1.strpcut(ssd,0,i,SMG_SIZE,sdev,SMG_SIZE);
  sdev[i]=0;

  j=i+1;
  for (i=j;i<(int)strlen(ssd);i++)
  {
    if (ssd[i]==',') break;
  }
  bw_inkey1.strpcut(ssd,j,i-j,SMG_SIZE,sdri,SMG_SIZE);
  sdri[i-j]=0;

  j=i+1;
  for (i=j;i<(int)strlen(ssd);i++)
  {
    if (ssd[i]==',') break;
  }
  bw_inkey1.strpcut(ssd,j,strlen(ssd)-j,SMG_SIZE,sport,SMG_SIZE);
  sport[strlen(ssd)-j]=0;

  hdc=CreateDC(sdri,sdev,sport,NULL);

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

  i=StartPage(hdc);
  if (i<=0)
  {
    DeleteDC(hdc);
    fclose(s_fp2);
    return(1);
  }

  GetTextMetrics(hdc,&tm);
  win_print_xchar=tm.tmAveCharWidth;
  win_print_ychar=tm.tmHeight+tm.tmExternalLeading;

  for (i=1;i<=bw_main1.win_page_size;i++)
  {
    fgets(s1,SMG_SIZE,s_fp2);

    exist=0;
    for (j=strlen(s1);j>=0;j--)
    {
      if ((s1[j]>' ')||(s1[j]<0))
      {
	exist=1;
	break;
      }
    }

    if (exist==1) s1[j+1]=0;
    else s1[0]=0;

    j=win_print_ychar*i;
    TextOut(hdc,1,j,s1,strlen(s1));
    if (feof(s_fp2)) break;
  }

  i=EndPage(hdc);
  if (i<0)
  {
    DeleteDC(hdc);
    fclose(s_fp2);
    return(1);
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
*/
  return(0);
}

int bw_print::w_cnt_pageline(int basep,int ln)
{
  int i,k;

  k=0;
  for (i=0;i<=t6_pp1;i++) /* find first screen field */
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

  for (k=0;k<=t6_pp1;k++)
  {
    if ((get_t6_linecol(k,0)==p1)&&(get_t6_linecol(k,1)==p2))
    {
      exist=1;
      l=get_t6_linecol(k,2);
    }
  }

  if (exist==1) return(l);
  else return(0-1);
}

int bw_print::w_print_page(int page,int form,int wpp)
{
  long s_recno[STRU_NUM];
  int  i,j,k,l,m,n,o,p,q,s,u;
  int  exist;
  char logic;
  int  s_tmpn5[STRU_NUM];
//  char s_fldtable[SMG_SIZE];
  char s_fldname[SMG_SIZE];
  int  s_end[STRU_NUM];
//  int  m1,m2,m3,m4,m5;
  char str[SMG_SIZE];
  char sfn[SMG_SIZE];

//win_state7[win_fcnt][win_pp_win_mark]=win_print_state1;

  for (i=0;i<PAGE_LINE;i++)
    for (j=0;j<PAGE_COLU;j++)
      set_t6_tmpc2(i,j,get_t6_pagefile(i,j));

  exist=0;

  if (page==1)
  {
    for (i=0;i<STRU_NUM;i++)
    {
      if ((bw_win1.get_win_pp_wins_dbf(i,wpp)==1)&&(bw_xbase1.get_win_lnktab(i)==0))
      {
        set_t6_recno(i,form,0);
        exist=1;
      }
    }
  }
  else exist=1;

  if (exist==0) return(1);

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp_wins_dbf(i,wpp)!=1) continue;
    s_recno[i]=get_t6_recno(i,form);
    s_tmpn5[i]=0;
    s_end[i]=1;
  }

  for (k=0;k<STRU_NUM;k++)
  {
    if ((bw_win1.get_win_pp_wins_dbf(k,wpp)!=1)||(bw_xbase1.get_win_lnktab(k)!=0)) continue;
    for (l=1;l<=w_cnt_pageline(k,PAGE_LINE);l++)
    {
      for (m=0;m<=t6_pp1;m++)
      {
	if (get_t6_fldbase(m)!=k) continue;
	if (get_t6_fldseri(m)!=l) continue;

	i=get_t6_linecol(m,0);
	j=get_t6_linecol(m,1);

	if ((get_t6c_fldname(m,0)==':')||(get_t6c_fldname(m,0)=='%'))
	{
	  if (s_tmpn5[k]!=get_t6_fldseri(m))
	  {
	    s_recno[k]=bw_mbase1.w_down_rec(k,wpp,s_recno[k]);
	    s_tmpn5[k]=get_t6_fldseri(m);
	    if (bw_xbase1.win_state_dbf_err!=0) s_end[k]=1;
	    else s_end[k]=0;
	  }

	  get_t6_fldname(m,sfn,SMG_SIZE);
          bw_inkey1.strpcut(sfn,1,strlen(sfn)-1,SMG_SIZE,s_fldname,SMG_SIZE);
			     /* fetch win_field number */
	  n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (n==1)
	  {
	    for (n=1;n<=get_t6_fldlen(m);n++)
	    {
	      set_t6_tmpc2(i,j+n-1,' ');
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
	      if (n>(int)strlen(str)) set_t6_tmpc2(i,j+n-1,' ');
	      else  set_t6_tmpc2(i,j+n-1,str[n-1]);
            }
	  }
	  else
	  {
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

	    bw_link1.w_save_sv(bw_win1.win_pp_new_win
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
	    set_t6_tmpc2(i,j+n-1,' ');
	  }
	}
      }                                   
    }
  }

  /* save imp var */
  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp_wins_dbf(i,wpp)!=1) continue;
    set_t6_recno(i,form,s_recno[i]);
  }

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp_wins_dbf(i,wpp)!=1) continue;
    if (s_end[i]==0) exist=1;
  }

//  win_state7[win_fcnt][win_pp_win_mark]=0;

  if (exist==1) return(0);
  else return(1);
}

int bw_print::w_print_memo(int o)
{
  int  i,j;
  int  m1,m4;
  char str[SMG_SIZE];

  for (i=0;i<PAGE_LINE;i++)
    for (j=0;j<PAGE_COLU;j++)
  {
    set_t6_tmpc2(i,j,' ');
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

int bw_print::w_print_lnk(int wpp) /* echo win rec where modified */
{
//  HDC  hdc1;
  long s_recno[STRU_NUM];
  int  s_seri[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  i,j,k,l,m,n,o,p,q,r,s,t,u,v;
//  int  p1,p2;
  int  exist;
  char str[SMG_SIZE];
//  char str1[SMG_SIZE];
//  char str2[SMG_SIZE];

//  win_tst1=0;

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_pp_wins_dbf(i,wpp)==1)&&(bw_xbase1.get_win_lnktab(i)>0))
    {
      if (bw_xbase1.get_win_lnktab(i)>0)
      {
	s_recno[i]=0;
	bw_xbase1.set_win_recno(i,wpp,0,0);
        s_seri[i]=0;
        exist=1;
      }
    }
  }

  if (exist==0)
  {
    return(0);
  }

  for (r=0;r<COND_NUM;r++)
  {
    if (bw_link1.get_win_bslink(r,2)!=wpp) continue;
    k=bw_link1.get_win_bslink(r,1);
    s=bw_link1.get_win_bslink(r,0);

    if (bw_win1.get_win_pp_wins_dbf(k,wpp)!=1) continue;

    if (bw_win1.get_win_pp_wins_dbf(s,wpp)!=1) continue;

    bw_link1.w_link_modi_mark(wpp,s,-1,-1);

    if (bw_link1.w_link_modified(wpp,s)!=1) continue;

    bw_link1.w_link_modi_unmark(wpp,s,-1,-1);

    bw_link1.w_link_modi_mark(wpp,k,-1,-1);

    for (l=1;l<=w_cnt_pageline(k,PAGE_LINE);l++)
    {
      for (v=0;v<=t6_pp1;v++)
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
	      set_t6_tmpc2(i,j+o-1,' ');
	    }
            continue;
	  }

	  if (get_t6_fldbase(m)!=k) continue;
	  if (get_t6_fldseri(m)!=l) continue;

	  get_t6_fldname(m,str,SMG_SIZE);
          bw_inkey1.strpcut(str,1,strlen(str)-1,SMG_SIZE,s_fldname,SMG_SIZE);

	  if (s_seri[k]!=get_t6_fldseri(m))
	  {

//	    win_tst1=0;

	    while (1)
	    {
	      s_recno[k]=bw_mbase1.w_down_rec(k,wpp,s_recno[k]);

	      if (bw_xbase1.get_win_lnktab(k)==3) u=1;
	      else u=get_t6_fldseri(m);

	      if (bw_link1.w_link_cond_ok(r,wpp,k,u,bw_win1.win_pp_new_win)==1) break;
	      if (bw_xbase1.win_state_dbf_err==1) break;
	    }
	    s_seri[k]=get_t6_fldseri(m);
	    if (bw_xbase1.win_state_dbf_err==0) bw_xbase1.set_win_enseri(k,wpp,l);
          }

		 /* fetch win_field number */
	  n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (n==1)
	  {
	    for (o=1;o<=get_t6_fldlen(m);o++)
	    {
	      set_t6_tmpc2(i,j+o-1,' ');
	    }
            continue;
          }

//	  sprintf(str1,"%d,%ld,",bw_xbase1.win_state_dbf_err,s_recno[k]);
//	  win_tst1++;
//	  hdc1=GetDC(bw_main1.win_hwnd1);
//	  TextOut(hdc1,1,win_tst1*20,str1,strlen(str1));
//          ReleaseDC(bw_main1.win_hwnd1,hdc1);

	  p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_SIZE,k);
	  q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,k);

          str[0]=0;

	  for (o=1;o<=q;o++)
          {
            str[o-1+0]=bw_xbase1.get_win_recvar(p+o-1);
            str[o-1+1]=0;
          }

	  str[q]=0;
	  str[get_t6_fldlen(m)]=0;

	  for (o=1;o<=get_t6_fldlen(m);o++)
	  {
	    if (o>(int)strlen(str)) set_t6_tmpc2(i,j+o-1,' ');
	    else  set_t6_tmpc2(i,j+o-1,str[o-1]);
          }

	  t=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	  if (t==0)
	  {
	    t=bw_fldstru1.win_field_num;

	    bw_link1.w_save_sv(bw_win1.win_pp_new_win
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
  int pp1,pp2,pp3,pp4;
  int pp0,pp5,pp6;
  char s_fldname[10];

		 
  for (m=0;m<=t6_pp1;m++)
  {
    if ((t6_fldname[m][0]!='%')&&
	(t6_fldedit[m]!=1)) continue;

    i=t6_linecol[m][0];
    j=t6_linecol[m][1];

    pp1=m;
    win_fcnt=t6_fldbase[pp1];

    if (t6_fldname[pp1][0]=='%')
      strpcut(t6_fldname[pp1],1,strlen(t6_fldname[pp1])-1,s_fldname);
    else
      strcpy(s_fldname,t6_fldname[pp1]);

    if (strempty(s_fldname)==1)
    {
      w_find_fldnum(s_fldname);
      if ((w_in_calc_var(t6_fldbase[pp1],win_field_num
			,t6_fldseri[pp1])>=0)&&
	  (w_calc_modi_var(t6_fldbase[pp1]
			,win_field_num
			,t6_fldseri[pp1])==1))
      {
	if (t6_fldseri[pp1]>win_enseri[win_pp_win_mark][t6_fldbase[pp1]]) continue;
	w_fetch_rec(pp4,t6_fldseri[pp1],pp3,t6_fldbase[pp1]);
	pp3=t6_fldbase[pp1];
	pp4=t6_fldseri[pp1];

	win_state6=w_calc_var(t6_fldbase[pp1],win_field_num
		       ,t2_fldlen[win_field_num],t6_fldseri[pp1]);

	if (win_state6==1) win_state_dbf_modi[pp3]=1;

	s_tmpn2=w_find_fldnum(s_fldname);
	if (s_tmpn2==1) continue;

	if (t6_fldlen[pp1]>t2_fldlen[win_field_num])
	  l=t2_fldlen[win_field_num];
	else
	  l=t6_fldlen[pp1];

	for (k=1;k<=l;k++)
	  t6_tmpc2[i][j+k-1]=win_recvar[t2_fldposi[win_field_num]+k-1];

	w_save_sv(win_fcnt,win_field_num-t2_fldpoin[win_fcnt][0]
			,t6_fldseri[pp1]
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
//  long s_fldrecno;
  int  i,j,k,l,m;
//  int  s_state1;
//  int  s_tmpn1;
  int  s_tmpn3;
  int  exist;
//  int  pp1,pp2;
  char s_tmpc1[30][50];
  char s_tmpc2[SMG_SIZE];
//  char s_fldtable[SMG_SIZE];
//  char s_fldname[SMG_SIZE];
  char sfn[SMG_SIZE];

  strcpy(s_tmpc1[1] ,"*y");
  strcpy(s_tmpc1[2] ,"*m");
  strcpy(s_tmpc1[3] ,"*d");
  strcpy(s_tmpc1[4] ,"*yr");
  strcpy(s_tmpc1[5] ,"*o");
  strcpy(s_tmpc1[6] ,"*time");
  strcpy(s_tmpc1[7] ,"*usr");
  strcpy(s_tmpc1[8] ,"*recno");
  strcpy(s_tmpc1[9] ,"*recnum");
  strcpy(s_tmpc1[10],"*fldlen");

  s_tmpn3=10;

  for (k=0;k<=t6_pp1;k++)
  {
    i=get_t6_linecol(k,0);
    j=get_t6_linecol(k,1);

    if (get_t6c_fldname(k,0)=='*')
    {
      exist=0;
      for (m=1;m<=s_tmpn3;m++)
      {
	get_t6_fldname(k,sfn,SMG_SIZE);
        if (strcmp(sfn,s_tmpc1[m])==0)
        {
	  exist=1;
	  break;
	}
      }

      if (exist==0) continue;

      if (m==1)  bw_dialog1.w_get_yy(s_tmpc2,SMG_SIZE);
      if (m==2)  bw_dialog1.w_get_mm(s_tmpc2,SMG_SIZE);
      if (m==3)  bw_dialog1.w_get_dd(s_tmpc2,SMG_SIZE);
      if (m==4)  bw_dialog1.w_get_year(s_tmpc2,SMG_SIZE);
      if (m==5)  bw_dialog1.w_get_mon(s_tmpc2,SMG_SIZE);
      if (m==6)  bw_dialog1.w_get_time(s_tmpc2,SMG_SIZE);
      if (m==7)  bw_dialog1.w_get_usr(s_tmpc2,SMG_SIZE);
      if (m==8)  bw_inkey1.long2str(0,s_tmpc2,SMG_SIZE);
      if (m==9)  bw_inkey1.long2str(0,s_tmpc2,SMG_SIZE);
      if (m==10) strcpy(s_tmpc2,"");

      if (m!=0)
      {
	for (l=1;l<=get_t6_fldlen(k);l++)
	{
	  if (l>=(int)strlen(s_tmpc2)) set_t6_tmpc2(i,j+l-1,' ');
	  else set_t6_tmpc2(i,j+l-1,s_tmpc2[l-1]);
	}
      }
    }
  }

  return(0);
}

int bw_print::w_scan_pagevar()
{
  int  i,k,p;
//  int  s_tmpn1,s_tmpn2;
  int  p1,p2;            /* p1 scrn var content poin,p2 scrn var num poin */
  int  exist;
  char str[FN_SIZE];
  char str1[FN_SIZE];

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if (bw_link1.get_win_svwind(i)==bw_win1.win_pp_new_win) break;
    if (bw_link1.get_win_svused(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);
  else
  {
    if (i==0)
    {
      p1=0;
      p2=0;
    }
    else
    {
      p1=bw_link1.get_win_svpoin(i-1,1);
      p2=i;
    }
  }

  for (p=0;p<=t6_pp1;p++)
  {
    if (get_t6_fldedit(p)==1)
    {
      get_t6_fldname(p,str,FN_SIZE);
      if (strlen(str)>1) bw_inkey1.strpcut(str,1,strlen(str)-1,FN_SIZE,str1,FN_SIZE);
      else continue;

      k=bw_link1.w_name_t1_t2(str1,get_t6_fldbase(p));
      if (k<0) continue;

      bw_link1.set_win_svpoin(p2,0,p1);
      bw_link1.set_win_svbase(p2,get_t6_fldbase(p));
      bw_link1.set_win_svseri(p2,k);
      bw_link1.set_win_svrecn(p2,get_t6_fldseri(p));
      bw_link1.set_win_svwind(p2,bw_win1.win_pp_new_win);
                                                
      p1=p1+bw_fldstru1.get_t2_fldlen(k+bw_fldstru1.get_t2_fldpoin(get_t6_fldbase(p),0));

      bw_link1.set_win_svpoin(p2,1,p1);
      bw_link1.set_win_svused(p2,1);

      p1++;
      if (p1>=VAR_IN_SCRN)
      {
        bw_win1.w_atten12();
        return(1);
      }

      p2++;
      if (p2>=WIN_VAR_NUM)
      {
        bw_win1.w_atten11();
        return(1);
      }
    }
  }

  return(0);
}

int bw_print::w_print(int wpp,char *p_s1,int p_s1_size)
{
/*
  int  i,j,k,l;
  char s2[FN_SIZE];
  char str[SMG_SIZE];
  //char s_fn4[FN_SIZE];

  strcpy(s2,p_s1);
  i=w_open_print(s2,FN_SIZE);
  if (i!=0) return(1);

  w_save_print();

  SendMessage(win_savep_hnd,WM_COMMAND,1005,(LPARAM)str);
  
  t6_wdir=0;
  k=0;
  while (1)
  {
    k++; //* page printed 
    l=0; //* continue print = n 
    j=0;
    while (1)
    {
      j++;  //* page seri 
      i=w_read_page(s2,FN_SIZE,j);
      if (i!=0) break;

      w_page_field1();
      w_page_field2(wpp);

      w_scan_pagevar();
  
      i=w_print_page(k,j,wpp);
      w_print_read();
      w_print_lnk(wpp);
//    w_print_cal();

      bw_link1.w_dele_svar(bw_win1.win_pp_new_win,bw_win1.win_pp_new_win);

      SendMessage(win_savep_hnd,WM_COMMAND,1006,(LPARAM)str);

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
      if (i==0) l=1;             // continue print next page
    }
    if (l==0) break;             // no next page
    if ((j==1)&&(i!=0)) break;   // empty file
  }

  SendMessage(win_savep_hnd,WM_COMMAND,1007,(LPARAM)str);

  w_close_print();

  if ((j==1)&&(i!=0)) return(0);

  t6_wdir=0;

  w_out_print(s2,FN_SIZE);
*/
  return(0);

}





int bw_print::get_t6_linecol(int fpp,int p02) 
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(t6_linecol[fpp][p02]);
}
int bw_print::set_t6_linecol(int fpp,int p02,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  t6_linecol[fpp][p02]=val;
  return(0);
}
int bw_print::get_t6c_fldname(int fpp,int pp1)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((pp1<0)||(pp1>21)) return(0);
  return(t6_fldname[fpp][pp1]);
}
int bw_print::set_t6c_fldname(int fpp,int pp1,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((pp1<0)||(pp1>21)) return(0);
  t6_fldname[fpp][pp1]=val;
  return(0);
}
int bw_print::get_t6_fldname(int fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>21) i=21;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t6_fldname[fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::set_t6_fldname(int fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>21) i=21;
  else i=p_s1_size;

  t6_fldname[fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    t6_fldname[fpp][j+0]=p_s1[j];
    t6_fldname[fpp][j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_fldtype(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldtype[fpp]);
}
int bw_print::set_t6_fldtype(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldtype[fpp]=val;
  return(0);
}
int bw_print::get_t6_fldedit(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldedit[fpp]);
}
int bw_print::set_t6_fldedit(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldedit[fpp]=val;
  return(0);
}
int bw_print::get_t6_fldbase(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldbase[fpp]);
}
int bw_print::set_t6_fldbase(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldbase[fpp]=val;
  return(0);
}
int bw_print::get_t6_fldseri(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldseri[fpp]);
}
int bw_print::set_t6_fldseri(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldseri[fpp]=val;
  return(0);
}
int bw_print::get_t6_fldlen(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldlen[fpp]);
}
int bw_print::set_t6_fldlen(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldlen[fpp]=val;
  return(0);
}
int bw_print::get_t6_flddec(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_flddec[fpp]);
}
int bw_print::set_t6_flddec(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_flddec[fpp]=val;
  return(0);
}
int bw_print::get_t6_pagefile(int lpp,int cpp)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  return(t6_pagefile[lpp][cpp]);
}
int bw_print::set_t6_pagefile(int lpp,int cpp,int val)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  t6_pagefile[lpp][cpp]=val;
  return(0);
}
int bw_print::get_t6s_pagefile(int lpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);

  if (p_s1_size>PAGE_COLU) i=PAGE_COLU;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t6_pagefile[lpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::get_t6_tmpc2(int lpp,int cpp)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  return(t6_tmpc2[lpp][cpp]);
}
int bw_print::set_t6_tmpc2(int lpp,int cpp,int val)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  t6_tmpc2[lpp][cpp]=val;
  return(0);
}
int bw_print::get_t6s_tmpc2(int lpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);

  if (p_s1_size>PAGE_COLU) i=PAGE_COLU;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t6_tmpc2[lpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
long bw_print::get_t6_recno(int p_fcnt,int wpp)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(t6_recno[p_fcnt][wpp]);
}
int bw_print::set_t6_recno(int p_fcnt,int wpp,long val)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  t6_recno[p_fcnt][wpp]=val;
  return(0);
}            
int bw_print::get_ts_field(int fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>10) i=10;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ts_field[fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_print::set_ts_field(int fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);

  if (p_s1_size>10) i=10;
  else i=p_s1_size;

  ts_field[fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    ts_field[fpp][j+0]=p_s1[j];
    ts_field[fpp][j+1]=0;
  }

  return(0);
}
int bw_print::set_ts_fieldc(int fpp,int cpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((cpp<0)||(cpp>=10)) return(0);
  ts_field[fpp][cpp]=val;
  return(0);
}
int bw_print::get_ts_fldseri(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(ts_fldseri[fpp]);
}
int bw_print::set_ts_fldseri(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  ts_fldseri[fpp]=val;
  return(0);
}
int bw_print::get_ts_base(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(ts_base[fpp]);
}
int bw_print::set_ts_base(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  ts_base[fpp]=val;
  return(0);
}
int bw_print::get_ts_recno(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(ts_recno[fpp]);
}
int bw_print::set_ts_recno(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  ts_recno[fpp]=val;
  return(0);
}
int bw_print::get_win_memo_print(int mpp)
{
  if ((mpp<0)||(mpp>=MEMO_NUM)) return(0);
  return(win_memo_print[mpp]);
}
int bw_print::set_win_memo_print(int mpp,int val)
{
  if ((mpp<0)||(mpp>=MEMO_NUM)) return(0);
  win_memo_print[mpp]=val;
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

