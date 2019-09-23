
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

#include "vc_bowo.h"

extern class bw_main         bw_main1;
extern class bw_buff         bw_buff1;
extern class bw_link         bw_link1;
extern class bw_win          bw_win1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;

//int  win_tst1;

int bw_link::tst_link1()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    sprintf(str,"lkpoin1,2=%d,%d,modi=%d,seri=%d,base=%d,recn=%d,wind=%d,"
    ,get_win_lkpoin(i,0)
    ,get_win_lkpoin(i,1)
    ,get_win_lkmodi(i)
    ,get_win_lkseri(i)
    ,get_win_lkbase(i)
    ,get_win_lkrecn(i)
    ,get_win_lkwind(i));

    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_link::tst_link2()
{
  HDC  hdc;
  int  i,j;
  char str[SMG_LEN*2];
  char str1[SMG_LEN];
  char str2[SMG_LEN];
//  char sln[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    if (get_win_bslink(i,2)!=0)
    {
      for (j=get_win_bspoin(i,0);j<=get_win_bspoin(i,1);j++)
      {
	str1[j-get_win_bspoin(i,0)]=get_win_chlink(j);
	str1[j-get_win_bspoin(i,0)+1]=0;
      }
    }
    else str1[0]=0;

    if (i<STRU_NUM) sprintf(str2,"%d",bw_xbase1.get_win_lnktab(i));
    else str2[0]=0;

    sprintf(str,"bslink0,1,2=%d,%d,%d,bspoin0,1=%d,%d,%s,%s,"
    ,get_win_bslink(i,0)
    ,get_win_bslink(i,1)
    ,get_win_bslink(i,2)
    ,get_win_bspoin(i,0)
    ,get_win_bspoin(i,1)
    ,str1
    ,str2);

    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_link::tst_link3()
{
  HDC  hdc;
  int  i,j;
  char str[SMG_LEN*2];
  char str1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    str1[0]=0;
    for (j=get_win_svpoin(i*5,0);j<get_win_svpoin(i*5,1);j++)
    {
      str1[j-get_win_svpoin(i*5,0)]=get_win_svar(j);
      str1[j-get_win_svpoin(i*5,0)+1]=0;
    }

    sprintf(str,"svpoin1,2=%d,%d,used=%d,seri=%d,base=%d,recn=%d,wind=%d,%s,"
    ,get_win_svpoin(i*5,0)
    ,get_win_svpoin(i*5,1)
    ,get_win_svused(i*5)
    ,get_win_svseri(i*5)
    ,get_win_svbase(i*5)
    ,get_win_svrecn(i*5)
    ,get_win_svwind(i*5)
    ,str1);

    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_link::tst_link4()
{
  HDC  hdc;
  int  i;
  char sv[SMG_LEN];
  char str[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    get_win_bb1(i,sv,SMG_LEN);

    sprintf(str,"win_bb231=%d,%d,%s,",get_win_bb2(i),get_win_bb3(i),sv);

    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_link::tst_link5()
{
  HDC  hdc;
  int  i,j;
  char str[SMG_LEN*2];
  char str1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<60;i++)
  {
    str1[0]=0;
    for (j=get_win_svpoin(i,0);j<get_win_svpoin(i,1);j++)
    {
      str1[j-get_win_svpoin(i,0)]=get_win_svar(j);
      str1[j-get_win_svpoin(i,0)+1]=0;
    }

    sprintf(str,"svpoin1,2=%d,%d,used=%d,seri=%d,base=%d,recn=%d,wind=%d,%s,"
    ,get_win_svpoin(i,0)
    ,get_win_svpoin(i,1)
    ,get_win_svused(i)
    ,get_win_svseri(i)
    ,get_win_svbase(i)
    ,get_win_svrecn(i)
    ,get_win_svwind(i)
    ,str1);

    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_link::w_dele_link(int wp1,int wp2)
{
  int  i,j,k,l,m,n,p,o,q,r,s,t,u,v,w,x;
//  char str[SMG_LEN];

  i=(-1);
  j=(-1);
  n=(-1);
  w=(-1);

  for (k=0;k<COND_NUM;k++)
  {
    if ((get_win_bslink(k,2)>=wp1)&&(get_win_bslink(k,2)<=wp2))
    {
      if (i<0) i=k;
      if (j<k) j=k;
    }
    if (get_win_bslink(k,2)>0)
    {
      if (n<k) n=k;
    }
    if ((get_win_bslink(k,2)<wp1)&&(get_win_bslink(k,2)>0))
    {
      if (w<k) w=k;
    }
  }

  if ((i>=0)&&(j>=0))
  {
    l=get_win_lkpoin(i,0);
    m=get_win_lkpoin(j,1);
    p=get_win_lkpoin(n,1);

    r=get_win_bspoin(i,0);
    s=get_win_bspoin(j,1);
    t=get_win_bspoin(n,1);

    u=j-i+1;
    if (u<0) u=0;

    o=m-l+1;
    if (o<0) o=0;

    v=s-r+1;
    if (v<0) v=0;
  }
  else
  {
    l=0;
    m=(-1);
//    p=win_lkpoin[n][1];
    p=(-1);

    r=0;
    s=(-1);
//    t=win_lkpoin[n][1];
    t=(-1);

    u=0;
    o=0;
    v=0;
  }

  if (w>=0)
  {
    x=get_win_lkpoin(w,1);
  }
  else
  {
    x=(-1);
  }
/*
  sprintf(str,"i,j,n=%d,%d,%d,w=%d,u,o,v=%d,%d,%d,"
	     ,i,j,n,w,u,o,v);
  MessageBox(bw_main1.win_hwnd1,str,"Aa",MB_OK);
*/
  if ((i>=0)&&(j>=0))
  {
    for (k=j+1;k<=n;k++)
    {
      if (get_win_lkpoin(k,0)-o>=0)
	set_win_lkpoin(k-u,0,get_win_lkpoin(k,0)-o);
      else
	set_win_lkpoin(k-u,0,0);

      if (get_win_lkpoin(k,1)-o>=0)
	set_win_lkpoin(k-u,1,get_win_lkpoin(k,1)-o);
      else
	set_win_lkpoin(k-u,1,0);

      if (get_win_bspoin(k,0)-v>=0)
	set_win_bspoin(k-u,0,get_win_bspoin(k,0)-v);
      else
	set_win_bspoin(k-u,0,0);

      if (get_win_bspoin(k,1)-v>=0)
	set_win_bspoin(k-u,1,get_win_bspoin(k,1)-v);
      else
	set_win_bspoin(k-u,1,0);

      set_win_bslink(k-u,0,get_win_bslink(k,0));
      set_win_bslink(k-u,1,get_win_bslink(k,1));
      if (get_win_bslink(k,2)-wp2+wp1-1>0)
	set_win_bslink(k-u,2,get_win_bslink(k,2)-wp2+wp1-1);
      else
	set_win_bslink(k-u,2,1);
    }

    for (k=m+1;k<=p;k++)
    {
      set_win_lkmodi(k-o,get_win_lkmodi(k));
      set_win_lkseri(k-o,get_win_lkseri(k));
      set_win_lkrecn(k-o,get_win_lkrecn(k));
      set_win_lkbase(k-o,get_win_lkbase(k));

      if (get_win_lkwind(k)-wp2+wp1-1>0)
	set_win_lkwind(k-o,get_win_lkwind(k)-wp2+wp1-1);
      else
	set_win_lkwind(k-o,1);
    }

  }
  else
  {
    for (k=w+1;k<=n;k++)
    {
      if (get_win_lkpoin(k,0)-o>=0)
	set_win_lkpoin(k-u,0,get_win_lkpoin(k,0)-o);
      else
	set_win_lkpoin(k-u,0,0);

      if (get_win_lkpoin(k,1)-o>=0)
	set_win_lkpoin(k-u,1,get_win_lkpoin(k,1)-o);
      else
	set_win_lkpoin(k-u,1,0);

      if (get_win_bspoin(k,0)-v>=0)
	set_win_bspoin(k-u,0,get_win_bspoin(k,0)-v);
      else
	set_win_bspoin(k-u,0,0);

      if (get_win_bspoin(k,1)-v>=0)
	set_win_bspoin(k-u,1,get_win_bspoin(k,1)-v);
      else
	set_win_bspoin(k-u,1,0);

      set_win_bslink(k-u,0,get_win_bslink(k,0));
      set_win_bslink(k-u,1,get_win_bslink(k,1));
      if (get_win_bslink(k,2)-wp2+wp1-1>0)
	set_win_bslink(k-u,2,get_win_bslink(k,2)-wp2+wp1-1);
      else
	set_win_bslink(k-u,2,1);
    }

    for (k=x+1;k<=p;k++)
    {
      set_win_lkmodi(k-o,get_win_lkmodi(k));
      set_win_lkseri(k-o,get_win_lkseri(k));
      set_win_lkrecn(k-o,get_win_lkrecn(k));
      set_win_lkbase(k-o,get_win_lkbase(k));

      if (get_win_lkwind(k)-wp2+wp1-1>0)
	set_win_lkwind(k-o,get_win_lkwind(k)-wp2+wp1-1);
      else
	set_win_lkwind(k-o,1);
    }
  }

  if ((i>=0)&&(j>=0))
  {
    if (n-j>=0)
    {
      if (n-j>0) q=i+n-j;
      else q=i;
       
      for (k=q;k<=n;k++)
      {
	set_win_bslink(k,0,0);
	set_win_bslink(k,1,0);
	set_win_bslink(k,2,0);

	set_win_bspoin(k,0,0);
	set_win_bspoin(k,1,0);

	set_win_lkpoin(k,0,0);
	set_win_lkpoin(k,1,0);
      }
    }

    if (p-m>=0)
    {
      if (p-m>0) q=l+p-m;
      else q=l;
       
      for (k=q;k<=p;k++)
      {
	set_win_lkmodi(k,0);
	set_win_lkseri(k,0);
	set_win_lkrecn(k,0);
	set_win_lkbase(k,0);
	set_win_lkwind(k,0);
      }
    }

  }

  if ((i>=0)&&(j>=0)&&(v>0))
  {
    for (k=s+1;k<=t;k++)
    {
      set_win_chlink(k-v,get_win_chlink(k));
    }

    for (k=t-v+1;k<=t;k++) set_win_chlink(k,0);
  }

  return(0);
}

int bw_link::w_dele_svar(int wp1,int wp2)
{
  int  i,j,k,l,m,n,p,o,q,r;
//  char str[SMG_LEN];

  i=(-1);
  j=(-1);
  n=(-1);
  r=(-1);

  for (k=0;k<WIN_VAR_NUM;k++)
  {
    if ((get_win_svwind(k)>=wp1)&&(get_win_svwind(k)<=wp2))
    {
      if (i<0) i=k;
      if (j<k) j=k;
    }
    if (get_win_svused(k)>0)
    {
      if (n<k) n=k;
    }
    if ((get_win_svwind(k)<wp1)&&(get_win_svwind(k)>0))
    {
      if (r<k) r=k;
    }
  }

  if ((i>=0)&&(j>=0))
  {
    l=get_win_svpoin(i,0);
    m=get_win_svpoin(j,1);
    p=get_win_svpoin(n,1);
  }
  else
  {
    if (r>=0)
    {
      l=get_win_svpoin(r,1);
      m=get_win_svpoin(r,1);
      p=get_win_svpoin(n,1);
    }
    else
    {
      l=0;
      m=0;
      p=get_win_svpoin(n,1);
    }
  }
/*
  sprintf(str,"wpp=%d,%d,lvpp=%d,%d,%d,svpp=%d,%d,%d,"
	     ,wp1,wp2
	     ,i,j,n
	     ,l,m,p);
  MessageBox(bw_main1.win_hwnd1,str,"aa",MB_OK);
*/
  o=m-l;
  if (o<0) o=0;

  if ((i>=0)&&(j>=0))
  {
    for (k=j+1;k<=n;k++)
    {
      set_win_svused(i+k-j-1,get_win_svused(k));
      if (get_win_svpoin(k,0)-o>=0) set_win_svpoin(i+k-j-1,0,get_win_svpoin(k,0)-o);
      else set_win_svpoin(i+k-j-1,0,0);
      if (get_win_svpoin(k,1)-o>=0) set_win_svpoin(i+k-j-1,1,get_win_svpoin(k,1)-o);
      else set_win_svpoin(i+k-j-1,1,0);
      set_win_svseri(i+k-j-1,get_win_svseri(k));
      set_win_svrecn(i+k-j-1,get_win_svrecn(k));
      set_win_svbase(i+k-j-1,get_win_svbase(k));
      if (get_win_svwind(k)-wp2+wp1-1>0) set_win_svwind(i+k-j-1,get_win_svwind(k)-wp2+wp1-1);
      else set_win_svwind(i+k-j-1,1);
    }

    if (n-j>=0)
    {
      if (n-j>0) q=i+n-j;
      else q=i;
       
      for (k=q;k<=n;k++)
      {
	set_win_svused(k,0);
	set_win_svpoin(k,0,0);
	set_win_svpoin(k,1,0);
	set_win_svseri(k,0);
	set_win_svrecn(k,0);
	set_win_svbase(k,0);
	set_win_svwind(k,0);
      }
    }

  }
  else
  {
    for (k=r+1;k<=n;k++)
    {
      if (get_win_svwind(k)-wp2+wp1-1>0)
	set_win_svwind(k,get_win_svwind(k)-wp2+wp1-1);
      else
	set_win_svwind(k,1);
    }
  }

  if ((i>=0)&&(j>=0)&&(o>0))
  {
    for (k=m;k<=p;k++)
    {
      set_win_svar(k-o,get_win_svar(k));
    }

    for (k=p-o+1;k<=p;k++) set_win_svar(k,0);
  }

  return(0);
}
int bw_link::w_read_link(char *p_fn,int p_fn_len,int wpp,int num)
{
  FILE *fp1;
  int   i,j,k,l;
  char  s_tmpc1[SMG_LEN];

  i=bw_inkey1.strlocc(p_fn,p_fn_len,'.');
  p_fn[i]=0;
  strcat(p_fn,".lnk");
  fp1=fopen(p_fn,"r");
  if (fp1==NULL) return(1);

  for (i=1+1;i<=num;i++)
  {
    while (1)
    {
      for (j=0;j<SMG_LEN;j++) s_tmpc1[j]=0;
      fgets(s_tmpc1,SMG_LEN,fp1);
      if (feof(fp1)) break;  
      if (strncmp(s_tmpc1,"&screenseg",10)==0) break;
    }
    if (feof(fp1)) break;
  }

  if (feof(fp1))
  {
    fclose(fp1);
    return(1);
  }

  for (i=0;i<COND_NUM;i++)
  {
    if (get_win_bslink(i,2)==0) break;
  }

  if (i>0) l=get_win_bspoin(i-1,1)+1;
  else l=0;

  while (1)
  {
    for (j=0;j<SMG_LEN;j++) s_tmpc1[j]=0;
    fgets(s_tmpc1,SMG_LEN,fp1);
    if (bw_inkey1.strempty(s_tmpc1)==0) break;
    if (s_tmpc1[0]=='&') break;
    k=w_find_link_tn(s_tmpc1,SMG_LEN,wpp,i);
    if (k==1)
    {
      fclose(fp1);
      return(1);
    }
    if (feof(fp1)) break;

    for (j=0;j<SMG_LEN;j++) s_tmpc1[j]=0;
    fgets(s_tmpc1,SMG_LEN,fp1);
    if (bw_inkey1.strempty(s_tmpc1)==0) break;
    if (s_tmpc1[0]=='&') break;
    l=w_find_link_cd(s_tmpc1,SMG_LEN,i,l);
    if (l<0)
    {
      fclose(fp1);
      return(1);
    }
    if (feof(fp1)) break;
    i++;
  }
  fclose(fp1);

  return(0);
}
int bw_link::w_find_link_tn(char *p_s1,int p_s1_len,int wpp,int i)
{
  int  j,l,m,n;
  int  p1,p2,p3,p4,p5,p6;
  char tn1[FN_SIZE],tn2[FN_SIZE],tn3[FN_SIZE];
  char *kk[8]={"none","multi","single","share",
	       "downright","up","upleft","upright"};
  char stn[FN_SIZE];

  for (j=0;j<SMG_LEN;j++) if (p_s1[j]>' ') break;
  if (j>=SMG_LEN) return(1);
  p1=j;
  for (j=j;j<SMG_LEN;j++) if (p_s1[j]=='>') break;
  if (j>=SMG_LEN) return(1);
  p2=j-1;
  p3=j+1;
  for (j=j;j<SMG_LEN;j++) if (p_s1[j]<=' ') break;
  if (j>=SMG_LEN) return(1);
  p4=j-1;
  for (j=j;j<SMG_LEN;j++) if (p_s1[j]>' ') break;
  if (j>=SMG_LEN) return(1);
  p5=j;
  for (j=j;j<SMG_LEN;j++) if (p_s1[j]<=' ') break;
  if (j>=SMG_LEN) return(1);
  p6=j-1;
  bw_inkey1.strpcut(p_s1,p1,p2-p1+1,p_s1_len,tn1,FN_SIZE);
  bw_inkey1.strpcut(p_s1,p3,p4-p3+1,p_s1_len,tn2,FN_SIZE);
  bw_inkey1.strpcut(p_s1,p5,p6-p5+1,p_s1_len,tn3,FN_SIZE);

  for (m=0;m<STRU_NUM;m++)
  {
    if (bw_win1.get_win_pp9(m,wpp)==1)
    {
      bw_win1.get_win_tabname(1,m,stn,FN_SIZE);

      if (strcmp(stn,tn1)==0) break;
    }
  }
  if (m>=STRU_NUM) return(0);

  for (n=0;n<STRU_NUM;n++)
  {
    if (bw_win1.get_win_pp9(n,wpp)==1)
    {
      bw_win1.get_win_tabname(1,n,stn,FN_SIZE);

      if (strcmp(stn,tn2)==0) break;
    }
  }
  if (n>=STRU_NUM) return(0);

  for (l=0;l<=7;l++) if (strcmp(kk[l],tn3)==0) break;
  if (l>7) l=0;
  set_win_bslink(i,0,m);
  set_win_bslink(i,1,n);
  set_win_bslink(i,2,wpp);
  bw_xbase1.set_win_lnktab(n,l);
  return(0);
}
int bw_link::w_find_link_cd(char *p_s1,int p_s1_len,int i,int k)
{
//  int  j;
  int  l,m;
  int  p1,p2;
  char tmpc2[SMG_LEN];

  m=k;
  for (l=0;l<SMG_LEN;l++) if (p_s1[l]>' ') break;
  if (l>=SMG_LEN) return(-1);
  p1=l;
  for (l=l;l<SMG_LEN;l++) if (p_s1[l]<=' ') break;
  if (l>=SMG_LEN) return(-1);
  p2=l-1;
  bw_inkey1.strpcut(p_s1,p1,p2-p1+1,p_s1_len,tmpc2,SMG_LEN);
  l=k;

  if (l+strlen(tmpc2)>=LINK_CHAR)
  {
    bw_win1.w_atten10();
    return(-1);
  }

  for (k=l;k<=l+(int)strlen(tmpc2)-1;k++) set_win_chlink(k,tmpc2[k-l]);

  k=l+strlen(tmpc2)-1;
  set_win_bspoin(i,0,m);
  set_win_bspoin(i,1,k);

  return(k+1);
}

int bw_link::w_link_modi(int wpp)  /* fetch link var in cond & link var if modi */
{
  char s1[SMG_LEN];
  char tn[SMG_LEN];
  char fn[SMG_LEN];
  int  i,j;
  int  p1,p2;
  long tr;
  char stn[FN_SIZE];

  for (i=0;i<COND_NUM;i++)
  {
    if (get_win_bslink(i,2)!=wpp) continue;

    if (i>=COND_NUM) return(-1);
    if (i>0) p1=get_win_lkpoin(i-1,1)+1;
    else p1=0;

    set_win_lkpoin(i,0,p1);
    p2=get_win_bspoin(i,0);
    while (1)
    {
      p2=w_fetch_link_var(i,p2,s1,SMG_LEN);
      if (p2<0) break;

      bw_win1.w_fetch_fld_style(s1,SMG_LEN,tn,SMG_LEN,&tr,fn,SMG_LEN,wpp);
      if (bw_inkey1.strempty(fn)==0) continue;
      if (bw_inkey1.strempty(tn)==0) continue;

      for (j=0;j<STRU_NUM;j++)
      {
	if (bw_win1.get_win_pp9(j,wpp)==1)
        {
	  bw_win1.get_win_tabname(1,j,stn,FN_SIZE);

	  if (strcmp(stn,tn)==0) break;
        }
      }
      if (j>=STRU_NUM) j=0;

      if (get_win_bslink(i,1)==j) continue;

      w_link_modi_set(tn,SMG_LEN,fn,SMG_LEN,p1,wpp);

      p1++;
    }

    set_win_lkpoin(i,1,p1-1);
  }
/*
  for (i=0;i<=COND_NUM-1;i++)
  {
    loc(i+1,1);
    printf("p1,p2=%d,%d,",win_lkpoin[i][0],win_lkpoin[i][1]);
  }
  inkey();

  for (i=0;i<=20;i++)
  {
    loc(i+1,1);
    printf("seri=%d,base=%d,",win_lkseri[i],win_lkbase[i]);
  }
  inkey();
*/
  return(0);
}

int bw_link::w_fetch_link_var(int p1,int p2,char *p_s1,int p_s1_len)
{
  char ff[10]={'(',')','+','-','*','/','^','|','&','='};
  int  i,j,k,l;
  int  exist;
  int  exist2;

  for (i=p2;i<=get_win_bspoin(p1,1);i++)
  {
    exist=0;
    for (j=0;j<=9;j++)
    {
      if (get_win_chlink(i)==ff[j])
      {
        exist=1;
        break;
      }
    }
    if (exist==1) continue;  /* ca1 no beg */

    for (k=i;k<=get_win_bspoin(p1,1);k++)
    {
      exist=0;
      exist2=0;
      for (j=0;j<=9;j++)
      {
        if (get_win_chlink(k)==ff[j])
        {
          if (j==0)
          {
            exist2=1;
          }
          exist=1;
          break;
        }
      }
      if (exist==1) break;
    }
    if (exist2==1)
    {
      i=k+1;
      continue;   /* ca2 beg no end */
    }

    p_s1[0]=0;

    for (l=i;l<k;l++)
    {
      if (l-i+0<p_s1_len) p_s1[l-i+0]=get_win_chlink(l);
      if (l-i+1<p_s1_len) p_s1[l-i+1]=0;
    }

    return(k);    /* ca3 beg and end */
  }
  return(-1);
}

int bw_link::w_fetch_link_var2(int p1,int p2,char *p_s1,int p_s1_len)
{
  char ff[10]={'(',')','+','-','*','/','^','|','&','='};
  int  i,j,k,l;
  int  exist;
  int  exist2;

  for (i=p2;i<=get_win_bspoin(p1,1);i++)
  {
    exist=0;
    for (j=0;j<=9;j++)
    {
      if (get_win_chlink(i)==ff[j])
      {
        exist=1;
        break;
      }
    }
    if (exist==1)                     /* ca1 no beg */
    {
      p_s1[0]=ff[j];
      p_s1[1]=0;
      return(i+1);
    }
    for (k=i;k<=get_win_bspoin(p1,1);k++)
    {
      exist=0;
      exist2=0;
      for (j=0;j<=9;j++)
      {
        if (get_win_chlink(k)==ff[j])
        {
          if (j==0)
          {
            exist2=1;
          }
          exist=1;
          break;
        }
      }
      if (exist==1) break;
    }
    if (exist2==1)
    {
      i=k+1;
      continue;   /* ca2 beg no end */
    }

    p_s1[0]=0;

    for (l=i;l<k;l++)
    {
      if (l-i+0<p_s1_len) p_s1[l-i+0]=get_win_chlink(l);
      if (l-i+1<p_s1_len) p_s1[l-i+1]=0;
    }
    return(k);    /* ca3 beg and end */
  }
  return(-1);
}

int bw_link::w_link_modi_set(char *p_tn,int p_tn_len,char *p_fn,int p_fn_len,int p1,int wpp)
{
  int  i,j;
  char stn[FN_SIZE];
  char sf1[20];

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp9(i,wpp)==1)
    {
      bw_win1.get_win_tabname(1,i,stn,FN_SIZE);

      if (strcmp(stn,p_tn)==0) break;
    }
  }
  if (i>=STRU_NUM) i=0;

  for (j=bw_fldstru1.get_t2_fldpoin(i,0);j<=bw_fldstru1.get_t2_fldpoin(i,1);j++)
  {
    bw_fldstru1.get_t2_fldname(j,sf1,20);
    if (strcmp(sf1,p_fn)==0) break;
  }
  if (j>bw_fldstru1.get_t2_fldpoin(i,1)) j=0;
  else j=j-bw_fldstru1.get_t2_fldpoin(i,0);

  set_win_lkseri(p1,j);
  set_win_lkbase(p1,i);
  set_win_lkwind(p1,wpp);
  set_win_lkrecn(p1,0);

  return(0);
}

int bw_link::w_link_modi_mark(int wpp,int mark,int seri,int recn)   /* echo win rec ,link rec should change */
{
  int i,j,k;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp9(i,wpp)!=1) continue;
    if ((mark>=0)&&(i!=mark)) continue;

    for (j=0;j<COND_NUM;j++)
    {
      if ((get_win_bslink(j,0)==i)&&(get_win_bslink(j,2)==wpp))
      {
	for (k=get_win_lkpoin(j,0);k<=get_win_lkpoin(j,1);k++)
	{
	  if (get_win_lkbase(k)==i)
	  {
	    if ((seri>=0)&&(get_win_lkseri(k)!=seri)) continue;
	    set_win_lkmodi(k,1);
	    set_win_lkrecn(k,recn);
	  }
	}
      }
    }
  }
/*
  for (i=0;i<COND_NUM;i++)
  {
    loc(i+1,1);
    for (j=win_lkpoin[i][0];j<=win_lkpoin[i][1];j++)
      printf("%d,",win_lkmodi[j]);
  }
  inkey();
*/
  return(0);
}

int bw_link::w_link_modi_unmark(int wpp,int mark,int seri,int recn)   /* echo win rec ,link rec should change */
{
  int i,j,k;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_pp9(i,wpp)!=1) continue;
    if ((mark>=0)&&(i!=mark)) continue;

    for (j=0;j<COND_NUM;j++)
    {
      if ((get_win_bslink(j,0)==i)&&(get_win_bslink(j,2)==wpp))
      {
	for (k=get_win_lkpoin(j,0);k<=get_win_lkpoin(j,1);k++)
        {
	  if (get_win_lkbase(k)==i)
          {
	    if ((seri>=0)&&(get_win_lkseri(k)!=seri)) continue;
	    set_win_lkmodi(k,0);
	    set_win_lkrecn(k,recn);
          }
        }
      }
    }
  }
