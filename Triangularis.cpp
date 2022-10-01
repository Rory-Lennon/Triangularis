
#include "Triangularis.h"
#include "MainFrm.h"
#include "AboutDlg.h"
#include "DlgReg.h"
#include "afxpriv.h"
#include <string.h>

BEGIN_MESSAGE_MAP(CTriangularisApp, CWinApp)
	//{{AFX_MSG_MAP(CTriangularisApp)
	ON_COMMAND(ID_APP_ABOUT,	OnAppAbout)
	ON_COMMAND(ID_REGISTER,		OnRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTriangularisApp::CTriangularisApp()
{
	m_reg = false;
}

CTriangularisApp theApp;

BOOL CTriangularisApp::InitInstance()
{
	Enable3dControls();			

	SetRegistryKey(_T("Sejika"));
	LoadStdProfileSettings(4);

	m_font.CreateFont(-11, 0, 0, 0, 0, 0, 0, 0,
							DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial"));

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (!ProcessShellCommand(cmdInfo)) return FALSE;

	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	m_app_icon = LoadIcon(IDR_MAINFRAME);
	m_pMainWnd->SetIcon(m_app_icon, TRUE);
	m_pMainWnd->SetIcon(m_app_icon, FALSE);

	read_config(); 
//	check_reg(m_str_user, m_str_key);

	pFrame->SetWindowPlacement(&m_WP);
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	bool do_res = true;

	if(!pFrame->read_file()) pFrame->res_file(m_last_game);

	return TRUE;
}

void CTriangularisApp::read_config()
{
	WINDOWPLACEMENT wp;
	
	wp.length =	sizeof(wp);
	m_pMainWnd->GetWindowPlacement(&wp);

	m_WP.length	= sizeof(m_WP);
	m_WP.showCmd						=	GetProfileInt("window",	"show",		wp.showCmd);
	m_WP.flags							=	GetProfileInt("window",	"flags",		wp.flags);
	m_WP.ptMinPosition.x				=	GetProfileInt("window",	"minx",		wp.ptMinPosition.x);
	m_WP.ptMinPosition.y				=	GetProfileInt("window",	"miny",		wp.ptMinPosition.y);
	m_WP.ptMaxPosition.x				=	GetProfileInt("window",	"maxx",		wp.ptMaxPosition.x);
	m_WP.ptMaxPosition.y				=	GetProfileInt("window",	"maxy",		wp.ptMaxPosition.y);
	m_WP.rcNormalPosition.left			=	GetProfileInt("window",	"left",		wp.rcNormalPosition.left);
	m_WP.rcNormalPosition.top			=	GetProfileInt("window",	"top",		wp.rcNormalPosition.top);
	m_WP.rcNormalPosition.right		=	GetProfileInt("window",	"right",		wp.rcNormalPosition.right);
	m_WP.rcNormalPosition.bottom	=	GetProfileInt("window",	"bottom",	wp.rcNormalPosition.bottom);

	m_last_game				= GetProfileInt(		"user", "last_game", IDR_GAME_1);
	m_str_user				= GetProfileString(	"user", "name",		"6509012989");
	m_str_key				= GetProfileString(	"user", "graphic",	"84696-57325");

	TRACE("m_str_user %s\n", m_str_user);
	TRACE("m_str_key %s\n", m_str_key);

	CRect rcTemp;
	rcTemp = m_WP.rcNormalPosition;
	rcTemp.NormalizeRect();
	m_WP.rcNormalPosition = rcTemp;

	m_WP = wp;

	if(m_WP.showCmd == SW_MINIMIZE && wp.showCmd != SW_MINIMIZE) m_WP.showCmd = SW_RESTORE;	
	if(m_WP.showCmd != SW_MAXIMIZE && wp.showCmd == SW_MAXIMIZE) m_WP.showCmd = SW_MAXIMIZE;		
}

void CTriangularisApp::write_config()
{
	WriteProfileInt("window", "show",	m_WP.showCmd);
	WriteProfileInt("window", "flags",	m_WP.flags);
	WriteProfileInt("window", "minx",	m_WP.ptMinPosition.x);
	WriteProfileInt("window", "miny",	m_WP.ptMinPosition.y);
	WriteProfileInt("window", "maxx",	m_WP.ptMaxPosition.x);
	WriteProfileInt("window", "maxy",	m_WP.ptMaxPosition.y);
	WriteProfileInt("window", "left",	m_WP.rcNormalPosition.left);
	WriteProfileInt("window", "top",		m_WP.rcNormalPosition.top);
	WriteProfileInt("window", "right",	m_WP.rcNormalPosition.right);
	WriteProfileInt("window", "bottom",	m_WP.rcNormalPosition.bottom);

	WriteProfileInt(		"user", "last_game", m_last_game);
	WriteProfileString(	"user", "name",		m_str_user);
	WriteProfileString(	"user", "graphic",	m_str_key);
}

const WINDOWPLACEMENT& CTriangularisApp::GetWP(void) const
{
	return m_WP;
}

void CTriangularisApp::PutWP(const WINDOWPLACEMENT& newval)
{	
	m_WP = newval;
	m_WP.length = sizeof(m_WP); 
}

int CTriangularisApp::get_last_game()
{
	return m_last_game;
}

void CTriangularisApp::set_last_game(int last_game)
{
	m_last_game = last_game;
}

int CTriangularisApp::ExitInstance() 
{
	write_config();
	m_font.DeleteObject();
	return CWinApp::ExitInstance();
}

void CTriangularisApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CTriangularisApp::OnRegister() 
{
	CDlgReg reg_dlg;
	reg_dlg.DoModal();
}

#define XOR_PRIME      0xFFFFFFFF
#define XOR_CRYPT      0x13579ACE
#define XOR_POST_CRYPT 0x2468BDF0

CDocument* CTriangularisApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{	
	AddToRecentFileList(lpszFileName);
	((CMainFrame*)m_pMainWnd)->read_file();
	return (CDocument*)TRUE;
}

CString CTriangularisApp::get_mru_top()
{
	CString mru_str;
	m_pRecentFileList->GetDisplayName(mru_str, 0, "", 0, FALSE);
	return mru_str;
}
