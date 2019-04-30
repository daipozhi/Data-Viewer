// (char *s1,no len)
 
#define STRICT
#include <windows.h>
#include <commdlg.h>

#include <stdio.h>
#include <math.h>
//#include <dir.h>
#include <dos.h>
//#include <bios.h>
#include <conio.h>
#include <process.h>
#include <string.h>

#include "vc_bowo.h"

extern class bw_main    far bw_main1;
extern class bw_get_bua far bw_get_bua1;
extern class bw_getread far bw_getread1;


int bw_getread::get_read_ini()
{
  int i;
  for (i=0;i<GET_NUM;i++) bw_get_bua1.set_smg_read_id(i,0);
  smg_insert=1;
/*
  //--- debug ---
  deb_record_init();
*/
  return(0);
}

int bw_getread::get_read_login()
{
  int i;
  int exist;

  exist=0;
  for (i=0;i<GET_NUM;i++)
  {
    if (bw_get_bua1.get_smg_read_id(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);
  else
  {
    bw_get_bua1.set_smg_read_id(i,1);
    return(i);
  }
}

int bw_getread::get_read_logout(int pp)
{
  if ((pp<0)||(pp>=GET_NUM)) return(-1);
  else
  {
    bw_get_bua1.set_smg_line(pp,0);
    bw_get_bua1.set_smg_colu(pp,0);
    bw_get_bua1.setc_smg_string(pp,0,0);
    bw_get_bua1.set_smg_type(pp,0);
    bw_get_bua1.set_smg_dlen(pp,0);
    bw_get_bua1.set_smg_dlen2(pp,0);
    bw_get_bua1.set_smg_ddec(pp,0);
    bw_get_bua1.set_smg_link(pp,0);
    bw_get_bua1.set_smg_color(pp,0);
    bw_get_bua1.set_smg_read_id(pp,0);
    return(0);
  }
}

int bw_getread::tst_getread()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char s1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<=12;i++)
  {
    bw_get_bua1.get_smg_string(i,s1,SMG_LEN);

    sprintf(str,"l=%d,c=%d,d=%s,t=%d,n=%d,n2=%d,dc=%d,l=%d,c=%d,id=%d,"
	    ,bw_get_bua1.get_smg_line(i),bw_get_bua1.get_smg_colu(i),s1
	    ,bw_get_bua1.get_smg_type(i),bw_get_bua1.get_smg_dlen(i),bw_get_bua1.get_smg_dlen2(i)
	    ,bw_get_bua1.get_smg_ddec(i),bw_get_bua1.get_smg_link(i),bw_get_bua1.get_smg_color(i)
	    ,bw_get_bua1.get_smg_read_id(i));
    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_getread::get_read(int scrn_l,int scrn_c,char *atten,
                     char *string,int datalen,char datatype,
		     char command,int datalen_real,int datadec,
		     char link,int color,int *posi,
		     int  array_pp)
{  
  HDC   hdc;
  HFONT hfont,holdfont;

  char  s_tmpc1[SMG_LEN];
  int   key;
//  char *p1;
  int   i,j,k,w;
//  int   s_pp1;
//  char  str[SMG_LEN];
  char  s1[SMG_LEN];
  char  s2[SMG_LEN];
  int   pos[300];

  if (command=='g')
  {
    if (array_pp<0)        return(1);
    if (array_pp>=GET_NUM) return(1);

    smg_pp=array_pp;

    bw_get_bua1.set_smg_line(smg_pp,scrn_l);
    bw_get_bua1.set_smg_colu(smg_pp,scrn_c);
    bw_get_bua1.set_smg_atte(smg_pp,atten,strlen(atten)+1);
    bw_get_bua1.set_smg_type(smg_pp,datatype);
    bw_get_bua1.set_smg_dlen(smg_pp,datalen);
    bw_get_bua1.set_smg_dlen2(smg_pp,datalen_real);
    bw_get_bua1.set_smg_ddec(smg_pp,datadec);
    bw_get_bua1.set_smg_link(smg_pp,link);
    bw_get_bua1.set_smg_color(smg_pp,color);
    bw_get_bua1.set_smg_posi(smg_pp,posi);
    bw_get_bua1.set_smg_string(smg_pp,string,strlen(string)+1);

    if (datatype=='n')
    {
      for (i=0;i<=60;i++)  s_tmpc1[i]=' ';
      for (i=0;i<=datalen_real-1;i++) if (string[i]=='.') break;
      if (i>=datalen_real)
      {
	for (i=datalen_real-1;i>=0;i--) if (string[i]>' ') break;
	i++;
      }
      for (j=0;j<=i-1;j++) s_tmpc1[30-i+j]=string[j];
      s_tmpc1[30]='.';
      for (j=i+1;j<=datalen_real-1;j++) s_tmpc1[30+j-i]=string[j];
      for (j=0;j<=datalen_real-1;j++)
      {
	if (datadec==0) string[j]=s_tmpc1[30-datalen_real+j];
	else string[j]=s_tmpc1[30-(datalen_real-datadec-1)+j];
      }
    }

    win_p_y=(int)(bw_main1.win_edit_ychar*(scrn_l-1));
    win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));

    i=strlen(atten);

    hdc=GetDC(bw_main1.win_hwnd);
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
    TextOut(hdc,win_p_x,win_p_y,atten,i);

    win_p_x=win_p_x+(int)(i*bw_main1.win_edit_xchar);

    bw_get_bua1.get_smg_string(smg_pp,s1,SMG_LEN);
    i=strlen(s1);
    if (i>datalen) i=datalen;

    HideCaret(bw_main1.win_hwnd);
    TextOut(hdc,win_p_x,win_p_y,s1,i);
    ShowCaret(bw_main1.win_hwnd);

    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.win_hwnd,hdc);

    if (*posi>datalen) *posi=datalen;
    if (*posi<1)       *posi=1;



    // get char , avoid half chiness
    bw_get_bua1.get_smg_string(smg_pp,s1,SMG_LEN);

    for (k=0;k<300;k++) pos[k]=(-1);

    k=0;
    j=0;
    pos[0]=0;

    while(k<strlen(s1))
    {
      if (s1[k]<0) k=k+2;
      else k=k+1;

      j++;

      pos[j]=k;
    }

    w=0;

    for (k=0;k<300;k++)
    {
      if (pos[k]<0) break;

      if (pos[k]<= *posi-1)
      {
        w=pos[k];
      }

    }

    *posi=w+1;



    HideCaret(bw_main1.win_hwnd);
    SetCaretPos(win_p_x+(int)((*posi-1)*bw_main1.win_edit_xchar)
                 ,win_p_y);
    ShowCaret(bw_main1.win_hwnd);
  }
  else
  {
    if (command=='r')
    {
      if (array_pp<0)        return(1);
      if (array_pp>=GET_NUM) return(1);

      smg_pp2=array_pp;

      bw_get_bua1.get_smg_string(smg_pp2,s1,SMG_LEN);

      for (i=0;i<bw_get_bua1.get_smg_dlen2(smg_pp2);i++)
      {
	if (i>=(int)strlen(s1)) bw_get_bua1.set_smg_data(i,' ');
        else bw_get_bua1.set_smg_data(i,s1[i]);
      }
      for (i=i;i<SMG_LEN;i++) bw_get_bua1.set_smg_data(i,' ');

      if (bw_get_bua1.get_smg_type(smg_pp2)=='c')
      {
	bw_get_bua1.get_smg_atte(smg_pp2,s2,SMG_LEN);

        key=get_txt(
bw_get_bua1.get_smg_line(smg_pp2),bw_get_bua1.get_smg_colu(smg_pp2),s2,
bw_get_bua1.get_smg_dlen(smg_pp2),bw_get_bua1.get_smg_dlen2(smg_pp2),bw_get_bua1.get_smg_link(smg_pp2),
smg_pp2,bw_get_bua1.get_smg_color(smg_pp2),bw_get_bua1.get_smg_posi(smg_pp2));
      }
      else
      {
	bw_get_bua1.get_smg_atte(smg_pp2,s2,SMG_LEN);

	key=get_num(
bw_get_bua1.get_smg_line(smg_pp2),bw_get_bua1.get_smg_colu(smg_pp2),s2,
bw_get_bua1.get_smg_dlen(smg_pp2),bw_get_bua1.get_smg_dlen2(smg_pp2),bw_get_bua1.get_smg_link(smg_pp2),
smg_pp2,bw_get_bua1.get_smg_color(smg_pp2),bw_get_bua1.get_smg_ddec(smg_pp2),bw_get_bua1.get_smg_posi(smg_pp2));
      }
      for (i=0;i<bw_get_bua1.get_smg_dlen2(smg_pp2);i++)
      {
	bw_get_bua1.setc_smg_string(smg_pp2,i,bw_get_bua1.get_smg_data(i));
      }
      bw_get_bua1.setc_smg_string(smg_pp2,i,0);

      if (key!=0)
      {
	if ((key==127)||(key==ESC_KEY)||(key==CTRL_W)
	    ||(key>200)||(key==RET_KEY)
	    ||((key<32)&&(key>0)))

	{
	  bw_main1.win_key=key;
	  return(1);
        }
        else
        {
	  if ((((key>=32)&&(key<127))
                ||(key<0))&&(win_confirm==0))  
	  {
	    if (win_edit_mode[array_pp]==1) bw_main1.win_key=RIGHT_ROW;
	    else bw_main1.win_key=10;
            return(1);
	  }
        }
      }
    }
  }
  return(0);
}
int bw_getread::get_txt(int scrn_l,int scrn_c,char *atten,
		    int datalen,int datalen_real,char link,
		    int pp,int color,int *posi)
{
  HDC   hdc;
  HFONT hfont,holdfont;
//  char *sp1;
  char str[SMG_LEN];
  char c1;
  char s1[SMG_LEN];
  int  n1,n2;
  int  i;
  int  key;
//  int  pp1;
  int  p2,p3;
  int w,w2;

  int j,k;
  int pos[300];

/* --- display attention and data --- */
  win_get_pp=pp;
  win_get_link=link;
  win_color=color;

  n1=strlen(atten);

/* --- input command --- */
  if ( *posi > datalen ) *posi= datalen;
  n2= *posi;

  win_cur1=scrn_c+n1;

  scrn_c=scrn_c+n1+n2-1;

  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
  win_p_y=(int)(bw_main1.win_edit_ychar*(scrn_l-1));

  HideCaret(bw_main1.win_hwnd);
  SetCaretPos(win_p_x,win_p_y);
  ShowCaret(bw_main1.win_hwnd);

/* --- pre insert when smg_chns_next==1 --- */
  if (bw_main1.win_key!=0)
  {
    if (bw_main1.win_key==410) return(0);
    if (bw_main1.win_key==427) return(0);
    if (bw_main1.win_key==639) return(0);

    hdc=GetDC(bw_main1.win_hwnd);
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);

    key=bw_main1.win_key;
/*
    // --- debug --- 
    sprintf(s1,"win_key=%d,",bw_main1.win_key);
    deb_record(s1);
*/
    if (((key>=32)&&(key<=126))||(key<0))
    {
      if ((key>=0)&&(win_chns_char==0))
      {
        c1=key;
        str[0]=c1;
        str[1]=0;
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str,1);
	ShowCaret(bw_main1.win_hwnd);
/*
        // --- debug ---
        deb_record(str);
*/
      }
      else
      {
        if (win_chns_char==0)
        {
          win_chns_char=1;
          win_chns_str[0]=key;
          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
         return(0);
        }
        else
        {
          win_chns_str[1]=key;
          win_chns_str[2]=0;
	  HideCaret(bw_main1.win_hwnd);
          if (n2+2>datalen)
            TextOut(hdc,win_p_x,win_p_y,win_chns_str,1);
          else
            TextOut(hdc,win_p_x,win_p_y,win_chns_str,2);
	  ShowCaret(bw_main1.win_hwnd);
/*
          // --- debug ---
          deb_record(win_chns_str);
*/
        }
      }
/*
      if (smg_insert==0)
      {
        if (win_chns_char==0)
        {
	  bw_get_bua1.set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        }
        else
        {
          win_chns_char=0;
	  bw_get_bua1.set_smg_data(win_p1+n2-1,win_chns_str[0]);
	  if (win_p1+n2<=datalen_real)
	    bw_get_bua1.set_smg_data(win_p1+n2-0,win_chns_str[1]);
          n2=n2+2;
          scrn_c=scrn_c+2;
        }
	if (win_p1+n2>datalen_real)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          //win_chns_char=0;
          return(RET_KEY);
	}
	if (n2>datalen)
	{
	  if (win_edit_mode[pp]==1)
	  {

	    win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	      else str[i-1]=' ';
	    }
	    str[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	    ShowCaret(bw_main1.win_hwnd);

            SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
          bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_after(s1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
      }
      else
      {
*/      



  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  bw_get_bua1.gets_smg_data(s1,SMG_LEN);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(s1)))
  {
    if (s1[k]<0) k=k+2;
    else k=k+1;

    j++;

    pos[j]=k;
  }

  j=0;
  w=0;
  w2=0;

  for (k=0;k<300;k++)
  {
    if (pos[k]==(win_p1+n2-1))
    {
      w2=0;
      break;
    }

    if (pos[k]>(win_p1+n2-1))
    {
      w2=1;
      break;
    }

    if (pos[k]<0) break;
  }



        n2=n2+w2;
	scrn_c=scrn_c+w2;

        // insert
        if (win_chns_char==0)
        {
	  for (i=datalen_real-1;i>=n2+win_p1;i--)
	  {
	    bw_get_bua1.set_smg_data(i+1-1,bw_get_bua1.get_smg_data(i-1));
	  }
	  bw_get_bua1.set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
        }
        else
        {
          win_chns_char=0;
	  for (i=datalen_real-2;i>=n2+win_p1;i--)
	  {
	    bw_get_bua1.set_smg_data(i+2-1,bw_get_bua1.get_smg_data(i-1));
	  }
	  bw_get_bua1.set_smg_data(win_p1+n2+0-1,win_chns_str[0]);
	  bw_get_bua1.set_smg_data(win_p1+n2+1-1,win_chns_str[1]);
	  n2=n2+2;
	  scrn_c=scrn_c+2;
        }
	if (win_p1+n2>datalen_real)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          //win_chns_char=0;
          return(RET_KEY);
	}
	if (n2>datalen)
	{
	  if (win_edit_mode[pp]==1)
	  {

	    win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	      else str[i-1]=' ';
	    }
	    str[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	    ShowCaret(bw_main1.win_hwnd);

	    SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }

          for (k=0;k<3;k++)
          {
	    bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	    p2=get_txt_after(s1,datalen_real,datalen,win_p1);
	    p3=p2-win_p1;
	    win_p1=p2;
	    win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	    for (i=win_p1+1;i<=win_p1+datalen;i++)
	    {
	      if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	      else str[i-win_p1-1]=' ';
	    }
	    str[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	    ShowCaret(bw_main1.win_hwnd);
	    n2=n2-p3;
	    scrn_c=scrn_c-p3;
	    win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	    HideCaret(bw_main1.win_hwnd);
            SetCaretPos(win_p_x,win_p_y);
	    ShowCaret(bw_main1.win_hwnd);

	    if (n2>datalen) continue;
            else break;
          }

	}
	else
	{
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-n2+1-1));
	  for (i=1/*n2*/;i<=datalen;i++)
	  {
	    if (i+win_p1>datalen_real) str[i-1/*n2*/]=' ';
	    else str[i-1/*n2*/]=bw_get_bua1.get_smg_data(win_p1+i-1);
	  }
	  str[datalen-1/*n2*/+1]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	}