/*
  for (i=0;i<COND_NUM;i++)
  {
    loc(i+1,1);
    for (j=win_lkpoin[i][0];j<=win_lkpoin[i][1];j++)
      printf("%d,",win_lkmodi[j]);
  }
  inkey();
*/
  return(0);
}

int bw_link::w_echo_winrec_lnk(int wpp) /* echo win rec where modified */
{
  long s_recno[STRU_NUM];
  int  s_seri[STRU_NUM];
  char s_fldname[SMG_LEN];
  int  i,j,k,l,m,n,o,p,q,r,s,t,u,v;
  int  p1,p2;
  int  exist;
  char str[SMG_LEN];
//  char str1[SMG_LEN];
  char str2[SMG_LEN];
  char str3[SMG_LEN];

  HFONT  holdfont,hfont;
  HDC    hdc;
//  HDC    hdc1;
  HWND   hnd;

  hdc=GetDC(bw_main1.win_hwnd);
  hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  holdfont=(HFONT)SelectObject(hdc,hfont);

  exist=0;
  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_pp9(i,wpp)==1)&&(bw_xbase1.get_win_lnktab(i)>0))
    {
      if (bw_xbase1.get_win_lnktab(i)>0)
      {
	if (bw_xbase1.get_win_lnktab(i)>1)
	{
	  s_recno[i]=0;
	  bw_xbase1.set_win_recno(i,wpp,0,0);
	}
        else
	{
	  if (get_win_continue(i,wpp)==1)
	  {
	    s_recno[i]=bw_xbase1.get_win_recno(i,wpp,1)-1;
	    set_win_continue(i,wpp,0);
	  }
	  else
	  {
	    s_recno[i]=0;
	    bw_xbase1.set_win_recno(i,wpp,0,0);
	  }
	}
      }
      else s_recno[i]=bw_xbase1.get_win_recno(i,wpp,1)-1;
      s_seri[i]=0;
      bw_xbase1.set_win_enseri(i,wpp,0);
      bw_xbase1.set_win_cuseri(i,wpp,0);
      exist=1;
    }
  }

  if (exist==0)
  {
    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.win_hwnd,hdc);

    return(0);
  }

  for (r=0;r<COND_NUM;r++)
  {
    if (get_win_bslink(r,2)!=wpp) continue;
    k=get_win_bslink(r,1);
    s=get_win_bslink(r,0);

    exist=0;

    if (bw_win1.get_win_pp9(k,wpp)!=1) continue;

    if (bw_win1.get_win_pp9(s,wpp)!=1) continue;

    if (w_link_modified(wpp,s)!=1) continue;

    w_link_modi_unmark(wpp,s,-1,-1);

    w_link_modi_mark(wpp,k,-1,-1);

    for (l=1;l<=bw_win1.w_cnt_winline(k,wpp,LIN_NUM);l++)
    {
      for (i=1;i<LIN_NUM;i++)
      {
	for (j=1;j<COL_NUM;j++)
	{
	  if (bw_buff1.get_linecol(wpp,i,j)!=0)
	  {
	    m=bw_buff1.get_linecol(wpp,i,j);

            bw_win1.get_1fldname(m,str2,SMG_LEN);

	    if ((str2[0]!=':')&&(str2[0]!='%')&&(str2[0]!='+')) continue;
	    if (bw_win1.get_1fldbase(m)!=k) continue;
	    if (bw_win1.get_1fldseri(m)!=l) continue;

	    strcpy(str,str2);
            bw_inkey1.strpcut(str,1,strlen(str)-1,SMG_LEN,s_fldname,SMG_LEN);

	    if (s_seri[k]!=bw_win1.get_1fldseri(m))
	    {

//	      win_tst1=0;

	      while (1)
	      {
		s_recno[k]=bw_mbase1.w_down_rec(k,wpp,s_recno[k]);

		if (bw_xbase1.get_win_lnktab(k)==3)
		{
		  u=bw_buff1.get_linecol(wpp,bw_win1.pline,bw_win1.pfield);
		  if(u>=0) u=bw_win1.get_1fldseri(u);
		  else u=1;
		}
		else u=bw_win1.get_1fldseri(m);

		if (w_link_cond_ok(r,wpp,k,u,wpp)==1) break;
		if (bw_xbase1.win_state3==1)    break;
	      }
	      s_seri[k]=bw_win1.get_1fldseri(m);
	      if (bw_xbase1.win_state3==0)
	      {
		bw_xbase1.set_win_enseri(k,wpp,l);
		if (bw_xbase1.get_win_recno(k,wpp,0)<=0)
		{
		  bw_xbase1.set_win_recno(k,wpp,0,s_recno[k]);
		}
                exist=1;
	      }
	    }

		 /* fetch win_field number */
	    n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_LEN,k);
	    if (n==1) continue;

	    p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_LEN,k);
	    q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_LEN,k);

	    v=bw_fldstru1.w_find_fldtype(s_fldname,SMG_LEN,k);
	    if (v=='m') continue;
            if (v=='b') continue;

	    for (o=1;o<=q;o++) str[o-1]=bw_xbase1.get_win_recvar(p+o-1);

	    strcpy(str3,str);
            str3[q]=0;

	    str[q]=0;
	    str[bw_win1.get_1fldlen(m)]=0;

	    if ((str2[0]==':')||(str2[0]=='%'))
            {
	      p1=(int)((j-bw_win1.get_win_con(wpp,0))*bw_main1.win_edit_xchar);
	      p2=(int)((i-bw_win1.get_win_con(wpp,1))*bw_main1.win_edit_ychar);

	      HideCaret(bw_main1.win_hwnd);
	      TextOut(hdc,p1,p2,str,strlen(str));
	      ShowCaret(bw_main1.win_hwnd);
	    }
	    else
	    {
	      t=bw_win1.w_find_hnd(wpp,j,i);
	      if (t!=0)
	      {
                hnd=bw_win1.get_win_hnd(t);
	        SetWindowText(hnd,str3);
              }
	    }

	    t=bw_fldstru1.w_find_fldnum(s_fldname,SMG_LEN,k);
	    if (t==0)
	    {
	      t=bw_fldstru1.win_field_num;

	      w_save_sv(wpp
	                ,k
			,t-bw_fldstru1.get_t2_fldpoin(k,0)
			,bw_win1.get_1fldseri(m)
                        ,bw_fldstru1.get_t2_fldposi(t)
			,bw_fldstru1.get_t2_fldlen(t));
	    }
              /*save scrn var to arr*/
	  }
	}
      }                                   
    }
    if (exist==0)
    {
      bw_xbase1.set_win_recno(k,wpp,0,1);
    }
  }

  SelectObject(hdc,holdfont);
  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}

