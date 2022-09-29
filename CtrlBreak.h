
#pragma once

class CCtrlBreak : public CStatic
{

public:
						CCtrlBreak();

	//{{AFX_VIRTUAL(CCtrlBreak)
	//}}AFX_VIRTUAL

	virtual			~CCtrlBreak();
	CFont*			get_font();

protected:
	
	int				text_width;
	int				left_offset;
	int				height;
	int				half_height;

	//{{AFX_MSG(CCtrlBreak)
	afx_msg void	OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


