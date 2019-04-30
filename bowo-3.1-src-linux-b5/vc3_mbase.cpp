#define _CRT_SECURE_NO_WARNINGS

//#define STRICT
#include "windows.h"
/*
#include <commdlg.h>
*/
#include <stdio.h>
/*
#include <math.h>
#include <direct.h>
#include <dos.h>
#include <io.h>
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

extern class bw_xbase_bua    bw_xbase_bua1;
extern class bw_win_bub      bw_win_bub1;
extern class bw_win_bua      bw_win_bua1;
extern class bw_win          bw_win1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;

int bw_mbase::w_ins_rec(int p_fcnt,int wpp,long recno)
{
  unsigned char c1,c2,c3,c4;
  int           s_state1;
  int           i=0,j;
  long          li;
  char          str[FN_SIZE];
  char          str2[SMG_LEN];

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)==0)
  {
    bw_xbase1.win_state3=0;

    if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==0)
    {
      s_state1=bw_xbase1.w_insert_xbase_rec(recno,p_fcnt,1);
      return(s_state1);
    }
    else
    {
      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      j=read(bw_xbase1.win_fp2[wpp],str,5);

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      //if (eof(bw_xbase1.win_fp2[wpp]))
      if (j<5)
      {
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(1);
      }

      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_insert_xbase_rec(li,p_fcnt,1);

/*    w_find_recno_ins(recno);*/
      while (1)
      {
	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);
	j=read(bw_xbase1.win_fp2[wpp],str2,5);

	//if (eof(bw_xbase1.win_fp2[wpp])) i=1;
        if (j<5) i=1;

	li++;
        c1=(unsigned char )(li/256/256/256);
        c2=(unsigned char )((li-c1*256*256*256)/256/256);
        c3=(unsigned char )((li-c1*256*256*256-c2*256*256)/256);
        c4=(unsigned char )(li-c1*256*256*256-c2*256*256-c3*256);

        str[0]=c4;
        str[1]=c3;
        str[2]=c2;
        str[3]=c1;
        str[4]=0;

	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);
	write(bw_xbase1.win_fp2[wpp],str,5);

	if (i==1)
        {
          write(bw_xbase1.win_fp2[wpp],"  ",2);
          return(0);
        }

	c1=str2[0];
        c2=str2[1];
        c3=str2[2];
	c4=str2[3];

	li=c4*256*256*256+c3*256*256+c2*256+c1;
        
        recno++;
      }
    }
  }
  else
  {
    bw_xbase1.w_clr_recvar(p_fcnt);
    return(1);
  }
}

long bw_mbase::w_add_rec(int p_fcnt,int wpp,long recno)
{
  unsigned char c1,c2,c3,c4;
//  int           s_state1;
  int           j;
  long          li;
  //long          recno;
  char          str[FN_SIZE];
  char          str2[SMG_LEN];

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)==0)
  {
    bw_xbase1.win_state3=0;

    if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==0)
    {
      li=bw_xbase1.w_insert_xbase_rec(recno,p_fcnt,0);
      return(li);
    }
    else
    {
      recno=0;
      
      li=bw_xbase1.w_insert_xbase_rec(recno,p_fcnt,0);

      while (1)
      {
	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);
	j=read(bw_xbase1.win_fp2[wpp],str2,5);

	//if (eof(bw_xbase1.win_fp2[wpp])) break;
        if (j<5) break;

        recno++;
      }

      c1=(unsigned char )(li/256/256/256);
      c2=(unsigned char )((li-c1*256*256*256)/256/256);
      c3=(unsigned char )((li-c1*256*256*256-c2*256*256)/256);
      c4=(unsigned char )(li-c1*256*256*256-c2*256*256-c3*256);

      str[0]=c4;
      str[1]=c3;
      str[2]=c2;
      str[3]=c1;
      str[4]=0;

      lseek(bw_xbase1.win_fp2[wpp],recno*5,0);
      write(bw_xbase1.win_fp2[wpp],str,5);

      write(bw_xbase1.win_fp2[wpp],"  ",2);
      return(recno);
    }
  }
  else
  {
    bw_xbase1.w_clr_recvar(p_fcnt);
    return(-1);
  }
}

int bw_mbase::w_del_rec(int p_fcnt,int wpp,long recno)
{
  unsigned char c1,c2,c3,c4;
  int           s_state1;
  int           j;
  long          li;
//  int           s_fp1;
//  char          s_fn1[FN_SIZE];
//  char          s_fn2[FN_SIZE];
  char          str[FN_SIZE];

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)==0)
  {
    bw_xbase1.win_state3=0;
    if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==0)
    {
      s_state1=bw_xbase1.w_dele_xbase_rec(recno,p_fcnt);
      return(s_state1);
    }
    else
    {
      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      j=read(bw_xbase1.win_fp2[wpp],str,5);

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      //if (eof(bw_xbase1.win_fp2[wpp]))
      if (j<5)
      {
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(1);
      }

      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_dele_xbase_rec(li,p_fcnt);

/*    w_find_recno_del(recno);*/
      while (1)
      {
	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);
	j=read(bw_xbase1.win_fp2[wpp],str,5);
/*
	//if (eof(bw_xbase1.win_fp2[wpp]))
        if (j<5)
	{
	  chsize(bw_xbase1.win_fp2[wpp],(recno-1)*5+1);
	  return(0);
	}
*/
	lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
	write(bw_xbase1.win_fp2[wpp],str,5);

        recno++;
      }
    }
  }
  else
  {
    bw_xbase1.w_clr_recvar(p_fcnt);
    return(1);
  }
}

