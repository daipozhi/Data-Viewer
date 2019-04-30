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

extern class bw_main      bw_main1;

int bw_buff::get_linecol(int wpp,int line,int col)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(t_linecol[wpp][line][col]);
}

int bw_buff::set_linecol(int wpp,int line,int col,int val)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  t_linecol[wpp][line][col]=val;
  return(0);
}

char bw_buffa::get_tmpc1(int wpp,int line,int col)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(tmpc1[wpp][line][col]);
}
int bw_buffa::set_tmpc1(int wpp,int line,int col,char val)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  tmpc1[wpp][line][col]=val;
  return(0);
}

long bw_win_bua::get_win_timer(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_timer[wpp]);
}
int bw_win_bua::set_win_timer(int wpp,long val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_timer[wpp]=val;
  return(0);
}

int bw_win_bua::get_1fldname(int p1,char *sval,int slen)
{
  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN))
  {
    sval[0]=0;
    return(0);
  }
  else
  {
    if (slen>FLD_NAME_LEN) j=FLD_NAME_LEN;
    else j=slen;

    for (i=0;i<j-1;i++)
    {
      sval[i]=t_fldname[p1][i];
    }

    sval[j-1]=0;

    return(0);
  }
}

int bw_win_bua::set_1fldname(int p1,char *sval,int slen)
{
  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  else
  {
    if (slen>FLD_NAME_LEN) j=FLD_NAME_LEN;
    else j=slen;

    for (i=0;i<j-1;i++)
    {
      t_fldname[p1][i]=sval[i];
    }

    t_fldname[p1][j-1]=0;

    return(0);
  }
}
int bw_win_bua::set_1fldname1(int p1,int p2,char c1)
{
 // int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  if ((p2<0)||(p2>=FLD_NAME_LEN)) return(0);
  t_fldname[p1][p2]=c1;
  return(0);
}
int bw_win_bua::get_1fldtype(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldtype[p1]);
}
int bw_win_bua::set_1fldtype(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldtype[p1]=val;
  return(0);
}
int bw_win_bua::get_1fldbase(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldbase[p1]);
}
int bw_win_bua::set_1fldbase(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldbase[p1]=val;
  return(0);
}
int bw_win_bua::get_1fldseri(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldseri[p1]);
}
int bw_win_bua::set_1fldseri(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldseri[p1]=val;
  return(0);
}
int bw_win_bua::get_1fldlen(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldlen[p1]);
}
int bw_win_bua::set_1fldlen(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldlen[p1]=val;
  return(0);
}
int bw_win_bua::get_1flddec(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_flddec[p1]);
}
int bw_win_bua::set_1flddec(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_flddec[p1]=val;
  return(0);
}
int bw_win_bua::get_1fldedt(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldedt[p1]);
}
int bw_win_bua::set_1fldedt(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldedt[p1]=val;
  return(0);
}
int bw_win_bua::get_fldseri_tmp(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_fldseri_tmp[p1]);
}
int bw_win_bua::set_fldseri_tmp(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_fldseri_tmp[p1]=val;
  return(0);
}
int bw_win_bua::get_field_tmp(int p1,char *sval,int len)
{
  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN))
  {
    sval[0]=0;
    return(0);
  }
  else
  {
    if (len>10) j=10;
    else j=len;

    for (i=0;i<j-1;i++)
    {
      sval[i]=t_field_tmp[p1][i];
    }

    sval[j-1]=0;

    return(0);
  }
}
int bw_win_bua::set_field_tmp(int p1,char *sval,int len)
{
  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  else
  {
    if (len>10) j=10;
    else j=len;

    for (i=0;i<j-1;i++)
    {
      t_field_tmp[p1][i]=sval[i];
    }

    t_field_tmp[p1][j-1]=0;

    return(0);
  }
}
int bw_win_bua::set_field_tmp1(int p1,int p2,char c1)
{
//  int i,j;

  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  else
  {
    if ((p2<0)||(p2>=10)) return(0);
    t_field_tmp[p1][p2]=c1;
    return(0);
  }
}
int bw_win_bua::get_base_tmp(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_base_tmp[p1]);
}
int bw_win_bua::set_base_tmp(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_base_tmp[p1]=val;
  return(0);
}
int bw_win_bua::get_recno_tmp(int p1)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  return(t_recno_tmp[p1]);
}
int bw_win_bua::set_recno_tmp(int p1,int val)
{
  if ((p1<0)||(p1>=FLD_IN_SCRN)) return(0);
  t_recno_tmp[p1]=val;
  return(0);
}
/*
int bw_win_bua::get_win_subhndid(int wpp,int pp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>9)) return(0);
  return(win_subhndid[wpp][pp]);
}
int bw_win_bua::set_win_subhndid(int wpp,int pp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>9)) return(0);
  win_subhndid[wpp][pp]=val;
  return(0);
}
int bw_win_bua::get_win_subhndpp(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_subhndpp[wpp]);
}
int bw_win_bua::set_win_subhndpp(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_subhndpp[wpp]=val;
  return(0);
}
*/
int bw_win_bua::get_win_state12(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_state12[wpp]);
}
int bw_win_bua::set_win_state12(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_state12[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_state13(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_state13[wpp]);
}
int bw_win_bua::set_win_state13(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_state13[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_switch_bmp(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_switch_bmp[wpp]);
}
int bw_win_bua::set_win_switch_bmp(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_switch_bmp[wpp]=val;
  return(0);
}

int bw_win_bua::get_win_pp2(int wpp,int pp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>3)) return(0);
  return(win_pp2[wpp][pp]);
}
int bw_win_bua::set_win_pp2(int wpp,int pp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>3)) return(0);
  win_pp2[wpp][pp]=val;
  return(0);
}
int bw_win_bua::get_win_hpp3(int wpp,int pp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>8)) return(0);
  return(win_hpp3[wpp][pp]);
}
int bw_win_bua::set_win_hpp3(int wpp,int pp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>8)) return(0);
  win_hpp3[wpp][pp]=val;
  return(0);
}
int bw_win_bua::get_win_hpp7(int wpp,int pp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>1)) return(0);
  return(win_hpp7[wpp][pp]);
}
int bw_win_bua::set_win_hpp7(int wpp,int pp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>1)) return(0);
  win_hpp7[wpp][pp]=val;
  return(0);
}

