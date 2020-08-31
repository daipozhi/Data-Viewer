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

int bw_buff::get_linecol(int p_wpp,int line,int col)
{
  if ((p_wpp<1)||(p_wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(t_linecol[p_wpp][line][col]);
}

int bw_buff::set_linecol(int p_wpp,int line,int col,int val)
{
  if ((p_wpp<1)||(p_wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  t_linecol[p_wpp][line][col]=val;
  return(0);
}

char bw_buff::get_t_winfile(int p_wpp,int line,int col)
{
  if ((p_wpp<1)||(p_wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  return(t_winfile[p_wpp][line][col]);
}

int bw_buff::set_t_winfile(int p_wpp,int line,int col,char val)
{
  if ((p_wpp<1)||(p_wpp>=WIN_NUM)) return(0);
  if ((line<1)||(line>=LIN_NUM)) return(0);
  if ((col<1)||(col>=COL_NUM)) return(0);

  t_winfile[p_wpp][line][col]=val;
  return(0);
}


