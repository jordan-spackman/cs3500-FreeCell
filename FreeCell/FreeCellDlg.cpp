
// FreeCellDlg.cpp : implementation file
//

#include <iostream>
#include "pch.h"
#include "framework.h"
#include "FreeCell.h"
#include "FreeCellDlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"
#include <stdlib.h>

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


	//Free Cells
	//0-3
	int leftFree = 10, topFree = 10, rightFree = 100, bottomFree = 100;
	int cellIndexFree = 0;
	for (int i = 0; i <= 3; i++) {
		mCells[cellIndexFree] = new FreeCell(leftFree, topFree, rightFree, bottomFree);
		leftFree += 100;
		rightFree += 100;
		cellIndexFree += 1;
	}

	//End Cells
	//4-7
	int leftEnd = 610, topEnd = 10, rightEnd = 700, bottomEnd = 100;
	int cellIndexEnd = 4;
	for (int i = 0; i <= 7; i++) {
		mCells[cellIndexEnd] = new EndCell(leftEnd, topEnd, rightEnd, bottomEnd);
		leftEnd += 100;
		rightEnd += 100;
		cellIndexEnd += 1;
	}

	//Start Cells
	//8-16
	int leftStart = 80, topStart = 170, rightStart = 170, bottomStart = 460;
	int cellIndexStart = 8;
	int cardHeight = 80;
	for (int i = 0; i <= 15; i++) {
		mCells[cellIndexStart] = new StartCell(leftStart, topStart, rightStart, bottomStart);
		leftStart += 100;
		rightStart += 100;
		cellIndexStart += 1;
	}


	//Shuffle and Draw cards.
	
	int randomDeck[52];
	for (int i = 0; i < 52; i++) {
		randomDeck[i] = i;
	}

	for (int i = 0; i < 52; i++) {
		int j = rand() % 52;

		int temp = randomDeck[i];
		randomDeck[i] = randomDeck[j];
		randomDeck[j] = temp;
	}

	int c = -1;
	for (int i = 8; i < 16; i++) {
		if (i > 11) {
			for (int t = 0; t < 6; t++) {
				mCells[i]->AddCard(randomDeck[c + 1]);
				c += 1;
			}
		}
		else {
			for (int t = 0; t < 7; t++) {
				mCells[i]->AddCard(randomDeck[c + 1]);
				c += 1;
			}
		}
	};

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
			mCells[i]->Draw(dc);
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


void CFreeCellDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int picked = -1;


	for (int i = 0; i < 16; i++) {
		//mCells[i]->SetSelected(false);
		//checks every cell and checks if it was clicked anywhere in the box.
		if (mCells[i]->IsClicked(point.x, point.y))
			picked = i;
	}



	// Check if the click was inside the window
	if (picked == -1) {
		return;
	}

	// checks if it was the first click
	if (mSelected == -1) {
		//check if we can move if so then remove the card
		if (mCells[picked]->CanRemoveCard()) {
			mCells[picked]->SetSelected(true); // highlight
			mSelected = picked;
		}
	}

	else {
		// last card of the first picked card
		int firstCard = mCells[mSelected]->GetTopCard();

		// in if statement I am passing the last card of the cell that was selected in the first click
		if (mCells[picked]->CanAcceptCard(firstCard)) {


			mCells[mSelected]->RemoveCard();
			mCells[picked]->AddCard(firstCard);

			mCells[mSelected]->SetSelected(false);
			mSelected = -1;
		}
		else {
			mCells[mSelected]->SetSelected(false);
			mSelected = -1;
		}
	}
	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}

