
/* error 1: WM_CREATE should have return() */

/* error 2: att to this func(char *s); s[n]=NULL;func(""); */
 
#define   STRICT
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

extern class bw_main_bua     bw_main_bua1;
extern class bw_fldstru_bua  bw_fldstru_bua1;
extern class bw_menuvar_bua  bw_menuvar_bua1;
extern class bw_switch_bua   bw_switch_bua1;
extern class bw_switch_bua   bw_switch_bua1;
extern class bw_dialog_bua   bw_dialog_bua1;
extern class bw_get_bua      bw_get_bua1;
extern class bw_xbase_bua    bw_xbase_bua1;
extern class bw_win_bub      bw_win_bub1;
extern class bw_win_bua      bw_win_bua1;
extern class bw_buff         bw_buff1;
extern class bw_font         bw_font1;
extern class bw_user         bw_user1;
extern class bw_bmp          bw_bmp1;
extern class bw_print        bw_print1;
extern class bw_link         bw_link1;
extern class bw_edit         bw_edit1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_main         bw_main1;
extern class bw_dialog       bw_dialog1;
extern class bw_switch       bw_switch1;
extern class bw_choose       bw_choose1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;
extern class bw_getread      bw_getread1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_menuvar      bw_menuvar1;

extern long FAR PASCAL w_bmp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long FAR PASCAL w_main_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long FAR PASCAL w_menu_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long FAR PASCAL w_edit_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long FAR PASCAL w_savep_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long FAR PASCAL w_outp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long FAR PASCAL w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long FAR PASCAL w_menu2_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long FAR PASCAL w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);

long FAR PASCAL w_menu_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
  HCURSOR hcursor;
//  HDC     hdc;
//  RECT    rt;
  HWND    hnd;
//  int     state1;  
  int     i,j,k,l,m,n,o,p,q;
  char    str[SMG_LEN];
//  char    str2[SMG_LEN];
  char    str3[SMG_LEN];
  char    fldname[SMG_LEN];
  char    fldvar[SMG_LEN];
//  long    recno;
  long    li;
  char    s_fn1[FN_SIZE];
  char    sf1[SMG_LEN];

  bw_main1.win_msg=msg;
  bw_main1.win_wp=wp;
  bw_main1.win_hwnd=hwnd;
  bw_main1.win_lp=lp;

  switch(msg)    
  {
    case WM_CREATE:
    {
      bw_win1.w_echo_win_cr(bw_main1.win_hnd_id,1);

      bw_win1.w_find_edit_field(bw_main1.win_hnd_id);

      bw_win1.w_set_winafedit(bw_main1.win_hnd_id);

      bw_link1.w_scan_svar(bw_main1.win_hnd_id);   /* fetch screen var posi  */

      j=bw_win_bua1.get_win_con(bw_main1.win_hnd_id,2);

      if (bw_win_bua1.get_win_create_menu(bw_main1.win_hnd_id)>0)
      {
	if (bw_win_bua1.get_win_create_menu(bw_main1.win_hnd_id)==1) i=bw_main1.win_ychar;
	if (bw_win_bua1.get_win_create_menu(bw_main1.win_hnd_id)==2)
	{
	  if (j<50) i=bw_main1.win_ychar*2;
	  else i=bw_main1.win_ychar;
        }
	if (bw_win_bua1.get_win_create_menu(bw_main1.win_hnd_id)==3)
	{
	  if (j<60) i=bw_main1.win_ychar*2;
	  else i=bw_main1.win_ychar;
        }
	bw_win_bua1.set_win_create_menu(bw_main1.win_hnd_id,0);
      }
      else i=0;

      if (bw_main1.win_lang==1) i=i+10;

      if (bw_win_bua1.get_win_ci_mode(bw_main1.win_hnd_id)==0)
      {
	MoveWindow(hwnd
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,0)*bw_main1.win_edit_xchar)
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,1)*bw_main1.win_edit_ychar)
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,2)*bw_main1.win_edit_xchar)
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,3)*bw_main1.win_edit_ychar+i)
		,FALSE);
      }
      else
      {
        MoveWindow(hwnd
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,0)*bw_main1.win_xchar)
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,1)*bw_main1.win_ychar)
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,2)*bw_main1.win_xchar)
		,(int)(bw_win_bua1.get_win_con(bw_main1.win_hnd_id,3)*bw_main1.win_ychar+i)
		,FALSE);
      }

      /* notice set dir */
      bw_win_bub1.get_win_window_name(bw_main1.win_hnd_id,s_fn1,FN_SIZE);
      k=bw_link1.w_read_link(s_fn1,FN_SIZE,bw_main1.win_hnd_id,bw_main1.win_hnd_id-bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(bw_main1.win_hnd_id),1)+1);
      l=0;

      if (k==0)
      {
	k=bw_link1.w_link_modi(bw_main1.win_hnd_id);  /* fetch link var in cond & link var if modi */
        if (k!=0) l=1;
      }
      else l=1;

      if (l==0)
      {
	bw_win_bua1.set_win_is_link(bw_main1.win_hnd_id,1);
      }

      if (bw_win_bua1.get_win_style(bw_main1.win_hnd_id,2)==1) bw_win1.w_echo_win_radio(bw_main1.win_hnd_id,1);

      if (bw_win_bua1.get_win_style(bw_main1.win_hnd_id,3)==1) bw_win1.w_echo_win_chs(bw_main1.win_hnd_id,1);

      if (bw_win_bua1.get_win_style(bw_main1.win_hnd_id,9)==1) bw_win1.w_echo_win_edit(bw_main1.win_hnd_id,1);

      bw_win1.w_just_edit(bw_main1.win_hnd_id);

      bw_win_bua1.set_win_pp11(bw_main1.win_hnd_id,bw_getread1.get_read_login());

      bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,1);
      bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,2);

      bw_win1.pline=1;
      bw_win1.pfield=2;

      li=bw_win_bua1.get_win_timer(bw_main1.win_hnd_id);
      if (li>0)
      {
	SetTimer(hwnd,1,li,NULL);
      }

      break;
    }
    case WM_TIMER:
    {



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);

      if (bw_win_bua1.get_win_switch_bmp(bw_main1.win_hnd_id)==1)
      {
        i=bw_win1.pline;
        j=bw_win1.pfield;

	bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	bw_main1.w_set_focus_timer(hwnd);

        bw_win1.pline=i;
	bw_win1.pfield=j;
      }

      break;
    }
    case WM_SETFOCUS:
    {



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      if (GetFocus()==hwnd)
      {
	CreateCaret(hwnd,NULL,NULL,(int)bw_main1.win_edit_ychar);
	ShowCaret(hwnd);
      }

      break;
    }
    case WM_PAINT:



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      if (wp==0)
      {
	bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);

	bw_win1.w_echo_win_pa(bw_main1.win_hnd_id,1);

	bw_choose1.w_echo_winrec_chs(bw_main1.win_hnd_id);

	bw_switch1.w_echo_winrec_radio(bw_main1.win_hnd_id);

	bw_dialog1.w_echo_winrec_var(bw_main1.win_hnd_id);

        if (bw_xbase1.win_answer==0)
        {
	  bw_fldstru1.w_echo_winrec(bw_main1.win_hnd_id);

	  if (bw_win_bua1.get_win_is_link(bw_main1.win_hnd_id)==1)
          {
	    bw_link1.w_link_modi_mark(bw_main1.win_hnd_id,-1,-1,-1); /* echo win rec ,link rec should change */

	    bw_link1.w_echo_winrec_lnk(bw_main1.win_hnd_id);
	  }
        }

	if (bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0)<=0)
	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,1);

	if (bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1)<=0)
	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,2);

	bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1)-1);

	bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	bw_win1.w_next_field(bw_main1.win_hnd_id);

	bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

	i=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
	if (i>0) j=bw_win_bua1.get_1fldbase(i);
	else j=0;

	bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

	bw_dialog1.w_echo_winrec_read(j,bw_main1.win_hnd_id,11);

//      first field name and first position
//	hdc=GetDC(win_hwnd);
//	sprintf(str2,"%d,%d,%s,",bw_win1.pline,bw_win1.pfield,str);
//	TextOut(hdc,1,1,str2,strlen(str2));
//	ReleaseDC(win_hwnd,hdc);

	if (str[0]=='?') bw_dialog1.w_mv_get_read_paint(str,SMG_LEN,bw_main1.win_hnd_id,'g');
	else
        {
	  if (str[0]==':')
	  {
            if (bw_xbase1.win_answer==0)
            {
	      bw_mbase1.w_down_rec(j,bw_main1.win_hnd_id,bw_xbase_bua1.get_win_recno(j,bw_main1.win_hnd_id,0)-1);
	      bw_fldstru1.w_tv_get_read_paint(str,SMG_LEN,bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,'g');
            }
	  }

        }
      }

      break;

    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      if (bw_main1.win_key>=10000)
      {
	bw_main1.win_key=bw_main1.win_key-10000;
	i=1;
      }
      else
      {
	if (bw_main1.win_key>=5000)
        {
	  bw_main1.win_key=bw_main1.win_key-5000;
	  i=1;
	}
	else i=bw_inkey1.inkey();
      }

      if (i==1)
      {
	bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);

	bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

	if (str[0]=='@')
	{
	  bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	  bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	  j=bw_win1.pline;
          k=bw_win1.pfield;

	  i=bw_win1.w_find_hnd(bw_main1.win_hnd_id,k,j);
	  InvalidateRect(bw_win_bua1.get_win_hnd(i),NULL,TRUE);
          
	  if (bw_main1.win_key==401)
	  {
	    bw_win1.pline =bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,2);
	    bw_win1.pfield=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,1);
          }
	  if (bw_main1.win_key==274) bw_win1.w_up_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==275) bw_win1.w_down_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==276) bw_win1.w_left_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==277) bw_win1.w_right_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==32)
	  {
	    bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);
	    bw_win1.win_menu_cmd=str[0]-'a'+1;
	  }
	  if ((bw_main1.win_key==401)||(bw_main1.win_key==32))
	  {
	    bw_main1.w_set_lbutt(hwnd,bw_main1.win_hnd_id);
	    if ((bw_menuvar1.t5_m_pp2==14)||(bw_menuvar1.t5_m_pp2==15))
	    {
	      bw_menuvar1.t5_m_pp2=0;
	      return(0);
            }
	  }
	  if (bw_main1.win_key==27)
	  {
	    bw_fldstru1.w_find_exit(bw_main1.win_hnd_id);
	    bw_win1.w_close_win(bw_main1.win_hnd_id);
            return(0);
	  }

          bw_main1.w_set_focus(hwnd);

	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

