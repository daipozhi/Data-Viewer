//#define _CRT_SECURE_NO_WARNINGS

#define  CPY_BSIZE    20000 /* copy file buffer size      */
#define  FN_SIZE      256   /* file name size */
#define  GET_NUM      200   /*   get_read subroutine var number */
#define  SMG_SIZE     300   /*   get_read var max size */
//#define  ATTE_LEN     50    /*   attention text array */
#define  SUB_WIN_NUM  10

#define  MEM_FLD_LEN  80   // memory field lenght
#define  EXT_SIZE      256  // extern file name size

#define  LIN_NUM      80   /* table window line number */
#define  COL_NUM      300  /* table window column number */
#define  WIN_NUM      32   /* max windows number */
#define  REC_SIZE      3000000 /* one record max size */
#define  STRU_NUM     20    /* total structure number */
#define  BUTTON_NUM_RA  2000   /* radio button number */
#define  BUTTON_NUM_CHS 2000   /* chkbox button number */
#define  BUTTON_NUM_BTN  2000   /* command button number */
#define  FLD_IN_SCRN  100000 /* field number in one win */
#define  FLD_NAME_SIZE 21    // field name size
#define  FLD_IN_BASE  50000   /* field in database number */
#define  FLD_IN_XBASE 5000   /* field number in single database file*/
                            /* link table define */
#define  VAR_IN_SCRN   1500000 /* screen var storage size */
#define  WIN_VAR_NUM   200000 /* screen var number */
#define  LINK_CHAR     80000  /* link condition string storage */
#define  COND_NUM      600   /* link condition string number */
#define  LINK_MODI_NUM 10000  /* link var modify number */
                            /* calculate function define  */
#define  VAL_NUM      60    /* calculate condition var buffer*/
#define  FUNC_NUM     100   /* function number   */
#define  FUNC_VARN    300   /* condition var number     */
#define  FUNC_LEN     2000  /* function string len */

//#define  PAGE_NUM   4
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
#define  CTRL_N     14  /* no find condition */
#define  CTRL_R     18  /* rollback    */
#define  CTRL_W     23  /* commit      */
#define  CTRL_Y     25  /* delete line in edit window*/
#define  CTRL_D     4   /* delete record */
#define  CTRL_A     1   /* insert record */
#define  CTRL_P     16  /* print data  */
#define  F1_KEY     321 /* edit memo   */
#define  F2_KEY     322 /* run ole     */
#define  F3_KEY     323 /* edit memo   */
#define  F4_KEY     324 /* run ole     */
#define  F5_KEY     325 /* edit memo   */
#define  F6_KEY     326 /* run ole     */
#define  ESC_KEY    27  /* close window   */
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

#define  HND_NUM       5000 /* control item id number */
#define  WIN_STYLE_NUM 20   /* control item style number */

#define MEM_VAR_NUM   20000
#define MEM_VAR_SIZE  3000000

#define EDIT_NUM 10        /* max edit window number */

#define  FLD_IN_PAGE  5000  /* print model field number */
#define  PAGE_LINE    81    /* print page line number*/
#define  PAGE_COLU    300   /* print page column number      */
#define  MEMO_NUM     10    /* memo field number per-record */

#define  BMP_BUFF_SIZE 64000




#define  PRINT_FORM_NUM 10
#define  VAR_IN_PAGE/*VAR_IN_SCRN*/   500000 /* print page var storage */
#define  PRT_VAR_NUM/*WIN_VAR_NUM*/   20000 /* print page var number */

#define  BW_WIN_FOCUS_NUM 150

class bw_buff
{
  private:

    int        t3_linecol[WIN_NUM][LIN_NUM][COL_NUM];

  public:

    int        get_t3_linecol(int p_wptr,int line,int col);
    int        set_t3_linecol(int p_wptr,int line,int col,int val);
/*
};

class bw_buffa
{
*/
  private:

    char       t3_winfile[WIN_NUM][LIN_NUM][COL_NUM];

  public:

    char       get_t3_winfile(int p_wptr,int line,int col);
    int        set_t3_winfile(int p_wptr,int line,int col,char val);
};

class bw_font
{
  public:

    int   mn_font_ptr1;

  public:

    int   w_font_ini(void);
    int   w_read_fdc(char *p_fn1,int p_fn1_size,int p_wptr);
    int   w_dele_font(int wp1,int wp2);

    int   tst_font(void);
/*
};

class bw_font_bua
{
*/
  private:

    char  ms_font_name[FONT_NUM][11];

    int   mn_font[FONT_NUM][4];  /* in use,pre val,seri,win num */

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

    HWND     mn_bmp_hnd;

  private:

    HGLOBAL  ReadDibBitmapInfo(int fh);
    int      DibInfo(HGLOBAL hbi,LPBITMAPINFOHEADER lpbi);
    HPALETTE CreateDIBPalette(LPBITMAPINFOHEADER lpbi);
    WORD     DibNumColors(LPBITMAPINFOHEADER lpbi);

  public:

    int      DIB(char *bfn,int bfn_size);
    BOOL     DisplayDIB(HWND hwnd,int x,int y,LPSTR szFile);
    BOOL     PaintDIB(HWND hwnd,int x,int y,int h,LPSTR szFile);
    int      echo_bmp(HWND hwnd,char *comm,int comm_size,int mcntr,int p_wptr);

    int      w_bmp_add(int p_dbptr,int p_wptr,char *fldname,int fldname_size);
    int      w_bmp_paint(HWND hwnd);

    int      tst_b1(void);
};

class bw_print
{
  private:

    char          ms_texts1[20];
    char          ms_texts2[20];
    char          ms_texts3[20];
    char          ms_texts4[20];
    char          ms_texts5[20];
    char          ms_texts6[20];
    char          ms_texts7[20];
    char          ms_texts8[20];

    char  ms_pv[VAR_IN_PAGE];
    int   mn_pvused[PRT_VAR_NUM];
    int   mn_pvpntr[PRT_VAR_NUM][2];
    int   mn_pvseri[PRT_VAR_NUM];
    int   mn_pvrecn[PRT_VAR_NUM];
    int   mn_pvbase[PRT_VAR_NUM];
    int   mn_pvwind[PRT_VAR_NUM];

  public:

    int         t6_ptr1;
    int         t6_page_num;
    int         t6_wdir;

  public:

    FILE       *txt_out_fp1;
    FILE       *txt_out_fp2[MEMO_NUM];

    int         mn_memo_left,mn_memo_leng;

    int         p1;
    int         p2;
    int         p3;
    int         p4;

  public:

    int         mn_print_xchar;
    int         mn_print_ychar;
    int         mn_page_num;

    DOCINFO     mn_print_inf;
    HWND        mn_savep_hnd;
    HWND        mn_outp_hnd;

  public:

    int w_out_linux_print(void);
    int w_close_opwin(void);
    int w_close_spwin(void);
    int w_open_print_file(char *p_s1,int p_s1_size);
    int w_close_print_file(void);
    int w_read_page(char *p_fn2,int p_fn2_size);
    int w_page_field1(void);
    int w_page_field2(int p_wptr);
    int w_fld_set_edit(char *p_fldname,int p_fldname_size);
    int w_print_page(int p_wptr);
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
    int w_print_lnk(int p_wptr);
    int w_print_cal(void);
    int w_print_read(void);
    int w_scan_pagevar(void);
    int w_print_echo1(HWND hwnd);
    int w_print_echo2(HWND hwnd);

  public:

    int w_print(int p_wptr,char *s1,int s1_size);       /* public*/
    int w_read_setup(void);                            /* public*/

    int tst_p1(void);
    int tst_p2(void);
    int tst_p3(void);




    int w_print_page_down(int p_dbptr,int p_wptr);
    int w_print_link_cond_ok(int condnum,int p_wptr,int basep,int recn,int page);
    int w_scan_pv(int p_wptr);
    int w_save_pv(int p_wptr,int base,int seri,int recn,int posi,int len);           /*save scrn var to arr*/
    int w_get_pv(int p_wptr,int base,int seri,int recn,char *p_str,int p_str_size);  /*get scrn var to arr*/

    int get_ms_pv(int sptr);
    int set_ms_pv(int sptr,char val);
    int get_mn_pvused(int vptr);
    int set_mn_pvused(int vptr,int val);
    int get_mn_pvpntr(int vptr,int p01);
    int set_mn_pvpntr(int vptr,int p01,int val);
    int get_mn_pvseri(int vptr);
    int set_mn_pvseri(int vptr,int val);
    int get_mn_pvrecn(int vptr);
    int set_mn_pvrecn(int vptr,int val);
    int get_mn_pvbase(int vptr);
    int set_mn_pvbase(int vptr,int val);
    int get_mn_pvwind(int vptr);
    int set_mn_pvwind(int vptr,int val);


