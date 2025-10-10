 
#define  STRICT
#include <windows.h>
#include <commdlg.h>

#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <conio.h>
#include <process.h>
#include <string.h>

#include "vc_bowo.h"

extern class bw_main     bw_main1;
extern class bw_getread  bw_getread1;
extern class bw_inkey    bw_inkey1;

int bw_getread::get_read_ini()
{
  int i;

  for (i=0;i<SMG_GET_NUM;i++) set_smg_read_id(i,0);
  smg_insert=1;

  return(0);
}
/*
int bw_getread::get_read_login()
{
  int i;
  int exist;

  exist=0;

  for (i=0;i<SMG_GET_NUM;i++)
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
  if ((ptr<0)||(ptr>=SMG_GET_NUM)) return(1);

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
  char  str1[SMG_SIZE];
  char  str2[SMG_SIZE];
  char  str3[SMG_SIZE];
  char  str4[SMG_SIZE];
  char  str5[SMG_SIZE];
  int   pos[300];

  if (command=='g')
  {
    if (array_ptr<0)        return(1);
    if (array_ptr>=SMG_GET_NUM) return(1);

    
    //sprintf(str4, "mn_hnd_id=%d,wp=%d,", mn_hnd_id, wp);
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

    mn_p_y=(int)(bw_main1.mn_edit_ychar*(scrn_l));
    mn_p_x=(int)(bw_main1.mn_edit_xchar*(scrn_c));

    i=strlen(atten);

    hdc=GetDC(bw_main1.get_mn_hwnd(p_wptr));
    hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
    holdfont=(HFONT)SelectObject(hdc,hfont);
    TextOut(hdc,mn_p_x,mn_p_y,atten,i);

    mn_p_x=mn_p_x+(int)(i*bw_main1.mn_edit_xchar);

    get_smg_string(smg_ptr,str1,SMG_SIZE);
    i=strlen(str1);
    if (i>datalen) i=datalen;

    u=bw_inkey1.w_chs_string_cut(str1,i);
    str1[u]=0;

    strcat(str1," ");
    str1[i]=0;

    HideCaret(bw_main1.get_mn_hwnd(p_wptr));
    TextOut(hdc,mn_p_x,mn_p_y,str1,strlen(str1));
    ShowCaret(bw_main1.get_mn_hwnd(p_wptr));

    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.get_mn_hwnd(p_wptr),hdc);

    if (posi>=datalen) posi=datalen-1;
    if (posi<0)        posi=0;



    // get char , avoid half chiness
    get_smg_string(smg_ptr,str1,SMG_SIZE);

    for (k=0;k<300;k++) pos[k]=(-1);

    k=0;
    j=0;
    pos[0]=0;

    while(k<strlen(str1))
    {
      if (str1[k]<0) k=k+2;
      else k=k+1;

      j++;

      pos[j]=k;
    }

    w=0;

    for (k=0;k<300;k++)
    {
      if (pos[k]<0) break;

      if (pos[k]<= posi)
      {
        w=pos[k];
      }

    }

    posi=w;



    HideCaret(bw_main1.get_mn_hwnd(p_wptr));
    SetCaretPos(mn_p_x+(int)((posi)*bw_main1.mn_edit_xchar)
                 ,mn_p_y);
    ShowCaret(bw_main1.get_mn_hwnd(p_wptr));
  }
  else if (command=='r')
  {
    if (array_ptr<0)        return(1);
    if (array_ptr>=SMG_GET_NUM) return(1);


    //sprintf(str4, "into getread()... wptr=%d,",p_wptr);
    //bw_getread1.deb_record(str4);


    smg_ptr2=array_ptr;

    get_smg_string(smg_ptr2,str1,SMG_SIZE);

    set_smg_data(0,0);

    //sprintf(str4, "in getread()... ,string=%s,dlen_real=%d,",str1,get_smg_dlen_real(smg_ptr2));
    //bw_getread1.deb_record(str4);

    for (i=0;i<get_smg_dlen_real(smg_ptr2);i++)
    {
      if (i<(int)strlen(str1))
      {
        set_smg_data(i+0,str1[i]);
        set_smg_data(i+1,0);
      }
      else
      {
        set_smg_data(i+0,' ');
        set_smg_data(i+1,0);
      }
    }

    //get_s_smg_data(str5,SMG_SIZE);
    //sprintf(str4, "in getread()... ,data=%s,dlen_real=%d,",str5,get_smg_dlen_real(smg_ptr2));
    //bw_getread1.deb_record(str4);

    if (get_smg_type(smg_ptr2)=='c')
    {
      get_smg_atte(smg_ptr2,str2,SMG_SIZE);

      key=get_text(
p_wptr,
get_smg_line(smg_ptr2),get_smg_colu(smg_ptr2),str2,
get_smg_dlen(smg_ptr2),get_smg_dlen_real(smg_ptr2),get_smg_link(smg_ptr2),
smg_ptr2,get_smg_color(smg_ptr2),get_smg_posi(smg_ptr2));
    }
    else
    {
      get_smg_atte(smg_ptr2,str2,SMG_SIZE);

      //sprintf(str4, "into get_num...");
      //bw_getread1.deb_record(str4);

      key=get_num(
p_wptr,
get_smg_line(smg_ptr2),get_smg_colu(smg_ptr2),str2,
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
      if (    (key==127)
            ||(key==SMG_KEY_ESC)
            ||(key==CTRL_W)
	    ||(key>200)
	    ||(key==SMG_KEY_RET)
	    ||((key>0)&&(key<32))  )

      {
	bw_main1.mn_key=key;
	return(1);
      }
      else  if (  (((key>=32)&&(key<127))||(key<0))  &&
                  (mn_confirm==0)  )  
      {
	bw_main1.mn_key=10;
        return(1);
      }
    }
  }

  return(0);
}

int bw_getread::get_text(int p_wptr,int scrn_l,int scrn_c,char *atten,
		    int datalen,int datalen_real,char link,
		    int ptr,int color,int posi)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  char  c1;
  char  str1[SMG_SIZE];
  char  str2[SMG_SIZE];
  int   n1,n2;
  int   i,u;
  int   key;
  int   p2,p3;
  int   w,w2;

  int   j,k;
  int   pos[300];
  int   disp;

/* --- display attention and data --- */
  //mn_get_ptr=ptr;
  //mn_get_link=link;
  //mn_color=color;

  disp=0;

  n1=strlen(atten);

