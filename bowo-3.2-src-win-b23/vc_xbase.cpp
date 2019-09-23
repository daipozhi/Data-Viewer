/* 
 DEC VAX/VMS error 1: fseek() don't clear feof() ,use clearerr()
*/
/* 
 DEC VAX/VMS error 2: there is error when program continue fputc 300 times,
	      use fputs
*/
/*   
  motorola unix system V 
   1.  when define extern function do not use param
   2.  when define function param, not allow ss(int i,int j)
       must like this 
	 ss(i,j)
	 int i,j;
*/

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
#include <stdio.h>
#include <time.h>

#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>

#include "vc_bowo.h"

extern class bw_mbase        bw_mbase1;
extern class bw_main         bw_main1;
extern class bw_inkey        bw_inkey1;
extern class bw_win          bw_win1;
extern class bw_fldstru      bw_fldstru1;

/*
int bw_xbase::get_xbase_open(int p_fcnt,char *p_s1,int p_s1_len,char *p_s2,int p_s2_len)
{
  int  i,j;
//  char str[SMG_LEN];

  if (get_win_state1(p_fcnt)!=0) return(1);

  bw_win1.set_win_tabname(1,p_fcnt,p_s1,p_s1_len);
  bw_win1.set_win_tabname(0,p_fcnt,p_s2,p_s2_len);

  set_win_state1(p_fcnt,1);
  set_win_base_backup(p_fcnt,1);

  i=bw_fldstru1.w_read_stru(p_s2,p_s2_len,p_fcnt);
  j=bw_mbase1.w_open_base(p_s1,p_s1_len,p_fcnt);

  if ((i!=0)||(j!=0)) return(1);
  else return(0);
}
*/
/*
int bw_xbase::get_xbase_close(int p_fcnt)
{
  char str1[SMG_LEN];
  int  i;

  bw_fldstru1.w_dele_stru(p_fcnt);

  if (get_win_state5(p_fcnt)==1)
  {
    get_win_basename(p_fcnt,str1,SMG_LEN);

    i=bw_win1.w_atten9(str1);
    if (i==2)
    {
      bw_win1.get_win_tabname(1,p_fcnt,str1,SMG_LEN);
      w_rollback_xbase(str1,SMG_LEN,get_win_base_backup(p_fcnt),p_fcnt);
    }
    else w_commit_xbase(p_fcnt);

    set_win_state5(p_fcnt,0);
  }

  w_close_xbase(p_fcnt);

  return(0);
}
*/
int bw_xbase::tst_xbase1()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char st1[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_ext(i,st1,FN_SIZE);

    sprintf(str,"recno012=%ld,%ld,%ld,%ld,%ld,%ld,cuseri12345=%d,%d,%d,%d,%d,rcnt=%ld,lcnt01=%d,%d,ext=%s,lnktab=%d,"
	       ,get_win_recno(i,1,0)
	       ,get_win_recno(i,1,1)
	       ,get_win_recno(i,1,2)
	       ,get_win_recno(i,2,0)
	       ,get_win_recno(i,2,1)
	       ,get_win_recno(i,2,2)
	       ,get_win_cuseri(i,1)
	       ,get_win_cuseri(i,2)
	       ,get_win_cuseri(i,3)
	       ,get_win_cuseri(i,4)
	       ,get_win_cuseri(i,5)
	       ,get_win_rcnt(i)
	       ,get_win_lcnt(i,0)
	       ,get_win_lcnt(i,1)
	       ,st1
	       ,get_win_lnktab(i));
    TextOut(hdc,1,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_xbase::tst_xbase2()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);
  for (i=0;i<STRU_NUM;i++)
  {
    sprintf(str,"state1357=%d,%d,%d,%d,type=%d,backup=%d,"
	       ,get_win_state1(i)
	       ,win_state3
	       ,get_win_state5(i)
	       ,get_win_state7(i,0)
	       ,get_win_base_type(i)
	       ,get_win_base_backup(i));
    TextOut(hdc,1,i*20,str,strlen(str));
  }
  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_xbase::w_login_xbase(int pp1)
{
  int i;
  int exist;

  exist=0;

  for (i=pp1;i<STRU_NUM;i++)
  {
    if (get_win_state1(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1) return(i);
  else return(-1);
}

int bw_xbase::w_free_xbase(void)
{
  int i;
  int exist;

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_win_state1(i)==0)
    {
      exist++;
    }
  }

  return(exist);
}

int bw_xbase::w_dele_state(int p_fcnt)
{         
  int j;

  for (j=1;j<WIN_NUM;j++)
  {
    set_win_recno(p_fcnt,j,0,0);
    set_win_recno(p_fcnt,j,1,0);
    set_win_recno(p_fcnt,j,2,0);

    set_win_state7(p_fcnt,j,0);
  }

  set_win_rcnt(p_fcnt,0);
  set_win_lcnt(p_fcnt,0,0);
  set_win_lcnt(p_fcnt,1,0);

  set_win_lnktab(p_fcnt,0);

  set_win_state1(p_fcnt,0);
  set_win_state5(p_fcnt,0);

  setc_win_ext(p_fcnt,0,0);
  setc_win_basedir(p_fcnt,0,0);
  setc_win_basename(p_fcnt,0,0);

  return(0);
}

int bw_xbase::w_open_xbase(char *p_fn1,int p_fn1_len,int backup,int p_fcnt)
{
  char          s_fn1[FN_SIZE];
  char          s_fn2[FN_SIZE];
  char          s_fn3[FN_SIZE];
  //char          s_fn4[FN_SIZE];
//  char          str[SMG_LEN];
  int           i,j;
  int           s_state1,s_state2;
  char          st1[FN_SIZE];

  strcpy(s_fn1,p_fn1);
  bw_inkey1.strtrim(s_fn1,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  strcat(s_fn1,".dbf");

  while(1)
  {
    win_fp[p_fcnt]=sopen(s_fn1,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
    if (win_fp[p_fcnt]<0)
    {
      if (bw_inkey1.w_find_file(s_fn1)==1)
      {
        s_state1=bw_win1.w_atten8(s_fn1);   /* open error */
        if (s_state1==1) continue;          /* retry      */
	else return(1);                     /* cancel     */
      }
      else
      {
		s_state1=bw_win1.w_atten9a(s_fn1); // dbf file not exist
		if (s_state1==0) continue; //cancel
		else
		{
			if (s_state1==1)  // yes,create
			{
				i=w_create_xbase(s_fn1,FN_SIZE,p_fcnt);
				if (i!=0) return(1);
				else continue;
			}
			else return(1);  // no,not create
		}
      }
    }
    else break;                   /* open success */
  }

  s_state1=w_compare_xbase(win_fp[p_fcnt],p_fcnt);
  if (s_state1==1)
  {
    s_state2=bw_win1.w_atten18(s_fn1);
    if (s_state2==2) return(1);
    else
    {
      strcpy(s_fn3,s_fn1);
      i=bw_inkey1.strlocc(s_fn3,FN_SIZE,'.');
      s_fn3[i]=0;
      strcat(s_fn3,".dbk");
      bw_inkey1.w_del_file(s_fn3);
      bw_inkey1.w_cpy_file(s_fn1,s_fn3);
      i=w_create_xbase(s_fn1,FN_SIZE,p_fcnt);
      if (i!=0) return(1);
      j=w_use_fox(s_fn3,FN_SIZE);
      if (j!=0) return(1);
      w_append_fox(p_fcnt);
      w_close_fox();
    }
  }

  if (get_win_rcnt(p_fcnt)<=0)
  {
	  w_insert_xbase_rec2(p_fcnt); // add 3 empty record to empty xbase file to avoid error 
  }

  if (backup==1)
  {
    strcpy(s_fn2,s_fn1);
    w_find_empty_file(s_fn2,FN_SIZE,p_fcnt);

    strcpy(s_fn2,s_fn1);
    i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
    s_fn2[i]=0;
    get_win_ext(p_fcnt,st1,FN_SIZE);
    strcat(s_fn2,st1);

    bw_inkey1.w_del_file(s_fn2);

    s_state1=bw_inkey1.w_cpy_file(s_fn1,s_fn2);
    if (s_state1==1) return(1);

    close(win_fp[p_fcnt]);

    win_fp[p_fcnt]=sopen(s_fn2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
    if (win_fp[p_fcnt]<0) return(1);

  }

  set_win_state1(p_fcnt,1);

  return(0);
}
long bw_xbase::w_read_recno(int fp)
{
  char str[SMG_LEN];
  int  c1,c2,c3,c4;
  long rn;

  lseek(fp,4,0);
  read(fp,str,10);
  c4=str[0];
  c3=str[1];
  c2=str[2];
  c1=str[3];
  rn=c1*256*256*256+c2*256*256+c3*256+c4;

  return(rn);
}
int bw_xbase::w_create_xbase(char *p_fn1,int p_fn1_len,int p_fcnt)
{
  int           i,j,k;
  int           s_fp1;
  char          s_tmpc1[16+1];
//  int           s_state1;
  unsigned int  s_tmpn1;
  unsigned char c1,c2,c3,c4;
  char          str[SMG_LEN];
  //char          s_fn4[FN_SIZE];

  s_fp1=sopen(p_fn1,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_fp1<0) return(1);

  j=get_win_lcnt(p_fcnt,0);   /* write head line 1 */
  s_tmpn1=(j+1)*32+1;
  c1=s_tmpn1/256;
  c2=s_tmpn1-c1*256;
  s_tmpn1=get_win_lcnt(p_fcnt,1);
  s_tmpn1++;
  c3=s_tmpn1/256;
  c4=s_tmpn1-c3*256;
  for (i=0;i<=16;i++) s_tmpc1[i]=0;
  s_tmpc1[0]=3;
  s_tmpc1[1]=94;
  s_tmpc1[2]=5;
  s_tmpc1[3]=25;
  s_tmpc1[8]=c2;
  s_tmpc1[9]=c1;
  s_tmpc1[10]=c4;
  s_tmpc1[11]=c3;
  write(s_fp1,s_tmpc1,16);
  for (i=0;i<=15;i++) s_tmpc1[i]=0;
  write(s_fp1,s_tmpc1,16);

  s_tmpn1=1;
  for (i=bw_fldstru1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru1.setc_t2_fldname(i,10,0);
    bw_fldstru1.get_t2_fldname(i,str,20);
    for (k=0;k<=9;k++) str[k]=bw_inkey1.upper(str[k]);
    write(s_fp1,str,11);
    if (bw_fldstru1.get_t2_fldtype(i)=='c') str[0]='C';
    else
    {
      if (bw_fldstru1.get_t2_fldtype(i)=='m') str[0]='M';
      else
      {
	if (bw_fldstru1.get_t2_fldtype(i)=='l') str[0]='L';
	else
	{
	  if (bw_fldstru1.get_t2_fldtype(i)=='b') str[0]='B';
	  else  str[0]='N';
        }
      }
    }
    write(s_fp1,str,1);
    c1=s_tmpn1/256;
    c2=s_tmpn1-c1*256;
    str[0]=c2;
    str[1]=c1;
    str[2]=0;
    str[3]=0;
    s_tmpn1=s_tmpn1+bw_fldstru1.get_t2_fldlen(i);
    write(s_fp1,str,4);
    c1=bw_fldstru1.get_t2_fldlen(i);
    c2=bw_fldstru1.get_t2_flddec(i);
    str[0]=c1;
    str[1]=c2;
    for (k=2;k<=15;k++) str[k]=0;
    write(s_fp1,str,16);
  }
  str[0]=13;
  str[1]=26;
  write(s_fp1,str,2);
  close(s_fp1);
  set_win_rcnt(p_fcnt,0);
  return(0);
}
int bw_xbase::w_compare_xbase(int p_fp,int p_fcnt)
{
  int           i,k;
//  char          str[SMG_LEN];
  char          sf1[SMG_LEN];
//  char          c1,c2;
  char          s_tmpc2[SMG_LEN];
  unsigned char uc1,uc2;
  char          fldname[SMG_LEN];
  char          fldtype;
  unsigned int  fldlen,flddec;
  unsigned char s_tmpc1[SMG_LEN];

  read(p_fp,s_tmpc1,16);
  if (eof(p_fp))
  {
    set_win_rcnt(p_fcnt,0);
    return(1);
  }

  uc1=s_tmpc1[4];   /* calculate record number */
  uc2=s_tmpc1[5];
  set_win_rcnt(p_fcnt,uc2*256+uc1);
  uc1=s_tmpc1[6];
  uc2=s_tmpc1[7];
  set_win_rcnt(p_fcnt,get_win_rcnt(p_fcnt)+(uc2*256+uc1)*256*256);

  read(p_fp,s_tmpc1,16);
  if (eof(p_fp))
  {
    set_win_rcnt(p_fcnt,0);
    return(1);
  }

  for (k=bw_fldstru1.get_t2_fldpoin(p_fcnt,0);k<=bw_fldstru1.get_t2_fldpoin(p_fcnt,1);k++)
  {
    read(p_fp,s_tmpc1,16);
    if (eof(p_fp))
    {
      set_win_rcnt(p_fcnt,0);
      return(1);
    }
    for (i=0;i<=10;i++) fldname[i]=s_tmpc1[i];
    fldtype=s_tmpc1[11];                                    

    read(p_fp,s_tmpc1,16);
    if (eof(p_fp))
    {
      set_win_rcnt(p_fcnt,0);
      return(1);
    }

    fldlen=s_tmpc1[0];
    flddec=s_tmpc1[1];
    bw_fldstru1.get_t2_fldname(k,sf1,20);
    for (i=0;i<(int)strlen(sf1);i++)
    {
      s_tmpc2[i+0]=bw_inkey1.upper(bw_fldstru1.getc_t2_fldname(k,i));
      s_tmpc2[i+1]=0;
    }

    if (strcmp(s_tmpc2,fldname)!=0)
    {
      set_win_rcnt(p_fcnt,0);
      return(1);
    }
    if (bw_inkey1.upper(bw_fldstru1.get_t2_fldtype(k))!=fldtype)
    {
      set_win_rcnt(p_fcnt,0);
      return(1);
    }
    if (bw_fldstru1.get_t2_fldlen(k)!=(int)fldlen)
    {
      set_win_rcnt(p_fcnt,0);
      return(1);
    }
    if (bw_fldstru1.get_t2_flddec(k)!=(int)flddec)
    {
      set_win_rcnt(p_fcnt,0);
      return(1);
    }
  }

  read(p_fp,s_tmpc1,1);
  if (s_tmpc1[0]!=13)
  {
    set_win_rcnt(p_fcnt,0);
    return(1);
  }

  return(0);
}
int bw_xbase::w_read_xbase_rec(long recno,int p_fcnt)
{
  long i,j;
  int  s_state1;
//  char str[SMG_LEN];

  s_state1=w_loc_xbase_rec(recno,p_fcnt);
  if (s_state1!=0)
  {
    for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar(i,' ');
    return(1);
  }

  j=read_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

  if ((eof(win_fp[p_fcnt]))&&(j<get_win_lcnt(p_fcnt,1)+1))
  {
    for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar(i,' ');
    return(1);
  }

  return(0);
}
int bw_xbase::w_save_xbase_rec(long recno,int p_fcnt)
{
//  int i,j;
  int s_state1;

  s_state1=w_loc_xbase_rec(recno,p_fcnt);
  if (s_state1!=0) return(1);

  write_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

  return(0);
}
int bw_xbase::w_append_xbase_rec(long recno,int p_fcnt)
{
  long i;
//  char c1;
//  char str[SMG_LEN];

  if (recno<=0) return(1);

  i=(get_win_lcnt(p_fcnt,0)+1)*32+1+(recno-1)*(get_win_lcnt(p_fcnt,1)+1);

  lseek(win_fp[p_fcnt],i,0);

//  write(win_fp[p_fcnt],win_recvar,get_win_lcnt(p_fcnt,1)+1);

  write_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

//  str[0]=26;
//
//  write(win_fp[p_fcnt],str,1);

  return(0);
}
int bw_xbase::w_append_xbase_rec2(int p_fcnt)
{
  long i;
//  char c1;
  char str[SMG_LEN];

  i=(get_win_lcnt(p_fcnt,0)+1)*32+1+get_win_rcnt(p_fcnt)*(get_win_lcnt(p_fcnt,1)+1);

  lseek(win_fp[p_fcnt],i,0);

  w_clr_recvar(p_fcnt);

  write_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

  str[0]=26;

  write(win_fp[p_fcnt],str,1);

  set_win_rcnt(p_fcnt,get_win_rcnt(p_fcnt)+1);
  w_set_xbase_recno(get_win_rcnt(p_fcnt),p_fcnt);

  return(get_win_rcnt(p_fcnt));
}
int bw_xbase::w_loc_xbase_rec(long recno,int p_fcnt)
{
  long i;

  win_state3=0;

  if (recno<=0) return(1);
  if (recno>get_win_rcnt(p_fcnt)) return(1);

  i=(get_win_lcnt(p_fcnt,0)+1)*32+1+(recno-1)*(get_win_lcnt(p_fcnt,1)+1);
  lseek(win_fp[p_fcnt],i,0);
  if (eof(win_fp[p_fcnt])) return(1);
  else return(0);
}
long bw_xbase::w_up_xbase_rec(long recno,int p_fcnt)
{
//  int  i,j;
  int  s_state1;
  long recno1;
  long recno2;

  recno1=recno;

  if (recno1>get_win_rcnt(p_fcnt)+1) recno1=get_win_rcnt(p_fcnt)+1;

  recno2=recno1;

  while (1)
  {
    if (recno1>1) recno1--;
    else
    {
      if (w_xbase_rec_del()==1)
      {
	w_clr_recvar(p_fcnt);
	set_win_recvar(0,'*');
      }
      else w_clr_recvar(p_fcnt);
      win_state3=1;
      return(recno2);
    }
    s_state1=w_read_xbase_rec(recno1,p_fcnt);
    if (s_state1!=0)
    {
      win_state3=1;
      break;
    }
    if (w_xbase_rec_del()==1) continue;
    break;
/*    if (get_win_state7[p_fcnt][wpp]==0) break;*/
/*    if (w_find_cond(wpp,p_fcnt)==1) break;*/ /* add*/
  }
  if (win_state3==1) return(recno2);
  else return(recno1);
}
long bw_xbase::w_down_xbase_rec(long recno,int p_fcnt)
{
  int  s_state1;
//  HDC  hdc;
  long recno1;
  long recno2;

  recno1=recno;

  if (recno1<0) recno1=0;

  recno2=recno1;

  while (1)
  {
    if (recno1<get_win_rcnt(p_fcnt)) recno1++;
    else
    {
      if (w_xbase_rec_del()==1)
      {
	w_clr_recvar(p_fcnt);
	set_win_recvar(0,'*');
      }
      else w_clr_recvar(p_fcnt);
      win_state3=1;
      return(recno2);
    }
    s_state1=w_read_xbase_rec(recno1,p_fcnt);
    if (s_state1!=0)
    {
      win_state3=1;
      break;
    }
    if (w_xbase_rec_del()==1) continue;
    break;
/*    if (win_state7[p_fcnt][wpp]==0) break;*/
/*    if (w_find_cond(wpp,p_fcnt)==1) break;*//*add*/
  }
  if (win_state3==1) return(recno2);
  else return(recno1);
} 
int bw_xbase::w_xbase_rec_del()
{
  if (get_win_recvar(0)=='*') return(1);
  else return(0);
}
int bw_xbase::w_dele_xbase_rec(long recno,int p_fcnt)
{
  int  s_state1;
  char str[SMG_LEN];
  s_state1=w_loc_xbase_rec(recno,p_fcnt);
  if (s_state1!=0) return(1);
  str[0]='*';
  write(win_fp[p_fcnt],str,1);
  return(0);
}
int bw_xbase::w_insert_xbase_rec(long recno,int p_fcnt,int aft)
{
//  long recno1;
  int  s_state1;
  int  s_state2;
  int  i;

  if (recno>=0)
  {
    s_state1=w_loc_xbase_rec(recno,p_fcnt);
    if (s_state1!=0) return(1);

    s_state2=aft;  // 1 insert before , 0 insert after
    if (s_state2==0)
    {
      recno++;
      win_insert_dir=1;
    }
    else win_insert_dir=0;
  }
  else
  {
    recno=1;
    win_insert_dir=1;
  }

  s_state1=w_read_xbase_rec(recno,p_fcnt);

  for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar2(i,0,get_win_recvar(i));

  if (get_win_lnktab(p_fcnt)==255)
  {
    if (get_win_carry_on(p_fcnt)!=1) w_clr_recvar(p_fcnt);
  }
  else
  {
    if (get_win_carry_on(p_fcnt)!=1) w_clr_recvar(p_fcnt);
  }

  if (s_state1==0) w_save_xbase_rec(recno,p_fcnt);
  else
  {
    w_append_xbase_rec(recno,p_fcnt);
    set_win_rcnt(p_fcnt,get_win_rcnt(p_fcnt)+1);
    w_set_xbase_recno(get_win_rcnt(p_fcnt),p_fcnt);
    return(0);
  }

  while (1)
  {
    recno++;
    s_state1=w_read_xbase_rec(recno,p_fcnt);
    for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar2(i,1,get_win_recvar(i));
    for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar(i,get_win_recvar2(i,0));
    if (s_state1==0) w_save_xbase_rec(recno,p_fcnt);
    else
    {
      w_append_xbase_rec(recno,p_fcnt);
      set_win_rcnt(p_fcnt,get_win_rcnt(p_fcnt)+1);
      w_set_xbase_recno(get_win_rcnt(p_fcnt),p_fcnt);
      return(0);
    }

    for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar2(i,0,get_win_recvar2(i,1));
  }
}

int bw_xbase::w_insert_xbase_rec2(int p_fcnt) // for empty base ,add three empty rec
{
  long recno1;
  int  s_state1;
  int  s_state2;
  int  i;

  //recno1=1;

  w_clr_recvar(p_fcnt);

  i=(get_win_lcnt(p_fcnt,0)+1)*32+1+0*(get_win_lcnt(p_fcnt,1)+1);
  lseek(win_fp[p_fcnt],i,0);
  write_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

  i=(get_win_lcnt(p_fcnt,0)+1)*32+1+1*(get_win_lcnt(p_fcnt,1)+1);
  lseek(win_fp[p_fcnt],i,0);
  write_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

  i=(get_win_lcnt(p_fcnt,0)+1)*32+1+2*(get_win_lcnt(p_fcnt,1)+1);
  lseek(win_fp[p_fcnt],i,0);
  write_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

  //w_append_xbase_rec(recno,p_fcnt);

  w_set_xbase_recno(3,p_fcnt);

  return(0);

}

int bw_xbase::w_pack_xbase_base(int p_fcnt)
{
  long  s_recno1,s_recno2;
  long  s_fl,s_fl2;
  int   s_state1;
//  int   i,j;
//  int   stn1;
  int   s_fh;
//  char  c1;
  char  s_tmpc1[32+1];
  char  s_tmpc2[SMG_LEN];
  char  s_tmpc3[FN_SIZE];
  char  s_tmpc4[SMG_LEN];
  char  s_tmpc5[SMG_LEN];

  /* find tmp pack file name */
  get_win_ext(p_fcnt,s_tmpc2,SMG_LEN);

  strcpy(s_tmpc5,"tmp_pack");
  w_find_empty_file(s_tmpc5,SMG_LEN,p_fcnt);
  get_win_ext(p_fcnt,s_tmpc4,SMG_LEN);
  set_win_ext(p_fcnt,s_tmpc2,SMG_LEN);
  strcpy(s_tmpc3,"tmp_pack");
  strcat(s_tmpc3,s_tmpc4);

  /* sopen tmp pack file */
  s_fh=sopen(s_tmpc3,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_fh<0) return(1);

  /* copy header */
  lseek(win_fp[p_fcnt],0,0);
  while (1)
  {
    read(win_fp[p_fcnt],s_tmpc1,32);
    if (s_tmpc1[0]==13) break;
    write(s_fh,s_tmpc1,32);
  }
  s_tmpc2[0]=13;
  s_tmpc2[1]=0;
  write(s_fh,s_tmpc2,1);

  /* copy record */
  s_recno1=0;
  s_recno2=0;
  while (1)
  {
    s_recno1++;
    s_state1=w_loc_xbase_rec(s_recno1,p_fcnt);
    if (s_state1!=0) break;

    read_win_recvar(win_fp[p_fcnt],get_win_lcnt(p_fcnt,1)+1);

    if (eof(win_fp[p_fcnt])) break;

    if (get_win_recvar(0)=='*') continue;

    s_recno2++;

    write_win_recvar(s_fh,get_win_lcnt(p_fcnt,1)+1);
  }

  /* write tail */
  s_tmpc2[0]=26;
  s_tmpc2[1]=0;
  write(s_fh,s_tmpc2,1);

  /* set recno */
  w_set_fox_recno2(s_recno2,s_fh);
  set_win_rcnt(p_fcnt,s_recno2);

  /* copy back file */
  lseek(s_fh,0,0);
  lseek(win_fp[p_fcnt],0,0);
  s_fl=0;
  s_fl2=0;
  while (1)
  {
    s_recno1=read_win_recvar(s_fh,REC_LEN);

    s_fl2=write_win_recvar(win_fp[p_fcnt],s_recno1);

    s_fl=s_fl+s_fl2;
    if (eof(s_fh)) break;
  }

  /* dele pack file */
  close(s_fh);

  bw_inkey1.w_del_file(s_tmpc3);

  chsize(win_fp[p_fcnt],s_fl);

  return(0);
}
int bw_xbase::w_set_xbase_recno(long recno,int p_fcnt)
{
  unsigned char c1,c2,c3,c4;
  char          str[5];

  set_win_rcnt(p_fcnt,recno);

  c1=(unsigned char)(recno/256/256/256);
  c2=(unsigned char)((recno-c1*256*256*256)/256/256);
  c3=(unsigned char)((recno-c1*256*256*256-c2*256*256)/256);
  c4=(unsigned char)(recno-c1*256*256*256-c2*256*256-c3*256);

  lseek(win_fp[p_fcnt],4,0);
  str[0]=c4;
  str[1]=c3;
  str[2]=c2;
  str[3]=c1;
  write(win_fp[p_fcnt],str,4);
  return(0);
}
int bw_xbase::w_set_fox_recno2(long recno,int p_fp)
{
  unsigned char c1,c2,c3,c4;
  char          str[5];

  c1=(unsigned char )(recno/256/256/256);
  c2=(unsigned char )((recno-c1*256*256*256)/256/256);
  c3=(unsigned char )((recno-c1*256*256*256-c2*256*256)/256);
  c4=(unsigned char )(recno-c1*256*256*256-c2*256*256-c3*256);

  lseek(p_fp,4,0);
  str[0]=c4;
  str[1]=c3;
  str[2]=c2;
  str[3]=c1;
  write(p_fp,str,4);
  return(0);
}
int bw_xbase::w_commit_xbase(int p_fcnt)
{
  int  i,j,k;
  int  s_state1;
  char s_tmpc1[FN_SIZE];
  char st1[FN_SIZE];
  char st2[FN_SIZE];    

  if (get_win_state5(p_fcnt)==0) return(0);

  get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  //s_state1=w_pack_xbase_base(p_fcnt);
  //if (s_state1!=0) return(1);

  get_win_basename(p_fcnt,st1,FN_SIZE);

  strcpy(s_tmpc1,st1);
  i=bw_inkey1.strlocc(s_tmpc1,FN_SIZE,'.');
  s_tmpc1[i]=0;
  get_win_ext(p_fcnt,st2,FN_SIZE);
  strcat(s_tmpc1,st2);

  //get_win_basename(p_fcnt,st1,FN_SIZE);

  // delete dbf file
  while(1)
  {
    j=bw_inkey1.w_del_file(st1);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(st1);   /* open error */
      if (k==1) continue;        /* retry      */
      else break;                /* cancel     */
    }
  }

  // copy to dbf file
  while(1)
  {
    j=bw_inkey1.w_cpy_file(s_tmpc1,st1);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(st1);   /* open error */
      if (k==1) continue;        /* retry      */
      else break;                /* cancel     */
    }
  }

  return(0);
}
int bw_xbase::w_rollback_xbase(char *p_fn1,int p_fn1_len,int backup,int p_fcnt)
{
  long s_recno1;
  int  i,j,k;
  char s_fn2[FN_SIZE];
  char st1[FN_SIZE];
  char st2[FN_SIZE];
  char sc1[FN_SIZE];
  //char s_fn4[FN_SIZE];
//  int  s_state1;
  int  s_fh;

  if (get_win_state5(p_fcnt)==0) return(0);

  if (backup==0) return(1);

  get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  /* make backup file name */
  strcpy(s_fn2,p_fn1);
  bw_inkey1.strtrim(s_fn2,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
  s_fn2[i]=0;
  get_win_ext(p_fcnt,sc1,FN_SIZE);
  strcat(s_fn2,sc1);

  close(win_fp[p_fcnt]);

  bw_win1.get_win_tabname(1,p_fcnt,st2,FN_SIZE);
  bw_inkey1.strtrim(st2,FN_SIZE);
  i=bw_inkey1.strlocc(st2,FN_SIZE,'.');
  st2[i]=0;
  strcat(st2,".dbf");

  // delete tmp file
  while(1)
  {
    j=bw_inkey1.w_del_file(s_fn2);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(s_fn2);   /* open error */
      if (k==1) continue;          /* retry      */
      else break;                  /* cancel     */
    }
  }

  // copy to tmp file
  while(1)
  {
    j=bw_inkey1.w_cpy_file(st2,s_fn2);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(s_fn2);   /* open error */
      if (k==1) continue;          /* retry      */
      else break;                  /* cancel     */
    }
  }

  win_fp[p_fcnt]=sopen(s_fn2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (win_fp[p_fcnt]<0) return(1);

/*
*/  /* copy back */
/*  s_fh=sopen(s_fn2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_fh<0) return(1);

  lseek(s_fh,0,0);
  lseek(win_fp[p_fcnt],0,0);

  while (1)
  {
    s_recno1=read_win_recvar(s_fh,REC_LEN);

    write_win_recvar(win_fp[p_fcnt],s_recno1);

    if (eof(s_fh)) break;
  }

  close(s_fh);
*/
  set_win_rcnt(p_fcnt,w_read_recno(win_fp[p_fcnt]));

  return(0);
}
int bw_xbase::w_append_sdf(char *p_fn,int p_fn_len,int p_fcnt)
{
  long recno;
  int  i,j;
//  char s_tmpc1[SMG_LEN];
  //char s_fn4[FN_SIZE];
  FILE *s_fh;

  s_fh=fopen(p_fn,"r");
  if (s_fh==NULL) return(1);

  /* find max recno */
  recno=get_win_rcnt(p_fcnt);

  i=0;
  while (1)
  {
    fgets_win_recvar(s_fh,REC_LEN);

    w_append_xbase_rec(recno,p_fcnt);
    set_win_rcnt(p_fcnt,get_win_rcnt(p_fcnt)+1);
    recno++;

    i++;

    if (feof(s_fh)) break;
  }

  w_set_xbase_recno(recno,p_fcnt);

  fclose(s_fh);

  return(i);
}
int bw_xbase::w_copy_sdf(char *p_fn,int p_fn_len,int p_fcnt)
{
  long  i;
  int   j;
//  int   exist;
//  char  s_tmpc1[SMG_LEN];
  //char  s_fn4[FN_SIZE];
  FILE *s_fp1;

  s_fp1=fopen(p_fn,"w");
  if (s_fp1==NULL) return(0);

  i=0;
  while (1)
  {
    i=w_down_xbase_rec(i,p_fcnt);
    if (win_state3==1) break;

    set_win_recvar(get_win_lcnt(p_fcnt,1)+1,'\n');
    set_win_recvar(get_win_lcnt(p_fcnt,1)+2,0);

    fputs_win_recvar(s_fp1);

    i++;
  }

  fclose(s_fp1);

  return(i);
}
int bw_xbase::w_zap_xbase(int p_fcnt)
{
  long i;

  i=0;

  w_set_xbase_recno(i,p_fcnt);

  return(0);
}
int bw_xbase::w_clr_recvar(int p_fcnt)
{
  int i;
  for (i=0;i<=get_win_lcnt(p_fcnt,1);i++) set_win_recvar(i,' ');
  return(0);
}
int bw_xbase::w_find_empty_file(char *p_str,int p_str_len,int p_fcnt)
{
  int   i,j,k,l;
  char  s_stc1[SMG_LEN];
  char  s_stc2[FN_SIZE];
//  char  sc1[FN_SIZE];
  //char  s_tm[SMG_LEN];
  char  c1,c2;

  strcpy(s_stc2,p_str);
  s_stc1[0]='$';
  k=bw_inkey1.strlocc(s_stc2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;
    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      s_stc1[1]=c1;
      s_stc1[2]=c2;
      s_stc1[3]=0;

      s_stc2[k]=0;
      strcat(s_stc2,".");
      strcat(s_stc2,s_stc1);

      l=bw_inkey1.w_find_file(s_stc2);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    setc_win_ext(p_fcnt,0,'.');
    setc_win_ext(p_fcnt,1,'$');
    setc_win_ext(p_fcnt,2,c1);
    setc_win_ext(p_fcnt,3,c2);
    setc_win_ext(p_fcnt,4,0);

    return(0);
  }
  else
  {
    setc_win_ext(p_fcnt,0,0);
    return(1);
  }
}
int bw_xbase::w_find_empty_ffile(char *p_str,int p_str_len,int wpp)
{
  int   i,j,k,l;
  char  s_stc1[SMG_LEN];
  char  s_stc2[FN_SIZE];
  //char  s_tm[SMG_LEN];
  char  c1,c2;

  strcpy(s_stc2,p_str);
  s_stc1[0]='#';
  k=bw_inkey1.strlocc(s_stc2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;
    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      s_stc1[1]=c1;
      s_stc1[2]=c2;
      s_stc1[3]=0;

      s_stc2[k]=0;
      strcat(s_stc2,".");
      strcat(s_stc2,s_stc1);

      l=bw_inkey1.w_find_file(s_stc2);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    setc_win_fext(wpp,0,'.');
    setc_win_fext(wpp,1,'#');
    setc_win_fext(wpp,2,c1);
    setc_win_fext(wpp,3,c2);
    setc_win_fext(wpp,4,0);
    return(0);
  }
  else
  {
    setc_win_fext(wpp,0,0);
    return(1);
  }
}
int bw_xbase::w_find_empty_mfile(char *p_str,int p_str_len,int p_fcnt)
{
  int   i,j,k,l;
  char  s_stc1[SMG_LEN];
  char  s_stc2[FN_SIZE];
  //char  s_tm[SMG_LEN];
  char  c1,c2;

  strcpy(s_stc2,p_str);
  s_stc1[0]='@';
  k=bw_inkey1.strlocc(s_stc2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;
    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      s_stc1[1]=c1;
      s_stc1[2]=c2;
      s_stc1[3]=0;

      s_stc2[k]=0;
      strcat(s_stc2,".");
      strcat(s_stc2,s_stc1);

      l=bw_inkey1.w_find_file(s_stc2);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    setc_win_mem_ext(p_fcnt,0,'.');
    setc_win_mem_ext(p_fcnt,1,'@');
    setc_win_mem_ext(p_fcnt,2,c1);
    setc_win_mem_ext(p_fcnt,3,c2);
    setc_win_mem_ext(p_fcnt,4,0);
    return(0);
  }
  else
  {
    setc_win_mem_ext(p_fcnt,0,0);
    return(1);
  }
}
int bw_xbase::w_close_xbase(int p_fcnt)
{
  int  i;
  char s_fn1[FN_SIZE];
  char st1[FN_SIZE];
  char sc1[FN_SIZE];

  close(win_fp[p_fcnt]);

  get_win_basename(p_fcnt,st1,FN_SIZE);

  strcpy(s_fn1,st1);
  i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  get_win_ext(p_fcnt,sc1,FN_SIZE);
  strcat(s_fn1,sc1);

  get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  bw_inkey1.w_del_file(s_fn1);

  w_dele_state(p_fcnt);

  return(0);
}
int bw_xbase::w_use_fox(char *p_fn1,int p_fn1_len)
{
  int           i,k;
//  char          c1,c2;
//  char          s_tmpc2[SMG_LEN];
  unsigned char uc1,uc2,uc3,uc4;
  long          j;
  char          fldname[SMG_LEN];
  char          fldtype;
  unsigned int  fldlen,flddec;
  unsigned char s_tmpc1[SMG_LEN];
//  char          str[SMG_LEN];
  //char          s_fn4[FN_SIZE];

  win_use_fh=sopen(p_fn1,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (win_use_fh<0) return(1);

  read(win_use_fh,s_tmpc1,16);
  if (eof(win_use_fh)) return(1);

  uc1=s_tmpc1[5];      /* calculate record number */
  uc2=s_tmpc1[6];
  uc3=s_tmpc1[7];
  uc4=s_tmpc1[8];

  set_t4_recnumb(0,((uc4*256+uc3)*256+uc2)*256+uc1);

  read(win_use_fh,s_tmpc1,16);
  if (eof(win_use_fh)) return(1);

  k=0;
  j=1;
  while (1)
  {
    read(win_use_fh,s_tmpc1,16);
    if (s_tmpc1[0]==13) break;
    if (eof(win_use_fh)) return(1);

    for (i=0;i<=10;i++) fldname[i]=s_tmpc1[i];
    fldtype=s_tmpc1[11];

    read(win_use_fh,s_tmpc1,16);
    if (eof(win_use_fh)) return(1);

    fldlen=s_tmpc1[0];
    flddec=s_tmpc1[1];

    for (i=0;i<(int)strlen(fldname);i++) fldname[i]=bw_inkey1.lower(fldname[i]);
    fldtype=bw_inkey1.lower(fldtype);

    k++;
    j=j+fldlen;
    if (k>=FLD_IN_XBASE) return(1);
    i=k;

    set_t4_fldname(i,fldname,SMG_LEN);
    set_t4_fldtype(i,fldtype);
    set_t4_fldposi(i,j-fldlen);
    set_t4_fldlen(i,fldlen);
    set_t4_flddec(i,flddec);
  }

  set_t4_recnumb(1,k);
  set_t4_recnumb(2,j);
/*
  sprintf(str,"%ld,%ld,%ld,",t4_recnumb[0]
			    ,t4_recnumb[1]
			    ,t4_recnumb[2]);
  MessageBox(bw_main1.win_hwnd1,str,"22",MB_OK);
*/
/*
  for (i=1;i<=k;i++)
  {
     sprintf(str,"%s,%d,%d,%d,%d,",t4_fldname[i]
                                  ,t4_fldtype[i]
		                  ,t4_fldlen[i]
			          ,t4_flddec[i]
				  ,t4_fldposi[i]);
     MessageBox(bw_main1.win_hwnd1,str,"33",MB_OK);
  }
*/
  return(0);
}
int bw_xbase::w_append_fox(int p_fcnt)
{
  int   i,j,k,l,m,n,o;
  int   recdel;
  char  s_stc1[SMG_LEN];
  char  s_stc2[SMG_LEN];
  char  s_stc3[SMG_LEN];
  char  s_stc4[SMG_LEN];
  char  s_stc5[SMG_LEN];
  char  s_stc6[SMG_LEN];
  long  r,s;
  float f1;

  r=1;
  while (1)
  {
    i=w_go_fox(r);
    if (i!=0) break;

    s=get_t4_recnumb(2);

    read_win_recvar(win_use_fh,s);

    if (eof(win_use_fh)) break;

    if (get_win_recvar(0)=='*') recdel=1;
	else recdel=0;

    j=s;
    for (i=0;i<=j;i++) set_win_recvar2(i,0,get_win_recvar(i));

    w_clr_recvar(p_fcnt);

    for (i=1;i<=get_t4_recnumb(1);i++)
    {
      for (j=get_t4_fldposi(i);j<get_t4_fldposi(i)+get_t4_fldlen(i);j++)
		s_stc1[j-get_t4_fldposi(i)]=get_win_recvar2(j,0);

      j=get_t4_fldlen(i);
      s_stc1[j]=0;

      get_t4_fldname(i,s_stc6,SMG_LEN);

      bw_inkey1.lowers(s_stc6);

      l=bw_fldstru1.w_find_fldnum(s_stc6,SMG_LEN,p_fcnt);
      if (l!=0) continue;

      if (get_t4_fldtype(i)=='n')
      {
		if ((bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='c')
		  ||(bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='l')
		  ||(bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='m')
		  ||(bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='b'))
		{
		  for (k=strlen(s_stc1);k<bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);k++)
		    s_stc1[k]=' ';

		  k=bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);
		  s_stc1[k]=0;
		  strcpy(s_stc4,s_stc1);
        }
	
		if (bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='n')
		{
		  if (w_there_is_a(s_stc1,j)==1)
          {
		    for (k=strlen(s_stc1);k<bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);k++)
		      s_stc1[k]=' ';
		    k=bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);
		    s_stc1[k]=0;
		    strcpy(s_stc4,s_stc1);
          }
          else
          {
		    f1=bw_inkey1.str2float(s_stc1,SMG_LEN);
		    sprintf(s_stc2,"%25.10f",f1);

		    k=bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);
		    l=bw_fldstru1.w_find_flddec(s_stc6,SMG_LEN,p_fcnt);

		    if (l!=0)
            {
		      if (k-l-1<=0) m=0;
		      else m=k-l-1;
              if (l>k-1) n=k-1;
		      else n=l;
		      bw_inkey1.strpcut(s_stc2,14-m,m,SMG_LEN,s_stc3,SMG_LEN);
		      bw_inkey1.strpcut(s_stc2,14,n+1,SMG_LEN,s_stc5,SMG_LEN);
		    }
		    else
		    {
		      m=k;
		      n=0;
		      bw_inkey1.strpcut(s_stc2,14-m,m,SMG_LEN,s_stc3,SMG_LEN);
		      s_stc5[0]=0;

			  if (bw_inkey1.str2int(s_stc3,strlen(s_stc3)+1)==0)
			  {
				  for (o=0;o<(int)strlen(s_stc3);o++) s_stc3[o]=32;
			  }
		    }


		    strcpy(s_stc4,s_stc3);
		    strcat(s_stc4,s_stc5);
          }
        }
      }
      if ((get_t4_fldtype(i)=='c')||(get_t4_fldtype(i)=='l')||(get_t4_fldtype(i)=='m')||(get_t4_fldtype(i)=='b'))
      {
		if ((bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='c')
			||(bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='l')
			||(bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='m')
			||(bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='b'))
		{
		  for (k=strlen(s_stc1);k<bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);k++)
		    s_stc1[k]=' ';
		  k=bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);
		  s_stc1[k]=0;
		  strcpy(s_stc4,s_stc1);
        }
		if (bw_fldstru1.w_find_fldtype(s_stc6,SMG_LEN,p_fcnt)=='n')
		{
		  f1=bw_inkey1.str2float(s_stc1,SMG_LEN);
		  sprintf(s_stc2,"%25.10f",f1);

		  k=bw_fldstru1.w_find_fldlen(s_stc6,SMG_LEN,p_fcnt);
		  l=bw_fldstru1.w_find_flddec(s_stc6,SMG_LEN,p_fcnt);

		  if (l!=0)
          {
		    if (k-l-1<=0) m=0;
		    else m=k-l-1;
            if (l>k-1) n=k-1;
		    else n=l;
		    bw_inkey1.strpcut(s_stc2,14-m,m,SMG_LEN,s_stc3,SMG_LEN);
		    bw_inkey1.strpcut(s_stc2,14,n+1,SMG_LEN,s_stc5,SMG_LEN);
		  }
		  else
		  {
		    m=k;
		    n=0;
		    bw_inkey1.strpcut(s_stc2,14-m,m,SMG_LEN,s_stc3,SMG_LEN);
		    s_stc5[0]=0;
		  }

		  strcpy(s_stc4,s_stc3);
		  strcat(s_stc4,s_stc5);
        }
      }

      w_bsav_var(p_fcnt,s_stc6,SMG_LEN,s_stc4,SMG_LEN);
    }

    set_win_rcnt(p_fcnt,get_win_rcnt(p_fcnt)+1);

    if (recdel==1) set_win_recvar(0,'*');

    w_append_xbase_rec(get_win_rcnt(p_fcnt),p_fcnt);

    r++;
  }

  r=(get_win_lcnt(p_fcnt,0)+1)*32+1+get_win_rcnt(p_fcnt)*(get_win_lcnt(p_fcnt,1)+1);
  chsize(win_fp[p_fcnt],r+1);

  w_set_xbase_recno(get_win_rcnt(p_fcnt),p_fcnt);

  return(0);
}
int bw_xbase::w_close_fox()
{
  close(win_use_fh);

  return(0);
}
int bw_xbase::w_go_fox(long r)
{
  long i;
  i=(get_t4_recnumb(1)+1)*32+1+(r-1)*get_t4_recnumb(2);
  lseek(win_use_fh,i,0);
  if (eof(win_use_fh)) return(1);
  else return(0);
}
int bw_xbase::w_bcpy_var(int p_fcnt,char *p_fld,int p_fld_len,char *p_stc4,int p_stc4_len)
{
  int i,j,k;

  i=bw_fldstru1.w_find_fldnum(p_fld,p_fld_len,p_fcnt);
  if (i!=0) return(1);

  j=bw_fldstru1.w_find_fldlen(p_fld,p_fld_len,p_fcnt);
  k=bw_fldstru1.w_find_fldposi(p_fld,p_fld_len,p_fcnt);
  for (i=1;i<=j;i++)
  {
    if (i-1<p_stc4_len)
    {
      p_stc4[i-1]=get_win_recvar(i-1+k);
    }
  }
  if (i-1<p_stc4_len)
  {
    p_stc4[i-1]=0;
  }
  return(0);
}
int bw_xbase::w_bsav_var(int p_fcnt,char *p_fld,int p_fld_len,char *p_stc4,int p_stc4_len)
{
  int  i,j,k;
  char c1;

  i=bw_fldstru1.w_find_fldnum(p_fld,p_fld_len,p_fcnt);
  if (i!=0) return(1);

  j=bw_fldstru1.w_find_fldposi(p_fld,p_fld_len,p_fcnt);
  k=strlen(p_stc4);
  if (k>=p_stc4_len) k=p_stc4_len-1;
  for (i=1;i<=bw_fldstru1.w_find_fldlen(p_fld,p_fld_len,p_fcnt);i++)
  {
    if (i>k) c1=' ';
    else
    {
      if ((p_stc4[i-1]<' ')&&(p_stc4[i-1]>=0)) c1=' ';
      else c1=p_stc4[i-1];
    }
    set_win_recvar(i-1+j,c1);
  }
  return(0);
}
int bw_xbase::w_there_is_a(char *p_s,int p_s_len)  
{
  int i;
  int exist;
  exist=0;
  for (i=0;i<p_s_len;i++)
  {
    if (((p_s[i]>='0')&&(p_s[i]<='9'))||(p_s[i]==' ')||(p_s[i]=='-'))
    {
      exist=0;
    }
    else
    {
      exist=1;
      break;
    }
  }
  return(exist);
}





