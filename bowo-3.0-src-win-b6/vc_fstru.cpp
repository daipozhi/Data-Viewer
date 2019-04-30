#define STRICT
#include <windows.h>
#include <commdlg.h>
 
#include <stdio.h>
#include <math.h>
//#include <dir.h>
#include <dos.h>
//#include <bios.h>
#include <conio.h>
#include <process.h>
#include <string.h>

#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>

#include "vc_bowo.h"

extern class bw_fldstru_bua  bw_fldstru_bua1;
extern class bw_dialog_bua   bw_dialog_bua1;
extern class bw_xbase_bua    bw_xbase_bua1;
extern class bw_win_bub      bw_win_bub1;
extern class bw_win_bua      bw_win_bua1;
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

int bw_fldstru::w_cnt_tabfield(int p_fcnt)
{
//  int i,j,k;
  return(bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1)-bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0)+1);
}
int bw_fldstru::w_cnt_reclen(int p_fcnt)
{
  int i;
  unsigned j;
  j=0;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    j=j+bw_fldstru_bua1.get_t2_fldlen(i);
  }
  return(j);
}
int bw_fldstru::w_cnt_fldposi(int p_fcnt)
{
  int i,j;
  j=1;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru_bua1.set_t2_fldposi(i,j);
    j=j+bw_fldstru_bua1.get_t2_fldlen(i);
  }
  return(0);
}
int bw_fldstru::w_read_stru(char *p_fn1,int len,int pstn)
{
  int  exist;
  int  i,j,k,l/*,m,n*/;
  int  p1,p2,p3,p4,p5,p6,p7/*,same,*//*spg,*//*ends*/;
  //int  state2,state3;
  //int  state4,state5,state6;
  int  pp1/*,pp2*/;
  //char str[SMG_LEN];
  char tmpc2[SMG_LEN];
  //char stc[FN_SIZE];
  FILE *fp1;
/*
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=p_fn1[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //bw_main1.set_string(stc,FN_SIZE,p_fn1,len);

  exist=0;
  for (i=0;i<FLD_IN_BASE;i++)
  {
    if (bw_fldstru_bua1.get_t2_fldtype(i)==0)
    {
      exist=1;
      break;
    }
  }

  if (exist==0) return(1);
  else pp1=i;

  bw_fldstru_bua1.set_t2_fldpoin(pstn,0,pp1);

  fp1=fopen(p_fn1,"r");        /* fetch table field from table file */
  if (fp1==NULL)
  {
    bw_win1.w_atten1(p_fn1);
    return(1);
  }
  k=0;
  while (!feof(fp1))
  {
    for (i=0;i<SMG_LEN;i++) tmpc2[i]=0;
    fgets(tmpc2,SMG_LEN,fp1);
    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>0)) tmpc2[i]=' ';
						  /* scan for pre space */
    for (i=0;i<SMG_LEN;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=SMG_LEN) break;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for fldrem */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
					 /* scan for space after fldrem */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p1=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for fldname */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p2=i-1;
					  /* scan for space after fldname */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p3=i;
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]==' ') break; /* scan for fldtype */
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
				   /* scan for space after fldtype */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    if (i>=SMG_LEN)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
    p4=i;
				   /* scan for fldlen*/
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]<=' ') break;
    p5=i-1;
    if (p4>p5)
    {
      fclose(fp1);
      bw_win1.w_atten2();
      return(1);
    }
				   /* scan for space after fldlen */
    for (i=i;i<SMG_LEN;i++) if (tmpc2[i]!=' ') break;
    p6=i;
				   /* scan for space after fldlen */
    for (i=i;i<SMG_LEN;i++) if ((tmpc2[i]==' ')||(tmpc2[i]==0)) break;
    p7=i-1;
    k++;
    for (j=p1;j<=p2;j++)
    {
      if (tmpc2[j]==' ') break;
      bw_fldstru_bua1.setc_t2_fldname(pp1+k-1,j-p1,tmpc2[j]);
      bw_fldstru_bua1.setc_t2_fldname(pp1+k-1,j-p1+1,0);
    }

    l=bw_inkey1.char2int(tmpc2,p4,p5);

    bw_fldstru_bua1.set_t2_fldtype(pp1+k-1,tmpc2[p3]);

    if ((bw_fldstru_bua1.get_t2_fldtype(pp1+k-1)=='c')||(bw_fldstru_bua1.get_t2_fldtype(pp1+k-1)=='n'))
    {
      bw_fldstru_bua1.set_t2_fldlen(pp1+k-1,l);
    }
    else
    {
      if (bw_fldstru_bua1.get_t2_fldtype(pp1+k-1)=='m') bw_fldstru_bua1.set_t2_fldlen(pp1+k-1,8);
      else
      {
	if (bw_fldstru_bua1.get_t2_fldtype(pp1+k-1)=='b') bw_fldstru_bua1.set_t2_fldlen(pp1+k-1,250);
	else bw_fldstru_bua1.set_t2_fldlen(pp1+k-1,1);
      }
    }

    l=bw_inkey1.char2int(tmpc2,p6,p7);
    bw_fldstru_bua1.set_t2_flddec(pp1+k-1,l);
  }

  bw_fldstru_bua1.set_t2_fldpoin(pstn,1,pp1+k-1);

  fclose(fp1);

  bw_xbase_bua1.set_win_lcnt(pstn,0,w_cnt_tabfield(pstn)); /*fldnum 2 */
  bw_xbase_bua1.set_win_lcnt(pstn,1,w_cnt_reclen(pstn));   /*reclen 3 */
  w_cnt_fldposi(pstn);

  return(0);
}
int bw_fldstru::tst_stru()
{
  HDC  hdc;
  int  i;
  char str[SMG_LEN];
  char sf1[SMG_LEN];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<=50;i++)
  {
    bw_fldstru_bua1.get_t2_fldname(i,sf1,20);

    sprintf(str,"n=%s,t=%c,l=%d,d=%d,p=%d,"
	       ,sf1
	       ,bw_fldstru_bua1.get_t2_fldtype(i)
	       ,bw_fldstru_bua1.get_t2_fldlen(i)
	       ,bw_fldstru_bua1.get_t2_flddec(i)
	       ,bw_fldstru_bua1.get_t2_fldposi(i));
    TextOut(hdc,1,i*20,str,strlen(str));
  }

  for (i=0;i<STRU_NUM;i++)
  {
    sprintf(str,"poin01=%d,%d,"
	       ,bw_fldstru_bua1.get_t2_fldpoin(i,0)
	       ,bw_fldstru_bua1.get_t2_fldpoin(i,1));
    TextOut(hdc,300,i*20,str,strlen(str));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}

int bw_fldstru::w_dele_stru(int p_fcnt)
{
  int  i,j;
  int  p1,p3,p4;
  int  n1;
  int  exist;
  //char str[SMG_LEN];
  char sf1[SMG_LEN];

  n1=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1)-bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0)+1;
  p1=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);
  p4=0;

  while (1)
  {
    exist=0;
    for (i=0;i<STRU_NUM;i++)
    {
      if (bw_fldstru_bua1.get_t2_fldpoin(i,0)>p1)
      {
	exist=1;
	p3=i;
	break;
      }
    }
    if (exist==0) break;

    p1=bw_fldstru_bua1.get_t2_fldpoin(p3,1);

    if (p4<bw_fldstru_bua1.get_t2_fldpoin(p3,1)) p4=bw_fldstru_bua1.get_t2_fldpoin(p3,1);

    for (j=bw_fldstru_bua1.get_t2_fldpoin(p3,0);j<=bw_fldstru_bua1.get_t2_fldpoin(p3,1);j++)
    {
      bw_fldstru_bua1.get_t2_fldname(j,sf1,20);
      bw_fldstru_bua1.set_t2_fldname(j-n1,sf1,20);

      bw_fldstru_bua1.set_t2_fldtype(j-n1,bw_fldstru_bua1.get_t2_fldtype(j));
      bw_fldstru_bua1.set_t2_fldlen(j-n1,bw_fldstru_bua1.get_t2_fldlen(j));
      bw_fldstru_bua1.set_t2_flddec(j-n1,bw_fldstru_bua1.get_t2_fldlen(j));
      bw_fldstru_bua1.set_t2_fldposi(j-n1,bw_fldstru_bua1.get_t2_fldposi(j));
    }

    bw_fldstru_bua1.set_t2_fldpoin(p3,0,bw_fldstru_bua1.get_t2_fldpoin(p3,0)-n1);
    bw_fldstru_bua1.set_t2_fldpoin(p3,1,bw_fldstru_bua1.get_t2_fldpoin(p3,1)-n1);
  }

  if (p4==0) p4=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);

  for (i=p4-n1+1;i<=p4;i++)
  {
    bw_fldstru_bua1.setc_t2_fldname(i,0,0);;
    bw_fldstru_bua1.set_t2_fldtype(i,0);
    bw_fldstru_bua1.set_t2_fldlen(i,0);
    bw_fldstru_bua1.set_t2_flddec(i,0);
    bw_fldstru_bua1.set_t2_fldposi(i,0);
  }

  bw_fldstru_bua1.set_t2_fldpoin(p_fcnt,0,0);
  bw_fldstru_bua1.set_t2_fldpoin(p_fcnt,1,0);

  bw_xbase_bua1.set_win_lcnt(p_fcnt,0,0); /*fldnum 2 */
  bw_xbase_bua1.set_win_lcnt(p_fcnt,1,0);   /*reclen 3 */

  return(0);
}

