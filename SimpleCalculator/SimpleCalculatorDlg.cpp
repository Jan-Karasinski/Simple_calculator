
// SimpleCalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleCalculator.h"
#include "SimpleCalculatorDlg.h"
#include "afxdialogex.h"
#include "Operations.h"
#include <exception>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSimpleCalculatorDlg dialog

CSimpleCalculatorDlg::CSimpleCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SIMPLECALCULATOR_DIALOG, pParent), m_history(&m_history_ctrl),
		m_controler(&m_output_ctrl, &buttons_map, &m_history, &m_math)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON0, m_button_0);
	DDX_Control(pDX, IDC_BUTTON1, m_button_1);
	DDX_Control(pDX, IDC_BUTTON2, m_button_2);
	DDX_Control(pDX, IDC_BUTTON3, m_button_3);
	DDX_Control(pDX, IDC_BUTTON4, m_button_4);
	DDX_Control(pDX, IDC_BUTTON5, m_button_5);
	DDX_Control(pDX, IDC_BUTTON6, m_button_6);
	DDX_Control(pDX, IDC_BUTTON7, m_button_7);
	DDX_Control(pDX, IDC_BUTTON8, m_button_8);
	DDX_Control(pDX, IDC_BUTTON9, m_button_9);

	DDX_Control(pDX, IDC_EDIT_OUT, m_output_ctrl);
	DDX_Control(pDX, IDC_EDIT_HISTORY, m_history_ctrl);

	DDX_Control(pDX, IDC_BUTTON_DPOINT, m_button_dpoint);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_button_back);
	DDX_Control(pDX, IDC_BUTTON_CE, m_button_ce);
	DDX_Control(pDX, IDC_BUTTON_C, m_button_c);
	DDX_Control(pDX, IDC_BUTTON_EQUALS, m_button_equals);

	DDX_Control(pDX, IDC_BUTTON_PLUS, m_button_plus);
	DDX_Control(pDX, IDC_BUTTON_SUB, m_button_sub);
	DDX_Control(pDX, IDC_BUTTON_MULT, m_button_mult);
	DDX_Control(pDX, IDC_BUTTON_DIV, m_button_div);

	DDX_Control(pDX, IDC_BUTTON_PERC, m_button_perc);

	DDX_Control(pDX, IDC_BUTTON_RECIPROC, m_button_reciproc);
	DDX_Control(pDX, IDC_BUTTON_SQRT, m_button_sqrt);
	DDX_Control(pDX, IDC_BUTTON_NEG, m_button_neg);
}

BEGIN_MESSAGE_MAP(CSimpleCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BUTTON0, IDC_BUTTON9, &AddDigit)
	ON_COMMAND_RANGE(IDC_BUTTON_PLUS, IDC_BUTTON_DIV, &ArithmeticOPS)
	ON_COMMAND_RANGE(IDC_BUTTON_PERC, IDC_BUTTON_NEG, &ReplacingOPS)
	ON_BN_CLICKED(IDC_BUTTON_DPOINT, &CSimpleCalculatorDlg::OnClickDPoint)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CSimpleCalculatorDlg::OnClickBack)
	ON_BN_CLICKED(IDC_BUTTON_CE, &CSimpleCalculatorDlg::OnClickCe)
	ON_BN_CLICKED(IDC_BUTTON_C, &CSimpleCalculatorDlg::OnClickC)
	ON_BN_CLICKED(IDC_BUTTON_EQUALS, &CSimpleCalculatorDlg::OnClickEquals)
END_MESSAGE_MAP()

// CSimpleCalculatorDlg message handlers

