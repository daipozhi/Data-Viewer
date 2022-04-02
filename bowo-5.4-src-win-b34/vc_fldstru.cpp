
#define  STRICT
#include <windows.h>
#include <commdlg.h>
 
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <conio.h>
#include <process.h>
#include <string.h>

#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>

#include "vc_bowo.h"

extern class bw_buff         bw_buff1;
extern class bw_edit         bw_edit1;
extern class bw_link         bw_link1;
extern class bw_main         bw_main1;
extern class bw_getread      bw_getread1;
extern class bw_dialog       bw_dialog1;
extern class bw_mbase        bw_mbase1;
extern class bw_xbase        bw_xbase1;
extern class bw_fldstru      bw_fldstru1;
extern class bw_win          bw_win1;
extern class bw_inkey        bw_inkey1;

int bw_fldstru::w_cnt_tabfield(int p_dbptr)
{
  return(get_t2_fldpoin(p_dbptr,1)-get_t2_fldpoin(p_dbptr,0));
}
int bw_fldstru::w_cnt_reclen(int p_dbptr)
{
  int i,j;

  j=0;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    j=j+get_t2_fldlen(i);
  }

  return(j);
}
int bw_fldstru::w_cnt_fldposi(int p_dbptr)
{
  int i,j;

  j=1;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    set_t2_fldposi(i,j);
    j=j+get_t2_fldlen(i);
  }

  return(0);
}
int bw_fldstru::w_read_stru(char *p_fn1,int p_fn1_size,int p_dbptr)
{
  int  exist;
  int  i,j,k,l;
  int  p1,p2,p3,p4,p5,p6,p7;
  int  pp1;
  char str1[SMG_SIZE];  
  char str2[SMG_SIZE];
  FILE *fp1;

  exist=0;

  for (i=0;i<FLD_IN_BASE;i++)
  {
    if (get_t2_fldtype(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);

  pp1=i;

  set_t2_fldpoin(p_dbptr,0,pp1);

  fp1=fopen(p_fn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(p_fn1);
    return(1);
  }

  k=0;

  while (!feof(fp1))
  {
    for (i=0;i<SMG_SIZE;i++) str2[i]=0;

    fgets(str2,SMG_SIZE,fp1);

    for (i=0;i<SMG_SIZE;i++) if ((str2[i]<' ')&&(str2[i]>=0)) str2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_SIZE;i++) if ((str2[i]>' ')||(str2[i]<0)) break;
    if (i>=SMG_SIZE) break;

    for (i=i;i<SMG_SIZE;i++) if (str2[i]==' ') break; /* scan for fldrem */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
					 /* scan for space after fldrem */
    for (i=i;i<SMG_SIZE;i++) if (str2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p1=i;

    for (i=i;i<SMG_SIZE;i++) if (str2[i]==' ') break; /* scan for fldname */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p2=i-1;
					  /* scan for space after fldname */
    for (i=i;i<SMG_SIZE;i++) if (str2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p3=i;

    for (i=i;i<SMG_SIZE;i++) if (str2[i]==' ') break; /* scan for fldtype */
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
				   /* scan for space after fldtype */
    for (i=i;i<SMG_SIZE;i++) if (str2[i]!=' ') break;
    if (i>=SMG_SIZE)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p4=i;
				   /* scan for fldlen*/
    for (i=i;i<SMG_SIZE;i++) if (str2[i]==' ') break;
    p5=i-1;
    if (p4>p5)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
				   /* scan for space after fldlen */
    for (i=i;i<SMG_SIZE;i++) if (str2[i]!=' ') break;
    p6=i;
				   /* scan for space after fldlen */
    for (i=i;i<SMG_SIZE;i++) if (str2[i]==' ') break;
    p7=i-1;

    for (j=p1;j<=p2;j++)
    {
      if (str2[j]==' ') break;
      set_c_t2_fldname(pp1+k,j-p1+0,str2[j]);
      set_c_t2_fldname(pp1+k,j-p1+1,0);
    }

    bw_inkey1.cut_string(str2,p4,p5-p4+1,SMG_SIZE,str1,SMG_SIZE);
    l=bw_inkey1.str2int(str1,SMG_SIZE);

    set_t2_fldtype(pp1+k,str2[p3]);

    if ((get_t2_fldtype(pp1+k)=='c')||(get_t2_fldtype(pp1+k)=='n'))
    {
      set_t2_fldlen(pp1+k,l);
    }
    else
    {
      if (get_t2_fldtype(pp1+k)=='m') set_t2_fldlen(pp1+k,8);
      else
      {
	if (get_t2_fldtype(pp1+k)=='b') set_t2_fldlen(pp1+k,250);
	else set_t2_fldlen(pp1+k,1);
      }
    }

    bw_inkey1.cut_string(str2,p6,p7-p6+1,SMG_SIZE,str1,SMG_SIZE);
    l=bw_inkey1.str2int(str1,SMG_SIZE);
    set_t2_flddec(pp1+k,l);

    k++;
  }

  set_t2_fldpoin(p_dbptr,1,pp1+k);

  fclose(fp1);

  bw_xbase1.set_win_fld_cnt(p_dbptr/*,0*/,w_cnt_tabfield(p_dbptr));   /* field number */
  bw_xbase1.set_win_len_cnt(p_dbptr/*,1*/,  w_cnt_reclen(p_dbptr));   /* record length */
  w_cnt_fldposi(p_dbptr);

  return(0);
}

int bw_fldstru::tst_stru()
{
  int  i;
  char str1[SMG_SIZE];
  char sfn1[SMG_SIZE];

  bw_getread1.deb_record("bw_fldstru::tst_stru()");

  for (i=0;i<=50;i++)
  {
    get_t2_fldname(i,sfn1,20);

    sprintf(str1,"ptr=%d,fldname=%s,type=%c,len=%d,dec=%d,posi=%d,"
	       ,i,sfn1
	       ,get_t2_fldtype(i)
	       ,get_t2_fldlen(i)
	       ,get_t2_flddec(i)
	       ,get_t2_fldposi(i));

    bw_getread1.deb_record(str1);
  }

  for (i=0;i<STRU_NUM;i++)
  {
    sprintf(str1,"ptr=%d,fldpoin01=%d,%d,"
	       ,i,get_t2_fldpoin(i,0)
	       ,get_t2_fldpoin(i,1));

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_fldstru::tst_stru2()
{
  int  i;
  char str1[SMG_SIZE];
  char sfn1[SMG_SIZE];

  bw_getread1.deb_record("bw_fldstru::tst_stru2()");

  for (i=0;i<100;i++)
  {
    get_t2_fldname(i,sfn1,20);

    sprintf(str1,"ptr=%d,fldname=%s,type=%c,len=%d,dec=%d,posi=%d,"
	       ,i
               ,sfn1
	       ,get_t2_fldtype(i)
	       ,get_t2_fldlen(i)
	       ,get_t2_flddec(i)
	       ,get_t2_fldposi(i));

    bw_getread1.deb_record(str1);
  }

  for (i=0;i<STRU_NUM;i++)
  {
    sprintf(str1,"STRU_NUM=%d,dbptr=%d,fldpoin01=%d,%d,"
               ,STRU_NUM
	       ,i
               ,get_t2_fldpoin(i,0)
	       ,get_t2_fldpoin(i,1));

    bw_getread1.deb_record(str1);
  }

  return(0);
}

int bw_fldstru::w_dele_stru(int p_dbptr)
{
  int  i,j;
  int  p1,p3,p4;
  int  n1;
  int  exist;
  char sfn1[SMG_SIZE];

  n1=get_t2_fldpoin(p_dbptr,1)-get_t2_fldpoin(p_dbptr,0);
  if (n1<0) n1=0;

  p1=get_t2_fldpoin(p_dbptr,1); // last current field
  p4=get_t2_fldpoin(p_dbptr,1); // last field
  i=(-1);

  while (n1>0)
  {
    exist=0;

    while (i<STRU_NUM)
    {
      i++;

      if (get_t2_fldpoin(i,0)>=p1)
      {
	exist=1;
	p3=i;
	break;
      }
    }

    if (exist==0) break;

    if (p4<get_t2_fldpoin(p3,1)) p4=get_t2_fldpoin(p3,1);

    for (j=get_t2_fldpoin(p3,0);j<get_t2_fldpoin(p3,1);j++)
    {
      get_t2_fldname(j,sfn1,20);
      set_t2_fldname(j-n1,sfn1,20);

      set_t2_fldtype(j-n1,get_t2_fldtype(j));
      set_t2_fldlen(j-n1,get_t2_fldlen(j));
      set_t2_flddec(j-n1,get_t2_fldlen(j));
      set_t2_fldposi(j-n1,get_t2_fldposi(j));
    }

    set_t2_fldpoin(p3,0,get_t2_fldpoin(p3,0)-n1);
    set_t2_fldpoin(p3,1,get_t2_fldpoin(p3,1)-n1);
  }

  for (i=p4-n1;i<p4;i++)
  {
    set_c_t2_fldname(i,0,0);
    set_t2_fldtype(i,0);
    set_t2_fldlen(i,0);
    set_t2_flddec(i,0);
    set_t2_fldposi(i,0);
  }

  set_t2_fldpoin(p_dbptr,0,0);
  set_t2_fldpoin(p_dbptr,1,0);

  bw_xbase1.set_win_fld_cnt(p_dbptr/*,0*/,0);   /* field number */
  bw_xbase1.set_win_len_cnt(p_dbptr/*,1*/,0);   /* record length */

  return(0);
}

int bw_fldstru::w_find_fldnum(char *p_str,int p_str_size,int p_dbptr)
{
  int  i;
  int  exist;
  char sfn1[SMG_SIZE];

  exist=0;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    get_t2_fldname(i,sfn1,20);

    if (strcmp(p_str,sfn1)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    //win_field_num=i;
    return(i);
  }
  else
  {
    //win_field_num=(-1);
    return(-1);
  }
}
int bw_fldstru::w_find_fldlen(char *p_str,int p_str_size,int p_dbptr)
{
  int  i;
  int  exist;
  char sfn1[SMG_SIZE];

  exist=0;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    get_t2_fldname(i,sfn1,20);

    if (strcmp(p_str,sfn1)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    //win_field_num=i;
    return(get_t2_fldlen(i));
  }
  else
  {
    //win_field_num=(-1);
    return(-1);
  }
}
int bw_fldstru::w_find_fldtype(char *p_str,int p_str_size,int p_dbptr)
{
  int  i;
  int  exist;
  char sfn1[SMG_SIZE];

  exist=0;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    get_t2_fldname(i,sfn1,20);

    if (strcmp(p_str,sfn1)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    //win_field_num=i;
    return(get_t2_fldtype(i));
  }
  else
  {
    //win_field_num=(-1);
    return(-1);
  }
}
int bw_fldstru::w_find_flddec(char *p_str,int p_str_size,int p_dbptr)
{
  int  i;
  int  exist;
  char sfn1[SMG_SIZE];

  exist=0;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    get_t2_fldname(i,sfn1,20);

    if (strcmp(p_str,sfn1)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    //win_field_num=i;
    return(get_t2_flddec(i));
  }
  else
  {
    //win_field_num=(-1);
    return(-1);
  }
}
int bw_fldstru::w_find_fldposi(char *p_str,int p_str_size,int p_dbptr)
{
  int  i;
  int  exist;
  char sfn1[SMG_SIZE];

  exist=0;

  for (i=get_t2_fldpoin(p_dbptr,0);i<get_t2_fldpoin(p_dbptr,1);i++)
  {
    get_t2_fldname(i,sfn1,20);

    if (strcmp(p_str,sfn1)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    //win_field_num=i;
    return(get_t2_fldposi(i));
  }
  else
  {
    //win_field_num=(-1);
    return(-1);
  }
}
int bw_fldstru::w_find_fldpoin0(int i)
{
  return(get_t2_fldpoin(i,0));
}
int bw_fldstru::w_find_fldpoin1(int i)
{
  return(get_t2_fldpoin(i,1));
}

//int bw_fldstru::w_find_fldname(int j,int i,char *p_str,int p_str_len)

int bw_fldstru::w_find_fldname(int p1,int p2,char *p_str,int p_str_size)
{
  char str1[SMG_SIZE];

  p_str[0]=0;

  if ((p2<get_t2_fldpoin(p1,0))||(p2>=get_t2_fldpoin(p1,1))) return(1);

  get_t2_fldname(p2,str1,11);

  bw_inkey1.cpy_string(p_str,p_str_size,str1,SMG_SIZE);

  return(0);
}

int bw_fldstru::w_echo_winrec(int p_wptr)
{
  HWND hnd;
  long s_recno[STRU_NUM];
  int  s_seri[STRU_NUM];
  char s_first[STRU_NUM];
  char s_fldname[SMG_SIZE];
  int  i,j,k,l,m,n,o,p,q,r,s,t,u,v;
  int  p1,p2;
  int  exist;
  char logic;
  char str1[SMG_SIZE];
  char str2[SMG_SIZE];
  char str3[SMG_SIZE];

  HFONT  holdfont,hfont;
  HDC    hdc;

  hdc=GetDC(bw_main1.win_hwnd);
  hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  holdfont=(HFONT)SelectObject(hdc,hfont);

  for (i=0;i<STRU_NUM;i++) s_first[i]=1;

  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(i,p_wptr)==1)&&(bw_xbase1.get_win_lnktab(i)==0))
    {
      s_recno[i]=bw_xbase1.get_win_recno(i,p_wptr,1)-1;
      s_seri[i]=0;
      bw_xbase1.set_win_enseri(i,p_wptr,0);
      exist=1;
    }
  }

  if (exist==0)
  {
    SelectObject(hdc,holdfont);
    ReleaseDC(bw_main1.win_hwnd,hdc);
    return(0);
  }

  for (k=0;k<STRU_NUM;k++)
  {
    if ((bw_win1.get_win_ptr_wins_dbf(k,p_wptr)!=1)||(bw_xbase1.get_win_lnktab(k)!=0)) continue;

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

	    if ((str2[0]!=':')&&(str2[0]!='%')&&(str2[0]!='+')&&(str2[0]!='-')) continue;

	    if (bw_win1.get_t_fldbase(m)!=k) continue;
	    if (bw_win1.get_t_fldseri(m)!=l) continue;

	    strcpy(str1,str2);
            bw_inkey1.cut_string(str1,1,strlen(str1)-1,SMG_SIZE,s_fldname,SMG_SIZE);

	    if (s_seri[k]!=bw_win1.get_t_fldseri(m))
	    {
	      s_recno[k]=bw_mbase1.w_down_rec(k,p_wptr,s_recno[k]);
	      s_seri[k]=bw_win1.get_t_fldseri(m);
	      if (bw_xbase1.win_state_dbf_err==0)
	      {
		bw_xbase1.set_win_enseri(k,p_wptr,l);
		if (bw_xbase1.get_win_recno(k,p_wptr,0)<=0)
                {
		  bw_xbase1.set_win_recno(k,p_wptr,0,1);
		}
//		bw_xbase1.set_win_recno(k,p_wptr,0,s_seri[k]);
	      }
	    }

            if ((l==1)&&(s_first[k]==1))  // set page recno
            {
              bw_xbase1.set_win_recno(k,p_wptr,1,s_recno[k]);
              s_first[k]=0;
            }

		 /* fetch win_field number */
	    win_field_num=w_find_fldnum(s_fldname,SMG_SIZE,k);
	    if (win_field_num<0) continue;

	    p=w_find_fldposi(s_fldname,SMG_SIZE,k);
	    q=w_find_fldlen(s_fldname,SMG_SIZE,k);

	    s=w_find_fldtype(s_fldname,SMG_SIZE,k);
	    if (s=='m') continue;
            if (s=='b') continue;

            str1[0]=0;   // get field string

	    for (o=1;o<=q;o++)
            {
              str1[o-1+0]=bw_xbase1.get_win_recvar(p+o-1);
              str1[o-1+1]=0;
            }

	    strcpy(str3,str1);
            str3[q]=0;

	    str1[bw_win1.get_t_fldlen(m)]=0;

            if (bw_win1.get_t_fldlen(m)<q) v=bw_win1.get_t_fldlen(m);
            else v=q;
            u=bw_inkey1.w_chs_string_cut(str1,v);
            str1[u]=0;

            while (u<v)
            {
              strcat(str1," ");
              u++;
            }

	    if (s=='l')
            {
	      logic=bw_inkey1.upper(str1[0]);

	      if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
              else logic='F';

	      if (bw_xbase1.win_state_dbf_err!=0) str1[0]=' ';
              else str1[0]=logic;
	      str1[1]=0;

	      logic=bw_inkey1.upper(str3[0]);

              if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
              else logic='F';

	      if (bw_xbase1.win_state_dbf_err!=0) str3[0]=' ';
	      else str3[0]=logic;
	      str3[1]=0;

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

	    win_field_num=w_find_fldnum(s_fldname,SMG_SIZE,k);
	    if (win_field_num>=0)
	    {
              r=win_field_num;

              bw_link1.w_save_sv(p_wptr
			,k
			,r-get_t2_fldpoin(k,0)
			,bw_win1.get_t_fldseri(m)
                        ,get_t2_fldposi(r)
			,get_t2_fldlen(r));
	    }
              /*save scrn var to arr*/
	  }
	}
      }                                   
    }
  }

  SelectObject(hdc,holdfont);
  ReleaseDC(bw_main1.win_hwnd,hdc);

  return(0);
}
/*
int bw_fldstru::w_tv_get_read_paint(char *p_str,int p_str_size,int p_wptr,int l,int c,char comm)
{
  HWND hnd;
  int  i,j,q;
  char s1[SMG_SIZE];
  char s2[SMG_SIZE];
  char s3[SMG_SIZE];
  char fldtype;
  char logic;

  if ((p_str[0]!=':')&&(p_str[0]!='+')) return(1);

  if (p_str_size>0) p_str[p_str_size-1]=0;

  i=bw_buff1.get_t3_linecol(p_wptr,l,c);
  j=bw_win1.get_t_fldbase(i);
  bw_inkey1.cut_string(p_str,1,strlen(p_str)-1,p_str_size,s2,SMG_SIZE);
  if (w_find_fldnum(s2,SMG_SIZE,j)!=0) return(1);

  if ((w_find_fldtype(s2,SMG_SIZE,j)=='n')||(w_find_fldtype(s2,SMG_SIZE,j)=='c'))
  {
    w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

    bw_xbase1.set_win_scrnvar(p_wptr,s1,SMG_SIZE);

    fldtype=w_find_fldtype(s2,SMG_SIZE,j);

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      {
        hnd=bw_win1.get_win_hnd(q);
	SetWindowText(hnd,s1);
      }
    }
  }
  else
  {
    if (w_find_fldtype(s2,SMG_SIZE,j)=='l')
    {
      w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

      bw_xbase1.set_win_scrnvar(p_wptr,s1,SMG_SIZE);

      logic=bw_inkey1.upper(bw_xbase1.get_c_win_scrnvar(p_wptr,0));

      if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
      else logic='F';

      bw_xbase1.set_c_win_scrnvar(p_wptr,0,logic);
      bw_xbase1.set_c_win_scrnvar(p_wptr,1,0);

      bw_xbase1.get_win_scrnvar(p_wptr,s1,SMG_SIZE);

      fldtype='c';

      if (p_str[0]=='+')
      {
        q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
        if (q!=0)
        {
          hnd=bw_win1.get_win_hnd(q);
	  SetWindowText(hnd,s1);
        }
      }
    }
    else
    {
      if (w_find_fldtype(s2,SMG_SIZE,j)=='m')
      {
        w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

        bw_xbase1.set_win_memno(j,s1,SMG_SIZE);

        bw_xbase1.set_win_scrnvar(p_wptr,"                     ",20);

	bw_xbase1.set_c_win_scrnvar(p_wptr,bw_win1.get_t_fldlen(i),0);

        fldtype='c';

	if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
        {
	  bw_main1.win_key=0;
	}

        if (p_str[0]=='+')
        {
          q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
          if (q!=0)
          { 
            hnd=bw_win1.get_win_hnd(q);
	    SetWindowText(hnd,"");
          }
        }
      }
      else
      {
	w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

	bw_inkey1.strtrim(s1,SMG_SIZE);

	bw_xbase1.set_win_bmp_name(s1,SMG_SIZE);

	bw_xbase1.set_c_win_scrnvar(p_wptr,0,0);

        fldtype='c';

	if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
        {
	  bw_main1.win_key=0;
	}

        if (p_str[0]=='+')
        {
          q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
          if (q!=0)
          { 
            hnd=bw_win1.get_win_hnd(q);
	    SetWindowText(hnd,"");
          }
        }
      }
    }
  }

  if (p_str[0]==':')
  {
    bw_xbase1.get_win_scrnvar(p_wptr,s3,SMG_SIZE);

    j=bw_getread1.get_read(l-bw_win1.get_win_con(p_wptr,1)+1,
			 c-bw_win1.get_win_con(p_wptr,0)+1,
		       "",
		       s3,
		       bw_win1.get_t_fldlen(i),
		       fldtype,
		       comm,
		       w_find_fldlen(s2,SMG_SIZE,j),
		       w_find_flddec(s2,SMG_SIZE,j),
		       1,1,
		       bw_dialog1.get_win_mv_getp(p_wptr),
		       bw_win1.get_win_ptr_get_rd(p_wptr));

  }

  return(j);
}
*/
int bw_fldstru::w_tv_get_read_g(char *p_str,int p_str_size,int p_wptr,int l,int c,char comm)  // 'tv'(table variant)
{
  HWND hnd;
  int  i,j,q;
  char s1[SMG_SIZE];
  char s2[SMG_SIZE];
  char s3[SMG_SIZE];
  char fldtype;
  char logic;

  if ((p_str[0]!=':')&&(p_str[0]!='+')) return(1);

  if (p_str_size>0) p_str[p_str_size-1]=0;

  i=bw_buff1.get_t3_linecol(p_wptr,l,c);
  j=bw_win1.get_t_fldbase(i);
  bw_inkey1.cut_string(p_str,1,strlen(p_str)-1,p_str_size,s2,SMG_SIZE);
  if (w_find_fldnum(s2,SMG_SIZE,j)<0) return(1);

  if ((w_find_fldtype(s2,SMG_SIZE,j)=='n')||(w_find_fldtype(s2,SMG_SIZE,j)=='c'))
  {
    if (bw_getread1.get_smg_modi(bw_win1.get_win_ptr_get_rd(p_wptr))==1)
    {
      bw_getread1.get_smg_string(bw_win1.get_win_ptr_get_rd(p_wptr),s1,SMG_SIZE);
    }
    else
    {
      w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);
    }

    bw_xbase1.set_win_scrnvar(p_wptr,s1,SMG_SIZE);

    fldtype=w_find_fldtype(s2,SMG_SIZE,j);

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      {
        hnd=bw_win1.get_win_hnd(q);
	SetWindowText(hnd,s1);
	if (bw_main1.win_key!=401) SetFocus(hnd);
      }
    }
  }
  else if (w_find_fldtype(s2,SMG_SIZE,j)=='l')
  {
    w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

    bw_xbase1.set_win_scrnvar(p_wptr,s1,SMG_SIZE);

    logic=bw_inkey1.upper(bw_xbase1.get_c_win_scrnvar(p_wptr,0));

    if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
    else logic='F';

    bw_xbase1.set_c_win_scrnvar(p_wptr,0,logic);
    bw_xbase1.set_c_win_scrnvar(p_wptr,1,0);

    bw_xbase1.get_win_scrnvar(p_wptr,s1,SMG_SIZE);

    fldtype='c';

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      {
        hnd=bw_win1.get_win_hnd(q);
	SetWindowText(hnd,s1);
	if (bw_main1.win_key!=401) SetFocus(hnd);
      }
    }
  }
  else if (w_find_fldtype(s2,SMG_SIZE,j)=='m')
  {
    w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

    bw_xbase1.set_win_memno(j,s1,SMG_SIZE);

    bw_xbase1.set_win_scrnvar(p_wptr,"                     ",20);

    bw_xbase1.set_c_win_scrnvar(p_wptr,bw_win1.get_t_fldlen(i),0);

    fldtype='c';

    if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
    {
      bw_main1.win_key=0;
    }

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      { 
        hnd=bw_win1.get_win_hnd(q);
	SetWindowText(hnd,"");
	if (bw_main1.win_key!=401) SetFocus(hnd);
      }
    }
  }
  else
  {
    w_get_tab_var(s2,SMG_SIZE,j,s1,SMG_SIZE);

    bw_inkey1.strtrim(s1,SMG_SIZE);

    bw_xbase1.set_win_bmp_name(s1,SMG_SIZE);

    bw_xbase1.set_c_win_scrnvar(p_wptr,0,0);

    fldtype='c';

    if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
    {
      bw_main1.win_key=0;
    }

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(p_wptr,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      { 
        hnd=bw_win1.get_win_hnd(q);
	SetWindowText(hnd,"");
	if (bw_main1.win_key!=401) SetFocus(hnd);
      }
    }
  }

  if (p_str[0]==':')
  {
    bw_xbase1.get_win_scrnvar(p_wptr,s3,SMG_SIZE);

    j=bw_getread1.get_read(l-bw_win1.get_win_con(p_wptr,1)+1,
			 c-bw_win1.get_win_con(p_wptr,0)+1,
		       "",
		       s3,
		       bw_win1.get_t_fldlen(i),
		       fldtype,
		       comm,
		       w_find_fldlen(s2,SMG_SIZE,j),
		       w_find_flddec(s2,SMG_SIZE,j),
		       1,1,
		       bw_dialog1.get_win_mv_getp(p_wptr),
		       bw_win1.get_win_ptr_get_rd(p_wptr));

    if ((GetFocus()==bw_win1.get_win_phh(p_wptr))||(bw_win1.get_ci_mhnd(GetFocus())==bw_win1.get_win_phh(p_wptr)))
    {
      SetFocus(bw_win1.get_win_phh(p_wptr));
    }

  }

  return(j);
}
int bw_fldstru::w_tv_get_read_r(char *p_str,int p_str_size,int p_wptr,int l,int c,char comm)
{
  int  i,j;
  char s2[SMG_SIZE];
  char s3[SMG_SIZE];
  char fldtype;

  if (p_str[0]!=':') return(1);

  if (p_str_size>0) p_str[p_str_size-1]=0;

  i=bw_buff1.get_t3_linecol(p_wptr,l,c);
  j=bw_win1.get_t_fldbase(i);
  bw_inkey1.cut_string(p_str,1,strlen(p_str)-1,p_str_size,s2,SMG_SIZE);
  if (w_find_fldnum(s2,SMG_SIZE,j)<0) return(1);

  if ((w_find_fldtype(s2,SMG_SIZE,j)=='n')||(w_find_fldtype(s2,SMG_SIZE,j)=='c'))
  {
    fldtype=w_find_fldtype(s2,SMG_SIZE,j);
  }
  else if (w_find_fldtype(s2,SMG_SIZE,j)=='l')
  {
    fldtype='c';
  }
  else if (w_find_fldtype(s2,SMG_SIZE,j)=='m')
  {
    fldtype='c';
    if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
    {
      bw_main1.win_key=0;
    }
  }
  else
  {
    fldtype='c';
    if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
    {
      bw_main1.win_key=0;
    }
  }

  bw_xbase1.get_win_scrnvar(p_wptr,s3,SMG_SIZE);

  //bw_getread1.win_p1=0;

  j=bw_getread1.get_read(l-bw_win1.get_win_con(p_wptr,1)+1,
			 c-bw_win1.get_win_con(p_wptr,0)+1,
		       "",
		       s3,
		       bw_win1.get_t_fldlen(i),
	               fldtype,
		       comm,
		       w_find_fldlen(s2,SMG_SIZE,j),
		       w_find_flddec(s2,SMG_SIZE,j),
		       1,1,
		       bw_dialog1.get_win_mv_getp(p_wptr),
		       bw_win1.get_win_ptr_get_rd(p_wptr));

  return(j);
}
int bw_fldstru::w_get_tab_var(char *p_fn,int p_fn_size,int p_dbptr,char *p_ca,int p_ca_size)
{
  int  i,j,k;

  p_ca[0]=0;

  i=w_find_fldnum(p_fn,p_fn_size,p_dbptr);
  if (i<0) return(1);
  j=w_find_fldlen(p_fn,p_fn_size,p_dbptr);
  k=w_find_fldposi(p_fn,p_fn_size,p_dbptr);

  for (i=1;i<=j;i++)
  {
    if (i-1+1<p_ca_size)
    {
      p_ca[i-1+0]=bw_xbase1.get_win_recvar(i-1+k);
      p_ca[i-1+1]=0;
    }
  }

  return(0);
}
int bw_fldstru::w_cmp_tab_var(char *p_fn,int p_fn_size,int p_dbptr,char *p_ca,int p_ca_size)
{
  int  exist;
  int  i,j,k,l;

  i=w_find_fldnum(p_fn,p_fn_size,p_dbptr);
  if (i<0) return(1);
  j=strlen(p_ca);
  l=w_find_fldlen(p_fn,p_fn_size,p_dbptr);
  k=w_find_fldposi(p_fn,p_fn_size,p_dbptr);
  if (j!=l) return(1);

  exist=0;

  for (i=1;i<=l;i++)
  {
    if (i-1<p_ca_size)
    {
      if (p_ca[i-1]!=bw_xbase1.get_win_recvar(i-1+k))
      {
        exist=1;
	break;
      }
    }
  }

  return(exist);
}
int bw_fldstru::w_sav_tab_var(char *p_fn,int p_fn_size,int p_dbptr,char *p_ca,int p_ca_size)
{
  int  i,j,k,l;
  char c1;

  i=w_find_fldnum(p_fn,p_fn_size,p_dbptr);
  if (i<0) return(1);
  j=w_find_fldlen(p_fn,p_fn_size,p_dbptr);
  k=w_find_fldposi(p_fn,p_fn_size,p_dbptr);

  if (p_ca_size>0) p_ca[p_ca_size-1]=0;

  l=strlen(p_ca);
  //if (l>=p_ca_len) l=p_ca_len-1;
   
  for (i=0;i<j;i++)
  {
    if (i+1>l) c1=' ';
    else
    {
      if ((p_ca[i]>=0)&&(p_ca[i]<' ')) c1=' ';
      else c1=p_ca[i];
    }
    bw_xbase1.set_win_recvar(k+i,c1);
  }

  return(0);
}
int bw_fldstru::w_fetch_rec(int p_dbptr,int p_wptr,int seri)
{
  int  i,j,l;
  int  r1,r2;
  long recno;

  if (bw_xbase1.get_win_cur_seri(p_dbptr,p_wptr)==0)
  {
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,0);

    recno=0;

    if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
    {
      recno=bw_mbase1.w_down_rec(p_dbptr,p_wptr,recno);
    }
    else
    {
      while (1)
      {
        recno=bw_mbase1.w_down_rec(p_dbptr,p_wptr,recno);
	j=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(j,p_wptr,p_dbptr,seri,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
    }

    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,recno);
  }

  if (bw_xbase1.get_win_rec_cnt(p_dbptr)<1)
  {
    bw_xbase1.w_clr_recvar(p_dbptr);

    return(1);
  }
/*
  if (bw_xbase1.get_win_cur_seri(p_dbptr,p_wptr)==seri)
  {
    recno=bw_xbase1.get_win_recno(p_dbptr,p_wptr,0);
    recno--;

    if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
    {
      recno=bw_mbase1.w_down_rec(p_dbptr,p_wptr,recno);
    }
    else
    {
      if (bw_xbase1.get_win_lnktab(p_dbptr)>1) recno=0;

      while (1)
      {
        recno=bw_mbase1.w_down_rec(p_dbptr,p_wptr,recno);
	j=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(j,p_wptr,p_dbptr,seri,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
    }

    if (bw_xbase1.win_state_dbf_err==1)
    {
      bw_xbase1.w_clr_recvar(p_dbptr);
      return(1);
    }
    else
    {
      bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,seri);
      bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,recno);
      return(0);
    }
  }
*/
  if (1/*bw_xbase1.get_win_cur_seri(p_dbptr,p_wptr)!=seri*/)
  {
    if (bw_xbase1.get_win_lnktab(p_dbptr)==0) // not linked table (type 0, not type 1,2,3)
    {
      r1=bw_xbase1.get_win_recno(p_dbptr,bw_main1.win_hnd_id,1)-1;
      r2=0;

      //s_tmpn1=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
      for (i=1;i<=seri;i++)
      {
        r2=bw_mbase1.w_down_rec(p_dbptr,bw_main1.win_hnd_id,r1);
        if (bw_xbase1.win_state_dbf_err==1) break;
        r1=r2;
      }

      if (bw_xbase1.win_state_dbf_err==1) return(1);

      bw_xbase1.set_win_cur_seri(p_dbptr,bw_main1.win_hnd_id,seri);
      bw_xbase1.set_win_recno(p_dbptr,bw_main1.win_hnd_id,0,r2);

      return(0);
    }
    else  // linked tab
    {
      r1=bw_xbase1.get_win_recno(p_dbptr,bw_main1.win_hnd_id,1)-1;
      r2=0;

      if (bw_xbase1.get_win_lnktab(p_dbptr)>1) r1=0;

      for (i=1;i<=seri;i++)
      {
        while (1)
        {
          r2=bw_mbase1.w_down_rec(p_dbptr,bw_main1.win_hnd_id,r1);
/*
          m=bw_buff1.get_t3_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
          if (m>0) n=bw_win1.get_t_fldseri(m);
          else n=1;
*/
          l=bw_link1.w_link_number(bw_main1.win_hnd_id,p_dbptr);
          r1=r2;
          if (bw_link1.w_link_cond_ok(l,bw_main1.win_hnd_id,p_dbptr,i,1)==1) break;
          if (bw_xbase1.win_state_dbf_err==1) break;
        }
        if (bw_xbase1.win_state_dbf_err==1) break;
      }

      if (bw_xbase1.win_state_dbf_err==1)
      {
/*
        while (1)
        {
          r2=bw_mbase1.w_up_rec(p_dbptr,bw_main1.win_hnd_id,r1);
          *//*m=bw_buff1.get_t3_linecol(bw_main1.win_hnd_id,bw_win1.pline,bw_win1.pfield);
          if (m>0) n=bw_win1.get_t_fldseri(m);
          else n=1;*//*
          l=bw_link1.w_link_number(bw_main1.win_hnd_id,p_dbptr);
          r1=r2;
          if (bw_link1.w_link_cond_ok(l,bw_main1.win_hnd_id,p_dbptr,seri,1)==1) break;
          if (bw_xbase1.win_state_dbf_err==1) break;
        }
        if (bw_xbase1.win_state_dbf_err==1)
        {
          //bw_xbase1.set_win_recno(p_dbptr,bw_main1.win_hnd_id,0,1);
          //r2=1;
        }*/
        return(1);
      }

      bw_xbase1.set_win_cur_seri(p_dbptr,bw_main1.win_hnd_id,seri);
      bw_xbase1.set_win_recno(p_dbptr,bw_main1.win_hnd_id,0,r2);

      return(0);
    }
  }

  return(1);
}
int bw_fldstru::w_page_up(int p_dbptr,int p_wptr)
{
  int  i,j,k,l;
  int  s_tmpn1;

  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(0);

  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);

    for (i=1;i<=s_tmpn1;i++)
    {
      bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
      if (bw_xbase1.win_state_dbf_err==1) break;
    }

    w_echo_winrec(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

    return(0);
  }
  else
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);

    for (i=1;i<=s_tmpn1;i++)
    {
      while (1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1) break;
    }

    if (bw_xbase1.win_state_dbf_err==1)
    {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)-1);
	while (1)
        {
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	  j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win1.get_t_fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(p_wptr,p_dbptr);
	  if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	  if (bw_xbase1.win_state_dbf_err==1) break;
	}
	if (bw_xbase1.win_state_dbf_err==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);
    }

    i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
    bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
    bw_link1.w_link_set_continue(p_wptr,p_dbptr);
    bw_link1.w_echo_winrec_lnk(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
    return(0);
  }
}
int bw_fldstru::w_page_down(int p_dbptr,int p_wptr)
{
  int  i,j,k,l;
  int  s_tmpn1,s_tmpn2;
  int  r1,r2;

  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(0);

  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
    s_tmpn2=s_tmpn1+1;

    r1=bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)-1; // try if there are n lines in after
    r2=0;

    for (i=1;i<=s_tmpn2;i++)
    {
      r2=bw_mbase1.w_down_rec(p_dbptr,p_wptr,r1);
      r1=r2;
      if (bw_xbase1.win_state_dbf_err==1) break;
    }

    if (bw_xbase1.win_state_dbf_err==1)
    {
      w_echo_winrec(p_wptr);
      w_first_editposi(p_dbptr,p_wptr);
      bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
      bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
      return(0);
    }
    else
    {
      for (i=1;i<=s_tmpn1;i++)  // move
      {
        bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
        if (bw_xbase1.win_state_dbf_err==1) break;
      }

      w_echo_winrec(p_wptr);
      w_first_editposi(p_dbptr,p_wptr);
      bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
      bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

      return(0);
    }
  }
  else
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
    s_tmpn2=s_tmpn1+1;

    r1=bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)-1;  // try if there are n lines in after
    r2=0;

    for (i=1;i<=s_tmpn2;i++)
    {
      while (1)
      {
	r2=bw_mbase1.w_down_rec(p_dbptr,p_wptr,r1);
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
        r1=r2;
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1) break;
    }

    if (bw_xbase1.win_state_dbf_err==1)
    {
      i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
      bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
      bw_link1.w_link_set_continue(p_wptr,p_dbptr);
      bw_link1.w_echo_winrec_lnk(p_wptr);
      w_first_editposi(p_dbptr,p_wptr);
      bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
      bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
      return(0);
    }
    else
    {
      for (i=1;i<=s_tmpn1;i++)  // move
      {
        while (1)
        {
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
          j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
          if (j>0) k=bw_win1.get_t_fldseri(j);
          else k=1;
          l=bw_link1.w_link_number(p_wptr,p_dbptr);
          if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
          if (bw_xbase1.win_state_dbf_err==1) break;
        }
        if (bw_xbase1.win_state_dbf_err==1) break;
      }

      if (bw_xbase1.win_state_dbf_err==1)
      {
	while (1)
	{
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	  j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win1.get_t_fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(p_wptr,p_dbptr);
	  if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	  if (bw_xbase1.win_state_dbf_err==1) break;
	}
	if (bw_xbase1.win_state_dbf_err==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);
      }

      i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
      bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
      bw_link1.w_link_set_continue(p_wptr,p_dbptr);
      bw_link1.w_echo_winrec_lnk(p_wptr);
      w_first_editposi(p_dbptr,p_wptr);
      bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
      bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

      return(0);
    }
  }
}
int bw_fldstru::w_first_editposi(int p_dbptr,int p_wptr)
{
  int i,j,k,l;

  k=0;

  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      l=bw_buff1.get_t3_linecol(p_wptr,i,j);
      if ((l!=0)&&(bw_win1.get_t_fldedt(l)==0)&&(bw_win1.get_t_fldbase(l)==p_dbptr))
      {
	bw_win1.pline=i;
        bw_win1.set_win_linep(p_wptr,0,i);
	bw_win1.pfield=j;
	bw_win1.set_win_linep(p_wptr,1,j);
	k=i;
	break;
      }
    }
    if (k!=0) break;
  }

  return(k);
}
int bw_fldstru::w_last_editposi(int p_dbptr,int p_wptr)
{
  int i,j,k,l;

  k=0;

  for (i=LIN_NUM-1;i>=1;i--) /* find first screen field */
  {
    for (j=COL_NUM-1;j>=1;j--)
    {
      l=bw_buff1.get_t3_linecol(p_wptr,i,j);

      if ((l!=0)&&(bw_win1.get_t_fldedt(l)==0)&&(bw_win1.get_t_fldbase(l)==p_dbptr))
      {
	bw_win1.pline=i;
	bw_win1.set_win_linep(p_wptr,0,i);
	bw_win1.pfield=j;
	bw_win1.set_win_linep(p_wptr,1,j);
	k=i;
	break;
      }
    }
    if (k!=0) break;
  }

  return(k);
}