int bw_link::w_link_modified(int wpp,int basep)
{
  int i,j;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,0)==basep)&&(get_win_bslink(i,2)==wpp))
    {
      for (j=get_win_lkpoin(i,0);j<=get_win_lkpoin(i,1);j++)
	if (get_win_lkmodi(j)==1) return(1);
    }
  }

  return(0);
}

int bw_link::w_link_cond_ok(int condnum,int wpp,int basep,int recn,int page)
{
//  HDC  hdc;
  int  i,j,k;
  int  exist;
  int  p2;
  int  pp1,pp2,pp3,pp4;
  int  state;
  char tn[SMG_LEN];
  char fn[SMG_LEN];
  char s1[SMG_LEN];
//  char str[SMG_LEN];
  long tr;
  char stn[FN_SIZE];
  char sv1[SMG_LEN];
  char sv2[SMG_LEN];

  i=condnum;

  exist=0;
  if ((get_win_bslink(i,1)==basep)&&(get_win_bslink(i,2)==wpp)) exist=1;
  if (exist==0) return(0);

  pp1=(-1);  /* base poin */
  pp2=(-1);  /* fld  seri */
  pp3=(-1);  /* buff poin */
  pp4=(-1);  /* calc char poin */
  state=0;
  p2=get_win_bspoin(i,0);     /* load condition */
  while (1)
  {
    p2=w_fetch_link_var2(i,p2,s1,SMG_LEN);
    if (p2<0) break;

    if (w_is_calc(s1)==1)
    {
      if (state!=1) continue;
      state=0;
      pp4++;
      set_win_bb2(pp4,s1[0]);
      continue;
    }

    bw_win1.w_fetch_fld_style(s1,SMG_LEN,tn,SMG_LEN,&tr,fn,SMG_LEN,wpp);

    state=1;
    if (bw_inkey1.strempty(tn)==0)
    {
      bw_win1.w_atten13(s1);
      return(0);
    }
    else
    {
      for (j=0;j<STRU_NUM;j++)
      {
	if (bw_win1.get_win_pp9(j,wpp)==1)
        {
	  bw_win1.get_win_tabname(1,j,stn,FN_SIZE);

	  if (strcmp(stn,tn)==0) break;
        }
      }
      if (j>=STRU_NUM) return(0);
      else pp1=j;
    }

    if (bw_inkey1.strempty(fn)==0)
    {
      bw_win1.w_atten14(s1);
      return(0);
    }
    else
    {
      exist=w_name_t1_t2(fn,pp1);
      if (exist<0)
      {
        bw_win1.w_atten14(s1);
        return(0);
      }
      else pp2=exist;
    }

    if (pp1==basep)
    {
      pp3++;
      if (pp3>=VAL_NUM)
      {
        bw_win1.w_atten12();
        return(0);
      }

      for (j=1;j<=bw_fldstru1.get_t2_fldlen(pp2+bw_fldstru1.get_t2_fldpoin(pp1,0));j++)
      {
	set_win_cbb1(pp3,j-1,bw_xbase1.get_win_recvar(bw_fldstru1.get_t2_fldposi(pp2+bw_fldstru1.get_t2_fldpoin(pp1,0))+j-1));
	set_win_cbb1(pp3,j-0,0);
      }
      set_win_bb3(pp3,bw_fldstru1.get_t2_fldtype(pp2+bw_fldstru1.get_t2_fldpoin(pp1,0)));

    }
    else
    {
      exist=0;
      for (j=0;j<WIN_VAR_NUM;j++)
      {
	if ((get_win_svwind(j)==page)&&(get_win_svbase(j)==pp1)&&(get_win_svseri(j)==pp2))
        {
	  if (bw_xbase1.get_win_lnktab(basep)<=1)
          {
            exist=1;
	    break;
          }
          else
          {
	    if (get_win_svrecn(j)==recn)
            {
              exist=1;  
              break;
            }
          }
        }
      }
      if (exist==0) return(0);

      pp3++;
      if (pp3>=VAL_NUM)
      {
        bw_win1.w_atten12();
        return(0);
      }

      for (k=get_win_svpoin(j,0);k<get_win_svpoin(j,1);k++)
      {
	set_win_cbb1(pp3,k-get_win_svpoin(j,0),get_win_svar(k));
	set_win_cbb1(pp3,k-get_win_svpoin(j,0)+1,0);
      }
      set_win_bb3(pp3,bw_fldstru1.get_t2_fldtype(pp2+bw_fldstru1.get_t2_fldpoin(pp1,0)));
    }

    if (pp3>=1) break;
  }

  get_win_bb1(0,sv1,SMG_LEN);
  get_win_bb1(1,sv2,SMG_LEN);

  bw_inkey1.strtrim(sv1,SMG_LEN);
  bw_inkey1.strtrim(sv2,SMG_LEN);

//  sprintf(str,"%s,%s,",sv1,sv2);
//  win_tst1++;
//  hdc=GetDC(bw_main1.win_hwnd1);
//  TextOut(hdc,1,win_tst1*20,str,strlen(str));
//  ReleaseDC(bw_main1.win_hwnd1,hdc);

  if ((get_win_bb3(0)=='c')&&(get_win_bb3(1)=='c')&&(get_win_bb2(0)=='='))
  {
    if (strcmp(sv1,sv2)==0) return(1);
    else return(0);
  }
  else return(0);
}

