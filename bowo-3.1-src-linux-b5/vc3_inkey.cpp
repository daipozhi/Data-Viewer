#define _CRT_SECURE_NO_WARNINGS

// (char *s1,no len)
 
//#define STRICT
#include "windows.h"
/*
#include <commdlg.h>
*/
#include <stdio.h>

#include <math.h>
/*
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

extern class bw_main  /*far*/ bw_main1;
extern class bw_inkey /*far*/ bw_inkey1;

int bw_inkey::keystart()
{
  return(1);
}
int bw_inkey::refresh()
{
  return(1);
}
int bw_inkey::keyend()
{
  return(1);
}
int bw_inkey::w_set_dir(char *p_s1)
{
  int  i;

  i=chdir(p_s1);
  if (i!=0) return(1);
 
  return(0);
}
int bw_inkey::w_get_dir(char *p_s1,int l)
{
  getcwd(p_s1,l);
  return(0);
}
int bw_inkey::inkey()
{
  char c1;
  switch (bw_main1.win_msg)
  {
    case WM_KEYDOWN:
    {
      if ((bw_main1.win_key2!=0)||((bw_main1.win_key1==(int)bw_main1.win_wp)&&(bw_main1.win_key1!=0)))
      {
	if (bw_main1.win_key2!=0)
        {
	  bw_main1.win_key=bw_main1.win_key2;
	  if ((bw_main1.win_key==8)&&(bw_main1.win_wp==8))  bw_main1.win_key=127;
	  if (bw_main1.win_key==13) bw_main1.win_key=10;
        }
        else
        {
	  switch (bw_main1.win_key1)
	  {
	    case 1:
	    {
	      bw_main1.win_key=401;
              break;
	    }
	    case 2:
	    {
	      bw_main1.win_key=402;
              break;
	    }
	    case 3:
	    {
	      bw_main1.win_key=404;
              break;
	    }
	    case 4:
            {
	      bw_main1.win_key=403;
              break;
  	    }
	    case 8:
	    {
	      bw_main1.win_key=127;
              break;
	    }
	    case 13:
	    {
	      bw_main1.win_key=10;
	      break;
	    }
	    case 33:
	    {
	      bw_main1.win_key=315;
              break;
	    }
	    case 34:
	    {
	      bw_main1.win_key=316;
              break;
	    }
	    case 35:
	    {
	      bw_main1.win_key=318;
              break;
	    }
	    case 36:
	    {
	      bw_main1.win_key=317;
              break;
	    }
	    case 37:
	    {
	      bw_main1.win_key=276;
              break;
	    }
	    case 38:
	    {
	      bw_main1.win_key=274;
              break;
	    }
	    case 39:
	    {
	      bw_main1.win_key=277;
              break;
	    }
	    case 40:
	    {
	      bw_main1.win_key=275;
              break;
	    }
	    case 45:
	    {
	      bw_main1.win_key=312;
              break;
	    }
	    case 46:
	    {
	      bw_main1.win_key=313;
              break;
	    }
	    case 120:
	    {
	      bw_main1.win_key=310;
              break;
	    }
	    default:
	    {
	      bw_main1.win_key=410+bw_main1.win_key1;
            }
          }
        }
	bw_main1.win_key1=0;
	bw_main1.win_key2=0;
        return(1);
      }
      else
      {
	bw_main1.win_key1=bw_main1.win_wp;
	bw_main1.win_key2=0;
        return(0);
      }
    }
    case WM_CHAR:
    {
      bw_main1.win_key2=bw_main1.win_wp;
      if ((bw_main1.win_key2>=0)&&(bw_main1.win_key2<128)) return(0);
      else
      {
	c1=bw_main1.win_key2;
	bw_main1.win_key=c1;
	bw_main1.win_key1=0;
	bw_main1.win_key2=0;
        return(1);
      }
    }
    case WM_KEYUP:
    {
      if (bw_main1.win_key2!=0)
      {
	bw_main1.win_key=bw_main1.win_key2;
	if ((bw_main1.win_key==8)&&(bw_main1.win_key1==8)) bw_main1.win_key=127;
	if (bw_main1.win_key==13) bw_main1.win_key=10;
      }
      else
      {
	switch (bw_main1.win_key1)
	{
	  case 1:
	  {
	    bw_main1.win_key=401;
            break;
	  }
	  case 2:
	  {
	    bw_main1.win_key=402;
            break;
	  }
	  case 3:
	  {
	    bw_main1.win_key=404;
            break;
	  }
	  case 4:
	  {
	    bw_main1.win_key=403;
            break;
	  }
	  case 8:
	  {
	    bw_main1.win_key=127;
            break;
	  }
	  case 13:
	  {
	    bw_main1.win_key=10;
	    break;
	  }
	  case 33:
	  {
	    bw_main1.win_key=315;
            break;
	  }
	  case 34:
	  {
	    bw_main1.win_key=316;
            break;
	  }
	  case 35:
	  {
	    bw_main1.win_key=318;
            break;
	  }
	  case 36:
	  {
	    bw_main1.win_key=317;
            break;
	  }
	  case 37:
	  {
	    bw_main1.win_key=276;
            break;
	  }
	  case 38:
	  {
	    bw_main1.win_key=274;
            break;
	  }
	  case 39:
	  {
	    bw_main1.win_key=277;
            break;
	  }
	  case 40:
	  {
	    bw_main1.win_key=275;
            break;
	  }
	  case 45:
	  {
	    bw_main1.win_key=312;
            break;
	  }
	  case 46:
	  {
	    bw_main1.win_key=313;
            break;
	  }
	  case 120:
	  {
	    bw_main1.win_key=310;
            break;
	  }
	  default:
	  {
	    bw_main1.win_key=410+bw_main1.win_key1;
          }
        }
      }
      bw_main1.win_key1=0;
      bw_main1.win_key2=0;
      return(1);
    }
    default:
    {
      bw_main1.win_key1=0;
      bw_main1.win_key2=0;
      return(0);
    }
  }
}
int bw_inkey::strlocc(char *p_str,char c1)
{
  int i,j;
  strtrim(p_str);
  j=strlen(p_str);
  for (i=0;i<=j-1;i++) if (p_str[i]==c1) break;
  if (i<j) return(i);
  else return(j);
}
int bw_inkey::strpcat(char *s1,int p,char *s2)
{
  int i;
  for (i=0;i<=(int)strlen(s2);i++) s1[p++]=s2[i];
  return(1);
}
int bw_inkey::strtrim(char *p_str)
{
  int i;
  for (i=strlen(p_str)-1;i>=0;i--)
  {
    if ((p_str[i]>' ')||(p_str[i]<0)) break;
    else p_str[i]=0;
  }
  return(0);
}