int bw_fldstru::w_insert_rec(int p_dbptr,int p_wptr)
{
  int s_state1;
  int i;

  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(0);

  s_state1=bw_mbase1.w_ins_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0));

  if (s_state1!=0)
  {
    bw_win1.w_atten7();                   /* insert record error */
    return(0);
  }

  if (bw_xbase1.get_win_lnktab(p_dbptr)==1)
  {
    if ((bw_xbase1.get_win_carry_on(p_dbptr)!=1)||(bw_xbase1.get_win_enseri(p_dbptr,p_wptr)<=0))
    {
      bw_link1.w_keep_linkfld(p_wptr,p_dbptr,bw_xbase1.win_insert_dir);
    }

    i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
    bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
    bw_link1.w_link_set_continue(p_wptr,p_dbptr);
    bw_link1.w_echo_winrec_lnk(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
  }
  else w_echo_winrec(p_wptr);

  bw_xbase1.set_win_state_dbf_modi(p_dbptr,1);

  return(0);
}

int bw_fldstru::w_add_rec(int p_dbptr,int p_wptr)
{
  int s_state1;
  int i,j,k;

  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(0);

  s_state1=bw_mbase1.w_add_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0));

  if (s_state1!=0)
  {
    bw_win1.w_atten7b();                   /* insert record error */
    return(0);
  }

  j=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
  k=w_last_line(p_dbptr,p_wptr);
    
  if ((j>1)&&(k==0)) bw_win1.w_down_field(p_wptr);  // multi line windows and not at last line
  else bw_fldstru1.w_down_line2(p_dbptr,p_wptr); // single line window or in last line

  if (bw_xbase1.get_win_lnktab(p_dbptr)==1)
  {
    if ((bw_xbase1.get_win_carry_on(p_dbptr)!=1)||(bw_xbase1.get_win_enseri(p_dbptr,p_wptr)<=0))
    {
      bw_link1.w_keep_linkfld(p_wptr,p_dbptr,bw_xbase1.win_insert_dir);
    }

    i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
    bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
    bw_link1.w_link_set_continue(p_wptr,p_dbptr);
    bw_link1.w_echo_winrec_lnk(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
  }
  else w_echo_winrec(p_wptr);

  bw_xbase1.set_win_state_dbf_modi(p_dbptr,1);

  return(0);
}

