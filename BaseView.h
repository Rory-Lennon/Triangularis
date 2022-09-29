
#pragma once

#include "SJNode.h"

class CBaseView : public CView
{
protected:
					
	DECLARE_DYNCREATE(CBaseView)

public:

	HGLRC				m_hglrc;
	bool				m_chooser;

//{{AFX_VIRTUAL(CBaseView)
public:
protected:
	virtual void	OnDraw(CDC* pDC);      
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
//}}AFX_VIRTUAL

protected:

						CBaseView(); 
	virtual			~CBaseView();
	virtual void	build_scene_graph();
	int				get_mode();
	BOOL				create_gl();
	BOOL				create_gl_context(HDC hDC);
	BOOL				set_window_pixel_format(HDC hDC);

	int				m_GLPixelIndex;

#ifdef _DEBUG
	virtual void	AssertValid() const;
	virtual void	Dump(CDumpContext& dc) const;
#endif

//{{AFX_MSG(CBaseView)
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnDestroy	();
	afx_msg BOOL	OnSetCursor	(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