HWND bw_win_bua::get_win_phh(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_phh[wpp]);
}

int bw_win_bua::set_win_phh(int wpp,HWND hwnd)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_phh[wpp]=hwnd;
  return(0);
}

int bw_win_bub::get_win_tabname(int p1,int p_fcnt,char *p_s1,int len)
{
  int i,j;
  if ((p1<0)||(p1>1)) return(0);
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_tabname[p1][p_fcnt][j];
  }
  if (i-1<0) p_s1[0]=0;
  else  p_s1[i-1]=0;
  return(0);
}
int bw_win_bub::set_win_tabname(int p1,int p_fcnt,char *p_s1,int len)
{
  int i,j;
  if ((p1<0)||(p1>1)) return(0);
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_tabname[p1][p_fcnt][j]=p_s1[j];
  }
  if (i-1<0) win_tabname[p1][p_fcnt][0]=0;
  else win_tabname[p1][p_fcnt][i-1]=0;
  return(0);
}
int bw_win_bua::get_win_pp4(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_pp4[wpp]);
}
int bw_win_bua::set_win_pp4(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_pp4[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_pp5(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_pp5[wpp]);
}
int bw_win_bua::set_win_pp5(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_pp5[wpp]=val;
  return(0);
}


int bw_win_bua::get_win_msgboxlock(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_msgboxlock[wpp]);
}
int bw_win_bua::set_win_msgboxlock(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_msgboxlock[wpp]=val;
  return(0);
}


