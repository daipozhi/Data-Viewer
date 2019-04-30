#define STRICT
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

#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_main_bua     bw_main_bua1;
extern class bw_dialog_bua   bw_dialog_bua1;
extern class bw_xbase_bua    bw_xbase_bua1;
extern class bw_edit_bua     bw_edit_bua1;
extern class bw_win_bub      bw_win_bub1;
extern class bw_win_bua      bw_win_bua1;
extern class bw_buffa        bw_buffa1;
extern class bw_buff         bw_buff1;
extern class bw_edit         bw_edit1;
extern class bw_link         bw_link1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_getread      bw_getread1;
extern class bw_dialog       bw_dialog1;
extern class bw_switch       bw_switch1;
extern class bw_choose       bw_choose1;
extern class bw_menuvar      bw_menuvar1;
extern class bw_inkey        bw_inkey1;
extern class bw_win          bw_win1;
extern class bw_fldstru      bw_fldstru1;

extern long FAR PASCAL w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long FAR PASCAL w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);

/* should into class */

HWND bw_win_bua::get_ci_mhnd(HWND hwnd)
{
  int i,j;
  for (i=0;i<HND_NUM;i++)
  {
    if (win_hnd[i]==hwnd)
    {
      j=win_hpp4[i][4];
      return(win_hnd[j]);
    }
  }
  return(NULL);
}

int bw_win::w_first_pp5()
{
  int i;
  int exist;
  exist=0;
  for (i=1;i<WIN_NUM;i++)
  {
    if (bw_win_bua1.get_win_pp5(i)==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    //bw_win_bua1.set_win_subhndpp(i,0);
    return(i);
  }
  else return(-1);
}
int bw_win::w_ini_win()
{
  int i;

  win_pp1=1; /* can not be zero 0 */

  for (i=0;i<WIN_NUM;i++)
  {
    bw_win_bua1.set_win_pp2(i,0,0);
    bw_win_bua1.set_win_pp2(i,1,0);
    bw_win_bua1.set_win_pp2(i,2,0);
    bw_win_bua1.set_win_pp2(i,3,0);
    bw_win_bua1.set_win_pp4(i,0);
    bw_win_bua1.set_win_pp5(i,0);
    bw_win_bua1.set_win_pp6(i,0,0);
    bw_win_bua1.set_win_pp6(i,1,0);
    bw_win_bua1.set_win_pp6(i,2,0);

    bw_win_bua1.set_win_msgboxlock(i,0);
  }

  return(0);
}

int bw_win::w_login_win(int i1,int i2,char *p_win_name,int len1,char *p_find_name,int len2)
{
  int i,j,k;
  int exist;

  exist=0;
  for (i=1;i<WIN_NUM;i++)
  {
    if (bw_win_bua1.get_win_pp6(i,0)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0)
  {
    w_atten3();
    return(1);
  }

  bw_win_bua1.set_win_pp6(i,0,i1);
  bw_win_bua1.set_win_pp6(i,1,i1);
  bw_win_bua1.set_win_pp6(i,2,i2);

  for (j=i1;j<=i2;j++)
  {
    bw_win_bua1.set_win_pp5(j,i);
    bw_win_bua1.set_win_pp4(j,j);
    bw_win_bub1.set_win_window_name(j,p_win_name,len1);
    bw_win_bub1.set_win_find_name(  j,p_find_name,len2);

    for (k=0;k<STRU_NUM;k++)
    {
      bw_xbase_bua1.set_win_cuseri(k,j,0);
      bw_xbase_bua1.set_win_recno(k,j,0,0);
      bw_xbase_bua1.set_win_recno(k,j,1,0);
      bw_xbase_bua1.set_win_recno(k,j,2,0);
      bw_xbase_bua1.set_win_state9(j,k,0);
    }
  }

  return(0);
}

int bw_win::w_dele_win_pp(int wpp)
{
  int i,j,k;
//  int exist;

  i=bw_win_bua1.get_win_pp5(wpp);

  for (j=bw_win_bua1.get_win_pp6(i,0);j<=bw_win_bua1.get_win_pp6(i,2);j++)
  {
    bw_win_bua1.set_win_pp5(j,0);
    bw_win_bua1.set_win_pp4(j,0);
    for (k=0;k<STRU_NUM;k++)
    {
      bw_win_bua1.set_win_pp9(k,j,0);
    }
  }

  bw_win_bua1.set_win_pp6(i,0,0);
  bw_win_bua1.set_win_pp6(i,1,0);
  bw_win_bua1.set_win_pp6(i,2,0);

  return(0);
}

int bw_win::w_dele_win_pp9(int wpp)
{
  int i,j;

  for (j=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0)
      ;j<=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),2)
      ;j++)
  {
    for (i=0;i<STRU_NUM;i++)
    {
      if (bw_win_bua1.get_win_pp9(i,j)==1)
      {
	bw_win_bub1.set_win_tabname(0,i,"",0);
	bw_win_bub1.set_win_tabname(1,i,"",0);
      }
      bw_win_bua1.set_win_pp9(i,j,0);
    }
  }

  return(0);
}

int bw_win::w_login_wwin(int p_pagecnt)
{
  win_hpp6=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(p_pagecnt),2)-bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(p_pagecnt),0);

  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),0,win_hpp1);
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),1,win_hpp1+win_hpp6);
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),2,win_hpp1);
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),3,bw_win_bua1.get_win_pp5(p_pagecnt)-1);

  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),4,win_hpp1+win_hpp6+1);
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5,0);
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),6,win_hpp1+win_hpp6+1);
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),7,bw_win_bua1.get_win_pp5(p_pagecnt));

  win_hpp5=win_hpp1+win_hpp6+1;
  win_hpp1=win_hpp5;

  return(0);
}
int bw_win::w_find_winhand(HWND hwnd)
{
  int i;
  int exist;

  exist=0;
  for (i=1;i<win_pp1;i++)
  {
    if (hwnd==bw_win_bua1.get_win_phh(i))
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);
  else return(i);
}
int bw_win::w_mouse_infield(int wpp,int y,int x)
{
  int  exist;
  int  m,n;
  char str[SMG_LEN];

  exist=0;
  for (m=1;m<COL_NUM;m++)
  {
    n=bw_buff1.get_linecol(wpp,y,m);
    if ((n>0)&&(bw_win_bua1.get_1fldedt(n)==0))
    {
      if ((m<=x)&&(x<=m+bw_win_bua1.get_1fldlen(n)-1))
      {
	bw_win_bua1.get_1fldname(n,str,SMG_LEN);

	if ((str[0]=='?')||(str[0]==':'))
        {
	  exist=1;
	  win_mouse_y=y;
	  win_mouse_x=m;
	  bw_main1.win_field_posi=x-m+1;
	  break;
	}
      }
    }
  }

  return(exist);
}