int bw_fldstru::w_find_fldnum(char *p_str,int len,int p_fcnt)
{
  int  i,j;
  int  exist;
  char sf1[SMG_LEN];
  //char stc[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=str[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //bw_main1.set_string(stc,SMG_LEN,str,len);

  exist=0;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru_bua1.get_t2_fldname(i,sf1,20);

    if (strcmp(p_str,sf1)==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    win_field_num=i;
    return(0);
  }
  else return(1);
}
int bw_fldstru::w_find_fldlen(char *p_str,int len,int p_fcnt)
{
  int  i,j;
  int  exist;
  char sf1[SMG_LEN];
  //char stc[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=str[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //bw_main1.set_string(stc,SMG_LEN,str,len);

  exist=0;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru_bua1.get_t2_fldname(i,sf1,20);

    if (strcmp(p_str,sf1)==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    win_field_num=i;
    return(bw_fldstru_bua1.get_t2_fldlen(i));
  }
  else return(0);
}
int bw_fldstru::w_find_fldtype(char *p_str,int len,int p_fcnt)
{
  int  i,j;
  int  exist;
  char sf1[SMG_LEN];
  //char stc[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=str[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //bw_main1.set_string(stc,SMG_LEN,str,len);

  exist=0;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru_bua1.get_t2_fldname(i,sf1,20);

    if (strcmp(p_str,sf1)==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    win_field_num=i;
    return(bw_fldstru_bua1.get_t2_fldtype(i));
  }
  else return(0);
}
int bw_fldstru::w_find_flddec(char *p_str,int len,int p_fcnt)
{
  int  i,j;
  int  exist;
  char sf1[SMG_LEN];
  //char stc[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=str[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //bw_main1.set_string(stc,SMG_LEN,str,len);

  exist=0;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru_bua1.get_t2_fldname(i,sf1,20);

    if (strcmp(p_str,sf1)==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    win_field_num=i;
    return(bw_fldstru_bua1.get_t2_flddec(i));
  }
  else return(0);
}
int bw_fldstru::w_find_fldposi(char *p_str,int len,int p_fcnt)
{
  int  i,j;
  int  exist;
  char sf1[SMG_LEN];
  //char stc[SMG_LEN];
/*
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++) stc[j]=str[j];
  if (i>0) stc[i-1]=0;
  else stc[0]=0;
*/
  //bw_main1.set_string(stc,SMG_LEN,str,len);

  exist=0;
  for (i=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,0);i<=bw_fldstru_bua1.get_t2_fldpoin(p_fcnt,1);i++)
  {
    bw_fldstru_bua1.get_t2_fldname(i,sf1,20);
    if (strcmp(p_str,sf1)==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==1)
  {
    win_field_num=i;
    return(bw_fldstru_bua1.get_t2_fldposi(i));
  }
  else return(0);
}
int bw_fldstru::w_find_fldpoin0(int i)
{
  return(bw_fldstru_bua1.get_t2_fldpoin(i,0));
}
int bw_fldstru::w_find_fldpoin1(int i)
{
  return(bw_fldstru_bua1.get_t2_fldpoin(i,1));
}
int bw_fldstru::w_find_fldname(int j,int i,char *p_str,int len)
{
  char stc[SMG_LEN];

   if ((i<bw_fldstru_bua1.get_t2_fldpoin(j,0))||(i>bw_fldstru_bua1.get_t2_fldpoin(j,1))) return(1);
  else
  {
    bw_fldstru_bua1.get_t2_fldname(i,stc,11);
/*
    if (len>11) i=11;
    else i=len;
    for (j=0;j<i-1;j++) str[j]=stc[j];
    if (i>0) str[i-1]=0;
    else str[0]=0;
*/
    bw_main1.set_string(p_str,len,stc,SMG_LEN);

  }

  return(0);
}
int bw_fldstru::w_echo_winrec(int wpp)
{
  HWND hnd;
  long s_recno[STRU_NUM];
  int  s_seri[STRU_NUM];
  char s_fldname[SMG_LEN];
  int  i,j,k,l,m,n,o,p,q,r,s,t;
  int  p1,p2;
  int  exist;
  char logic;
  char str[SMG_LEN];
  char str2[SMG_LEN];
  char str3[SMG_LEN];

  HFONT  holdfont,hfont;
  HDC    hdc;

  hdc=GetDC(bw_main1.win_hwnd);
  hfont=(HFONT)GetStockObject(OEM_FIXED_FONT);
  holdfont=(HFONT)SelectObject(hdc,hfont);

  exist=0;
  for (i=0;i<STRU_NUM;i++)
  {
    if ((bw_win_bua1.get_win_pp9(i,wpp)==1)&&(bw_xbase_bua1.get_win_lnktab(i)==0))
    {
      s_recno[i]=bw_xbase_bua1.get_win_recno(i,wpp,1)-1;
      s_seri[i]=0;
      bw_xbase_bua1.set_win_enseri(i,wpp,0);
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
    if ((bw_win_bua1.get_win_pp9(k,wpp)!=1)||(bw_xbase_bua1.get_win_lnktab(k)!=0)) continue;
    for (l=1;l<=bw_win1.w_cnt_winline(k,wpp,LIN_NUM);l++)
    {
      for (i=1;i<LIN_NUM;i++)
      {
	for (j=1;j<COL_NUM;j++)
	{
	  if (bw_buff1.get_linecol(wpp,i,j)!=0)
	  {
	    m=bw_buff1.get_linecol(wpp,i,j);

            bw_win_bua1.get_1fldname(m,str2,SMG_LEN);

	    if ((str2[0]!=':')&&(str2[0]!='%')&&(str2[0]!='+')&&(str2[0]!='-')) continue;

	    if (bw_win_bua1.get_1fldbase(m)!=k) continue;
	    if (bw_win_bua1.get_1fldseri(m)!=l) continue;

	    strcpy(str,str2);
            bw_inkey1.strpcut(str,1,strlen(str)-1,SMG_LEN,s_fldname,SMG_LEN);

	    if (s_seri[k]!=bw_win_bua1.get_1fldseri(m))
	    {
	      s_recno[k]=bw_mbase1.w_down_rec(k,wpp,s_recno[k]);
	      s_seri[k]=bw_win_bua1.get_1fldseri(m);
	      if (bw_xbase1.win_state3==0)
	      {
		bw_xbase_bua1.set_win_enseri(k,wpp,l);
		if (bw_xbase_bua1.get_win_recno(k,wpp,0)<=0)
                {
		  bw_xbase_bua1.set_win_recno(k,wpp,0,1);
		}
//		bw_xbase_bua1.set_win_recno(k,wpp,0,s_seri[k]);
	      }
	    }

		 /* fetch win_field number */
	    n=w_find_fldnum(s_fldname,SMG_LEN,k);
	    if (n==1) continue;

	    p=w_find_fldposi(s_fldname,SMG_LEN,k);
	    q=w_find_fldlen(s_fldname,SMG_LEN,k);

	    s=w_find_fldtype(s_fldname,SMG_LEN,k);
	    if (s=='m') continue;
            if (s=='b') continue;

	    for (o=1;o<=q;o++) str[o-1]=bw_xbase_bua1.get_win_recvar(p+o-1);

	    str[q]=0;

	    strcpy(str3,str);

	    str[bw_win_bua1.get_1fldlen(m)]=0;

	    if (s=='l')
            {
	      logic=bw_inkey1.upper(str[0]);

	      if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
              else logic='F';

	      if (bw_xbase1.win_state3!=0) str[0]=' ';
              else str[0]=logic;
	      str[1]=0;

	      logic=bw_inkey1.upper(str3[0]);

              if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
              else logic='F';

	      if (bw_xbase1.win_state3!=0) str3[0]=' ';
	      else str3[0]=logic;
	      str3[1]=0;

	    }

	    if ((str2[0]==':')||(str2[0]=='%'))
            {
	      p1=(int)((j-bw_win_bua1.get_win_con(wpp,0))*bw_main1.win_edit_xchar);
	      p2=(int)((i-bw_win_bua1.get_win_con(wpp,1))*bw_main1.win_edit_ychar);

	      HideCaret(bw_main1.win_hwnd);
	      TextOut(hdc,p1,p2,str,strlen(str));
	      ShowCaret(bw_main1.win_hwnd);
	    }
	    else
	    {
	      t=bw_win1.w_find_hnd(wpp,j,i);
	      if (t!=0)
	      {
                hnd=bw_win_bua1.get_win_hnd(t);
		SetWindowText(hnd,str3);
              }
	    }

	    r=w_find_fldnum(s_fldname,SMG_LEN,k);
	    if (r==0)
	    {
              r=win_field_num;

              bw_link1.w_save_sv(wpp
			,k
			,r-bw_fldstru_bua1.get_t2_fldpoin(k,0)
			,bw_win_bua1.get_1fldseri(m)
                        ,bw_fldstru_bua1.get_t2_fldposi(r)
			,bw_fldstru_bua1.get_t2_fldlen(r));
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
int bw_fldstru::w_tv_get_read_paint(char *p_str,int len,int wpp,int l,int c,char comm)
{
  HWND hnd;
  int  i,j,q;
  char s1[SMG_LEN];
  char s2[SMG_LEN];
  char s3[SMG_LEN];
  char fldtype;
  char logic;

//  HDC  hdc;

  if ((p_str[0]!=':')&&(p_str[0]!='+')) return(1);

  p_str[len-1]=0;

  i=bw_buff1.get_linecol(wpp,l,c);
  j=bw_win_bua1.get_1fldbase(i);
  bw_inkey1.strpcut(p_str,1,strlen(p_str)-1,len,s2,SMG_LEN);
  if (w_find_fldnum(s2,SMG_LEN,j)!=0) return(1);

  if ((w_find_fldtype(s2,SMG_LEN,j)=='n')||(w_find_fldtype(s2,SMG_LEN,j)=='c'))
  {
    w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

    bw_xbase_bua1.set_win_scrnvar(wpp,s1,SMG_LEN);

    fldtype=w_find_fldtype(s2,SMG_LEN,j);

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      {
        hnd=bw_win_bua1.get_win_hnd(q);
	SetWindowText(hnd,s1);
      }
    }
  }
  else
  {
    if (w_find_fldtype(s2,SMG_LEN,j)=='l')
    {
      w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

      bw_xbase_bua1.set_win_scrnvar(wpp,s1,SMG_LEN);

      logic=bw_inkey1.upper(bw_xbase_bua1.getc_win_scrnvar(wpp,0));

      if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
      else logic='F';

      bw_xbase_bua1.setc_win_scrnvar(wpp,0,logic);
      bw_xbase_bua1.setc_win_scrnvar(wpp,1,0);

      bw_xbase_bua1.get_win_scrnvar(wpp,s1,SMG_LEN);

      fldtype='c';

      if (p_str[0]=='+')
      {
        q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
        if (q!=0)
        {
          hnd=bw_win_bua1.get_win_hnd(q);
	  SetWindowText(hnd,s1);
        }
      }
    }
    else
    {
      if (w_find_fldtype(s2,SMG_LEN,j)=='m')
      {
        w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

        bw_xbase_bua1.set_win_memno(j,s1,SMG_LEN);

        bw_xbase_bua1.set_win_scrnvar(wpp,"                     ",20);

	bw_xbase_bua1.setc_win_scrnvar(wpp,bw_win_bua1.get_1fldlen(i),0);

        fldtype='c';

	if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
        {
	  bw_main1.win_key=0;
	}

        if (p_str[0]=='+')
        {
          q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
          if (q!=0)
          { 
            hnd=bw_win_bua1.get_win_hnd(q);
	    SetWindowText(hnd,"");
          }
        }
      }
      else
      {
	w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

	bw_inkey1.strtrim(s1);

	bw_xbase_bua1.set_win_bmp_name(s1,SMG_LEN);

	bw_xbase_bua1.setc_win_scrnvar(wpp,0,0);

        fldtype='c';

	if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
        {
	  bw_main1.win_key=0;
	}

        if (p_str[0]=='+')
        {
          q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
          if (q!=0)
          { 
            hnd=bw_win_bua1.get_win_hnd(q);
	    SetWindowText(hnd,"");
          }
        }
      }
    }
  }

  if (p_str[0]==':')
  {
    bw_xbase_bua1.get_win_scrnvar(wpp,s3,SMG_LEN);

    j=bw_getread1.get_read(l-bw_win_bua1.get_win_con(wpp,1)+1,
			 c-bw_win_bua1.get_win_con(wpp,0)+1,
		       "",
		       s3,
		       bw_win_bua1.get_1fldlen(i),
		       fldtype,
		       comm,
		       w_find_fldlen(s2,SMG_LEN,j),
		       w_find_flddec(s2,SMG_LEN,j),
		       1,1,
		       bw_dialog_bua1.get_win_mv_getp(wpp),
		       bw_win_bua1.get_win_pp11(wpp));

  }

  return(j);
}
int bw_fldstru::w_tv_get_read(char *p_str,int len,int wpp,int l,int c,char comm)
{
  HWND hnd;
  int  i,j,q;
  char s1[SMG_LEN];
  char s2[SMG_LEN];
  char s3[SMG_LEN];
  char fldtype;
  char logic;

  //HDC  hdc;

  if ((p_str[0]!=':')&&(p_str[0]!='+')) return(1);

  p_str[len-1]=0;

  i=bw_buff1.get_linecol(wpp,l,c);
  j=bw_win_bua1.get_1fldbase(i);
//
//  bw_mbase1.w_down_rec(j,wpp,bw_xbase_bua1.get_win_recno(j,wpp,0)-1);
//
  bw_inkey1.strpcut(p_str,1,strlen(p_str)-1,len,s2,SMG_LEN);
  if (w_find_fldnum(s2,SMG_LEN,j)!=0) return(1);

  if ((w_find_fldtype(s2,SMG_LEN,j)=='n')||(w_find_fldtype(s2,SMG_LEN,j)=='c'))
  {
    w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

    bw_xbase_bua1.set_win_scrnvar(wpp,s1,SMG_LEN);

    fldtype=w_find_fldtype(s2,SMG_LEN,j);

    if (p_str[0]=='+')
    {
      q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
      if (q!=0)
      {
        hnd=bw_win_bua1.get_win_hnd(q);
	SetWindowText(hnd,s1);
	if (bw_main1.win_key!=401) SetFocus(hnd);
      }
    }
  }
  else
  {
    if (w_find_fldtype(s2,SMG_LEN,j)=='l')
    {
      w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

      bw_xbase_bua1.set_win_scrnvar(wpp,s1,SMG_LEN);

      logic=bw_inkey1.upper(bw_xbase_bua1.getc_win_scrnvar(wpp,0));

      if ((logic=='1')||(logic=='Y')||(logic=='T')) logic='T';
      else logic='F';

      bw_xbase_bua1.setc_win_scrnvar(wpp,0,logic);
      bw_xbase_bua1.setc_win_scrnvar(wpp,1,0);

      bw_xbase_bua1.get_win_scrnvar(wpp,s1,SMG_LEN);

      fldtype='c';

      if (p_str[0]=='+')
      {
        q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
        if (q!=0)
        {
          hnd=bw_win_bua1.get_win_hnd(q);
	  SetWindowText(hnd,s1);
	  if (bw_main1.win_key!=401) SetFocus(hnd);
        }
      }
    }
    else
    {
      if (w_find_fldtype(s2,SMG_LEN,j)=='m')
      {
        w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

        bw_xbase_bua1.set_win_memno(j,s1,SMG_LEN);

        bw_xbase_bua1.set_win_scrnvar(wpp,"                     ",20);

	bw_xbase_bua1.setc_win_scrnvar(wpp,bw_win_bua1.get_1fldlen(i),0);

        fldtype='c';

	if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
        {
	  bw_main1.win_key=0;
	}

        if (p_str[0]=='+')
        {
          q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
          if (q!=0)
          { 
            hnd=bw_win_bua1.get_win_hnd(q);
	    SetWindowText(hnd,"");
	    if (bw_main1.win_key!=401) SetFocus(hnd);
          }
        }
      }
      else
      {
	w_get_tab_var(s2,SMG_LEN,j,s1,SMG_LEN);

	bw_inkey1.strtrim(s1);

	bw_xbase_bua1.set_win_bmp_name(s1,SMG_LEN);

	bw_xbase_bua1.setc_win_scrnvar(wpp,0,0);

        fldtype='c';

	if (((bw_main1.win_key>=32)&&(bw_main1.win_key<128))||(bw_main1.win_key<0))
        {
	  bw_main1.win_key=0;
	}

        if (p_str[0]=='+')
        {
          q=bw_win1.w_find_hnd(wpp,bw_win1.pfield,bw_win1.pline);
          if (q!=0)
          { 
            hnd=bw_win_bua1.get_win_hnd(q);
	    SetWindowText(hnd,"");
	    if (bw_main1.win_key!=401) SetFocus(hnd);
          }
        }
      }
    }
  }

  if (p_str[0]==':')
  {
    bw_xbase_bua1.get_win_scrnvar(wpp,s3,SMG_LEN);

    j=bw_getread1.get_read(l-bw_win_bua1.get_win_con(wpp,1)+1,
			 c-bw_win_bua1.get_win_con(wpp,0)+1,
		       "",
		       s3,
		       bw_win_bua1.get_1fldlen(i),
		       fldtype,
		       comm,
		       w_find_fldlen(s2,SMG_LEN,j),
		       w_find_flddec(s2,SMG_LEN,j),
		       1,1,
		       bw_dialog_bua1.get_win_mv_getp(wpp),
		       bw_win_bua1.get_win_pp11(wpp));

    if ((GetFocus()==bw_win_bua1.get_win_phh(wpp))||(bw_win_bua1.get_ci_mhnd(GetFocus())==bw_win_bua1.get_win_phh(wpp)))
    {
      SetFocus(bw_win_bua1.get_win_phh(wpp));
    }

  }

  return(j);
}
int bw_fldstru::w_tv_get_read1(char *p_str,int len,int wpp,int l,int c,char comm)
{
  int  i,j;
//  char s1[SMG_LEN];
  char s2[SMG_LEN];
  char s3[SMG_LEN];
  char fldtype;
//  HDC  hdc;

  if (p_str[0]!=':') return(1);

  p_str[len-1]=0;

  i=bw_buff1.get_linecol(wpp,l,c);
  j=bw_win_bua1.get_1fldbase(i);
  bw_inkey1.strpcut(p_str,1,strlen(p_str)-1,len,s2,SMG_LEN);
  if (w_find_fldnum(s2,SMG_LEN,j)!=0) return(1);

  if ((w_find_fldtype(s2,SMG_LEN,j)=='n')||(w_find_fldtype(s2,SMG_LEN,j)=='c'))
  {
    fldtype=w_find_fldtype(s2,SMG_LEN,j);
  }
  else
  {
    if (w_find_fldtype(s2,SMG_LEN,j)=='l')
    {
      fldtype='c';
    }
    else
    {
      if (w_find_fldtype(s2,SMG_LEN,j)=='m')
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
    }
  }

  bw_xbase_bua1.get_win_scrnvar(wpp,s3,SMG_LEN);

  //bw_getread1.win_p1=0;

  j=bw_getread1.get_read(l-bw_win_bua1.get_win_con(wpp,1)+1,
			 c-bw_win_bua1.get_win_con(wpp,0)+1,
		       "",
		       s3,
		       bw_win_bua1.get_1fldlen(i),
	               fldtype,
		       comm,
		       w_find_fldlen(s2,SMG_LEN,j),
		       w_find_flddec(s2,SMG_LEN,j),
		       1,1,
		       bw_dialog_bua1.get_win_mv_getp(wpp),
		       bw_win_bua1.get_win_pp11(wpp));

  return(j);
}
int bw_fldstru::w_get_tab_var(char *p_fn,int len1,int p_fcnt,char *p_ca,int len2)
{
  int  i,j,k;
//  char str[SMG_LEN];
//  HDC  hdc;

  i=w_find_fldnum(p_fn,len1,p_fcnt);
  if (i!=0) return(1);
  j=w_find_fldlen(p_fn,len1,p_fcnt);
  k=w_find_fldposi(p_fn,len1,p_fcnt);

  for (i=1;i<=j;i++)
  {
    if (i-1<len2)
    {
      p_ca[i-1]=bw_xbase_bua1.get_win_recvar(i-1+k);
    }
  }

  if (i-1<len2) p_ca[i-1]=0;

  return(0);
}
int bw_fldstru::w_cmp_tab_var(char *p_fn,int len1,int p_fcnt,char *p_ca,int len2)
{
  int  exist;
  int  i,j,k,l;
//  char str[SMG_LEN];
//  HDC  hdc;

  i=w_find_fldnum(p_fn,len1,p_fcnt);
  if (i!=0) return(1);
  j=strlen(p_ca);
  l=w_find_fldlen(p_fn,len1,p_fcnt);
  k=w_find_fldposi(p_fn,len1,p_fcnt);
  if (j!=l) return(1);

  exist=0;
  for (i=1;i<=l;i++)
  {
    if (i-1<len2)
    {
      if (p_ca[i-1]!=bw_xbase_bua1.get_win_recvar(i-1+k))
      {
        exist=1;
	break;
      }
    }
  }

  return(exist);
}
int bw_fldstru::w_sav_tab_var(char *p_fn,int len1,int p_fcnt,char *p_ca,int len2)
{
  int  i,j,k,l;
  char c1;
  i=w_find_fldnum(p_fn,len1,p_fcnt);
  if (i!=0) return(1);
  j=w_find_fldlen(p_fn,len1,p_fcnt);
  k=w_find_fldposi(p_fn,len1,p_fcnt);
  l=strlen(p_ca);

  if (l>=len2) l=len2-1;
   
  for (i=0;i<=j-1;i++)
  {
    if (i>l) c1=' ';
    else
    {
      if ((p_ca[i]<' ')&&(p_ca[i]>=0)) c1=' ';
      else c1=p_ca[i];
    }
    bw_xbase_bua1.set_win_recvar(i+k,c1);
  }
  return(0);
}
int bw_fldstru::w_fetch_rec(int p_fcnt,int wpp,int seri)
{
  int  i,j;
//  char str[SMG_LEN];
  long recno;

  if (bw_xbase_bua1.get_win_cuseri(p_fcnt,wpp)==0)
  {
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,0);

    recno=0;

    if (bw_xbase_bua1.get_win_lnktab(p_fcnt)!=0)
    {
      while (1)
      {
        recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
	j=bw_link1.w_link_number(wpp,p_fcnt);
	if (bw_link1.w_link_cond_ok(j,wpp,p_fcnt,seri,wpp)==1) break;
	if (bw_xbase1.win_state3==1) break;
      }
    }
    else
    {
      recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
    }

    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,recno);
  }

  if (bw_xbase_bua1.get_win_rcnt(p_fcnt)<1)
  {
    bw_xbase1.w_clr_recvar(p_fcnt);

    return(1);
  }

  recno=bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0);

  if (bw_xbase_bua1.get_win_cuseri(p_fcnt,wpp)==seri)
  {
    recno--;

    if (bw_xbase_bua1.get_win_lnktab(p_fcnt)!=0)
    {
      if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) recno=0;

      while (1)
      {
        recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
	j=bw_link1.w_link_number(wpp,p_fcnt);
	if (bw_link1.w_link_cond_ok(j,wpp,p_fcnt,seri,wpp)==1) break;
	if (bw_xbase1.win_state3==1) break;
      }
    }
    else
    {
      recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
    }

    if (bw_xbase1.win_state3==1)
    {
      bw_xbase1.w_clr_recvar(p_fcnt);
      return(1);
    }
    else
    {
      bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,seri);
      bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,recno);
      return(0);
    }
  }

  if (bw_xbase_bua1.get_win_cuseri(p_fcnt,wpp)<seri)
  {
    if (bw_xbase_bua1.get_win_lnktab(p_fcnt)<=1)
    {
      for (i=bw_xbase_bua1.get_win_cuseri(p_fcnt,wpp)+1;i<=seri;i++)
      {
	if (bw_xbase_bua1.get_win_lnktab(p_fcnt)!=0)
	{
	  while (1)
	  {
	    recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
	    j=bw_link1.w_link_number(wpp,p_fcnt);
	    if (bw_link1.w_link_cond_ok(j,wpp,p_fcnt,seri,wpp)==1) break;
	    if (bw_xbase1.win_state3==1) break;
	  }
	}
	else
	{
	  recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
	}
	if (bw_xbase1.win_state3!=0) break;
      }

      if (bw_xbase1.win_state3!=0)
      {
	bw_xbase1.w_clr_recvar(p_fcnt);
	return(1);
      }
      else
      {
	bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,seri);
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,recno);
	return(0);
      }
    }
    else
    {
      recno=0;
      while (1)
      {
	recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
	j=bw_link1.w_link_number(wpp,p_fcnt);
	if (bw_link1.w_link_cond_ok(j,wpp,p_fcnt,seri,wpp)==1) break;
	if (bw_xbase1.win_state3==1) break;
      }

      if (bw_xbase1.win_state3!=0)
      {
	bw_xbase1.w_clr_recvar(p_fcnt);
	return(1);
      }
      else
      {
	bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,seri);
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,recno);
	return(0);
      }
    }
  }

  if (bw_xbase_bua1.get_win_cuseri(p_fcnt,wpp)>seri)
  {
    if (bw_xbase_bua1.get_win_lnktab(p_fcnt)<=1)
    {
      for (i=bw_xbase_bua1.get_win_cuseri(p_fcnt,wpp)-1;i>=seri;i--)
      {
	if (bw_xbase_bua1.get_win_lnktab(p_fcnt)!=0)
	{
	  while (1)
	  {
//	    sprintf(str,"%ld,%d,%d,",recno,i,seri);
//	    MessageBox(bw_main1.win_hwnd,str,"aa",MB_OK);
//
	    recno=bw_mbase1.w_up_rec(p_fcnt,wpp,recno);
	    j=bw_link1.w_link_number(wpp,p_fcnt);
	    if (bw_link1.w_link_cond_ok(j,wpp,p_fcnt,seri,wpp)==1) break;
	    if (bw_xbase1.win_state3==1) break;
	  }
	}
	else
	{
	  recno=bw_mbase1.w_up_rec(p_fcnt,wpp,recno);
	}
	if (bw_xbase1.win_state3!=0) break;
      }

      if (bw_xbase1.win_state3!=0)
      {
	bw_xbase1.w_clr_recvar(p_fcnt);
	return(1);
      }
      else
      {
	bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,seri);
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,recno);
	return(0);
      }
    }
    else
    {
      recno=0;
      while (1)
      {
	recno=bw_mbase1.w_down_rec(p_fcnt,wpp,recno);
	j=bw_link1.w_link_number(wpp,p_fcnt);
	if (bw_link1.w_link_cond_ok(j,wpp,p_fcnt,seri,wpp)==1) break;
	if (bw_xbase1.win_state3==1) break;
      }

      if (bw_xbase1.win_state3!=0)
      {
	bw_xbase1.w_clr_recvar(p_fcnt);
	return(1);
      }
      else
      {
	bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,seri);
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,recno);
	return(0);
      }
    }
  }

  return(1);
}
int bw_fldstru::w_page_up(int p_fcnt,int wpp)
{
  int  i,j,k,l;
  int  s_tmpn1/*,s_tmpn2*/;
//  int  s_tmpn3,s_tmpn4;
//  char str[SMG_LEN];

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) return(0);

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==0)
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_fcnt,wpp,LIN_NUM);
    for (i=1;i<=s_tmpn1;i++)
    {
      bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_mbase1.w_up_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)));

      if (bw_xbase1.win_state3==1) break;
    }
    w_echo_winrec(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
    return(0);
  }
  else
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_fcnt,wpp,LIN_NUM);
    for (i=1;i<=s_tmpn1;i++)
    {
      while (1)
      {
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_mbase1.w_up_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)));
	j=bw_buff1.get_linecol(wpp,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win_bua1.get_1fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(wpp,p_fcnt);
	if (bw_link1.w_link_cond_ok(l,wpp,p_fcnt,k,wpp)==1) break;
	if (bw_xbase1.win_state3==1) break;
      }
      if (bw_xbase1.win_state3==1)
      {
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)-1);
	while (1)
        {
	  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_mbase1.w_down_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)));
	  j=bw_buff1.get_linecol(wpp,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win_bua1.get_1fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(wpp,p_fcnt);
	  if (bw_link1.w_link_cond_ok(l,wpp,p_fcnt,k,wpp)==1) break;
	  if (bw_xbase1.win_state3==1) break;
	}
	if (bw_xbase1.win_state3==1) bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,1);
	break;
      }
    }
    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
    return(0);
  }
}
int bw_fldstru::w_page_down(int p_fcnt,int wpp)
{
  int  i,j,k,l;
  int  s_tmpn1/*,s_tmpn2*/;
//  int  s_tmpn3,s_tmpn4;
//  char str[SMG_LEN];

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) return(0);

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==0)
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_fcnt,wpp,LIN_NUM);
    for (i=1;i<=s_tmpn1;i++)
    {
      bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_mbase1.w_down_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)));

      if (bw_xbase1.win_state3==1) break;
    }
    w_echo_winrec(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
    return(0);
  }
  else
  {
    s_tmpn1=bw_win1.w_cnt_winline(p_fcnt,wpp,LIN_NUM);
    for (i=1;i<=s_tmpn1;i++)
    {
      while (1)
      {
	bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_mbase1.w_down_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)));
	j=bw_buff1.get_linecol(wpp,bw_win1.pline,bw_win1.pfield);
	if (j>0) k=bw_win_bua1.get_1fldseri(j);
	else k=1;
	l=bw_link1.w_link_number(wpp,p_fcnt);
	if (bw_link1.w_link_cond_ok(l,wpp,p_fcnt,k,wpp)==1) break;
	if (bw_xbase1.win_state3==1) break;
      }
      if (bw_xbase1.win_state3==1)
      {
	while (1)
	{
	  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_mbase1.w_up_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1)));
	  j=bw_buff1.get_linecol(wpp,bw_win1.pline,bw_win1.pfield);
	  if (j>0) k=bw_win_bua1.get_1fldseri(j);
	  else k=1;
	  l=bw_link1.w_link_number(wpp,p_fcnt);
	  if (bw_link1.w_link_cond_ok(l,wpp,p_fcnt,k,wpp)==1) break;
	  if (bw_xbase1.win_state3==1) break;
	}
	if (bw_xbase1.win_state3==1) bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,1);
	break;
      }
    }
    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
    return(0);
  }
}
int bw_fldstru::w_first_editposi(int p_fcnt,int wpp)
{
  int i,j,k,l;
  k=0;
  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      l=bw_buff1.get_linecol(wpp,i,j);
      if ((l!=0)&&(bw_win_bua1.get_1fldedt(l)==0)&&(bw_win_bua1.get_1fldbase(l)==p_fcnt))
      {
	bw_win1.pline=i;
        bw_win_bua1.set_win_linep(wpp,0,i);
	bw_win1.pfield=j;
	bw_win_bua1.set_win_linep(wpp,1,j);
	k=i;
	break;
      }
    }
    if (k!=0) break;
  }
  return(k);
}
int bw_fldstru::w_last_editposi(int p_fcnt,int wpp)
{
  int i,j,k,l;
  k=0;
  for (i=LIN_NUM-1;i>=1;i--) /* find first screen field */
  {
    for (j=COL_NUM-1;j>=1;j--)
    {
      l=bw_buff1.get_linecol(wpp,i,j);

      if ((l!=0)&&(bw_win_bua1.get_1fldedt(l)==0)&&(bw_win_bua1.get_1fldbase(l)==p_fcnt))
      {
	bw_win1.pline=i;
	bw_win_bua1.set_win_linep(wpp,0,i);
	bw_win1.pfield=j;
	bw_win_bua1.set_win_linep(wpp,1,j);
	k=i;
	break;
      }
    }
    if (k!=0) break;
  }
  return(k);
}

