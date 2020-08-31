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

#include "vc_bowo.h"

extern class bw_main     bw_main1;
extern class bw_getread  bw_getread1;


int bw_getread::get_read_ini()
{
  int i;
  for (i=0;i<GET_NUM;i++) set_smg_read_id(i,0);
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
    if (get_smg_read_id(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(0);
  else
  {
    set_smg_read_id(i,1);
    return(i);
  }
}

int bw_getread::get_read_logout(int pp)
{
  if ((pp<0)||(pp>=GET_NUM)) return(-1);
  else
  {
    set_smg_line(pp,0);
    set_smg_colu(pp,0);
    setc_smg_string(pp,0,0);
    set_smg_type(pp,0);
    set_smg_dlen(pp,0);
    set_smg_dlen2(pp,0);
    set_smg_ddec(pp,0);
    set_smg_link(pp,0);
    set_smg_color(pp,0);
    set_smg_read_id(pp,0);
    return(0);
  }
}

int bw_getread::tst_getread()
{
  HDC  hdc;
  int  i;
  char str2[SMG_SIZE];
  char str1[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<=12;i++)
  {
    get_smg_string(i,str1,SMG_SIZE);

    sprintf(str2,"l=%d,c=%d,d=%s,t=%d,n=%d,n2=%d,dc=%d,l=%d,c=%d,id=%d,"
	    ,get_smg_line(i),get_smg_colu(i),str1
	    ,get_smg_type(i),get_smg_dlen(i),get_smg_dlen2(i)
	    ,get_smg_ddec(i),get_smg_link(i),get_smg_color(i)
	    ,get_smg_read_id(i));
    TextOut(hdc,1,i*20,str2,strlen(str2));
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

  char  s_tmps1[SMG_SIZE];
  int   key;
  int   i,j,k,w;
  char  s1[SMG_SIZE];
  char  s2[SMG_SIZE];
  int   pos[300];

  if (command=='g')
  {
    if (array_pp<0)        return(1);
    if (array_pp>=GET_NUM) return(1);

    smg_pp=array_pp;

    set_smg_line(smg_pp,scrn_l);
    set_smg_colu(smg_pp,scrn_c);
    set_smg_atte(smg_pp,atten,strlen(atten)+1);
    set_smg_type(smg_pp,datatype);
    set_smg_dlen(smg_pp,datalen);
    set_smg_dlen2(smg_pp,datalen_real);
    set_smg_ddec(smg_pp,datadec);
    set_smg_link(smg_pp,link);
    set_smg_color(smg_pp,color);
    set_smg_posi(smg_pp,posi);
    set_smg_string(smg_pp,string,strlen(string)+1);

    if (datatype=='n')
    {
      for (i=0;i<=60;i++)  s_tmps1[i]=' ';
      for (i=0;i<=datalen_real-1;i++) if (string[i]=='.') break;
      if (i>=datalen_real)
      {
	for (i=datalen_real-1;i>=0;i--) if (string[i]>' ') break;
	i++;
      }
      for (j=0;j<=i-1;j++) s_tmps1[30-i+j]=string[j];
      s_tmps1[30]='.';
      for (j=i+1;j<=datalen_real-1;j++) s_tmps1[30+j-i]=string[j];
      for (j=0;j<=datalen_real-1;j++)
      {
	if (datadec==0) string[j]=s_tmps1[30-datalen_real+j];
	else string[j]=s_tmps1[30-(datalen_real-datadec-1)+j];
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

    get_smg_string(smg_pp,s1,SMG_SIZE);
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
    get_smg_string(smg_pp,s1,SMG_SIZE);

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

      get_smg_string(smg_pp2,s1,SMG_SIZE);

      for (i=0;i<get_smg_dlen2(smg_pp2);i++)
      {
	if (i>=(int)strlen(s1)) set_smg_data(i,' ');
        else set_smg_data(i,s1[i]);
      }
      for (i=i;i<SMG_SIZE;i++) set_smg_data(i,' ');

      if (get_smg_type(smg_pp2)=='c')
      {
	get_smg_atte(smg_pp2,s2,SMG_SIZE);

        key=get_txt(
get_smg_line(smg_pp2),get_smg_colu(smg_pp2),s2,
get_smg_dlen(smg_pp2),get_smg_dlen2(smg_pp2),get_smg_link(smg_pp2),
smg_pp2,get_smg_color(smg_pp2),get_smg_posi(smg_pp2));
      }
      else
      {
	get_smg_atte(smg_pp2,s2,SMG_SIZE);

	key=get_num(
get_smg_line(smg_pp2),get_smg_colu(smg_pp2),s2,
get_smg_dlen(smg_pp2),get_smg_dlen2(smg_pp2),get_smg_link(smg_pp2),
smg_pp2,get_smg_color(smg_pp2),get_smg_ddec(smg_pp2),get_smg_posi(smg_pp2));
      }
      for (i=0;i<get_smg_dlen2(smg_pp2);i++)
      {
	setc_smg_string(smg_pp2,i,get_smg_data(i));
      }
      setc_smg_string(smg_pp2,i,0);

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
  char str2[SMG_SIZE];
  char c1;
  char str1[SMG_SIZE];
  int  n1,n2;
  int  i;
  int  key;
  int  p2,p3;
  int  w,w2;

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
    sprintf(str1,"win_key=%d,",bw_main1.win_key);
    deb_record(str1);
*/
    if (((key>=32)&&(key<=126))||(key<0))
    {
      if ((key>=0)&&(win_chns_char==0))
      {
        c1=key;
        str2[0]=c1;
        str2[1]=0;
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str2,1);
	ShowCaret(bw_main1.win_hwnd);
/*
        // --- debug ---
        deb_record(str2);
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
	  set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        }
        else
        {
          win_chns_char=0;
	  set_smg_data(win_p1+n2-1,win_chns_str[0]);
	  if (win_p1+n2<=datalen_real)
	    set_smg_data(win_p1+n2-0,win_chns_str[1]);
          n2=n2+2;
          scrn_c=scrn_c+2;
        }
	if (win_p1+n2>datalen_real)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.win_hwnd);

            SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
          gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
  gets_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(str1)))
  {
    if (str1[k]<0) k=k+2;
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
	    set_smg_data(i+1-1,get_smg_data(i-1));
	  }
	  set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
        }
        else
        {
          win_chns_char=0;
	  for (i=datalen_real-2;i>=n2+win_p1;i--)
	  {
	    set_smg_data(i+2-1,get_smg_data(i-1));
	  }
	  set_smg_data(win_p1+n2+0-1,win_chns_str[0]);
	  set_smg_data(win_p1+n2+1-1,win_chns_str[1]);
	  n2=n2+2;
	  scrn_c=scrn_c+2;
        }
	if (win_p1+n2>datalen_real)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    gets_smg_data(str1,SMG_SIZE);
	    p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	    p3=p2-win_p1;
	    win_p1=p2;
	    win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	    for (i=win_p1+1;i<=win_p1+datalen;i++)
	    {
	      if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	      else str2[i-win_p1-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i+win_p1>datalen_real) str2[i-1/*n2*/]=' ';
	    else str2[i-1/*n2*/]=get_smg_data(win_p1+i-1);
	  }
	  str2[datalen-1/*n2*/+1]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
  gets_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(str1)))
  {
    if (str1[k]<0) k=k+2;
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

        if (str1[j]<0) w=2;
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

        if (str1[j]<0) w=2;
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (win_p1>0)
	{
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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


/*
  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  gets_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*//*(k<strlen(str1)))
  {
    if (str1[k]<0) k=k+2;
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

      if (str1[j]<0) w=2;
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
	if (n2+win_p1<datalen_real)
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
	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
        }
      }
      else
      {
	if (win_edit_mode[pp]==1)
	{

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (n2+win_p1<datalen_real)
	{
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
	  TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
      return(0);*/


      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=bw_getread1.get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.win_hwnd);

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      win_p1=0;
      return(key);


    }
    if (key==UP_ROW)
    {

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
  gets_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(str1)))
  {
    if (str1[k]<0) k=k+2;
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

        if (str1[j]<0) w=2;
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

        if (str1[j]<0) w=2;
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
	    set_smg_data(i-1-1,get_smg_data(i-1));
	  }
	  set_smg_data(datalen_real-1,' ');
	  n2--;
	  scrn_c--;
        }
        else 
        {
          if (w==2)
          {
    	    for (i=n2+win_p1;i<=datalen_real;i++)
	    {
	      set_smg_data(i-1-2,get_smg_data(i-1));
	    }
	    set_smg_data(datalen_real-2,' ');
	    set_smg_data(datalen_real-1,' ');
	    n2=n2-w;
	    scrn_c=scrn_c-w;
          }
        }

	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str2[i-n2]=' ';
	  else str2[i-n2]=get_smg_data(win_p1+i-1);
	}
	str2[datalen-n2+1]=0;
	HideCaret(bw_main1.win_hwnd);
	TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_p1>0)
	{
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
            else str2[i-1]=' ';
          }
          str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
  gets_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(/*(k<l1)&&*/(k<strlen(str1)))
  {
    if (str1[k]<0) k=k+2;
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

      if (str1[j]<0) w=2;
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
	    set_smg_data(i-1-1,get_smg_data(i-1));
	  }
	  set_smg_data(datalen_real-1,' ');
        }
        else
        {
          if (w==2)
          {
	    for (i=win_p1+n2+2;i<=datalen_real;i++)
	    {
	      set_smg_data(i-1-2,get_smg_data(i-1));
	    }
	    set_smg_data(datalen_real-2,' ');
	    set_smg_data(datalen_real-1,' ');
          }
        }

	for (i=1/*n2*/;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str2[i-1/*n2*/]=' ';
	  else str2[i-1/*n2*/]=get_smg_data(win_p1+i-1);
	}
	str2[datalen-1/*n2*/+1]=0;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-n2+1-1));
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	set_smg_data(win_p1+n2-1,' ');
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
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
  char str2[SMG_SIZE];
  char c1;
  char str1[SMG_SIZE];
  int  n1,n2;
  int  i;
  int  key;
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
        str2[0]=c1;
        str2[1]=0;
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str2,1);
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
	  set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        }
        else
        {
          win_chns_char=0;
	  set_smg_data(win_p1+n2-1,win_chns_str[0]);
	  if (win_p1+n2<datalen_real)
	    set_smg_data(win_p1+n2-0,win_chns_str[1]);
          n2=n2+2;
          scrn_c=scrn_c+2;
        }
	if (win_p1+n2>datalen_real)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.win_hwnd);

            SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    set_smg_data(i+1-1,get_smg_data(i-1));
	  }
	  set_smg_data(win_p1+n2-1,c1);
	  n2++;
	  scrn_c++;
        }
        else
        {
/*
          win_chns_char=0;
	  for (i=datalen_real-2;i>=n2+win_p1;i--)
	  {
	    set_smg_data(i+2-1,get_smg_data(i-1));
	  }
	  set_smg_data(win_p1+n2-1,win_chns_str[0]);
	  set_smg_data(win_p1+n2-0,win_chns_str[1]);
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.win_hwnd);
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.win_hwnd);

	    SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.win_hwnd,hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i+win_p1>datalen_real) str2[i-n2]=' ';
	    else str2[i-n2]=get_smg_data(win_p1+i-1);
	  }
	  str2[datalen-n2+1]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (win_p1>0)
	{
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
/*
      if (n2<datalen)
      {
        if (n2+win_p1<datalen_real)
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
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
        }
      }
      else
      {
	if (win_edit_mode[pp]==1)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
	}
	if (n2+win_p1<datalen_real)
	{
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  HideCaret(bw_main1.win_hwnd);
	  TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
*/
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.win_hwnd);

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.win_hwnd,hdc);
          *posi=n2;
          win_p1=0;
          return(key);
