/* 
 DEC VAX/VMS error 1: fseek() don't clear feof() ,use clearerr()
*/
/* 
 DEC VAX/VMS error 2: there is error when program continue call fputc() 300 times,
	      use fputs()
*/
/*   
  motorola unix system V 
   1.  when define extern function do not use param
   2.  when define function param, not allow ss(int i,int j)
       must like this 
	 ss(i,j)
	 int i,j;
*/
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
#include <direct.h>
#include <dos.h>
#include <io.h>
#include <conio.h>
#include <process.h>
*/
#include <string.h>
/*
#include <stdio.h>
#include <time.h>

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
extern class bw_main         bw_main1;
extern class bw_inkey        bw_inkey1;
extern class bw_win          bw_win1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_getread      bw_getread1;

int bw_xbase::tst_xbase1()
{
  int  i;
  char str[SMG_SIZE];
  char sfn[FN_SIZE];

  bw_getread1.deb_record("bw_xbase::tst_xbase1()");

  for (i=0;i<STRU_NUM;i++)
  {
    get_ms_ext(i,sfn,FN_SIZE);

    sprintf(str,"ptr=%d,recno012=%ld,%ld,%ld,%ld,%ld,%ld,cuseri12345=%d,%d,%d,%d,%d,rcntr=%ld,lcntr-01=%d,%d,ext=%s,lnktab=%d,"
	       ,i
	       ,get_mn_recno(i,1,0)
	       ,get_mn_recno(i,1,1)
	       ,get_mn_recno(i,1,2)
	       ,get_mn_recno(i,2,0)
	       ,get_mn_recno(i,2,1)
	       ,get_mn_recno(i,2,2)
	       ,get_mn_cur_seri(i,1)
	       ,get_mn_cur_seri(i,2)
	       ,get_mn_cur_seri(i,3)
	       ,get_mn_cur_seri(i,4)
	       ,get_mn_cur_seri(i,5)
	       ,get_mn_rec_cntr(i)
	       ,get_mn_fld_cntr(i)
	       ,get_mn_len_cntr(i)
	       ,sfn
	       ,get_mn_lnktab(i));

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_xbase::tst_xbase2()
{
  int  i;
  char str[SMG_SIZE];

  bw_getread1.deb_record("bw_xbase::tst_xbase2()");

  for (i=0;i<STRU_NUM;i++)
  {
    sprintf(str,"ptr=%d,state1357=%d,%d,%d,%d,type=%d,backup=%d,"
	       ,i
	       ,get_mn_state_bff_in_use(i)
	       ,mn_state_dbf_err
	       ,get_mn_state_dbf_modi(i)
	       ,0
	       ,get_mn_base_type(i)
	       ,get_mn_base_backup(i));

    bw_getread1.deb_record(str);
  }

  return(0);
}

int bw_xbase::w_login_xbase(int ptr1)
{
  int i;
  int exist;

  exist=0;

  for (i=ptr1;i<STRU_NUM;i++)
  {
    if (get_mn_state_bff_in_use(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1) return(i);
  
  return(-1);
}

int bw_xbase::w_free_xbase(void)
{
  int i;
  int exist;

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (get_mn_state_bff_in_use(i)==0)
    {
      exist++;
    }
  }

  return(exist);
}

int bw_xbase::w_dele_state(int p_dbptr)
{         
  int i;

  for (i=1;i<WIN_NUM;i++)
  {
    set_mn_recno(p_dbptr,i,0,0);
    set_mn_recno(p_dbptr,i,1,0);
    set_mn_recno(p_dbptr,i,2,0);
  }

  set_mn_rec_cntr(p_dbptr,0);  // total record number
  set_mn_fld_cntr(p_dbptr,0);  // field number
  set_mn_len_cntr(p_dbptr,0);  // record length

  set_mn_lnktab(p_dbptr,0);

  set_mn_state_bff_in_use(p_dbptr,0);
  set_mn_state_dbf_modi(p_dbptr,0);

  set_c_ms_ext(p_dbptr,0,0);
  set_c_ms_basedir(p_dbptr,0,0);
  set_c_ms_basename(p_dbptr,0,0);

  return(0);
}

int bw_xbase::w_open_xbase(char *p_fn,int p_fn_size,int backup,int p_dbptr)
{
  char          s_fn1[FN_SIZE];
  char          s_fn2[FN_SIZE];
  char          s_fn3[FN_SIZE];
  char          str1[FN_SIZE];
  int           i,j;
  int           n_state1,n_state2;
  char          s_ext[FN_SIZE];

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(s_fn1,p_fn);
  bw_inkey1.strtrim(s_fn1,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  strcat(s_fn1,".dbf");

  while(1)
  {
    mn_fh[p_dbptr]=/*s*/open(s_fn1,O_RDWR/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
    if (mn_fh[p_dbptr]>=0) break;            /* open success */
    else if (bw_inkey1.w_find_file(s_fn1,FN_SIZE)==1) // open error , file exist
    {
      n_state1=bw_win1.w_atten8(bw_main1.mn_hwnd1,s_fn1);   /* open error */
      if (n_state1==1) continue;          /* retry      */
      else return(1);                     /* cancel     */
    }
    else                                
    {
      n_state1=bw_win1.w_atten9a(bw_main1.mn_hwnd1,s_fn1); // dbf file not exist , create ? yes no cancel 
      if (n_state1==0) return(1);        // cancel
      else if (n_state1==1)              // yes,create
      {
	i=w_create_xbase(s_fn1,FN_SIZE,p_dbptr);
	if (i!=0) return(1);
	else continue;                   
      }
      else return(1);                    // return 2,no,not create
    }
  }

  n_state1=w_compare_xbase(mn_fh[p_dbptr],p_dbptr);
  if (n_state1==1)                      // differant structure database
  {
    n_state2=bw_win1.w_atten18(bw_main1.mn_hwnd1,s_fn1);  // if to update structure
    if (n_state2==2) return(1);         // don't update structure
    else			         // update structure
    {
      strcpy(s_fn3,s_fn1);
      i=bw_inkey1.str_seek_char_last(s_fn3,FN_SIZE,'.');
      s_fn3[i]=0;
      strcat(s_fn3,".dbk");
      bw_inkey1.w_del_file(s_fn3,FN_SIZE);
      bw_inkey1.w_cpy_file(s_fn1,FN_SIZE,s_fn3,FN_SIZE);

      close(mn_fh[p_dbptr]);

      bw_inkey1.w_del_file(s_fn1,FN_SIZE);

      mn_fh[p_dbptr] = /*s*/open(s_fn1,O_RDWR|O_CREAT/*|O_BINARY, SH_DENYNO*/, S_IREAD|S_IWRITE);  // create new dbf

      i=w_create_xbase(s_fn1,FN_SIZE,p_dbptr);
      if (i!=0) return(1);
      j=w_fox_use(s_fn3,FN_SIZE);
      if (j!=0) return(1);
      w_fox_append(p_dbptr);
      w_fox_close();
    }
  }

  if (get_mn_rec_cntr(p_dbptr)<=0)
  {
    w_insert_xbase_rec2(p_dbptr); // add 3 empty record to empty dbase file to avoid error 
  }

  if (backup==1)
  {
    strcpy(s_fn2,s_fn1);
    w_find_empty_file(s_fn2,FN_SIZE,p_dbptr);

    strcpy(s_fn2,s_fn1);
    i=bw_inkey1.str_seek_char_last(s_fn2,FN_SIZE,'.');
    s_fn2[i]=0;
    get_ms_ext(p_dbptr,s_ext,FN_SIZE);
    strcat(s_fn2,s_ext);

    bw_inkey1.w_del_file(s_fn2,FN_SIZE);
    n_state1=bw_inkey1.w_cpy_file(s_fn1,FN_SIZE,s_fn2,FN_SIZE);
    if (n_state1==1) return(1);

    close(mn_fh[p_dbptr]);

    mn_fh[p_dbptr]=/*s*/open(s_fn2,O_RDWR/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
    if (mn_fh[p_dbptr]<0) return(1);

  }

  set_mn_state_bff_in_use(p_dbptr,1);

  getcwd(str1,FN_SIZE);
  set_ms_basedir(p_dbptr,str1,FN_SIZE);
  set_ms_basename(p_dbptr,p_fn,p_fn_size);

  return(0);
}

