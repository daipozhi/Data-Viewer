
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

#include "vc_bowo.h"

extern class bw_main         bw_main1;
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

extern long  PASCAL w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long  PASCAL w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);

/* should into class */

HWND bw_win::get_ci_mhnd(HWND hwnd)
{
  int i,j;

  for (i=0;i<HND_NUM;i++)
  {
    if (win_hnd[i]==hwnd)
    {
      j=win_h_ci_ptr[i][4];
      return(win_hnd[j]);
    }
  }

  return(0);
}

int bw_win::w_first_grp(void)
{
  int i;
  int exist;

  exist=0;

  for (i=1;i<WIN_NUM;i++)
  {
    if (get_win_ptr_grp_id(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    return(i);
  }
  else return(-1);
}

int bw_win::w_ini_win(void)
{
  int i;

  win_ptr_new_win=1; /* can not be zero (0) */

  for (i=0;i<WIN_NUM;i++)
  {
    set_win_ptr_fld_in_win(i,0,0);
    set_win_ptr_fld_in_win(i,1,0);
    set_win_ptr_fld_in_win(i,2,0);
    set_win_ptr_fld_in_win(i,3,0);
    set_win_ptr_win_mark(i,0);
    set_win_ptr_grp_id(i,0);
    set_win_ptr_grp_ptr(i,0,0);
    set_win_ptr_grp_ptr(i,1,0);
    set_win_ptr_grp_ptr(i,2,0);

    set_win_msgboxlock(i,0);
  }

  return(0);
}

int bw_win::w_login_win(int p1,int p2,char *p_win_name,int p_win_name_size,char *p_find_name,int p_find_name_size)
{
  int i,j,k;
  int exist;

  exist=0;

  for (i=1;i<WIN_NUM;i++)
  {
    if (get_win_ptr_grp_ptr(i,0)==0)
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

  set_win_ptr_grp_ptr(i,0,p1);
  set_win_ptr_grp_ptr(i,1,p1);
  set_win_ptr_grp_ptr(i,2,p2);

  for (j=p1;j<=p2;j++)
  {
    set_win_ptr_grp_id(j,i);
    set_win_ptr_win_mark(j,j);
    set_win_window_name(j,p_win_name ,p_win_name_size );
    set_win_find_name(  j,p_find_name,p_find_name_size);

    for (k=0;k<STRU_NUM;k++)
    {
      bw_xbase1.set_win_cur_seri(k,j,0);
      bw_xbase1.set_win_recno(k,j,0,0);
      bw_xbase1.set_win_recno(k,j,1,0);
      bw_xbase1.set_win_recno(k,j,2,0);
      bw_xbase1.set_win_state_in_srch(j,k,0);
    }
  }

  return(0);
}

int bw_win::w_dele_win_ptr(int p_wptr)
{
  int i,j,k;

  i=get_win_ptr_grp_id(p_wptr);

  for (j=get_win_ptr_grp_ptr(i,0);j<=get_win_ptr_grp_ptr(i,2);j++)
  {
    set_win_ptr_grp_id(j,0);
    set_win_ptr_win_mark(j,0);
    for (k=0;k<STRU_NUM;k++)
    {
      set_win_ptr_wins_dbf(k,j,0);
    }
  }

  set_win_ptr_grp_ptr(i,0,0);
  set_win_ptr_grp_ptr(i,1,0);
  set_win_ptr_grp_ptr(i,2,0);

  return(0);
}

int bw_win::w_dele_win_ptr_wins_dbf(int p_wptr)
{
  int i,j;

  for (j=get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_wptr),0)
      ;j<=get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_wptr),2)
      ;j++)
  {
    for (i=0;i<STRU_NUM;i++)
    {
      if (get_win_ptr_wins_dbf(i,j)==1)
      {
	set_win_tabname(0,i,"",0);
	set_win_tabname(1,i,"",0);
      }
      set_win_ptr_wins_dbf(i,j,0);
    }
  }

  return(0);
}

int bw_win::w_login_wwin(int p_pagecnt)
{
  win_h_ptr=get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_pagecnt),2)-get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_pagecnt),0);

  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),0,win_h_w_total_ptr);
  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),1,win_h_w_total_ptr+win_h_ptr);
  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),2,win_h_w_total_ptr);
  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),3,get_win_ptr_grp_id(p_pagecnt)-1);

  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),4,win_h_w_total_ptr+win_h_ptr+1);
  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5,0);
  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),6,win_h_w_total_ptr+win_h_ptr+1);
  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),7,get_win_ptr_grp_id(p_pagecnt));

  win_h_ci_total_ptr=win_h_w_total_ptr+win_h_ptr+1;
  win_h_w_total_ptr=win_h_ci_total_ptr;

  return(0);
}

int bw_win::w_find_winhand(HWND hwnd)
{
  int i;
  int exist;

  exist=0;

  for (i=1;i<win_ptr_new_win;i++)
  {
    if (hwnd==get_win_phh(i))
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);
  else return(i);
}