    int get_setup_print(void);

/*
};

class bw_print_bua
{
*/
/* t6_ t5_ t4_ t3_ t2_ t_ t7_ is module name , table name */

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

    int   t7_fldseri[FLD_IN_PAGE];       // t7_ temp var
    char  t7_fldname[FLD_IN_PAGE][10];
    int   t7_fldbase[FLD_IN_PAGE];
    int   t7_fldrecn[FLD_IN_PAGE];

    int   mn_memo_print[MEMO_NUM];

    char  ms_print_fname[SMG_SIZE];

  public:

    int   get_t6_linecol(int fldptr,int p02);
    int   set_t6_linecol(int fldptr,int p02,int val);

    int   get_c_t6_fldname(int fldptr,int ptr1);
    int   set_c_t6_fldname(int fldptr,int ptr1,int val);

    int   get_t6_fldname(int fldptr,char *s1,int s1_size);
    int   set_t6_fldname(int fldptr,char *s1,int s1_size);
    int   get_t6_fldtype(int fldptr);
    int   set_t6_fldtype(int fldptr,int val);
    int   get_t6_fldedit(int fldptr);
    int   set_t6_fldedit(int fldptr,int val);
    int   get_t6_fldbase(int fldptr);
    int   set_t6_fldbase(int fldptr,int val);
    int   get_t6_fldseri(int fldptr);
    int   set_t6_fldseri(int fldptr,int val);
    int   get_t6_fldlen(int fldptr);
    int   set_t6_fldlen(int fldptr,int val);
    int   get_t6_flddec(int fldptr);
    int   set_t6_flddec(int fldptr,int val);

    int   get_t6_recno(int p_dbptr,int form);
    int   set_t6_recno(int p_dbptr,int form,int val);

    int   get_t6_eof(int p_dbptr,int form);
    int   set_t6_eof(int p_dbptr,int form,int val);

    int   get_t7_fldname(int fldptr,char *s1,int s1_size);
    int   set_t7_fldname(int fldptr,char *s1,int s1_size);

    int   set_c_t7_fldname(int fldptr,int cptr,int val);

    int   get_t7_fldseri(int fldptr);
    int   set_t7_fldseri(int fldptr,int val);
    int   get_t7_fldbase(int fldptr);
    int   set_t7_fldbase(int fldptr,int val);
    int   get_t7_fldrecn(int fldptr);
    int   set_t7_fldrecn(int fldptr,int val);

    int   get_mn_memo_print(int mptr);
    int   set_mn_memo_print(int mptr,int val);

    int   get_ms_print_fname(char *s1,int s1_size);
    int   set_ms_print_fname(char *s1,int s1_size);
/*
};

class bw_print_bub
{
*/
  private:

    char t6_pagefile[PAGE_LINE][PAGE_COLU];

  public:

    int  get_t6_pagefile(int lptr,int cptr);
    int  set_t6_pagefile(int lptr,int cptr,int val);
    int  get_s_t6_pagefile(int lptr,char *s1,int s1_size);
/*
};

class bw_print_buc
{
*/
  private:

    char t6_prtbuff[PAGE_LINE][PAGE_COLU];

  public:

    int  get_t6_prtbuff(int lptr,int cptr);
    int  set_t6_prtbuff(int lptr,int cptr,int val);
    int  get_s_t6_prtbuff(int lptr,char *ps1,int ps1_size);
};

class bw_edit
{
  public:

    int  mn_edit_ptr1;

  public:

    int  get_edit(char *fn,int fn_size,int p_wptr,HWND hwnd);
    int  w_find_edithand(HWND hwnd);
    int  w_ini_edit(void);
/*
};

class bw_edit_bua
{
*/
  private:

    HWND mn_edit_hnd1[EDIT_NUM];
    HWND mn_edit_hnd2[EDIT_NUM];
    char ms_edit_dirn[EDIT_NUM][FN_SIZE];
    char ms_edit_file[EDIT_NUM][FN_SIZE];
    int  mn_edit_modi[EDIT_NUM];
    int  mn_edit_inuse[EDIT_NUM];
    int  mn_edit_wptr[EDIT_NUM];

  public:

    HWND get_mn_edit_hnd1(int eptr);
    int  set_mn_edit_hnd1(int eptr,HWND hwnd);
    HWND get_mn_edit_hnd2(int eptr);
    int  set_mn_edit_hnd2(int eptr,HWND hwnd);
    int  get_ms_edit_dirn(int eptr,char *s1,int s1_size);
    int  set_ms_edit_dirn(int eptr,char *s1,int s1_size);
    int  get_ms_edit_file(int eptr,char *s1,int s1_size);
    int  set_ms_edit_file(int eptr,char *s1,int s1_size);

    int  tst_dirn_file(void);

    int  get_mn_edit_modi(int eptr);
    int  set_mn_edit_modi(int eptr,int val);
    int  get_mn_edit_inuse(int eptr);
    int  set_mn_edit_inuse(int eptr,int val);
    int  get_mn_edit_wptr(int eptr);
    int  set_mn_edit_wptr(int eptr,int val);

};

class bw_link
{

  public:

    int w_dele_link(int wp1);
    int w_dele_svar(int wp1);
    int w_read_link(char *fn,int fn_size,int p_wptr,int num);
    int w_find_link_tn(char *str1,int str1_size,int p_wptr,int i);
    int w_find_link_cd(int p_wptr,char *str1,int str1_size,int i,int k);
    int w_link_modi(int p_wptr);      /* fetch link var in condition & link var if modified */
    int w_fetch_link_var(int p1,int p2,char *s1,int s1_size);
    int w_fetch_link_var2(int p1,int p2,char *s1,int s1_size);
    int w_link_modi_set(char *tn,int tn_size,char *fn,int fn_size,int p1,int p_wptr);
    int w_link_modi_mark(int p_wptr,int p_dbptr,int seri,int field);     /* echo window record ,link record should change */
    int w_link_modi_unmark(int p_wptr,int p_dbptr,int seri,int field);   /* echo window record ,link record should change */
    int w_echo_winrec_lnk(int p_wptr);                               /* echo window record where modified */
    int w_link_modified(int p_wptr,int basep);
    int w_link_cond_ok(int condnum,int p_wptr,int basep,int recn,int page);
    int w_is_calc(char *s1);
    int w_name_in_tab(char *s1,int s1_size,int basep);
    int w_scan_sv(int p_wptr);
    int w_save_sv(int p_wptr,int base,int seri,int recn,int posi,int len);
    int w_get_sv(int p_wptr,int base,int seri,int recn,char *str,int str_size);
    int w_link_type(int p_wptr,int basep);
    int w_link_number(int p_wptr,int basep);
    int w_link_base_num(int p_wptr,int basep);
    int w_link_set_continue(int p_wptr,int basep);
    int w_keep_linkfld(int p_wptr,int p_dbptr,int dir);

    int tst_link1(void);
    int tst_link1_lkchar(void);
    int tst_link2(void);
    int tst_link3(void);
    int tst_link4(void);
    int tst_link5(void);
    int tst_link5_svar(void);
/*
};

class bw_link_bua
{
*/
  private:

    char  ms_svar[VAR_IN_SCRN];

    int   mn_svused[WIN_VAR_NUM];
    int   mn_svpntr[WIN_VAR_NUM][2];
    int   mn_svseri[WIN_VAR_NUM];
    int   mn_svrecn[WIN_VAR_NUM];
    int   mn_svbase[WIN_VAR_NUM];
    int   mn_svwind[WIN_VAR_NUM];

    char  ms_chlink[LINK_CHAR];     

    int   mn_bslink[COND_NUM][3];   /* database to database & p_wptr */
    int   mn_bspntr[COND_NUM][2];   /* link condition string pntr */

    int   mn_lkpntr[COND_NUM][2];   /* modi var pntrt */
    int   mn_lkmodi[LINK_MODI_NUM]; /* modi var status*/
    int   mn_lkseri[LINK_MODI_NUM]; /* modi var seri */
    int   mn_lkbase[LINK_MODI_NUM]; /* modi var database */
    int   mn_lkfield[LINK_MODI_NUM]; /* modi var record no.*/
    int   mn_lkwind[LINK_MODI_NUM]; /* modi var window */

    int   mn_continue[STRU_NUM][WIN_NUM];/* continue link data page */

    char  ms_bb1[VAL_NUM][SMG_SIZE];  /* val buff  */
    int   mn_bb2[VAL_NUM];            /* calc char */
    int   mn_bb3[VAL_NUM];            /* val type  */


  public:

    int   get_ms_svar(int sptr);
    int   set_ms_svar(int sptr,char val);
    int   get_mn_svused(int vptr);
    int   set_mn_svused(int vptr,int val);
    int   get_mn_svpntr(int vptr,int p01);
    int   set_mn_svpntr(int vptr,int p01,int val);
    int   get_mn_svseri(int vptr);
    int   set_mn_svseri(int vptr,int val);
    int   get_mn_svrecn(int vptr);
    int   set_mn_svrecn(int vptr,int val);
    int   get_mn_svbase(int vptr);
    int   set_mn_svbase(int vptr,int val);
    int   get_mn_svwind(int vptr);
    int   set_mn_svwind(int vptr,int val);