int bw_fldstru::w_delete_rec(int p_dbptr,int p_wptr)
{
  int s_state1;
  int i,j,k;
  long recno;

  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(0);

  s_state1=bw_mbase1.w_del_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0));

  if (s_state1!=0)
  {
    bw_win1.w_atten7a();                   /* delete record error */
    return(0);
  }

  recno=bw_xbase1.get_win_recno(p_dbptr,p_wptr,0);

  if (w_have_next_rec2(p_dbptr,p_wptr,recno))
  { 
  }  // adjust cursor
  else
  {
    j=bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
    k=w_first_line(p_dbptr,p_wptr);
    
    if ((j>1)&&(k==0)) bw_win1.w_up_field(p_wptr);  // multi line windows and not at first line
    else
    {
      if (w_have_prev_rec2(p_dbptr,p_wptr,recno)) bw_fldstru1.w_up_line2(p_dbptr,p_wptr); // single line window or in first line
    }
  }

  if (bw_xbase1.get_win_lnktab(p_dbptr)==1)
  {
    i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
    bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
    bw_link1.w_link_set_continue(p_wptr,p_dbptr);
    bw_link1.w_echo_winrec_lnk(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
  }
  else w_echo_winrec(p_wptr);

  bw_xbase1.set_win_state_dbf_modi(p_dbptr,1);

  return(0);
}

