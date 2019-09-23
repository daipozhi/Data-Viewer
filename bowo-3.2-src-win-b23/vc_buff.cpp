
#define STRICT
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

char bw_buff::get_tmpc1(int wpp,int line,int col)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(tmpc1[wpp][line][col]);
}

int bw_buff::set_tmpc1(int wpp,int line,int col,char val)
{
  if ((wpp<1)||(wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  tmpc1[wpp][line][col]=val;
  return(0);
}


