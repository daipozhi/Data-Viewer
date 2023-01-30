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
extern class bw_inkey    bw_inkey1;


int bw_getread::get_read_ini()
{
  int i;

  for (i=0;i<GET_NUM;i++) set_smg_read_id(i,0);
  smg_insert=1;

  return(0);
}
/*
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

  if (exist==0) return(-1);

  set_smg_read_id(i,1);

  return(i);
}
*/
int bw_getread::get_read_logout(int ptr)
{
  if ((ptr<0)||(ptr>=GET_NUM)) return(1);

  set_smg_line(ptr,0);
  set_smg_colu(ptr,0);
  set_c_smg_string(ptr,0,0);
  set_smg_type(ptr,0);
  set_smg_dlen(ptr,0);
  set_smg_dlen_real(ptr,0);
  set_smg_ddec(ptr,0);
  set_smg_link(ptr,0);
  set_smg_color(ptr,0);
  set_smg_read_id(ptr,0);
  set_smg_modi(ptr,0);
  
  return(0);
}

int bw_getread::tst_getread()
{
  HDC  hdc;
  int  i;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE*2];

  deb_record("bw_getread::tst_getread()");

  for (i=0;i<=12;i++)
  {
    get_smg_string(i,str1,SMG_SIZE);

    sprintf(str2,"ptr=%d,smg_line=%d,colu=%d,data=%s,type=%c,len=%d,len2=%d,dec=%d,link=%d,color=%d,id=%d,"
	    ,i,get_smg_line(i),get_smg_colu(i),str1
	    ,get_smg_type(i),get_smg_dlen(i),get_smg_dlen_real(i)
	    ,get_smg_ddec(i),get_smg_link(i),get_smg_color(i)
	    ,get_smg_read_id(i));

    bw_getread1.deb_record(str2);
  }

  return(0);
}