int bw_xbase::w_read_recno(int p_fh)
{
  unsigned char ustr1[SMG_SIZE];
  unsigned char uc1,uc2,uc3,uc4;
  int  rn;

  lseek(p_fh,4,0);
  read(p_fh,ustr1,4);

  uc4=ustr1[0];
  uc3=ustr1[1];
  uc2=ustr1[2];
  uc1=ustr1[3];

  rn=uc1*256*256*256+uc2*256*256+uc3*256+uc4;

  return(rn);
}

int bw_xbase::w_create_xbase(char *p_fn,int p_fn_size,int p_dbptr)
{
  int           i,j,k;
  int           s_fh1;
  char          str1[SMG_SIZE];
  char          str2[16+1];
  unsigned int  s_n1;
  unsigned char uc1,uc2,uc3,uc4;
  
  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  s_fh1=/*s*/open(p_fn,O_RDWR|O_CREAT/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
  if (s_fh1<0) return(1);

  j=get_mn_fld_cntr(p_dbptr);   /* write head line 1 */
  s_n1=(j+1)*32+1;
  uc1=s_n1/256;
  uc2=s_n1-uc1*256;
  
  s_n1=get_mn_len_cntr(p_dbptr);
  s_n1++;
  uc3=s_n1/256;
  uc4=s_n1-uc3*256;

  for (i=0;i<16;i++) str2[i]=0;
  
  str2[ 0]=3;
  str2[ 1]=94;
  str2[ 2]=5;
  str2[ 3]=25;
  str2[ 8]=uc2;
  str2[ 9]=uc1;
  str2[10]=uc4;
  str2[11]=uc3;
  
  write(s_fh1,str2,16);

  for (i=0;i<16;i++) str2[i]=0;
  
  write(s_fh1,str2,16);

  s_n1=1;

  for (i=bw_fldstru1.get_t2_fldpntr(p_dbptr,0);i<bw_fldstru1.get_t2_fldpntr(p_dbptr,1);i++)
  {
    //bw_fldstru1.set_c_t2_fldname(i,10,0);
    bw_fldstru1.get_t2_fldname(i,str1,20);
    
    for (k=0;k<10;k++) str1[k]=bw_inkey1.upper(str1[k]);

    write(s_fh1,str1,11);

    if (bw_fldstru1.get_t2_fldtype(i)=='c') str1[0]='C';
    else if (bw_fldstru1.get_t2_fldtype(i)=='m') str1[0]='M';
    else if (bw_fldstru1.get_t2_fldtype(i)=='l') str1[0]='L';
    else if (bw_fldstru1.get_t2_fldtype(i)=='b') str1[0]='B';
    else  str1[0]='N';

    write(s_fh1,str1,1);

    uc1=s_n1/256;
    uc2=s_n1-uc1*256;
    
    str1[0]=uc2;
    str1[1]=uc1;
    str1[2]=0;
    str1[3]=0;
    
    s_n1=s_n1+bw_fldstru1.get_t2_fldlen(i);
    
    write(s_fh1,str1,4);

    uc1=bw_fldstru1.get_t2_fldlen(i);
    uc2=bw_fldstru1.get_t2_flddec(i);
    
    str1[0]=uc1;
    str1[1]=uc2;
    
    for (k=2;k<16;k++) str1[k]=0;
    
    write(s_fh1,str1,16);
  }

  str1[0]=13;
  str1[1]=26;
  write(s_fh1,str1,2);

  close(s_fh1);

  set_mn_rec_cntr(p_dbptr,0);

  return(0);
}

int bw_xbase::w_compare_xbase(int p_fh,int p_dbptr)
{
  int           i,j,k;
  char          sfn1[SMG_SIZE];
  unsigned char ustr1[SMG_SIZE];
  char          str2[SMG_SIZE];
  unsigned char uc1,uc2,uc3,uc4;
  char          s_fldname[SMG_SIZE];
  char          s_fldtype;
  unsigned char n_fldlen;
  unsigned char n_flddec;

  j=read(p_fh,ustr1,16);
  if (/*eof(p_fh)&&*/(j<16))
  {
    set_mn_rec_cntr(p_dbptr,0);
    return(1);
  }

  uc1=ustr1[4];   /* calculate record number */
  uc2=ustr1[5];
  uc3=ustr1[6];
  uc4=ustr1[7];
  
  set_mn_rec_cntr(p_dbptr,uc4*256*256*256+uc3*256*256+uc2*256+uc1);

  j=read(p_fh,ustr1,16);
  if (/*eof(p_fh)&&*/(j<16))
  {
    set_mn_rec_cntr(p_dbptr,0);
    return(1);
  }

  for (k=bw_fldstru1.get_t2_fldpntr(p_dbptr,0);k<bw_fldstru1.get_t2_fldpntr(p_dbptr,1);k++)
  {
    j=read(p_fh,ustr1,16);
    if (/*eof(p_fh)&&*/(j<16))
    {
      set_mn_rec_cntr(p_dbptr,0);
      return(1);
    }

    for (i=0;i<11;i++) s_fldname[i]=ustr1[i];

    s_fldtype=ustr1[11];                                    

    j=read(p_fh,ustr1,16);
    if (/*eof(p_fh)&&*/(j<16))
    {
      set_mn_rec_cntr(p_dbptr,0);
      return(1);
    }

    n_fldlen=ustr1[0];
    n_flddec=ustr1[1];
    
    bw_fldstru1.get_t2_fldname(k,sfn1,20);

    for (i=0;i<(int)strlen(sfn1);i++)
    {
      str2[i+0]=bw_inkey1.upper(bw_fldstru1.get_c_t2_fldname(k,i));
      str2[i+1]=0;
    }

    if (strcmp(str2,s_fldname)!=0)
    {
      set_mn_rec_cntr(p_dbptr,0);
      return(1);
    }

    if (bw_inkey1.upper(bw_fldstru1.get_t2_fldtype(k))!=s_fldtype)
    {
      set_mn_rec_cntr(p_dbptr,0);
      return(1);
    }

    if (bw_fldstru1.get_t2_fldlen(k)!=(int)n_fldlen)
    {
      set_mn_rec_cntr(p_dbptr,0);
      return(1);
    }

    if (bw_fldstru1.get_t2_flddec(k)!=(int)n_flddec)
    {
      set_mn_rec_cntr(p_dbptr,0);
      return(1);
    }
  }

  read(p_fh,ustr1,1);
  if (ustr1[0]!=13)
  {
    set_mn_rec_cntr(p_dbptr,0);
    return(1);
  }

  return(0);
}

int bw_xbase::w_read_xbase_rec(int recno,int p_dbptr)
{
  int  i,j;
  int  n_state1;

  n_state1=w_loc_xbase_rec(recno,p_dbptr);
  
  if (n_state1!=0)
  {
    for (i=0;i<=get_mn_len_cntr(p_dbptr);i++) set_ms_recvar(i,' ');
    return(1);
  }

  j=read_ms_recvar(mn_fh[p_dbptr],get_mn_len_cntr(p_dbptr)+1);

  if (/*eof(mn_fh[p_dbptr])&&*/(j<get_mn_len_cntr(p_dbptr)+1))
  {
    for (i=0;i<=get_mn_len_cntr(p_dbptr);i++) set_ms_recvar(i,' ');
    return(1);
  }

  return(0);
}

int bw_xbase::w_save_xbase_rec(int recno,int p_dbptr)
{
  int n_state1;

  n_state1=w_loc_xbase_rec(recno,p_dbptr);
  if (n_state1!=0) return(1);

  write_ms_recvar(mn_fh[p_dbptr],get_mn_len_cntr(p_dbptr)+1);

  return(0);
}

int bw_xbase::w_append_xbase_rec(int recno,int p_dbptr)
{
  int i;
  int n_state1;

  n_state1=w_loc_xbase_rec(recno,p_dbptr);
  //if (n_state1!=0) return(1);

  write_ms_recvar(mn_fh[p_dbptr],get_mn_len_cntr(p_dbptr)+1);

  return(0);
}

int bw_xbase::w_loc_xbase_rec(int recno,int p_dbptr)
{
  int  i,j;
  char str1[SMG_SIZE];

  mn_state_dbf_err=0;

  if (recno<1) return(1);
  //if (recno>get_mn_rec_cntr(p_dbptr)) return(1);  				//get_mn_rec_cntr(p_dbptr) total record number

  i=(get_mn_fld_cntr(p_dbptr)+1)*32+1+(recno-1)*(get_mn_len_cntr(p_dbptr)+1); //get_mn_fld_cntr(p_dbptr) field number,

  lseek(mn_fh[p_dbptr],i,0);
  
  j=read(mn_fh[p_dbptr],str1,2);

  lseek(mn_fh[p_dbptr],i,0);

  if (/*eof(mn_fh[p_dbptr])&&*/(j<2)) return(1);
  
  return(0);
}

int bw_xbase::w_up_xbase_rec(int recno,int p_dbptr)
{
  int  n_state1;
  int  recno1;
  int  recno2;

  recno1=recno;

  if (recno1>get_mn_rec_cntr(p_dbptr)+1) recno1=get_mn_rec_cntr(p_dbptr)+1;

  recno2=recno1;

  while (1)
  {
    if (recno1>1) recno1--;
    else
    {
      if (w_xbase_rec_del()==1)
      {
	w_clr_recvar(p_dbptr);
	set_ms_recvar(0,'*');
      }
      else w_clr_recvar(p_dbptr);

      mn_state_dbf_err=1;
      break;
    }

    n_state1=w_read_xbase_rec(recno1,p_dbptr);
    if (n_state1!=0)
    {
      mn_state_dbf_err=1;
      break;
    }

    if (w_xbase_rec_del()==1) continue;

    break;
  }

  if (mn_state_dbf_err==1) return(recno2);
  
  return(recno1);
}

int bw_xbase::w_down_xbase_rec(int recno,int p_dbptr)
{
  int  n_state1;
  int  recno1;
  int  recno2;

  recno1=recno;

  if (recno1<0) recno1=0;

  recno2=recno1;

  while (1)
  {
    if (recno1<get_mn_rec_cntr(p_dbptr)) recno1++;
    else
    {
      if (w_xbase_rec_del()==1)
      {
	w_clr_recvar(p_dbptr);
	set_ms_recvar(0,'*');
      }
      else w_clr_recvar(p_dbptr);

      mn_state_dbf_err=1;
      break;
    }

    n_state1=w_read_xbase_rec(recno1,p_dbptr);
    if (n_state1!=0)
    {
      mn_state_dbf_err=1;
      break;
    }

    if (w_xbase_rec_del()==1) continue;

    break;
  }

  if (mn_state_dbf_err==1) return(recno2);
  
  return(recno1);
} 

int bw_xbase::w_xbase_rec_del()
{
  if (get_ms_recvar(0)=='*') return(1);
  else return(0);
}

int bw_xbase::w_dele_xbase_rec(int recno,int p_dbptr)
{
  int  n_state1;
  char str[SMG_SIZE];

  n_state1=w_loc_xbase_rec(recno,p_dbptr);
  if (n_state1!=0) return(1);

  str[0]='*';
  write(mn_fh[p_dbptr],str,1);

  return(0);
}

int bw_xbase::w_insert_xbase_rec(int recno,int p_dbptr,int aft)
{
  int  n_state1;
  int  i;

  if (recno<1) recno=1;

  n_state1=w_loc_xbase_rec(recno,p_dbptr);
  if (n_state1!=0) return(1);

  // aft, 1 insert before, 0 insert after
  if (aft==0) recno++;

  n_state1=w_read_xbase_rec(recno,p_dbptr);
  
  for (i=0;i<=get_mn_len_cntr(p_dbptr);i++)
    set_ms_recvar2(i,0,get_ms_recvar(i));  // current record copy to buffer0
    
  w_clr_recvar(p_dbptr);                     // clear record buffer

  if (n_state1==0) w_save_xbase_rec(recno,p_dbptr);  // write empty record
  else
  {
    w_append_xbase_rec(recno,p_dbptr);
    set_mn_rec_cntr(p_dbptr,get_mn_rec_cntr(p_dbptr)+1);
    w_set_xbase_recno(get_mn_rec_cntr(p_dbptr),p_dbptr);
    return(0);
  }

  while (1)
  {
    recno++;

    n_state1=w_read_xbase_rec(recno,p_dbptr);            // read current record
    
    for (i=0;i<=get_mn_len_cntr(p_dbptr);i++)
      set_ms_recvar2(i,1,get_ms_recvar(i)); // put current rec to buffer1
      
    for (i=0;i<=get_mn_len_cntr(p_dbptr);i++)
      set_ms_recvar(i,get_ms_recvar2(i,0)); // put buffer0(prev rec) to current rec

    if (n_state1==0) w_save_xbase_rec(recno,p_dbptr);    // write this record
    else
    {
      w_append_xbase_rec(recno,p_dbptr);
      set_mn_rec_cntr(p_dbptr,get_mn_rec_cntr(p_dbptr)+1);
      w_set_xbase_recno(get_mn_rec_cntr(p_dbptr),p_dbptr);
      return(0);
    }

    for (i=0;i<=get_mn_len_cntr(p_dbptr);i++)
      set_ms_recvar2(i,0,get_ms_recvar2(i,1)); // put buffer1 to buffer0
  }
}

int bw_xbase::w_insert_xbase_rec2(int p_dbptr) // for empty database ,add three empty records to avoid error
{
  int  recno1;
  int  n_state1;
  int  n_state2;
  int  i;

  w_clr_recvar(p_dbptr);

  w_loc_xbase_rec(1,p_dbptr);
  write_ms_recvar(mn_fh[p_dbptr],get_mn_len_cntr(p_dbptr)+1);

  w_loc_xbase_rec(2,p_dbptr);
  write_ms_recvar(mn_fh[p_dbptr],get_mn_len_cntr(p_dbptr)+1);

  w_loc_xbase_rec(3,p_dbptr);
  write_ms_recvar(mn_fh[p_dbptr],get_mn_len_cntr(p_dbptr)+1);

  w_set_xbase_recno(3,p_dbptr);

  return(0);
}

int bw_xbase::w_fox_pack(char *p_fn,int p_fn_size)
{
  int   n_recno1;
  int   n_recno2;
  //int   s_fl,s_fl2;
  int   n_state1;
  int   i,j,k;
  int   s_fh;
  char  str1[32+1];
  char  str2[SMG_SIZE];
  char  str3[FN_SIZE];
  char  str4[SMG_SIZE];
  char  str5[SMG_SIZE];

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  /* open pack file */
  s_fh=/*s*/open(p_fn,O_RDWR|O_CREAT/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
  if (s_fh<0) return(1);

  /* copy header */
  lseek(mn_use_fh,0,0);

  while (1)
  {
    read(mn_use_fh,str1,32);
    if (str1[0]==13) break;
    write(s_fh,str1,32);
  }

  str2[0]=13;
  str2[1]=0;
  write(s_fh,str2,1);

  /* copy record */
  n_recno1=0;
  n_recno2=0;
  j=get_t4_rec_num(2);

  while (1)
  {
    n_recno1++;

    n_state1=w_fox_go(n_recno1);
    if (n_state1!=0) break;

    k=read_ms_recvar(mn_use_fh,j);

    if (/*eof(mn_use_fh)&&*/(k<j)) break;

    if (get_ms_recvar(0)=='*') continue;

    n_recno2++;

    write_ms_recvar(s_fh,j);
  }

  if (n_recno2<=0)
  {
    w_clr_recvar2();

    n_recno2=n_recno2+3;
    
    write_ms_recvar(s_fh,j);
    write_ms_recvar(s_fh,j);
    write_ms_recvar(s_fh,j);
  }
  
  /* write tail */
  //str2[0]=26;
  //str2[1]=0;
  //write(s_fh,str2,1);

  /* set recno */
  w_fox_set_recno(n_recno2,s_fh);

  close(s_fh);

  return(0);
}

int bw_xbase::w_set_xbase_recno(int recno,int p_dbptr)
{
  unsigned char uc1,uc2,uc3,uc4;
  unsigned char ustr[5];

  set_mn_rec_cntr(p_dbptr,recno);

  uc1=(unsigned char)(recno/256/256/256);
  uc2=(unsigned char)((recno-uc1*256*256*256)/256/256);
  uc3=(unsigned char)((recno-uc1*256*256*256-uc2*256*256)/256);
  uc4=(unsigned char)(recno-uc1*256*256*256-uc2*256*256-uc3*256);

  ustr[0]=uc4;
  ustr[1]=uc3;
  ustr[2]=uc2;
  ustr[3]=uc1;

  lseek(mn_fh[p_dbptr],4,0);
  write(mn_fh[p_dbptr],ustr,4);

  return(0);
}

int bw_xbase::w_fox_set_recno(int recno,int p_fh)
{
  unsigned char uc1,uc2,uc3,uc4;
  unsigned char ustr[5];

  uc1=(unsigned char)(recno/256/256/256);
  uc2=(unsigned char)((recno-uc1*256*256*256)/256/256);
  uc3=(unsigned char)((recno-uc1*256*256*256-uc2*256*256)/256);
  uc4=(unsigned char)(recno-uc1*256*256*256-uc2*256*256-uc3*256);

  ustr[0]=uc4;
  ustr[1]=uc3;
  ustr[2]=uc2;
  ustr[3]=uc1;

  lseek(p_fh,4,0);
  write(p_fh,ustr,4);

  return(0);
}

int bw_xbase::w_commit_xbase(int p_wptr,int backup,int p_dbptr)
{
  int  i,j,k,l;
  int  n_state1;
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];    

  if (get_mn_state_dbf_modi(p_dbptr)==0) return(0);

  if (backup==0) return(1);

  get_ms_basedir(p_dbptr,str1,FN_SIZE);

  bw_inkey1.w_set_dir(str1,FN_SIZE);

  get_ms_basename(p_dbptr,s_fn1,FN_SIZE);

  strcpy(s_fn2,s_fn1);
  i=bw_inkey1.str_seek_char_last(s_fn2,FN_SIZE,'.');
  s_fn2[i]=0;
  get_ms_ext(p_dbptr,str2,FN_SIZE);
  strcat(s_fn2,str2);

  // delete dbf file
  while(1)
  {
    j=bw_inkey1.w_del_file(s_fn1,FN_SIZE);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(bw_main1.get_mn_hwnd(p_wptr),s_fn1);     /* delete error */
      if (k==1) continue;            /* retry        */
      else  return(1);               /* cancel       */
    }
  }

  w_fox_use(s_fn2,FN_SIZE);
  l=w_fox_del_num();

  if (l<200)  // if deleted record's number is 200 or more than pack
  {
    // copy to dbf file
    while(1)
    {
      j=bw_inkey1.w_cpy_file(s_fn2,FN_SIZE,s_fn1,FN_SIZE);
      if (j==0) break;
      else
      {
        k=bw_win1.w_atten8(bw_main1.get_mn_hwnd(p_wptr),s_fn1);     /* copy error */
        if (k==1) continue;            /* retry      */
        else  return(1);               /* cancel     */
      }
    }
  }
  else
  {
    // pack dbf file
    w_fox_pack(s_fn1,FN_SIZE);
  }

  w_fox_close();

  return(0);
}

