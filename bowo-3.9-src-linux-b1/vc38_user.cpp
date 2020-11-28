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
#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>
*/
#include "vc_bowo.h"

extern class bw_user    bw_user1;
extern class bw_bmp     bw_bmp1;
extern class bw_dialog  bw_dialog1;
extern class bw_main    bw_main1;
extern class bw_inkey   bw_inkey1;

int bw_user::w_user_triger(char *p_win,int p_win_size,char *p_msg,int p_msg_size,char *p_itm,int p_itm_size,char *p_stt,int p_stt_size)
{
  int  i;
  char str2[SMG_SIZE];
  char str1[SMG_SIZE];

  for (i=0;i<(int)strlen(p_win);i++) p_win[i]=bw_inkey1.upper(p_win[i]);

  if ((strncmp(p_win,"DCFF_WY3",8)==0)&&
      (strncmp(p_msg,"WM_CLOSE",8)==0))
  {
    
    i=0;
    if (bw_dialog1.w_mv_exist("fdca1",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca1",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"4*2");
    if (i==2) strcpy(str1,"2*2");
    if (i==3) strcpy(str1,"4*1");
    if (i==4) strcpy(str1,"2*1");
    if (i==5) strcpy(str1,"3*2");
    if (i==6) strcpy(str1,"1*1");
    if (i==7) strcpy(str1,"3*1");

    bw_dialog1.w_mv_save_mem("?f1",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca2",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca2",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"<=1000");
    if (i==2) strcpy(str1,">=3001,<=4000");
    if (i==3) strcpy(str1,">=1001,<=2000");
    if (i==4) strcpy(str1,">=4001");
    if (i==5) strcpy(str1,">=2001,<=3000");

    bw_dialog1.w_mv_save_mem("?f2",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca3",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca3",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"现");
    if (i==2) strcpy(str1,"期");

    bw_dialog1.w_mv_save_mem("?f3",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca4",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca4",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"租");
    if (i==2) strcpy(str1,"售");

    bw_dialog1.w_mv_save_mem("?f4",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca5",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca5",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"多层");
    if (i==2) strcpy(str1,"高层");
    if (i==3) strcpy(str1,"别墅");

    bw_dialog1.w_mv_save_mem("?fa",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca6",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca6",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"一");
    if (i==2) strcpy(str1,"二");
    if (i==3) strcpy(str1,"三");
    if (i==4) strcpy(str1,"四");

    bw_dialog1.w_mv_save_mem("?f7",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca7",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca7",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"=1");
    if (i==2) strcpy(str1,"=99");
    if (i==3) strcpy(str1,">1,<99");

    bw_dialog1.w_mv_save_mem("?fd",4,0,str1,strlen(str1));

    str1[0]=0;

    if (bw_dialog1.w_mv_exist("fdcb1",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb1",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"上城;");

    if (bw_dialog1.w_mv_exist("fdcb2",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb2",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"下城;");

    if (bw_dialog1.w_mv_exist("fdcb3",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb3",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"西湖;");

    if (bw_dialog1.w_mv_exist("fdcb4",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb4",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"江干;");

    if (bw_dialog1.w_mv_exist("fdcb5",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb5",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"拱墅;");

    if (bw_dialog1.w_mv_exist("fdcb6",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb6",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"萧山;");

    if (bw_dialog1.w_mv_exist("fdcb7",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb7",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"余杭;");

    if (bw_dialog1.w_mv_exist("fdcb8",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb8",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"富阳;");

    if (bw_dialog1.w_mv_exist("fdcb9",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb9",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"建德;");

    if (bw_dialog1.w_mv_exist("fdcb10",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb10",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"临安;");

    if (bw_dialog1.w_mv_exist("fdcb11",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb11",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"桐芦;");

    if (bw_dialog1.w_mv_exist("fdcb12",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb12",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"淳安;");

    if (bw_dialog1.w_mv_exist("fdcb13",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb13",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"其它;");

    bw_dialog1.w_mv_save_mem("?f8",4,0,str1,strlen(str1));

  }
  
  if ((strncmp(p_win,"DCFF_WY4",8)==0)&&
      (strncmp(p_msg,"WM_CLOSE",8)==0))
  {
    
    i=0;
    if (bw_dialog1.w_mv_exist("fdca1",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca1",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"<=500");
    if (i==2) strcpy(str1,">=501,<=1000");
    if (i==3) strcpy(str1,">=1001");

    bw_dialog1.w_mv_save_mem("?f1",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca2",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca2",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"<=1000");
    if (i==2) strcpy(str1,">=3001,<=4000");
    if (i==3) strcpy(str1,">=1001,<=2000");
    if (i==4) strcpy(str1,">=4001");
    if (i==5) strcpy(str1,">=2001,<=3000");

    bw_dialog1.w_mv_save_mem("?f2",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca3",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca3",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"现");
    if (i==2) strcpy(str1,"期");

    bw_dialog1.w_mv_save_mem("?f3",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca4",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca4",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"租");
    if (i==2) strcpy(str1,"售");

    bw_dialog1.w_mv_save_mem("?f4",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca5",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca5",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"商业");
    if (i==2) strcpy(str1,"工业");
    if (i==3) strcpy(str1,"办公");

    bw_dialog1.w_mv_save_mem("?f6",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca6",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca6",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"一");
    if (i==2) strcpy(str1,"二");
    if (i==3) strcpy(str1,"三");
    if (i==4) strcpy(str1,"四");

    bw_dialog1.w_mv_save_mem("?f7",4,0,str1,strlen(str1));

    i=0;
    if (bw_dialog1.w_mv_exist("fdca7",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdca7",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }

    str1[0]=0;

    if (i==1) strcpy(str1,"=1");
    if (i==2) strcpy(str1,"=99");
    if (i==3) strcpy(str1,">1,<99");

    bw_dialog1.w_mv_save_mem("?fb",4,0,str1,strlen(str1));

    str1[0]=0;

    if (bw_dialog1.w_mv_exist("fdcb1",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb1",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"上城;");

    if (bw_dialog1.w_mv_exist("fdcb2",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb2",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"下城;");

    if (bw_dialog1.w_mv_exist("fdcb3",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb3",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"西湖;");

    if (bw_dialog1.w_mv_exist("fdcb4",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb4",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"江干;");

    if (bw_dialog1.w_mv_exist("fdcb5",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb5",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"拱墅;");

    if (bw_dialog1.w_mv_exist("fdcb6",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb6",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"萧山;");

    if (bw_dialog1.w_mv_exist("fdcb7",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb7",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"余杭;");

    if (bw_dialog1.w_mv_exist("fdcb8",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb8",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"富阳;");

    if (bw_dialog1.w_mv_exist("fdcb9",6,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb9",6,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"建德;");

    if (bw_dialog1.w_mv_exist("fdcb10",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb10",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"临安;");

    if (bw_dialog1.w_mv_exist("fdcb11",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb11",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"桐芦;");

    if (bw_dialog1.w_mv_exist("fdcb12",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb12",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"淳安;");

    if (bw_dialog1.w_mv_exist("fdcb13",7,0)==1)
    {
      bw_dialog1.w_mv_fet_val("fdcb13",7,0,str2,SMG_SIZE);
      i=bw_inkey1.str2int(str2,SMG_SIZE);
    }
    if (i==1) strcat(str1,"其它;");

    strcat(str1,"  ");

    bw_dialog1.w_mv_save_mem("?f8",4,0,str1,strlen(str1));

  }
  
  return(0);
}