int bw_fldstru::w_have_next_rec2(int p_dbptr,int p_wptr,int recno)
{
  int i;
  i=bw_mbase1.w_down_rec(p_dbptr,p_wptr,recno-1);
  if (bw_xbase1.win_state_dbf_err==0) return(1);
  else return(0);
}


int bw_fldstru::w_have_prev_rec2(int p_dbptr,int p_wptr,int recno)
{
  int i;
  i=bw_mbase1.w_up_rec(p_dbptr,p_wptr,recno);
  if (bw_xbase1.win_state_dbf_err==0) return(1);
  else return(0);
}

int bw_fldstru::w_rollback_base(int p_dbptr,int p_wptr)
{
  int  i,k;
  int  p1;
  char s_fn1[FN_SIZE];
  char s_fn3[FN_SIZE];
  char str1[FN_SIZE];
  char s_ext[EXT_SIZE];

  if (bw_xbase1.get_win_state_dbf_modi(p_dbptr)==0) return(0);

  if (bw_xbase1.get_win_state_in_srch(p_wptr,p_dbptr)==1)
  {
    close(bw_xbase1.win_fh2[p_wptr]);

    bw_win1.get_win_window_name(p_wptr,s_fn1,FN_SIZE);
    i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
    s_fn1[i]=0;
    bw_xbase1.get_win_fext(p_wptr,s_ext,EXT_SIZE);
    strcat(s_fn1,s_ext);

    bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

    bw_inkey1.w_set_dir(str1);

    bw_inkey1.w_del_file(s_fn1);

    bw_xbase1.set_win_state_in_srch(p_wptr,p_dbptr,0);
  }

  bw_win1.get_win_tabname(1,p_dbptr,s_fn3,FN_SIZE);

  bw_xbase1.w_rollback_xbase(/*s_fn3,FN_SIZE,*/bw_xbase1.get_win_base_backup(p_dbptr),p_dbptr);

  bw_xbase1.set_win_state_dbf_modi(p_dbptr,0);
/*
  for (p1=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),0)
      ;p1<=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),2)
      ;p1++)
  {
*/
    p1=p_wptr;

    if (bw_xbase1.get_win_state_in_srch(p1,p_dbptr)==1)
    {
      close(bw_xbase1.win_fh2[p1]);
      bw_xbase1.set_win_state_in_srch(p1,p_dbptr,0);

      bw_win1.get_win_window_name(p1,s_fn1,FN_SIZE);
      i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
      s_fn1[i]=0;
      bw_xbase1.get_win_fext(p1,s_ext,EXT_SIZE);
      strcat(s_fn1,s_ext);

      bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

      bw_inkey1.w_set_dir(str1);

      bw_inkey1.w_del_file(s_fn1);
    }
/*
  }
*/
  w_first_editposi(p_dbptr,p_wptr);
  bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
  bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,1);
  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);

  if (bw_xbase1.get_win_lnktab(p_dbptr)==1)
  {
    i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
    bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
    bw_link1.w_link_set_continue(p_wptr,p_dbptr);
    bw_link1.w_echo_winrec_lnk(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
  }
  else w_echo_winrec(p_wptr);

  return(0);
}

int bw_fldstru::w_commit_base(int p_dbptr,int p_wptr)
{

  int  i;
  int  p1;
  char s_fn1[FN_SIZE];
  char str1[FN_SIZE];
  char s_ext[EXT_SIZE];

  if (bw_xbase1.get_win_state_dbf_modi(p_dbptr)==0) return(0);

  if (bw_xbase1.get_win_state_in_srch(p_wptr,p_dbptr)==1)
  {
    close(bw_xbase1.win_fh2[p_wptr]);

    bw_win1.get_win_window_name(p_wptr,s_fn1,FN_SIZE);
    i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
    s_fn1[i]=0;
    bw_xbase1.get_win_fext(p_wptr,s_ext,EXT_SIZE);
    strcat(s_fn1,s_ext);

    bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

    bw_inkey1.w_set_dir(str1);

    bw_inkey1.w_del_file(s_fn1);

    bw_xbase1.set_win_state_in_srch(p_wptr,p_dbptr,0);
  }

  bw_xbase1.w_commit_xbase(bw_xbase1.get_win_base_backup(p_dbptr),p_dbptr);

  bw_xbase1.set_win_state_dbf_modi(p_dbptr,0);
/*
  for (p1=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),0)
      ;p1<=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),2)
      ;p1++)
  {
*/
    p1=p_wptr;

    if (bw_xbase1.get_win_state_in_srch(p1,p_dbptr)==1)
    {
      close(bw_xbase1.win_fh2[p1]);
      bw_xbase1.set_win_state_in_srch(p1,p_dbptr,0);

      bw_win1.get_win_window_name(p1,s_fn1,FN_SIZE);
      i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
      s_fn1[i]=0;
      bw_xbase1.get_win_fext(p1,s_ext,EXT_SIZE);
      strcat(s_fn1,s_ext);

      bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

      bw_inkey1.w_set_dir(str1);

      bw_inkey1.w_del_file(s_fn1);
    }
/*
  }
*/
  w_first_editposi(p_dbptr,p_wptr);
  bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
  bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,1);
  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);

  if (bw_xbase1.get_win_lnktab(p_dbptr)==1)
  {
    i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
    bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
    bw_link1.w_link_set_continue(p_wptr,p_dbptr);
    bw_link1.w_echo_winrec_lnk(p_wptr);
    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
  }
  else w_echo_winrec(p_wptr);

  return(0);
}

int bw_fldstru::w_link_window(int p_dbptr,int p_wptr)
{
  int i,j;

  if (bw_xbase1.get_win_state_in_srch(p_wptr,p_dbptr)==1) return(1);

  i=w_is_card(p_dbptr,p_wptr);

  j=p_wptr;//bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),0);

  if (i==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_xbase1.get_win_recno(p_dbptr,j,0));
  else bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_xbase1.get_win_recno(p_dbptr,j,1));

  w_echo_winrec(p_wptr);
  w_first_editposi(p_dbptr,p_wptr);
  bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
  bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);

  return(0);
}

int bw_fldstru::w_is_card(int p_dbptr,int p_wptr)  // single record window
{
  int i,j,k,l;

  k=0;

  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      l=bw_buff1.get_t3_linecol(p_wptr,i,j);
      if ((l!=0)&&(bw_win1.get_t_fldedt(l)==0)&&(bw_win1.get_t_fldbase(l)==p_dbptr))
      {
	if (k<bw_win1.get_t_fldseri(l)) k=bw_win1.get_t_fldseri(l);
      }
    }
  }

  if (k==1) return(1);
  else return(0);
}