int bw_xbase::w_rollback_xbase(int p_wptr,int backup,int p_dbptr)
{
  int  n_recno1;
  int  i,j,k;
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char str1[FN_SIZE];
  //char str2[FN_SIZE];
  char str3[FN_SIZE];
  int  s_fh;

  if (get_mn_state_dbf_modi(p_dbptr)==0) return(0);

  if (backup==0) return(1);

  get_ms_basedir(p_dbptr,str1,FN_SIZE);

  bw_inkey1.w_set_dir(str1,FN_SIZE);

  /* make backup file name */
  bw_win1.get_ms_tabname(1,p_dbptr,s_fn2,FN_SIZE);
  bw_inkey1.strtrim(s_fn2,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(s_fn2,FN_SIZE,'.');
  s_fn2[i]=0;
  get_ms_ext(p_dbptr,str3,FN_SIZE);
  strcat(s_fn2,str3);

  close(mn_fh[p_dbptr]);

  bw_win1.get_ms_tabname(1,p_dbptr,s_fn1,FN_SIZE);
  bw_inkey1.strtrim(s_fn1,FN_SIZE);
  i=bw_inkey1.str_seek_char_last(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  strcat(s_fn1,".dbf");

  // delete tmp file
  while(1)
  {
    j=bw_inkey1.w_del_file(s_fn2,FN_SIZE);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(bw_main1.get_mn_hwnd(p_wptr),s_fn2);   /* delete error */
      if (k==1) continue;          /* retry        */
      else return(1);              /* cancel       */
    }
  }

  // copy to tmp file
  while(1)
  {
    j=bw_inkey1.w_cpy_file(s_fn1,FN_SIZE,s_fn2,FN_SIZE);
    if (j==0) break;
    else
    {
      k=bw_win1.w_atten8(bw_main1.get_mn_hwnd(p_wptr),s_fn2);   /* copy error */
      if (k==1) continue;          /* retry      */
      else return(1);              /* cancel     */
    }
  }

  mn_fh[p_dbptr]=/*s*/open(s_fn2,O_RDWR/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
  if (mn_fh[p_dbptr]<0) return(1);

  set_mn_rec_cntr(p_dbptr,w_read_recno(mn_fh[p_dbptr]));

  return(0);
}

int bw_xbase::w_append_from_sdf(char *p_fn,int p_fn_size,int p_dbptr)
{
  int  recno;
  int  i;
  FILE *s_fp;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  s_fp=fopen(p_fn,"r");
  if (s_fp==NULL) return(1);

  /* find max recno */
  recno=get_mn_rec_cntr(p_dbptr);

  i=0;

  while (!feof(s_fp))
  {
    fgets_ms_recvar(s_fp,REC_SIZE);

    w_append_xbase_rec(recno,p_dbptr);
    set_mn_rec_cntr(p_dbptr,get_mn_rec_cntr(p_dbptr)+1);
    
    recno++;
    i++;

    //if (feof(s_fp)) break;
  }

  w_set_xbase_recno(recno,p_dbptr);

  fclose(s_fp);

  return(i);
}

int bw_xbase::w_copy_to_sdf(char *p_fn,int p_fn_size,int p_dbptr)
{
  int   i,j;
  FILE *s_fp1;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(0);

  s_fp1=fopen(p_fn,"w");
  if (s_fp1==NULL) return(0);

  i=0;

  while (1)
  {
    i=w_down_xbase_rec(i,p_dbptr);
    if (mn_state_dbf_err==1) break;

    set_ms_recvar(get_mn_len_cntr(p_dbptr)+1,'\n');
    set_ms_recvar(get_mn_len_cntr(p_dbptr)+2,0);

    fputs_ms_recvar(s_fp1);

    i++;
  }

  fclose(s_fp1);

  return(i);
}

int bw_xbase::w_zap_xbase(int p_dbptr)
{
  w_set_xbase_recno(0,p_dbptr);

  return(0);
}

int bw_xbase::w_clr_recvar(int p_dbptr)
{
  int i;
  
  for (i=0;i<=get_mn_len_cntr(p_dbptr);i++) set_ms_recvar(i,' ');

  return(0);
}

int bw_xbase::w_clr_recvar2()
{
  int i;
  
  for (i=0;i<REC_SIZE;i++) set_ms_recvar(i,' ');

  return(0);
}

int bw_xbase::w_find_empty_file(char *p_fn,int p_fn_size,int p_dbptr)
{
  int   i,j,k,l;
  char  str1[SMG_SIZE];
  char  str2[FN_SIZE];
  char  c1,c2;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(str2,p_fn);
  str1[0]='$';
  k=bw_inkey1.str_seek_char_last(str2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;

    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      str1[1]=c1;
      str1[2]=c2;
      str1[3]=0;

      str2[k]=0;
      strcat(str2,".");
      strcat(str2,str1);

      l=bw_inkey1.w_find_file(str2,FN_SIZE);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    set_c_ms_ext(p_dbptr,0,'.');
    set_c_ms_ext(p_dbptr,1,'$');
    set_c_ms_ext(p_dbptr,2,c1);
    set_c_ms_ext(p_dbptr,3,c2);
    set_c_ms_ext(p_dbptr,4,0);

    return(0);
  }
  else
  {
    set_c_ms_ext(p_dbptr,0,0);
    return(1);
  }
}

int bw_xbase::w_find_empty_ffile(char *p_fn,int p_fn_size,int p_wptr)
{
  int   i,j,k,l;
  char  str1[SMG_SIZE];
  char  str2[FN_SIZE];
  char  c1,c2;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(str2,p_fn);
  str1[0]='#';
  k=bw_inkey1.str_seek_char_last(str2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;

    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      str1[1]=c1;
      str1[2]=c2;
      str1[3]=0;

      str2[k]=0;
      strcat(str2,".");
      strcat(str2,str1);

      l=bw_inkey1.w_find_file(str2,FN_SIZE);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    set_c_ms_fext(p_wptr,0,'.');
    set_c_ms_fext(p_wptr,1,'#');
    set_c_ms_fext(p_wptr,2,c1);
    set_c_ms_fext(p_wptr,3,c2);
    set_c_ms_fext(p_wptr,4,0);
    return(0);
  }
  else
  {
    set_c_ms_fext(p_wptr,0,0);
    return(1);
  }
}

int bw_xbase::w_find_empty_mfile(char *p_fn,int p_fn_size,int p_dbptr)
{
  int   i,j,k,l;
  char  str1[SMG_SIZE];
  char  str2[FN_SIZE];
  char  c1,c2;

  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  strcpy(str2,p_fn);
  str1[0]='@';
  k=bw_inkey1.str_seek_char_last(str2,FN_SIZE,'.');

  for (i=1;i<=36;i++)
  {
    if (i<=10) c1='0'+i-1;
    else c1='a'+i-11;

    for (j=1;j<=36;j++)
    {
      if (j<=10) c2='0'+j-1;
      else c2='a'+j-11;

      str1[1]=c1;
      str1[2]=c2;
      str1[3]=0;

      str2[k]=0;
      strcat(str2,".");
      strcat(str2,str1);

      l=bw_inkey1.w_find_file(str2,FN_SIZE);
      if (l==0) break;
    }
    if (l==0) break;
  }

  if (l==0)
  {
    set_c_mn_mem_ext(p_dbptr,0,'.');
    set_c_mn_mem_ext(p_dbptr,1,'@');
    set_c_mn_mem_ext(p_dbptr,2,c1);
    set_c_mn_mem_ext(p_dbptr,3,c2);
    set_c_mn_mem_ext(p_dbptr,4,0);
    return(0);
  }
  else
  {
    set_c_mn_mem_ext(p_dbptr,0,0);
    return(1);
  }
}

int bw_xbase::w_close_xbase(int p_wptr,int p_dbptr)
{
  int  i,j,k,l;
  char s_fn1[FN_SIZE];
  char s_fn2[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];

  if ((get_mn_state_dbf_modi(p_dbptr)==1)&&
      (get_mn_base_backup(p_dbptr)==1))
  {
    get_ms_basename(p_dbptr,s_fn1,FN_SIZE);

    i=bw_win1.w_atten9(bw_main1.get_mn_hwnd(p_wptr),s_fn1); // if to save
    if (i==2) { /* don't save file*/ }
    else        // save file
    {
      /* make backup file name */
      strcpy(s_fn2,s_fn1);
      bw_inkey1.strtrim(s_fn2,FN_SIZE);
      i=bw_inkey1.str_seek_char_last(s_fn2,FN_SIZE,'.');
      s_fn2[i]=0;
      get_ms_ext(p_dbptr,str2,FN_SIZE);
      strcat(s_fn2,str2);

      // delete dbf file
      while(1)
      {
        j=bw_inkey1.w_del_file(s_fn1,FN_SIZE);
        if (j==0) break;
        else
        {
          k=bw_win1.w_atten8(bw_main1.get_mn_hwnd(p_wptr),s_fn1); /* delete error */
          if (k==1) continue;        /* retry      */
	  else break;                /* cancel     */
        }
      }

      w_fox_use(s_fn2,FN_SIZE);
      l=w_fox_del_num();

      if (l<200)  // if deleted record's number is 200 or more than pack
      {
        // copy to dbf file
        while(1)
        {
          j=bw_inkey1.w_cpy_file(s_fn2,FN_SIZE,s_fn1,FN_SIZE);
          if (j==0) break;
          else
          {
            k=bw_win1.w_atten8(bw_main1.get_mn_hwnd(p_wptr),s_fn1); /* copy error */
            if (k==1) continue;        /* retry      */
	    else break;                /* cancel     */
          }
        }
      }
      else
      {
        // pack dbf file
        w_fox_pack(s_fn1,FN_SIZE);
      }

      w_fox_close();
    }

    set_mn_state_dbf_modi(p_dbptr,0);
  }

  close(mn_fh[p_dbptr]);

  if (get_mn_base_backup(p_dbptr)==1)
  {
    get_ms_basename(p_dbptr,str1,FN_SIZE);

    strcpy(s_fn2,str1);
    i=bw_inkey1.str_seek_char_last(s_fn2,FN_SIZE,'.');
    s_fn2[i]=0;
    get_ms_ext(p_dbptr,str2,FN_SIZE);
    strcat(s_fn2,str2);

    get_ms_basedir(p_dbptr,str1,FN_SIZE);
    bw_inkey1.w_set_dir(str1,FN_SIZE);
    bw_inkey1.w_del_file(s_fn2,FN_SIZE);
  }

  w_dele_state(p_dbptr);

  return(0);
}

int bw_xbase::w_fox_use(char *p_fn,int p_fn_size)
{
  int           i,j,k,m;
  unsigned char uc1,uc2,uc3,uc4;
  char          s_fldname[SMG_SIZE];
  char          s_fldtype;
  unsigned char n_fldlen;
  unsigned char n_flddec;
  unsigned char ustr1[SMG_SIZE];
  
  i=bw_inkey1.str_has_null(p_fn,p_fn_size);
  if (i!=1) return(1);

  mn_use_fh=/*s*/open(p_fn,O_RDWR/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
  if (mn_use_fh<0) return(1);

  m=read(mn_use_fh,ustr1,16);      /* calculate record number */
  if (/*eof(mn_use_fh)&&*/(m<16)) return(1);

  uc1=ustr1[5];      
  uc2=ustr1[6];
  uc3=ustr1[7];
  uc4=ustr1[8];

  set_t4_rec_num(0,((uc4*256+uc3)*256+uc2)*256+uc1);

  m=read(mn_use_fh,ustr1,16);
  if (/*eof(mn_use_fh)&&*/(m<16)) return(1);

  k=0;
  j=1;

  while (1)
  {
    m=read(mn_use_fh,ustr1,16);
    if (ustr1[0]==13) break;
    if (/*eof(mn_use_fh)&&*/(m<16)) return(1);

    for (i=0;i<11;i++) s_fldname[i]=ustr1[i];
    s_fldtype=ustr1[11];

    m=read(mn_use_fh,ustr1,16);
    if (/*eof(mn_use_fh)&&*/(m<16)) return(1);

    n_fldlen=ustr1[0];
    n_flddec=ustr1[1];
    for (i=0;i<(int)strlen(s_fldname);i++) s_fldname[i]=bw_inkey1.lower(s_fldname[i]);
    s_fldtype=bw_inkey1.lower(s_fldtype);

    set_t4_fldname(k,s_fldname,SMG_SIZE);
    set_t4_fldtype(k,s_fldtype);
    set_t4_fldposi(k,j);
    set_t4_fldlen(k,n_fldlen);
    set_t4_flddec(k,n_flddec);

    k++;
    j=j+n_fldlen;
    if (k>=FLD_IN_XBASE) return(1);
  }

  set_t4_rec_num(1,k);
  set_t4_rec_num(2,j);
/*
  sprintf(str,"%ld,%ld,%ld,",t4_rec_num[0]
			    ,t4_rec_num[1]
			    ,t4_rec_num[2]);
  MessageBox(bw_main1.mn_hwnd1,str,"22",MB_OK);
*/
/*
  for (i=1;i<=k;i++)
  {
     sprintf(str,"%s,%d,%d,%d,%d,",t4_fldname[i]
                                  ,t4_fldtype[i]
		                  ,t4_fldlen[i]
			          ,t4_flddec[i]
				  ,t4_fldposi[i]);
     MessageBox(bw_main1.mn_hwnd1,str,"33",MB_OK);
  }
*/
  return(0);
}

int bw_xbase::w_fox_del_num()
{
  int   i,j,k,l;
  int   recdel=0;
  float f1;
  int   exist;

  j=1;
  k=get_t4_rec_num(2);

  while (1)
  {
    i=w_fox_go(j);
    if (i!=0) break;

    l=read_ms_recvar(mn_use_fh,k);
    if (/*eof(mn_use_fh)&&*/(l<k)) break;

    if (get_ms_recvar(0)=='*') recdel++;

    j++;
  }

  return(recdel);
}

int bw_xbase::w_fox_append(int p_dbptr)
{
  int   i,j,k,l,m,n,o,q;
  int   recdel;
  char  s_fldname[SMG_SIZE];
  char  s_fldval1[SMG_SIZE];
  char  s_fldval2[SMG_SIZE];
  char  str2[SMG_SIZE];
  char  str3[SMG_SIZE];
  char  str5[SMG_SIZE];
  int   r,s,t;
  float f1;
  int   exist;

  r=1;

  while (1)
  {
    i=w_fox_go(r);
    if (i!=0) break;

    s=get_t4_rec_num(2);

    t=read_ms_recvar(mn_use_fh,s);
    if (/*eof(mn_use_fh)&&*/(t<s)) break;

    if (get_ms_recvar(0)=='*') recdel=1;
    else recdel=0;

    j=s;
    for (i=0;i<=j;i++) set_ms_recvar2(i,0,get_ms_recvar(i));

    w_clr_recvar(p_dbptr);

    for (i=0;i<get_t4_rec_num(1);i++)
    {
      s_fldval1[0]=0;

      for (j=get_t4_fldposi(i);j<get_t4_fldposi(i)+get_t4_fldlen(i);j++)
      {
	s_fldval1[j-get_t4_fldposi(i)+0]=get_ms_recvar2(j,0);
	s_fldval1[j-get_t4_fldposi(i)+1]=0;
      }

      j=get_t4_fldlen(i);
      s_fldval1[j]=0;

      get_t4_fldname(i,s_fldname,SMG_SIZE);

      bw_inkey1.lowers(s_fldname,SMG_SIZE);

      bw_fldstru1.mn_field_num=bw_fldstru1.w_find_fldnum(s_fldname,SMG_SIZE,p_dbptr);
      if (bw_fldstru1.mn_field_num<0) continue;

      if (get_t4_fldtype(i)=='n')
      {
	if ((bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='c')
	  ||(bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='l')
	  ||(bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='m')
	  ||(bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='b'))
	{
	  for (k=strlen(s_fldval1);k<bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);k++)
          {
	    s_fldval1[k+0]=' ';
            s_fldval1[k+1]=0;
          }

	  k=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);
	  s_fldval1[k]=0;
	  strcpy(s_fldval2,s_fldval1);
       }

	if (bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='n')
	{
	  if (w_there_is_a(s_fldval1,j)==1)
          {
	    for (k=strlen(s_fldval1);k<bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);k++)
            {
	      s_fldval1[k+0]=' ';
              s_fldval1[k+1]=0;
            }
	    k=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);
	    s_fldval1[k]=0;
	    strcpy(s_fldval2,s_fldval1);
          }
          else
          {
	    f1=bw_inkey1.str2float(s_fldval1,SMG_SIZE);
	    sprintf(str2,"%31.10f",f1);

	    k=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);
	    l=bw_fldstru1.w_find_flddec(s_fldname,SMG_SIZE,p_dbptr);

	    if (l>0)
            {
	      if (k-l-1<=0) m=0;
	      else m=k-l-1;
              if (l>k-1) n=k-1;
	      else n=l;

              //exist=0;
              //for (q=0;q<14-m;q++) if ((str2[q]!=' ')&&(str2[q]!='-')&&(str2[q]!='+')&&(str2[q]!='0')) exist=1;
              //if (exist==1) strcpy(str2,"**************.**********");

	      bw_inkey1.cut_string(str2,20-m,m,SMG_SIZE,str3,SMG_SIZE);
	      bw_inkey1.cut_string(str2,20,n+1,SMG_SIZE,str5,SMG_SIZE);
	    }
	    else
	    {
	      m=k;
	      n=0;

              //exist=0;
              //for (q=0;q<14-m;q++) if ((str2[q]!=' ')&&(str2[q]!='-')&&(str2[q]!='+')&&(str2[q]!='0')) exist=1;
              //if (exist==1) strcpy(str2,"**************.**********");

	      bw_inkey1.cut_string(str2,20-m,m,SMG_SIZE,str3,SMG_SIZE);
	      str5[0]=0;

              if (bw_inkey1.str2int(str3,strlen(str3)+1)==0)
              {
		  for (o=0;o<(int)strlen(str3);o++) str3[o]=32;
              }
            }


	    strcpy(s_fldval2,str3);
	    strcat(s_fldval2,str5);
          }
        }
      }
      if ((get_t4_fldtype(i)=='c')||(get_t4_fldtype(i)=='l')||(get_t4_fldtype(i)=='m')||(get_t4_fldtype(i)=='b'))
      {
	if ((bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='c')
	  ||(bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='l')
	  ||(bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='m')
	  ||(bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='b'))
	{
	  for (k=strlen(s_fldval1);k<bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);k++)
          {
	    s_fldval1[k+0]=' ';
	    s_fldval1[k+1]=0;
          }
	  k=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);
	  s_fldval1[k]=0;
	  strcpy(s_fldval2,s_fldval1);
        }

	if (bw_fldstru1.w_find_fldtype(s_fldname,SMG_SIZE,p_dbptr)=='n')
	{
	  f1=bw_inkey1.str2float(s_fldval1,SMG_SIZE);
	  sprintf(str2,"%31.10f",f1);

	  k=bw_fldstru1.w_find_fldlen(s_fldname,SMG_SIZE,p_dbptr);
	  l=bw_fldstru1.w_find_flddec(s_fldname,SMG_SIZE,p_dbptr);

	  if (l>0)
          {
	    if (k-l-1<=0) m=0;
	    else m=k-l-1;
            if (l>k-1) n=k-1;
	    else n=l;

            //exist=0;
            //for (q=0;q<14-m;q++) if ((str2[q]!=' ')&&(str2[q]!='-')&&(str2[q]!='+')&&(str2[q]!='0')) exist=1;
            //if (exist==1) strcpy(str2,"**************.**********");

	    bw_inkey1.cut_string(str2,20-m,m,SMG_SIZE,str3,SMG_SIZE);
	    bw_inkey1.cut_string(str2,20,n+1,SMG_SIZE,str5,SMG_SIZE);
	  }
	  else
	  {
	    m=k;
	    n=0;

            //exist=0;
            //for (q=0;q<14-m;q++) if ((str2[q]!=' ')&&(str2[q]!='-')&&(str2[q]!='+')&&(str2[q]!='0')) exist=1;
            //if (exist==1) strcpy(str2,"**************.**********");

	    bw_inkey1.cut_string(str2,20-m,m,SMG_SIZE,str3,SMG_SIZE);
	    str5[0]=0;
	  }

	  strcpy(s_fldval2,str3);
	  strcat(s_fldval2,str5);
        }
      }

      w_fld_sav(p_dbptr,s_fldname,SMG_SIZE,s_fldval2,SMG_SIZE);
    }

    set_mn_rec_cntr(p_dbptr,get_mn_rec_cntr(p_dbptr)+1);

    if (recdel==1) set_ms_recvar(0,'*');

    w_append_xbase_rec(get_mn_rec_cntr(p_dbptr),p_dbptr);

    r++;
  }

  w_set_xbase_recno(get_mn_rec_cntr(p_dbptr),p_dbptr);

  return(0);
}

