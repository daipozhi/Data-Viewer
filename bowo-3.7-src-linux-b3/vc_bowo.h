//#define _CRT_SECURE_NO_WARNINGS

#define  CPY_BSIZE    20000 /* copy file buffer size      */
#define  FN_SIZE      256   /* file name size */
#define  GET_NUM      2000  /*   get_read subroutine var number */
#define  SMG_SIZE      300  /*   get_read var max len */
#define  ATTE_LEN     50    /*   atten text array */
#define  SUB_WIN_NUM  10

#define  MEM_FLD_LEN  80   // memory field lenght
#define  EXT_LEN      256  // extern file name lenght

#define  LIN_NUM      80   /* table's filed lines number */
#define  COL_NUM      300  /* colunm number */
#define  WIN_NUM      32   /* windows number for table data */
#define  REC_LEN      100000 /* one record max len */
#define  STRU_NUM     10    /* stru number in one win     */
#define  MENU_NUM_RA  200   /* multi select menu num */
#define  MENU_NUM_CHS 200   /* choose menu number */
#define  MENU_NUM_MN  200   /* single select menu num */
#define  FLD_IN_SCRN  10000 /* field number in one win */
#define  FLD_NAME_LEN 21    // fld name len
#define  FLD_IN_BASE  5000   /* field in some base number */
#define  FLD_IN_XBASE 5000   /* field number in single file*/
                            /* link tab define */
#define  VAR_IN_SCRN   640000 /* all var in screen store */
#define  WIN_VAR_NUM   20000 /* scrn base var num */
#define  LINK_CHAR     400  /* link condition    */
#define  COND_NUM      60   /* conditi num       */
#define  LINK_MODI_NUM 100  /* link var modi num */
                            /* calc func define  */
#define  VAL_NUM      60    /* calc cond var buff*/
#define  FUNC_NUM     100   /* function number   */
#define  FUNC_VARN    300   /* condi var num     */
#define  FUNC_LEN     2000  /* function char len */

#define  PAGE_NUM   4
//#define  PAGE_LIN   81
//#define  PAGE_COL   300

#define  FONT_NUM   100

#define  F10        310
#define  BACKSP     127
#define  RET_KEY    10
#define  TAB_KEY    9
#define  CTRL_B     2
#define  CTRL_K     11
#define  CTRL_I     9
#define  CTRL_L     12
#define  CTRL_Q     17
#define  CTRL_O     15
#define  CTRL_T     20
#define  CTRL_Y     25
#define  CTRL_C     3
#define  CTRL_V     22
#define  CTRL_E     5
#define  CTRL_H     8
#define  CTRL_F     6   /* find condition */
#define  CTRL_N     14  /* no find condit */
#define  CTRL_R     18  /* rollback    */
#define  CTRL_W     23  /* commit      */
#define  CTRL_Y     25  /* dele line in edit */
#define  CTRL_D     4   /* dele record */
#define  CTRL_A     1   /* insert rec  */
#define  CTRL_P     16  /* print data  */
#define  F1_KEY     321 /* edit memo   */
#define  F2_KEY     322 /* run ole     */
#define  F3_KEY     323 /* edit memo   */
#define  F4_KEY     324 /* run ole     */
#define  F5_KEY     325 /* edit memo   */
#define  F6_KEY     326 /* run ole     */
#define  ESC_KEY    27  /* close win   */
#define  LEFT_ROW   276
#define  RIGHT_ROW  277
#define  UP_ROW     274
#define  DOWN_ROW   275
#define  INSERT     312
#define  DEL_KEY    313
#define  PG_UP      315 /* page up     */
#define  PG_DOWN    316 /* page down   */
#define  FIND       317 /* start find  */
#define  SELECT     318 /* open window */

#define  HND_NUM       500 /* control item id num */
#define  WIN_STYLE_NUM 20  /* control item style num */

#define MEM_VAR  2000
#define MEM_LEN  30000

#define EDIT_NUM 10        /* max edit windows number */

#define  FLD_IN_PAGE  5000  /* print format field number */
#define  PAGE_LINE    81    /* page char number per line */
#define  PAGE_COLU    300   /* page lines number      */
#define  MEMO_NUM     10    /* memo field num per rec */

#define  BMP_BUFF_SIZE 64000




#define  PRINT_FORM_NUM 10
#define  VAR_IN_PAGE/*VAR_IN_SCRN*/   64000 /* all var in screen store */
#define  PRT_VAR_NUM/*WIN_VAR_NUM*/   20000 /* scrn base var num */

class bw_buff
{
  private:

    int        t_linecol[WIN_NUM][LIN_NUM][COL_NUM];

  public:

    int        get_linecol(int p_wpp,int line,int col);
    int        set_linecol(int p_wpp,int line,int col,int val);
/*
};

class bw_buffa
{
*/
  private:

    char       t_winfile[WIN_NUM][LIN_NUM][COL_NUM];

  public:

    char       get_t_winfile(int p_wpp,int line,int col);
    int        set_t_winfile(int p_wpp,int line,int col,char val);
};

class bw_font
{
  public:

    int   win_font_pp1;

  public:

    int   w_font_ini(void);
    int   w_read_fdc(char *p_fn1,int p_fn1_size,int p_wpp);
    int   w_dele_font(int wp1,int wp2);
    int   tst_font(void);
/*
};

class bw_font_bua
{
*/
  private:

    char  win_font_name[FONT_NUM][11];

    int   win_font[FONT_NUM][4];  /* in use,pre val,seri,win num */

};

class bw_user
{
  public:

    int w_user_triger(char *winname,int size1,char *msg,int size2,char *itemname,int size3,char *state,int size4);
};

class bw_bmp
{
  public:

    int mx;
    int my;

    HPALETTE hPalCurrent;
    HGLOBAL  hbiCurrent;
    BOOL     fPalColors;
    DWORD    dwOffSet;

    HWND     win_bmp_hnd;

  private:

    HGLOBAL  ReadDibBitmapInfo(int fh);
    int      DibInfo(HGLOBAL hbi,LPBITMAPINFOHEADER lpbi);
    HPALETTE CreateDIBPalette(LPBITMAPINFOHEADER lpbi);
    WORD     DibNumColors(LPBITMAPINFOHEADER lpbi);

  public:

    int      DIB(char *bfn,int bfn_size);
    BOOL     DisplayDIB(HWND hwnd,int x,int y,LPSTR szFile);
    BOOL     PaintDIB(HWND hwnd,int x,int y,int h,LPSTR szFile);
    int      echo_bmp(HWND hwnd,char *comm,int comm_size,int mcnt,int p_wpp);

    int      w_bmp_add(int p_fpp,int p_wpp,char *fldname,int fldname_size);
    int      w_bmp_paint(HWND hwnd);

    int      tst_b1(void);
};

class bw_print
{
  private:

    char          texts1[20];
    char          texts2[20];
    char          texts3[20];
    char          texts4[20];
    char          texts5[20];
    char          texts6[20];
    char          texts7[20];
    char          texts8[20];

    char  win_pv[VAR_IN_PAGE];
    int   win_pvused[PRT_VAR_NUM];
    int   win_pvpoin[PRT_VAR_NUM][2];
    int   win_pvseri[PRT_VAR_NUM];
    int   win_pvrecn[PRT_VAR_NUM];
    int   win_pvbase[PRT_VAR_NUM];
    int   win_pvwind[PRT_VAR_NUM];

  public:

    int         t6_pp1;
    int         t6_page_num;
    int         t6_wdir;

  public:

    FILE       *txt_out_fp1;
    FILE       *txt_out_fp2[MEMO_NUM];

    int         win_memo_left,win_memo_leng;

    int         p1,p2,p3,p4;

  public:

    int         win_print_xchar;
    int         win_print_ychar;
    int         win_page_num;

    DOCINFO     win_print_inf;
    HWND        win_savep_hnd;
    HWND        win_outp_hnd;

  public:

    int w_out_win_print(void);
    int w_out_linux_print(void);
    int w_close_opwin(void);
    int w_close_spwin(void);
    int w_open_print_file(char *p_s1,int p_s1_size);
    int w_close_print_file(void);
    int w_read_page(char *p_fn2,int p_fn2_size,int page);
    int w_page_field1(void);
    int w_page_field2(int p_wpp);
    int w_fld_set_edit(char *p_fldname,int p_fldname_size);
    int w_print_page(int page,int form,int p_wpp);
    int w_print_memo(int o);
    int w_open_memo_print(char *s1,int s1_size);
    int w_fetch_memo_size(int l,int c);
    int w_read_memo(char *s1,int s1_size,int m5);
    int w_put_memo_char(int l,char *s1,int s1_size);
    int w_close_memo_print(int m5);
    int w_save_print(void);
    int w_save_memo(void);
    int w_out_print(char *s1,int s1_size);
    int w_cnt_pageline(int basep,int ln);
    int w_find_pagefld(int i,int j);
    int w_print_lnk(int p_wpp);
    int w_print_cal(void);
    int w_print_read(void);
    int w_scan_pagevar(void);
    int w_print_echo1(HWND hwnd);
    int w_print_echo2(HWND hwnd);