/*
	}
      }
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.win_hwnd,hdc);
      *posi=n2;
      return(0);
*/
    }
    if (key==UP_ROW)
    {
      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	  set_smg_data(i-1-1,get_smg_data(i-1));
	}
	set_smg_data(datalen_real-1,' ');
	n2--;
	scrn_c--;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
        for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str2[i-n2]=' ';
	  else str2[i-n2]=get_smg_data(win_p1+i-1);
	}
	str2[datalen-n2+1]=0;
	HideCaret(bw_main1.win_hwnd);
	TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	ShowCaret(bw_main1.win_hwnd);
	HideCaret(bw_main1.win_hwnd);
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.win_hwnd);
      }
      else
      {
	if (win_p1>0)
	{
	  gets_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1-1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
            else str2[i-1]=' ';
          }
          str2[datalen]=0;
	  HideCaret(bw_main1.win_hwnd);
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	  set_smg_data(i-1-1,get_smg_data(i-1));
	}
	set_smg_data(datalen_real-1,' ');
	for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str2[i-n2]=' ';
	  else str2[i-n2]=get_smg_data(win_p1+i-1);
	}
	str2[datalen-n2+1]=0;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	HideCaret(bw_main1.win_hwnd);
        TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
	set_smg_data(win_p1+n2-1,' ');
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
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.win_hwnd);
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
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
  char s_tmps1[SMG_SIZE];
  int  s_state1;
  int  i,j;
