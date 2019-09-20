
// FreeCellDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FreeCell.h"
#include "FreeCellDlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"

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


// CFreeCellDlg dialog



CFreeCellDlg::CFreeCellDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FREECELL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreeCellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreeCellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CFreeCellDlg message handlers

BOOL CFreeCellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	InitializeCards();
	
	mCells[0] = new Cell(10, 10, 100, 100);
	mCells[1] = new Cell(110, 10, 200, 100);
	mCells[2] = new Cell(210, 10, 300, 100);
	mCells[3] = new Cell(310, 10, 400, 100);

	mCells[4] = new Cell(610, 10, 700, 100);
	mCells[5] = new Cell(710, 10, 800, 100);
	mCells[6] = new Cell(810, 10, 900, 100);
	mCells[7] = new Cell(910, 10, 1000, 100);

	mCells[8] = new Cell(10, 150, 100, 240);
	mCells[9] = new Cell(110, 150, 200, 240);
	mCells[10] = new Cell(210, 150, 300, 240);
	mCells[11] = new Cell(310, 150, 400, 240);

	mCells[12] = new Cell(610, 150, 700, 240);
	mCells[13] = new Cell(710, 150, 800, 240);
	mCells[14] = new Cell(810, 150, 900, 240);
	mCells[15] = new Cell(910, 150, 1000, 240);
	//Cell(int left, int top, int right, int bottom);

	mCells[0]->AddCard(17);
	mCells[1]->AddCard(12);
	mCells[2]->AddCard(13);
	mCells[3]->AddCard(16);
	mCells[4]->AddCard(18);
	mCells[5]->AddCard(19);
	mCells[6]->AddCard(20);
	mCells[7]->AddCard(21);
	mCells[8]->AddCard(22);
	mCells[9]->AddCard(23);
	mCells[10]->AddCard(24);
	mCells[11]->AddCard(25);
	mCells[12]->AddCard(26);
	mCells[13]->AddCard(27);
	mCells[14]->AddCard(28);
	mCells[15]->AddCard(29);
	



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFreeCellDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFreeCellDlg::OnPaint()
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
		CPaintDC dc(this); // device context for painting
		CRect rect;
		GetClientRect(&rect);
		/*
		int left = 2;
		int top = 2;
		for (int index = 0; index < 52; index++)
		{
			DrawCard(dc, left, top, index);
			left += 20;
		}
		*/
		for (int i = 0; i < 16; i++)
		{
			mCells[i]->Draw(dc, rect.Width(), rect.Height(), mCardImages);
		}
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFreeCellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