int bw_fldstru::w_insert_rec(int p_fcnt,int wpp)
{
  int s_state1;
  int i;

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) return(0);

  s_state1=bw_mbase1.w_ins_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0));

  if (s_state1!=0)
  {
    bw_win1.w_atten7();                   /* insert record error */
    return(0);
  }

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==1)
  {
    if ((bw_xbase_bua1.get_win_carry_on(p_fcnt)!=1)||(bw_xbase_bua1.get_win_enseri(p_fcnt,wpp)<=0))
    {
      bw_link1.w_keep_linkfld(wpp,p_fcnt,bw_xbase1.win_insert_dir);
    }

    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
  }
  else w_echo_winrec(wpp);

  bw_xbase_bua1.set_win_state5(p_fcnt,1);

  return(0);
}

int bw_fldstru::w_add_rec(int p_fcnt,int wpp)
{
  int s_state1;
  int i;

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) return(0);

  s_state1=bw_mbase1.w_add_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0));

  if (s_state1!=0)
  {
    bw_win1.w_atten7b();                   /* insert record error */
    return(0);
  }

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==1)
  {
    if ((bw_xbase_bua1.get_win_carry_on(p_fcnt)!=1)||(bw_xbase_bua1.get_win_enseri(p_fcnt,wpp)<=0))
    {
      bw_link1.w_keep_linkfld(wpp,p_fcnt,bw_xbase1.win_insert_dir);
    }

    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
  }
  else w_echo_winrec(wpp);

  bw_xbase_bua1.set_win_state5(p_fcnt,1);

  return(0);
}