    int   get_ms_chlink(int lptr);
    int   set_ms_chlink(int lptr,char val);
    int   get_mn_bslink(int dptr,int p02);
    int   set_mn_bslink(int dptr,int p02,int val);
    int   get_mn_bspntr(int dptr,int p01);
    int   set_mn_bspntr(int dptr,int p01,int val);

    int   get_mn_lkpntr(int cptr,int p01);
    int   set_mn_lkpntr(int cptr,int p01,int val);
    int   get_mn_lkmodi(int lptr);
    int   set_mn_lkmodi(int lptr,int val);
    int   get_mn_lkseri(int lptr);
    int   set_mn_lkseri(int lptr,int val);
    int   get_mn_lkbase(int lptr);
    int   set_mn_lkbase(int lptr,int val);
    int   get_mn_lkfield(int lptr);
    int   set_mn_lkfield(int lptr,int val);
    int   get_mn_lkwind(int lptr); 
    int   set_mn_lkwind(int lptr,int val);

    int   get_mn_continue(int p_dbptr,int p_wptr);
    int   set_mn_continue(int p_dbptr,int p_wptr,int val);

    int   set_mn_cbb1(int vptr,int ptr1,int val);

    int   get_ms_bb1(int vptr,char *s1,int s1_size);
    int   set_ms_bb1(int vptr,char *s1,int s1_size);
    int   get_mn_bb2(int vptr);
    int   set_mn_bb2(int vptr,int val);
    int   get_mn_bb3(int vptr);  
    int   set_mn_bb3(int vptr,int val);


};

class bw_mbase
{
  public:

    int  w_open_base(char *bn,int bn_size,int p_dbptr);
    int  w_close_base(int p_dbptr,int p_wptr);

    int w_down_rec(int p_dbptr,int p_wptr,int recno);
    int   w_up_rec(int p_dbptr,int p_wptr,int recno);
    int  w_save_rec(int p_dbptr,int p_wptr,int recno);
    int   w_ins_rec(int p_dbptr,int p_wptr,int recno);
    int  w_add_rec(int p_dbptr,int p_wptr,int recno);
    int   w_del_rec(int p_dbptr,int p_wptr,int recno);
};

class bw_xbase
{
  public:

    int  mn_answer;
    int  mn_insert_dir;
    int  mn_state_dbf_err; //mn_state3;           /* error mark */

    int  mn_fh2[WIN_NUM];

  private:

    int  mn_fh[STRU_NUM];

  private:

    int  t4_eof;
    int  t4_bof;
    int  mn_use_fh;

  public:

    //int  get_xbase_open(int p_dbptr,char *s1,int l1,char *s2,int l2);
    //int  get_xbase_close(int p_dbptr);

    int  tst_xbase1(void);
    int  tst_xbase2(void);

    int  w_read_recno(int fh);
    int  w_open_xbase(char *p_fn1,int p_fn1_size,int backup,int p_dbptr);
    int  w_close_xbase(int p_wptr,int p_dbptr);
    int  w_login_xbase(int ptr);
    int  w_free_xbase(void);
    int  w_dele_state(int p_dbptr);
    int  w_create_xbase(char *p_fn12,int p_fn12_size,int p_dbptr);
    int  w_compare_xbase(int p_fh,int p_dbptr);
    int  w_read_xbase_rec(int recno,int p_dbptr);
    int  w_save_xbase_rec(int recno,int p_dbptr);
    int  w_append_xbase_rec(int recno,int p_dbptr);
    int  w_append_xbase_rec2(int p_dbptr);
    int  w_loc_xbase_rec(int recno,int p_dbptr);
    int  w_up_xbase_rec(int recno,int p_dbptr);
    int  w_down_xbase_rec(int recno,int p_dbptr);
    int  w_xbase_rec_del(void);
    int  w_dele_xbase_rec(int recno,int p_dbptr);
    int  w_insert_xbase_rec(int recno,int p_dbptr,int aft);
    int  w_insert_xbase_rec2(int p_dbptr);
    int  w_pack_xbase_base(int p_dbptr);
    int  w_set_xbase_recno(int recno,int p_dbptr);
    int  w_fox_set_recno(int recno,int p_fh);
    int  w_commit_xbase(int p_wptr,int backup,int p_dbptr);
    int  w_rollback_xbase(int p_wptr,int backup,int p_dbptr);
    int  w_append_from_sdf(char *p_fn,int p_fn_size,int p_dbptr);
    int  w_copy_to_sdf(char *p_fn,int p_fn_size,int p_dbptr);
    int  w_zap_xbase(int p_dbptr);
    int  w_clr_recvar(int p_dbptr);
    int  w_clr_recvar2(void);
    int  w_find_empty_file(char *str,int str_size,int p_dbptr);
    int  w_find_empty_ffile(char *str,int str_size,int p_wptr);
    int  w_find_empty_mfile(char *str,int str_size,int p_dbptr);
    int  w_fox_use(char *fn1,int fn1_size);
    int  w_fox_append(int p_dbptr);
    int  w_fox_del_num(void);
    int  w_fox_pack(char *,int);
    int  w_fox_go(int r);
    int  w_fox_close(void);
    int  w_fld_cpy(int p_dbptr,char *p_fld,int p_fld_size,char *p_val,int p_val_size);
    int  w_fld_sav(int p_dbptr,char *p_fld,int p_fld_size,char *p_val,int p_val_size);
    int  w_there_is_a(char *s,int s_size);
/*
};

class bw_xbase_bua
{
*/
  private:

    int  mn_state_bff_in_use[STRU_NUM]; /* database in use */
    //int  mn_state4[STRU_NUM]; /* current rec modified */
    int  mn_state_dbf_modi[STRU_NUM]; /* database modified */
    //int  mn_state7[STRU_NUM][WIN_NUM];  /* finding mark */
    int  mn_state_in_srch[WIN_NUM][STRU_NUM];  /* finding file is open this win*/
    //int  mn_state10[STRU_NUM]; /* finding file basep*/

    int mn_recno[STRU_NUM][WIN_NUM][3];
    int mn_rec_cntr[STRU_NUM];
    int  mn_fld_cntr[STRU_NUM];
    int  mn_len_cntr[STRU_NUM]; /*field number,record lenght */
    int  mn_lnktab[STRU_NUM];

    char ms_scrnvar[WIN_NUM][SMG_SIZE];

    char mn_memno[STRU_NUM][MEM_FLD_LEN+3];
    char mn_mem_ext[STRU_NUM][EXT_SIZE];
    char mn_mem_fn[STRU_NUM][FN_SIZE];
    int  mn_mem_inuse[STRU_NUM];
    int  mn_mem_wptr[STRU_NUM];

    char ms_bmp_name[SMG_SIZE];
    char ms_recvar[REC_SIZE];
    char ms_recvar2[REC_SIZE][2];

    char ms_basename[STRU_NUM][FN_SIZE];
    char ms_basedir[STRU_NUM][FN_SIZE];

    int  mn_base_type[STRU_NUM];
    int  mn_base_backup[STRU_NUM];

    int  mn_enseri[STRU_NUM][WIN_NUM];
    int  mn_cur_seri[STRU_NUM][WIN_NUM];

    int  mn_carry_on[STRU_NUM];

    char ms_ext[STRU_NUM][EXT_SIZE];

    char ms_fext[WIN_NUM][EXT_SIZE];

    int t4_rec_num[4]; /* 0-record counter,1-field number,2-record length,3-record no. */
    
    char t4_fldname[FLD_IN_XBASE][10+1];
    int  t4_fldtype[FLD_IN_XBASE];
    int  t4_fldlen[FLD_IN_XBASE];
    int  t4_flddec[FLD_IN_XBASE];
    int  t4_fldposi[FLD_IN_XBASE];

  public:

    int  get_mn_state_bff_in_use(int sptr);
    //int  get_mn_state4(int sptr);
    int  get_mn_state_dbf_modi(int sptr);
    //int  get_mn_state7(int sptr,int p_wptr);
    int  get_mn_state_in_srch(int p_wptr,int sptr);
    //int  get_mn_state10(int sptr);

    int  set_mn_state_bff_in_use(int sptr,int val);
    //int  set_mn_state4(int sptr,int val);
    int  set_mn_state_dbf_modi(int sptr,int val);
    //int  set_mn_state7(int sptr,int p_wptr,int val);
    int  set_mn_state_in_srch(int p_wptr,int sptr,int val);
    //int  set_mn_state10(int sptr,int val);

