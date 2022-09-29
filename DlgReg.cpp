
#include "Jiki.h"
#include "DlgReg.h"

CDlgReg::CDlgReg(CWnd* pParent /*=NULL*/) : CDialog(CDlgReg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgReg)
	//}}AFX_DATA_INIT
}

void CDlgReg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgReg, CDialog)
	//{{AFX_MSG_MAP(CDlgReg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgReg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_hyperlink.SubclassDlgItem(IDC_HYPERLINK, this, "www.sejika.com/zodiac/");
	m_break_register.SubclassDlgItem(IDC_BREAK_REGISTER, this);
//	m_break_user.SubclassDlgItem(IDC_BREAK_USER, this);

//	GetDlgItem(IDC_EDIT_NAME)->SetFocus();

//	CFont font;
//	font.CreatePointFont(-10, "Courier");
//	font.CreateFont(-8, 0, 0, 0, 0, 0, 0, 0,
//							DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
//							ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Fixedsys"));

//	CEdit* p_name_edit = (CEdit*)	GetDlgItem(IDC_EDIT_NAME);
//	p_name_edit->SetFont(&font); 
//	font.DeleteObject();

	return TRUE;  
}





