
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

#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>

#include "vc_bowo.h"

extern class bw_win          bw_win1;
extern class bw_menuvar      bw_menuvar1;
extern class bw_bmp          bw_bmp1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_main         bw_main1;
extern class bw_inkey        bw_inkey1;

int  bw_bmp::DIB(char *p_bfn,int p_bfn_size)
{
  int                fh;
  LPBITMAPINFOHEADER lpbi;
  BITMAPINFOHEADER   bi;

  fh=sopen(p_bfn,O_RDONLY|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (fh<0) return(1);

  hbiCurrent=ReadDibBitmapInfo(fh);

  dwOffSet=lseek(fh,0,SEEK_CUR);
  close(fh);

  if (hbiCurrent==NULL) return(1);

  DibInfo(hbiCurrent,&bi);

  lpbi=(LPBITMAPINFOHEADER)GlobalLock(hbiCurrent);

  if (lpbi==NULL) return(1);

  hPalCurrent=(HPALETTE)CreateDIBPalette(lpbi);

  if (hPalCurrent==NULL)
  {
    GlobalUnlock(hbiCurrent);
    return(1);
  }

  if (bi.biBitCount!=24)
  {
    fPalColors=TRUE;
//    pw=(WORD FAR *)((LPSTR)lpbi+lpbi->biSize);
//    for (i=0;i<(int)bi.biClrUsed;i++)
//    {
//      i++;
//      *pw=(WORD)i;
//    }
  }
  else fPalColors=FALSE;

  GlobalUnlock(hbiCurrent);

  return(0);
}

HGLOBAL bw_bmp::ReadDibBitmapInfo(int fh)
{
  WORD               nnumcolors;
  RGBQUAD FAR        *prgb;
  BITMAPINFOHEADER   bi;
  LPBITMAPINFOHEADER lpbi;
  BITMAPFILEHEADER   bf;
  HGLOBAL            hbi;
  int                i;

  lseek(fh,0,SEEK_SET);

  i=sizeof(bf);

  i=read(fh,&bf,i);

  i=sizeof(bi);

  i=read(fh,&bi,i);

  nnumcolors=DibNumColors(&bi);

  if (bi.biSizeImage==0)
    bi.biSizeImage=((((DWORD)bi.biWidth*bi.biBitCount)+31)/32*4)*bi.biHeight;

  if (bi.biClrUsed==0) bi.biClrUsed=nnumcolors;

  i=bi.biSize+nnumcolors*sizeof(RGBQUAD);
  hbi=GlobalAlloc(GHND,i);
  if (!hbi) return(NULL);

  lpbi=(LPBITMAPINFOHEADER)GlobalLock(hbi);

  if (lpbi==NULL) return(NULL);

  *lpbi=bi;

  prgb=(RGBQUAD FAR *)((LPSTR)lpbi+bi.biSize);

  i=nnumcolors*sizeof(RGBQUAD);
  read(fh,(LPSTR)prgb,i);

  GlobalUnlock(hbi);

  return(hbi);
}

WORD bw_bmp::DibNumColors(LPBITMAPINFOHEADER lpbi)
{
  if (lpbi->biClrUsed!=0) return((WORD)lpbi->biClrUsed);
  else
  {
    switch (lpbi->biBitCount)
    {
      case 1:
	return(2);
      case 4:
	return(16);
      case 8:
	return(256);
      default:
	return(0);
    }
  }
}

HPALETTE bw_bmp::CreateDIBPalette(LPBITMAPINFOHEADER lpbi)
{
  LOGPALETTE  *ppal;
  HPALETTE     hpal=NULL;
  WORD         nnumbercolors;
  BYTE         red,green,blue;
  int          i;
  RGBQUAD FAR *prgb;

  if (!lpbi) return(NULL);

  prgb=(RGBQUAD FAR *)((LPSTR)lpbi+(WORD)lpbi->biSize);

  nnumbercolors=DibNumColors(lpbi);

  if (nnumbercolors)
  {
    i=sizeof(LOGPALETTE)+nnumbercolors*sizeof(RGBQUAD);
    ppal=(LOGPALETTE *)LocalAlloc(LPTR,i);
    if (!ppal) return(NULL);

    ppal->palNumEntries=nnumbercolors;
    ppal->palVersion=0x300;

    for (i=0;i<nnumbercolors;i++)
    {
      ppal->palPalEntry[i].peRed  =prgb[i].rgbRed;
      ppal->palPalEntry[i].peGreen=prgb[i].rgbGreen;
      ppal->palPalEntry[i].peBlue =prgb[i].rgbBlue;
      ppal->palPalEntry[i].peFlags=(BYTE)0;
    }

    hpal=CreatePalette(ppal);

    if (hpal==NULL) return(NULL);

    LocalFree((HLOCAL)ppal);
  }
  else
  {
    if (lpbi->biBitCount==24)
    {
      nnumbercolors=256;

      i=sizeof(LOGPALETTE)+nnumbercolors*sizeof(RGBQUAD);
      ppal=(LOGPALETTE *)LocalAlloc(LPTR,i);
      if (!ppal) return(NULL);

      ppal->palNumEntries=nnumbercolors;
      ppal->palVersion=0x300;

      red=0;
      green=0;
      blue=0;

      for (i=0;i<nnumbercolors;i++)
      {
        ppal->palPalEntry[i].peRed  =red;
     	ppal->palPalEntry[i].peGreen=green;
	    ppal->palPalEntry[i].peBlue =blue;
	    ppal->palPalEntry[i].peFlags=(BYTE)0;

	if (!(red +=32))
	  if (!(green +=32))
	    blue +=64;
      }

      hpal=CreatePalette(ppal);

      LocalFree((HLOCAL)ppal);
    }
  }

  return(hpal);
}

BOOL bw_bmp::DibInfo(HGLOBAL hbi,LPBITMAPINFOHEADER lpbi)
{
  *lpbi=*(LPBITMAPINFOHEADER)GlobalLock(hbi);

  if (lpbi->biSizeImage==0L)
    lpbi->biSizeImage=(((DWORD)lpbi->biWidth*lpbi->biBitCount+31)/32*4)*lpbi->biHeight;

  if (lpbi->biClrUsed==0L)
    lpbi->biClrUsed=DibNumColors(lpbi);

  GlobalUnlock(hbi);

  return(TRUE);
}

BOOL bw_bmp::DisplayDIB(HWND hwnd,int x,int y,LPSTR szFile)
{
  LPBITMAPINFOHEADER lpbi;
  WORD               wread;
  WORD               wscansleft;
  DWORD              dwmapsize;
  DWORD              dwscans;
  HGLOBAL            hbuf;
  LPSTR              pbuf;
  HPALETTE           holdpal;
  int                fh;
  int                nbandsize;
  BOOL               ok;
  HDC                hdc;

  fh=sopen(szFile,O_RDONLY|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (fh<0) return(1);

  lpbi=(LPBITMAPINFOHEADER)GlobalLock(hbiCurrent);
  if (!lpbi)
  {
    close(fh);
    return(FALSE);
  }

  dwscans=((DWORD)lpbi->biWidth*lpbi->biBitCount+31)/32*4;
  wscansleft=(WORD)lpbi->biHeight;
  nbandsize=BMP_BUFF_SIZE/dwscans;

//  sprintf(str,"width=%ld,bitcount=%d,dot=%ld,band=%d,scanleft=%d,"
//	     ,lpbi->biWidth
//	     ,lpbi->biBitCount
//	     ,dwscans
//	     ,nbandsize
//	     ,wscansleft);
//  MessageBox(bw_main1.win_hwnd1,str,"aa",MB_OK);

  hbuf=GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,nbandsize*dwscans);
  if (!hbuf) return(FALSE);

  pbuf=(LPSTR)GlobalLock(hbuf);

  lseek(fh,dwOffSet,0);

  hdc=GetDC(hwnd);
  holdpal=SelectPalette(hdc,hPalCurrent,1);
  RealizePalette(hdc);

  ok=TRUE;

  while (1)
  {
    if (wscansleft>nbandsize) wread=nbandsize;
    else wread=wscansleft;

    dwmapsize=(DWORD)wread*dwscans;

    /*i=*/read(fh,(LPSTR)pbuf,dwmapsize);

//	sprintf(str,"%d,",i);
//	MessageBox(bw_main1.win_hwnd1,str,"22",MB_OK);

//      sprintf(str,"x=%d,y=%d,width=%ld,height=%ld,start=%d,dist=%d,size=%ld,"
//	,x,y,lpbi->biWidth,lpbi->biHeight
//	,(WORD)lpbi->biHeight-wscansleft
//	,wread
//	,lpbi->biSizeImage);
//      MessageBox(hwnd,str,"bb",MB_OK);
//
//      sprintf(str,"scanleft=%d,wread=%d,mapsize=%ld,"
//        ,wscansleft,wread,dwmapsize);
//      MessageBox(hwnd,str,"cc",MB_OK);

    if (fPalColors)
    {
	     SetDIBitsToDevice(hdc
	     ,x
	     ,y
	     ,(WORD)lpbi->biWidth
	     ,(WORD)lpbi->biHeight
         ,0,0
	     ,(WORD)lpbi->biHeight-wscansleft
	     ,wread
	     ,pbuf
	     ,(LPBITMAPINFO)lpbi
	     ,DIB_RGB_COLORS);

//        if (display_ok!=wread)
//        {
//	        ok=FALSE;
//	        break;
//	      }
//	      i=GetLastError();
//          sprintf(str,"%d,",i);
//          MessageBox(bw_main1.win_hwnd1,str,"88",MB_OK);
    }
    else
    {
          SetDIBitsToDevice(hdc
	     ,x
	     ,y
	     ,(WORD)lpbi->biWidth
	     ,(WORD)lpbi->biHeight
	     ,0,0
	     ,(WORD)lpbi->biHeight-wscansleft
	     ,wread
	     ,pbuf
	     ,(LPBITMAPINFO)lpbi
	     ,DIB_PAL_COLORS);

//        if (display_ok!=wread)
//        {
//	        ok=FALSE;
//	        break;
//	      }
//	      i=GetLastError();
//          sprintf(str,"%d,,,",i);
//		  MessageBox(bw_main1.win_hwnd1,str,"88",MB_OK);

    }

    wscansleft=wscansleft-wread;

    if (wscansleft<=0) break;

//    if (eof(fh)) break;
  }

  GlobalUnlock(hbuf);
  GlobalFree(hbuf);
  SelectPalette(hdc,holdpal,0);
  GlobalUnlock(hbiCurrent);
  GlobalFree(hbiCurrent);

  ReleaseDC(hwnd,hdc);

  close(fh);

  return(ok);
}

BOOL bw_bmp::PaintDIB(HWND hwnd,int mx,int my,int mh,LPSTR szFile)
{
  LPBITMAPINFOHEADER lpbi;
  WORD               wread;
  WORD               wscansleft;
  DWORD              dwmapsize;
  DWORD              dwscans;
  HGLOBAL            hbuf;
  LPSTR              pbuf;
  HPALETTE           holdpal;
  int                fh;
  int                nbandsize;
  BOOL               ok;
  HDC                hdc;
  long               skip;

  fh=sopen(szFile,O_RDONLY|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (fh<0) return(1);

  lpbi=(LPBITMAPINFOHEADER)GlobalLock(hbiCurrent);
  if (!lpbi)
  {
    close(fh);
    return(FALSE);
  }

  dwscans=((DWORD)lpbi->biWidth*lpbi->biBitCount+31)/32*4;
  wscansleft=mh;
  nbandsize=BMP_BUFF_SIZE/dwscans;

//  sprintf(str,"width=%ld,bitcount=%d,dot=%ld,band=%d,scanleft=%d,"
//	     ,lpbi->biWidth
//	     ,lpbi->biBitCount
//	     ,dwscans
//	     ,nbandsize
//	     ,wscansleft);
//  MessageBox(win_hwnd1,str,"aa",MB_OK);

  hbuf=GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,nbandsize*dwscans);
  if (!hbuf) return(FALSE);

  pbuf=(LPSTR)GlobalLock(hbuf);

  lseek(fh,dwOffSet,0);

  hdc=GetDC(hwnd);
  holdpal=SelectPalette(hdc,hPalCurrent,1);
  RealizePalette(hdc);

  skip=dwscans*my;
  lseek(fh,skip,SEEK_CUR);

  ok=TRUE;

  while (1)
  {
    if (wscansleft>nbandsize) wread=nbandsize;
    else wread=wscansleft;

    dwmapsize=(DWORD)wread*dwscans;

      read(fh,(LPSTR)pbuf,dwmapsize);

//      sprintf(str,"x=%d,y=%d,width=%ld,height=%ld,start=%d,dist=%d,size=%ld,"
//	,x,y,lpbi->biWidth,lpbi->biHeight
//	,(WORD)lpbi->biHeight-wscansleft
//	,wread
//	,lpbi->biSizeImage);
//      MessageBox(hwnd,str,"bb",MB_OK);

//      sprintf(str,"scanleft=%d,wread=%d,mapsize=%ld,"
//        ,wscansleft,wread,dwmapsize);
//      MessageBox(hwnd,str,"cc",MB_OK);

      if (fPalColors)
      {
        lpbi->biHeight=mh;

	SetDIBitsToDevice(hdc
	     ,0
	     ,0
	     ,lpbi->biWidth
	     ,mh
	     ,mx
	     ,0
	     ,(WORD)lpbi->biHeight-wscansleft
	     ,wread
	     ,pbuf
	     ,(LPBITMAPINFO)lpbi
	     ,DIB_RGB_COLORS);

//        if (display_ok!=wread)
//        {
//	  ok=FALSE;
//	  break;
//	}
      }
      else
      {
	lpbi->biHeight=mh;

	SetDIBitsToDevice(hdc
	     ,0
	     ,0
	     ,lpbi->biWidth
	     ,mh
	     ,mx
	     ,0
	     ,(WORD)lpbi->biHeight-wscansleft
	     ,wread
	     ,pbuf
	     ,(LPBITMAPINFO)lpbi
	     ,DIB_PAL_COLORS);

//        if (display_ok!=wread)
//        {
//	  ok=FALSE;
//	  break;
//	}
      }

    wscansleft=wscansleft-wread;

    if (wscansleft<=0) break;

    if (eof(fh)) break;
  }

  GlobalUnlock(hbuf);
  GlobalFree(hbuf);
  SelectPalette(hdc,holdpal,0);
  GlobalUnlock(hbiCurrent);
  GlobalFree(hbiCurrent);

  ReleaseDC(hwnd,hdc);

  close(fh);

  return(ok);
}

int bw_bmp::tst_b1()
{
  int  i,j,k;
  char str1[SMG_SIZE];
  char s_ts0[FN_SIZE];
  char s_ts1[FN_SIZE];
  char s_ts2[FN_SIZE];
  char s_ts3[FN_SIZE];
  char s_ts4[FN_SIZE];
  char s_ts5[FN_SIZE];
  char s_ts6[FN_SIZE];
  char s_ts7[FN_SIZE];

  strcpy(s_ts0,"*.bmp");
  strcpy(s_ts6,"Select File For Copy From");
  bw_main1.dlg_f1.lStructSize=sizeof(OPENFILENAME);
  bw_main1.dlg_f1.hwndOwner=bw_main1.win_hwnd;
  strcpy(s_ts1,"ALL BMP File");
  strcat(s_ts1,"(");
  strcat(s_ts1,s_ts0);
  strcat(s_ts1,")");
  j=strlen(s_ts1);
  for (i=0;i<=(int)strlen(s_ts0);i++) s_ts1[j+1+i]=s_ts0[i];
  s_ts1[j+1+i]=0;
  bw_main1.dlg_f1.lpstrFilter=s_ts1;
  bw_main1.dlg_f1.nFilterIndex=1;
  strcpy(s_ts2,s_ts0);
  bw_main1.dlg_f1.lpstrFile=s_ts2;
  bw_main1.dlg_f1.nMaxFile=FN_SIZE;
  bw_main1.dlg_f1.lpstrFileTitle=s_ts3;
  bw_main1.dlg_f1.nMaxFileTitle=FN_SIZE;
  bw_main1.dlg_f1.lpstrInitialDir=NULL;
  bw_main1.dlg_f1.lpstrTitle=s_ts6;
  strcpy(s_ts4,"bmp");
  bw_main1.dlg_f1.lpstrDefExt=s_ts4;
  bw_main1.dlg_f1.lpstrCustomFilter=s_ts5;
  bw_main1.dlg_f1.nMaxCustFilter=FN_SIZE;
  bw_main1.dlg_f1.nFileOffset=NULL;
  bw_main1.dlg_f1.nFileExtension=NULL;
  bw_main1.dlg_f1.Flags=NULL;

  i=GetOpenFileName(&bw_main1.dlg_f1);
  if (i==0) return(1);

  strcpy(s_ts7,bw_main1.dlg_f1.lpstrFile);
  bw_main1.w_fetch_filename(s_ts7,FN_SIZE);

  strcpy(bw_main1.win_cpy_f1,bw_main1.win_seadir);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);
  k=strlen(bw_main1.win_cpy_f1);
  bw_main1.win_cpy_f1[k+0]=92;
  bw_main1.win_cpy_f1[k+1]=0;
  strcat(bw_main1.win_cpy_f1,bw_main1.win_seaname);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);

  strcpy(str1,bw_main1.win_cpy_f1);

  i=DIB(str1,SMG_SIZE);
  if (i==0) DisplayDIB(bw_main1.win_hwnd1,0,0,(LPSTR)str1);
  else GlobalFree(hbiCurrent);

  return(0);
}