  public:

    int w_print(int p_wpp,char *s1,int s1_size);       /* public*/
    int w_read_setup(void);              /* public*/

    int tst_p1(void);
    int tst_p2(void);
    int tst_p3(void);




    int w_print_page_down(int p_fpp,int p_wpp);
    int w_print_link_cond_ok(int condnum,int p_wpp,int basep,int recn,int page);
    int w_scan_pv(int p_wpp);
    int w_save_pv(int p_wpp,int base,int seri,int recn,int posi,int len);  /*save scrn var to arr*/
    int w_get_pv(int p_wpp,int base,int seri,int recn,char *p_str,int p_str_size);  /*save scrn var to arr*/
    int get_win_pv(int spp);
    int set_win_pv(int spp,int val);
    int get_win_pvused(int vpp);
    int set_win_pvused(int vpp,int val);
    int get_win_pvpoin(int vpp,int p01);
    int set_win_pvpoin(int vpp,int p01,int val);
    int get_win_pvseri(int vpp);
    int set_win_pvseri(int vpp,int val);
    int get_win_pvrecn(int vpp);
    int set_win_pvrecn(int vpp,int val);
    int get_win_pvbase(int vpp);
    int set_win_pvbase(int vpp,int val);
    int get_win_pvwind(int vpp);
    int set_win_pvwind(int vpp,int val);


    int get_setup_print(void);

/*
};

class bw_print_bua
{
*/
/* t6_ t5_ t4_ t2_ t_ t7_is module name */

  private:

    int   t6_linecol[FLD_IN_PAGE][3];

    char  t6_fldname[FLD_IN_PAGE][21];
    char  t6_fldtype[FLD_IN_PAGE];
    char  t6_fldedit[FLD_IN_PAGE];
    char  t6_fldbase[FLD_IN_PAGE];
    char  t6_fldseri[FLD_IN_PAGE];
    int   t6_fldlen[FLD_IN_PAGE];
    int   t6_flddec[FLD_IN_PAGE];

    int   t6_recno[STRU_NUM][PRINT_FORM_NUM];
    int   t6_eof[STRU_NUM][PRINT_FORM_NUM];

    int   t7_fldseri[FLD_IN_PAGE];
    char  t7_field[FLD_IN_PAGE][10];
    int   t7_base[FLD_IN_PAGE];
    int   t7_recno[FLD_IN_PAGE];

    int   win_memo_print[MEMO_NUM];

    char  win_print_fname[SMG_SIZE];

  public:

    int   get_t6_linecol(int fpp,int p02);
    int   set_t6_linecol(int fpp,int p02,int val);

    int   get_t6c_fldname(int fpp,int pp1);
    int   set_t6c_fldname(int fpp,int pp1,int val);

    int   get_t6_fldname(int fpp,char *s1,int s1_size);
    int   set_t6_fldname(int fpp,char *s1,int s1_size);
    int   get_t6_fldtype(int fpp);
    int   set_t6_fldtype(int fpp,int val);
    int   get_t6_fldedit(int fpp);
    int   set_t6_fldedit(int fpp,int val);
    int   get_t6_fldbase(int fpp);
    int   set_t6_fldbase(int fpp,int val);
    int   get_t6_fldseri(int fpp);
    int   set_t6_fldseri(int fpp,int val);
    int   get_t6_fldlen(int fpp);
    int   set_t6_fldlen(int fpp,int val);
    int   get_t6_flddec(int fpp);
    int   set_t6_flddec(int fpp,int val);

    long  get_t6_recno(int p_fpp,int form);
    int   set_t6_recno(int p_fpp,int form,long val);

    int   get_t6_eof(int p_fpp,int form);
    int   set_t6_eof(int p_fpp,int form,int val);

    int   get_t7_field(int fpp,char *s1,int s1_size);
    int   set_t7_field(int fpp,char *s1,int s1_size);

    int   set_t7_fieldc(int fpp,int cpp,int val);

    int   get_t7_fldseri(int fpp);
    int   set_t7_fldseri(int fpp,int val);
    int   get_t7_base(int fpp);
    int   set_t7_base(int fpp,int val);
    int   get_t7_recno(int fpp);
    int   set_t7_recno(int fpp,int val);

    int   get_win_memo_print(int mpp);
    int   set_win_memo_print(int mpp,int val);

    int   get_win_print_fname(char *s1,int s1_size);
    int   set_win_print_fname(char *s1,int s1_size);
/*
};

class bw_print_bub
{
*/
  private:

    char t6_pagefile[PAGE_LINE][PAGE_COLU];

  public:

    int  get_t6_pagefile(int lpp,int cpp);
    int  set_t6_pagefile(int lpp,int cpp,int val);
    int  get_t6s_pagefile(int lpp,char *s1,int s1_size);
/*
};

class bw_print_buc
{
*/
  private:

    char t6_tmps2[PAGE_LINE][PAGE_COLU];

  public:

    int  get_t6_tmps2(int lpp,int cpp);
    int  set_t6_tmps2(int lpp,int cpp,int val);
    int  get_t6s_tmps2(int lpp,char *ps1,int ps1_size);
};

class bw_edit
{
  public:

    int  win_edit_pp1;

  public:

    int  get_edit(char *fn,int fn_size,int wpp,HWND hwnd);
    int  w_find_edithand(HWND hwnd);
    int  w_ini_edit(void);
/*
};

class bw_edit_bua
{
*/
  private:

    HWND win_edit_hnd1[EDIT_NUM];
    HWND win_edit_hnd2[EDIT_NUM];
    char win_edit_dirn[EDIT_NUM][FN_SIZE];
    char win_edit_file[EDIT_NUM][FN_SIZE];
    int  win_edit_modi[EDIT_NUM];
    int  win_edit_inuse[EDIT_NUM];
    int  win_edit_wpp[EDIT_NUM];

  public:

    HWND get_win_edit_hnd1(int epp);
    int  set_win_edit_hnd1(int epp,HWND hwnd);
    HWND get_win_edit_hnd2(int epp);
    int  set_win_edit_hnd2(int epp,HWND hwnd);
    int  get_win_edit_dirn(int epp,char *s1,int s1_size);
    int  set_win_edit_dirn(int epp,char *s1,int s1_size);
    int  get_win_edit_file(int epp,char *s1,int s1_size);
    int  set_win_edit_file(int epp,char *s1,int s1_size);
    int  tst_dirn_file(void);
    int  get_win_edit_modi(int epp);
    int  set_win_edit_modi(int epp,int val);
    int  get_win_edit_inuse(int epp);
    int  set_win_edit_inuse(int epp,int val);
    int  get_win_edit_wpp(int epp);
    int  set_win_edit_wpp(int epp,int val);

};

class bw_link
{

  public:

    int w_dele_link(int wp1,int wp2);
    int w_dele_svar(int wp1,int wp2);
    int w_read_link(char *fn,int fn_size,int p_wpp,int num);
    int w_find_link_tn(char *tmpc1,int tmpc1_size,int p_wpp,int i);
    int w_find_link_cd(char *tmpc1,int tmpc1_size,int i,int k);
    int w_link_modi(int p_wpp);      /* fetch link var in cond & link var if modi */
    int w_fetch_link_var(int p1,int p2,char *s1,int s1_size);
    int w_fetch_link_var2(int p1,int p2,char *s1,int s1_size);
    int w_link_modi_set(char *tn,int tn_size,char *fn,int fn_size,int p1,int p_wpp);
    int w_link_modi_mark(int p_wpp,int mark,int seri,int recn);   /* echo win rec ,link rec should change */
    int w_link_modi_unmark(int p_wpp,int mark,int seri,int recn);   /* echo win rec ,link rec should change */
    int w_echo_winrec_lnk(int p_wpp);        /* echo win rec where modified */
    int w_link_modified(int p_wpp,int basep);
    int w_link_cond_ok(int condnum,int p_wpp,int basep,int recn,int page);
    int w_is_calc(char *s1);
    int w_name_t1_t2(char *s1,int basep);
    int w_scan_sv(int p_wpp);
    int w_save_sv(int p_wpp,int base,int seri,int recn,int posi,int len);
    int w_get_sv(int p_wpp,int base,int seri,int recn,char *str,int str_size);
    int w_link_type(int p_wpp,int basep);
    int w_link_number(int p_wpp,int basep);
    int w_link_base_num(int p_wpp,int basep);
    int w_link_set_continue(int p_wpp,int basep);
    int w_keep_linkfld(int p_wpp,int p_fpp,int dir);

