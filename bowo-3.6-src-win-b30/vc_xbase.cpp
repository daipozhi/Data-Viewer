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

int bw_xbase::tst_xbase1()
{
  HDC  hdc;
  int  i;
  char str[SMG_SIZE];
  char sfn[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<STRU_NUM;i++)
  {
    get_win_ext(i,sfn,FN_SIZE);

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
	       ,sfn
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
  char str[SMG_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);
  for (i=0;i<STRU_NUM;i++)
  {
    sprintf(str,"state1357=%d,%d,%d,%d,type=%d,backup=%d,"
	       ,get_win_state_bff_in_use(i)
	       ,win_state_dbf_err
	       ,get_win_state_dbf_modi(i)
	       ,0/*get_win_state7(i,0)*/
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
    if (get_win_state_bff_in_use(i)==0)
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
    if (get_win_state_bff_in_use(i)==0)
    {
      exist++;
    }
  }

  return(exist);
}

int bw_xbase::w_dele_state(int p_fpp)
{         
  int j;

  for (j=1;j<WIN_NUM;j++)
  {
    set_win_recno(p_fpp,j,0,0);
    set_win_recno(p_fpp,j,1,0);
    set_win_recno(p_fpp,j,2,0);
  }

  set_win_rcnt(p_fpp,0);    // total record number
  set_win_lcnt(p_fpp,0,0);  // field number
  set_win_lcnt(p_fpp,1,0);  // record length

  set_win_lnktab(p_fpp,0);

  set_win_state_bff_in_use(p_fpp,0);
  set_win_state_dbf_modi(p_fpp,0);

  setc_win_ext(p_fpp,0,0);
  setc_win_basedir(p_fpp,0,0);
  setc_win_basename(p_fpp,0,0);

  return(0);
}

int bw_xbase::w_open_xbase(char *p_fn1,int p_fn1_size,int backup,int p_fpp)
{
  char          s_fn1[FN_SIZE];
  char          s_fn2[FN_SIZE];
  char          s_fn3[FN_SIZE];
  char          str[FN_SIZE];
  int           i,j;
  int           s_state1,s_state2;
  char          s_ext[FN_SIZE];

  strcpy(s_fn1,p_fn1);
  bw_inkey1.strtrim(s_fn1,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  strcat(s_fn1,".dbf");

  while(1)
  {
    win_fp[p_fpp]=sopen(s_fn1,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
    if (win_fp[p_fpp]>=0) break;           /* open success */
    else
    {
      if (bw_inkey1.w_find_file(s_fn1)==1)  // file exist
      {
        s_state1=bw_win1.w_atten8(s_fn1);   /* open error */
        if (s_state1==1) continue;          /* retry      */
	else return(1);                     /* cancel     */
      }
      else
      {
	s_state1=bw_win1.w_atten9a(s_fn1); // dbf file not exist , create ? yes no cancel
	if (s_state1==0) return(1);        // cancel
	else
	{
	  if (s_state1==1)                 // yes,create
	  {
	    i=w_create_xbase(s_fn1,FN_SIZE,p_fpp);
	    if (i!=0) return(1);
	    else continue;
	  }
	  else return(1);                  // return 2,no,not create
	}
      }
    }
  }

  s_state1=w_compare_xbase(win_fp[p_fpp],p_fpp);
  if (s_state1==1)              // differant database
  {
    s_state2=bw_win1.w_atten18(s_fn1);  // if to update structure
    if (s_state2==2) return(1);         // don't update structure
    else			        // update stru
    {
      strcpy(s_fn3,s_fn1);
      i=bw_inkey1.strlocc(s_fn3,FN_SIZE,'.');
      s_fn3[i]=0;
      strcat(s_fn3,".dbk");
      //MessageBox(0, "delete .dbk", "s1", MB_OK);
      bw_inkey1.w_del_file(s_fn3);
      //MessageBox(0, "copy .dbk", "s2", MB_OK);
      bw_inkey1.w_cpy_file(s_fn1,s_fn3);

      close(win_fp[p_fpp]);

      //MessageBox(0, "delete .dbf", "s3", MB_OK);
      bw_inkey1.w_del_file(s_fn1);

      win_fp[p_fpp] = sopen(s_fn1,O_RDWR|O_CREAT|O_BINARY, SH_DENYNO, S_IREAD|S_IWRITE);

      //MessageBox(0, "re-create .dbf", "s4", MB_OK);
      i=w_create_xbase(s_fn1,FN_SIZE,p_fpp);
      if (i!=0) return(1);
      j=w_use_fox(s_fn3,FN_SIZE);
      if (j!=0) return(1);
      w_append_fox(p_fpp);
      w_close_fox();
    }
  }

  if (get_win_rcnt(p_fpp)<=0)
  {
    w_insert_xbase_rec2(p_fpp); // add 3 empty record to empty dbase file to avoid error 
  }

  if (backup==1)
  {
    strcpy(s_fn2,s_fn1);
    w_find_empty_file(s_fn2,FN_SIZE,p_fpp);

    strcpy(s_fn2,s_fn1);
    i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
    s_fn2[i]=0;
    get_win_ext(p_fpp,s_ext,FN_SIZE);
    strcat(s_fn2,s_ext);

    bw_inkey1.w_del_file(s_fn2);
    s_state1=bw_inkey1.w_cpy_file(s_fn1,s_fn2);
    if (s_state1==1) return(1);

    close(win_fp[p_fpp]);

    win_fp[p_fpp]=sopen(s_fn2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
    if (win_fp[p_fpp]<0) return(1);

  }

  set_win_state_bff_in_use(p_fpp,1);

  getcwd(str,FN_SIZE);
  set_win_basedir(p_fpp,str,FN_SIZE);
  set_win_basename(p_fpp,p_fn1,p_fn1_size);

  return(0);
}

long bw_xbase::w_read_recno(int p_fp)
{
  unsigned char str[SMG_SIZE];  // bug ??? // char* to unsigned char* ??? // ok now
  int  c1,c2,c3,c4;
  long rn;

  lseek(p_fp,4,0);
  read(p_fp,str,10);

  c4=str[0];
  c3=str[1];
  c2=str[2];
  c1=str[3];

  rn=c1*256*256*256+c2*256*256+c3*256+c4;

  return(rn);
}
int bw_xbase::w_create_xbase(char *p_fn1,int p_fn1_size,int p_fpp)
{
  int           i,j,k;
  int           s_fp1;
  char          str2[16+1];
  unsigned int  s_tmpn1;
  unsigned char c1,c2,c3,c4;
  char          str1[SMG_SIZE];

  s_fp1=sopen(p_fn1,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_fp1<0) return(1);

  j=get_win_lcnt(p_fpp,0);   /* write head line 1 */
  s_tmpn1=(j+1)*32+1;
  c1=s_tmpn1/256;
  c2=s_tmpn1-c1*256;
  s_tmpn1=get_win_lcnt(p_fpp,1);
  s_tmpn1++;
  c3=s_tmpn1/256;
  c4=s_tmpn1-c3*256;

  for (i=0;i<=16;i++) str2[i]=0;
  str2[0 ]=3;
  str2[1 ]=94;
  str2[2 ]=5;
  str2[3 ]=25;
  str2[8 ]=c2;
  str2[9 ]=c1;
  str2[10]=c4;
  str2[11]=c3;
  write(s_fp1,str2,16);

  for (i=0;i<=15;i++) str2[i]=0;
  write(s_fp1,str2,16);

  s_tmpn1=1;

  for (i=bw_fldstru1.get_t2_fldpoin(p_fpp,0);i<=bw_fldstru1.get_t2_fldpoin(p_fpp,1);i++)
  {
    bw_fldstru1.setc_t2_fldname(i,10,0);
    bw_fldstru1.get_t2_fldname(i,str1,20);
    for (k=0;k<=9;k++) str1[k]=bw_inkey1.upper(str1[k]);

    write(s_fp1,str1,11);

    if (bw_fldstru1.get_t2_fldtype(i)=='c') str1[0]='C';
    else
    {
      if (bw_fldstru1.get_t2_fldtype(i)=='m') str1[0]='M';
      else
      {
	if (bw_fldstru1.get_t2_fldtype(i)=='l') str1[0]='L';
	else
	{
	  if (bw_fldstru1.get_t2_fldtype(i)=='b') str1[0]='B';
	  else  str1[0]='N';
        }
      }
    }

    write(s_fp1,str1,1);

    c1=s_tmpn1/256;
    c2=s_tmpn1-c1*256;
    str1[0]=c2;
    str1[1]=c1;
    str1[2]=0;
    str1[3]=0;
    s_tmpn1=s_tmpn1+bw_fldstru1.get_t2_fldlen(i);
    write(s_fp1,str1,4);

    c1=bw_fldstru1.get_t2_fldlen(i);
    c2=bw_fldstru1.get_t2_flddec(i);
    str1[0]=c1;
    str1[1]=c2;
    for (k=2;k<=15;k++) str1[k]=0;
    write(s_fp1,str1,16);
  }

  str1[0]=13;
  str1[1]=26;
  write(s_fp1,str1,2);

  close(s_fp1);

  set_win_rcnt(p_fpp,0);

  return(0);
}

int bw_xbase::w_compare_xbase(int p_fp,int p_fpp)
{
  int           i,k;
  char          sfn1[SMG_SIZE];
  char          str2[SMG_SIZE];
  unsigned char uc1,uc2;
  char          fldname[SMG_SIZE];
  char          fldtype;
  unsigned int  fldlen,flddec;
  unsigned char str1[SMG_SIZE];

  read(p_fp,str1,16);
  if (eof(p_fp))
  {
    set_win_rcnt(p_fpp,0);
    return(1);
  }

  uc1=str1[4];   /* calculate record number */
  uc2=str1[5];
  set_win_rcnt(p_fpp,uc2*256+uc1);
  uc1=str1[6];
  uc2=str1[7];
  set_win_rcnt(p_fpp,get_win_rcnt(p_fpp)+(uc2*256+uc1)*256*256);

  read(p_fp,str1,16);
  if (eof(p_fp))
  {
    set_win_rcnt(p_fpp,0);
    return(1);
  }

  for (k=bw_fldstru1.get_t2_fldpoin(p_fpp,0);k<=bw_fldstru1.get_t2_fldpoin(p_fpp,1);k++)
  {
    read(p_fp,str1,16);
    if (eof(p_fp))
    {
      set_win_rcnt(p_fpp,0);
      return(1);
    }

    for (i=0;i<=10;i++) fldname[i]=str1[i];

    fldtype=str1[11];                                    

    read(p_fp,str1,16);
    if (eof(p_fp))
    {
      set_win_rcnt(p_fpp,0);
      return(1);
    }

    fldlen=str1[0];
    flddec=str1[1];
    bw_fldstru1.get_t2_fldname(k,sfn1,20);

    for (i=0;i<(int)strlen(sfn1);i++)
    {
      str2[i+0]=bw_inkey1.upper(bw_fldstru1.getc_t2_fldname(k,i));
      str2[i+1]=0;
    }

    if (strcmp(str2,fldname)!=0)
    {
      set_win_rcnt(p_fpp,0);
      return(1);
    }

    if (bw_inkey1.upper(bw_fldstru1.get_t2_fldtype(k))!=fldtype)
    {
      set_win_rcnt(p_fpp,0);
      return(1);
    }

    if (bw_fldstru1.get_t2_fldlen(k)!=(int)fldlen)
    {
      set_win_rcnt(p_fpp,0);
      return(1);
    }

    if (bw_fldstru1.get_t2_flddec(k)!=(int)flddec)
    {
      set_win_rcnt(p_fpp,0);
      return(1);
    }
  }

  read(p_fp,str1,1);
  if (str1[0]!=13)
  {
    set_win_rcnt(p_fpp,0);
    return(1);
  }

  return(0);
}

int bw_xbase::w_read_xbase_rec(long recno,int p_fpp)
{
  long i,j;
  int  s_state1;

  s_state1=w_loc_xbase_rec(recno,p_fpp);

  if (s_state1!=0)
  {
    for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar(i,' ');
    return(1);
  }

  j=read_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

  if ((eof(win_fp[p_fpp]))&&(j<get_win_lcnt(p_fpp,1)+1))
  {
    for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar(i,' ');
    return(1);
  }

  return(0);
}

int bw_xbase::w_save_xbase_rec(long recno,int p_fpp)
{
  int s_state1;

  s_state1=w_loc_xbase_rec(recno,p_fpp);

  if (s_state1!=0) return(1);

  write_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

  return(0);
}

int bw_xbase::w_append_xbase_rec(long recno,int p_fpp)
{
  long i;
  int s_state1;

  s_state1=w_loc_xbase_rec(recno,p_fpp);

  //if (s_state1!=0) return(1);

  write_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

  return(0);
}

int bw_xbase::w_loc_xbase_rec(long recno,int p_fpp)
{
  long i;

  win_state_dbf_err=0;

  if (recno<=0) return(1);
  //if (recno>get_win_rcnt(p_fpp)) return(1);  //get_win_rcnt(p_fpp) total record number

  i=(get_win_lcnt(p_fpp,0)+1)*32+1+(recno-1)*(get_win_lcnt(p_fpp,1)+1); //get_win_lcnt(p_fpp,0) field number,get_win_lcnt(p_fpp,1) record length

  lseek(win_fp[p_fpp],i,0);

  if (eof(win_fp[p_fpp])) return(1);
  else return(0);
}

long bw_xbase::w_up_xbase_rec(long recno,int p_fpp)
{
  int  s_state1;
  long recno1;
  long recno2;

  recno1=recno;

  if (recno1>get_win_rcnt(p_fpp)+1) recno1=get_win_rcnt(p_fpp)+1;

  recno2=recno1;

  while (1)
  {
    if (recno1>1) recno1--;
    else
    {
      if (w_xbase_rec_del()==1)
      {
	w_clr_recvar(p_fpp);
	set_win_recvar(0,'*');
      }
      else w_clr_recvar(p_fpp);

      win_state_dbf_err=1;
      break;
    }
    s_state1=w_read_xbase_rec(recno1,p_fpp);
    if (s_state1!=0)
    {
      win_state_dbf_err=1;
      break;
    }
    if (w_xbase_rec_del()==1) continue;
    break;
  }
  if (win_state_dbf_err==1) return(recno2);
  else return(recno1);
}

long bw_xbase::w_down_xbase_rec(long recno,int p_fpp)
{
  int  s_state1;
  long recno1;
  long recno2;

  recno1=recno;

  if (recno1<0) recno1=0;

  recno2=recno1;

  while (1)
  {
    if (recno1<get_win_rcnt(p_fpp)) recno1++;
    else
    {
      if (w_xbase_rec_del()==1)
      {
	w_clr_recvar(p_fpp);
	set_win_recvar(0,'*');
      }
      else w_clr_recvar(p_fpp);

      win_state_dbf_err=1;
      break;
    }
    s_state1=w_read_xbase_rec(recno1,p_fpp);
    if (s_state1!=0)
    {
      win_state_dbf_err=1;
      break;
    }
    if (w_xbase_rec_del()==1) continue;
    break;
  }
  if (win_state_dbf_err==1) return(recno2);
  else return(recno1);
} 

int bw_xbase::w_xbase_rec_del()
{
  if (get_win_recvar(0)=='*') return(1);
  else return(0);
}

int bw_xbase::w_dele_xbase_rec(long recno,int p_fpp)
{
  int  s_state1;
  char str[SMG_SIZE];

  s_state1=w_loc_xbase_rec(recno,p_fpp);

  if (s_state1!=0) return(1);

  str[0]='*';
  write(win_fp[p_fpp],str,1);

  return(0);
}

int bw_xbase::w_insert_xbase_rec(long recno,int p_fpp,int aft)
{
  int  s_state1;
  int  s_state2;
  int  i;

  if (recno>0)
  {
    s_state1=w_loc_xbase_rec(recno,p_fpp);
    if (s_state1!=0) return(1);

    s_state2=aft;  // aft ,1 insert before , 0 insert after
    if (s_state2==0)
    {
      recno++;
      win_insert_dir=1;      // for link dbf
    }
    else win_insert_dir=0;   // for link dbf
  }
  else
  {
    recno=1;
    win_insert_dir=1;        // for link dbf
  }

  s_state1=w_read_xbase_rec(recno,p_fpp);

  for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar2(i,0,get_win_recvar(i));  // current record copy to buffer0

  if (get_win_carry_on(p_fpp)!=1) w_clr_recvar(p_fpp);

  if (s_state1==0) w_save_xbase_rec(recno,p_fpp);  // write empty record
  else
  {
    w_append_xbase_rec(recno,p_fpp);
    set_win_rcnt(p_fpp,get_win_rcnt(p_fpp)+1);
    w_set_xbase_recno(get_win_rcnt(p_fpp),p_fpp);
    return(0);
  }

  while (1)
  {
    recno++;
    s_state1=w_read_xbase_rec(recno,p_fpp);  // read current record
    for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar2(i,1,get_win_recvar(i)); // put current rec to buffer1
    for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar(i,get_win_recvar2(i,0)); // put buffer0(prev rec) to current rec
    if (s_state1==0) w_save_xbase_rec(recno,p_fpp); // write this record
    else
    {
      w_append_xbase_rec(recno,p_fpp);
      set_win_rcnt(p_fpp,get_win_rcnt(p_fpp)+1);
      w_set_xbase_recno(get_win_rcnt(p_fpp),p_fpp);
      return(0);
    }

    for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar2(i,0,get_win_recvar2(i,1)); // put buffer1 to buffer0
  }
}

int bw_xbase::w_insert_xbase_rec2(int p_fpp) // for empty database ,add three empty records
{
  long recno1;
  int  s_state1;
  int  s_state2;
  int  i;

  w_clr_recvar(p_fpp);

  w_loc_xbase_rec(1,p_fpp);
  write_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

  w_loc_xbase_rec(2,p_fpp);
  write_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

  w_loc_xbase_rec(3,p_fpp);
  write_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

  w_set_xbase_recno(3,p_fpp);

  return(0);

}

int bw_xbase::w_pack_xbase_base(int p_fpp)
{
  long  s_recno1,s_recno2;
  long  s_fl,s_fl2;
  int   s_state1;
//  int   i,j;
//  int   stn1;
  int   s_fh;
//  char  c1;
  char  s_tmpc1[32+1];
  char  s_tmpc2[SMG_SIZE];
  char  s_tmpc3[FN_SIZE];
  char  s_tmpc4[SMG_SIZE];
  char  s_tmpc5[SMG_SIZE];

  /* find tmp pack file name */
  get_win_ext(p_fpp,s_tmpc2,SMG_SIZE);

  strcpy(s_tmpc5,"tmp_pack");
  w_find_empty_file(s_tmpc5,SMG_SIZE,p_fpp);
  get_win_ext(p_fpp,s_tmpc4,SMG_SIZE);
  set_win_ext(p_fpp,s_tmpc2,SMG_SIZE);
  strcpy(s_tmpc3,"tmp_pack");
  strcat(s_tmpc3,s_tmpc4);

  /* sopen tmp pack file */
  s_fh=sopen(s_tmpc3,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (s_fh<0) return(1);

  /* copy header */
  lseek(win_fp[p_fpp],0,0);
  while (1)
  {
    read(win_fp[p_fpp],s_tmpc1,32);
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
    s_state1=w_loc_xbase_rec(s_recno1,p_fpp);
    if (s_state1!=0) break;

    read_win_recvar(win_fp[p_fpp],get_win_lcnt(p_fpp,1)+1);

    if (eof(win_fp[p_fpp])) break;

    if (get_win_recvar(0)=='*') continue;

    s_recno2++;

    write_win_recvar(s_fh,get_win_lcnt(p_fpp,1)+1);
  }

  /* write tail */
  s_tmpc2[0]=26;
  s_tmpc2[1]=0;
  write(s_fh,s_tmpc2,1);

  /* set recno */
  w_set_fox_recno2(s_recno2,s_fh);
  set_win_rcnt(p_fpp,s_recno2);

  /* copy back file */
  lseek(s_fh,0,0);
  lseek(win_fp[p_fpp],0,0);
  s_fl=0;
  s_fl2=0;
  while (1)
  {
    s_recno1=read_win_recvar(s_fh,REC_LEN);

    s_fl2=write_win_recvar(win_fp[p_fpp],s_recno1);

    s_fl=s_fl+s_fl2;
    if (eof(s_fh)) break;
  }

  /* dele pack file */
  close(s_fh);

  bw_inkey1.w_del_file(s_tmpc3);

  chsize(win_fp[p_fpp],s_fl);

  return(0);
}

int bw_xbase::w_set_xbase_recno(long recno,int p_fpp)
{
  unsigned char c1,c2,c3,c4;
  unsigned char str[5];

  set_win_rcnt(p_fpp,recno);

  c1=(unsigned char)(recno/256/256/256);
  c2=(unsigned char)((recno-c1*256*256*256)/256/256);
  c3=(unsigned char)((recno-c1*256*256*256-c2*256*256)/256);
  c4=(unsigned char)(recno-c1*256*256*256-c2*256*256-c3*256);

  str[0]=c4;
  str[1]=c3;
  str[2]=c2;
  str[3]=c1;

  lseek(win_fp[p_fpp],4,0);
  write(win_fp[p_fpp],str,4);

  return(0);
}
int bw_xbase::w_set_fox_recno2(long recno,int p_fp)
{
  unsigned char c1,c2,c3,c4;
  unsigned char str[5];

  c1=(unsigned char )(recno/256/256/256);
  c2=(unsigned char )((recno-c1*256*256*256)/256/256);
  c3=(unsigned char )((recno-c1*256*256*256-c2*256*256)/256);
  c4=(unsigned char )(recno-c1*256*256*256-c2*256*256-c3*256);

  str[0]=c4;
  str[1]=c3;
  str[2]=c2;
  str[3]=c1;

  lseek(p_fp,4,0);
  write(p_fp,str,4);

  return(0);
}

int bw_xbase::w_commit_xbase(int backup,int p_fpp)
{
  int  i,j,k;
  int  s_state1;
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];    

  if (get_win_state_dbf_modi(p_fpp)==0) return(0);

  if (backup==0) return(1);

  get_win_basedir(p_fpp,str1,FN_SIZE);

  bw_inkey1.w_set_dir(str1);

  get_win_basename(p_fpp,s_fn1,FN_SIZE);

  strcpy(s_fn2,s_fn1);
  i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
  s_fn2[i]=0;
  get_win_ext(p_fpp,str2,FN_SIZE);
  strcat(s_fn2,str2);

  // delete dbf file
  while(1)
  {
    j=bw_inkey1.w_del_file(s_fn1);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(s_fn1);     /* delete error */
      if (k==1) continue;            /* retry        */
      else  return(1);               /* cancel       */
    }
  }

  // copy to dbf file
  while(1)
  {
    j=bw_inkey1.w_cpy_file(s_fn2,s_fn1);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(s_fn1);     /* copy error */
      if (k==1) continue;            /* retry      */
      else  return(1);               /* cancel     */
    }
  }

  return(0);
}

int bw_xbase::w_rollback_xbase(int backup,int p_fpp)
{
  long s_recno1;
  int  i,j,k;
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];
  char str3[FN_SIZE];
  int  s_fh;

  if (get_win_state_dbf_modi(p_fpp)==0) return(0);

  if (backup==0) return(1);

  get_win_basedir(p_fpp,str1,FN_SIZE);

  bw_inkey1.w_set_dir(str1);

  /* make backup file name */
  bw_win1.get_win_tabname(1,p_fpp,s_fn2,FN_SIZE);
  bw_inkey1.strtrim(s_fn2,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
  s_fn2[i]=0;
  get_win_ext(p_fpp,str3,FN_SIZE);
  strcat(s_fn2,str3);

  close(win_fp[p_fpp]);

  bw_win1.get_win_tabname(1,p_fpp,s_fn1,FN_SIZE);
  bw_inkey1.strtrim(s_fn1,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  strcat(s_fn1,".dbf");

  // delete tmp file
  while(1)
  {
    j=bw_inkey1.w_del_file(s_fn2);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(s_fn2);   /* delete error */
      if (k==1) continue;          /* retry        */
      else return(1);              /* cancel       */
    }
  }

  // copy to tmp file
  while(1)
  {
    j=bw_inkey1.w_cpy_file(s_fn1,s_fn2);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(s_fn2);   /* copy error */
      if (k==1) continue;          /* retry      */
      else return(1);              /* cancel     */
    }
  }

  win_fp[p_fpp]=sopen(s_fn2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (win_fp[p_fpp]<0) return(1);

  set_win_rcnt(p_fpp,w_read_recno(win_fp[p_fpp]));

  return(0);
}

int bw_xbase::w_append_sdf(char *p_fn,int p_fn_size,int p_fpp)
{
  long recno;
  int  i,j;
//  char s_tmpc1[SMG_SIZE];
  //char s_fn4[FN_SIZE];
  FILE *s_fh;

  s_fh=fopen(p_fn,"r");
  if (s_fh==NULL) return(1);

  /* find max recno */
  recno=get_win_rcnt(p_fpp);

  i=0;
  while (1)
  {
    fgets_win_recvar(s_fh,REC_LEN);

    w_append_xbase_rec(recno,p_fpp);
    set_win_rcnt(p_fpp,get_win_rcnt(p_fpp)+1);
    recno++;

    i++;

    if (feof(s_fh)) break;
  }

  w_set_xbase_recno(recno,p_fpp);

  fclose(s_fh);

  return(i);
}
int bw_xbase::w_copy_sdf(char *p_fn,int p_fn_size,int p_fpp)
{
  long  i;
  int   j;
//  int   exist;
//  char  s_tmpc1[SMG_SIZE];
  //char  s_fn4[FN_SIZE];
  FILE *s_fp1;

  s_fp1=fopen(p_fn,"w");
  if (s_fp1==NULL) return(0);

  i=0;
  while (1)
  {
    i=w_down_xbase_rec(i,p_fpp);
    if (win_state_dbf_err==1) break;

    set_win_recvar(get_win_lcnt(p_fpp,1)+1,'\n');
    set_win_recvar(get_win_lcnt(p_fpp,1)+2,0);

    fputs_win_recvar(s_fp1);

    i++;
  }

  fclose(s_fp1);

  return(i);
}
int bw_xbase::w_zap_xbase(int p_fpp)
{
  long i;

  i=0;

  w_set_xbase_recno(i,p_fpp);

  return(0);
}

int bw_xbase::w_clr_recvar(int p_fpp)
{
  int i;
  for (i=0;i<=get_win_lcnt(p_fpp,1);i++) set_win_recvar(i,' ');
  return(0);
}

int bw_xbase::w_find_empty_file(char *p_str,int p_str_size,int p_fpp)
{
  int   i,j,k,l;
  char  s_str1[SMG_SIZE];
  char  s_str2[FN_SIZE];
  char  c1,c2;

  strcpy(s_str2,p_str);
  s_str1[0]='$';
  k=bw_inkey1.strlocc(s_str2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;

    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      s_str1[1]=c1;
      s_str1[2]=c2;
      s_str1[3]=0;

      s_str2[k]=0;
      strcat(s_str2,".");
      strcat(s_str2,s_str1);

      l=bw_inkey1.w_find_file(s_str2);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    setc_win_ext(p_fpp,0,'.');
    setc_win_ext(p_fpp,1,'$');
    setc_win_ext(p_fpp,2,c1);
    setc_win_ext(p_fpp,3,c2);
    setc_win_ext(p_fpp,4,0);

    return(0);
  }
  else
  {
    setc_win_ext(p_fpp,0,0);
    return(1);
  }
}

int bw_xbase::w_find_empty_ffile(char *p_str,int p_str_size,int p_wpp)
{
  int   i,j,k,l;
  char  s_str1[SMG_SIZE];
  char  s_str2[FN_SIZE];
  char  c1,c2;

  strcpy(s_str2,p_str);
  s_str1[0]='#';
  k=bw_inkey1.strlocc(s_str2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;

    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      s_str1[1]=c1;
      s_str1[2]=c2;
      s_str1[3]=0;

      s_str2[k]=0;
      strcat(s_str2,".");
      strcat(s_str2,s_str1);

      l=bw_inkey1.w_find_file(s_str2);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    setc_win_fext(p_wpp,0,'.');
    setc_win_fext(p_wpp,1,'#');
    setc_win_fext(p_wpp,2,c1);
    setc_win_fext(p_wpp,3,c2);
    setc_win_fext(p_wpp,4,0);
    return(0);
  }
  else
  {
    setc_win_fext(p_wpp,0,0);
    return(1);
  }
}

int bw_xbase::w_find_empty_mfile(char *p_str,int p_str_size,int p_fpp)
{
  int   i,j,k,l;
  char  s_str1[SMG_SIZE];
  char  s_str2[FN_SIZE];
  char  c1,c2;

  strcpy(s_str2,p_str);
  s_str1[0]='@';
  k=bw_inkey1.strlocc(s_str2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;

    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      s_str1[1]=c1;
      s_str1[2]=c2;
      s_str1[3]=0;

      s_str2[k]=0;
      strcat(s_str2,".");
      strcat(s_str2,s_str1);

      l=bw_inkey1.w_find_file(s_str2);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    setc_win_mem_ext(p_fpp,0,'.');
    setc_win_mem_ext(p_fpp,1,'@');
    setc_win_mem_ext(p_fpp,2,c1);
    setc_win_mem_ext(p_fpp,3,c2);
    setc_win_mem_ext(p_fpp,4,0);
    return(0);
  }
  else
  {
    setc_win_mem_ext(p_fpp,0,0);
    return(1);
  }
}

int bw_xbase::w_close_xbase(int p_fpp)
{
  int  i,j,k;
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];

  if ((get_win_state_dbf_modi(p_fpp)==1)&&
      (get_win_base_backup(p_fpp)==1))
  {
    get_win_basename(p_fpp,s_fn1,FN_SIZE);

    i=bw_win1.w_atten9(s_fn1); // if to save
    if (i==2) { /* don't save file*/ }
    else        // save file
    {
      /* make backup file name */
      strcpy(s_fn2,s_fn1);
      bw_inkey1.strtrim(s_fn2,FN_SIZE);
      i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
      s_fn2[i]=0;
      get_win_ext(p_fpp,str2,FN_SIZE);
      strcat(s_fn2,str2);

      // delete dbf file
      while(1)
      {
        j=bw_inkey1.w_del_file(s_fn1);
        if (j==0) break;
        else
        {
          k=bw_win1.w_atten8(s_fn1); /* delete error */
          if (k==1) continue;        /* retry      */
	  else break;                /* cancel     */
        }
      }

      // copy to dbf file
      while(1)
      {
        j=bw_inkey1.w_cpy_file(s_fn2,s_fn1);
        if (j==0) break;
        else
        {
          k=bw_win1.w_atten8(s_fn1); /* copy error */
          if (k==1) continue;        /* retry      */
	  else break;                /* cancel     */
        }
      }

    }

    set_win_state_dbf_modi(p_fpp,0);
  }

  close(win_fp[p_fpp]);

  if (get_win_base_backup(p_fpp)==1)
  {
    get_win_basename(p_fpp,str1,FN_SIZE);

    strcpy(s_fn2,str1);
    i=bw_inkey1.strlocc(s_fn2,FN_SIZE,'.');
    s_fn2[i]=0;
    get_win_ext(p_fpp,str2,FN_SIZE);
    strcat(s_fn2,str2);

    get_win_basedir(p_fpp,str1,FN_SIZE);

    bw_inkey1.w_set_dir(str1);

    bw_inkey1.w_del_file(s_fn2);
  }

  w_dele_state(p_fpp);

  return(0);
}

int bw_xbase::w_use_fox(char *p_fn1,int p_fn1_size)
{
  int           i,k;
  unsigned char uc1,uc2,uc3,uc4;
  long          j;
  char          fldname[SMG_SIZE];
  char          fldtype;
  unsigned int  fldlen,flddec;
  unsigned char s_tmps1[SMG_SIZE];

  win_use_fh=sopen(p_fn1,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (win_use_fh<0) return(1);

  read(win_use_fh,s_tmps1,16);      /* calculate record number */
  if (eof(win_use_fh)) return(1);

  uc1=s_tmps1[5];      
  uc2=s_tmps1[6];
  uc3=s_tmps1[7];
  uc4=s_tmps1[8];

  set_t4_recnumb(0,((uc4*256+uc3)*256+uc2)*256+uc1);

  read(win_use_fh,s_tmps1,16);
  if (eof(win_use_fh)) return(1);

  k=0;
  j=1;
  while (1)
  {
    read(win_use_fh,s_tmps1,16);
    if (s_tmps1[0]==13) break;
    if (eof(win_use_fh)) return(1);

    for (i=0;i<=10;i++) fldname[i]=s_tmps1[i];
    fldtype=s_tmps1[11];

    read(win_use_fh,s_tmps1,16);
    if (eof(win_use_fh)) return(1);

    fldlen=s_tmps1[0];
    flddec=s_tmps1[1];
    for (i=0;i<(int)strlen(fldname);i++) fldname[i]=bw_inkey1.lower(fldname[i]);
    fldtype=bw_inkey1.lower(fldtype);

    k++;
    j=j+fldlen;
    if (k>=FLD_IN_XBASE) return(1);
    i=k;

    set_t4_fldname(i,fldname,SMG_SIZE);
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

int bw_xbase::w_append_fox(int p_fpp)
{
  int   i,j,k,l,m,n,o,q;
  int   recdel;
  char  s_str1[SMG_SIZE];
  char  s_str2[SMG_SIZE];
  char  s_str3[SMG_SIZE];
  char  s_str4[SMG_SIZE];
  char  s_str5[SMG_SIZE];
  char  s_str6[SMG_SIZE];
  long  r,s,t;
  float f1;
  int   exist;

  r=1;

  while (1)
  {
    i=w_go_fox(r);
    if (i!=0) break;

    s=get_t4_recnumb(2);

    t=read_win_recvar(win_use_fh,s);
    if (eof(win_use_fh)&&(t<s)) break;

    if (get_win_recvar(0)=='*') recdel=1;
	else recdel=0;

    j=s;
    for (i=0;i<=j;i++) set_win_recvar2(i,0,get_win_recvar(i));

    w_clr_recvar(p_fpp);

    for (i=1;i<=get_t4_recnumb(1);i++)
    {
      s_str1[0]=0;

      for (j=get_t4_fldposi(i);j<get_t4_fldposi(i)+get_t4_fldlen(i);j++)
      {
	s_str1[j-get_t4_fldposi(i)+0]=get_win_recvar2(j,0);
	s_str1[j-get_t4_fldposi(i)+1]=0;
      }

      j=get_t4_fldlen(i);
      s_str1[j]=0;

      get_t4_fldname(i,s_str6,SMG_SIZE);

      bw_inkey1.lowers(s_str6);

      l=bw_fldstru1.w_find_fldnum(s_str6,SMG_SIZE,p_fpp);
      if (l!=0) continue;

      if (get_t4_fldtype(i)=='n')
      {
	if ((bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='c')
	  ||(bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='l')
	  ||(bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='m')
	  ||(bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='b'))
	{
	  for (k=strlen(s_str1);k<bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);k++)
          {
	    s_str1[k+0]=' ';
            s_str1[k+1]=0;
          }

	  k=bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);
	  s_str1[k]=0;
	  strcpy(s_str4,s_str1);
       }

	if (bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='n')
	{
	  if (w_there_is_a(s_str1,j)==1)
          {
	    for (k=strlen(s_str1);k<bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);k++)
            {
	      s_str1[k+0]=' ';
              s_str1[k+1]=0;
            }
	    k=bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);
	    s_str1[k]=0;
	    strcpy(s_str4,s_str1);
          }
          else
          {
	    f1=bw_inkey1.str2float(s_str1,SMG_SIZE);
	    sprintf(s_str2,"%31.10f",f1);

	    k=bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);
	    l=bw_fldstru1.w_find_flddec(s_str6,SMG_SIZE,p_fpp);

	    if (l!=0)
            {
	      if (k-l-1<=0) m=0;
	      else m=k-l-1;
              if (l>k-1) n=k-1;
	      else n=l;

              exist=0;
              for (q=0;q<14-m;q++) if ((s_str2[q]!=' ')&&(s_str2[q]!='-')&&(s_str2[q]!='+')&&(s_str2[q]!='0')) exist=1;
              if (exist==1) strcpy(s_str2,"**************.**********");

	      bw_inkey1.strpcut(s_str2,20-m,m,SMG_SIZE,s_str3,SMG_SIZE);
	      bw_inkey1.strpcut(s_str2,20,n+1,SMG_SIZE,s_str5,SMG_SIZE);
	    }
	    else
	    {
	      m=k;
	      n=0;

              exist=0;
              for (q=0;q<14-m;q++) if ((s_str2[q]!=' ')&&(s_str2[q]!='-')&&(s_str2[q]!='+')&&(s_str2[q]!='0')) exist=1;
              if (exist==1) strcpy(s_str2,"**************.**********");

	      bw_inkey1.strpcut(s_str2,20-m,m,SMG_SIZE,s_str3,SMG_SIZE);
	      s_str5[0]=0;

              if (bw_inkey1.str2int(s_str3,strlen(s_str3)+1)==0)
              {
		  for (o=0;o<(int)strlen(s_str3);o++) s_str3[o]=32;
              }
            }


	    strcpy(s_str4,s_str3);
	    strcat(s_str4,s_str5);
          }
        }
      }
      if ((get_t4_fldtype(i)=='c')||(get_t4_fldtype(i)=='l')||(get_t4_fldtype(i)=='m')||(get_t4_fldtype(i)=='b'))
      {
	if ((bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='c')
		||(bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='l')
		||(bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='m')
		||(bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='b'))
	{
	  for (k=strlen(s_str1);k<bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);k++)
          {
	    s_str1[k+0]=' ';
	    s_str1[k+1]=0;
          }
	  k=bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);
	  s_str1[k]=0;
	  strcpy(s_str4,s_str1);
        }

	if (bw_fldstru1.w_find_fldtype(s_str6,SMG_SIZE,p_fpp)=='n')
	{
	  f1=bw_inkey1.str2float(s_str1,SMG_SIZE);
	  sprintf(s_str2,"%31.10f",f1);

	  k=bw_fldstru1.w_find_fldlen(s_str6,SMG_SIZE,p_fpp);
	  l=bw_fldstru1.w_find_flddec(s_str6,SMG_SIZE,p_fpp);

	  if (l!=0)
          {
	    if (k-l-1<=0) m=0;
	    else m=k-l-1;
            if (l>k-1) n=k-1;
	    else n=l;

            exist=0;
            for (q=0;q<14-m;q++) if ((s_str2[q]!=' ')&&(s_str2[q]!='-')&&(s_str2[q]!='+')&&(s_str2[q]!='0')) exist=1;
            if (exist==1) strcpy(s_str2,"**************.**********");

	    bw_inkey1.strpcut(s_str2,20-m,m,SMG_SIZE,s_str3,SMG_SIZE);
	    bw_inkey1.strpcut(s_str2,20,n+1,SMG_SIZE,s_str5,SMG_SIZE);
	  }
	  else
	  {
	    m=k;
	    n=0;

            exist=0;
            for (q=0;q<14-m;q++) if ((s_str2[q]!=' ')&&(s_str2[q]!='-')&&(s_str2[q]!='+')&&(s_str2[q]!='0')) exist=1;
            if (exist==1) strcpy(s_str2,"**************.**********");

	    bw_inkey1.strpcut(s_str2,20-m,m,SMG_SIZE,s_str3,SMG_SIZE);
	    s_str5[0]=0;
	  }

	  strcpy(s_str4,s_str3);
	  strcat(s_str4,s_str5);
        }
      }

      w_bsav_var(p_fpp,s_str6,SMG_SIZE,s_str4,SMG_SIZE);
    }

    set_win_rcnt(p_fpp,get_win_rcnt(p_fpp)+1);

    if (recdel==1) set_win_recvar(0,'*');

    w_append_xbase_rec(get_win_rcnt(p_fpp),p_fpp);

    r++;
  }

  //r=(get_win_lcnt(p_fpp,0)+1)*32+1+get_win_rcnt(p_fpp)*(get_win_lcnt(p_fpp,1)+1);
  //chsize(win_fp[p_fpp],r+1);

  w_set_xbase_recno(get_win_rcnt(p_fpp),p_fpp);

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

