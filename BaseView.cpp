
#include "Triangularis.h"
#include "BaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBaseView, CView)

CBaseView::CBaseView()
{
	m_hglrc = NULL;
	m_GLPixelIndex = 0;
}

CBaseView::~CBaseView()
{
//	delete m_pCDC;
}

BEGIN_MESSAGE_MAP(CBaseView, CView)
	//{{AFX_MSG_MAP(CBaseView)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CBaseView::OnDraw(CDC* pDC)
{}

void CBaseView::build_scene_graph()
{}

int CBaseView::get_mode()
{
	CTriangularisApp* pSetriangularisApp = (CTriangularisApp*)AfxGetApp();
	return pSetriangularisApp->m_mode;
}

#ifdef _DEBUG
void CBaseView::AssertValid() const
{
	CView::AssertValid();
}

void CBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif 

BOOL CBaseView::OnEraseBkgnd(CDC* pDC) 
{	
	return FALSE;
}

BOOL CBaseView::create_gl()
{
	HDC hDC = ::GetDC(GetSafeHwnd());
	if (set_window_pixel_format(hDC) == FALSE) return 0;
	if (create_gl_context(hDC) == FALSE) return 0;
	return TRUE;
}

BOOL CBaseView::create_gl_context(HDC hDC)
{
	m_hglrc = wglCreateContext(hDC);
	if (m_hglrc == NULL) return FALSE;
	if (wglMakeCurrent(hDC, m_hglrc) == FALSE) return FALSE;
	return TRUE;
}

BOOL CBaseView::set_window_pixel_format(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion	= 1;

	pixelDesc.dwFlags	=	PFD_DRAW_TO_WINDOW	| 
								PFD_SUPPORT_OPENGL	| 
								PFD_DOUBLEBUFFER		| 
								PFD_STEREO_DONTCARE;  

	pixelDesc.iPixelType			= PFD_TYPE_RGBA;
	pixelDesc.cColorBits			= 32;
	pixelDesc.cRedBits			= 8;
	pixelDesc.cRedShift			= 16;
	pixelDesc.cGreenBits			= 8;
	pixelDesc.cGreenShift		= 8;
	pixelDesc.cBlueBits			= 8;
	pixelDesc.cBlueShift			= 0;
	pixelDesc.cAlphaBits			= 0;
	pixelDesc.cAlphaShift		= 0;
	pixelDesc.cAccumBits			= 64;	
	pixelDesc.cAccumRedBits		= 16;
	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits			= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType			= PFD_MAIN_PLANE;
	pixelDesc.bReserved			= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;

	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex == 0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
		{
			return FALSE;
		}
	}
	if(SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc) == FALSE) return FALSE;
	return TRUE;
}

void CBaseView::OnDestroy() 
{
	if(wglGetCurrentContext() != NULL) wglMakeCurrent(NULL, NULL);
	
	if (m_hglrc != NULL)
	{
		wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}
	CView::OnDestroy();

}

BOOL CBaseView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	cs.style &= ~WS_BORDER;
	cs.style &= ~WS_THICKFRAME;
//	cs.style |= WS_DLGFRAME;
	return CView::PreCreateWindow(cs);
}

BOOL CBaseView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_chooser) return TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_ROTATE));
	return TRUE;
}