int bw_win::tst_win1()
{
  HDC  hdc;
  int  i,j,k,l,m;
  char str[SMG_LEN];
  char str2[FLD_NAME_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=1;i<60;i++)
  {
    bw_win_bua1.get_1fldname(i,str2,FLD_NAME_LEN);

    sprintf(str,"%s,t=%d,b=%d,s=%d,l=%d,d=%d,e=%d,"
                                       ,str2
				       ,bw_win_bua1.get_1fldtype(i)
				       ,bw_win_bua1.get_1fldbase(i)
				       ,bw_win_bua1.get_1fldseri(i)
				       ,bw_win_bua1.get_1fldlen(i)
				       ,bw_win_bua1.get_1flddec(i)
				       ,bw_win_bua1.get_1fldedt(i));
    TextOut(hdc,1,(i-1)*20,str,strlen(str));
  }

  k=0;
  for (l=1;l<WIN_NUM;l++)
  {
    for (i=1;i<LIN_NUM;i++)
    {
      for (j=1;j<COL_NUM;j++)
      {
	if (bw_buff1.get_linecol(l,i,j)!=0)
	{
	  m=bw_buff1.get_linecol(l,i,j);
	  bw_win_bua1.get_1fldname(m,str2,FLD_NAME_LEN);
	  sprintf(str,"w=%d,l=%d,c=%d,n=%d,seri=%d,base=%d,%s,",l,i,j,m,bw_win_bua1.get_1fldseri(m),bw_win_bua1.get_1fldbase(m),str2);
          TextOut(hdc,300,k*20,str,strlen(str));
	  k++;
	  if (k>=60) break;
        }
      }
      if (k>=60) break;
    }
    if (k>=60) break;
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_win::tst_win2()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str,"20=%d,21=%d,4=%d,5=%d,60=%d,61=%d,62=%d,90=%d,91=%d,92=%d,93=%d,pp1=%d,subwub=%d,"
                                       ,bw_win_bua1.get_win_pp2(i,0)
				       ,bw_win_bua1.get_win_pp2(i,1)
				       ,bw_win_bua1.get_win_pp4(i)   
				       ,bw_win_bua1.get_win_pp5(i)
				       ,bw_win_bua1.get_win_pp6(i,0)
				       ,bw_win_bua1.get_win_pp6(i,1)
				       ,bw_win_bua1.get_win_pp6(i,2)
				       ,bw_win_bua1.get_win_pp9(0,i)
				       ,bw_win_bua1.get_win_pp9(1,i)
				       ,bw_win_bua1.get_win_pp9(2,i)
				       ,bw_win_bua1.get_win_pp9(3,i)
				       ,win_pp1
				       ,0/*bw_win_bua1.get_win_subhndpp(i)*/);
    TextOut(hdc,1,i*20,str,strlen(str));

  }

  for (i=0;i<STRU_NUM;i++)
  {
    bw_win_bub1.get_win_tabname(0,i,stn1,FN_SIZE);
    bw_win_bub1.get_win_tabname(1,i,stn2,FN_SIZE);
    sprintf(str,"tab=%s,stru=%s,",stn1,stn2);
    TextOut(hdc,600,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_win::tst_win3()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];
  char stn3[FN_SIZE];
  char stn4[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<STRU_NUM;i++)
  {
    bw_win_bub1.get_win_tabname(0,i,stn1,FN_SIZE);
    bw_win_bub1.get_win_tabname(1,i,stn2,FN_SIZE);
    bw_win_bub1.get_win_window_name(i,stn3,FN_SIZE);
    bw_win_bub1.get_win_find_name(i,stn4,FN_SIZE);

    sprintf(str,"wn=%s,fn=%s,stru=%s,base=%s,"
                                       ,stn3
				       ,stn4
				       ,stn1
				       ,stn2);
    TextOut(hdc,1,i*20,str,strlen(str));

  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_win::tst_win4()
{
  HDC  hdc;
  int  i,j;
  char str[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=1;i<24;i++)
  {
    for (j=1;j<=80;j++)
    {
      str[j-1]=bw_buffa1.get_tmpc1(1,i,j);
    }
    str[80]=0;

    TextOut(hdc,1,i*20,str,strlen(str));

  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_win::tst_win5()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<STRU_NUM;i++)
  {
    bw_win_bub1.get_win_tabname(0,i,stn1,FN_SIZE);
    bw_win_bub1.get_win_tabname(1,i,stn2,FN_SIZE);

    sprintf(str,"base=%s,stru=%s,",stn1,stn2);

    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}
int bw_win::tst_win6()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=1;i<WIN_NUM;i++)
  {
    sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,"
	,0/*bw_win_bua1.get_win_subhndid(i,0)*/
	,0/*bw_win_bua1.get_win_subhndid(i,1)*/
	,0/*bw_win_bua1.get_win_subhndid(i,2)*/
	,0/*bw_win_bua1.get_win_subhndid(i,3)*/
	,0/*bw_win_bua1.get_win_subhndid(i,4)*/
	,0/*bw_win_bua1.get_win_subhndid(i,5)*/
	,0/*bw_win_bua1.get_win_subhndid(i,6)*/
	,0/*bw_win_bua1.get_win_subhndid(i,7)*/
           );

    TextOut(hdc,0,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}
int bw_win::w_close_win(int p1)
{
  HWND edit_hnd;
  int  i,j,k,l,m,n;
  int  pp5;
  int  id[WIN_NUM];
  //int  subhndpp[WIN_NUM];
  char str[SMG_LEN];

  for (i=1;i<WIN_NUM;i++)
  {
    id[i]=0;
    //subhndpp[i]=0;
  }

  pp5=bw_win_bua1.get_win_pp5(p1);

  id[pp5]=1;
/*
  for (i=1;i<WIN_NUM;i++)
  {
    if (id[i]==1)
    {
      for (j=0;j<bw_win_bua1.get_win_subhndpp(i);j++)
      {
	k=bw_win_bua1.get_win_subhndid(i,j);
	id[k]=1;
//	win_subhndid[i][j]=0;
      }
    }
  }
*/
/*
  for (i=1;i<WIN_NUM;i++)
  {
    for (j=0;j<bw_win_bua1.get_win_subhndpp(i);j++)
    {
      k=bw_win_bua1.get_win_subhndid(i,j);
      if ((k>0)&&(id[k]!=0)) subhndpp[i]++;
    }
  }
*/
/*
  for (i=1;i<WIN_NUM;i++)
  {
    if (id[i]==1)
    {
      for (j=0;j<bw_win_bua1.get_win_subhndpp(i);j++)
      {
	bw_win_bua1.set_win_subhndid(i,j,0);
      }
    }
  }
*/
/*
  for (i=1;i<WIN_NUM;i++)
  {
    for (j=0;j<bw_win_bua1.get_win_subhndpp(i);j++)
    {
      if (bw_win_bua1.get_win_subhndid(i,j)==pp5)
      {
	bw_win_bua1.set_win_subhndid(i,j,0);
      }
    }
  }
*/
  for (i=WIN_NUM-1;i>=1;i--)
  {
    if (id[i]==1)
    {
      for (m=0;m<STRU_NUM;m++)
      {
	if ((bw_win_bua1.get_win_pp9(m,i)==1)&&(bw_xbase_bua1.get_win_mem_inuse(m)==1))
	{
	  for (n=0;n<EDIT_NUM;n++)
	  {
	    if (bw_edit_bua1.get_win_edit_wpp(n)==i)
	    {
	      edit_hnd=bw_edit_bua1.get_win_edit_hnd1(n);
	      SendMessage(edit_hnd,WM_COMMAND,1803,(LPARAM)str);
	    }
          }
	}
      }

//      sprintf(str,"%d,%d,",i,win_pp6[i][0]);
//      MessageBox(bw_main1.win_hwnd1,str,"aa",MB_OK);

      w_close_subwin(bw_win_bua1.get_win_pp6(i,0));

//      bw_dialog1.tst_mem();
/*
      for (l=1;l<WIN_NUM;l++)
      {
	for (j=0;j<bw_win_bua1.get_win_subhndpp(l);j++)
        {
	  if (bw_win_bua1.get_win_subhndid(l,j)>=i)
          {
	    bw_win_bua1.set_win_subhndid(l,j,bw_win_bua1.get_win_subhndid(l,j)-1);
	  }
        }
      }
*/
    }
  }
/*
  for (l=1;l<WIN_NUM;l++)
  {
    bw_win_bua1.set_win_subhndpp(l,bw_win_bua1.get_win_subhndpp(l)-subhndpp[l]);
  }
*/
  return(0);
}
int bw_win::w_close_subwin(int p1)
{
//  HDC  hdc;
  int  exist;
  int  i,j,k,l,m,n,o,p,q,r,s,t;
  int  p10;
//  char str[SMG_LEN];
  char sfn[FLD_NAME_LEN];
  char stn1[FN_SIZE];
  char sm1[SMG_LEN];

  // must answer
  if (bw_xbase1.win_answer!=0)
  {
    w_atten66();
    return(1);
  }

  bw_xbase1.win_answer=1;

  i=bw_win_bua1.get_win_pp5(p1);



  /* close database */
  for (k=bw_win_bua1.get_win_pp6(i,0);k<=bw_win_bua1.get_win_pp6(i,2);k++)
  {
	  bw_win_bua1.set_win_msgboxlock(k,1);
  }



  for (k=0;k<STRU_NUM;k++)
  {
    if (bw_win_bua1.get_win_pp9(k,p1)==1)
    {
      bw_fldstru1.w_dele_stru(k);
      bw_mbase1.w_close_base(k,p1);
      bw_fldstru1.w_clr_condition(k);
    }
  }



  for (k=bw_win_bua1.get_win_pp6(i,0);k<=bw_win_bua1.get_win_pp6(i,2);k++)
  {
	  bw_win_bua1.set_win_msgboxlock(k,0);
  }



  /* remove mem var */

  bw_menuvar1.w_dele_menu(bw_win_bua1.get_win_pp6(i,0),bw_win_bua1.get_win_pp6(i,2));

  bw_choose1.w_dele_choose(bw_win_bua1.get_win_pp6(i,0),bw_win_bua1.get_win_pp6(i,2));

  bw_switch1.w_dele_switch(bw_win_bua1.get_win_pp6(i,0),bw_win_bua1.get_win_pp6(i,2));

  bw_dialog1.w_dele_dialog(bw_win_bua1.get_win_pp6(i,0),bw_win_bua1.get_win_pp6(i,2));

  bw_link1.w_dele_svar(bw_win_bua1.get_win_pp6(i,0),bw_win_bua1.get_win_pp6(i,2));

  bw_link1.w_dele_link(bw_win_bua1.get_win_pp6(i,0),bw_win_bua1.get_win_pp6(i,2));

  for (k=bw_win_bua1.get_win_pp6(i,0);k<=bw_win_bua1.get_win_pp6(i,2);k++)
  {
    j=bw_win_bua1.get_win_pp11(k);
    bw_getread1.get_read_logout(j);
  }

  w_dele_win_pp9(p1);

  for (j=bw_win_bua1.get_win_pp6(i,0);j<=bw_win_bua1.get_win_pp6(i,2);j++)
  {
    SetFocus(bw_main1.win_main_hnd);

    k=bw_win_bua1.get_win_hpp3(i,0)+j-bw_win_bua1.get_win_pp6(i,0);
    DestroyWindow(bw_win_bua1.get_win_hnd(k));
  }

  SetFocus(bw_main1.win_main_hnd);

  exist=0;
  for (j=WIN_NUM-1;j>=1;j--)
  {
    if (bw_win_bua1.get_win_pp4(j)!=0)
    {
      exist=1;
      break;
    }
  }
  if (exist==0)
  {
    bw_xbase1.win_answer=0;
    return(1);
  }

  l=bw_win_bua1.get_win_pp5(j);

  n=bw_win_bua1.get_win_pp6(i,2)-bw_win_bua1.get_win_pp6(i,0)+1;

  q=0;

  for (k=bw_win_bua1.get_win_pp6(i,0);k<=bw_win_bua1.get_win_pp6(i,2);k++)
  {
    q=q+bw_win_bua1.get_win_pp2(k,1)-bw_win_bua1.get_win_pp2(k,0)+1;
  }

  r=bw_win_bua1.get_win_pp2(bw_win_bua1.get_win_pp6(l,2),1);

  s=bw_win_bua1.get_win_pp2(bw_win_bua1.get_win_pp6(i,2),1)+1;

  for (k=s;k<=r;k++)
  {
    bw_win_bua1.get_1fldname(k,sfn,FLD_NAME_LEN);
    bw_win_bua1.set_1fldname(k-q,sfn,FLD_NAME_LEN);
    bw_win_bua1.set_1fldtype(k-q,bw_win_bua1.get_1fldtype(k));
    bw_win_bua1.set_1fldbase(k-q,bw_win_bua1.get_1fldbase(k));
    bw_win_bua1.set_1fldseri(k-q,bw_win_bua1.get_1fldseri(k));
    bw_win_bua1.set_1fldlen(k-q,bw_win_bua1.get_1fldlen(k));
    bw_win_bua1.set_1flddec(k-q,bw_win_bua1.get_1flddec(k));
    bw_win_bua1.set_1fldedt(k-q,bw_win_bua1.get_1fldedt(k));
  }

  for (k=r-q+1;k<=r;k++)
  {
    bw_win_bua1.set_1fldname1(k,0,0);
    bw_win_bua1.set_1fldbase(k,0);
    bw_win_bua1.set_1fldseri(k,0);
    bw_win_bua1.set_1fldlen(k,0);
    bw_win_bua1.set_1flddec(k,0);
    bw_win_bua1.set_1fldedt(k,0);
    bw_win_bua1.set_1fldtype(k,0);
  }

  t=bw_win_bua1.get_win_hpp3(i,1)-bw_win_bua1.get_win_hpp3(i,0)+1;
  if (bw_win_bua1.get_win_hpp3(i,5)==0)
     t=t;
  else
     t=t+bw_win_bua1.get_win_hpp3(i,5)-bw_win_bua1.get_win_hpp3(i,4)+1;

  p10=bw_win_bua1.get_win_pp6(l,2);

  for (k=i+1;k<=l;k++)
  {
    for (m=bw_win_bua1.get_win_pp6(k,0);m<=bw_win_bua1.get_win_pp6(k,2);m++)
    {
      bw_win_bua1.set_win_pp2(m-n,0,bw_win_bua1.get_win_pp2(m,0)-q);
      bw_win_bua1.set_win_pp2(m-n,1,bw_win_bua1.get_win_pp2(m,1)-q);
      bw_win_bua1.set_win_pp5(m-n,bw_win_bua1.get_win_pp5(m)-1);
      bw_win_bua1.set_win_pp4(m-n,m-n);

      for (o=0;o<STRU_NUM;o++)
      {
	bw_win_bua1.set_win_pp9(o,m-n,bw_win_bua1.get_win_pp9(o,m));
      }

      bw_win_bua1.set_win_pp11(m-n,bw_win_bua1.get_win_pp11(m));

      bw_win_bua1.set_win_linep(m-n,0,bw_win_bua1.get_win_linep(m,0));
      bw_win_bua1.set_win_linep(m-n,1,bw_win_bua1.get_win_linep(m,1));

      bw_win_bua1.set_win_con(m-n,0,bw_win_bua1.get_win_con(m,0));
      bw_win_bua1.set_win_con(m-n,1,bw_win_bua1.get_win_con(m,1));

      bw_dialog_bua1.setc_win_mv_getv(m,SMG_LEN-1,0);

      bw_dialog_bua1.get_win_mv_getv(m,sm1,SMG_LEN);
      bw_dialog_bua1.set_win_mv_getv(m-n,sm1,SMG_LEN);

      bw_dialog_bua1.set_win_mv_getp(m-n,bw_dialog_bua1.getv_win_mv_getp(m));

      bw_win_bua1.set_win_hpp7(m-n,0,bw_win_bua1.get_win_hpp7(m,0)-t);
      bw_win_bua1.set_win_hpp7(m-n,1,bw_win_bua1.get_win_hpp7(m,1)-t);

      bw_win_bua1.set_win_phh(m-n,bw_win_bua1.get_win_phh(m));

      bw_win_bub1.get_win_window_name(m,stn1,FN_SIZE);
      bw_win_bub1.set_win_window_name(m-n,stn1,FN_SIZE);
      bw_win_bub1.get_win_find_name(m,stn1,FN_SIZE);
      bw_win_bub1.set_win_find_name(m-n,stn1,FN_SIZE);

      for (o=1;o<LIN_NUM;o++)
      {
	for (p=1;p<COL_NUM;p++)
	{
	  bw_buffa1.set_tmpc1(m-n,o,p,bw_buffa1.get_tmpc1(m,o,p));
	  if (bw_buff1.get_linecol(m,o,p)!=0)
	    bw_buff1.set_linecol(m-n,o,p,bw_buff1.get_linecol(m,o,p)-q);
	  else
	    bw_buff1.set_linecol(m-n,o,p,0);
	}
      }
    }

    bw_win_bua1.set_win_pp6(k-1,0,bw_win_bua1.get_win_pp6(k,0)-n);
    bw_win_bua1.set_win_pp6(k-1,1,bw_win_bua1.get_win_pp6(k,1)-n);
    bw_win_bua1.set_win_pp6(k-1,2,bw_win_bua1.get_win_pp6(k,2)-n);

    if (k==l)
    {
      bw_win_bua1.set_win_pp6(l,0,0);
      bw_win_bua1.set_win_pp6(l,1,0);
      bw_win_bua1.set_win_pp6(l,2,0);
    }
  }

  for (k=p10-n+1;k<=p10;k++)
  {
    bw_win_bua1.set_win_pp2(k,0,0);
    bw_win_bua1.set_win_pp2(k,1,0);
    bw_win_bua1.set_win_pp4(k,0);
    bw_win_bua1.set_win_pp5(k,0);

    for (o=0;o<STRU_NUM;o++)
    {
      bw_win_bua1.set_win_pp9(o,k,0);
    }

    bw_win_bua1.set_win_pp11(k,0);
  }

  if (i==l)
  {
    bw_win_bua1.set_win_pp6(l,0,0);
    bw_win_bua1.set_win_pp6(l,1,0);
    bw_win_bua1.set_win_pp6(l,2,0);
  }

  /* segment */

  j=bw_win_bua1.get_win_hpp3(i,1)-bw_win_bua1.get_win_hpp3(i,0)+1;
  if (bw_win_bua1.get_win_hpp3(i,5)==0)
    j=j;
  else
    j=j+bw_win_bua1.get_win_hpp3(i,5)-bw_win_bua1.get_win_hpp3(i,4)+1;

  if (bw_win_bua1.get_win_hpp3(i,5)==0) m=bw_win_bua1.get_win_hpp3(i,4);
  else m=bw_win_bua1.get_win_hpp3(i,5)+1;

  if (bw_win_bua1.get_win_hpp3(l,5)==0) o=bw_win_bua1.get_win_hpp3(l,1);
  else o=bw_win_bua1.get_win_hpp3(l,5);
/*
  sprintf(str,"j=%d,hpp30=%d,hpp31=%d,i=%d,l=%d,m=%d,o=%d,"
				       ,j
				       ,win_hpp3[i][0]
				       ,win_hpp3[i][1]
				       ,i,l,m,o);
  MessageBox(bw_main1.win_hwnd1,str,"aa",MB_OK);
*/
  for (k=i+1;k<=l;k++)
  {
    if (bw_win_bua1.get_win_hpp3(k,0)>=j) bw_win_bua1.set_win_hpp3(k-1,0,bw_win_bua1.get_win_hpp3(k,0)-j);
    else                  bw_win_bua1.set_win_hpp3(k-1,0,0);
    if (bw_win_bua1.get_win_hpp3(k,1)>=j) bw_win_bua1.set_win_hpp3(k-1,1,bw_win_bua1.get_win_hpp3(k,1)-j);
    else                  bw_win_bua1.set_win_hpp3(k-1,1,0);
    if (bw_win_bua1.get_win_hpp3(k,2)>=j) bw_win_bua1.set_win_hpp3(k-1,2,bw_win_bua1.get_win_hpp3(k,2)-j);
    else                  bw_win_bua1.set_win_hpp3(k-1,2,0);
    if (bw_win_bua1.get_win_hpp3(k,4)>=j) bw_win_bua1.set_win_hpp3(k-1,4,bw_win_bua1.get_win_hpp3(k,4)-j);
    else                  bw_win_bua1.set_win_hpp3(k-1,4,0);
    if (bw_win_bua1.get_win_hpp3(k,5)>=j) bw_win_bua1.set_win_hpp3(k-1,5,bw_win_bua1.get_win_hpp3(k,5)-j);
    else                  bw_win_bua1.set_win_hpp3(k-1,5,0);
    if (bw_win_bua1.get_win_hpp3(k,6)>=j) bw_win_bua1.set_win_hpp3(k-1,6,bw_win_bua1.get_win_hpp3(k,6)-j);
    else                  bw_win_bua1.set_win_hpp3(k-1,6,0);

    if (k==l)
    {
      bw_win_bua1.set_win_hpp3(k,0,0);
      bw_win_bua1.set_win_hpp3(k,1,0);
      bw_win_bua1.set_win_hpp3(k,2,0);
      bw_win_bua1.set_win_hpp3(k,3,0);
      bw_win_bua1.set_win_hpp3(k,4,0);
      bw_win_bua1.set_win_hpp3(k,5,0);
      bw_win_bua1.set_win_hpp3(k,6,0);
    }
  }

  for (k=m;k<=o;k++)
  {
    if (bw_win_bua1.get_win_hpp4(k,4)!=0)
    {
      SetWindowLong(bw_win_bua1.get_win_hnd(k),GWL_ID,k-j);
    }

    if (bw_win_bua1.get_win_hpp4(k,0)>=n) bw_win_bua1.set_win_hpp4(k-j,0,bw_win_bua1.get_win_hpp4(k,0)-n);  /* win num,x,y,hnd num,main hnd */
    bw_win_bua1.set_win_hpp4(k-j,1,bw_win_bua1.get_win_hpp4(k,1));
    bw_win_bua1.set_win_hpp4(k-j,2,bw_win_bua1.get_win_hpp4(k,2));
    bw_win_bua1.set_win_hpp4(k-j,3,k-j);

    if (bw_win_bua1.get_win_hpp4(k,4)==0) bw_win_bua1.set_win_hpp4(k-j,4,0);
    else bw_win_bua1.set_win_hpp4(k-j,4,bw_win_bua1.get_win_hpp4(k,4)-j);

    bw_win_bua1.set_win_hnd(k-j,bw_win_bua1.get_win_hnd(k));

    bw_win_bua1.set_win_fpp(k-j,bw_win_bua1.get_win_fpp(k));

  }

  for (k=o-j+1;k<=o;k++)
  {
    bw_win_bua1.set_win_hpp4(k,0,0);  /* win num,x,y,hnd num,main hnd */
    bw_win_bua1.set_win_hpp4(k,1,0);
    bw_win_bua1.set_win_hpp4(k,2,0);
    bw_win_bua1.set_win_hpp4(k,3,0);
    bw_win_bua1.set_win_hpp4(k,4,0);

    bw_win_bua1.set_win_hnd(k,0);
  }

  if (i==l)
  {
    bw_win_bua1.set_win_hpp3(i,0,0);
    bw_win_bua1.set_win_hpp3(i,1,0);
    bw_win_bua1.set_win_hpp3(i,2,0);
    bw_win_bua1.set_win_hpp3(i,3,0);
    bw_win_bua1.set_win_hpp3(i,4,0);
    bw_win_bua1.set_win_hpp3(i,5,0);
    bw_win_bua1.set_win_hpp3(i,6,0);
  }

  /* end mem var move */

  win_pp1=win_pp1-n;

  win_hpp1=win_hpp1-j;

  bw_xbase1.win_answer=0;

  return(0);
}

int bw_win::w_read_winfile(char *p_fn2,int len)
{
  int  p1,p2,same,ends;
  int  state1,state2,state3;
  int  state4,state5,state6;
  int  state7,state8,state9;
  int  state10;

  long li;

  int  is_tab=0;
  int  is_find=0;
  char ts[SMG_LEN*2];
//  char tmpc3;
  char tmpc5[STRU_NUM][FN_SIZE];
  int  tmpc6[STRU_NUM];
  char tmpc7[FN_SIZE];
  char tmpc8[FN_SIZE];
  char tmpc9[FN_SIZE];
  int  s_ps=(-1);
  int  s_ps1;
  int  i,j,k,l,m,n,o,p;
  int  lcnt,cmd;
//  int  scrn_type;
//  int  read_type;
  int  free_base;
//  char str[FN_SIZE];
  char str2[FN_SIZE];
  char str3[FN_SIZE];
  char str4[FN_SIZE];
  FILE *fp1;
  char stn[FN_SIZE];
  char st1[FN_SIZE];

  int  s_firstline;
  int  s_lastline;
  int  s_exist;
  int  s_beginposi;
  int  s_endposi;

//  MessageBox(bw_main1.win_hwnd1,"ee","ee",MB_OK);

  strcpy(texts1 ,"usetable= ");
  strcpy(texts2 ,"enddefine ");
  strcpy(texts3 ,"screenseg ");
  strcpy(texts4 ,"endscreen ");
  strcpy(texts5 ,"readvatype");
  strcpy(texts6 ,"findfile= ");
  strcpy(texts7 ,"findbase= ");
  strcpy(texts8 ,"switchbmp ");
  strcpy(texts9 ,"switchtm= ");
  strcpy(texts10,"ci_mode   ");

  free_base=bw_xbase1.w_free_xbase();


//  MessageBox(bw_main1.win_hwnd1,"dd","dd",MB_OK);

  fp1=fopen(p_fn2,"r");    /* fetch page of screen format from screen file */
  if (fp1==NULL)
  {
    w_atten1(p_fn2);
    return(1);
  }

//  MessageBox(bw_main1.win_hwnd1,"cc","cc",MB_OK);
  
  for (k=win_pp1;k<WIN_NUM-1;k++)
  {
    bw_win_bua1.set_win_timer(k,0);

    bw_win_bua1.set_win_ci_mode(k,0);

    s_firstline=1;
    s_lastline=1;

    for (j=1;j<LIN_NUM;j++)
      for (i=1;i<COL_NUM;i++)
	bw_buffa1.set_tmpc1(k,j,i,' ');
    lcnt=0;
    bw_win_bua1.set_win_switch_bmp(k,0);
    for (i=1;i<LIN_NUM+10;i++)
    {
      cmd=0;
      for (n=0;n<SMG_LEN*2;n++) ts[n]=' ';
      fgets(ts,SMG_LEN*2,fp1);
      if (feof(fp1))
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
      state7=0;
      state8=0;
      state9=0;
      state10=0;
      j=0;
      while (p1<COL_NUM)  /* scan this line */
      {
	for (j=j;j<=COL_NUM-1;j++) if (ts[j]=='&') break; /* locate for '&' */
	j++;
	p1=j;
	if (p1>COL_NUM-1) break;

        // find usetable & stru name
	same=1;
	for (p2=p1;p2<=p1+9-1;p2++)  
	{
	  if (texts1[p2-p1]==' ') break;
	  if (ts[p2]!=texts1[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  state1=1;  // there is keyword "usetable" 
	  is_tab=1;  // this scrn file is table screen 

	  s_ps++;
	  if (s_ps>=STRU_NUM) s_ps=STRU_NUM-1;

	  for (l=0;l<FN_SIZE;l++)
	  {
	    tmpc5[s_ps][l]=ts[p1+9+l];
	    if ((ts[p1+9+l]==0)||
		(ts[p1+9+l]=='\n')||
		(ts[p1+9+l]==10))
	    {
	      tmpc5[s_ps][l]=' ';
	      break;
	    }
	  }
	}

        // find findbase name
	same=1;
	for (p2=p1;p2<=p1+9-1;p2++)  
	{
	  if (texts7[p2-p1]==' ') break;
	  if (ts[p2]!=texts7[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  state6=1;
          is_find=1;

	  for (l=0;l<FN_SIZE;l++)
	  {
	    tmpc8[l]=ts[p1+9+l];
	    if ((ts[p1+9+l]>=0)&&
		(ts[p1+9+l]<=' '))
	    {
	      tmpc8[l]=0;
	      break;
	    }
	  }
	}

	// find timer name
	same=1;
	for (p2=p1;p2<=p1+9-1;p2++)  
	{
	  if (texts9[p2-p1]==' ') break;
	  if (ts[p2]!=texts9[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
          state9=1;

	  for (l=0;l<FN_SIZE;l++)
	  {
	    tmpc9[l]=ts[p1+9+l];
	    if ((ts[p1+9+l]>=0)&&
		(ts[p1+9+l]<=' '))
	    {
	      tmpc9[l]=0;
	      break;
	    }
	  }
	}

	same=1;
	for (p2=p1;p2<=p1+10-1;p2++)  /* recnigze keywords */
	{
	  if (texts5[p2-p1]==' ') break;
	  if (ts[p2]!=texts5[p2-p1])
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
	for (p2=p1;p2<=p1+10-1;p2++)  /* recnigze keywords */
	{
	  if (texts10[p2-p1]==' ') break;
	  if (ts[p2]!=texts10[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  bw_win_bua1.set_win_ci_mode(k,1);
          state10=1;
	}

	same=1;
	for (p2=p1;p2<=p1+10-1;p2++)  /* recnigze keywords */
	{
	  if (texts8[p2-p1]==' ') break;
	  if (ts[p2]!=texts8[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  state8=1;
	}

	same=1;
	for (p2=p1;p2<=p1+10-1;p2++)
	{
	  if (texts2[p2-p1]==' ') break;
	  if (ts[p2]!=texts2[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state2=1;

	same=1;
	for (p2=p1;p2<=p1+10-1;p2++)
	{
	  if (texts3[p2-p1]==' ') break;
	  if (ts[p2]!=texts3[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state3=1;

	same=1;
	for (p2=p1;p2<=p1+10-1;p2++)
	{
	  if (texts4[p2-p1]==' ') break;
	  if (ts[p2]!=texts4[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state4=1;

	same=1;
	for (p2=p1;p2<=p1+10-1;p2++)
	{
	  if (texts6[p2-p1]==' ') break;
	  if (ts[p2]!=texts6[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  state7=1;
	  o=p1+9;
	  for (p=o;p<COL_NUM;p++)
	  {
	    if ((ts[p]<=' ')&&(ts[p]>=0))
	    {
	      tmpc7[p-o]=0;
	      break;
	    }
	    else tmpc7[p-o]=ts[p];
          }
        }
      }
      if (state1==1)  cmd=1; /* screentype */
      if (state5==1)  cmd=1; /* screentype */
      if (state2==1)  cmd=1; /* enddefine  */
      if (state6==1)  cmd=1; /* find findbase*/
      if (state7==1)  cmd=1; /* find define  */
      if (state10==1) cmd=1; /* ci_mode */
      if (state8==1)
      {
	cmd=1; /* switch bmp */
	bw_win_bua1.set_win_switch_bmp(k,1);
      }
      if (state9==1)
      {
	cmd=1; // timer
        bw_inkey1.char2long(tmpc9,&li);
	bw_win_bua1.set_win_timer(k,li);
      }
      if (state3==1) break; /* screenseg */
      if (state4==1)        /* endscreen */
      {
	ends=1;
	break;
      }
      scnt=k;
      if (cmd==0) lcnt++;
      else
      {
	cmd=0;
	continue;
      }

      if (bw_win_bua1.get_win_ci_mode(k)==1)
      {
        ts[COL_NUM-1]=0;

        if (bw_inkey1.strempty(ts)==1)
        {
	  if (s_firstline==1)
	  {
	    s_exist=0;
	    for (j=0;j<COL_NUM;j++)
	    {
	      if ((ts[j]>' ')||(ts[j]<0))
	      {
	        s_exist=1;
	        break;
	      }
	    }
	    if (s_exist==1) s_beginposi=j;
            else s_beginposi=0;
          
	    s_exist=0;
	    for (j=COL_NUM-1;j>=0;j--)
	    {
	      if ((ts[j]>' ')||(ts[j]<0))
	      {
	        s_exist=1;
	        break;
	      }
	    }
	    if (s_exist==1) s_endposi=j;
            else s_endposi=1;

	    for (j=0;j<COL_NUM;j++)
	    {
	      ts[j]=' ';
	    }

	    ts[s_beginposi]='.';
            ts[s_endposi]='.';

            bw_win_bua1.set_win_ci_posi(k,0,s_beginposi+1);
	    bw_win_bua1.set_win_ci_posi(k,1,s_endposi+1);

	    s_firstline=0;
	  }
	  else
	  {
            s_exist=0;
	    for (j=0;j<COL_NUM;j++)
	    {
	      if ((ts[j]>' ')||(ts[j]<0))
	      {
	        s_exist=1;
	        break;
	      }
	    }
	    if (s_exist==1) s_beginposi=j;
            else s_beginposi=0;
          
            s_exist=0;
	    for (j=COL_NUM-1;j>=0;j--)
	    {
	      if ((ts[j]>' ')||(ts[j]<0))
	      {
	        s_exist=1;
	        break;
	      }
	    }
	    if (s_exist==1) s_endposi=j;
            else s_endposi=1;

	    if (bw_main1.win_lang==1)
	    {
	      ts[s_beginposi]=' ';
	      ts[s_endposi]=' ';
	    }
	    else
	    {
	      ts[s_beginposi]=' ';
	      ts[s_endposi]=' ';

	      if (s_beginposi+1<COL_NUM) ts[s_beginposi+1]=' ';
	      if (s_endposi-1>=0)        ts[s_endposi-1]=' ';
            }
	  }
        }
        else
        {
	  if (s_firstline==0)
	  {
	    if (s_lastline==1)
            {
	      if ((lcnt-1>0)&&(lcnt-1<LIN_NUM))
	      {
	        for (j=1;j<COL_NUM;j++)
	        {
	          bw_buffa1.set_tmpc1(k,lcnt-1,j,' ');
	        }
	      }
	      s_lastline=0;

	      bw_buffa1.set_tmpc1(k,lcnt-1,s_beginposi+1,'.');
	      bw_buffa1.set_tmpc1(k,lcnt-1,s_endposi+1,'.');

	    }
          }
        }

      }

      for (j=0;j<COL_NUM;j++)
      {
	if ((ts[j]<' ')&&(ts[j]>=0)) ts[j]=' ';
	bw_buffa1.set_tmpc1(k,lcnt,j+1,ts[j]);
      }

      if (feof(fp1))
      {
	ends=1;
	break;
      }
    }
    if (ends==1) break;
  }

  m=win_pp1;

  fclose(fp1);

  if (ends==1)
  {
    if (s_ps+1>free_base)
    {
      w_atten22();
      return(1);
    }
    else
    {
      win_pp1=k+1;
    }
  }
  else
  {
    w_atten3();
    return(1);
  }

  w_login_win(m,k,p_fn2,len,tmpc7,FN_SIZE);
  
  if (is_tab==1)  /* it is a table scrn */
  {
    l=0;
    for (i=0;i<=s_ps;i++)     /* login base ,fetch buff pp */
    {
      j=bw_xbase1.w_login_xbase(l);
      if (j<0)
      {
	w_atten58();
	w_dele_win_pp(m);
	return(1);
      }
      tmpc6[i]=j;
      l=j+1;
    }

    for (i=m;i<=k;i++)  /* mark win base pp */
    {
      for (j=0;j<STRU_NUM;j++)
      {
	bw_win_bua1.set_win_pp9(j,i,0);
      }

      for (j=0;j<=s_ps;j++)
      {
        if (tmpc6[j]>=STRU_NUM) continue;
	bw_win_bua1.set_win_pp9(tmpc6[j],i,1);
	bw_xbase_bua1.set_win_state1(tmpc6[j],1);
      }
    }

    for (i=0;i<=1;i++) for (j=0;j<=s_ps;j++)
    {
      if (tmpc6[j]>=STRU_NUM) continue;
      bw_win_bub1.set_win_tabname(i,tmpc6[j],"                      ",20);
    }
			   /* stru&base nam in win 0-stru 1-base*/
    for (s_ps1=0;s_ps1<=s_ps;s_ps1++)  /* fetch stru & base name from tmpc5 */
    {
      if (tmpc6[s_ps1]>=STRU_NUM) continue;
      j=0;
      for (i=0;i<FN_SIZE;i++)          /* fetch base name */
      {
	if (tmpc5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten4();
	w_dele_xbase_state(m);
        w_dele_win_pp(m);
	return(1);
      }
      else
      {
	bw_inkey1.strpcut(tmpc5[s_ps1],0,i,FN_SIZE,stn,FN_SIZE);
	bw_win_bub1.set_win_tabname(1,tmpc6[s_ps1],stn,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch stru name */
      {
	if (tmpc5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ' ' */
      {
	w_atten5();
	w_dele_xbase_state(m);
        w_dele_win_pp(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten6();
	else bw_inkey1.strpcut(tmpc5[s_ps1],p1+5,i-p1-5,FN_SIZE,stn,FN_SIZE);
	bw_win_bub1.set_win_tabname(0,tmpc6[s_ps1],stn,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch base type */
      {
	if (tmpc5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ' ' */
      {
	w_atten59();
	w_dele_xbase_state(m);
        w_dele_win_pp(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten60();
	else bw_inkey1.strpcut(tmpc5[s_ps1],p1+9,i-p1-9,FN_SIZE,str2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch backup type */
      {
	if ((tmpc5[s_ps1][i]==' ')||(tmpc5[s_ps1][i]==','))
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ' ' */
      {
	w_atten61();
	w_dele_xbase_state(m);
	w_dele_win_pp(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten62();
	else bw_inkey1.strpcut(tmpc5[s_ps1],p1+7,i-p1-7,FN_SIZE,str3,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch carryon &carryoff */
      {
	if (tmpc5[s_ps1][i]==' ')
	{
	  j=1;
	  break;
	}
      }
      if (j==1)  /* not find ' ' */
      {
	if (i-p1>0)
	{
	  bw_inkey1.strpcut(tmpc5[s_ps1],p1,i-p1,FN_SIZE,str4,FN_SIZE);
	  if (strncmp(str4,"carryon",7)==0)
	    bw_xbase_bua1.set_win_carry_on(tmpc6[s_ps1],1);
	  else
	    bw_xbase_bua1.set_win_carry_on(tmpc6[s_ps1],0);
	}
	else bw_xbase_bua1.set_win_carry_on(tmpc6[s_ps1],0);
      }
      else bw_xbase_bua1.set_win_carry_on(tmpc6[s_ps1],0);
    }
  }

  for (s_ps1=0;s_ps1<=s_ps;s_ps1++)  /* fetch stru & base name from tmpc5 */
  {
    if (tmpc6[s_ps1]>=STRU_NUM) continue;

    if (strcmp(str2,"xbase")==0) bw_xbase_bua1.set_win_base_type(tmpc6[s_ps1],0);
    else bw_xbase_bua1.set_win_base_type(tmpc6[s_ps1],1);

    if (strcmp(str3,"1")==0) bw_xbase_bua1.set_win_base_backup(tmpc6[s_ps1],1);
    else bw_xbase_bua1.set_win_base_backup(tmpc6[s_ps1],0);
  }

  if (is_find==1)
  {
    bw_inkey1.strtrim(tmpc8);
    i=bw_inkey1.strlocc(tmpc8,'.');
    tmpc8[i]=0;
    strcat(tmpc8,".dbf");

    for (j=0;j<STRU_NUM;j++)
    {
      if (bw_xbase_bua1.get_win_state1(j)==1)
      {
        bw_xbase_bua1.get_win_basename(j,st1,FN_SIZE);

	if (strncmp(tmpc8,st1,strlen(tmpc8))==0)
	{
	  bw_xbase_bua1.set_win_state10(j,1);
	}
	else bw_xbase_bua1.set_win_state10(j,0);
      }
      else bw_xbase_bua1.set_win_state10(j,0);
    }
  }

  return(0);
}

int bw_win::w_dele_xbase_state(int wpp)
{
  int i;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win_bua1.get_win_pp9(i,wpp)==1)
    {
      bw_xbase_bua1.set_win_state1(i,0);
      bw_win_bub1.set_win_tabname(0,i,"",0);
      bw_win_bub1.set_win_tabname(1,i,"",0);
    }
  }

  return(0);
}

int bw_win::w_echo_win_pa(int p_pagecnt,int mark)
{ 
  HFONT holdfont,hfont;
  HDC   hdc;
  int   p1,p2,p4,p5,p7,p8;
  int   state1;
//  int   state5;
  int   state7;
  int   i,j,k;
  int   pp1,pp3;
//  int   hpp1;
  char  str[SMG_LEN];
//  char  str1[COL_NUM];

  if (bw_win_bua1.get_win_pp2(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((bw_win_bua1.get_win_pp2(i,1)==0)&&(i>0))
    {
      i--;
    }
    bw_win_bua1.set_win_pp2(p_pagecnt,0,bw_win_bua1.get_win_pp2(i,1)+1);
    pp1=bw_win_bua1.get_win_pp2(i,1);
  }
  else pp1=bw_win_bua1.get_win_pp2(p_pagecnt,0)-1;

  hdc=GetDC(bw_main1.win_hwnd);

  if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  p7=0;   
  p8=0;   

  for (i=1;i<LIN_NUM;i++)
  {
    if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
    {                                                                                    
      p1=COL_NUM-1;
      p2=0;
      for (j=1;j<COL_NUM;j++)  
      {
        if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
        {
	  p1=j;
	  break;
        }
      }
      for (j=COL_NUM-1;j>=1;j--)
      {
	if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
        {
	  p2=j;
	  break;
        }
      }
      if (p2<p1) continue;
    }
    else
    {
      p1=bw_win_bua1.get_win_ci_posi(p_pagecnt,0);
      p2=bw_win_bua1.get_win_ci_posi(p_pagecnt,1);

      j=0;
      for (k=p1;k<=p2;k++)
      {
	if ((bw_buffa1.get_tmpc1(p_pagecnt,i,k)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,k)<0))
	{
	  j=1;
	  break;
	}
      }

      if (j==0) continue;
    }

    state1=0;
    if (p8==0) p8=p1;
    if (p7==0) p7=i;
    p4=0;
    p5=0;
    pp3=0;
    state7=0;
    for (j=p1;j<=p2;j++)  
    {
      if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='&')
      {
        pp1++;
	p4=0;      
	p5=1;      
        state1=1; 
	if (mark==1)
	{
	}
      }
      else
      {
	if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)<=' ')
	{
          if (state7==1) continue;
	  if (mark==1)
	  {
	    if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0)
	    {
	      if (pp3==1)
	      {
		pp3=0;
		continue;
              }
	      else
	      {
                pp3=1;
		str[0]=bw_buffa1.get_tmpc1(p_pagecnt,i,j);
		if (bw_buffa1.get_tmpc1(p_pagecnt,i,j+1)!='&')
                {
		  str[1]=bw_buffa1.get_tmpc1(p_pagecnt,i,j+1);
                  str[2]=0;
                }
                else str[1]=0;
		if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
                {
		  TextOut(hdc,(int)((j-p8)*bw_main1.win_edit_xchar)
                        ,(int)((i-p7)*bw_main1.win_edit_ychar)
		        ,str,strlen(str));
                }
		else
                {
		  TextOut(hdc,(int)((j-p8)*bw_main1.win_xchar)
                        ,(int)((i-p7)*bw_main1.win_ychar)
		        ,str,strlen(str));
                }
              }
            }
          }
	  state1=0;
	  if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      p5=0;
	    }
	  }
	  else
	  {
	    state1=0;
	    pp3=0;
	  }
	}
	else
	{
	  pp3=0;
	  if (state1==1)
	  {
	    if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='(')
	      &&(bw_buffa1.get_tmpc1(p_pagecnt,i,j-1)!='&'))
	    {
	      state7=1;
              state1=0;
              continue;
            }
	    if ((p4==0)&&(bw_buffa1.get_tmpc1(p_pagecnt,i,j-1)=='%'))
	    {
	      p4++;
	    }
	    p4++;
	    if (mark==1)
            {
	    }
	  }
	  else
	  {
	    if (p5==1)
	    {
	      p5=0;
	    }
	    if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)==')')
            {
	      state7=0;
	      continue;
	    }
	    if (state7==1) continue;
	    if (mark==1)
	    {
	      str[0]=bw_buffa1.get_tmpc1(p_pagecnt,i,j);
	      str[1]=0;
	      if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
              {
		TextOut(hdc,(int)((j-p8)*bw_main1.win_edit_xchar)
		     ,(int)((i-p7)*bw_main1.win_edit_ychar)
	             ,str,strlen(str));
              }
              else
              {
		TextOut(hdc,(int)((j-p8)*bw_main1.win_xchar)
		     ,(int)((i-p7)*bw_main1.win_ychar)
	             ,str,strlen(str));
              }
            }
	  }
	}
      }
    }
  }

  if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
  {
    SelectObject(hdc,holdfont);
  }

  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}

int bw_win::w_echo_win_cr(int p_pagecnt,int mark)
{ 
//  HDC  hdc;
//  HWND hnd;
  int  p1,p2,p4,p5,p6,p7,p8,p9,p10,p10a;
  int  state1;
//  int  state5;
  int  state7;
  int  i,j,k,l;
  int  pp1,pp3;
  int  t1,t2;
//  char str[SMG_LEN];
  char s1[SMG_LEN];
  char s2[FLD_NAME_LEN];

  win_mark=mark;

  for (i=0;i<WIN_STYLE_NUM;i++) bw_win_bua1.set_win_style(p_pagecnt,i,0);

  if (bw_win_bua1.get_win_pp2(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((bw_win_bua1.get_win_pp2(i,1)==0)&&(i>0))
    {
      i--;
    }
    bw_win_bua1.set_win_pp2(p_pagecnt,0,bw_win_bua1.get_win_pp2(i,1)+1);
    pp1=bw_win_bua1.get_win_pp2(i,1);
  }
  else pp1=bw_win_bua1.get_win_pp2(p_pagecnt,0)-1;

  win_hpp5=win_hpp1;

  pp3=win_hpp5;

  if (win_hpp5>=HND_NUM) return(0);

  p7=0;
  p8=0;   
  p9=0;   
  p10=0;  
  p10a=0; 

  for (i=1;i<LIN_NUM;i++) for (j=1;j<COL_NUM;j++) bw_buff1.set_linecol(p_pagecnt,i,j,0);

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
    {                                                                                    
      p1=COL_NUM-1;
      p2=0;
      for (j=1;j<COL_NUM;j++)  
      {
        if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
        {
	  p1=j;
	  break;
        }
      }
      for (j=COL_NUM-1;j>=1;j--)
      {
	if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
        {
	  p2=j;
	  break;
        }
      }
      if (p2<p1) continue;
    }
    else
    {
      p1=bw_win_bua1.get_win_ci_posi(p_pagecnt,0);
      p2=bw_win_bua1.get_win_ci_posi(p_pagecnt,1);

      j=0;
      for (k=p1;k<=p2;k++)
      {
	if ((bw_buffa1.get_tmpc1(p_pagecnt,i,k)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,k)<0))
	{
	  j=1;
	  break;
	}
      }

      if (j==0) continue;
    }

    state1=0;
    if (p7==0) p7=i;
    if (p8==0) p8=p1;
    if (p7!=0) bw_win_bua1.set_win_con(p_pagecnt,1,p7);
    if (p8!=0) bw_win_bua1.set_win_con(p_pagecnt,0,p8);
    if (p9==0) p9=p2-p1+2;
    if (p9!=0)   bw_win_bua1.set_win_con(p_pagecnt,2,p9);
    if (p10==0)  p10=i;

    if (bw_main1.win_cre_menu==1) p10a=i-p10+4;
    else p10a=i-p10+3;

    if (p10a!=0) bw_win_bua1.set_win_con(p_pagecnt,3,p10a);
    p4=0;
    p5=0;
    p6=0;

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='&')
      {
	if (p5==1)
	{
	  bw_win_bua1.set_1fldlen(pp1,j-1-p6);

	  bw_win_bua1.set_win_style(p_pagecnt,1,1);

	  bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	  if (s2[0]=='(') bw_win_bua1.set_win_style(p_pagecnt,2,1);
	  if (s2[0]=='[') bw_win_bua1.set_win_style(p_pagecnt,3,1);
	  if (s2[0]=='@') bw_win_bua1.set_win_style(p_pagecnt,4,1);
	  if (s2[0]=='#') bw_win_bua1.set_win_style(p_pagecnt,5,1);
	  if (s2[0]=='%') bw_win_bua1.set_win_style(p_pagecnt,6,1);
	  if (s2[0]==':') bw_win_bua1.set_win_style(p_pagecnt,7,1);
	  if (s2[0]=='?') bw_win_bua1.set_win_style(p_pagecnt,8,1);
	  if (s2[0]=='+') bw_win_bua1.set_win_style(p_pagecnt,9,1);
	  if (s2[0]=='-') bw_win_bua1.set_win_style(p_pagecnt,9,1);

	}

	pp1++;
	if (bw_buffa1.get_tmpc1(p_pagecnt,i,j+1)=='#') bw_buff1.set_linecol(p_pagecnt,i,j+1,pp1);
	else bw_buff1.set_linecol(p_pagecnt,i,j,pp1);
	p4=0;      
	p5=1;      
	state1=1;
        p6=j;      

      }
      else
      {
	if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)<=' ')
	{
          if (state7==1) continue;
	  state1=0;
	  if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.set_win_style(p_pagecnt,1,1);

	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if (s2[0]=='(') bw_win_bua1.set_win_style(p_pagecnt,2,1);
	      if (s2[0]=='[') bw_win_bua1.set_win_style(p_pagecnt,3,1);
	      if (s2[0]=='@') bw_win_bua1.set_win_style(p_pagecnt,4,1);
	      if (s2[0]=='#') bw_win_bua1.set_win_style(p_pagecnt,5,1);
	      if (s2[0]=='%') bw_win_bua1.set_win_style(p_pagecnt,6,1);
	      if (s2[0]==':') bw_win_bua1.set_win_style(p_pagecnt,7,1);
	      if (s2[0]=='?') bw_win_bua1.set_win_style(p_pagecnt,8,1);
	      if (s2[0]=='+') bw_win_bua1.set_win_style(p_pagecnt,9,1);
	      if (s2[0]=='-') bw_win_bua1.set_win_style(p_pagecnt,9,1);

	      if ((s2[0]=='#')||(s2[0]=='%'))
	      {
		bw_win_bua1.set_1fldlen(pp1,j-p6);
	      }
	      else
	      {
		if (s2[0]=='@')
		{
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buffa1.get_tmpc1(p_pagecnt,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buffa1.get_tmpc1(p_pagecnt,i,t2)==')') break;
		  }

                  s1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    s1[l-t1-1]=bw_buffa1.get_tmpc1(p_pagecnt,i,l);
		    s1[l-t1]=0;
                  }

		  w_cre_ci_butt(p_pagecnt,s1,SMG_LEN,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
		bw_win_bua1.set_1fldlen(pp1,j-p6);
	      }
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
	    if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='(')
	      &&(bw_buffa1.get_tmpc1(p_pagecnt,i,j-1)!='&'))
	    {
		bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

		if (s2[0]=='@')
		{
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buffa1.get_tmpc1(p_pagecnt,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buffa1.get_tmpc1(p_pagecnt,i,t2)==')') break;
		  }

		  s1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    s1[l-t1-1]=bw_buffa1.get_tmpc1(p_pagecnt,i,l);
		    s1[l-t1]=0;
		  }

		  w_cre_ci_butt(p_pagecnt,s1,SMG_LEN,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}

              state7=1;
	      state1=0;
	      bw_win_bua1.set_1fldlen(pp1,j-p6);
              continue;
	    }
	    if ((p4==0)&&(bw_buffa1.get_tmpc1(p_pagecnt,i,j-1)=='%'))
	    {
	      bw_win_bua1.set_1fldname1(pp1,p4,'%');
	      p4++;
	    }
	    bw_win_bua1.set_1fldname1(pp1,p4+0,bw_buffa1.get_tmpc1(p_pagecnt,i,j));
	    bw_win_bua1.set_1fldname1(pp1,p4+1,0);
	    bw_win_bua1.set_1fldtype(pp1,'c');
	    p4++;
	  }
	  else
	  {
	    if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)==')')
	    {
	      state7=0;
	      continue;
            }
	    if (p5==1)
	    {
	      bw_win_bua1.set_win_style(p_pagecnt,1,1);

	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if (s2[0]=='(') bw_win_bua1.set_win_style(p_pagecnt,2,1);
	      if (s2[0]=='[') bw_win_bua1.set_win_style(p_pagecnt,3,1);
	      if (s2[0]=='@') bw_win_bua1.set_win_style(p_pagecnt,4,1);
	      if (s2[0]=='#') bw_win_bua1.set_win_style(p_pagecnt,5,1);
	      if (s2[0]=='%') bw_win_bua1.set_win_style(p_pagecnt,6,1);
	      if (s2[0]==':') bw_win_bua1.set_win_style(p_pagecnt,7,1);
	      if (s2[0]=='?') bw_win_bua1.set_win_style(p_pagecnt,8,1);
	      if (s2[0]=='+') bw_win_bua1.set_win_style(p_pagecnt,9,1);
	      if (s2[0]=='-') bw_win_bua1.set_win_style(p_pagecnt,9,1);

	      if ((s2[0]=='#')||(s2[0]=='%'))
	      {
		bw_win_bua1.set_1fldlen(pp1,j-p6);
	      }
	      else
	      {
		if (s2[0]=='@')
		{
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buffa1.get_tmpc1(p_pagecnt,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buffa1.get_tmpc1(p_pagecnt,i,t2)==')') break;
		  }

		  s1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    s1[l-t1-1]=bw_buffa1.get_tmpc1(p_pagecnt,i,l);
		    s1[l-t1]=0;
                  }

		  w_cre_ci_butt(p_pagecnt,s1,SMG_LEN,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
		bw_win_bua1.set_1fldlen(pp1,j-p6);
	      }
	      p5=0;
	    }
	  }
	}
      }
    }

    if (p5==1)
    {
      bw_win_bua1.set_1fldlen(pp1,j-1-p6);

      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

      if (s2[0]=='@')
      {
	for (t1=p6;t1<COL_NUM;t1++)
        {
          if (bw_buffa1.get_tmpc1(p_pagecnt,i,t1)=='(') break;
        }

        for (t2=p6;t2<COL_NUM;t2++)
        {
          if (bw_buffa1.get_tmpc1(p_pagecnt,i,t2)==')') break;
        }

        s1[0]=0;

        for (l=t1+1;l<t2;l++)
        {
          s1[l-t1-1]=bw_buffa1.get_tmpc1(p_pagecnt,i,l);
	  s1[l-t1]=0;
        }

        w_cre_ci_butt(p_pagecnt,s1,SMG_LEN,p6,p7,p8,i);

	if (win_hpp5>=HND_NUM) return(0);
      }
    }
  }

  win_tfpp=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=pp3;i<=bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5);i++)
  {
    bw_win_bua1.set_win_fpp(i,(FARPROC)GetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tfpp);
  }

  bw_win_bua1.set_win_hpp7(p_pagecnt,0,bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),6));
  bw_win_bua1.set_win_hpp7(p_pagecnt,1,bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5));

  win_hpp1=win_hpp5;

  bw_win_bua1.set_win_pp2(p_pagecnt,1,pp1);

  // adjust field length for 800*600 256c mode
  /*
  for (i=bw_win_bua1.get_win_pp2(p_pagecnt,0);i<=bw_win_bua1.get_win_pp2(p_pagecnt,1);i++)
  {
    if (bw_win_bua1.get_1fldlen(i)>18)
    {
      bw_win_bua1.set_1fldlen(i,bw_win_bua1.get_1fldlen(i)-4);
    }
  }
  */
  return(0);
}

int bw_win::w_cre_ci_butt(int p_pagecnt,char *p_s1,int len,int p6,int p7,int p8,int i)
{
  HWND hnd;
  int  l,j;
  //char s2[SMG_LEN];
/*
  if (len>SMG_LEN) l=SMG_LEN;
  else l=len;
  for (j=0;j<l-1;j++)
  {
    s2[j]=s1[j];
  }
  if (l-1<0) s2[0]=0;
  else  s2[l-1]=0;
*/
  //bw_main1.set_string(s2,SMG_LEN,s1,len);

  if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("button",p_s1
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,(int)((p6-p8)*bw_main1.win_edit_xchar)
		      ,(int)((i-p7)*bw_main1.win_edit_ychar-3)
		      ,(int)((strlen(p_s1)+3)*bw_main1.win_edit_xchar)
		      ,(int)(bw_main1.win_edit_ychar+6)
		      ,bw_main1.win_hwnd,(HMENU)win_hpp5
		      ,bw_main1.win_ins,NULL);
    bw_win_bua1.set_win_hnd(win_hpp5,hnd);
    if (bw_win_bua1.get_win_hnd(win_hpp5)==NULL) bw_main1.win_cre_ok=0;
  }
  else
  {
    hnd=CreateWindow("button",p_s1
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,(int)((p6-p8)*bw_main1.win_xchar)
		      ,(int)((i-p7)*bw_main1.win_ychar-3)
		      ,(int)((3+strlen(p_s1))*bw_main1.win_xchar)
		      ,(int)(bw_main1.win_ychar+6)
		      ,bw_main1.win_hwnd,(HMENU)win_hpp5
		      ,bw_main1.win_ins,NULL);
    bw_win_bua1.set_win_hnd(win_hpp5,hnd);
    if (bw_win_bua1.get_win_hnd(win_hpp5)==NULL) bw_main1.win_cre_ok=0;
  }

  win_hpp5++;
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,0,p_pagecnt);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,1,p6);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,2,i);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,3,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,4,p_pagecnt-bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(p_pagecnt),0)+bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),0));

  return(0);
}

int bw_win::w_cre_ci_edit(int p_pagecnt,int p6,int p7,int p8,int i)
{
  HWND hnd;

  if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("edit",""
		,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
		,(int)((p6-p8)*bw_main1.win_edit_xchar)
		,(int)((i-p7)*bw_main1.win_edit_ychar-6)
		,(int)(4*bw_main1.win_edit_xchar)
		,(int)(bw_main1.win_edit_ychar+12)
		,bw_main1.win_hwnd,(HMENU)win_hpp5
		,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("edit",""
		,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
		,(int)((p6-p8)*bw_main1.win_xchar)
		,(int)((i-p7)*bw_main1.win_ychar-6)
		,(int)(4*bw_main1.win_xchar)
		,(int)(bw_main1.win_ychar+12)
		,bw_main1.win_hwnd,(HMENU)win_hpp5
		,bw_main1.win_ins,NULL);
  }

  bw_win_bua1.set_win_hnd(win_hpp5,hnd);
  if (bw_win_bua1.get_win_hnd(win_hpp5)==NULL) bw_main1.win_cre_ok=0;

  win_hpp5++;
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,0,p_pagecnt);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,1,p6);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,2,i);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,3,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,4,p_pagecnt-bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(p_pagecnt),0)+bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),0));

  return(0);
}