int bw_win_bua::get_win_pp6(int wpp,int p04)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p04<0)||(p04>=5)) return(0);
  return(win_pp6[wpp][p04]);
}
int bw_win_bua::set_win_pp6(int wpp,int p04,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p04<0)||(p04>=5)) return(0);
  win_pp6[wpp][p04]=val;
  return(0);
}
int bw_win_bua::get_win_pp9(int p_fcnt,int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  return(win_pp9[p_fcnt][wpp]);
}
int bw_win_bua::set_win_pp9(int p_fcnt,int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  win_pp9[p_fcnt][wpp]=val;
  return(0);
}
int bw_win_bua::get_win_con(int wpp,int p03)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_con[wpp][p03]);
}
int bw_win_bua::set_win_con(int wpp,int p03,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_con[wpp][p03]=val;
  return(0);
}
int bw_win_bua::get_win_style(int wpp,int pp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>=WIN_STYLE_NUM)) return(0);
  return(win_style[wpp][pp]);
}
int bw_win_bua::set_win_style(int wpp,int pp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp<0)||(pp>=WIN_STYLE_NUM)) return(0);
  win_style[wpp][pp]=val;
  return(0);
}
FARPROC bw_win_bua::get_win_fpp(int pp)
{
  if ((pp<0)||(pp>=HND_NUM)) return(0);
  return(win_fpp[pp]);
}  
int bw_win_bua::set_win_fpp(int pp,FARPROC fproc)
{
  if ((pp<0)||(pp>=HND_NUM)) return(0);
  win_fpp[pp]=fproc;
  return(0);
}
HWND bw_win_bua::get_win_hnd(int pp)
{
  if ((pp<0)||(pp>=HND_NUM)) return(0);
  return(win_hnd[pp]);
}
int bw_win_bua::set_win_hnd(int pp,HWND hnd)
{
  if ((pp<0)||(pp>=HND_NUM)) return(0);
  win_hnd[pp]=hnd;
  return(0);
}
int bw_win_bua::get_win_hpp4(int hpp,int p04)
{
  if ((hpp<0)||(hpp>=HND_NUM)) return(0);
  if ((p04<0)||(p04>4)) return(0);
  return(win_hpp4[hpp][p04]);
}
int bw_win_bua::set_win_hpp4(int hpp,int p04,int val)
{
  if ((hpp<0)||(hpp>=HND_NUM)) return(0);
  if ((p04<0)||(p04>4)) return(0);
  win_hpp4[hpp][p04]=val;
  return(0);
}
int bw_win_bua::get_win_pp11(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_pp11[wpp]);
}
int bw_win_bua::set_win_pp11(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_pp11[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_create_menu(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_create_menu[wpp]);
}
int bw_win_bua::set_win_create_menu(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_create_menu[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_linep(int wpp,int p01)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_linep[wpp][p01]);
}
int bw_win_bua::set_win_linep(int wpp,int p01,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_linep[wpp][p01]=val;
  return(0);
}
int bw_win_bub::get_win_window_name(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_window_name[wpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_win_bub::set_win_window_name(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_window_name[wpp][j]=p_s1[j];
  }
  if (i>0) win_window_name[wpp][i-1]=0;
  else win_window_name[wpp][0]=0;
  return(0);
}
int bw_win_bub::get_win_find_name(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_find_name[wpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_win_bub::set_win_find_name(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_find_name[wpp][j]=p_s1[j];
  }
  if (i>0) win_find_name[wpp][i-1]=0;
  else win_find_name[wpp][0]=0;
  return(0);
}
int bw_win_bua::get_win_is_link(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_is_link[wpp]);
}
int bw_win_bua::set_win_is_link(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_is_link[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_is_calc(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_is_calc[wpp]);
}
int bw_win_bua::set_win_is_calc(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_is_calc[wpp]=val;
  return(0);
}
int bw_win_bua::get_win_memo_basep(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_memo_basep[wpp]);
}
int bw_win_bua::set_win_memo_basep(int wpp,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_memo_basep[wpp]=val;
  return(0);
}
HWND bw_edit_bua::get_win_edit_hnd1(int epp)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  return(win_edit_hnd1[epp]);
}
int bw_edit_bua::set_win_edit_hnd1(int epp,HWND hwnd)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  win_edit_hnd1[epp]=hwnd;
  return(0);
}
HWND bw_edit_bua::get_win_edit_hnd2(int epp)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  return(win_edit_hnd2[epp]);
}
int bw_edit_bua::set_win_edit_hnd2(int epp,HWND hwnd)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  win_edit_hnd2[epp]=hwnd;
  return(0);
}
int bw_edit_bua::get_win_edit_dirn(int epp,char *p_s1,int len)
{
  int i,j;
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_edit_dirn[epp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_edit_bua::set_win_edit_dirn(int epp,char *p_s1,int len)
{
  int i,j;
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_edit_dirn[epp][j]=p_s1[j];
  }
  if (i>0) win_edit_dirn[epp][i-1]=0;
  else win_edit_dirn[epp][0]=0;
  return(0);
}
int bw_edit_bua::get_win_edit_file(int epp,char *p_s1,int len)
{
  int i,j;
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_edit_file[epp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_edit_bua::set_win_edit_file(int epp,char *p_s1,int len)
{
  int i,j;
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_edit_file[epp][j]=p_s1[j];
  }
  if (i>0) win_edit_file[epp][i-1]=0;
  else win_edit_file[epp][0]=0;
  return(0);
}
int bw_edit_bua::tst_dirn_file(void)
{
  HDC  hdc;
  int  i;
  char stn1[FN_SIZE];
  char stn2[FN_SIZE];

  hdc=GetDC(bw_main1.win_hwnd1);

  for (i=0;i<10;i++)
  {
    get_win_edit_dirn(i,stn1,FN_SIZE);
    get_win_edit_file(i,stn2,FN_SIZE);

    TextOut(hdc,0  ,i*20,stn1,strlen(stn1));
    TextOut(hdc,250,i*20,stn2,strlen(stn2));
  }

  ReleaseDC(bw_main1.win_hwnd1,hdc);

  return(0);
}
int bw_edit_bua::get_win_edit_modi(int epp)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  return(win_edit_modi[epp]);
}
int bw_edit_bua::set_win_edit_modi(int epp,int val)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  win_edit_modi[epp]=val;
  return(0);
}
int bw_edit_bua::get_win_edit_inuse(int epp)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  return(win_edit_inuse[epp]);
}
int bw_edit_bua::set_win_edit_inuse(int epp,int val)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  win_edit_inuse[epp]=val;
  return(0);
}
int bw_edit_bua::get_win_edit_wpp(int epp)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  return(win_edit_wpp[epp]);
}
int bw_edit_bua::set_win_edit_wpp(int epp,int val)
{
  if ((epp<0)||(epp>=EDIT_NUM)) return(0);
  win_edit_wpp[epp]=val;
  return(0);
}
int bw_link_bua::get_win_svar(int spp)
{
  if ((spp<0)||(spp>=VAR_IN_SCRN)) return(0);
  return(win_svar[spp]);
}
int bw_link_bua::set_win_svar(int spp,int val)
{
  if ((spp<0)||(spp>=VAR_IN_SCRN)) return(0);
  win_svar[spp]=val;
  return(0);
}
int bw_link_bua::get_win_svused(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svused[vpp]);
}
int bw_link_bua::set_win_svused(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svused[vpp]=val;
  return(0);
}
int bw_link_bua::get_win_svpoin(int vpp,int p01)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_svpoin[vpp][p01]);
}
int bw_link_bua::set_win_svpoin(int vpp,int p01,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_svpoin[vpp][p01]=val;
  return(0);
}
int bw_link_bua::get_win_svseri(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svseri[vpp]);
}
int bw_link_bua::set_win_svseri(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svseri[vpp]=val;
  return(0);
}
int bw_link_bua::get_win_svrecn(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svrecn[vpp]);
}
int bw_link_bua::set_win_svrecn(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svrecn[vpp]=val;
  return(0);
}
int bw_link_bua::get_win_svbase(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svbase[vpp]);
}
int bw_link_bua::set_win_svbase(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svbase[vpp]=val;
  return(0);
}
int bw_link_bua::get_win_svwind(int vpp)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  return(win_svwind[vpp]);
}
int bw_link_bua::set_win_svwind(int vpp,int val)
{
  if ((vpp<0)||(vpp>=WIN_VAR_NUM)) return(0);
  win_svwind[vpp]=val;
  return(0);
}
int bw_link_bua::get_win_chlink(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_CHAR)) return(0);
  return(win_chlink[lpp]);
}
int bw_link_bua::set_win_chlink(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_CHAR)) return(0);
  win_chlink[lpp]=val;
  return(0);
}
int bw_link_bua::get_win_bslink(int dpp,int p02)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(win_bslink[dpp][p02]);
}
int bw_link_bua::set_win_bslink(int dpp,int p02,int val)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  win_bslink[dpp][p02]=val;
  return(0);

}
int bw_link_bua::get_win_bspoin(int dpp,int p01)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_bspoin[dpp][p01]);
}
int bw_link_bua::set_win_bspoin(int dpp,int p01,int val)
{
  if ((dpp<0)||(dpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_bspoin[dpp][p01]=val;
  return(0);
}
int bw_link_bua::get_win_lkpoin(int cpp,int p01)
{
  if ((cpp<0)||(cpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_lkpoin[cpp][p01]);
}
int bw_link_bua::set_win_lkpoin(int cpp,int p01,int val)
{
  if ((cpp<0)||(cpp>=COND_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_lkpoin[cpp][p01]=val;
  return(0);
}
int bw_link_bua::get_win_lkmodi(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkmodi[lpp]);
}
int bw_link_bua::set_win_lkmodi(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkmodi[lpp]=val;
  return(0);
}
int bw_link_bua::get_win_lkseri(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkseri[lpp]);
}
int bw_link_bua::set_win_lkseri(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkseri[lpp]=val;
  return(0);
}
int bw_link_bua::get_win_lkbase(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkbase[lpp]);
}
int bw_link_bua::set_win_lkbase(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkbase[lpp]=val;
  return(0);
}
int bw_link_bua::get_win_lkrecn(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkrecn[lpp]);
}
int bw_link_bua::set_win_lkrecn(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkrecn[lpp]=val;
  return(0);
}
int bw_link_bua::get_win_lkwind(int lpp)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  return(win_lkwind[lpp]);
}
int bw_link_bua::set_win_lkwind(int lpp,int val)
{
  if ((lpp<0)||(lpp>=LINK_MODI_NUM)) return(0);
  win_lkwind[lpp]=val;
  return(0);
}
int bw_link_bua::get_win_continue(int p_fcnt,int wpp)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_continue[p_fcnt][wpp]);
}
int bw_link_bua::set_win_continue(int p_fcnt,int wpp,int val)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_continue[p_fcnt][wpp]=val;
  return(0);
}
int bw_link_bua::set_win_cbb1(int vpp,int pp1,int val)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  win_bb1[vpp][pp1]=val;
  return(0);
}
int bw_link_bua::get_win_bb1(int vpp,char *p_s1,int len)
{
  int i,j;
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_bb1[vpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_link_bua::set_win_bb1(int vpp,char *p_s1,int len)
{
  int i,j;
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_bb1[vpp][j]=p_s1[j];
  }
  if (i>0) win_bb1[vpp][i-1]=0;
  else win_bb1[vpp][0]=0;
  return(0);
}
int bw_link_bua::get_win_bb2(int vpp)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  return(win_bb2[vpp]);
}
int bw_link_bua::set_win_bb2(int vpp,int val)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  win_bb2[vpp]=val;
  return(0);
}
int bw_link_bua::get_win_bb3(int vpp)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  return(win_bb3[vpp]);
}
int bw_link_bua::set_win_bb3(int vpp,int val)
{
  if ((vpp<0)||(vpp>=VAL_NUM)) return(0);
  win_bb3[vpp]=val;
  return(0);
}