int bw_xbase::w_bcpy_var(int p_fpp,char *p_fld,int p_fld_size,char *p_str4,int p_str4_size)
{
  int i,j,k;

  i=bw_fldstru1.w_find_fldnum(p_fld,p_fld_size,p_fpp);
  if (i!=0) return(1);

  j=bw_fldstru1.w_find_fldlen(p_fld,p_fld_size,p_fpp);
  k=bw_fldstru1.w_find_fldposi(p_fld,p_fld_size,p_fpp);
  for (i=1;i<=j;i++)
  {
    if (i-1<p_str4_size)
    {
      p_str4[i-1]=get_win_recvar(i-1+k);
    }
  }
  if (i-1<p_str4_size)
  {
    p_str4[i-1]=0;
  }
  return(0);
}
int bw_xbase::w_bsav_var(int p_fpp,char *p_fld,int p_fld_size,char *p_str4,int p_str4_size)
{
  int  i,j,k;
  char c1;

  i=bw_fldstru1.w_find_fldnum(p_fld,p_fld_size,p_fpp);
  if (i!=0) return(1);

  j=bw_fldstru1.w_find_fldposi(p_fld,p_fld_size,p_fpp);

  k=strlen(p_str4);
  if (k>=p_str4_size) k=p_str4_size-1;
  for (i=1;i<=bw_fldstru1.w_find_fldlen(p_fld,p_fld_size,p_fpp);i++)
  {
    if (i-1>k) c1=' ';
    else
    {
      if ((p_str4[i-1]<' ')&&(p_str4[i-1]>=0)) c1=' ';
      else c1=p_str4[i-1];
    }
    set_win_recvar(i-1+j,c1);
  }
  return(0);
}
int bw_xbase::w_there_is_a(char *p_s,int p_s_size)  
{
  int i;
  int exist;

  exist=0;

  for (i=0;i<p_s_size;i++)
  {
    if (((p_s[i]>='0')&&(p_s[i]<='9'))||(p_s[i]==' ')||(p_s[i]=='-'))
    {
     /* exist=0;*/ // this is number
    }
    else
    {
      exist=1;
      break;
    }
  }

  return(exist);
}





