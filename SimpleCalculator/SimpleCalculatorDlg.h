#pragma once
#include "afxwin.h"
#include "MathOPS.h"
#include "MathHistory.h"
#include "Buttons.h"
#include <vector>

enum class ACTION : UINT {
	REPLACING, ARITHMETIC, BUTTON
};

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

	CString m_result, m_second;
	bool m_placeholder{ 0 };
	bool m_error{ 0 };
	bool m_new_sequence{ 1 };
	ACTION m_recent_action = ACTION::BUTTON;

	CFont m_font_button, m_font_cedit;

	DButton m_button_1{ CString("1") }, m_button_2{ CString("2") }, m_button_3{ CString("3") },
			m_button_4{ CString("4") }, m_button_5{ CString("5") }, m_button_6{ CString("6") },
			m_button_7{ CString("7") }, m_button_8{ CString("8") }, m_button_9{ CString("9") },
			m_button_0{ CString("0") };

	AButton m_button_plus  { CString("+"), [&](const CString& a, const CString& b) { return m_math.add (a, b); } },
			m_button_minus { CString("-"), [&](const CString& a, const CString& b) { return m_math.sub (a, b); } },
			m_button_mult  { CString("*"), [&](const CString& a, const CString& b) { return m_math.mult(a, b); } },
			m_button_div   { CString("/"), [&](const CString& a, const CString& b) { return m_math.div	(a, b); } };
	
	RButton m_button_reciproc { true, CString("reciproc"), [&](std::vector<const CString*> vec) {
																	return m_math.reciproc(std::move(vec)); } },
			m_button_perc	  { true, CString("perc"),	   [&](std::vector<const CString*> vec) {
																	return m_math.perc	 (std::move(vec)); },
									[&](CString& number) {
										if (!m_history.IsEmpty()) {
											CString temp;
											if (m_history.LastIsRepl()) {
												m_history.DeleteLast();
											}
											temp.Format(L" %.16g", m_button_perc.compute({ &number, &m_result }));
											m_history._history += temp;
										}
										else {
											m_history._history = L"0";
										}}},
			m_button_sqrt { true,  CString("sqrt"),	  [&](std::vector<const CString*> vec) { return m_math.sqrt(std::move(vec)); } },
			m_button_neg  { false, CString("negate"), [&](std::vector<const CString*> vec) { return m_math.neg (std::move(vec)); },
									[&](CString& number) {
										if (!m_history.IsEmpty()) {
											if (m_history.LastIsNumber()) {
												m_history.DeleteLast();
												m_history._history += L'-' + number;
											}
											else if (m_history.LastIsRepl()) {
												auto& history = m_history._history;
												history.Insert(history.ReverseFind(' ') + 1, m_button_neg.GetDescription() + L"(");
												history += ')';
											}
										}}};

	CButton m_button_equals, m_button_ce, m_button_c, m_button_dpoint;
	CButton m_button_back;

	CEdit	m_output_ctrl, m_history_ctrl;

	std::vector<CButton *> buttons_map = {  &m_button_1, &m_button_2, &m_button_3, &m_button_4, &m_button_5, &m_button_6,
											&m_button_7, &m_button_8, &m_button_9, &m_button_0,
											
											&m_button_plus, &m_button_minus, &m_button_mult, &m_button_div,

											&m_button_reciproc, &m_button_perc, &m_button_sqrt, &m_button_neg,
	
											&m_button_equals, &m_button_ce, &m_button_c, &m_button_dpoint,
											&m_button_back };

public:
	void ResizeFont(CWnd*, CFont*, int);
	void SetAndResize(CWnd*, const CString&);
	void Reset();

	afx_msg void ArithmeticOPS(UINT);
	afx_msg void ReplacingOPS(UINT);
	
	afx_msg void AddDigit(UINT);
	afx_msg void OnBnClickedButtonDPoint();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonCe();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonEquals();
};