int bw_win::w_mouse_infield(int p_wptr,int y,int x)
{
  int  exist;
  int  m,n;
  char str1[SMG_SIZE];

  exist=0;

  for (m=1;m<COL_NUM;m++)
  {
    n=bw_buff1.get_t3_linecol(p_wptr,y,m);

    if ((n>0)&&(get_t_fldedt(n)==0))
    {
      if ((m<=x)&&(x<=m+get_t_fldlen(n)-1))
      {
	get_t_fldname(n,str1,SMG_SIZE);

	if ((str1[0]=='?')||(str1[0]==':'))
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
  //HDC  hdc;
  int  i,j,k,l,m;
  char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];

  bw_getread1.deb_record("bw_win::tst_win1()");

  for (i=1;i<60;i++)
  {
    get_t_fldname(i,str2,FLD_NAME_SIZE);

    sprintf(str1,"ptr=%d,fldname=%s,type=%c,base=%d,seri=%d,len=%d,dec=%d,edit=%d,"
                                       ,i,str2
				       ,get_t_fldtype(i)
				       ,get_t_fldbase(i)
				       ,get_t_fldseri(i)
				       ,get_t_fldlen(i)
				       ,get_t_flddec(i)
				       ,get_t_fldedt(i));

    bw_getread1.deb_record(str1);
  }

  k=0;

  for (l=1;l<WIN_NUM;l++)
  {
    for (i=1;i<LIN_NUM;i++)
    {
      for (j=1;j<COL_NUM;j++)
      {
	if (bw_buff1.get_t3_linecol(l,i,j)!=0)
	{
	  m=bw_buff1.get_t3_linecol(l,i,j);
	  get_t_fldname(m,str2,FLD_NAME_SIZE);

	  sprintf(str1,"win=%d,line=%d,col=%d,linecol=%d,seri=%d,base=%d,name=%s,",l,i,j,m,get_t_fldseri(m),get_t_fldbase(m),str2);
          bw_getread1.deb_record(str1);
	  k++;
	  if (k>=60) break;
        }
      }
      if (k>=60) break;
    }
    if (k>=60) break;
  }

  return(0);
}

int bw_win::tst_win2()
{
  //HDC  hdc;
  int  i;
  char str1[SMG_SIZE];
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win2()");

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str1,"win_ptr=%d,20=%d,21=%d,4=%d,5=%d,60=%d,61=%d,62=%d,90=%d,91=%d,92=%d,93=%d,ptr1=%d,subwub=%d,"
                                       ,i,get_win_ptr_fld_in_win(i,0)
				       ,get_win_ptr_fld_in_win(i,1)
				       ,get_win_ptr_win_mark(i)   
				       ,get_win_ptr_grp_id(i)
				       ,get_win_ptr_grp_ptr(i,0)
				       ,get_win_ptr_grp_ptr(i,1)
				       ,get_win_ptr_grp_ptr(i,2)
				       ,get_win_ptr_wins_dbf(0,i)
				       ,get_win_ptr_wins_dbf(1,i)
				       ,get_win_ptr_wins_dbf(2,i)
				       ,get_win_ptr_wins_dbf(3,i)
				       ,win_ptr_new_win
				       ,0/*get_win_subhndptr(i)*/);

    bw_getread1.deb_record(str1);
  }

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_tabname(0,i,stn1,FN_SIZE);
    get_win_tabname(1,i,stn2,FN_SIZE);

    sprintf(str1,"ptr=%d,tabn=%s,stru=%s,",i,stn1,stn2);
    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win3()
{
  //HDC  hdc;
  int  i;
  char str1[SMG_SIZE];
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];
  char stn3[FN_SIZE];
  char stn4[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win3()");

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_tabname(0,i,stn1,FN_SIZE);
    get_win_tabname(1,i,stn2,FN_SIZE);
    get_win_window_name(i,stn3,FN_SIZE);
    get_win_find_name(i,stn4,FN_SIZE);

    sprintf(str1,"ptr=%d,winname=%s,findname=%s,stru=%s,base=%s,"
                                       ,i,stn3
				       ,stn4
				       ,stn1
				       ,stn2);

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win4()
{
  //HDC  hdc;
  int  i,j;
  char str1[SMG_SIZE];

  bw_getread1.deb_record("bw_win::tst_win4()");

  for (i=1;i<24;i++)
  {
    for (j=1;j<=80;j++)
    {
      str1[j-1]=bw_buff1.get_t3_winfile(1,i,j);
    }
    str1[80]=0;

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win5()
{
  //HDC  hdc;
  int  i;
  char str1[SMG_SIZE];
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win5()");

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_tabname(0,i,stn1,FN_SIZE);
    get_win_tabname(1,i,stn2,FN_SIZE);

    sprintf(str1,"ptr=%d,base=%s,stru=%s,",i,stn1,stn2);

    bw_getread1.deb_record(str1);
  }

  return(0);
}
/*
int bw_win::tst_win6()
{
  HDC  hdc;
  int  i;
  char str1[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=1;i<WIN_NUM;i++)
  {
    sprintf(str1,"%d,%d,%d,%d,%d,%d,%d,%d,"
	,get_win_subhndid(i,0)
	,get_win_subhndid(i,1)
	,get_win_subhndid(i,2)
	,get_win_subhndid(i,3)
	,get_win_subhndid(i,4)
	,get_win_subhndid(i,5)
	,get_win_subhndid(i,6)
	,get_win_subhndid(i,7)
           );

    TextOut(hdc,0,i*20,str1,strlen(str1));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}
*/
int bw_win::w_close_win(int p1)
{
  HWND edit_hnd;
  int  i,j,k,l,m,n;
  int  ptr5;
  int  id[WIN_NUM];
  char str1[SMG_SIZE];

  for (i=1;i<WIN_NUM;i++)
  {
    id[i]=0;
  }

  ptr5=get_win_ptr_grp_id(p1);

  id[ptr5]=1;

  for (i=WIN_NUM-1;i>=1;i--)
  {
    if (id[i]==1)
    {
      for (m=0;m<STRU_NUM;m++)
      {
	if ((get_win_ptr_wins_dbf(m,i)==1)&&(bw_xbase1.get_win_mem_inuse(m)==1))
	{
	  for (n=0;n<EDIT_NUM;n++)
	  {
	    if (bw_edit1.get_win_edit_wptr(n)==i)
	    {
	      edit_hnd=bw_edit1.get_win_edit_hnd1(n);
	      SendMessage(edit_hnd,WM_COMMAND,1803,(LPARAM)0);
	    }
          }
	}
      }

//      sprintf(str1,"%d,%d,",i,win_ptr_grp_ptr[i][0]);
//      MessageBox(bw_main1.win_hwnd1,str1,"aa",MB_OK);

      w_close_subwin(get_win_ptr_grp_ptr(i,0));

//      bw_dialog1.tst_mem();

    }
  }

  return(0);
}

int bw_win::w_close_subwin(int p1)
{
  int  exist;
  int  i,j,k,l,m,n,o,p,q,r,s,t;
  int  p10;
  char sfn1[FLD_NAME_SIZE];
  char stn1[FN_SIZE];
  char smv1[SMG_SIZE];

  // must answer
  if (bw_xbase1.win_answer!=0)
  {
    w_atten66();
    return(1);
  }

  bw_xbase1.win_answer=1;

  i=get_win_ptr_grp_id(p1);



  /* close database */  
  // lock msg
  for (k=get_win_ptr_grp_ptr(i,0);k<=get_win_ptr_grp_ptr(i,2);k++)
  {
	  set_win_msgboxlock(k,1);
  }



  for (k=0;k<STRU_NUM;k++)
  {
    if (get_win_ptr_wins_dbf(k,p1)==1)
    {
      bw_fldstru1.w_dele_stru(k);
      bw_mbase1.w_close_base(k,p1);
      bw_fldstru1.w_clr_condition(k);
    }
  }


  // unlock msg
  for (k=get_win_ptr_grp_ptr(i,0);k<=get_win_ptr_grp_ptr(i,2);k++)
  {
	  set_win_msgboxlock(k,0);
  }



  /* remove mem var */

  bw_menuvar1.w_dele_menu(get_win_ptr_grp_ptr(i,0),get_win_ptr_grp_ptr(i,2));

  //bw_choose1.w_dele_choose(get_win_ptr_grp_ptr(i,0),get_win_ptr_grp_ptr(i,2));
  //bw_switch1.w_dele_switch(get_win_ptr_grp_ptr(i,0),get_win_ptr_grp_ptr(i,2));
  //bw_dialog1.w_dele_dialog(get_win_ptr_grp_ptr(i,0),get_win_ptr_grp_ptr(i,2));

  bw_choose1.w_clr_recvar_chs(get_win_ptr_grp_ptr(i,0));
  bw_switch1.w_clr_recvar_radio(get_win_ptr_grp_ptr(i,0));
  //bw_dialog1.w_clr_recvar_dialog(get_win_ptr_grp_ptr(i,0));

  bw_link1.w_dele_svar(get_win_ptr_grp_ptr(i,0),get_win_ptr_grp_ptr(i,2));

  bw_link1.w_dele_link(get_win_ptr_grp_ptr(i,0),get_win_ptr_grp_ptr(i,2));

  for (k=get_win_ptr_grp_ptr(i,0);k<=get_win_ptr_grp_ptr(i,2);k++)
  {
    j=get_win_ptr_get_rd(k);
    bw_getread1.get_read_logout(j);
  }

  w_dele_win_ptr_wins_dbf(p1);

  for (j=get_win_ptr_grp_ptr(i,0);j<=get_win_ptr_grp_ptr(i,2);j++)
  {
    SetFocus(bw_main1.win_main_hnd);

    k=get_win_h_w_ptr(i,0)+j-get_win_ptr_grp_ptr(i,0);
    DestroyWindow(get_win_hnd(k));
  }

  SetFocus(bw_main1.win_main_hnd);

  exist=0;

  for (j=WIN_NUM-1;j>=1;j--)
  {
    if (get_win_ptr_win_mark(j)!=0)
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

  l=get_win_ptr_grp_id(j);

  n=get_win_ptr_grp_ptr(i,2)-get_win_ptr_grp_ptr(i,0)+1;

  q=0;

  for (k=get_win_ptr_grp_ptr(i,0);k<=get_win_ptr_grp_ptr(i,2);k++)
  {
    q=q+get_win_ptr_fld_in_win(k,1)-get_win_ptr_fld_in_win(k,0)+1;
  }

  r=get_win_ptr_fld_in_win(get_win_ptr_grp_ptr(l,2),1);

  s=get_win_ptr_fld_in_win(get_win_ptr_grp_ptr(i,2),1)+1;

  for (k=s;k<=r;k++)
  {
    get_t_fldname(k,sfn1,FLD_NAME_SIZE);
    set_t_fldname(k-q,sfn1,FLD_NAME_SIZE);
    set_t_fldtype(k-q,get_t_fldtype(k));
    set_t_fldbase(k-q,get_t_fldbase(k));
    set_t_fldseri(k-q,get_t_fldseri(k));
    set_t_fldlen(k-q,get_t_fldlen(k));
    set_t_flddec(k-q,get_t_flddec(k));
    set_t_fldedt(k-q,get_t_fldedt(k));
  }

  for (k=r-q+1;k<=r;k++)
  {
    set_c_t_fldname(k,0,0);
    set_t_fldbase(k,0);
    set_t_fldseri(k,0);
    set_t_fldlen(k,0);
    set_t_flddec(k,0);
    set_t_fldedt(k,0);
    set_t_fldtype(k,0);
  }

  t=get_win_h_w_ptr(i,1)-get_win_h_w_ptr(i,0)+1;
  if (get_win_h_w_ptr(i,5)==0)
     t=t;
  else
     t=t+get_win_h_w_ptr(i,5)-get_win_h_w_ptr(i,4)+1;

  p10=get_win_ptr_grp_ptr(l,2);

  for (k=i+1;k<=l;k++)
  {
    for (m=get_win_ptr_grp_ptr(k,0);m<=get_win_ptr_grp_ptr(k,2);m++)
    {
      set_win_ptr_fld_in_win(m-n,0,get_win_ptr_fld_in_win(m,0)-q);
      set_win_ptr_fld_in_win(m-n,1,get_win_ptr_fld_in_win(m,1)-q);
      set_win_ptr_grp_id(m-n,get_win_ptr_grp_id(m)-1);
      set_win_ptr_win_mark(m-n,m-n);

      for (o=0;o<STRU_NUM;o++)
      {
	set_win_ptr_wins_dbf(o,m-n,get_win_ptr_wins_dbf(o,m));
      }

      set_win_ptr_get_rd(m-n,get_win_ptr_get_rd(m));

      set_win_linep(m-n,0,get_win_linep(m,0));
      set_win_linep(m-n,1,get_win_linep(m,1));

      set_win_con(m-n,0,get_win_con(m,0));
      set_win_con(m-n,1,get_win_con(m,1));

      bw_dialog1.set_c_win_mv_getv(m,SMG_SIZE-1,0);

      bw_dialog1.get_win_mv_getv(m,smv1,SMG_SIZE);
      bw_dialog1.set_win_mv_getv(m-n,smv1,SMG_SIZE);

      bw_dialog1.set_win_mv_getp(m-n,bw_dialog1.getv_win_mv_getp(m));

      set_win_h_up_ptr(m-n,0,get_win_h_up_ptr(m,0)-t);
      set_win_h_up_ptr(m-n,1,get_win_h_up_ptr(m,1)-t);

      set_win_phh(m-n,get_win_phh(m));

      get_win_window_name(m,stn1,FN_SIZE);
      set_win_window_name(m-n,stn1,FN_SIZE);
      get_win_find_name(m,stn1,FN_SIZE);
      set_win_find_name(m-n,stn1,FN_SIZE);

      for (o=1;o<LIN_NUM;o++)
      {
	for (p=1;p<COL_NUM;p++)
	{
	  bw_buff1.set_t3_winfile(m-n,o,p,bw_buff1.get_t3_winfile(m,o,p));
	  if (bw_buff1.get_t3_linecol(m,o,p)!=0)
	    bw_buff1.set_t3_linecol(m-n,o,p,bw_buff1.get_t3_linecol(m,o,p)-q);
	  else
	    bw_buff1.set_t3_linecol(m-n,o,p,0);
	}
      }
    }

    set_win_ptr_grp_ptr(k-1,0,get_win_ptr_grp_ptr(k,0)-n);
    set_win_ptr_grp_ptr(k-1,1,get_win_ptr_grp_ptr(k,1)-n);
    set_win_ptr_grp_ptr(k-1,2,get_win_ptr_grp_ptr(k,2)-n);

    if (k==l)
    {
      set_win_ptr_grp_ptr(l,0,0);
      set_win_ptr_grp_ptr(l,1,0);
      set_win_ptr_grp_ptr(l,2,0);
    }
  }

  for (k=p10-n+1;k<=p10;k++)
  {
    set_win_ptr_fld_in_win(k,0,0);
    set_win_ptr_fld_in_win(k,1,0);
    set_win_ptr_win_mark(k,0);
    set_win_ptr_grp_id(k,0);

    for (o=0;o<STRU_NUM;o++)
    {
      set_win_ptr_wins_dbf(o,k,0);
    }

    set_win_ptr_get_rd(k,0);
  }

  if (i==l)
  {
    set_win_ptr_grp_ptr(l,0,0);
    set_win_ptr_grp_ptr(l,1,0);
    set_win_ptr_grp_ptr(l,2,0);
  }

  /* segment */

  j=get_win_h_w_ptr(i,1)-get_win_h_w_ptr(i,0)+1;
  if (get_win_h_w_ptr(i,5)==0)
    j=j;
  else
    j=j+get_win_h_w_ptr(i,5)-get_win_h_w_ptr(i,4)+1;

  if (get_win_h_w_ptr(i,5)==0) m=get_win_h_w_ptr(i,4);
  else m=get_win_h_w_ptr(i,5)+1;

  if (get_win_h_w_ptr(l,5)==0) o=get_win_h_w_ptr(l,1);
  else o=get_win_h_w_ptr(l,5);
/*
  sprintf(str,"j=%d,hptr30=%d,hptr31=%d,i=%d,l=%d,m=%d,o=%d,"
				       ,j
				       ,win_h_w_ptr[i][0]
				       ,win_h_w_ptr[i][1]
				       ,i,l,m,o);
  MessageBox(bw_main1.win_hwnd1,str,"aa",MB_OK);
*/
  for (k=i+1;k<=l;k++)
  {
    if (get_win_h_w_ptr(k,0)>=j) set_win_h_w_ptr(k-1,0,get_win_h_w_ptr(k,0)-j);
    else                  set_win_h_w_ptr(k-1,0,0);
    if (get_win_h_w_ptr(k,1)>=j) set_win_h_w_ptr(k-1,1,get_win_h_w_ptr(k,1)-j);
    else                  set_win_h_w_ptr(k-1,1,0);
    if (get_win_h_w_ptr(k,2)>=j) set_win_h_w_ptr(k-1,2,get_win_h_w_ptr(k,2)-j);
    else                  set_win_h_w_ptr(k-1,2,0);
    if (get_win_h_w_ptr(k,4)>=j) set_win_h_w_ptr(k-1,4,get_win_h_w_ptr(k,4)-j);
    else                  set_win_h_w_ptr(k-1,4,0);
    if (get_win_h_w_ptr(k,5)>=j) set_win_h_w_ptr(k-1,5,get_win_h_w_ptr(k,5)-j);
    else                  set_win_h_w_ptr(k-1,5,0);
    if (get_win_h_w_ptr(k,6)>=j) set_win_h_w_ptr(k-1,6,get_win_h_w_ptr(k,6)-j);
    else                  set_win_h_w_ptr(k-1,6,0);

    if (k==l)
    {
      set_win_h_w_ptr(k,0,0);
      set_win_h_w_ptr(k,1,0);
      set_win_h_w_ptr(k,2,0);
      set_win_h_w_ptr(k,3,0);
      set_win_h_w_ptr(k,4,0);
      set_win_h_w_ptr(k,5,0);
      set_win_h_w_ptr(k,6,0);
    }
  }

  for (k=m;k<=o;k++)
  {
    if (get_win_h_ci_ptr(k,4)!=0)
    {
      SetWindowLong(get_win_hnd(k),GWL_ID,k-j);
    }

    if (get_win_h_ci_ptr(k,0)>=n) set_win_h_ci_ptr(k-j,0,get_win_h_ci_ptr(k,0)-n);  /* win num,x,y,hnd num,main hnd */
    set_win_h_ci_ptr(k-j,1,get_win_h_ci_ptr(k,1));
    set_win_h_ci_ptr(k-j,2,get_win_h_ci_ptr(k,2));
    set_win_h_ci_ptr(k-j,3,k-j);

    if (get_win_h_ci_ptr(k,4)==0) set_win_h_ci_ptr(k-j,4,0);
    else set_win_h_ci_ptr(k-j,4,get_win_h_ci_ptr(k,4)-j);

    set_win_hnd(k-j,get_win_hnd(k));

    set_win_proc(k-j,get_win_proc(k));

  }

  for (k=o-j+1;k<=o;k++)
  {
    set_win_h_ci_ptr(k,0,0);  /* win num,x,y,hnd num,main hnd */
    set_win_h_ci_ptr(k,1,0);
    set_win_h_ci_ptr(k,2,0);
    set_win_h_ci_ptr(k,3,0);
    set_win_h_ci_ptr(k,4,0);

    set_win_hnd(k,0);
  }

  if (i==l)
  {
    set_win_h_w_ptr(i,0,0);
    set_win_h_w_ptr(i,1,0);
    set_win_h_w_ptr(i,2,0);
    set_win_h_w_ptr(i,3,0);
    set_win_h_w_ptr(i,4,0);
    set_win_h_w_ptr(i,5,0);
    set_win_h_w_ptr(i,6,0);
  }

  /* end mem var move */

  win_ptr_new_win=win_ptr_new_win-n;

  win_h_w_total_ptr=win_h_w_total_ptr-j;

  bw_xbase1.win_answer=0;

  return(0);
}

int bw_win::w_read_winfile(char *p_fn,int p_fn_size)
{
  int  p1,p2,same,ends;
  int  state1,state2,state3;
  int  state4,state5,state6;
  int  state7,state8,state9;
  int  state10;
  long li;
  int  is_tab=0;
  int  is_find=0;
  char tmps5[STRU_NUM][FN_SIZE];
  int  tmps6[STRU_NUM];
  char tmps7[FN_SIZE];
  char tmps8[FN_SIZE];
  char tmps9[FN_SIZE];
  int  s_ps=(-1);
  int  s_ps1;
  int  i,j,k,l,m,n,o,p;
  int  lcnt,cmd;
  int  free_base;
  char str1[SMG_SIZE*2];
  char str2[FN_SIZE];
  char str3[FN_SIZE];
  char str4[FN_SIZE];
  FILE *fp1;
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  int  s_firstline;
  int  s_lastline;
  int  s_exist;
  int  s_beginposi;
  int  s_endposi;

  for (i=0;i<STRU_NUM;i++) 
    for (j=0;j<FN_SIZE;j++) 
      tmps5[i][j]=0;

  for (j=0;j<FN_SIZE;j++) 
  {
    tmps7[j]=0;
    tmps8[j]=0;
    tmps9[j]=0;
  }

  strcpy(texts1 ,"usetable=");
  strcpy(texts2 ,"enddefine");
  strcpy(texts3 ,"screenseg");
  strcpy(texts4 ,"endscreen");
  strcpy(texts5 ,"readvatype");
  strcpy(texts6 ,"findfile=");
  strcpy(texts7 ,"findbase=");
  strcpy(texts8 ,"switchbmp");
  strcpy(texts9 ,"switchtm=");
  strcpy(texts10,"ci_mode");

  free_base=bw_xbase1.w_free_xbase();

  fp1=fopen(p_fn,"r");    /* fetch page of screen format from screen file */
  if (fp1==NULL)
  {
    w_atten1(p_fn);
    return(1);
  }

  for (k=win_ptr_new_win;k<WIN_NUM-1;k++)
  {
    set_win_timer(k,0);

    set_win_ci_mode(k,0);

    s_firstline=1;
    s_lastline=1;

    for (j=1;j<LIN_NUM;j++)
      for (i=1;i<COL_NUM;i++)
	bw_buff1.set_t3_winfile(k,j,i,' ');

    lcnt=0;
    set_win_switch_bmp(k,0);

    for (i=1;i<LIN_NUM+10;i++)
    {
      for (n=0;n<SMG_SIZE*2;n++) str1[n]=' ';

      fgets(str1,SMG_SIZE*2,fp1);
      if (feof(fp1))
      {
	ends=1;
	break;
      }

      cmd=0;
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

      while (p1<COL_NUM)  /* scan this line */ // get head lines
      {
	for (j=j;j<COL_NUM;j++)
        {
          if (str1[j]=='&') break; /* locate for '&' */
        }

	j++;
	p1=j;
	if (p1>COL_NUM-1) break;

        // find usetable & stru name
	same=1;
	for (p2=p1;p2<=p1+strlen(texts1)-1;p2++)  
	{
	  if ((texts1[p2-p1]>=0)&&(texts1[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts1[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  state1=1;  // there is keyword "usetable=" 
	  is_tab=1;  // this scrn file is table screen 

	  s_ps++;
	  if (s_ps>=STRU_NUM) s_ps=STRU_NUM-1;

	  for (l=0;l<FN_SIZE;l++)
	  {
	    if ((str1[p1+strlen(texts1)+l]>=0)&&(str1[p1+strlen(texts1)+l]<=' ')) break;
            else
            {
	      tmps5[s_ps][l+0]=str1[p1+strlen(texts1)+l];
	      tmps5[s_ps][l+1]=0;
            }
	  }
	}

        // find findbase name
	same=1;
	for (p2=p1;p2<=p1+strlen(texts7)-1;p2++)  
	{
	  if ((texts7[p2-p1]>=0)&&(texts7[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts7[p2-p1])
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
	    if ((str1[p1+strlen(texts7)+l]>=0)&&(str1[p1+strlen(texts7)+l]<=' ')) break;
            else
            {
	      tmps8[l+0]=str1[p1+strlen(texts7)+l];
	      tmps8[l+1]=0;
            }
	  }
	}

	// find timer name
	same=1;
	for (p2=p1;p2<=p1+strlen(texts9)-1;p2++)  
	{
	  if ((texts9[p2-p1]>=0)&&(texts9[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts9[p2-p1])
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
	    if ((str1[p1+strlen(texts9)+l]>=0)&&(str1[p1+strlen(texts9)+l]<=' ')) break;
            else
            {
	      tmps9[l+0]=str1[p1+strlen(texts9)+l];
	      tmps9[l+1]=0;
            }
	  }
	}

	same=1;
	for (p2=p1;p2<=p1+strlen(texts5)-1;p2++)  /* recnigze keywords */
	{
	  if ((texts5[p2-p1]>=0)&&(texts5[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts5[p2-p1])
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
	for (p2=p1;p2<=p1+strlen(texts10)-1;p2++)  /* recnigze keywords */
	{
	  if ((texts10[p2-p1]>=0)&&(texts10[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts10[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  set_win_ci_mode(k,1);
          state10=1;
	}

	same=1;
	for (p2=p1;p2<=p1+strlen(texts8)-1;p2++)  /* recnigze keywords */
	{
	  if ((texts8[p2-p1]>=0)&&(texts8[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts8[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state8=1;

	same=1;
	for (p2=p1;p2<=p1+strlen(texts2)-1;p2++)
	{
	  if ((texts2[p2-p1]>=0)&&(texts2[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts2[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state2=1;

	same=1;
	for (p2=p1;p2<=p1+strlen(texts3)-1;p2++)
	{
	  if ((texts3[p2-p1]>=0)&&(texts3[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts3[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state3=1;

	same=1;
	for (p2=p1;p2<=p1+strlen(texts4)-1;p2++)
	{
	  if ((texts4[p2-p1]>=0)&&(texts4[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts4[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1) state4=1;

	same=1;
	for (p2=p1;p2<=p1+strlen(texts6)-1;p2++)
	{
	  if ((texts6[p2-p1]>=0)&&(texts6[p2-p1]<=' ')) break;
	  if (str1[p2]!=texts6[p2-p1])
	  {
	    same=0;
	    break;
	  }
	}
	if (same==1)
	{
	  state7=1;
	  o=p1+strlen(texts6);
	  for (p=o;p<COL_NUM;p++)
	  {
	    if ((str1[p]>=0)&&(str1[p]<=' ')) break;
	    else
            {
              tmps7[p-o+0]=str1[p];
              tmps7[p-o+1]=0;
            }
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
	set_win_switch_bmp(k,1);
      }
      if (state9==1)
      {
	cmd=1; // timer
        li=bw_inkey1.str2long(tmps9,FN_SIZE);
	set_win_timer(k,li);
      }
      if (state3==1) break; /* screenseg */
      if (state4==1)        /* endscreen */
      {
	ends=1;
	break;
      }

      scnt=k;

      if (cmd!=0) continue;

      lcnt++;

      if (get_win_ci_mode(k)==1)
      {
        str1[COL_NUM-1]=0;

        if (bw_inkey1.strempty(str1)==1)
        {
	  if (s_firstline==1)
	  {
	    s_exist=0;
	    for (j=0;j<COL_NUM;j++)
	    {
	      if ((str1[j]>' ')||(str1[j]<0))
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
	      if ((str1[j]>' ')||(str1[j]<0))
	      {
	        s_exist=1;
	        break;
	      }
	    }
	    if (s_exist==1) s_endposi=j;
            else s_endposi=1;

	    for (j=0;j<COL_NUM;j++)
	    {
	      str1[j]=' ';
	    }

	    str1[s_beginposi]='.';
            str1[s_endposi]='.';

            set_win_ci_posi(k,0,s_beginposi+1);
	    set_win_ci_posi(k,1,s_endposi+1);

	    s_firstline=0;
	  }
	  else
	  {
            s_exist=0;
	    for (j=0;j<COL_NUM;j++)
	    {
	      if ((str1[j]>' ')||(str1[j]<0))
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
	      if ((str1[j]>' ')||(str1[j]<0))
	      {
	        s_exist=1;
	        break;
	      }
	    }
	    if (s_exist==1) s_endposi=j;
            else s_endposi=1;

	    if (bw_main1.win_lang==1)
	    {
	      str1[s_beginposi]=' ';
	      str1[s_endposi]=' ';
	    }
	    else
	    {
	      str1[s_beginposi]=' ';
	      str1[s_endposi]=' ';

	      if (s_beginposi+1<COL_NUM) str1[s_beginposi+1]=' ';
	      if (s_endposi-1>=0)        str1[s_endposi-1]=' ';
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
	          bw_buff1.set_t3_winfile(k,lcnt-1,j,' ');
	        }
	      }
	      s_lastline=0;

	      bw_buff1.set_t3_winfile(k,lcnt-1,s_beginposi+1,'.');
	      bw_buff1.set_t3_winfile(k,lcnt-1,s_endposi+1,'.');

	    }
          }
        }

      }

      for (j=0;j<COL_NUM;j++)
      {
	if ((str1[j]>=0)&&(str1[j]<' ')) str1[j]=' ';
	bw_buff1.set_t3_winfile(k,lcnt,j+1,str1[j]);
      }

      if (feof(fp1))
      {
	ends=1;
	break;
      }
    }
    if (ends==1) break;
  }

  m=win_ptr_new_win;

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
      win_ptr_new_win=k+1;
    }
  }
  else
  {
    w_atten3();
    return(1);
  }

  w_login_win(m,k,p_fn,p_fn_size,tmps7,FN_SIZE);
  
  if (is_tab==1)  /* it is a table scrn */
  {
    l=0;
    for (i=0;i<=s_ps;i++)     /* login base ,fetch buff ptr */
    {
      j=bw_xbase1.w_login_xbase(l);
      if (j<0)
      {
	w_atten58();
	w_dele_win_ptr(m);
	return(1);
      }
      tmps6[i]=j;
      l=j+1;
    }

    for (i=m;i<=k;i++)  /* mark win base ptr */
    {
      for (j=0;j<STRU_NUM;j++)
      {
	set_win_ptr_wins_dbf(j,i,0);
      }

      for (j=0;j<=s_ps;j++)
      {
        if (tmps6[j]>=STRU_NUM) continue;
	set_win_ptr_wins_dbf(tmps6[j],i,1);
	bw_xbase1.set_win_state_bff_in_use(tmps6[j],1);
      }
    }

    for (i=0;i<=1;i++) for (j=0;j<=s_ps;j++)
    {
      if (tmps6[j]>=STRU_NUM) continue;
      set_win_tabname(i,tmps6[j],"                      ",20);
    }
			   /* stru&base name in win 0-stru 1-base*/
    for (s_ps1=0;s_ps1<=s_ps;s_ps1++)  /* fetch stru & base name from tmps5 */
    {
      if (tmps6[s_ps1]>=STRU_NUM) continue;
      j=0;
      for (i=0;i<FN_SIZE;i++)          /* fetch base name */
      {
	if (tmps5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten4();
	w_dele_xbase_state(m);
        w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	bw_inkey1.cut_string(tmps5[s_ps1],0,i,FN_SIZE,stn2,FN_SIZE);
	set_win_tabname(1,tmps6[s_ps1],stn2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch stru name */
      {
	if (tmps5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten5();
	w_dele_xbase_state(m);
        w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten6();
	else bw_inkey1.cut_string(tmps5[s_ps1],p1+5,i-p1-5,FN_SIZE,stn2,FN_SIZE);
	set_win_tabname(0,tmps6[s_ps1],stn2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch base type */
      {
	if (tmps5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten59();
	w_dele_xbase_state(m);
        w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten60();
	else bw_inkey1.cut_string(tmps5[s_ps1],p1+9,i-p1-9,FN_SIZE,str2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch backup type */
      {
	if (((tmps5[s_ps1][i]>=0)&&(tmps5[s_ps1][i]<=' '))||(tmps5[s_ps1][i]==','))
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten61();
	w_dele_xbase_state(m);
	w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten62();
	else bw_inkey1.cut_string(tmps5[s_ps1],p1+7,i-p1-7,FN_SIZE,str3,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch carryon &carryoff */
      {
	if ((tmps5[s_ps1][i]>=0)&&(tmps5[s_ps1][i]<=' '))
	{
	  j=1;
	  break;
	}
      }
      if (j==1)  /* not find ' ' */
      {
	if (i-p1>0)
	{
	  bw_inkey1.cut_string(tmps5[s_ps1],p1,i-p1,FN_SIZE,str4,FN_SIZE);
	  if (strncmp(str4,"carryon",7)==0)
	    bw_xbase1.set_win_carry_on(tmps6[s_ps1],1);
	  else
	    bw_xbase1.set_win_carry_on(tmps6[s_ps1],0);
	}
	else bw_xbase1.set_win_carry_on(tmps6[s_ps1],0);
      }
      else bw_xbase1.set_win_carry_on(tmps6[s_ps1],0);
    }
  }

  for (s_ps1=0;s_ps1<=s_ps;s_ps1++)  /* database type , backup type */
  {
    if (tmps6[s_ps1]>=STRU_NUM) continue;

    if (strcmp(str2,"xbase")==0) bw_xbase1.set_win_base_type(tmps6[s_ps1],0);
    else bw_xbase1.set_win_base_type(tmps6[s_ps1],1);

    bw_inkey1.strtrim(str3,FN_SIZE);

    if (strcmp(str3,"1")==0) bw_xbase1.set_win_base_backup(tmps6[s_ps1],1);
    else bw_xbase1.set_win_base_backup(tmps6[s_ps1],0);
  }

  return(0);
}

int bw_win::w_dele_xbase_state(int p_wptr)
{
  int  i;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_win_ptr_wins_dbf(i,p_wptr)==1)
    {
      bw_xbase1.set_win_state_bff_in_use(i,0);
      set_win_tabname(0,i,"",0);
      set_win_tabname(1,i,"",0);
    }
  }

  return(0);
}

int bw_win::w_echo_winrec_paint(int p_pagecnt,int mark)  //paint win
{ 
  HFONT holdfont,hfont;
  HDC   hdc;
  int   p1,p2,p4,p5,p7,p8;
  int   state1;
  int   state7;
  int   i,j,k;
  int   ptr1,ptr3;
  char  str[SMG_SIZE];

  if (get_win_ptr_fld_in_win(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((get_win_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_win_ptr_fld_in_win(p_pagecnt,0,get_win_ptr_fld_in_win(i,1)+1);
    ptr1=get_win_ptr_fld_in_win(i,1);
  }
  else ptr1=get_win_ptr_fld_in_win(p_pagecnt,0)-1;

  hdc=GetDC(bw_main1.win_hwnd);

  if (get_win_ci_mode(p_pagecnt)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  p7=0;   
  p8=0;   

  for (i=1;i<LIN_NUM;i++)
  {
    if (get_win_ci_mode(p_pagecnt)==0)
    {                                                                                    
      p1=COL_NUM-1;
      p2=0;
      for (j=1;j<COL_NUM;j++)  
      {
        if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
        {
	  p1=j;
	  break;
        }
      }
      for (j=COL_NUM-1;j>=1;j--)
      {
	if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
        {
	  p2=j;
	  break;
        }
      }
      if (p2<p1) continue;
    }
    else
    {
      p1=get_win_ci_posi(p_pagecnt,0);
      p2=get_win_ci_posi(p_pagecnt,1);

      j=0;

      for (k=p1;k<=p2;k++)
      {
	if ((bw_buff1.get_t3_winfile(p_pagecnt,i,k)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,k)<0))
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
    ptr3=0;
    state7=0;

    for (j=p1;j<=p2;j++)  
    {
      if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='&')
      {
        ptr1++;
	p4=0;      
	p5=1;      
        state1=1; 
	if (mark==1)
	{
	}
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<=' ')
	{
          if (state7==1) continue;
	  if (mark==1)
	  {
	    if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0)
	    {
	      if (ptr3==1)
	      {
		ptr3=0;
		continue;
              }
	      else
	      {
                ptr3=1;
		str[0]=bw_buff1.get_t3_winfile(p_pagecnt,i,j);
		if (bw_buff1.get_t3_winfile(p_pagecnt,i,j+1)!='&')
                {
		  str[1]=bw_buff1.get_t3_winfile(p_pagecnt,i,j+1);
                  str[2]=0;
                }
                else str[1]=0;
		if (get_win_ci_mode(p_pagecnt)==0)
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
	  if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      p5=0;
	    }
	  }
	  else
	  {
	    //state1=0;
	    ptr3=0;
	  }
	}
	else
	{
	  ptr3=0;
	  if (state1==1)
	  {
	    if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='(')
	      &&(bw_buff1.get_t3_winfile(p_pagecnt,i,j-1)!='&'))
	    {
	      state7=1;
              state1=0;
              continue;
            }
	    if ((p4==0)&&(bw_buff1.get_t3_winfile(p_pagecnt,i,j-1)=='%'))
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
	    if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)==')')
            {
	      state7=0;
	      continue;
	    }
	    if (state7==1) continue;
	    if (mark==1)
	    {
	      str[0]=bw_buff1.get_t3_winfile(p_pagecnt,i,j);
	      str[1]=0;
	      if (get_win_ci_mode(p_pagecnt)==0)
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

  if (get_win_ci_mode(p_pagecnt)==0)
  {
    SelectObject(hdc,holdfont);
  }

  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}

int bw_win::w_field_info1(int p_pagecnt,int mark) // get field info
{ 
  int  p1,p2,p4,p5,p6,p7,p8,p9,p10,p10a;
  int  state1;
  int  state7;
  int  i,j,k,l;
  int  ptr1,ptr3;
  int  t1,t2;
  char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];

  win_mark=mark;

  for (i=0;i<WIN_STYLE_NUM;i++) set_win_style(p_pagecnt,i,0);

  if (get_win_ptr_fld_in_win(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((get_win_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_win_ptr_fld_in_win(p_pagecnt,0,get_win_ptr_fld_in_win(i,1)+1);
    ptr1=get_win_ptr_fld_in_win(i,1);
  }
  else ptr1=get_win_ptr_fld_in_win(p_pagecnt,0)-1;

  win_h_ci_total_ptr=win_h_w_total_ptr;

  ptr3=win_h_ci_total_ptr;

  if (win_h_ci_total_ptr>=HND_NUM) return(0);

  p7=0;
  p8=0;   
  p9=0;   
  p10=0;  
  p10a=0; 

  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      bw_buff1.set_t3_linecol(p_pagecnt,i,j,0);
    }
  }

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    if (get_win_ci_mode(p_pagecnt)==0)
    {                                                                                    
      p1=COL_NUM-1;
      p2=0;
      for (j=1;j<COL_NUM;j++)  
      {
        if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
        {
	  p1=j;
	  break;
        }
      }
      for (j=COL_NUM-1;j>=1;j--)
      {
	if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
        {
	  p2=j;
	  break;
        }
      }
      if (p2<p1) continue;
    }
    else
    {
      p1=get_win_ci_posi(p_pagecnt,0);
      p2=get_win_ci_posi(p_pagecnt,1);

      j=0;
      for (k=p1;k<=p2;k++)
      {
	if ((bw_buff1.get_t3_winfile(p_pagecnt,i,k)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,k)<0))
	{
	  j=1;
	  break;
	}
      }

      if (j==0) continue;
    }

    state1=0;
    state7=0;
    if (p7==0) p7=i;
    if (p8==0) p8=p1;
    if (p7!=0) set_win_con(p_pagecnt,1,p7);
    if (p8!=0) set_win_con(p_pagecnt,0,p8);
    if (p9==0) p9=p2-p1+2;
    if (p9!=0)   set_win_con(p_pagecnt,2,p9);
    if (p10==0)  p10=i;

    if (bw_main1.win_cre_menu==1) p10a=i-p10+4;
    else p10a=i-p10+3;

    if (p10a!=0) set_win_con(p_pagecnt,3,p10a);
    p4=0;
    p5=0;
    p6=0;

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='&')
      {
	if (p5==1)
	{
	  set_t_fldlen(ptr1,j-1-p6);

	  set_win_style(p_pagecnt,1,1);

	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if (str2[0]=='(') set_win_style(p_pagecnt,2,1);
	  if (str2[0]=='[') set_win_style(p_pagecnt,3,1);
	  if (str2[0]=='@') set_win_style(p_pagecnt,4,1);
	  if (str2[0]=='#') set_win_style(p_pagecnt,5,1);
	  if (str2[0]=='%') set_win_style(p_pagecnt,6,1);
	  if (str2[0]==':') set_win_style(p_pagecnt,7,1);
	  if (str2[0]=='?') set_win_style(p_pagecnt,8,1);
	  if (str2[0]=='+') set_win_style(p_pagecnt,9,1);
	  if (str2[0]=='-') set_win_style(p_pagecnt,9,1);

	}

	ptr1++;
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j+1)=='#') bw_buff1.set_t3_linecol(p_pagecnt,i,j+1,ptr1);
	else bw_buff1.set_t3_linecol(p_pagecnt,i,j,ptr1);
	p4=0;      
	p5=1;      
	state1=1;
        p6=j;      

      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<=' ')
	{
          if (state7==1) continue;
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      set_win_style(p_pagecnt,1,1);

	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='(') set_win_style(p_pagecnt,2,1);
	      if (str2[0]=='[') set_win_style(p_pagecnt,3,1);
	      if (str2[0]=='@') set_win_style(p_pagecnt,4,1);
	      if (str2[0]=='#') set_win_style(p_pagecnt,5,1);
	      if (str2[0]=='%') set_win_style(p_pagecnt,6,1);
	      if (str2[0]==':') set_win_style(p_pagecnt,7,1);
	      if (str2[0]=='?') set_win_style(p_pagecnt,8,1);
	      if (str2[0]=='+') set_win_style(p_pagecnt,9,1);
	      if (str2[0]=='-') set_win_style(p_pagecnt,9,1);

	      set_t_fldlen(ptr1,j-p6);
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
	    if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='(')
	      &&(bw_buff1.get_t3_winfile(p_pagecnt,i,j-1)!='&'))
	    {
              state7=1;
	      state1=0;
	      set_t_fldlen(ptr1,j-p6);
              continue;
	    }
	    if ((p4==0)&&(bw_buff1.get_t3_winfile(p_pagecnt,i,j-1)=='%'))
	    {
	      set_c_t_fldname(ptr1,p4,'%');
	      p4++;
	    }
	    set_c_t_fldname(ptr1,p4+0,bw_buff1.get_t3_winfile(p_pagecnt,i,j));
	    set_c_t_fldname(ptr1,p4+1,0);
	    set_t_fldtype(ptr1,'c');
	    p4++;
	  }
	  else
	  {
	    if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)==')')
	    {
	      state7=0;
	      continue;
            }
	    if (p5==1)
	    {
	      set_win_style(p_pagecnt,1,1);

	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='(') set_win_style(p_pagecnt,2,1);
	      if (str2[0]=='[') set_win_style(p_pagecnt,3,1);
	      if (str2[0]=='@') set_win_style(p_pagecnt,4,1);
	      if (str2[0]=='#') set_win_style(p_pagecnt,5,1);
	      if (str2[0]=='%') set_win_style(p_pagecnt,6,1);
	      if (str2[0]==':') set_win_style(p_pagecnt,7,1);
	      if (str2[0]=='?') set_win_style(p_pagecnt,8,1);
	      if (str2[0]=='+') set_win_style(p_pagecnt,9,1);
	      if (str2[0]=='-') set_win_style(p_pagecnt,9,1);

	      set_t_fldlen(ptr1,j-p6);
	      p5=0;
	    }
	  }
	}
      }
    }

    if (p5==1)
    {
      set_t_fldlen(ptr1,j-1-p6);
    }
  }
/*
  win_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=ptr3;i<=get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5);i++)
  {
    set_win_proc(i,(FARPROC)GetWindowLong(get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tproc);
  }
*/
  set_win_h_up_ptr(p_pagecnt,0,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),6));
  set_win_h_up_ptr(p_pagecnt,1,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5));

  win_h_w_total_ptr=win_h_ci_total_ptr;

  set_win_ptr_fld_in_win(p_pagecnt,1,ptr1);

  // adjust field length for 800*600 256color mode
  /*
  for (i=get_win_ptr_fld_in_win(p_pagecnt,0);i<=get_win_ptr_fld_in_win(p_pagecnt,1);i++)
  {
    if (get_t_fldlen(i)>18)
    {
      set_t_fldlen(i,get_t_fldlen(i)-4);
    }
  }
  */
  return(0);
}

//int bw_win::w_cre_ci_button(int p_pagecnt,char *p_s1,int p_s1_len,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_button(int p_pagecnt,char *p_s1,int p_s1_size,int p6,int p7,int p8,int p9)
{
  HWND hnd;
  int  l,j;

  if (get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("button",p_s1
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,(int)((p6-p8)*bw_main1.win_edit_xchar)
		      ,(int)((p9-p7)*bw_main1.win_edit_ychar-3)
		      ,(int)((strlen(p_s1)+3)*bw_main1.win_edit_xchar)
		      ,(int)(bw_main1.win_edit_ychar+6)
		      ,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
		      ,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",p_s1
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,(int)((p6-p8)*bw_main1.win_xchar)
		      ,(int)((p9-p7)*bw_main1.win_ychar-3)
		      ,(int)((3+strlen(p_s1))*bw_main1.win_xchar)
		      ,(int)(bw_main1.win_ychar+6)
		      ,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
		      ,bw_main1.win_ins,NULL);
  }

  set_win_hnd(win_h_ci_total_ptr,hnd);
  if (get_win_hnd(win_h_ci_total_ptr)==NULL) bw_main1.win_cre_ok=0;

  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,0,p_pagecnt);
  set_win_h_ci_ptr(win_h_ci_total_ptr,1,p6);
  set_win_h_ci_ptr(win_h_ci_total_ptr,2,p9);
  set_win_h_ci_ptr(win_h_ci_total_ptr,3,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,4,p_pagecnt-get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_pagecnt),0)+get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),0));

  win_h_ci_total_ptr++;

  return(0);
}

//int bw_win::w_cre_ci_edit(int p_pagecnt,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_edit(int p_pagecnt,int p6,int p7,int p8,int p9)
{
  HWND hnd;

  if (get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("edit",""
		,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
		,(int)((p6-p8)*bw_main1.win_edit_xchar)
		,(int)((p9-p7)*bw_main1.win_edit_ychar-6)
		,(int)(4*bw_main1.win_edit_xchar)
		,(int)(bw_main1.win_edit_ychar+12)
		,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
		,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("edit",""
		,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
		,(int)((p6-p8)*bw_main1.win_xchar)
		,(int)((p9-p7)*bw_main1.win_ychar-6)
		,(int)(4*bw_main1.win_xchar)
		,(int)(bw_main1.win_ychar+12)
		,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
		,bw_main1.win_ins,NULL);
  }

  set_win_hnd(win_h_ci_total_ptr,hnd);
  if (get_win_hnd(win_h_ci_total_ptr)==NULL) bw_main1.win_cre_ok=0;

  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,0,p_pagecnt);
  set_win_h_ci_ptr(win_h_ci_total_ptr,1,p6);
  set_win_h_ci_ptr(win_h_ci_total_ptr,2,p9);
  set_win_h_ci_ptr(win_h_ci_total_ptr,3,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,4,p_pagecnt-get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_pagecnt),0)+get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),0));

  win_h_ci_total_ptr++;

  return(0);
}

//int bw_win::w_cre_ci_radio(int p_pagecnt,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_radio(int p_pagecnt,int p6,int p7,int p8,int p9)
{
  HWND hnd;

  if (get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON
			,(int)((p6-p8)*bw_main1.win_edit_xchar)
			,(int)((p9-p7)*bw_main1.win_edit_ychar)
			,(int)(2*bw_main1.win_edit_xchar)
			,(int)(bw_main1.win_edit_ychar)
			,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
			,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON
			,(int)((p6-p8)*bw_main1.win_xchar)
			,(int)((p9-p7)*bw_main1.win_ychar)
			,(int)(2*bw_main1.win_xchar)
			,(int)(bw_main1.win_ychar)
			,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
			,bw_main1.win_ins,NULL);
  }

  set_win_hnd(win_h_ci_total_ptr,hnd);
  if (get_win_hnd(win_h_ci_total_ptr)==NULL) bw_main1.win_cre_ok=0;

  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,0,p_pagecnt);
  set_win_h_ci_ptr(win_h_ci_total_ptr,1,p6);
  set_win_h_ci_ptr(win_h_ci_total_ptr,2,p9);
  set_win_h_ci_ptr(win_h_ci_total_ptr,3,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,4,p_pagecnt-get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_pagecnt),0)+get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),0));

  win_h_ci_total_ptr++;

  return(0);
}

//int bw_win::w_cre_ci_check(int p_pagecnt,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_check(int p_pagecnt,int p6,int p7,int p8,int p9)
{
  HWND hnd;

  if (get_win_ci_mode(p_pagecnt)==0)
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_CHECKBOX
			,(int)((p6-p8)*bw_main1.win_edit_xchar)
			,(int)((p9-p7)*bw_main1.win_edit_ychar)
			,(int)(2*bw_main1.win_edit_xchar)
			,(int)(bw_main1.win_edit_ychar)
			,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
			,bw_main1.win_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",""
			,WS_CHILD|WS_VISIBLE|BS_CHECKBOX
			,(int)((p6-p8)*bw_main1.win_xchar)
			,(int)((p9-p7)*bw_main1.win_ychar)
			,(int)(2*bw_main1.win_xchar)
			,(int)(bw_main1.win_ychar)
			,bw_main1.win_hwnd,(HMENU)win_h_ci_total_ptr
			,bw_main1.win_ins,NULL);
  }

  set_win_hnd(win_h_ci_total_ptr,hnd);
  if (get_win_hnd(win_h_ci_total_ptr)==NULL) bw_main1.win_cre_ok=0;

  set_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,0,p_pagecnt);
  set_win_h_ci_ptr(win_h_ci_total_ptr,1,p6);
  set_win_h_ci_ptr(win_h_ci_total_ptr,2,p9);
  set_win_h_ci_ptr(win_h_ci_total_ptr,3,win_h_ci_total_ptr);
  set_win_h_ci_ptr(win_h_ci_total_ptr,4,p_pagecnt-get_win_ptr_grp_ptr(get_win_ptr_grp_id(p_pagecnt),0)+get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),0));

  win_h_ci_total_ptr++;

  return(0);
}

int bw_win::w_cre_win_button(int p_pagecnt,int mark) // create button ci
{ 
  int  p1,p2,p4,p5,p6,p7,p8,p9,p10,p10a;
  int  state1;
  int  state7;
  int  i,j,k,l;
  int  ptr1,ptr3;
  int  t1,t2;
  char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];

  win_mark=mark;

  if (get_win_ptr_fld_in_win(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((get_win_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_win_ptr_fld_in_win(p_pagecnt,0,get_win_ptr_fld_in_win(i,1)+1);
    ptr1=get_win_ptr_fld_in_win(i,1);
  }
  else ptr1=get_win_ptr_fld_in_win(p_pagecnt,0)-1;

  win_h_ci_total_ptr=win_h_w_total_ptr;

  ptr3=win_h_ci_total_ptr;

  if (win_h_ci_total_ptr>=HND_NUM) return(0);

  p7=0;
  p8=0;   

  for (i=1;i<LIN_NUM;i++)
  {
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++)  
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue;
    if (p7==0) p7=i;
    if (p8==0) p8=p1;
    state1=0;
    state7=0;
    p4=0;
    p5=0;
    p6=0;

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='&')
      {
	ptr1++;
	p4=0;      
	p5=1;      
	state1=1;
        p6=j;      
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<=' ')
	{
          if (state7==1) continue;
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='@')
	      {
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buff1.get_t3_winfile(p_pagecnt,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buff1.get_t3_winfile(p_pagecnt,i,t2)==')') break;
		  }

                  str1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    str1[l-t1-1]=bw_buff1.get_t3_winfile(p_pagecnt,i,l);
		    str1[l-t1]=0;
                  }

		  w_cre_ci_button(p_pagecnt,str1,SMG_SIZE,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
	    if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='(')
	      &&(bw_buff1.get_t3_winfile(p_pagecnt,i,j-1)!='&'))
	    {
		get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

		if (str2[0]=='@')
		{
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buff1.get_t3_winfile(p_pagecnt,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buff1.get_t3_winfile(p_pagecnt,i,t2)==')') break;
		  }

		  str1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    str1[l-t1-1]=bw_buff1.get_t3_winfile(p_pagecnt,i,l);
		    str1[l-t1]=0;
		  }

		  w_cre_ci_button(p_pagecnt,str1,SMG_SIZE,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
		}

              state7=1;
	      state1=0;
              continue;
	    }
	  }
	  else
	  {
	    if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)==')')
	    {
	      state7=0;
	      continue;
            }
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='@')
	      {
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buff1.get_t3_winfile(p_pagecnt,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buff1.get_t3_winfile(p_pagecnt,i,t2)==')') break;
		  }

		  str1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    str1[l-t1-1]=bw_buff1.get_t3_winfile(p_pagecnt,i,l);
		    str1[l-t1]=0;
                  }

		  w_cre_ci_button(p_pagecnt,str1,SMG_SIZE,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
	      }
	      p5=0;
	    }
	  }
	}
      }
    }

    if (p5==1)
    {
      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

      if (str2[0]=='@')
      {
	for (t1=p6;t1<COL_NUM;t1++)
        {
          if (bw_buff1.get_t3_winfile(p_pagecnt,i,t1)=='(') break;
        }

        for (t2=p6;t2<COL_NUM;t2++)
        {
          if (bw_buff1.get_t3_winfile(p_pagecnt,i,t2)==')') break;
        }

        str1[0]=0;

        for (l=t1+1;l<t2;l++)
        {
          str1[l-t1-1]=bw_buff1.get_t3_winfile(p_pagecnt,i,l);
	  str1[l-t1]=0;
        }

        w_cre_ci_button(p_pagecnt,str1,SMG_SIZE,p6,p7,p8,i);

	if (win_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }
  }

  win_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=ptr3;i<=get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5);i++)
  {
    set_win_proc(i,(FARPROC)GetWindowLong(get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tproc);
  }

  //set_win_h_up_ptr(p_pagecnt,0,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),6));
  set_win_h_up_ptr(p_pagecnt,1,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5));

  win_h_w_total_ptr=win_h_ci_total_ptr;

  return(0);
}