    int get_mn_recno(int sptr,int p_wptr,int p02);
    int  set_mn_recno(int sptr,int p_wptr,int p02,int val);

    int  get_mn_rec_cntr(int sptr);
    int  set_mn_rec_cntr(int sptr,int val);
    int  get_mn_fld_cntr(int sptr);
    int  set_mn_fld_cntr(int sptr,int val);
    int  get_mn_len_cntr(int sptr/*,int p01*/);
    int  set_mn_len_cntr(int sptr/*,int p01*/,int val);
    int  get_mn_lnktab(int sptr);
    int  set_mn_lnktab(int sptr,int val);

    int  get_ms_scrnvar(int p_wptr,char *s1,int s1_size);
    int  set_ms_scrnvar(int p_wptr,char *s1,int s1_size);
    int  get_c_ms_scrnvar(int p_wptr,int ptr1);
    int  set_c_ms_scrnvar(int p_wptr,int ptr1,int val);

    int  get_mn_memno(int sptr,char *s1,int s1_size);
    int  get_mn_mem_ext(int sptr,char *s1,int s1_size);
    int  get_mn_mem_fn(int sptr,char *s1,int s1_size);
    int  get_mn_mem_inuse(int sptr);
    int  get_mn_mem_wptr(int sptr);

    int  set_mn_memno(int sptr,char *s1,int s1_size);
    int  set_mn_mem_ext(int sptr,char *s1,int s1_size);
    int  set_c_mn_mem_ext(int sptr,int ptr1,int val);
    int  set_mn_mem_fn(int sptr,char *s1,int s1_size);
    int  set_c_mn_mem_fn(int sptr,int ptr1,int val);
    int  set_mn_mem_inuse(int sptr,int val);
    int  set_mn_mem_wptr(int sptr,int val);

    int  get_ms_bmp_name(char *s1,int s1_size);
    int  set_ms_bmp_name(char *s1,int s1_size);

    int  get_ms_recvar(int rptr);
    int  set_ms_recvar(int rptr,int val);
    int  get_ms_recvar2(int rptr,int p01);
    int  set_ms_recvar2(int rptr,int p01,int val);
    int  read_ms_recvar(int fh,int len);
    int  write_ms_recvar(int fh,int len);
    int  fgets_ms_recvar(FILE *fh,int len);
    int  fputs_ms_recvar(FILE *fh);

    int  get_ms_basename(int sptr,char *s1,int s1_size);
    int  set_ms_basename(int sptr,char *s1,int s1_size);
    int  set_c_ms_basename(int sptr,int ptr1,int val);
    int  get_ms_basedir(int sptr,char *s1,int s1_size);
    int  set_ms_basedir(int sptr,char *s1,int s1_size);
    int  set_c_ms_basedir(int sptr,int ptr1,int val);

    int  get_mn_base_type(int sptr);
    int  set_mn_base_type(int sptr,int val);
    int  get_mn_base_backup(int sptr);
    int  set_mn_base_backup(int sptr,int val);

    int  get_mn_enseri(int sptr,int p_wptr);
    int  get_mn_cur_seri(int sptr,int p_wptr);
    int  set_mn_enseri(int sptr,int p_wptr,int val);
    int  set_mn_cur_seri(int sptr,int p_wptr,int val);

    int  get_mn_carry_on(int sptr);
    int  set_mn_carry_on(int sptr,int val);

    int  get_ms_ext(int sptr,char *s1,int s1_size);
    int  set_ms_ext(int sptr,char *s1,int s1_size);
    int  set_c_ms_ext(int sptr,int ptr1,int val);

    int  get_ms_fext(int p_wptr,char *s1,int s1_size);
    int  set_c_ms_fext(int p_wptr,int ptr1,int val);

    int  get_t4_rec_num(int p03); 
    int  set_t4_rec_num(int p03,int val);

    int  get_t4_fldname(int fldptr,char *s1,int s1_size);
    int  set_t4_fldname(int fldptr,char *s1,int s1_size);

    int  get_t4_fldtype(int fldptr);
    int  get_t4_fldlen(int fldptr);
    int  get_t4_flddec(int fldptr);
    int  get_t4_fldposi(int fldptr);

    int  set_t4_fldtype(int fldptr,int val);
    int  set_t4_fldlen(int fldptr,int val);
    int  set_t4_flddec(int fldptr,int val);
    int  set_t4_fldposi(int fldptr,int val);
};

class bw_main
{
  public:

    char          ms_face_bmp0[FN_SIZE];
    int           mn_face_ptr2;

    OPENFILENAME  dlg_f1;
    PRINTDLG      dlg_f2;

    int        mn_color;
    int        mn_confirm;
    int        mn_field_posi;
    int        mn_var_ci;
    int        mn_cre_ok;
    int        mn_cre_menu;

    int        mn_main_xsize;
    int        mn_main_ysize;
    int        mn_main_xposi;
    int        mn_main_yposi;

    int        mn_lang;
    int        mn_800;
    int        mn_ibm_s3;

    HWND       mn_main_hnd;
    int        mn_hnd_id;

    int        mn_xchar;
    int        mn_ychar;
    float      mn_edit_xchar;
    float      mn_edit_ychar;
    int        mn_key;
    int        mn_key1;
    int        mn_key2;

    HINSTANCE  mn_ins;
    HINSTANCE  mn_pins;
    LPSTR      mn_cl;
    UINT       mn_msg;
    WPARAM     mn_wp;
    LPARAM     mn_lp;
    
  private:
  
    HWND       mn_hwnd[WIN_NUM];
    
  public:
  
    HWND       get_mn_hwnd(int wptr);
    int        set_mn_hwnd(int wptr,HWND val);
    
  public:
  
    HWND       mn_hwnd1;
    int        mn_show;

    HFONT      holdfont,hfont;
    HCURSOR    hcursor;
    HDC        hdc,hdc2;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    RECT        rt;
    MSG         msg;

    char   ms_m_bs1[FN_SIZE];
    char   ms_m_bs2[FN_SIZE];
    char   ms_m_bs3[FN_SIZE];

    char   ms_m_ts0[FN_SIZE];
    char   ms_m_ts1[FN_SIZE];
    char   ms_m_ts2[FN_SIZE];
    char   ms_m_ts3[FN_SIZE];
    char   ms_m_ts4[FN_SIZE];
    char   ms_m_ts5[FN_SIZE];
    char   ms_m_ts6[FN_SIZE];
    char   ms_m_ts7[FN_SIZE];

    char ms_cpy_f1[FN_SIZE];
    char ms_cpy_f2[FN_SIZE];
    char ms_seaname[FN_SIZE];
    char ms_seadir[FN_SIZE];

    char ms_home_dir[FN_SIZE];
    char ms_well_dir[FN_SIZE];
    char ms_work_dir[FN_SIZE];
    int  mn_pwd_mrk;
    int  mn_print;
    float mn_page_size;
    int  mn_page_line_num;

  public:

    int  w_ini_main(HINSTANCE p_pins);
    int  w_fetch_filename(char *str,int str_size);
    int  w_set_focus(HWND hwnd);
    int  w_set_focus_timer(HWND hwnd);
    int  w_set_focus2(HWND hwnd);
    int  w_set_lbutton(HWND hwnd,int hnd_id);

    int  get_view(char *fn,int fn_size,HWND hwnd,int ptr);
    int  get_edit(char *fn);
    int  get_setup(void);
    int  get_setup_save(void);
    int  get_xbase_open(void);
    int  get_skip(int rn);
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

    char   ms_face_bmp1[20][FN_SIZE];

  public:

    int    get_ms_face_bmp1(int p019,char *s1,int s1_size);
    int    set_ms_face_bmp1(int p019,char *s1,int s1_size);

  private:

    int    mn_caret_cre[WIN_NUM];

  public:

    int    get_mn_caret_cre(int p_wptr);
    int    set_mn_caret_cre(int p_wptr,int val);

  public:

    int mn_par_win_dbptr;
    int mn_par_win_ptr;
};

class bw_dialog
{
  private:

	 int      mn_mv_ptr1;
	 int      mn_mv_ptr2;

  public:

	 int      w_read_diadc(char *p_fn,int p_fn_size,int p_wptr);
	 int      w_mv_save_mem(char *s1,int s1_size,int p_wptr,char *s2,int s2_size);
	 int      w_dele_mem(char *s1,int p_wptr,char *s2);
         int      w_save_dialog(int p_wptr);
	 int      w_dele_dialog(int wp1,int wp2);
         int      w_clr_recvar_dialog(int p_wptr);
	 int      w_mv_add_val(char *s1,int s1_size,int p_wptr,char *s2,int s2_size);
	 int      w_mv_fet_val(char *s1,int s1_size,int p_wptr,char *s2,int s2_size);
	 int      w_mv_sav_var(char *s1,int s1_size,int p_wptr);
	 int      w_mv_get_var(char *s1,int s1_size,int p_wptr);
	 int      w_mv_exist(char *s1,int s1_size,int p_wptr);
         int      w_mv_add_name(char *str1,int str1_size);
	 int      w_mv_seri(char *str1,int str1_size,int p_wptr);
         int      w_mv_move_aft(int dd,int num);
	 int      w_mv_move_bef(int dd,int num);
	 int      w_echo_winrec_var(int p_wptr);
	 //int      w_mv_get_read_paint(char *s1,int s1_size,int p_wptr,char comm);
	 int      w_mv_get_read_g(char *s1,int s1_size,int p_wptr,char comm);
	 int      w_mv_get_read_r(char *s1,int s1_size,int p_wptr,char comm);

