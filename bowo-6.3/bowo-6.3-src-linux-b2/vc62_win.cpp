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

#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_buff         bw_buff1;
extern class bw_edit         bw_edit1;
extern class bw_link         bw_link1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_getread      bw_getread1;
extern class bw_dialog       bw_dialog1;
extern class bw_rabox        bw_rabox1;
extern class bw_chkbox       bw_chkbox1;
extern class bw_buttonvar    bw_buttonvar1;
extern class bw_inkey        bw_inkey1;
extern class bw_win          bw_win1;
extern class bw_fldstru      bw_fldstru1;

extern long  /* pascal */  w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long  /* pascal */  w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);

/* should into class */

HWND bw_win::get_ci_mhnd(HWND hwnd)
{
  int i,j;

  for (i=0;i<HND_NUM;i++)
  {
    if (mn_hnd[i]==hwnd)
    {
      j=get_mn_h_ci_ptr(i,4);  //parent hwnd ptr
      return(mn_hnd[j]);
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
    if (get_mn_ptr_grp_id(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1) return(i);
  
  return(-1);
}

int bw_win::w_ini_win(void)
{
  int i;

  mn_ptr_new_win=1; /* can not be zero (0) */

  for (i=0;i<WIN_NUM;i++)
  {
    set_mn_ptr_fld_in_win(i,0,0);
    set_mn_ptr_fld_in_win(i,1,0);
    set_mn_ptr_fld_in_win(i,2,0);
    set_mn_ptr_fld_in_win(i,3,0);

    set_mn_ptr_grp_id(i,0);

    set_mn_msgboxlock(i,0);
  }

  //windows focus manage
  mn_focus_ptr1=0;
  mn_focus_ptr2=0;

  return(0);
}

/* notice */
int bw_win::w_login_win(int p1,char *p_win_name,int p_win_name_size,char *p_find_name,int p_find_name_size)
{
  int i,j,k;
  int exist;

  exist=0;

  for (i=1;i<WIN_NUM;i++)
  {
    if (get_mn_ptr_grp_id(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0)
  {
    w_atten3(bw_main1.mn_hwnd1);
    return(1);
  }

  //j=p1;

  set_mn_ptr_grp_id( p1,i);
  set_ms_window_name(p1,p_win_name ,p_win_name_size );
  set_ms_find_name(  p1,p_find_name,p_find_name_size);

  for (k=0;k<STRU_NUM;k++)
  {
    bw_xbase1.set_mn_cur_seri(k,p1,0);
    bw_xbase1.set_mn_recno(k,p1,0,0);
    bw_xbase1.set_mn_recno(k,p1,1,0);
    bw_xbase1.set_mn_recno(k,p1,2,0);
    bw_xbase1.set_mn_state_in_srch(p1,k,0);
  }

  return(0);
}

int bw_win::w_dele_win_ptr(int p_wptr)
{
  int i,j,k;

  //i=p_wptr;

  set_mn_ptr_grp_id(p_wptr,0);

  for (k=0;k<STRU_NUM;k++)
  {
    set_mn_ptr_wins_dbf(k,p_wptr,0);
  }

  return(0);
}

int bw_win::w_dele_win_ptr_wins_dbf(int p_wptr)
{
  int i,j;

  //j=p_wptr;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_mn_ptr_wins_dbf(i,p_wptr)==1)
    {
      set_ms_tabname(0,i,"",0);
      set_ms_tabname(1,i,"",0);
    }

    set_mn_ptr_wins_dbf(i,p_wptr,0);
  }

  return(0);
}

int bw_win::w_login_wwin(int p_wptr)
{
  set_mn_h_w_ptr(p_wptr,0,mn_h_ci_total_ptr);
  set_mn_h_w_ptr(p_wptr,5,0);

  mn_h_ci_total_ptr++;

  return(0);
}

int bw_win::w_find_winhand(HWND hwnd)
{
  int i;
  int exist;

  exist=0;

  for (i=1;i<mn_ptr_new_win;i++)
  {
    if (hwnd==get_mn_phh(i))
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);

  return(i);
}

int bw_win::w_mouse_infield(int p_wptr,int y,int x)
{
  int  exist;
  int  i,j;
  char str1[SMG_SIZE];

  exist=0;

  for (i=0;i<COL_NUM;i++)
  {
    j=bw_buff1.get_t3_linecol(p_wptr,y,i);

    if ((j>0)&&(get_t_fldedt(j)==0))
    {
      if (  (i<=x)  &&  (x<i+get_t_fldlen(j))  )
      {
	get_t_fldname(j,str1,SMG_SIZE);

	if ((str1[0]=='?')||(str1[0]==':'))
        {
	  exist=1;
	  mn_mouse_y=y;
	  mn_mouse_x=i;
	  bw_main1.mn_field_posi=x-i;
	  break;
	}
      }
    }
  }

  return(exist);
}

int bw_win::tst_win1()
{
  int  i,j,k,l,m;
  char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];

  bw_getread1.deb_record("bw_win::tst_win1()");

  for (i=1;i<60;i++)
  {
    get_t_fldname(i,str2,FLD_NAME_SIZE);

    sprintf(str1,"ptr=%d,fldname=%s,type=%c,base=%d,seri=%d,len=%d,dec=%d,edit=%d,"
                                      ,i
                                      ,str2
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
    for (i=0;i<LIN_NUM;i++)
    {
      for (j=0;j<COL_NUM;j++)
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

int bw_win::tst_win1_fld()
{
  int  i,j,k,l,m;
  char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];

  bw_getread1.deb_record("bw_win::tst_win1_fld()");

  for (i=1;i<240;i++)
  {
    get_t_fldname(i,str2,FLD_NAME_SIZE);

    sprintf(str1,"ptr=%d,fldname=%s,type=%d,base=%d,seri=%d,len=%d,dec=%d,edit=%d,"
                                      ,i
                                      ,str2
				       ,get_t_fldtype(i)
				       ,get_t_fldbase(i)
				       ,get_t_fldseri(i)
				       ,get_t_fldlen(i)
				       ,get_t_flddec(i)
				       ,get_t_fldedt(i)
					   );

    bw_getread1.deb_record(str1);
  }

  k=0;

  for (l=1;l<WIN_NUM;l++)
  {
    for (i=0;i<LIN_NUM;i++)
    {
      for (j=0;j<COL_NUM;j++)
      {
	if (bw_buff1.get_t3_linecol(l,i,j)!=0)
	{
	  m=bw_buff1.get_t3_linecol(l,i,j);
	  get_t_fldname(m,str2,FLD_NAME_SIZE);

	  sprintf(str1,"win=%d,line=%d,col=%d,linecol_fldid=%d,seri=%d,base=%d,name=%s,",l,i,j,m,get_t_fldseri(m),get_t_fldbase(m),str2);
          bw_getread1.deb_record(str1);
	  k++;
	  //if (k>=60) break;
        }
      }
      //if (k>=60) break;
    }
    //if (k>=60) break;
  }

  return(0);
}

int bw_win::tst_win2()
{
  int  i;
  char str1[SMG_SIZE];
  char str_tab1[FN_SIZE];
  char str_tab2[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win2()");

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str1,"mn_ptr=%d,20=%d,21=%d,4=%d,5=%d,60=%d,61=%d,62=%d,90=%d,91=%d,92=%d,93=%d,ptr1=%d,subwub=%d,"
                                      ,i
                                      ,get_mn_ptr_fld_in_win(i,0)
				       ,get_mn_ptr_fld_in_win(i,1)
				       ,0//get_mn_ptr_mn_mark(i)   
				       ,get_mn_ptr_grp_id(i)
				       ,0//get_mn_ptr_grp_ptr(i,0)
				       ,0//get_mn_ptr_grp_ptr(i,1)
				       ,0//get_mn_ptr_grp_ptr(i,2)
				       ,get_mn_ptr_wins_dbf(0,i)
				       ,get_mn_ptr_wins_dbf(1,i)
				       ,get_mn_ptr_wins_dbf(2,i)
				       ,get_mn_ptr_wins_dbf(3,i)
				       ,mn_ptr_new_win
				       ,0/*get_mn_subhndptr(i)*/);

    bw_getread1.deb_record(str1);
  }

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_tabname(0,i,str_tab1,FN_SIZE);
    get_ms_tabname(1,i,str_tab2,FN_SIZE);

    sprintf(str1,"ptr=%d,tabn=%s,stru=%s,",i,str_tab1,str_tab2);
    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win2_fld_in_win()
{
  int  i;
  char str1[SMG_SIZE];
  char str_tab1[FN_SIZE];
  char str_tab2[FN_SIZE];
  char str_tab3[FN_SIZE];
  char str_tab4[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win2_fld_in_win()");

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str1,"mn_ptr=%d,fldinwin0=%d,fldinwin1=%d,mark=%d,id=%d,0=%d,0=%d,0=%d,windbf0=%d,windbf1=%d,windbf2=%d,windbf3=%d,ptr_new_win=%d,0=%d,h_w_p0=%d,h_w_p5=%d,ci_total_ptr=%d,"
                                      ,i
                                      ,get_mn_ptr_fld_in_win(i,0)
				       ,get_mn_ptr_fld_in_win(i,1)
				       ,0//get_mn_ptr_mn_mark(i)   
				       ,get_mn_ptr_grp_id(i)
				       ,0//get_mn_ptr_grp_ptr(i,0)
				       ,0//get_mn_ptr_grp_ptr(i,1)
				       ,0//get_mn_ptr_grp_ptr(i,2)
				       ,get_mn_ptr_wins_dbf(0,i)
				       ,get_mn_ptr_wins_dbf(1,i)
				       ,get_mn_ptr_wins_dbf(2,i)
				       ,get_mn_ptr_wins_dbf(3,i)
				       ,mn_ptr_new_win
				       ,0/*get_mn_subhndptr(i)*/
                       	       ,get_mn_h_w_ptr(i,0)
				       ,get_mn_h_w_ptr(i,5)
				       ,mn_h_ci_total_ptr
				   );

    bw_getread1.deb_record(str1);
  }

  bw_getread1.deb_record("bw_win::tst_win2...()  window name...");

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_tabname(    0,i,str_tab1,FN_SIZE);
    get_ms_tabname(    1,i,str_tab2,FN_SIZE);
    get_ms_window_name(  i,str_tab3,FN_SIZE);
    get_ms_find_name(    i,str_tab4,FN_SIZE);

    sprintf(str1,"stru_ptr=%d,winname=%s,findname=%s,stru_name=%s,base_name=%s,"
                                       ,i
                                       ,str_tab3
				       ,str_tab4
				       ,str_tab1
				       ,str_tab2);

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win3()
{
  int  i;
  char str1[SMG_SIZE];
  char str_tab1[FN_SIZE];
  char str_tab2[FN_SIZE];
  char str_tab3[FN_SIZE];
  char str_tab4[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win3()");

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_tabname(0,i,str_tab1,FN_SIZE);
    get_ms_tabname(1,i,str_tab2,FN_SIZE);
    get_ms_window_name(i,str_tab3,FN_SIZE);
    get_ms_find_name(i,str_tab4,FN_SIZE);

    sprintf(str1,"ptr=%d,winname=%s,findname=%s,stru=%s,base=%s,"
                                       ,i,str_tab3
				       ,str_tab4
				       ,str_tab1
				       ,str_tab2);

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win4()
{
  int  i,j;
  char str1[SMG_SIZE];

  bw_getread1.deb_record("bw_win::tst_win4()");

  for (i=0;i<24;i++)
  {
    for (j=0;j<80;j++)
    {
      str1[j+0]=bw_buff1.get_t3_winfile(1,i,j);
      str1[j+1]=0;
    }

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win5()
{
  int  i;
  char str1[SMG_SIZE];
  char str_tab1[FN_SIZE];
  char str_tab2[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win5()");

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_tabname(0,i,str_tab1,FN_SIZE);
    get_ms_tabname(1,i,str_tab2,FN_SIZE);

    sprintf(str1,"ptr=%d,base=%s,stru=%s,",i,str_tab1,str_tab2);

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win6_ci_ptr()
{
  int  i,j,k,l,m,n;
  char str1[SMG_SIZE];
  char str_tab1[FN_SIZE];
  char str_tab2[FN_SIZE];

  bw_getread1.deb_record("bw_win::tst_win6_ci_ptr()");

  for (i=0;i<WIN_NUM;i++)
  {
    j=get_mn_h_w_ptr(i,0);
    k=get_mn_h_w_ptr(i,5);

    sprintf(str1,"mn_id=%d,h_w_ptr0=%d,h_w_ptr5=%d,",i,j,k);

    bw_getread1.deb_record(str1);
  }

  for (i=0;i<300;i++)
  {
    j=get_mn_h_ci_ptr(i,0);
    k=get_mn_h_ci_ptr(i,1);
    l=get_mn_h_ci_ptr(i,2);
    m=get_mn_h_ci_ptr(i,3);
    n=get_mn_h_ci_ptr(i,4);

    sprintf(str1,"HND_NUM=%d,hnd_id=%d,ci_ptr0=%d,ci_ptr1=%d,ci_ptr2=%d,ci_ptr3=%d,ci_ptr4=%d,",HND_NUM,i,j,k,l,m,n);

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_win::tst_win7_focus_buf()
{
  int  i,j,k;
  char str1[SMG_SIZE];

  bw_getread1.deb_record("bw_win::tst_win7_focus_buf()");

  sprintf(str1,"mn_focus_ptr1=%d,mn_focus_ptr2=%d,",mn_focus_ptr1,mn_focus_ptr2);
  bw_getread1.deb_record(str1);

  i=mn_focus_ptr1;

  while(1)
  {
    if (i==mn_focus_ptr2) break;

    sprintf(str1,"ptr=%d,mn_focus_buf=%d,",i,get_mn_focus_buf(i));
    bw_getread1.deb_record(str1);

    i++;
    if (i>=BW_WIN_FOCUS_NUM) i=0;
  }

  return(0);
}

int bw_win::w_close_win(int p1)
{
  HWND edit_hnd;
  int  i,j,k,l,m,n;
  int  ptr5;
  int  id[WIN_NUM];
  char str1[SMG_SIZE];

  //i=p1;

  for (m=0;m<STRU_NUM;m++)
  {
    if ((get_mn_ptr_wins_dbf(m,p1)==1)&&(bw_xbase1.get_mn_mem_inuse(m)==1))
    {
      for (n=0;n<EDIT_NUM;n++)
      {
        if (bw_edit1.get_mn_edit_wptr(n)==p1)
	{
	  edit_hnd=bw_edit1.get_mn_edit_hnd1(n);
	  SendMessage(edit_hnd,WM_COMMAND,1803,(LPARAM)0);
	}
      }
    }
  }

  w_close_subwin(p1);

  return(0);
}

int bw_win::w_close_subwin(int p1)
{
  int  exist;
  int  i,j,j2,k,l,m,n,o,p,q,r,s,t,u;
  int  p10,p11,p12;
  char sfn1[FLD_NAME_SIZE];
  char str_tab1[FN_SIZE];
  char str_mvar1[SMG_SIZE];
  char str1[SMG_SIZE];
  int  wid,rid;

  //bw_getread1.deb_record("****** new operate");

  // must answer
  if (bw_xbase1.mn_answer!=0)
  {
    w_atten66(bw_main1.get_mn_hwnd(p1));
    return(1);
  }

  bw_xbase1.mn_answer=1;

  //i=p1;



  /* close database */  
  // lock msg
  set_mn_msgboxlock(p1,1);



  //bw_getread1.deb_record("------before close");
  //bw_fldstru1.tst_stru2();



  for (k=0;k<STRU_NUM;k++)
  {
    if (get_mn_ptr_wins_dbf(k,p1)==1)
    {
      bw_fldstru1.w_dele_stru(k);
      bw_mbase1.w_close_base(k,p1);
      bw_fldstru1.w_clr_condition(k);
    }
  }



  //bw_getread1.deb_record("======after close");
  //bw_fldstru1.tst_stru2();



  // unlock msg
  set_mn_msgboxlock(p1,0);



  //bw_getread1.deb_record("------before close");
  //bw_buttonvar1.tst_button2();
  //bw_link1.tst_link1_lkchar();
  //bw_link1.tst_link5_svar();



  /* remove memory var */
  // notice
  bw_buttonvar1.w_dele_button(p1);

  bw_chkbox1.w_clr_recvar_chkbox(p1);
  bw_rabox1.w_clr_recvar_rabox(p1);
  //bw_dialog1.w_clr_recvar_dialog(p1);

  // notice 
  bw_link1.w_dele_svar(p1);
  bw_link1.w_dele_link(p1);



  //bw_getread1.deb_record("======after close");
  //bw_buttonvar1.tst_button2();
  //bw_link1.tst_link1_lkchar();
  //bw_link1.tst_link5_svar();




  w_dele_win_ptr_wins_dbf(p1);

  /* notice */
  //j=i;
  
  SetFocus(bw_main1.mn_main_hnd);
  k=get_mn_h_w_ptr(p1,0);

  DestroyWindow(get_mn_hnd(k));




  //bw_getread1.deb_record("------before close");
  //tst_win1_fld();



  q=get_mn_ptr_fld_in_win(p1,1)-get_mn_ptr_fld_in_win(p1,0)+1;
  if (q<0) q=0;

  p12=get_mn_ptr_fld_in_win(p1,1);  // last fld ptr

  n=1;

  if (q>0)
  {
    for (j=p1+1;j<WIN_NUM;j++)
    {
      if (get_mn_ptr_grp_id(j)!=0)
      {
        s=get_mn_ptr_fld_in_win(j,0);
        r=get_mn_ptr_fld_in_win(j,1);

        if (p12<r) p12=r;

        for (k=s;k<=r;k++)
        {
          get_t_fldname(k,sfn1,FLD_NAME_SIZE);
          set_t_fldname(k-q,sfn1,FLD_NAME_SIZE);
          set_t_fldtype(k-q,get_t_fldtype(k));
          set_t_fldbase(k-q,get_t_fldbase(k));
          set_t_fldseri(k-q,get_t_fldseri(k));
          set_t_fldlen( k-q,get_t_fldlen(k));
          set_t_flddec( k-q,get_t_flddec(k));
          set_t_fldedt( k-q,get_t_fldedt(k));
        }
      }
    }

    for (k=p12-q+1;k<=p12;k++)
    {
      set_c_t_fldname(k,0,0);
      set_t_fldtype(k,0);
      set_t_fldbase(k,0);
      set_t_fldseri(k,0);
      set_t_fldlen( k,0);
      set_t_flddec( k,0);
      set_t_fldedt( k,0);
    }
  }



  //bw_getread1.deb_record("======after close");
  //tst_win1_fld();



  //bw_getread1.deb_record("------before close");
  //tst_win2_fld_in_win();



  t=1;


  // notice
  p10=p1;                            // last window ptr
  p11=get_mn_h_w_ptr(p1,5);          // last ci ptr

  for (k=p1+1;k<WIN_NUM;k++)
  {
    if (get_mn_ptr_grp_id(k)!=0)
    {
      if (p10<k) p10=k;
      if (p11<get_mn_h_w_ptr(k,5)) p11=get_mn_h_w_ptr(k,5);

      set_mn_ptr_fld_in_win(k-1,0,get_mn_ptr_fld_in_win(k,0)-q);
      set_mn_ptr_fld_in_win(k-1,1,get_mn_ptr_fld_in_win(k,1)-q);

      for (o=0;o<STRU_NUM;o++)
      {
	set_mn_ptr_wins_dbf(o,k-1,get_mn_ptr_wins_dbf(o,k));

        bw_xbase1.set_mn_recno(o,k-1,0,bw_xbase1.get_mn_recno(o,k,0));
        bw_xbase1.set_mn_recno(o,k-1,1,bw_xbase1.get_mn_recno(o,k,1));
      }

      set_mn_linep(k-1,0,get_mn_linep(k,0));
      set_mn_linep(k-1,1,get_mn_linep(k,1));

      bw_win1.set_pline(k-1,bw_win1.get_pline(k));
      bw_win1.set_pcolu(k-1,bw_win1.get_pcolu(k));

      set_mn_con(k-1,0,get_mn_con(k,0));
      set_mn_con(k-1,1,get_mn_con(k,1));

      bw_main1.set_mn_hwnd(k-1,bw_main1.get_mn_hwnd(k));
      
      set_mn_is_link(k-1,get_mn_is_link(k));

      bw_dialog1.set_c_ms_mv_getv(k,SMG_SIZE-1,0);

      bw_dialog1.get_ms_mv_getv(k,str_mvar1,SMG_SIZE);
      bw_dialog1.set_ms_mv_getv(k-1,str_mvar1,SMG_SIZE);

      bw_getread1.set_smg_posi(k-1,bw_getread1.get_smg_posi(k));

      set_mn_phh(k-1,get_mn_phh(k));

      get_ms_window_name(  k,str_tab1,FN_SIZE);
      set_ms_window_name(k-1,str_tab1,FN_SIZE);
      get_ms_find_name(    k,str_tab1,FN_SIZE);
      set_ms_find_name(  k-1,str_tab1,FN_SIZE);

      for (o=0;o<LIN_NUM;o++)
      {
	for (p=0;p<COL_NUM;p++)
	{
	  bw_buff1.set_t3_winfile(k-1,o,p,bw_buff1.get_t3_winfile(k,o,p));
	  if (bw_buff1.get_t3_linecol(k,o,p)!=0)
	    bw_buff1.set_t3_linecol(k-1,o,p,bw_buff1.get_t3_linecol(k,o,p)-q);
	  else
	    bw_buff1.set_t3_linecol(k-1,o,p,0);
	}
      }
    }

  }

  k=p10;

  set_mn_phh(k,0);

  set_mn_ptr_fld_in_win(k,0,0);
  set_mn_ptr_fld_in_win(k,1,0);

  for (o=0;o<STRU_NUM;o++)
  {
    set_mn_ptr_wins_dbf(o,k,0);

    bw_xbase1.set_mn_recno(o,k,0,0);
    bw_xbase1.set_mn_recno(o,k,1,0);
  }




  //bw_getread1.deb_record("======after close");
  //tst_win2_fld_in_win();



  //bw_getread1.deb_record("------before close");
  //tst_win6_ci_ptr();



  if (p1<=1) j2=get_mn_h_w_ptr(p1,5)-0+1;                    // how many ci in current window
  else       j2=get_mn_h_w_ptr(p1,5)-get_mn_h_w_ptr(p1,0)+1;

  for (u=p1+1;u<WIN_NUM;u++)
  {
    if (get_mn_ptr_grp_id(u)!=0)
    {
      m=get_mn_h_w_ptr(u,0);
      o=get_mn_h_w_ptr(u,5);

      for (k=m;k<=o;k++)
      {
        /* notice */
        if (get_mn_h_ci_ptr(k,4)!=0)
        {
          //SetWindowLong(get_mn_hnd(k),GWL_ID,k-j2);
        }

        if (get_mn_h_ci_ptr(k,0)>=1) set_mn_h_ci_ptr(k-j2,0,get_mn_h_ci_ptr(k,0)-1);  /* ci's win num,x,y,hnd num,main hnd */
        set_mn_h_ci_ptr(k-j2,1,get_mn_h_ci_ptr(k,1));
        set_mn_h_ci_ptr(k-j2,2,get_mn_h_ci_ptr(k,2));
        set_mn_h_ci_ptr(k-j2,3,k-j2);

        if (get_mn_h_ci_ptr(k,4)<=0) set_mn_h_ci_ptr(k-j2,4,0);
        else set_mn_h_ci_ptr(k-j2,4,get_mn_h_ci_ptr(k,4)-j2);

        set_mn_hnd(k-j2,get_mn_hnd(k));

        set_mn_proc(k-j2,get_mn_proc(k));
      }
    }
  }

  for (k=p11-j2+1;k<=p11;k++)
  {
    set_mn_h_ci_ptr(k,0,0);  /* ci's win num,x,y,hnd num,main hnd */
    set_mn_h_ci_ptr(k,1,0);
    set_mn_h_ci_ptr(k,2,0);
    set_mn_h_ci_ptr(k,3,0);
    set_mn_h_ci_ptr(k,4,0);

    set_mn_hnd(k,0);
  }



  for (k=p1+1;k<WIN_NUM;k++)
  {
    if (get_mn_ptr_grp_id(k)!=0)
    {
      if (get_mn_h_w_ptr(k,0)>=j2) set_mn_h_w_ptr(k-1,0,get_mn_h_w_ptr(k,0)-j2);
      else                         set_mn_h_w_ptr(k-1,0,0);
      if (get_mn_h_w_ptr(k,5)>=j2) set_mn_h_w_ptr(k-1,5,get_mn_h_w_ptr(k,5)-j2);
      else                         set_mn_h_w_ptr(k-1,5,0);
    }
  }

  set_mn_h_w_ptr(p10,0,0);
  set_mn_h_w_ptr(p10,5,0);



  //bw_getread1.deb_record("======after close");
  //tst_win6_ci_ptr();



  k=get_mn_ptr_get_rd(p1);  // first ptr
  o=k;

  for (m=k+1;m<SMG_GET_NUM;m++)
  {
    if (bw_getread1.get_smg_read_id(m)!=0) o=m; // last ptr
    else break;
  }

  if (o<=k) bw_getread1.get_read_logout(o);
  else
  {
    for (j=k+1;j<=o;j++)
    {
      bw_getread1.set_smg_line(j-1,bw_getread1.get_smg_line(j));
      bw_getread1.set_smg_colu(j-1,bw_getread1.get_smg_colu(j));
      bw_getread1.set_smg_type(j-1,bw_getread1.get_smg_type(j));
      bw_getread1.set_smg_dlen(j-1,bw_getread1.get_smg_dlen(j));
      bw_getread1.set_smg_dlen_real(j-1,bw_getread1.get_smg_dlen_real(j));
      bw_getread1.set_smg_ddec(j-1,bw_getread1.get_smg_ddec(j));
      bw_getread1.set_smg_link(j-1,bw_getread1.get_smg_link(j));
      bw_getread1.set_smg_color(j-1,bw_getread1.get_smg_color(j));
      bw_getread1.set_smg_posi(j-1,bw_getread1.get_smg_posi(j));
      bw_getread1.set_smg_modi(j-1,bw_getread1.get_smg_modi(j));

      bw_getread1.get_smg_atte(j  ,str1,SMG_SIZE);
      bw_getread1.set_smg_atte(j-1,str1,SMG_SIZE);

      bw_getread1.get_smg_string(j  ,str1,SMG_SIZE);
      bw_getread1.set_smg_string(j-1,str1,SMG_SIZE);
    }

    bw_getread1.get_read_logout(o);
  }

  for (j=p1+1;j<WIN_NUM;j++)
  {
    o=get_mn_ptr_get_rd(j);
    if (o>0) set_mn_ptr_get_rd(j-1,o-1);
  }

  set_mn_ptr_get_rd(WIN_NUM-1,0);

  bw_getread1.mn_chns_char=0;



  set_mn_ptr_grp_id(p10,0);



  /* end of memory var move */

  mn_ptr_new_win--;

  // windows focus manage

  //bw_getread1.deb_record("------before close");
  //tst_win7_focus_buf();

  j=mn_focus_ptr2;    // delete focus which is closing

  //sprintf(str1,"step1 j=%d,",j);
  //bw_getread1.deb_record(str1);

  while(1)
  {
    if (j==mn_focus_ptr1) break;
    j--;
    if (j<0) j=BW_WIN_FOCUS_NUM-1;
    if (get_mn_focus_buf(j)==p10) delete_win_focus(j);

    //sprintf(str1,"step1 j=%d,mn_focus_ptr1=%d,mn_focus_ptr2=%d,",j,mn_focus_ptr1,mn_focus_ptr2);
    //bw_getread1.deb_record(str1);
  }

  //bw_getread1.deb_record("step1 ok");

  j=mn_focus_ptr2;    // delete focus which is repeated
  k=0;

  //sprintf(str1,"step2 j=%d,",j);
  //bw_getread1.deb_record(str1);

  while(1)
  {
    if (j==mn_focus_ptr1) break;
    j--;
    if (j<0) j=BW_WIN_FOCUS_NUM-1;
    if (get_mn_focus_buf(j)==k) delete_win_focus(j);
    else k=get_mn_focus_buf(j);

    //sprintf(str1,"step2 j=%d,k=%d,mn_focus_ptr1=%d,mn_focus_ptr2=%d,",j,k,mn_focus_ptr1,mn_focus_ptr2);
    //bw_getread1.deb_record(str1);
  }

  //bw_getread1.deb_record("step2 ok");

  j=mn_focus_ptr2;    // change focus windows id

  while(1)
  {
    if (j==mn_focus_ptr1) break;
    j--;
    if (j<0) j=BW_WIN_FOCUS_NUM-1;
    if (get_mn_focus_buf(j)>p10) set_mn_focus_buf(j,get_mn_focus_buf(j)-1);
  }

  //bw_getread1.deb_record("step3 ok");

  if (mn_focus_ptr2!=mn_focus_ptr1)  // set focus
  {
    j=mn_focus_ptr2-1;
    if (j<0) j=BW_WIN_FOCUS_NUM-1;
    k=get_mn_focus_buf(j);
    SetFocus(get_mn_phh(k));
    
    
    
    //setup get_read
    wid=bw_win1.w_find_winhand(get_mn_phh(k));
    rid=bw_getread1.get_smg_read_id(wid);
    
    bw_getread1.get_smg_string(rid,str1,SMG_SIZE);

    bw_getread1.set_smg_data(0,0);

    for (i=0;i<bw_getread1.get_smg_dlen_real(rid);i++)
    {
      if (i<(int)strlen(str1))
      {
        bw_getread1.set_smg_data(i+0,str1[i]);
        bw_getread1.set_smg_data(i+1,0);
      }
      else
      {
        bw_getread1.set_smg_data(i+0,' ');
        bw_getread1.set_smg_data(i+1,0);
      }
    }
    // end of setup
    
    
    
  }
  else if (mn_ptr_new_win-1>0)
  {
    SetFocus(get_mn_phh(mn_ptr_new_win-1));
    
    
    
    //setup get_read
    wid=bw_win1.w_find_winhand(get_mn_phh(k));
    rid=bw_getread1.get_smg_read_id(wid);
    
    bw_getread1.get_smg_string(rid,str1,SMG_SIZE);

    bw_getread1.set_smg_data(0,0);

    for (i=0;i<bw_getread1.get_smg_dlen_real(rid);i++)
    {
      if (i<(int)strlen(str1))
      {
        bw_getread1.set_smg_data(i+0,str1[i]);
        bw_getread1.set_smg_data(i+1,0);
      }
      else
      {
        bw_getread1.set_smg_data(i+0,' ');
        bw_getread1.set_smg_data(i+1,0);
      }
    }
    // end of setup
    
    
    
  }

  //bw_getread1.deb_record("step4 ok");

  //bw_getread1.deb_record("======after close");
  //tst_win7_focus_buf();



  mn_h_ci_total_ptr=mn_h_ci_total_ptr-j2;

  bw_xbase1.mn_answer=0;

  return(0);
}

int bw_win::delete_win_focus(int ptr)
{
  int i,j;

  i=ptr;
  j=ptr+1;
  if (j>=BW_WIN_FOCUS_NUM) j=0;

  while(1)
  {
    if (j==mn_focus_ptr2) break;
    set_mn_focus_buf(i,get_mn_focus_buf(j));
    i++;
    if (i>=BW_WIN_FOCUS_NUM) i=0;
    j++;
    if (j>=BW_WIN_FOCUS_NUM) j=0;
  }

  mn_focus_ptr2--;
  if (mn_focus_ptr2<0) mn_focus_ptr2=BW_WIN_FOCUS_NUM-1;

  return(0);
}

//can't be static !!!
char m101_str5[STRU_NUM][FN_SIZE];

int bw_win::w_read_winfile(char *p_fn,int p_fn_size)
{
  int  p1,p2,same,end;
  int  state1,state2,state3;
  int  state4,state5,state6;
  int  state7,state8,state9;
  int  state10;
  int  li;
  int  is_tab=0;
  int  is_find=0;
  char str1[SMG_SIZE];
  char str2[FN_SIZE];
  char str3[FN_SIZE];
  char str4[FN_SIZE];
  //char str5[STRU_NUM][FN_SIZE];
  int  n_base6[STRU_NUM];
  char str7[FN_SIZE];
  char str8[FN_SIZE];
  char str9[FN_SIZE];
  int  s_ps=(-1);
  int  s_ps1;
  int  i,j,k,l,m,n,o,p;
  int  lcntr,cmd;
  int  free_base;
  FILE *fp1;
  //char str_tab1[FN_SIZE];
  char str_tab2[FN_SIZE];

  int  s_firstline;
  int  s_lastline;
  int  s_exist;
  int  s_beginposi;
  int  s_endposi;
  char c1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  for (i=0;i<STRU_NUM;i++) 
    for (j=0;j<FN_SIZE;j++) 
      m101_str5[i][j]=0;

  for (j=0;j<FN_SIZE;j++) 
  {
    str7[j]=0;
    str8[j]=0;
    str9[j]=0;
  }

  strcpy(ms_texts1 ,"usetable=");
  strcpy(ms_texts2 ,"enddefine");
  strcpy(ms_texts3 ,"screenseg");
  strcpy(ms_texts4 ,"endscreen");
  strcpy(ms_texts5 ,"readvatype");
  strcpy(ms_texts6 ,"findfile=");
  strcpy(ms_texts7 ,"findbase=");
  strcpy(ms_texts8 ,"switchbmp");
  strcpy(ms_texts9 ,"switchtm=");
  strcpy(ms_texts10,"ci_mode");

  free_base=bw_xbase1.w_free_xbase();

  fp1=fopen(p_fn,"r");    /* fetch page of screen format from screen file */
  if (fp1==NULL)
  {
    w_atten1(bw_main1.mn_hwnd1,p_fn);
    return(1);
  }

  k=mn_ptr_new_win;

  set_mn_timer(k,0);

  set_mn_ci_mode(k,0);

  s_firstline=1;
  s_lastline=1;

  for (j=0;j<LIN_NUM;j++)
    for (i=0;i<COL_NUM;i++)
	bw_buff1.set_t3_winfile(k,j,i,' ');

  lcntr=0;
  set_mn_switch_bmp(k,0);

  i=(-1);
/*
  for (i=0;i<LIN_NUM+10;i++)
  {
    if (feof(fp1))
    {
      end=1;
      break;
    }
*/
  while (!feof(fp1))
  {
    str1[0]=0;

    fgets(str1,SMG_SIZE,fp1);
    
    i++;
    if (i>=LIN_NUM+10) break;
    
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
    state7=0;
    state8=0;
    state9=0;
    state10=0;

    for (j=0;j<COL_NUM;j++)
    {
      if (str1[j]=='&') break; /* locate for '&' */
    }

    j++;
    p1=j;
    if (p1<strlen(str1))  //there is '&'
    {
      same=1;     // find usetable & stru name
      for (p2=p1;p2<=p1+strlen(ms_texts1)-1;p2++)  
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
        state1=1;  // there is keyword "usetable=" 
        is_tab=1;  // this scrn file is table screen 

        s_ps++;
        if (s_ps>=STRU_NUM) s_ps=STRU_NUM-1;

        for (l=0;l<FN_SIZE;l++)
        {
          if ((str1[p1+strlen(ms_texts1)+l]>=0)&&(str1[p1+strlen(ms_texts1)+l]<=' ')) break;
          else
          {
            m101_str5[s_ps][l+0]=str1[p1+strlen(ms_texts1)+l];
            m101_str5[s_ps][l+1]=0;
          }
        }
      }

      same=1;  //enddefine
      for (p2=p1;p2<=p1+strlen(ms_texts2)-1;p2++)
      {
        if ((ms_texts2[p2-p1]>=0)&&(ms_texts2[p2-p1]<=' ')) break;
        if (str1[p2]!=ms_texts2[p2-p1])
        {
          same=0;
          break;
        }
      }
      if (same==1) state2=1;

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
      if (same==1) state3=1;

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
      if (same==1) state4=1;

      same=1;  //read var type
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

      same=1;  //find file
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
        state7=1;
        o=p1+strlen(ms_texts6);
        for (p=o;p<COL_NUM;p++)
        {
          if ((str1[p]>=0)&&(str1[p]<=' ')) break;
          else
          {
            str7[p-o+0]=str1[p];
            str7[p-o+1]=0;
          }
        }
      }

      same=1;     // find findbase name
      for (p2=p1;p2<=p1+strlen(ms_texts7)-1;p2++)  
      {
        if ((ms_texts7[p2-p1]>=0)&&(ms_texts7[p2-p1]<=' ')) break;
        if (str1[p2]!=ms_texts7[p2-p1])
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
          if ((str1[p1+strlen(ms_texts7)+l]>=0)&&(str1[p1+strlen(ms_texts7)+l]<=' ')) break;
          else
          {
            str8[l+0]=str1[p1+strlen(ms_texts7)+l];
            str8[l+1]=0;
          }
        }
      }

      same=1;  //switch bmp
      for (p2=p1;p2<=p1+strlen(ms_texts8)-1;p2++)  /* recnigze keywords */
      {
        if ((ms_texts8[p2-p1]>=0)&&(ms_texts8[p2-p1]<=' ')) break;
        if (str1[p2]!=ms_texts8[p2-p1])
        {
          same=0;
          break;
        }
      }
      if (same==1) state8=1;

      same=1;   // find timer name
      for (p2=p1;p2<=p1+strlen(ms_texts9)-1;p2++)  
      {
        if ((ms_texts9[p2-p1]>=0)&&(ms_texts9[p2-p1]<=' ')) break;
        if (str1[p2]!=ms_texts9[p2-p1])
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
          if ((str1[p1+strlen(ms_texts9)+l]>=0)&&(str1[p1+strlen(ms_texts9)+l]<=' ')) break;
          else
          {
            str9[l+0]=str1[p1+strlen(ms_texts9)+l];
            str9[l+1]=0;
          }
        }
      }

      same=1;  //ci mode
      for (p2=p1;p2<=p1+strlen(ms_texts10)-1;p2++)  /* recnigze keywords */
      {
        if ((ms_texts10[p2-p1]>=0)&&(ms_texts10[p2-p1]<=' ')) break;
        if (str1[p2]!=ms_texts10[p2-p1])
        {
          same=0;
          break;
        }
      }
      if (same==1)
      {
        set_mn_ci_mode(k,1);
        state10=1;
      }

    }

    if (state1==1)  cmd=1; /* use table */
    if (state2==1)  cmd=1; /* enddefine  */
    if (state3==1)         /* screenseg */
    {
      end=1;
      break; 
    }
    if (state4==1)        /* endscreen */
    {
      end=1;
      break;
    }
    if (state5==1)  cmd=1; /* screentype */
    if (state6==1)  cmd=1; /* find findbase*/
    if (state7==1)  cmd=1; /* find define  */
    if (state8==1)
    {
      cmd=1; /* switch bmp */
      set_mn_switch_bmp(k,1);
    }
    if (state9==1)
    {
      cmd=1; // timer
      li=bw_inkey1.str2int(str9,FN_SIZE);
      set_mn_timer(k,li);
    }
    if (state10==1) cmd=1; /* ci_mode */

    if (cmd==1) continue;  //command line

    for (j=0;j<COL_NUM;j++)  // save window
    {
      if (  (j>=strlen(str1))  ||  ((str1[j]>=0)&&(str1[j]<' '))  ) c1=' ';
      else c1=str1[j];
      
      bw_buff1.set_t3_winfile(k,lcntr,j,c1);
    }
    
    lcntr++;                //window form line
  }

  m=mn_ptr_new_win;

  if (feof(fp1)) end=1;

  fclose(fp1);
  
  if (end==1)
  {
    if (s_ps+1>free_base)
    {
      w_atten22(bw_main1.mn_hwnd1);
      return(1);
    }
    else
    {
      mn_ptr_new_win++;
    }
  }
  else
  {
    w_atten3(bw_main1.mn_hwnd1);
    return(1);
  }

  w_login_win(k,p_fn,p_fn_size,str7,FN_SIZE);
  
  if (is_tab==1)  /* it is a table scrn */
  {
    l=0;
    for (i=0;i<=s_ps;i++)     /* login base ,fetch buff ptr */
    {
      j=bw_xbase1.w_login_xbase(l);
      if (j<0)
      {
	w_atten58(bw_main1.mn_hwnd1);
	w_dele_win_ptr(m);
	return(1);
      }
      n_base6[i]=j;
      l=j+1;
    }

    for (i=m;i<=k;i++)  /* mark win base ptr */
    {
      for (j=0;j<STRU_NUM;j++)
      {
	set_mn_ptr_wins_dbf(j,i,0);
      }

      for (j=0;j<=s_ps;j++)
      {
        if (n_base6[j]>=STRU_NUM) continue;
	set_mn_ptr_wins_dbf(n_base6[j],i,1);
	bw_xbase1.set_mn_state_bff_in_use(n_base6[j],1);
      }
    }

    for (i=0;i<=1;i++) for (j=0;j<=s_ps;j++)
    {
      if (n_base6[j]>=STRU_NUM) continue;
      set_ms_tabname(i,n_base6[j],"                      ",20);
    }
			   /* stru&base name in win 0-stru 1-base*/
    for (s_ps1=0;s_ps1<=s_ps;s_ps1++)  /* fetch stru & base name from m101_str5 */
    {
      if (n_base6[s_ps1]>=STRU_NUM) continue;
      j=0;
      for (i=0;i<FN_SIZE;i++)          /* fetch base name */
      {
	if (m101_str5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten4(bw_main1.mn_hwnd1);
	w_dele_xbase_state(m);
        w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	bw_inkey1.cut_string(m101_str5[s_ps1],0,i,FN_SIZE,str_tab2,FN_SIZE);
	set_ms_tabname(1,n_base6[s_ps1],str_tab2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch stru name */
      {
	if (m101_str5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten5(bw_main1.mn_hwnd1);
	w_dele_xbase_state(m);
        w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten6(bw_main1.mn_hwnd1);
	else bw_inkey1.cut_string(m101_str5[s_ps1],p1+5,i-p1-5,FN_SIZE,str_tab2,FN_SIZE);
	set_ms_tabname(0,n_base6[s_ps1],str_tab2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch base type */
      {
	if (m101_str5[s_ps1][i]==',')
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten59(bw_main1.mn_hwnd1);
	w_dele_xbase_state(m);
        w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten60(bw_main1.mn_hwnd1);
	else bw_inkey1.cut_string(m101_str5[s_ps1],p1+9,i-p1-9,FN_SIZE,str2,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch backup type */
      {
	if (((m101_str5[s_ps1][i]>=0)&&(m101_str5[s_ps1][i]<=' '))||(m101_str5[s_ps1][i]==','))
	{
	  j=1;
	  break;
	}
      }
      if (j==0)  /* not find ',' */
      {
	w_atten61(bw_main1.mn_hwnd1);
	w_dele_xbase_state(m);
	w_dele_win_ptr(m);
	return(1);
      }
      else
      {
	if (i-p1-5<=0) w_atten62(bw_main1.mn_hwnd1);
	else bw_inkey1.cut_string(m101_str5[s_ps1],p1+7,i-p1-7,FN_SIZE,str3,FN_SIZE);
      }

      p1=i+1;
      j=0;
      for (i=p1;i<FN_SIZE;i++)          /* fetch carryon &carryoff */
      {
	if ((m101_str5[s_ps1][i]>=0)&&(m101_str5[s_ps1][i]<=' '))
	{
	  j=1;
	  break;
	}
      }
      if (j==1)  /* not find ' ' */
      {
	if (i-p1>0)
	{
	  bw_inkey1.cut_string(m101_str5[s_ps1],p1,i-p1,FN_SIZE,str4,FN_SIZE);
	  if (strncmp(str4,"carryon",7)==0)
	    bw_xbase1.set_mn_carry_on(n_base6[s_ps1],1);
	  else
	    bw_xbase1.set_mn_carry_on(n_base6[s_ps1],0);
	}
	else bw_xbase1.set_mn_carry_on(n_base6[s_ps1],0);
      }
      else bw_xbase1.set_mn_carry_on(n_base6[s_ps1],0);
    }
  }

  for (s_ps1=0;s_ps1<=s_ps;s_ps1++)  /* database type , backup type */
  {
    if (n_base6[s_ps1]>=STRU_NUM) continue;

    if (strcmp(str2,"xbase")==0) bw_xbase1.set_mn_base_type(n_base6[s_ps1],0);
    else bw_xbase1.set_mn_base_type(n_base6[s_ps1],1);

    bw_inkey1.strtrim(str3,FN_SIZE);

    if (strcmp(str3,"1")==0) bw_xbase1.set_mn_base_backup(n_base6[s_ps1],1);
    else bw_xbase1.set_mn_base_backup(n_base6[s_ps1],0);
  }

  return(0);
}

int bw_win::w_dele_xbase_state(int p_wptr)
{
  int  i;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_mn_ptr_wins_dbf(i,p_wptr)==1)
    {
      bw_xbase1.set_mn_state_bff_in_use(i,0);
      set_ms_tabname(0,i,"",0);
      set_ms_tabname(1,i,"",0);
    }
  }

  return(0);
}

int bw_win::w_echo_winrec_paint(int p_wptr,int mark)  //paint win
{ 
  HFONT holdfont,hfont;
  HDC   hdc;
  int   p1,p2,p4,p5,p7,p8;
  int   state1;
  int   state7;
  int   i,j,k;
  int   ptr1,ptr3;
  char  str[SMG_SIZE];
  int   ini=0;

  if (get_mn_ptr_fld_in_win(p_wptr,0)==0)
  {
    i=p_wptr-1;
    while ((get_mn_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_mn_ptr_fld_in_win(p_wptr,0,get_mn_ptr_fld_in_win(i,1)+1);
    ptr1=get_mn_ptr_fld_in_win(i,1);
  }
  else ptr1=get_mn_ptr_fld_in_win(p_wptr,0)-1;

  hdc=GetDC(bw_main1.get_mn_hwnd(p_wptr));

  if (get_mn_ci_mode(p_wptr)==0)
  {
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
  }

  for (i=0;i<LIN_NUM;i++)
  {
    if (get_mn_ci_mode(p_wptr)==0)
    {                                                                                    
      p1=COL_NUM-1;
      p2=0;
      for (j=0;j<COL_NUM;j++)  
      {
        if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
        {
	  p1=j;
	  break;
        }
      }
      for (j=COL_NUM-1;j>=0;j--)
      {
	if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
        {
	  p2=j;
	  break;
        }
      }
      if (p2<p1) continue;
    }
    else
    {
      p1=get_mn_ci_posi(p_wptr,0);
      p2=get_mn_ci_posi(p_wptr,1);

      j=0;

      for (k=p1;k<=p2;k++)
      {
	if ((bw_buff1.get_t3_winfile(p_wptr,i,k)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,k)<0))
	{
	  j=1;
	  break;
	}
      }

      if (j==0) continue;
    }

    state1=0;
    state7=0;
    p4=0;
    p5=0;
    if (ini==0)
    {
      p7=i;  //corner y
      p8=p1; //corner x
      ini=1;
    }
    ptr3=0;

    for (j=p1;j<=p2;j++)  
    {
      if (bw_buff1.get_t3_winfile(p_wptr,i,j)=='&')
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
	if (bw_buff1.get_t3_winfile(p_wptr,i,j)<=' ')
	{
          if (state7==1) continue;
	  if (mark==1)
	  {
	    if (bw_buff1.get_t3_winfile(p_wptr,i,j)<0)
	    {
	      if (ptr3==1)
	      {
		ptr3=0;
		continue;
              }
	      else
	      {
                ptr3=1;
		str[0]=bw_buff1.get_t3_winfile(p_wptr,i,j);
		if (bw_buff1.get_t3_winfile(p_wptr,i,j+1)!='&')
                {
		  str[1]=bw_buff1.get_t3_winfile(p_wptr,i,j+1);
                  str[2]=0;
                }
                else str[1]=0;
		if (get_mn_ci_mode(p_wptr)==0)
                {
		  TextOut(hdc,(int)((j-p8)*bw_main1.mn_edit_xchar)
                        ,(int)((i-p7)*bw_main1.mn_edit_ychar)
		        ,str,strlen(str));
                }
		else
                {
		  TextOut(hdc,(int)((j-p8)*bw_main1.mn_xchar)
                        ,(int)((i-p7)*bw_main1.mn_ychar)
		        ,str,strlen(str));
                }
              }
            }
          }
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_wptr,i,j)!=' ')
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
	    if ((bw_buff1.get_t3_winfile(p_wptr,i,j)=='(')
	      &&(bw_buff1.get_t3_winfile(p_wptr,i,j-1)!='&'))
	    {
	      state7=1;
              state1=0;
              continue;
            }
	    if ((p4==0)&&(bw_buff1.get_t3_winfile(p_wptr,i,j-1)=='%'))
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
	    if (bw_buff1.get_t3_winfile(p_wptr,i,j)==')')
            {
	      state7=0;
	      continue;
	    }
	    if (state7==1) continue;
	    if (mark==1)
	    {
	      str[0]=bw_buff1.get_t3_winfile(p_wptr,i,j);
	      str[1]=0;
	      if (get_mn_ci_mode(p_wptr)==0)
              {
		TextOut(hdc,(int)((j-p8)*bw_main1.mn_edit_xchar)
		     ,(int)((i-p7)*bw_main1.mn_edit_ychar)
	             ,str,strlen(str));
              }
              else
              {
		TextOut(hdc,(int)((j-p8)*bw_main1.mn_xchar)
		     ,(int)((i-p7)*bw_main1.mn_ychar)
	             ,str,strlen(str));
              }
            }
	  }
	}
      }
    }
  }

  if (get_mn_ci_mode(p_wptr)==0)
  {
    SelectObject(hdc,holdfont);
  }

  ReleaseDC(bw_main1.get_mn_hwnd(p_wptr),hdc);

  return(0);
}

int bw_win::w_field_info1(int p_wptr,int mark) // get field info
{ 
  int  p1,p2,p4,p5,p6,p7,p8,p9,p10,p10a;
  int  state1;
  int  state7;
  int  i,j,k,l;
  int  ptr1,ptr3;
  int  t1,t2;
  //char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];
  int  ini=0;

  mn_mark=mark;

  for (i=0;i<WIN_STYLE_NUM;i++) set_mn_style(p_wptr,i,0);

  if (get_mn_ptr_fld_in_win(p_wptr,0)==0)
  {
    i=p_wptr-1;
    while ((get_mn_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_mn_ptr_fld_in_win(p_wptr,0,get_mn_ptr_fld_in_win(i,1)+1);
    ptr1=get_mn_ptr_fld_in_win(i,1);
  }
  else ptr1=get_mn_ptr_fld_in_win(p_wptr,0)-1;

  ptr3=mn_h_ci_total_ptr;

  if (mn_h_ci_total_ptr>=HND_NUM) return(0);

  for (i=0;i<LIN_NUM;i++)
  {
    for (j=0;j<COL_NUM;j++)
    {
      bw_buff1.set_t3_linecol(p_wptr,i,j,0);
    }
  }

  for (i=0;i<LIN_NUM;i++)
  {                                                                                       
    if (get_mn_ci_mode(p_wptr)==0)  // get 1 line's begin and end
    {                                                                                    
      p1=COL_NUM-1;
      p2=0;
      for (j=0;j<COL_NUM;j++)  
      {
        if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
        {
	  p1=j;
	  break;
        }
      }
      for (j=COL_NUM-1;j>=0;j--)
      {
	if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
        {
	  p2=j;
	  break;
        }
      }
      if (p2<p1) continue;
    }
    else
    {
      p1=get_mn_ci_posi(p_wptr,0);
      p2=get_mn_ci_posi(p_wptr,1);

      j=0;
      for (k=p1;k<=p2;k++)
      {
	if ((bw_buff1.get_t3_winfile(p_wptr,i,k)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,k)<0))
	{
	  j=1;
	  break;
	}
      }

      if (j==0) continue;
    }

    state1=0;
    state7=0;
    if (ini==0)
    {
      p7=i;
      p8=p1;
      set_mn_con(p_wptr,1,p7);
      set_mn_con(p_wptr,0,p8);
      p9=p2-p1+2;
      set_mn_con(p_wptr,2,p9);
      p10=i;
      ini=1;
    }

    if (bw_main1.mn_cre_menu==1) p10a=i-p10+4;
    else p10a=i-p10+3;

    set_mn_con(p_wptr,3,p10a);
      
    p4=0;
    p5=0;
    p6=0;

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_wptr,i,j)=='&')
      {
	if (p5==1)                   // before is ci ,save before ci
	{
	  set_mn_style(p_wptr,1,1);

	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if (str2[0]=='(') set_mn_style(p_wptr,2,1);
	  if (str2[0]=='[') set_mn_style(p_wptr,3,1);
	  if (str2[0]=='@') set_mn_style(p_wptr,4,1);
	  if (str2[0]=='#') set_mn_style(p_wptr,5,1);
	  if (str2[0]=='%') set_mn_style(p_wptr,6,1);
	  if (str2[0]==':') set_mn_style(p_wptr,7,1);
	  if (str2[0]=='?') set_mn_style(p_wptr,8,1);
	  if (str2[0]=='+') set_mn_style(p_wptr,9,1);
	  if (str2[0]=='-') set_mn_style(p_wptr,9,1);

	  set_t_fldlen(ptr1,j-1-p6);
	}

	ptr1++;                      // into new ci
	if (bw_buff1.get_t3_winfile(p_wptr,i,j+1)=='#') bw_buff1.set_t3_linecol(p_wptr,i,j+1,ptr1);
	else bw_buff1.set_t3_linecol(p_wptr,i,j,ptr1);
	p4=0;      
	p5=1;        // ci begin
	state1=1;    // ci name begin
        p6=j;      

      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_wptr,i,j)<=' ')
	{
          if (state7==1) continue;  // its button name
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_wptr,i,j)!=' ') //its chiness
	  {
	    if (p5==1)  // before ci end,save before ci
	    {
	      set_mn_style(p_wptr,1,1);

	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='(') set_mn_style(p_wptr,2,1);
	      if (str2[0]=='[') set_mn_style(p_wptr,3,1);
	      if (str2[0]=='@') set_mn_style(p_wptr,4,1);
	      if (str2[0]=='#') set_mn_style(p_wptr,5,1);
	      if (str2[0]=='%') set_mn_style(p_wptr,6,1);
	      if (str2[0]==':') set_mn_style(p_wptr,7,1);
	      if (str2[0]=='?') set_mn_style(p_wptr,8,1);
	      if (str2[0]=='+') set_mn_style(p_wptr,9,1);
	      if (str2[0]=='-') set_mn_style(p_wptr,9,1);

	      set_t_fldlen(ptr1,j-p6);
	      p5=0;
	    }
	  }
	}
	else
	{
	  if (state1==1)  // ci's name
	  {
	    if ((bw_buff1.get_t3_winfile(p_wptr,i,j)=='(')
	      &&(bw_buff1.get_t3_winfile(p_wptr,i,j-1)!='&'))
	    {
              state7=1;                // button name begin
	      state1=0;
	      set_t_fldlen(ptr1,j-p6);
              continue;
	    }
	    if ((p4==0)&&(bw_buff1.get_t3_winfile(p_wptr,i,j-1)=='%'))  //save ci's name
	    {
	      set_c_t_fldname(ptr1,p4,'%');
	      p4++;
	    }
	    set_c_t_fldname(ptr1,p4+0,bw_buff1.get_t3_winfile(p_wptr,i,j));
	    set_c_t_fldname(ptr1,p4+1,0);
	    set_t_fldtype(ptr1,'c');
	    p4++;
	  }
	  else  // out of ci
	  {
	    if (bw_buff1.get_t3_winfile(p_wptr,i,j)==')')
	    {
	      state7=0;  // button name end
	      continue;
            }
	    if (p5==1)  // save before ci
	    {
	      set_mn_style(p_wptr,1,1);

	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='(') set_mn_style(p_wptr,2,1);
	      if (str2[0]=='[') set_mn_style(p_wptr,3,1);
	      if (str2[0]=='@') set_mn_style(p_wptr,4,1);
	      if (str2[0]=='#') set_mn_style(p_wptr,5,1);
	      if (str2[0]=='%') set_mn_style(p_wptr,6,1);
	      if (str2[0]==':') set_mn_style(p_wptr,7,1);
	      if (str2[0]=='?') set_mn_style(p_wptr,8,1);
	      if (str2[0]=='+') set_mn_style(p_wptr,9,1);
	      if (str2[0]=='-') set_mn_style(p_wptr,9,1);

	      set_t_fldlen(ptr1,j-p6);
	      p5=0;
	    }
	  }
	}
      }
    }

    if (p5==1)   // before return
    {
	set_mn_style(p_wptr,1,1);

	get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	if (str2[0]=='(') set_mn_style(p_wptr,2,1);
	if (str2[0]=='[') set_mn_style(p_wptr,3,1);
	if (str2[0]=='@') set_mn_style(p_wptr,4,1);
	if (str2[0]=='#') set_mn_style(p_wptr,5,1);
	if (str2[0]=='%') set_mn_style(p_wptr,6,1);
	if (str2[0]==':') set_mn_style(p_wptr,7,1);
	if (str2[0]=='?') set_mn_style(p_wptr,8,1);
	if (str2[0]=='+') set_mn_style(p_wptr,9,1);
	if (str2[0]=='-') set_mn_style(p_wptr,9,1);
	
        set_t_fldlen(ptr1,j-1-p6);
    }
  }

  set_mn_ptr_fld_in_win(p_wptr,1,ptr1);

  // adjust field length for 800*600 256 color mode
  /*
  for (i=get_mn_ptr_fld_in_win(p_wptr,0);i<=get_mn_ptr_fld_in_win(p_wptr,1);i++)
  {
    if (get_t_fldlen(i)>18)
    {
      set_t_fldlen(i,get_t_fldlen(i)-4);
    }
  }
  */
  return(0);
}

//int bw_win::w_cre_ci_button(int p_wptr,char *p_s1,int p_s1_len,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_button(int p_wptr,char *p_s1,int p_s1_size,int p6,int p7,int p8,int p9,char *p_s2,int p_s2_size)
{
  HWND hnd;
  int  i,j;

  char s3[SMG_SIZE];
  char s4[SMG_SIZE];

  if (p_s2_size<2) return(0);

  s4[0]=p_s2[1];
  s4[1]=0;

  strcpy(s3,"<");
  strcat(s3,s4);
  strcat(s3,p_s1);
  strcat(s3,">");

  if (get_mn_ci_mode(p_wptr)==0)
  {
    hnd=CreateWindow("button",s3
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,(int)((p6-p8)*bw_main1.mn_edit_xchar)
		      ,(int)((p9-p7)*bw_main1.mn_edit_ychar)
		      ,(int)((strlen(p_s1)+3)*bw_main1.mn_edit_xchar)
		      ,(int)(bw_main1.mn_edit_ychar+6)
		      ,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
		      ,bw_main1.mn_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",s3
		      ,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE
		      ,(int)((p6-p8)*bw_main1.mn_xchar)
		      ,(int)((p9-p7)*bw_main1.mn_ychar)
		      ,(int)((3+strlen(p_s1))*bw_main1.mn_xchar)
		      ,(int)(bw_main1.mn_ychar+6)
		      ,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
		      ,bw_main1.mn_ins,NULL);
  }

  set_mn_hnd(mn_h_ci_total_ptr,hnd);
  if (get_mn_hnd(mn_h_ci_total_ptr)==NULL) bw_main1.mn_cre_ok=0;

  set_mn_h_w_ptr(p_wptr,5,mn_h_ci_total_ptr);

  set_mn_h_ci_ptr(mn_h_ci_total_ptr,0,p_wptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,1,p6);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,2,p9);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,3,mn_h_ci_total_ptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,4,get_mn_h_w_ptr(p_wptr,0));

  mn_h_ci_total_ptr++;

  return(0);
}

//int bw_win::w_cre_ci_edit(int p_wptr,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_edit(int p_wptr,int p6,int p7,int p8,int p9)
{
  HWND hnd;

  if (get_mn_ci_mode(p_wptr)==0)
  {
    hnd=CreateWindow("edit",""
		,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
		,(int)((p6-p8)*bw_main1.mn_edit_xchar)
		,(int)((p9-p7)*bw_main1.mn_edit_ychar-6)
		,(int)(4*bw_main1.mn_edit_xchar)
		,(int)(bw_main1.mn_edit_ychar+12)
		,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
		,bw_main1.mn_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("edit",""
		,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
		,(int)((p6-p8)*bw_main1.mn_xchar)
		,(int)((p9-p7)*bw_main1.mn_ychar-6)
		,(int)(4*bw_main1.mn_xchar)
		,(int)(bw_main1.mn_ychar+12)
		,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
		,bw_main1.mn_ins,NULL);
  }

  set_mn_hnd(mn_h_ci_total_ptr,hnd);
  if (get_mn_hnd(mn_h_ci_total_ptr)==NULL) bw_main1.mn_cre_ok=0;

  set_mn_h_w_ptr(p_wptr,5,mn_h_ci_total_ptr);

  set_mn_h_ci_ptr(mn_h_ci_total_ptr,0,p_wptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,1,p6);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,2,p9);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,3,mn_h_ci_total_ptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,4,get_mn_h_w_ptr(p_wptr,0));

  mn_h_ci_total_ptr++;

  return(0);
}

//int bw_win::w_cre_ci_radio(int p_wptr,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_radio(int p_wptr,int p6,int p7,int p8,int p9,char *p_s1,int p_s1_size)
{
  HWND hnd;


  char str1[SMG_SIZE];

  strcpy(str1,p_s1);
  strcat(str1," )");


  if (get_mn_ci_mode(p_wptr)==0)
  {
    hnd=CreateWindow("button",str1
			,WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON
			,(int)((p6-p8)*bw_main1.mn_edit_xchar)
			,(int)((p9-p7)*bw_main1.mn_edit_ychar)
			,(int)(2*bw_main1.mn_edit_xchar)
			,(int)(bw_main1.mn_edit_ychar)
			,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
			,bw_main1.mn_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",str1
			,WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON
			,(int)((p6-p8)*bw_main1.mn_xchar)
			,(int)((p9-p7)*bw_main1.mn_ychar)
			,(int)(2*bw_main1.mn_xchar)
			,(int)(bw_main1.mn_ychar)
			,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
			,bw_main1.mn_ins,NULL);
  }

  set_mn_hnd(mn_h_ci_total_ptr,hnd);
  if (get_mn_hnd(mn_h_ci_total_ptr)==NULL) bw_main1.mn_cre_ok=0;

  set_mn_h_w_ptr(p_wptr,5,mn_h_ci_total_ptr);

  set_mn_h_ci_ptr(mn_h_ci_total_ptr,0,p_wptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,1,p6);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,2,p9);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,3,mn_h_ci_total_ptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,4,get_mn_h_w_ptr(p_wptr,0));

  mn_h_ci_total_ptr++;

  return(0);
}