int bw_win::w_cre_win_edit(int p_pagecnt,int mark) // create edit ci
{
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
  int  i,j;
  int  ptr1;
  int  hptr1;
  char str2[FLD_NAME_SIZE];

  win_mark=mark;

  if (get_win_ptr_fld_in_win(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((get_win_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_win_ptr_fld_in_win(p_pagecnt,0,get_win_ptr_fld_in_win(i,1)+1);
    ptr1=get_win_ptr_fld_in_win(i,1);
  }
  else ptr1=get_win_ptr_fld_in_win(p_pagecnt,0)-1;

  hptr1=win_h_ci_total_ptr;

  p7=0;  
  p8=0;

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++)  
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
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
      if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='&')
      {
	if (p5==1)
	{
	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if ((str2[0]!='+')&&(str2[0]!='-'))
	  {
	  }
	  else
	  {
	    if (bw_inkey1.strempty(str2)==1)
	    {
	      w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

	      if (win_h_ci_total_ptr>=HND_NUM) return(0);
	    }
	  }
	  p5=0;
	}

        ptr1++;
	p4=0;
	p5=1;      
        state1=1;  
	p6=j;    
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if ((str2[0]!='+')&&(str2[0]!='-'))
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2)==1)
		{
		  w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if ((str2[0]!='+')&&(str2[0]!='-'))
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2)==1)
		{
		  w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

      if ((str2[0]=='+')||(str2[0]=='-'))
      {
        w_cre_ci_edit(p_pagecnt,p6,p7,p8,i);

	if (win_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }

  }

  win_tproc=(FARPROC)MakeProcInstance((FARPROC)w_tab_ci_wp,bw_main1.win_ins);
  for (i=hptr1;i<=get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5);i++)
  {
    set_win_proc(i,(FARPROC)GetWindowLong(get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tproc);
  }

  set_win_h_up_ptr(p_pagecnt,1,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5));

  win_h_w_total_ptr=win_h_ci_total_ptr;

  return(0);
}

