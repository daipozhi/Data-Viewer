
/* error 1: WM_CREATE should have break/return */

/* error 2: att to this func(char *s); s[n]=NULL;func(""); */

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
class bw_switch       bw_switch1;
class bw_choose       bw_choose1;
class bw_win          bw_win1;
class bw_inkey        bw_inkey1;
class bw_getread      bw_getread1;
class bw_fldstru      bw_fldstru1;
class bw_menuvar      bw_menuvar1;

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
//  int           s_state1,s_state2;
  int           i;

  //bw_getread1.deb_record_init();  // test recorder

  bw_main1.win_ins=ins;
  bw_main1.win_pins=pins;
  bw_main1.win_cl=cl;
  bw_main1.win_show=show;

  bw_main1.get_setup();

  i=bw_main1.w_ini_main(pins);
  if (i!=0) return(0);
/*
HCURSOR CreateCursor( HINSTANCE hInst, 
			int xHotSpot, 
			int yHotSpot, 
			int nWidth, 
			int nHeight, 
			CONST VOID *pvANDPlane, 
			CONST VOID *pvXORPlane);
*/

  bw_getread1.get_read_ini();

  bw_win1.w_ini_win();

  bw_edit1.w_ini_edit();

  if (bw_main1.win_main_xsize>30000) ws=SW_SHOWMAXIMIZED;
  else
  {
    if (bw_main1.win_main_xsize<=0) ws=SW_SHOWMINIMIZED;
    else ws=SW_NORMAL;
  }

  bw_main1.win_main_hnd=CreateWindow ("bowo_main",
				      "Date Viewer Main Window",
				      WS_OVERLAPPEDWINDOW,
				      50,
				      50,
				      501,
				      301,
				      NULL,
				      NULL,
				      bw_main1.win_ins,
				      NULL);

  ShowWindow(bw_main1.win_main_hnd,ws);
  UpdateWindow(bw_main1.win_main_hnd);

  while (GetMessage(&bw_main1.msg,NULL,NULL,NULL))
  {
    TranslateMessage(&bw_main1.msg);
    DispatchMessage(&bw_main1.msg);
  }

  //bw_getread1.deb_record_close();//test recorder

  return bw_main1.msg.wParam;
}

