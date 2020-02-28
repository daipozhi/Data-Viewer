/*
#define STRICT
*/
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

extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;

int bw_mbase::w_ins_rec(int p_fcnt,int wpp,long recno)
{
  unsigned char c1,c2,c3,c4,c5;
  int           s_state1;
  int           i=0,j;
  long          li;
  unsigned char str[FN_SIZE];
  unsigned char str2[SMG_SIZE];

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    bw_xbase1.win_state_dbf_err=0;

    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==0)
    {
      s_state1=bw_xbase1.w_insert_xbase_rec(recno,p_fcnt,1);
      return(s_state1);
    }
    else
    {
      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);  // get rec no , and insert
      j=read(bw_xbase1.win_fp2[wpp],str,5);

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      c5=str[4];

      if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5)
      {
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(1);
      }

      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_insert_xbase_rec(li,p_fcnt,1);

/*    w_find_recno_ins(recno);*/

      while (1)
      {
	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);  // read current rec
	j=read(bw_xbase1.win_fp2[wpp],str2,5);

	if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5) i=1;

	li++;
        c1=(unsigned char )(li/256/256/256);
        c2=(unsigned char )((li-c1*256*256*256)/256/256);
        c3=(unsigned char )((li-c1*256*256*256-c2*256*256)/256);
        c4=(unsigned char )(li-c1*256*256*256-c2*256*256-c3*256);

        str[0]=c4;
        str[1]=c3;
        str[2]=c2;
        str[3]=c1;
        str[4]=c5;

	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);  // rewriter current rec with prev rec , rec no +1
	write(bw_xbase1.win_fp2[wpp],str,5);

	if (i==1)
        {
          write(bw_xbase1.win_fp2[wpp],"  ",2);
          return(0);
        }

	c1=str2[0];				// generate next rec no
        c2=str2[1];
        c3=str2[2];
	c4=str2[3];
        c5=str2[4];

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
  unsigned char c1,c2,c3,c4,c5;