/*	  return(0);*/
	}
	if (str[0]=='[')
	{
	  bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	  bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	  j=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);

	  SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETSTATE,0,(LPARAM)str);

	  if (bw_main1.win_key==401)
	  {
	    bw_win1.pline =bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,2);
	    bw_win1.pfield=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,1);
          }
	  if (bw_main1.win_key==274) bw_win1.w_up_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==275) bw_win1.w_down_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==276) bw_win1.w_left_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==277) bw_win1.w_right_field(bw_main1.win_hnd_id);
	  if ((bw_main1.win_key==32)||(bw_main1.win_key==401))
	  {
	    bw_main1.w_set_lbutt(hwnd,bw_main1.win_hnd_id);
	    if ((bw_menuvar1.t5_m_pp2==14)||(bw_menuvar1.t5_m_pp2==15))
	    {
	      bw_menuvar1.t5_m_pp2=0;
	      return(0);
            }
	  }
	  if (bw_main1.win_key==CTRL_E)
	  {
	    bw_choose1.w_clr_recvar_chs(bw_main1.win_hnd_id);
	    bw_choose1.w_echo_winrec_chs(bw_main1.win_hnd_id);
	    return(0);
	  }
	  if (bw_main1.win_key==ESC_KEY)
	  {
	    bw_fldstru1.w_find_exit(bw_main1.win_hnd_id);
	    bw_win1.w_close_win(bw_main1.win_hnd_id);
	    return(0);
	  }

          bw_main1.w_set_focus(hwnd);

	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

/*          return(0);*/
        }
	if (str[0]=='(')
	{
	  bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	  bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	  j=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);

	  SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETSTATE,0,(LPARAM)str);

	  if (bw_main1.win_key==401)
	  {
	    bw_win1.pline =bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,2);
	    bw_win1.pfield=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,1);
          }
	  if (bw_main1.win_key==274) bw_win1.w_up_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==275) bw_win1.w_down_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==276) bw_win1.w_left_field(bw_main1.win_hnd_id);
	  if (bw_main1.win_key==277) bw_win1.w_right_field(bw_main1.win_hnd_id);
	  if ((bw_main1.win_key==32)||(bw_main1.win_key==401))
	  {
	    bw_main1.w_set_lbutt(hwnd,bw_main1.win_hnd_id);
	    if ((bw_menuvar1.t5_m_pp2==14)||(bw_menuvar1.t5_m_pp2==15))
	    {
	      bw_menuvar1.t5_m_pp2=0;
	      return(0);
	    }
	  }
	  if (bw_main1.win_key==CTRL_E)
	  {
	    bw_switch1.w_clr_recvar_radio(bw_main1.win_hnd_id);
	    bw_switch1.w_echo_winrec_radio(bw_main1.win_hnd_id);
	    return(0);
	  }
	  if (bw_main1.win_key==ESC_KEY)
	  {
	    bw_fldstru1.w_find_exit(bw_main1.win_hnd_id);
	    bw_win1.w_close_win(bw_main1.win_hnd_id);
	    return(0);
	  }

          bw_main1.w_set_focus(hwnd);

	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

/*	  return(0);*/
        }
	if ((str[0]=='?')||(str[0]=='-'))
	{
	  bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	  bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	  i=bw_win1.pline;
          j=bw_win1.pfield;

	  if (str[0]=='?')
          {
	    k=bw_dialog1.w_mv_get_read1(str,SMG_LEN,bw_main1.win_hnd_id,'r');
	  }
	  else
	  {
	    k=1;
          }

	  if (k==1)
	  {
	    if (str[0]=='?')
            {
	      bw_get_bua1.get_smg_string(bw_win_bua1.get_win_pp11(bw_main1.win_hnd_id),sf1,SMG_LEN);
	    }
	    else
	    {
	      q=bw_win1.w_find_hnd(bw_main1.win_hnd_id,j,i);
	      if (q!=0)
	      {
                hnd=bw_win_bua1.get_win_hnd(q);
		GetWindowText(hnd,sf1,SMG_LEN);
	      }
              else sf1[0]=0;
	    }

	    bw_xbase_bua1.set_win_scrnvar(bw_main1.win_hnd_id,sf1,SMG_LEN);
	    bw_dialog_bua1.set_win_mv_getv(bw_main1.win_hnd_id,sf1,SMG_LEN);

	    bw_dialog1.w_mv_sav_var(str,SMG_LEN,bw_main1.win_hnd_id);

	    if ((bw_main1.win_key==276)||(bw_main1.win_key==277)
	      ||(bw_main1.win_key==RET_KEY))
	    {
	      bw_dialog_bua1.set_win_mv_getp(bw_main1.win_hnd_id,1);
	    }

	    if (bw_main1.win_key==401)
	    {
	      bw_win1.pline =bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,2);
	      bw_win1.pfield=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,1);
            }
	    if (bw_main1.win_key==10)  bw_win1.w_next_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==274) bw_win1.w_up_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==275) bw_win1.w_down_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==276) bw_win1.w_left_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==277) bw_win1.w_right_field(bw_main1.win_hnd_id);
	    if ((bw_main1.win_key==401)||(bw_main1.win_key==32))
	    {
	      bw_main1.w_set_lbutt(hwnd,bw_main1.win_hnd_id);
	      if ((bw_menuvar1.t5_m_pp2==14)||(bw_menuvar1.t5_m_pp2==15))
	      {
	        bw_menuvar1.t5_m_pp2=0;
	        return(0);
              }
	    }
	    if (bw_main1.win_key==ESC_KEY)
	    {
	      bw_fldstru1.w_find_exit(bw_main1.win_hnd_id);
	      bw_win1.w_close_win(bw_main1.win_hnd_id);
	      return(0);
	    }
	    if (bw_main1.win_key==CTRL_E)
	    {
	      bw_dialog_bua1.setc_win_mv_getv(bw_main1.win_hnd_id,0,0);
	    }

            bw_main1.w_set_focus(hwnd);

	    bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	    bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