int bw_getread::get_read(int p_wptr,int scrn_l,int scrn_c,char *atten,
                     char *string,int datalen,char datatype,
		     char command,int datalen_real,int datadec,
		     char link,int color,int posi,
		     int  array_ptr)
{  
  HDC   hdc;
  HFONT hfont,holdfont;
  int   key;
  int   i,j,k,w,u;
  char  s1[SMG_SIZE];
  char  s2[SMG_SIZE];
  char  s3[SMG_SIZE];
  int   pos[300];
  char  str1[SMG_SIZE];

  if (command=='g')
  {
    if (array_ptr<0)        return(1);
    if (array_ptr>=GET_NUM) return(1);

    
    //sprintf(str1, "win_hnd_id=%d,wp=%d,", win_hnd_id, wp);
    //bw_getread1.deb_record("get read ,g");
    

    smg_ptr=array_ptr;

    set_smg_line(smg_ptr,scrn_l);
    set_smg_colu(smg_ptr,scrn_c);
    set_smg_atte(smg_ptr,atten,strlen(atten)+1);
    set_smg_type(smg_ptr,datatype);
    set_smg_dlen(smg_ptr,datalen);
    set_smg_dlen_real(smg_ptr,datalen_real);
    set_smg_ddec(smg_ptr,datadec);
    set_smg_link(smg_ptr,link);
    set_smg_color(smg_ptr,color);
    set_smg_posi(smg_ptr,posi);
    set_smg_string(smg_ptr,string,strlen(string)+1);
    //set_smg_modi(smg_ptr,0);

    win_p_y=(int)(bw_main1.win_edit_ychar*(scrn_l));
    win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));

    i=strlen(atten);

    hdc=GetDC(bw_main1.get_win_hwnd(p_wptr));
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
    TextOut(hdc,win_p_x,win_p_y,atten,i);

    win_p_x=win_p_x+(int)(i*bw_main1.win_edit_xchar);

    get_smg_string(smg_ptr,s1,SMG_SIZE);
    i=strlen(s1);
    if (i>datalen) i=datalen;

    u=bw_inkey1.w_chs_string_cut(s1,i);
    s1[u]=0;

    strcat(s1," ");
    s1[i]=0;

    HideCaret(bw_main1.get_win_hwnd(p_wptr));
    TextOut(hdc,win_p_x,win_p_y,s1,strlen(s1));
    ShowCaret(bw_main1.get_win_hwnd(p_wptr));

    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);

    if (posi>datalen) posi=datalen;
    if (posi<1)       posi=1;



    // get char , avoid half chiness
    get_smg_string(smg_ptr,s1,SMG_SIZE);

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

      if (pos[k]<= posi-1)
      {
        w=pos[k];
      }

    }

    posi=w+1;



    HideCaret(bw_main1.get_win_hwnd(p_wptr));
    SetCaretPos(win_p_x+(int)((posi-1)*bw_main1.win_edit_xchar)
                 ,win_p_y);
    ShowCaret(bw_main1.get_win_hwnd(p_wptr));
  }
  else if (command=='r')
  {
    if (array_ptr<0)        return(1);
    if (array_ptr>=GET_NUM) return(1);


    //sprintf(str1, "win_hnd_id=%d,wp=%d,", win_hnd_id, wp);
    //bw_getread1.deb_record("get read ,r");


    smg_ptr2=array_ptr;

    get_smg_string(smg_ptr2,s1,SMG_SIZE);

    set_smg_data(0,0);

    for (i=0;i<get_smg_dlen_real(smg_ptr2);i++)
    {
      if (i>=(int)strlen(s1))
      {
        set_smg_data(i+0,' ');
        set_smg_data(i+1,0);
      }
      else
      {
        set_smg_data(i+0,s1[i]);
        set_smg_data(i+1,0);
      }
    }
    
    /*
    for (i=i;i<SMG_SIZE-1;i++)
    {
      set_smg_data(i+0,' ');
      set_smg_data(i+1,0);
    }
    */
    
    if (get_smg_type(smg_ptr2)=='c')
    {
      get_smg_atte(smg_ptr2,s2,SMG_SIZE);

      key=get_txt(
p_wptr,
get_smg_line(smg_ptr2),get_smg_colu(smg_ptr2),s2,
get_smg_dlen(smg_ptr2),get_smg_dlen_real(smg_ptr2),get_smg_link(smg_ptr2),
smg_ptr2,get_smg_color(smg_ptr2),get_smg_posi(smg_ptr2));
    }
    else
    {
      get_smg_atte(smg_ptr2,s2,SMG_SIZE);

      key=get_num(
p_wptr,
get_smg_line(smg_ptr2),get_smg_colu(smg_ptr2),s2,
get_smg_dlen(smg_ptr2),get_smg_dlen_real(smg_ptr2),get_smg_link(smg_ptr2),
smg_ptr2,get_smg_color(smg_ptr2),get_smg_ddec(smg_ptr2),get_smg_posi(smg_ptr2));
    }
      
    set_c_smg_string(smg_ptr2,0,0);
      
    for (i=0;i<get_smg_dlen_real(smg_ptr2);i++)
    {
      set_c_smg_string(smg_ptr2,i+0,get_smg_data(i));
      set_c_smg_string(smg_ptr2,i+1,0);
    }

    if (key!=0)
    {
      if (  (key==127)
            ||(key==ESC_KEY)
            ||(key==CTRL_W)
	    ||(key>200)
	    ||(key==RET_KEY)
	    ||((key<32)&&(key>0))  )

      {
	bw_main1.win_key=key;
	return(1);
      }
      else  if (  (((key>=32)&&(key<127))||(key<0))  &&
                  (win_confirm==0)  )  
      {
	if (win_edit_mode[array_ptr]==1) bw_main1.win_key=RIGHT_ROW;
	else bw_main1.win_key=10;
        return(1);
      }
    }
  }

  return(0);
}

int bw_getread::get_txt(int p_wptr,int scrn_l,int scrn_c,char *atten,
		    int datalen,int datalen_real,char link,
		    int ptr,int color,int posi)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  char c1;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  int  n1,n2;
  int  i,u;
  int  key;
  int  p2,p3;
  int  w,w2;

  int  j,k;
  int  pos[300];

/* --- display attention and data --- */
  //win_get_ptr=ptr;
  //win_get_link=link;
  //win_color=color;

  n1=strlen(atten);

/* --- input command --- */
  if ( posi > datalen ) posi= datalen;
  if ( posi<1)       posi=1;
  n2= posi;

  win_cur1=scrn_c+n1;

  scrn_c=scrn_c+n1+n2-1;

  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
  win_p_y=(int)(bw_main1.win_edit_ychar*(scrn_l));

  HideCaret(bw_main1.get_win_hwnd(p_wptr));
  SetCaretPos(win_p_x,win_p_y);
  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