	 int      w_echo_winrec_read(int p_dbptr,int p_wptr,int mark);
         int        w_get_yy(char *p_s,int p_s_size);
         int        w_get_mm(char *p_s,int p_s_size);
         int        w_get_dd(char *p_s,int p_s_size);
         int      w_get_year(char *p_s,int p_s_size);
         int       w_get_mon(char *p_s,int p_s_size);
         int      w_get_time(char *p_s,int p_s_size);
         int      w_get_date(char *p_s,int p_s_size);
	 int       w_get_usr(char *p_s,int p_s_size);

	 int      tst_mem(void);
/*
};

class bw_dialog_bua
{
*/
  private:

    char     ms_mv_stor[MEM_VAR_SIZE];
    int      mn_mv_posi[MEM_VAR_NUM][2];  /* memory var posion & length */
    int      mn_mv_type[MEM_VAR_NUM][6];  /* memory var display_type,type,len,dec,window num,edit len */
    //int      mn_mv_getp[WIN_NUM];         /* cursor dist */

    char     ms_mv_name[MEM_VAR_NUM][11]; /* mem var name */
    char     ms_mv_getv[WIN_NUM][SMG_SIZE];

  public:

    int      get_ms_mv_stor(int mlptr);
    int      get_mn_mv_posi(int mvptr,int p01);
    int      get_mn_mv_type(int mvptr,int p05);
    //int     *get_mn_mv_getp(int p_wptr);
    //int      get_v_mn_mv_getp(int p_wptr);
    //int      set_v_mn_mv_getp(int p_wptr,int val);

    int      set_ms_mv_stor(int mlptr,int val);
    int      set_mn_mv_posi(int mvptr,int p01,int val);
    int      set_mn_mv_type(int mvptr,int p05,int val);
    int      set_mn_mv_getp(int p_wptr ,int val);

    int      get_ms_mv_name(int mvptr,char *s1,int s1_size);
    int      set_ms_mv_name(int mvptr,char *s1,int s1_size);
    int      set_c_ms_mv_name(int mvptr,int p0a,int val);

    int      get_ms_mv_getv(int p_wptr,char *s1,int s1_size);
    int      set_ms_mv_getv(int p_wptr,char *s1,int s1_size);
    int      set_c_ms_mv_getv(int p_wptr,int ptr1,int val);
};

class bw_rabox
{

  private:

    int   mn_rabox_ptr1;

  public:

    int w_rabox_ini(void);
    int w_read_radc(char *p_fn1,int p_fn1_size,int p_wptr);
    int w_save_rabox(int p_wptr);
    int w_dele_rabox(int wp1,int wp2);
    int w_set_radio_var(int l,int c,int p,int p_wptr);
    int w_echo_winrec_rabox(int p_wptr);
    int w_clr_recvar_rabox(int p_wptr);

    int tst_rabox(void);
/*
};

class bw_rabox_bua
{
*/
  private:

    int   mn_rabox[BUTTON_NUM_RA][4];  /* in use,pre val,seri number,window number */
    char  ms_rabox_name[BUTTON_NUM_RA][11];

  public:

    int   get_mn_rabox(int mptr,int p03);
    int   set_mn_rabox(int mptr,int p03,int val);

    int   get_ms_rabox_name(int mptr,char *s1,int s1_size);
    int   set_ms_rabox_name(int mptr,char *s1,int s1_size);
    int   set_c_ms_rabox_name(int mptr,int p0a,int val);
};

class bw_chkbox
{

  private:

    int      mn_chkbox_ptr1;

  public:

    int w_chkbox_ini(void);
    int w_read_chkdc(char *p_fn1,int p_fn1_size,int p_wptr);
    int w_save_chkbox(int p_wptr);
    int w_dele_chkbox(int wp1,int wp2);
    int w_echo_chk_change(int link,int p_wptr);
    int w_echo_winrec_chkbox(int p_wptr);
    int w_clr_recvar_chkbox(int p_wptr);

    int tst_chkbox(void);
/*
};

class bw_chkbox_bua
{
*/
  private:

    int      mn_chkbox[BUTTON_NUM_CHS][4]; /* in use,pre val,seri number,window number */
    char     ms_chkbox_name[BUTTON_NUM_CHS][11];

  public:

    int      get_mn_chkbox(int cptr,int p03);
    int      set_mn_chkbox(int cptr,int p03,int val);

    int      get_ms_chkbox_name(int cptr,char *s1,int s1_size);
    int      set_ms_chkbox_name(int cptr,char *s1,int s1_size);
    int      set_c_ms_chkbox_name(int cptr,int p0a,int val);
};

class bw_buttonvar
{

  private:

   int      t5_btn_tot_ptr;

  public:

   char     t5_btn_com_str[SMG_SIZE];
   int      t5_btn_cur_ptr;
   int      t5_btn_dict_ptr;

  public:

    int w_button_find_seri(int ptr1);
    int w_read_btndc(char *p_fn1,int p_fn1_size,int p_wptr);
    int w_dele_button(int wptr);
    int w_button_comm(int p1,int state);
    int w_button_pntr(char *s1,int s1_size,int p1);

    int tst_button(void);
    int tst_button2(void);
/*
};

class bw_buttonvar_bua
{
*/
  private:

    int      t5_btn_wind[BUTTON_NUM_BTN];
    int      t5_btn_mcntr[BUTTON_NUM_BTN];
    char     t5_btn_name[BUTTON_NUM_BTN][11];
    char     t5_btn_button[BUTTON_NUM_BTN][81];
    char     t5_btn_comm[BUTTON_NUM_BTN][81];
    char     t5_btn_focus[BUTTON_NUM_BTN][81];

  public:

    int      get_t5_btn_wind(int mptr);
    int      get_t5_btn_mcntr(int mptr);

    int      set_t5_btn_wind(int mptr,int val);
    int      set_t5_btn_mcntr(int mptr,int val);

    int      get_t5_btn_name(int mptr,char *s1,int s1_size);
    int      set_t5_btn_name(int mptr,char *s1,int s1_size);
    int      set_c_t5_btn_name(int mptr,int p0a,int val);

    int      get_t5_btn_button(int mptr,char *s1,int s1_size);
    int      set_t5_btn_button(int mptr,char *s1,int s1_size);
    int      set_c_t5_btn_button(int mptr,int ptr1,int val);

    int      get_t5_btn_comm(int mptr,char *s1,int s1_size);
    int      set_t5_btn_comm(int mptr,char *s1,int s1_size);
    int      set_c_t5_btn_comm(int mptr,int ptr1,int val);

    int      get_t5_btn_focus(int mptr,char *s1,int s1_size);
    int      set_t5_btn_focus(int mptr,char *s1,int s1_size);
    int      set_c_t5_btn_focus(int mptr,int ptr1,int val);
};

class bw_fldstru
{
  public:

    int   mn_field_num;
    
    int   mn_master;

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
    int w_find_fldpntr0(int i);
    int w_find_fldpntr1(int i);
    int w_find_fldname(int i,int j,char *str,int str_size);

    int w_echo_winrec(int p_wptr);
    int w_fetch_rec(int p_dbptr,int p_wptr,int seri);
    //int w_tv_get_read_paint(char *fn,int fn_size,int p_wptr,int l,int c,char comm);
    int w_tv_get_read_g(char *fn,int fn_size,int p_wptr,int l,int c,char comm);
    int w_tv_get_read_r(char *fn,int fn_size,int p_wptr,int l,int c,char comm);
    int w_get_tab_var(char *fn,int fn_size,int p_dbptr,char *ca,int ca_size);
    int w_cmp_tab_var(char *fn,int fn_size,int p_dbptr,char *ca,int ca_size);
    int w_sav_tab_var(char *fn,int fn_size,int p_dbptr,char *ca,int ca_size);
    int w_page_up(int p_dbptr,int p_wptr);
    int w_page_down(int p_dbptr,int p_wptr);
    int w_page_down2(int p_dbptr,int p_wptr);
    int w_first_editposi(int p_dbptr,int p_wptr);
    int w_last_editposi(int p_dbptr,int p_wptr);
    int w_insert_rec(int p_dbptr,int p_wptr);
    int w_add_rec(int p_dbptr,int p_wptr);
    int w_delete_rec(int p_dbptr,int p_wptr);
    int w_rollback_base(int p_dbptr,int p_wptr);
    int w_commit_base(int p_dbptr,int p_wptr);
    int w_link_window(int p_dbptr,int p_wptr);
    int w_is_card(int p_dbptr,int p_wptr);
    int w_find_cond(int p_dbptr,int p_wptr);
    int w_find_key(int p_dbptr,int p_wptr);
    int w_find_recno(int p_dbptr,int p_wptr);
    int w_find_end(int p_dbptr,int p_wptr);
    int w_find_exit(int p_wptr);
    int w_find_cond_ok(int p_dbptr);
    int w_clr_condition(int p_dbptr);