int bw_fldstru::w_find_cond(int p_dbptr,int p_wptr)
{
  char  sfn1[FN_SIZE];
  char  str1[FN_SIZE];

  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(1);

  w_clr_condition(p_dbptr);
  bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);
  bw_inkey1.w_set_dir(str1);

  bw_win1.get_win_find_name(p_wptr,sfn1,FN_SIZE);
  bw_main1.get_view(sfn1,FN_SIZE,bw_main1.win_hwnd,p_wptr/*bw_win1.get_win_ptr_grp_ptr(p_wptr,0)*/);

  return(0);
}

int bw_fldstru::w_find_key(int p_dbptr,int p_wptr)
{
  int i,j;

  i=w_find_recno(p_dbptr,p_wptr);
  if (i!=0) return(1);

  for (j=0;j<=2;j++) bw_xbase1.set_win_recno(p_dbptr,p_wptr,j,1);
  bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
  w_echo_winrec(p_wptr);
  w_first_editposi(p_dbptr,p_wptr);

  return(0);
}

int bw_fldstru::w_find_recno(int p_dbptr,int p_wptr)
{
  int           i;
  int           exist;
  long          lj;
  unsigned char c1,c2,c3,c4;
  char          s_fn1[FN_SIZE];
  char          s_fn2[FN_SIZE];
  char          str1[FN_SIZE];
  unsigned char str2[SMG_SIZE];
  char          s_ext[EXT_SIZE];
  
  exist=0;

  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_xbase1.get_win_state_in_srch(p_wptr,i)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    close(bw_xbase1.win_fh2[p_wptr]);
    bw_xbase1.set_win_state_in_srch(p_wptr,i,0);

    bw_win1.get_win_window_name(p_wptr,s_fn1,FN_SIZE);
    i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
    s_fn1[i]=0;
    bw_xbase1.get_win_fext(p_wptr,s_ext,EXT_SIZE);
    strcat(s_fn1,s_ext);

    bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

    bw_inkey1.w_set_dir(str1);

    bw_inkey1.w_del_file(s_fn1);
  }

  bw_win1.get_win_window_name(p_wptr,s_fn2,FN_SIZE);
  i=bw_xbase1.w_find_empty_ffile(s_fn2,FN_SIZE,p_wptr);
  if (i!=0) return(1);

  bw_win1.get_win_window_name(p_wptr,s_fn1,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
  s_fn1[i]=0;
  bw_xbase1.get_win_fext(p_wptr,s_ext,EXT_SIZE);
  strcat(s_fn1,s_ext);

  bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

  bw_inkey1.w_set_dir(str1);

  bw_xbase1.win_fh2[p_wptr]=sopen(s_fn1,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (bw_xbase1.win_fh2[p_wptr]<0) return(1);

  bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,0);
  lj=0;
  while (1)
  {
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)));
    if (bw_xbase1.win_state_dbf_err!=0) break;
    if (w_find_cond_ok(p_dbptr)!=1) continue;

    c1=(unsigned char)(bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)/256/256/256);
    c2=(unsigned char)((bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)-c1*256*256*256)/256/256);
    c3=(unsigned char)((bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)-c1*256*256*256-c2*256*256)/256);
    c4=(unsigned char)(bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)-c1*256*256*256-c2*256*256-c3*256);

    str2[0]=c4;
    str2[1]=c3;
    str2[2]=c2;
    str2[3]=c1;
    str2[4]=0;

    lj++;
    lseek(bw_xbase1.win_fh2[p_wptr],(lj-1)*5,0);
    write(bw_xbase1.win_fh2[p_wptr],str2,7);

  }
  
  bw_xbase1.set_win_state_in_srch(p_wptr,p_dbptr,1);

  return(0);
}

int bw_fldstru::w_clr_condition(int p_dbptr)
{
  int   i;
  int   zero=0;
  char  str1[SMG_SIZE];
  char  str2[SMG_SIZE];
  char  str3[SMG_SIZE];

  for (i=w_find_fldpoin0(p_dbptr)
      ;i<w_find_fldpoin1(p_dbptr)
      ;i++)
  {
    w_find_fldname(p_dbptr,i,str3,SMG_SIZE);

    strcpy(str1,"?");
    strcat(str1,str3);

    if (bw_dialog1.w_mv_exist(str1,SMG_SIZE,zero)==1)
    {
      str2[0]=0;
      bw_dialog1.w_mv_save_mem(str1,SMG_SIZE,zero,str2,SMG_SIZE);
    }

    strcpy(str1,"-");
    strcat(str1,str3);

    if (bw_dialog1.w_mv_exist(str1,SMG_SIZE,zero)==1)
    {
      str2[0]=0;
      bw_dialog1.w_mv_save_mem(str1,SMG_SIZE,zero,str2,SMG_SIZE);
    }
  }

  return(0);
}

int bw_fldstru::w_find_end(int p_dbptr,int p_wptr)
{
  int  i;
  char s_fn1[FN_SIZE];
  char str1[FN_SIZE];
  char s_ext[EXT_SIZE];

  if (bw_xbase1.get_win_state_in_srch(p_wptr,p_dbptr)==1)
  {
    close(bw_xbase1.win_fh2[p_wptr]);

    bw_win1.get_win_window_name(p_wptr,s_fn1,FN_SIZE);
    i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
    s_fn1[i]=0;
    bw_xbase1.get_win_fext(p_wptr,s_ext,EXT_SIZE);
    strcat(s_fn1,s_ext);

    bw_xbase1.get_win_basedir(p_dbptr,str1,FN_SIZE);

    bw_inkey1.w_set_dir(str1);

    bw_inkey1.w_del_file(s_fn1);

    bw_xbase1.set_win_state_in_srch(p_wptr,p_dbptr,0);

    w_first_editposi(p_dbptr,p_wptr);
    bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,1);
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);

    w_echo_winrec(p_wptr);

    return(0);
  }
  
  return(1);
}

int bw_fldstru::w_find_exit(int p_wptr)
{
  int  i;
  int  p1,p2;
  char s_fn1[FN_SIZE];
  char str1[FN_SIZE];
  char s_ext[EXT_SIZE];
/*
  for (p1=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),0)
      ;p1<=bw_win1.get_win_ptr_grp_ptr(bw_win1.get_win_ptr_grp_id(p_wptr),2)
      ;p1++)
  {
*/
    p1=p_wptr;

    for (p2=0;p2<STRU_NUM;p2++)
    {
      if (bw_xbase1.get_win_state_in_srch(p1,p2)==1)
      {
        close(bw_xbase1.win_fh2[p1]);
        bw_xbase1.set_win_state_in_srch(p1,p2,0);

	bw_win1.get_win_window_name(p1,s_fn1,FN_SIZE);
        i=bw_inkey1.strlocc(s_fn1,FN_SIZE,'.');
	s_fn1[i]=0;
	bw_xbase1.get_win_fext(p1,s_ext,EXT_SIZE);
	strcat(s_fn1,s_ext);

	bw_xbase1.get_win_basedir(p2,str1,FN_SIZE);

	bw_inkey1.w_set_dir(str1);

	bw_inkey1.w_del_file(s_fn1);
      }
    }
/*
  }
*/
  return(0);
}

int bw_fldstru::w_find_cond_ok(int p_dbptr)
{
  float f1,f2;
  int   i,j=1,k,l,m,n,o;
  int   exist;
  int   zero=0;
  char  str1[SMG_SIZE]; // scrn field val
  char  str2[SMG_SIZE]; // tab field val
  char  str3[SMG_SIZE];
  char  str4[SMG_SIZE];
  char  str5[SMG_SIZE];
  char  str6[SMG_SIZE]; // scrn field name
  char  str7[SMG_SIZE]; // tab field name


  for (i=w_find_fldpoin0(p_dbptr)
      ;i<w_find_fldpoin1(p_dbptr)
      ;i++)
  {
    w_find_fldname(p_dbptr,i,str7,SMG_SIZE);

    strcpy(str6,"?");
    strcat(str6,str7);

    strcpy(str4,"-");
    strcat(str4,str7);

    if ((bw_dialog1.w_mv_exist(str6,SMG_SIZE,zero)==1)||(bw_dialog1.w_mv_exist(str4,SMG_SIZE,zero)==1))
    {
      if (bw_dialog1.w_mv_exist(str4,SMG_SIZE,zero)==1) strcpy(str6,str4);

      bw_dialog1.w_mv_fet_val(str6,SMG_SIZE,zero,str1,SMG_SIZE);

      bw_inkey1.strtrim(str1,SMG_SIZE);
      bw_inkey1.strltrim(str1,SMG_SIZE);

      w_get_tab_var(str7,SMG_SIZE,p_dbptr,str2,SMG_SIZE);

      if (w_find_fldtype(str7,SMG_SIZE,p_dbptr)=='c')
      {
	k=bw_inkey1.strlocc(str1,SMG_SIZE,';');

	if (str1[k]!=';')
        {
	  if (bw_inkey1.strfind(str2,str1)<0)
	  {
	    j=0;
	    break;
	  }
	}
	else
	{
	  l=0;
          m=0;
	  while (1)
	  {
	    k=bw_inkey1.strlocc(str1,SMG_SIZE,';');
	    if (str1[k]!=';') break;
            else
	    {
	      str1[k]=' ';
	      bw_inkey1.cut_string(str1,l,k-l,SMG_SIZE,str3,SMG_SIZE);
	      if (bw_inkey1.strfind(str2,str3)>=0)
	      {
		m=1;
		break;
              }
	      l=k+1;
            }
	  }

	  if (m==0)
	  {
	    j=0;
	    break;
	  }
	}
      }
      
      if (w_find_fldtype(str7,SMG_SIZE,p_dbptr)=='n')
      {
        f1=bw_inkey1.str2float(str2,SMG_SIZE);

      	k=0;
        bw_inkey1.strtrim(str1,SMG_SIZE);
	while (1)
	{
          exist=0;
	  for (l=k;l<(int)strlen(str1);l++)
	  {
	    if ((str1[l]=='<')||(str1[l]=='=')||(str1[l]=='>'))
	    {
	      exist=1;
	      break;
            }
	  }

	  if (exist==0) break;
	  else
	  {
            o=1;
	    if (str1[l]=='>')
	    {
	      if (str1[l+1]=='=') m=1;
	      else
	      {
		if (str1[l+1]=='<') m=5;
		else
		{
		  o=0;
		  m=0;
                }
	      }
	    }

	    if (str1[l]=='=')
	    {
	      if (str1[l+1]=='>') m=1;
	      else
	      {
		if (str1[l+1]=='=') m=4;
		else
		{
		  o=0;
		  m=4;
                }
	      }
	    }

	    if (str1[l]=='<')
	    {
	      if (str1[l+1]=='>') m=5;
	      else
	      {
		if (str1[l+1]=='=') m=3;
		else
		{
		  o=0;
		  m=2;
                }
	      }
            }

            k=l+1+o;
	    exist=0;
	    for (n=k;n<=(int)strlen(str1);n++)
	    {
	      if ((str1[n]=='<')||(str1[n]=='=')||(str1[n]=='>')||(str1[n]<=' ')||(str1[n]==','))
	      {
	        exist=1;
	        break;
              }
	    }

	    if (exist==0) break;
            else
	    {
	      bw_inkey1.cut_string(str1,l+1+o,n-l-1-o,SMG_SIZE,str3,SMG_SIZE);

	      f2=bw_inkey1.str2float(str3,SMG_SIZE);

	      if (m==0)
	      {
		if (f2>=f1)
		{
		  j=0;
		  break;
		}
              }
              if (m==1)
	      {
	        if (f2>f1)
                {
		  j=0;
		  break;
                }
	      }
	      if (m==2)
	      {
	        if (f2<=f1)
	        {
	          j=0;
	          break;
	        }
	      }
              if (m==3)
	      {
	        if (f2<f1)
	        {
	          j=0;
	          break;
	        }
	      }
	      if (m==4)
	      {
	        if (f2!=f1)
	        {
	          j=0;
	          break;
	        }
	      }
	      if (m==5)
	      {
	        if (f2==f1)
	        {
	          j=0;
	          break;
	        }
	      }

            }
	  }
	}

        if (j==0) break;
      }

      if (w_find_fldtype(str7,SMG_SIZE,p_dbptr)=='l')
      {
	if (str1[0]==' ')
	{
          break;
	}

	if ((str1[0]=='1')||(str1[0]=='y')||(str1[0]=='t')
          ||(str1[0]=='Y')||(str1[0]=='T'))
	{
          if ((str2[0]!='1')&&(str2[0]!='y')&&(str2[0]!='t')
            &&(str2[0]!='Y')&&(str2[0]!='T'))
	  {
	    j=0;
	    break;
	  }
        }

	if ((str1[0]!='1')&&(str1[0]!='y')&&(str1[0]!='t')
	  &&(str1[0]!='Y')&&(str1[0]!='T'))
	{
	  if ((str2[0]=='1')||(str2[0]=='y')||(str2[0]=='t')
            ||(str2[0]=='Y')||(str2[0]=='T'))
	  {
	    j=0;
	    break;
	  }
        }
      }

//      if (w_find_fldtype(str7,p_dbptr)=='m')
//      {
//	if ((str2[0]=='0')||(str2[0]=='n')||(str2[0]=='f')
//          ||(str2[0]=='N')||(str2[0]=='F'))
//	{
//	  j=0;
//	  break;
//	}
//      }

    }
  }

  return(j);
}