int bw_fldstru::w_delete_rec(int p_fcnt,int wpp)
{
  int s_state1;
  int i;

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) return(0);

  s_state1=bw_mbase1.w_del_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0));

  if (s_state1!=0)
  {
    bw_win1.w_atten7a();                   /* insert record error */
    return(0);
  }

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==1)
  {
    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
  }
  else w_echo_winrec(wpp);

  bw_xbase_bua1.set_win_state5(p_fcnt,1);

  return(0);
}

int bw_fldstru::w_rollback_base(int p_fcnt,int wpp)
{
  int  i;
  int  p1;
  char s_fn1[FN_SIZE];
//  char s_fn2[FN_SIZE];
  char s_fn3[FN_SIZE];
  char st1[FN_SIZE];
  char sd1[EXT_LEN];

  if (bw_xbase_bua1.get_win_state5(p_fcnt)==0) return(0);

  bw_win_bub1.get_win_tabname(1,p_fcnt,s_fn3,FN_SIZE);

  bw_xbase1.w_rollback_xbase(s_fn3,FN_SIZE,bw_xbase_bua1.get_win_base_backup(p_fcnt),p_fcnt);

  bw_xbase_bua1.set_win_state5(p_fcnt,0);

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

  w_first_editposi(p_fcnt,wpp);
  bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,1);
  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,1);

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==1)
  {
    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
  }
  else w_echo_winrec(wpp);

  return(0);
}

