// Lab 14Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lab 14.h"
#include "Lab 14Dlg.h"

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


// CLab14Dlg dialog




CLab14Dlg::CLab14Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLab14Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLab14Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLab14Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON00, &CLab14Dlg::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON01, &CLab14Dlg::OnBnClickedButton01)
	ON_BN_CLICKED(IDC_BUTTON02, &CLab14Dlg::OnBnClickedButton02)
	ON_BN_CLICKED(IDC_BUTTON10, &CLab14Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CLab14Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CLab14Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON20, &CLab14Dlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CLab14Dlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CLab14Dlg::OnBnClickedButton22)
END_MESSAGE_MAP()


// CLab14Dlg message handlers

BOOL CLab14Dlg::OnInitDialog()
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
	// Initialize grid and curPlayer:
	curPlayer = 'X';  // X always gets first turn
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			grid[row][col] = 'e';  // all grid cells start out empty

	//  Prompt player X for their turn:
	CEdit* ptr = (CEdit*)GetDlgItem(IDC_EDIT1);
	ptr->SetWindowTextW(TEXT("Player X: Please take your turn."));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLab14Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLab14Dlg::OnPaint()
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
HCURSOR CLab14Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Function to disable all buttons -- called when game over is reached.
void CLab14Dlg::disableAll()
{
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON00);
	ptr->EnableWindow(false);  // makes button unclickable
	ptr = (CButton*)GetDlgItem(IDC_BUTTON01);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON02);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON10);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON11);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON12);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON20);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON21);
	ptr->EnableWindow(false);
	ptr = (CButton*)GetDlgItem(IDC_BUTTON22);
	ptr->EnableWindow(false);
}

// Assesses grid to see if anyone has achieved 3 in a row:
// Returns: 'X' if player X has achieved a win
//          'O' if player O has achieved a win
//          'S' if a stalemate has been reached (all cells filled with no win)
//          'E' if no one has won and there are still moves to be made
char CLab14Dlg::checkWin()
{
	// Check for three in a row
	for (int row = 0; row < 3; row++)
	{
		if (grid[row][0] == 'X' && grid[row][1] == 'X' && grid[row][2] == 'X')
			return 'X';
		if (grid[row][0] == 'O' && grid[row][1] == 'O' && grid[row][2] == 'O')
			return 'O';
	}

	// Check for three in a column
	for (int col = 0; col < 3; col++)
	{
		if (grid[0][col] == 'X' && grid[1][col] == 'X' && grid[2][col] == 'X')
			return 'X';
		if (grid[0][col] == 'O' && grid[1][col] == 'O' && grid[2][col] == 'O')
			return 'O';
	}

	// Check for three on a diagonal
	if (grid[0][0] == 'X' && grid[1][1] == 'X' && grid[2][2] == 'X')
		return 'X';
	if (grid[0][2] == 'X' && grid[1][1] == 'X' && grid[2][0] == 'X')
		return 'X';
	if (grid[0][0] == 'O' && grid[1][1] == 'O' && grid[2][2] == 'O')
		return 'O';
	if (grid[0][2] == 'O' && grid[1][1] == 'O' && grid[2][0] == 'O')
		return 'O';

	// Check for stalemate -- if there are any empty cells then not a stalemate
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			if (grid[r][c] == 'e')
				return 'E';
	return 'S'; // if no empty cells stalemate has been reached.

}
void CLab14Dlg::OnBnClickedButton00()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON00);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[0][0] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		Pntr->SetWindowTextW(TEXT("WIN"));
		disableAll();
		

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton01()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON01);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[0][1] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton02()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON02);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[0][2] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton10()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON10);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[1][0] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton11()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON11);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[1][1] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton12()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON12);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[1][2] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton20()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON20);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[2][0] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton21()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON21);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[2][1] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}

void CLab14Dlg::OnBnClickedButton22()
{
	
	CButton* ptr = (CButton*)GetDlgItem(IDC_BUTTON22);
	CEdit* Pntr = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(true);
	
	if(curPlayer == 'X')
	{
	ptr->SetWindowTextW(TEXT("X"));
	}
	else
	{
		ptr->SetWindowTextW(TEXT("O"));
	}

	ptr->EnableWindow(false);

	grid[2][2] = curPlayer;

	char check = checkWin();
	if(check == 'X' || check == 'O')
	{
		disableAll();

	}
	else if(check == 'S')
	{
		disableAll();
		Pntr->SetWindowTextW(TEXT("STALEMATE"));
	}
	else
	{
		if(curPlayer == 'X')
			curPlayer = 'O';
		else
			curPlayer = 'X';
	}

	UpdateData(false);
}
