
#pragma once

#include "CtrlBreak.h"

class CDlgChoose : public CDialog
{
public:

							CDlgChoose(int game, HGLRC	hglrc);

	//{{AFX_DATA(CDlgChoose)
	//}}AFX_DATA
	HGLRC					m_hglrc;
	CWnd*					mp_view;
	int					m_game;
	CCtrlBreak			m_break_beginner;
	CCtrlBreak			m_break_clever;
	CCtrlBreak			m_break_impos;

	//{{AFX_VIRTUAL(CDlgChoose)
	public:
	protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CDlgChoose)
	virtual BOOL		OnInitDialog();
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	afx_msg void		OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void		on_radio_range(UINT nID);
};
