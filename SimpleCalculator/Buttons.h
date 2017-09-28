#pragma once
#include "resource.h"
#include "afxwin.h"
#include <functional>
#include <vector>

typedef std::function<long double(const CString&, const CString&)> arithmetic_operator;

class IHistoryButton {
public:
	CString m_description;
	virtual CString GetDescription() const = 0;
};

class ISpecialHistoryButton : public IHistoryButton {
public:
	bool special_care = 0;
	std::function<void(CString&)> AddHistory = nullptr;
};

class IReplacingButton {
public:
	std::function<long double(std::vector<const CString*>)> m_compute;
	virtual long double compute(std::vector<const CString*>) const = 0;
};

class IArithmeticButton {
public:
	arithmetic_operator m_operator;
	virtual arithmetic_operator GetOperator() const = 0;
};

//Button for replacing operations
class RButton final : public CButton, public ISpecialHistoryButton, public IReplacingButton {
	bool m_placeholder;
public:
	RButton(bool _placeholder, const CString&, std::function<long double(std::vector<const CString*>)>);

	RButton(bool _placeholder, const CString&, std::function<long double(std::vector<const CString*>)>, std::function<void(CString&)>);

	bool GetPlaceholder();

	CString GetDescription() const final;

	long double compute(std::vector<const CString*>) const final;
};

//Button for arithmetic operations
class AButton final : public CButton, public IHistoryButton, public IArithmeticButton {
public:
	AButton(const CString&, arithmetic_operator);

	CString GetDescription() const final;

	arithmetic_operator GetOperator() const final;
};

//Button for digis
class DButton final : public CButton, public IHistoryButton {
public:
	DButton(const CString&);

	CString GetDescription() const final;
};