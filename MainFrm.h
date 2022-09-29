
#pragma once

#include "CtrlStatus.h"

class CMainFrame : public CFrameWnd
{
	
public:

							CMainFrame();
	void					save_file();
	bool					read_file();
	bool					res_file(int RES_ID);
	void					check_save();

	bool					m_file_changed;
	CWnd*					mp_view;

protected: 

	DECLARE_DYNAMIC(CMainFrame)

public:

	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL		OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL		OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL		OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

public:
	virtual ~CMainFrame();

	CCtrlStatus			m_status;

protected:

	//{{AFX_MSG(CMainFrame)
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	afx_msg void		OnSetFocus(CWnd *pOldWnd);
	afx_msg void		OnFileOpen();
	afx_msg void		OnClose();
	afx_msg void		OnFileSaveAs();
	afx_msg void		OnFileSave();
	afx_msg void		OnNewGame();
	afx_msg void		OnViewGrid();
	afx_msg void		OnViewIndex();
	afx_msg void		OnViewSpin();
	afx_msg void		OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void		OnUpdateViewIndex(CCmdUI* pCmdUI);
	afx_msg LONG		on_update_covered(LONG percent, LPARAM lParam);
	afx_msg LONG		on_update_dims(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