int bw_bmp::echo_bmp(HWND hwnd,char *comm,int comm_size,int mcnt,int p_wptr)
{
  FILE *s_fp;
  int  i,j,k,l,m;
  int  exist;
  long li,lj,lk;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[FN_SIZE];
  char str4[SMG_SIZE];
  char str5[SMG_SIZE];
  char s_fn4[SMG_SIZE];

  bw_inkey1.cpy_string(s_fn4,SMG_SIZE,comm,comm_size);

  exist=0;

  for (i=0;i<(int)strlen(s_fn4);i++)
  {
    if (s_fn4[i]==',')
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    j=i+1;
    bw_inkey1.cut_string(s_fn4,0,i,SMG_SIZE,str1,SMG_SIZE);
  }
  else return(1);

  exist=0;

  for (i=j;i<(int)strlen(s_fn4);i++)
  {
    if (s_fn4[i]==',')
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    bw_inkey1.cut_string(s_fn4,j,i-j,SMG_SIZE,str2,SMG_SIZE);
  }
  else return(1);

  bw_inkey1.cut_string(s_fn4,i+1,strlen(s_fn4)-i-1,SMG_SIZE,str3,FN_SIZE);

  k=bw_inkey1.str2int(str1,strlen(str1)+1);
  l=bw_inkey1.str2int(str2,strlen(str2)+1);

  if (bw_win1.get_win_ci_mode(p_wptr)==0) k=(int)(k*bw_main1.win_edit_xchar);
  else k=(int)(k*bw_main1.win_xchar);

  if (bw_win1.get_win_ci_mode(p_wptr)==0) l=(int)(l*bw_main1.win_edit_ychar);
  else l=(int)(l*bw_main1.win_ychar);

  i=bw_inkey1.strlocc(str3,FN_SIZE,'.');
  bw_inkey1.cut_string(str3,i,4,FN_SIZE,str4,SMG_SIZE);

  if (strncmp(str4,".bmp",4)==0)
  {
    m=DIB(str3,FN_SIZE);
    if (m==0)
    {
      m=DisplayDIB(hwnd,k,l,str3);
      return(m);
    }
    else
    {
      GlobalFree(hbiCurrent);
      return(1);
    }
  }

  if (strncmp(str4,".smf",4)==0)
  {
    s_fp=fopen(str3,"r");
    if (s_fp==NULL) return(1);

    li=0;
    lj=0;

    for (i=1;i<= mcnt;i++)
    {
      fgets(str5,SMG_SIZE,s_fp);

      if (feof(s_fp))
      {
	lj=li;

	fseek(s_fp,0,0);
	continue;
      }

      li++;
    }

    lk=bw_menuvar1.get_t5_m_mcnt(bw_menuvar1.t5_m_ptr3);
    if (lk>lj) lk=lk-lj;
    bw_menuvar1.set_t5_m_mcnt(bw_menuvar1.t5_m_ptr3,lk);

    fgets(str3,SMG_SIZE,s_fp);
    bw_inkey1.strtrim(str3,FN_SIZE);

    fclose(s_fp);

    m=DIB(str3,FN_SIZE);
    if (m==0)
    {
      m=DisplayDIB(hwnd,k,l,str3);
      return(m);
    }
    else
    {
      GlobalFree(hbiCurrent);
      return(1);
    }
  }

  return(1);
}