/* --- pre insert when smg_chns_next==1 --- */
  if (bw_main1.win_key!=0)
  {
    if (bw_main1.win_key==410) return(0);
    if (bw_main1.win_key==427) return(0);
    if (bw_main1.win_key==639) return(0);

    hdc=GetDC(bw_main1.get_win_hwnd(p_wptr));
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);

    key=bw_main1.win_key;
/*
    // --- debug --- 
    sprintf(str1,"win_key=%d,",bw_main1.win_key);
    deb_record(str1);
*/
    if ( (key<0) || ((key>=32)&&(key<127)) )
    {
      set_smg_modi(ptr,1);

      if ((key>0)&&(win_chns_char==0))
      {
        c1=key;
        str2[0]=c1;
        str2[1]=0;
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        TextOut(hdc,win_p_x,win_p_y,str2,1);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
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
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
         return(0);
        }
        else
        {
          win_chns_str[1]=key;
          win_chns_str[2]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          if (n2+2>datalen)
          { 
	    /*TextOut(hdc,win_p_x,win_p_y,win_chns_str,1);*/ 
          }
          else
          {
            //TextOut(hdc,win_p_x,win_p_y,win_chns_str,2);
          }
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
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
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          *posi=n2;
          win_p1=0;
          //win_chns_char=0;
          return(RET_KEY);
	}
	if (n2>datalen)
	{
	  if (win_edit_mode[ptr]==1)
	  {

	    win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.get_win_hwnd(p_wptr));
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.get_win_hwnd(p_wptr));

            SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
          get_s_smg_data(str1,SMG_SIZE);
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
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
      }
      else
      {
*/      



  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  get_s_smg_data(str1,SMG_SIZE);

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
          if (calc_len()+1>datalen_real) erase_last_char(1);

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
          if (win_p1+n2+1<=datalen_real)
          {
            if (calc_len()+2>datalen_real) erase_last_char(2);

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
          else
          {
            win_chns_char=0;
	    n2=n2+2;
	    scrn_c=scrn_c+2;
          }
        }
        
	if (win_p1+n2>datalen_real)
	{
	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

    	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          //win_chns_char=0;
          set_smg_modi(ptr,0);
          return(RET_KEY);
	}
	
	if (n2>datalen)
	{
	  if (win_edit_mode[ptr]==1)
	  {
	    win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real)
              {
                str2[i-1+0]=get_smg_data(i-1);
                str2[i-1+1]=0;
              }
	      else
              {
                str2[i-1+0]=' ';
                str2[i-1+1]=0;
              }
	    }
	    //str2[datalen]=0;

            u=bw_inkey1.w_chs_string_cut(str2,datalen);
            str2[u]=0;

            strcat(str2," ");
            str2[datalen]=0;

	    HideCaret(bw_main1.get_win_hwnd(p_wptr));
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	    SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
            //posi=n2;
            set_smg_posi(ptr,n2);
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }

          for (k=0;k<3;k++)
          {
	    get_s_smg_data(str1,SMG_SIZE);
	    p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	    p3=p2-win_p1;
	    win_p1=p2;
	    win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));

	    for (i=win_p1+1;i<=win_p1+datalen;i++)
	    {
	      if (i<=datalen_real)
              {
                str2[i-win_p1-1+0]=get_smg_data(i-1);
                str2[i-win_p1-1+1]=0;
              }
	      else
              {
                str2[i-win_p1-1+0]=' ';
                str2[i-win_p1-1+1]=0;
              }
	    }
	    //str2[datalen]=0;

            u=bw_inkey1.w_chs_string_cut(str2,datalen);
            str2[u]=0;

            strcat(str2," ");
            str2[datalen]=0;

	    HideCaret(bw_main1.get_win_hwnd(p_wptr));
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	    n2=n2-p3;
	    scrn_c=scrn_c-p3;
	    win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	    HideCaret(bw_main1.get_win_hwnd(p_wptr));
            SetCaretPos(win_p_x,win_p_y);
	    ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	    if (n2>datalen) continue;
            else break;
          }

	}
	else
	{
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-n2+1));

	  for (i=1;i<=datalen;i++)
	  {
	    if (i+win_p1>datalen_real)
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=get_smg_data(win_p1+i-1);
              str2[i-1+1]=0;
	    }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