/* convert to number */
  for (i=0;i<=60;i++)  s_tmps1[i]=' ';
  s_state1=0;
  if (datalen_real!=0)
  {
/*
    for (i=datalen_real-1;i<=datalen_real-1;i++) get_smg_data[i]=' ';
*/
    for (i=0;i<=datalen_real-1;i++)
    {
      if (get_smg_data(i)>='0') s_state1=1;
      if ((get_smg_data(i)==' ')&&(s_state1==1)) break;
    }
    for (i=i+1;i<=datalen_real-1;i++) set_smg_data(i,' ');
  }
  for (i=0;i<=datalen_real-1;i++) if (get_smg_data(i)=='.') break;
  if (i>=datalen_real)
  {
    for (i=datalen_real-1;i>=0;i--) if (get_smg_data(i)>' ') break;
    i++;
  }
  for (j=0;j<=i-1;j++) s_tmps1[30-i+j]=get_smg_data(j);
  s_tmps1[30]='.';
  for (j=i+1;j<=datalen_real-1;j++) s_tmps1[30+j-i]=get_smg_data(j);
  for (j=0;j<=datalen_real-1;j++)
    if (dec==0)
      set_smg_data(j,s_tmps1[30-datalen_real+j]);
    else
      set_smg_data(j,s_tmps1[30-(datalen_real-dec-1)+j]);

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
int bw_getread::get_txt_before(char *data,int l1,int p1)
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

	deb_record_fp=fopen("deb_record.txt","a");
	if (deb_record_fp==NULL) return(1);
	fclose(deb_record_fp);

	return(0);
}