/* --- input command --- */
  if ( posi >= datalen ) posi= datalen-1;
  if ( posi < 0)         posi=0;
  n2= posi;

  mn_cur1=scrn_c+n1;

  scrn_c =scrn_c+n1+n2;

  mn_p_x=(int)(bw_main1.mn_edit_xchar*(scrn_c));
  mn_p_y=(int)(bw_main1.mn_edit_ychar*(scrn_l));

  HideCaret(bw_main1.get_mn_hwnd(p_wptr));
  SetCaretPos(mn_p_x,mn_p_y);
  ShowCaret(bw_main1.get_mn_hwnd(p_wptr));

  hdc=GetDC(bw_main1.get_mn_hwnd(p_wptr));
  hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  holdfont=(HFONT)SelectObject(hdc,hfont);

/* --- pre insert when smg_chns_next==1 --- */
  while (bw_main1.mn_key!=0)
  {
    if (bw_main1.mn_key==410) break;
    if (bw_main1.mn_key==427) break;
    if (bw_main1.mn_key==639) break;

    key=bw_main1.mn_key;
/*
    // --- debug --- 
    sprintf(str1,"mn_key=%d,",bw_main1.mn_key);
    deb_record(str1);
*/
    if ( (key<0) || ((key>=32)&&(key<127)) )
    {
        set_smg_modi(ptr,1);

        if ((key>0)&&(mn_chns_char==0))  //save key to str2
        {
          c1=key;
          //str2[0]=c1;
          //str2[1]=0;
/*
          // --- debug ---
          deb_record(str2);
*/
        }
        else
        {
          if (mn_chns_char==0)
          {
            mn_chns_char=1;
            mn_chns_str[0]=key;
            mn_chns_str[1]=0;

            disp=1;

            break;
          }
          else
          {
            mn_chns_str[1]=key;
            mn_chns_str[2]=0;
/*
            // --- debug ---
            deb_record(mn_chns_str);
*/
          }
        }
      


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
          if (pos[k]==(mn_p1+n2))
          {
            w2=0;
            break;
          }

          if (pos[k]> (mn_p1+n2))
          {
            w2=1;
            break;
          }

          if (pos[k]<0) break;
        }



        n2=n2+w2;
	scrn_c=scrn_c+w2;

        // insert
        if (mn_chns_char==0)   // save str2 to smg_data
        {
          if (calc_len()+1>datalen_real) erase_last_char(1);

	  for (i=datalen_real-1;i>n2+mn_p1;i--)
	  {
	    set_smg_data(i,get_smg_data(i-1));
	  }
	  set_smg_data(mn_p1+n2,c1);
	  n2++;
	  scrn_c++;
        }
        else
        {
          if (mn_p1+n2+1<=datalen_real)
          {
            if (calc_len()+2>datalen_real) erase_last_char(2);

            mn_chns_char=0;
            
	    for (i=datalen_real-1;i>=n2+mn_p1;i--)
	    {
	      set_smg_data(i+2,get_smg_data(i));
	    }
	    
	    set_smg_data(mn_p1+n2+0,mn_chns_str[0]);
	    set_smg_data(mn_p1+n2+1,mn_chns_str[1]);
	    n2=n2+2;
	    scrn_c=scrn_c+2;
          }
          else
          {
            mn_chns_char=0;
	    n2=n2+2;
	    scrn_c=scrn_c+2;
          }
        }
        
	if (mn_p1+n2+1>datalen_real)  //display string
	{
          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          //mn_chns_char=0;
          set_smg_modi(ptr,0);

          key=SMG_KEY_RET;
          disp=1;

          break;
	}
	else if (n2+1>datalen)
	{
          for (k=0;k<3;k++)   //left scroll
          {
	    get_s_smg_data(str1,SMG_SIZE);
	    p2=get_txt_after(str1,mn_p1);
	    p3=p2-mn_p1;
	    mn_p1=p2;
	    
	    n2=n2-p3;
	    scrn_c=scrn_c-p3;

	    if (n2+1>datalen) continue;
            else break;
          }

	}
	else
	{
	}

        //posi=n2;
        set_smg_posi(ptr,n2);

        disp=1;
	key=0;

        break;
    }
    
    if (key==SMG_KEY_LEFT)
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
        if (pos[k]==(mn_p1+n2))
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

        if (pos[k]>(mn_p1+n2))
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
              j=(mn_p1+n2);

              w=0;
              w2=0;
            }
          }

          break;
        }

        if (pos[k]<0) break;
      }



      if (n2+1>w+w2)
      {
        n2=n2-w-w2;
	scrn_c=scrn_c-w-w2;
	key=0;
      }
      else
      {
	if (mn_p1>0)  //right scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,mn_p1);
	  p3=mn_p1-p2;
	  mn_p1=p2;

	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  key=0;
	}
	else  //at begin of string,normal display string and return with key 
	{
          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
	}
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;

      break;
    }
    
    if (key==SMG_KEY_RIGHT)
    {



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
        if (pos[k]==(mn_p1+n2))
        {
          j=pos[k];

          if (str1[j]<0) w=2;
          else w=1;
          w2=0;

          break;
        }

        if (pos[k]>(mn_p1+n2))
        {
          w=0;
          w2=1;

          break;
        }

        if (pos[k]<0) break;
      }



      if (n2+w+w2+1<datalen)
      {
	if (n2+mn_p1+1<datalen_real)
	{
          n2=n2+w+w2;
	  scrn_c=scrn_c+w+w2;
	  key=0;
        }
        else  // at end of string , display string and return with key
        {
          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
        }
      }
      else
      {
	if (n2+mn_p1+1<datalen_real)  //left scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,mn_p1);
	  p3=p2-mn_p1;
	  mn_p1=p2;
	  
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  key=0;
	}
	else  // at end of string , display string and return with key
	{
          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
	}
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;

      break;
    }
    
    if (key==SMG_KEY_UP)
    {
      set_smg_modi(ptr,0);
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;

      disp=1;

      break;
    }
    
    if (key==SMG_KEY_DOWN)
    {
      set_smg_modi(ptr,0);

      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;

      disp=1;

      break;
    }
    
    if (key==SMG_KEY_BACKSP)
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
        if (pos[k]==(mn_p1+n2))
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

        if (pos[k]>(mn_p1+n2))
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
              j=(mn_p1+n2);

              w=0;
              w2=0;
            }
          }

          break;
        }

        if (pos[k]<0) break;
      }



      if (n2+1>w+w2)
      {
        n2=n2-w2;
        scrn_c=scrn_c-w2;

        if (w==1)
        {
  	  for (i=n2+mn_p1+0;i<datalen_real;i++)
	  {
	    set_smg_data(i-1,get_smg_data(i));
	  }
	  set_smg_data(datalen_real-1,' ');
	  n2--;
	  scrn_c--;
	  key=0;
        }
        else 
        {
          if (w==2)
          {
    	    for (i=n2+mn_p1+0;i<datalen_real;i++)
	    {
	      set_smg_data(i-2,get_smg_data(i));
	    }
	    set_smg_data(datalen_real-2,' ');
	    set_smg_data(datalen_real-1,' ');
	    n2=n2-w;
	    scrn_c=scrn_c-w;
	    key=0;
          }
        }
      }
      else
      {
	if (mn_p1>0)  // right scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,mn_p1);
	  p3=mn_p1-p2;
	  mn_p1=p2;
	  
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  key=0;
	}
	else  //at begin of string ,display string and return with key
	{
          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
	}
      }

      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    if (key==SMG_KEY_RET)
    {
      set_smg_modi(ptr,0);
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;

      disp=1;

      break;
    }

    if (key==SMG_KEY_DEL)
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
        if (pos[k]==(mn_p1+n2))
        {
          j=pos[k];

          if (str1[j]<0) w=2;
          else w=1;
          w2=0;

          break;
        }

        if (pos[k]>(mn_p1+n2))
        {
          w=0;
          w2=1;

          break;
        }

        if (pos[k]<0) break;
      }



      if (mn_p1+n2+1<datalen_real)
      {
        n2=n2-w2;
        scrn_c=scrn_c-w2;

        if (w==1)
        {
	  for (i=mn_p1+n2+1;i<datalen_real;i++)
	  {
	    set_smg_data(i-1,get_smg_data(i));
	  }
	  set_smg_data(datalen_real-1,' ');
        }
        else
        {
          if (w==2)
          {
	    for (i=mn_p1+n2+2;i<datalen_real;i++)
	    {
	      set_smg_data(i-2,get_smg_data(i));
	    }
	    set_smg_data(datalen_real-2,' ');
	    set_smg_data(datalen_real-1,' ');
          }
        }

      }
      else
      {
	set_smg_data(mn_p1+n2-1,' ');
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    if (  ((key>=0)&&(key<32))  ||(key==SMG_KEY_PGUP)||(key==SMG_KEY_PGDOWN)||  ((key>200)&&(key<=410))  )
    {
      set_smg_modi(ptr,0);
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;

      disp=1;

      break;
    }
    
    //posi=n2;
    set_smg_posi(ptr,n2);

    disp=1;
    key=0;

    break;
  }

  if (disp==1)
  {
    mn_p_x=(int)(bw_main1.mn_edit_xchar*(mn_cur1));
	  
    str2[0]=0;
            
    for (i=mn_p1+0;i<mn_p1+datalen;i++)
    {
      if (i+1<=datalen_real)
      {
        str2[i-mn_p1+0]=get_smg_data(i);
        str2[i-mn_p1+1]=0;
      }
      else
      {
        str2[i-mn_p1+0]=' ';
        str2[i-mn_p1+1]=0;
      }
    }
    //str2[datalen]=0;

    u=bw_inkey1.w_chs_string_cut(str2,datalen);
    str2[u]=0;

    strcat(str2," ");
    str2[datalen]=0;

    HideCaret(bw_main1.get_mn_hwnd(p_wptr));
    TextOut(hdc,mn_p_x,mn_p_y,str2,strlen(str2));
    ShowCaret(bw_main1.get_mn_hwnd(p_wptr));
	    
    mn_p_x=(int)(bw_main1.mn_edit_xchar*(scrn_c));
	    
    HideCaret(bw_main1.get_mn_hwnd(p_wptr));
    SetCaretPos(mn_p_x,mn_p_y);
    ShowCaret(bw_main1.get_mn_hwnd(p_wptr));
  }

  SelectObject(hdc,holdfont);
  ReleaseDC(bw_main1.get_mn_hwnd(p_wptr),hdc);
  
  return(key);
}

