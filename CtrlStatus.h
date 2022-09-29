
#pragma once

class CCtrlStatus : public CStatusBar
{
	DECLARE_DYNCREATE(CCtrlStatus)
public:
						CCtrlStatus();

	//{{AFX_VIRTUAL(CCtrlStatus)
	//}}AFX_VIRTUAL

	virtual			~CCtrlStatus();
	CFont*			get_font();
	void				set_dims(int x, int y);

	CProgressCtrl	m_covered;

	bool				m_show_grid;
	bool				m_show_index;

protected:
	
	//{{AFX_MSG(CCtrlStatus)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