int bw_win::w_cre_ci_radio(int p_pagecnt,int p6,int p7,int p8,int i)
{
  HWND hnd;

  if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON
			,(int)((p6-p8)*bw_main1.win_edit_xchar)
			,(int)((i-p7)*bw_main1.win_edit_ychar)
			,(int)(2*bw_main1.win_edit_xchar)
			,(int)(bw_main1.win_edit_ychar)
			,bw_main1.win_hwnd,(HMENU)win_hpp5
			,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON
			,(int)((p6-p8)*bw_main1.win_xchar)
			,(int)((i-p7)*bw_main1.win_ychar)
			,(int)(2*bw_main1.win_xchar)
			,(int)(bw_main1.win_ychar)
			,bw_main1.win_hwnd,(HMENU)win_hpp5
			,bw_main1.win_ins,NULL);
  }

  bw_win_bua1.set_win_hnd(win_hpp5,hnd);

  if (bw_win_bua1.get_win_hnd(win_hpp5)==NULL) bw_main1.win_cre_ok=0;

  win_hpp5++;
  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,0,p_pagecnt);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,1,p6);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,2,i);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,3,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,4,p_pagecnt-bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(p_pagecnt),0)+bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),0));

  return(0);
}

int bw_win::w_cre_ci_check(int p_pagecnt,int p6,int p7,int p8,int i)
{
  HWND hnd;

  if (bw_win_bua1.get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_CHECKBOX
			,(int)((p6-p8)*bw_main1.win_edit_xchar)
			,(int)((i-p7)*bw_main1.win_edit_ychar)
			,(int)(2*bw_main1.win_edit_xchar)
			,(int)(bw_main1.win_edit_ychar)
			,bw_main1.win_hwnd,(HMENU)win_hpp5
			,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_CHECKBOX
			,(int)((p6-p8)*bw_main1.win_xchar)
			,(int)((i-p7)*bw_main1.win_ychar)
			,(int)(2*bw_main1.win_xchar)
			,(int)(bw_main1.win_ychar)
			,bw_main1.win_hwnd,(HMENU)win_hpp5
			,bw_main1.win_ins,NULL);
  }

  bw_win_bua1.set_win_hnd(win_hpp5,hnd);

  if (bw_win_bua1.get_win_hnd(win_hpp5)==NULL) bw_main1.win_cre_ok=0;

  win_hpp5++;

  bw_win_bua1.set_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,0,p_pagecnt);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,1,p6);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,2,i);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,3,win_hpp5-1);
  bw_win_bua1.set_win_hpp4(win_hpp5-1,4,p_pagecnt-bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(p_pagecnt),0)+bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),0));

  return(0);
}