    int w_edit_memo(int p_dbptr,int p_wptr,char *fldname,int fldname_size);
    int w_edit_memo_close(int p_wptr);
    int w_edit_memo_add(int p_dbptr,int p_wptr,char *fldname,int fldname_size);
    int w_wps_to_txt(char *fn1,int fn1_size,char *fn2,int fn2_size);

    int tst_stru(void);
    int tst_stru2(void);
/*
};

class bw_fldstru_bua
{
*/
  private:

    int   t2_fldpntr[STRU_NUM][2];
    int   t2_fldtype[FLD_IN_BASE];
    int   t2_fldlen[FLD_IN_BASE];
    int   t2_flddec[FLD_IN_BASE];
    int   t2_fldposi[FLD_IN_BASE];

    char  t2_fldname[FLD_IN_BASE][11];

  public:

    int   get_t2_fldpntr(int sptr,int p01);
    int   get_t2_fldtype(int fbptr);
    int   get_t2_fldlen(int fbptr);
    int   get_t2_flddec(int fbptr);
    int   get_t2_fldposi(int fbptr);

    int   set_t2_fldpntr(int sptr,int p01,int val);
    int   set_t2_fldtype(int fbptr,int val);
    int   set_t2_fldlen(int fbptr,int val);
    int   set_t2_flddec(int fbptr,int val);
    int   set_t2_fldposi(int fbptr,int val);

    int   get_t2_fldname(int fbptr,char *s1,int s1_size);
    int   set_t2_fldname(int fbptr,char *s1,int s1_size);
    int   set_c_t2_fldname(int fbptr,int p0a,int val);
    int   get_c_t2_fldname(int fbptr,int p0a);

    int w_up_line(int p_dbptr,int p_wptr);
    int w_down_line(int p_dbptr,int p_wptr);
    int w_up_line2(int p_dbptr,int p_wptr);
    int w_down_line2(int p_dbptr,int p_wptr);
    int w_last_line(int p_dbptr,int p_wptr);
    int w_first_line(int p_dbptr,int p_wptr);
    int w_have_next_rec(int p_dbptr,int p_wptr);
    int w_have_prev_rec(int p_dbptr,int p_wptr);
    int w_be_linked(int p_dbptr,int p_wptr);

    int w_have_next_rec2(int p_dbptr,int p_wptr,int recno);
    int w_have_prev_rec2(int p_dbptr,int p_wptr,int recno);


};

class bw_win
{

  private:

    int           scntr;

    char          ms_texts1[12];
    char          ms_texts2[12];
    char          ms_texts3[12];
    char          ms_texts4[12];
    char          ms_texts5[12];
    char          ms_texts6[12];
    char          ms_texts7[12];
    char          ms_texts8[12];
    char          ms_texts9[12];
    char          ms_texts10[12];

  public:

    int       mn_mark;

    int       mn_h_ci_total_ptr;     /* ci counter & ptr */
    //int       mn_h_ptr;              /* windows number for one group */

    //int       mn_ptr21;   /* 1 should echo read var */
    //int       mn_ptr22;   /* 1 should echo link var */
    //int       mn_ptr23;   /* 1 should echo calc var */

  public:

    //int       mn_h_w_total_ptr,mn_h_w_cur_ptr;     /* total hwnd ptr & current hwnd ptr */

    int       mn_ptr_new_win;               /* empty array pntr */
    int       mn_menu_cmd;
    int       mn_menu_seri;
    
  private:

    int       pline[WIN_NUM];
    int       pcolu[WIN_NUM];
    
    int       fld_l[WIN_NUM];
    int       fld_c[WIN_NUM];

  public:

    int       get_pline(int wptr);
    int       get_pcolu(int wptr);
    int       set_pline(int wptr,int val);
    int       set_pcolu(int wptr,int val);

    int       get_fld_l(int wptr);
    int       get_fld_c(int wptr);
    int       set_fld_l(int wptr,int val);
    int       set_fld_c(int wptr,int val);

  public:

    int       mn_mouse_y;
    int       mn_mouse_x;

  public:

    int w_cre_ci_button(int wptr,char *s1,int s1_size,int p6,int p7,int p8,int i,char *,int);
    int w_cre_ci_edit(int wptr,int p6,int p7,int p8,int i);
    int w_cre_ci_radio(int wptr,int p6,int p7,int p8,int i,char *,int);
    int w_cre_ci_check(int wptr,int p6,int p7,int p8,int i,char *,int);

    int w_first_grp(void);
    int w_ini_win(void);
    int w_login_win(int p1,char *mn_name,int mn_name_size,char *find_name,int find_name_size);
    int w_login_wwin(int i);
    int w_close_win(int p1);
    int w_close_subwin(int p1);
    int w_dele_win_ptr(int p_wptr);
    int w_dele_win_ptr_wins_dbf(int p_wptr);
    int w_dele_xbase_state(int p_wptr);

    int tst_win1(void);
    int tst_win1_fld(void);
    int tst_win2(void);
    int tst_win2_fld_in_win(void);
    int tst_win3(void);
    int tst_win4(void);
    int tst_win5(void);
    int tst_win6_ci_ptr(void);
    int tst_win7_focus_buf(void);

    int w_find_winhand(HWND hwnd);
    int w_mouse_infield(int p_wptr,int y,int x);
    int w_adjust_edit(int p_wptr);
    int w_find_hnd(int p1,int p2,int p3);
    int w_find_winfname(int w,int l,int c,char *s1,int s1_size);
    int w_find_winflen(int w,int l,int c);
    int w_set_winfedit(int w,int l,int c,int v);
    int w_field_info3(int w);
    int w_read_winfile(char *p_fn2,int p_fn2_size);
    int w_echo_winrec_paint(int wptr,int mark);
    int w_field_info1(int wptr,int mark);
    int w_cre_win_button(int wptr,int mark);
    int w_cre_win_edit(int wptr,int mark);
    int w_cre_win_radio(int wptr,int mark);
    int w_cre_win_check(int wptr,int mark);
    int w_next_field(int i);
    int w_next_afield(int i);
    int w_right_field(int i);
    int w_left_field(int i);
    int w_up_field(int i);
    int w_down_field(int i);
    int w_down_line(int p_ptr,int i);
    int w_up_line(int p_ptr,int i);
    int w_echo_var_pa(int ,char *p_var1);
    int w_field_type(char *str);
    int w_fetch_fld_style(char *tfn,int tfn_size,char *tn,int tn_size,int *tr,char *fn,int fn_size,int p_wptr);
    int w_find_base_name(char *str,int str_size,int p_wptr);
    int w_find_fld_name(char *str,int str_size,int p_wptr);
    int w_find_recno_name(char *str,int str_size);
    int w_fld_set_base(char *p_fldtable,int p_fldtable_size,int ptr1,int p_wptr);
    int w_fld_set_recno(int p_fldrecno,int ptr2);
    int w_fld_set_fld(char *p_fldname,int p_fldname_size);
    int w_field_info2(int p_wptr);
    int w_cnt_winline(int p_dbptr,int p_wptr,int line);