/*	    return(0);*/
	  }
	}
	if ((str[0]==':')||(str[0]=='+'))
	{
	  bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	  bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	  i=bw_win1.pline;
	  j=bw_win1.pfield;

	  l=bw_buff1.get_linecol(bw_main1.win_hnd_id,i,j);
	  m=bw_win_bua1.get_1fldbase(l);

	  //if (bw_main1.win_key==401)
	  //{
          //  bw_getread1.win_p1=0;
	  //}

	  if (str[0]==':')
          {
	    k=bw_fldstru1.w_tv_get_read1(str,SMG_LEN,bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,'r');
	  }
	  else
	  {
            k=1; // &+fx ci
          }

	  if (k==1)
	  {
	    bw_inkey1.strpcut(str,1,strlen(str)-1,SMG_LEN,fldname,SMG_LEN);
	    m=bw_win_bua1.get_1fldbase(l);
	    bw_mbase1.w_down_rec(m,bw_main1.win_hnd_id,bw_xbase_bua1.get_win_recno(m,bw_main1.win_hnd_id,0)-1);


	    if (str[0]==':')
            {
	      bw_get_bua1.get_smg_string(bw_win_bua1.get_win_pp11(bw_main1.win_hnd_id),sf1,SMG_LEN);
	      bw_xbase_bua1.set_win_scrnvar(bw_main1.win_hnd_id,sf1,SMG_LEN);
	      bw_xbase_bua1.get_win_scrnvar(bw_main1.win_hnd_id,fldvar,SMG_LEN);
	    }
	    else
	    {
	      q=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
	      if (q!=0)
	      {
                hnd=bw_win_bua1.get_win_hnd(q);
		GetWindowText(hnd,fldvar,SMG_LEN);
	      }
              else fldvar[0]=0;
	      bw_xbase_bua1.set_win_scrnvar(bw_main1.win_hnd_id,fldvar,SMG_LEN);
	    }

            bw_fldstru1.w_get_tab_var(fldname,SMG_LEN,m,str3,SMG_LEN);

//	    sprintf(str2,",%s,%d,%s,%d,",fldvar,strlen(fldvar),str3,strlen(str3));
//	    MessageBox(hwnd,str2,"aa",MB_OK);

	    n=bw_fldstru1.w_cmp_tab_var(fldname,SMG_LEN,m,fldvar,SMG_LEN);

	    if (n==1)
	    {
	      if ((bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)!='m')
                &&(bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)!='b'))
              {
	        bw_fldstru1.w_sav_tab_var(fldname,SMG_LEN,m,fldvar,SMG_LEN);
		bw_mbase1.w_save_rec(m,bw_main1.win_hnd_id,bw_xbase_bua1.get_win_recno(m,bw_main1.win_hnd_id,0));
		bw_xbase_bua1.set_win_state5(m,1);
              }

	      p=bw_link1.w_link_type(bw_main1.win_hnd_id,m);

	      if (p>0)
	      {
		bw_link1.w_link_modi_mark(bw_main1.win_hnd_id
			     ,m
			     ,bw_fldstru1.w_find_fldnum(fldname,SMG_LEN,m)-bw_fldstru_bua1.get_t2_fldpoin(m,0)
			     ,bw_win_bua1.get_1fldseri(l));

		bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,1);
	      }
	    }

	    if ((bw_main1.win_key==276)||(bw_main1.win_key==277)
	      ||(bw_main1.win_key==RET_KEY))
	    {
	      bw_dialog_bua1.set_win_mv_getp(bw_main1.win_hnd_id,1);
	    }

	    if ((bw_main1.win_key==CTRL_D)||(bw_main1.win_key==CTRL_I)
	      ||(bw_main1.win_key==PG_UP) ||(bw_main1.win_key==PG_DOWN)
	      ||(bw_main1.win_key==CTRL_R)||(bw_main1.win_key==CTRL_N)
	      ||(bw_main1.win_key==CTRL_C))
	    {
	      p=bw_link1.w_link_type(bw_main1.win_hnd_id,m);

	      if (p>0)
	      {
		bw_link1.w_link_modi_mark(bw_main1.win_hnd_id
			      ,m
			      ,-1
			      ,bw_win_bua1.get_1fldseri(l));

		bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,1);
	      }
	    }

	    if ((bw_main1.win_key==274)||(bw_main1.win_key==275))
	    {
	      p=bw_link1.w_link_type(bw_main1.win_hnd_id,m);

	      if (p>2)
	      {
		bw_link1.w_link_modi_mark(bw_main1.win_hnd_id
			      ,m
			      ,-1
			      ,bw_win_bua1.get_1fldseri(l));

		bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,1);
	      }
	    }

	    if (bw_main1.win_key==401)
	    {
	      bw_win1.pline =bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,2);
	      bw_win1.pfield=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,1);
	    }
	    if (bw_main1.win_key==401)
	    {
	      l=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
              m=bw_win_bua1.get_1fldbase(l);

	      p=bw_link1.w_link_type(bw_main1.win_hnd_id,m);

	      if (p>0)
	      {
		bw_link1.w_link_modi_mark(bw_main1.win_hnd_id
			      ,m
			      ,-1
			      ,bw_win_bua1.get_1fldseri(l));

		bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,1);
	      }
	    }
	    if (bw_main1.win_key==10)  bw_win1.w_next_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==274) bw_win1.w_up_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==275) bw_win1.w_down_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==276) bw_win1.w_left_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==277) bw_win1.w_right_field(bw_main1.win_hnd_id);
	    if (bw_main1.win_key==PG_UP)   bw_fldstru1.w_page_up(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==PG_DOWN) bw_fldstru1.w_page_down(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_I)  bw_fldstru1.w_insert_rec(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_A)  bw_fldstru1.w_add_rec(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_D)  bw_fldstru1.w_delete_rec(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_R)  bw_fldstru1.w_rollback_base(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_W)  bw_fldstru1.w_commit_base(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_L)  bw_fldstru1.w_link_window(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_F)  bw_fldstru1.w_find_cond(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_C)  bw_fldstru1.w_find_key(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==CTRL_N)  bw_fldstru1.w_find_end(m,bw_main1.win_hnd_id);
	    if (bw_main1.win_key==F3_KEY)
	    {
	      bw_win_bub1.get_win_window_name(bw_main1.win_hnd_id,s_fn1,FN_SIZE);
	      bw_print1.w_print(bw_main1.win_hnd_id,s_fn1,FN_SIZE);
            }
	    if (bw_main1.win_key==F1_KEY)
	    {
	      if (bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)=='m')
	      {
		bw_fldstru1.w_edit_memo(m,bw_main1.win_hnd_id,fldname,SMG_LEN);
	      }
	    }
	    if (bw_main1.win_key==F2_KEY)
	    {
	      if (bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)=='m')
	      {
		bw_fldstru1.w_edit_memo_add(m,bw_main1.win_hnd_id,fldname,SMG_LEN);
	      }
	    }
	    if (bw_main1.win_key==F5_KEY)
	    {
	      if (bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)=='b')
	      {
		bw_bmp1.w_bmp_add(m,bw_main1.win_hnd_id,fldname,SMG_LEN);
	      }
	    }
	    if (bw_main1.win_key==F6_KEY)
	    {
	      if (bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)=='b')
	      {
		bw_bmp1.w_bmp_paint(hwnd);
		return(0);
	      }
	    }
	    if ((bw_main1.win_key==401)||(bw_main1.win_key==32))
	    {
	      bw_main1.w_set_lbutt(hwnd,bw_main1.win_hnd_id);
	      if ((bw_menuvar1.t5_m_pp2==14)||(bw_menuvar1.t5_m_pp2==15))
	      {
	        bw_menuvar1.t5_m_pp2=0;
		return(0);
	      }
	    }
	    if (bw_main1.win_key==ESC_KEY)
	    {
	      bw_fldstru1.w_find_exit(bw_main1.win_hnd_id);
	      bw_win1.w_close_win(bw_main1.win_hnd_id);
	      return(0);
	    }
	    if (bw_main1.win_key==CTRL_E)
	    {
	      if (str[0]==':') bw_xbase_bua1.setc_win_scrnvar(bw_main1.win_hnd_id,0,0);
	      else
	      {
		q=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
	        if (q!=0)
	        {
                  hnd=bw_win_bua1.get_win_hnd(q);
		  SetWindowText(hnd,"");
                }
	      }
	    }

	    bw_main1.w_set_focus(hwnd);

	    bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	    bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