int bw_print_bua::get_t6_linecol(int fpp,int p02) 
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(t6_linecol[fpp][p02]);
}
int bw_print_bua::set_t6_linecol(int fpp,int p02,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  t6_linecol[fpp][p02]=val;
  return(0);
}
int bw_print_bua::get_t6c_fldname(int fpp,int pp1)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((pp1<0)||(pp1>21)) return(0);
  return(t6_fldname[fpp][pp1]);
}
int bw_print_bua::set_t6c_fldname(int fpp,int pp1,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((pp1<0)||(pp1>21)) return(0);
  t6_fldname[fpp][pp1]=val;
  return(0);
}
int bw_print_bua::get_t6_fldname(int fpp,char *p_s1,int len)
{
  int i,j;
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if (len>21) i=21;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t6_fldname[fpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_print_bua::set_t6_fldname(int fpp,char *p_s1,int len)
{
  int i,j;
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if (len>21) i=21;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t6_fldname[fpp][j]=p_s1[j];
  }
  if (i>0) t6_fldname[fpp][i-1]=0;
  else t6_fldname[fpp][0]=0;
  return(0);
}
int bw_print_bua::get_t6_fldtype(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldtype[fpp]);
}
int bw_print_bua::set_t6_fldtype(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldtype[fpp]=val;
  return(0);
}
int bw_print_bua::get_t6_fldedit(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldedit[fpp]);
}
int bw_print_bua::set_t6_fldedit(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldedit[fpp]=val;
  return(0);
}
int bw_print_bua::get_t6_fldbase(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldbase[fpp]);
}
int bw_print_bua::set_t6_fldbase(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldbase[fpp]=val;
  return(0);
}
int bw_print_bua::get_t6_fldseri(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldseri[fpp]);
}
int bw_print_bua::set_t6_fldseri(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldseri[fpp]=val;
  return(0);
}
int bw_print_bua::get_t6_fldlen(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_fldlen[fpp]);
}
int bw_print_bua::set_t6_fldlen(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_fldlen[fpp]=val;
  return(0);
}
int bw_print_bua::get_t6_flddec(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(t6_flddec[fpp]);
}
int bw_print_bua::set_t6_flddec(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  t6_flddec[fpp]=val;
  return(0);
}
int bw_print_bub::get_t6_tmpc1(int lpp,int cpp)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  return(t6_tmpc1[lpp][cpp]);
}
int bw_print_bub::set_t6_tmpc1(int lpp,int cpp,int val)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  t6_tmpc1[lpp][cpp]=val;
  return(0);
}
int bw_print_bub::get_t6s_tmpc1(int lpp,char *p_s1,int len)
{
  int i,j;
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if (len>PAGE_COLU) i=PAGE_COLU;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t6_tmpc1[lpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_print_buc::get_t6_tmpc2(int lpp,int cpp)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  return(t6_tmpc2[lpp][cpp]);
}
int bw_print_buc::set_t6_tmpc2(int lpp,int cpp,int val)
{
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if ((cpp<0)||(cpp>=PAGE_COLU)) return(0);
  t6_tmpc2[lpp][cpp]=val;
  return(0);
}
int bw_print_buc::get_t6s_tmpc2(int lpp,char *p_s1,int len)
{
  int i,j;
  if ((lpp<0)||(lpp>=PAGE_LINE)) return(0);
  if (len>PAGE_COLU) i=PAGE_COLU;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t6_tmpc2[lpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
long bw_print_bua::get_t6_recno(int p_fcnt,int wpp)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(t6_recno[p_fcnt][wpp]);
}
int bw_print_bua::set_t6_recno(int p_fcnt,int wpp,long val)
{
  if ((p_fcnt<0)||(p_fcnt>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  t6_recno[p_fcnt][wpp]=val;
  return(0);
}            
int bw_print_bua::get_ts_field(int fpp,char *p_s1,int len)
{
  int i,j;
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if (len>10) i=10;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=ts_field[fpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_print_bua::set_ts_field(int fpp,char *p_s1,int len)
{
  int i,j;
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if (len>10) i=10;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    ts_field[fpp][j]=p_s1[j];
  }
  if (i>0) ts_field[fpp][i-1]=0;
  else ts_field[fpp][0]=0;
  return(0);
}
int bw_print_bua::set_ts_fieldc(int fpp,int cpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  if ((cpp<0)||(cpp>=10)) return(0);
  ts_field[fpp][cpp]=val;
  return(0);
}
int bw_print_bua::get_ts_fldseri(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(ts_fldseri[fpp]);
}
int bw_print_bua::set_ts_fldseri(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  ts_fldseri[fpp]=val;
  return(0);
}
int bw_print_bua::get_ts_base(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(ts_base[fpp]);
}
int bw_print_bua::set_ts_base(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  ts_base[fpp]=val;
  return(0);
}
int bw_print_bua::get_ts_recno(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  return(ts_recno[fpp]);
}
int bw_print_bua::set_ts_recno(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_PAGE)) return(0);
  ts_recno[fpp]=val;
  return(0);
}
int bw_print_bua::get_win_memo_print(int mpp)
{
  if ((mpp<0)||(mpp>=MEMO_NUM)) return(0);
  return(win_memo_print[mpp]);
}
int bw_print_bua::set_win_memo_print(int mpp,int val)
{
  if ((mpp<0)||(mpp>=MEMO_NUM)) return(0);
  win_memo_print[mpp]=val;
  return(0);
}
int bw_print_bua::get_win_print_fname(char *p_s1,int len)
{
  int i,j;
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_print_fname[j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_print_bua::set_win_print_fname(char *p_s1,int len)
{
  int i,j;
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_print_fname[j]=p_s1[j];
  }
  if (i>0) win_print_fname[i-1]=0;
  else win_print_fname[0]=0;
  return(0);
}

int bw_xbase_bua::get_win_state1(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state1[spp]);
}
int bw_xbase_bua::get_win_state4(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state4[spp]);
}
int bw_xbase_bua::get_win_state5(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state5[spp]);
}
int bw_xbase_bua::get_win_state7(int spp,int wpp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_state7[spp][wpp]);
}
int bw_xbase_bua::get_win_state9(int wpp,int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_state9[wpp][spp]);
}
int bw_xbase_bua::get_win_state10(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_state10[spp]);
}