int bw_xbase::w_fox_close()
{
  close(mn_use_fh);
  return(0);
}

int bw_xbase::w_fox_go(int recno)
{
  int  i,j;
  char str1[SMG_SIZE];

  i=(get_t4_rec_num(1)+1)*32+1+(recno-1)*get_t4_rec_num(2);

  lseek(mn_use_fh,i,0);
  j=read(mn_use_fh,str1,2);

  lseek(mn_use_fh,i,0);

  if (/*eof(mn_use_fh)&&*/(j<2)) return(1);
  
  return(0);
}

int bw_xbase::w_fld_cpy(int p_dbptr,char *p_fld,int p_fld_size,char *p_val,int p_val_size)  //read from dbf
{
  int i,j,k;

  p_val[0]=0;

  i=bw_fldstru1.w_find_fldnum(p_fld,p_fld_size,p_dbptr);
  if (i<0) return(1);

  j=bw_fldstru1.w_find_fldlen(p_fld,p_fld_size,p_dbptr);
  k=bw_fldstru1.w_find_fldposi(p_fld,p_fld_size,p_dbptr);

  for (i=0;i<j;i++)
  {
    if (i+1+1<=p_val_size)
    {
      p_val[i+0]=get_ms_recvar(i+k);
      p_val[i+1]=0;
    }
  }

  return(0);
}