/*	    return(0);*/
          }
	}

	i=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
	if (i>0)
	{
	  j=bw_win_bua1.get_1fldbase(i);
	  bw_dialog1.w_echo_winrec_read(j,bw_main1.win_hnd_id,bw_win1.win_pp21);
        }

	if (bw_win_bua1.get_win_state12(bw_main1.win_hnd_id)==1)
	{
	  bw_link1.w_echo_winrec_lnk(bw_main1.win_hnd_id);

	  bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,0);
	}
      }

      break;

    case WM_COMMAND:



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      i=wp/100;

      if ((i==10)||(i==14)||(i==15)||(i==16))
      {
	bw_main1.win_key=0;

	if (wp==1011) bw_main1.win_key=5000+PG_UP;
	if (wp==1012) bw_main1.win_key=5000+PG_DOWN;
	if (wp==1013) bw_main1.win_key=5000+CTRL_D;
	if (wp==1014) bw_main1.win_key=5000+CTRL_I;
	if (wp==1021) bw_main1.win_key=5000+CTRL_A;
	if (wp==1015) bw_main1.win_key=5000+CTRL_W;
	if (wp==1016) bw_main1.win_key=5000+CTRL_R;
	if (wp==1017) bw_main1.win_key=5000+CTRL_L;
	if (wp==1018) bw_main1.win_key=5000+CTRL_P;
	if (wp==1099) bw_main1.win_key=5000+ESC_KEY;

	if (wp==1501) bw_main1.win_key=5000+CTRL_F;
	if (wp==1502) bw_main1.win_key=5000+CTRL_C;
	if (wp==1503) bw_main1.win_key=5000+CTRL_N;

	if (wp==1601) bw_main1.win_key=5000+F1_KEY;
	if (wp==1602) bw_main1.win_key=5000+F2_KEY;
	if (wp==1603) bw_main1.win_key=5000+F3_KEY;
	if (wp==1604) bw_main1.win_key=5000+F4_KEY;
	if (wp==1605) bw_main1.win_key=5000+F5_KEY;
	if (wp==1606) bw_main1.win_key=5000+F6_KEY;

	if (wp==1401) bw_main1.win_key=5000+CTRL_E;
	if (wp==1499) bw_main1.win_key=5000+ESC_KEY;

	if (bw_main1.win_key>=5000)
	{
	  SendMessage(bw_main1.win_hwnd,WM_CHAR,1002,(LPARAM)str);
	} 
      }

      break;

    case WM_LBUTTONDOWN:
    {



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      if ((wp==1)&&(bw_win_bua1.get_win_ci_mode(bw_main1.win_hnd_id)==0))
      {
	bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);

	bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

	n=0;
	
	if ((str[0]=='?')||(str[0]=='-'))
	{
	  if (str[0]=='?')
          {
	    bw_get_bua1.get_smg_string(bw_win_bua1.get_win_pp11(bw_main1.win_hnd_id),sf1,SMG_LEN);
	  }
	  else
	  {
	    q=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
	    if (q!=0)
	    {
              hnd=bw_win_bua1.get_win_hnd(q);
	      GetWindowText(hnd,sf1,SMG_LEN);
	    }
            else sf1[0]=0;
	  }

	  bw_xbase_bua1.set_win_scrnvar(bw_main1.win_hnd_id,sf1,SMG_LEN);
	  bw_dialog_bua1.set_win_mv_getv(bw_main1.win_hnd_id,sf1,SMG_LEN);

	  bw_dialog1.w_mv_sav_var(str,SMG_LEN,bw_main1.win_hnd_id);
	  n=1;

        }
	
	if ((str[0]==':')||(str[0]=='+'))
	{
	  l=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
	  bw_inkey1.strpcut(str,1,strlen(str)-1,SMG_LEN,fldname,SMG_LEN);
	  m=bw_win_bua1.get_1fldbase(l);

	  p=bw_link1.w_link_type(bw_main1.win_hnd_id,m);

	  if (p>2)
	  {
	    bw_link1.w_link_modi_mark(bw_main1.win_hnd_id
			      ,m
			      ,-1
			      ,bw_win_bua1.get_1fldseri(l));

	    bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,1);
	  }

	  bw_mbase1.w_down_rec(m,bw_main1.win_hnd_id,bw_xbase_bua1.get_win_recno(m,bw_main1.win_hnd_id,0)-1);

	  if (str[0]==':')
          {
	    bw_get_bua1.get_smg_string(bw_win_bua1.get_win_pp11(bw_main1.win_hnd_id),sf1,SMG_LEN);
	  }
	  else
	  {
	    q=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
	    if (q!=0)
	    {
              hnd=bw_win_bua1.get_win_hnd(q);
	      GetWindowText(hnd,sf1,SMG_LEN);
	    }
            else sf1[0]=0;
	  }

	  bw_xbase_bua1.set_win_scrnvar(bw_main1.win_hnd_id,sf1,SMG_LEN);

	  bw_xbase_bua1.get_win_scrnvar(bw_main1.win_hnd_id,fldvar,SMG_LEN);
          o=bw_fldstru1.w_cmp_tab_var(fldname,SMG_LEN,m,fldvar,SMG_LEN);

	  if (o==1)    // save prev field 
	  {
	    if ((bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)!='m')
	      &&(bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)!='b'))
	    {
	      bw_fldstru1.w_sav_tab_var(fldname,SMG_LEN,m,fldvar,SMG_LEN);
	      bw_mbase1.w_save_rec(m,bw_main1.win_hnd_id,bw_xbase_bua1.get_win_recno(m,bw_main1.win_hnd_id,0));
	      bw_xbase_bua1.set_win_state5(m,1);

//            timer make wrong data
//	      sprintf(str,"%d,%d,",bw_win1.pline,bw_win1.pfield);
//	      MessageBox(hwnd,str,"aa",MB_OK);
            }
	  }
        }

        // set field roll to 0
        bw_getread1.win_p1=0;

	i=LOWORD(lp);
	j=HIWORD(lp);

	k=(int)(j/bw_main1.win_edit_ychar+bw_win_bua1.get_win_con(bw_main1.win_hnd_id,1));
	l=(int)(i/bw_main1.win_edit_xchar+bw_win_bua1.get_win_con(bw_main1.win_hnd_id,0));

	m=bw_win1.w_mouse_infield(bw_main1.win_hnd_id,k,l);

	if (m==1)
	{
	  bw_win1.pline =bw_win1.win_mouse_y;
          bw_win1.pfield=bw_win1.win_mouse_x;

	  bw_dialog_bua1.set_win_mv_getp(bw_main1.win_hnd_id,bw_main1.win_field_posi);

	  bw_main1.w_set_focus(hwnd);

	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,0,bw_win1.pline);
	  bw_win_bua1.set_win_linep(bw_main1.win_hnd_id,1,bw_win1.pfield);

	  i=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
	  if (i>0) j=bw_win_bua1.get_1fldbase(i);
	  else j=0;

	  bw_dialog1.w_echo_winrec_read(j,bw_main1.win_hnd_id,bw_win1.win_pp21);

	  if (bw_win_bua1.get_win_state12(bw_main1.win_hnd_id)==1)
	  {
	    bw_link1.w_echo_winrec_lnk(bw_main1.win_hnd_id);

	    bw_win_bua1.set_win_state12(bw_main1.win_hnd_id,0);
	  }
	}

      }

      break;

    }

    case WM_MOUSEMOVE:
    {



      bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);
      if (bw_win_bua1.get_win_msgboxlock(bw_main1.win_hnd_id)==1)
      {
        break;
      }



      if ((wp==0)&&(bw_win_bua1.get_win_ci_mode(bw_main1.win_hnd_id)==0))
      {
	bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);

	i=LOWORD(lp);
	j=HIWORD(lp);

	k=(int)(j/bw_main1.win_edit_ychar+bw_win_bua1.get_win_con(bw_main1.win_hnd_id,1));
	l=(int)(i/bw_main1.win_edit_xchar+bw_win_bua1.get_win_con(bw_main1.win_hnd_id,0));

	m=bw_win1.w_mouse_infield(bw_main1.win_hnd_id,k,l);

	if (m==1)
        {
	  hcursor=LoadCursor(NULL,IDC_IBEAM);
//	  hcursor=LoadCursor(NULL,"cursor2.cur");
          SetCursor(hcursor);
	}
	else
	{
	  hcursor=LoadCursor(NULL,IDC_ARROW);
          SetCursor(hcursor);
	}

      }

	  break;
    }
    case WM_SYSCOMMAND:
    {
//       sprintf(sf1,"%d,",wp);
//	   hdc=GetDC(bw_main1.win_hwnd1);
//	   TextOut(hdc,0,0,sf1,strlen(sf1));
//	   ReleaseDC(bw_main1.win_hwnd1,hdc);

      if ((0-wp==4000)||(wp==61536))
      {
	bw_main1.win_hnd_id=bw_win1.w_find_winhand(hwnd);

	bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
	bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);

	i=bw_win1.pline;
	j=bw_win1.pfield;

	l=bw_buff1.get_linecol(bw_main1.win_hnd_id,i,j);
	m=bw_win_bua1.get_1fldbase(l);

	bw_fldstru1.w_find_exit(bw_main1.win_hnd_id);
	bw_win1.w_close_win(bw_main1.win_hnd_id);
      }
    }
  }
  return DefWindowProc(hwnd,msg,wp,lp);
}
// _export
long FAR PASCAL w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp)
{
//  HDC  hdc;
  int  i,j,k;
  char str[SMG_LEN];

  j=(int)GetWindowLong(hwnd,GWL_ID);

  switch(msg)
  {
    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:
    {
      bw_main1.win_msg=msg;
      bw_main1.win_wp=wp;

      i=bw_inkey1.inkey();

      if (i==1)
      {
        bw_win1.win_menu_seri=j;

	if ((bw_main1.win_key==274)||
	    (bw_main1.win_key==275)||
	    (bw_main1.win_key==276)||
	    (bw_main1.win_key==277)||
	    (bw_main1.win_key==10 )||
	    (bw_main1.win_key<=32))
	{
	  k=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,4);
	  bw_main1.win_key=10000+bw_main1.win_key;
	  SendMessage(bw_win_bua1.get_win_hnd(k),WM_CHAR,1002,(LPARAM)str);
	}
      }
    }
    case WM_LBUTTONUP:
    {
      if (wp==0)
      {  
        bw_win1.win_menu_seri=j;

	bw_main1.win_key=10000+401;
	k=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,4);
	SendMessage(bw_win_bua1.get_win_hnd(k),WM_CHAR,1002,(LPARAM)str);
      }
    }
  }
  return (CallWindowProc((WNDPROC)bw_win_bua1.get_win_fpp(j),hwnd,msg,wp,lp));
}
long FAR PASCAL w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp)
{
//  HDC  hdc;
  int  i,j,k;
//  int  t1,t2;
  char str[SMG_LEN];

  j=(int)GetWindowLong(hwnd,GWL_ID);

  switch(msg)
  {
    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:
    {
      bw_main1.win_msg=msg;
      bw_main1.win_wp=wp;

      i=bw_inkey1.inkey();

      if (i==1)
      {
        bw_win1.win_menu_seri=j;

	if ((bw_main1.win_key==274)||
	    (bw_main1.win_key==275)||
	    (bw_main1.win_key==10 )||
	    (bw_main1.win_key==27) ||
	    (bw_main1.win_key==PG_UP)||
	    (bw_main1.win_key==PG_DOWN)||
	    (bw_main1.win_key==CTRL_I)||
	    (bw_main1.win_key==CTRL_D)||
	    (bw_main1.win_key==CTRL_R)||
	    (bw_main1.win_key==CTRL_W)||
	    (bw_main1.win_key==CTRL_L)||
	    (bw_main1.win_key==CTRL_F)||
	    (bw_main1.win_key==CTRL_C)||
	    (bw_main1.win_key==CTRL_N)||
	    (bw_main1.win_key==F3_KEY)||
	    (bw_main1.win_key==F1_KEY)||
	    (bw_main1.win_key==F2_KEY)||
	    (bw_main1.win_key==F5_KEY)||
	    (bw_main1.win_key==F6_KEY))
	{
	  k=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,4);
	  bw_main1.win_key=10000+bw_main1.win_key;
	  SendMessage(bw_win_bua1.get_win_hnd(k),WM_CHAR,1002,(LPARAM)str);
          return(0);
	}
      }
      else
      {
	if ((wp==VK_RETURN)||
	    (wp==VK_ESCAPE)||
	    (wp==VK_PRIOR) ||
	    (wp==VK_NEXT)  ||
	    (wp==VK_END)   ||
	    (wp==VK_HOME)  ||
	    (wp==VK_UP)    ||
	    (wp==VK_DOWN)  ||
	    (wp==VK_INSERT)||
	    (wp==VK_F1)    ||
	    (wp==VK_F2)    ||
	    (wp==VK_F3)    ||
	    (wp==VK_F5)    ||
	    (wp==VK_F6))
	{
          return(0);
	}
      }
    }
    case WM_LBUTTONUP:
    {
      if (wp==0)
      {
	bw_win1.win_menu_seri=j;

	bw_main1.win_key=10000+401;
	k=bw_win_bua1.get_win_hpp4(bw_win1.win_menu_seri,4);
	SendMessage(bw_win_bua1.get_win_hnd(k),WM_CHAR,1002,(LPARAM)str);
      }
    }
  }
  return (CallWindowProc((WNDPROC)bw_win_bua1.get_win_fpp(j),hwnd,msg,wp,lp));
}

