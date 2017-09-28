#include "stdafx.h"
#include "MathHistory.h"

History::History(CEdit* pDisplay) : _display(pDisplay)
{
}

void History::Add(ISpecialHistoryButton* pButton, CString& number) {
	if (pButton->special_care) {
		pButton->AddHistory(number);
	}
	else {
		number.TrimRight('.');
		if (_history.IsEmpty()) {
			_history = pButton->GetDescription() + L"(" + number + L")";
		}
		else if(LastIsRepl()) {
			_history.Insert(_history.ReverseFind(' ') + 1, pButton->GetDescription() + L"(");
			_history += ')';
		}
		else {
			if (LastIsNumber()) {
				DeleteLast();
			}
			_history += L" " + pButton->GetDescription() + L"(" + number + L")";
		}
	}
	Update();
}

void History::Add(CString& number) {
	number.TrimRight('.');
	if (_history.IsEmpty()) {
		_history = number;
	}
	else if (LastIsNumber() || LastIsRepl()) {
		DeleteLast();
		_history += L" " + number;
	}
	else if (LastIsArith()) {
		_history += L" " + number;
	}
	Update();
}

void History::Add(IHistoryButton* pButton) {
	// if last pos is operator - replace
	if (!IsEmpty()) {
		if (LastIsArith()) {
			_history.SetAt(_history.GetLength() - 1, pButton->GetDescription()[0]);
		}
		else {
			_history += L" " + pButton->GetDescription();
		}
	}
	Update();
}

void History::DeleteLast() {
	int i = _history.ReverseFind(' ');
	_history.Delete(i, _history.GetLength() - i);
	Update();
}

bool History::IsEmpty() {
	return _history.IsEmpty();
}

bool History::LastIsNumber() {
	return isdigit(_history[_history.GetLength() - 1]);
}

bool History::LastIsArith() {
	wchar_t c = _history[_history.GetLength() - 1];
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool History::LastIsRepl() {
	return _history[_history.GetLength() - 1] == ')';
}

int History::GetLength() {
	return _history.GetLength();
}

void History::Clear() {
	_history.Empty();
	Update();
}

void History::Update() {
	if (_display) {
		_display->SetWindowText(_history);
	}
}