int bw_xbase::get_win_state_bff_in_use(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_state_bff_in_use[p_fpp]);
}
/*
int bw_xbase::get_win_state4(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_state4[p_fpp]);
}
*/
int bw_xbase::get_win_state_dbf_modi(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_state_dbf_modi[p_fpp]);
}
/*
int bw_xbase::get_win_state7(int p_fpp,int p_wpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  return(win_state7[p_fpp][p_wpp]);
}
*/
int bw_xbase::get_win_state_in_srch(int p_wpp,int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  return(win_state_in_srch[p_wpp][p_fpp]);
}
/*
int bw_xbase::get_win_state10(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_state10[pp]);
}
*/
int bw_xbase::set_win_state_bff_in_use(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_state_bff_in_use[p_fpp]=val;
  return(0);
}
/*
int bw_xbase::set_win_state4(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_state4[p_fpp]=val;
  return(0);
}
*/
int bw_xbase::set_win_state_dbf_modi(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_state_dbf_modi[p_fpp]=val;
  return(0);
}
/*
int bw_xbase::set_win_state7(int p_fpp,int p_wpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  win_state7[p_fpp][p_wpp]=val;
  return(0);
}
*/
int bw_xbase::set_win_state_in_srch(int p_wpp,int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  win_state_in_srch[p_wpp][p_fpp]=val;
  return(0);
}
/*
int bw_xbase::set_win_state10(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_state10[p_fpp]=val;
  return(0);
}
*/
long bw_xbase::get_win_recno(int p_fpp,int p_wpp,int p02)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(win_recno[p_fpp][p_wpp][p02]);
}
int bw_xbase::set_win_recno(int p_fpp,int p_wpp,int p02,long val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  win_recno[p_fpp][p_wpp][p02]=val;
  return(0);
}

