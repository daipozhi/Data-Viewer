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
#include <dos.h>
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
#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_edit         bw_edit1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;

int bw_edit::get_edit(char *p_fn,int p_fn_size,int p_wptr,HWND hwnd)
{
/*
  HWND    hnd;
  int     s_hp1;
  int     i,j,k,l;
  int     exist;
  int     cp1;
  char    str1[FN_SIZE];

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  exist=0;

  //i=1; can not be this i=0;
  for (i=1;i<EDIT_NUM;i++)
  {
    if (get_win_edit_inuse(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  win_edit_ptr1=i;

  bw_inkey1.w_get_dir(str1,FN_SIZE);

  set_win_edit_dirn(win_edit_ptr1,str1,FN_SIZE);

  set_win_edit_file(win_edit_ptr1,p_fn,p_fn_size);

  set_win_edit_inuse(win_edit_ptr1,1);

  s_hp1=sopen(p_fn,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_hp1<0)
  {
    bw_win1.w_atten1(hwnd,p_fn);
    return(0);
  }

  if (win_edit_ptr1>=EDIT_NUM) return(0);

  i=win_edit_ptr1;
  while (i>3)
  {
    i=i-3;
  }

  j=win_edit_ptr1;
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

  hnd=CreateWindow ("bowo_edit",
		"Date Viewer Editor Window",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		i*30,
		j*30,
		k,
		l,
		hwnd,
		NULL,
		bw_main1.win_ins,
		NULL);

  set_win_edit_hnd1(win_edit_ptr1,hnd);

  cp1=read(s_hp1,bw_inkey1.tmp_buff,CPY_BSIZE);
  bw_inkey1.tmp_buff[cp1]=0;
                
  close(s_hp1);

  SetWindowText(get_win_edit_hnd2(win_edit_ptr1),bw_inkey1.tmp_buff);

  set_win_edit_modi(win_edit_ptr1,0);

  if (p_wptr>0) set_win_edit_wptr(win_edit_ptr1,p_wptr);
  else set_win_edit_wptr(win_edit_ptr1,0);

  win_edit_ptr1++;
*/
  return(0);
}

int bw_edit::w_find_edithand(HWND hwnd)
{
/*
  int i;
  int exist;

  exist=0;

  for (i=1;i<win_edit_ptr1;i++)
  {
    if (hwnd==get_win_edit_hnd1(i))
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);
  else return(i);
  */
  return(0);
}