int bw_fldstru::w_commit_base(int p_fcnt,int wpp)
{

  int  i;
  int  p1;
  char s_fn1[FN_SIZE];
//  char s_fn2[FN_SIZE];
  char st1[FN_SIZE];
  char sd1[EXT_LEN];

  if (bw_xbase_bua1.get_win_state5(p_fcnt)==0) return(0);

  bw_xbase1.w_commit_xbase(p_fcnt);

  bw_xbase_bua1.set_win_state5(p_fcnt,0);

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

  w_first_editposi(p_fcnt,wpp);
  bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,1);
  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,1);

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)==1)
  {
    i=bw_link1.w_link_base_num(wpp,p_fcnt);
    bw_link1.w_link_modi_mark(wpp,i,-1,-1);
    bw_link1.w_link_set_continue(wpp,p_fcnt);
    bw_link1.w_echo_winrec_lnk(wpp);
    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
  }
  else w_echo_winrec(wpp);


  return(0);
}

int bw_fldstru::w_link_window(int p_fcnt,int wpp)
{
  int i,j;

  if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==1) return(1);

  i=w_is_card(p_fcnt,wpp);

  j=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0);

  if (i==1) bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_xbase_bua1.get_win_recno(p_fcnt,j,0));
  else bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,bw_xbase_bua1.get_win_recno(p_fcnt,j,1));

  w_echo_winrec(wpp);
  w_first_editposi(p_fcnt,wpp);
  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,1));
  bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);

  return(0);
}