int bw_main::w_fetch_filename(char *p_s1,int len)
{
  int i;
  int exist;

  exist=0;

  p_s1[len-1]=0;

  bw_inkey1.strtrim(p_s1);

  for (i=strlen(p_s1)-1;i>=0;i--)
  {
    if (i<len)
    {
      if (p_s1[i]==92)
      {
        exist=1;
	break;
      }
    }
  }

  if (exist==1)
  {
    bw_inkey1.strpcut(p_s1,0,i,len,win_seadir,FN_SIZE);
    bw_inkey1.strpcut(p_s1,i+1,strlen(p_s1)-i-1,len,win_seaname,FN_SIZE);

    for (i=0;i<(int)strlen(win_seadir);i++) win_seadir[i]=bw_inkey1.upper(win_seadir[i]);
    for (i=0;i<(int)strlen(win_seaname);i++) win_seaname[i]=bw_inkey1.upper(win_seaname[i]);
  }
  else
  {
    win_seadir[0]=0;
    strcpy(win_seaname,p_s1);
  }

  return(0);
}

int bw_main::set_string(char *p_s1,int p_s1_l,char *p_s2,int p_s2_l)
{
  int i;

  p_s1[0]=0;

  for (i=0;i<p_s2_l;i++)
  {
    if (i+1>=p_s1_l) continue;
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

int bw_main::get_view(char *p_str,int len,HWND hwnd,int pp5)
{
  HMENU hm1;
  HWND  hwnd2;

  int  i,j,k,l,m,n=0,o;
  int  tmpn1,tmpn2;
  int  open_base_ok=1;
  int  open_base_menu=1;
  int  open_base_have;
  int  open_base[STRU_NUM];
  int  open_stru[STRU_NUM];
  int  exist;
  //char stc[SMG_LEN];

  //bw_main1.win_hwnd=bw_main1.win_hwnd1;

/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=str[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //set_string(stc,SMG_LEN,str,len);

  if (bw_xbase1.win_answer!=0)
  { 
    bw_win1.w_atten66();
    return(1);
  }
/*
  if (bw_win_bua1.get_win_subhndpp(pp5)+1>=SUB_WIN_NUM)
  {
    bw_win1.w_atten67();
    return(1);
  }
*/
  // set current dir
  strcpy(bw_main1.s_bs3,p_str);
  exist=0;
  for (i=strlen(bw_main1.s_bs3)-1;i>=0;i--)
  {
    if (bw_main1.s_bs3[i]==92)
    {
      exist=1;

      if (i>0)
      {
	if (bw_main1.s_bs3[i-1]==':') bw_main1.s_bs3[i+1]=0;
	else bw_main1.s_bs3[i]=0;
      }
      else
      {
	bw_main1.s_bs3[0]=92;
	bw_main1.s_bs3[1]=0;
      }

      break;
    }
  }

  if (exist==1)
  {
    bw_inkey1.w_set_dir(bw_main1.s_bs3);
  }

  for (i=0;i<STRU_NUM;i++)
  {
    open_base[i]=0;
    open_stru[i]=0;
  }


//  MessageBox(bw_main1.win_hwnd1,"bb","bb",MB_OK);

  strcpy(bw_main1.s_bs1,p_str);
  i=bw_inkey1.strlocc(bw_main1.s_bs1,'.');
  bw_main1.s_bs1[i]=0;

  bw_main1.win_hnd_id=bw_win1.win_pp1;

  tmpn1=bw_main1.win_hnd_id;

  i=1;
  strcpy(bw_main1.s_bs2,bw_main1.s_bs1);
  if (bw_main1.win_lang==1) strcat(bw_main1.s_bs2,".sc3");
  else strcat(bw_main1.s_bs2,".sc4");
  //strcat(bw_main1.s_bs2,".sc3");
  if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
  {
    i=bw_win1.w_read_winfile(bw_main1.s_bs2,FN_SIZE);
  }
  else
  {
    bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
    bw_inkey1.w_set_dir(win_home_dir);
    if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
	{
      i=bw_win1.w_read_winfile(bw_main1.s_bs2,FN_SIZE);
	}
	else
	{  
	  bw_win1.w_atten1(bw_main1.s_bs2);
	}
    bw_inkey1.w_set_dir(win_work_dir);
  }

  if (i!=0)
  {
    bw_win1.win_pp1=tmpn1;
    return(1);
  }

  tmpn2=bw_win1.win_pp1;

  m=1;
  strcpy(bw_main1.s_bs2,bw_main1.s_bs1);
  strcat(bw_main1.s_bs2,".tb1");
  if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_menuvar1.w_read_mdc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
  else
  {
    bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
    bw_inkey1.w_set_dir(win_home_dir);
    if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_menuvar1.w_read_mdc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
    bw_inkey1.w_set_dir(win_work_dir);
  }
  if (m==0) n=1;

  strcpy(bw_main1.s_bs2,bw_main1.s_bs1);
  strcat(bw_main1.s_bs2,".tb4");
  if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1) bw_font1.w_read_fdc(bw_main1.s_bs2,bw_main1.win_hnd_id);
  else
  {
    bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
    bw_inkey1.w_set_dir(win_home_dir);
    if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1) bw_font1.w_read_fdc(bw_main1.s_bs2,bw_main1.win_hnd_id);
    bw_inkey1.w_set_dir(win_work_dir);
  }

  bw_main1.win_hnd_id      = tmpn1;
  bw_win1.win_pp1 = tmpn2;

  m=1;
  strcpy(bw_main1.s_bs2,bw_main1.s_bs1);
  strcat(bw_main1.s_bs2,".tb6");
  if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_choose1.w_read_cdc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
  else
  {
    bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
    bw_inkey1.w_set_dir(win_home_dir);
    if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_choose1.w_read_cdc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
    bw_inkey1.w_set_dir(win_work_dir);
  }
  if (m==0) n=1;

  bw_main1.win_hnd_id      = tmpn1;
  bw_win1.win_pp1 = tmpn2;

  m=1;
  strcpy(bw_main1.s_bs2,bw_main1.s_bs1);
  strcat(bw_main1.s_bs2,".tb5");
  if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_switch1.w_read_sdc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
  else
  {
    bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
    bw_inkey1.w_set_dir(win_home_dir);
    if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_switch1.w_read_sdc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
    bw_inkey1.w_set_dir(win_work_dir);
  }
  if (m==0) n=1;

  bw_main1.win_hnd_id      = tmpn1;
  bw_win1.win_pp1 = tmpn2;

  m=1;
  strcpy(bw_main1.s_bs2,bw_main1.s_bs1);
  strcat(bw_main1.s_bs2,".tb2");
  if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_dialog1.w_read_ddc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
  else
  {
    bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
    bw_inkey1.w_set_dir(win_home_dir);
    if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
      m=bw_dialog1.w_read_ddc(bw_main1.s_bs2,FN_SIZE,bw_main1.win_hnd_id);
    bw_inkey1.w_set_dir(win_work_dir);
  }
  if (m==0) n=1;

  /* read table stru */

  open_base_have=0;

  for (j=0;j<STRU_NUM;j++)
  {
    if (bw_win_bua1.get_win_pp9(j,bw_main1.win_hnd_id)==1)
    {
      bw_main1.win_hnd_id      = tmpn1;
      bw_win1.win_pp1 = tmpn2;

      open_base_have=1;

      bw_win_bub1.get_win_tabname(0,j,bw_main1.s_bs2,FN_SIZE);
      k=bw_inkey1.strlocc(bw_main1.s_bs2,'.');
      bw_main1.s_bs2[k]=0;
      strcat(bw_main1.s_bs2,".tb3");
      k=1;
      if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
	 k=bw_fldstru1.w_read_stru(bw_main1.s_bs2,FN_SIZE,j);
      else
      {
        bw_inkey1.w_get_dir(win_work_dir,FN_SIZE);
        bw_inkey1.w_set_dir(win_home_dir);
	if (bw_inkey1.w_find_file(bw_main1.s_bs2)==1)
	  k=bw_fldstru1.w_read_stru(bw_main1.s_bs2,FN_SIZE,j);
        else open_base_menu=0;
        bw_inkey1.w_set_dir(win_work_dir);
      }
      if (k==0)
      {
	open_stru[j]=1;
      }
      else
      {
	open_base_menu=0;
      }
    }
  }

  if (open_base_have==0) open_base_menu=0;

  /* read table base */

  open_base_have=0;

  for (j=0;j<STRU_NUM;j++)
  {
    if (bw_win_bua1.get_win_pp9(j,bw_main1.win_hnd_id)==1)
    {
      bw_main1.win_hnd_id      = tmpn1;
      bw_win1.win_pp1 = tmpn2;

      open_base_have=1;

      bw_win_bub1.get_win_tabname(1,j,bw_main1.s_bs2,FN_SIZE);

      k=bw_inkey1.strlocc(bw_main1.s_bs2,'.');
      bw_main1.s_bs2[k]=0;
      strcat(bw_main1.s_bs2,".dbf");
      
      k=bw_mbase1.w_open_base(bw_main1.s_bs2,FN_SIZE,j);

      if (k!=0)
      {
	open_base_ok=0;
        open_base_menu=0;
	open_base[j]=1;
	break;
      }
      else
      {
	open_base[j]=1;
      }
    }
  }

  if (open_base_have==0) open_base_menu=0;

  /* close opened base */

  if (open_base_ok==0)
  {
    for (j=0;j<STRU_NUM;j++)
    {
      bw_main1.win_hnd_id      = tmpn1;
      bw_win1.win_pp1 = tmpn2;

      if ((bw_win_bua1.get_win_pp9(j,bw_main1.win_hnd_id)==1)&&(open_base[j]==1))
      {
	bw_win_bub1.get_win_tabname(1,j,bw_main1.s_bs2,FN_SIZE);

	bw_mbase1.w_close_base(j,0);
      }
      if ((bw_win_bua1.get_win_pp9(j,bw_main1.win_hnd_id)==1)&&(open_stru[j]==1))
      {
	bw_fldstru1.w_dele_stru(j);
      }
    }

    bw_main1.win_hnd_id      = tmpn1;
    bw_win1.win_pp1 = tmpn2;

    bw_win1.w_dele_xbase_state(bw_main1.win_hnd_id);

    bw_main1.win_hnd_id      = tmpn1;
    bw_win1.win_pp1 = tmpn2;

    bw_win1.w_dele_win_pp(bw_main1.win_hnd_id);

    bw_win1.win_pp1=tmpn1;    // add close_win() part
     
    return(1);
  }

  bw_main1.win_hnd_id      = tmpn1;
  bw_win1.win_pp1 = tmpn2;

  if (n==0)
  {
    if (open_base_menu==1)
    {
      if (bw_main1.win_lang==1) hm1=(HMENU)LoadMenu(win_ins,"TAB_MENU");
      else hm1=(HMENU)LoadMenu(win_ins,"CTAB_MENU");
      o=2;
    }
    else
    {
      hm1=(HMENU)NULL;
      o=0;
    }
  }
  else
  {
    if (open_base_menu==1)
    {
      if (bw_main1.win_lang==1) hm1=(HMENU)LoadMenu(win_ins,"MTAB_MENU");
      else hm1=(HMENU)LoadMenu(win_ins,"CMTAB_MENU");
      o=3;
    }
    else
    {
      if (bw_main1.win_lang==1) hm1=(HMENU)LoadMenu(win_ins,"VAR_MENU");
      else hm1=(HMENU)LoadMenu(win_ins,"CVAR_MENU");
      o=1;
    }
  }

  for (m=bw_main1.win_hnd_id;m<bw_win1.win_pp1;m++)
  {
    bw_win_bua1.set_win_create_menu(m,o);
  }

  j=bw_win1.win_hpp1;

  bw_win1.w_login_wwin(bw_main1.win_hnd_id);

  l=bw_win_bua1.get_win_pp5(bw_main1.win_hnd_id);

  for (k=bw_win_bua1.get_win_pp6(l,0);k<=bw_win_bua1.get_win_pp6(l,2);k++)
  {
    bw_main1.win_hnd_id=k;

    hwnd2=CreateWindow ("bowo_menu",
			"Date Viewer Sub Window",
			WS_CAPTION|WS_VISIBLE|WS_SYSMENU|
			WS_BORDER|WS_CLIPCHILDREN|
			WS_MINIMIZEBOX|WS_THICKFRAME,
			50,
			50,
			50,
			50,
			hwnd,
			hm1,
			win_ins,
			NULL);

   bw_win_bua1.set_win_phh(k,hwnd2);
   bw_win_bua1.set_win_hnd(j+k-bw_win_bua1.get_win_pp6(l,0),bw_win_bua1.get_win_phh(k));

  }
/*
  bw_win_bua1.set_win_subhndid(pp5,bw_win_bua1.get_win_subhndpp(pp5),l);
  bw_win_bua1.set_win_subhndpp(pp5,1+bw_win_bua1.get_win_subhndpp(pp5));

  bw_win_bua1.set_win_subhndpp(l+1,0);
*/
  return(0);
}
int bw_main::w_set_focus(HWND hwnd)
{
  HDC  hdc;
  RECT rt;

  int  i,j,k,l;
  char str[SMG_LEN];
//  char str1[SMG_LEN];

  bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

  if (str[0]=='@')
  {
    i=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);

    hdc=GetDC(bw_win_bua1.get_win_hnd(i));
    GetWindowRect(bw_win_bua1.get_win_hnd(i),&rt);
    InvalidateRect(bw_win_bua1.get_win_hnd(i),&rt,NULL);
    DrawFocusRect(hdc,&rt);
    ReleaseDC(bw_win_bua1.get_win_hnd(i),hdc);

    SetFocus(bw_win_bua1.get_win_hnd(i));

    bw_menuvar1.w_menu_poin(str,SMG_LEN,bw_main1.win_hnd_id);
    bw_menuvar1.w_menu_comm(bw_menuvar1.t5_m_pp3,1);

    if (bw_menuvar1.t5_m_pp2==26)
    {
      bw_bmp1.echo_bmp(hwnd,bw_menuvar1.t5_m_como,SMG_LEN,bw_menuvar_bua1.get_t5_m_mcnt(bw_menuvar1.t5_m_pp3),bw_main1.win_hnd_id);

      bw_menuvar_bua1.set_t5_m_mcnt(bw_menuvar1.t5_m_pp3,bw_menuvar_bua1.get_t5_m_mcnt(bw_menuvar1.t5_m_pp3)+1);
    }
  }
  if (str[0]=='[')
  {
    j=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
    SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETSTATE,11,(LPARAM)str);
  }
  if (str[0]=='(')
  {
    j=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
    SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETSTATE,11,(LPARAM)str);
  }
  if ((str[0]=='?')||(str[0]=='-'))
  {
    ShowCaret(hwnd);
    bw_dialog1.w_mv_get_read(str,SMG_LEN,bw_main1.win_hnd_id,'g');
  }
  if ((str[0]==':')||(str[0]=='+'))
  {
    i=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
    j=bw_win_bua1.get_1fldseri(i);
    k=bw_win_bua1.get_1fldbase(i);
    l=bw_fldstru1.w_fetch_rec(k,bw_main1.win_hnd_id,j);

    ShowCaret(hwnd);

    if (l==0)
    {
      bw_fldstru1.w_tv_get_read(str,SMG_LEN,bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,'g');
    }
    else
    {
//      MessageBox(bw_main1.win_hwnd,"bb","bb",MB_OK);
//
      bw_win1.pline =bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,0);
      bw_win1.pfield=bw_win_bua1.get_win_linep(bw_main1.win_hnd_id,1);
      bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

      i=bw_buff1.get_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
      j=bw_win_bua1.get_1fldseri(i);
      k=bw_win_bua1.get_1fldbase(i);

      if ((str[0]==':')||(str[0]=='+'))
      {
	bw_mbase1.w_down_rec(k,bw_main1.win_hnd_id,bw_xbase_bua1.get_win_recno(k,bw_main1.win_hnd_id,0)-1);
	bw_fldstru1.w_tv_get_read(str,SMG_LEN,bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,'g');
      }
      else w_set_focus2(hwnd);
    }
  }
  return(0);
}
int bw_main::w_set_focus_timer(HWND hwnd)
{
//  HDC  hdc;
//  RECT rt;

//  int  i,j,k,l;
  char str[SMG_LEN];
//  char str1[SMG_LEN];

  bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

  if (str[0]=='@')
  {
    bw_menuvar1.w_menu_poin(str,SMG_LEN,bw_main1.win_hnd_id);
    bw_menuvar1.w_menu_comm(bw_menuvar1.t5_m_pp3,1);

    if (bw_menuvar1.t5_m_pp2==26)
    {
      bw_bmp1.echo_bmp(hwnd,bw_menuvar1.t5_m_como,SMG_LEN,bw_menuvar_bua1.get_t5_m_mcnt(bw_menuvar1.t5_m_pp3),bw_main1.win_hnd_id);

      bw_menuvar_bua1.set_t5_m_mcnt(bw_menuvar1.t5_m_pp3,bw_menuvar_bua1.get_t5_m_mcnt(bw_menuvar1.t5_m_pp3)+1);
    }
  }

  return(0);
}