int bw_getread::get_num(int p_wptr,int scrn_l,int scrn_c,char *atten,
		    int datalen,int datalen_real,char link,
		    int ptr,int color,int dec,int posi)
{
  HDC   hdc;
  HFONT hfont,holdfont;
  char  c1;
  char  str1[SMG_SIZE];
  char  str2[SMG_SIZE];
  char  str4[SMG_SIZE];
  char  str5[SMG_SIZE];
  int   n1,n2;
  int   i;
  int   key;
  int   p2,p3;
  int   disp;

  disp=0;

/* --- display attention and data --- */
  //mn_get_ptr=ptr;
  //mn_get_link=link;
  //mn_color=color;

    //get_s_smg_data(str5,SMG_SIZE);
    //sprintf(str4, "in get_num...into get_num,data=%s,",str5);
    //bw_getread1.deb_record(str4);

  n1=strlen(atten);

/* --- input command --- */
  if ( posi >= datalen ) posi= datalen-1;
  if ( posi <  0)        posi= 0;
  n2= posi;

  mn_cur1=scrn_c+n1;

  scrn_c=scrn_c+n1+n2;

  mn_p_x=(int)(bw_main1.mn_edit_xchar*(scrn_c));
  mn_p_y=(int)(bw_main1.mn_edit_ychar*(scrn_l));

  HideCaret(bw_main1.get_mn_hwnd(p_wptr));
  SetCaretPos(mn_p_x,mn_p_y);
  ShowCaret(bw_main1.get_mn_hwnd(p_wptr));

  hdc=GetDC(bw_main1.get_mn_hwnd(p_wptr));
  hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  holdfont=(HFONT)SelectObject(hdc,hfont);

/* --- pre insert when smg_chns_next==1 --- */
  while (bw_main1.mn_key!=0)
  {
    key=bw_main1.mn_key;

    if (  (key=='+')||(key=='-')||(key=='.')||(key==' ')||  ((key>='0')&&(key<='9'))  )    //(((key>=32)&&(key<=126))/*||(key<0)*/)
    {
      set_smg_modi(ptr,1);

        c1=key;                   //save to str2
        //str2[0]=c1;
        //str2[1]=0;
        
	//HideCaret(bw_main1.get_mn_hwnd(p_wptr));
        //TextOut(hdc,mn_p_x,mn_p_y,str2,1);
	//ShowCaret(bw_main1.get_mn_hwnd(p_wptr));

        // insert
        if (mn_chns_char==0)           //save to smg_data
        {
	  for (i=datalen_real-1;i>=n2+mn_p1;i--)
	  {
	    set_smg_data(i+1,get_smg_data(i));
	  }
	  set_smg_data(mn_p1+n2,c1);
	  n2++;
	  scrn_c++;
	  key=0;
        }

	if (mn_p1+n2+1>datalen_real)
	{
	  get_num_conv(datalen_real,dec);

          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          //mn_chns_char=0;
          set_smg_modi(ptr,0);

          disp=1;
          key=SMG_KEY_RET;

          break;
	}
	
	if (n2+1>datalen)  //left scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,mn_p1);
	  p3=p2-mn_p1;
	  mn_p1=p2;
	  
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  key=0;
	}
	else  //normal display string
	{
	}

      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    //get_s_smg_data(str5,SMG_SIZE);
    //sprintf(str4, "in get_num...before left_arrow,data=%s,",str5);
    //bw_getread1.deb_record(str4);

    if (key==SMG_KEY_LEFT)
    {
      if (n2+1>1)
      {
        n2--;
	scrn_c--;
	key=0;
      }
      else
      {
	if (mn_p1>0)  //right scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,mn_p1);
	  p3=mn_p1-p2;
	  mn_p1=p2;
	  
	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  key=0;
	}
	else  // at begin of string ,normal display and return with key
	{
	  get_num_conv(datalen_real,dec);

          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
	}
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    if (key==SMG_KEY_RIGHT)
    {
      if (n2+1<datalen)
      {
        if (n2+mn_p1+1<datalen_real)
        {
          n2++;
	  scrn_c++;
	  key=0;
        }
        else  //at end of string, normal display and return with key
        {
	  get_num_conv(datalen_real,dec);

          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;

          disp=1;

          break;
        }
      }
      else
      {
	if (n2+mn_p1+1<datalen_real)  //left scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_after(str1,mn_p1);
	  p3=p2-mn_p1;
	  mn_p1=p2;
	  
	  n2=n2-p3;
	  scrn_c=scrn_c-p3;
	  key=0;
	}
	else  //at end of string ,normal display string and return with key
	{
	  get_num_conv(datalen_real,dec);

          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
	}
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    //get_s_smg_data(str5,SMG_SIZE);
    //sprintf(str4, "in get_num...before up_arrow,data=%s,",str5);
    //bw_getread1.deb_record(str4);

    if (key==SMG_KEY_UP)
    {

      get_num_conv(datalen_real,dec);

      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;
      set_smg_modi(ptr,0);

      disp=1;

      break;
    }
    
    if (key==SMG_KEY_DOWN)
    {
      get_num_conv(datalen_real,dec);

      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;
      set_smg_modi(ptr,0);

      disp=1;

      break;
    }
    
    if (key==SMG_KEY_BACKSP)
    {
      set_smg_modi(ptr,1);

      if (n2+1>1)
      {
	for (i=n2+mn_p1+0;i<datalen_real;i++)
	{
	  set_smg_data(i-1,get_smg_data(i));
	}
	set_smg_data(datalen_real-1,' ');
	n2--;
	scrn_c--;
	key=0;
      }
      else
      {
	if (mn_p1>0)  //right scroll
	{
	  get_s_smg_data(str1,SMG_SIZE);
	  p2=get_txt_before(str1,mn_p1);
	  p3=mn_p1-p2;
	  mn_p1=p2;

	  n2=n2+p3;
	  scrn_c=scrn_c+p3;
	  key=0;
	}
	else  //at begin of string ,normal display and return with key
	{
	  get_num_conv(datalen_real,dec);

          //posi=n2;
          set_smg_posi(ptr,n2);

          mn_p1=0;
          set_smg_modi(ptr,0);

          disp=1;

          break;
	}
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    if (key==SMG_KEY_RET)
    {
      get_num_conv(datalen_real,dec);

      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;
      set_smg_modi(ptr,0);

      disp=1;

      break;
    }

    if (key==SMG_KEY_DEL)
    {
      set_smg_modi(ptr,1);

      if (mn_p1+n2+1<=datalen_real)
      {
	for (i=mn_p1+n2+1;i<datalen_real;i++)
	{
	  set_smg_data(i-1,get_smg_data(i));
	}
	set_smg_data(datalen_real-1,' ');
      }
      else
      {
	set_smg_data(mn_p1+n2-1,' ');
      }
      
      //posi=n2;
      set_smg_posi(ptr,n2);

      disp=1;
      key=0;

      break;
    }
    
    if (  ((key>=0)&&(key<32))  ||  (key==SMG_KEY_PGUP)  ||  (key==SMG_KEY_PGDOWN)  ||  ((key>200)&&(key<=410))  )
    {
      get_num_conv(datalen_real,dec);

      //posi=n2;
      set_smg_posi(ptr,n2);

      mn_p1=0;
      set_smg_modi(ptr,0);

      disp=1;

      break;
    }
    
    //posi=n2;
    set_smg_posi(ptr,n2);

    disp=1;

    break;
  }
  
  if (disp==1)
  {
    mn_p_x=(int)(bw_main1.mn_edit_xchar*(mn_cur1));
	  
    str2[0]=0;
	  
    for (i=mn_p1+0;i<mn_p1+datalen;i++)
    {
      if (i+1<=datalen_real)
      {
        str2[i-mn_p1+0]=get_smg_data(i);
        str2[i-mn_p1+1]=0;
      }
      else
      {
        str2[i-mn_p1+0]=' ';
        str2[i-mn_p1+1]=0;
      }
    }
    //str2[datalen]=0;
	  
    HideCaret(bw_main1.get_mn_hwnd(p_wptr));
    TextOut(hdc,mn_p_x,mn_p_y,str2,strlen(str2));
    ShowCaret(bw_main1.get_mn_hwnd(p_wptr));
	  
    mn_p_x=(int)(bw_main1.mn_edit_xchar*(scrn_c));
	    
    HideCaret(bw_main1.get_mn_hwnd(p_wptr));
    SetCaretPos(mn_p_x,mn_p_y);
    ShowCaret(bw_main1.get_mn_hwnd(p_wptr));
  }

  SelectObject(hdc,holdfont);
  ReleaseDC(bw_main1.get_mn_hwnd(p_wptr),hdc);

  return(key);
}

int bw_getread::get_num_conv(int datalen_real,int dec)
{
  char str1[SMG_SIZE];
  int  s_state1;
  int  i,j,k;

/* convert to number */
  for (i=0;i<SMG_SIZE;i++)  str1[i]=' ';
  str1[61]=0;

  s_state1=0;
  
  if (datalen_real<=0) return(0);
  
  // erase number which after number+' '(after number and space)
  k=0;
  
  for (i=0;i<datalen_real;i++)
  {
      if (get_smg_data(i)>='0') s_state1=1;
      if ((get_smg_data(i)==' ')&&(s_state1==1))
      {
        k=1;
        break;
      }
  }

  if (k==1)
      for (i=i+1;i<datalen_real;i++) set_smg_data(i,' ');
  
  // search '.' position
  k=0;
  
  for (i=0;i<datalen_real;i++) 
  {
    if (get_smg_data(i)=='.')
    {
      k=1;
      break;
    }
  }

  if (k==0)  // not found '.'
  {
    for (i=datalen_real-1;i>=0;i--) if (get_smg_data(i)>' ') break;
    
    i++;
  }
  
  for (j=0;j<i;j++)
  {
    if  ((30-i+j<0)||(30-i+j>=61)) continue;
    
    str1[30-i+j]=get_smg_data(j);  // copy number where before '.'
  }
  
  str1[30]='.';
  
  for (j=i+1;j<datalen_real;j++)
  {
    if ((30+j-i<0)||(30+j-i>=61)) continue;
    
    str1[30+j-i]=get_smg_data(j);  // copy number where after '.'
  }
  
  for (j=0;j<datalen_real;j++)  // copy number
    if (dec==0)
    {
      if ((30-datalen_real+j<0)||(30-datalen_real+j>=61)) continue;
      
      set_smg_data(j,str1[30-datalen_real+j]);
    }
    else
    {
      if ((30-(datalen_real-dec-1)+j<0)||(30-(datalen_real-dec-1)+j>=61)) continue;
      
      set_smg_data(j,str1[30-(datalen_real-dec-1)+j]);
    }

  return(0);
}

int bw_getread::get_txt_after(char *data,int p1)
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

  while(i<strlen(data))
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

int bw_getread::get_txt_before(char *data,int p1)
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

  while(i<strlen(data))
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
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_line[gptr]);
}
int bw_getread::get_smg_colu(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
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

  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);

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
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  return(smg_string[gptr][ptr1]);
}
int bw_getread::get_smg_type(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_type[gptr]);
}
int bw_getread::get_smg_dlen(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_dlen[gptr]);
}
int bw_getread::get_smg_dlen_real(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_dlen_real[gptr]);
}
int bw_getread::get_smg_ddec(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_ddec[gptr]);
}
int bw_getread::get_smg_link(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_link[gptr]);
}
int bw_getread::get_smg_color(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_color[gptr]);
}
int bw_getread::get_smg_posi(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_posi[gptr]);
}
int bw_getread::get_smg_atte(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);

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
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_read_id[gptr]);
}

int bw_getread::set_smg_line(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_line[gptr]=val;
  return(0);
}
int bw_getread::set_smg_colu(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
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
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_type[gptr]=val;
  return(0);
}
int bw_getread::set_smg_dlen(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_dlen[gptr]=val;
  return(0);
}
int bw_getread::set_smg_dlen_real(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_dlen_real[gptr]=val;
  return(0);
}
int bw_getread::set_smg_ddec(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_ddec[gptr]=val;
  return(0);
}
int bw_getread::set_smg_link(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_link[gptr]=val;
  return(0);
}
int bw_getread::set_smg_color(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_color[gptr]=val;
  return(0);
}
int bw_getread::set_smg_posi(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_posi[gptr]=val;
  return(0);
}
int bw_getread::set_smg_read_id(int gptr,int val)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_read_id[gptr]=val;
  return(0);
}
int bw_getread::set_smg_string(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);

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
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  smg_string[gptr][ptr1]=val;
  return(0);
}
int bw_getread::set_smg_atte(int gptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);

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
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  smg_modi[gptr]=val;
  return(0);
}

int bw_getread::get_smg_modi(int gptr)
{
  if ((gptr<0)||(gptr>=SMG_GET_NUM)) return(0);
  return(smg_modi[gptr]);
}