    int tst_link1(void);
    int tst_link2(void);
    int tst_link3(void);
    int tst_link4(void);
    int tst_link5(void);
/*
};

class bw_link_bua
{
*/
  private:

    char  win_svar[VAR_IN_SCRN];

    int   win_svused[WIN_VAR_NUM];
    int   win_svpoin[WIN_VAR_NUM][2];
    int   win_svseri[WIN_VAR_NUM];
    int   win_svrecn[WIN_VAR_NUM];
    int   win_svbase[WIN_VAR_NUM];
    int   win_svwind[WIN_VAR_NUM];

    char  win_chlink[LINK_CHAR];     

    int   win_bslink[COND_NUM][3];   /* base to base & p_wpp */
    int   win_bspoin[COND_NUM][2];   /* link cond char poin */

    int   win_lkpoin[COND_NUM][2];   /* modi var poin */
    char  win_lkmodi[LINK_MODI_NUM]; /* modi var state*/
    int   win_lkseri[LINK_MODI_NUM]; /* modi var seri */
    char  win_lkbase[LINK_MODI_NUM]; /* modi var base */
    int   win_lkrecn[LINK_MODI_NUM]; /* modi var recno*/
    int   win_lkwind[LINK_MODI_NUM]; /* modi var window */

    int   win_continue[STRU_NUM][WIN_NUM];/* continue link data page */

    char  win_bb1[VAL_NUM][SMG_SIZE];  /* val buff  */
    char  win_bb2[VAL_NUM];       /* calc char */
    char  win_bb3[VAL_NUM];       /* val type  */


  public:

    int   get_win_svar(int spp);
    int   set_win_svar(int spp,int val);
    int   get_win_svused(int vpp);
    int   set_win_svused(int vpp,int val);
    int   get_win_svpoin(int vpp,int p01);
    int   set_win_svpoin(int vpp,int p01,int val);
    int   get_win_svseri(int vpp);
    int   set_win_svseri(int vpp,int val);
    int   get_win_svrecn(int vpp);
    int   set_win_svrecn(int vpp,int val);
    int   get_win_svbase(int vpp);
    int   set_win_svbase(int vpp,int val);
    int   get_win_svwind(int vpp);
    int   set_win_svwind(int vpp,int val);

    int   get_win_chlink(int lpp);
    int   set_win_chlink(int lpp,int val);
    int   get_win_bslink(int dpp,int p02);
    int   set_win_bslink(int dpp,int p02,int val);
    int   get_win_bspoin(int dpp,int p01);
    int   set_win_bspoin(int dpp,int p01,int val);

    int   get_win_lkpoin(int cpp,int p01);
    int   set_win_lkpoin(int cpp,int p01,int val);
    int   get_win_lkmodi(int lpp);
    int   set_win_lkmodi(int lpp,int val);
    int   get_win_lkseri(int lpp);
    int   set_win_lkseri(int lpp,int val);
    int   get_win_lkbase(int lpp);
    int   set_win_lkbase(int lpp,int val);
    int   get_win_lkrecn(int lpp);
    int   set_win_lkrecn(int lpp,int val);
    int   get_win_lkwind(int lpp); 
    int   set_win_lkwind(int lpp,int val);

    int   get_win_continue(int p_fpp,int p_wpp);
    int   set_win_continue(int p_fpp,int p_wpp,int val);

    int   set_win_cbb1(int vpp,int pp1,int val);

    int   get_win_bb1(int vpp,char *s1,int s1_size);
    int   set_win_bb1(int vpp,char *s1,int s1_size);
    int   get_win_bb2(int vpp);
    int   set_win_bb2(int vpp,int val);
    int   get_win_bb3(int vpp);  
    int   set_win_bb3(int vpp,int val);


};

class bw_mbase
{
  public:

    int  w_open_base(char *bn,int bn_size,int p_fpp);
    int  w_close_base(int p_fpp,int p_wpp);

    long w_down_rec(int p_fpp,int p_wpp,long recno);
    long   w_up_rec(int p_fpp,int p_wpp,long recno);
    int  w_save_rec(int p_fpp,int p_wpp,long recno);
    int   w_ins_rec(int p_fpp,int p_wpp,long recno);
    long  w_add_rec(int p_fpp,int p_wpp,long recno);
    int   w_del_rec(int p_fpp,int p_wpp,long recno);
};

class bw_xbase
{
  public:

    int  win_answer;
    int  win_insert_dir;
    int  win_state_dbf_err; //win_state3;           /* error mark */

    int  win_fp2[WIN_NUM];

  private:

    int  win_fp[STRU_NUM];

  private:

    char  t4_eof;
    char  t4_bof;
    int   win_use_fh;

  public:

    //int  get_xbase_open(int p_fpp,char *s1,int l1,char *s2,int l2);
    //int  get_xbase_close(int p_fpp);

    int  tst_xbase1(void);
    int  tst_xbase2(void);

    long w_read_recno(int fp);
    int  w_open_xbase(char *p_fn1,int p_fn1_size,int backup,int p_fpp);
    int  w_close_xbase(int p_fpp);
    int  w_login_xbase(int pp);
    int  w_free_xbase(void);
    int  w_dele_state(int p_fpp);
    int  w_create_xbase(char *p_fn12,int p_fn12_size,int p_fpp);
    int  w_compare_xbase(int p_fp,int p_fpp);
    int  w_read_xbase_rec(long recno,int p_fpp);
    int  w_save_xbase_rec(long recno,int p_fpp);
    int  w_append_xbase_rec(long recno,int p_fpp);
    int  w_append_xbase_rec2(int p_fpp);
    int  w_loc_xbase_rec(long recno,int p_fpp);
    long w_up_xbase_rec(long recno,int p_fpp);
    long w_down_xbase_rec(long recno,int p_fpp);
    int  w_xbase_rec_del(void);
    int  w_dele_xbase_rec(long recno,int p_fpp);
    int  w_insert_xbase_rec(long recno,int p_fpp,int aft);
    int  w_insert_xbase_rec2(int p_fpp);
    int  w_pack_xbase_base(int p_fpp);
    int  w_set_xbase_recno(long recno,int p_fpp);
    int  w_set_fox_recno2(long recno,int p_fp);
    int  w_commit_xbase(int backup,int p_fpp);
    int  w_rollback_xbase(/*char *p_fn1,int p_fn1_size,*/int backup,int p_fpp);
    int  w_append_sdf(char *p_fn,int p_fn_size,int p_fpp);
    int  w_copy_sdf(char *p_fn,int p_fn_size,int p_fpp);
    int  w_zap_xbase(int p_fpp);
    int  w_clr_recvar(int p_fpp);
    int  w_find_empty_file(char *str,int str_size,int p_fpp);
    int  w_find_empty_ffile(char *str,int str_size,int p_wpp);
    int  w_find_empty_mfile(char *str,int str_size,int p_fpp);
    int  w_use_fox(char *fn1,int fn1_size);
    int  w_append_fox(int p_fpp);
    int  w_go_fox(long r);
    int  w_close_fox(void);
    int  w_bcpy_var(int p_fpp,char *p_fld,int p_fld_size,char *p_stc4,int p_stc4_size);
    int  w_bsav_var(int p_fpp,char *p_fld,int p_fld_size,char *p_stc4,int p_stc4_size);
    int  w_there_is_a(char *s,int s_size);
/*
};

class bw_xbase_bua
{
*/
  private:

    int  win_state_bff_in_use[STRU_NUM]; /* base in use */
    //int  win_state4[STRU_NUM]; /* current rec modified */
    int  win_state_dbf_modi[STRU_NUM]; /* base modified */
    //int  win_state7[STRU_NUM][WIN_NUM];  /* finding mark */
    int  win_state_in_srch[WIN_NUM][STRU_NUM];  /* finding file is open this win*/
    //int  win_state10[STRU_NUM]; /* finding file basep*/