// _export
long w_edit_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
/*
  HWND    hnd;
  RECT    rt;
  HFONT   hfont;
  int     i,j,k,l;
  int     s_hp1;
  char    str1[SMG_SIZE];
  char    str2[FN_SIZE];
  char    tl1[11][2];
  char    tl2[11][3];
  char    sf1[FN_SIZE];

  //bw_main1.win_msg=msg;
  //bw_main1.win_wp=wp;
  //bw_main1.win_hwnd=hwnd;
  //bw_main1.win_lp=lp;

  switch(msg)    
  {
    case WM_CREATE:
    {
      GetClientRect(hwnd,&rt);

      k=rt.right-rt.left+1;
      l=rt.bottom-rt.top+1;

      hnd=CreateWindow("edit",NULL
		 ,WS_CHILD|WS_VISIBLE|WS_HSCROLL
		 |WS_VSCROLL|WS_BORDER|ES_LEFT
		 |ES_MULTILINE|ES_AUTOHSCROLL
		 |ES_AUTOVSCROLL
		 ,0,0,k,l
		 ,hwnd,(HMENU)bw_edit1.win_edit_ptr1
		 ,bw_main1.win_ins,NULL);

      bw_edit1.set_win_edit_hnd2(bw_edit1.win_edit_ptr1,hnd);

      hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);

      SendMessage(bw_edit1.get_win_edit_hnd2(bw_edit1.win_edit_ptr1)
		 ,WM_SETFONT
		 ,(WPARAM)hfont
                 ,(LPARAM)0);

      break;
    }
    case WM_SIZE:
    {
      i=bw_edit1.w_find_edithand(hwnd);

      GetClientRect(hwnd,&rt);

      k=rt.right-rt.left+1;
      l=rt.bottom-rt.top+1;

      MoveWindow(bw_edit1.get_win_edit_hnd2(i),0,0,k,l,1);

      break;
    }
    case WM_COMMAND:
    {
      i=bw_edit1.w_find_edithand(hwnd);

      if (HIWORD(lp)==EN_CHANGE) bw_edit1.set_win_edit_modi(i,1);

      if (wp==1801)
      {
	if ((bw_edit1.get_win_edit_wptr(i)<=0)&&(bw_edit1.get_win_edit_modi(i)==1))
        {
	  GetWindowText(bw_edit1.get_win_edit_hnd2(i),bw_inkey1.tmp_buff,CPY_BSIZE);

	  j=GetWindowTextLength(bw_edit1.get_win_edit_hnd2(i));
          bw_inkey1.tmp_buff[j]=0;


          bw_edit1.get_win_edit_dirn(i,str2,FN_SIZE);
	  bw_inkey1.w_set_dir(str2,FN_SIZE);

          bw_edit1.get_win_edit_file(i,str2,FN_SIZE);
	  s_hp1=sopen(str2,O_RDWR|O_TRUNC|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
          if (s_hp1>=0)
          {
            write(s_hp1,bw_inkey1.tmp_buff,strlen(bw_inkey1.tmp_buff));
            close(s_hp1);
          }

	  bw_edit1.set_win_edit_modi(i,0);

	}

      }
      if (wp==1802)
      {
	bw_edit1.get_win_edit_dirn(i,str2,FN_SIZE);
	bw_inkey1.w_set_dir(str2,FN_SIZE);

	bw_edit1.get_win_edit_file(i,str2,FN_SIZE);
	s_hp1=sopen(str2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
        if (s_hp1>=0)
        {
          j=read(s_hp1,bw_inkey1.tmp_buff,CPY_BSIZE);
          bw_inkey1.tmp_buff[j]=0;
          close(s_hp1);
        }


	SetWindowText(bw_edit1.get_win_edit_hnd2(i),bw_inkey1.tmp_buff);

	bw_edit1.set_win_edit_modi(i,0);

      }
      if (wp==1803)
      {
	if (bw_edit1.get_win_edit_modi(i)==1)
        {
	  bw_edit1.get_win_edit_file(i,str2,FN_SIZE);
	  k=bw_win1.w_atten64(hwnd,str2);
        }
        else k=0;

        if (k==1)
        {
	  GetWindowText(bw_edit1.get_win_edit_hnd2(i),bw_inkey1.tmp_buff,CPY_BSIZE);

	  j=GetWindowTextLength(bw_edit1.get_win_edit_hnd2(i));
          bw_inkey1.tmp_buff[j]=0;

	  bw_edit1.get_win_edit_dirn(i,str2,FN_SIZE);
	  bw_inkey1.w_set_dir(str2,FN_SIZE);

	  bw_edit1.get_win_edit_file(i,str2,FN_SIZE);
	  s_hp1=sopen(str2,O_RDWR|O_TRUNC|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
          if (s_hp1>=0)
          {
            write(s_hp1,bw_inkey1.tmp_buff,strlen(bw_inkey1.tmp_buff));
            close(s_hp1);
          }
	}

	DestroyWindow(bw_edit1.get_win_edit_hnd1(i));

        bw_edit1.set_win_edit_inuse(i,0);

	if ((bw_edit1.get_win_edit_wptr(i)>0)&&(bw_edit1.get_win_edit_modi(i)==1))
	{
	  bw_fldstru1.w_edit_memo_close(bw_edit1.get_win_edit_wptr(i));
	  bw_edit1.set_win_edit_wptr(i,0);
	  bw_edit1.set_win_edit_modi(i,0);
        }
	else
	{
	  if (bw_edit1.get_win_edit_wptr(i)>0)
	  {
	    j=bw_edit1.get_win_edit_wptr(i);
	    k=bw_win1.get_win_memo_basep(j);
	    bw_xbase1.set_win_mem_inuse(k,0);

	    bw_xbase1.get_win_mem_fn(k,sf1,FN_SIZE);
	    bw_inkey1.w_del_file(sf1,FN_SIZE);
	  }
        }

	SetFocus(bw_main1.win_hwnd1);
      }
      if (wp==1804)
      {
	DestroyWindow(bw_edit1.get_win_edit_hnd1(i));

	bw_edit1.set_win_edit_inuse(i,0);

	bw_edit1.set_win_edit_modi(i,0);

	j=bw_edit1.get_win_edit_wptr(i);
	k=bw_win1.get_win_memo_basep(j);
	bw_win1.set_win_memo_basep(j,0);
	bw_xbase1.set_win_mem_inuse(k,0);
	bw_xbase1.set_win_mem_wptr(k,0);
	bw_xbase1.set_c_win_mem_fn(k,0,0);

	bw_edit1.set_win_edit_wptr(i,0);

	SetFocus(bw_main1.win_hwnd1);
      }
      if (wp==1811)
      {
	j=SendMessage(bw_edit1.get_win_edit_hnd2(i)
		 ,EM_CANUNDO
		 ,0
                 ,(LPARAM)0);

        if (j==0)
        {
          bw_win1.w_atten65(hwnd);
        }
        else
        {
	  SendMessage(bw_edit1.get_win_edit_hnd2(i)
		 ,WM_UNDO
		 ,0
                 ,(LPARAM)0);

        }
      }
      if (wp==1812)
      {
	SendMessage(bw_edit1.get_win_edit_hnd2(i)
		 ,WM_CUT
		 ,0
                 ,(LPARAM)0);

      }
      if (wp==1813)
      {
	SendMessage(bw_edit1.get_win_edit_hnd2(i)
		 ,WM_COPY
		 ,0
                 ,(LPARAM)0);

      }
      if (wp==1814)
      {
	SendMessage(bw_edit1.get_win_edit_hnd2(i)
		 ,WM_PASTE
		 ,0
                 ,(LPARAM)0);

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

      // if linux
       /*
      if (wp==1821)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)0);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)0);
      }

      if (wp==1822)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)1);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)1);
      }

      if (wp==1823)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)2);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)2);
      }

      if (wp==1824)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)3);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)3);
      }

      if (wp==1825)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)4);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)4);
      }

      if (wp==1826)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)5);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)5);
      }

      if (wp==1827)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)6);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)6);
      }

      if (wp==1828)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)7);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)7);
      }

      if (wp==1829)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)8);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)8);
      }

      if (wp==1830)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)9);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)9);
      }

      if (wp==1831)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)10);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)10);
      }
       * // 
      // end if linux

      // if windows
      // // *
      if (wp==1821)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[0]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[0]);
      }

      if (wp==1822)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[1]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[1]);
      }

      if (wp==1823)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[2]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[2]);
      }

      if (wp==1824)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[3]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[3]);
      }

      if (wp==1825)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[4]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[4]);
      }

      if (wp==1826)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[5]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[5]);
      }

      if (wp==1827)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[6]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[6]);
      }

      if (wp==1828)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[7]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[7]);
      }

      if (wp==1829)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[8]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[8]);
      }

      if (wp==1830)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[9]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[9]);
      }

      if (wp==1831)
      {
	if (bw_main1.win_lang==1) SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl1[10]);
	else SendMessage(bw_edit1.get_win_edit_hnd2(i),EM_REPLACESEL,0,(LPARAM)tl2[10]);
      }
      // * //
      // end if windows

      break;
    }
    case WM_SYSCOMMAND:
    {
      if (0-wp==4000)
      {
	i=bw_edit1.w_find_edithand(hwnd);

	if (bw_edit1.get_win_edit_modi(i)==1)
        {
	  bw_edit1.get_win_edit_file(i,str2,FN_SIZE);
	  k=bw_win1.w_atten64(hwnd,str2);
        }
        else k=0;

        if (k==1)
        {
	  GetWindowText(bw_edit1.get_win_edit_hnd2(i),bw_inkey1.tmp_buff,CPY_BSIZE);

	  j=GetWindowTextLength(bw_edit1.get_win_edit_hnd2(i));
          bw_inkey1.tmp_buff[j]=0;

	  bw_edit1.get_win_edit_dirn(i,str2,FN_SIZE);
	  bw_inkey1.w_set_dir(str2,FN_SIZE);

	  bw_edit1.get_win_edit_file(i,str2,FN_SIZE);
	  s_hp1=sopen(str2,O_RDWR|O_TRUNC|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
          if (s_hp1>=0)
          {
            write(s_hp1,bw_inkey1.tmp_buff,strlen(bw_inkey1.tmp_buff));
            close(s_hp1);
          }
        }

	DestroyWindow(bw_edit1.get_win_edit_hnd1(i));

	bw_edit1.set_win_edit_inuse(i,0);

	if ((bw_edit1.get_win_edit_wptr(i)>0)&&(bw_edit1.get_win_edit_modi(i)==1))
	{
	  bw_fldstru1.w_edit_memo_close(bw_edit1.get_win_edit_wptr(i));
	  bw_edit1.set_win_edit_wptr(i,0);
	  bw_edit1.set_win_edit_modi(i,0);
	}
	else
	{
	  if (bw_edit1.get_win_edit_wptr(i)>0)
	  {
	    j=bw_edit1.get_win_edit_wptr(i);
	    k=bw_win1.get_win_memo_basep(j);
	    bw_xbase1.set_win_mem_inuse(k,0);

            bw_xbase1.get_win_mem_fn(k,sf1,FN_SIZE);
	    bw_inkey1.w_del_file(sf1,FN_SIZE);
	  }
        }

        SetFocus(bw_main1.win_hwnd1);
      }
    }
  }

  return DefWindowProc(hwnd,msg,wp,lp);
  */
  return(0);
}

