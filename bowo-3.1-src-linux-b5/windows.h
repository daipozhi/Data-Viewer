//------------------------------------------------------
//
//    Define for Windows Var
//
//------------------------------------------------------

#define   FALSE        0
#define   TRUE         1
#define   HFONT        int
#define   HDC          int
#define   FARPROC      int
#define   WNDPROC      int
#define   OPENFILENAME int
#define   PRINTDLG     int
#define   HINSTANCE    int
#define   LPSTR        int
#define   LONG         int
#define   UINT         int
#define   WPARAM       int
#define   LPARAM       int
#define   HCURSOR      int
#define   PAINTSTRUCT  int
#define   TEXTMETRIC   int
#define   RECT         int
#define   MSG          int
#define   DOCINFO        int
#define   HWND           int
#define   OEM_FIXED_FONT 0
#define   HPALETTE       int
#define   HGLOBAL        int
#define   BOOL           int
#define   DWORD          int
#define   LPBITMAPINFOHEADER  int
#define   WORD           int
#define   HMENU			int
#define   WNDCLASS		int

#define   IDYES			1
#define   IDNO			2
#define   IDCANCEL		3
#define   IDOK			4
#define   IDRETRY		5

#define   GWL_ID		0

#define   BM_SETSTATE		0
#define   BM_GETCHECK		1
#define   BM_SETCHECK		211

#define   BS_RADIOBUTTON       2
#define   BS_CHECKBOX          4
#define   BS_PUSHBUTTON        8

#define   CS_HREDRAW		0
#define   CS_VREDRAW		1

#define   EM_CANUNDO       0
#define   EM_REPLACESEL    0
#define   EM_LIMITTEXT		0

#define   EN_CHANGE        0

#define   ES_AUTOHSCROLL   0

#define   IDC_IBEAM		0
#define   IDC_ARROW		1

#define   IDI_APPLICATION	0

#define   MB_OK			1
#define   MB_ICONASTERISK	2
#define   MB_OKCANCEL		3
#define   MB_ICONQUESTION	4
#define   MB_YESNO		5
#define   MB_RETRYCANCEL	6
#define   MB_YESNOCANCEL	7

#define   SW_SHOWMAXIMIZED 0
#define   SW_NORMAL        1
#define   SW_SHOWMINIMIZED 2

#define   VK_RETURN		0
#define   VK_ESCAPE		1
#define   VK_PRIOR		2
#define   VK_NEXT		3
#define   VK_END		4
#define   VK_HOME		5
#define   VK_UP			6
#define   VK_DOWN		7
#define   VK_INSERT		8
#define   VK_F1			9
#define   VK_F2			10
#define   VK_F3			11
#define   VK_F4			12
#define   VK_F5			13
#define   VK_F6			15

#define   WM_UNDO          0
#define   WM_CUT           0
#define   WM_COPY          0
#define   WM_PASTE         0
#define   WM_CREATE		     0
#define   WM_SIZE		       1
#define   WM_COMMAND		   2
#define   WM_SYSCOMMAND		 3
#define   WM_KEYDOWN		4
#define   WM_CHAR		5
#define   WM_KEYUP		6
#define   WM_TIMER		7
#define   WM_SETFOCUS		8
#define   WM_PAINT		9
#define   WM_LBUTTONDOWN	10
#define   WM_MOUSEMOVE		11
#define   WM_LBUTTONUP		12
#define   WM_MOVE     		13
#define   WM_PROGRAM1      14    // for inner program only
#define   WM_PROGRAM2      15    // for inner program only
#define   WM_PROGRAM3      16    // for inner program only

#define   WS_CHILD             1
#define   WS_BORDER            0
#define   WS_CAPTION           0
#define   WS_SYSMENU           0
#define   WS_CLIPCHILDREN      0
#define   WS_MINIMIZEBOX       0
#define   WS_THICKFRAME        0
#define   WS_CLIPSIBLINGS      0
#define   WS_OVERLAPPEDWINDOW  0
#define   WS_VISIBLE           0

// -----------------------------------------------
//
//       Define for Windows Functions
//



//------------------------------------------------

int   GetDC(int h1);
int   TextOut(int h1,int h2,int h3,char *h4,int h5);
int   ReleaseDC(int h1,int h2);
int   GetStockObject(int h1);
int   SelectObject(int h1,int h2);
int   HideCaret(int h1);
int   ShowCaret(int h1);
int   SetWindowText(int h1,char *h2);
int   SetFocus(int h1);
int   GetFocus(void);
int   CreateWindow(char *h1,char *h2,int h3,int h4,int h5,int h6,int h7,int h8,int h9,int h10,int h11);
int   GetClientRect(int h1,int *h2);

int   SendMessage(int h1,int h2,int h3,int h4);
int   MoveWindow(int h1,int h2,int h3,int h4,int h5,int h6);
int   GetWindowText(int h1,char *h2,int h3);
int   GetWindowTextLength(int h1);
int   DestroyWindow(int h1);
int   DefWindowProc(int h1,int h2,int h3,int h4);
int   SetCaretPos(int h1,int h2);
int   SetTimer(int h1,int h2,int h3,int h4);
int   KillTimer(int hwnd,int id);

int   CreateCaret(int h1,int h2,int h3,int h4);
int   InvalidateRect(int h1,int h2,int h3);
int   LoadCursor(int h1,int h2);
int   SetCursor(int h1);
int   GetWindowLong(int h1,int h2);
int   CallWindowProc(int h1,int h2,int h3,int h4,int h5);
int   LoadMenu(int h1,char *h2);
int   GetWindowRect(int h1,int h2);
int   DrawFocusRect(int h1,int h2);
int   IsZoomed(int h1);
int   IsIconic(int h1);
int   MessageBox(int h1,const char *h2,const char *h3,int h4);

//int   chsize(int h1,long h2);
int   ShowWindow(int ,int );
int   UpdateWindow(int );

int   GetMessage(int *,int ,int ,int );
int   TranslateMessage(int *);
int   DispatchMessage(int *);

int   GlobalFree(int );
int   chdir(char *);
int   PostQuitMessage(int );
int   LOWORD(int lp);
int   HIWORD(int lp);

int   ShowWindow(int );
int   UpdateWindow(int );

int   WinMain(int ,int ,int ,int );

int   reg_win_class(char * ,int ,char *);
int   set_cursor(int ,int ,int );
int   get_win_ci_text(char *);
int   set_win_ci_text(char *);

// ---------------------------------------------
//
// End of declare for Windows
//
//----------------------------------------------


