
/* error 1: WM_CREATE should have break/return */

/* error 2: att to this func(char *s); s[n]=NULL; func(""); */

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

class bw_buff         bw_buff1;
class bw_font         bw_font1;
class bw_user         bw_user1;
class bw_bmp          bw_bmp1;
class bw_print        bw_print1;
class bw_link         bw_link1;
class bw_edit         bw_edit1;
class bw_mbase        bw_mbase1;
class bw_xbase        bw_xbase1;
class bw_main         bw_main1;
class bw_dialog       bw_dialog1;
class bw_rabox        bw_rabox1;
class bw_chkbox       bw_chkbox1;
class bw_win          bw_win1;
class bw_inkey        bw_inkey1;
class bw_getread      bw_getread1;
class bw_fldstru      bw_fldstru1;
class bw_buttonvar    bw_buttonvar1;

extern long  PASCAL w_main_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long  PASCAL w_menu_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long  PASCAL w_edit_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);
extern long  PASCAL w_menu_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long  PASCAL w_menu2_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);
extern long  PASCAL w_tab_ci_wp(HWND hwnd,WORD msg,WORD wp,LONG lp);


int pascal WinMain(HINSTANCE ins
		   ,HINSTANCE pins
		   ,LPSTR cl
		   ,int show)
{
  int           ws;
  int           i;

  //bw_getread1.deb_record_init();  // testing recorder

  bw_main1.mn_ins=ins;
  bw_main1.mn_pins=pins;
  bw_main1.mn_cl=cl;
  bw_main1.mn_show=show;

  bw_main1.get_setup();

  i=bw_main1.w_ini_main(pins);
  if (i!=0) return(0);

  bw_getread1.get_read_ini();

  bw_win1.w_ini_win();

  bw_edit1.w_ini_edit();

  bw_main1.mn_par_win_dbptr=(-1);
  bw_main1.mn_par_win_ptr  =(-1);

  if (bw_main1.mn_main_xsize>30000) ws=SW_SHOWMAXIMIZED;
  else
  {
    if (bw_main1.mn_main_xsize<=0) ws=SW_SHOWMINIMIZED;
    else ws=SW_NORMAL;
  }

  bw_main1.mn_main_hnd=CreateWindow ("bowo_main",
				      "Date Viewer Main Window",
				      WS_OVERLAPPEDWINDOW,
				      50,
				      50,
				      600,
				      200,
				      NULL,
				      NULL,
				      bw_main1.mn_ins,
				      NULL);

  ShowWindow(bw_main1.mn_main_hnd,ws);
  UpdateWindow(bw_main1.mn_main_hnd);

  while (GetMessage(&bw_main1.msg,NULL,NULL,NULL))
  {
    TranslateMessage(&bw_main1.msg);
    DispatchMessage(&bw_main1.msg);
  }

  //bw_getread1.deb_record_close();   //testing recorder

  return bw_main1.msg.wParam;
}