int bw_win::w_echo_win_edit(int p_pagecnt,int mark)
{
//  HDC  hdc;
//  HWND hnd;
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
//  int  state5;
  int  i,j;
  int  pp1;
  int  hpp1;
//  char str[SMG_LEN];
  char s2[FLD_NAME_LEN];

  win_mark=mark;

  if (bw_win_bua1.get_win_pp2(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((bw_win_bua1.get_win_pp2(i,1)==0)&&(i>0))
    {
      i--;
    }
    bw_win_bua1.set_win_pp2(p_pagecnt,0,bw_win_bua1.get_win_pp2(i,1)+1);
    pp1=bw_win_bua1.get_win_pp2(i,1);
  }
  else pp1=bw_win_bua1.get_win_pp2(p_pagecnt,0)-1;

  hpp1=win_hpp5;

  p7=0;  
  p8=0;

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++)  
    {
      if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue; 
    if (p7==0) p7=i;
    if (p8==0) p8=p1;
    state1=0;
    p4=0;
    p5=0;
    p6=0;
    for (j=p1;j<=p2;j++) 
    {
      if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='&')
      {
	if (p5==1)
	{
	  bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	  if ((s2[0]!='+')&&(s2[0]!='-'))
	  {
	  }
	  else
	  {
	    if (bw_inkey1.strempty(s2)==1)
	    {
	      w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

	      if (win_hpp5>=HND_NUM) return(0);
	    }
	  }
	  p5=0;
	}

        pp1++;
	p4=0;
	p5=1;      
        state1=1;  
	p6=j;    
      }
      else
      {
	if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if ((s2[0]!='+')&&(s2[0]!='-'))
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(s2)==1)
		{
		  w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
	      }
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
	    p4++;
	  }
	  else
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if ((s2[0]!='+')&&(s2[0]!='-'))
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(s2)==1)
		{
		  w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
	      }

	      p5=0;

	    }
	  }
	}
      }
    }

    if (p5==1)
    {
      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

      if ((s2[0]=='+')||(s2[0]=='-'))
      {
        w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

	if (win_hpp5>=HND_NUM) return(0);
      }
    }

  }

  win_tfpp=(FARPROC)MakeProcInstance((FARPROC)w_tab_ci_wp,bw_main1.win_ins);
  for (i=hpp1;i<=bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5);i++)
  {
    bw_win_bua1.set_win_fpp(i,(FARPROC)GetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tfpp);
  }

  bw_win_bua1.set_win_hpp7(p_pagecnt,1,bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5));

  win_hpp1=win_hpp5;

  return(0);
}