int bw_xbase::w_fld_sav(int p_dbptr,char *p_fld,int p_fld_size,char *p_val,int p_val_size)  //save to dbf
{
  int  i,j,k,l;
  char c1;
  
  i=bw_inkey1.str_has_null(p_val,p_val_size);
  if (i!=1) return(1);

  i=bw_fldstru1.w_find_fldnum(p_fld,p_fld_size,p_dbptr);
  if (i<0) return(1);

  j=bw_fldstru1.w_find_fldlen(p_fld,p_fld_size,p_dbptr);
  k=bw_fldstru1.w_find_fldposi(p_fld,p_fld_size,p_dbptr);

  l=strlen(p_val);

  for (i=0;i<j;i++)
  {
    if (i+1>l) c1=' ';
    else
    {
      if ((p_val[i]>=0)&&(p_val[i]<' ')) c1=' ';
      else c1=p_val[i];
    }
    
    set_ms_recvar(i+k,c1);
  }

  return(0);
}

int bw_xbase::w_there_is_a(char *p_str,int p_str_size)  
{
  int i;
  int exist;

  exist=0;

  for (i=0;i<p_str_size;i++)
  {
    if (((p_str[i]>='0')&&(p_str[i]<='9'))||(p_str[i]==' ')||(p_str[i]=='-'))
    {
     /* exist=0;*/ // this is number
    }
    else
    {
      exist=1;  // this is a b c ...
      break;
    }
  }

  return(exist);
}




