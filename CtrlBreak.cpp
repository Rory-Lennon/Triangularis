

#include "Jiki.h"
#include "CtrlBreak.h"

CCtrlBreak::CCtrlBreak()
{
	height		= 15;
	half_height	= height / 2;
	left_offset	= half_height;
	text_width	= 160;
}

CCtrlBreak::~CCtrlBreak()
{}

BEGIN_MESSAGE_MAP(CCtrlBreak, CStatic)
	//{{AFX_MSG_MAP(CCtrlBreak)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCtrlBreak::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{	
//	CStatic::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

BOOL CCtrlBreak::OnEraseBkgnd(CDC* pDC) 
{	
	return CStatic::OnEraseBkgnd(pDC);
}

void CCtrlBreak::OnPaint() 
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(&rect);

	CPen white_pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen red_pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen pen_shadow(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
	CPen pen_highlight(PS_SOLID, 1, ::GetSysColor(COLOR_BTNHIGHLIGHT));

	CPen* p_old_pen = dc.SelectObject(&white_pen);

	dc.SelectObject(&white_pen);

	rect.top		= 0;
	rect.bottom	= height;
	rect.left	= left_offset + text_width;
	rect.right	= left_offset + text_width + height;
	dc.Ellipse(rect);

	rect.left	= left_offset + text_width;
	rect.right	= left_offset + text_width + height;
	dc.Ellipse(rect);

//	rect.left	= left_offset + half_height;
	rect.left	= 0;
	rect.right	= left_offset + text_width + half_height;
	dc.Rectangle(rect);

//	rect.left	= left_offset + text_width;
//	rect.right	= left_offset + text_width + height;
//	rect.bottom	= half_height;
//	dc.Rectangle(rect);

	CString str;
	GetWindowText(str);

	CFont* p_old_font = dc.SelectObject(get_font());
	dc.TextOut(half_height, 0, str);
	dc.SelectObject(p_old_font);

//	dc.SelectObject(&red_pen);

//	dc.MoveTo(0, 0);
//	dc.LineTo(text_width, 0);

//	dc.MoveTo(0, 0);
//	dc.LineTo(text_width, 0);

	GetClientRect(&rect);
	dc.SelectObject(&pen_shadow);
	dc.MoveTo(0, 0);
	dc.LineTo(rect.right, 0);

	dc.SelectObject(&pen_highlight);
	dc.MoveTo(0,  1);
	dc.LineTo(rect.right, 1);

	dc.SelectObject(p_old_pen);
}

CFont* CCtrlBreak::get_font()
{
	CJikiApp* pSejiki = (CJikiApp*)AfxGetApp();
	return &(pSejiki->m_font);
}