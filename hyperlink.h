
#pragma once

class CHyperLink : public CStatic
{
	DECLARE_DYNAMIC(CHyperLink)

public:

	static const DWORD StyleUnderline;
	static const DWORD StyleUseHover;
	static const DWORD StyleAutoSize;
	static const DWORD StyleDownClick;
	static const DWORD StyleGetFocusOnClick;
	static const DWORD StyleNoHandCursor;
	static const DWORD StyleNoActiveColor;

	CHyperLink();
	virtual ~CHyperLink();

public:	

	static HCURSOR GetLinkCursor();
	static void SetLinkCursor(HCURSOR hCursor);
    
    static void SetColors();

	void SetURL(CString strURL);
    CString GetURL() const;
	  
	void SetWindowText(LPCTSTR lpszText);
	void SetFont(CFont* pFont);
	
	BOOL SubclassDlgItem(UINT nID, CWnd* pParent, LPCTSTR lpszURL=NULL)
	{
		m_strURL = lpszURL;
		return CStatic::SubclassDlgItem(nID, pParent);
	}

	//{{AFX_VIRTUAL(CHyperLink)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	protected:
	virtual void PreSubclassWindow();	
	//}}AFX_VIRTUAL

protected:

	static void SetDefaultCursor();
	static LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);	

	void AdjustWindow();	
	void FollowLink();

protected:

	static COLORREF g_crLinkColor;		// Link normal color
	static COLORREF g_crActiveColor;		// Link active color
	static COLORREF g_crVisitedColor;	// Link visited color
	static COLORREF g_crHoverColor;		// Hover color
	static HCURSOR  g_hLinkCursor;		// Hyperlink mouse cursor

	BOOL				m_bLinkActive;			// Is the link active?
	BOOL				m_bOverControl;		// Is cursor over control?
	DWORD				m_dwStyle;				// Link styles
	CString			m_strURL;				// Hyperlink URL string
	CFont				m_Font;					// Underlined font (if required)	
	CToolTipCtrl	m_ToolTip;				// The link tooltip	

protected:

	//{{AFX_MSG(CHyperLink)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


