#pragma once
#include "afxwin.h"
#include "MathOPS.h"
#include "MathHistory.h"
#include "Buttons.h"
#include "Controler.h"
#include <vector>

// CSimpleCalculatorDlg dialog
class CSimpleCalculatorDlg : public CDialogEx
{
	// Construction
public:
	CSimpleCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_SIMPLECALCULATOR_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	BOOL PreTranslateMessage(MSG*);

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	History m_history;
	MathOPS m_math;
	Controler m_controler;

	CFont m_font_button, m_font_cedit;

	DButton m_button_1{ CString("1") }, m_button_2{ CString("2") }, m_button_3{ CString("3") },
			m_button_4{ CString("4") }, m_button_5{ CString("5") }, m_button_6{ CString("6") },
			m_button_7{ CString("7") }, m_button_8{ CString("8") }, m_button_9{ CString("9") },
			m_button_0{ CString("0") };

	AButton m_button_plus	{ CString("+"), [&](const CString& a, const CString& b) { return m_controler.m_math->add (a, b); } },
			m_button_sub	{ CString("-"), [&](const CString& a, const CString& b) { return m_controler.m_math->sub (a, b); } },
			m_button_mult	{ CString("*"), [&](const CString& a, const CString& b) { return m_controler.m_math->mult(a, b); } },
			m_button_div	{ CString("/"), [&](const CString& a, const CString& b) { return m_controler.m_math->div	(a, b); } };
	
	RButton m_button_reciproc { true, CString("reciproc"), [&](std::vector<const CString*> vec) { return m_controler.m_math->reciproc (std::move(vec)); } },
			m_button_perc	  { true, CString("perc"),	   [&](std::vector<const CString*> vec) { return m_controler.m_math->perc (std::move(vec)); },
									[&](CString& number) {
										if (!m_controler.m_history->IsEmpty()) {
											CString temp;
											if (m_controler.m_history->LastIsRepl()) {
												m_controler.m_history->DeleteLast();
											}
											temp.Format(L" %.16g", m_button_perc.compute({ &number, &(m_controler.m_result) }));
											m_controler.m_history->_history += temp;
										}
										else {
											m_controler.m_history->_history = L"0";
										}}},
			m_button_sqrt { true,  CString("sqrt"),	  [&](std::vector<const CString*> vec) { return m_controler.m_math->sqrt(std::move(vec)); } },
			m_button_neg  { false, CString("negate"), [&](std::vector<const CString*> vec) { return m_controler.m_math->neg (std::move(vec)); },
									[&](CString& number) {
										if (!m_controler.m_history->IsEmpty()) {
											if (m_controler.m_history->LastIsNumber()) {
												m_controler.m_history->DeleteLast();
												m_controler.m_history->_history += L'-' + number;
											}
											else if (m_controler.m_history->LastIsRepl()) {
												auto& history = m_controler.m_history->_history;
												history.Insert(history.ReverseFind(' ') + 1, m_button_neg.GetDescription() + L"(");
												history += ')';
											}
										}}};

	CButton m_button_equals, m_button_ce, m_button_c, m_button_dpoint, m_button_back;

	CEdit m_output_ctrl, m_history_ctrl;

	std::map<UINT, CButton*> buttons_map = { { IDC_BUTTON1, &m_button_1 },{IDC_BUTTON2, &m_button_2},{ IDC_BUTTON3, &m_button_3 },
											{ IDC_BUTTON4, &m_button_4 },{ IDC_BUTTON5, &m_button_5 },{ IDC_BUTTON6, &m_button_6 },
											{ IDC_BUTTON7, &m_button_7 },{ IDC_BUTTON8, &m_button_8 },{ IDC_BUTTON9, &m_button_9 },
											{ IDC_BUTTON0, &m_button_0 },

											{ IDC_BUTTON_PLUS, &m_button_plus },{ IDC_BUTTON_SUB, &m_button_sub },
											{ IDC_BUTTON_MULT, &m_button_mult },{ IDC_BUTTON_DIV, &m_button_div },
	
											{ IDC_BUTTON_RECIPROC, &m_button_reciproc },{ IDC_BUTTON_PERC, &m_button_perc }, 
											{ IDC_BUTTON_SQRT, &m_button_sqrt },{ IDC_BUTTON_NEG, &m_button_neg }, 
	
											{ IDC_BUTTON_EQUALS, &m_button_equals },{ IDC_BUTTON_CE, &m_button_ce }, 
											{ IDC_BUTTON_C, &m_button_c },{ IDC_BUTTON_DPOINT, &m_button_dpoint }, 
											{ IDC_BUTTON_BACK, &m_button_back } };

public:
	afx_msg void ArithmeticOPS(UINT);
	afx_msg void ReplacingOPS(UINT);
	afx_msg void AddDigit(UINT);
	afx_msg void OnClickDPoint();
	afx_msg void OnClickBack();
	afx_msg void OnClickCe();
	afx_msg void OnClickC();
	afx_msg void OnClickEquals();
};