int bw_win::w_cre_win_radio(int p_pagecnt,int mark) // create radio ci
{
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
  int  i,j;
  int  ptr1;
  int  hptr1;
  char str2[FLD_NAME_SIZE];

  win_mark=mark;

  if (get_win_ptr_fld_in_win(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((get_win_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_win_ptr_fld_in_win(p_pagecnt,0,get_win_ptr_fld_in_win(i,1)+1);
    ptr1=get_win_ptr_fld_in_win(i,1);
  }
  else ptr1=get_win_ptr_fld_in_win(p_pagecnt,0)-1;

  hptr1=win_h_ci_total_ptr;

  p7=0;  
  p8=0;

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++)  
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
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
      if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='&')
      {
        ptr1++;
	p4=0;
	p5=1;      
        state1=1;  
	p6=j;    
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]!='(')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2)==1)
		{
		  w_cre_ci_radio(p_pagecnt,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]!='(')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2)==1)
		{
		  w_cre_ci_radio(p_pagecnt,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

      if (str2[0]=='(')
      {
        w_cre_ci_radio(p_pagecnt,p6,p7,p8,i);

	if (win_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }

  }

  win_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=hptr1;i<=get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5);i++)
  {
    set_win_proc(i,(FARPROC)GetWindowLong(get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tproc);
  }

  set_win_h_up_ptr(p_pagecnt,1,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5));

  win_h_w_total_ptr=win_h_ci_total_ptr;

  return(0);
}