int bw_inkey::strltrim(char *p_str)
{
  int  i,j,k;
  char s1[SMG_LEN];

  i=strlen(p_str);
  
  for (j=0;j<i;j++)
  {
    if (p_str[j]!=' ') break;
    else p_str[j]=0;
  }

  s1[0]=0;
  k=0;

  for (j=0;j<i;j++)
  {
    if (p_str[j]==0) continue;
    else
    {
      s1[k+0]=p_str[j];
      s1[k+1]=0;
      k++;
    }
  }

  strcpy(p_str,s1);

  return(0);
}

/*
int bw_inkey::strpcut(char *s1,int p1,int p2,char *s2)
{
  int i;
  s2[0]=0;
  for (i=p1;i<=p1+p2-1;i++) s2[i-p1]=s1[i];
  s2[i-p1]=0;
  return(1);
}
*/

int bw_inkey::strpcut(char *p_s1,int p1,int p2,int len1,char *p_s2,int len2)
{
  int  i,j;
  char c1;
  i=0;
  p_s2[0]=0;
  for (j=p1;j<p1+p2;j++)
  {
    if ((j<0)||(j>=len1)) continue;
    c1=p_s1[j];
    if (i+1>=len2) continue;
    p_s2[i+0]=c1;
    p_s2[i+1]=0;
    i++;
  }
  return(1);
}