    long win_recno[STRU_NUM][WIN_NUM][3];
    long win_rcnt[STRU_NUM];
    int  win_lcnt[STRU_NUM][2]; /*field number,record len */
    int  win_lnktab[STRU_NUM];

    char win_scrnvar[WIN_NUM][SMG_SIZE];

    char win_memno[STRU_NUM][MEM_FLD_LEN+3];
    char win_mem_ext[STRU_NUM][EXT_LEN];
    char win_mem_fn[STRU_NUM][FN_SIZE];
    int  win_mem_inuse[STRU_NUM];
    int  win_mem_wpp[STRU_NUM];

    char win_bmp_name[SMG_SIZE];
    char win_recvar[REC_LEN];
    char win_recvar2[REC_LEN][2];

    char win_basename[STRU_NUM][FN_SIZE];
    char win_basedir[STRU_NUM][FN_SIZE];

    int  win_base_type[STRU_NUM];
    int  win_base_backup[STRU_NUM];

    int  win_enseri[STRU_NUM][WIN_NUM];
    int  win_cuseri[STRU_NUM][WIN_NUM];

    int  win_carry_on[STRU_NUM];

    char win_ext[STRU_NUM][EXT_LEN];

    char win_fext[WIN_NUM][EXT_LEN];

    long t4_recnumb[4]; /* 0-reccnt,1-fldnum,2-reclen,3-recno */
    char t4_fldname[FLD_IN_XBASE][10+1];
    int  t4_fldtype[FLD_IN_XBASE];
    int  t4_fldlen[FLD_IN_XBASE];
    int  t4_flddec[FLD_IN_XBASE];
    int  t4_fldposi[FLD_IN_XBASE];

  public:

    int  get_win_state_bff_in_use(int spp);
    //int  get_win_state4(int spp);
    int  get_win_state_dbf_modi(int spp);
    //int  get_win_state7(int spp,int p_wpp);
    int  get_win_state_in_srch(int p_wpp,int spp);
    //int  get_win_state10(int spp);

    int  set_win_state_bff_in_use(int spp,int val);
    //int  set_win_state4(int spp,int val);
    int  set_win_state_dbf_modi(int spp,int val);
    //int  set_win_state7(int spp,int p_wpp,int val);
    int  set_win_state_in_srch(int p_wpp,int spp,int val);
    //int  set_win_state10(int spp,int val);

    long get_win_recno(int spp,int p_wpp,int p02);
    int  set_win_recno(int spp,int p_wpp,int p02,long val);

    long get_win_rcnt(int spp);
    int  set_win_rcnt(int spp,long val);
    int  get_win_lcnt(int spp,int p01);
    int  set_win_lcnt(int spp,int p01,int val);
    int  get_win_lnktab(int spp);
    int  set_win_lnktab(int spp,int val);

    int  get_win_scrnvar(int p_wpp,char *s1,int s1_size);
    int  set_win_scrnvar(int p_wpp,char *s1,int s1_size);
    int  getc_win_scrnvar(int p_wpp,int pp1);
    int  setc_win_scrnvar(int p_wpp,int pp1,int val);

    int  get_win_memno(int spp,char *s1,int s1_size);
    int  get_win_mem_ext(int spp,char *s1,int s1_size);
    int  get_win_mem_fn(int spp,char *s1,int s1_size);
    int  get_win_mem_inuse(int spp);
    int  get_win_mem_wpp(int spp);

    int  set_win_memno(int spp,char *s1,int s1_size);
    int  set_win_mem_ext(int spp,char *s1,int s1_size);
    int  setc_win_mem_ext(int spp,int pp1,int val);
    int  set_win_mem_fn(int spp,char *s1,int s1_size);
    int  setc_win_mem_fn(int spp,int pp1,int val);
    int  set_win_mem_inuse(int spp,int val);
    int  set_win_mem_wpp(int spp,int val);

    int  get_win_bmp_name(char *s1,int s1_size);
    int  set_win_bmp_name(char *s1,int s1_size);

    int  get_win_recvar(int rpp);
    int  set_win_recvar(int rpp,int val);
    int  get_win_recvar2(int rpp,int p01);
    int  set_win_recvar2(int rpp,int p01,int val);
    long read_win_recvar(int fh,long len);
    long write_win_recvar(int fh,long len);
    int  fgets_win_recvar(FILE *fh,long len);
    int  fputs_win_recvar(FILE *fh);

    int  get_win_basename(int spp,char *s1,int s1_size);
    int  set_win_basename(int spp,char *s1,int s1_size);
    int  setc_win_basename(int spp,int pp1,int val);
    int  get_win_basedir(int spp,char *s1,int s1_size);
    int  set_win_basedir(int spp,char *s1,int s1_size);
    int  setc_win_basedir(int spp,int pp1,int val);

    int  get_win_base_type(int spp);
    int  set_win_base_type(int spp,int val);
    int  get_win_base_backup(int spp);
    int  set_win_base_backup(int spp,int val);

    int  get_win_enseri(int spp,int p_wpp);
    int  get_win_cuseri(int spp,int p_wpp);
    int  set_win_enseri(int spp,int p_wpp,int val);
    int  set_win_cuseri(int spp,int p_wpp,int val);

    int  get_win_carry_on(int spp);
    int  set_win_carry_on(int spp,int val);

    int  get_win_ext(int spp,char *s1,int s1_size);
    int  set_win_ext(int spp,char *s1,int s1_size);
    int  setc_win_ext(int spp,int pp1,int val);

    int  get_win_fext(int p_wpp,char *s1,int s1_size);
    int  setc_win_fext(int p_wpp,int pp1,int val);

    long get_t4_recnumb(int p03); 
    int  set_t4_recnumb(int p03,long val);

    int  get_t4_fldname(int fpp,char *s1,int s1_size);
    int  set_t4_fldname(int fpp,char *s1,int s1_size);

    int  get_t4_fldtype(int fpp);
    int  get_t4_fldlen(int fpp);
    int  get_t4_flddec(int fpp);
    int  get_t4_fldposi(int fpp);

    int  set_t4_fldtype(int fpp,int val);
    int  set_t4_fldlen(int fpp,int val);
    int  set_t4_flddec(int fpp,int val);
    int  set_t4_fldposi(int fpp,int val);
};

class bw_main
{
  public:

    char          win_face_bmp0[FN_SIZE];
    int           win_face_pp2;

    OPENFILENAME  dlg_f1;
    PRINTDLG      dlg_f2;

    int        win_color;
    int        win_confirm;
    int        win_field_posi;
    int        win_var_ci;
    int        win_cre_ok;
    int        win_cre_menu;

    int        win_main_xsize;
    int        win_main_ysize;
    int        win_main_xposi;
    int        win_main_yposi;

    int        win_lang;
    int        win_800;
    int        win_ibm_s3;

    HWND       win_main_hnd;
    int        win_hnd_id;

    int        win_xchar;
    int        win_ychar;
    float      win_edit_xchar;
    float      win_edit_ychar;
    int        win_key;
    int        win_key1;
    int        win_key2;

    HINSTANCE  win_ins;
    HINSTANCE  win_pins;
    LPSTR      win_cl;
    UINT       win_msg;
    WPARAM     win_wp;
    LPARAM     win_lp;
    HWND       win_hwnd;
    HWND       win_hwnd1;
    int        win_show;

    HFONT      holdfont,hfont;
    HCURSOR    hcursor;
    HDC        hdc,hdc2;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    RECT        rt;
    MSG         msg;

    char   win_m_bs1[FN_SIZE];
    char   win_m_bs2[FN_SIZE];
    char   win_m_bs3[FN_SIZE];

    char   win_m_ts0[FN_SIZE];
    char   win_m_ts1[FN_SIZE];
    char   win_m_ts2[FN_SIZE];
    char   win_m_ts3[FN_SIZE];
    char   win_m_ts4[FN_SIZE];
    char   win_m_ts5[FN_SIZE];
    char   win_m_ts6[FN_SIZE];
    char   win_m_ts7[FN_SIZE];

    char win_cpy_f1[FN_SIZE];
    char win_cpy_f2[FN_SIZE];
    char win_seaname[FN_SIZE];
    char win_seadir[FN_SIZE];

    char win_home_dir[FN_SIZE];
    char win_well_dir[FN_SIZE];
    char win_work_dir[FN_SIZE];
    int  win_pwd_mrk;
    int  win_print;
    float win_page_size;
    int  win_page_line_num;

  public:

    int  w_ini_main(HINSTANCE p_pins);
    int  w_fetch_filename(char *str,int str_size);
    int  w_set_focus(HWND hwnd);
    int  w_set_focus_timer(HWND hwnd);
    int  w_set_focus2(HWND hwnd);
    int  w_set_lbutton(HWND hwnd,int hnd_id);