int bw_win::w_cre_win_check(int p_pagecnt,int mark) // create choose ci
{ 
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
  int  i,j;
  int  ptr1;
  int  hptr1;
  char str2[FLD_NAME_SIZE];

  win_mark=mark;

  if (get_win_ptr_fld_in_win(p_pagecnt,0)==0)
  {
    i=p_pagecnt-1;
    while ((get_win_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_win_ptr_fld_in_win(p_pagecnt,0,get_win_ptr_fld_in_win(i,1)+1);
    ptr1=get_win_ptr_fld_in_win(i,1);
  }
  else ptr1=get_win_ptr_fld_in_win(p_pagecnt,0)-1;

  hptr1=win_h_ci_total_ptr;

  p7=0;  
  p8=0;

  for (i=1;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=1;j<COL_NUM;j++) 
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=1;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_pagecnt,i,j)>' ')||(bw_buff1.get_t3_winfile(p_pagecnt,i,j)<0))
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
      if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)=='&')
      {
        ptr1++;
	p4=0;      
	p5=1;     
        state1=1;  
	p6=j;
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_pagecnt,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]!='[')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2)==1)
		{
		  w_cre_ci_check(p_pagecnt,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]!='[')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2)==1)
		{
		  w_cre_ci_check(p_pagecnt,p6,p7,p8,i);

		  if (win_h_ci_total_ptr>=HND_NUM) return(0);
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
      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

      if (str2[0]=='[')
      {
        w_cre_ci_check(p_pagecnt,p6,p7,p8,i);

	if (win_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }

  }

  win_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.win_ins);
  for (i=hptr1;i<=get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5);i++)
  {
    set_win_proc(i,(FARPROC)GetWindowLong(get_win_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_win_hnd(i),GWL_WNDPROC,(LPARAM)win_tproc);
  }

  set_win_h_up_ptr(p_pagecnt,1,get_win_h_w_ptr(get_win_ptr_grp_id(p_pagecnt),5));

  win_h_w_total_ptr=win_h_ci_total_ptr;

  return(0);
}

