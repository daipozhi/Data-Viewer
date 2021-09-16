
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

extern class bw_main         bw_main1;
extern class bw_buff         bw_buff1;
extern class bw_link         bw_link1;
extern class bw_win          bw_win1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;
extern class bw_getread      bw_getread1;


int bw_link::tst_link1()
{
  //HDC  hdc;
  int  i;
  char str1[SMG_SIZE];

  bw_getread1.deb_record("bw_link::tst_link1()");

  for (i=0;i<60;i++)
  {
    sprintf(str1,"ptr=%d,win_lkpoin0,1=%d,%d,lkmodi=%d,lkseri=%d,lkbase=%d,lkrecn=%d,lkwind=%d,"
    ,i
    ,get_win_lkpoin(i,0)
    ,get_win_lkpoin(i,1)
    ,get_win_lkmodi(i)
    ,get_win_lkseri(i)
    ,get_win_lkbase(i)
    ,get_win_lkrecn(i)
    ,get_win_lkwind(i));

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_link::tst_link1_lkchar()
{
  int  i,j;
  char str1[3000];
  char str2[300];
  char str3[300];

  bw_getread1.deb_record("bw_link::tst_link_lkchar()");

  for (i=0;i<60;i++)
  {
    sprintf(str1,"ptr=%d,win_lkpoin0=%d,lkpoin1=%d,lkmodi=%d,lkseri=%d,lkbase=%d,lkrecn=%d,lkwind=%d,"
    ,i
    ,get_win_lkpoin(i,0)
    ,get_win_lkpoin(i,1)
    ,get_win_lkmodi(i)
    ,get_win_lkseri(i)
    ,get_win_lkbase(i)
    ,get_win_lkrecn(i)
    ,get_win_lkwind(i));

    bw_getread1.deb_record(str1);
  }

  for (i=0;i<60;i++)
  {
    if (get_win_bslink(i,2)!=0)
    {
      for (j=get_win_bspoin(i,0);j<=get_win_bspoin(i,1);j++)
      {
	str3[j-get_win_bspoin(i,0)+0]=get_win_chlink(j);
	str3[j-get_win_bspoin(i,0)+1]=0;
      }
    }
    else str3[0]=0;

    if (i<STRU_NUM) sprintf(str2,"%d",bw_xbase1.get_win_lnktab(i));
    else str2[0]=0;

    sprintf(str1,"ptr=%d,win_bslink0,1,2=%d,%d,%d,bspoin0,1=%d,%d,win_lnktab=%s,win_chlink=%s,"
    ,i
    ,get_win_bslink(i,0)
    ,get_win_bslink(i,1)
    ,get_win_bslink(i,2)
    ,get_win_bspoin(i,0)
    ,get_win_bspoin(i,1)
    ,str2
    ,str3
    );

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_link::tst_link2()
{
  //HDC  hdc;
  int  i,j;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE*2];

  bw_getread1.deb_record("bw_link::tst_link2()");

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

    sprintf(str3,"ptr=%d,win_bslink0,1,2=%d,%d,%d,bspoin0,1=%d,%d,win_chlink=%s,win_lnktab=%s,"
    ,i,get_win_bslink(i,0)
    ,get_win_bslink(i,1)
    ,get_win_bslink(i,2)
    ,get_win_bspoin(i,0)
    ,get_win_bspoin(i,1)
    ,str1
    ,str2);

    bw_getread1.deb_record(str3);
  }

  return(0);
}
/*
int bw_link::tst_link3()
{
  HDC  hdc;
  int  i,j;
  char str3[SMG_SIZE*2];
  char str1[SMG_SIZE];

  bw_getread1.deb_record("bw_link::tst_link3");

  for (i=0;i<60;i++)
  {
    str1[0]=0;
    for (j=get_win_svpoin(i*5,0);j<get_win_svpoin(i*5,1);j++)
    {
      str1[j-get_win_svpoin(i*5,0)]=get_win_svar(j);
      str1[j-get_win_svpoin(i*5,0)+1]=0;
    }

    sprintf(str3,"win_svpoin1,2=%d,%d,svused=%d,svseri=%d,svbase=%d,svrecn=%d,svwind=%d,svar=%s,"
    ,get_win_svpoin(i*5,0)
    ,get_win_svpoin(i*5,1)
    ,get_win_svused(i*5)
    ,get_win_svseri(i*5)
    ,get_win_svbase(i*5)
    ,get_win_svrecn(i*5)
    ,get_win_svwind(i*5)
    ,str1);

    bw_getread1.deb_record(str3);
  }

  return(0);
}
*/
int bw_link::tst_link4()
{
  //HDC  hdc;
  int  i;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];

  bw_getread1.deb_record("bw_link::tst_link4()");

  for (i=0;i<60;i++)
  {
    get_win_bb1(i,str2,SMG_SIZE);

    sprintf(str1,"ptr=%d,win_bb2bb3bb1=%c,%c,%s,",i,get_win_bb2(i),get_win_bb3(i),str2);

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_link::tst_link5()
{
  //HDC  hdc;
  int  i,j;
  char str1[SMG_SIZE];
  char str3[SMG_SIZE*2];

  bw_getread1.deb_record("bw_link::tst_link5()");

  for (i=0;i<60;i++)
  {
    str1[0]=0;
    for (j=get_win_svpoin(i,0);j<get_win_svpoin(i,1);j++)
    {
      str1[j-get_win_svpoin(i,0)]=get_win_svar(j);
      str1[j-get_win_svpoin(i,0)+1]=0;
    }

    sprintf(str3,"ptr=%d,win_svpoin0,1=%d,%d,svused=%d,svseri=%d,svbase=%d,svrecn=%d,svwind=%d,svar=%s,"
    ,i,get_win_svpoin(i,0)
    ,get_win_svpoin(i,1)
    ,get_win_svused(i)
    ,get_win_svseri(i)
    ,get_win_svbase(i)
    ,get_win_svrecn(i)
    ,get_win_svwind(i)
    ,str1);

    bw_getread1.deb_record(str3);
  }

  return(0);
}

int bw_link::tst_link5_svar()
{
  int  i,j;
  char str1[SMG_SIZE];
  char str3[3000];

  bw_getread1.deb_record("bw_link::tst_link_svar()");

  sprintf(str3,"COND_NUM=%d,",COND_NUM);
  bw_getread1.deb_record(str3);

  for (i=0;i<60;i++)
  {
    str1[0]=0;

    for (j=get_win_svpoin(i,0);j<get_win_svpoin(i,1);j++)
    {
      str1[j-get_win_svpoin(i,0)]=get_win_svar(j);
      str1[j-get_win_svpoin(i,0)+1]=0;
    }

    sprintf(str3,"ptr=%d,win_svpoin0,1=%d,%d,svused=%d,svseri=%d,svbase=%d,svrecn=%d,svwind=%d,svar=%s,"
    ,i
    ,get_win_svpoin(i,0)
    ,get_win_svpoin(i,1)
    ,get_win_svused(i)
    ,get_win_svseri(i)
    ,get_win_svbase(i)
    ,get_win_svrecn(i)
    ,get_win_svwind(i)
    ,str1);

    bw_getread1.deb_record(str3);
  }

  return(0);
}

int bw_link::w_dele_link(int wptr)
{
  int  i,j,k,l,m,n,p,o,q,r,s,t,u,v,w,x,y;

  i=(-1);
  j=(-1);
  n=(-1);
  w=(-1);

  for (k=0;k<COND_NUM;k++)
  {
    if ((get_win_bslink(k,2)==wptr))
    {
      if (i<0) i=k;
      if (j<k) j=k;
    }
    if (get_win_bslink(k,2)>0)
    {
      if (n<k) n=k;
    }
    if ((get_win_bslink(k,2)>0)&&(get_win_bslink(k,2)<wptr))
    {
      if (w<k) w=k;
    }
  }

  if (i>=0)
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
  if (i>=0)
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

      if (get_win_bslink(k,2)-1>0)
	set_win_bslink(k-u,2,get_win_bslink(k,2)-1);
      else
	set_win_bslink(k-u,2,1);
    }

    for (y=m+1;y<=p;y++)
    {
      set_win_lkmodi(y-o,get_win_lkmodi(y));
      set_win_lkseri(y-o,get_win_lkseri(y));
      set_win_lkrecn(y-o,get_win_lkrecn(y));
      set_win_lkbase(y-o,get_win_lkbase(y));

      if (get_win_lkwind(y)-1>0)
	set_win_lkwind(y-o,get_win_lkwind(y)-1);
      else
	set_win_lkwind(y-o,1);
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

      if (get_win_bslink(k,2)-1>0)
	set_win_bslink(k-u,2,get_win_bslink(k,2)-1);
      else
	set_win_bslink(k-u,2,1);
    }

    for (y=x+1;y<=p;y++)
    {
      set_win_lkmodi(y-o,get_win_lkmodi(y));
      set_win_lkseri(y-o,get_win_lkseri(y));
      set_win_lkrecn(y-o,get_win_lkrecn(y));
      set_win_lkbase(y-o,get_win_lkbase(y));

      if (get_win_lkwind(y)-1>0)
	set_win_lkwind(y-o,get_win_lkwind(y)-1);
      else
	set_win_lkwind(y-o,1);
    }
  }

  if (i>=0)
  {
    if (n-j>=0)
    {
      q=i+n-j;
       
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
      q=l+p-m;
              
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

  if ((i>=0)&&(v>0))
  {
    for (k=s+1;k<=t;k++)
    {
      set_win_chlink(k-v,get_win_chlink(k));
    }

    for (k=t-v+1;k<=t;k++) set_win_chlink(k,0);
  }

  return(0);
}

int bw_link::w_dele_svar(int wptr)
{
  int  i,j,k,l,m,n,p,o,q,r;

  i=(-1);
  j=(-1);
  n=(-1);
  r=(-1);

  for (k=0;k<WIN_VAR_NUM;k++)
  {
    if (get_win_svwind(k)==wptr)
    {
      if (i<0) i=k;
      if (j<k) j=k;
    }
    if (get_win_svused(k)>0)
    {
      if (n<k) n=k;
    }
    if ((get_win_svwind(k)>0)&&(get_win_svwind(k)<wptr))
    {
      if (r<k) r=k;
    }
  }

  if (i>=0)
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
  sprintf(str,"p_wptr=%d,%d,lvptr=%d,%d,%d,svptr=%d,%d,%d,"
	     ,wp1,wp2
	     ,i,j,n
	     ,l,m,p);
  MessageBox(bw_main1.win_hwnd1,str,"aa",MB_OK);
*/
  o=m-l;
  if (o<0) o=0;

  if (i>=0)
  {
    for (k=j+1;k<=n;k++)
    {
      set_win_svused(i+k-j-1,get_win_svused(k));
      set_win_svseri(i+k-j-1,get_win_svseri(k));
      set_win_svrecn(i+k-j-1,get_win_svrecn(k));
      set_win_svbase(i+k-j-1,get_win_svbase(k));
      set_win_svwind(i+k-j-1,get_win_svwind(k)-1);

      set_win_svpoin(i+k-j-1,0,get_win_svpoin(k,0)-o);
      set_win_svpoin(i+k-j-1,1,get_win_svpoin(k,1)-o);
    }

    if (n-j>=0)
    {
      q=i+n-j;
       
      for (k=q;k<=n;k++)
      {
	set_win_svused(k,0);
	set_win_svseri(k,0);
	set_win_svrecn(k,0);
	set_win_svbase(k,0);
	set_win_svwind(k,0);

	set_win_svpoin(k,0,0);
	set_win_svpoin(k,1,0);
      }
    }

  }
  else
  {
    for (k=r+1;k<=n;k++)
    {
      set_win_svwind(k,get_win_svwind(k)-1);
    }
  }

  if ((i>=0)&&(o>0))
  {
    for (k=m;k<=p;k++)
    {
      set_win_svar(k-o,get_win_svar(k));
    }

    for (k=p-o+1;k<=p;k++) set_win_svar(k,0);
  }

  return(0);
}

int bw_link::w_read_link(char *p_fn,int p_fn_size,int p_wptr,int num)  //read link file
{
  FILE *fp1;
  int   i,j,k,l;
  char  s_tmps1[SMG_SIZE];

  i=bw_inkey1.strlocc(p_fn,p_fn_size,'.');
  p_fn[i]=0;
  strcat(p_fn,".lin");

  fp1=fopen(p_fn,"r");
  if (fp1==NULL) return(1);

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
    for (j=0;j<SMG_SIZE;j++) s_tmps1[j]=0;
    fgets(s_tmps1,SMG_SIZE,fp1);
    if (bw_inkey1.strempty(s_tmps1)==0) break;
    if (s_tmps1[0]=='&') break;
    k=w_find_link_tn(s_tmps1,SMG_SIZE,p_wptr,i);
    if (k==1)
    {
      fclose(fp1);
      return(1);
    }
    if (feof(fp1)) break;

    for (j=0;j<SMG_SIZE;j++) s_tmps1[j]=0;
    fgets(s_tmps1,SMG_SIZE,fp1);
    if (bw_inkey1.strempty(s_tmps1)==0) break;
    if (s_tmps1[0]=='&') break;
    l=w_find_link_cd(s_tmps1,SMG_SIZE,i,l);
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
int bw_link::w_find_link_tn(char *p_s1,int p_s1_size,int p_wptr,int i) // get table name
{
  int  j,l,m,n;
  int  p1,p2,p3,p4,p5,p6;
  char tn1[FN_SIZE],tn2[FN_SIZE],tn3[FN_SIZE];
  char *kk[8]={"none","multi","single","share",
	       "downright","up","upleft","upright"};
  char stn[FN_SIZE];

  for (j=0;j<p_s1_size;j++) if (p_s1[j]>' ') break;
  if (j>=p_s1_size) return(1);
  p1=j;
  for (j=j;j<p_s1_size;j++) if (p_s1[j]=='>') break;
  if (j>=p_s1_size) return(1);
  p2=j-1;
  p3=j+1;
  for (j=j;j<p_s1_size;j++) if (p_s1[j]<=' ') break;
  if (j>=p_s1_size) return(1);
  p4=j-1;
  for (j=j;j<p_s1_size;j++) if (p_s1[j]>' ') break;
  if (j>=p_s1_size) return(1);
  p5=j;
  for (j=j;j<p_s1_size;j++) if (p_s1[j]<=' ') break;
  if (j>=p_s1_size) return(1);
  p6=j-1;
  bw_inkey1.cut_string(p_s1,p1,p2-p1+1,p_s1_size,tn1,FN_SIZE);
  bw_inkey1.cut_string(p_s1,p3,p4-p3+1,p_s1_size,tn2,FN_SIZE);
  bw_inkey1.cut_string(p_s1,p5,p6-p5+1,p_s1_size,tn3,FN_SIZE);

  for (m=0;m<STRU_NUM;m++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(m,p_wptr)==1)
    {
      bw_win1.get_win_tabname(1,m,stn,FN_SIZE);

      if (strcmp(stn,tn1)==0) break;
    }
  }

  if (m>=STRU_NUM) return(0);

  for (n=0;n<STRU_NUM;n++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(n,p_wptr)==1)
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
  set_win_bslink(i,2,p_wptr);
  bw_xbase1.set_win_lnktab(n,l);

  return(0);
}

int bw_link::w_find_link_cd(char *p_s1,int p_s1_size,int i,int k) // link condition string
{
  int  l,m;
  int  p1,p2;
  char s_tmps1[SMG_SIZE];

  m=k;
  for (l=0;l<p_s1_size;l++) if (p_s1[l]>' ') break;
  if (l>=p_s1_size) return(-1);
  p1=l;
  for (l=l;l<p_s1_size;l++) if (p_s1[l]<=' ') break;
  if (l>=p_s1_size) return(-1);
  p2=l-1;
  bw_inkey1.cut_string(p_s1,p1,p2-p1+1,p_s1_size,s_tmps1,SMG_SIZE);
  l=k;

  if (l+strlen(s_tmps1)>=LINK_CHAR)
  {
    bw_win1.w_atten10();
    return(-1);
  }

  for (k=l;k<=l+(int)strlen(s_tmps1)-1;k++) set_win_chlink(k,s_tmps1[k-l]);

  k=l+strlen(s_tmps1)-1;
  set_win_bspoin(i,0,m);
  set_win_bspoin(i,1,k);

  return(k+1);
}

int bw_link::w_link_modi(int p_wptr)  // fetch link var in cond // and link var if modi // prepare for link
{
  char str1[SMG_SIZE];
  char tn[SMG_SIZE];
  char fn[SMG_SIZE];
  int  i,j;
  int  p1,p2;
  long tr;
  char stn[FN_SIZE];

  for (i=0;i<COND_NUM;i++)
  {
    if (get_win_bslink(i,2)!=p_wptr) continue;

    if (i>=COND_NUM) return(-1);
    if (i>0) p1=get_win_lkpoin(i-1,1)+1;
    else p1=0;

    set_win_lkpoin(i,0,p1);
    p2=get_win_bspoin(i,0);
    while (1)
    {
      p2=w_fetch_link_var(i,p2,str1,SMG_SIZE);
      if (p2<0) break;

      bw_win1.w_fetch_fld_style(str1,SMG_SIZE,tn,SMG_SIZE,&tr,fn,SMG_SIZE,p_wptr);
      if (bw_inkey1.strempty(fn)==0) continue;
      if (bw_inkey1.strempty(tn)==0) continue;

      for (j=0;j<STRU_NUM;j++)
      {
	if (bw_win1.get_win_ptr_wins_dbf(j,p_wptr)==1)
        {
	  bw_win1.get_win_tabname(1,j,stn,FN_SIZE);

	  if (strcmp(stn,tn)==0) break;
        }
      }
      if (j>=STRU_NUM) j=0;

      if (get_win_bslink(i,1)==j) continue;

      w_link_modi_set(tn,SMG_SIZE,fn,SMG_SIZE,p1,p_wptr);

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

int bw_link::w_fetch_link_var(int p1,int p2,char *p_s1,int p_s1_size)
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

    if (exist==1) continue;  /* ca1 no begin */

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
      continue;   /* ca2 begin no end */
    }

    p_s1[0]=0;

    for (l=i;l<k;l++)
    {
      if (l-i+1<p_s1_size)
      {
        p_s1[l-i+0]=get_win_chlink(l);
        p_s1[l-i+1]=0;
      }
    }

    return(k);    /* ca3 begin and end */
  }

  return(-1);
}

int bw_link::w_fetch_link_var2(int p1,int p2,char *p_s1,int p_s1_size)
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

    if (exist==1)                     /* ca1 no begin */
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
      continue;   /* ca2 begin no end */
    }

    p_s1[0]=0;

    for (l=i;l<k;l++)
    {
      if (l-i+1<p_s1_size)
      {
        p_s1[l-i+0]=get_win_chlink(l);
        p_s1[l-i+1]=0;
      }
    }
    return(k);    /* ca3 begin and end */
  }
  return(-1);
}