int bw_xbase::get_win_state1(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state1[spp]);
}
int bw_xbase::get_win_state4(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state4[spp]);
}
int bw_xbase::get_win_state5(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state5[spp]);
}
int bw_xbase::get_win_state7(int spp,int wpp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_state7[spp][wpp]);
}
int bw_xbase::get_win_state9(int wpp,int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_state9[wpp][spp]);
}
int bw_xbase::get_win_state10(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state10[spp]);
}

int bw_xbase::set_win_state1(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state1[spp]=val;
  return(0);
}
int bw_xbase::set_win_state4(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state4[spp]=val;
  return(0);
}
int bw_xbase::set_win_state5(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state5[spp]=val;
  return(0);
}
int bw_xbase::set_win_state7(int spp,int wpp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_state7[spp][wpp]=val;
  return(0);
}
int bw_xbase::set_win_state9(int wpp,int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_state9[wpp][spp]=val;
  return(0);
}
int bw_xbase::set_win_state10(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state10[spp]=val;
  return(0);
}

long bw_xbase::get_win_recno(int spp,int wpp,int p02)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(win_recno[spp][wpp][p02]);
}
int bw_xbase::set_win_recno(int spp,int wpp,int p02,long val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  win_recno[spp][wpp][p02]=val;
  return(0);
}