//int bw_win::w_cre_ci_check(int p_wptr,int p6,int p7,int p8,int i)
int bw_win::w_cre_ci_check(int p_wptr,int p6,int p7,int p8,int p9,char *p_s1,int p_s1_size)
{
  HWND hnd;
  
  
  char str1[SMG_SIZE];

  strcpy(str1,p_s1);
  strcat(str1," ]");


  if (get_mn_ci_mode(p_wptr)==0)
  {
    hnd=CreateWindow("button",str1
			,WS_CHILD|WS_VISIBLE|BS_CHECKBOX
			,(int)((p6-p8)*bw_main1.mn_edit_xchar)
			,(int)((p9-p7)*bw_main1.mn_edit_ychar)
			,(int)(2*bw_main1.mn_edit_xchar)
			,(int)(bw_main1.mn_edit_ychar)
			,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
			,bw_main1.mn_ins,NULL);
  }
  else
  {
    hnd=CreateWindow("button",str1
			,WS_CHILD|WS_VISIBLE|BS_CHECKBOX
			,(int)((p6-p8)*bw_main1.mn_xchar)
			,(int)((p9-p7)*bw_main1.mn_ychar)
			,(int)(2*bw_main1.mn_xchar)
			,(int)(bw_main1.mn_ychar)
			,bw_main1.get_mn_hwnd(p_wptr),(HMENU)mn_h_ci_total_ptr
			,bw_main1.mn_ins,NULL);
  }

  set_mn_hnd(mn_h_ci_total_ptr,hnd);
  if (get_mn_hnd(mn_h_ci_total_ptr)==NULL) bw_main1.mn_cre_ok=0;

  set_mn_h_w_ptr(p_wptr,5,mn_h_ci_total_ptr);

  set_mn_h_ci_ptr(mn_h_ci_total_ptr,0,p_wptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,1,p6);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,2,p9);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,3,mn_h_ci_total_ptr);
  set_mn_h_ci_ptr(mn_h_ci_total_ptr,4,get_mn_h_w_ptr(p_wptr,0));

  mn_h_ci_total_ptr++;

  return(0);
}