/*
      }
*/
      win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      SetCaretPos(win_p_x,win_p_y);
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (key==LEFT_ROW)
    {



  // get prev char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  get_s_smg_data(str1,SMG_SIZE);

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
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      }
      else
      {
	if (win_edit_mode[ptr]==1)
	{

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          return(key);
	}
	
	if (win_p1>0)
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;

	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-win_p1-1+0]=get_smg_data(i-1);
              str2[i-win_p1-1+1]=0;
            }
	    else
            {
              str2[i-win_p1-1+0]=' ';
              str2[i-win_p1-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);
	}
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (key==RIGHT_ROW)
    {
/*


  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  get_s_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++) pos[k]=(-1);

  k=0;
  j=0;
  pos[0]=0;

  while(*//*(k<l1)&&*//*(k<strlen(str1)))
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
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
        }
        else
        {
	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);
        }
      }
      else
      {
	if (win_edit_mode[ptr]==1)
	{
	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          return(key);
	}
	
	if (n2+win_p1<datalen_real)
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;

	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-win_p1-1+0]=get_smg_data(i-1);
              str2[i-win_p1-1+1]=0;
            }
	    else
            {
              str2[i-win_p1-1+0]=' ';
              str2[i-win_p1-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
	  TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
	  SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{*/
	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);/*
	}
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);*/
    }
    
    if (key==UP_ROW)
    {
      set_smg_modi(ptr,0);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real)
        {
          str2[i-1+0]=get_smg_data(i-1);
          str2[i-1+1]=0;
        }
        else
        {
          str2[i-1+0]=' ';
          str2[i-1+1]=0;
        }
      }
      //str2[datalen]=0;

      u=bw_inkey1.w_chs_string_cut(str2,datalen);
      str2[u]=0;

      strcat(str2," ");
      str2[datalen]=0;

      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      win_p1=0;
      return(key);
    }
    
    if (key==DOWN_ROW)
    {
      set_smg_modi(ptr,0);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real)
        {
          str2[i-1+0]=get_smg_data(i-1);
          str2[i-1+1]=0;
        }
        else
        {
          str2[i-1+0]=' ';
          str2[i-1+1]=0;
        }
      }
      //str2[datalen]=0;

      u=bw_inkey1.w_chs_string_cut(str2,datalen);
      str2[u]=0;

      strcat(str2," ");
      str2[datalen]=0;

      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      win_p1=0;
      return(key);
    }
    
    if (key==BACKSP)
    {
      set_smg_modi(ptr,1);



  // get prev char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  get_s_smg_data(str1,SMG_SIZE);

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

	win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));

        for (i=1/*n2*/;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real)
          {
            str2[i-1/*n2*/+0]=' ';
            str2[i-1/*n2*/+1]=0;
          }
	  else
          {
            str2[i-1/*n2*/+0]=get_smg_data(win_p1+i-1);
            str2[i-1/*n2*/+1]=0;
          }
	}
	//str2[datalen-n2+1]=0;

        u=bw_inkey1.w_chs_string_cut(str2,datalen);
        str2[u]=0;

        strcat(str2," ");
        str2[datalen]=0;

	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      }
      else
      {
	if (win_p1>0)
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));

	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real)
            {
              str2[i-win_p1-1+0]=get_smg_data(i-1);
              str2[i-win_p1-1+1]=0;
            }
	    else
            {
              str2[i-win_p1-1+0]=' ';
              str2[i-win_p1-1+1]=0;
            }
	  }
	  //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

          for (i=1;i<=datalen;i++)
          {
	    if (i<=datalen_real)
            {
              str2[i-1+0]=get_smg_data(i-1);
              str2[i-1+1]=0;
            }
            else
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
          }
          //str2[datalen]=0;

          u=bw_inkey1.w_chs_string_cut(str2,datalen);
          str2[u]=0;

          strcat(str2," ");
          str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);
	}
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (key==RET_KEY)
    {
      set_smg_modi(ptr,0);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real)
        {
          str2[i-1+0]=get_smg_data(i-1);
          str2[i-1+1]=0;
        }
        else
        {
          str2[i-1+0]=' ';
          str2[i-1+1]=0;
        }
      }
      //str2[datalen]=0;

      u=bw_inkey1.w_chs_string_cut(str2,datalen);
      str2[u]=0;

      strcat(str2," ");
      str2[datalen]=0;

      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
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
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      *posi=n2;
      return(0);
    }