long bw_xbase::get_win_rcnt(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_rcnt[spp]);
}
int bw_xbase::set_win_rcnt(int spp,long val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_rcnt[spp]=val;
  return(0);
}
int bw_xbase::get_win_lcnt(int spp,int p01)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_lcnt[spp][p01]);
}
int bw_xbase::set_win_lcnt(int spp,int p01,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_lcnt[spp][p01]=val;
  return(0);
}
int bw_xbase::get_win_lnktab(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_lnktab[spp]);
}
int bw_xbase::set_win_lnktab(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_lnktab[spp]=val;
  return(0);
}

int bw_xbase::get_win_scrnvar(int wpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (p_s1_len>SMG_LEN) i=SMG_LEN;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_scrnvar[wpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_scrnvar(int wpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (p_s1_len>SMG_LEN) i=SMG_LEN;
  else i=p_s1_len;

  win_scrnvar[wpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_scrnvar[wpp][j+0]=p_s1[j];
    win_scrnvar[wpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::getc_win_scrnvar(int wpp,int pp1)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  return(win_scrnvar[wpp][pp1]);
}
int bw_xbase::setc_win_scrnvar(int wpp,int pp1,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  win_scrnvar[wpp][pp1]=val;
  return(0);
}





int bw_xbase::get_win_memno(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_memno[spp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_mem_ext(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>EXT_LEN) i=EXT_LEN;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mem_ext[spp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_mem_fn(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>FN_SIZE) i=FN_SIZE;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mem_fn[spp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_mem_inuse(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_mem_inuse[spp]);
}
int bw_xbase::get_win_mem_wpp(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_mem_wpp[spp]);
}

int bw_xbase::set_win_memno(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=p_s1_len;

  win_memno[spp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_memno[spp][j+0]=p_s1[j];
    win_memno[spp][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_mem_ext(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>EXT_LEN) i=EXT_LEN;
  else i=p_s1_len;

  win_mem_ext[spp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mem_ext[spp][j+0]=p_s1[j];
    win_mem_ext[spp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_mem_ext(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_mem_ext[spp][pp1]=val;
  return(0);
}
int bw_xbase::set_win_mem_fn(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>FN_SIZE) i=FN_SIZE;
  else i=p_s1_len;

  win_mem_fn[spp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mem_fn[spp][j+0]=p_s1[j];
    win_mem_fn[spp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_mem_fn(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_mem_fn[spp][pp1]=val;
  return(0);
}
int bw_xbase::set_win_mem_inuse(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_mem_inuse[spp]=val;
  return(0);
}
int bw_xbase::set_win_mem_wpp(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_mem_wpp[spp]=val;
  return(0);
}
int bw_xbase::get_win_bmp_name(char *p_s1,int p_s1_len)
{
  int i,j;

  if (p_s1_len>SMG_LEN) i=SMG_LEN;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_bmp_name[j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_bmp_name(char *p_s1,int p_s1_len)
{
  int i,j;

  if (p_s1_len>SMG_LEN) i=SMG_LEN;
  else i=p_s1_len;

  win_bmp_name[0]=0;

  for (j=0;j<i-1;j++)
  {
    win_bmp_name[j+0]=p_s1[j];
    win_bmp_name[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_recvar(int rpp)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  return(win_recvar[rpp]);
}
int bw_xbase::set_win_recvar(int rpp,int val)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  win_recvar[rpp]=val;
  return(0);
}
int bw_xbase::get_win_recvar2(int rpp,int p01)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_recvar2[rpp][p01]);
}
int bw_xbase::set_win_recvar2(int rpp,int p01,int val)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_recvar2[rpp][p01]=val;
  return(0);
}
long bw_xbase::read_win_recvar(int fh,long len)
{
  long rl;
  if (fh<0) return(0);
  if ((len<0)||(len>REC_LEN)) return(0);
  rl=read(fh,win_recvar,len);
  return(rl);
}
long bw_xbase::write_win_recvar(int fh,long len)
{
  long wl;
  if (fh<0) return(0);
  if ((len<0)||(len>REC_LEN)) return(0);
  wl=write(fh,win_recvar,len);
  return(wl);
}
int bw_xbase::fgets_win_recvar(FILE *fh,long len)
{
  if (fh==NULL) return(0);
  if ((len<0)||(len>REC_LEN)) return(0);
  fgets(win_recvar,len,fh);
  return(0);
}
int bw_xbase::fputs_win_recvar(FILE *fh)
{
  if (fh==NULL) return(0);
  fputs(win_recvar,fh);
  return(0);
}
int bw_xbase::get_win_basename(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>FN_SIZE) i=FN_SIZE;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_basename[spp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_basename(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>FN_SIZE) i=FN_SIZE;
  else i=p_s1_len;

  win_basename[spp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_basename[spp][j+0]=p_s1[j];
    win_basename[spp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_basename(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_basename[spp][pp1]=val;
  return(0);
}
int bw_xbase::get_win_basedir(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>FN_SIZE) i=FN_SIZE;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_basedir[spp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_basedir(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>FN_SIZE) i=FN_SIZE;
  else i=p_s1_len;

  win_basedir[spp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_basedir[spp][j+0]=p_s1[j];
    win_basedir[spp][j+1]=0;
  }

  return(0);
}

int bw_xbase::setc_win_basedir(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_basedir[spp][pp1]=val;
  return(0);
}

int bw_xbase::get_win_base_type(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_base_type[spp]);
}
int bw_xbase::set_win_base_type(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_base_type[spp]=val;
  return(0);
}
int bw_xbase::get_win_base_backup(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_base_backup[spp]);
}
int bw_xbase::set_win_base_backup(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_base_backup[spp]=val;
  return(0);
}
int bw_xbase::get_win_enseri(int spp,int wpp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_enseri[spp][wpp]);
}
int bw_xbase::get_win_cuseri(int spp,int wpp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_cuseri[spp][wpp]);
}
int bw_xbase::set_win_enseri(int spp,int wpp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_enseri[spp][wpp]=val;
  return(0);
}
int bw_xbase::set_win_cuseri(int spp,int wpp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_cuseri[spp][wpp]=val;
  return(0);
}

int bw_xbase::get_win_carry_on(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_carry_on[spp]);
}
int bw_xbase::set_win_carry_on(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_carry_on[spp]=val;
  return(0);
}

int bw_xbase::get_win_ext(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>EXT_LEN) i=EXT_LEN;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_ext[spp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_ext(int spp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (p_s1_len>EXT_LEN) i=EXT_LEN;
  else i=p_s1_len;

  win_ext[spp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_ext[spp][j+0]=p_s1[j];
    win_ext[spp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_ext(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_ext[spp][pp1]=val;
  return(0);
}

int bw_xbase::get_win_fext(int wpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (p_s1_len>EXT_LEN) i=EXT_LEN;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_fext[wpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_fext(int wpp,int pp1,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_fext[wpp][pp1]=val;
  return(0);
}

long bw_xbase::get_t4_recnumb(int p03)
{
  if ((p03<0)||(p03>3)) return(0);
  return(t4_recnumb[p03]);
}
int bw_xbase::set_t4_recnumb(int p03,long val)
{
  if ((p03<0)||(p03>3)) return(0);
  t4_recnumb[p03]=val;
  return(0);
}

int bw_xbase::get_t4_fldname(int fpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  if (p_s1_len>11) i=11;
  else i=p_s1_len;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t4_fldname[fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_t4_fldname(int fpp,char *p_s1,int p_s1_len)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  if (p_s1_len>11) i=11;
  else i=p_s1_len;

  t4_fldname[fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    t4_fldname[fpp][j+0]=p_s1[j];
    t4_fldname[fpp][j+1]=0;
  }

  return(0);
}

int bw_xbase::get_t4_fldtype(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_fldtype[fpp]);
}
int bw_xbase::get_t4_fldlen(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_fldlen[fpp]);
}
int bw_xbase::get_t4_flddec(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_flddec[fpp]);
}
int bw_xbase::get_t4_fldposi(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_fldposi[fpp]);
}

int bw_xbase::set_t4_fldtype(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_fldtype[fpp]=val;
  return(0);
}
int bw_xbase::set_t4_fldlen(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_fldlen[fpp]=val;
  return(0);
}
int bw_xbase::set_t4_flddec(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_flddec[fpp]=val;
  return(0);
}
int bw_xbase::set_t4_fldposi(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_fldposi[fpp]=val;
  return(0);
}