int bw_link::w_is_calc(char *s1)
{
  char ff[10]={'(',')','+','-','*','/','^','|','&','='};
  char c1;
  int  exist;
  int  i;

  exist=0;
  c1=s1[0];
  for (i=0;i<=9;i++)
  {
    if (ff[i]==c1)
    {
      exist=1;
      break;
    }
  }

  return(exist);
}

int bw_link::w_name_t1_t2(char *p_str,int basep)
{
  int  i;
  int  exist;
  char sf1[20];

  exist=0;

  for (i=bw_fldstru1.get_t2_fldpoin(basep,0);i<=bw_fldstru1.get_t2_fldpoin(basep,1);i++)
  {
    bw_fldstru1.get_t2_fldname(i,sf1,20);
    if (strcmp(sf1,p_str)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1) return(i-bw_fldstru1.get_t2_fldpoin(basep,0));
  else return(-1);
}

int bw_link::w_scan_svar(int wpp)
{
  int  i,j,k,n;
//  int  s_tmpn1,s_tmpn2;
  int  p1,p2;            /* p1 scrn var content poin,p2 scrn var num poin */
  int  exist;
  char str[FN_SIZE];
  char str1[FN_SIZE];

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if (get_win_svwind(i)==wpp) break;
    if (get_win_svused(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);
  else
  {
    if (i==0)
    {
      p1=0;
      p2=0;
    }
    else
    {
      p1=get_win_svpoin(i-1,1);
      p2=i;
    }
  }

  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_linecol(wpp,i,j)>0)
      {
	n=bw_buff1.get_linecol(wpp,i,j);
	if (bw_win1.get_1fldedt(n)==0)
	{
	  bw_win1.get_1fldname(n,str,FN_SIZE);
	  if (strlen(str)>1) bw_inkey1.strpcut(str,1,strlen(str)-1,FN_SIZE,str1,FN_SIZE);
	  else continue;

	  k=w_name_t1_t2(str1,bw_win1.get_1fldbase(n));
	  if (k<0) continue;

	  set_win_svpoin(p2,0,p1);
	  set_win_svbase(p2,bw_win1.get_1fldbase(n));
	  set_win_svseri(p2,k);
	  set_win_svrecn(p2,bw_win1.get_1fldseri(n));
	  set_win_svwind(p2,wpp);
                                                
	  p1=p1+bw_fldstru1.get_t2_fldlen(k+bw_fldstru1.get_t2_fldpoin(bw_win1.get_1fldbase(n),0));

	  set_win_svpoin(p2,1,p1);
	  set_win_svused(p2,1);

          p1++;
          if (p1>=VAR_IN_SCRN)
	  {
             bw_win1.w_atten12();
             return(1);
          }

	  p2++;
          if (p2>=WIN_VAR_NUM)
	  {
             bw_win1.w_atten11();
             return(1);
          }
	}
      }
    }
  }