*/
    if (key==DEL_KEY)
    {
      set_smg_modi(ptr,1);



  // get char , if chiness w=2 if ascii w=1 ,w2=1(half chiness)
  get_s_smg_data(str1,SMG_SIZE);

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

	for (i=1;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real)
          {
            str2[i-1+0]=' ';
            str2[i-1+1]=0;
          }
	  else
          {
            str2[i-1+0]=get_smg_data(win_p1+i-1);
            str2[i-1+1]=0;
          }
	}
	//str2[datalen]=0;

        u=bw_inkey1.w_chs_string_cut(str2,datalen);
        str2[u]=0;

        strcat(str2," ");
        str2[datalen]=0;

	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-n2+1));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      }
      else
      {
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	TextOut(hdc,win_p_x,win_p_y," ",1);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	set_smg_data(win_p1+n2-1,' ');
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (  ((key>=0)&&(key<32))  ||(key==PG_UP)||(key==PG_DOWN)||  ((key>200)&&(key<=410))  )
    {
      set_smg_modi(ptr,0);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);

      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real)
        {
          str2[i-1+0]=get_smg_data(i-1);
          str2[i-1+1]=0;
        }
        else
        {
          str2[i-1+0]=' ';
          str2[i-1+1]=0;
        }
      }
      //str2[datalen]=0;

      u=bw_inkey1.w_chs_string_cut(str2,datalen);
      str2[u]=0;

      strcat(str2," ");
      str2[datalen]=0;

      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      win_p1=0;
      return(key);
    }
    
    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
    //posi=n2;
    set_smg_posi(ptr,n2);
    return(0);
  }
  
  return(0);
}

int bw_getread::get_num(int p_wptr,int scrn_l,int scrn_c,char *atten,
		    int datalen,int datalen_real,char link,
		    int ptr,int color,int dec,int posi)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  char c1;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  int  n1,n2;
  int  i;
  int  key;
  int  p2,p3;

/* --- display attention and data --- */
  //win_get_ptr=ptr;
  //win_get_link=link;
  //win_color=color;

  n1=strlen(atten);

/* --- input command --- */
  if ( posi > datalen ) posi= datalen;
  if ( posi<1)       posi=1;
  n2= posi;

  win_cur1=scrn_c+n1;

  scrn_c=scrn_c+n1+n2-1;

  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
  win_p_y=(int)(bw_main1.win_edit_ychar*(scrn_l));

  HideCaret(bw_main1.get_win_hwnd(p_wptr));
  SetCaretPos(win_p_x,win_p_y);
  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