int bw_fldstru::w_edit_memo(int p_dbptr,int p_wptr,char *p_fldname,int p_fldname_size)
{                           
  char fn1[FN_SIZE];
  char str[SMG_SIZE];
  char str1[SMG_SIZE];
  char str2[FN_SIZE];
  char str3[FN_SIZE];
  char str4[SMG_SIZE];
  char str5[SMG_SIZE];
  char str6[SMG_SIZE];
//  char str7[SMG_SIZE];
  char str8[SMG_SIZE];
  char str9[SMG_SIZE];
//  char stra[SMG_SIZE];
  char ret[10];
  char sstr[20];
  char st1[FN_SIZE];
  char st2[FN_SIZE];
  int  i,l,m,n;
  FILE *fh;
  FILE *fh1;
  long mno;
  long mnu;
  long mnop;
  int  exist;
  int  mark=0;

  //if already in use return
  if (bw_xbase1.get_win_mem_inuse(p_dbptr)==1) return(0);

  //make empty string
  for (i=0;i<=10;i++) sstr[i]=' ';
  sstr[10]=0;

  //save field name
  if (p_fldname_size>0) p_fldname[p_fldname_size-1]=0;
  strcpy(str6,p_fldname);

  // make return string
  ret[0]=13;
  ret[1]=10;
  ret[2]=0;

  // make file name
  bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

  strcpy(fn1,st2);
  bw_inkey1.strtrim(fn1,FN_SIZE);
  i=bw_inkey1.strlocc(fn1,FN_SIZE,'.');
  fn1[i]=0;
  strcat(fn1,".mem");

  //file exist
  bw_xbase1.get_win_basedir(p_dbptr,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);
  if (bw_inkey1.w_find_file(fn1)==0)
  {
    fh=fopen(fn1,"w");
    if (fh==NULL) return(1);

    bw_xbase1.get_win_memno(p_dbptr,str9,SMG_SIZE);

    if (bw_inkey1.strempty(str9)==0)
    {
      mnu=0;
      mno=0;
      mark=1;
      bw_inkey1.long2str(mno,str9,SMG_SIZE);
    }
    else
    {
      mno=bw_inkey1.str2long(str9,SMG_SIZE);
      mark=0;
      mnu=mno;
    }

    strcpy(str,str9);

    strcpy(str1,"&&memorynum:");
    strcat(str1,str);
    strcat(str1,sstr);
    str1[22]=0;
    strcat(str1,ret);
    fputs(str1,fh);

    strcpy(str1,"&&memoryno.:");
    strcat(str1,str);
    strcat(str1,sstr);
    str1[22]=0;
    strcat(str1,ret);
    fputs(str1,fh);

//    fclose(fh);

    bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

    strcpy(str2,st2);
    bw_inkey1.strtrim(str2,FN_SIZE);
    i=bw_inkey1.strlocc(str2,FN_SIZE,'.');
    str2[i]=0;

    bw_xbase1.w_find_empty_mfile(str2,FN_SIZE,p_dbptr);

    strcpy(str3,str2);
    bw_xbase1.get_win_mem_ext(p_dbptr,str8,SMG_SIZE);
    strcat(str3,str8);
    bw_inkey1.strtrim(str3,FN_SIZE);

    fh1=fopen(str3,"w");
    if (fh1==NULL) return(1);
    fclose(fh1);

  }
  else
  {
    bw_xbase1.get_win_memno(p_dbptr,str9,SMG_SIZE);

    fh=fopen(fn1,"r+");
    if (fh==NULL) return(1);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_SIZE,fh);

      if (strncmp(str4,"&&memorynum:",12)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      bw_inkey1.cut_string(str4,12,8,SMG_SIZE,str,SMG_SIZE);
      bw_inkey1.strtrim(str,SMG_SIZE);
      mnu=bw_inkey1.str2long(str,SMG_SIZE);
    }
    else
    {
      fseek(fh,0,SEEK_END);

      if (bw_inkey1.strempty(str9)==0)
      {
        mnu=0;
      }
      else
      {
	mnu=bw_inkey1.str2long(str9,SMG_SIZE);
      }

      strcpy(str,str9);

      fputs(ret,fh);

      strcpy(str1,"&&memorynum:");
      strcat(str1,str);
      strcat(str1,sstr);
      str1[22]=0;
      strcat(str1,ret);
      fputs(str1,fh);
    }

    fseek(fh,0,0);

    if (bw_inkey1.strempty(str9)==0)
    {
      mnu++;
      mno=mnu;
      mark=1;
      bw_inkey1.long2str(mno,str9,SMG_SIZE);
    }
    else
    {
      mno=bw_inkey1.str2long(str9,SMG_SIZE);
      if (mno>mnu)
      {
        mark=1;
	mnu=mno;
      }
      else mark=0;
    }

    strcpy(str5,"&&memoryno.:");
    strcat(str5,str9);
    strcat(str5,sstr);
    str5[22]=0;
    strcat(str5,ret);

    bw_inkey1.strtrim(str5,SMG_SIZE);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_SIZE,fh);

      bw_inkey1.strtrim(str4,SMG_SIZE);

      l=strlen(str4);
      m=strlen(str5);

//      MessageBox(bw_main1.win_hwnd1,str4,str5,MB_OK);

      if (l>m) n=l;
      else n=m;

      if (strncmp(str4,str5,n)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

      strcpy(str2,st2);
      bw_inkey1.strtrim(str2,FN_SIZE);
      i=bw_inkey1.strlocc(str2,FN_SIZE,'.');
      str2[i]=0;

      bw_xbase1.w_find_empty_mfile(str2,FN_SIZE,p_dbptr);

      strcpy(str3,str2);
      bw_xbase1.get_win_mem_ext(p_dbptr,str8,FN_SIZE);
      strcat(str3,str8);
      bw_inkey1.strtrim(str3,FN_SIZE);

      fh1=fopen(str3,"w");
      if (fh1==NULL)
      {
	fclose(fh);
	return(1);
      }

      while (!feof(fh))
      {
	fgets(str4,SMG_SIZE,fh);
	if (strncmp(str4,"&&memoryn",9)==0) break;
	else fputs(str4,fh1);
      }

//      fclose(fh);
      fclose(fh1);

    }
    else
    {
      strcpy(str,str9);

      fseek(fh,0,SEEK_END);

      fputs(ret,fh);
      strcpy(str1,"&&memoryno.:");
      strcat(str1,str);
      strcat(str1,sstr);
      str1[22]=0;
      strcat(str1,ret);
      fputs(str1,fh);

//      fclose(fh);

      bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

      strcpy(str2,st2);
      bw_inkey1.strtrim(str2,FN_SIZE);
      i=bw_inkey1.strlocc(str2,FN_SIZE,'.');
      str2[i]=0;

      bw_xbase1.w_find_empty_mfile(str2,FN_SIZE,p_dbptr);

      strcpy(str3,str2);
      bw_xbase1.get_win_mem_ext(p_dbptr,str8,FN_SIZE);
      strcat(str3,str8);
      bw_inkey1.strtrim(str3,FN_SIZE);

      fh1=fopen(str3,"w");
      if (fh1==NULL) return(1);
      fclose(fh1);

    }
  }

  if (mark==1)
  {
    bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)-1);

    w_sav_tab_var(str6,SMG_SIZE,p_dbptr,str9,SMG_SIZE);
    bw_mbase1.w_save_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0));
    bw_xbase1.set_win_state_dbf_modi(p_dbptr,1);

    fseek(fh,0,0);

    mnop=0;
    exist=0;
    while (!feof(fh))
    {
      mnop=fseek(fh,0,SEEK_CUR);
      fgets(str4,SMG_SIZE,fh);
      if (strncmp(str4,"&&memorynum:",12)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==0)
    {
      fclose(fh);
      return(1);
    }
    else
    {
      fseek(fh,mnop,0);

      bw_inkey1.long2str(mnu,str,SMG_SIZE);

      strcpy(str1,"&&memorynum:");
      strcat(str1,str);
      strcat(str1,sstr);
      str1[22]=0;
      strcat(str1,ret);
      fputs(str1,fh);

      fclose(fh);
    }
  }
  else fclose(fh);

  bw_xbase1.set_win_mem_inuse(p_dbptr,1);
  bw_xbase1.set_win_mem_wptr(p_dbptr,p_wptr);
  bw_xbase1.set_win_mem_fn(p_dbptr,str3,FN_SIZE);
  bw_win1.set_win_memo_basep(p_wptr,p_dbptr);

  bw_edit1.get_edit(str3,FN_SIZE,p_wptr,bw_main1.win_hwnd);

  return(0);
}

int bw_fldstru::w_edit_memo_close(int p_wptr)
{
  int  i,j,k,l,m;
  int  p_dbptr;
  int  exist;
  char ret[10];
  char str0[10];
  char fn1[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];
  char str4[FN_SIZE];
  char str5[SMG_SIZE];
  char str6[FN_SIZE];
  char str7[10];
  char str8[FN_SIZE];
  char st1[FN_SIZE];
  char st2[FN_SIZE];
//  long memp;
  FILE *fh1;
  FILE *fh2;
  FILE *fh3;

  p_dbptr=bw_win1.get_win_memo_basep(p_wptr);
  bw_xbase1.set_win_mem_inuse(p_dbptr,0);

  // save mem ext name
  bw_xbase1.get_win_mem_ext(p_dbptr,str0,10);
                                
  // make edited file name
  bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

  strcpy(str6,st2);
  bw_inkey1.strtrim(str6,FN_SIZE);
  i=bw_inkey1.strlocc(str6,FN_SIZE,'.');
  str6[i]=0;
  strcat(str6,str0);

  // make return string
  ret[0]=13;
  ret[1]=10;
  ret[2]=0;

  // make file name
  bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

  strcpy(fn1,st2);
  bw_inkey1.strtrim(fn1,FN_SIZE);
  i=bw_inkey1.strlocc(fn1,FN_SIZE,'.');
  fn1[i]=0;
  strcat(fn1,".mem");

//  MessageBox(bw_main1.win_hwnd1,fn1,"aa",MB_OK);

  //file exist
  bw_xbase1.get_win_basedir(p_dbptr,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);
  if (bw_inkey1.w_find_file(fn1)==0) return(1);
  else
  {
    bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

    strcpy(str1,st2);
    bw_inkey1.strtrim(str1,FN_SIZE);
    i=bw_inkey1.strlocc(str1,FN_SIZE,'.');
    str1[i]=0;

    bw_xbase1.w_find_empty_mfile(str1,FN_SIZE,p_dbptr);

    bw_xbase1.get_win_mem_ext(p_dbptr,str7,10);
    strcpy(str2,str1);
    strcat(str2,str7);

//    MessageBox(bw_main1.win_hwnd1,str2,fn1,MB_OK);

    j=bw_inkey1.w_cpy_file(fn1,str2);
    if (j!=0) return(0);

    fh1=fopen(fn1,"r+");
    if (fh1==NULL) return(1);

//    MessageBox(bw_main1.win_hwnd1,"copy & open ok","bb",MB_OK);

    strcpy(str4,"&&memoryno.:");
    bw_xbase1.get_win_memno(p_dbptr,str8,FN_SIZE);
    strcat(str4,str8);
    bw_inkey1.strtrim(str4,FN_SIZE);

    exist=0;
    while (!feof(fh1))
    {
      fgets(str5,SMG_SIZE,fh1);
      bw_inkey1.strtrim(str5,SMG_SIZE);

      k=strlen(str5);
      l=strlen(str4);

//      MessageBox(bw_main1.win_hwnd1,str4,str5,MB_OK);

      if (k>l) m=k;
      else m=l;

      if (strncmp(str5,str4,m)==0)  // remember error
      {
	exist=1;
	break;
      }
    }

    if (exist==0)
    {
      fclose(fh1);
      bw_inkey1.w_del_file(str2);
      return(1);
    }

//    MessageBox(bw_main1.win_hwnd1,"find1 ok,add",str6,MB_OK);

    // add edited file to mem file
    fh2=fopen(str6,"r");
    if (fh2==NULL)
    {
      fclose(fh1);
      bw_inkey1.w_del_file(str2);
      bw_inkey1.w_del_file(str6);
      return(1);
    }

    fseek(fh1,0,SEEK_CUR);

    while (!feof(fh2))
    {
      str5[0]=0;
      fgets(str5,SMG_SIZE,fh2);
      if (feof(fh2))
      {
	if (bw_inkey1.strempty(str5)==0) break;
	else
	{
	  fputs(str5,fh1);
	  fputs(ret,fh1);
	  break;
	}
      }
      else fputs(str5,fh1);
    }

    fclose(fh2);
    bw_inkey1.w_del_file(str6);

//    MessageBox(bw_main1.win_hwnd1,str2,"dd",MB_OK);

    fh3=fopen(str2,"r+");
    if (fh3==NULL)
    {
      fclose(fh1);
      bw_inkey1.w_del_file(str2);
      return(1);
    }

    strcpy(str4,"&&memoryno.:");
    bw_xbase1.get_win_memno(p_dbptr,str8,FN_SIZE);
    strcat(str4,str8);
    bw_inkey1.strtrim(str4,FN_SIZE);

    exist=0;
    while (!feof(fh3))
    {
      fgets(str5,SMG_SIZE,fh3);
      bw_inkey1.strtrim(str5,SMG_SIZE);

      k=strlen(str5);
      l=strlen(str4);

      if (k>l) m=k;
      else m=l;

//      MessageBox(bw_main1.win_hwnd1,str4,str5,MB_OK);

      if (strncmp(str5,str4,m)==0)  // remember error
      {
	exist=1;
	break;
      }
    }

    if (exist==0)
    {
      fclose(fh1);
      fclose(fh3);
      bw_inkey1.w_del_file(str2);
      return(1);
    }

    strcpy(str4,"&&memoryno.:");

    exist=0;
    while (!feof(fh3))
    {
      fgets(str5,SMG_SIZE,fh3);

//      MessageBox(bw_main1.win_hwnd1,str4,str5,MB_OK);

      if (strncmp(str5,str4,12)==0)  // remember error
      {
	exist=1;
	break;
      }
    }

    if (exist==0)
    {
      fclose(fh1);
      fclose(fh3);
      bw_inkey1.w_del_file(str2);
      return(1);
    }

    if (!feof(fh3)) fputs(str5,fh1);

    while (!feof(fh3))
    {
      fgets(str5,SMG_SIZE,fh3);
      fputs(str5,fh1);
    }

    fclose(fh1);
    fclose(fh3);
    bw_inkey1.w_del_file(str2);
  }

  return(0);
}