BOOL CSimpleCalculatorDlg::PreTranslateMessage(MSG* pMSG) {
	if (pMSG->message == WM_SETFOCUS) {
		return TRUE;
	}
	else if (pMSG->message == WM_KEYDOWN) {
		SHORT value = GetKeyState(VK_SHIFT);
		bool toggled = ((unsigned short) value) >> 15;
		if (toggled) {
			switch (pMSG->wParam) {
				case 0x38: {
					ArithmeticOPS(IDC_BUTTON_MULT); break;
				}
				case VK_ADD: {
					ArithmeticOPS(IDC_BUTTON_PLUS); break;
				}
			}
		}
		else {
			switch (pMSG->wParam) {
				case VK_NUMPAD0: case 0x30: {
					AddDigit(IDC_BUTTON0); break;
				}
				case VK_NUMPAD1: case 0x31: {
					AddDigit(IDC_BUTTON1); break;
				}
				case VK_NUMPAD2: case 0x32: {
					AddDigit(IDC_BUTTON2); break;
				}
				case VK_NUMPAD3: case 0x33: {
					AddDigit(IDC_BUTTON3); break;
				}
				case VK_NUMPAD4: case 0x34: {
					AddDigit(IDC_BUTTON4); break;
				}
				case VK_NUMPAD5: case 0x35: {
					AddDigit(IDC_BUTTON5); break;
				}
				case VK_NUMPAD6: case 0x36: {
					AddDigit(IDC_BUTTON6); break;
				}
				case VK_NUMPAD7: case 0x37: {
					AddDigit(IDC_BUTTON7); break;
				}
				case VK_NUMPAD8: case 0x38: {
					AddDigit(IDC_BUTTON8); break;
				}
				case VK_NUMPAD9: case 0x39: {
					AddDigit(IDC_BUTTON9); break;
				}
				case VK_DECIMAL: case VK_OEM_PERIOD: {
					OnClickDPoint(); break;
				}

				case VK_ADD: case VK_OEM_PLUS: {
					ArithmeticOPS(IDC_BUTTON_PLUS); break;
				}
				case VK_SUBTRACT: case VK_OEM_MINUS: {
					ArithmeticOPS(IDC_BUTTON_SUB); break;
				}

				case VK_MULTIPLY: {
					ArithmeticOPS(IDC_BUTTON_MULT); break;
				}
				case VK_DIVIDE: case VK_OEM_2: {
					ArithmeticOPS(IDC_BUTTON_DIV); break;
				}
				case VK_RETURN: {
					OnClickEquals(); return TRUE; // Prevent closing dlg
				}
				case VK_BACK: {
					OnClickBack(); break;
				}
				case VK_TAB: {
					return FALSE;
				}
				case VK_SPACE: {
					return TRUE;
				}
			}
		}
	}

	return CDialog::PreTranslateMessage(pMSG);
}

BOOL CSimpleCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_font_button.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
								0, 0, 0, 0, _T("Microsoft Sans serif"));
	m_font_cedit.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
								0, 0, 0, 0, _T("Microsoft Sans serif"));
	
	for (auto bt : buttons_map) {
		bt.second->SetFont(&m_font_button);
		bt.second->SetButtonStyle(BS_FLAT);
	}

	m_output_ctrl.SetFont(&m_font_cedit);
	m_output_ctrl.SetWindowText(L"0");

	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleCalculatorDlg::OnPaint()
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
HCURSOR CSimpleCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Msg handlers
void CSimpleCalculatorDlg::AddDigit(UINT nid) {
	m_controler.AddDigit(nid);
}

void CSimpleCalculatorDlg::ArithmeticOPS(UINT nid) {
	m_controler.ArithmeticOPS(nid);
}

// Operators which replaces current number
void CSimpleCalculatorDlg::ReplacingOPS(UINT nid) {
	m_controler.ReplacingOPS(nid);
}

void CSimpleCalculatorDlg::OnClickDPoint() {
	m_controler.OnClickDPoint();
}

void CSimpleCalculatorDlg::OnClickBack() {
	m_controler.OnClickBack();
}

void CSimpleCalculatorDlg::OnClickCe() {
	m_controler.OnClickCe();
}

void CSimpleCalculatorDlg::OnClickC() {
	m_controler.OnClickC();
}

void CSimpleCalculatorDlg::OnClickEquals() {
	m_controler.OnClickEquals();
}