/*
      }
*/
      win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
      HideCaret(bw_main1.win_hwnd);
      SetCaretPos(win_p_x,win_p_y);
      ShowCaret(bw_main1.win_hwnd);
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==LEFT_ROW)
    {



  // get prev char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  bw_get_bua1.gets_smg_data(s1,SMG_LEN);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(s1)))
  {
    if (s1[k]<0) k=k+2;
    else k=k+1;

    j++;

    pos[j]=k;
  }

  j=0;
  w=0;
  w2=0;

  for (k=0;k<300;k++)
  {
    if (pos[k]==(win_p1+n2-1))
    {
      if (k>0)
      {
        j=pos[k-1];

        if (s1[j]<0) w=2;
        else w=1;
        w2=0;
      }
      else
      {
        j=pos[0];

        w=1;
        w2=0;
      }
      break;
    }

    if (pos[k]>(win_p1+n2-1))
    {
      if (k>=2)
      {
        j=pos[k-2];

        if (s1[j]<0) w=2;
        else w=1;
        w2=1;
      }
      else 
      {
        if (k==1)
        {
          j=pos[0];

          w=0;
          w2=1;
        }
        else
        {
          j=(win_p1+n2-1);

          w=0;
          w2=0;
        }
      }

      break;
    }

    if (pos[k]<0) break;
  }



      if (n2>w+w2)
      {
        n2=n2-w-w2;
	scrn_c=scrn_c-w-w2;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_edit_mode[pp]==1)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (win_p1>0)
	{
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_befor(s1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==RIGHT_ROW)
    {



  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  bw_get_bua1.gets_smg_data(s1,SMG_LEN);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(s1)))
  {
    if (s1[k]<0) k=k+2;
    else k=k+1;

    j++;

    pos[j]=k;
  }

  j=0;
  w=0;
  w2=0;

  for (k=0;k<300;k++)
  {
    if (pos[k]==(win_p1+n2-1))
    {
      j=pos[k];

      if (s1[j]<0) w=2;
      else w=1;
      w2=0;

      break;
    }

    if (pos[k]>(win_p1+n2-1))
    {
      w=0;
      w2=1;

      break;
    }

    if (pos[k]<0) break;
  }



      if (n2+w+w2-1<datalen)
      {
        n2=n2+w+w2;
	scrn_c=scrn_c+w+w2;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_edit_mode[pp]==1)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (n2+win_p1<datalen_real)
	{
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_after(s1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
	  TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
	  SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==UP_ROW)
    {

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
    if (key==DOWN_ROW)
    {

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
    if (key==BACKSP)
    {



  // get prev char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  bw_get_bua1.gets_smg_data(s1,SMG_LEN);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(s1)))
  {
    if (s1[k]<0) k=k+2;
    else k=k+1;

    j++;

    pos[j]=k;
  }

  j=0;
  w=0;
  w2=0;

  for (k=0;k<300;k++)
  {
    if (pos[k]==(win_p1+n2-1))
    {
      if (k>0)
      {
        j=pos[k-1];

        if (s1[j]<0) w=2;
        else w=1;
        w2=0;
      }
      else
      {
        j=pos[0];

        w=1;
        w2=0;
      }
      break;
    }

    if (pos[k]>(win_p1+n2-1))
    {
      if (k>=2)
      {
        j=pos[k-2];

        if (s1[j]<0) w=2;
        else w=1;
        w2=1;
      }
      else 
      {
        if (k==1)
        {
          j=pos[0];

          w=0;
          w2=1;
        }
        else
        {
          j=(win_p1+n2-1);

          w=0;
          w2=0;
        }
      }

      break;
    }

    if (pos[k]<0) break;
  }



      if (n2>w+w2)
      {
        n2=n2-w2;
        scrn_c=scrn_c-w2;

        if (w==1)
        {
  	  for (i=n2+win_p1;i<=datalen_real;i++)
	  {
	    bw_get_bua1.set_smg_data(i-1-1,bw_get_bua1.get_smg_data(i-1));
	  }
	  bw_get_bua1.set_smg_data(datalen_real-1,' ');
	  n2--;
	  scrn_c--;
        }
        else 
        {
          if (w==2)
          {
    	    for (i=n2+win_p1;i<=datalen_real;i++)
	    {
	      bw_get_bua1.set_smg_data(i-1-2,bw_get_bua1.get_smg_data(i-1));
	    }
	    bw_get_bua1.set_smg_data(datalen_real-2,' ');
	    bw_get_bua1.set_smg_data(datalen_real-1,' ');
	    n2=n2-w;
	    scrn_c=scrn_c-w;
          }
        }

	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str[i-n2]=' ';
	  else str[i-n2]=bw_get_bua1.get_smg_data(win_p1+i-1);
	}
	str[datalen-n2+1]=0;
	HideCaret(bw_main1.win_hwnd);
	TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_p1>0)
	{
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_befor(s1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
          for (i=1;i<=datalen;i++)
          {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
            else str[i-1]=' ';
          }
          str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==RET_KEY)
    {

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
/*
    if (key==INSERT)
    {
      if (smg_insert==1)
      {
	smg_insert=0;
      }
      else
      {
	smg_insert=1;
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
*/
    if (key==DEL_KEY)
    {



  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  bw_get_bua1.gets_smg_data(s1,SMG_LEN);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(s1)))
  {
    if (s1[k]<0) k=k+2;
    else k=k+1;

    j++;

    pos[j]=k;
  }

  j=0;
  w=0;
  w2=0;

  for (k=0;k<300;k++)
  {
    if (pos[k]==(win_p1+n2-1))
    {
      j=pos[k];

      if (s1[j]<0) w=2;
      else w=1;
      w2=0;

      break;
    }

    if (pos[k]>(win_p1+n2-1))
    {
      w=0;
      w2=1;

      break;
    }

    if (pos[k]<0) break;
  }



      if (win_p1+n2<datalen_real)
      {
        n2=n2-w2;
        scrn_c=scrn_c-w2;

        if (w==1)
        {
	  for (i=win_p1+n2+1;i<=datalen_real;i++)
	  {
	    bw_get_bua1.set_smg_data(i-1-1,bw_get_bua1.get_smg_data(i-1));
	  }
	  bw_get_bua1.set_smg_data(datalen_real-1,' ');
        }
        else
        {
          if (w==2)
          {
	    for (i=win_p1+n2+2;i<=datalen_real;i++)
	    {
	      bw_get_bua1.set_smg_data(i-1-2,bw_get_bua1.get_smg_data(i-1));
	    }
	    bw_get_bua1.set_smg_data(datalen_real-2,' ');
	    bw_get_bua1.set_smg_data(datalen_real-1,' ');
          }
        }

	for (i=1/*n2*/;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str[i-1/*n2*/]=' ';
	  else str[i-1/*n2*/]=bw_get_bua1.get_smg_data(win_p1+i-1);
	}
	str[datalen-1/*n2*/+1]=0;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-n2+1-1));
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
	TextOut(hdc,win_p_x,win_p_y," ",1);
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
	bw_get_bua1.set_smg_data(win_p1+n2-1,' ');
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if ((key<32)||(key==PG_UP)||(key==PG_DOWN)||(key>200))
    {

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.win_hwnd,hdc);
    *posi=n2;
    return(0);
  }
  return(0);
}
int bw_getread::get_num(int scrn_l,int scrn_c,char *atten,
		    int datalen,int datalen_real,char link,
		    int pp,int color,int dec,int *posi)
{
  HDC   hdc;
  HFONT hfont,holdfont;
//  char *sp1;
  char str[SMG_LEN];
  char c1;
  char s1[SMG_LEN];
  int  n1,n2;
  int  i;
  int  key;
//  int  pp1;
  int  p2,p3;
/* --- display attention and data --- */
  win_get_pp=pp;
  win_get_link=link;
  win_color=color;

  n1=strlen(atten);

/* --- input command --- */
  if ( *posi > datalen ) *posi= datalen;
  n2= *posi;

  win_cur1=scrn_c+n1;

  scrn_c=scrn_c+n1+n2-1;

  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
  win_p_y=(int)(bw_main1.win_edit_ychar*(scrn_l-1));

  HideCaret(bw_main1.win_hwnd);
  SetCaretPos(win_p_x,win_p_y);
  ShowCaret(bw_main1.win_hwnd);

/* --- pre insert when smg_chns_next==1 --- */
  if (bw_main1.win_key!=0)
  {
    hdc=GetDC(bw_main1.win_hwnd);
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);

    key=bw_main1.win_key;

    if ( (key=='+')||(key=='-')||(key=='.')||(key==' ')||((key>='0')&&(key<='9')) )    //(((key>=32)&&(key<=126))/*||(key<0)*/)
    {
/*
      if ((key>=0)&&(win_chns_char==0))
      {
*/
        c1=key;
        str[0]=c1;
        str[1]=0;
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str,1);
	ShowCaret(bw_main1.win_hwnd);
/*
      }
      else
      {

        if (win_chns_char==0)
        {
          win_chns_char=1;
          win_chns_str[0]=key;
          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
         return(0);
        }
        else
        {
          win_chns_str[1]=key;
          win_chns_str[2]=0;
	  HideCaret(bw_main1.win_hwnd);
          if (n2+2>datalen)
            TextOut(hdc,win_p_x,win_p_y,win_chns_str,1);
          else
            TextOut(hdc,win_p_x,win_p_y,win_chns_str,2);
	  ShowCaret(bw_main1.win_hwnd);
        }

      }
*/
/*
      if (smg_insert==0)
      {
        if (win_chns_char==0)
        {
	  bw_get_bua1.set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        }
        else
        {
          win_chns_char=0;
	  bw_get_bua1.set_smg_data(win_p1+n2-1,win_chns_str[0]);
	  if (win_p1+n2<datalen_real)
	    bw_get_bua1.set_smg_data(win_p1+n2-0,win_chns_str[1]);
          n2=n2+2;
          scrn_c=scrn_c+2;
        }
	if (win_p1+n2>datalen_real)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          //win_chns_char=0;
          return(RET_KEY);
	}
	if (n2>datalen)
	{
	  if (win_edit_mode[pp]==1)
	  {
	    get_num_conv(datalen_real,dec);

	    win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	      else str[i-1]=' ';
	    }
	    str[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	    ShowCaret(bw_main1.win_hwnd);

            SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_after(s1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
      }
      else
      {
*/      // insert
        if (win_chns_char==0)
        {
	  for (i=datalen_real-1;i>=n2+win_p1;i--)
	  {
	    bw_get_bua1.set_smg_data(i+1-1,bw_get_bua1.get_smg_data(i-1));
	  }
	  bw_get_bua1.set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
        }
        else
        {
/*
          win_chns_char=0;
	  for (i=datalen_real-2;i>=n2+win_p1;i--)
	  {
	    bw_get_bua1.set_smg_data(i+2-1,bw_get_bua1.get_smg_data(i-1));
	  }
	  bw_get_bua1.set_smg_data(win_p1+n2-1,win_chns_str[0]);
	  bw_get_bua1.set_smg_data(win_p1+n2-0,win_chns_str[1]);
	  n2=n2+2;
	  scrn_c=scrn_c+2;
*/
        }
	if (win_p1+n2>datalen_real)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          //win_chns_char=0;
          return(RET_KEY);
	}
	if (n2>datalen)
	{
	  if (win_edit_mode[pp]==1)
	  {
	    get_num_conv(datalen_real,dec);

	    win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	      else str[i-1]=' ';
	    }
	    str[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	    ShowCaret(bw_main1.win_hwnd);

	    SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_after(s1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  for (i=n2;i<=datalen;i++)
	  {
	    if (i+win_p1>datalen_real) str[i-n2]=' ';
	    else str[i-n2]=bw_get_bua1.get_smg_data(win_p1+i-1);
	  }
	  str[datalen-n2+1]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	}
/*
      }
*/
      win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
      HideCaret(bw_main1.win_hwnd);
      SetCaretPos(win_p_x,win_p_y);
      ShowCaret(bw_main1.win_hwnd);
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==LEFT_ROW)
    {
      if (n2>1)
      {
        n2--;
	scrn_c--;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_edit_mode[pp]==1)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (win_p1>0)
	{
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_befor(s1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==RIGHT_ROW)
    {
      if (n2<datalen)
      {
        n2++;
	scrn_c++;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_edit_mode[pp]==1)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (n2+win_p1<datalen_real)
	{
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_after(s1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  str[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
	  TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
	  SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-1]=' ';
	  }
	  str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==UP_ROW)
    {
      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
    if (key==DOWN_ROW)
    {
      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
    if (key==BACKSP)
    {
      if (n2>1)
      {
	for (i=n2+win_p1;i<=datalen_real;i++)
	{
	  bw_get_bua1.set_smg_data(i-1-1,bw_get_bua1.get_smg_data(i-1));
	}
	bw_get_bua1.set_smg_data(datalen_real-1,' ');
	n2--;
	scrn_c--;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str[i-n2]=' ';
	  else str[i-n2]=bw_get_bua1.get_smg_data(win_p1+i-1);
	}
	str[datalen-n2+1]=0;
	HideCaret(bw_main1.win_hwnd);
	TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_p1>0)
	{
	  bw_get_bua1.gets_smg_data(s1,SMG_LEN);
	  p2=get_txt_befor(s1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str[i-win_p1-1]=bw_get_bua1.get_smg_data(i-1);
	    else str[i-win_p1-1]=' ';
	  }
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.win_hwnd);
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.win_hwnd);
	}
	else
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
          for (i=1;i<=datalen;i++)
          {
	    if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
            else str[i-1]=' ';
          }
          str[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if (key==RET_KEY)
    {
      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
/*
    if (key==INSERT)
    {
      if (smg_insert==1)
      {
	smg_insert=0;
      }
      else
      {
	smg_insert=1;
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
*/
    if (key==DEL_KEY)
    {
      if (win_p1+n2<datalen_real)
      {
	for (i=win_p1+n2+1;i<=datalen_real;i++)
	{
	  bw_get_bua1.set_smg_data(i-1-1,bw_get_bua1.get_smg_data(i-1));
	}
	bw_get_bua1.set_smg_data(datalen_real-1,' ');
	for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str[i-n2]=' ';
	  else str[i-n2]=bw_get_bua1.get_smg_data(win_p1+i-1);
	}
	str[datalen-n2+1]=0;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
	SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
	TextOut(hdc,win_p_x,win_p_y," ",1);
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
	bw_get_bua1.set_smg_data(win_p1+n2-1,' ');
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
    }
    if ((key<32)||(key==PG_UP)||(key==PG_DOWN)||(key>200))
    {
      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str[i-1]=bw_get_bua1.get_smg_data(i-1);
        else str[i-1]=' ';
      }
      str[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str,strlen(str));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);
    }
    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.win_hwnd,hdc);
    *posi=n2;
    return(0);
  }
  return(0);
}
int bw_getread::get_num_conv(int datalen_real,int dec)
{
  char s_tmpc1[SMG_LEN];
  int  s_state1;
  int  i,j;
/* convert to number */
  for (i=0;i<=60;i++)  s_tmpc1[i]=' ';
  s_state1=0;
  if (datalen_real!=0)
  {
/*
    for (i=datalen_real-1;i<=datalen_real-1;i++) bw_get_bua1.get_smg_data[i]=' ';
*/
    for (i=0;i<=datalen_real-1;i++)
    {
      if (bw_get_bua1.get_smg_data(i)>='0') s_state1=1;
      if ((bw_get_bua1.get_smg_data(i)==' ')&&(s_state1==1)) break;
    }
    for (i=i+1;i<=datalen_real-1;i++) bw_get_bua1.set_smg_data(i,' ');
  }
  for (i=0;i<=datalen_real-1;i++) if (bw_get_bua1.get_smg_data(i)=='.') break;
  if (i>=datalen_real)
  {
    for (i=datalen_real-1;i>=0;i--) if (bw_get_bua1.get_smg_data(i)>' ') break;
    i++;
  }
  for (j=0;j<=i-1;j++) s_tmpc1[30-i+j]=bw_get_bua1.get_smg_data(j);
  s_tmpc1[30]='.';
  for (j=i+1;j<=datalen_real-1;j++) s_tmpc1[30+j-i]=bw_get_bua1.get_smg_data(j);
  for (j=0;j<=datalen_real-1;j++)
    if (dec==0)
      bw_get_bua1.set_smg_data(j,s_tmpc1[30-datalen_real+j]);
    else
      bw_get_bua1.set_smg_data(j,s_tmpc1[30-(datalen_real-dec-1)+j]);

  return(0);
}
int bw_getread::get_txt_after(char *data,int l2,int l1,int p1)
{
/*
  if (data[p1]>=0)// &&(data[p1]<=127)) 
  {
    if (p1+1<=l2) return(p1+1);
    else return(p1);
  }
  else
  {
    if ((p1+2<=l2)&&(2<=l1)) return(p1+2);
    else
    {
      if (p1+1>l2) return(p1);
      else return(p1+1);
    }
  }
*/

  int pos[300];
  int i,j;

  for (i=0;i<300;i++) pos[i]=(-1);

  i=0;
  j=0;
  pos[0]=0;

  while((i<l2)&&(i<strlen(data)))
  {
    if (data[i]<0) i=i+2;
    else i=i+1;

    j++;

    pos[j]=i;
  }

  j=p1;

  for (i=0;i<300;i++)
  {
    if (pos[i]>p1)
    {
      j=pos[i];

      break;
    }

    if (pos[i]<0) break;
  }

  return(j);
}
int bw_getread::get_txt_befor(char *data,int l1,int p1)
{
/*
  if (p1<2) 
  {
    if (p1>=1) return(p1-1);
    else return(p1);
  }
  else
  {



  if (data[p1-2]>=0)//&&(data[p1-1]<=127))
  {
    return(p1-1);
  }
  else
  {
    return(p1-2);
  }



  }
*/

  int pos[300];
  int i,j;

  for (i=0;i<300;i++) pos[i]=(-1);

  i=0;
  j=0;
  pos[0]=0;

  while(/*(i<l1)&&*/(i<strlen(data)))
  {
    if (data[i]<0) i=i+2;
    else i=i+1;

    j++;

    pos[j]=i;
  }

  j=0;

  for (i=0;i<300;i++)
  {
    if (pos[i]==p1)
    {
      if (i>0) j=pos[i-1];
      else j=pos[0];

      break;
    }

    if (pos[i]>p1)
    {
      if (i>=2) j=pos[i-2];
      else 
      {
        if (i==1) j=pos[0];
        else j=p1;
      }

      break;
    }

    if (pos[i]<0) break;
  }

  return(j);
}

int bw_getread::deb_record_init(void)
{

	deb_record_fp=fopen("deb_record.txt","w");
	if (deb_record_fp==NULL) return(1);

	return(0);
}

int bw_getread::deb_record_close(void)
{
	fclose(deb_record_fp);

	return(0);
}

int bw_getread::deb_record(char *p_str1)
{

	fputs(p_str1,deb_record_fp);
	fputs("\n",deb_record_fp);

	return(0);
}









