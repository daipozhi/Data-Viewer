/* 
#define STRICT
*/
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

extern class bw_main   bw_main1;
extern class bw_inkey  bw_inkey1;

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
int bw_inkey::w_get_dir(char *p_s1,int p_s1_len)
{
  getcwd(p_s1,p_s1_len);
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
int bw_inkey::strlocc(char *p_str,int p_str_len,char c1)
{
  int i,j;

  strtrim(p_str,p_str_len);

  if (p_str_len>0) p_str[p_str_len-1]=0;

  j=strlen(p_str);

  if (p_str_len<j) j=p_str_len;

  for (i=0;i<=j-1;i++) if (p_str[i]==c1) break;

  if (i<j) return(i);
  else return(j);
}
int bw_inkey::strtrim(char *p_str,int p_str_len)
{
  int i,j;

  if (p_str_len>0) p_str[p_str_len-1]=0;

  j=strlen(p_str);

  if (p_str_len<j) j=p_str_len;

  for (i=j-1;i>=0;i--)
  {
    if ((p_str[i]>' ')||(p_str[i]<0)) break;
    else p_str[i]=0;
  }

  return(0);
}

int bw_inkey::strltrim(char *p_str,int p_str_len)
{
  int  i,j,k;
  char s1[SMG_LEN];

  if (p_str_len>0) p_str[p_str_len-1]=0;

  i=strlen(p_str);

  if (p_str_len<i) i=p_str_len;

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

int bw_inkey::strpcut(char *p_s1,int p1,int p2,int p_s1_len,char *p_s2,int p_s2_len)
{
  int  i,j;
  char c1;
  i=0;
  p_s2[0]=0;
  for (j=p1;j<p1+p2;j++)
  {
    if ((j<0)||(j>=p_s1_len)) continue;
    c1=p_s1[j];
    if (i+1>=p_s2_len) continue;
    p_s2[i+0]=c1;
    p_s2[i+1]=0;
    i++;
  }
  return(1);
}
/*
int bw_inkey::str2int(char *p_string,int p1,int p2)
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
     val=val*10+(*(p_string+i)-'0')*sin;
     continue;
   }
   val=0;

   break;
  }
  return(val);
}

*/

int bw_inkey::str2int(char *p_string,int p_string_len)
{
  int val;
  int i,j;
  int sin;
  int num;
  if (p_string_len>0) p_string[p_string_len-1]=0;
  val=0;
  sin=1;
  num=0;
  j=strlen(p_string);
  for (i=0;i<j;i++)
  {
   if (p_string[i]<=' ') continue;
   if (p_string[i]=='-')
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
   if (p_string[i]=='+')
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
   if ((p_string[i]>='0')&&(p_string[i]<='9'))
   {
     num=1;
     val=val*10+(p_string[i]-'0')*sin;
     continue;
   }
   val=0;
   break;
  }

  return(val);
}
/*
int bw_inkey::str2long(char *p_str,long *l)
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
*/
/*  --- copy 2
long bw_inkey::str2long(char *p_str,int p_str_len)
{
  long li;
  int  i,j,k;
  char c1;
  if (p_str_len>0) p_str[p_str_len-1]=0;
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
    if (c1==' ') continue;
  }
  return(li);
}
*/
long bw_inkey::str2long(char *p_string,int p_string_len)
{
  long val;
  int  i,j;
  int  sin;
  int  num;
  if (p_string_len>0) p_string[p_string_len-1]=0;
  val=0;
  sin=1;
  num=0;
  j=strlen(p_string);
  for (i=0;i<j;i++)
  {
   if (p_string[i]<=' ') continue;
   if (p_string[i]=='-')
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
   if (p_string[i]=='+')
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
   if ((p_string[i]>='0')&&(p_string[i]<='9'))
   {
     num=1;
     val=val*10+(p_string[i]-'0')*sin;
     continue;
   }
   val=0;
   break;
  }

  return(val);
}

/*
int bw_inkey::str2float(char *p_str,float *l)
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
*/

float bw_inkey::str2float(char *p_str,int p_str_len)
{
  float l1;
  int   i,j,k;
  int   s1;
  int   s2;
  char  c1;

  l1=0;
  s1=0;
  s2=0;

  p_str[p_str_len-1]=0;

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
      if ((c1=='+')||(c1==' ')) { continue;}
      if (c1=='-') { s2=1; continue;}
      if (c1=='.') { s1=1; continue;}
      return(0);
    }
  }

  if (s2==1) l1=0-l1;

  return(l1);
}

