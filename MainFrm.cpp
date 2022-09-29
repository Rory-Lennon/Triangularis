
#include "Jiki.h"
#include "MainFrm.h"
#include "SejikiView.h"
#include "DlgChoose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN,				OnFileOpen)
	ON_COMMAND(ID_FILE_SAVEAS,				OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE,				OnFileSave)
	ON_COMMAND(ID_NEW_GAME,					OnNewGame)
	ON_COMMAND(ID_VIEW_GRID,				OnViewGrid)
	ON_COMMAND(ID_VIEW_INDEX,				OnViewIndex)
	ON_COMMAND(ID_VIEW_SPIN,				OnViewSpin)
	ON_COMMAND(ID_HELP_FINDER,				OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID,	OnUpdateViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INDEX, OnUpdateViewIndex)
	ON_MESSAGE(MSG_UPDATE_COVERED,		on_update_covered)
	ON_MESSAGE(MSG_UPDATE_DIMS,			on_update_dims)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
	mp_view = NULL;
	m_file_changed = false;
}

CMainFrame::~CMainFrame()
{}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

	m_status.Create(this);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CCreateContext context;
	context.m_pCurrentDoc		= NULL;
	context.m_pCurrentFrame		= this;
	context.m_pLastView			= NULL;
	context.m_pNewDocTemplate	= NULL;
	context.m_pNewViewClass		= RUNTIME_CLASS(CSejikiView);

	mp_view = CreateView(&context);

	((CSejikiView*)mp_view)->set_main_board();
	((CSejikiView*)mp_view)->spin_360();

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs)) return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

LONG CMainFrame::on_update_covered(LONG percent, LPARAM lParam)
{
	m_status.m_covered.SetPos(percent);
	return TRUE;
}

LONG CMainFrame::on_update_dims(WPARAM wParam, LPARAM lParam)
{
	m_status.set_dims((LONG)wParam, (LONG)lParam);
	return TRUE;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	if(mp_view != NULL) mp_view->SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if(mp_view != NULL) mp_view->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnClose() 
{	
	CJikiApp* p_app = (CJikiApp*)AfxGetApp();
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	p_app->PutWP(wp);

	check_save();

	CFrameWnd::OnClose();
}

void CMainFrame::OnFileOpen() 
{
	BOOL b_save_or_open = TRUE;
	CString str_default_extension = "";
	CString str_file_title = "";
	CString str_filter = _T("Gemini Game Files (*.gni)|*.gni||");

	CFileDialog dlg_file(b_save_or_open, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY,
							   str_filter,
							   this);

	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Gemini Game Files");
	int do_it = dlg_file.DoModal();

	if(do_it == 1) 
	{
		AfxGetApp()->AddToRecentFileList(dlg_file.GetPathName());
		read_file();
	}
}

void CMainFrame::OnFileSave() 
{
	CJikiApp* p_app = (CJikiApp*)AfxGetApp();
	if(m_file_changed) OnFileSaveAs();
	else save_file();	
}

void CMainFrame::OnFileSaveAs() 
{
	CJikiApp* p_app = (CJikiApp*)AfxGetApp();

	CString str_default_extension = "gni";
	CString str_file_title = "gemini-1.gni";
	CString str_filter = "Gemini Files (*.gni)|*.gni||";

	CFileDialog dlg_file(FALSE, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							   str_filter,
							   this);

	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Gemini Game Files");
	int do_it = dlg_file.DoModal();
	if(do_it == 1) 
	{
		AfxGetApp()->AddToRecentFileList(dlg_file.GetPathName());
		save_file();
	}
}

void CMainFrame::OnNewGame() 
{
	CJikiApp* p_app = (CJikiApp*)AfxGetApp();
	CSejikiView* p_view = (CSejikiView*)mp_view;
	CDlgChoose dlg_choose(p_app->get_last_game() + 1, p_view->m_hglrc);
	int do_it = dlg_choose.DoModal();
	if(do_it == 1) 
	{
		check_save();
		p_app->set_last_game(dlg_choose.m_game);
		m_file_changed = true;
		res_file(dlg_choose.m_game);
	}
	((CSejikiView*)mp_view)->mp_board->update_dims();
}

void CMainFrame::save_file()
{
	m_file_changed = false;
	((CSejikiView*)mp_view)->save_file(((CJikiApp*)AfxGetApp())->get_mru_top());
}

void CMainFrame::check_save()
{
	CJikiApp* p_app = (CJikiApp*)AfxGetApp();
	if(p_app->get_mru_top() == "")
	{
		int mba = MessageBox(	"Do you want to save the changes you made to the current game?", 
										"Gemini",
										MB_YESNO | MB_ICONEXCLAMATION);

		if(mba == 6) OnFileSaveAs();
	}
	else save_file();
}

bool CMainFrame::read_file()
{
	CJikiApp* p_app = (CJikiApp*)AfxGetApp();
	return ((CSejikiView*)mp_view)->read_duck(p_app->get_mru_top());
}

bool CMainFrame::res_file(int RES_ID)
{
	((CSejikiView*)mp_view)->res_duck(RES_ID);
	return true;
}

void CMainFrame::OnViewGrid() 
{
	((CSejikiView*)mp_view)->toggle_grid();
	m_status.m_show_grid = ((CSejikiView*)mp_view)->m_show_grid;
}

void CMainFrame::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	if(((CJikiApp*)AfxGetApp())->m_reg) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if(((CSejikiView*)mp_view)->m_show_grid) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewIndex() 
{
	((CSejikiView*)mp_view)->toggle_index();
}

void CMainFrame::OnUpdateViewIndex(CCmdUI* pCmdUI) 
{
	if(((CJikiApp*)AfxGetApp())->m_reg) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if(((CSejikiView*)mp_view)->m_show_index) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);

}

void CMainFrame::OnViewSpin() 
{
	((CSejikiView*)mp_view)->spin_360();	
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{ 
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
}