int bw_win::w_find_hnd(int p1,int p2,int p3)
{
  int  i,j;

  j=0;

  for (i=0;i<=win_h_w_total_ptr-1;i++)
  {
    if ((get_win_h_ci_ptr(i,0)==p1)&&
	(get_win_h_ci_ptr(i,1)==p2)&&
	(get_win_h_ci_ptr(i,2)==p3))
    {
      j=get_win_h_ci_ptr(i,3);
      break;
    }
  }

  return(j);
}

int bw_win::w_find_winfname(int w,int l,int c,char *p_s1,int p_s1_size)
{
  int  i,j,k;
  char str2[FLD_NAME_SIZE];

  p_s1[0]=0;

  i=bw_buff1.get_t3_linecol(w,l,c);
  if (i>0)
  {
    get_t_fldname(i,str2,FLD_NAME_SIZE);

    if (FLD_NAME_SIZE>p_s1_size) k=p_s1_size;
    else k=FLD_NAME_SIZE;
    
    for (j=0;j<k-1;j++)
    {
      p_s1[j+0]=str2[j];
      p_s1[j+1]=0;
    }
  }

  return(0);
}

int bw_win::w_find_winflen(int w,int l,int c)
{
  int i;
  i=bw_buff1.get_t3_linecol(w,l,c);
  if (i>0) return(get_t_fldlen(i));
  else return(0);
}

int bw_win::w_set_winfedit(int w,int l,int c,int v)
{
  int i;
  i=bw_buff1.get_t3_linecol(w,l,c);
  if (i>0) set_t_fldedt(i,v);
  return(0);
}

int bw_win::w_field_info3(int w)
{
  int  i,j,k,m;
  char str2[FLD_NAME_SIZE];

  m=w;

  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	k=bw_buff1.get_t3_linecol(m,i,j);

	get_t_fldname(k,str2,FLD_NAME_SIZE);

	if (str2[0]=='*') set_t_fldedt(k,1);
	else
	{
	  if (strlen(str2)<=1) set_t_fldedt(k,1);
	  else
	  {
	    if (str2[0]=='%') set_t_fldedt(k,1);
	    else set_t_fldedt(k,0);
	  }
	}
      }
    }
  }

  return(0);
}