int bw_fldstru::w_is_card(int p_fcnt,int wpp)
{
  int i,j,k,l;

  k=0;
  for (i=1;i<LIN_NUM;i++) /* find first screen field */
  {
    for (j=1;j<COL_NUM;j++)
    {
      l=bw_buff1.get_linecol(wpp,i,j);
      if ((l!=0)&&(bw_win_bua1.get_1fldedt(l)==0)&&(bw_win_bua1.get_1fldbase(l)==p_fcnt))
      {
	if (k<bw_win_bua1.get_1fldseri(l)) k=bw_win_bua1.get_1fldseri(l);
      }
    }
  }

  if (k==1) return(1);
  else return(0);
}

int bw_fldstru::w_find_cond(int p_fcnt,int wpp)
{
//  int   i,j,k;
  char  sfn1[FN_SIZE];
  char  st1[FN_SIZE];

  if (bw_xbase_bua1.get_win_lnktab(p_fcnt)>1) return(1);

  w_clr_condition(p_fcnt);

  bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  bw_win_bub1.get_win_find_name(wpp,sfn1,FN_SIZE);
  bw_main1.get_view(sfn1,FN_SIZE,bw_main1.win_hwnd,bw_win_bua1.get_win_pp6(wpp,0));

  return(0);
}

int bw_fldstru::w_find_key(int p_fcnt,int wpp)
{
  int i,j;

  i=w_find_recno(p_fcnt,wpp);
  if (i!=0) return(1);

  for (j=0;j<=2;j++) bw_xbase_bua1.set_win_recno(p_fcnt,wpp,j,1);
  bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
  w_echo_winrec(wpp);
  w_first_editposi(p_fcnt,wpp);

  return(0);
}

int bw_fldstru::w_find_recno(int p_fcnt,int wpp)
{
  int           i;
  int           exist;
  long          lj;
  unsigned char c1,c2,c3,c4;
  char          s_fn1[FN_SIZE];
  char          s_fn2[FN_SIZE];
  char          str[SMG_LEN];
  char          st1[FN_SIZE];
  char          sd1[EXT_LEN];
  
  exist=0;
  for (i=0;i<STRU_NUM;i++)
  {
    if (bw_xbase_bua1.get_win_state9(wpp,i)==1)
    {
      exist=1;
      break;
    }
  }

  if (exist==1)
  {
    close(bw_xbase1.win_fp2[wpp]);
    bw_xbase_bua1.set_win_state9(wpp,i,0);

    bw_win_bub1.get_win_window_name(wpp,s_fn1,FN_SIZE);
    i=bw_inkey1.strlocc(s_fn1,'.');
    s_fn1[i]=0;
    bw_xbase_bua1.get_win_fext(wpp,sd1,EXT_LEN);
    strcat(s_fn1,sd1);

    bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

    bw_inkey1.w_set_dir(st1);

    bw_inkey1.w_del_file(s_fn1);
  }

  bw_win_bub1.get_win_window_name(wpp,s_fn2,FN_SIZE);
  i=bw_xbase1.w_find_empty_ffile(s_fn2,FN_SIZE,wpp);
  if (i!=0) return(1);

  bw_win_bub1.get_win_window_name(wpp,s_fn1,FN_SIZE);
  i=bw_inkey1.strlocc(s_fn1,'.');
  s_fn1[i]=0;
  bw_xbase_bua1.get_win_fext(wpp,sd1,EXT_LEN);
  strcat(s_fn1,sd1);

  bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  bw_xbase1.win_fp2[wpp]=sopen(s_fn1,O_RDWR|O_CREAT|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE);
  if (bw_xbase1.win_fp2[wpp]<0) return(1);

  bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,0);
  lj=0;
  while (1)
  {
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,bw_mbase1.w_down_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)));
    if (bw_xbase1.win_state3!=0) break;
    if (w_find_cond_ok(p_fcnt)!=1) continue;

    c1=(unsigned char)(bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)/256/256/256);
    c2=(unsigned char)((bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)-c1*256*256*256)/256/256);
    c3=(unsigned char)((bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)-c1*256*256*256-c2*256*256)/256);
    c4=(unsigned char)(bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)-c1*256*256*256-c2*256*256-c3*256);

    str[0]=c4;
    str[1]=c3;
    str[2]=c2;
    str[3]=c1;
    str[4]=0;

    lj++;
    lseek(bw_xbase1.win_fp2[wpp],(lj-1)*5,0);
    write(bw_xbase1.win_fp2[wpp],str,7);

  }
  
  bw_xbase_bua1.set_win_state9(wpp,p_fcnt,1);

  return(0);
}

int bw_fldstru::w_clr_condition(int p_fcnt)
{
  int   i/*,j,k,l,m,n,o*/;
//  int   exist;
  int   zero=0;
  char  str[SMG_LEN];
  char  stra[SMG_LEN];
  char  str2[SMG_LEN];


  for (i=w_find_fldpoin0(p_fcnt)
     ;i<=w_find_fldpoin1(p_fcnt)
     ;i++)
  {
    w_find_fldname(p_fcnt,i,stra,SMG_LEN);

    strcpy(str,"?");
    strcat(str,stra);

    if (bw_dialog1.w_mv_exist(str,SMG_LEN,zero)==1)
    {
      str2[0]=0;
      bw_dialog1.w_save_mem(str,SMG_LEN,zero,str2,SMG_LEN);
    }

    strcpy(str,"-");
    strcat(str,stra);

    if (bw_dialog1.w_mv_exist(str,SMG_LEN,zero)==1)
    {
      str2[0]=0;
      bw_dialog1.w_save_mem(str,SMG_LEN,zero,str2,SMG_LEN);
    }
  }

  return(0);
}

int bw_fldstru::w_find_end(int p_fcnt,int wpp)
{
  int  i;
//  int  p1,p2;
  char s_fn1[FN_SIZE];
//  char s_fn2[FN_SIZE];
  char st1[FN_SIZE];
  char sd1[EXT_LEN];

  if (bw_xbase_bua1.get_win_state9(wpp,p_fcnt)==1)
  {
    close(bw_xbase1.win_fp2[wpp]);

    bw_win_bub1.get_win_window_name(wpp,s_fn1,FN_SIZE);
    i=bw_inkey1.strlocc(s_fn1,'.');
    s_fn1[i]=0;
    bw_xbase_bua1.get_win_fext(wpp,sd1,EXT_LEN);
    strcat(s_fn1,sd1);

    bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

    bw_inkey1.w_set_dir(st1);

    bw_inkey1.w_del_file(s_fn1);

    bw_xbase_bua1.set_win_state9(wpp,p_fcnt,0);

    w_first_editposi(p_fcnt,wpp);
    bw_xbase_bua1.set_win_cuseri(p_fcnt,wpp,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,0,1);
    bw_xbase_bua1.set_win_recno(p_fcnt,wpp,1,1);

    w_echo_winrec(wpp);

    return(0);
  }
  else return(1);

}

int bw_fldstru::w_find_exit(int wpp)
{
  int  i/*,j,k*/;
  int  p1,p2;
  char s_fn1[FN_SIZE];
//  char s_fn2[FN_SIZE];
  char st1[FN_SIZE];
  char sd1[EXT_LEN];

  for (p1=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),0)
      ;p1<=bw_win_bua1.get_win_pp6(bw_win_bua1.get_win_pp5(wpp),2)
      ;p1++)
  {

    for (p2=0;p2<STRU_NUM;p2++)
    {
      if (bw_xbase_bua1.get_win_state9(p1,p2)==1)
      {
        close(bw_xbase1.win_fp2[p1]);
        bw_xbase_bua1.set_win_state9(p1,p2,0);

	bw_win_bub1.get_win_window_name(p1,s_fn1,FN_SIZE);
        i=bw_inkey1.strlocc(s_fn1,'.');
	s_fn1[i]=0;
	bw_xbase_bua1.get_win_fext(p1,sd1,EXT_LEN);
	strcat(s_fn1,sd1);

	bw_xbase_bua1.get_win_basedir(p2,st1,FN_SIZE);

	bw_inkey1.w_set_dir(st1);

	bw_inkey1.w_del_file(s_fn1);
      }
    }
  }

  return(0);
}