int bw_link::w_link_modi_set(char *p_tn,int p_tn_size,char *p_fn,int p_fn_size,int p1,int p_wptr)  // prepare for link
{
  int  i,j;
  char stn[FN_SIZE];
  char sfn1[20];

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)
    {
      bw_win1.get_win_tabname(1,i,stn,FN_SIZE);

      if (strcmp(stn,p_tn)==0) break;
    }
  }

  if (i>=STRU_NUM) i=0;

  for (j=bw_fldstru1.get_t2_fldpoin(i,0);j<bw_fldstru1.get_t2_fldpoin(i,1);j++)
  {
    bw_fldstru1.get_t2_fldname(j,sfn1,20);
    if (strcmp(sfn1,p_fn)==0) break;
  }
  if (j>=bw_fldstru1.get_t2_fldpoin(i,1)) j=0;
  else j=j-bw_fldstru1.get_t2_fldpoin(i,0);

  set_win_lkseri(p1,j);
  set_win_lkbase(p1,i);
  set_win_lkwind(p1,p_wptr);
  set_win_lkrecn(p1,0);

  return(0);
}

int bw_link::w_link_modi_mark(int p_wptr,int mark,int seri,int recn)   // if changed ,mark it /* echo win rec ,link rec should change */
{
  int i,j,k;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(i,p_wptr)!=1) continue;
    if ((mark>=0)&&(i!=mark)) continue;

    for (j=0;j<COND_NUM;j++)
    {
      if ((get_win_bslink(j,0)==i)&&(get_win_bslink(j,2)==p_wptr))
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

int bw_link::w_link_modi_unmark(int p_wptr,int mark,int seri,int recn)   /* echo win rec ,link rec should change */
{
  int i,j,k;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_win1.get_win_ptr_wins_dbf(i,p_wptr)!=1) continue;
    if ((mark>=0)&&(i!=mark)) continue;

    for (j=0;j<COND_NUM;j++)
    {
      if ((get_win_bslink(j,0)==i)&&(get_win_bslink(j,2)==p_wptr))
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

int bw_link::w_echo_winrec_lnk(int p_wptr) /* echo win rec where modified */
{
  long s_recno[STRU_NUM];
  int  s_seri[STRU_NUM];
  char s_first[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x;
  int  p1,p2;
  int  exist;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];
  HFONT  holdfont,hfont;
  HDC    hdc;
  HWND   hnd;

  for (i=0;i<STRU_NUM;i++) s_first[i]=1;

  hdc=GetDC(bw_main1.win_hwnd);
  hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  holdfont=(HFONT)SelectObject(hdc,hfont);

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)>0))
    {
      //if (bw_xbase1.get_win_lnktab(i)>0)
      //{
	if (bw_xbase1.get_win_lnktab(i)>1)
	{
	  s_recno[i]=0;
	  bw_xbase1.set_win_recno(i,p_wptr,0,0);
	}
        else
	{
	  if (get_win_continue(i,p_wptr)==1)
	  {
	    s_recno[i]=bw_xbase1.get_win_recno(i,p_wptr,1)-1;
	    set_win_continue(i,p_wptr,0);
	  }
	  else
	  {
	    s_recno[i]=0;
	    bw_xbase1.set_win_recno(i,p_wptr,0,0);
	  }
	}
      //}
      //else s_recno[i]=bw_xbase1.get_win_recno(i,p_wptr,1)-1;
      s_seri[i]=0;
      bw_xbase1.set_win_enseri(i,p_wptr,0);
      bw_xbase1.set_win_cur_seri(i,p_wptr,0);
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
    if (get_win_bslink(r,2)!=p_wptr) continue;
    k=get_win_bslink(r,1);
    s=get_win_bslink(r,0);

    exist=0;

    if (bw_win1.get_win_ptr_wins_dbf(k,p_wptr)!=1) continue;

    if (bw_win1.get_win_ptr_wins_dbf(s,p_wptr)!=1) continue;

    if (w_link_modified(p_wptr,s)!=1) continue;

    w_link_modi_unmark(p_wptr,s,-1,-1);

    w_link_modi_mark(p_wptr,k,-1,-1);

    for (l=1;l<=bw_win1.w_cnt_winline(k,p_wptr,LIN_NUM);l++)
    {
      for (i=1;i<LIN_NUM;i++)
      {
	for (j=1;j<COL_NUM;j++)
	{
	  if (bw_buff1.get_t3_linecol(p_wptr,i,j)!=0)
	  {
	    m=bw_buff1.get_t3_linecol(p_wptr,i,j);

            bw_win1.get_t_fldname(m,str2,SMG_SIZE);

	    if ((str2[0]!=':')&&(str2[0]!='%')&&(str2[0]!='+')) continue;
	    if (bw_win1.get_t_fldbase(m)!=k) continue;
	    if (bw_win1.get_t_fldseri(m)!=l) continue;

	    strcpy(str1,str2);
            bw_inkey1.cut_string(str1,1,strlen(str1)-1,SMG_SIZE,s_fldname,SMG_SIZE);

	    if (s_seri[k]!=bw_win1.get_t_fldseri(m))
	    {
	      while (1)
	      {
		s_recno[k]=bw_mbase1.w_down_rec(k,p_wptr,s_recno[k]);

		if (bw_xbase1.get_win_lnktab(k)==3)
		{
		  u=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
		  if(u>=0) u=bw_win1.get_t_fldseri(u);
		  else u=1;
		}
		else u=bw_win1.get_t_fldseri(m);

		if (w_link_cond_ok(r,p_wptr,k,u,1)==1) break;
		if (bw_xbase1.win_state_dbf_err==1)    break;
	      }
	      s_seri[k]=bw_win1.get_t_fldseri(m);
	      if (bw_xbase1.win_state_dbf_err==0)
	      {
		bw_xbase1.set_win_enseri(k,p_wptr,l);
		if (bw_xbase1.get_win_recno(k,p_wptr,0)<=0)
		{
		  bw_xbase1.set_win_recno(k,p_wptr,0,s_recno[k]);
		}
                exist=1;
	      }
	    }

            if ((l==1)&&(s_first[k]==1))  // set page recno
            {
              bw_xbase1.set_win_recno(k,p_wptr,1,s_recno[k]);
              s_first[k]=0;
            }

		 /* fetch win_field number */
	    n=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	    if (n==1) continue;

	    p=bw_fldstru1.w_find_fldposi(s_fldname,SMG_SIZE,k);
	    q=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,k);

	    v=bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,k);
	    if (v=='m') continue;
            if (v=='b') continue;

            str1[0]=0;

	    for (o=1;o<=q;o++)
            {
              str1[o-1+0]=bw_xbase1.get_win_recvar(p+o-1);
              str1[o-1+1]=0;
	    }

	    strcpy(str3,str1);
            str3[q]=0;

	    str1[q]=0;
	    str1[bw_win1.get_t_fldlen(m)]=0;

            if (bw_win1.get_t_fldlen(m)<q) x=bw_win1.get_t_fldlen(m);
            else x=q;
            w=bw_inkey1.w_chs_string_cut(str1,x);
            str1[w]=0;

            while (w<x)
            {
              strcat(str1," ");
              w++;
            }

	    if ((str2[0]==':')||(str2[0]=='%'))
            {
	      p1=(int)((j-bw_win1.get_win_con(p_wptr,0))*bw_main1.win_edit_xchar);
	      p2=(int)((i-bw_win1.get_win_con(p_wptr,1))*bw_main1.win_edit_ychar);

	      HideCaret(bw_main1.win_hwnd);
	      TextOut(hdc,p1,p2,str1,strlen(str1));
	      ShowCaret(bw_main1.win_hwnd);
	    }
	    else
	    {
	      t=bw_win1.w_find_hnd(p_wptr,j,i);
	      if (t!=0)
	      {
                hnd=bw_win1.get_win_hnd(t);
	        SetWindowText(hnd,str3);
              }
	    }

	    t=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,k);
	    if (t==0)
	    {
	      t=bw_fldstru1.win_field_num;

	      w_save_sv(p_wptr
	                ,k
			,t-bw_fldstru1.get_t2_fldpoin(k,0)
			,bw_win1.get_t_fldseri(m)
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
      bw_xbase1.set_win_recno(k,p_wptr,0,1);
    }
  }

  SelectObject(hdc,holdfont);
  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}

int bw_link::w_link_modified(int p_wptr,int basep)
{
  int i,j;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,0)==basep)&&(get_win_bslink(i,2)==p_wptr))
    {
      for (j=get_win_lkpoin(i,0);j<=get_win_lkpoin(i,1);j++)
	if (get_win_lkmodi(j)==1) return(1);
    }
  }

  return(0);
}