int bw_win::w_cre_win_button(int p_wptr,int mark) // create button ci
{ 
  int  p1,p2,p4,p5,p6,p7,p8,p9,p10,p10a;
  int  state1;
  int  state7;
  int  i,j,k,l;
  int  ptr1,ptr3;
  int  t1,t2;
  char str1[SMG_SIZE];
  char str2[FLD_NAME_SIZE];
  int  ini=0;

  mn_mark=mark;

  if (get_mn_ptr_fld_in_win(p_wptr,0)==0)
  {
    i=p_wptr-1;
    while ((get_mn_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_mn_ptr_fld_in_win(p_wptr,0,get_mn_ptr_fld_in_win(i,1)+1);
    ptr1=get_mn_ptr_fld_in_win(i,1);
  }
  else ptr1=get_mn_ptr_fld_in_win(p_wptr,0)-1;

  ptr3=mn_h_ci_total_ptr;

  if (mn_h_ci_total_ptr>=HND_NUM) return(0);

  for (i=0;i<LIN_NUM;i++)
  {
    p1=COL_NUM-1;
    p2=0;
    for (j=0;j<COL_NUM;j++)  
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=0;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue;

    state1=0;
    state7=0;
    p4=0;
    p5=0;
    p6=0;
    if (ini==0)
    {
      p7=i;  //corner y
      p8=p1; //corner x
      ini=1;
    }

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_wptr,i,j)=='&')
      {
	if (p5==1)
	{
	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if (str2[0]=='@')
	  {
	    for (t1=p6;t1<COL_NUM;t1++)
	    {
	      if (bw_buff1.get_t3_winfile(p_wptr,i,t1)=='(') break;
            }

	    for (t2=p6;t2<COL_NUM;t2++)
	    {
	      if (bw_buff1.get_t3_winfile(p_wptr,i,t2)==')') break;
	    }

            str1[0]=0;

	    for (l=t1+1;l<t2;l++)
	    {
	      str1[l-t1-1]=bw_buff1.get_t3_winfile(p_wptr,i,l);
	      str1[l-t1]=0;
            }

	    w_cre_ci_button(p_wptr,str1,SMG_SIZE,p6,p7,p8,i,str2,strlen(str2)+1);

	    if (mn_h_ci_total_ptr>=HND_NUM) return(0);
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
	if (bw_buff1.get_t3_winfile(p_wptr,i,j)<=' ')
	{
          if (state7==1) continue;
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_wptr,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]=='@')
	      {
		  for (t1=p6;t1<COL_NUM;t1++)
		  {
		    if (bw_buff1.get_t3_winfile(p_wptr,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buff1.get_t3_winfile(p_wptr,i,t2)==')') break;
		  }

                  str1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    str1[l-t1-1]=bw_buff1.get_t3_winfile(p_wptr,i,l);
		    str1[l-t1]=0;
                  }

		  w_cre_ci_button(p_wptr,str1,SMG_SIZE,p6,p7,p8,i,str2,strlen(str2)+1);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
	      }
	      p5=0;
	    }
	  }
	}
	else
	{
	  if (state1==1)
	  {
	    if ((bw_buff1.get_t3_winfile(p_wptr,i,j)=='(')
	      &&(bw_buff1.get_t3_winfile(p_wptr,i,j-1)!='&'))
	    {
              state7=1;
	      state1=0;
              continue;
	    }
	  }
	  else
	  {
	    if (bw_buff1.get_t3_winfile(p_wptr,i,j)==')')
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
		    if (bw_buff1.get_t3_winfile(p_wptr,i,t1)=='(') break;
                  }

		  for (t2=p6;t2<COL_NUM;t2++)
		  {
		    if (bw_buff1.get_t3_winfile(p_wptr,i,t2)==')') break;
		  }

		  str1[0]=0;

		  for (l=t1+1;l<t2;l++)
		  {
		    str1[l-t1-1]=bw_buff1.get_t3_winfile(p_wptr,i,l);
		    str1[l-t1]=0;
                  }

		  w_cre_ci_button(p_wptr,str1,SMG_SIZE,p6,p7,p8,i,str2,strlen(str2)+1);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
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
          if (bw_buff1.get_t3_winfile(p_wptr,i,t1)=='(') break;
        }

        for (t2=p6;t2<COL_NUM;t2++)
        {
          if (bw_buff1.get_t3_winfile(p_wptr,i,t2)==')') break;
        }

        str1[0]=0;

        for (l=t1+1;l<t2;l++)
        {
          str1[l-t1-1]=bw_buff1.get_t3_winfile(p_wptr,i,l);
	  str1[l-t1]=0;
        }

        w_cre_ci_button(p_wptr,str1,SMG_SIZE,p6,p7,p8,i,str2,strlen(str2)+1);

	if (mn_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }
  }