int bw_win::w_echo_win_radio(int p_pagecnt,int mark)
{
//  HDC  hdc;
//  HWND hnd;
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
//  int  state5;
  int  i,j;
  int  pp1;
  int  hpp1;
//  char str[SMG_LEN];
  char s2[FLD_NAME_LEN];

  win_mark=mark;

  if (bw_win_bua1.get_win_pp2(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((bw_win_bua1.get_win_pp2(i,1)==0)&&(i>0))
    {
      i--;
    }
    bw_win_bua1.set_win_pp2(p_pagecnt,0,bw_win_bua1.get_win_pp2(i,1)+1);
    pp1=bw_win_bua1.get_win_pp2(i,1);
  }
  else pp1=bw_win_bua1.get_win_pp2(p_pagecnt,0)-1;

  hpp1=win_hpp5;

  p7=0;  
  p8=0;

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++)  
    {
      if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue; 
    if (p7==0) p7=i;
    if (p8==0) p8=p1;
    state1=0;
    p4=0;
    p5=0;
    p6=0;
    for (j=p1;j<=p2;j++) 
    {
      if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='&')
      {
        pp1++;
	p4=0;
	p5=1;      
        state1=1;  
	p6=j;    
      }
      else
      {
	if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if (s2[0]!='(')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(s2)==1)
		{
		  w_cre_ci_radio(p_pagecnt,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
	      }
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
	    p4++;
	  }
	  else
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if (s2[0]!='(')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(s2)==1)
		{
		  w_cre_ci_radio(p_pagecnt,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
	      }
	      p5=0;

	    }
	  }
	}
      }
    }

    if (p5==1)
    {
      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

      if (s2[0]=='(')
      {
        w_cre_ci_radio(p_pagecnt,p6,p7,p8,i);

	if (win_hpp5>=HND_NUM) return(0);
      }
    }

  }

  win_tfpp=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=hpp1;i<=bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5);i++)
  {
    bw_win_bua1.set_win_fpp(i,(FARPROC)GetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tfpp);
  }

  bw_win_bua1.set_win_hpp7(p_pagecnt,1,bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5));

  win_hpp1=win_hpp5;

  return(0);
}