int bw_bmp::w_bmp_add(int p_fptr,int p_wptr,char *p_fldname,int p_fldname_size)
{
  int  i,j,k;
  char str[SMG_SIZE];
  char sfld[SMG_SIZE];
  char s_ts0[FN_SIZE];
  char s_ts1[FN_SIZE];
  char s_ts2[FN_SIZE];
  char s_ts3[FN_SIZE];
  char s_ts4[FN_SIZE];
  char s_ts5[FN_SIZE];
  char s_ts6[FN_SIZE];
  char s_ts7[FN_SIZE];

  strcpy(sfld,p_fldname);

  strcpy(s_ts0,"*.bmp");
  strcpy(s_ts6,"Select BMP File For Add");
  bw_main1.dlg_f1.lStructSize=sizeof(OPENFILENAME);
  bw_main1.dlg_f1.hwndOwner=bw_main1.win_hwnd;
  strcpy(s_ts1,"ALL BMP File");
  strcat(s_ts1,"(");
  strcat(s_ts1,s_ts0);
  strcat(s_ts1,")");
  j=strlen(s_ts1);
  for (i=0;i<=(int)strlen(s_ts0);i++) s_ts1[j+1+i]=s_ts0[i];
  s_ts1[j+1+i]=0;
  bw_main1.dlg_f1.lpstrFilter=s_ts1;
  bw_main1.dlg_f1.nFilterIndex=1;
  strcpy(s_ts2,s_ts0);
  bw_main1.dlg_f1.lpstrFile=s_ts2;
  bw_main1.dlg_f1.nMaxFile=FN_SIZE;
  bw_main1.dlg_f1.lpstrFileTitle=s_ts3;
  bw_main1.dlg_f1.nMaxFileTitle=FN_SIZE;
  bw_main1.dlg_f1.lpstrInitialDir=NULL;
  bw_main1.dlg_f1.lpstrTitle=s_ts6;
  strcpy(s_ts4,"bmp");
  bw_main1.dlg_f1.lpstrDefExt=s_ts4;
  bw_main1.dlg_f1.lpstrCustomFilter=s_ts5;
  bw_main1.dlg_f1.nMaxCustFilter=FN_SIZE;
  bw_main1.dlg_f1.nFileOffset=NULL;
  bw_main1.dlg_f1.nFileExtension=NULL;
  bw_main1.dlg_f1.Flags=NULL;

  i=GetOpenFileName(&bw_main1.dlg_f1);
  if (i==0) return(1);

  strcpy(s_ts7,bw_main1.dlg_f1.lpstrFile);
  bw_main1.w_fetch_filename(s_ts7,FN_SIZE);

  strcpy(bw_main1.win_cpy_f1,bw_main1.win_seadir);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);
  k=strlen(bw_main1.win_cpy_f1);
  bw_main1.win_cpy_f1[k+0]=92;
  bw_main1.win_cpy_f1[k+1]=0;
  strcat(bw_main1.win_cpy_f1,bw_main1.win_seaname);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);

  strcpy(str,bw_main1.win_cpy_f1);

  bw_mbase1.w_down_rec(p_fptr,p_wptr,bw_xbase1.get_win_recno(p_fptr,p_wptr,0)-1);
  bw_fldstru1.w_sav_tab_var(sfld,SMG_SIZE,p_fptr,str,SMG_SIZE);
  bw_mbase1.w_save_rec(p_fptr,p_wptr,bw_xbase1.get_win_recno(p_fptr,p_wptr,0));
  bw_xbase1.set_win_state_dbf_modi(p_fptr,1);

  return(0);
}

