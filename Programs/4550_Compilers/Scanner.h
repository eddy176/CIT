#pragma once
#include "Token.h"
#include "Debug.h"
#include "StateMachine.h"


class ScannerClass{

public:
	ScannerClass();
	ScannerClass(string sString);

	~ScannerClass(void);
	int GetLineNumber();

	TokenClass GetNextToken();
	TokenClass PeekNextToken();


private:
	ifstream mFin;
	int mLineNumber = 1;

};