int bw_link::w_link_cond_ok(int condnum,int p_wptr,int basep,int recn,int page)
{
  int  i,j,k;
  int  exist;
  int  p2;
  int  ptr1,ptr2,ptr3,ptr4;
  int  state;
  char tn[SMG_SIZE];
  char fn[SMG_SIZE];
  char str1[SMG_SIZE];
  long tr;
  char stn[FN_SIZE];
  char sv1[SMG_SIZE];
  char sv2[SMG_SIZE];

  i=condnum;

  exist=0;

  if ((get_win_bslink(i,1)==basep)&&(get_win_bslink(i,2)==p_wptr))
  {
    exist=1;
  }

  if (exist==0) return(0);

  ptr1=(-1);  /* base poin */
  ptr2=(-1);  /* fld  seri */
  ptr3=(-1);  /* buff poin */
  ptr4=(-1);  /* calc char poin */
  state=0;
  p2=get_win_bspoin(i,0);     /* load condition */

  while (1)
  {
    p2=w_fetch_link_var2(i,p2,str1,SMG_SIZE);
    if (p2<0) break;

    if (w_is_calc(str1)==1)
    {
      if (state!=1) continue;
      state=0;
      ptr4++;
      set_win_bb2(ptr4,str1[0]);
      continue;
    }

    bw_win1.w_fetch_fld_style(str1,SMG_SIZE,tn,SMG_SIZE,&tr,fn,SMG_SIZE,p_wptr);

    state=1;
    if (bw_inkey1.strempty(tn)==0)
    {
      bw_win1.w_atten13(str1);
      return(0);
    }
    else
    {
      for (j=0;j<STRU_NUM;j++)
      {
	if (bw_win1.get_win_ptr_wins_dbf(j,p_wptr)==1)
        {
	  bw_win1.get_win_tabname(1,j,stn,FN_SIZE);

	  if (strcmp(stn,tn)==0) break;
        }
      }
      if (j>=STRU_NUM) return(0);
      else ptr1=j;
    }

    if (bw_inkey1.strempty(fn)==0)
    {
      bw_win1.w_atten14(str1);
      return(0);
    }
    else
    {
      exist=w_name_in_tab(fn,SMG_SIZE,ptr1);
      if (exist<0)
      {
        bw_win1.w_atten14(str1);
        return(0);
      }
      else ptr2=exist;
    }

    if (ptr1==basep)
    {
      ptr3++;
      if (ptr3>=VAL_NUM)
      {
        bw_win1.w_atten12();
        return(0);
      }

      for (j=1;j<=bw_fldstru1.get_t2_fldlen(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0));j++)
      {
	set_win_cbb1(ptr3,j-1,bw_xbase1.get_win_recvar(bw_fldstru1.get_t2_fldposi(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0))+j-1));
	set_win_cbb1(ptr3,j-0,0);
      }
      set_win_bb3(ptr3,bw_fldstru1.get_t2_fldtype(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0)));

    }
    else
    {
      exist=0;
      for (j=0;j<WIN_VAR_NUM;j++)
      {
	if ((get_win_svwind(j)==p_wptr)&&(get_win_svbase(j)==ptr1)&&(get_win_svseri(j)==ptr2))
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

      ptr3++;
      if (ptr3>=VAL_NUM)
      {
        bw_win1.w_atten12();
        return(0);
      }

      for (k=get_win_svpoin(j,0);k<get_win_svpoin(j,1);k++)
      {
	set_win_cbb1(ptr3,k-get_win_svpoin(j,0),get_win_svar(k));
	set_win_cbb1(ptr3,k-get_win_svpoin(j,0)+1,0);
      }
      set_win_bb3(ptr3,bw_fldstru1.get_t2_fldtype(ptr2+bw_fldstru1.get_t2_fldpoin(ptr1,0)));
    }

    if (ptr3>=1) break;
  }

  get_win_bb1(0,sv1,SMG_SIZE);
  get_win_bb1(1,sv2,SMG_SIZE);

  bw_inkey1.strtrim(sv1,SMG_SIZE);
  bw_inkey1.strtrim(sv2,SMG_SIZE);

  bw_inkey1.strltrim(sv1,SMG_SIZE);
  bw_inkey1.strltrim(sv2,SMG_SIZE);

  if (sv1[0]==0) return(0);
  if (sv2[0]==0) return(0);

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