/* --- pre insert when smg_chns_next==1 --- */
  if (bw_main1.win_key!=0)
  {
    hdc=GetDC(bw_main1.get_win_hwnd(p_wptr));
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);

    key=bw_main1.win_key;

    if (  (key=='+')||(key=='-')||(key=='.')||(key==' ')||  ((key>='0')&&(key<='9'))  )    //(((key>=32)&&(key<=126))/*||(key<0)*/)
    {
      set_smg_modi(ptr,1);
/*
      if ((key>=0)&&(win_chns_char==0))
      {
*/
        c1=key;
        str2[0]=c1;
        str2[1]=0;
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        TextOut(hdc,win_p_x,win_p_y,str2,1);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
/*
      }
      else
      {

        if (win_chns_char==0)
        {
          win_chns_char=1;
          win_chns_str[0]=key;
          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
         return(0);
        }
        else
        {
          win_chns_str[1]=key;
          win_chns_str[2]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          if (n2+2>datalen)
            TextOut(hdc,win_p_x,win_p_y,win_chns_str,1);
          else
            TextOut(hdc,win_p_x,win_p_y,win_chns_str,2);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
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
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

          SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          *posi=n2;
          win_p1=0;
          //win_chns_char=0;
          return(RET_KEY);
	}
	if (n2>datalen)
	{
	  if (win_edit_mode[ptr]==1)
	  {
	    get_num_conv(datalen_real,dec);

	    win_p_x=(int)((win_cur1-1)*bw_main1.win_edit_xchar);
    	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.get_win_hwnd(p_wptr));
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.get_win_hwnd(p_wptr));

            SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
            *posi=n2;
            win_p1=0;
            //win_chns_char=0;
            return(key);
	  }
	  get_s_smg_data(str1,SMG_SIZE);
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
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-1));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
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

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
    	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          //win_chns_char=0;
          set_smg_modi(ptr,0);
          return(RET_KEY);
	}
	
	if (n2>datalen)
	{
	  if (win_edit_mode[ptr]==1)
	  {
	    get_num_conv(datalen_real,dec);

	    win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      	    for (i=1;i<=datalen;i++)
	    {
	      if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	      else str2[i-1]=' ';
	    }
	    str2[datalen]=0;
	    HideCaret(bw_main1.get_win_hwnd(p_wptr));
            TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	    ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	    SelectObject(hdc,holdfont);
	    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
            //posi=n2;
            set_smg_posi(ptr,n2);
            win_p1=0;
            //win_chns_char=0;
            set_smg_modi(ptr,0);
            return(key);
	  }
	  
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{
	  //win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  //for (i=n2;i<=datalen;i++)
	  //{
	  //  if (i+win_p1>datalen_real) str2[i-n2]=' ';
	  //  else str2[i-n2]=get_smg_data(win_p1+i-1);
	  //}
	  //str2[datalen-n2+1]=0;
	  //HideCaret(bw_main1.get_win_hwnd(p_wptr));
          //TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  //ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c-n2+1));

	  for (i=1;i<=datalen;i++)
	  {
	    if (i+win_p1>datalen_real)
            {
              str2[i-1+0]=' ';
              str2[i-1+1]=0;
            }
	    else
            {
              str2[i-1+0]=get_smg_data(win_p1+i-1);
              str2[i-1+1]=0;
	    }
	  }
	  //str2[datalen]=0;

	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  
	}
/*
      }
*/
      win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      SetCaretPos(win_p_x,win_p_y);
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (key==LEFT_ROW)
    {
      if (n2>1)
      {
        n2--;
	scrn_c--;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      }
      else
      {
	if (win_edit_mode[ptr]==1)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          return(key);
	}
	
	if (win_p1>0)
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);
	}
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (key==RIGHT_ROW)
    {/*
      if (n2<datalen)
      {
        if (n2+win_p1<datalen_real)
        {
          n2++;
	  scrn_c++;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
        }
        else
        {
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          return(key);
        }
      }
      else
      {
	if (win_edit_mode[ptr]==1)
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          return(key);
	}
	
	if (n2+win_p1<datalen_real)
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,datalen_real,datalen,win_p1);
	  p3=p2-win_p1;
	  win_p1=p2;
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  str2[datalen]=0;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
	  TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
	  SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{*/
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      	  for (i=1;i<=datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
	    else str2[i-1]=' ';
	  }
	  str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);/*
	}
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);*/
    }
    
    if (key==UP_ROW)
    {
      set_smg_modi(ptr,0);

      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      win_p1=0;
      return(key);
    }
    
    if (key==DOWN_ROW)
    {
      set_smg_modi(ptr,0);

      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      win_p1=0;
      return(key);
    }
    
    if (key==BACKSP)
    {
      set_smg_modi(ptr,1);

      if (n2>1)
      {
	for (i=n2+win_p1;i<=datalen_real;i++)
	{
	  set_smg_data(i-1-1,get_smg_data(i-1));
	}
	set_smg_data(datalen_real-1,' ');
	n2--;
	scrn_c--;
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
        for (i=n2;i<=datalen;i++)
	{
	  if (i+win_p1>datalen_real) str2[i-n2]=' ';
	  else str2[i-n2]=get_smg_data(win_p1+i-1);
	}
	str2[datalen-n2+1]=0;
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      }
      else
      {
	if (win_p1>0)
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,datalen,win_p1);
	  p3=win_p1-p2;
	  win_p1=p2;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(win_cur1));
	  for (i=win_p1+1;i<=win_p1+datalen;i++)
	  {
	    if (i<=datalen_real) str2[i-win_p1-1]=get_smg_data(i-1);
	    else str2[i-win_p1-1]=' ';
	  }
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          SetCaretPos(win_p_x,win_p_y);
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	}
	else
	{
	  get_num_conv(datalen_real,dec);

	  win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
          for (i=1;i<=datalen;i++)
          {
	    if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
            else str2[i-1]=' ';
          }
          str2[datalen]=0;
	  HideCaret(bw_main1.get_win_hwnd(p_wptr));
          TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	  ShowCaret(bw_main1.get_win_hwnd(p_wptr));

	  SelectObject(hdc,holdfont);
	  ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
          //posi=n2;
          set_smg_posi(ptr,n2);
          win_p1=0;
          set_smg_modi(ptr,0);
          return(key);
	}
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (key==RET_KEY)
    {
      set_smg_modi(ptr,0);

      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
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
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      *posi=n2;
      return(0);
    }