//  int           s_state1;
  int           i=0,j;
  long          li;
  //long          recno;
  unsigned char str[FN_SIZE];
  unsigned char str2[SMG_SIZE];

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    bw_xbase1.win_state_dbf_err=0;

    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==0)
    {
      li=bw_xbase1.w_insert_xbase_rec(recno,p_fcnt,0);
      return(li);
    }
    else
    {
      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);  // get rec no , and insert
      j=read(bw_xbase1.win_fp2[wpp],str,5);

      c1=str[0];
      c2=str[1];
      c3=str[2];
      c4=str[3];
      c5=str[4];

      if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5)
      {
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(1);
      }

      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_insert_xbase_rec(li,p_fcnt,0);

      while (1)
      {
	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);  // read current rec
	j=read(bw_xbase1.win_fp2[wpp],str2,5);

	if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5) i=1;

	li++;
        c1=(unsigned char )(li/256/256/256);
        c2=(unsigned char )((li-c1*256*256*256)/256/256);
        c3=(unsigned char )((li-c1*256*256*256-c2*256*256)/256);
        c4=(unsigned char )(li-c1*256*256*256-c2*256*256-c3*256);

        str[0]=c4;
        str[1]=c3;
        str[2]=c2;
        str[3]=c1;
        str[4]=c5;

	lseek(bw_xbase1.win_fp2[wpp],recno*5,0);  // rewriter current rec with prev rec , rec no +1
	write(bw_xbase1.win_fp2[wpp],str,5);

	if (i==1)
        {
          write(bw_xbase1.win_fp2[wpp],"  ",2);
          return(0);
        }

	c1=str2[0];				// generate next rec no
        c2=str2[1];
        c3=str2[2];
	c4=str2[3];
        c5=str2[4];

	li=c4*256*256*256+c3*256*256+c2*256+c1;
        
        recno++;
      }
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
  unsigned char   str[FN_SIZE];

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    bw_xbase1.win_state_dbf_err=0;
    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==0)
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

      if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5)
      {
        bw_xbase1.w_clr_recvar(p_fcnt);
        return(1);
      }

      li=c4*256*256*256+c3*256*256+c2*256+c1;

      bw_xbase1.w_dele_xbase_rec(li,p_fcnt);

      str[4]='*';
      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      write(bw_xbase1.win_fp2[wpp],str,5);

      return(0);
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
  unsigned char str[SMG_SIZE];
  long          li;

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==0)
    {
      i=bw_xbase1.w_save_xbase_rec(recno,p_fcnt);
      return(i);
    }
    else
    {
      if (recno<1) recno=1;

      lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
      j=read(bw_xbase1.win_fp2[wpp],str,5);

      if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5)
      {
        bw_xbase1.win_state_dbf_err=1;
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
  int           j=0;
  long          li;
  unsigned char str[SMG_SIZE];
  unsigned char c1,c2,c3,c4;

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==0)
    {
      li=bw_xbase1.w_down_xbase_rec(recno,p_fcnt);
      return(li);
    }
    else
    {
      if (recno<0) recno=0;

      while(1)
      {
        recno++;

        lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
        j=read(bw_xbase1.win_fp2[wpp],str,5);

        if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5) break;
        if (str[4]=='*') continue;
        break;
      }

      if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5)
      {
        bw_xbase1.win_state_dbf_err=1;
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
  int           j=0;
  long          li;
  unsigned char str[SMG_SIZE];
  unsigned char c1,c2,c3,c4;

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==0)
    {
      li=bw_xbase1.w_up_xbase_rec(recno,p_fcnt);
      return(li);
    }
    else
    {
      while(1)
      {
        if (recno>1) recno--;
        else
        {
          bw_xbase1.win_state_dbf_err=1;
          bw_xbase1.w_clr_recvar(p_fcnt);
          return(recno);
        }

        lseek(bw_xbase1.win_fp2[wpp],(recno-1)*5,0);
        j=read(bw_xbase1.win_fp2[wpp],str,5);

        if (str[4]=='*') continue;
        break;
      }

      if (/*eof(bw_xbase1.win_fp2[wpp])*/j<5)
      {
        bw_xbase1.win_state_dbf_err=1;
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
//  char str[SMG_SIZE];
//  char str2[SMG_SIZE];
  char st1[FN_SIZE];
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char sc1[FN_SIZE];
  char sd1[FN_SIZE];
  int  i,j,k,l;
//  long li;

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    if (bw_xbase1.get_win_state_in_srch(wpp,p_fcnt)==1)
    {
      close(bw_xbase1.win_fp2[wpp]);

      bw_win1.get_win_window_name(wpp,s_fn1,FN_SIZE);
      i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
      s_fn1[i]=0;
      bw_xbase1.get_win_fext(wpp,sd1,EXT_LEN);
      strcat(s_fn1,sd1);

      bw_xbase1.get_win_basedir(p_fcnt,st1,FN_SIZE);

      bw_inkey1.w_set_dir(st1);

      bw_inkey1.w_del_file(s_fn1);

      bw_xbase1.set_win_state_in_srch(wpp,p_fcnt,0);
    }

    bw_xbase1.w_close_xbase(p_fcnt);
  }

  return(0);
}

int bw_mbase::w_open_base(char *p_bn,int p_bn_size,int p_fcnt)
{
//  HDC  hdc;
  int  l,m,o;
  char str[FN_SIZE];
  //char stc[FN_SIZE];
//  char c1;

  if (bw_xbase1.get_win_base_type(p_fcnt)==0)
  {
    o=bw_xbase1.get_win_base_backup(p_fcnt);

    m=bw_xbase1.w_open_xbase(p_bn,p_bn_size,o,p_fcnt);
    if (m!=0) return(1);
  }

  return(0);
}