int  bw_mbase::w_save_rec(int p_fcnt,int wpp,long recno)
{
  unsigned char c1,c2,c3,c4;
  int           i,j;
  char          str[SMG_LEN];
  long          li;

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==0)
    {
      i=bw_xbase1.w_save_xbase_rec(recno,p_fcnt);
      return(i);
    }
    else
    {
      if (recno<1) recno=1;

      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      j=read(bw_xbase1.win_fp2[wpp],str,5);
      //if (eof(bw_xbase1.win_fp2[wpp]))
      if (j<5)
      {
        bw_xbase1.win_state3=1;
        bw_xbase1.w_clr_recvar(p_fcnt);
	return(1);
      }

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      li=c4*256*256*256+c3*256*256+c2*256+c1;

      i=bw_xbase1.w_save_xbase_rec(li,p_fcnt);
      return(recno);
    }
  }
  else
  {
    bw_xbase1.w_clr_recvar(p_fcnt);
    return(1);
  }
}

long bw_mbase::w_down_rec(int p_fcnt,int wpp,long recno)
{
  long          li;
  char          str[SMG_LEN];
  unsigned char c1,c2,c3,c4;
  int           j;

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==0)
    {
      li=bw_xbase1.w_down_xbase_rec(recno,p_fcnt);
      return(li);
    }
    else
    {
      if (recno<1) recno=0;
      recno++;

      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      j=read(bw_xbase1.win_fp2[wpp],str,5);
      //if (eof(bw_xbase1.win_fp2[wpp]))
      if (j<5)
      {
        bw_xbase1.win_state3=1;
        bw_xbase1.w_clr_recvar(p_fcnt);
	return(recno);
      }

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_read_xbase_rec(li,p_fcnt);
      return(recno);
    }
  }
  else
  {
    bw_xbase1.w_clr_recvar(p_fcnt);
    return(recno);
  }
}

long bw_mbase::w_up_rec(int p_fcnt,int wpp,long recno)
{
  long          li;
  char          str[SMG_LEN];
  unsigned char c1,c2,c3,c4;
  int           j;

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==0)
    {
      li=bw_xbase1.w_up_xbase_rec(recno,p_fcnt);
      return(li);
    }
    else
    {
      if (recno>1) recno--;
      else
      {
        bw_xbase1.win_state3=1;
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(recno);
      }

      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      j=read(bw_xbase1.win_fp2[wpp],str,5);
      //if (eof(bw_xbase1.win_fp2[wpp]))
      if (j<5)
      {
        bw_xbase1.win_state3=1;
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(recno);
      }

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_read_xbase_rec(li,p_fcnt);
      return(recno);
    }
  }
  else
  {
    bw_xbase1.w_clr_recvar(p_fcnt);
    return(recno);
  }
}
int bw_mbase::w_close_base(int p_fcnt,int wpp)
{
//  HDC  hdc;
//  char str[SMG_LEN];
//  char str2[SMG_LEN];
  char st1[FN_SIZE];
  int  i,l;
//  long li;

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)!=0) return(1);

  l=p_fcnt;

  if (bw_xbase_bua1.get_win_state1(l)!=1) return(1);

  if (bw_xbase_bua1.get_win_state5(l)==1)
  {
    bw_xbase_bua1.get_win_basename(l,st1,FN_SIZE);

    i=bw_win1.w_atten9(st1);

    if (i==2) w_mrollback_base(l,wpp);

    bw_xbase_bua1.set_win_state5(l,0);
  }

  bw_xbase1.w_close_xbase(l);

  return(0);
}
int bw_mbase::w_open_base(char *p_bn,int len,int p_fcnt)
{
//  HDC  hdc;
  int  i,j,l,m,o;
  char str[FN_SIZE];
  //char stc[FN_SIZE];
//  char c1;
/*
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=bn[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/

  //printf("111\n");

  if (bw_xbase_bua1.get_win_base_type(p_fcnt)!=0) return(1);

  //printf("222\n");

  o=bw_xbase_bua1.get_win_base_backup(p_fcnt);

  l=p_fcnt;

  m=bw_xbase1.w_open_xbase(p_bn,len,o,l);

  if (m!=0) return(1);

  //printf("333\n");

  getcwd(str,FN_SIZE);
  bw_xbase_bua1.set_win_basedir(l,str,FN_SIZE);
  bw_xbase_bua1.set_win_basename(l,p_bn,len);

  return(0);
}

int bw_mbase::w_mrollback_base(int p_fcnt,int wpp)
{
  int  i;
  int  p1;
  char s_fn1[FN_SIZE];
//  char s_fn2[FN_SIZE];
  char st1[FN_SIZE];
  char stn[FN_SIZE];
  char sd1[EXT_LEN];

  if (bw_xbase_bua1.get_win_state5(p_fcnt)==0) return(0);

  bw_win_bub1.get_win_tabname(1,p_fcnt,stn,FN_SIZE);

  bw_xbase1.w_rollback_xbase(stn,FN_SIZE,bw_xbase_bua1.get_win_base_backup(p_fcnt),p_fcnt);

  bw_xbase_bua1.set_win_state5(p_fcnt,0);

  if (wpp<=0) return(0);

  for (p1=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0)
      ;p1<=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),2)
      ;p1++)
  {
    if (bw_xbase_bua1.get_win_state9(p1,p_fcnt)==1)
    {
      close(bw_xbase1.win_fp2[p1]);
      bw_xbase_bua1.set_win_state9(p1,p_fcnt,0);

      bw_win_bub1.get_win_window_name(p1,s_fn1,FN_SIZE);
      i=bw_inkey1.strlocc(s_fn1,'.');
      s_fn1[i]=0;
      bw_xbase_bua1.get_win_fext(p1,sd1,EXT_LEN);
      strcat(s_fn1,sd1);

      bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

      bw_inkey1.w_set_dir(st1);

      bw_inkey1.w_del_file(s_fn1);
    }
  }

  return(0);
}

