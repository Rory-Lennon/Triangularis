
#pragma once

#include "HyperLink.h"
#include "CtrlBreak.h"

class CDlgReg : public CDialog
{
public:

	CDlgReg(CWnd* pParent = NULL);  

	CHyperLink			m_hyperlink;
	CCtrlBreak			m_break_register;
	CCtrlBreak			m_break_user;

	//{{AFX_DATA(CDlgReg)
	enum { IDD = IDD_DLG_REG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CDlgReg)

	protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CDlgReg)
	virtual BOOL		OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


