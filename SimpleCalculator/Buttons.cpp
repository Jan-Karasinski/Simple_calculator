#include "stdafx.h"
#include "Buttons.h"

RButton::RButton(bool _pl, const CString& desc, std::function<long double(std::vector<const CString*>)> function)
	: m_placeholder(_pl)
{
	m_compute = function;
	m_description = desc;
	
}

RButton::RButton(bool _pl, const CString& desc, std::function<long double(std::vector<const CString*>)> function, std::function<void(CString&)> special)
	: m_placeholder(_pl)
{
	m_compute = function;
	m_description = desc;
	special_care = 1;
	AddHistory = special;
}

bool RButton::GetPlaceholder() {
	return m_placeholder;
}

CString RButton::GetDescription() const {
	return m_description;
}

long double RButton::compute(std::vector<const CString*> pArr) const {
	return m_compute(pArr);
}


AButton::AButton(const CString& desc, arithmetic_operator _operator)
{
	m_operator = _operator;
	m_description = desc;
}

CString AButton::GetDescription() const {
	return m_description;
}

arithmetic_operator AButton::GetOperator() const {
	return m_operator;
}


DButton::DButton(const CString& desc)
{
	m_description = desc;
}

CString DButton::GetDescription() const {
	return m_description;
}