int bw_win::w_echo_win_chs(int p_pagecnt,int mark)
{ 
//  HDC  hdc;
//  HWND hnd;
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
//  int  state4,state5;
  int  i,j;
  int  pp1;
  int  hpp1;
//  char str[SMG_LEN];
  char s2[FLD_NAME_LEN];

  win_mark=mark;

  if (bw_win_bua1.get_win_pp2(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((bw_win_bua1.get_win_pp2(i,1)==0)&&(i>0))
    {
      i--;
    }
    bw_win_bua1.set_win_pp2(p_pagecnt,0,bw_win_bua1.get_win_pp2(i,1)+1);
    pp1=bw_win_bua1.get_win_pp2(i,1);
  }
  else pp1=bw_win_bua1.get_win_pp2(p_pagecnt,0)-1;

  hpp1=win_hpp5;

  p7=0;  
  p8=0;

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++) 
    {
      if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buffa1.get_tmpc1(p_pagecnt,i,j)>' ')||(bw_buffa1.get_tmpc1(p_pagecnt,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue; 
    if (p7==0) p7=i;
    if (p8==0) p8=p1;
    state1=0;
    p4=0;
    p5=0;
    p6=0;
    for (j=p1;j<=p2;j++) 
    {
      if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)=='&')
      {
        pp1++;
	p4=0;      
	p5=1;     
        state1=1;  
	p6=j;
      }
      else
      {
	if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buffa1.get_tmpc1(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if (s2[0]!='[')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(s2)==1)
		{
		  w_cre_ci_check(p_pagecnt,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
	      }
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
	    p4++;
	  }
	  else
	  {
	    if (p5==1)
	    {
	      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

	      if (s2[0]!='[')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(s2)==1)
		{
		  w_cre_ci_check(p_pagecnt,p6,p7,p8,i);

		  if (win_hpp5>=HND_NUM) return(0);
		}
	      }
	      p5=0;

	    }
	  }
	}
      }
    }

    if (p5==1)
    {
      bw_win_bua1.get_1fldname(pp1,s2,FLD_NAME_LEN);

      if (s2[0]=='[')
      {
        w_cre_ci_check(p_pagecnt,p6,p7,p8,i);

	if (win_hpp5>=HND_NUM) return(0);
      }
    }

  }

  win_tfpp=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=hpp1;i<=bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5);i++)
  {
    bw_win_bua1.set_win_fpp(i,(FARPROC)GetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(bw_win_bua1.get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tfpp);
  }

  bw_win_bua1.set_win_hpp7(p_pagecnt,1,bw_win_bua1.get_win_hpp3(bw_win_bua1.get_win_pp5(p_pagecnt),5));

  win_hpp1=win_hpp5;

  return(0);
}

int bw_win::w_find_hnd(int p1,int p2,int p3)
{
  int  i,j;
//  char str[SMG_LEN];
//  HDC  hdc;

  j=0;
  for (i=0;i<=win_hpp1-1;i++)
  {
    if ((bw_win_bua1.get_win_hpp4(i,0)==p1)&&
	(bw_win_bua1.get_win_hpp4(i,1)==p2)&&
	(bw_win_bua1.get_win_hpp4(i,2)==p3))
    {
      j=bw_win_bua1.get_win_hpp4(i,3);
      break;
    }
  }

  return(j);
}
int bw_win::w_find_winfname(int w,int l,int c,char *p_s1,int len)
{
  int  i,j;
  char s2[FLD_NAME_LEN];

  i=bw_buff1.get_linecol(w,l,c);
  if (i>0)
  {
    bw_win_bua1.get_1fldname(i,s2,FLD_NAME_LEN);
//    strcpy(s1,s2);

    if (FLD_NAME_LEN>len) i=len;
    else i=FLD_NAME_LEN;
    for (j=0;j<i-1;j++)
    {
      p_s1[j]=s2[j];
    }
    if (i-1<0) p_s1[0]=0;
    else  p_s1[i-1]=0;
  }
  return(0);
}
int bw_win::w_find_winflen(int w,int l,int c)
{
  int i;
  i=bw_buff1.get_linecol(w,l,c);
  if (i>0) return(bw_win_bua1.get_1fldlen(i));
  else return(0);
}
int bw_win::w_set_winfedit(int w,int l,int c,int v)
{
  int i;
  i=bw_buff1.get_linecol(w,l,c);
  if (i>0) bw_win_bua1.set_1fldedt(i,v);
  return(0);
}
int bw_win::w_set_winafedit(int w)
{
  int  i,j,k,m;
  char s2[FLD_NAME_LEN];

  m=w;
  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	k=bw_buff1.get_linecol(m,i,j);

	bw_win_bua1.get_1fldname(k,s2,FLD_NAME_LEN);

	if (s2[0]=='*') bw_win_bua1.set_1fldedt(k,1);
	else
	{
	  if (strlen(s2)<=1) bw_win_bua1.set_1fldedt(k,1);
	  else
	  {
	    if (s2[0]=='%') bw_win_bua1.set_1fldedt(k,1);
	    else bw_win_bua1.set_1fldedt(k,0);
	  }
	}
      }
    }
  }

  return(0);
}
int bw_win::w_next_field(int i1)
{
//  HDC  hdc;
//  char str[SMG_LEN];
  int  i,j,m;
  int  s_tmpn1,s_tmpn2;
  int  exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=i1;
  pfield++;
  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	if (bw_win_bua1.get_1fldedt(bw_buff1.get_linecol(m,i,j))==0)
	{
	  exist=1;
	  break;
	}
      }
    }
    if (exist==1) break;
    pfield=1;
  }
  if (exist==0)
  {
    pline=s_tmpn1;
    pfield=s_tmpn2;
  }
  else
  {
    exist=0;
    pline=i;
    pfield=j;
  }

  return(exist);
}
int bw_win::w_next_afield(int i1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=i1;
  pfield++;
  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
        exist=1;
        break;
      }
    }
    if (exist==1) break;
    pfield=1;
  }
  if (exist==0)
  {
    pline=s_tmpn1;
    pfield=s_tmpn2;
  }
  else
  {
    exist=0;
    pline=i;
    pfield=j;
  }
  return(exist);
}
int bw_win::w_right_field(int i1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=i1;
  pfield++;
  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	if (bw_win_bua1.get_1fldedt(bw_buff1.get_linecol(m,i,j))==0)
	{
	  exist=1;
	  break;
	}
      }
    }
    if (exist==1) break;
    pfield=1;
  }
  if (exist==0)
  {
    pline=s_tmpn1;
    pfield=s_tmpn2;
  }
  else
  {
    exist=0;
    pline=i;
    pfield=j;
  }
  return(exist);
}
int bw_win::w_left_field(int i1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=i1;
  pfield--;
  if (pfield<1)
  {
    pline--;
    if (pline<1) pline=1;
    pfield=COL_NUM-1;
  }
  for (i=pline;i>=1;i--)
  {
    for (j=pfield;j>=1;j--)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	if (bw_win_bua1.get_1fldedt(bw_buff1.get_linecol(m,i,j))==0)
	{
	  exist=1;
	  break;
	}
      }
    }
    if (exist==1) break;
    pfield=COL_NUM-1;
  }
  if (exist==0)
  {
    pline=s_tmpn1;
    pfield=s_tmpn2;
  }
  else
  {
    exist=0;
    pline=i;
    pfield=j;
  }
  return(exist);
}
int bw_win::w_up_field(int i1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  pline--;
  if (pline<1) pline=1;
  m=i1;
  for (i=pline;i>=1;i--)
  {
    for (j=pfield;j>=1;j--)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	if (bw_win_bua1.get_1fldedt(bw_buff1.get_linecol(m,i,j))==0)
	{
	  exist=1;
	  break;
	}
      }
    }
    if (exist==1) break;
  }
  if (exist==0)
  {
    pline=s_tmpn1;
    pfield=s_tmpn2;
  }
  else
  {
    pline=i;
    pfield=j;
  }

  return(0);
}
int bw_win::w_down_field(int i1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  pline++;
  m=i1;
  if (pline>=LIN_NUM) pline=1;
  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j>=1;j--)
    {
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	if (bw_win_bua1.get_1fldedt(bw_buff1.get_linecol(m,i,j))==0)
	{
	  exist=1;
	  break;
	}
      }
    }
    if (exist==1) break;
  }
  if (exist==0)
  {
    pline=s_tmpn1;
    pfield=s_tmpn2;
  }
  else
  {
    pline=i;
    pfield=j;
  }

  return(0);
}
int bw_win::w_down_line(int p_pp,int i1)                      
{
  int  i,j,m,n;
  int  exist;
  char s2[FLD_NAME_LEN];

  exist=0;
  m=i1;
  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      n=bw_buff1.get_linecol(m,i,j);

      bw_win_bua1.get_1fldname(n,s2,FLD_NAME_LEN);
      
      if ((n!=0)&&(s2[0]!='#')&&(s2[0]!='%')&&(s2[0]!='@'))
      {
	if (bw_win_bua1.get_1fldseri(n)==p_pp+1)
	{
	  pline=i;
          pfield=j;
	  exist=1;
	  break;
        }
      }
    }
    if (exist==1) break;
  }

  return(i);
}
int bw_win::w_up_line(int p_pp,int i1)
{
  int  i,j,m,n;
  int  exist;
  char s2[FLD_NAME_LEN];

  exist=0;
  m=i1;
  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      n=bw_buff1.get_linecol(m,i,j);

      bw_win_bua1.get_1fldname(n,s2,FLD_NAME_LEN);
      
      if ((n!=0)&&(s2[0]!='#')&&(s2[0]!='%')&&(s2[0]!='@'))
      {
	if (bw_win_bua1.get_1fldseri(n)==p_pp-1)
	{
	  pline=i;
          pfield=j;
	  exist=1;
	  break;
        }
      }
    }
    if (exist==1) break;
  }

  return(0);
}
int bw_win::w_field_type(char *str)
{
  if (str[0]=='&') return(0);  /* all field&var header */
  if (str[0]=='$') return(1);  /* suond */
  if (str[0]=='(') return(2);  /* (X)    ci */
  if (str[0]=='[') return(3);  /* [X]    ci */
  if (str[0]=='@') return(4);  /* button ci */
  if (str[0]=='#') return(5);  /* bitmap */
  if (str[0]=='%') return(6);  /* read base var */
  if (str[0]==':') return(7);  /* edit base var */
  if (str[0]=='?') return(8);  /* memory var */
  if (str[0]=='+') return(9);  /* edit base ci */
  if (str[0]=='-') return(10); /* edit var  ci */
  return(0);
}
int bw_win::w_fetch_fld_style(char *tfn,int len1,char *tn,int len2,long *tr,char *fn,int len3,int wpp)
{
  int  i,j,k,l;
  int  p1;
  int  s_pp1[3][2];
  char s_fld[3][SMG_LEN];
  //char tfn2[SMG_LEN];
/*
  if (len1>SMG_LEN) i=SMG_LEN;
  else i=len1;
  for (j=0;j<i-1;j++)
  {
    tfn2[j]=tfn[j];
  }
  if (i-1<0) tfn2[0]=0;
  else  tfn2[i-1]=0;
*/
  //bw_main1.set_string(tfn2,SMG_LEN,tfn,len1);

  i=strlen(tfn);
  j=0;
  l=0;
  for (k=0;k<=i;k++)  /* make tfn position */
  {
    if (tfn[k]=='.')
    {
      s_pp1[j][0]=l;
      s_pp1[j][1]=k-1;
      if (k-1-l+1>=9) s_pp1[j][1]=8+l;
      j++;
      l=k+1;
      if (j>=3)
      {
	j=3;
	break;
      }
    }
    else
    {
      if ((tfn[k]==0)||(tfn[k]==' '))
      {
	s_pp1[j][0]=l;
	s_pp1[j][1]=k-1;
	if (k-1-l+1>=9) s_pp1[j][1]=8+l;
	break;
      }
    }
  }

  for (i=0;i<=j;i++)   /* make str */
  {
    for (k=s_pp1[i][0];k<=s_pp1[i][1];k++)
      s_fld[i][k-s_pp1[i][0]]=tfn[k];
    s_fld[i][s_pp1[i][1]-s_pp1[i][0]+1]=0;
  }

  tn[0]=0;
  *tr=0;
  fn[0]=0;

  /* jugy tab|recno|fld */
  if (j==0)  /* 1 jie */
  {
    i=w_find_base_name(s_fld[0],SMG_LEN,wpp);
    k=w_find_recno_name(s_fld[0],SMG_LEN);
    l=w_find_fld_name(s_fld[0],SMG_LEN,wpp);
    if (i==1)
    {
      if ((int)strlen(s_fld[0])<len2)
      {
	strcpy(tn,s_fld[0]);
      }
      return(1);
    }
    if (k==1)
    {
      bw_inkey1.char2long(s_fld[0],tr);
      return(1);
    }
    if (l==1)
    {
      if ((int)strlen(s_fld[0])<len3)
      {
	strcpy(fn,s_fld[0]);
      }
      return(1);
    }
    return(0);
  }

  if (j==1)  /* 2 jie */
  {
    i=w_find_base_name(s_fld[0],SMG_LEN,wpp);
    k=w_find_recno_name(s_fld[0],SMG_LEN);
    l=w_find_fld_name(s_fld[0],SMG_LEN,wpp);
    if (i==1)
    {
      if ((int)strlen(s_fld[0])<len2)
      {
        strcpy(tn,s_fld[0]);
	p1=1;
      }
    }
    if (k==1)
    {
      bw_inkey1.char2long(s_fld[0],tr);
      p1=2;
    }
    if (l==1)
    {
      if ((int)strlen(s_fld[0])<len3)
      {
        strcpy(fn,s_fld[0]);
	p1=3;
      }
    }
    if ((i==0)&&(k==0)&&(l==0))
    {
      return(0);
    }

    i=w_find_base_name(s_fld[1],SMG_LEN,wpp);
    k=w_find_recno_name(s_fld[1],SMG_LEN);
    l=w_find_fld_name(s_fld[1],SMG_LEN,wpp);
    if (i==1)
    {
      if (p1==1)
      {
	return(0);
      }
      if ((int)strlen(s_fld[1])<len2)
      {
	strcpy(tn,s_fld[1]);
      }
    }
    if (k==1)
    {
      if (p1==2)
      {
	return(0);
      }
      bw_inkey1.char2long(s_fld[1],tr);
      p1=2;
    }
    if (l==1)
    {
      if (p1==3)
      {
	return(0);
      }
      if ((int)strlen(s_fld[1])<len3)
      {
        strcpy(fn,s_fld[1]);
	p1=3;
      }
    }
    if ((i==0)&&(k==0)&&(l==0))
    {
      return(0);
    }
  }

  if (j==2)  /* 3 jie */
  {
    i=w_find_base_name(s_fld[0],SMG_LEN,wpp);
    k=w_find_recno_name(s_fld[1],SMG_LEN);
    l=w_find_fld_name(s_fld[2],SMG_LEN,wpp);
    if (i==1)
    {
      if ((int)strlen(s_fld[0])<len2)
      {
	strcpy(tn,s_fld[0]);
      }
    }
    else
    {
      return(0);
    }
    if (k==1)
    {
      bw_inkey1.char2long(s_fld[0],tr);
    }
    else
    {
      return(0);
    }
    if (l==1)
    {
      if ((int)strlen(s_fld[0])<len3)
      {
	strcpy(fn,s_fld[0]);
      }
    }
    else
    {
      return(0);
    }
  }

  return(1);
}
int bw_win::w_find_base_name(char *p_str,int len,int wpp)
{
  int i,j;
  char stn[FN_SIZE];
  //char stm[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    stm[j]=str[j];
  }
  if (i-1<0) stm[0]=0;
  else  stm[i-1]=0;
