#include "stdafx.h"
#include "MathOPS.h"
#include <cmath>
#include <exception>

long double MathOPS::compute(const CString& pF, const CString& pS) const {
	return m_operator(pF, pS);
}

long double MathOPS::compute(IReplacingButton* pButton, std::vector<const CString*> pArr) const {
	return pButton->compute(pArr);
}

void MathOPS::setOperator(IArithmeticButton* pButton) {
	m_operator = pButton->GetOperator();
}

void MathOPS::resetOperator() {
	m_operator = nullptr;
}

bool MathOPS::isSetOperator() {
	return m_operator != nullptr;
}


long double MathOPS::add(const CString& pF, const CString& pS) const {
	return _tstof(pF) + _tstof(pS);
}

long double MathOPS::sub(const CString& pF, const CString& pS) const {
	return _tstof(pF) - _tstof(pS);
}

long double MathOPS::mult(const CString& pF, const CString& pS) const {
	return _tstof(pF) * _tstof(pS);
}

long double MathOPS::div(const CString& pF, const CString& pS) const {
	if (pS == "0") {
		if (pF == "0") {
			throw std::exception("Indefinite result");
		}
		throw std::exception("Cannot divide by 0");
	}
	return _tstof(pF) / _tstof(pS);
}


long double MathOPS::perc(std::vector<const CString*>& pArr) const {
	if ((pArr.size() < 2) || *pArr[0] == "0" || *pArr[0] == "") {
		return 0;
	}
	else {
		return _tstof(*pArr[1]) * (_tstof(*pArr[0]) / 100);
	}
}

long double MathOPS::reciproc(std::vector<const CString*>& pArr) const {
	if (*pArr[0] == "0") {
		throw std::exception("Cannot divide by 0");
	}
	return 1.0 / _tstof(*pArr[0]);
}

long double MathOPS::sqrt(std::vector<const CString*>& pArr) const {
	if (*pArr[0][0] == '-') {
		throw std::exception("Invalid input");
	}
	return ::sqrtl(_tstof(*pArr[0]));
}

long double MathOPS::neg(std::vector<const CString*>& pArr) const {
	return *pArr[0] == "0" ? 0 : -_tstof(*pArr[0]);
}