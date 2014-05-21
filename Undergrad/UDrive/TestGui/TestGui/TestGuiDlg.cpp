// TestGuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGui.h"
#include "TestGuiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestGuiDlg dialog




CTestGuiDlg::CTestGuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGuiDlg::IDD, pParent)
	, number(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, number);
}

BEGIN_MESSAGE_MAP(CTestGuiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CTestGuiDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestGuiDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestGuiDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestGuiDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestGuiDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestGuiDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CTestGuiDlg message handlers

BOOL CTestGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	total = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestGuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestGuiDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	total += number;
	number = total;
	UpdateData(false);
}

void CTestGuiDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CEdit* textPtr = (CEdit*)GetDlgItem(IDC_EDIT2);
	total = 0;
	textPtr->SetWindowTextW(TEXT(""));
}

void CTestGuiDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	exit(0);
}

void CTestGuiDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	total -= number;
	number = total;
	UpdateData(false);
}

void CTestGuiDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	total *= number;
	number = total;
	UpdateData(false);
}

void CTestGuiDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	total = 666;
	number = total;
	UpdateData(false);
}
