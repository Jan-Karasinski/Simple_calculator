#pragma once
#include "afxwin.h"
#include "Buttons.h"
#include <functional>

class MathOPS
{
protected:
	std::function<long double(const CString&, const CString&)> m_operator = nullptr;

public:
	long double compute(const CString&, const CString&) const;
	long double compute(IReplacingButton*, std::vector<const CString*>) const;

	void setOperator(IArithmeticButton*);
	void resetOperator();
	bool isSetOperator();

	long double add	(const CString&, const CString&) const;
	long double sub	(const CString&, const CString&) const;
	long double mult(const CString&, const CString&) const;
	long double div	(const CString&, const CString&) const;

	long double perc	(std::vector<const CString*>&) const;
	long double reciproc(std::vector<const CString*>&) const;
	long double sqrt	(std::vector<const CString*>&) const;
	long double neg		(std::vector<const CString*>&) const;

public:
	MathOPS() = default;

};