int bw_main::w_set_focus2(HWND hwnd)
{
  HDC  hdc;
  RECT rt;

  int  i,j;
  char str[SMG_LEN];

  bw_win1.w_find_winfname(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

  if (str[0]=='@')
  {
    i=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);

    hdc=GetDC(bw_win_bua1.get_win_hnd(i));
    GetWindowRect(bw_win_bua1.get_win_hnd(i),&rt);
    InvalidateRect(bw_win_bua1.get_win_hnd(i),&rt,NULL);
    DrawFocusRect(hdc,&rt);
    ReleaseDC(bw_win_bua1.get_win_hnd(i),hdc);

    SetFocus(bw_win_bua1.get_win_hnd(i));
  }
  if (str[0]=='[')
  {
    j=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
    SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETSTATE,11,(LPARAM)str);
  }
  if (str[0]=='(')
  {
    j=bw_win1.w_find_hnd(bw_main1.win_hnd_id,bw_win1.pfield,bw_win1.pline);
    SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETSTATE,11,(LPARAM)str);
  }
  if ((str[0]=='?')||(str[0]=='-'))
  {
    ShowCaret(hwnd);
    bw_dialog1.w_mv_get_read(str,SMG_LEN,bw_main1.win_hnd_id,'g');
  }
  return(0);
}
int bw_main::w_set_lbutt(HWND hwnd,int hnd_id)
{
//  HDC  hdc;
//  HWND hnd;
  int  i,j,k,l,p;
  char str[SMG_LEN];
//  char str1[SMG_LEN];
//  char fldname[SMG_LEN];
//  char fldvar[SMG_LEN];
  char s_win[SMG_LEN];
  char s_msg[SMG_LEN];
  char s_itm[SMG_LEN];
  char s_stt[SMG_LEN];
//  char sf1[SMG_LEN];

  bw_main1.win_hwnd=hwnd;

  get_ci_save(hnd_id);
  
  bw_win1.w_find_winfname(hnd_id,bw_win1.pline,bw_win1.pfield,str,SMG_LEN);

  if (str[0]=='@')
  {
    bw_menuvar1.w_menu_poin(str,SMG_LEN,hnd_id);
    bw_menuvar1.w_menu_comm(bw_menuvar1.t5_m_pp3,0);

    if (bw_menuvar1.t5_m_pp2==1)
    {
      bw_main1.get_view(bw_menuvar1.t5_m_como,SMG_LEN,bw_main1.win_hwnd,bw_win_bua1.get_win_pp6(hnd_id,0));
      return(0);
    }

    if (bw_menuvar1.t5_m_pp2==14)
    {
      if (bw_win_bua1.get_win_style(hnd_id,2)==1) bw_switch1.w_save_switch(hnd_id);
      if (bw_win_bua1.get_win_style(hnd_id,3)==1) bw_choose1.w_save_choose(hnd_id);
      if (bw_win_bua1.get_win_style(hnd_id,8)==1) bw_dialog1.w_save_dialog(hnd_id);
      if (bw_win_bua1.get_win_style(hnd_id,9)==1) bw_dialog1.w_save_dialog(hnd_id);

      // use app interface

      bw_win_bub1.get_win_window_name(hnd_id,s_win,SMG_LEN);
      bw_inkey1.strtrim(s_win);
      l=bw_inkey1.strlocc(s_win,'.');
      s_win[l]=0;
      strcpy(s_msg,"WM_CLOSE");

      bw_user1.w_user_triger(s_win,SMG_LEN,s_msg,SMG_LEN,s_itm,SMG_LEN,s_stt,SMG_LEN);

      //------------

      bw_fldstru1.w_find_exit(hnd_id);
      bw_win1.w_close_win(hnd_id);

      return(0);
    }
    if (bw_menuvar1.t5_m_pp2==15)
    {
      bw_fldstru1.w_find_exit(hnd_id);
      bw_win1.w_close_win(hnd_id);
      return(0);
    }

    i=bw_buff1.get_linecol(hnd_id,bw_win1.pline,bw_win1.pfield);
    if (i>0) j=bw_win_bua1.get_1fldbase(i);
    else j=0;

    if (bw_menuvar1.t5_m_pp2==16)
    {
      p=bw_link1.w_link_type(hnd_id,j);
      if (p>0)
      {
	bw_link1.w_link_modi_mark(hnd_id
			      ,j
			      ,-1
			      ,bw_win_bua1.get_1fldseri(i));

	bw_win_bua1.set_win_state12(hnd_id,1);
      }

      bw_fldstru1.w_page_up(j,hnd_id);

      if (bw_win_bua1.get_win_state12(hnd_id)==1)
      {
	bw_link1.w_echo_winrec_lnk(hnd_id);
	bw_win_bua1.set_win_state12(hnd_id,0);
      }
    }
    if (bw_menuvar1.t5_m_pp2==17)
    {
      p=bw_link1.w_link_type(hnd_id,j);
      if (p>0)
      {
	bw_link1.w_link_modi_mark(hnd_id
			      ,j
			      ,-1
			      ,bw_win_bua1.get_1fldseri(i));

	bw_win_bua1.set_win_state12(hnd_id,1);
      }

      bw_fldstru1.w_page_down(j,hnd_id);

      if (bw_win_bua1.get_win_state12(hnd_id)==1)
      {
	bw_link1.w_echo_winrec_lnk(hnd_id);
	bw_win_bua1.set_win_state12(hnd_id,0);
      }
    }
    if (bw_menuvar1.t5_m_pp2==18)
    {
      bw_fldstru1.w_insert_rec(j,hnd_id);
    }
    if (bw_menuvar1.t5_m_pp2==27)
    {
      bw_fldstru1.w_add_rec(j,hnd_id);
    }
    if (bw_menuvar1.t5_m_pp2==19) bw_fldstru1.w_delete_rec(j,hnd_id);
    if (bw_menuvar1.t5_m_pp2==20) bw_fldstru1.w_rollback_base(j,hnd_id);
    if (bw_menuvar1.t5_m_pp2==21) bw_fldstru1.w_commit_base(j,hnd_id);
    if (bw_menuvar1.t5_m_pp2==22) bw_fldstru1.w_link_window(j,hnd_id);
    if (bw_menuvar1.t5_m_pp2==23) bw_fldstru1.w_find_cond(j,hnd_id);
    if (bw_menuvar1.t5_m_pp2==24)
    {
      p=bw_link1.w_link_type(hnd_id,j);
      if (p>0)
      {
	bw_link1.w_link_modi_mark(hnd_id
			      ,j
			      ,-1
			      ,bw_win_bua1.get_1fldseri(i));

	bw_win_bua1.set_win_state12(hnd_id,1);
      }

      bw_fldstru1.w_find_key(j,hnd_id);

      if (bw_win_bua1.get_win_state12(hnd_id)==1)
      {
	bw_link1.w_echo_winrec_lnk(hnd_id);
	bw_win_bua1.set_win_state12(hnd_id,0);
      }
    }
    if (bw_menuvar1.t5_m_pp2==25)
    {
      p=bw_link1.w_link_type(hnd_id,j);
      if (p>0)
      {
	bw_link1.w_link_modi_mark(hnd_id
			      ,j
			      ,-1
			      ,bw_win_bua1.get_1fldseri(i));

	bw_win_bua1.set_win_state12(hnd_id,1);
      }

      bw_fldstru1.w_find_end(j,hnd_id);

      if (bw_win_bua1.get_win_state12(hnd_id)==1)
      {
	bw_link1.w_echo_winrec_lnk(hnd_id);
	bw_win_bua1.set_win_state12(hnd_id,0);
      }
    }
  }

  if (str[0]=='[')
  {
    k=bw_inkey1.char2int(str,1,strlen(str)-1);
    i=bw_choose1.w_echo_chs_change(k,hnd_id);
    j=bw_win1.w_find_hnd(hnd_id,bw_win1.pfield,bw_win1.pline);
    i=SendMessage(bw_win_bua1.get_win_hnd(j),BM_GETCHECK,11,(LPARAM)str);
    if (i==0) SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETCHECK,11,(LPARAM)str);
    else  SendMessage(bw_win_bua1.get_win_hnd(j),BM_SETCHECK,0,(LPARAM)str);

    // use app interface

    bw_win_bub1.get_win_window_name(hnd_id,s_win,SMG_LEN);
    bw_inkey1.strtrim(s_win);
    l=bw_inkey1.strlocc(s_win,'.');
    s_win[l]=0;
    strcpy(s_msg,"WM_LBUTTON");
    bw_win1.w_find_winfname(hnd_id,bw_win1.pline,bw_win1.pfield,s_itm,SMG_LEN);
    if (i==0) i=1;
    else i=0;
    sprintf(s_stt,"%d",i);
   
    bw_user1.w_user_triger(s_win,SMG_LEN,s_msg,SMG_LEN,s_itm,SMG_LEN,s_stt,SMG_LEN);

    //------------
  }

  if (str[0]=='(')
  {
    k=bw_inkey1.char2int(str,1,strlen(str)-1);
    i=bw_switch1.w_set_radio_var(bw_win1.pline,bw_win1.pfield,k,hnd_id);

    // use app interface

    bw_win_bub1.get_win_window_name(hnd_id,s_win,SMG_LEN);
    bw_inkey1.strtrim(s_win);
    l=bw_inkey1.strlocc(s_win,'.');
    s_win[l]=0;
    strcpy(s_msg,"WM_LBUTTON");
    bw_win1.w_find_winfname(hnd_id,bw_win1.pline,bw_win1.pfield,s_itm,SMG_LEN);
    sprintf(s_stt,"%d",bw_switch_bua1.get_win_switch(i,1));

    bw_user1.w_user_triger(s_win,SMG_LEN,s_msg,SMG_LEN,s_itm,SMG_LEN,s_stt,SMG_LEN);

    //------------
  }

  if ((str[0]=='?')||(str[0]=='-'))
  {

  }

  if ((str[0]==':')||(str[0]=='+'))
  {

  }

  return(0);
}