/*
  mn_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.mn_ins);

  for (i=ptr3;i<=get_mn_h_w_ptr(p_wptr,5);i++)
  {
    set_mn_proc(i,(FARPROC)GetWindowLong(get_mn_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_mn_hnd(i),GWL_WNDPROC,(LPARAM)mn_tproc);
  }
*/
  return(0);
}

int bw_win::w_cre_win_edit(int p_wptr,int mark) // create edit ci
{
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
  int  i,j;
  int  ptr1;
  int  hptr1;
  char str2[FLD_NAME_SIZE];
  int  ini=0;

  mn_mark=mark;

  if (get_mn_ptr_fld_in_win(p_wptr,0)==0)
  {
    i=p_wptr-1;
    while ((get_mn_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_mn_ptr_fld_in_win(p_wptr,0,get_mn_ptr_fld_in_win(i,1)+1);
    ptr1=get_mn_ptr_fld_in_win(i,1);
  }
  else ptr1=get_mn_ptr_fld_in_win(p_wptr,0)-1;

  hptr1=mn_h_ci_total_ptr;

  for (i=0;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=0;j<COL_NUM;j++)  
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=0;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue; 

    state1=0;
    p4=0;
    p5=0;
    p6=0;
    if (ini==0)
    {
      p7=i;  //corner y
      p8=p1; //corner x
      ini=1;
    }

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_wptr,i,j)=='&')
      {
	if (p5==1)
	{
	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if ((str2[0]!='+')&&(str2[0]!='-'))
	  {
	  }
	  else
	  {
	    if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
	    {
	      w_cre_ci_edit(p_wptr,p6,p7,p8,i);

	      if (mn_h_ci_total_ptr>=HND_NUM) return(0);
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
	if (bw_buff1.get_t3_winfile(p_wptr,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_wptr,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if ((str2[0]!='+')&&(str2[0]!='-'))
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
		{
		  w_cre_ci_edit(p_wptr,p6,p7,p8,i);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
		}
	      }
	      p5=0;
	    }
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
	        if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
		{
		  w_cre_ci_edit(p_wptr,p6,p7,p8,i);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
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
          w_cre_ci_edit(p_wptr,p6,p7,p8,i);

	  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }

  }
/*
  mn_tproc=(FARPROC)MakeProcInstance((FARPROC)w_tab_ci_wp,bw_main1.mn_ins);

  for (i=hptr1;i<=get_mn_h_w_ptr(p_wptr,5);i++)
  {
    set_mn_proc(i,(FARPROC)GetWindowLong(get_mn_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_mn_hnd(i),GWL_WNDPROC,(LPARAM)mn_tproc);
  }
*/
  return(0);
}

int bw_win::w_cre_win_radio(int p_wptr,int mark) // create radio ci
{
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
  int  i,j;
  int  ptr1;
  int  hptr1;
  char str2[FLD_NAME_SIZE];
  int  ini=0;

  mn_mark=mark;

  if (get_mn_ptr_fld_in_win(p_wptr,0)==0)
  {
    i=p_wptr-1;
    while ((get_mn_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_mn_ptr_fld_in_win(p_wptr,0,get_mn_ptr_fld_in_win(i,1)+1);
    ptr1=get_mn_ptr_fld_in_win(i,1);
  }
  else ptr1=get_mn_ptr_fld_in_win(p_wptr,0)-1;

  hptr1=mn_h_ci_total_ptr;

  for (i=0;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=0;j<COL_NUM;j++)  
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=0;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue; 

    state1=0;
    p4=0;
    p5=0;
    p6=0;
    if (ini==0)
    {
      p7=i;  //corner
      p8=p1;
      ini=1;
    }

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_wptr,i,j)=='&')
      {
	if (p5==1)
	{
	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if (str2[0]!='(')
	  {
	  }
	  else
	  {
	    if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
	    {
		w_cre_ci_radio(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

		if (mn_h_ci_total_ptr>=HND_NUM) return(0);
	    }
	  }
	}

        ptr1++;
	p4=0;
	p5=1;      
        state1=1;  
	p6=j;    
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_wptr,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_wptr,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]!='(')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
		{
		  w_cre_ci_radio(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
		}
	      }
	      p5=0;
	    }
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
	        if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
		{
		  w_cre_ci_radio(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
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
          w_cre_ci_radio(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

	  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }

  }
/*
  mn_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.mn_ins);

  for (i=hptr1;i<=get_mn_h_w_ptr(p_wptr,5);i++)
  {
    set_mn_proc(i,(FARPROC)GetWindowLong(get_mn_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_mn_hnd(i),GWL_WNDPROC,(LPARAM)mn_tproc);
  }
*/
  return(0);
}

int bw_win::w_cre_win_check(int p_wptr,int mark) // create chkbox ci
{ 
  int  p1,p2,p4,p5,p6,p7,p8;
  int  state1;
  int  i,j;
  int  ptr1;
  int  hptr1;
  char str2[FLD_NAME_SIZE];
  int  ini=0;

  mn_mark=mark;

  if (get_mn_ptr_fld_in_win(p_wptr,0)==0)
  {
    i=p_wptr-1;
    while ((get_mn_ptr_fld_in_win(i,1)==0)&&(i>0))
    {
      i--;
    }
    set_mn_ptr_fld_in_win(p_wptr,0,get_mn_ptr_fld_in_win(i,1)+1);
    ptr1=get_mn_ptr_fld_in_win(i,1);
  }
  else ptr1=get_mn_ptr_fld_in_win(p_wptr,0)-1;

  hptr1=mn_h_ci_total_ptr;

  for (i=0;i<LIN_NUM;i++)
  {                                                                                       
    p1=COL_NUM-1;
    p2=0;
    for (j=0;j<COL_NUM;j++) 
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p1=j;
	break;
      }
    }
    for (j=COL_NUM-1;j>=0;j--)
    {
      if ((bw_buff1.get_t3_winfile(p_wptr,i,j)>' ')||(bw_buff1.get_t3_winfile(p_wptr,i,j)<0))
      {
	p2=j;
	break;
      }
    }
    if (p2<p1) continue; 

    state1=0;
    p4=0;
    p5=0;
    p6=0;
    if (ini==0)
    {
      p7=i;  // corner
      p8=p1;
      ini=1;
    }

    for (j=p1;j<=p2;j++) 
    {
      if (bw_buff1.get_t3_winfile(p_wptr,i,j)=='&')
      {
	if (p5==1)
	{
	  get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	  if (str2[0]!='[')
	  {
	  }
	  else
	  {
	    if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
	    {
	      w_cre_ci_check(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

	      if (mn_h_ci_total_ptr>=HND_NUM) return(0);
	    }
	  }
	}
      
        ptr1++;
	p4=0;      
	p5=1;     
        state1=1;  
	p6=j;
      }
      else
      {
	if (bw_buff1.get_t3_winfile(p_wptr,i,j)<=' ')
	{
	  state1=0;
	  if (bw_buff1.get_t3_winfile(p_wptr,i,j)!=' ')
	  {
	    if (p5==1)
	    {
	      get_t_fldname(ptr1,str2,FLD_NAME_SIZE);

	      if (str2[0]!='[')
	      {
	      }
	      else
	      {
	        if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
		{
		  w_cre_ci_check(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
		}
	      }
	      p5=0;
	    }
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
	        if (bw_inkey1.strempty(str2,FLD_NAME_SIZE)==1)
		{
		  w_cre_ci_check(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

		  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
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
          w_cre_ci_check(p_wptr,p6,p7,p8,i,str2,strlen(str2)+1);

	  if (mn_h_ci_total_ptr>=HND_NUM) return(0);
      }
    }

  }
/*
  mn_tproc=(FARPROC)MakeProcInstance((FARPROC)w_menu_ci_wp,bw_main1.mn_ins);

  for (i=hptr1;i<=get_mn_h_w_ptr(p_wptr,5);i++)
  {
    set_mn_proc(i,(FARPROC)GetWindowLong(get_mn_hnd(i),GWL_WNDPROC));
    SetWindowLong(get_mn_hnd(i),GWL_WNDPROC,(LPARAM)mn_tproc);
  }
*/
  return(0);
}

int bw_win::w_find_hnd(int p1,int p2,int p3)
{
  int  i,j;

  j=0;

  for (i=0;i<mn_h_ci_total_ptr;i++)
  {
    if ((get_mn_h_ci_ptr(i,0)==p1)&&
	(get_mn_h_ci_ptr(i,1)==p2)&&
	(get_mn_h_ci_ptr(i,2)==p3))
    {
      j=get_mn_h_ci_ptr(i,3);
      break;
    }
  }

  return(j);
}

int bw_win::w_find_winfname(int w,int l,int c,char *p_fld,int p_fld_size)
{
  int  i,j,k;
  char str2[FLD_NAME_SIZE];

  p_fld[0]=0;

  i=bw_buff1.get_t3_linecol(w,l,c);
  if (i>0)
  {
    get_t_fldname(i,str2,FLD_NAME_SIZE);

    if (FLD_NAME_SIZE>p_fld_size) k=p_fld_size;
    else k=FLD_NAME_SIZE;
    
    for (j=0;j<k-1;j++)
    {
      p_fld[j+0]=str2[j];
      p_fld[j+1]=0;
    }
  }

  return(0);
}

int bw_win::w_find_winflen(int w,int l,int c)
{
  int i;
  i=bw_buff1.get_t3_linecol(w,l,c);
  if (i>0) return(get_t_fldlen(i));
  return(0);
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

  //m=w;

  for (i=0;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=0;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(w,i,j)>0)
      {
	k=bw_buff1.get_t3_linecol(w,i,j);

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
  int  n3,n4;

  exist=0;
  s_tmpn1=get_pline(p1);
  s_tmpn2=get_pcolu(p1);
  m=p1;
  n3=s_tmpn1;
  n4=s_tmpn2;
  
  n4++;

  for (i=n3;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=n4;j<COL_NUM;j++)
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
    n4=0;
  }

  if (exist==0)
  {
    set_pline(p1,s_tmpn1);
    set_pcolu(p1,s_tmpn2);
  }
  else
  {
    exist=0;
    set_pline(p1,i);
    set_pcolu(p1,j);
  }

  return(exist);
}

int bw_win::w_next_afield(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;
  int s_tmpn3,s_tmpn4;

  exist=0;
  s_tmpn1=get_fld_l(p1);
  s_tmpn2=get_fld_c(p1);
  m=p1;
  s_tmpn3=s_tmpn1;
  s_tmpn4=s_tmpn2;
  
  s_tmpn4++;

  for (i=s_tmpn3;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=s_tmpn4;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(m,i,j)>0)
      {
        exist=1;
        break;
      }
    }
    if (exist==1) break;
    s_tmpn4=0;
  }

  if (exist==0)
  {
    set_fld_l(p1,s_tmpn1);
    set_fld_c(p1,s_tmpn2);
  }
  else
  {
    exist=0;
    set_fld_l(p1,i);
    set_fld_c(p1,j);
  }

  return(exist);
}

int bw_win::w_right_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;
  int n3,n4;

  exist=0;
  s_tmpn1=get_pline(p1);
  s_tmpn2=get_pcolu(p1);
  m=p1;
  n3=s_tmpn1;
  n4=s_tmpn2;
  
  n4++;

  for (i=n3;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=n4;j<COL_NUM;j++)
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
    n4=0;
  }

  if (exist==0)
  {
    set_pline(p1,s_tmpn1);
    set_pcolu(p1,s_tmpn2);
  }
  else
  {
    exist=0;
    set_pline(p1,i);
    set_pcolu(p1,j);
  }

  return(exist);
}

int bw_win::w_left_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;
  int n3,n4;

  exist=0;
  s_tmpn1=get_pline(p1);
  s_tmpn2=get_pcolu(p1);
  m=p1;
  n3=s_tmpn1;
  n4=s_tmpn2;
  
  n4--;
  if (n4<0)
  {
    n3--;
    if (n3<0) n3=0;
    n4=COL_NUM-1;
  }

  for (i=n3;i>=0;i--)
  {
    for (j=n4;j>=0;j--)
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
    n4=COL_NUM-1;
  }

  if (exist==0)
  {
    set_pline(p1,s_tmpn1);
    set_pcolu(p1,s_tmpn2);
  }
  else
  {
    exist=0;
    set_pline(p1,i);
    set_pcolu(p1,j);
  }

  return(exist);
}

int bw_win::w_up_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;
  int n3,n4;

  exist=0;
  s_tmpn1=get_pline(p1);
  s_tmpn2=get_pcolu(p1);
  n3=s_tmpn1;
  n4=s_tmpn2;
  
  n3--;
  if (n3<0) n3=0;
  m=p1;

  for (i=n3;i>=0;i--)
  {
    for (j=n4;j>=0;j--)
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
    set_pline(p1,s_tmpn1);
    set_pcolu(p1,s_tmpn2);
  }
  else
  {
    set_pline(p1,i);
    set_pcolu(p1,j);
  }

  return(0);
}

int bw_win::w_down_field(int p1)
{
  int i,j,m;
  int s_tmpn1,s_tmpn2;
  int exist;
  int n3,n4;

  exist=0;
  s_tmpn1=get_pline(p1);
  s_tmpn2=get_pcolu(p1);
  n3=s_tmpn1;
  n4=s_tmpn2;
  
  n3++;
  if (n3>=LIN_NUM) n3=LIN_NUM-1;
  m=p1;

  for (i=n3;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=n4;j>=0;j--)
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
    set_pline(p1,s_tmpn1);
    set_pcolu(p1,s_tmpn2);
  }
  else
  {
    set_pline(p1,i);
    set_pcolu(p1,j);
  }

  return(0);
}

