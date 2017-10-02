#pragma once
#include "afxwin.h"
#include "MathHistory.h"
#include "MathOPS.h"
#include <map>

enum class ACTION : UINT {
	REPLACING, ARITHMETIC, BUTTON
};

class CSimpleCalculatorDlg;

class FontControler {
protected:
	void ResizeFont(CWnd*, CFont*, int);
	void SetAndResize(CWnd*, const CString&);
};

class Controler : public FontControler
{
	CSimpleCalculatorDlg* _dlg;
	CEdit*  _display;
	History* m_history;
	MathOPS* m_math;

	std::map<UINT, CButton*>* _buttons;

	CString m_result, m_second;
	bool m_placeholder{ 0 };
	bool m_error{ 0 };
	bool m_new_sequence{ 1 };
	ACTION m_recent_action = ACTION::BUTTON;

public:
	Controler(CSimpleCalculatorDlg*, CEdit*, std::map<UINT, CButton*>*, History*, MathOPS*);

	void Reset();

	void ArithmeticOPS(UINT);
	void ReplacingOPS(UINT);
	void AddDigit(UINT);
	void OnClickDPoint();
	void OnClickBack();
	void OnClickCe();
	void OnClickC();
	void OnClickEquals();

	friend class CSimpleCalculatorDlg;
};