int bw_main::get_ci_save(int hnd_id)
{
  HWND hnd;
  int  m,o,q;
  char fldvar[SMG_LEN];
  char sf1[SMG_LEN];
  char str1[SMG_LEN];
  char fldname[SMG_LEN];

  bw_win1.w_find_winfname(hnd_id,bw_win_bua1.get_win_linep(hnd_id,0),bw_win_bua1.get_win_linep(hnd_id,1),str1,SMG_LEN);

  if ((str1[0]=='?')||(str1[0]=='-'))
  {
    if (str1[0]=='?')
    {
      bw_get_bua1.get_smg_string(bw_win_bua1.get_win_pp11(hnd_id),sf1,SMG_LEN);
      bw_xbase_bua1.set_win_scrnvar(hnd_id,sf1,SMG_LEN);
      bw_dialog_bua1.set_win_mv_getv(hnd_id,sf1,SMG_LEN);
    }
    else
    {
      q=bw_win1.w_find_hnd(hnd_id,bw_win_bua1.get_win_linep(hnd_id,1),bw_win_bua1.get_win_linep(hnd_id,0));
      if (q!=0)
      {
        hnd=bw_win_bua1.get_win_hnd(q);
        GetWindowText(hnd,sf1,SMG_LEN);
      }
      else sf1[0]=0;

      bw_xbase_bua1.set_win_scrnvar(hnd_id,sf1,SMG_LEN);
      bw_dialog_bua1.set_win_mv_getv(hnd_id,sf1,SMG_LEN);
    }

    bw_dialog1.w_mv_sav_var(str1,SMG_LEN,hnd_id);
  }

  if ((str1[0]==':')||(str1[0]=='+'))
  {
    m=bw_buff1.get_linecol(hnd_id,bw_win_bua1.get_win_linep(hnd_id,0),bw_win_bua1.get_win_linep(hnd_id,1));
    if (m>=0) m=bw_win_bua1.get_1fldbase(m);

    bw_inkey1.strpcut(str1,1,strlen(str1)-1,SMG_LEN,fldname,SMG_LEN);

    bw_mbase1.w_down_rec(m,hnd_id,bw_xbase_bua1.get_win_recno(m,hnd_id,0)-1);

    if (str1[0]==':')
    {
      bw_get_bua1.get_smg_string(bw_win_bua1.get_win_pp11(hnd_id),sf1,SMG_LEN);
    }
    else
    {
      q=bw_win1.w_find_hnd(hnd_id,bw_win_bua1.get_win_linep(hnd_id,1),bw_win_bua1.get_win_linep(hnd_id,0));
      if (q!=0)
      {
        hnd=bw_win_bua1.get_win_hnd(q);
        GetWindowText(hnd,sf1,SMG_LEN);
      }
      else sf1[0]=0;
    }

    bw_xbase_bua1.set_win_scrnvar(hnd_id,sf1,SMG_LEN);

    bw_xbase_bua1.get_win_scrnvar(hnd_id,fldvar,SMG_LEN);
    o=bw_fldstru1.w_cmp_tab_var(fldname,SMG_LEN,m,fldvar,SMG_LEN);

    if (o==1)
    {
      if ((bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)!='m')
        &&(bw_fldstru1.w_find_fldtype(fldname,SMG_LEN,m)!='b'))
      {
        bw_fldstru1.w_sav_tab_var(fldname,SMG_LEN,m,fldvar,SMG_LEN);
        bw_mbase1.w_save_rec(m,hnd_id,bw_xbase_bua1.get_win_recno(m,hnd_id,0));
        bw_xbase_bua1.set_win_state5(m,1);
      }
    }
  }

  return(0);
}