int bw_getread::deb_record_close(void)
{
	//fclose(deb_record_fp);

	return(0);
}

int bw_getread::deb_record(char *p_str1)
{

	deb_record_fp=fopen("deb_record.txt","a");
	if (deb_record_fp==NULL) return(1);

	fputs(p_str1,deb_record_fp);
	fputs("\n",deb_record_fp);

	fclose(deb_record_fp);

	return(0);
}





int bw_getread::get_smg_line(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_line[gpp]);
}
int bw_getread::get_smg_colu(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_colu[gpp]);
}
int bw_getread::get_smg_data(int pp1)
{
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  return(smg_data[pp1]);
}
int bw_getread::gets_smg_data(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=smg_data[j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_getread::get_smg_string(int gpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((gpp<0)||(gpp>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=smg_string[gpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_getread::getc_smg_string(int gpp,int pp1)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  return(smg_string[gpp][pp1]);
}
int bw_getread::get_smg_type(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_type[gpp]);
}
int bw_getread::get_smg_dlen(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_dlen[gpp]);
}
int bw_getread::get_smg_dlen2(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_dlen2[gpp]);
}
int bw_getread::get_smg_ddec(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_ddec[gpp]);
}
int bw_getread::get_smg_link(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_link[gpp]);
}
int bw_getread::get_smg_color(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_color[gpp]);
}
int * bw_getread::get_smg_posi(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_posi[gpp]);
}
int bw_getread::get_smg_atte(int gpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((gpp<0)||(gpp>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=smg_atte[gpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_getread::get_smg_read_id(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_read_id[gpp]);
}

int bw_getread::set_smg_line(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_line[gpp]=val;
  return(0);
}
int bw_getread::set_smg_colu(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_colu[gpp]=val;
  return(0);
}
int bw_getread::set_smg_data(int pp1,int val)
{
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  smg_data[pp1]=val;
  return(0);
}
int bw_getread::set_smg_type(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_type[gpp]=val;
  return(0);
}
int bw_getread::set_smg_dlen(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_dlen[gpp]=val;
  return(0);
}
int bw_getread::set_smg_dlen2(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_dlen2[gpp]=val;
  return(0);
}
int bw_getread::set_smg_ddec(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_ddec[gpp]=val;
  return(0);
}
int bw_getread::set_smg_link(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_link[gpp]=val;
  return(0);
}
int bw_getread::set_smg_color(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_color[gpp]=val;
  return(0);
}
int bw_getread::set_smg_posi(int gpp,int *val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_posi[gpp]=val;
  return(0);
}
int bw_getread::set_smg_read_id(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_read_id[gpp]=val;
  return(0);
}
int bw_getread::set_smg_string(int gpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((gpp<0)||(gpp>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  smg_string[gpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    smg_string[gpp][j+0]=p_s1[j];
    smg_string[gpp][j+1]=0;
  }

  return(0);
}
int bw_getread::setc_smg_string(int gpp,int pp1,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  smg_string[gpp][pp1]=val;
  return(0);
}
int bw_getread::set_smg_atte(int gpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((gpp<0)||(gpp>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  smg_atte[gpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    smg_atte[gpp][j+0]=p_s1[j];
    smg_atte[gpp][j+1]=0;
  }

  return(0);
}