    int  set_string(char *s1,int s1_size,char *s2,int s2_size);

    int  get_view(char *str,int str_size,HWND hwnd,int pp5);
    int  get_edit(char *str);
    int  get_setup(void);
    int  get_setup_save(void);
    int  get_xbase_open(void);
    int  get_skip(long rn);
    int  get_insert(void);
    int  get_delete(void);
    int  get_display(void);
    int  get_setrecno(void);
    int  get_locate(void);
    int  get_commit(void);
    int  get_rollback(void);
    int  get_close(void);
    int  get_ci_save(int hnd_id);
/*
};

class bw_main_bua
{
*/
  private:

    char   win_face_bmp1[20][FN_SIZE];

  public:

    int    get_win_face_bmp1(int p019,char *s1,int s1_size);
    int    set_win_face_bmp1(int p019,char *s1,int s1_size);
};

class bw_dialog
{
  private:

	 int      win_mv_pp1;
	 int      win_mv_pp2;

  public:

	 int      w_read_ddc(char *p_fn,int p_fn_size,int p_wpp);
	 int      w_mv_save_mem(char *s1,int s1_size,int p_wpp,char *s2,int s2_size);
	 int      w_dele_mem(char *s1,int p_wpp,char *s2);
         int      w_save_dialog(int p_wpp);
	 int      w_dele_dialog(int wp1,int wp2);
         int      w_clr_recvar_dialog(int p_wpp);
	 int      w_mv_add_val(char *s1,int s1_size,int p_wpp,char *s2,int s2_size);
	 int      w_mv_fet_val(char *s1,int s1_size,int p_wpp,char *s2,int s2_size);
	 int      w_mv_sav_var(char *s1,int s1_size,int p_wpp);
	 int      w_mv_get_var(char *s1,int s1_size,int p_wpp);
	 int      w_mv_exist(char *s1,int s1_size,int p_wpp);
         int      w_mv_add_name(char *p_tmpc1,int p_tmpc1_size);
	 int      w_mv_seri(char *p_tmpc1,int p_tmpc1_size,int p_wpp);
         int      w_mv_move_aft(int dd,int num);
	 int      w_mv_move_bef(int dd,int num);
	 int      w_echo_winrec_var(int p_wpp);
	 int      w_mv_get_read_paint(char *s1,int s1_size,int p_wpp,char comm);
	 int      w_mv_get_read_g(char *s1,int s1_size,int p_wpp,char comm);
	 int      w_mv_get_read_r(char *s1,int s1_size,int p_wpp,char comm);

	 int      w_echo_winrec_read(int p_fpp,int p_wpp,int mark);
         int        w_get_yy(char *p_tmpc2,int p_tmpc2_size);
         int        w_get_mm(char *p_tmpc2,int p_tmpc2_size);
         int        w_get_dd(char *p_tmpc2,int p_tmpc2_size);
         int      w_get_year(char *p_tmpc2,int p_tmpc2_size);
         int       w_get_mon(char *p_tmpc2,int p_tmpc2_size);
         int      w_get_time(char *p_tmpc2,int p_tmpc2_size);
	 int       w_get_usr(char *p_tmpc2,int p_tmpc2_size);

	 int      tst_mem(void);
/*
};

class bw_dialog_bua
{
*/
  private:

    char     win_mv_stor[MEM_LEN];
    int      win_mv_posi[MEM_VAR][2];  /* mem var posi & len */
    int      win_mv_type[MEM_VAR][6];/* mem var display_type,type,len,dec,win num,edit len */
    int      win_mv_getp[WIN_NUM]; /* cursor dist */

    char     win_mv_name[MEM_VAR][11]; /* mem var name */
    char     win_mv_getv[WIN_NUM][SMG_SIZE];

  public:

    int      get_win_mv_stor(int mlpp);
    int      get_win_mv_posi(int mvpp,int p01);
    int      get_win_mv_type(int mvpp,int p05);
    int     *get_win_mv_getp(int p_wpp);
    int      getv_win_mv_getp(int p_wpp);

    int      set_win_mv_stor(int mlpp,int val);
    int      set_win_mv_posi(int mvpp,int p01,int val);
    int      set_win_mv_type(int mvpp,int p05,int val);
    int      set_win_mv_getp(int p_wpp ,int val);

    int      get_win_mv_name(int mvpp,char *s1,int s1_size);
    int      set_win_mv_name(int mvpp,char *s1,int s1_size);
    int      setc_win_mv_name(int mvpp,int p0a,int val);

    int      get_win_mv_getv(int p_wpp,char *s1,int s1_size);
    int      set_win_mv_getv(int p_wpp,char *s1,int s1_size);
    int      setc_win_mv_getv(int p_wpp,int pp1,int val);
};

class bw_switch
{

  private:

    int   win_switch_pp1;

  public:

    int w_switch_ini(void);
    int w_read_sdc(char *p_fn1,int p_fn1_size,int p_wpp);
    int w_save_switch(int p_wpp);
    int w_dele_switch(int wp1,int wp2);
    int w_set_radio_var(int l,int c,int p,int p_wpp);
    int w_echo_winrec_radio(int p_wpp);
    int w_clr_recvar_radio(int p_wpp);
    int tst_switch(void);
/*
};

class bw_switch_bua
{
*/
  private:

    int   win_switch[MENU_NUM_RA][4];  /* in use,pre val,seri,win num */
    char  win_switch_name[MENU_NUM_RA][11];

  public:

    int   get_win_switch(int mpp,int p03);
    int   set_win_switch(int mpp,int p03,int val);

    int   get_win_switch_name(int mpp,char *s1,int s1_size);
    int   set_win_switch_name(int mpp,char *s1,int s1_size);
    int   setc_win_switch_name(int mpp,int p0a,int val);
};

class bw_choose
{

  private:

    int      win_choose_pp1;

  public:

    int w_choose_ini(void);
    int w_read_cdc(char *p_fn1,int p_fn1_size,int p_wpp);
    int w_save_choose(int p_wpp);
    int w_dele_choose(int wp1,int wp2);
    int w_echo_chs_change(int link,int p_wpp);
    int w_echo_winrec_chs(int p_wpp);
    int w_clr_recvar_chs(int p_wpp);
    int tst_choose(void);
/*
};

class bw_choose_bua
{
*/
  private:

    int      win_choose[MENU_NUM_CHS][4]; /* in use,pre val,seri,win num */
    char     win_choose_name[MENU_NUM_CHS][11];

  public:

    int      get_win_choose(int cpp,int p03);
    int      set_win_choose(int cpp,int p03,int val);

    int      get_win_choose_name(int cpp,char *s1,int s1_size);
    int      set_win_choose_name(int cpp,char *s1,int s1_size);
    int      setc_win_choose_name(int cpp,int p0a,int val);
};

class bw_menuvar
{

  private:

   int      t5_m_pp1;

  public:

   char     t5_m_como[SMG_SIZE];
   int      t5_m_pp3;
   int      t5_m_pp2;

  public:

    int w_menu_find_seri(int pp1);
    int w_read_mdc(char *p_fn1,int p_fn1_size,int p_wpp);
    int w_dele_menu(int wp1,int wp2);
    int w_menu_comm(int p1,int state);
    int w_menu_poin(char *s1,int s1_size,int p1);
    int tst_menu(void);
/*
};

class bw_menuvar_bua
{
*/
  private:

    int      t5_m_wind[MENU_NUM_MN];
    int      t5_m_mcnt[MENU_NUM_MN];
    char     t5_m_name[MENU_NUM_MN][11];
    char     t5_m_button[MENU_NUM_MN][81];
    char     t5_m_comm[MENU_NUM_MN][81];
    char     t5_m_focus[MENU_NUM_MN][81];

  public:

    int      get_t5_m_wind(int mpp);
    int      get_t5_m_mcnt(int mpp);

    int      set_t5_m_wind(int mpp,int val);
    int      set_t5_m_mcnt(int mpp,int val);

    int      get_t5_m_name(int mpp,char *s1,int s1_size);
    int      set_t5_m_name(int mpp,char *s1,int s1_size);
    int      setc_t5_m_name(int mpp,int p0a,int val);

    int      get_t5_m_button(int mpp,char *s1,int s1_size);
    int      set_t5_m_button(int mpp,char *s1,int s1_size);
    int      setc_t5_m_button(int mpp,int pp1,int val);