int bw_xbase_bua::set_win_state1(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state1[spp]=val;
  return(0);
}
int bw_xbase_bua::set_win_state4(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state4[spp]=val;
  return(0);
}
int bw_xbase_bua::set_win_state5(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state5[spp]=val;
  return(0);
}
int bw_xbase_bua::set_win_state7(int spp,int wpp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_state7[spp][wpp]=val;
  return(0);
}
int bw_xbase_bua::set_win_state9(int wpp,int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_state9[wpp][spp]=val;
  return(0);
}
int bw_xbase_bua::set_win_state10(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_state10[spp]=val;
  return(0);
}

long bw_xbase_bua::get_win_recno(int spp,int wpp,int p02)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  return(win_recno[spp][wpp][p02]);
}
int bw_xbase_bua::set_win_recno(int spp,int wpp,int p02,long val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((p02<0)||(p02>2)) return(0);
  win_recno[spp][wpp][p02]=val;
  return(0);
}

long bw_xbase_bua::get_win_rcnt(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_rcnt[spp]);
}
int bw_xbase_bua::set_win_rcnt(int spp,long val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_rcnt[spp]=val;
  return(0);
}
int bw_xbase_bua::get_win_lcnt(int spp,int p01)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_lcnt[spp][p01]);
}
int bw_xbase_bua::set_win_lcnt(int spp,int p01,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_lcnt[spp][p01]=val;
  return(0);
}
int bw_xbase_bua::get_win_lnktab(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_lnktab[spp]);
}
int bw_xbase_bua::set_win_lnktab(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_lnktab[spp]=val;
  return(0);
}

int bw_xbase_bua::get_win_scrnvar(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_scrnvar[wpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::set_win_scrnvar(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_scrnvar[wpp][j]=p_s1[j];
  }
  if (i>0) win_scrnvar[wpp][i-1]=0;
  else win_scrnvar[wpp][0]=0;
  return(0);
}
int bw_xbase_bua::getc_win_scrnvar(int wpp,int pp1)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  return(win_scrnvar[wpp][pp1]);
}
int bw_xbase_bua::setc_win_scrnvar(int wpp,int pp1,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  win_scrnvar[wpp][pp1]=val;
  return(0);
}

