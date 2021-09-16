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
#include <dos.h>
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

extern class bw_main      bw_main1;

int bw_buff::get_t3_linecol(int p_wptr,int line,int col)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(t3_linecol[p_wptr][line][col]);
}

int bw_buff::set_t3_linecol(int p_wptr,int line,int col,int val)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  t3_linecol[p_wptr][line][col]=val;
  return(0);
}

char bw_buff::get_t3_winfile(int p_wptr,int line,int col)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(t3_winfile[p_wptr][line][col]);
}

int bw_buff::set_t3_winfile(int p_wptr,int line,int col,char val)
{
  if ((p_wptr<1)||(p_wptr>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  t3_winfile[p_wptr][line][col]=val;
  return(0);
}