int bw_edit::w_ini_edit(void)
{
/*
  win_edit_ptr1=1;
  */
  return(0);
}





HWND bw_edit::get_win_edit_hnd1(int eptr)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  return(win_edit_hnd1[eptr]);
}
int bw_edit::set_win_edit_hnd1(int eptr,HWND hwnd)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  win_edit_hnd1[eptr]=hwnd;
  return(0);
}
HWND bw_edit::get_win_edit_hnd2(int eptr)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  return(win_edit_hnd2[eptr]);
}
int bw_edit::set_win_edit_hnd2(int eptr,HWND hwnd)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  win_edit_hnd2[eptr]=hwnd;
  return(0);
}
int bw_edit::get_win_edit_dirn(int eptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_edit_dirn[eptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_edit::set_win_edit_dirn(int eptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_edit_dirn[eptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_edit_dirn[eptr][j+0]=p_s1[j];
    win_edit_dirn[eptr][j+1]=0;
  }

  return(0);
}
int bw_edit::get_win_edit_file(int eptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_edit_file[eptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_edit::set_win_edit_file(int eptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_edit_file[eptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_edit_file[eptr][j+0]=p_s1[j];
    win_edit_file[eptr][j+1]=0;
  }

  return(0);
}
int bw_edit::tst_dirn_file(void)
{
  HDC  hdc;
  int  i;
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<10;i++)
  {
    get_win_edit_dirn(i,stn1,FN_SIZE);
    get_win_edit_file(i,stn2,FN_SIZE);

    TextOut(hdc,0  ,i*20,stn1,strlen(stn1));
    TextOut(hdc,250,i*20,stn2,strlen(stn2));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}
int bw_edit::get_win_edit_modi(int eptr)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  return(win_edit_modi[eptr]);
}
int bw_edit::set_win_edit_modi(int eptr,int val)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  win_edit_modi[eptr]=val;
  return(0);
}
int bw_edit::get_win_edit_inuse(int eptr)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  return(win_edit_inuse[eptr]);
}
int bw_edit::set_win_edit_inuse(int eptr,int val)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  win_edit_inuse[eptr]=val;
  return(0);
}
int bw_edit::get_win_edit_wptr(int eptr)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  return(win_edit_wptr[eptr]);
}
int bw_edit::set_win_edit_wptr(int eptr,int val)
{
  if ((eptr<0)||(eptr>=EDIT_NUM)) return(0);
  win_edit_wptr[eptr]=val;
  return(0);
}