int bw_get_bua::get_smg_line(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_line[gpp]);
}
int bw_get_bua::get_smg_colu(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_colu[gpp]);
}
int bw_get_bua::get_smg_data(int pp1)
{
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  return(smg_data[pp1]);
}
int bw_get_bua::gets_smg_data(char *p_s1,int len)
{
  int i,j;
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=smg_data[j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}
int bw_get_bua::get_smg_string(int gpp,char *p_s1,int len)
{
  int i,j;
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=smg_string[gpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_get_bua::getc_smg_string(int gpp,int pp1)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  return(smg_string[gpp][pp1]);
}
int bw_get_bua::get_smg_type(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_type[gpp]);
}
int bw_get_bua::get_smg_dlen(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_dlen[gpp]);
}
int bw_get_bua::get_smg_dlen2(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_dlen2[gpp]);
}
int bw_get_bua::get_smg_ddec(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_ddec[gpp]);
}
int bw_get_bua::get_smg_link(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_link[gpp]);
}
int bw_get_bua::get_smg_color(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_color[gpp]);
}
int * bw_get_bua::get_smg_posi(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_posi[gpp]);
}
int bw_get_bua::get_smg_atte(int gpp,char *p_s1,int len)
{
  int i,j;
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=smg_atte[gpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_get_bua::get_smg_read_id(int gpp)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  return(smg_read_id[gpp]);
}

int bw_get_bua::set_smg_line(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_line[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_colu(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_colu[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_data(int pp1,int val)
{
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  smg_data[pp1]=val;
  return(0);
}
int bw_get_bua::set_smg_type(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_type[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_dlen(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_dlen[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_dlen2(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_dlen2[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_ddec(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_ddec[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_link(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_link[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_color(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_color[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_posi(int gpp,int *val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_posi[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_read_id(int gpp,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  smg_read_id[gpp]=val;
  return(0);
}
int bw_get_bua::set_smg_string(int gpp,char *p_s1,int len)
{
  int i,j;
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    smg_string[gpp][j]=p_s1[j];
  }
  if (i>0) smg_string[gpp][i-1]=0;
  else   smg_string[gpp][0]=0;
  return(0);
}
int bw_get_bua::setc_smg_string(int gpp,int pp1,int val)
{
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  smg_string[gpp][pp1]=val;
  return(0);
}
int bw_get_bua::set_smg_atte(int gpp,char *p_s1,int len)
{
  int i,j;
  if ((gpp<0)||(gpp>=GET_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    smg_atte[gpp][j]=p_s1[j];
  }
  if (i>0) smg_atte[gpp][i-1]=0;
  else   smg_atte[gpp][0]=0;
  return(0);
}

int bw_xbase_bua::get_win_memno(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_memno[spp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::get_win_mem_ext(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>EXT_LEN) i=EXT_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_mem_ext[spp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::get_win_mem_fn(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_mem_fn[spp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::get_win_mem_inuse(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_mem_inuse[spp]);
}
int bw_xbase_bua::get_win_mem_wpp(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_mem_wpp[spp]);
}

int bw_xbase_bua::set_win_memno(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>MEM_FLD_LEN+3) i=MEM_FLD_LEN+3;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_memno[spp][j]=p_s1[j];
  }
  if (i>0) win_memno[spp][i-1]=0;
  else   win_memno[spp][0]=0;
  return(0);
}
int bw_xbase_bua::set_win_mem_ext(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>EXT_LEN) i=EXT_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_mem_ext[spp][j]=p_s1[j];
  }
  if (i>0) win_mem_ext[spp][i-1]=0;
  else   win_mem_ext[spp][0]=0;
  return(0);
}
int bw_xbase_bua::setc_win_mem_ext(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_mem_ext[spp][pp1]=val;
  return(0);
}
int bw_xbase_bua::set_win_mem_fn(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_mem_fn[spp][j]=p_s1[j];
  }
  if (i>0) win_mem_fn[spp][i-1]=0;
  else   win_mem_fn[spp][0]=0;
  return(0);
}
int bw_xbase_bua::setc_win_mem_fn(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_mem_fn[spp][pp1]=val;
  return(0);
}
int bw_xbase_bua::set_win_mem_inuse(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_mem_inuse[spp]=val;
  return(0);
}
int bw_xbase_bua::set_win_mem_wpp(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_mem_wpp[spp]=val;
  return(0);
}
int bw_xbase_bua::get_win_bmp_name(char *p_s1,int len)
{
  int i,j;
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_bmp_name[j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::set_win_bmp_name(char *p_s1,int len)
{
  int i,j;
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_bmp_name[j]=p_s1[j];
  }
  if (i>0) win_bmp_name[i-1]=0;
  else   win_bmp_name[0]=0;
  return(0);
}
int bw_xbase_bua::get_win_recvar(int rpp)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  return(win_recvar[rpp]);
}
int bw_xbase_bua::set_win_recvar(int rpp,int val)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  win_recvar[rpp]=val;
  return(0);
}
int bw_xbase_bua::get_win_recvar2(int rpp,int p01)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_recvar2[rpp][p01]);
}
int bw_xbase_bua::set_win_recvar2(int rpp,int p01,int val)
{
  if ((rpp<0)||(rpp>=REC_LEN)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_recvar2[rpp][p01]=val;
  return(0);
}
long bw_xbase_bua::read_win_recvar(int fh,long len)
{
  long rl;
  if (fh<0) return(0);
  if ((len<0)||(len>REC_LEN)) return(0);
  rl=read(fh,win_recvar,len);
  return(rl);
}
long bw_xbase_bua::write_win_recvar(int fh,long len)
{
  long wl;
  if (fh<0) return(0);
  if ((len<0)||(len>REC_LEN)) return(0);
  wl=write(fh,win_recvar,len);
  return(wl);
}
int bw_xbase_bua::fgets_win_recvar(FILE *fh,long len)
{
  if (fh==NULL) return(0);
  if ((len<0)||(len>REC_LEN)) return(0);
  fgets(win_recvar,len,fh);
  return(0);
}
int bw_xbase_bua::fputs_win_recvar(FILE *fh)
{
  if (fh==NULL) return(0);
  fputs(win_recvar,fh);
  return(0);
}
int bw_xbase_bua::get_win_basename(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_basename[spp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::set_win_basename(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_basename[spp][j]=p_s1[j];
  }
  if (i>0) win_basename[spp][i-1]=0;
  else   win_basename[spp][0]=0;
  return(0);
}
int bw_xbase_bua::setc_win_basename(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_basename[spp][pp1]=val;
  return(0);
}
int bw_xbase_bua::get_win_basedir(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_basedir[spp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::set_win_basedir(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_basedir[spp][j]=p_s1[j];
  }
  if (i>0) win_basedir[spp][i-1]=0;
  else   win_basedir[spp][0]=0;
  return(0);
}

int bw_xbase_bua::setc_win_basedir(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=FN_SIZE)) return(0);
  win_basedir[spp][pp1]=val;
  return(0);
}

int bw_xbase_bua::get_win_base_type(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_base_type[spp]);
}
int bw_xbase_bua::set_win_base_type(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_base_type[spp]=val;
  return(0);
}
int bw_xbase_bua::get_win_base_backup(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_base_backup[spp]);
}
int bw_xbase_bua::set_win_base_backup(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_base_backup[spp]=val;
  return(0);
}
int bw_xbase_bua::get_win_enseri(int spp,int wpp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_enseri[spp][wpp]);
}
int bw_xbase_bua::get_win_cuseri(int spp,int wpp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_cuseri[spp][wpp]);
}
int bw_xbase_bua::set_win_enseri(int spp,int wpp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_enseri[spp][wpp]=val;
  return(0);
}
int bw_xbase_bua::set_win_cuseri(int spp,int wpp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_cuseri[spp][wpp]=val;
  return(0);
}

int bw_xbase_bua::get_win_carry_on(int spp)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  return(win_carry_on[spp]);
}
int bw_xbase_bua::set_win_carry_on(int spp,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  win_carry_on[spp]=val;
  return(0);
}

int bw_xbase_bua::get_win_ext(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>EXT_LEN) i=EXT_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_ext[spp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::set_win_ext(int spp,char *p_s1,int len)
{
  int i,j;
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if (len>EXT_LEN) i=EXT_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_ext[spp][j]=p_s1[j];
  }
  if (i>0) win_ext[spp][i-1]=0;
  else   win_ext[spp][0]=0;
  return(0);
}
int bw_xbase_bua::setc_win_ext(int spp,int pp1,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_ext[spp][pp1]=val;
  return(0);
}

int bw_xbase_bua::get_win_fext(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>EXT_LEN) i=EXT_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_fext[wpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::setc_win_fext(int wpp,int pp1,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=EXT_LEN)) return(0);
  win_fext[wpp][pp1]=val;
  return(0);
}

long bw_xbase_bua::get_t4_recnumb(int p03)
{
  if ((p03<0)||(p03>3)) return(0);
  return(t4_recnumb[p03]);
}
int bw_xbase_bua::set_t4_recnumb(int p03,long val)
{
  if ((p03<0)||(p03>3)) return(0);
  t4_recnumb[p03]=val;
  return(0);
}

int bw_xbase_bua::get_t4_fldname(int fpp,char *p_s1,int len)
{
  int i,j;
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t4_fldname[fpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_xbase_bua::set_t4_fldname(int fpp,char *p_s1,int len)
{
  int i,j;
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t4_fldname[fpp][j]=p_s1[j];
  }
  if (i>0) t4_fldname[fpp][i-1]=0;
  else   t4_fldname[fpp][0]=0;
  return(0);
}

int bw_xbase_bua::get_t4_fldtype(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_fldtype[fpp]);
}
int bw_xbase_bua::get_t4_fldlen(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_fldlen[fpp]);
}
int bw_xbase_bua::get_t4_flddec(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_flddec[fpp]);
}
int bw_xbase_bua::get_t4_fldposi(int fpp)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  return(t4_fldposi[fpp]);
}

int bw_xbase_bua::set_t4_fldtype(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_fldtype[fpp]=val;
  return(0);
}
int bw_xbase_bua::set_t4_fldlen(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_fldlen[fpp]=val;
  return(0);
}
int bw_xbase_bua::set_t4_flddec(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_flddec[fpp]=val;
  return(0);
}
int bw_xbase_bua::set_t4_fldposi(int fpp,int val)
{
  if ((fpp<0)||(fpp>=FLD_IN_XBASE)) return(0);
  t4_fldposi[fpp]=val;
  return(0);
}

int bw_dialog_bua::get_win_mv_stor(int mlpp)
{
  if ((mlpp<0)||(mlpp>=MEM_LEN)) return(0);
  return(win_mv_stor[mlpp]);
}
int bw_dialog_bua::get_win_mv_posi(int mvpp,int p01)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(win_mv_posi[mvpp][p01]);
}
int bw_dialog_bua::get_win_mv_type(int mvpp,int p05)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p05<0)||(p05>5)) return(0);
  return(win_mv_type[mvpp][p05]);
}
int * bw_dialog_bua::get_win_mv_getp(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(&win_mv_getp[wpp]);
}
int bw_dialog_bua::getv_win_mv_getp(int wpp)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  return(win_mv_getp[wpp]);
}

int bw_dialog_bua::set_win_mv_stor(int mlpp,int val)
{
  if ((mlpp<0)||(mlpp>=MEM_LEN)) return(0);
  win_mv_stor[mlpp]=val;
  return(0);
}
int bw_dialog_bua::set_win_mv_posi(int mvpp,int p01,int val)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  win_mv_posi[mvpp][p01]=val;
  return(0);
}
int bw_dialog_bua::set_win_mv_type(int mvpp,int p05,int val)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p05<0)||(p05>5)) return(0);
  win_mv_type[mvpp][p05]=val;
  return(0);
}
int bw_dialog_bua::set_win_mv_getp(int wpp ,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  win_mv_getp[wpp]=val;
  return(0);
}