int bw_link::w_is_calc(char *p_s1)
{
  char ff[10]={'(',')','+','-','*','/','^','|','&','='};
  char c1;
  int  exist;
  int  i;

  exist=0;

  c1=p_s1[0];

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

int bw_link::w_name_in_tab(char *p_str,int p_str_size,int basep)
{
  int  i;
  int  exist;
  char sfn1[20];

  exist=0;

  for (i=bw_fldstru1.get_t2_fldpoin(basep,0);i<bw_fldstru1.get_t2_fldpoin(basep,1);i++)
  {
    bw_fldstru1.get_t2_fldname(i,sfn1,20);
    if (strcmp(sfn1,p_str)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1) return(i-bw_fldstru1.get_t2_fldpoin(basep,0));
  else return(-1);
}

int bw_link::w_scan_sv(int p_wptr)
{
  int  i,j,k,n;
//  int  s_tmpn1,s_tmpn2;
  int  p1,p2;            /* p1 scrn var content poin,p2 scrn var num poin */
  int  exist;
  char str1[FN_SIZE];
  char str2[FN_SIZE];

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if (get_win_svwind(i)==p_wptr) break;
    if (get_win_svused(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

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

  for (i=1;i<LIN_NUM;i++)
  {
    for (j=1;j<COL_NUM;j++)
    {
      if (bw_buff1.get_t3_linecol(p_wptr,i,j)>0)
      {
	n=bw_buff1.get_t3_linecol(p_wptr,i,j);
	if (bw_win1.get_t_fldedt(n)==0)
	{
	  bw_win1.get_t_fldname(n,str2,FN_SIZE);
	  if (strlen(str2)>1) bw_inkey1.cut_string(str2,1,strlen(str2)-1,FN_SIZE,str1,FN_SIZE);
	  else continue;

	  k=w_name_in_tab(str1,FN_SIZE,bw_win1.get_t_fldbase(n));
	  if (k<0) continue;

	  set_win_svpoin(p2,0,p1);
	  set_win_svbase(p2,bw_win1.get_t_fldbase(n));
	  set_win_svseri(p2,k);
	  set_win_svrecn(p2,bw_win1.get_t_fldseri(n));
	  set_win_svwind(p2,p_wptr);
                                                
	  p1=p1+bw_fldstru1.get_t2_fldlen(k+bw_fldstru1.get_t2_fldpoin(bw_win1.get_t_fldbase(n),0));

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

int bw_link::w_save_sv(int p_wptr,int base,int seri,int recn,int posi,int len)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if ((get_win_svwind(i)==p_wptr)&&(get_win_svbase(i)==base)&&(get_win_svseri(i)==seri)&&(get_win_svrecn(i)==recn))
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

int bw_link::w_get_sv(int p_wptr,int base,int seri,int recn,char *p_str,int p_str_size)  /*save scrn var to arr*/
{
  int i,j;
  int exist;

  exist=0;

  for (i=0;i<WIN_VAR_NUM;i++)
  {
    if ((get_win_svwind(i)==p_wptr)&&(get_win_svbase(i)==base)&&(get_win_svseri(i)==seri)&&(get_win_svrecn(i)==recn))
    {
      exist=1;
      break;
    }
  }

  if (exist!=1) return(1);

  p_str[0]=0;

  for (j=get_win_svpoin(i,0);j<get_win_svpoin(i,1);j++)
  {
    if (j-get_win_svpoin(i,0)<p_str_size-1)
    {
      p_str[j-get_win_svpoin(i,0)+0]=get_win_svar(j);
      p_str[j-get_win_svpoin(i,0)+1]=0;
    }
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

int bw_link::w_link_type(int p_wptr,int basep)
{
  int i,j,k;

  j=0;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,2)==p_wptr)&&(get_win_bslink(i,0)==basep))
    {
      k=get_win_bslink(i,1);
      if (k<STRU_NUM) k=bw_xbase1.get_win_lnktab(k);
      else k=0;
      if (k>j) j=k;
    }
  }

  return(j);
}

int bw_link::w_link_number(int p_wptr,int basep)
{
  int i,j;

  j=0;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,2)==p_wptr)&&(get_win_bslink(i,1)==basep))
    {
      j=i;
    }
  }

  return(j);
}

int bw_link::w_link_base_num(int p_wptr,int basep)
{
  int i,j;

  j=0;

  for (i=0;i<COND_NUM;i++)
  {
    if ((get_win_bslink(i,2)==p_wptr)&&(get_win_bslink(i,1)==basep))
    {
      j=get_win_bslink(i,0);
    }
  }

  return(j);
}

int bw_link::w_link_set_continue(int p_wptr,int p_dbptr)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  set_win_continue(p_dbptr,p_wptr,1);
  return(0);
}

int bw_link::w_keep_linkfld(int p_wptr,int p_dbptr,int dir)
{
  int  i,j,k,l,m,n;
  int  exist;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];
  char str4[SMG_SIZE];

  exist=0;

  for (i=0;i<COND_NUM;i++)   
  {
    if ((get_win_bslink(i,1)==p_dbptr)&&(get_win_bslink(i,2)==p_wptr))
    {
      j=get_win_bslink(i,0);
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  k=get_win_lkpoin(i,0);
  l=get_win_lkseri(k);
  w_get_sv(p_wptr,j,l,1,str4,SMG_SIZE);

  for (m=get_win_bspoin(i,0);m<=get_win_bspoin(i,1);m++)
  {
    str1[m-get_win_bspoin(i,0)]=get_win_chlink(m);
  }
  str1[get_win_bspoin(i,1)-get_win_bspoin(i,0)+1]=0;

  n=bw_inkey1.strlocc(str1,SMG_SIZE,'=');
  bw_inkey1.cut_string(str1,n+1,strlen(str1)-n-1,SMG_SIZE,str2,SMG_SIZE);
  n=bw_inkey1.strlocc(str2,SMG_SIZE,'.');
  bw_inkey1.cut_string(str2,n+1,strlen(str2)-n-1,SMG_SIZE,str3,SMG_SIZE);

  bw_xbase1.w_clr_recvar(p_dbptr);
  bw_fldstru1.w_sav_tab_var(str3,SMG_SIZE,p_dbptr,str4,SMG_SIZE);
  bw_mbase1.w_save_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)+dir);
  bw_xbase1.set_win_state_dbf_modi(p_dbptr,1);

  return(0);
}





int bw_link::get_win_svar(int vptr)
{
  if ((vptr<0)||(vptr>=VAR_IN_SCRN)) return(0);
  return(win_svar[vptr]);
}
int bw_link::set_win_svar(int vptr,int val)
{
  if ((vptr<0)||(vptr>=VAR_IN_SCRN)) return(0);
  win_svar[vptr]=val;
  return(0);
}
int bw_link::get_win_svused(int vptr)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  return(win_svused[vptr]);
}
int bw_link::set_win_svused(int vptr,int val)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  win_svused[vptr]=val;
  return(0);
}
int bw_link::get_win_svpoin(int vptr,int p01)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_svpoin[vptr][p01]);
}
int bw_link::set_win_svpoin(int vptr,int p01,int val)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_svpoin[vptr][p01]=val;
  return(0);
}
int bw_link::get_win_svseri(int vptr)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  return(win_svseri[vptr]);
}
int bw_link::set_win_svseri(int vptr,int val)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  win_svseri[vptr]=val;
  return(0);
}
int bw_link::get_win_svrecn(int vptr)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  return(win_svrecn[vptr]);
}
int bw_link::set_win_svrecn(int vptr,int val)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  win_svrecn[vptr]=val;
  return(0);
}
int bw_link::get_win_svbase(int vptr)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  return(win_svbase[vptr]);
}
int bw_link::set_win_svbase(int vptr,int val)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  win_svbase[vptr]=val;
  return(0);
}
int bw_link::get_win_svwind(int vptr)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  return(win_svwind[vptr]);
}
int bw_link::set_win_svwind(int vptr,int val)
{
  if ((vptr<0)||(vptr>=WIN_VAR_NUM)) return(0);
  win_svwind[vptr]=val;
  return(0);
}
int bw_link::get_win_chlink(int lptr)
{
  if ((lptr<0)||(lptr>=LINK_CHAR)) return(0);
  return(win_chlink[lptr]);
}
int bw_link::set_win_chlink(int lptr,int val)
{
  if ((lptr<0)||(lptr>=LINK_CHAR)) return(0);
  win_chlink[lptr]=val;
  return(0);
}
int bw_link::get_win_bslink(int dptr,int p02)
{
  if ((dptr<0)||(dptr>=COND_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(win_bslink[dptr][p02]);
}
int bw_link::set_win_bslink(int dptr,int p02,int val)
{
  if ((dptr<0)||(dptr>=COND_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  win_bslink[dptr][p02]=val;
  return(0);

}
int bw_link::get_win_bspoin(int dptr,int p01)
{
  if ((dptr<0)||(dptr>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_bspoin[dptr][p01]);
}
int bw_link::set_win_bspoin(int dptr,int p01,int val)
{
  if ((dptr<0)||(dptr>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_bspoin[dptr][p01]=val;
  return(0);
}
int bw_link::get_win_lkpoin(int cptr,int p01)
{
  if ((cptr<0)||(cptr>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_lkpoin[cptr][p01]);
}
int bw_link::set_win_lkpoin(int cptr,int p01,int val)
{
  if ((cptr<0)||(cptr>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_lkpoin[cptr][p01]=val;
  return(0);
}
int bw_link::get_win_lkmodi(int lptr)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  return(win_lkmodi[lptr]);
}
int bw_link::set_win_lkmodi(int lptr,int val)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  win_lkmodi[lptr]=val;
  return(0);
}
int bw_link::get_win_lkseri(int lptr)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  return(win_lkseri[lptr]);
}
int bw_link::set_win_lkseri(int lptr,int val)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  win_lkseri[lptr]=val;
  return(0);
}
int bw_link::get_win_lkbase(int lptr)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  return(win_lkbase[lptr]);
}
int bw_link::set_win_lkbase(int lptr,int val)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  win_lkbase[lptr]=val;
  return(0);
}
int bw_link::get_win_lkrecn(int lptr)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  return(win_lkrecn[lptr]);
}
int bw_link::set_win_lkrecn(int lptr,int val)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  win_lkrecn[lptr]=val;
  return(0);
}
int bw_link::get_win_lkwind(int lptr)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  return(win_lkwind[lptr]);
}
int bw_link::set_win_lkwind(int lptr,int val)
{
  if ((lptr<0)||(lptr>=LINK_MODI_NUM)) return(0);
  win_lkwind[lptr]=val;
  return(0);
}
int bw_link::get_win_continue(int p_dbptr,int p_wptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(win_continue[p_dbptr][p_wptr]);
}
int bw_link::set_win_continue(int p_dbptr,int p_wptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  win_continue[p_dbptr][p_wptr]=val;
  return(0);
}
int bw_link::set_win_cbb1(int vptr,int ptr1,int val)
{
  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  win_bb1[vptr][ptr1]=val;
  return(0);
}
int bw_link::get_win_bb1(int vptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_bb1[vptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_link::set_win_bb1(int vptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  win_bb1[vptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_bb1[vptr][j+0]=p_s1[j];
    win_bb1[vptr][j+1]=0;
  }

  return(0);
}
int bw_link::get_win_bb2(int vptr)
{
  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);
  return(win_bb2[vptr]);
}
int bw_link::set_win_bb2(int vptr,int val)
{
  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);
  win_bb2[vptr]=val;
  return(0);
}
int bw_link::get_win_bb3(int vptr)
{
  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);
  return(win_bb3[vptr]);
}
int bw_link::set_win_bb3(int vptr,int val)
{
  if ((vptr<0)||(vptr>=VAL_NUM)) return(0);
  win_bb3[vptr]=val;
  return(0);
}

