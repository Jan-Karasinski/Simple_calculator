#pragma once
#include "resource.h"
#include "Buttons.h"

struct History {
	CEdit* _display;
	CString _history;

	History(CEdit*);

	// Add should be used before compute
	//for replacing operators
	void Add(ISpecialHistoryButton*, CString&);
	//for numbers
	void Add(CString&);
	//for arithmetic operators
	void Add(IHistoryButton*);
	//delete last sequence of replacing ops to closest arithmetic op
	void DeleteLast();
	bool IsEmpty();
	//true if last char is digit, false otherwise
	bool LastIsNumber();
	//true if last char is arithmetic op, false otherwise
	bool LastIsArith();
	//true if last char is replacing op, false otherwise
	bool LastIsRepl();
	int	 GetLength();
	void Clear();
	//display history
	void Update();
};