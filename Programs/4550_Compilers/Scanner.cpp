#include "Scanner.h"

ScannerClass::ScannerClass() {
}

ScannerClass::ScannerClass(string filename) {
	MSG("Initializing ScannerClass object");
	mFin.open(filename);
	if (!mFin.is_open()) {
		cout << "Error reading file" << endl;
		exit(EXIT_FAILURE);
	}
}

ScannerClass::~ScannerClass(void) {
	mFin.close();
}

int ScannerClass::GetLineNumber() {
	return mLineNumber;
}


TokenClass ScannerClass::GetNextToken() {	// need to make the constructor of scanner code
	TokenType TT;
	StateMachineClass SM;
	string lexeme;
	MachineState state;
	char c;
	do {
		c = mFin.get();
		if (c == '\n') {
			mLineNumber += 1;
		}
		lexeme += c;
		state = SM.UpdateState(c, TT);	// from part 3
		if (state == START_STATE) {
			lexeme = "";
		}
	} while (state != CANTMOVE_STATE);
	mFin.unget();
	if (c == '\n') {
		mLineNumber -= 1;
	}
	lexeme.pop_back();
 	if (TT == BAD_TOKEN) {
		cerr << "This lexeme made a bad token: " << lexeme;
		exit(1);
	}
	TokenClass T(TT, lexeme);
	T.CheckReserved();
	return T;
}

TokenClass ScannerClass::PeekNextToken() {

	long long fileoffset;
	int line;
	fileoffset = mFin.tellg();
	line = GetLineNumber();
	TokenClass tc = GetNextToken();
	if (!mFin) {
		mFin.clear();
	}
	mFin.seekg(fileoffset);
	mLineNumber = line;
	return tc;
}