int bw_xbase::get_mn_state_bff_in_use(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_state_bff_in_use[p_dbptr]);
}
int bw_xbase::get_mn_state_dbf_modi(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_state_dbf_modi[p_dbptr]);
}
int bw_xbase::get_mn_state_in_srch(int p_wptr,int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_state_in_srch[p_wptr][p_dbptr]);
}
int bw_xbase::set_mn_state_bff_in_use(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_state_bff_in_use[p_dbptr]=val;
  return(0);
}
int bw_xbase::set_mn_state_dbf_modi(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_state_dbf_modi[p_dbptr]=val;
  return(0);
}
int bw_xbase::set_mn_state_in_srch(int p_wptr,int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_state_in_srch[p_wptr][p_dbptr]=val;
  return(0);
}
int bw_xbase::get_mn_recno(int p_dbptr,int p_wptr,int p02)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(mn_recno[p_dbptr][p_wptr][p02]);
}
int bw_xbase::set_mn_recno(int p_dbptr,int p_wptr,int p02,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  mn_recno[p_dbptr][p_wptr][p02]=val;
  return(0);
}

int bw_xbase::get_mn_rec_cntr(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_rec_cntr[p_dbptr]);
}
int bw_xbase::set_mn_rec_cntr(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_rec_cntr[p_dbptr]=val;
  return(0);
}

