#define _CRT_SECURE_NO_WARNINGS

// (char *s1,no need len)

//#define STRICT
#include "windows.h"
/*
#include <commdlg.h>
*/
#include <stdio.h>
/*
#include <math.h>
//#include <dir.h>
#include <dos.h>
//#include <bios.h>
#include <conio.h>
#include <process.h>
*/
#include <string.h>
/*
#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>
*/


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/io.h>


#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_xbase_bua    bw_xbase_bua1;
extern class bw_edit_bua     bw_edit_bua1;
extern class bw_win_bua      bw_win_bua1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_edit         bw_edit1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;

int bw_edit::get_edit(char *p_s1,int wpp,HWND hwnd)
{
  HWND    hnd;
  int     s_hp1;
  int     i,j,k,l;
  int     exist;
  int     cp1;
  //char    str[SMG_LEN];
  char    stn[FN_SIZE];

  exist=0;

  //i=1; can not be this i=0;
  for (i=1;i<EDIT_NUM;i++)
  {
    if (bw_edit_bua1.get_win_edit_inuse(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  win_edit_pp1=i;

  bw_inkey1.w_get_dir(stn,FN_SIZE);

  bw_edit_bua1.set_win_edit_dirn(win_edit_pp1,stn,FN_SIZE);

  bw_edit_bua1.set_win_edit_file(win_edit_pp1,p_s1,strlen(p_s1)+1);

  bw_edit_bua1.set_win_edit_inuse(win_edit_pp1,1);
/*
  s_hp1=sopen(p_s1,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_hp1<0)
  {
    bw_win1.w_atten1(p_s1);
    return(0);
  }
*/
  if (win_edit_pp1>=EDIT_NUM) return(0);

  i=win_edit_pp1;
  while (i>3)
  {
    i=i-3;
  }

  j=win_edit_pp1;
  while (j>7)
  {
    j=j-7;
  }

  if (bw_main1.win_800==1)
  {
    i=0;
    j=0;
    k=800;
    l=600;
  }
  else
  {
    k=600;
    l=480;
  }
/*
  hnd=CreateWindow ("bowo_edit",
		"Date Viewer Editor Window",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		i*30,
		j*30,
		k,
		l,
		hwnd,
		0,
		bw_main1.win_ins,
		0);
*/
  bw_edit_bua1.set_win_edit_hnd1(win_edit_pp1,hnd);

  cp1=read(s_hp1,bw_inkey1.tmpc4,CPY_BSIZE);
  bw_inkey1.tmpc4[cp1]=0;
                
  close(s_hp1);

  SetWindowText(bw_edit_bua1.get_win_edit_hnd2(win_edit_pp1),bw_inkey1.tmpc4);

  bw_edit_bua1.set_win_edit_modi(win_edit_pp1,0);

  if (wpp>0) bw_edit_bua1.set_win_edit_wpp(win_edit_pp1,wpp);
  else bw_edit_bua1.set_win_edit_wpp(win_edit_pp1,0);

  win_edit_pp1++;

  return(0);
}

int bw_edit::w_find_edithand(HWND hwnd)
{
  int i;
  int exist;

  exist=0;
  for (i=1;i<win_edit_pp1;i++)
  {
    if (hwnd==bw_edit_bua1.get_win_edit_hnd1(i))
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);
  else return(i);
}
// _export
long /*PASCAL*/ w_edit_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
  HWND    hnd;
//  HCURSOR hcursor;
//  HDC     hdc;
  RECT    rt;
  HFONT   hfont;

  int     i,j,k,l;
  int     s_hp1;
  char    str[SMG_LEN];
  char    tl1[11][2];
  char    tl2[11][3];
  char    stn[FN_SIZE];
  char    sf1[FN_SIZE];

  bw_main1.win_msg=msg;
  bw_main1.win_wp=wp;
  bw_main1.win_hwnd=hwnd;
  bw_main1.win_lp=lp;

  switch(msg)    
  {
    case WM_CREATE:
    {
/*
      GetClientRect(hwnd,&rt);

      k=rt.right-rt.left+1;
      l=rt.bottom-rt.top+1;

      hnd=CreateWindow("edit",NULL
		 ,WS_CHILD|WS_VISIBLE|WS_HSCROLL
		 |WS_VSCROLL|WS_BORDER|ES_LEFT
		 |ES_MULTILINE|ES_AUTOHSCROLL
		 |ES_AUTOVSCROLL
		 ,0,0,k,l
		 ,bw_main1.win_hwnd,(HMENU)bw_edit1.win_edit_pp1
		 ,bw_main1.win_ins,NULL);

      bw_edit_bua1.set_win_edit_hnd2(bw_edit1.win_edit_pp1,hnd);

      hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);

      SendMessage(bw_edit_bua1.get_win_edit_hnd2(bw_edit1.win_edit_pp1)
		 ,WM_SETFONT
		 ,(WPARAM)hfont
                 ,(LPARAM)str);
*/
      return(0);
    }
    case WM_SIZE:
    {
/*
      i=bw_edit1.w_find_edithand(hwnd);

      GetClientRect(hwnd,&rt);

      k=rt.right-rt.left+1;
      l=rt.bottom-rt.top+1;

      MoveWindow(bw_edit_bua1.get_win_edit_hnd2(i),0,0,k,l,1);
*/
    }
    case WM_COMMAND:
    {
/*
      i=bw_edit1.w_find_edithand(hwnd);

      if (HIWORD(lp)==EN_CHANGE) bw_edit_bua1.set_win_edit_modi(i,1);

      if (wp==1801)
      {
	if ((bw_edit_bua1.get_win_edit_wpp(i)<=0)&&(bw_edit_bua1.get_win_edit_modi(i)==1))
        {
	  GetWindowText(bw_edit_bua1.get_win_edit_hnd2(i),bw_inkey1.tmpc4,CPY_BSIZE);

	  j=GetWindowTextLength(bw_edit_bua1.get_win_edit_hnd2(i));
          bw_inkey1.tmpc4[j]=0;


          bw_edit_bua1.get_win_edit_dirn(i,stn,FN_SIZE);
	  bw_inkey1.w_set_dir(stn);

          bw_edit_bua1.get_win_edit_file(i,stn,FN_SIZE);
	  s_hp1=sopen(stn,O_RDWR|O_TRUNC|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
          if (s_hp1>=0)
          {
            write(s_hp1,bw_inkey1.tmpc4,strlen(bw_inkey1.tmpc4));
            close(s_hp1);
          }

	  bw_edit_bua1.set_win_edit_modi(i,0);

	}

      }
      if (wp==1802)
      {
	bw_edit_bua1.get_win_edit_dirn(i,stn,FN_SIZE);
	bw_inkey1.w_set_dir(stn);

	bw_edit_bua1.get_win_edit_file(i,stn,FN_SIZE);
	s_hp1=sopen(stn,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
        if (s_hp1>=0)
        {
          j=read(s_hp1,bw_inkey1.tmpc4,CPY_BSIZE);
          bw_inkey1.tmpc4[j]=0;
          close(s_hp1);
        }


	SetWindowText(bw_edit_bua1.get_win_edit_hnd2(i),bw_inkey1.tmpc4);

	bw_edit_bua1.set_win_edit_modi(i,0);

      }
      if (wp==1803)
      {
	if (bw_edit_bua1.get_win_edit_modi(i)==1)
        {
	  bw_edit_bua1.get_win_edit_file(i,stn,FN_SIZE);
	  k=bw_win1.w_atten64(stn);
        }
        else k=0;

        if (k==1)
        {
	  GetWindowText(bw_edit_bua1.get_win_edit_hnd2(i),bw_inkey1.tmpc4,CPY_BSIZE);

	  j=GetWindowTextLength(bw_edit_bua1.get_win_edit_hnd2(i));
          bw_inkey1.tmpc4[j]=0;

	  bw_edit_bua1.get_win_edit_dirn(i,stn,FN_SIZE);
	  bw_inkey1.w_set_dir(stn);

	  bw_edit_bua1.get_win_edit_file(i,stn,FN_SIZE);
	  s_hp1=sopen(stn,O_RDWR|O_TRUNC|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
          if (s_hp1>=0)
          {
            write(s_hp1,bw_inkey1.tmpc4,strlen(bw_inkey1.tmpc4));
            close(s_hp1);
          }
	}

	DestroyWindow(bw_edit_bua1.get_win_edit_hnd1(i));

        bw_edit_bua1.set_win_edit_inuse(i,0);

	if ((bw_edit_bua1.get_win_edit_wpp(i)>0)&&(bw_edit_bua1.get_win_edit_modi(i)==1))
	{
	  bw_fldstru1.w_edit_memo_close(bw_edit_bua1.get_win_edit_wpp(i));
	  bw_edit_bua1.set_win_edit_wpp(i,0);
	  bw_edit_bua1.set_win_edit_modi(i,0);
        }
	else
	{
	  if (bw_edit_bua1.get_win_edit_wpp(i)>0)
	  {
	    j=bw_edit_bua1.get_win_edit_wpp(i);
	    k=bw_win_bua1.get_win_memo_basep(j);
	    bw_xbase_bua1.set_win_mem_inuse(k,0);

	    bw_xbase_bua1.get_win_mem_fn(k,sf1,FN_SIZE);
	    bw_inkey1.w_del_file(sf1);
	  }
        }

	SetFocus(bw_main1.win_hwnd1);
      }
      if (wp==1804)
      {
	DestroyWindow(bw_edit_bua1.get_win_edit_hnd1(i));

	bw_edit_bua1.set_win_edit_inuse(i,0);

	bw_edit_bua1.set_win_edit_modi(i,0);

	j=bw_edit_bua1.get_win_edit_wpp(i);
	k=bw_win_bua1.get_win_memo_basep(j);
	bw_win_bua1.set_win_memo_basep(j,0);
	bw_xbase_bua1.set_win_mem_inuse(k,0);
	bw_xbase_bua1.set_win_mem_wpp(k,0);
	bw_xbase_bua1.setc_win_mem_fn(k,0,0);

	bw_edit_bua1.set_win_edit_wpp(i,0);

	SetFocus(bw_main1.win_hwnd1);
      }
      if (wp==1811)
      {
	j=SendMessage(bw_edit_bua1.get_win_edit_hnd2(i)
		 ,EM_CANUNDO
		 ,0
                 ,(LPARAM)str);

        if (j==0)
        {
          bw_win1.w_atten65();
        }
        else
        {
	  SendMessage(bw_edit_bua1.get_win_edit_hnd2(i)
		 ,WM_UNDO
		 ,0
                 ,(LPARAM)str);

        }
      }
      if (wp==1812)
      {
	SendMessage(bw_edit_bua1.get_win_edit_hnd2(i)
		 ,WM_CUT
		 ,0
                 ,(LPARAM)str);

      }
      if (wp==1813)
      {
	SendMessage(bw_edit_bua1.get_win_edit_hnd2(i)
		 ,WM_COPY
		 ,0
                 ,(LPARAM)str);

      }
      if (wp==1814)
      {
	SendMessage(bw_edit_bua1.get_win_edit_hnd2(i)
		 ,WM_PASTE
		 ,0
                 ,(LPARAM)str);

      }

      if ((wp/10==182)||(wp/10==183))
      {
        tl1[0][0]=(char)218;
        tl1[0][1]=0;

        tl1[1][0]=(char)194;
        tl1[1][1]=0;

        tl1[2][0]=(char)191;
        tl1[2][1]=0;

        tl1[3][0]=(char)195;
        tl1[3][1]=0;

        tl1[4][0]=(char)197;
        tl1[4][1]=0;

        tl1[5][0]=(char)180;
        tl1[5][1]=0;

        tl1[6][0]=(char)192;
        tl1[6][1]=0;

        tl1[7][0]=(char)193;
        tl1[7][1]=0;

        tl1[8][0]=(char)217;
        tl1[8][1]=0;

        tl1[9][0]=(char)196;
        tl1[9][1]=0;

        tl1[10][0]=(char)179;
        tl1[10][1]=0;

        strcpy(tl2[0],"©°");
        strcpy(tl2[1],"©Ð");
        strcpy(tl2[2],"©´");

        strcpy(tl2[3],"©À");
        strcpy(tl2[4],"©à");
        strcpy(tl2[5],"©È");

        strcpy(tl2[6],"©¸");
        strcpy(tl2[7],"©Ø");
        strcpy(tl2[8],"©¼");

        strcpy(tl2[9] ,"©¤");
        strcpy(tl2[10],"©¦");
      }

      if (wp==1821)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[0]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[0]);
      }

      if (wp==1822)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[1]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[1]);
      }

      if (wp==1823)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[2]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[2]);
      }

      if (wp==1824)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[3]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[3]);
      }

      if (wp==1825)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[4]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[4]);
      }

      if (wp==1826)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[5]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[5]);
      }

      if (wp==1827)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[6]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[6]);
      }

      if (wp==1828)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[7]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[7]);
      }

      if (wp==1829)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[8]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[8]);
      }

      if (wp==1830)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[9]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[9]);
      }

      if (wp==1831)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[10]);
	else SendMessage(bw_edit_bua1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[10]);
      }
*/
    }
    case WM_SYSCOMMAND:
    {
      if (0-wp==4000)
      {
	i=bw_edit1.w_find_edithand(hwnd);

	if (bw_edit_bua1.get_win_edit_modi(i)==1)
        {
	  bw_edit_bua1.get_win_edit_file(i,stn,FN_SIZE);
	  k=bw_win1.w_atten64(stn);
        }
        else k=0;

        if (k==1)
        {
/*
	  GetWindowText(bw_edit_bua1.get_win_edit_hnd2(i),bw_inkey1.tmpc4,CPY_BSIZE);

	  j=GetWindowTextLength(bw_edit_bua1.get_win_edit_hnd2(i));
          bw_inkey1.tmpc4[j]=0;

	  bw_edit_bua1.get_win_edit_dirn(i,stn,FN_SIZE);
	  bw_inkey1.w_set_dir(stn);

	  bw_edit_bua1.get_win_edit_file(i,stn,FN_SIZE);
	  s_hp1=sopen(stn,O_RDWR|O_TRUNC|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
          if (s_hp1>=0)
          {
            write(s_hp1,bw_inkey1.tmpc4,strlen(bw_inkey1.tmpc4));
            close(s_hp1);
          }
*/
        }

	DestroyWindow(bw_edit_bua1.get_win_edit_hnd1(i));

	bw_edit_bua1.set_win_edit_inuse(i,0);

	if ((bw_edit_bua1.get_win_edit_wpp(i)>0)&&(bw_edit_bua1.get_win_edit_modi(i)==1))
	{
	  bw_fldstru1.w_edit_memo_close(bw_edit_bua1.get_win_edit_wpp(i));
	  bw_edit_bua1.set_win_edit_wpp(i,0);
	  bw_edit_bua1.set_win_edit_modi(i,0);
	}
	else
	{
	  if (bw_edit_bua1.get_win_edit_wpp(i)>0)
	  {
	    j=bw_edit_bua1.get_win_edit_wpp(i);
	    k=bw_win_bua1.get_win_memo_basep(j);
	    bw_xbase_bua1.set_win_mem_inuse(k,0);

            bw_xbase_bua1.get_win_mem_fn(k,sf1,FN_SIZE);
	    bw_inkey1.w_del_file(sf1);
	  }
        }

        SetFocus(bw_main1.win_hwnd1);
      }
    }
  }

  return DefWindowProc(hwnd,msg,wp,lp);
}

int bw_edit::w_ini_edit(void)
{
  win_edit_pp1=1;
  return(0);
}