int bw_inkey::int2str(int val,char *p_string,int p_string_len)
{
  int  i,j;
  char c1;
  int  zero=0,zero_p;

  if (p_string_len<12) return(0);

  if (val<0) { c1='-'; val=0-val; }
  else       { c1=' '; }

  for (i=0;i<=9;i++)
  {
	j=val-(val/10)*10;
	val=val/10;
	p_string[10-i]='0'+j;
  }

  p_string[ 0]=c1;
  p_string[11]=0;

  for (i=1;i<10;i++)
  {
	if (p_string[i]=='0')
	{
	    p_string[i]=' ';
	    zero=1;
	    zero_p=i;
	}
	else break;
  }

  if (zero==1)
  {
	p_string[zero_p]=c1;
	p_string[0     ]=' ';
  }

  return(1);
}

/*
int bw_inkey::long2str(long l,char *p_tmpc2,int p_tmpc2_len)
{
  char s_tmpc3[11];
  long j;
  int  i,k,m;
  char c1;

  if (p_tmpc2_len<11) return(0);

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
*/
int bw_inkey::long2str(long val,char *p_string,int p_string_len)
{
  int  i,j;
  char c1;
  int  zero=0,zero_p;

  if (p_string_len<12) return(0);

  if (val<0) { c1='-'; val=0-val; }
  else       { c1=' '; }

  for (i=0;i<=9;i++)
  {
	j=val-(val/10)*10;
	val=val/10;
	p_string[10-i]='0'+j;
  }

  p_string[ 0]=c1;
  p_string[11]=0;

  for (i=1;i<10;i++)
  {
	if (p_string[i]=='0')
	{
	    p_string[i]=' ';
	    zero=1;
	    zero_p=i;
	}
	else break;
  }

  if (zero==1)
  {
	p_string[zero_p]=c1;
	p_string[0     ]=' ';
  }

  return(1);
}

int bw_inkey::float2str(float val,char *p_str,int p_str_len)
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
    val=0-val;
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

  if (strlen(p_str)+strlen(s1)<p_str_len) strcat(p_str,s1);

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
  if ((c1>='a')&&(c1<='z')) c1=c1-'a'+'A';
  return(c1);
}
int bw_inkey::lower(char c1)
{
  if ((c1>='A')&&(c1<='Z')) c1=c1-'A'+'a';
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
/*
int bw_inkey::dateadd(char *s1,char *s2,int i)
{
  int a,b,c,e;
  char dc[4],ec[12];
  a=str2int(s1,0,1);
  dc[0]=s1[3];
  dc[1]=s1[4];
  dc[2]=s1[5];
  dc[3]=0;
  b=mon2int(dc);
  e=mon2day(b);
  c=str2int(s1,7,8);
  if (e>=a+i)
  {
    int2str(a+i,ec,12);
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
    int2str(a+i-e,ec,12);
    s2[0]=ec[3];
    s2[1]=ec[4];
    s2[2]='-';
    s2[3]=0;
    int2mon(b,dc);
    strcat(s2,dc);
    s2[6]='-';
    int2str(c,ec,12);
    s2[7]=ec[3];
    s2[8]=ec[4];
    s2[9]=0;
  }
  return(1);
}
*/
/*
int bw_inkey::cdate(char *p1,char *p2)
{
  int i;
  char tmpc1[12];
  i=str2int(p1,7,8);
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
  int2str(i,tmpc1,12);
  p2[6]=tmpc1[ 9];
  p2[7]=tmpc1[10];
  p2[8]=0;
  strcat(p2,"ÔÂ");
  p2[10]=p1[0];
  p2[11]=p1[1];
  p2[12]=0;
  strcat(p2,"ÈÕ");
  return(1);
}
*/
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
/*
int bw_inkey::w_find_dir(char *fn1)
{
  int i;
  struct _finddata_t ffblk;
  i=(int)_findfirst(fn1,&ffblk);
  if (i==(-1)) return(0);
  else return(1);
}
*/
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

  fp1=/*s*/open(fn1,O_RDWR/*|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE*/);
  if (fp1<0) return(1);

  fp2=/*s*/open(fn2,O_RDWR|O_CREAT/*|O_BINARY,SH_DENYNO,S_IREAD|S_IWRITE*/);
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
int bw_inkey::w_del_file(char *fn1)
{
  int s_state1;
  s_state1=remove(fn1);
  return(s_state1);
}