int bw_xbase::get_mn_fld_cntr(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_fld_cntr[p_dbptr]);
}
int bw_xbase::set_mn_fld_cntr(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_fld_cntr[p_dbptr]=val;
  return(0);
}

int bw_xbase::get_mn_len_cntr(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_len_cntr[p_dbptr]);
}
int bw_xbase::set_mn_len_cntr(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_len_cntr[p_dbptr]=val;
  return(0);
}
int bw_xbase::get_mn_lnktab(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_lnktab[p_dbptr]);
}
int bw_xbase::set_mn_lnktab(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_lnktab[p_dbptr]=val;
  return(0);
}

int bw_xbase::get_ms_scrnvar(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_scrnvar[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_ms_scrnvar(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  ms_scrnvar[p_wptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_scrnvar[p_wptr][j+0]=p_s1[j];
    ms_scrnvar[p_wptr][j+1]=0;
  }

  return(0);
}
int bw_xbase::get_c_ms_scrnvar(int p_wptr,int ptr1)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  return(ms_scrnvar[p_wptr][ptr1]);
}
int bw_xbase::set_c_ms_scrnvar(int p_wptr,int ptr1,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=SMG_SIZE)) return(0);
  ms_scrnvar[p_wptr][ptr1]=val;
  return(0);
}