*/
    if (key==DEL_KEY)
    {
      set_smg_modi(ptr,1);

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
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
      }
      else
      {
	win_p_x=(int)(bw_main1.win_edit_xchar*(scrn_c));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
	TextOut(hdc,win_p_x,win_p_y," ",1);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	HideCaret(bw_main1.get_win_hwnd(p_wptr));
        SetCaretPos(win_p_x,win_p_y);
	ShowCaret(bw_main1.get_win_hwnd(p_wptr));
	set_smg_data(win_p1+n2-1,' ');
      }
      
      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      return(0);
    }
    
    if (  ((key>=0)&&(key<32))  ||(key==PG_UP)||(key==PG_DOWN)||  ((key>200)&&(key<=410))  )
    {
      set_smg_modi(ptr,0);

      get_num_conv(datalen_real,dec);

      win_p_x=(int)((win_cur1)*bw_main1.win_edit_xchar);
      for (i=1;i<=datalen;i++)
      {
	if (i<=datalen_real) str2[i-1]=get_smg_data(i-1);
        else str2[i-1]=' ';
      }
      str2[datalen]=0;
      HideCaret(bw_main1.get_win_hwnd(p_wptr));
      TextOut(hdc,win_p_x,win_p_y,str2,strlen(str2));
      ShowCaret(bw_main1.get_win_hwnd(p_wptr));

      SelectObject(hdc,holdfont);
      ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
      //posi=n2;
      set_smg_posi(ptr,n2);
      win_p1=0;
      return(key);
    }
    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.get_win_hwnd(p_wptr),hdc);
    //posi=n2;
    set_smg_posi(ptr,n2);
    return(0);
  }
  return(0);
}

int bw_getread::get_num_conv(int datalen_real,int dec)
{
  char s3[SMG_SIZE];
  int  s_state1;
  int  i,j;

/* convert to number */
  for (i=0;i<=60;i++)  s3[i]=' ';
  s3[61]=0;

  s_state1=0;
  if (datalen_real!=0)  // erase number where after number+' '(number and space)
  {
    //for (i=datalen_real-1;i<=datalen_real-1;i++) get_smg_data[i]=' ';

    for (i=0;i<datalen_real;i++)
    {
      if (get_smg_data(i)>='0') s_state1=1;
      if ((get_smg_data(i)==' ')&&(s_state1==1)) break;
    }
    for (i=i+1;i<datalen_real;i++) set_smg_data(i,' ');
  }
  
  for (i=0;i<datalen_real;i++) if (get_smg_data(i)=='.') break;  // calcu '.' position
  if (i>=datalen_real)
  {
    for (i=datalen_real-1;i>=0;i--) if (get_smg_data(i)>' ') break;
    i++;
  }
  
  for (j=0;j<i;j++) s3[30-i+j]=get_smg_data(j);  // copy number where before '.'
  
  s3[30]='.';
  
  for (j=i+1;j<datalen_real;j++) s3[30+j-i]=get_smg_data(j);  // copy number where after '.'
  
  for (j=0;j<datalen_real;j++)  // copy number
    if (dec==0)
      set_smg_data(j,s3[30-datalen_real+j]);
    else
      set_smg_data(j,s3[30-(datalen_real-dec-1)+j]);

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

int bw_getread::calc_len(void)
{
  int  pos[SMG_SIZE];
  int  pos2[SMG_SIZE];
  char str1[SMG_SIZE];
  int  i,j,k,l;

  get_s_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++)
  {
    pos[k]=(-1);
    pos2[k]=(-1);
  }

  i=0;
  j=0;
  k=0;
  pos[0]=0;
  pos2[0]=0;

  while(/*(k<l1)&&*/(k<strlen(str1)))
  {
    pos[j] =k;

    if (str1[k]<0)
    {
      k=k+2;
      i=2;
    }
    else
    {
      k=k+1;
      i=1;
    }

    pos2[j]=i;
    j++;
  }

  if (j>0)
  {
    j--;

    while(j>0)
    {
      if ((pos2[j]==1)&&(get_smg_data(pos[j])>=0)&&(get_smg_data(pos[j])<=' ')) j--;
      else break;
    }

    return(pos[j]+pos2[j]);
  }

  return(0);
}