    int w_atten1(HWND hwnd,char *p_fn1);
    int w_atten2(HWND hwnd);
    int w_atten3(HWND hwnd);
    int w_atten4(HWND hwnd);
    int w_atten5(HWND hwnd);
    int w_atten6(HWND hwnd);
    int w_atten7(HWND hwnd);
    int w_atten7a(HWND hwnd);
    int w_atten7b(HWND hwnd);
    int w_atten8(HWND hwnd,char *s1);
    int w_atten9(HWND hwnd,char *s1);
    int w_atten9a(HWND hwnd,char *s1);
    int w_atten10(HWND hwnd);
    int w_atten11(HWND hwnd);
    int w_atten12(HWND hwnd);
    int w_atten13(HWND hwnd,char *s1);
    int w_atten14(HWND hwnd,char *s1);
    int w_atten15(HWND hwnd,char *s1);
    int w_atten16(HWND hwnd,char *s1);
    int w_atten17(HWND hwnd,char *s1);
    int w_atten18(HWND hwnd,char *s1);
    int w_atten19(HWND hwnd,char *s1);
    int w_atten20(HWND hwnd,char *s1);
    int w_atten21(HWND hwnd);
    int w_atten22(HWND hwnd);
    int w_atten23(HWND hwnd,char *s1);
    int w_atten24(HWND hwnd,char *s1);
    int w_atten25(HWND hwnd,char *s1);
    int w_atten26(HWND hwnd,char *s1);
    int w_atten27(HWND hwnd,char *s1);
    int w_atten28(HWND hwnd,char *s1);
    int w_atten29(HWND hwnd,char *s1);
    int w_atten30(HWND hwnd,char *s1);
    int w_atten31(HWND hwnd,char *s1);
    int w_atten32(HWND hwnd,char *s1);
    int w_atten33(HWND hwnd,char *s1);
    int w_atten34(HWND hwnd,char *s1);
    int w_atten35(HWND hwnd,char *s1);
    int w_atten36(HWND hwnd,char *s1);
    int w_atten37(HWND hwnd,char *s1);
    int w_atten38(HWND hwnd,char *s1);
    int w_atten39(HWND hwnd);
    int w_atten40(HWND hwnd);
    int w_atten41(HWND hwnd);
    int w_atten42(HWND hwnd);
    int w_atten43(HWND hwnd);
    int w_atten44(HWND hwnd);
    int w_atten45(HWND hwnd,char *s1);
    int w_atten46(HWND hwnd,char *s1);
    int w_atten47(HWND hwnd,char *s1);
    int w_atten48(HWND hwnd,char *s1);
    int w_atten49(HWND hwnd);
    int w_atten50(HWND hwnd);
    int w_atten51(HWND hwnd);
    int w_atten52(HWND hwnd);
    int w_atten53(HWND hwnd);
    int w_atten54(HWND hwnd);
    int w_atten55(HWND hwnd);
    int w_atten56(HWND hwnd);
    int w_atten57(HWND hwnd,int l);
    int w_atten58(HWND hwnd);
    int w_atten59(HWND hwnd);
    int w_atten60(HWND hwnd);
    int w_atten61(HWND hwnd);
    int w_atten62(HWND hwnd);
    int w_atten63(HWND hwnd);
    int w_atten64(HWND hwnd,char *s1);
    int w_atten65(HWND hwnd);
    int w_atten66(HWND hwnd);
    int w_atten67(HWND hwnd);
    int w_atten68(HWND hwnd);

    int tst_hptr3(void);
    int tst_hptr4(void);
/*
};

class bw_win_bua
{
*/
  private:

    char          t_fldname[FLD_IN_SCRN][FLD_NAME_SIZE];
    char          t_fldtype[FLD_IN_SCRN];
    char          t_fldbase[FLD_IN_SCRN];
    int           t_fldseri[FLD_IN_SCRN];
    int           t_fldlen[FLD_IN_SCRN];
    int           t_flddec[FLD_IN_SCRN];
    int           t_fldedt[FLD_IN_SCRN];

    int           t_fldseri_tmp[FLD_IN_SCRN];
    char          t_field_tmp[FLD_IN_SCRN][10];

    int           mn_state_link_modi[WIN_NUM]; /* link modified */
    int           mn_state_calc_modi[WIN_NUM]; /* calc modified */
    int           mn_switch_bmp[WIN_NUM];

    int           mn_ptr_fld_in_win[WIN_NUM][4];   /* field in table window, current&first&last&echo ptr */

    int           mn_h_w_ptr[WIN_NUM][9];   /* start,end,current,parent ptr ,parent focus*/
    int           mn_h_ci_ptr[HND_NUM][5];  /* window number,x,y, hwnd number,parent hwnd */
    //int           mn_h_up_ptr[WIN_NUM][2];  /* up scrn seg posi */

    HWND          mn_phh[WIN_NUM];         /* win_ptr_grp_ptr's windows handle */

    //int           mn_ptr_win_mark[WIN_NUM];          /* current table window pntr */
    int           mn_ptr_grp_id[WIN_NUM];            /* window table in use */
    //int           mn_ptr_grp_ptr[WIN_NUM][5];         /* every table window's group number(0) and group's &first(0)&current(1)&last(2) tablewin number */
    int           mn_ptr_wins_dbf[STRU_NUM][WIN_NUM];/* database file in buffer, pntr beg & end */
    int           mn_ptr_get_rd[WIN_NUM];            /* get_read id */

    int           mn_msgboxlock[WIN_NUM];

    int           mn_con[WIN_NUM][4];       /* window conner posion */
    int           mn_style[WIN_NUM][WIN_STYLE_NUM];
    FARPROC       mn_proc[HND_NUM];
    HWND          mn_hnd[HND_NUM];
    int           mn_create_menu[WIN_NUM];
    int           mn_linep[WIN_NUM][2];
    int           mn_is_link[WIN_NUM];
    int           mn_is_calc[WIN_NUM];
    int           mn_memo_basep[WIN_NUM];

    int          mn_timer[WIN_NUM];

    int           mn_ci_mode[WIN_NUM];
    int           mn_ci_posi[WIN_NUM][2];

    FARPROC       mn_tproc;

  public:

	HWND get_ci_mhnd(HWND hwnd);

  public:

    int  get_t_fldname(int p1,char *sval,int sval_size);
    int  set_t_fldname(int p1,char *sval,int sval_size);
    int  get_t_fldtype(int p1);
    int  set_t_fldtype(int p1,int val);
    int  get_t_fldbase(int p1);
    int  set_t_fldbase(int p1,int val);
    int  get_t_fldseri(int p1);
    int  set_t_fldseri(int p1,int val);
    int  get_t_fldlen(int p1);
    int  set_t_fldlen(int p1,int val);
    int  get_t_flddec(int p1);
    int  set_t_flddec(int p1,int val);
    int  get_t_fldedt(int p1);
    int  set_t_fldedt(int p1,int val);
    int  set_c_t_fldname(int p1,int p2,char c1);

    int  get_t_fldseri_tmp(int p1);
    int  set_t_fldseri_tmp(int p1,int val);
    int  get_t_field_tmp(int p1,char *sval,int sval_size);
    int  set_t_field_tmp(int p1,char *sval,int sval_size);
    int  set_c_t_field_tmp(int p1,int p2,char c1);

    int  get_mn_state_link_modi(int p_wptr);         /* link modified */
    int  set_mn_state_link_modi(int p_wptr,int val); /* link modified */
    int  get_mn_state_calc_modi(int p_wptr);         /* calc modified */
    int  set_mn_state_calc_modi(int p_wptr,int val); /* calc modified */

    int  get_mn_switch_bmp(int p_wptr);
    int  set_mn_switch_bmp(int p_wptr,int val);

    int  get_mn_ptr_fld_in_win(int p_wptr,int ptr);   /* table in screen current&first&last&echo window ptr */
    int  set_mn_ptr_fld_in_win(int p_wptr,int ptr,int val);
    int  get_mn_h_w_ptr(int p_wptr,int ptr);  /*  start,end,current,parent ptr ,parent focus*/
    int  set_mn_h_w_ptr(int p_wptr,int ptr,int val);
    //int  get_mn_h_up_ptr(int p_wptr,int ptr);  /* up scrn segment posion */
    //int  set_mn_h_up_ptr(int p_wptr,int ptr,int val);

    HWND get_mn_phh(int p_wptr);          /* mn_ptr_grp_ptr's windows handle */
    int  set_mn_phh(int p_wptr,HWND hwnd);

    //int get_mn_ptr_win_mark(int p_wptr);
    //int set_mn_ptr_win_mark(int p_wptr,int val);
    int get_mn_ptr_grp_id(int p_wptr);
    int set_mn_ptr_grp_id(int p_wptr,int val);
    //int get_mn_ptr_grp_ptr(int p_wptr,int ptr04);
    //int set_mn_ptr_grp_ptr(int p_wptr,int ptr04,int val);
    int get_mn_ptr_wins_dbf(int p_dbptr,int p_wptr);
    int set_mn_ptr_wins_dbf(int p_dbptr,int p_wptr,int val);
    int get_mn_ptr_get_rd(int p_wptr);
    int set_mn_ptr_get_rd(int p_wptr,int val);


    int get_mn_msgboxlock(int p_wptr);
    int set_mn_msgboxlock(int p_wptr,int val);


    int get_mn_con(int p_wptr,int p03);
    int set_mn_con(int p_wptr,int p03,int val);
    int get_mn_style(int p_wptr,int ptr);
    int set_mn_style(int p_wptr,int ptr,int val);