int bw_xbase::get_mn_memno(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=mn_memno[p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_mn_mem_ext(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_SIZE) i=EXT_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=mn_mem_ext[p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_mn_mem_fn(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=mn_mem_fn[p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_mn_mem_inuse(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_mem_inuse[p_dbptr]);
}
int bw_xbase::get_mn_mem_wptr(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_mem_wptr[p_dbptr]);
}

int bw_xbase::set_mn_memno(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=p_s1_size;

  mn_memno[p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    mn_memno[p_dbptr][j+0]=p_s1[j];
    mn_memno[p_dbptr][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_mn_mem_ext(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_SIZE) i=EXT_SIZE;
  else i=p_s1_size;

  mn_mem_ext[p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    mn_mem_ext[p_dbptr][j+0]=p_s1[j];
    mn_mem_ext[p_dbptr][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_c_mn_mem_ext(int p_dbptr,int ptr1,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=EXT_SIZE)) return(0);
  mn_mem_ext[p_dbptr][ptr1]=val;
  return(0);
}
int bw_xbase::set_mn_mem_fn(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  mn_mem_fn[p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    mn_mem_fn[p_dbptr][j+0]=p_s1[j];
    mn_mem_fn[p_dbptr][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_c_mn_mem_fn(int p_dbptr,int ptr1,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=FN_SIZE)) return(0);
  mn_mem_fn[p_dbptr][ptr1]=val;
  return(0);
}
int bw_xbase::set_mn_mem_inuse(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_mem_inuse[p_dbptr]=val;
  return(0);
}
int bw_xbase::set_mn_mem_wptr(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_mem_wptr[p_dbptr]=val;
  return(0);
}
int bw_xbase::get_ms_bmp_name(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  p_s1[0]=0;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_bmp_name[j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_ms_bmp_name(char *p_s1,int p_s1_size)
{
  int i,j;

  if (p_s1_size>SMG_SIZE) i=SMG_SIZE;
  else i=p_s1_size;

  ms_bmp_name[0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_bmp_name[j+0]=p_s1[j];
    ms_bmp_name[j+1]=0;
  }

  return(0);
}
int bw_xbase::get_ms_recvar(int rptr)
{
  if ((rptr<0)||(rptr>=REC_SIZE)) return(0);
  return(ms_recvar[rptr]);
}
int bw_xbase::set_ms_recvar(int rptr,int val)
{
  if ((rptr<0)||(rptr>=REC_SIZE)) return(0);
  ms_recvar[rptr]=val;
  return(0);
}
int bw_xbase::get_ms_recvar2(int rptr,int p01)
{
  if ((rptr<0)||(rptr>=REC_SIZE)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(ms_recvar2[rptr][p01]);
}
int bw_xbase::set_ms_recvar2(int rptr,int p01,int val)
{
  if ((rptr<0)||(rptr>=REC_SIZE)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  ms_recvar2[rptr][p01]=val;
  return(0);
}
int bw_xbase::read_ms_recvar(int fh,int len)
{
  int rl;
  if (fh<0) return(0);
  if ((len<0)||(len>REC_SIZE)) return(0);
  rl=read(fh,ms_recvar,len);
  return(rl);
}
int bw_xbase::write_ms_recvar(int fh,int len)
{
  int wl;
  if (fh<0) return(0);
  if ((len<0)||(len>REC_SIZE)) return(0);
  wl=write(fh,ms_recvar,len);
  return(wl);
}
int bw_xbase::fgets_ms_recvar(FILE *fh,int len)
{
  if (fh==NULL) return(0);
  if ((len<0)||(len>REC_SIZE)) return(0);
  fgets(ms_recvar,len,fh);
  return(0);
}
int bw_xbase::fputs_ms_recvar(FILE *fh)
{
  if (fh==NULL) return(0);
  fputs(ms_recvar,fh);
  return(0);
}
int bw_xbase::get_ms_basename(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_basename[p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_ms_basename(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  ms_basename[p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_basename[p_dbptr][j+0]=p_s1[j];
    ms_basename[p_dbptr][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_c_ms_basename(int p_dbptr,int ptr1,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=FN_SIZE)) return(0);
  ms_basename[p_dbptr][ptr1]=val;
  return(0);
}
int bw_xbase::get_ms_basedir(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_basedir[p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_ms_basedir(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>FN_SIZE) i=FN_SIZE;
  else i=p_s1_size;

  ms_basedir[p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_basedir[p_dbptr][j+0]=p_s1[j];
    ms_basedir[p_dbptr][j+1]=0;
  }

  return(0);
}

int bw_xbase::set_c_ms_basedir(int p_dbptr,int ptr1,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=FN_SIZE)) return(0);
  ms_basedir[p_dbptr][ptr1]=val;
  return(0);
}

int bw_xbase::get_mn_base_type(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_base_type[p_dbptr]);
}
int bw_xbase::set_mn_base_type(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_base_type[p_dbptr]=val;
  return(0);
}
int bw_xbase::get_mn_base_backup(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_base_backup[p_dbptr]);
}
int bw_xbase::set_mn_base_backup(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_base_backup[p_dbptr]=val;
  return(0);
}
int bw_xbase::get_mn_enseri(int p_dbptr,int p_wptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_enseri[p_dbptr][p_wptr]);
}
int bw_xbase::get_mn_cur_seri(int p_dbptr,int p_wptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  return(mn_cur_seri[p_dbptr][p_wptr]);
}
int bw_xbase::set_mn_enseri(int p_dbptr,int p_wptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_enseri[p_dbptr][p_wptr]=val;
  return(0);
}
int bw_xbase::set_mn_cur_seri(int p_dbptr,int p_wptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  mn_cur_seri[p_dbptr][p_wptr]=val;
  return(0);
}

int bw_xbase::get_mn_carry_on(int p_dbptr)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  return(mn_carry_on[p_dbptr]);
}
int bw_xbase::set_mn_carry_on(int p_dbptr,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  mn_carry_on[p_dbptr]=val;
  return(0);
}

int bw_xbase::get_ms_ext(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_SIZE) i=EXT_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_ext[p_dbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_ms_ext(int p_dbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);

  if (p_s1_size>EXT_SIZE) i=EXT_SIZE;
  else i=p_s1_size;

  ms_ext[p_dbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    ms_ext[p_dbptr][j+0]=p_s1[j];
    ms_ext[p_dbptr][j+1]=0;
  }

  return(0);
}
int bw_xbase::set_c_ms_ext(int p_dbptr,int ptr1,int val)
{
  if ((p_dbptr<0)||(p_dbptr>=STRU_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=EXT_SIZE)) return(0);
  ms_ext[p_dbptr][ptr1]=val;
  return(0);
}

int bw_xbase::get_ms_fext(int p_wptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);

  if (p_s1_size>EXT_SIZE) i=EXT_SIZE;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=ms_fext[p_wptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_c_ms_fext(int p_wptr,int ptr1,int val)
{
  if ((p_wptr<0)||(p_wptr>=WIN_NUM)) return(0);
  if ((ptr1<0)||(ptr1>=EXT_SIZE)) return(0);
  ms_fext[p_wptr][ptr1]=val;
  return(0);
}

int bw_xbase::get_t4_rec_num(int p03)
{
  if ((p03<0)||(p03>3)) return(0);
  return(t4_rec_num[p03]);
}
int bw_xbase::set_t4_rec_num(int p03,int val)
{
  if ((p03<0)||(p03>3)) return(0);
  t4_rec_num[p03]=val;
  return(0);
}

int bw_xbase::get_t4_fldname(int fldptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t4_fldname[fldptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_xbase::set_t4_fldname(int fldptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  t4_fldname[fldptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t4_fldname[fldptr][j+0]=p_s1[j];
    t4_fldname[fldptr][j+1]=0;
  }

  return(0);
}

int bw_xbase::get_t4_fldtype(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  return(t4_fldtype[fldptr]);
}
int bw_xbase::get_t4_fldlen(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  return(t4_fldlen[fldptr]);
}
int bw_xbase::get_t4_flddec(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  return(t4_flddec[fldptr]);
}
int bw_xbase::get_t4_fldposi(int fldptr)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  return(t4_fldposi[fldptr]);
}

int bw_xbase::set_t4_fldtype(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  t4_fldtype[fldptr]=val;
  return(0);
}
int bw_xbase::set_t4_fldlen(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  t4_fldlen[fldptr]=val;
  return(0);
}
int bw_xbase::set_t4_flddec(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  t4_flddec[fldptr]=val;
  return(0);
}
int bw_xbase::set_t4_fldposi(int fldptr,int val)
{
  if ((fldptr<0)||(fldptr>=FLD_IN_XBASE)) return(0);
  t4_fldposi[fldptr]=val;
  return(0);
}