int bw_fldstru::w_find_cond_ok(int p_fcnt)
{
  float f1,f2;
  int   i,j=1,k,l,m,n,o;
  int   exist;
  int   zero=0;
  char  stra[SMG_LEN]; // scrn field name
  char  strb[SMG_LEN]; // tab field name
  char  str1[SMG_LEN]; // scrn field val
  char  str2[SMG_LEN]; // tab field val
  char  str3[SMG_LEN];
  char  str4[SMG_LEN];
  char  str5[SMG_LEN];


  for (i=w_find_fldpoin0(p_fcnt)
     ;i<=w_find_fldpoin1(p_fcnt)
     ;i++)
  {
    w_find_fldname(p_fcnt,i,strb,SMG_LEN);

    //MessageBox(0,"aa strb",strb,MB_OK);

    strcpy(stra,"?");
    strcat(stra,strb);

    strcpy(str4,"-");
    strcat(str4,strb);

    if ((bw_dialog1.w_mv_exist(stra,SMG_LEN,zero)==1)||(bw_dialog1.w_mv_exist(str4,SMG_LEN,zero)==1))
    {
      if (bw_dialog1.w_mv_exist(str4,SMG_LEN,zero)==1) strcpy(stra,str4);

      bw_dialog1.w_mv_fet_val(stra,SMG_LEN,zero,str1,SMG_LEN);

      //MessageBox(0,"bb str1",str1,MB_OK);

      bw_inkey1.strtrim(str1);
      bw_inkey1.strltrim(str1);

      w_get_tab_var(strb,SMG_LEN,p_fcnt,str2,SMG_LEN);

      //MessageBox(0,"cc str2",str2,MB_OK);

      if (w_find_fldtype(strb,SMG_LEN,p_fcnt)=='c')
      {
	k=bw_inkey1.strlocc(str1,';');

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
	    k=bw_inkey1.strlocc(str1,';');
	    if (str1[k]!=';') break;
            else
	    {
	      str1[k]=' ';
	      bw_inkey1.strpcut(str1,l,k-l,SMG_LEN,str3,SMG_LEN);
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
      
      if (w_find_fldtype(strb,SMG_LEN,p_fcnt)=='n')
      {
        bw_inkey1.char2float(str2,&f1);

      	k=0;
        bw_inkey1.strtrim(str1);
	while (1)
	{

		//sprintf(str5,"k=%d,str1=%s,",k,str1);
		//MessageBox(0,"cc2",str5,MB_OK);

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

        //MessageBox(0,"dd exist=1","dd",MB_OK);

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
	      bw_inkey1.strpcut(str1,l+1+o,n-l-1-o,SMG_LEN,str3,SMG_LEN);

	      bw_inkey1.char2float(str3,&f2);

		  //sprintf(str5,"m=%d,str3=%s,f1=%f,f2=%f,",m,str3,f1,f2);
		  //MessageBox(0,"ee",str5,MB_OK);

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

      if (w_find_fldtype(strb,SMG_LEN,p_fcnt)=='l')
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

//      if (w_find_fldtype(strb,p_fcnt)=='m')
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

int bw_fldstru::w_edit_memo(int p_fcnt,int wpp,char *p_fldname,int len)
{                           
  char fn1[FN_SIZE];
  char str[SMG_LEN];
  char str1[SMG_LEN];
  char str2[FN_SIZE];
  char str3[FN_SIZE];
  char str4[SMG_LEN];
  char str5[SMG_LEN];
  char str6[SMG_LEN];
//  char str7[SMG_LEN];
  char str8[SMG_LEN];
  char str9[SMG_LEN];
//  char stra[SMG_LEN];
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
  if (bw_xbase_bua1.get_win_mem_inuse(p_fcnt)==1) return(0);

  //make empty string
  for (i=0;i<=10;i++) sstr[i]=' ';
  sstr[10]=0;

  //save field name
  p_fldname[len-1]=0;
  strcpy(str6,p_fldname);

  // make return string
  ret[0]=13;
  ret[1]=10;
  ret[2]=0;

  // make file name
  bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

  strcpy(fn1,st2);
  bw_inkey1.strtrim(fn1);
  i=bw_inkey1.strlocc(fn1,'.');
  fn1[i]=0;
  strcat(fn1,".mem");

  //file exist
  bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);
  if (bw_inkey1.w_find_file(fn1)==0)
  {
    fh=fopen(fn1,"w");
    if (fh==NULL) return(1);

    bw_xbase_bua1.get_win_memno(p_fcnt,str9,SMG_LEN);

    if (bw_inkey1.strempty(str9)==0)
    {
      mnu=0;
      mno=0;
      mark=1;
      bw_inkey1.long2char(mno,str9);
    }
    else
    {
      bw_inkey1.char2long(str9,&mno);
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

    bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

    strcpy(str2,st2);
    bw_inkey1.strtrim(str2);
    i=bw_inkey1.strlocc(str2,'.');
    str2[i]=0;

    bw_xbase1.w_find_empty_mfile(str2,FN_SIZE,p_fcnt);

    strcpy(str3,str2);
    bw_xbase_bua1.get_win_mem_ext(p_fcnt,str8,SMG_LEN);
    strcat(str3,str8);
    bw_inkey1.strtrim(str3);

    fh1=fopen(str3,"w");
    if (fh1==NULL) return(1);
    fclose(fh1);

  }
  else
  {
    bw_xbase_bua1.get_win_memno(p_fcnt,str9,SMG_LEN);

    fh=fopen(fn1,"r+");
    if (fh==NULL) return(1);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_LEN,fh);

      if (strncmp(str4,"&&memorynum:",12)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      bw_inkey1.strpcut(str4,12,8,SMG_LEN,str,SMG_LEN);
      bw_inkey1.strtrim(str);
      bw_inkey1.char2long(str,&mnu);
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
	bw_inkey1.char2long(str9,&mnu);
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
      bw_inkey1.long2char(mno,str9);
    }
    else
    {
      bw_inkey1.char2long(str9,&mno);
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

    bw_inkey1.strtrim(str5);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_LEN,fh);

      bw_inkey1.strtrim(str4);

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
      bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

      strcpy(str2,st2);
      bw_inkey1.strtrim(str2);
      i=bw_inkey1.strlocc(str2,'.');
      str2[i]=0;

      bw_xbase1.w_find_empty_mfile(str2,FN_SIZE,p_fcnt);

      strcpy(str3,str2);
      bw_xbase_bua1.get_win_mem_ext(p_fcnt,str8,FN_SIZE);
      strcat(str3,str8);
      bw_inkey1.strtrim(str3);

      fh1=fopen(str3,"w");
      if (fh1==NULL)
      {
	fclose(fh);
	return(1);
      }

      while (!feof(fh))
      {
	fgets(str4,SMG_LEN,fh);
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

      bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

      strcpy(str2,st2);
      bw_inkey1.strtrim(str2);
      i=bw_inkey1.strlocc(str2,'.');
      str2[i]=0;

      bw_xbase1.w_find_empty_mfile(str2,FN_SIZE,p_fcnt);

      strcpy(str3,str2);
      bw_xbase_bua1.get_win_mem_ext(p_fcnt,str8,FN_SIZE);
      strcat(str3,str8);
      bw_inkey1.strtrim(str3);

      fh1=fopen(str3,"w");
      if (fh1==NULL) return(1);
      fclose(fh1);

    }
  }

  if (mark==1)
  {
    bw_mbase1.w_down_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)-1);

    w_sav_tab_var(str6,SMG_LEN,p_fcnt,str9,SMG_LEN);
    bw_mbase1.w_save_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0));
    bw_xbase_bua1.set_win_state5(p_fcnt,1);

    fseek(fh,0,0);

    mnop=0;
    exist=0;
    while (!feof(fh))
    {
      mnop=fseek(fh,0,SEEK_CUR);
      fgets(str4,SMG_LEN,fh);
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

      bw_inkey1.long2char(mnu,str);

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

  bw_xbase_bua1.set_win_mem_inuse(p_fcnt,1);
  bw_xbase_bua1.set_win_mem_wpp(p_fcnt,wpp);
  bw_xbase_bua1.set_win_mem_fn(p_fcnt,str3,FN_SIZE);
  bw_win_bua1.set_win_memo_basep(wpp,p_fcnt);

  bw_edit1.get_edit(str3,wpp,bw_main1.win_hwnd);

  return(0);
}

int bw_fldstru::w_edit_memo_close(int wpp)
{
  int  i,j,k,l,m;
  int  p_fcnt;
  int  exist;
  char ret[10];
  char str0[10];
  char fn1[FN_SIZE];
  char str1[FN_SIZE];
  char str2[FN_SIZE];
  char str4[FN_SIZE];
  char str5[SMG_LEN];
  char str6[FN_SIZE];
  char str7[10];
  char str8[FN_SIZE];
  char st1[FN_SIZE];
  char st2[FN_SIZE];
//  long memp;
  FILE *fh1;
  FILE *fh2;
  FILE *fh3;

  p_fcnt=bw_win_bua1.get_win_memo_basep(wpp);
  bw_xbase_bua1.set_win_mem_inuse(p_fcnt,0);

  // save mem ext name
  bw_xbase_bua1.get_win_mem_ext(p_fcnt,str0,10);
                                
  // make edited file name
  bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

  strcpy(str6,st2);
  bw_inkey1.strtrim(str6);
  i=bw_inkey1.strlocc(str6,'.');
  str6[i]=0;
  strcat(str6,str0);

  // make return string
  ret[0]=13;
  ret[1]=10;
  ret[2]=0;

  // make file name
  bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

  strcpy(fn1,st2);
  bw_inkey1.strtrim(fn1);
  i=bw_inkey1.strlocc(fn1,'.');
  fn1[i]=0;
  strcat(fn1,".mem");

//  MessageBox(bw_main1.win_hwnd1,fn1,"aa",MB_OK);

  //file exist
  bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);
  if (bw_inkey1.w_find_file(fn1)==0) return(1);
  else
  {
    bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

    strcpy(str1,st2);
    bw_inkey1.strtrim(str1);
    i=bw_inkey1.strlocc(str1,'.');
    str1[i]=0;

    bw_xbase1.w_find_empty_mfile(str1,FN_SIZE,p_fcnt);

    bw_xbase_bua1.get_win_mem_ext(p_fcnt,str7,10);
    strcpy(str2,str1);
    strcat(str2,str7);

//    MessageBox(bw_main1.win_hwnd1,str2,fn1,MB_OK);

    j=bw_inkey1.w_cpy_file(fn1,str2);
    if (j!=0) return(0);

    fh1=fopen(fn1,"r+");
    if (fh1==NULL) return(1);

//    MessageBox(bw_main1.win_hwnd1,"copy & open ok","bb",MB_OK);

    strcpy(str4,"&&memoryno.:");
    bw_xbase_bua1.get_win_memno(p_fcnt,str8,FN_SIZE);
    strcat(str4,str8);
    bw_inkey1.strtrim(str4);

    exist=0;
    while (!feof(fh1))
    {
      fgets(str5,SMG_LEN,fh1);
      bw_inkey1.strtrim(str5);

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
      fgets(str5,SMG_LEN,fh2);
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
    bw_xbase_bua1.get_win_memno(p_fcnt,str8,FN_SIZE);
    strcat(str4,str8);
    bw_inkey1.strtrim(str4);

    exist=0;
    while (!feof(fh3))
    {
      fgets(str5,SMG_LEN,fh3);
      bw_inkey1.strtrim(str5);

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
      fgets(str5,SMG_LEN,fh3);

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
      fgets(str5,SMG_LEN,fh3);
      fputs(str5,fh1);
    }

    fclose(fh1);
    fclose(fh3);
    bw_inkey1.w_del_file(str2);
  }

  return(0);
}

int bw_fldstru::w_edit_memo_add(int p_fcnt,int wpp,char *p_fldname,int len)
{
  int  i,j,k,l,m,n;
  char s_tc0[SMG_LEN];
  char s_tc1[SMG_LEN];
  char s_tc2[SMG_LEN];
  char s_tc3[SMG_LEN];
  char s_tc4[SMG_LEN];
  char s_tc5[SMG_LEN];
  char s_tc6[SMG_LEN];
  char s_tc7[SMG_LEN];
  char s_tc8[SMG_LEN];
  char fn1[FN_SIZE];
  char str[SMG_LEN];
  char str1[SMG_LEN];
//  char str2[FN_SIZE];
//  char str3[FN_SIZE];
  char str4[SMG_LEN];
  char str5[50];
  char str6[SMG_LEN];
  char str7[10];
  char str8[SMG_LEN];
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
  bw_main1.w_fetch_filename(s_tc7,SMG_LEN);
  strcpy(bw_main1.win_cpy_f1,bw_main1.win_seadir);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1);
  k=strlen(bw_main1.win_cpy_f1);
  bw_main1.win_cpy_f1[k]=92;
  bw_main1.win_cpy_f1[k+1]=0;
  strcat(bw_main1.win_cpy_f1,bw_main1.win_seaname);
  bw_inkey1.strtrim(bw_main1.win_cpy_f1);

  bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

  strcpy(s_tc7,st2);
  bw_inkey1.strtrim(s_tc7);
  i=bw_inkey1.strlocc(s_tc7,'.');
  s_tc7[i]=0;

  bw_xbase1.w_find_empty_mfile(s_tc7,SMG_LEN,p_fcnt);

  strcpy(s_tc8,s_tc7);
  bw_xbase_bua1.get_win_mem_ext(p_fcnt,str7,10);
  strcat(s_tc8,str7);

  bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);

  w_wps_to_txt(bw_main1.win_cpy_f1,FN_SIZE,s_tc8,SMG_LEN);

  //if already in use return
  if (bw_xbase_bua1.get_win_mem_inuse(p_fcnt)==1) return(0);

  //make empty string
  for (i=0;i<=10;i++) sstr[i]=' ';
  sstr[10]=0;

  //save field name
  p_fldname[len-1]=0;
  strcpy(str6,p_fldname);

  // make return string
  ret[0]=13;
  ret[1]=10;
  ret[2]=0;

  // make file name
  bw_xbase_bua1.get_win_basename(p_fcnt,st2,FN_SIZE);

  strcpy(fn1,st2);
  bw_inkey1.strtrim(fn1);
  i=bw_inkey1.strlocc(fn1,'.');
  fn1[i]=0;
  strcat(fn1,".mem");

  bw_xbase_bua1.get_win_memno(p_fcnt,str8,SMG_LEN);

  //file exist
  bw_xbase_bua1.get_win_basedir(p_fcnt,st1,FN_SIZE);

  bw_inkey1.w_set_dir(st1);
  if (bw_inkey1.w_find_file(fn1)==1)
  {
    fh=fopen(fn1,"r+");
    if (fh==NULL) return(1);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_LEN,fh);

      if (strncmp(str4,"&&memorynum:",12)==0)
      {
	exist=1;
	break;
      }
    }

    if (exist==1)
    {
      bw_inkey1.strpcut(str4,12,8,SMG_LEN,str,SMG_LEN);
      bw_inkey1.strtrim(str);
      bw_inkey1.char2long(str,&mnu);
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
      bw_inkey1.long2char(mno,str8);
    }
    else
    {
      bw_inkey1.char2long(str8,&mno);
      mark=0;
    }

    strcpy(str5,"&&memoryno.:");
    strcat(str5,str8);
    strcat(str5,sstr);
    str5[22]=0;
    strcat(str5,ret);

    bw_inkey1.strtrim(str5);

    exist=0;
    while (!feof(fh))
    {
      fgets(str4,SMG_LEN,fh);

      bw_inkey1.strtrim(str4);

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

      bw_xbase_bua1.set_win_memno(p_fcnt,str8,strlen(str8)+1);
    }
    else  bw_xbase_bua1.set_win_memno(p_fcnt,str8,strlen(str8)+1);
  }
  else return(1);

  if (mark==1)
  {
    bw_mbase1.w_down_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0)-1);

    w_sav_tab_var(str6,SMG_LEN,p_fcnt,str8,SMG_LEN);
    bw_mbase1.w_save_rec(p_fcnt,wpp,bw_xbase_bua1.get_win_recno(p_fcnt,wpp,0));
    bw_xbase_bua1.set_win_state5(p_fcnt,1);

    fseek(fh,0,0);

    mnop=0;
    exist=0;
    while (!feof(fh))
    {
      mnop=fseek(fh,0,SEEK_CUR);
      fgets(str4,SMG_LEN,fh);
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

      bw_inkey1.long2char(mnu,str);

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

  bw_xbase_bua1.set_win_mem_inuse(p_fcnt,1);
  bw_xbase_bua1.set_win_mem_fn(p_fcnt,s_tc8,SMG_LEN);
  bw_win_bua1.set_win_memo_basep(wpp,p_fcnt);

  w_edit_memo_close(wpp);

  return(0);
}

int bw_fldstru::w_wps_to_txt(char *p_s1,int len1,char *p_s2,int len2)
{
  FILE     *s_fp1;
  FILE     *s_fp2;
  unsigned char c1;
  unsigned char str[SMG_LEN];
  //char          i_stc1[SMG_LEN];
  //char          i_stc2[SMG_LEN];
  int           i,j;
/*
  if (len1<SMG_LEN) i=len1;
  else i=SMG_LEN;
  for (j=0;j<i-1;j++) i_stc1[j]=p_s1[j];
  if (i>0) i_stc1[i-1]=0;
  else i_stc1[0]=0;
*/
/*
  if (len2<SMG_LEN) i=len2;
  else i=SMG_LEN;
  for (j=0;j<i-1;j++) i_stc2[j]=p_s2[j];
  if (i>0) i_stc2[i-1]=0;
  else i_stc2[0]=0;
*/
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

