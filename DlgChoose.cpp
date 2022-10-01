
#include "Triangularis.h"
#include "DlgChoose.h"
#include "SetriangularisView.h"

CDlgChoose::CDlgChoose(int game, HGLRC	hglrc) : CDialog(IDD_CHOOSE_GAME)
{
	//{{AFX_DATA_INIT(CDlgChoose)		
	//}}AFX_DATA_INIT
	m_hglrc	= hglrc;
	m_game	= game;
	mp_view	= NULL;
}

void CDlgChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChoose)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgChoose, CDialog)
	//{{AFX_MSG_MAP(CDlgChoose)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED , FIRST_GAME, LAST_GAME, on_radio_range)
END_MESSAGE_MAP()

BOOL CDlgChoose::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_break_beginner.	SubclassDlgItem(IDC_BREAK_BEGINNER, this);
	m_break_clever.	SubclassDlgItem(IDC_BREAK_CLEVER,	this);
	m_break_impos.		SubclassDlgItem(IDC_BREAK_IMPOS,		this);

	CWnd* p_check = GetDlgItem(m_game);
	if(p_check) ((CButton*)p_check)->SetCheck(1);

	return TRUE;  
}

int CDlgChoose::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1) return -1;

	mp_view = (CWnd*)RUNTIME_CLASS(CSetriangularisView)->CreateObject();
	mp_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), this, 0);

	((CSetriangularisView*)mp_view)->set_chooser(m_hglrc);
	((CSetriangularisView*)mp_view)->res_file(m_game);

	return 0;
}

void CDlgChoose::on_radio_range(UINT nID)
{
	if(nID < IDR_GAME_8)
	{
		m_game = nID;
		((CSetriangularisView*)mp_view)->res_file(m_game);
		((CSetriangularisView*)mp_view)->gl_render();
	}
	else 
	{
		((CTriangularisApp*)AfxGetApp())->OnRegister();

		CWnd* p_id = GetDlgItem(nID);
		if(p_id) ((CButton*)p_id)->SetCheck(0);

		CWnd* p_check = GetDlgItem(m_game);
		if(p_check) ((CButton*)p_check)->SetCheck(1);
	}
}

void CDlgChoose::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	mp_view->MoveWindow(210, 10, 200, 150);
}

void CDlgChoose::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	((CSetriangularisView*)mp_view)->start_chooser_timer();	
}

