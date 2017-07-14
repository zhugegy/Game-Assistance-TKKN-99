
// trueman-20-seconds-toolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "trueman-20-seconds-tool.h"
#include "trueman-20-seconds-toolDlg.h"
#include "afxdialogex.h"

#include "Trueman20SecondsCheats.h"
#include "DoNotUse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctrueman20secondstoolDlg dialog



Ctrueman20secondstoolDlg::Ctrueman20secondstoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRUEMAN20SECONDSTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctrueman20secondstoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctrueman20secondstoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON1, &Ctrueman20secondstoolDlg::OnBnClickedButton1)
  ON_BN_CLICKED(IDC_BUTTON2, &Ctrueman20secondstoolDlg::OnBnClickedButton2)
  ON_BN_CLICKED(IDC_BUTTON3, &Ctrueman20secondstoolDlg::OnBnClickedButton3)
  ON_BN_CLICKED(IDC_BUTTON4, &Ctrueman20secondstoolDlg::OnBnClickedButton4)
  ON_BN_CLICKED(IDC_BUTTON5, &Ctrueman20secondstoolDlg::OnBnClickedButton5)
  ON_BN_CLICKED(IDOK, &Ctrueman20secondstoolDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Ctrueman20secondstoolDlg message handlers

BOOL Ctrueman20secondstoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
  srand(0);
  CDoNotUse objForSingleInstance;
  //InitializeCriticalSection(&Trueman20SecondsCheats::m_cs);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ctrueman20secondstoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ctrueman20secondstoolDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ctrueman20secondstoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ctrueman20secondstoolDlg::OnBnClickedButton1()
{
  // TODO: Add your control notification handler code here
  Trueman20SecondsCheats::m_bIsNowCheating = true;

  int nCheatType = Trueman20SecondsCheats::INVULNERABILITY;
  Trueman20SecondsCheats::m_hCheatingThread = CreateThread(NULL, 0, Trueman20SecondsCheats::CheatingThreadFunc, (LPVOID)nCheatType, 0, NULL);
}


void Ctrueman20secondstoolDlg::OnBnClickedButton2()
{
  // TODO: Add your control notification handler code here
  Trueman20SecondsCheats::m_bIsNowCheating = false;

  Sleep(200);

  if (Trueman20SecondsCheats::m_hCheatingThread != NULL)
  {
    TerminateThread(Trueman20SecondsCheats::m_hCheatingThread, -1);
  }

}


void Ctrueman20secondstoolDlg::OnBnClickedButton3()
{
  // TODO: Add your control notification handler code here
  Trueman20SecondsCheats::m_bIsNowCheating = true;

  int nCheatType = Trueman20SecondsCheats::FLASH_MOVE;
  Trueman20SecondsCheats::m_hCheatingThread = CreateThread(NULL, 0, Trueman20SecondsCheats::CheatingThreadFunc, (LPVOID)nCheatType, 0, NULL);
}


void Ctrueman20secondstoolDlg::OnBnClickedButton4()
{
  // TODO: Add your control notification handler code here
  Trueman20SecondsCheats::m_bIsNowCheating = true;

  int nCheatType = Trueman20SecondsCheats::SHIELD;
  Trueman20SecondsCheats::m_hCheatingThread = CreateThread(NULL, 0, Trueman20SecondsCheats::CheatingThreadFunc, (LPVOID)nCheatType, 0, NULL);
}


void Ctrueman20secondstoolDlg::OnBnClickedButton5()
{
  // TODO: Add your control notification handler code here
  Trueman20SecondsCheats::m_bIsNowCheating = true;



  int nCheatType = Trueman20SecondsCheats::AUTO_MOVE;
  Trueman20SecondsCheats::m_hCheatingThread = CreateThread(NULL, 0x1000 * 0x1000, Trueman20SecondsCheats::CheatingThreadFunc, (LPVOID)nCheatType, 0, NULL);

   m_pAutoMoveNaviDlg = new CAutoMoveNaviDialog;
   m_pAutoMoveNaviDlg->Create(IDD_AUTOMOVENAVIDIALOG, this);
   m_pAutoMoveNaviDlg->ShowWindow(SW_SHOW);
}


void Ctrueman20secondstoolDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  

  CDialogEx::OnOK();
}