int bw_dialog_bua::get_win_mv_name(int mvpp,char *p_s1,int len)
{
  int i,j;
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_mv_name[mvpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_dialog_bua::set_win_mv_name(int mvpp,char *p_s1,int len)
{
  int i,j;
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_mv_name[mvpp][j]=p_s1[j];
  }
  if (i>0) win_mv_name[mvpp][i-1]=0;
  else   win_mv_name[mvpp][0]=0;
  return(0);
}
int bw_dialog_bua::setc_win_mv_name(int mvpp,int p0a,int val)
{
  if ((mvpp<0)||(mvpp>=MEM_VAR)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_mv_name[mvpp][p0a]=val;
  return(0);
}

int bw_dialog_bua::get_win_mv_getv(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_mv_getv[wpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_dialog_bua::set_win_mv_getv(int wpp,char *p_s1,int len)
{
  int i,j;
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if (len>SMG_LEN) i=SMG_LEN;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_mv_getv[wpp][j]=p_s1[j];
  }
  if (i>0) win_mv_getv[wpp][i-1]=0;
  else   win_mv_getv[wpp][0]=0;
  return(0);
}
int bw_dialog_bua::setc_win_mv_getv(int wpp,int pp1,int val)
{
  if ((wpp<0)||(wpp>=WIN_NUM)) return(0);
  if ((pp1<0)||(pp1>=SMG_LEN)) return(0);
  win_mv_getv[wpp][pp1]=val;
  return(0);
}

int bw_switch_bua::get_win_switch(int mpp,int p03)
{
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_switch[mpp][p03]);
}
int bw_switch_bua::set_win_switch(int mpp,int p03,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_switch[mpp][p03]=val;
  return(0);
}
int bw_switch_bua::get_win_switch_name(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_switch_name[mpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_switch_bua::set_win_switch_name(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_switch_name[mpp][j]=p_s1[j];
  }
  if (i>0) win_switch_name[mpp][i-1]=0;
  else   win_switch_name[mpp][0]=0;
  return(0);
}
int bw_switch_bua::setc_win_switch_name(int mpp,int p0a,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_RA)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_switch_name[mpp][p0a]=val;
  return(0);
}

int bw_choose_bua::get_win_choose(int cpp,int p03)
{
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  return(win_choose[cpp][p03]);
}
int bw_choose_bua::set_win_choose(int cpp,int p03,int val)
{
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if ((p03<0)||(p03>3)) return(0);
  win_choose[cpp][p03]=val;
  return(0);
}
int bw_choose_bua::get_win_choose_name(int cpp,char *p_s1,int len)
{
  int i,j;
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_choose_name[cpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_choose_bua::set_win_choose_name(int cpp,char *p_s1,int len)
{
  int i,j;
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_choose_name[cpp][j]=p_s1[j];
  }
  if (i>0) win_choose_name[cpp][i-1]=0;
  else   win_choose_name[cpp][0]=0;
  return(0);
}
int bw_choose_bua::setc_win_choose_name(int cpp,int p0a,int val)
{
  if ((cpp<0)||(cpp>=MENU_NUM_CHS)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  win_choose_name[cpp][p0a]=val;
  return(0);
}

int bw_menuvar_bua::get_t5_m_wind(int mpp)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  return(t5_m_wind[mpp]);
}
int bw_menuvar_bua::get_t5_m_mcnt(int mpp)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  return(t5_m_mcnt[mpp]);
}
int bw_menuvar_bua::set_t5_m_wind(int mpp,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  t5_m_wind[mpp]=val;
  return(0);
}
int bw_menuvar_bua::set_t5_m_mcnt(int mpp,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  t5_m_mcnt[mpp]=val;
  return(0);
}
int bw_menuvar_bua::get_t5_m_name(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t5_m_name[mpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_menuvar_bua::set_t5_m_name(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t5_m_name[mpp][j]=p_s1[j];
  }
  if (i>0) t5_m_name[mpp][i-1]=0;
  else   t5_m_name[mpp][0]=0;
  return(0);
}
int bw_menuvar_bua::setc_t5_m_name(int mpp,int p0a,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  t5_m_name[mpp][p0a]=val;
  return(0);
}

int bw_menuvar_bua::get_t5_m_butt(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>81) i=81;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t5_m_butt[mpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_menuvar_bua::set_t5_m_butt(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>81) i=81;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t5_m_butt[mpp][j]=p_s1[j];
  }
  if (i>0) t5_m_butt[mpp][i-1]=0;
  else   t5_m_butt[mpp][0]=0;
  return(0);
}
int bw_menuvar_bua::setc_t5_m_butt(int mpp,int pp1,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((pp1<0)||(pp1>80)) return(0);
  t5_m_butt[mpp][pp1]=val;
  return(0);
}

int bw_menuvar_bua::get_t5_m_comm(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>81) i=81;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t5_m_comm[mpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_menuvar_bua::set_t5_m_comm(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>81) i=81;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t5_m_comm[mpp][j]=p_s1[j];
  }
  if (i>0) t5_m_comm[mpp][i-1]=0;
  else   t5_m_comm[mpp][0]=0;
  return(0);
}
int bw_menuvar_bua::setc_t5_m_comm(int mpp,int pp1,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((pp1<0)||(pp1>80)) return(0);
  t5_m_comm[mpp][pp1]=val;
  return(0);
}

int bw_menuvar_bua::get_t5_m_focus(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>81) i=81;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t5_m_focus[mpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_menuvar_bua::set_t5_m_focus(int mpp,char *p_s1,int len)
{
  int i,j;
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if (len>81) i=81;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t5_m_focus[mpp][j]=p_s1[j];
  }
  if (i>0) t5_m_focus[mpp][i-1]=0;
  else   t5_m_focus[mpp][0]=0;
  return(0);
}
int bw_menuvar_bua::setc_t5_m_focus(int mpp,int pp1,int val)
{
  if ((mpp<0)||(mpp>=MENU_NUM_MN)) return(0);
  if ((pp1<0)||(pp1>80)) return(0);
  t5_m_focus[mpp][pp1]=val;
  return(0);
}

int bw_fldstru_bua::get_t2_fldpoin(int spp,int p01)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  return(t2_fldpoin[spp][p01]);
}
int bw_fldstru_bua::get_t2_fldtype(int fbpp)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  return(t2_fldtype[fbpp]);
}
int bw_fldstru_bua::get_t2_fldlen(int fbpp)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  return(t2_fldlen[fbpp]);
}
int bw_fldstru_bua::get_t2_flddec(int fbpp)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  return(t2_flddec[fbpp]);
}
int bw_fldstru_bua::get_t2_fldposi(int fbpp)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  return(t2_fldposi[fbpp]);
}