int bw_fldstru::w_edit_memo_add(int p_dbptr,int p_wptr,char *p_fldname,int p_fldname_size)
{
  int  i,j,k,l,m,n;
  char s_tc0[SMG_SIZE];
  char s_tc1[SMG_SIZE];
  char s_tc2[SMG_SIZE];
  char s_tc3[SMG_SIZE];
  char s_tc4[SMG_SIZE];
  char s_tc5[SMG_SIZE];
  char s_tc6[SMG_SIZE];
  char s_tc7[SMG_SIZE];
  char s_tc8[SMG_SIZE];
  char fn1[FN_SIZE];
  char str[SMG_SIZE];
  char str1[SMG_SIZE];
//  char str2[FN_SIZE];
//  char str3[FN_SIZE];
  char str4[SMG_SIZE];
  char str5[50];
  char str6[SMG_SIZE];
  char str7[10];
  char str8[SMG_SIZE];
  char ret[10];
  char sstr[20];
  char st1[FN_SIZE];
  char st2[FN_SIZE];
  FILE *fh;
//  FILE *fh1;
  long mno;
  long mnu;
  long mnop;
  int  exist;
  int  mark=0;

  strcpy(s_tc0,"*.*");
  strcpy(s_tc6,"Select File For Add To Base");
  bw_main1.dlg_f1.lStructSize=sizeof(OPENFILENAME);
  bw_main1.dlg_f1.hwndOwner=bw_main1.win_hwnd;
  strcpy(s_tc1,"ALL File");
  strcat(s_tc1,"(");
  strcat(s_tc1,s_tc0);
  strcat(s_tc1,")");
  j=strlen(s_tc1);
  for (i=0;i<=(int)strlen(s_tc0);i++) s_tc1[j+1+i]=s_tc0[i];
  s_tc1[j+1+i]=0;
  bw_main1.dlg_f1.lpstrFilter=s_tc1;
  bw_main1.dlg_f1.nFilterIndex=1;
  strcpy(s_tc2,s_tc0);
  bw_main1.dlg_f1.lpstrFile=s_tc2;
  bw_main1.dlg_f1.nMaxFile=FN_SIZE;
  bw_main1.dlg_f1.lpstrFileTitle=s_tc3;
  bw_main1.dlg_f1.nMaxFileTitle=FN_SIZE;
  bw_main1.dlg_f1.lpstrInitialDir=NULL;
  bw_main1.dlg_f1.lpstrTitle=s_tc6;
  strcpy(s_tc4,"txt");
  bw_main1.dlg_f1.lpstrDefExt=s_tc4;
  bw_main1.dlg_f1.lpstrCustomFilter=s_tc5;
  bw_main1.dlg_f1.nMaxCustFilter=FN_SIZE;
  bw_main1.dlg_f1.nFileOffset=NULL;
  bw_main1.dlg_f1.nFileExtension=NULL;
  bw_main1.dlg_f1.Flags=NULL;

  i=GetOpenFileName(&bw_main1.dlg_f1);
  if (i==0) return(1);

  strcpy(s_tc7,bw_main1.dlg_f1.lpstrFile);
  bw_main1.w_fetch_filename(s_tc7,SMG_SIZE);
  strcpy(bw_main1.win_cpy_f1,bw_main1.win_seadir);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);
  k=strlen(bw_main1.win_cpy_f1);
  bw_main1.win_cpy_f1[k]=92;
  bw_main1.win_cpy_f1[k+1]=0;
  strcat(bw_main1.win_cpy_f1,bw_main1.win_seaname);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1,FN_SIZE);

  bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

  strcpy(s_tc7,st2);
  bw_inkey1.strtrim(s_tc7,SMG_SIZE);
  i=bw_inkey1.strlocc(s_tc7,SMG_SIZE,'.');
  s_tc7[i]=0;

  bw_xbase1.w_find_empty_mfile(s_tc7,SMG_SIZE,p_dbptr);

  strcpy(s_tc8,s_tc7);
  bw_xbase1.get_win_mem_ext(p_dbptr,str7,10);
  strcat(s_tc8,str7);

  bw_xbase1.get_win_basedir(p_dbptr,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  w_wps_to_txt(bw_main1.win_cpy_f1,FN_SIZE,s_tc8,SMG_SIZE);

  //if already in use return
  if (bw_xbase1.get_win_mem_inuse(p_dbptr)==1) return(0);

  //make empty string
  for (i=0;i<=10;i++) sstr[i]=' ';
  sstr[10]=0;

  //save field name
  if (p_fldname_size>0) p_fldname[p_fldname_size-1]=0;
  strcpy(str6,p_fldname);

  // make return string
  ret[0]=13;
  ret[1]=10;
  ret[2]=0;

  // make file name
  bw_xbase1.get_win_basename(p_dbptr,st2,FN_SIZE);

  strcpy(fn1,st2);
  bw_inkey1.strtrim(fn1,FN_SIZE);
  i=bw_inkey1.strlocc(fn1,FN_SIZE,'.');
  fn1[i]=0;
  strcat(fn1,".mem");

  bw_xbase1.get_win_memno(p_dbptr,str8,SMG_SIZE);

  //file exist
  bw_xbase1.get_win_basedir(p_dbptr,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);
  if (bw_inkey1.w_find_file(fn1)==1)
  {
    fh=fopen(fn1,"r+");
    if (fh==NULL) return(1);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_SIZE,fh);

      if (strncmp(str4,"&&memorynum:",12)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      bw_inkey1.cut_string(str4,12,8,SMG_SIZE,str,SMG_SIZE);
      bw_inkey1.strtrim(str,SMG_SIZE);
      mnu=bw_inkey1.str2long(str,SMG_SIZE);
    }
    else
    {
      fclose(fh);
      return(1);
    }

    fseek(fh,0,0);

    if (bw_inkey1.strempty(str8)==0)
    {
      mnu++;
      mno=mnu;
      mark=1;
      bw_inkey1.long2str(mno,str8,SMG_SIZE);
    }
    else
    {
      mno=bw_inkey1.str2long(str8,SMG_SIZE);
      mark=0;
    }

    strcpy(str5,"&&memoryno.:");
    strcat(str5,str8);
    strcat(str5,sstr);
    str5[22]=0;
    strcat(str5,ret);

    bw_inkey1.strtrim(str5,50);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_SIZE,fh);

      bw_inkey1.strtrim(str4,SMG_SIZE);

      l=strlen(str4);
      m=strlen(str5);

      if (l>m) n=l;
      else n=m;

      if (strncmp(str4,str5,n)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist!=1)
    {
      strcpy(str,str8);

      fseek(fh,0,SEEK_END);

      fputs(ret,fh);
      strcpy(str1,"&&memoryno.:");
      strcat(str1,str);
      strcat(str1,sstr);
      str1[22]=0;
      strcat(str1,ret);
      fputs(str1,fh);

      bw_xbase1.set_win_memno(p_dbptr,str8,strlen(str8)+1);
    }
    else  bw_xbase1.set_win_memno(p_dbptr,str8,strlen(str8)+1);
  }
  else return(1);

  if (mark==1)
  {
    bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0)-1);

    w_sav_tab_var(str6,SMG_SIZE,p_dbptr,str8,SMG_SIZE);
    bw_mbase1.w_save_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,0));
    bw_xbase1.set_win_state_dbf_modi(p_dbptr,1);

    fseek(fh,0,0);

    mnop=0;
    exist=0;
    while (!feof(fh))
    {
      mnop=fseek(fh,0,SEEK_CUR);
      fgets(str4,SMG_SIZE,fh);
      if (strncmp(str4,"&&memorynum:",12)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==0)
    {
      fclose(fh);
      return(1);
    }
    else
    {
      fseek(fh,mnop,0);

      bw_inkey1.long2str(mnu,str,SMG_SIZE);

      strcpy(str1,"&&memorynum:");
      strcat(str1,str);
      strcat(str1,sstr);
      str1[22]=0;
      strcat(str1,ret);
      fputs(str1,fh);

      fclose(fh);
    }
  }
  else fclose(fh);

  bw_xbase1.set_win_mem_inuse(p_dbptr,1);
  bw_xbase1.set_win_mem_fn(p_dbptr,s_tc8,SMG_SIZE);
  bw_win1.set_win_memo_basep(p_wptr,p_dbptr);

  w_edit_memo_close(p_wptr);

  return(0);
}

int bw_fldstru::w_wps_to_txt(char *p_s1,int p_s1_size,char *p_s2,int p_s2_size)
{
  FILE     *s_fp1;
  FILE     *s_fp2;
  unsigned char c1;
  unsigned char str[SMG_SIZE];
  //char          i_stc1[SMG_SIZE];
  //char          i_stc2[SMG_SIZE];
  //int           i,j;

  s_fp1=fopen(p_s1,"r");
  if (s_fp1==NULL) return(1);
  s_fp2=fopen(p_s2,"w");
  if (s_fp2==NULL)
  {
    fclose(s_fp1);
    return(1);
  }

  fgets((char *)str,10,s_fp1);

  if (((str[0]==2)||(str[0]==3))&&(str[1]==255))
  {
    fseek(s_fp1,1024,0);
  }
  else fseek(s_fp1,0,0);

  while (!feof(s_fp1))
  {
    c1=fgetc(s_fp1);
    if (c1==127) c1=' ';
    if (c1==128+13) c1=' ';
    if (c1==128+10) c1='\n';
    fputc(c1,s_fp2);
  }

  fclose(s_fp1);
  fclose(s_fp2);

  return(0);
}





int bw_fldstru::get_t2_fldpoin(int dbptr,int p01)
{
  if ((dbptr<0)||(dbptr>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(t2_fldpoin[dbptr][p01]);
}
int bw_fldstru::get_t2_fldtype(int fbptr)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  return(t2_fldtype[fbptr]);
}
int bw_fldstru::get_t2_fldlen(int fbptr)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  return(t2_fldlen[fbptr]);
}
int bw_fldstru::get_t2_flddec(int fbptr)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  return(t2_flddec[fbptr]);
}
int bw_fldstru::get_t2_fldposi(int fbptr)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  return(t2_fldposi[fbptr]);
}