int bw_win::w_next_field(int p1)
{
  int  i,j,m;
  int  s_tmpn1,s_tmpn2;
  int  exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=p1;
  pfield++;

  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	if (get_t_fldedt(bw_buff1.get_t3_linecol(m,i,j))==0)
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

int bw_win::w_next_afield(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=p1;
  pfield++;

  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
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

int bw_win::w_right_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=p1;
  pfield++;

  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	if (get_t_fldedt(bw_buff1.get_t3_linecol(m,i,j))==0)
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

int bw_win::w_left_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  m=p1;
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
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	if (get_t_fldedt(bw_buff1.get_t3_linecol(m,i,j))==0)
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

int bw_win::w_up_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  pline--;
  if (pline<1) pline=1;
  m=p1;

  for (i=pline;i>=1;i--)
  {
    for (j=pfield;j>=1;j--)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	if (get_t_fldedt(bw_buff1.get_t3_linecol(m,i,j))==0)
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

int bw_win::w_down_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;

  exist=0;
  s_tmpn1=pline;
  s_tmpn2=pfield;
  pline++;
  m=p1;
  if (pline>=LIN_NUM) pline=1;

  for (i=pline;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=pfield;j>=1;j--)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	if (get_t_fldedt(bw_buff1.get_t3_linecol(m,i,j))==0)
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
/*
int bw_win::w_down_line(int p_ptr,int p1)                      
{
  int  i,j,m,n;
  int  exist;
  char str2[FLD_NAME_SIZE];

  exist=0;
  m=p1;

  for (i=1;i<LIN_NUM;i++) // find first screen field 
  {
    for (j=1;j<COL_NUM;j++)
    {
      n=bw_buff1.get_t3_linecol(m,i,j);

      get_t_fldname(n,str2,FLD_NAME_SIZE);
      
      if ((n!=0)&&(str2[0]!='#')&&(str2[0]!='%')&&(str2[0]!='@'))
      {
	if (get_t_fldseri(n)==p_ptr+1)
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
*/
/*
int bw_win::w_up_line(int p_ptr,int p1)
{
  int  i,j,m,n;
  int  exist;
  char str2[FLD_NAME_SIZE];

  exist=0;
  m=p1;

  for (i=1;i<LIN_NUM;i++) // find first screen field 
  {
    for (j=1;j<COL_NUM;j++)
    {
      n=bw_buff1.get_t3_linecol(m,i,j);

      get_t_fldname(n,str2,FLD_NAME_SIZE);
      
      if ((n!=0)&&(str2[0]!='#')&&(str2[0]!='%')&&(str2[0]!='@'))
      {
	if (get_t_fldseri(n)==p_ptr-1)
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
*/
int bw_win::w_field_type(char *p_str)
{
  if (p_str[0]=='&') return(0);  /* all field&var header */
  if (p_str[0]=='$') return(1);  /* sound */
  if (p_str[0]=='(') return(2);  /* (X)    ci */ // ci : control item
  if (p_str[0]=='[') return(3);  /* [X]    ci */ // ci : control item
  if (p_str[0]=='@') return(4);  /* button ci */ // ci : control item
  if (p_str[0]=='#') return(5);  /* bitmap */
  if (p_str[0]=='%') return(6);  /* read database var */
  if (p_str[0]==':') return(7);  /* edit database var */
  if (p_str[0]=='?') return(8);  /* memory var */
  if (p_str[0]=='+') return(9);  /* edit database ci */ // ci : control item
  if (p_str[0]=='-') return(10); /* edit var      ci */ // ci : control item
  return(0);
}

int bw_win::w_fetch_fld_style(char *tfn,int tfn_size,char *tn,int tn_size,long *tr,char *fn,int fn_size,int p_wptr)
{
  int  i,j,k,l;
  int  p1;
  int  s_ptr1[3][2];
  char s_fld[3][SMG_SIZE];

  i=strlen(tfn);
  j=0;
  l=0;
  for (k=0;k<=i;k++)  /* make tfn(table.field.recno.) position */
  {
    if (tfn[k]=='.')
    {
      s_ptr1[j][0]=l;
      s_ptr1[j][1]=k-1;
      if (k-1-l+1>=9) s_ptr1[j][1]=8+l;
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
	s_ptr1[j][0]=l;
	s_ptr1[j][1]=k-1;
	if (k-1-l+1>=9) s_ptr1[j][1]=8+l;
	break;
      }
    }
  }

  for (i=0;i<=j;i++)   /* make str */
  {
    for (k=s_ptr1[i][0];k<=s_ptr1[i][1];k++)
    {
      s_fld[i][k-s_ptr1[i][0]+0]=tfn[k];
      s_fld[i][k-s_ptr1[i][0]+1]=0;
    }
  }

  tn[0]=0;
  *tr=0;
  fn[0]=0;

  /* get: table|recno|field */
  if (j==0)  /* 1 jie */
  {
    i=w_find_base_name(s_fld[0],SMG_SIZE,p_wptr);
    k=w_find_recno_name(s_fld[0],SMG_SIZE);
    l=w_find_fld_name(s_fld[0],SMG_SIZE,p_wptr);
    if (i==1)
    {
      if ((int)strlen(s_fld[0])<tn_size)
      {
	strcpy(tn,s_fld[0]);
      }
      return(1);
    }
    if (k==1)
    {
      *tr=bw_inkey1.str2long(s_fld[0],SMG_SIZE);
      return(1);
    }
    if (l==1)
    {
      if ((int)strlen(s_fld[0])<fn_size)
      {
	strcpy(fn,s_fld[0]);
      }
      return(1);
    }
    return(0);
  }

  /* get: table|recno|field */
  if (j==1)  /* 2 jie */
  {
    i=w_find_base_name(s_fld[0],SMG_SIZE,p_wptr);
    k=w_find_recno_name(s_fld[0],SMG_SIZE);
    l=w_find_fld_name(s_fld[0],SMG_SIZE,p_wptr);
    if (i==1)
    {
      if ((int)strlen(s_fld[0])<tn_size)
      {
        strcpy(tn,s_fld[0]);
	p1=1;
      }
    }
    if (k==1)
    {
      *tr=bw_inkey1.str2long(s_fld[0],SMG_SIZE);
      p1=2;
    }
    if (l==1)
    {
      if ((int)strlen(s_fld[0])<fn_size)
      {
        strcpy(fn,s_fld[0]);
	p1=3;
      }
    }
    if ((i==0)&&(k==0)&&(l==0))
    {
      return(0);
    }

    i=w_find_base_name(s_fld[1],SMG_SIZE,p_wptr);
    k=w_find_recno_name(s_fld[1],SMG_SIZE);
    l=w_find_fld_name(s_fld[1],SMG_SIZE,p_wptr);
    if (i==1)
    {
      if (p1==1)
      {
	return(0);
      }
      if ((int)strlen(s_fld[1])<tn_size)
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
      *tr=bw_inkey1.str2long(s_fld[1],SMG_SIZE);
      p1=2;
    }
    if (l==1)
    {
      if (p1==3)
      {
	return(0);
      }
      if ((int)strlen(s_fld[1])<fn_size)
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

  /* get: table|recno|field */
  if (j==2)  /* 3 jie */
  {
    i=w_find_base_name(s_fld[0],SMG_SIZE,p_wptr);
    k=w_find_recno_name(s_fld[1],SMG_SIZE);
    l=w_find_fld_name(s_fld[2],SMG_SIZE,p_wptr);
    if (i==1)
    {
      if ((int)strlen(s_fld[0])<tn_size)
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
      *tr=bw_inkey1.str2long(s_fld[0],SMG_SIZE);
    }
    else
    {
      return(0);
    }
    if (l==1)
    {
      if ((int)strlen(s_fld[0])<fn_size)
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


int bw_win::w_find_base_name(char *p_str,int p_str_size,int p_wptr)
{
  int i,j;
  char stn[FN_SIZE];

  j=0;

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_tabname(1,i,stn,FN_SIZE);

    if ((get_win_ptr_wins_dbf(i,p_wptr)==1)&&(strcmp(stn,p_str)==0))
    {
      j=1;
      break;
    }
  }

  return(j);
}

int bw_win::w_find_fld_name(char *p_str,int p_str_size,int p_wptr)
{
  int  i,j,k;
  char s_fn1[SMG_SIZE];

  k=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_win_ptr_wins_dbf(i,p_wptr)==1)
    {
      for (j=bw_fldstru1.w_find_fldpoin0(i);j<bw_fldstru1.w_find_fldpoin1(i);j++)
      {
        bw_fldstru1.w_find_fldname(i,j,s_fn1,SMG_SIZE);
        if (strcmp(s_fn1,p_str)==0)
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

int bw_win::w_find_recno_name(char *p_str,int p_str_size)
{
  int  i,j,k;

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

int bw_win::w_fld_set_base(char *p_fldtable,int p_fldtable_size,int ptr1,int p_wptr)
{
  int  i,j,k;
  char stn[FN_SIZE];

  if (bw_inkey1.strempty(p_fldtable)==0) return(ptr1);

  k=0;

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_tabname(1,i,stn,FN_SIZE);

    if ((get_win_ptr_wins_dbf(i,p_wptr)==1)&&(strcmp(p_fldtable,stn)==0))
    {
      k=1;
      break;
    }
  }

  if (k==1) return(i);
  else return(ptr1);
}

int bw_win::w_fld_set_recno(long p_fldrecno,int ptr2)
{
  if (p_fldrecno!=0) return(0);
  else return(ptr2);
}

int bw_win::w_fld_set_fld(char *p_fldname,int p_fldname_size)
{
  if (bw_inkey1.strempty(p_fldname)==0) return(1);
  else return(0);
}

int bw_win::w_field_info2(int p_wptr)
{
  int  i,j,k,l,m,n;
  int  exist;
  int  ptr1;
  char s_fldtable[SMG_SIZE];
  char s_fldname[SMG_SIZE];
  long s_fldrecno;
  char s_tmps2[SMG_SIZE];
  char s_tmps3[SMG_SIZE];
  int  s_tmpn1;
  char str1[FLD_NAME_SIZE];
  char str2[FLD_NAME_SIZE];
  char str3[SMG_SIZE];
  char str4[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_win_ptr_wins_dbf(i,p_wptr)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  ptr1=i;

  for (i=get_win_ptr_fld_in_win(p_wptr,0);i<=get_win_ptr_fld_in_win(p_wptr,1);i++)
  {
    set_t_fldbase(i,0);
    set_t_fldedt(i,0);
    set_t_fldseri(i,0);
  }
		      
  for (i=get_win_ptr_fld_in_win(p_wptr,0);i<=get_win_ptr_fld_in_win(p_wptr,1);i++)
  {
    set_t_fldseri_tmp(i,0);
  }
	
  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      m=p_wptr;
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
	s_fldtable[0]=0;  
	s_fldrecno=0;
	s_fldname[0]=0;

        n=bw_buff1.get_t3_linecol(m,i,j);

	get_t_fldname(n,str2,FLD_NAME_SIZE);
      
	if ((str2[0]==':')||(str2[0]=='%')||(str2[0]=='+')||(str2[0]=='-'))
	{
	  strcpy(s_tmps2,str2);
	  if ((s_tmps2[0]=='%')||(s_tmps2[0]=='-'))
	  {
	    str3[0]=s_tmps2[0];
            str3[1]=0;
	    s_tmpn1=1; /* read field */
            bw_inkey1.cut_string(s_tmps2,1,strlen(s_tmps2)-1,SMG_SIZE,s_tmps3,SMG_SIZE);
          }
	  else
	  {
	    str3[0]=s_tmps2[0];
            str3[1]=0;
	    s_tmpn1=0; /* edit field */
	    bw_inkey1.cut_string(s_tmps2,1,strlen(s_tmps2)-1,SMG_SIZE,s_tmps3,SMG_SIZE);
	  }

	  w_fetch_fld_style(s_tmps3,SMG_SIZE
			   ,s_fldtable,SMG_SIZE
			   ,&s_fldrecno
			   ,s_fldname,SMG_SIZE,p_wptr);

	  if ((bw_inkey1.strempty(s_fldname)==0)&&(bw_inkey1.strempty(s_fldtable)==0))
	  {
            strcpy(str4,str3);
	    strcat(str4,s_tmps3);
	    set_t_fldname(n,str4,strlen(str4)+1);
	  }
	  else
	  {
	    strcpy(str4,str3);
            strcat(str4,s_fldname);
	    set_t_fldname(n,str4,strlen(str4)+1);
          }
	  ptr1=w_fld_set_base(s_fldtable,SMG_SIZE,ptr1,p_wptr);
	  set_t_fldbase(n,ptr1);

	  if (bw_inkey1.strempty(s_fldname)==0)
	  {
	    continue;
          }

	  l=0;
	  for (k=bw_buff1.get_t3_linecol(m,i,j)-1;k>=get_win_ptr_fld_in_win(p_wptr,0);k--)
	  {
	    get_t_field_tmp(k,str1,FLD_NAME_SIZE);
	    if ((strcmp(s_fldname,str1)==0)
	      &&(ptr1==get_t_fldbase(k))
	      &&(s_fldrecno==0))
	    {
	      l=1;
	      set_t_fldseri_tmp(k,get_t_fldseri_tmp(k)+1);
	      set_t_fldseri(n,get_t_fldseri_tmp(k));
	    }
	  }
	  if (l==1) set_c_t_field_tmp(bw_buff1.get_t3_linecol(m,i,j),0,0);
	  else 
	  {
	    set_t_field_tmp(bw_buff1.get_t3_linecol(m,i,j),s_fldname,strlen(s_fldname)+1);
	    set_t_fldseri_tmp(n,get_t_fldseri_tmp(n)+1);
	    set_t_fldseri(n,get_t_fldseri_tmp(n));
	  }

	  if (s_tmpn1==1)
	    set_t_fldedt(n,1);
	  else
	    set_t_fldedt(n,w_fld_set_fld(s_fldname,SMG_SIZE));

	}
	else set_t_fldbase(n,ptr1);
      }
    }
  }

  return(1);
}

int bw_win::w_adjust_edit(int p_wptr)
{
  HWND hnd;
  int  i,j,k,l,n,o,p,q,r;
  char str1[FLD_NAME_SIZE];
  char str2[FLD_NAME_SIZE];

  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(p_wptr,i,j)>0)
      {
        n=bw_buff1.get_t3_linecol(p_wptr,i,j);

	get_t_fldname(n,str2,FLD_NAME_SIZE);

	if (str2[0]=='+')
        {
	  k=get_t_fldlen(n);
          l=get_t_fldbase(n);

	  bw_inkey1.cut_string(str2,1,strlen(str2)-1,FLD_NAME_SIZE,str1,FLD_NAME_SIZE);

	  o=bw_fldstru1.w_find_fldlen(str1,FLD_NAME_SIZE,l);

	  if (o>k) p=k;
	  else p=o;

	  if (p<3) p=3;

	  q=w_find_hnd(p_wptr,j,i);

	  hnd=get_win_hnd(q);

	  if (get_win_ci_mode(p_wptr)==0)
          {
	    MoveWindow(hnd
			,(int)((j-get_win_con(p_wptr,0))*bw_main1.win_edit_xchar-3)
			,(int)((i-get_win_con(p_wptr,1))*bw_main1.win_edit_ychar-6)
			,(int)(p*bw_main1.win_edit_xchar+6)
			,(int)(bw_main1.win_edit_ychar+12)
			,FALSE);
	  }
          else
	  {
	    MoveWindow(hnd
			,(int)((j-get_win_con(p_wptr,0))*bw_main1.win_xchar-3)
			,(int)((i-get_win_con(p_wptr,1))*bw_main1.win_ychar-6)
			,(int)(p*bw_main1.win_xchar+6)
			,(int)(bw_main1.win_ychar+12)
			,FALSE);
	  }

	  SendMessage(hnd,EM_LIMITTEXT,o,(LPARAM)0);
	}

	if (str2[0]=='-')
        {
	  k=get_t_fldlen(n);

	  r=bw_dialog1.w_mv_seri(str2,FLD_NAME_SIZE,p_wptr);

	  o=bw_dialog1.get_win_mv_type(r,2);

	  if (o>k) p=k;
	  else p=o;

	  if (p<3) p=3;

	  q=w_find_hnd(p_wptr,j,i);

	  hnd=get_win_hnd(q);

	  if (get_win_ci_mode(p_wptr)==0)
          {
	    MoveWindow(hnd
			,(int)((j-get_win_con(p_wptr,0))*bw_main1.win_edit_xchar-3)
			,(int)((i-get_win_con(p_wptr,1))*bw_main1.win_edit_ychar-6)
			,(int)(p*bw_main1.win_edit_xchar+6)
			,(int)(bw_main1.win_edit_ychar+12)
			,FALSE);
	  }
          else
	  {
	    MoveWindow(hnd
			,(int)((j-get_win_con(p_wptr,0))*bw_main1.win_xchar-3)
			,(int)((i-get_win_con(p_wptr,1))*bw_main1.win_ychar-6)
			,(int)(p*bw_main1.win_xchar+6)
			,(int)(bw_main1.win_ychar+12)
			,FALSE);
	  }

	  SendMessage(hnd,EM_LIMITTEXT,o,(LPARAM)0);
	}
      }
    }
  }

  return(0);
}

int bw_win::w_cnt_winline(int p_dbptr,int p_wptr,int ln)
{
  int i,j,k,l;

  k=0;

  for (i=1;i<ln;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      l=bw_buff1.get_t3_linecol(p_wptr,i,j);
      if ((l!=0)&&(get_t_fldbase(l)==p_dbptr))
      {
	if (k<get_t_fldseri(l)) k=get_t_fldseri(l);
      }
    }
  }

  return(k);
}

int bw_win::tst_hptr3()
{
  //HDC  hdc;
  char str[SMG_SIZE];
  int  i;

  bw_getread1.deb_record("bw_win::tst_hptr3()");

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str,"ptr=%d,hptr30123456=%d,%d,%d,%d,%d,%d,%d,"
			      ,i,get_win_h_w_ptr(i,0)
			      ,get_win_h_w_ptr(i,1)
			      ,get_win_h_w_ptr(i,2)
			      ,get_win_h_w_ptr(i,3)
			      ,get_win_h_w_ptr(i,4)
			      ,get_win_h_w_ptr(i,5)
			      ,get_win_h_w_ptr(i,6)
			      );

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_win::tst_hptr4()
{
  //HDC  hdc;
  char str[SMG_SIZE];
  int  i;

  bw_getread1.deb_record("bw_win::tst_hptr4()");

  for (i=0;i<60;i++)
  {
    sprintf(str,"ptr=%d,hptr401234=%d,%d,%d,%d,%d,"
			      ,i,get_win_h_ci_ptr(i,0)
			      ,get_win_h_ci_ptr(i,1)
			      ,get_win_h_ci_ptr(i,2)
			      ,get_win_h_ci_ptr(i,3)
			      ,get_win_h_ci_ptr(i,4));

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_win::w_atten1(char *p_fn1)
{
  char str2[256];
  char str1[256];

  strcpy(str2,"打开资料错误,资料名:");
  strcat(str2,p_fn1);

  strcpy(str1,"Error when open file,file name:");
  strcat(str1,p_fn1);

  if (bw_main1.win_lang==1) MessageBox(bw_main1.win_hwnd,str1,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(bw_main1.win_hwnd,str2,"错误信息",MB_OK|MB_ICONASTERISK);
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
  char str1[81];
  char str2[256];
  char str3[256];

  sprintf(str1,"%d!",l);
  strcpy(str2,"工作区没有数据库打开!,工作区号：");
  strcat(str2,str1);

  strcpy(str3,"There is not base opened in this buffer,buffer number:");
  strcat(str3,str1);


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





long bw_win::get_win_timer(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_timer[p_wptr]);
}
int bw_win::set_win_timer(int p_wptr,long val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_timer[p_wptr]=val;
  return(0);
}

int bw_win::get_t_fldname(int p1,char *p_val,int p_val_size)
{
  int i,j;

  p_val[0]=0;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);

  if (p_val_size>FLD_NAME_SIZE) j=FLD_NAME_SIZE;
  else j=p_val_size;

  for (i=0;i<j-1;i++)
  {
    p_val[i+0]=t_fldname[p1][i];
    p_val[i+1]=0;
  }

  return(0);
}

int bw_win::set_t_fldname(int p1,char *p_val,int p_val_size)
{
  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);

  if (p_val_size>FLD_NAME_SIZE) j=FLD_NAME_SIZE;
  else j=p_val_size;

  t_fldname[p1][0]=0;

  for (i=0;i<j-1;i++)
  {
    t_fldname[p1][i+0]=p_val[i];
    t_fldname[p1][i+1]=0;
  }

  return(0);
}
int bw_win::set_c_t_fldname(int p1,int p2,char c1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  if ((p2<0)||(p2>=FLD_NAME_SIZE)) return(0);
  t_fldname[p1][p2]=c1;
  return(0);
}
int bw_win::get_t_fldtype(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldtype[p1]);
}
int bw_win::set_t_fldtype(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldtype[p1]=val;
  return(0);
}
int bw_win::get_t_fldbase(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldbase[p1]);
}
int bw_win::set_t_fldbase(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldbase[p1]=val;
  return(0);
}
int bw_win::get_t_fldseri(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldseri[p1]);
}
int bw_win::set_t_fldseri(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldseri[p1]=val;
  return(0);
}
int bw_win::get_t_fldlen(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldlen[p1]);
}
int bw_win::set_t_fldlen(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldlen[p1]=val;
  return(0);
}
int bw_win::get_t_flddec(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_flddec[p1]);
}
int bw_win::set_t_flddec(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_flddec[p1]=val;
  return(0);
}
int bw_win::get_t_fldedt(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldedt[p1]);
}
int bw_win::set_t_fldedt(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldedt[p1]=val;
  return(0);
}
int bw_win::get_t_fldseri_tmp(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldseri_tmp[p1]);
}
int bw_win::set_t_fldseri_tmp(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldseri_tmp[p1]=val;
  return(0);
}
int bw_win::get_t_field_tmp(int p1,char *p_val,int p_val_size)
{
  int i,j;

  p_val[0]=0;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);

  if (p_val_size>10) j=10;
  else j=p_val_size;

  for (i=0;i<j-1;i++)
  {
    p_val[i+0]=t_field_tmp[p1][i];
    p_val[i+1]=0;
  }

  return(0);
}
int bw_win::set_t_field_tmp(int p1,char *p_val,int p_val_size)
{
  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);

  if (p_val_size>10) j=10;
  else j=p_val_size;

  t_field_tmp[p1][0]=0;

  for (i=0;i<j-1;i++)
  {
    t_field_tmp[p1][i+0]=p_val[i];
    t_field_tmp[p1][i+1]=0;
  }

  return(0);
}
int bw_win::set_c_t_field_tmp(int p1,int p2,char c1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  if ((p2<0)||(p2>=10)) return(0);
  t_field_tmp[p1][p2]=c1;
  return(0);
}
/*
int bw_win::get_base_tmp(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_base_tmp[p1]);
}
int bw_win::set_base_tmp(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_base_tmp[p1]=val;
  return(0);
}
*/
/*
int bw_win::get_recno_tmp(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_recno_tmp[p1]);
}
int bw_win::set_recno_tmp(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_recno_tmp[p1]=val;
  return(0);
}
*/
/*
int bw_win::get_win_subhndid(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>9)) return(0);
  return(win_subhndid[p_wptr][ptr]);
}
int bw_win::set_win_subhndid(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>9)) return(0);
  win_subhndid[p_wptr][ptr]=val;
  return(0);
}
int bw_win::get_win_subhndptr(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_subhndptr[p_wptr]);
}
int bw_win::set_win_subhndptr(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_subhndptr[p_wptr]=val;
  return(0);
}
*/
int bw_win::get_win_state_link_modi(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_state_link_modi[p_wptr]);
}
int bw_win::set_win_state_link_modi(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_state_link_modi[p_wptr]=val;
  return(0);
}
int bw_win::get_win_state_calc_modi(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_state_calc_modi[p_wptr]);
}
int bw_win::set_win_state_calc_modi(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_state_calc_modi[p_wptr]=val;
  return(0);
}
int bw_win::get_win_switch_bmp(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_switch_bmp[p_wptr]);
}
int bw_win::set_win_switch_bmp(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_switch_bmp[p_wptr]=val;
  return(0);
}