/*
  for (i=1;i<=20;i++)
  {
    loc(i,1);
    printf("poin=%d,seri=%d,base=%d,",
	      win_svpoin[i],win_svseri[i],win_svbase[i]);
  }
  inkey();
*/
  return(0);                         
}

int bw_link::w_save_sv(int wpp,int base,int seri,int recn,int posi,int len)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if ((get_win_svwind(i)==wpp)&&(get_win_svbase(i)==base)&&(get_win_svseri(i)==seri)&&(get_win_svrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  for (j=1;j<=len;j++) set_win_svar(get_win_svpoin(i,0)+j-1,bw_xbase1.get_win_recvar(posi+j-1));
/*
  loc(20,1);
  printf("%d,",win_svpoin[exist]);
  for (i=1;i<=len;i++)
    putchar(win_svar[win_svpoin[exist]+i-1]);
  inkey();
*/
  return(0);
}

int bw_link::w_get_sv(int wpp,int base,int seri,int recn,char *p_str,int p_str_len)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if ((get_win_svwind(i)==wpp)&&(get_win_svbase(i)==base)&&(get_win_svseri(i)==seri)&&(get_win_svrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  for (j=get_win_svpoin(i,0);j<get_win_svpoin(i,1);j++)
  {
    if (j-get_win_svpoin(i,0)<p_str_len)
    {
      p_str[j-get_win_svpoin(i,0)]=get_win_svar(j);
    }
  }

  if (get_win_svpoin(i,1)-get_win_svpoin(i,0)<p_str_len)
  {
    p_str[get_win_svpoin(i,1)-get_win_svpoin(i,0)]=0;
  }

/*
  loc(20,1);
  printf("%d,",win_svpoin[exist]);
  for (i=1;i<=p_str_len;i++)
    putchar(win_svar[win_svpoin[exist]+i-1]);
  inkey();
*/
  return(0);
}

int bw_link::w_link_type(int wpp,int basep)
{
  int i,j,k;

  j=0;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,2)==wpp)&&(get_win_bslink(i,0)==basep))
    {
      k=get_win_bslink(i,1);
      if (k<STRU_NUM) k=bw_xbase1.get_win_lnktab(k);
      else k=0;
      if (k>j) j=k;
    }
  }

  return(j);
}