int bw_fldstru::set_t2_fldpoin(int dbptr,int p01,int val)
{
  if ((dbptr<0)||(dbptr>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  t2_fldpoin[dbptr][p01]=val;
  return(0);
}
int bw_fldstru::set_t2_fldtype(int fbptr,int val)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  t2_fldtype[fbptr]=val;
  return(0);
}
int bw_fldstru::set_t2_fldlen(int fbptr,int val)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  t2_fldlen[fbptr]=val;
  return(0);
}
int bw_fldstru::set_t2_flddec(int fbptr,int val)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  t2_flddec[fbptr]=val;
  return(0);
}
int bw_fldstru::set_t2_fldposi(int fbptr,int val)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  t2_fldposi[fbptr]=val;
  return(0);
}

int bw_fldstru::get_t2_fldname(int fbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  p_s1[0]=0;

  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  for (j=0;j<i-1;j++)
  {
    p_s1[j+0]=t2_fldname[fbptr][j];
    p_s1[j+1]=0;
  }

  return(0);
}
int bw_fldstru::set_t2_fldname(int fbptr,char *p_s1,int p_s1_size)
{
  int i,j;

  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);

  if (p_s1_size>11) i=11;
  else i=p_s1_size;

  t2_fldname[fbptr][0]=0;

  for (j=0;j<i-1;j++)
  {
    t2_fldname[fbptr][j+0]=p_s1[j];
    t2_fldname[fbptr][j+1]=0;
  }

  return(0);
}
int bw_fldstru::set_c_t2_fldname(int fbptr,int p0a,int val)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  t2_fldname[fbptr][p0a]=val;
  return(0);
}
int bw_fldstru::get_c_t2_fldname(int fbptr,int p0a)
{
  if ((fbptr<0)||(fbptr>=FLD_IN_BASE)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  return(t2_fldname[fbptr][p0a]);
}





int bw_fldstru::w_down_line(int p_dbptr,int p_wptr)
{
  int i,j,k,l;
  int s_tmpn1;
  int r1,r2;

  i=w_last_line(p_dbptr,p_wptr);
  if (i==0) { /*MessageBox(0,"aa","aa",MB_OK);*/ bw_win1.w_down_field(p_wptr);}
  else
  {
    j=w_be_linked(p_dbptr,p_wptr);  // type 0,1 not link,type 2,3 linked
    if (j==1) { /*MessageBox(0,"bb","bb",MB_OK);*/ bw_win1.w_down_field(p_wptr);}
    else
    {
      k=w_have_next_rec(p_dbptr,p_wptr);
      if (k==0) { /*MessageBox(0,"cc","cc",MB_OK);*/ bw_win1.w_down_field(p_wptr);}
      else 
      {





  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
    //if (bw_xbase1.win_state_dbf_err==1) break;

    w_echo_winrec(p_wptr);
    //w_first_editposi(p_dbptr,p_wptr);
    //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

    return(0);
  }
  else
  {
      while (1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1)
      {
	while (1)
	{
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	  j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win1.get_t_fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(p_wptr,p_dbptr);
	  if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	  if (bw_xbase1.win_state_dbf_err==1) break;
	}
	if (bw_xbase1.win_state_dbf_err==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);
	//break;
      }

      i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
      bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
      bw_link1.w_link_set_continue(p_wptr,p_dbptr);
      bw_link1.w_echo_winrec_lnk(p_wptr);
    //w_first_editposi(p_dbptr,p_wptr);
    //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

      return(0);
  }





      }
    }
  }

  return(0);
}

int bw_fldstru::w_down_line2(int p_dbptr,int p_wptr) // button command
{
  int i,j,k,l;
  int r1,r2;

    j=w_be_linked(p_dbptr,p_wptr);  // type 0,1 not link,type 2,3 linked
    if (j==1) { /*MessageBox(0,"bb","bb",MB_OK);*/ /*bw_win1.w_down_field(p_wptr);*/}
    else
    {
      k=w_have_next_rec(p_dbptr,p_wptr);
      if (k==0) { /*MessageBox(0,"cc","cc",MB_OK);*/ /*bw_win1.w_down_field(p_wptr);*/}
      else 
      {




  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
    //if (bw_xbase1.win_state_dbf_err==1) break;

    w_echo_winrec(p_wptr);
    //w_first_editposi(p_dbptr,p_wptr);
    //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

    return(0);
  }
  else
  {
      while (1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1)
      {
	while (1)
	{
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	  j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win1.get_t_fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(p_wptr,p_dbptr);
	  if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	  if (bw_xbase1.win_state_dbf_err==1) break;
	}
	if (bw_xbase1.win_state_dbf_err==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);
	//break;
      }

      i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
      bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
      bw_link1.w_link_set_continue(p_wptr,p_dbptr);
      bw_link1.w_echo_winrec_lnk(p_wptr);
    //w_first_editposi(p_dbptr,p_wptr);
    //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

      return(0);
  }




      }
    }

	return(0);
}


int bw_fldstru::w_last_line(int p_dbptr,int p_wptr)
{
  int  i,j,k,l,m;
  int  exist;
  char str[SMG_SIZE];

  exist=0;

  for (i=bw_win1.pline+1;i<LIN_NUM;i++) /* find next screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
	k=bw_buff1.get_t3_linecol(p_wptr,i,j);
	m=bw_win1.get_t_fldedt(k); // edit field
	l=bw_win1.get_t_fldbase(k);
        bw_win1.get_t_fldname(k,str,SMG_SIZE);
	if ((str[0]==':')&&(l==p_dbptr)&&(m==0)) 
        { 
          exist=1; 
          break; 
        }
/*
      if (bw_buff1.get_t3_linecol(p_wptr,i,j)>0)
      {
	if ((bw_win1.get_t_fldedt(bw_buff1.get_t3_linecol(p_wptr,i,j))==0)&&
            (bw_win1.get_t_fldbase(bw_buff1.get_t3_linecol(p_wptr,i,j))==p_dbptr))
	{
	  exist=1;
	  break;
	}
      }
*/
    }
    if (exist==1) break;
  }

  if (exist==0) return(1);
  else return(0);
}

int bw_fldstru::w_be_linked(int p_dbptr,int p_wptr)
{
  if (bw_xbase1.get_win_lnktab(p_dbptr)>1) return(1);
  else return(0);
}

int bw_fldstru::w_have_next_rec(int p_dbptr,int p_wptr)
{
  int  i,j,k,l;
  int  s_tmpn1;
  int  r1,r2;

  r1=bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)-1;
  r2=0;

  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    s_tmpn1=1+bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
    for (i=1;i<=s_tmpn1;i++)
    {
      r2=bw_mbase1.w_down_rec(p_dbptr,p_wptr,r1);
      r1=r2;
      if (bw_xbase1.win_state_dbf_err==1) return(0);
    }
    return(1);
  }
  else
  {
    s_tmpn1=1+bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM);
    for (i=1;i<=s_tmpn1;i++)
    {
      while (1)
      {
	r2=bw_mbase1.w_down_rec(p_dbptr,p_wptr,r1);
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
        r1=r2;
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1) return(0);
    }
    return(1);
  }
}

int bw_fldstru::w_up_line(int p_dbptr,int p_wptr)
{
  int i,j,k,l;
  int r1,r2;
  int s_tmpn1;

  i=w_first_line(p_dbptr,p_wptr);
  if (i==0) { /*MessageBox(0,"aa","aa",MB_OK);*/ bw_win1.w_up_field(p_wptr); }
  else
  {
    j=w_be_linked(p_dbptr,p_wptr);
    if (j==1) { /*MessageBox(0,"bb","bb",MB_OK);*/ bw_win1.w_up_field(p_wptr); }
    else
    {
      k=w_have_prev_rec(p_dbptr,p_wptr);
      if (k==0) { /*MessageBox(0,"cc","cc",MB_OK);*/ bw_win1.w_up_field(p_wptr); }
      else 
      {




  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
    //if (bw_xbase1.win_state_dbf_err==1) break;

    w_echo_winrec(p_wptr);
    //w_first_editposi(p_dbptr,p_wptr);
    //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

    return(0);
  }
  else
  {
      while (1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)-1);
	while (1)
        {
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	  j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win1.get_t_fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(p_wptr,p_dbptr);
	  if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	  if (bw_xbase1.win_state_dbf_err==1) break;
	}
	if (bw_xbase1.win_state_dbf_err==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);
	//break;
      }

      i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
      bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
      bw_link1.w_link_set_continue(p_wptr,p_dbptr);
      bw_link1.w_echo_winrec_lnk(p_wptr);
      //w_first_editposi(p_dbptr,p_wptr);
      //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
      //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

      return(0);
  }




      }
    }
  }

  return(0);
}

int bw_fldstru::w_up_line2(int p_dbptr,int p_wptr)
{
  int i,j,k,l;
  int r1,r2;

    j=w_be_linked(p_dbptr,p_wptr);
    if (j==1) { /*MessageBox(0,"bb","bb",MB_OK);*/ /*bw_win1.w_up_field(p_wptr);*/ }
    else
    {
      k=w_have_prev_rec(p_dbptr,p_wptr);
      if (k==0) { /*MessageBox(0,"cc","cc",MB_OK);*/ /*bw_win1.w_up_field(p_wptr);*/ }
      else 
      {




  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
    //if (bw_xbase1.win_state_dbf_err==1) break;

    w_echo_winrec(p_wptr);
    //w_first_editposi(p_dbptr,p_wptr);
    //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
    //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

    return(0);
  }
  else
  {
      while (1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1)
      {
	bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)-1);
	while (1)
        {
	  bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,bw_mbase1.w_down_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1)));
	  j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win1.get_t_fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(p_wptr,p_dbptr);
	  if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	  if (bw_xbase1.win_state_dbf_err==1) break;
	}
	if (bw_xbase1.win_state_dbf_err==1) bw_xbase1.set_win_recno(p_dbptr,p_wptr,1,1);
	//break;
      }

      i=bw_link1.w_link_base_num(p_wptr,p_dbptr);
      bw_link1.w_link_modi_mark(p_wptr,i,-1,-1);
      bw_link1.w_link_set_continue(p_wptr,p_dbptr);
      bw_link1.w_echo_winrec_lnk(p_wptr);
      //w_first_editposi(p_dbptr,p_wptr);
      //bw_xbase1.set_win_cur_seri(p_dbptr,p_wptr,1);
      //bw_xbase1.set_win_recno(p_dbptr,p_wptr,0,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));

      return(0);
  }




      }
    }

    return(0);
}

int bw_fldstru::w_first_line(int p_dbptr,int p_wptr)
{
  int  i,j,k,l,m;
  int  exist;
  char str[SMG_SIZE];

  exist=0;

  for (i=bw_win1.pline-1;i>=1;i--)
  {
    for (j=COL_NUM-1;j>=1;j--)
    {

	k=bw_buff1.get_t3_linecol(p_wptr,i,j);
	m=bw_win1.get_t_fldedt(k); // edit field
	l=bw_win1.get_t_fldbase(k);
        bw_win1.get_t_fldname(k,str,SMG_SIZE);
	if ((str[0]==':')&&(l==p_dbptr)&&(m==0))
        { 
          exist=1; 
          break; 
        }
/*
      if (bw_buff1.get_t3_linecol(p_wptr,i,j)>0)
      {
	if ((bw_win1.get_t_fldedt(bw_buff1.get_t3_linecol(p_wptr,i,j))==0)&&
            (bw_win1.get_t_fldbase(bw_buff1.get_t3_linecol(p_wptr,i,j))==p_dbptr))
	{
	  exist=1;
	  break;
	}
      }
*/
    }
    if (exist==1) break;
  }

  if (exist==0) return(1);
  else return(0);
}

int bw_fldstru::w_have_prev_rec(int p_dbptr,int p_wptr)
{
  int i,j,k,l;
  int s_tmpn1;
  int r1,r2;

  if (bw_xbase1.get_win_lnktab(p_dbptr)==0)
  {
    s_tmpn1=1/*+bw_win1.w_cnt_winline(p_dbptr,p_wptr,LIN_NUM)*/;
    for (i=1;i<=s_tmpn1;i++)
    {
      bw_mbase1.w_up_rec(p_dbptr,p_wptr,bw_xbase1.get_win_recno(p_dbptr,p_wptr,1));
      if (bw_xbase1.win_state_dbf_err==1) return(0);
    }
    return(1);
  }
  else
  {
      r1=bw_xbase1.get_win_recno(p_dbptr,p_wptr,1);
      r2=0;

      while (1)
      {
	r2=bw_mbase1.w_up_rec(p_dbptr,p_wptr,r1);
	j=bw_buff1.get_t3_linecol(p_wptr,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win1.get_t_fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(p_wptr,p_dbptr);
        r1=r2;
	if (bw_link1.w_link_cond_ok(l,p_wptr,p_dbptr,k,1)==1) break;
	if (bw_xbase1.win_state_dbf_err==1) break;
      }
      if (bw_xbase1.win_state_dbf_err==1) return(0);
      else return(1);
  }
}