*/
  //bw_main1.set_string(stm,SMG_LEN,str,len);

  j=0;
  for (i=0;i<STRU_NUM;i++)
  {
    bw_win_bub1.get_win_tabname(1,i,stn,FN_SIZE);

    if ((bw_win_bua1.get_win_pp9(i,wpp)==1)&&(strcmp(stn,p_str)==0))
    {
      j=1;
      break;
    }
  }
  if (j==0) return(0);
  else return(1);
}
int bw_win::w_find_fld_name(char *p_str,int len,int wpp)
{
  int  i,j,k;
  char fn1[SMG_LEN];
  //char stm[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    stm[j]=str[j];
  }
  if (i-1<0) stm[0]=0;
  else  stm[i-1]=0;
*/
  //bw_main1.set_string(stm,SMG_LEN,str,len);

  k=0;
  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win_bua1.get_win_pp9(i,wpp)==1)
    {
      for (j=bw_fldstru1.w_find_fldpoin0(i);j<=bw_fldstru1.w_find_fldpoin1(i);j++)
      {
        bw_fldstru1.w_find_fldname(i,j,fn1,SMG_LEN);
        if (strcmp(fn1,p_str)==0)
	{
	  k=1;
	  break;
	}
      }
      if (k==1) break;
    }
  }

  return(k);
}
int bw_win::w_find_recno_name(char *p_str,int len)
{
  int  i,j,k;
  //char stm[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    stm[j]=str[j];
  }
  if (i-1<0) stm[0]=0;
  else  stm[i-1]=0;
*/
  //bw_main1.set_string(stm,SMG_LEN,str,len);

  i=strlen(p_str);
  k=1;
  for (j=0;j<=i-1;j++)
  {
    if ((p_str[j]<'0')||(p_str[j]>'9'))
    {
      k=0;
      break;
    }
  }
  return(k);
}
int bw_win::w_fld_set_base(char *p_fldtable,int len,int pp1,int wpp)
{
  int  i,j,k;
  char stn[FN_SIZE];
  //char stm[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    stm[j]=s_fldtable[j];
  }
  if (i-1<0) stm[0]=0;
  else  stm[i-1]=0;
*/
  //bw_main1.set_string(stm,SMG_LEN,s_fldtable,len);

  if (bw_inkey1.strempty(p_fldtable)==0) return(pp1);
  k=0;
  for (i=0;i<STRU_NUM;i++)
  {
    bw_win_bub1.get_win_tabname(1,i,stn,FN_SIZE);

    if ((bw_win_bua1.get_win_pp9(i,wpp)==1)&&(strcmp(p_fldtable,stn)==0))
    {
      k=1;
      break;
    }
  }
  if (k==1) return(i);
  else return(pp1);
}
int bw_win::w_fld_set_recno(long s_fldrecno,int pp2)
{
  if (s_fldrecno!=0) return(0);
  else return(pp2);
}
int bw_win::w_fld_set_fld(char *p_fldname,int len)
{
  //char stm[SMG_LEN];
  int  i,j;
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    stm[j]=s_fldname[j];
  }
  if (i-1<0) stm[0]=0;
  else  stm[i-1]=0;
*/
  //bw_main1.set_string(stm,SMG_LEN,s_fldname,len);

  if (bw_inkey1.strempty(p_fldname)==0) return(1);
  else return(0);
}
int bw_win::w_find_edit_field(int wpp)
{
  int  i,j,k,l,m,n;
  int  exist;
  int  pp1;
//  char s_tmpc1[SMG_LEN];
  char s_fldtable[SMG_LEN];
  char s_fldname[SMG_LEN];
  long s_fldrecno;
  char s_tmpc2[SMG_LEN];
  char s_tmpc3[SMG_LEN];
  int  s_tmpn1;
//  char str[SMG_LEN];
//  char str2[SMG_LEN];
  char str3[SMG_LEN];
  char str4[SMG_LEN];
  char s2[FLD_NAME_LEN];
  char s3[FLD_NAME_LEN];

  exist=0;
  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win_bua1.get_win_pp9(i,wpp)==1)
    {
      exist=1;
      break;
    }
  }
  if (exist==1) pp1=i;
  else return(1);

  for (i=bw_win_bua1.get_win_pp2(wpp,0);i<=bw_win_bua1.get_win_pp2(wpp,1);i++)
  {
    bw_win_bua1.set_1fldbase(i,0);
    bw_win_bua1.set_1fldedt(i,0);
    bw_win_bua1.set_1fldseri(i,0);
  }
		      
  for (i=bw_win_bua1.get_win_pp2(wpp,0);i<=bw_win_bua1.get_win_pp2(wpp,1);i++)
  {
    bw_win_bua1.set_fldseri_tmp(i,0);
  }
	
  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      m=wpp;
      if (bw_buff1.get_linecol(m,i,j)>0)
      {
	s_fldtable[0]=0;  
	s_fldrecno=0;
	s_fldname[0]=0;

        n=bw_buff1.get_linecol(m,i,j);

	bw_win_bua1.get_1fldname(n,s2,FLD_NAME_LEN);
      
	if ((s2[0]==':')||(s2[0]=='%')||(s2[0]=='+')||(s2[0]=='-'))
	{
	  strcpy(s_tmpc2,s2);
	  if ((s_tmpc2[0]=='%')||(s_tmpc2[0]=='-'))
	  {
	    str3[0]=s_tmpc2[0];
            str3[1]=0;
	    s_tmpn1=1; /* read field */
            bw_inkey1.strpcut(s_tmpc2,1,strlen(s_tmpc2)-1,SMG_LEN,s_tmpc3,SMG_LEN);
          }
	  else
	  {
	    str3[0]=s_tmpc2[0];
            str3[1]=0;
	    s_tmpn1=0; /* edit field */
	    bw_inkey1.strpcut(s_tmpc2,1,strlen(s_tmpc2)-1,SMG_LEN,s_tmpc3,SMG_LEN);
	  }

	  w_fetch_fld_style(s_tmpc3,SMG_LEN
			   ,s_fldtable,SMG_LEN
			   ,&s_fldrecno
			   ,s_fldname,SMG_LEN,wpp);

	  if ((bw_inkey1.strempty(s_fldname)==0)&&(bw_inkey1.strempty(s_fldtable)==0))
	  {
            strcpy(str4,str3);
	    strcat(str4,s_tmpc3);
	    bw_win_bua1.set_1fldname(n,str4,strlen(str4)+1);
	  }
	  else
	  {
	    strcpy(str4,str3);
            strcat(str4,s_fldname);
	    bw_win_bua1.set_1fldname(n,str4,strlen(str4)+1);
          }
	  pp1=w_fld_set_base(s_fldtable,SMG_LEN,pp1,wpp);
	  bw_win_bua1.set_1fldbase(n,pp1);

	  if (bw_inkey1.strempty(s_fldname)==0)
	  {
	    continue;
          }

	  l=0;
	  for (k=bw_buff1.get_linecol(m,i,j)-1;k>=bw_win_bua1.get_win_pp2(wpp,0);k--)
	  {
	    bw_win_bua1.get_field_tmp(k,s3,FLD_NAME_LEN);
	    if ((strcmp(s_fldname,s3)==0)
	      &&(pp1==bw_win_bua1.get_1fldbase(k))
	      &&(s_fldrecno==0))
	    {
	      l=1;
	      bw_win_bua1.set_fldseri_tmp(k,bw_win_bua1.get_fldseri_tmp(k)+1);
	      bw_win_bua1.set_1fldseri(n,bw_win_bua1.get_fldseri_tmp(k));
	    }
	  }
	  if (l==1) bw_win_bua1.set_field_tmp1(bw_buff1.get_linecol(m,i,j),0,0);
	  else 
	  {
	    bw_win_bua1.set_field_tmp(bw_buff1.get_linecol(m,i,j),s_fldname,strlen(s_fldname)+1);
	    bw_win_bua1.set_fldseri_tmp(n,bw_win_bua1.get_fldseri_tmp(n)+1);
	    bw_win_bua1.set_1fldseri(n,bw_win_bua1.get_fldseri_tmp(n));
	  }

	  if (s_tmpn1==1)
	    bw_win_bua1.set_1fldedt(n,1);
	  else
	    bw_win_bua1.set_1fldedt(n,w_fld_set_fld(s_fldname,SMG_LEN));

	}
	else bw_win_bua1.set_1fldbase(n,pp1);
      }
    }
  }

  return(1);
}