int bw_win::w_field_type(char *p_str)
{
  if (p_str[0]=='&') return(0);  /* all field&var header */
  if (p_str[0]=='$') return(1);  /* sound */
  if (p_str[0]=='(') return(2);  /* (X)    ci */ // ci : control item
  if (p_str[0]=='[') return(3);  /* [X]    ci */ // ci : control item
  if (p_str[0]=='@') return(4);  /* button ci */ // ci : control item
  if (p_str[0]=='#') return(5);  /* bitmap */
  if (p_str[0]=='%') return(6);  /* ??? database field */  //???
  if (p_str[0]==':') return(7);  /* editable database field */
  if (p_str[0]=='?') return(8);  /* editable var ci      */
  if (p_str[0]=='+') return(9);  /* readonly database ci */ // ci : control item  
  if (p_str[0]=='-') return(10); /* readonly var ci      */ // ci : control item  
  return(0);
}

int bw_win::w_fetch_fld_style(char *tfn,int tfn_size,char *tn,int tn_size,int *tr,char *fn,int fn_size,int p_wptr)
{
  int  i,j,k,l;
  int  p1;
  int  n_ptr1[3][2];
  char s_fld[3][SMG_SIZE];

  i=strlen(tfn);
  j=0;
  l=0;
  for (k=0;k<=i;k++)  /* make tfn(table.field.recno.) position */
  {
    if (tfn[k]=='.')
    {
      n_ptr1[j][0]=l;
      n_ptr1[j][1]=k-1;
      if (k-1-l+1>=9) n_ptr1[j][1]=8+l;
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
	n_ptr1[j][0]=l;
	n_ptr1[j][1]=k-1;
	if (k-1-l+1>=9) n_ptr1[j][1]=8+l;
	break;
      }
    }
  }

  for (i=0;i<=j;i++)   /* make str */
  {
    for (k=n_ptr1[i][0];k<=n_ptr1[i][1];k++)
    {
      s_fld[i][k-n_ptr1[i][0]+0]=tfn[k];
      s_fld[i][k-n_ptr1[i][0]+1]=0;
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
      *tr=bw_inkey1.str2int(s_fld[0],SMG_SIZE);
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
      *tr=bw_inkey1.str2int(s_fld[0],SMG_SIZE);
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
      *tr=bw_inkey1.str2int(s_fld[1],SMG_SIZE);
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
      *tr=bw_inkey1.str2int(s_fld[0],SMG_SIZE);
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


int bw_win::w_find_base_name(char *p_tab,int p_tab_size,int p_wptr)
{
  int i,j;
  char str_tab[FN_SIZE];

  j=0;

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_tabname(1,i,str_tab,FN_SIZE);

    if ((get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(strcmp(str_tab,p_tab)==0))
    {
      j=1;
      break;
    }
  }

  return(j);
}

int bw_win::w_find_fld_name(char *p_fld,int p_fld_size,int p_wptr)
{
  int  i,j,k;
  char s_fn1[SMG_SIZE];

  k=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_mn_ptr_wins_dbf(i,p_wptr)==1)
    {
      for (j=bw_fldstru1.w_find_fldpntr0(i);j<bw_fldstru1.w_find_fldpntr1(i);j++)
      {
        bw_fldstru1.w_find_fldname(i,j,s_fn1,SMG_SIZE);
        if (strcmp(s_fn1,p_fld)==0)
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

  for (j=0;j<i;j++)
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
  char str_tab[FN_SIZE];

  if (bw_inkey1.strempty(p_fldtable,p_fldtable_size)==0) return(ptr1);

  k=0;

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_tabname(1,i,str_tab,FN_SIZE);

    if ((get_mn_ptr_wins_dbf(i,p_wptr)==1)&&(strcmp(p_fldtable,str_tab)==0))
    {
      k=1;
      break;
    }
  }

  if (k==1) return(i);
  
  return(ptr1);
}

int bw_win::w_fld_set_recno(int p_fldrecno,int ptr2)
{
  if (p_fldrecno!=0) return(0);
  return(ptr2);
}

int bw_win::w_fld_set_fld(char *p_fldname,int p_fldname_size)
{
  if (bw_inkey1.strempty(p_fldname,p_fldname_size)==0) return(1);
  return(0);
}

int bw_win::w_field_info2(int p_wptr)
{
  int  i,j,k,l,m,n;
  int  exist;
  int  ptr1;
  char s_fldtable[SMG_SIZE];
  char s_fldname[SMG_SIZE];
  int  n_fldrecno;
  int  n1;
  char str1[FLD_NAME_SIZE];
  char str2[FLD_NAME_SIZE];
  char str3[SMG_SIZE];
  char str4[SMG_SIZE];
  char str5[SMG_SIZE];
  char str6[SMG_SIZE];

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_mn_ptr_wins_dbf(i,p_wptr)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  ptr1=i;

  for (i=get_mn_ptr_fld_in_win(p_wptr,0);i<=get_mn_ptr_fld_in_win(p_wptr,1);i++)
  {
    set_t_fldbase(i,0);
    set_t_fldedt(i,0);
    set_t_fldseri(i,0);
  }
		      
  for (i=get_mn_ptr_fld_in_win(p_wptr,0);i<=get_mn_ptr_fld_in_win(p_wptr,1);i++)
  {
    set_t_fldseri_tmp(i,0);
  }
	
  for (i=0;i<LIN_NUM;i++)
  {
    for (j=0;j<COL_NUM;j++)
    {
      //m=p_wptr;
      if (bw_buff1.get_t3_linecol(p_wptr,i,j)>0)
      {
	s_fldtable[0]=0;  
	n_fldrecno=0;
	s_fldname[0]=0;

        n=bw_buff1.get_t3_linecol(p_wptr,i,j);

	get_t_fldname(n,str2,FLD_NAME_SIZE);
      
	if ((str2[0]==':')||(str2[0]=='%')||(str2[0]=='+')||(str2[0]=='-'))
	{
	  strcpy(str5,str2);
	  if ((str5[0]=='%')||(str5[0]=='-'))
	  {
	    str3[0]=str5[0];
            str3[1]=0;
	    n1=1; /* read field */
            bw_inkey1.cut_string(str5,1,strlen(str5)-1,SMG_SIZE,str6,SMG_SIZE);
          }
	  else
	  {
	    str3[0]=str5[0];
            str3[1]=0;
	    n1=0; /* edit field */
	    bw_inkey1.cut_string(str5,1,strlen(str5)-1,SMG_SIZE,str6,SMG_SIZE);
	  }

	  w_fetch_fld_style(str6,SMG_SIZE
			   ,s_fldtable,SMG_SIZE
			   ,&n_fldrecno
			   ,s_fldname,SMG_SIZE,p_wptr);

	  if ((bw_inkey1.strempty(s_fldname,SMG_SIZE)==0)&&(bw_inkey1.strempty(s_fldtable,SMG_SIZE)==0))
	  {
            strcpy(str4,str3);
	    strcat(str4,str6);
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

	  if (bw_inkey1.strempty(s_fldname,SMG_SIZE)==0)
	  {
	    continue;
          }

	  l=0;
	  for (k=bw_buff1.get_t3_linecol(p_wptr,i,j)-1;k>=get_mn_ptr_fld_in_win(p_wptr,0);k--)
	  {
	    get_t_field_tmp(k,str1,FLD_NAME_SIZE);
	    if ((strcmp(s_fldname,str1)==0)
	      &&(ptr1==get_t_fldbase(k))
	      &&(n_fldrecno==0))
	    {
	      l=1;
	      set_t_fldseri_tmp(k,get_t_fldseri_tmp(k)+1);
	      set_t_fldseri(n,get_t_fldseri_tmp(k));
	    }
	  }
	  if (l==1) set_c_t_field_tmp(bw_buff1.get_t3_linecol(p_wptr,i,j),0,0);
	  else 
	  {
	    set_t_field_tmp(bw_buff1.get_t3_linecol(p_wptr,i,j),s_fldname,strlen(s_fldname)+1);
	    set_t_fldseri_tmp(n,get_t_fldseri_tmp(n)+1);
	    set_t_fldseri(n,get_t_fldseri_tmp(n));
	  }

	  if (n1==1)
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

  for (i=0;i<LIN_NUM;i++)
  {
    for (j=0;j<COL_NUM;j++)
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

	  hnd=get_mn_hnd(q);

	  if (get_mn_ci_mode(p_wptr)==0)
          {
	    MoveWindow(hnd
			,(int)((j-get_mn_con(p_wptr,0))*bw_main1.mn_edit_xchar-3)
			,(int)((i-get_mn_con(p_wptr,1))*bw_main1.mn_edit_ychar-6)
			,(int)(p*bw_main1.mn_edit_xchar+6)
			,(int)(bw_main1.mn_edit_ychar+12)
			,FALSE);
	  }
          else
	  {
	    MoveWindow(hnd
			,(int)((j-get_mn_con(p_wptr,0))*bw_main1.mn_xchar-3)
			,(int)((i-get_mn_con(p_wptr,1))*bw_main1.mn_ychar-6)
			,(int)(p*bw_main1.mn_xchar+6)
			,(int)(bw_main1.mn_ychar+12)
			,FALSE);
	  }

	  SendMessage(hnd,EM_LIMITTEXT,o,(LPARAM)0);
	}

	if (str2[0]=='-')
        {
	  k=get_t_fldlen(n);

	  r=bw_dialog1.w_mv_seri(str2,FLD_NAME_SIZE,p_wptr);

	  o=bw_dialog1.get_mn_mv_type(r,2);

	  if (o>k) p=k;
	  else p=o;

	  if (p<3) p=3;

	  q=w_find_hnd(p_wptr,j,i);

	  hnd=get_mn_hnd(q);

	  if (get_mn_ci_mode(p_wptr)==0)
          {
	    MoveWindow(hnd
			,(int)((j-get_mn_con(p_wptr,0))*bw_main1.mn_edit_xchar-3)
			,(int)((i-get_mn_con(p_wptr,1))*bw_main1.mn_edit_ychar-6)
			,(int)(p*bw_main1.mn_edit_xchar+6)
			,(int)(bw_main1.mn_edit_ychar+12)
			,FALSE);
	  }
          else
	  {
	    MoveWindow(hnd
			,(int)((j-get_mn_con(p_wptr,0))*bw_main1.mn_xchar-3)
			,(int)((i-get_mn_con(p_wptr,1))*bw_main1.mn_ychar-6)
			,(int)(p*bw_main1.mn_xchar+6)
			,(int)(bw_main1.mn_ychar+12)
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

  for (i=0;i<ln;i++) /* find first screen field */
  {
    for (j=0;j<COL_NUM;j++)
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
  char str[SMG_SIZE];
  int  i;

  bw_getread1.deb_record("bw_win::tst_hptr3()");

  for (i=0;i<WIN_NUM;i++)
  {
    sprintf(str,"ptr=%d,hptr30123456=%d,%d,%d,%d,%d,%d,%d,"
			      ,i
                             ,get_mn_h_w_ptr(i,0)
			      ,get_mn_h_w_ptr(i,1)
			      ,get_mn_h_w_ptr(i,2)
			      ,get_mn_h_w_ptr(i,3)
			      ,get_mn_h_w_ptr(i,4)
			      ,get_mn_h_w_ptr(i,5)
			      ,get_mn_h_w_ptr(i,6)
			      );

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_win::tst_hptr4()
{
  char str[SMG_SIZE];
  int  i;

  bw_getread1.deb_record("bw_win::tst_hptr4()");

  for (i=0;i<60;i++)
  {
    sprintf(str,"ptr=%d,hptr401234=%d,%d,%d,%d,%d,"
			      ,i
                             ,get_mn_h_ci_ptr(i,0)
			      ,get_mn_h_ci_ptr(i,1)
			      ,get_mn_h_ci_ptr(i,2)
			      ,get_mn_h_ci_ptr(i,3)
			      ,get_mn_h_ci_ptr(i,4));

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_win::w_atten1(HWND hwnd,char *p_fn1)
{
  char str1[256];
  char str2[256];

  strcpy(str2,"打开资料错误,资料名:");
  strcat(str2,p_fn1);

  strcpy(str1,"Error when open file,file name:");
  strcat(str1,p_fn1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,str1,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,str2,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten2(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error in table structure.","ERROR MESSGAE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"表格结构错误","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten3(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Windows too much.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"窗口数量太多","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten4(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Screen format define error,table name need ','.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义表格名时,没有','号."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten5(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Screen format define error,structure name too long.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义表格名时,结构名太长."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten6(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Screen format define error,need structure name.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义表格名时,结构名没有."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten7(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error when insert record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"插入数据时错误"
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten7b(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error when add record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"追加数据时错误"
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten7a(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error when delete record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"删除数据时错误"
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten8(HWND hwnd,char *s1)
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

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OKCANCEL|MB_ICONQUESTION);
  else i=MessageBox(hwnd
            ,s2 
	    ,"错误信息",MB_OKCANCEL|MB_ICONQUESTION);

  if (i==IDOK) return(1);
  else return(0);
}
int bw_win::w_atten9(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"是否保存资料,资料名:");
  strcat(s2,s1);

  strcpy(s3,"If to save file,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd
            ,s2 
	    ,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);  
  else return(2);
}
int bw_win::w_atten9a(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"数据库资料不存在,是否建立,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Database file don't exist,if to create:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd
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
int bw_win::w_atten10(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"const LINK_CHAR too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"常量LINK_CHAR太小.","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten11(HWND hwnd)
{      
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"const mn_VAR_NUM too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"常量mn_VAR_NUM太小."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten12(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"const VAR_IN_SCRN too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"常量VAR_IN_SCRN太小."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten13(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"不认识的数据库名:");
  strcat(s2,s1);
  
  strcpy(s3,"Unknow database name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten14(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"不认识的字段名:");
  strcat(s2,s1);

  strcpy(s3,"Unknow field name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten15(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"打开资料错误,资料忙:");
  strcat(s2,s1);

  strcpy(s3,"Error when open file,file is busy:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"ERROR MESSAGE",MB_RETRYCANCEL|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"错误信息",MB_RETRYCANCEL|MB_ICONQUESTION);

  if (i==IDRETRY) return(1);
  else return(0);
}
int bw_win::w_atten16(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"XBASE数据库资料不存在,是否建立:");
  strcat(s2,s1);

  strcpy(s3,"XBASE file does not exist,if to create:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"ERROR MESSAGE",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"错误信息",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(2);
  else return(1);
}
int bw_win::w_atten17(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"建立XBASE数据库资料出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when create XBASE file:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten18(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"XBASE数据库资料结构不同,是否更新结构?:");
  strcat(s2,s1);

  strcpy(s3,"The structure of XBASE file is not same,update?");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"ERROR MESSAGE",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"错误信息",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten19(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"字符串没找到:");
  strcat(s2,s1);

  strcpy(s3,"String not find:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
} 
int bw_win::w_atten20(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"是否替换:");
  strcat(s2,s1);

  strcpy(s3,"If to replace?:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten21(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Too much edit windows.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"编辑窗口太多","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten22(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Database buffer number is too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"库缓冲区不够","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten23(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"资料存在,是否复盖:");
  strcat(s2,s1);

  strcpy(s3,"The file is exist,recover it?:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten24(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"拷备资料时出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when copy file:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten25(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"资料名错误:");
  strcat(s2,s1);

  strcpy(s3,"There is error in file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten26(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"目录不存在:");
  strcat(s2,s1);

  strcpy(s3,"Directory is not exist:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten27(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"目录已存在:");
  strcat(s2,s1);

  strcpy(s3,"Directory is already exist:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten28(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"拷备目录时错误,目标目录:");
  strcat(s2,s1);

  strcpy(s3,"Error when copy directory,aim directory:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"EEROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten29(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"同名资料存在,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Exist same name file,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten30(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"建立目录时错误,目录名:");
  strcat(s2,s1);

  strcpy(s3,"Error when create directory,name is:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(1);
}
int bw_win::w_atten31(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"是否真的删除?,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Do you want to delete file?:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"请选择",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(2);
}
int bw_win::w_atten32(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"删除资料时出错,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Error when delete file,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten33(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"删除目录时出错,目录名:");
  strcat(s2,s1);

  strcpy(s3,"Error when delete directory,directory name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten34(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"换名资料已存在,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Aim file already exist,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten35(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"换名时出错,资料名:");
  strcat(s2,s1);

  strcpy(s3,"Error when rename file,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten36(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"菜单定义错误,资料名:");
  strcat(s2,s1);

  strcpy(s3,"There is error in menu define,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten37(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"多重选择定义错误,资料名:");
  strcat(s2,s1);

  strcpy(s3,"There is error in radio button define,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten38(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"对话框定义错误,资料名:");
  strcat(s2,s1);

  strcpy(s3,"There is error in dialog box define,file name:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"错误信息",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten39(HWND hwnd)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"情换页!");
  strcpy(s3,"Next page please.");

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNOCANCEL|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"信息显示",MB_YESNOCANCEL|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else
  {
    if (i==IDCANCEL) return(2);
    else return(0);
  }
}
int bw_win::w_atten40(HWND hwnd)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"打印机没连上!");
  strcpy(s3,"Printer is not online.");

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"ERROR MESSAGE",MB_RETRYCANCEL|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"错误信息",MB_RETRYCANCEL|MB_ICONQUESTION);

  if (i==IDRETRY) return(1);
  else return(2);
}
int bw_win::w_atten41(HWND hwnd)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"'是(Yes)'新记录插入当前记录前面,'否(No)'插入后面");
  strcpy(s3,"(Yes) to insert defore,(No) to insert after.");

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"信息显示",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(0);
}
int bw_win::w_atten42(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Only support XBASE,please choose database type.","INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"本软体目前只支持XBASE,请选数据库类型.","信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten43(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Please clear if to backup database defore open it.","INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"打开数据库前请规定是否备份。","信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten44(HWND hwnd)
{
  char s1[256];
  char s2[11];
  char s3[256];

  strcpy(s1,"打开数据库前请先规定工作区号,不能大于");
  sprintf(s2,"%d",STRU_NUM);
  strcat(s1,s2);

  strcpy(s3,"Please clear buffer number before open database,can not bigger than:");
  strcat(s3,s2);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s1,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten45(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"目录不存在：");
  strcat(s2,s1);

  strcpy(s3,"Directory do not exist:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten46(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"XBASE资料名不正确:");
  strcat(s2,s1);

  strcpy(s3,"The name of XBASE file is not correct:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten47(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"打开XBASE数据库结构资料出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when open structure define file of XBASE file:");
  strcat(s3,s1); 

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten48(HWND hwnd,char *s1)
{
  char s2[256];
  char s3[256];

  strcpy(s2,"打开XBASE数据库出错:");
  strcat(s2,s1);

  strcpy(s3,"Error when open XBASE file:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) MessageBox(hwnd,s3,"INFORMATION BOX",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,s2,"信息提示",MB_OK|MB_ICONASTERISK);

  return(0);
}
int bw_win::w_atten49(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"There are not so much records.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"数据库中没有这么多记录!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten50(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Record number can not little then zero.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"记录号不能为零或负!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten51(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error when read database record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"读数据库记录出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten52(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Record number is not correct,can not delete record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"记录号不正确，删除记录出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten53(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Record number is not correct,can not locate record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"记录号不正确，定位出错,请规定记录号!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten54(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Record number is not correct,can not display record.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"记录号不正确，显示记录出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten55(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error when commit data.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"数据库提交出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten56(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Error when rollback data.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"数据库滚回出错!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten57(HWND hwnd,int l)
{
  char str1[81];
  char str2[256];
  char str3[256];

  sprintf(str1,"%d!",l);
  strcpy(str2,"工作区没有数据库打开!,工作区号：");
  strcat(str2,str1);

  strcpy(str3,"There is not base opened in this buffer,buffer number:");
  strcat(str3,str1);


  if (bw_main1.mn_lang==1) MessageBox(hwnd,str3,"ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,str2,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten58(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"There is not enough data buffer.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"没有足够的数据区分配!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten59(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"There is error in screen format,type name is too long.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义库类型时,类型名太长."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten60(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"There is error in screen format,lack type name.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义库类型时,类型名没有."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten61(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"There is error in screen format,backup type name is too long.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义备份类型时,备份类型名太长."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten62(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"There is error int screen format,lack backup type name.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"屏幕格式错误,定义备份类型时,备份类型名没有."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten63(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Data buffer is already in use.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"数据区已被分配!","错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten64(HWND hwnd,char *s1)
{
  int  i;
  char s2[256];
  char s3[256];

  strcpy(s2,"'是(Yes)'保存修改过的资料,'否(No)'放弃修改.资料名:");
  strcat(s2,s1);
  strcpy(s3,"(Yes) to save text which is changed,(No) to exit without save.the name of the file:");
  strcat(s3,s1);

  if (bw_main1.mn_lang==1) i=MessageBox(hwnd,s3,"INFORMATION BOX",MB_YESNO|MB_ICONQUESTION);
  else i=MessageBox(hwnd,s2,"信息显示",MB_YESNO|MB_ICONQUESTION);

  if (i==IDYES) return(1);
  else return(0);
}
int bw_win::w_atten65(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"The change in text can not be undo.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"不能恢复对资料的修改."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten66(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"You must answer 'save or not' messagebox.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"必需回答'是否存盘对话框'."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten67(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"Sub windows too much.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"子窗口太多."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}
int bw_win::w_atten68(HWND hwnd)
{
  if (bw_main1.mn_lang==1) MessageBox(hwnd,"const VAL_NUM too small.","ERROR MESSAGE",MB_OK|MB_ICONASTERISK);
  else MessageBox(hwnd,"常量VAL_NUM太小."
	    ,"错误信息",MB_OK|MB_ICONASTERISK);
  return(0);
}





int bw_win::get_mn_timer(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_timer[p_wptr]);
}
int bw_win::set_mn_timer(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_timer[p_wptr]=val;
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

int bw_win::get_mn_state_link_modi(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_state_link_modi[p_wptr]);
}
int bw_win::set_mn_state_link_modi(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_state_link_modi[p_wptr]=val;
  return(0);
}
int bw_win::get_mn_state_calc_modi(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_state_calc_modi[p_wptr]);
}
int bw_win::set_mn_state_calc_modi(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_state_calc_modi[p_wptr]=val;
  return(0);
}
int bw_win::get_mn_switch_bmp(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_switch_bmp[p_wptr]);
}
int bw_win::set_mn_switch_bmp(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_switch_bmp[p_wptr]=val;
  return(0);
}

int bw_win::get_mn_ptr_fld_in_win(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>3)) return(0);
  return(mn_ptr_fld_in_win[p_wptr][ptr]);
}
int bw_win::set_mn_ptr_fld_in_win(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>3)) return(0);
  mn_ptr_fld_in_win[p_wptr][ptr]=val;
  return(0);
}
int bw_win::get_mn_h_w_ptr(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>8)) return(0);
  return(mn_h_w_ptr[p_wptr][ptr]);
}
int bw_win::set_mn_h_w_ptr(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>8)) return(0);
  mn_h_w_ptr[p_wptr][ptr]=val;
  return(0);
}
HWND bw_win::get_mn_phh(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_phh[p_wptr]);
}

int bw_win::set_mn_phh(int p_wptr,HWND hwnd)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_phh[p_wptr]=hwnd;
  return(0);
}

int bw_win::get_ms_tabname(int p1,int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p1<0)||(p1>1)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_tabname[p1][p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_win::set_ms_tabname(int p1,int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p1<0)||(p1>1)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  ms_tabname[p1][p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_tabname[p1][p_dbptr][j+0]=p_s1[j];
    ms_tabname[p1][p_dbptr][j+1]=0;
  }

  return(0);
}

int bw_win::get_mn_ptr_grp_id(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_ptr_grp_id[p_wptr]);
}
int bw_win::set_mn_ptr_grp_id(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_ptr_grp_id[p_wptr]=val;
  return(0);
}


int bw_win::get_mn_msgboxlock(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_msgboxlock[p_wptr]);
}
int bw_win::set_mn_msgboxlock(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_msgboxlock[p_wptr]=val;
  return(0);
}

int bw_win::get_mn_ptr_wins_dbf(int p_dbptr,int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_ptr_wins_dbf[p_dbptr][p_wptr]);
}
int bw_win::set_mn_ptr_wins_dbf(int p_dbptr,int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_ptr_wins_dbf[p_dbptr][p_wptr]=val;
  return(0);
}
int bw_win::get_mn_con(int p_wptr,int p03)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(mn_con[p_wptr][p03]);
}
int bw_win::set_mn_con(int p_wptr,int p03,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  mn_con[p_wptr][p03]=val;
  return(0);
}
int bw_win::get_mn_style(int p_wptr,int ptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>=WIN_STYLE_NUM)) return(0);
  return(mn_style[p_wptr][ptr]);
}
int bw_win::set_mn_style(int p_wptr,int ptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr<0)||(ptr>=WIN_STYLE_NUM)) return(0);
  mn_style[p_wptr][ptr]=val;
  return(0);
}
FARPROC bw_win::get_mn_proc(int ptr)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  return(mn_proc[ptr]);
}  
int bw_win::set_mn_proc(int ptr,FARPROC fproc)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  mn_proc[ptr]=fproc;
  return(0);
}
HWND bw_win::get_mn_hnd(int ptr)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  return(mn_hnd[ptr]);
}
int bw_win::set_mn_hnd(int ptr,HWND hnd)
{
  if ((ptr<0)||(ptr>=HND_NUM)) return(0);
  mn_hnd[ptr]=hnd;
  return(0);
}
int bw_win::get_mn_h_ci_ptr(int hptr,int p04)
{
  if ((hptr<0)||(hptr>=HND_NUM)) return(0);
  if ((p04<0)||(p04>4)) return(0);
  return(mn_h_ci_ptr[hptr][p04]);
}
int bw_win::set_mn_h_ci_ptr(int hptr,int p04,int val)
{
  if ((hptr<0)||(hptr>=HND_NUM)) return(0);
  if ((p04<0)||(p04>4)) return(0);
  mn_h_ci_ptr[hptr][p04]=val;
  return(0);
}
int bw_win::get_mn_ptr_get_rd(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_ptr_get_rd[p_wptr]);
}
int bw_win::set_mn_ptr_get_rd(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_ptr_get_rd[p_wptr]=val;
  return(0);
}
int bw_win::get_mn_create_menu(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_create_menu[p_wptr]);
}
int bw_win::set_mn_create_menu(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_create_menu[p_wptr]=val;
  return(0);
}
int bw_win::get_mn_linep(int p_wptr,int p01)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(mn_linep[p_wptr][p01]);
}
int bw_win::set_mn_linep(int p_wptr,int p01,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  mn_linep[p_wptr][p01]=val;
  return(0);
}
int bw_win::get_ms_window_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_window_name[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_win::set_ms_window_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  ms_window_name[p_wptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_window_name[p_wptr][j+0]=p_s1[j];
    ms_window_name[p_wptr][j+1]=0;
  }

  return(0);
}
int bw_win::get_ms_find_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_find_name[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_win::set_ms_find_name(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  ms_find_name[p_wptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_find_name[p_wptr][j+0]=p_s1[j];
    ms_find_name[p_wptr][j+1]=0;
  }

  return(0);
}
int bw_win::get_mn_is_link(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_is_link[p_wptr]);
}
int bw_win::set_mn_is_link(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_is_link[p_wptr]=val;
  return(0);
}
int bw_win::get_mn_is_calc(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_is_calc[p_wptr]);
}
int bw_win::set_mn_is_calc(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_is_calc[p_wptr]=val;
  return(0);
}
int bw_win::get_mn_memo_basep(int p_wptr)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_memo_basep[p_wptr]);
}
int bw_win::set_mn_memo_basep(int p_wptr,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_memo_basep[p_wptr]=val;
  return(0);
}





int bw_win::get_mn_ci_mode(int p_wptr)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_ci_mode[p_wptr]);
}
int bw_win::set_mn_ci_mode(int p_wptr,int val)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  mn_ci_mode[p_wptr]=val;
  return(0);
}

int bw_win::get_mn_ci_posi(int p_wptr,int p01)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1))       return(0);
  return(mn_ci_posi[p_wptr][p01]);
}
int bw_win::set_mn_ci_posi(int p_wptr,int p01,int val)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1))       return(0);
  mn_ci_posi[p_wptr][p01]=val;
  return(0);
}

int bw_win::get_mn_focus_buf(int ptr)
{
  if ((ptr<0)||(ptr>=BW_WIN_FOCUS_NUM)) return(0);
  return(mn_focus_buf[ptr]);
}

int bw_win::set_mn_focus_buf(int ptr,int val)
{
  if ((ptr<0)||(ptr>=BW_WIN_FOCUS_NUM)) return(0);
  mn_focus_buf[ptr]=val;
  return(0);
}

int bw_win::get_mn_created(int ptr)
{
  if ((ptr<0)||(ptr>=WIN_NUM)) return(0);
  return(mn_created[ptr]);
}

int bw_win::set_mn_created(int ptr,int val)
{
  if ((ptr<0)||(ptr>=WIN_NUM)) return(0);
  mn_created[ptr]=val;
  return(0);
}

int bw_win::get_mn_painted(int ptr)
{
  if ((ptr<0)||(ptr>=WIN_NUM)) return(0);
  return(mn_painted[ptr]);
}

int bw_win::set_mn_painted(int ptr,int val)
{
  if ((ptr<0)||(ptr>=WIN_NUM)) return(0);
  mn_painted[ptr]=val;
  return(0);
}

int bw_win::get_mn_focused(int ptr)
{
  if ((ptr<0)||(ptr>=WIN_NUM)) return(0);
  return(mn_focused[ptr]);
}

int bw_win::set_mn_focused(int ptr,int val)
{
  if ((ptr<0)||(ptr>=WIN_NUM)) return(0);
  mn_focused[ptr]=val;
  return(0);
}

int bw_win::get_mn_focused_wp(int ptr)
{
    if ((ptr < 0) || (ptr >= WIN_NUM)) return(0);
    return(mn_focused_wp[ptr]);
}

int bw_win::set_mn_focused_wp(int ptr, int val)
{
    if ((ptr < 0) || (ptr >= WIN_NUM)) return(0);
    mn_focused_wp[ptr] = val;
    return(0);
}

int bw_win::get_pline(int wptr)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  return(pline[wptr]);
}
int bw_win::get_pcolu(int wptr)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  return(pcolu[wptr]);
}
int bw_win::set_pline(int wptr,int val)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  pline[wptr]=val;
  return(0);
}
int bw_win::set_pcolu(int wptr,int val)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  pcolu[wptr]=val;
  return(0);
}

int bw_win::get_fld_l(int wptr)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  return(fld_l[wptr]);
}
int bw_win::get_fld_c(int wptr)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  return(fld_c[wptr]);
}
int bw_win::set_fld_l(int wptr,int val)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  fld_l[wptr]=val;
  return(0);
}
int bw_win::set_fld_c(int wptr,int val)
{
  if ((wptr<0)||(wptr>=WIN_NUM)) return(0);
  fld_c[wptr]=val;
  return(0);
}