int bw_bmp::w_bmp_paint(HWND hwnd)
{
  mx=0;
  my=0;

  win_bmp_hnd=CreateWindow ("bowo_bmp",
		"BMP Viewer Sub Window",
		WS_VISIBLE|WS_CAPTION|
		WS_BORDER|WS_SYSMENU|
		WS_HSCROLL|WS_VSCROLL|
		SW_SHOWMAXIMIZED,
		0,
		0,
		800,
		600,
		hwnd,
		(HMENU)NULL,
		bw_main1.win_ins,
		NULL);

  return(0);

}

// _export
long PASCAL w_bmp_wp(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
  LPBITMAPINFOHEADER lpbi;
  RECT               rect;
  int                i;
  char               str1[SMG_SIZE];

  switch(msg)
  {
    case WM_PAINT:
    {
      GetClientRect(hwnd,&rect);

      bw_xbase1.get_win_bmp_name(str1,SMG_SIZE);

      i=bw_bmp1.DIB(str1,SMG_SIZE);
      if (i==0) bw_bmp1.PaintDIB(hwnd,bw_bmp1.mx,bw_bmp1.my,rect.bottom,(LPSTR)str1);
      else GlobalFree(bw_bmp1.hbiCurrent);

      break;
    }
    case WM_VSCROLL:
    {
      if ((wp==SB_LINEUP)||(wp==SB_PAGEUP))
      {
	GetClientRect(hwnd,&rect);
  
        bw_xbase1.get_win_bmp_name(str1,SMG_SIZE);

	i=bw_bmp1.DIB(str1,SMG_SIZE);
  
        lpbi=(LPBITMAPINFOHEADER)GlobalLock(bw_bmp1.hbiCurrent);
  
	if (bw_bmp1.my+100+rect.bottom<=lpbi->biHeight)
        {
	  bw_bmp1.my=bw_bmp1.my+100;
        }
	else
        {
	  bw_bmp1.my=lpbi->biHeight-rect.bottom;
        }

	if (i==0) bw_bmp1.PaintDIB(hwnd,bw_bmp1.mx,bw_bmp1.my,rect.bottom,(LPSTR)str1);
	else GlobalFree(bw_bmp1.hbiCurrent);
  
      }
      if ((wp==SB_LINEDOWN)||(wp==SB_PAGEDOWN))
      {
	GetClientRect(hwnd,&rect);
  
        bw_xbase1.get_win_bmp_name(str1,SMG_SIZE);

	i=bw_bmp1.DIB(str1,SMG_SIZE);
  
        lpbi=(LPBITMAPINFOHEADER)GlobalLock(bw_bmp1.hbiCurrent);
  
	if (bw_bmp1.my-100>=0)
        {
	  bw_bmp1.my=bw_bmp1.my-100;
        }
	else
        {
	  bw_bmp1.my=0;
        }
  
	if (i==0) bw_bmp1.PaintDIB(hwnd,bw_bmp1.mx,bw_bmp1.my,rect.bottom,(LPSTR)str1);
	else GlobalFree(bw_bmp1.hbiCurrent);
  
      }

      break;
    }
    case WM_HSCROLL:
    {
      if ((wp==SB_LINEDOWN)||(wp==SB_PAGEDOWN))
      {
        GetClientRect(hwnd,&rect);
  
        bw_xbase1.get_win_bmp_name(str1,SMG_SIZE);

	i=bw_bmp1.DIB(str1,SMG_SIZE);
  
        lpbi=(LPBITMAPINFOHEADER)GlobalLock(bw_bmp1.hbiCurrent);
  
	if (bw_bmp1.mx+100+rect.right<=lpbi->biWidth)
        {
	  bw_bmp1.mx=bw_bmp1.mx+100;
        }
	else
        {
	  bw_bmp1.mx=lpbi->biWidth-rect.right;
        }
  
	if (i==0) bw_bmp1.PaintDIB(hwnd,bw_bmp1.mx,bw_bmp1.my,rect.bottom,(LPSTR)str1);
	else GlobalFree(bw_bmp1.hbiCurrent);
  
      }
      if ((wp==SB_LINEUP)||(wp==SB_PAGEUP))
      {
        GetClientRect(hwnd,&rect);
  
	bw_xbase1.get_win_bmp_name(str1,SMG_SIZE);

	i=bw_bmp1.DIB(str1,SMG_SIZE);
  
        lpbi=(LPBITMAPINFOHEADER)GlobalLock(bw_bmp1.hbiCurrent);
  
	if (bw_bmp1.mx-100>=0)
        {
	  bw_bmp1.mx=bw_bmp1.mx-100;
        }
	else
        {
	  bw_bmp1.mx=0;
        }
  
	if (i==0) bw_bmp1.PaintDIB(hwnd,bw_bmp1.mx,bw_bmp1.my,rect.bottom,(LPSTR)str1);
	else GlobalFree(bw_bmp1.hbiCurrent);
  
      }

      break;
    }
    case WM_SYSCOMMAND:
    {
      if (0-wp==4000)
      {
	DestroyWindow(hwnd);
      }
    }
   }

  return DefWindowProc(hwnd,msg,wp,lp);
}