int bw_win::get_win_ptr_fld_in_win(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>3)) return(0);
  return(win_ptr_fld_in_win[p_wptr][ptr]);
}
int bw_win::set_win_ptr_fld_in_win(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>3)) return(0);
  win_ptr_fld_in_win[p_wptr][ptr]=val;
  return(0);
}
int bw_win::get_win_h_w_ptr(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>8)) return(0);
  return(win_h_w_ptr[p_wptr][ptr]);
}
int bw_win::set_win_h_w_ptr(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>8)) return(0);
  win_h_w_ptr[p_wptr][ptr]=val;
  return(0);
}
int bw_win::get_win_h_up_ptr(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>1)) return(0);
  return(win_h_up_ptr[p_wptr][ptr]);
}
int bw_win::set_win_h_up_ptr(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>1)) return(0);
  win_h_up_ptr[p_wptr][ptr]=val;
  return(0);
}

HWND bw_win::get_win_phh(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_phh[p_wptr]);
}

int bw_win::set_win_phh(int p_wptr,HWND hwnd)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_phh[p_wptr]=hwnd;
  return(0);
}

int bw_win::get_win_tabname(int p1,int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p1<0)||(p1>1)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_tabname[p1][p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_win::set_win_tabname(int p1,int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p1<0)||(p1>1)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_tabname[p1][p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_tabname[p1][p_dbptr][j+0]=p_s1[j];
    win_tabname[p1][p_dbptr][j+1]=0;
  }

  return(0);
}
int bw_win::get_win_ptr_win_mark(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_ptr_win_mark[p_wptr]);
}
int bw_win::set_win_ptr_win_mark(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_ptr_win_mark[p_wptr]=val;
  return(0);
}
int bw_win::get_win_ptr_grp_id(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_ptr_grp_id[p_wptr]);
}
int bw_win::set_win_ptr_grp_id(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_ptr_grp_id[p_wptr]=val;
  return(0);
}


int bw_win::get_win_msgboxlock(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_msgboxlock[p_wptr]);
}
int bw_win::set_win_msgboxlock(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_msgboxlock[p_wptr]=val;
  return(0);
}


int bw_win::get_win_ptr_grp_ptr(int p_wptr,int p04)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p04<0)||(p04>=5)) return(0);
  return(win_ptr_grp_ptr[p_wptr][p04]);
}
int bw_win::set_win_ptr_grp_ptr(int p_wptr,int p04,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p04<0)||(p04>=5)) return(0);
  win_ptr_grp_ptr[p_wptr][p04]=val;
  return(0);
}
int bw_win::get_win_ptr_wins_dbf(int p_dbptr,int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(win_ptr_wins_dbf[p_dbptr][p_wptr]);
}
int bw_win::set_win_ptr_wins_dbf(int p_dbptr,int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  win_ptr_wins_dbf[p_dbptr][p_wptr]=val;
  return(0);
}
int bw_win::get_win_con(int p_wptr,int p03)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_con[p_wptr][p03]);
}
int bw_win::set_win_con(int p_wptr,int p03,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_con[p_wptr][p03]=val;
  return(0);
}
int bw_win::get_win_style(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>=WIN_STYLE_NUM)) return(0);
  return(win_style[p_wptr][ptr]);
}
int bw_win::set_win_style(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>=WIN_STYLE_NUM)) return(0);
  win_style[p_wptr][ptr]=val;
  return(0);
}
FARPROC bw_win::get_win_proc(int ptr)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  return(win_proc[ptr]);
}  
int bw_win::set_win_proc(int ptr,FARPROC fproc)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  win_proc[ptr]=fproc;
  return(0);
}
HWND bw_win::get_win_hnd(int ptr)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  return(win_hnd[ptr]);
}
int bw_win::set_win_hnd(int ptr,HWND hnd)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  win_hnd[ptr]=hnd;
  return(0);
}
int bw_win::get_win_h_ci_ptr(int hptr,int p04)
{
  if ((hptr<0)||(hptr>=HND_NUM)) return(0);
  if ((p04<0)||(p04>4)) return(0);
  return(win_h_ci_ptr[hptr][p04]);
}
int bw_win::set_win_h_ci_ptr(int hptr,int p04,int val)
{
  if ((hptr<0)||(hptr>=HND_NUM)) return(0);
  if ((p04<0)||(p04>4)) return(0);
  win_h_ci_ptr[hptr][p04]=val;
  return(0);
}
int bw_win::get_win_ptr_get_rd(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_ptr_get_rd[p_wptr]);
}
int bw_win::set_win_ptr_get_rd(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_ptr_get_rd[p_wptr]=val;
  return(0);
}
int bw_win::get_win_create_menu(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_create_menu[p_wptr]);
}
int bw_win::set_win_create_menu(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_create_menu[p_wptr]=val;
  return(0);
}
int bw_win::get_win_linep(int p_wptr,int p01)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_linep[p_wptr][p01]);
}
int bw_win::set_win_linep(int p_wptr,int p01,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_linep[p_wptr][p01]=val;
  return(0);
}
int bw_win::get_win_window_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_window_name[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_win::set_win_window_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_window_name[p_wptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_window_name[p_wptr][j+0]=p_s1[j];
    win_window_name[p_wptr][j+1]=0;
  }

  return(0);
}
int bw_win::get_win_find_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_find_name[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_win::set_win_find_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_find_name[p_wptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_find_name[p_wptr][j+0]=p_s1[j];
    win_find_name[p_wptr][j+1]=0;
  }

  return(0);
}
int bw_win::get_win_is_link(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_is_link[p_wptr]);
}
int bw_win::set_win_is_link(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_is_link[p_wptr]=val;
  return(0);
}
int bw_win::get_win_is_calc(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_is_calc[p_wptr]);
}
int bw_win::set_win_is_calc(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_is_calc[p_wptr]=val;
  return(0);
}
int bw_win::get_win_memo_basep(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_memo_basep[p_wptr]);
}
int bw_win::set_win_memo_basep(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_memo_basep[p_wptr]=val;
  return(0);
}





int bw_win::get_win_ci_mode(int p_wptr)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  return(win_ci_mode[p_wptr]);
}
int bw_win::set_win_ci_mode(int p_wptr,int val)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  win_ci_mode[p_wptr]=val;
  return(0);
}

int bw_win::get_win_ci_posi(int p_wptr,int p01)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1))       return(0);
  return(win_ci_posi[p_wptr][p01]);
}
int bw_win::set_win_ci_posi(int p_wptr,int p01,int val)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1))       return(0);
  win_ci_posi[p_wptr][p01]=val;
  return(0);
}