int bw_inkey::char2long(char *p_str,long *l)
{
  long li;
  int i,j,k;
  char c1;
  i=strlen(p_str);
  li=0;
  for (j=0;j<=i-1;j++)
  {
    c1=p_str[j];
    if ((c1>='0')&&(c1<='9'))
    {
      k=c1-'0';
      li=li*10+k;
    }
    if (c1=='-') li=0-li;
  }
  *l=li;
  return(1);
}
int bw_inkey::char2float(char *p_str,float *l)
{
  float l1;
  int i,j,k;
  int s1;
  int s2;
  char c1;

  l1=0;
  s1=0;
  s2=0;

  i=strlen(p_str);
  l1=0;
  for (j=0;j<=i-1;j++)
  {
    c1=p_str[j];
    if ((c1>='0')&&(c1<='9'))
    {
      if (s1==0)
      {
        k=c1-'0';
        l1=l1*10+k;
      }
      else
      {
        k=c1-'0';
        l1=l1+(float)(k/pow((float)10,s1));
        s1++;
      }
    }
    else
    {
      if ((c1=='+')||(c1==' ')) continue;
      else
      {
        if (c1=='-') s2=1;
        else
        {
          if (c1=='.')
          {
            s1=1;
          }
          else return(1);
        }
      }
    }
  }
  if (s2==1) l1=l1*(-1);
  *l=l1;
  return(0);
}
int bw_inkey::char2int(char *p_string,int p1,int p2)
{
  int val;
  int i;
  int sin;
  int num;
  val=0;
  sin=1;
  num=0;
  for (i=p1;i<=p2;i++)
  {
   if (*(p_string+i)<=' ') continue;
   if (*(p_string+i)=='-')
   {
     if (num==0)
     {
       sin= -1;
       continue;
     }
     else
     {
       val=0;
       break;
     }
   }
   if (*(p_string+i)=='+')
   {
     if (num==0)
     {
       sin=1;
       continue;
     }
     else
     {
       val=0;
       break;
     }
   }
   if ((*(p_string+i)>='0')&&(*(p_string+i)<='9'))
   {
     num=1;
     val=val*10+(*(p_string+i)-48)*sin;
     continue;
   }
   val=0;
   break;
  }
  return(val);
}
int bw_inkey::int2char(int val,char *p_string)
{
  int i,j;
  for (i=0;i<=4;i++)
  {
    j=val-(val/10)*10;
    val=val/10;
    *(p_string+4-i)=48+j;
  }
  *(p_string+5)=0;

  for (i=0;i<4;i++)
  {
	  if (*(p_string+i)=='0') *(p_string+i)=' ';
	  else break;
  }

  return(1);
}
int bw_inkey::float2char(float val,char *p_str)
{
  int i,j,k;
  int sin;
  int err;
  char string[SMG_LEN];
  char s1[SMG_LEN];

  k=1;
  sin=0;
  err=0;

  if (val<0)
  {
    val=val*(-1);
    sin=1;
  }
  val=val+(float)0.00000000009;

  for (i=19;i>=0;i--)
  {
    j=0;
    if (val>=pow((float)10,i))
    {
      for (j=1;j<=10;j++)
      {
        val=val-(float)pow((float)10,i);
        if (val<pow((float)10,i)) break;
      }
    }
    if (j>=10)
    {
      err=1;
      break;
    }
    string[k]='0'+j;
    k++;
  }
  if (err==1)
  {
    p_str[0]=0;
    return(1);
  }

  string[k]='.';
  k++;

  for (i=1;i<=8;i++)
  {
    j=0;
    if (val>=1/pow((float)10,i))
    {
      for (j=1;j<=10;j++)
      {
        val=val-(float)(1/pow((float)10,i));
        if (val<1/pow((float)10,i)) break;
      }
    }
    if (j>=10)
    {
      err=1;
      break;
    }
    string[k]='0'+j;
    k++;
  }
  if (err==1)
  {
    p_str[0]=0;
    return(1);
  }
  string[k]=0;

  for (i=1;i<=19;i++)  if (string[i]!='0') break;
  for (j=27;j>=21;j--) if (string[j]!='0') break;
  strpcut(string,i,j-i+1,SMG_LEN,s1,SMG_LEN);
  if (sin==1) strcpy(p_str,"-");
  else p_str[0]=0;
  strcat(p_str,s1);

  return(0);
}
int bw_inkey::long2char(long l,char *p_tmpc2)
{
  char s_tmpc3[11];
  long j;
  int  i,k,m;
  char c1;

  for (i=0;i<=10;i++) s_tmpc3[i]=0;

  if (l<0)
  {
    m=1;
    l=0-l;
  }
  else m=0;

  j=1000000000;
  c1='0';
  for (k=0;k<=9;k++)
  {
    i=0;
    while (l>=j)
    {
      i++;
      l=l-j;
    }
    s_tmpc3[k]=c1+i;
    j=j/10;
  }

  for (i=0;i<=8;i++) if (s_tmpc3[i]!='0') break;

  if (m==1)
  {
    k=1;
    p_tmpc2[0]='-';
  }
  else  k=0;

  for (i=i;i<=9;i++)
  {
    p_tmpc2[k++]=s_tmpc3[i];
    p_tmpc2[k]=0;
  }

  return(0);
}
int bw_inkey::strfind(char *p1,char *p2)
{
  int i,j;
  int len1,len2;
  int state;
  len1=strlen(p1);
  len2=strlen(p2);
  for (i=len2;i>=1;i--) if ((p2[i-1]>' ')||(p2[i-1]<0)) break;
  len2=i;
  for (i=1;i<=len1-len2+1;i++)
  {
    state=0;
    for (j=1;j<=len2;j++)
    {
      if (p1[i-1+j-1]!=p2[j-1])
      {
        state=1;
        break;
      }
    }
    if (state==0) break;
  }
  if (state==1) return(-1);
  else return(i-1);
}
int bw_inkey::strfinda(char *p1,char *p2)
{
  int i,j;
  int len1,len2;
  int state;
  len1=strlen(p1);
  len2=strlen(p2);
  for (i=1;i<=len1-len2+1;i++)
  {
    state=0;
    for (j=1;j<=len2;j++)
    {
      if (p1[i-1+j-1]!=p2[j-1])
      {
        state=1;
        break;
      }
    }
    if (state==0) break;
  }
  if (state==1) return(-1);
  else return(i-1);
}
int bw_inkey::strempty(char *p1)
{
  int i,k;
  i=0;
  k=0;
  while (1)
  {
    if (p1[i]==0) break;
    if ((p1[i]>' ')||(p1[i]<0))
    {
      k=1;
      break;
    }
    i++;
  }
  return(k);
}
int bw_inkey::upper(char c1)
{
  if ((c1>='a')&&(c1<='z')) c1=c1-32;
  return(c1);
}
int bw_inkey::lower(char c1)
{
  if ((c1>='A')&&(c1<='Z')) c1=c1+32;
  return(c1);
}
int bw_inkey::uppers(char *s1)
{
  int i;
  for (i=0;i<(int)strlen(s1);i++) s1[i]=upper(s1[i]);
  return(0);
}
int bw_inkey::lowers(char *s1)
{
  int i;
  for (i=0;i<(int)strlen(s1);i++) s1[i]=lower(s1[i]);
  return(0);
}
int bw_inkey::mon2int(char *str)
{
  int i;
  str[0]=upper(str[0]);
  str[1]=upper(str[1]);
  str[2]=upper(str[2]);
  str[3]=0;
  i=0;
  if (strcmp(str,"JAN")==0) i=1;
  if (strcmp(str,"FEB")==0) i=2;
  if (strcmp(str,"MAR")==0) i=3;
  if (strcmp(str,"APR")==0) i=4;
  if (strcmp(str,"MAY")==0) i=5;
  if (strcmp(str,"JUN")==0) i=6;
  if (strcmp(str,"JUL")==0) i=7;
  if (strcmp(str,"AUG")==0) i=8;
  if (strcmp(str,"SEP")==0) i=9;
  if (strcmp(str,"OCT")==0) i=10;
  if (strcmp(str,"NOV")==0) i=11;
  if (strcmp(str,"DEC")==0) i=12;
  return(i);
}
int bw_inkey::mon2day(int mon)
{
  int i;
  if ((mon==1)||(mon==3)||(mon==5)||(mon==7)||(mon==8)||(mon==10)||(mon==12))
  {
    i=31;
  }
  else
  {
    if (mon==2) i=28;
    else i=30;
  }
  return(i);
}
int bw_inkey::int2mon(int i,char *mon)
{
  strcpy(mon,"jan");
  if (i==1)  strcpy(mon,"jan");
  if (i==2)  strcpy(mon,"feb");
  if (i==3)  strcpy(mon,"mar");
  if (i==4)  strcpy(mon,"apr");
  if (i==5)  strcpy(mon,"may");
  if (i==6)  strcpy(mon,"jun");
  if (i==7)  strcpy(mon,"jul");
  if (i==8)  strcpy(mon,"aug");
  if (i==9)  strcpy(mon,"sep");
  if (i==10) strcpy(mon,"oct");
  if (i==11) strcpy(mon,"nov");
  if (i==12) strcpy(mon,"dec");
  return(1);
}
int bw_inkey::dateadd(char *s1,char *s2,int i)
{
  int a,b,c,e;
  char dc[4],ec[5+1];
  a=char2int(s1,0,1);
  dc[0]=s1[3];
  dc[1]=s1[4];
  dc[2]=s1[5];
  dc[3]=0;
  b=mon2int(dc);
  e=mon2day(b);
  c=char2int(s1,7,8);
  if (e>=a+i)
  {
    int2char(a+i,ec);
    strcpy(s2,s1);
    s2[0]=ec[3];
    s2[1]=ec[4];
  }
  else
  {
    b++;
    if (b>12) 
    {
      b=1;
      c++;
    }
    int2char(a+i-e,ec);
    s2[0]=ec[3];
    s2[1]=ec[4];
    s2[2]='-';
    s2[3]=0;
    int2mon(b,dc);
    strcat(s2,dc);
    s2[6]='-';
    int2char(c,ec);
    s2[7]=ec[3];
    s2[8]=ec[4];
    s2[9]=0;
  }
  return(1);
}
int bw_inkey::cdate(char *p1,char *p2)
{
  int i;
  char tmpc1[5+1];
  i=char2int(p1,7,8);
  if (i>70) 
  {
    p2[0]='1';
    p2[1]='9';
  }
  else
  {
    p2[0]='2';
    p2[1]='0';
  }
  p2[2]=p1[7];
  p2[3]=p1[8];
  p2[4]=0;
  strcat(p2,"Äê");
  tmpc1[0]=p1[3];
  tmpc1[1]=p1[4];
  tmpc1[2]=p1[5];
  tmpc1[3]=0;
  i=mon2int(tmpc1);
  int2char(i,tmpc1);
  p2[6]=tmpc1[3];
  p2[7]=tmpc1[4];
  p2[8]=0;
  strcat(p2,"ÔÂ");
  p2[10]=p1[0];
  p2[11]=p1[1];
  p2[12]=0;
  strcat(p2,"ÈÕ");
  return(1);
}
int bw_inkey::zero2sp(char *p)
{
  int i;
  for (i=0;i<=4;i++)
  {
    if (p[i]=='0') p[i]=' ';
    else break;
  }
  return(1);
}
int bw_inkey::w_find_file(char *fn1)
{
/*
  int i;
  struct _finddata_t ffblk;
  i=(int)_findfirst(fn1,&ffblk);
  if (i==(-1)) return(0);
  else return(1);
*/
  FILE *fp;
  fp=fopen(fn1,"r");
  if (fp==NULL) return(0);
  else
  {
    fclose(fp);
    return(1);
  }
}
int bw_inkey::w_find_dir(char *fn1)
{
/*
  int i;
  struct _finddata_t ffblk;
  i=(int)_findfirst(fn1,&ffblk);
  if (i==(-1)) return(0);
  else return(1);
*/
  return(0);
}
int bw_inkey::w_fname_ok(char *fn1)
{
  int i,j;
  j=0;
  for (i=0;i<(int)strlen(fn1);i++)
  {
    if ((fn1[i]=='?')||(fn1[i]=='*'))
    {
      j=1;
      break;
    }
  }
  if (j==1) return(0);
  else return(1);
}
int bw_inkey::w_cpy_file(char *fn1,char *fn2)
{
  int           fp1,fp2;
  unsigned int  rn1;
  int           rn2;

  fp1=/*s*/open(fn1,O_RDONLY/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
  if (fp1<0) return(1);

  fp2=/*s*/open(fn2,O_WRONLY|O_CREAT/*|O_BINARY,SH_DENYNO*/,S_IREAD|S_IWRITE);
  if (fp2<0)
  {
    close(fp1);
    return(1);
  }

  while (1)
  {
    rn2=read(fp1,tmpc4,CPY_BSIZE);
    rn1=rn2;
    write(fp2,tmpc4,rn1);
    //if (eof(fp1)) break;
    if (rn2<CPY_BSIZE) break;
  }

  close(fp1);
  close(fp2);

  return(0);
}
int bw_inkey::w_cpy_dir(char *win_cpy_f1,char *win_cpy_f2)
{
/*
  struct _finddata_t ffblk;
  int  i;
//  int  exist;
  int  p1,p2;
  long li;
  char fn1[FN_SIZE];
  char fn2[FN_SIZE];
  char fn3[FN_SIZE];

  strcpy(fn1,win_cpy_f1);
  strcpy(fn2,win_cpy_f2);
  strtrim(fn1);
  strtrim(fn2);

  i=mkdir(fn2);
  if (i!=0) return(1);

  strcpy(fn3,fn1);
  i=strlen(fn3);
  fn3[i]=92;
  fn3[i+1]=0;
  strcat(fn3,"*.*");

  i=strlen(fn1);
  fn1[i]=92;
  fn1[i+1]=0;
  p1=i;

  i=strlen(fn2);
  fn2[i]=92;
  fn2[i+1]=0;
  p2=i;

  li= _findfirst(fn3,&ffblk);
  if (li!=0) return(0);
  strcat(fn1,ffblk.name);
  strcat(fn2,ffblk.name);
  i=w_cpy_file(fn1,fn2);
  if (i!=0) return(1);

  while (1)
  {
    li= _findnext(li,&ffblk);
    if (li!=0)
    {
      i=0;
      break;
    }
    fn1[p1]=92;
    fn1[p1+1]=0;
    strcat(fn1,ffblk.name);
    fn2[p2]=92;
    fn2[p2+1]=0;
    strcat(fn2,ffblk.name);
    i=w_cpy_file(fn1,fn2);
    if (i!=0) break;
  }

  return(i);
*/
  return(0);
}
int bw_inkey::w_del_file(char *fn1)
{
  int s_state1;
  s_state1=remove(fn1);
  return(s_state1);
}
int bw_inkey::str_cmp(char *s1,int l1,char *s2,int l2)
{
	int i;
	if (l1!=l2) return(1);
	for (i=0;i<l1;i++)
	{
		if (s1[i]!=s2[i]) return(1);
	}
	return(0);
}