int bw_link::w_link_number(int wpp,int basep)
{
  int i,j;

  j=0;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,2)==wpp)&&(get_win_bslink(i,1)==basep))
    {
      j=i;
    }
  }

  return(j);
}

int bw_link::w_link_base_num(int wpp,int basep)
{
  int i,j;

  j=0;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,2)==wpp)&&(get_win_bslink(i,1)==basep))
    {
      j=get_win_bslink(i,0);
    }
  }

  return(j);
}

int bw_link::w_link_set_continue(int wpp,int p_fcnt)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  set_win_continue(p_fcnt,wpp,1);
  return(0);
}

int bw_link::w_keep_linkfld(int wpp,int p_fcnt,int dir)
{
  int  i,j,k,l,m,n;
  int  exist;
  char str[SMG_LEN];
  char str1[SMG_LEN];
  char str2[SMG_LEN];
  char str3[SMG_LEN];

  exist=0;

  for (i=0;i<COND_NUM;i++)   
  {
    if ((get_win_bslink(i,1)==p_fcnt)&&(get_win_bslink(i,2)==wpp))
    {
      j=get_win_bslink(i,0);
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  k=get_win_lkpoin(i,0);
  l=get_win_lkseri(k);
  w_get_sv(wpp,j,l,1,str,SMG_LEN);

  for (m=get_win_bspoin(i,0);m<=get_win_bspoin(i,1);m++)
  {
    str1[m-get_win_bspoin(i,0)]=get_win_chlink(m);
  }
  str1[get_win_bspoin(i,1)-get_win_bspoin(i,0)+1]=0;

  n=bw_inkey1.strlocc(str1,SMG_LEN,'=');
  bw_inkey1.strpcut(str1,n+1,strlen(str1)-n-1,SMG_LEN,str2,SMG_LEN);
  n=bw_inkey1.strlocc(str2,SMG_LEN,'.');
  bw_inkey1.strpcut(str2,n+1,strlen(str2)-n-1,SMG_LEN,str3,SMG_LEN);

  bw_xbase1.w_clr_recvar(p_fcnt);
  bw_fldstru1.w_sav_tab_var(str3,SMG_LEN,p_fcnt,str,SMG_LEN);
  bw_mbase1.w_save_rec(p_fcnt,wpp,bw_xbase1.get_win_recno(p_fcnt,wpp,0)+dir);
  bw_xbase1.set_win_state5(p_fcnt,1);

  return(0);
}





int bw_link::get_win_svar(int spp)
{
  if ((spp<0)||(spp>=VAR_IN_SCRN)) return(0);
  return(win_svar[spp]);
}
int bw_link::set_win_svar(int spp,int val)
{
  if ((spp<0)||(spp>=VAR_IN_SCRN)) return(0);
  win_svar[spp]=val;
  return(0);
}
int bw_link::get_win_svused(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svused[vpp]);
}
int bw_link::set_win_svused(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svused[vpp]=val;
  return(0);
}
int bw_link::get_win_svpoin(int vpp,int p01)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_svpoin[vpp][p01]);
}
int bw_link::set_win_svpoin(int vpp,int p01,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_svpoin[vpp][p01]=val;
  return(0);
}
int bw_link::get_win_svseri(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svseri[vpp]);
}
int bw_link::set_win_svseri(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svseri[vpp]=val;
  return(0);
}
int bw_link::get_win_svrecn(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svrecn[vpp]);
}
int bw_link::set_win_svrecn(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svrecn[vpp]=val;
  return(0);
}
int bw_link::get_win_svbase(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svbase[vpp]);
}
int bw_link::set_win_svbase(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svbase[vpp]=val;
  return(0);
}
int bw_link::get_win_svwind(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svwind[vpp]);
}
int bw_link::set_win_svwind(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svwind[vpp]=val;
  return(0);
}
int bw_link::get_win_chlink(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_CHAR)) return(0);
  return(win_chlink[lpp]);
}
int bw_link::set_win_chlink(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_CHAR)) return(0);
  win_chlink[lpp]=val;
  return(0);
}
int bw_link::get_win_bslink(int dpp,int p02)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(win_bslink[dpp][p02]);
}
int bw_link::set_win_bslink(int dpp,int p02,int val)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  win_bslink[dpp][p02]=val;
  return(0);

}
int bw_link::get_win_bspoin(int dpp,int p01)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_bspoin[dpp][p01]);
}
int bw_link::set_win_bspoin(int dpp,int p01,int val)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_bspoin[dpp][p01]=val;
  return(0);
}
int bw_link::get_win_lkpoin(int cpp,int p01)
{
  if ((cpp<0)||(cpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_lkpoin[cpp][p01]);
}
int bw_link::set_win_lkpoin(int cpp,int p01,int val)
{
  if ((cpp<0)||(cpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_lkpoin[cpp][p01]=val;
  return(0);
}
int bw_link::get_win_lkmodi(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkmodi[lpp]);
}
int bw_link::set_win_lkmodi(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkmodi[lpp]=val;
  return(0);
}
int bw_link::get_win_lkseri(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkseri[lpp]);
}
int bw_link::set_win_lkseri(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkseri[lpp]=val;
  return(0);
}
int bw_link::get_win_lkbase(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkbase[lpp]);
}
int bw_link::set_win_lkbase(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkbase[lpp]=val;
  return(0);
}
int bw_link::get_win_lkrecn(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkrecn[lpp]);
}
int bw_link::set_win_lkrecn(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkrecn[lpp]=val;
  return(0);
}
int bw_link::get_win_lkwind(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkwind[lpp]);
}
int bw_link::set_win_lkwind(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkwind[lpp]=val;
  return(0);
}
int bw_link::get_win_continue(int p_fcnt,int wpp)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_continue[p_fcnt][wpp]);
}
int bw_link::set_win_continue(int p_fcnt,int wpp,int val)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_continue[p_fcnt][wpp]=val;
  return(0);
}
int bw_link::set_win_cbb1(int vpp,int pp1,int val)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  win_bb1[vpp][pp1]=val;
  return(0);
}
int bw_link::get_win_bb1(int vpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  if (p_s1_len>SMG_LEN) i=SMG_LEN;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_bb1[vpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_link::set_win_bb1(int vpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  if (p_s1_len>SMG_LEN) i=SMG_LEN;
  else i=p_s1_len;

  win_bb1[vpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_bb1[vpp][j+0]=p_s1[j];
    win_bb1[vpp][j+1]=0;
  }

  return(0);
}
int bw_link::get_win_bb2(int vpp)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  return(win_bb2[vpp]);
}
int bw_link::set_win_bb2(int vpp,int val)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  win_bb2[vpp]=val;
  return(0);
}
int bw_link::get_win_bb3(int vpp)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  return(win_bb3[vpp]);
}
int bw_link::set_win_bb3(int vpp,int val)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  win_bb3[vpp]=val;
  return(0);
}