long  PASCAL w_main_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{

//  int    state1;  
  int    i,j;
//  char   str[SMG_LEN];
  char   sdir[FN_SIZE];

  bw_main1.win_msg=msg;
  bw_main1.win_wp=wp;
  bw_main1.win_hwnd=hwnd;
  bw_main1.win_hwnd1=hwnd;
  bw_main1.win_lp=lp;

  switch(msg)    
  {
    case WM_CREATE:

      bw_main1.hdc=GetDC(hwnd);
      GetTextMetrics(bw_main1.hdc,&bw_main1.tm);
      bw_main1.win_xchar=bw_main1.tm.tmAveCharWidth;
      bw_main1.win_ychar=bw_main1.tm.tmHeight+bw_main1.tm.tmExternalLeading;
      bw_main1.hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
      bw_main1.holdfont=(HFONT)SelectObject(bw_main1.hdc,bw_main1.hfont);
      GetTextMetrics(bw_main1.hdc,&bw_main1.tm);
      bw_main1.win_edit_xchar=(float)bw_main1.tm.tmAveCharWidth;
      bw_main1.win_edit_ychar=(float)bw_main1.tm.tmHeight+(float)bw_main1.tm.tmExternalLeading;
      SelectObject(bw_main1.hdc,bw_main1.holdfont);
      ReleaseDC(hwnd,bw_main1.hdc);

      if (bw_main1.win_ibm_s3==1)
      {
	bw_main1.win_edit_xchar=(float)(bw_main1.win_edit_xchar-0.5);
      }

      if ((bw_main1.win_main_xsize<=30000)&&(bw_main1.win_main_xsize>0))
      {
	MoveWindow(bw_main1.win_hwnd,bw_main1.win_main_xposi,bw_main1.win_main_yposi,bw_main1.win_main_xsize,bw_main1.win_main_ysize,(BOOL)0);
      }

      SetTimer(hwnd,1,60000,NULL);

      break;

    case WM_PAINT:

      bw_main1.get_win_face_bmp1(bw_main1.win_face_pp2,bw_main1.win_face_bmp0,FN_SIZE);

      bw_inkey1.w_get_dir(sdir,FN_SIZE);

      bw_inkey1.w_set_dir(bw_main1.win_well_dir);

      i=bw_bmp1.DIB(bw_main1.win_face_bmp0,FN_SIZE);
      if (i==0) bw_bmp1.DisplayDIB(bw_main1.win_hwnd,0,0,(LPSTR)bw_main1.win_face_bmp0);
      else GlobalFree(bw_bmp1.hbiCurrent);

      bw_inkey1.w_set_dir(sdir);

      break;

    case WM_TIMER:

      if (wp==1)
      {
	bw_main1.win_face_pp2++;
	if (bw_main1.win_face_pp2>10) bw_main1.win_face_pp2=0;

	bw_main1.get_win_face_bmp1(bw_main1.win_face_pp2,bw_main1.win_face_bmp0,FN_SIZE);

	bw_inkey1.w_get_dir(sdir,FN_SIZE);

	bw_inkey1.w_set_dir(bw_main1.win_well_dir);

	i=bw_bmp1.DIB(bw_main1.win_face_bmp0,FN_SIZE);
	if (i==0) bw_bmp1.DisplayDIB(bw_main1.win_hwnd,0,0,(LPSTR)bw_main1.win_face_bmp0);
	else GlobalFree(bw_bmp1.hbiCurrent);

	bw_inkey1.w_set_dir(sdir);

      }

      break;

    case WM_COMMAND:

      if (wp==1107)
      {
	bw_main1.get_setup_save();

	KillTimer(hwnd,1);

	PostQuitMessage(0);
      }

      if ((wp>=1126)&&(wp<=1135))
      {

	if (bw_main1.win_lang==1)
	{
		if (wp==1126) strcpy(bw_main1.win_seaname,"*.sc1");
		if (wp==1127) strcpy(bw_main1.win_seaname,"*.sc3");
		if (wp==1128) strcpy(bw_main1.win_seaname,"*.sc3");
		if (wp==1129) strcpy(bw_main1.win_seaname,"*.*");
		if (wp==1130) strcpy(bw_main1.win_seaname,"*.sc3");
		if (wp==1131) strcpy(bw_main1.win_seaname,"*.sc5");
		if (wp==1132) strcpy(bw_main1.win_seaname,"*.sc6");
		if (wp==1133) strcpy(bw_main1.win_seaname,"*.sc2");
	}
	else
	{
		if (wp==1126) strcpy(bw_main1.win_seaname,"*.sc1");
		if (wp==1127) strcpy(bw_main1.win_seaname,"*.sc4");
		if (wp==1128) strcpy(bw_main1.win_seaname,"*.sc4");
		if (wp==1129) strcpy(bw_main1.win_seaname,"*.*");
		if (wp==1130) strcpy(bw_main1.win_seaname,"*.sc4");
		if (wp==1131) strcpy(bw_main1.win_seaname,"*.sc5");
		if (wp==1132) strcpy(bw_main1.win_seaname,"*.sc6");
		if (wp==1133) strcpy(bw_main1.win_seaname,"*.sc2");
	}

	strcpy(bw_main1.s_tc0,bw_main1.win_seaname);
	strcpy(bw_main1.s_tc6,"Select File To Run");
	bw_main1.dlg_f1.lStructSize=sizeof(OPENFILENAME);
	bw_main1.dlg_f1.hwndOwner=bw_main1.win_hwnd;
	strcpy(bw_main1.s_tc1,"ALL Text File");
	strcat(bw_main1.s_tc1,"(");
	strcat(bw_main1.s_tc1,bw_main1.s_tc0);
	strcat(bw_main1.s_tc1,")");
	j=strlen(bw_main1.s_tc1);
	for (i=0;i<=(int)strlen(bw_main1.s_tc0);i++) bw_main1.s_tc1[j+1+i]=bw_main1.s_tc0[i];
	bw_main1.s_tc1[j+1+i]=0;
	bw_main1.dlg_f1.lpstrFilter=bw_main1.s_tc1;
	bw_main1.dlg_f1.nFilterIndex=1;
	strcpy(bw_main1.s_tc2,bw_main1.s_tc0);
	bw_main1.dlg_f1.lpstrFile=bw_main1.s_tc2;
	bw_main1.dlg_f1.nMaxFile=FN_SIZE;
	bw_main1.dlg_f1.lpstrFileTitle=bw_main1.s_tc3;
	bw_main1.dlg_f1.nMaxFileTitle=FN_SIZE;
	bw_main1.dlg_f1.lpstrInitialDir=NULL;
	bw_main1.dlg_f1.lpstrTitle=bw_main1.s_tc6;
	strcpy(bw_main1.s_tc4,"txt");
	bw_main1.dlg_f1.lpstrDefExt=bw_main1.s_tc4;
	bw_main1.dlg_f1.lpstrCustomFilter=bw_main1.s_tc5;
	bw_main1.dlg_f1.nMaxCustFilter=FN_SIZE;
	bw_main1.dlg_f1.nFileOffset=NULL;
	bw_main1.dlg_f1.nFileExtension=NULL;
	bw_main1.dlg_f1.Flags=NULL;

	i=GetOpenFileName(&bw_main1.dlg_f1);
        if (i==0) return(1);

	strcpy(bw_main1.s_tc7,bw_main1.dlg_f1.lpstrFile);
	bw_main1.w_fetch_filename(bw_main1.s_tc7,FN_SIZE);

	if (bw_inkey1.w_fname_ok(bw_main1.win_seaname)==1)
	{
	  strcpy(bw_main1.win_cpy_f1,bw_main1.win_seadir);
	  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);

	  chdir(bw_main1.win_cpy_f1);
	  strcpy(bw_main1.win_cpy_f1,bw_main1.win_seaname);

 	  i=bw_win1.w_first_pp5();
	  if (i<0) return(1);
	  bw_main1.get_view(bw_main1.win_cpy_f1,FN_SIZE,hwnd,i);

	  return(0);
	}
	else bw_win1.w_atten25(bw_main1.win_seaname);
      }

      if (wp==1122)
      {
	i=bw_win1.w_first_pp5();
	if (i<0) return(1);
        strcpy(bw_main1.win_cpy_f1,"atten60.sc3");
	bw_main1.get_view(bw_main1.win_cpy_f1,FN_SIZE,hwnd,i);
        return(0);
      }
      if (wp==1123)
      {
	i=bw_win1.w_first_pp5();
	if (i<0) return(1);
        strcpy(bw_main1.win_cpy_f1,"atten61.sc3");
	bw_main1.get_view(bw_main1.win_cpy_f1,FN_SIZE,hwnd,i);
        return(0);
      }

      if (wp==1191)
      {
	chdir("..");
	chdir("..");
	chdir("..");
	chdir("bowo2");
	chdir("fdcw");
	chdir("zc");
	i=bw_win1.w_first_pp5();
	if (i<0) return(1);
	strcpy(bw_main1.win_cpy_f1,"bowo_dc.sc3");
	bw_main1.get_view(bw_main1.win_cpy_f1,FN_SIZE,hwnd,i);
        return(0);
      }

      if (wp==1192)
      {
	chdir("..");
	chdir("..");
	chdir("..");
	chdir("bowo2");
	chdir("slw");
	i=bw_win1.w_first_pp5();
	if (i<0) return(1);
	strcpy(bw_main1.win_cpy_f1,"sl1x.sc3");
	bw_main1.get_view(bw_main1.win_cpy_f1,FN_SIZE,hwnd,i);
	return(0);
      }

      if (wp==1201) bw_dialog1.tst_mem();
      if (wp==1202) bw_win1.tst_hpp3();
      if (wp==1203) bw_switch1.tst_switch();
      if (wp==1204) bw_menuvar1.tst_menu();
      if (wp==1205) bw_choose1.tst_choose();
      if (wp==1206) bw_win1.tst_win1();
      if (wp==1207) bw_win1.tst_win2();
      if (wp==1208) bw_win1.tst_hpp4();
      if (wp==1209) bw_getread1.tst_getread();
      if (wp==1210) bw_fldstru1.tst_stru();
      if (wp==1211) bw_xbase1.tst_xbase1();
      if (wp==1212) bw_xbase1.tst_xbase2();
      if (wp==1213) bw_win1.tst_win3();
      if (wp==1214) bw_link1.tst_link1();
      if (wp==1215) bw_link1.tst_link2();
      if (wp==1216) bw_link1.tst_link3();
      if (wp==1217) bw_link1.tst_link4();
      if (wp==1218) bw_win1.tst_win4();
      if (wp==1219) bw_win1.tst_win5();
      if (wp==1220) bw_link1.tst_link5();
      if (wp==1221) bw_print1.tst_p1();
      if (wp==1222) bw_print1.tst_p2();
      if (wp==1223) bw_print1.tst_p3();
      if (wp==1224) bw_bmp1.tst_b1();
      if (wp==1225) bw_win1.tst_win6();
      if (wp==1226) bw_edit1.tst_dirn_file();

      if (wp==1136) bw_main1.win_color=0;
      if (wp==1137) bw_main1.win_color=1;
      if (wp==1138) bw_main1.win_confirm=0;
      if (wp==1139) bw_main1.win_confirm=1;
      if (wp==1140)
      {
	 bw_main1.dlg_f2.lStructSize=sizeof(PRINTDLG);
	 bw_main1.dlg_f2.hwndOwner=hwnd;
	 bw_main1.dlg_f2.hDevMode=NULL;

	 PrintDlg(&bw_main1.dlg_f2);
      }

      //if (wp==1141) bw_main1.get_xbase_open();
      //if (wp==1142) bw_main1.get_skip(1);
      //if (wp==1143) bw_main1.get_skip(-1);
      //if (wp==1144) bw_main1.get_insert();
      //if (wp==1145) bw_main1.get_delete();
      //if (wp==1146) bw_main1.get_display();
      //if (wp==1147) bw_main1.get_setrecno();
      //if (wp==1148) bw_main1.get_locate();
      //if (wp==1149) bw_main1.get_commit();
      //if (wp==1150) bw_main1.get_rollback();
      //if (wp==1151) bw_main1.get_close();

      break;

    case WM_MOVE:
    case WM_SIZE:

      GetWindowRect(bw_main1.win_hwnd,&bw_main1.rt);

      bw_main1.win_main_xposi=bw_main1.rt.left;
      bw_main1.win_main_yposi=bw_main1.rt.top;
      bw_main1.win_main_xsize=bw_main1.rt.right-bw_main1.rt.left+1;
      bw_main1.win_main_ysize=bw_main1.rt.bottom-bw_main1.rt.top+1;

      break;

    case WM_SYSCOMMAND:
    {
      if ((0-wp==4000)||(wp==61536))
      {
	bw_main1.get_setup_save();

        KillTimer(hwnd,1);

	PostQuitMessage(0);
      }
    }
  }

  return DefWindowProc(hwnd,msg,wp,lp);
}