    FARPROC   get_mn_proc(int ptr);
    int       set_mn_proc(int ptr,FARPROC fproc);
    HWND      get_mn_hnd(int ptr);
    int       set_mn_hnd(int ptr,HWND hwnd);
    int       get_mn_h_ci_ptr(int hptr,int p04);
    int       set_mn_h_ci_ptr(int hptr,int p04,int val);
    int       get_mn_create_menu(int p_wptr);
    int       set_mn_create_menu(int p_wptr,int val);
    int       get_mn_linep(int p_wptr,int p01);
    int       set_mn_linep(int p_wptr,int p01,int val);
    int       get_mn_is_link(int p_wptr);
    int       set_mn_is_link(int p_wptr,int val);
    int       get_mn_is_calc(int p_wptr);
    int       set_mn_is_calc(int p_wptr,int val);
    int       get_mn_memo_basep(int p_wptr);
    int       set_mn_memo_basep(int p_wptr,int val);

    int       get_mn_timer(int p_wptr);
    int       set_mn_timer(int p_wptr,int val);

    int       get_mn_ci_mode(int p_wptr);
    int       set_mn_ci_mode(int p_wptr,int val);

    int       get_mn_ci_posi(int p_wptr,int p01);
    int       set_mn_ci_posi(int p_wptr,int p01,int val);
/*
};

class bw_win_bub
{
*/
  private:

    char ms_tabname[2][STRU_NUM][FN_SIZE];/* window group 1-table & 0-structure file name */
    char ms_window_name[WIN_NUM][FN_SIZE];
    char ms_find_name[WIN_NUM][FN_SIZE];

  public:

    int  get_ms_tabname(int p1,int bp,char *s1,int s1_size);  /* window group 1-table & 0-structure file name */
    int  set_ms_tabname(int p1,int bp,char *s1,int s1_size);  /* window group 1-table & 0-structure file name */
    int  get_ms_window_name(int p_wptr,char *s1,int s1_size);
    int  set_ms_window_name(int p_wptr,char *s1,int s1_size);
    int  get_ms_find_name(int p_wptr,char *s1,int s1_size);
    int  set_ms_find_name(int p_wptr,char *s1,int s1_size);

  private:

    int  mn_focus_buf[BW_WIN_FOCUS_NUM];

  public:

    int  mn_focus_ptr1;
    int  mn_focus_ptr2;

  public:

    int  get_mn_focus_buf(int ptr);
    int  set_mn_focus_buf(int ptr,int val);
    int  delete_win_focus(int ptr);

  private:

    int mn_created[WIN_NUM];
    int mn_painted[WIN_NUM];
    int mn_focused[WIN_NUM];
    int mn_focused_wp[WIN_NUM];

  public:

    int get_mn_painted(int);
    int set_mn_painted(int,int);
    int get_mn_created(int);
    int set_mn_created(int,int);
    int get_mn_focused(int);
    int set_mn_focused(int, int);
    int get_mn_focused_wp(int);
    int set_mn_focused_wp(int, int);
};

class bw_inkey
{
  public:

    char  ms_cp_buff[CPY_BSIZE];

  public:

    int keystart(void);
    int refresh(void);
    int keyend(void);
    int w_set_dir(char *s,int s_size);
    int w_get_dir(char *s,int s_size);
    int inkey(UINT msg,WPARAM wp);
    //int strpcat(char *s1,int p,char *s2);
    int strtrim(char *str,int str_size);
    int strltrim(char *str,int str_size);
    int cpy_string(char *s1,int s1_size,char *s2,int s2_size);
    int cut_string(char *p_s1,int p1,int p2,int p_s1_size,char *p_s2,int p_s2_size);
    long str2long(char *str,int str_size);
    float str2float(char *str,int str_size);
    int str2int(char *string,int string_size);
    int int2str(int val,char *string,int string_size);
    int float2str(float val,char *str,int str_size);
    int long2str(long l,char *str,int str_size);
    int strfind(char *p1,int p1_size,char *p2,int p2_size);
    int strempty(char *p1,int p1_size);
    int upper(char c1);
    int lower(char c1);
    int uppers(char *s1,int);
    int lowers(char *s1,int);
    //int mon2int(char *str);
    //int mon2day(int mon);
    //int int2mon(int i,char *mon);
    //int dateadd(char *s1,char *s2,int i);
    //int cdate(char *p1,char *p2);
    int zero2space(char *p,int p_size);
    int w_find_file(char *fn1,int fn1_size);
    //int w_find_dir(char *fn1);
    int w_fname_ok(char *fn1,int fn1_size);
    //int w_cpy_dir(char *ms_cpy_f1,char *ms_cpy_f2);
    int w_cpy_file(char *fn1,int fn1_size,char *fn2,int fn2_size);
    int w_del_file(char *fn1,int fn1_size);
    int str_seek_char_first(char *p_str,int p_str_size,char c1);
    int str_seek_char_last(char *p_str,int p_str_size,char c1);
    //int str_cmp(char *s1,int l1,char *s2,int l2);

	int w_chs_string_cut(char *p_str,int p_n);
    int str_has_null(char *s1,int s1_size);
};

class bw_getread
{

  private:

    int   smg_insert;
    int   smg_ptr;
    int   smg_ptr2;
    int   smg_color1,smg_color2;

    //int   mn_get_ptr;
    //int   mn_get_link;
  public:

	  int   mn_chns_char;

  private:

    char  mn_chns_str[3];
    int   mn_cur1,mn_cur2;

  public:
    int   mn_p1;

 private:
    int   mn_edit_pain;
    int   mn_color;
    int   mn_confirm;           /* need enter or not need enter */
    int   mn_edit_mode[GET_NUM];/* 0--box,1--line    */
    int   mn_p_y;
    int   mn_p_x;

    FILE *deb_record_fp;

  public:

    int  tst_getread(void);

    int  get_read_ini(void);
    //int  get_read_login(void);
    int  get_read_logout(int ptr);
    int  get_read(int p_wptr,int scrn_l,int scrn_c,char *atten,
	    char *string,int datalen,char datatype,
	    char command,int datalen2,int datadec,
	    char link,int color,int posi,int array_ptr);

    int deb_record_init(void);
    int deb_record_close(void);
    int deb_record(char *p_str1);

  private:

    int  get_txt(int p_wptr,int scrn_l,int scrn_c,char *atten,
           int datalen,int datalen2,char link,
	   int ptr,int color,int posi);
    int  get_num(int p_wptr,int scrn_l,int scrn_c,char *atten,
	   int datalen,int datalen2,char link,
	   int ptr,int color,int dec,int posi);
    int  get_num_conv(int datalen2,int dec);
    int  get_txt_after(char *data,int l2,int l1,int p1);
    int  get_txt_before(char *data,int l1,int p1);

    int calc_len(void);
    int erase_last_char(int p1);

/*
};

class bw_get_bua
{
*/
  private:

    int    smg_line[GET_NUM];
    int    smg_colu[GET_NUM];
    char   smg_data[SMG_SIZE];
    char   smg_string[GET_NUM][SMG_SIZE];
    char   smg_type[GET_NUM];
    int    smg_dlen[GET_NUM];
    int    smg_dlen_real[GET_NUM];
    int    smg_ddec[GET_NUM];
    char   smg_link[GET_NUM];
    int    smg_color[GET_NUM];
    int    smg_posi[GET_NUM];
    char   smg_atte[GET_NUM][SMG_SIZE];
    int    smg_read_id[GET_NUM];
    char   smg_modi[GET_NUM];

  public:

    int   get_smg_line(int gptr);
    int   get_smg_colu(int gptr);
    int   get_smg_data(int ptr1);
    int   get_s_smg_data(char *s1,int s1_size);
    int   get_smg_string(int gptr,char *s1,int s1_size);
    int   get_c_smg_string(int gptr,int ptr1);
    int   get_smg_type(int gptr);
    int   get_smg_dlen(int gptr);
    int   get_smg_dlen_real(int gptr);
    int   get_smg_ddec(int gptr);
    int   get_smg_link(int gptr);
    int   get_smg_color(int gptr);
    int   get_smg_posi(int gptr);
    int   get_smg_atte(int gptr,char *s1,int s1_size);
    int   get_smg_read_id(int gptr);
    int   get_smg_modi(int gptr);

  public:

    int   set_smg_line(int gptr,int val);
    int   set_smg_colu(int gptr,int val);
    int   set_smg_data(int ptr1,int val);
    int   set_smg_string(int gptr,char *s1,int s1_size);
    int   set_c_smg_string(int gptr,int ptr1,int val);
    int   set_smg_type(int gptr,int val);
    int   set_smg_dlen(int gptr,int val);
    int   set_smg_dlen_real(int gptr,int val);
    int   set_smg_ddec(int gptr,int val);
    int   set_smg_link(int gptr,int val);
    int   set_smg_color(int gptr,int val);
    int   set_smg_posi(int gptr,int val);
    int   set_smg_atte(int gptr,char *s1,int s1_size);
    int   set_smg_read_id(int gptr,int val);
    int   set_smg_modi(int gptr,int val);
};


