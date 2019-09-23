
#define STRICT
#include <windows.h>
#include <commdlg.h>
 
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <conio.h>
#include <process.h>
#include <string.h>

#include "vc_bowo.h"

extern class bw_font     bw_font1;

int bw_font::w_read_fdc(char *p_fn1,int p_fn1_len,int p_win)
{
/*  int  i,j,k,l,m,n;
  int  p1,p2,p3,p4,p5,p6,p7,p8,same,spg,ends;
  int  state2,state3;
  int  state4,state5,state6;
  int  pp1,pp2;
  char sfn1[FN_SIZE];
  char tmpc2[310];
  int  exist;
  FILE *fp1;

  strcpy(sfn1,p_fn1);
  bw_inkey1.strtrim(sfn1,FN_SIZE);
  i=bw_inkey1.strlocc(sfn1,FN_SIZE,'.');
  sfn1[i]=0;
  strcat(sfn1,".tb4");

  exist=0;
  for (i=0;i<FONT_NUM;i++)
  {
    if (t5_m_wind[i]==0)
    {
      exist=1;
      break;
    }
  }
  if (exist==0) return(1);

  pp1=i;

  fp1=fopen(sfn1,"r");       
  if (fp1==NULL)
  {
    bw_win1.w_atten1(sfn1);
    return(1);
  }

  while (!feof(fp1))
  {
    for (i=0;i<=300;i++) tmpc2[i]=0;
    fgets(tmpc2,300,fp1);

    if (strncmp(tmpc2,"&screenseg",7)==0)
    {
      p_win++;
      continue;
    }

    for (i=0;i<=300;i++) if ((tmpc2[i]<' ')&&(tmpc2[i]>0)) tmpc2[i]=' ';
						  
    for (i=0;i<=300-1;i++) if ((tmpc2[i]>' ')||(tmpc2[i]<0)) break;
    if (i>=299) break;
    p1=i;
    for (i=i;i<=300-1;i++) if (tmpc2[i]==' ') break; 
    if (i>=300)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p2=i-1;
  
    for (i=i;i<=300-1;i++) if (tmpc2[i]!=' ') break;
    if (i>=300)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p3=i;
    for (i=i;i<=300-1;i++) if (tmpc2[i]==' ') break; 
    if (i>=300)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p4=i-1;
    
    for (i=i;i<=300-1;i++) if (tmpc2[i]!=' ') break;
    if (i>=300)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p5=i;
    for (i=i;i<=300-1;i++) if (tmpc2[i]==' ') break; 
    if (i>=300)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }
    p6=i-1;

    for (i=i;i<=300-1;i++) if (tmpc2[i]!=' ') break;
    p7=i;

    for (i=i;i<=300-1;i++) if (tmpc2[i]==' ') break; 
    p8=i-1;

    for (j=p1;j<=p2;j++)
    {
      if (tmpc2[j]==' ') break;
      t5_m_name[pp1][j-p1]=tmpc2[j];
      t5_m_name[pp1][j-p1+1]=0;
    }

    for (j=p3;j<=p4;j++)
    {
      if (tmpc2[j]==' ') break;
      t5_m_butt[pp1][j-p3]=tmpc2[j];
      t5_m_butt[pp1][j-p3+1]=0;
    }
    same=0;
    if (strncmp("button=",t5_m_butt[pp1],7)==0) same=1;
    if (strncmp("bitmap=",t5_m_butt[pp1],7)==0) same=1;
    if (same==0)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }

    for (j=p5;j<=p6;j++)
    {
      if (tmpc2[j]==' ') break;
      t5_m_comm[pp1][j-p5]=tmpc2[j];
      t5_m_comm[pp1][j-p5+1]=0;
    }
    same=0;
    if (strncmp("com=",t5_m_comm[pp1],4)==0) same=1;
    if (strncmp("do=",t5_m_comm[pp1],3)==0) same=1;
    if (same==0)
    {
      fclose(fp1);
      bw_win1.w_atten36(sfn1);
      return(1);
    }

    for (j=p7;j<=p8;j++)
    {
      if (tmpc2[j]==' ') break;
      t5_m_focus[pp1][j-p7]=tmpc2[j];
      t5_m_focus[pp1][j-p7+1]=0;
    }

    t5_m_wind[pp1]=p_win;

    pp1++;
  }

  t5_m_pp1=pp1-1;

  fclose(fp1);

  for (i=0;i<=t5_m_pp1;i++)
  {
    loc(i+1,1);
    printf("%s,%s,%s,"
	   ,t5_m_name[i]
	   ,t5_m_butt[i]
	   ,t5_m_comm[i]);
  }
  inkey();
*/
  return(0);
}

