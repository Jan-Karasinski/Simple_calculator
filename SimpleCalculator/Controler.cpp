#include "stdafx.h"
#include "SimpleCalculatorDlg.h"
#include "Controler.h"
#include "Buttons.h"

//Font
void FontControler::ResizeFont(CWnd *pWnd, CFont *pFont, int height) {
	pFont->Detach();
	pFont->CreateFont(height, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, L"Microsoft Sans serif");
	pWnd->SetFont(pFont);
}

void FontControler::SetAndResize(CWnd *pWnd, const CString &text) {
	pWnd->SetWindowText(text);
	ResizeFont(pWnd, pWnd->GetFont(), text.GetLength() > 12 ? 18 : 24);
}

Controler::Controler(CSimpleCalculatorDlg* pdlg, CEdit* pwnd, std::map<UINT, CButton*>* pmap, History* phist, MathOPS* pmath)
	: _dlg(pdlg), _display(pwnd), _buttons(pmap), m_history(phist), m_math(pmath)
{
}

void Controler::Reset() {
	m_result = "";
	m_second = "";
	m_placeholder = 0;
	m_error = 0;
	m_recent_action = ACTION::BUTTON;

	m_math->resetOperator();
	m_history->Clear();
}

//Msg handlers
void Controler::AddDigit(UINT nid) {
	if (!m_error) {
		if (!m_history->IsEmpty()) {
			if (!m_history->LastIsArith()) {
				m_history->DeleteLast();
			}
		}
		CString temp;
		_display->GetWindowText(temp);
		if (temp != "0" && !m_placeholder) {
			temp += static_cast<DButton*>(_dlg->GetDlgItem(nid))->GetDescription();
		}
		else {
			temp = static_cast<DButton*>(_dlg->GetDlgItem(nid))->GetDescription();
			m_placeholder = 0;
		}
		SetAndResize(_display, temp);
		m_recent_action = ACTION::BUTTON;
	}
	static_cast<CButton*>(_dlg->GetDlgItem(nid))->SetButtonStyle(BS_FLAT);
}

void Controler::OnClickDPoint() {
	if (!m_error) {
		CString temp;
		_display->GetWindowText(temp);
		if (!m_placeholder && temp.Find('.') == -1) {
			temp += '.';
			SetAndResize(_display, temp);
		}
	}
	_buttons->at(IDC_BUTTON_DPOINT)->SetButtonStyle(BS_FLAT);
}

void Controler::ArithmeticOPS(UINT nid) {
	if (!m_error) {
		try
		{
			if (m_history->IsEmpty() || !m_math->isSetOperator()) {
				_display->GetWindowText(m_result);
				m_history->Add(m_result);
			}
			else if (m_recent_action != ACTION::ARITHMETIC) {
				_display->GetWindowText(m_second);
				if (!m_placeholder) {
					m_history->Add(m_second);
				}
				m_result.Format(L"%.16g", m_math->compute(m_result, m_second));

				SetAndResize(_display, m_result);
			}
			//m_math.setOperator(static_cast<AButton*>(_dlg->GetDlgItem(nid)));
			m_math->setOperator(static_cast<AButton*>(_buttons->at(nid)));
			m_history->Add(static_cast<AButton*>(_buttons->at(nid)));
			m_placeholder = 1;
			m_recent_action = ACTION::ARITHMETIC;
		}
		catch (const std::exception& e)
		{
			SetAndResize(_display, CString(e.what()));
#ifndef NDEBUG
			AfxMessageBox(L"ArithmeticOPS");
#endif
			m_error = 1;
		}
	}
	static_cast<CButton*>(_dlg->GetDlgItem(nid))->SetButtonStyle(BS_FLAT);
}

// Operators which replaces current number
void Controler::ReplacingOPS(UINT nid) {
	if (!m_error) {
		try
		{
			CString temp;
			if (m_history->IsEmpty()) {
				_display->GetWindowText(m_result);
				m_history->Add(static_cast<RButton*>(_buttons->at(nid)), m_result);
				temp.Format(L"%.16g", m_math->compute(static_cast<RButton*>(_buttons->at(nid)), { &m_result }));
			}
			else {
				_display->GetWindowText(temp);
				m_history->Add(static_cast<RButton*>(_dlg->GetDlgItem(nid)), temp);
				temp.Format(L"%.16g", m_math->compute(static_cast<RButton*>(_buttons->at(nid)), { &temp, &m_result }));
			}
			SetAndResize(_display, temp);
			m_placeholder = static_cast<RButton*>(_buttons->at(nid))->GetPlaceholder();
			m_recent_action = ACTION::REPLACING;
		}
		catch (const std::exception& e)
		{
			SetAndResize(_display, CString(e.what()));
#ifndef NDEBUG
			AfxMessageBox(L"ReplacingOPS");
#endif
			m_error = 1;
		}
	}
	static_cast<CButton*>(_buttons->at(nid))->SetButtonStyle(BS_FLAT);
}

void Controler::OnClickBack() {
	if (!m_error && !m_placeholder) {
		CString temp;
		_display->GetWindowText(temp);
		if (temp.GetLength() > 1) {
			temp.Delete(temp.GetLength() - 1, 1);
			SetAndResize(_display, temp);
		}
		else {
			SetAndResize(_display, L"0");
		}
	}
	m_recent_action = ACTION::BUTTON;
	_buttons->at(IDC_BUTTON_BACK)->SetButtonStyle(BS_FLAT);
}

void Controler::OnClickCe() {
	if (m_error) {
		Reset();
	}
	else if (m_history->LastIsRepl()) {
		m_history->DeleteLast();
	}
	SetAndResize(_display, L"0");
	m_recent_action = ACTION::BUTTON;
	_buttons->at(IDC_BUTTON_CE)->SetButtonStyle(BS_FLAT);
}

void Controler::OnClickC() {
	SetAndResize(_display, L"0");
	Reset();
	m_recent_action = ACTION::BUTTON;
	_buttons->at(IDC_BUTTON_BACK)->SetButtonStyle(BS_FLAT);
}

void Controler::OnClickEquals() {
	if (!m_error && m_math->isSetOperator()) {
		try
		{
			if (!m_placeholder) {
				_display->GetWindowText(m_second);

				m_result.Format(L"%.16g", m_math->compute(m_result, m_second));

				SetAndResize(_display, m_result);
				m_placeholder = 1;
			}
			else {
				if (!m_history->IsEmpty()) {
					_display->GetWindowText(m_second);
				}
				m_result.Format(L"%.16g", m_math->compute(m_result, m_second));

				SetAndResize(_display, m_result);
			}
			m_history->Clear();
			m_recent_action = ACTION::BUTTON;
		}
		catch (const std::exception& e)
		{
			SetAndResize(_display, CString(e.what()));
#ifndef NDEBUG
			AfxMessageBox(L"OnBnClickedButtonEquals");
#endif
			m_error = 1;
		}
	}
	_buttons->at(IDC_BUTTON_EQUALS)->SetButtonStyle(BS_FLAT);
}