int bw_getread::erase_last_char(int p1)
{
  int  pos[SMG_SIZE];
  int  pos2[SMG_SIZE];
  char str1[SMG_SIZE];
  int  i,j,k,l;

  get_s_smg_data(str1,SMG_SIZE);

  for (k=0;k<300;k++)
  {
    pos[k]=(-1);
    pos2[k]=(-1);
  }

  i=0;
  j=0;
  k=0;
  pos[0]=0;
  pos2[0]=0;

  while(/*(k<l1)&&*/(k<strlen(str1)))
  {
    pos[j] =k;

    if (str1[k]<0)
    {
      k=k+2;
      i=2;
    }
    else
    {
      k=k+1;
      i=1;
    }

    pos2[j]=i;
    j++;
  }

  if (j>0)
  {
    j--;

    if (p1==1)
    {
      if (pos2[j]==1) 
      {
        set_smg_data(pos[j],' ');
      }
      else
      {
        set_smg_data(pos[j]+0,' ');
        set_smg_data(pos[j]+1,' ');
      }
    }
    else // p1==2
    {
      if (pos2[j]==2)
      {
        set_smg_data(pos[j]+0,' ');
        set_smg_data(pos[j]+1,' ');
      }
      else // pos2[j]==1
      {
        if (pos2[j-1]==1)
        {
          set_smg_data(pos[j-0],' ');
          set_smg_data(pos[j-1],' ');
        }
        else // pos2[j-1]==2
        {
          set_smg_data(pos[j-1]+0,' ');
          set_smg_data(pos[j-1]+1,' ');

          set_smg_data(pos[j],' ');
        }
      }
    }
  }

  return(0);
}

int bw_getread::deb_record_init(void)
{
  deb_record_fp=fopen("deb_record.txt","w");
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




int bw_getread::get_smg_line(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_line[gptr]);
}
int bw_getread::get_smg_colu(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_colu[gptr]);
}
int bw_getread::get_smg_data(int ptr1)
{
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  return(smg_data[ptr1]);
}
int bw_getread::get_s_smg_data(char *p_s1,int p_s1_size)
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
int bw_getread::get_smg_string(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((gptr<0)||(gptr>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=smg_string[gptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_getread::get_c_smg_string(int gptr,int ptr1)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  return(smg_string[gptr][ptr1]);
}
int bw_getread::get_smg_type(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_type[gptr]);
}
int bw_getread::get_smg_dlen(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_dlen[gptr]);
}
int bw_getread::get_smg_dlen_real(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_dlen_real[gptr]);
}
int bw_getread::get_smg_ddec(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_ddec[gptr]);
}
int bw_getread::get_smg_link(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_link[gptr]);
}
int bw_getread::get_smg_color(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_color[gptr]);
}
int bw_getread::get_smg_posi(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_posi[gptr]);
}
int bw_getread::get_smg_atte(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((gptr<0)||(gptr>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=smg_atte[gptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_getread::get_smg_read_id(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_read_id[gptr]);
}

int bw_getread::set_smg_line(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_line[gptr]=val;
  return(0);
}
int bw_getread::set_smg_colu(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_colu[gptr]=val;
  return(0);
}
int bw_getread::set_smg_data(int ptr1,int val)
{
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  smg_data[ptr1]=val;
  return(0);
}
int bw_getread::set_smg_type(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_type[gptr]=val;
  return(0);
}
int bw_getread::set_smg_dlen(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_dlen[gptr]=val;
  return(0);
}
int bw_getread::set_smg_dlen_real(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_dlen_real[gptr]=val;
  return(0);
}
int bw_getread::set_smg_ddec(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_ddec[gptr]=val;
  return(0);
}
int bw_getread::set_smg_link(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_link[gptr]=val;
  return(0);
}
int bw_getread::set_smg_color(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_color[gptr]=val;
  return(0);
}
int bw_getread::set_smg_posi(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_posi[gptr]=val;
  return(0);
}
int bw_getread::set_smg_read_id(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_read_id[gptr]=val;
  return(0);
}
int bw_getread::set_smg_string(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((gptr<0)||(gptr>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  smg_string[gptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    smg_string[gptr][j+0]=p_s1[j];
    smg_string[gptr][j+1]=0;
  }

  return(0);
}
int bw_getread::set_c_smg_string(int gptr,int ptr1,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  smg_string[gptr][ptr1]=val;
  return(0);
}
int bw_getread::set_smg_atte(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((gptr<0)||(gptr>=GET_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  smg_atte[gptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    smg_atte[gptr][j+0]=p_s1[j];
    smg_atte[gptr][j+1]=0;
  }

  return(0);
}

int bw_getread::set_smg_modi(int gptr,int val)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  smg_modi[gptr]=val;
  return(0);
}

int bw_getread::get_smg_modi(int gptr)
{
  if ((gptr<0)||(gptr>=GET_NUM)) return(0);
  return(smg_modi[gptr]);
}