    int      get_t5_m_comm(int mpp,char *s1,int s1_size);
    int      set_t5_m_comm(int mpp,char *s1,int s1_size);
    int      setc_t5_m_comm(int mpp,int pp1,int val);

    int      get_t5_m_focus(int mpp,char *s1,int s1_size);
    int      set_t5_m_focus(int mpp,char *s1,int s1_size);
    int      setc_t5_m_focus(int mpp,int pp1,int val);
};

class bw_fldstru
{
  public:

    int   win_field_num;

  public:

    int w_dele_stru(int p);
    int w_cnt_tabfield(int p);
    int w_cnt_reclen(int p);
    int w_cnt_fldposi(int p);
    int w_read_stru(char *p_fn1,int p_fn1_size,int pstn);
    int w_find_fldnum(char *str ,int str_size,int p);
    int w_find_fldlen(char *s1  ,int  s1_size,int p);
    int w_find_fldtype(char *str,int str_size,int p);
    int w_find_flddec(char *s1  ,int  s1_size,int p);
    int w_find_fldposi(char *s1 ,int  s1_size,int p);
    int w_find_fldpoin0(int i);
    int w_find_fldpoin1(int i);
    int w_find_fldname(int i,int j,char *str,int str_size);

    int w_echo_winrec(int p_wpp);
    int w_fetch_rec(int p_fpp,int p_wpp,int seri);
    int w_tv_get_read_paint(char *fn,int fn_size,int p_wpp,int l,int c,char comm);
    int w_tv_get_read_g(char *fn,int fn_size,int p_wpp,int l,int c,char comm);
    int w_tv_get_read_r(char *fn,int fn_size,int p_wpp,int l,int c,char comm);
    int w_get_tab_var(char *fn,int fn_size,int p_fpp,char *ca,int ca_size);
    int w_cmp_tab_var(char *fn,int fn_size,int p_fpp,char *ca,int ca_size);
    int w_sav_tab_var(char *fn,int fn_size,int p_fpp,char *ca,int ca_size);
    int w_page_up(int p_fpp,int p_wpp);
    int w_page_down(int p_fpp,int p_wpp);
    int w_first_editposi(int p_fpp,int p_wpp);
    int w_last_editposi(int p_fpp,int p_wpp);
    int w_insert_rec(int p_fpp,int p_wpp);
    int w_add_rec(int p_fpp,int p_wpp);
    int w_delete_rec(int p_fpp,int p_wpp);
    int w_rollback_base(int p_fpp,int p_wpp);
    int w_commit_base(int p_fpp,int p_wpp);
    int w_link_window(int p_fpp,int p_wpp);
    int w_is_card(int p_fpp,int p_wpp);
    int w_find_cond(int p_fpp,int p_wpp);
    int w_find_key(int p_fpp,int p_wpp);
    int w_find_recno(int p_fpp,int p_wpp);
    int w_find_end(int p_fpp,int p_wpp);
    int w_find_exit(int p_wpp);
    int w_find_cond_ok(int p_fpp);
    int w_clr_condition(int p_fpp);

    int w_edit_memo(int p_fpp,int p_wpp,char *fldname,int fldname_size);
    int w_edit_memo_close(int p_wpp);
    int w_edit_memo_add(int p_fpp,int p_wpp,char *fldname,int fldname_size);
    int w_wps_to_txt(char *fn1,int fn1_size,char *fn2,int fn2_size);

    int tst_stru(void);
/*
};

class bw_fldstru_bua
{
*/
  private:

    int   t2_fldpoin[STRU_NUM][2];
    int   t2_fldtype[FLD_IN_BASE];
    int   t2_fldlen[FLD_IN_BASE];
    int   t2_flddec[FLD_IN_BASE];
    int   t2_fldposi[FLD_IN_BASE];

    char  t2_fldname[FLD_IN_BASE][11];

  public:

    int   get_t2_fldpoin(int spp,int p01);
    int   get_t2_fldtype(int fbpp);
    int   get_t2_fldlen(int fbpp);
    int   get_t2_flddec(int fbpp);
    int   get_t2_fldposi(int fbpp);

    int   set_t2_fldpoin(int spp,int p01,int val);
    int   set_t2_fldtype(int fbpp,int val);
    int   set_t2_fldlen(int fbpp,int val);
    int   set_t2_flddec(int fbpp,int val);
    int   set_t2_fldposi(int fbpp,int val);

    int   get_t2_fldname(int fbpp,char *s1,int s1_size);
    int   set_t2_fldname(int fbpp,char *s1,int s1_size);
    int   setc_t2_fldname(int fbpp,int p0a,int val);
    int   getc_t2_fldname(int fbpp,int p0a);

    int w_up_line(int p_fpp,int p_wpp);
    int w_down_line(int p_fpp,int p_wpp);
    int w_up_line2(int p_fpp,int p_wpp);
    int w_down_line2(int p_fpp,int p_wpp);
    int w_last_line(int p_fpp,int p_wpp);
    int w_first_line(int p_fpp,int p_wpp);
    int w_have_next_rec(int p_fpp,int p_wpp);
    int w_have_prev_rec(int p_fpp,int p_wpp);
    int w_be_linked(int p_fpp,int p_wpp);

    int w_have_next_rec2(int p_fpp,int p_wpp,int recno);
    int w_have_prev_rec2(int p_fpp,int p_wpp,int recno);


};

class bw_win
{

  private:

    int           scnt;

    char          texts1[12];
    char          texts2[12];
    char          texts3[12];
    char          texts4[12];
    char          texts5[12];
    char          texts6[12];
    char          texts7[12];
    char          texts8[12];
    char          texts9[12];
    char          texts10[12];

    //int       win_pp3;                    /* current tab seri num */
    //int       win_pp7;                    /* find field number */
    //int       win_pp8;                    /* stru number in one scrn file */

  public:

    FARPROC   win_tfpp;

    int       win_mark;

    int       win_h_ci_total_pp;              /* ci cnt & pp */
    int       win_h_pp;              /* windows number for one group */

    //int       win_pp21;   /* 1 should echo read var */
    //int       win_pp22;   /* 1 should echo link var */
    //int       win_pp23;   /* 1 should echo calc var */

  public:

    int       win_h_w_total_pp,win_h_w_cur_pp;     /* total hwnd pp & current hwnd pp */

    int       win_pp_new_win;               /* empty array point */
    int       win_menu_cmd;
    int       win_menu_seri;

    int       pline;
    int       pfield;

    int       win_mouse_y;
    int       win_mouse_x;

  public:

    int w_cre_ci_button(int p_pagecnt,char *s1,int s1_size,int p6,int p7,int p8,int i,char *,int);
    int w_cre_ci_edit(int p_pagecnt,int p6,int p7,int p8,int i);
    int w_cre_ci_radio(int p_pagecnt,int p6,int p7,int p8,int i,char *,int);
    int w_cre_ci_check(int p_pagecnt,int p6,int p7,int p8,int i,char *,int);

    int w_first_grp(void);
    int w_ini_win(void);
    int w_login_win(int i,int j,char *win_name,int win_name_size,char *find_name,int find_name_size);
    int w_login_wwin(int i);
    int w_close_win(int p1);
    int w_close_subwin(int p1);
    int w_dele_win_pp(int p_wpp);
    int w_dele_win_pp_wins_dbf(int p_wpp);
    int w_dele_xbase_state(int p_wpp);
    int tst_win1(void);
    int tst_win2(void);
    int tst_win3(void);
    int tst_win4(void);
    int tst_win5(void);
    int tst_win6(void);
    int w_find_winhand(HWND hwnd);
    int w_mouse_infield(int p_wpp,int y,int x);
    int w_adjust_edit(int p_wpp);
    int w_find_hnd(int p1,int p2,int p3);
    int w_find_winfname(int w,int l,int c,char *s1,int s1_size);
    int w_find_winflen(int w,int l,int c);
    int w_set_winfedit(int w,int l,int c,int v);
    int w_field_info3(int w);
    int w_read_winfile(char *p_fn2,int p_fn2_size);
    int w_echo_winrec_paint(int p_pagecnt,int mark);
    int w_field_info1(int p_pagecnt,int mark);
    int w_cre_win_button(int p_pagecnt,int mark);
    int w_cre_win_edit(int p_pagecnt,int mark);
    int w_cre_win_radio(int p_pagecnt,int mark);
    int w_cre_win_check(int p_pagecnt,int mark);
    int w_next_field(int i);
    int w_next_afield(int i);
    int w_right_field(int i);
    int w_left_field(int i);
    int w_up_field(int i);
    int w_down_field(int i);
    int w_down_line(int p_pp,int i);
    int w_up_line(int p_pp,int i);
    int w_echo_var_pa(int ,char *p_var1);
    int w_field_type(char *str);
    int w_fetch_fld_style(char *tfn,int tfn_size,char *tn,int tn_size,long *tr,char *fn,int fn_size,int p_wpp);
    int w_find_base_name(char *str,int str_size,int p_wpp);
    int w_find_fld_name(char *str,int str_size,int p_wpp);
    int w_find_recno_name(char *str,int str_size);
    int w_fld_set_base(char *p_fldtable,int p_fldtable_size,int pp1,int p_wpp);
    int w_fld_set_recno(long p_fldrecno,int pp2);
    int w_fld_set_fld(char *p_fldname,int p_fldname_size);
    int w_field_info2(int p_wpp);
    int w_cnt_winline(int p_fpp,int p_wpp,int line);