int bw_main::get_setup()
{
  int  exist;
  int  i,j,k;
  int  p1,p2;
  int  tn1;
  int  tn2;
  char tc1[SMG_LEN];
  char tc2[20][20];
  char tc3[20][20];
  char tc4[SMG_LEN];
  char tc5[SMG_LEN];
  char tc6[SMG_LEN];
  char tc7[SMG_LEN];
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
    bw_win1.w_atten1("bowo_set.tb0");
    return(1);
  }

  while (!feof(s_fp1))
  {
    fgets(tc1,SMG_LEN,s_fp1);
    bw_inkey1.strtrim(tc1);
    for (i=0;i<(int)strlen(tc1);i++) tc1[i]=bw_inkey1.upper(tc1[i]);
    i=bw_inkey1.strfind(tc1,"=");
    if (i>=0)
    {
      bw_inkey1.strpcut(tc1,  0,              i,SMG_LEN,tc4,SMG_LEN);
      bw_inkey1.strpcut(tc1,i+1,strlen(tc1)-i-1,SMG_LEN,tc5,SMG_LEN);
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
      bw_inkey1.strpcut(tc5,0,i,SMG_LEN,tc6,SMG_LEN);
      bw_inkey1.strpcut(tc5,i+1,strlen(tc5)-i-1,SMG_LEN,tc7,SMG_LEN);
      win_main_xsize=bw_inkey1.char2int(tc6,0,strlen(tc6)-1);
      win_main_ysize=bw_inkey1.char2int(tc7,0,strlen(tc7)-1);
    }

    if (p1==7)
    {
      i=bw_inkey1.strlocc(tc5,',');
      bw_inkey1.strpcut(tc5,0,i,SMG_LEN,tc6,SMG_LEN);
      bw_inkey1.strpcut(tc5,i+1,strlen(tc5)-i-1,SMG_LEN,tc7,SMG_LEN);
      win_main_xposi=bw_inkey1.char2int(tc6,0,strlen(tc6)-1);
      win_main_yposi=bw_inkey1.char2int(tc7,0,strlen(tc7)-1);
    }

    if (p1==8)
    {
      if (p2==8) bw_main1.win_lang=1;
    }

    if (p1==9)
    {
      if (p2==9) win_800=1;
    }

    if (p1==10)
    {
      if (p2==10) win_ibm_s3=1;
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
int bw_main::get_setup_save()
{
  fpos_t lp;
  int    exist;
  int    i,j,k;
  int    p1;
  int    tn1;
//  int    tn2;
  char   tc1[SMG_LEN];
  char   tc2[20][20];
//  char   tc3[20][20];
  char   tc4[SMG_LEN];
  char   tc5[SMG_LEN];
  char   tc6[SMG_LEN];
  char   tc7[SMG_LEN];
  char   tc8[SMG_LEN];
  FILE   *s_fp1;

  tn1=8;
  strcpy(tc2[0],"COLOR");
  strcpy(tc2[1],"PRINTER");
  strcpy(tc2[2],"CONFIRM");
  strcpy(tc2[3],"PAGE");
  strcpy(tc2[4],"PASSWORD");
  strcpy(tc2[5],"DIR");
  strcpy(tc2[6],"SIZE");
  strcpy(tc2[7],"POSITION");
/*  tn2=8;
  strcpy(tc3[0],"EPSON");
  strcpy(tc3[1],"STAR");
  strcpy(tc3[2],"LQ_1600K");
  strcpy(tc3[3],"LQ-1600K");
  strcpy(tc3[4],"AR_3240");
  strcpy(tc3[5],"AR-3240");
  strcpy(tc3[6],"AR_2463");
  strcpy(tc3[7],"AR-2463");
*/

  bw_inkey1.w_set_dir(win_home_dir);

  s_fp1=fopen("bowo_set.tb0","r+");
  if (s_fp1==NULL)
  {
    bw_win1.w_atten1("bowo_set.tb0");
    return(1);
  }

  while (!feof(s_fp1))
  {
    fgetpos(s_fp1,&lp);
    fgets(tc1,(int)SMG_LEN,s_fp1);
    bw_inkey1.strtrim(tc1);
    for (i=0;i<(int)strlen(tc1);i++) tc1[i]=bw_inkey1.upper(tc1[i]);
    i=bw_inkey1.strfind(tc1,"=");
    if (i>=0)
    {
      bw_inkey1.strpcut(tc1,0,i,SMG_LEN,tc4,SMG_LEN);
      bw_inkey1.strpcut(tc1,i+1,strlen(tc1)-i-1,SMG_LEN,tc5,SMG_LEN);
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
    if (i>=0)
    {
      exist=0;
      for (k=0;k<tn1;k++)
      {
	if (strncmp(tc2[k],tc4,j)==0)
	{
	  exist=1;
	  break;
	}
      }
      if (exist==1) p1=k;
/*
      p2=(-1);
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
      if (exist==1) p2=k;*/
    }

    if (p1==6)
    {
      if (IsZoomed(bw_main1.win_hwnd1))
      {
        win_main_xsize=30001;
        win_main_ysize=30001;
      }

      if (IsIconic(bw_main1.win_hwnd1))
      {
        win_main_xsize=0;
        win_main_ysize=0;
      }

      bw_inkey1.int2char(win_main_xsize,tc6);
      bw_inkey1.int2char(win_main_ysize,tc7);
      strcpy(tc8,"size=");
      strcat(tc8,tc6);
      strcat(tc8,",");
      strcat(tc8,tc7);
      strcat(tc8,"\n");
      fseek(s_fp1,(long)lp,0);
      fputs(tc8,s_fp1);
      lp=lp+strlen(tc8);
      fseek(s_fp1,(long)lp,0);
    }

    if (p1==7)
    {
      bw_inkey1.int2char(win_main_xposi,tc6);
      bw_inkey1.int2char(win_main_yposi,tc7);
      strcpy(tc8,"position=");
      strcat(tc8,tc6);
      strcat(tc8,",");
      strcat(tc8,tc7);
      strcat(tc8,"\n");
      fseek(s_fp1,(long)lp,0);
      fputs(tc8,s_fp1);
      lp=lp+strlen(tc8);
      fseek(s_fp1,(long)lp,0);
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

int bw_main::w_ini_main(HINSTANCE s_pins)
{
  WNDCLASS wndclass;

  if (!s_pins)
  {
    wndclass.style         = CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)w_bmp_wp;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = win_ins;
    wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = (LPCTSTR)NULL;
    wndclass.lpszClassName = "bowo_bmp";
    if (!RegisterClass(&wndclass)) return(1);
  
    wndclass.style         = CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)w_main_wp;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = win_ins;
    wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    if (bw_main1.win_lang==1) wndclass.lpszMenuName  = "bowo_main";
    else wndclass.lpszMenuName  = "bowo_cmain";

    wndclass.lpszClassName = "bowo_main";
    if (!RegisterClass(&wndclass)) return(1);

    wndclass.style         = CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)w_menu_wp;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = win_ins;
    wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = "bowo_menu";
    if (!RegisterClass(&wndclass)) return(1);

    wndclass.style         = CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)w_edit_wp;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = win_ins;
    wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor       = NULL;
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    if (bw_main1.win_lang==1) wndclass.lpszMenuName  = "edit_menu";
    else wndclass.lpszMenuName  = "cedit_menu";

    wndclass.lpszClassName = "bowo_edit";
    if (!RegisterClass(&wndclass)) return(1);

    wndclass.style         = CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)w_savep_wp;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = win_ins;
    wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor       = NULL;
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    if (bw_main1.win_lang==1) wndclass.lpszMenuName  = "saveprint_menu";
    else wndclass.lpszMenuName  = "csaveprint_menu";

    wndclass.lpszClassName = "bowo_savep";
    if (!RegisterClass(&wndclass)) return(1);

    wndclass.style         = CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)w_outp_wp;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = win_ins;
    wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor       = NULL;
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    if (bw_main1.win_lang==1) wndclass.lpszMenuName  = "outprint_menu";
    else wndclass.lpszMenuName  = "coutprint_menu";

    wndclass.lpszClassName = "bowo_outp";
    if (!RegisterClass(&wndclass)) return(1);

  }

  return(0);
}