int bw_win::w_just_edit(int wpp)
{
  HWND hnd;
  int  i,j,k,l,n,o,p,q,r;
  char s1[FLD_NAME_LEN];
  char s2[FLD_NAME_LEN];
//  char str[SMG_LEN];

  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(wpp,i,j)>0)
      {
        n=bw_buff1.get_linecol(wpp,i,j);

	bw_win_bua1.get_1fldname(n,s2,FLD_NAME_LEN);

	if (s2[0]=='+')
        {
	  k=bw_win_bua1.get_1fldlen(n);
          l=bw_win_bua1.get_1fldbase(n);

	  bw_inkey1.strpcut(s2,1,strlen(s2)-1,FLD_NAME_LEN,s1,FLD_NAME_LEN);

	  o=bw_fldstru1.w_find_fldlen(s1,FLD_NAME_LEN,l);

	  if (o>k) p=k;
	  else p=o;

	  if (p<3) p=3;

	  q=w_find_hnd(wpp,j,i);

	  hnd=bw_win_bua1.get_win_hnd(q);

	  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
          {
	    MoveWindow(hnd
			,(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_edit_xchar-3)
			,(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_edit_ychar-6)
			,(int)(p*bw_main1.win_edit_xchar+6)
			,(int)(bw_main1.win_edit_ychar+12)
			,FALSE);
	  }
          else
	  {
	    MoveWindow(hnd
			,(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_xchar-3)
			,(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_ychar-6)
			,(int)(p*bw_main1.win_xchar+6)
			,(int)(bw_main1.win_ychar+12)
			,FALSE);
	  }

	  SendMessage(hnd,EM_LIMITTEXT,o,(LPARAM)s1);
	}

	if (s2[0]=='-')
        {
	  k=bw_win_bua1.get_1fldlen(n);

	  r=bw_dialog1.w_mv_seri(s2,FLD_NAME_LEN,wpp);

	  o=bw_dialog_bua1.get_win_mv_type(r,2);

	  if (o>k) p=k;
	  else p=o;

	  if (p<3) p=3;

	  q=w_find_hnd(wpp,j,i);

	  hnd=bw_win_bua1.get_win_hnd(q);

	  if (bw_win_bua1.get_win_ci_mode(wpp)==0)
          {
	    MoveWindow(hnd
			,(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_edit_xchar-3)
			,(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_edit_ychar-6)
			,(int)(p*bw_main1.win_edit_xchar+6)
			,(int)(bw_main1.win_edit_ychar+12)
			,FALSE);
	  }
          else
	  {
	    MoveWindow(hnd
			,(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_xchar-3)
			,(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_ychar-6)
			,(int)(p*bw_main1.win_xchar+6)
			,(int)(bw_main1.win_ychar+12)
			,FALSE);
	  }

	  SendMessage(hnd,EM_LIMITTEXT,o,(LPARAM)s1);
	}
      }
    }
  }

  return(0);
}

int bw_win::w_cnt_winline(int basep,int wpp,int ln)
{
  int i,j,k,l;

  k=0;
  for (i=1;i<ln;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      l=bw_buff1.get_linecol(wpp,i,j);
      if ((l!=0)&&(bw_win_bua1.get_1fldbase(l)==basep))
      {
	if (k<bw_win_bua1.get_1fldseri(l))
	  k=bw_win_bua1.get_1fldseri(l);
      }
    }
  }
  return(k);
}

int bw_win::tst_hpp3()
{
  HDC  hdc;
  char str[SMG_LEN];
  int  i;

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str,"hpp30123456=%d,%d,%d,%d,%d,%d,%d,"
			      ,bw_win_bua1.get_win_hpp3(i,0)
			      ,bw_win_bua1.get_win_hpp3(i,1)
			      ,bw_win_bua1.get_win_hpp3(i,2)
			      ,bw_win_bua1.get_win_hpp3(i,3)
			      ,bw_win_bua1.get_win_hpp3(i,4)
			      ,bw_win_bua1.get_win_hpp3(i,5)
			      ,bw_win_bua1.get_win_hpp3(i,6)
			      );
    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_win::tst_hpp4()
{
  HDC  hdc;
  char str[SMG_LEN];
  int  i;

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    sprintf(str,"hpp401234=%d,%d,%d,%d,%d,"
			      ,bw_win_bua1.get_win_hpp4(i,0)
			      ,bw_win_bua1.get_win_hpp4(i,1)
			      ,bw_win_bua1.get_win_hpp4(i,2)
			      ,bw_win_bua1.get_win_hpp4(i,3)
			      ,bw_win_bua1.get_win_hpp4(i,4));
    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_win::w_atten1(char *p_fn1)
{
  char str[256];
  char str1[256];

  strcpy(str,"打开资料错误,资料名:");
  strcat(str,p_fn1);

  strcpy(str1,"Error when open file,file name:");
  strcat(str1,p_fn1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,str1,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,str,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten2()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error in table structure.","ERROR MESSGAE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"表格结构错误","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten3()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Windows too much.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"窗口数量太多","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten4()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Screen format define error,table name need ','.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义表格名时,没有','号."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten5()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Screen format define error,structure name too long.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义表格名时,结构名太长."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten6()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Screen format define error,need structure name.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义表格名时,结构名没有."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten7()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error when insert record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"插入数据时错误"
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten7b()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error when add record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"追加数据时错误"
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten7a()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error when delete record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"删除数据时错误"
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten8(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"打开资料错误,资料名:");
  strcat(s2,s1);
  strcat(s2,"(资料正忙!),再试一次?");

  strcpy(s3,"Error when open file,file name:");
  strcat(s3,s1);
  strcat(s3,",file is busy,try again ?");

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OKCANCEL|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd
            ,s2 
	    ,"错误信息",MB_OKCANCEL|MB_ICONQUESTION);

  if (i==IDOK) return(1);
  else return(0);
}
int bw_win::w_atten9(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"是否保存资料,资料名:");
  strcat(s2,s1);

  strcpy(s3,"If to save file,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd
            ,s2 
	    ,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);  
  else return(2);
}
int bw_win::w_atten9a(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"数据库资料不存在,是否建立,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Database file don't exist,if to create:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd
	    ,s2
	    ,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDCANCEL) return(0);
  else
  {
    if (i==IDYES) return(1);
    else
    {
      if (i==IDNO) return(2);
      else return(0);
    }
  }
}
int bw_win::w_atten10()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"const LINK_CHAR too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"常量LINK_CHAR太小.","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten11()
{      
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"const WIN_VAR_NUM too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"常量WIN_VAR_NUM太小."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten12()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"const VAR_IN_SCRN too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"常量VAR_IN_SCRN太小."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten13(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"不认识的数据库名:");
  strcat(s2,s1);
  
  strcpy(s3,"Unknow database name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten14(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"不认识的字段名:");
  strcat(s2,s1);

  strcpy(s3,"Unknow field name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten15(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"打开资料错误,资料忙:");
  strcat(s2,s1);

  strcpy(s3,"Error when open file,file is busy:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_RETRYCANCEL|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_RETRYCANCEL|MB_ICONQUESTION);

  if (i==IDRETRY) return(1);
  else return(0);
}
int bw_win::w_atten16(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"XBASE数据库资料不存在,是否建立:");
  strcat(s2,s1);

  strcpy(s3,"XBASE file does not exist,if to create:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(2);
  else return(1);
}
int bw_win::w_atten17(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"建立XBASE数据库资料出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when create XBASE file:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten18(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"XBASE数据库资料结构不同,是否更新结构?:");
  strcat(s2,s1);

  strcpy(s3,"The structure of XBASE file is not same,update?");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten19(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"字符串没找到:");
  strcat(s2,s1);

  strcpy(s3,"String not find:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
} 
int bw_win::w_atten20(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"是否替换:");
  strcat(s2,s1);

  strcpy(s3,"If to replace?:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten21()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Too much edit windows.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"编辑窗口太多","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten22()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Database buffer number is too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"库缓冲区不够","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten23(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"资料存在,是否复盖:");
  strcat(s2,s1);

  strcpy(s3,"The file is exist,recover it?:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten24(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"拷备资料时出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when copy file:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten25(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"资料名错误:");
  strcat(s2,s1);

  strcpy(s3,"There is error in file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten26(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"目录不存在:");
  strcat(s2,s1);

  strcpy(s3,"Directory is not exist:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten27(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"目录已存在:");
  strcat(s2,s1);

  strcpy(s3,"Directory is already exist:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten28(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"拷备目录时错误,目标目录:");
  strcat(s2,s1);

  strcpy(s3,"Error when copy directory,aim directory:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"EEROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten29(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"同名资料存在,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Exist same name file,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten30(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"建立目录时错误,目录名:");
  strcat(s2,s1);

  strcpy(s3,"Error when create directory,name is:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten31(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"是否真的删除?,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Do you want to delete file?:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten32(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"删除资料时出错,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Error when delete file,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten33(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"删除目录时出错,目录名:");
  strcat(s2,s1);

  strcpy(s3,"Error when delete directory,directory name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten34(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"换名资料已存在,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Aim file already exist,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten35(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"换名时出错,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Error when rename file,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten36(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"菜单定义错误,资料名:");
  strcat(s2,s1);

  strcpy(s3,"There is error in menu define,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten37(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"多重选择定义错误,资料名:");
  strcat(s2,s1);

  strcpy(s3,"There is error in radio button define,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten38(char *s1)
{
//  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"对话框定义错误,资料名:");
  strcat(s2,s1);

  strcpy(s3,"There is error in dialog box define,file name:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten39()
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"情换页!");
  strcpy(s3,"Next page please.");

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNOCANCEL|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"信息显示",MB_YESNOCANCEL|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else
  {
    if (i==IDCANCEL) return(2);
    else return(0);
  }
}
int bw_win::w_atten40()
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"打印机没连上!");
  strcpy(s3,"Printer is not online.");

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"ERROR MESSAGE",MB_RETRYCANCEL|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"错误信息",MB_RETRYCANCEL|MB_ICONQUESTION);

  if (i==IDRETRY) return(1);
  else return(2);
}
int bw_win::w_atten41()
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"'是(Yes)'新记录插入当前记录前面,'否(No)'插入后面");
  strcpy(s3,"(Yes) to insert defore,(No) to insert after.");

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"信息显示",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(0);
}
int bw_win::w_atten42()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Only support XBASE,please choose database type.","INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"本软体目前只支持XBASE,请选数据库类型.","信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten43()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Please clear if to backup database defore open it.","INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"打开数据库前请规定是否备份。","信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten44()
{
  char s1[256];
  char s2[11];
  char s3[256];

  strcpy(s1,"打开数据库前请先规定工作区号,不能大于");
  sprintf(s2,"%d",STRU_NUM);
  strcat(s1,s2);

  strcpy(s3,"Please clear buffer number before open database,can not bigger than:");
  strcat(s3,s2);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s1,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten45(char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"目录不存在：");
  strcat(s2,s1);

  strcpy(s3,"Directory do not exist:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten46(char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"XBASE资料名不正确:");
  strcat(s2,s1);

  strcpy(s3,"The name of XBASE file is not correct:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten47(char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"打开XBASE数据库结构资料出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when open structure define file of XBASE file:");
  strcat(s3,s1); 

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten48(char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"打开XBASE数据库出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when open XBASE file:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten49()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"There are not so much records.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"数据库中没有这么多记录!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten50()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Record number can not little then zero.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"记录号不能为零或负!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten51()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error when read database record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"读数据库记录出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten52()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Record number is not correct,can not delete record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"记录号不正确，删除记录出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten53()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Record number is not correct,can not locate record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"记录号不正确，定位出错,请规定记录号!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten54()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Record number is not correct,can not display record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"记录号不正确，显示记录出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten55()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error when commit data.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"数据库提交出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten56()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Error when rollback data.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"数据库滚回出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten57(int l)
{
  char str[81];
  char str2[256];
  char str3[256];

  sprintf(str,"%d!",l);
  strcpy(str2,"工作区没有数据库打开!,工作区号：");
  strcat(str2,str);

  strcpy(str3,"There is not base opened in this buffer,buffer number:");
  strcat(str3,str);


  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,str3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,str2,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten58()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"There is not enough data buffer.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"没有足够的数据区分配!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten59()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"There is error in screen format,type name is too long.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义库类型时,类型名太长."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten60()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"There is error in screen format,lack type name.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义库类型时,类型名没有."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten61()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"There is error in screen format,backup type name is too long.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义备份类型时,备份类型名太长."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten62()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"There is error int screen format,lack backup type name.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"屏幕格式错误,定义备份类型时,备份类型名没有."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten63()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Data buffer is already in use.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"数据区已被分配!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten64(char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"'是(Yes)'保存修改过的资料,'否(No)'放弃修改.资料名:");
  strcat(s2,s1);
  strcpy(s3,"(Yes) to save text which is changed,(No) to exit without save.the name of the file:");
  strcat(s3,s1);

  if (bw_main1.win_lang==1) i=MessageBox(bw_main1.win_hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(bw_main1.win_hwnd,s2,"信息显示",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(0);
}
int bw_win::w_atten65()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"The change in text can not be undo.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"不能恢复对资料的修改."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten66()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"You must answer 'save or not' messagebox.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"必需回答'是否存盘对话框'."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten67()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"Sub windows too much.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"子窗口太多."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten68()
{
  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,"const VAL_NUM too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,"常量VAL_NUM太小."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}