    int w_atten1(char *p_fn1);
    int w_atten2(void);
    int w_atten3(void);
    int w_atten4(void);
    int w_atten5(void);
    int w_atten6(void);
    int w_atten7(void);
    int w_atten7a(void);
    int w_atten7b(void);
    int w_atten8(char *s1);
    int w_atten9(char *s1);
    int w_atten9a(char *s1);
    int w_atten10(void);
    int w_atten11(void);
    int w_atten12(void);
    int w_atten13(char *s1);
    int w_atten14(char *s1);
    int w_atten15(char *s1);
    int w_atten16(char *s1);
    int w_atten17(char *s1);
    int w_atten18(char *s1);
    int w_atten19(char *s1);
    int w_atten20(char *s1);
    int w_atten21(void);
    int w_atten22(void);
    int w_atten23(char *s1);
    int w_atten24(char *s1);
    int w_atten25(char *s1);
    int w_atten26(char *s1);
    int w_atten27(char *s1);
    int w_atten28(char *s1);
    int w_atten29(char *s1);
    int w_atten30(char *s1);
    int w_atten31(char *s1);
    int w_atten32(char *s1);
    int w_atten33(char *s1);
    int w_atten34(char *s1);
    int w_atten35(char *s1);
    int w_atten36(char *s1);
    int w_atten37(char *s1);
    int w_atten38(char *s1);
    int w_atten39(void);
    int w_atten40(void);
    int w_atten41(void);
    int w_atten42(void);
    int w_atten43(void);
    int w_atten44(void);
    int w_atten45(char *s1);
    int w_atten46(char *s1);
    int w_atten47(char *s1);
    int w_atten48(char *s1);
    int w_atten49(void);
    int w_atten50(void);
    int w_atten51(void);
    int w_atten52(void);
    int w_atten53(void);
    int w_atten54(void);
    int w_atten55(void);
    int w_atten56(void);
    int w_atten57(int l);
    int w_atten58(void);
    int w_atten59(void);
    int w_atten60(void);
    int w_atten61(void);
    int w_atten62(void);
    int w_atten63(void);
    int w_atten64(char *s1);
    int w_atten65(void);
    int w_atten66(void);
    int w_atten67(void);
    int w_atten68(void);

    int tst_hpp3(void);
    int tst_hpp4(void);
/*
};

class bw_win_bua
{
*/
  private:

    char          t_fldname[FLD_IN_SCRN][FLD_NAME_LEN];
    char          t_fldtype[FLD_IN_SCRN];
    char          t_fldbase[FLD_IN_SCRN];
    int           t_fldseri[FLD_IN_SCRN];
    int           t_fldlen[FLD_IN_SCRN];
    int           t_flddec[FLD_IN_SCRN];
    int           t_fldedt[FLD_IN_SCRN];

    int           t_fldseri_tmp[FLD_IN_SCRN];
    char          t_field_tmp[FLD_IN_SCRN][10];

    int           t_base_tmp[FLD_IN_SCRN];
    int           t_recno_tmp[FLD_IN_SCRN];

    //int           win_subhndid[WIN_NUM][10];
    //int           win_subhndpp[WIN_NUM];

    int           win_state_link_modi[WIN_NUM]; /* link modified */
    int           win_state_calc_modi[WIN_NUM]; /* calc modified */
    int           win_switch_bmp[WIN_NUM];

    int           win_pp_fld_in_win[WIN_NUM][4];   /* field in tab window, cur&first&last&echo pp */

    int           win_h_w_pp[WIN_NUM][9];  /* start,end,cur,parent pp.parent foc*/
    int           win_h_ci_pp[HND_NUM][5];  /* its win num,x,y,its hwnd num,parent hwnd */
    int           win_h_up_pp[WIN_NUM][2];  /* up scrn seg posi */

    HWND          win_phh[WIN_NUM];      /* win_pp_grp_pp's windows handle */

    int           win_pp_win_mark[WIN_NUM];          /* current tab win point */
    int           win_pp_grp_id[WIN_NUM];            /* every tablewin's group number */
    int           win_pp_grp_pp[WIN_NUM][5];         /* every tablewin's group number(0) and group's &first(0)&current(1)&last(2) tablewin number */
    int           win_pp_wins_dbf[STRU_NUM][WIN_NUM];/* base in buf point beg & end */
    int           win_pp_get_rd[WIN_NUM];            /* get_read id */

    int           win_msgboxlock[WIN_NUM];

    int           win_con[WIN_NUM][4];       /* win conner posi */
    int           win_style[WIN_NUM][WIN_STYLE_NUM];
    FARPROC       win_fpp[HND_NUM];
    HWND          win_hnd[HND_NUM];
    int           win_create_menu[WIN_NUM];
    int           win_linep[WIN_NUM][2];
    int           win_is_link[WIN_NUM];
    int           win_is_calc[WIN_NUM];
    int           win_memo_basep[WIN_NUM];

    long          win_timer[WIN_NUM];

    int           win_ci_mode[WIN_NUM];
    int           win_ci_posi[WIN_NUM][2];

  public:

    HWND get_ci_mhnd(HWND hwnd);

  public:

    int  get_1fldname(int p1,char *sval,int sval_size);
    int  set_1fldname(int p1,char *sval,int sval_size);
    int  get_1fldtype(int p1);
    int  set_1fldtype(int p1,int val);
    int  get_1fldbase(int p1);
    int  set_1fldbase(int p1,int val);
    int  get_1fldseri(int p1);
    int  set_1fldseri(int p1,int val);
    int  get_1fldlen(int p1);
    int  set_1fldlen(int p1,int val);
    int  get_1flddec(int p1);
    int  set_1flddec(int p1,int val);
    int  get_1fldedt(int p1);
    int  set_1fldedt(int p1,int val);
    int  set_1fldname1(int p1,int p2,char c1);

    int  get_fldseri_tmp(int p1);
    int  set_fldseri_tmp(int p1,int val);
    int  get_field_tmp(int p1,char *sval,int sval_size);
    int  set_field_tmp(int p1,char *sval,int sval_size);
    int  set_field_tmp1(int p1,int p2,char c1);
    int  get_base_tmp(int p1);
    int  set_base_tmp(int p1,int val);
    int  get_recno_tmp(int p1);
    int  set_recno_tmp(int p1,int val);
/*
    int  get_win_subhndid(int p_wpp,int pp);

    int  set_win_subhndid(int p_wpp,int pp,int val);
    int  get_win_subhndpp(int p_wpp);
    int  set_win_subhndpp(int p_wpp,int val);
*/
    int  get_win_state_link_modi(int p_wpp);         /* link modified */
    int  set_win_state_link_modi(int p_wpp,int val); /* link modified */
    int  get_win_state_calc_modi(int p_wpp);         /* calc modified */
    int  set_win_state_calc_modi(int p_wpp,int val); /* calc modified */

    int  get_win_switch_bmp(int p_wpp);
    int  set_win_switch_bmp(int p_wpp,int val);

    int  get_win_pp_fld_in_win(int p_wpp,int pp);   /* tab in scrn cur&first&last&echo win pp */
    int  set_win_pp_fld_in_win(int p_wpp,int pp,int val);
    int  get_win_h_w_pp(int p_wpp,int pp);  /* tow star,end,cur,parent pp.parent foc*/
    int  set_win_h_w_pp(int p_wpp,int pp,int val);
    int  get_win_h_up_pp(int p_wpp,int pp);  /* up scrn seg posi */
    int  set_win_h_up_pp(int p_wpp,int pp,int val);

    HWND get_win_phh(int p_wpp);          /* win_pp_grp_pp's windows handle */
    int  set_win_phh(int p_wpp,HWND hwnd);