long bw_xbase::get_win_rcnt(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_rcnt[p_fpp]);
}
int bw_xbase::set_win_rcnt(int p_fpp,long val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_rcnt[p_fpp]=val;
  return(0);
}
int bw_xbase::get_win_lcnt(int p_fpp,int p01)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_lcnt[p_fpp][p01]);
}
int bw_xbase::set_win_lcnt(int p_fpp,int p01,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_lcnt[p_fpp][p01]=val;
  return(0);
}
int bw_xbase::get_win_lnktab(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_lnktab[p_fpp]);
}
int bw_xbase::set_win_lnktab(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_lnktab[p_fpp]=val;
  return(0);
}

int bw_xbase::get_win_scrnvar(int p_wpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_scrnvar[p_wpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_scrnvar(int p_wpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  win_scrnvar[p_wpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_scrnvar[p_wpp][j+0]=p_s1[j];
    win_scrnvar[p_wpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::getc_win_scrnvar(int p_wpp,int pp1)
{
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  return(win_scrnvar[p_wpp][pp1]);
}
int bw_xbase::setc_win_scrnvar(int p_wpp,int pp1,int val)
{
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_SIZE)) return(0);
  win_scrnvar[p_wpp][pp1]=val;
  return(0);
}





int bw_xbase::get_win_memno(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_memno[p_fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_mem_ext(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_LEN) i=EXT_LEN;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mem_ext[p_fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_mem_fn(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_mem_fn[p_fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_win_mem_inuse(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_mem_inuse[p_fpp]);
}
int bw_xbase::get_win_mem_wpp(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_mem_wpp[p_fpp]);
}

int bw_xbase::set_win_memno(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=p_s1_size;

  win_memno[p_fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_memno[p_fpp][j+0]=p_s1[j];
    win_memno[p_fpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_mem_ext(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_LEN) i=EXT_LEN;
  else i=p_s1_size;

  win_mem_ext[p_fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mem_ext[p_fpp][j+0]=p_s1[j];
    win_mem_ext[p_fpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_mem_ext(int p_fpp,int pp1,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_mem_ext[p_fpp][pp1]=val;
  return(0);
}
int bw_xbase::set_win_mem_fn(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_mem_fn[p_fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_mem_fn[p_fpp][j+0]=p_s1[j];
    win_mem_fn[p_fpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_mem_fn(int p_fpp,int pp1,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_mem_fn[p_fpp][pp1]=val;
  return(0);
}
int bw_xbase::set_win_mem_inuse(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_mem_inuse[p_fpp]=val;
  return(0);
}
int bw_xbase::set_win_mem_wpp(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_mem_wpp[p_fpp]=val;
  return(0);
}
int bw_xbase::get_win_bmp_name(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_bmp_name[j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_bmp_name(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

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
int bw_xbase::get_win_basename(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_basename[p_fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_basename(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_basename[p_fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_basename[p_fpp][j+0]=p_s1[j];
    win_basename[p_fpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_basename(int p_fpp,int pp1,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_basename[p_fpp][pp1]=val;
  return(0);
}
int bw_xbase::get_win_basedir(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_basedir[p_fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_basedir(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  win_basedir[p_fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_basedir[p_fpp][j+0]=p_s1[j];
    win_basedir[p_fpp][j+1]=0;
  }

  return(0);
}

int bw_xbase::setc_win_basedir(int p_fpp,int pp1,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_basedir[p_fpp][pp1]=val;
  return(0);
}

int bw_xbase::get_win_base_type(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_base_type[p_fpp]);
}
int bw_xbase::set_win_base_type(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_base_type[p_fpp]=val;
  return(0);
}
int bw_xbase::get_win_base_backup(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_base_backup[p_fpp]);
}
int bw_xbase::set_win_base_backup(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_base_backup[p_fpp]=val;
  return(0);
}
int bw_xbase::get_win_enseri(int p_fpp,int p_wpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  return(win_enseri[p_fpp][p_wpp]);
}
int bw_xbase::get_win_cuseri(int p_fpp,int p_wpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  return(win_cuseri[p_fpp][p_wpp]);
}
int bw_xbase::set_win_enseri(int p_fpp,int p_wpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  win_enseri[p_fpp][p_wpp]=val;
  return(0);
}
int bw_xbase::set_win_cuseri(int p_fpp,int p_wpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  win_cuseri[p_fpp][p_wpp]=val;
  return(0);
}

int bw_xbase::get_win_carry_on(int p_fpp)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  return(win_carry_on[p_fpp]);
}
int bw_xbase::set_win_carry_on(int p_fpp,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  win_carry_on[p_fpp]=val;
  return(0);
}

int bw_xbase::get_win_ext(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_LEN) i=EXT_LEN;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_ext[p_fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_win_ext(int p_fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_LEN) i=EXT_LEN;
  else i=p_s1_size;

  win_ext[p_fpp][0]=0;

  for (j=0;j<i-1;j++)
  {
    win_ext[p_fpp][j+0]=p_s1[j];
    win_ext[p_fpp][j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_ext(int p_fpp,int pp1,int val)
{
  if ((p_fpp<0)||(p_fpp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_ext[p_fpp][pp1]=val;
  return(0);
}

int bw_xbase::get_win_fext(int p_wpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);

  if (p_s1_size>EXT_LEN) i=EXT_LEN;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=win_fext[p_wpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::setc_win_fext(int p_wpp,int pp1,int val)
{
  if ((p_wpp<0)||(p_wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_fext[p_wpp][pp1]=val;
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

int bw_xbase::get_t4_fldname(int fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t4_fldname[fpp][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_t4_fldname(int fpp,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

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