long  PASCAL w_main_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
  int    i,j;
  char   s_dir[FN_SIZE];

  switch(msg)    
  {
    case WM_CREATE:

      bw_main1.mn_hwnd1=hwnd;

      bw_main1.hdc=GetDC(hwnd);
      GetTextMetrics(bw_main1.hdc,&bw_main1.tm);
      bw_main1.mn_xchar=bw_main1.tm.tmAveCharWidth;
      bw_main1.mn_ychar=bw_main1.tm.tmHeight+bw_main1.tm.tmExternalLeading;
      bw_main1.hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
      bw_main1.holdfont=(HFONT)SelectObject(bw_main1.hdc,bw_main1.hfont);
      GetTextMetrics(bw_main1.hdc,&bw_main1.tm);
      bw_main1.mn_edit_xchar=(float)bw_main1.tm.tmAveCharWidth;
      bw_main1.mn_edit_ychar=(float)bw_main1.tm.tmHeight+(float)bw_main1.tm.tmExternalLeading;
      SelectObject(bw_main1.hdc,bw_main1.holdfont);
      ReleaseDC(hwnd,bw_main1.hdc);

      if (bw_main1.mn_ibm_s3==1)
      {
	bw_main1.mn_edit_xchar=(float)(bw_main1.mn_edit_xchar-0.5);
      }

      //if ((bw_main1.mn_main_xsize<=30000)&&(bw_main1.mn_main_xsize>0))
      //{
	//MoveWindow(bw_main1.mn_hwnd,bw_main1.mn_main_xposi,bw_main1.mn_main_yposi,bw_main1.mn_main_xsize,bw_main1.mn_main_ysize,(BOOL)0);
      //}

      //SetTimer(hwnd,1,60000,NULL);

      break;

    case WM_PAINT:

      //bw_main1.get_ms_face_bmp1(bw_main1.mn_face_ptr2,bw_main1.ms_face_bmp0,FN_SIZE);

      //bw_inkey1.w_get_dir(s_dir,FN_SIZE);

      //bw_inkey1.w_set_dir(bw_main1.ms_well_dir);

      //i=bw_bmp1.DIB(bw_main1.ms_face_bmp0,FN_SIZE);
      //if (i==0) bw_bmp1.DisplayDIB(bw_main1.mn_hwnd,0,0,(LPSTR)bw_main1.ms_face_bmp0);
      //else GlobalFree(bw_bmp1.hbiCurrent);

      //bw_inkey1.w_set_dir(s_dir);

      break;

    case WM_TIMER:
/*
      if (wp==1)
      {
	bw_main1.mn_face_ptr2++;
	if (bw_main1.mn_face_ptr2>10) bw_main1.mn_face_ptr2=0;

	bw_main1.get_ms_face_bmp1(bw_main1.mn_face_ptr2,bw_main1.ms_face_bmp0,FN_SIZE);

	bw_inkey1.w_get_dir(s_dir,FN_SIZE);

	bw_inkey1.w_set_dir(bw_main1.ms_well_dir);

	i=bw_bmp1.DIB(bw_main1.ms_face_bmp0,FN_SIZE);
	if (i==0) bw_bmp1.DisplayDIB(bw_main1.mn_hwnd,0,0,(LPSTR)bw_main1.ms_face_bmp0);
	else GlobalFree(bw_bmp1.hbiCurrent);

	bw_inkey1.w_set_dir(s_dir);
      }
*/
      break;

    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:

      i=bw_inkey1.inkey(msg,wp);

      if (i==1)
      {
        if (bw_main1.mn_key==274) // up arrow
        {
          bw_getread1.deb_record("begin...");

          bw_fldstru1.tst_stru2();
          bw_getread1.tst_getread();
          bw_link1.tst_link1_lkchar();
          bw_link1.tst_link2();
          bw_link1.tst_link4();
          bw_link1.tst_link5_svar();
          bw_buttonvar1.tst_button2();
          bw_chkbox1.tst_chkbox();
          bw_rabox1.tst_rabox();
          bw_print1.tst_p1();
          bw_print1.tst_p2();
          bw_print1.tst_p3();
          bw_win1.tst_win1_fld();
          bw_win1.tst_win2_fld_in_win();
          bw_win1.tst_win3();
          bw_win1.tst_win4();
          bw_win1.tst_win5();
          bw_win1.tst_win6_ci_ptr();
          bw_win1.tst_hptr3();
          bw_win1.tst_hptr4();
          bw_xbase1.tst_xbase1();
          bw_xbase1.tst_xbase2();

          bw_getread1.deb_record("...end");
        }
      }

      break;

    case WM_COMMAND:

      if (wp==1107)
      {
	//bw_main1.get_setup_save();
	//KillTimer(hwnd,1);

	PostQuitMessage(0);
      }

      if ((wp>=1126)&&(wp<=1135))
      {
	if (bw_main1.mn_lang==1)
	{
		if (wp==1126) strcpy(bw_main1.ms_seaname,"*.sc1");
		if (wp==1127) strcpy(bw_main1.ms_seaname,"*.sc3");
		if (wp==1128) strcpy(bw_main1.ms_seaname,"*.sc3");
		if (wp==1129) strcpy(bw_main1.ms_seaname,"*.*");
		if (wp==1130) strcpy(bw_main1.ms_seaname,"*.sc3");
		if (wp==1131) strcpy(bw_main1.ms_seaname,"*.sc5");
		if (wp==1132) strcpy(bw_main1.ms_seaname,"*.sc6");
		if (wp==1133) strcpy(bw_main1.ms_seaname,"*.sc2");
	}
	else
	{
		if (wp==1126) strcpy(bw_main1.ms_seaname,"*.sc1");
		if (wp==1127) strcpy(bw_main1.ms_seaname,"*.sc4");
		if (wp==1128) strcpy(bw_main1.ms_seaname,"*.sc4");
		if (wp==1129) strcpy(bw_main1.ms_seaname,"*.*");
		if (wp==1130) strcpy(bw_main1.ms_seaname,"*.sc4");
		if (wp==1131) strcpy(bw_main1.ms_seaname,"*.sc5");
		if (wp==1132) strcpy(bw_main1.ms_seaname,"*.sc6");
		if (wp==1133) strcpy(bw_main1.ms_seaname,"*.sc2");
	}

	strcpy(bw_main1.ms_m_ts0,bw_main1.ms_seaname);
	strcpy(bw_main1.ms_m_ts6,"Select File To Run");
	bw_main1.dlg_f1.lStructSize=sizeof(OPENFILENAME);
	bw_main1.dlg_f1.hwndOwner=bw_main1.mn_hwnd1;
	strcpy(bw_main1.ms_m_ts1,"ALL Text File");
	strcat(bw_main1.ms_m_ts1,"(");
	strcat(bw_main1.ms_m_ts1,bw_main1.ms_m_ts0);
	strcat(bw_main1.ms_m_ts1,")");
	j=strlen(bw_main1.ms_m_ts1);
	for (i=0;i<=(int)strlen(bw_main1.ms_m_ts0);i++) bw_main1.ms_m_ts1[j+1+i]=bw_main1.ms_m_ts0[i];
	bw_main1.ms_m_ts1[j+1+i]=0;
	bw_main1.dlg_f1.lpstrFilter=bw_main1.ms_m_ts1;
	bw_main1.dlg_f1.nFilterIndex=1;
	strcpy(bw_main1.ms_m_ts2,bw_main1.ms_m_ts0);
	bw_main1.dlg_f1.lpstrFile=bw_main1.ms_m_ts2;
	bw_main1.dlg_f1.nMaxFile=FN_SIZE;
	bw_main1.dlg_f1.lpstrFileTitle=bw_main1.ms_m_ts3;
	bw_main1.dlg_f1.nMaxFileTitle=FN_SIZE;
	bw_main1.dlg_f1.lpstrInitialDir=NULL;
	bw_main1.dlg_f1.lpstrTitle=bw_main1.ms_m_ts6;
	strcpy(bw_main1.ms_m_ts4,"txt");
	bw_main1.dlg_f1.lpstrDefExt=bw_main1.ms_m_ts4;
	bw_main1.dlg_f1.lpstrCustomFilter=bw_main1.ms_m_ts5;
	bw_main1.dlg_f1.nMaxCustFilter=FN_SIZE;
	bw_main1.dlg_f1.nFileOffset=NULL;
	bw_main1.dlg_f1.nFileExtension=NULL;
	bw_main1.dlg_f1.Flags=NULL;

	i=GetOpenFileName(&bw_main1.dlg_f1);
        if (i==0) return(1);

	strcpy(bw_main1.ms_m_ts7,bw_main1.dlg_f1.lpstrFile);
	bw_main1.w_fetch_filename(bw_main1.ms_m_ts7,FN_SIZE);

	if (bw_inkey1.w_fname_ok(bw_main1.ms_seaname,FN_SIZE)==1)
	{
	  strcpy(bw_main1.ms_cpy_f1,bw_main1.ms_seadir);
	  bw_inkey1.strtrim(bw_main1.ms_cpy_f1,FN_SIZE);

	  chdir(bw_main1.ms_cpy_f1);
	  strcpy(bw_main1.ms_cpy_f1,bw_main1.ms_seaname);

 	  i=bw_win1.w_first_grp();
	  if (i<0) return(1);
	  bw_main1.get_view(bw_main1.ms_cpy_f1,FN_SIZE,hwnd,i);

	  return(0);
	}
	else bw_win1.w_atten25(bw_main1.mn_hwnd1,bw_main1.ms_seaname);
      }

      if (wp==1122)
      {
	i=bw_win1.w_first_grp();
	if (i<0) return(1);
        strcpy(bw_main1.ms_cpy_f1,"atten60.sc3");
	bw_main1.get_view(bw_main1.ms_cpy_f1,FN_SIZE,hwnd,i);
        return(0);
      }
      if (wp==1123)
      {
	i=bw_win1.w_first_grp();
	if (i<0) return(1);
        strcpy(bw_main1.ms_cpy_f1,"atten61.sc3");
	bw_main1.get_view(bw_main1.ms_cpy_f1,FN_SIZE,hwnd,i);
        return(0);
      }
/*
      if (wp==1191)
      {
	chdir("..");
	chdir("..");
	chdir("..");
	chdir("bowo2");
	chdir("fdcw");
	chdir("zc");
	i=bw_win1.w_first_grp();
	if (i<0) return(1);
	strcpy(bw_main1.ms_cpy_f1,"bowo_dc.sc3");
	bw_main1.get_view(bw_main1.ms_cpy_f1,FN_SIZE,hwnd,i);
        return(0);
      }
*//*
      if (wp==1192)
      {
	chdir("..");
	chdir("..");
	chdir("..");
	chdir("bowo2");
	chdir("slw");
	i=bw_win1.w_first_grp();
	if (i<0) return(1);
	strcpy(bw_main1.ms_cpy_f1,"sl1x.sc3");
	bw_main1.get_view(bw_main1.ms_cpy_f1,FN_SIZE,hwnd,i);
	return(0);
      }
*/
/*
      if (wp==1140)
      {
	 bw_main1.dlg_f2.lStructSize=sizeof(PRINTDLG);
	 bw_main1.dlg_f2.hwndOwner=hwnd;
	 bw_main1.dlg_f2.hDevMode=NULL;

	 PrintDlg(&bw_main1.dlg_f2);
      }
*/
      break;

    case WM_MOVE:
    case WM_SIZE:

      GetWindowRect(bw_main1.mn_hwnd1,&bw_main1.rt);

      bw_main1.mn_main_xposi=bw_main1.rt.left;
      bw_main1.mn_main_yposi=bw_main1.rt.top;
      bw_main1.mn_main_xsize=bw_main1.rt.right-bw_main1.rt.left+1;
      bw_main1.mn_main_ysize=bw_main1.rt.bottom-bw_main1.rt.top+1;

      break;

    case WM_SYSCOMMAND:
    {
      if ((0-wp==4000)||(wp==61536))
      {
	//bw_main1.get_setup_save();
        //KillTimer(hwnd,1);

	PostQuitMessage(0);
      }
    }
  }

  return DefWindowProc(hwnd,msg,wp,lp);
}