    int get_win_pp_win_mark(int p_wpp);
    int set_win_pp_win_mark(int p_wpp,int val);
    int get_win_pp_grp_id(int p_wpp);
    int set_win_pp_grp_id(int p_wpp,int val);
    int get_win_pp_grp_pp(int p_wpp,int pp04);
    int set_win_pp_grp_pp(int p_wpp,int pp04,int val);
    int get_win_pp_wins_dbf(int p_fpp,int p_wpp);
    int set_win_pp_wins_dbf(int p_fpp,int p_wpp,int val);
    int get_win_pp_get_rd(int p_wpp);
    int set_win_pp_get_rd(int p_wpp,int val);


    int get_win_msgboxlock(int p_wpp);
    int set_win_msgboxlock(int p_wpp,int val);


    int get_win_con(int p_wpp,int p03);
    int set_win_con(int p_wpp,int p03,int val);
    int get_win_style(int p_wpp,int pp);
    int set_win_style(int p_wpp,int pp,int val);

    FARPROC   get_win_fpp(int pp);
    int       set_win_fpp(int pp,FARPROC fproc);
    HWND      get_win_hnd(int pp);
    int       set_win_hnd(int pp,HWND hwnd);
    int       get_win_h_ci_pp(int hpp,int p04);
    int       set_win_h_ci_pp(int hpp,int p04,int val);
    int       get_win_create_menu(int p_wpp);
    int       set_win_create_menu(int p_wpp,int val);
    int       get_win_linep(int p_wpp,int p01);
    int       set_win_linep(int p_wpp,int p01,int val);
    int       get_win_is_link(int p_wpp);
    int       set_win_is_link(int p_wpp,int val);
    int       get_win_is_calc(int p_wpp);
    int       set_win_is_calc(int p_wpp,int val);
    int       get_win_memo_basep(int p_wpp);
    int       set_win_memo_basep(int p_wpp,int val);

    long      get_win_timer(int p_wpp);
    int       set_win_timer(int p_wpp,long val);

    int       get_win_ci_mode(int p_wpp);
    int       set_win_ci_mode(int p_wpp,int val);

    int       get_win_ci_posi(int p_wpp,int p01);
    int       set_win_ci_posi(int p_wpp,int p01,int val);
/*
};

class bw_win_bub
{
*/
  private:

    char win_tabname[2][STRU_NUM][FN_SIZE];/* win group 1-tab&0-stru file name */
    char win_window_name[WIN_NUM][FN_SIZE];
    char win_find_name[WIN_NUM][FN_SIZE];

  public:

    int  get_win_tabname(int p1,int bp,char *s1,int s1_size);  /* win group 1-tab&0-stru file name */
    int  set_win_tabname(int p1,int bp,char *s1,int s1_size);  /* win group 1-tab&0-stru file name */
    int  get_win_window_name(int p_wpp,char *s1,int s1_size);
    int  set_win_window_name(int p_wpp,char *s1,int s1_size);
    int  get_win_find_name(int p_wpp,char *s1,int s1_size);
    int  set_win_find_name(int p_wpp,char *s1,int s1_size);
};

class bw_inkey
{
  public:

    char                 tmp_buff[CPY_BSIZE];

  public:

    int keystart(void);
    int refresh(void);
    int keyend(void);
    int w_set_dir(char *s);
    int w_get_dir(char *s,int s_size);
    int inkey(void);
    //int strpcat(char *s1,int p,char *s2);
    int strtrim(char *str,int str_size);
    int strltrim(char *str,int str_size);
    int strpcut(char *p_s1,int p1,int p2,int p_s1_size,char *p_s2,int p_s2_size);
    long str2long(char *str,int str_size);
    float str2float(char *str,int str_size);
    int str2int(char *string,int string_size);
    int int2str(int val,char *string,int string_size);
    int float2str(float val,char *str,int str_size);
    int long2str(long l,char *str,int str_size);
    int strfind(char *p1,char *p2);
    int strfinda(char *p1,char *p2);
    int strempty(char *p1);
    int upper(char c1);
    int lower(char c1);
    int uppers(char *s1);
    int lowers(char *s1);
    int mon2int(char *str);
    int mon2day(int mon);
    int int2mon(int i,char *mon);
    //int dateadd(char *s1,char *s2,int i);
    //int cdate(char *p1,char *p2);
    int zero2sp(char *p);
    int w_find_file(char *fn1);
    //int w_find_dir(char *fn1);
    int w_fname_ok(char *fn1);
    //int w_cpy_dir(char *win_cpy_f1,char *win_cpy_f2);
    int w_cpy_file(char *fn1,char *fn2);
    int w_del_file(char *fn1);
    int strlocc(char *p_str,int p_str_size,char c1);
    //int str_cmp(char *s1,int l1,char *s2,int l2);

	int w_chs_string_cut(char *p_str,int pn);
};

class bw_getread
{

  private:

    int   smg_insert;
    int   smg_pp;
    int   smg_pp2;
    int   smg_color1,smg_color2;

    int   win_get_pp;
    int   win_get_link;
    int   win_chns_char;
    char  win_chns_str[3];
    int   win_cur1,win_cur2;

  public:
    int   win_p1;

 private:
    int   win_edit_pain;
    int   win_color;
    int   win_confirm;  /* enter or no enter */
    int   win_edit_mode[GET_NUM];/* 0--box,1--line    */
    int   win_p_y;
    int   win_p_x;

    FILE *deb_record_fp;

  public:

    int  tst_getread(void);

    int  get_read_ini(void);
    int  get_read_login(void);
    int  get_read_logout(int pp);
    int  get_read(int scrn_l,int scrn_c,char *atten,
         char *string,int datalen,char datatype,
	 char command,int datalen2,int datadec,
	 char link,int color,int *posi,int array_pp);

    int deb_record_init(void);
    int deb_record_close(void);
    int deb_record(char *p_str1);

  private:

    int  get_txt(int scrn_l,int scrn_c,char *atten,
           int datalen,int datalen2,char link,
	   int pp,int color,int *posi);
    int  get_num(int scrn_l,int scrn_c,char *atten,
	   int datalen,int datalen2,char link,
	   int pp,int color,int dec,int *posi);
    int  get_num_conv(int datalen2,int dec);
    int  get_txt_after(char *data,int l2,int l1,int p1);
    int  get_txt_before(char *data,int l1,int p1);
/*
};

class bw_get_bua
{
*/
  private:

    int   smg_line[GET_NUM];
    int   smg_colu[GET_NUM];
    char  smg_data[SMG_SIZE];
    char  smg_string[GET_NUM][SMG_SIZE];
    char  smg_type[GET_NUM];
    int   smg_dlen[GET_NUM];
    int   smg_dlen2[GET_NUM];
    int   smg_ddec[GET_NUM];
    char  smg_link[GET_NUM];
    int   smg_color[GET_NUM];
    int   *smg_posi[GET_NUM];
    char  smg_atte[GET_NUM][SMG_SIZE];
    int   smg_read_id[GET_NUM];

  public:

    int   get_smg_line(int gpp);
    int   get_smg_colu(int gpp);
    int   get_smg_data(int pp1);
    int   gets_smg_data(char *s1,int s1_size);
    int   get_smg_string(int gpp,char *s1,int s1_size);
    int   getc_smg_string(int gpp,int pp1);
    int   get_smg_type(int gpp);
    int   get_smg_dlen(int gpp);
    int   get_smg_dlen2(int gpp);
    int   get_smg_ddec(int gpp);
    int   get_smg_link(int gpp);
    int   get_smg_color(int gpp);
    int   *get_smg_posi(int gpp);
    int   get_smg_atte(int gpp,char *s1,int s1_size);
    int   get_smg_read_id(int gpp);

  public:

    int   set_smg_line(int gpp,int val);
    int   set_smg_colu(int gpp,int val);
    int   set_smg_data(int pp1,int val);
    int   set_smg_string(int gpp,char *s1,int s1_size);
    int   setc_smg_string(int gpp,int pp1,int val);
    int   set_smg_type(int gpp,int val);
    int   set_smg_dlen(int gpp,int val);
    int   set_smg_dlen2(int gpp,int val);
    int   set_smg_ddec(int gpp,int val);
    int   set_smg_link(int gpp,int val);
    int   set_smg_color(int gpp,int val);
    int   set_smg_posi(int gpp,int *val);
    int   set_smg_atte(int gpp,char *s1,int s1_size);
    int   set_smg_read_id(int gpp,int val);
};
        