int bw_fldstru_bua::set_t2_fldpoin(int spp,int p01,int val)
{
  if ((spp<0)||(spp>=STRU_NUM)) return(0);
  if ((p01<0)||(p01>1)) return(0);
  t2_fldpoin[spp][p01]=val;
  return(0);
}
int bw_fldstru_bua::set_t2_fldtype(int fbpp,int val)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  t2_fldtype[fbpp]=val;
  return(0);
}
int bw_fldstru_bua::set_t2_fldlen(int fbpp,int val)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  t2_fldlen[fbpp]=val;
  return(0);
}
int bw_fldstru_bua::set_t2_flddec(int fbpp,int val)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  t2_flddec[fbpp]=val;
  return(0);
}
int bw_fldstru_bua::set_t2_fldposi(int fbpp,int val)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  t2_fldposi[fbpp]=val;
  return(0);
}

int bw_fldstru_bua::get_t2_fldname(int fbpp,char *p_s1,int len)
{
  int i,j;
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=t2_fldname[fbpp][j];
  }
  if (i>0) p_s1[i-1]=0;
  else   p_s1[0]=0;
  return(0);
}
int bw_fldstru_bua::set_t2_fldname(int fbpp,char *p_s1,int len)
{
  int i,j;
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  if (len>11) i=11;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    t2_fldname[fbpp][j]=p_s1[j];
  }
  if (i>0) t2_fldname[fbpp][i-1]=0;
  else   t2_fldname[fbpp][0]=0;
  return(0);
}
int bw_fldstru_bua::setc_t2_fldname(int fbpp,int p0a,int val)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  t2_fldname[fbpp][p0a]=val;
  return(0);
}
int bw_fldstru_bua::getc_t2_fldname(int fbpp,int p0a)
{
  if ((fbpp<0)||(fbpp>=FLD_IN_BASE)) return(0);
  if ((p0a<0)||(p0a>10)) return(0);
  return(t2_fldname[fbpp][p0a]);
}

int bw_win_bua::get_win_ci_mode(int wpp)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  return(win_ci_mode[wpp]);
}
int bw_win_bua::set_win_ci_mode(int wpp,int val)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  win_ci_mode[wpp]=val;
  return(0);
}

int bw_win_bua::get_win_ci_posi(int wpp,int p01)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1))       return(0);
  return(win_ci_posi[wpp][p01]);
}
int bw_win_bua::set_win_ci_posi(int wpp,int p01,int val)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((p01<0)||(p01>1))       return(0);
  win_ci_posi[wpp][p01]=val;
  return(0);
}

int bw_main_bua::get_win_face_bmp1(int p019,char *p_s1,int len)
{
  int i,j;
  if ((p019<0)||(p019>19)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    p_s1[j]=win_face_bmp1[p019][j];
  }
  if (i>0) p_s1[i-1]=0;
  else p_s1[0]=0;
  return(0);
}

int bw_main_bua::set_win_face_bmp1(int p019,char *p_s1,int len)
{
  int i,j;
  if ((p019<0)||(p019>19)) return(0);
  if (len>FN_SIZE) i=FN_SIZE;
  else i=len;
  for (j=0;j<i-1;j++)
  {
    win_face_bmp1[p019][j]=p_s1[j];
  }
  if (i>0) win_face_bmp1[p019][i-1]=0;
  else win_face_bmp1[p019][0]=0;
  return(0);
}
