
#include "Triangularis.h"
#include "CtrlStatus.h"

IMPLEMENT_DYNCREATE(CCtrlStatus, CStatusBar)

CCtrlStatus::CCtrlStatus()
{
	m_show_grid  = false;
	m_show_index = false;
}

CCtrlStatus::~CCtrlStatus()
{}

BEGIN_MESSAGE_MAP(CCtrlStatus, CStatusBar)
	//{{AFX_MSG_MAP(CCtrlStatus)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFont* CCtrlStatus::get_font()
{
	CTriangularisApp* pSetriangularis = (CTriangularisApp*)AfxGetApp();
	return &(pSetriangularis->m_font);
}

static UINT indicators[] =
{
	ID_SEPARATOR,	
	IDS_COVERED,
	IDS_ROWS,
	IDS_COLS
};

int CCtrlStatus::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1) return -1;
	
	SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	CRect rect;
	GetItemRect(CommandToIndex(IDS_COVERED), &rect);

	this->SetWindowText("Gemini Ready");

//| PBS_SMOOTH

	m_covered.Create(WS_VISIBLE | WS_CHILD | PBS_SMOOTH, rect, this, IDS_COVERED);
	m_covered.SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)RGB(235, 0, 0));
	m_covered.SetRange(0, 100);
   m_covered.SetPos(0);

	return 0;
}

void CCtrlStatus::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
	CRect rect;
	GetItemRect(CommandToIndex(IDS_COVERED), &rect);
	m_covered.MoveWindow(rect);
}

void CCtrlStatus::set_dims(int x, int y)
{
	CString str;
	str.Format("ROWS %i", x);
	SetPaneText(CommandToIndex(IDS_ROWS), str);
	str.Format("COLS %i", y);
	SetPaneText(CommandToIndex(IDS_COLS), str);
}
