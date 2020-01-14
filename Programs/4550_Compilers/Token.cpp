#include "Token.h"


TokenClass::TokenClass() {
}

TokenClass::TokenClass(TokenType type, const string & lexeme) {
	mType = type;
	mLexeme = lexeme;
}

TokenType TokenClass::GetTokenType() const {
	return mType; 
}

const string & TokenClass::GetTokenTypeName() const {
	return gTokenTypeNames[mType];
}

string TokenClass::GetLexeme() const { 
	return mLexeme;
}

void TokenClass::CheckReserved() {
	string lexeme = GetLexeme();
	if (lexeme == "void") {
		mType = VOID_TOKEN;
	}
	else if (lexeme == "main") {
		mType = MAIN_TOKEN;
	}
	else if (lexeme == "int") {
		mType = INT_TOKEN;
	}
	else if (lexeme == "cout") {
		mType = COUT_TOKEN;
	}
	else if (lexeme == "if") {
		mType = IF_TOKEN;
	}
	else if (lexeme == "else") {
		mType = ELSE_TOKEN;
	}
	else if (lexeme == "while") {
		mType = WHILE_TOKEN;
	}
	else if (lexeme == "do") {
		mType = DO_TOKEN;
	}
	else if (lexeme == "or") {
		mType = OR_TOKEN;
	}
	else if (lexeme == "and") {
		mType = AND_TOKEN;
	}
	else if (lexeme == "repeat") {
		mType = REPEAT_TOKEN;
	}
	else if (lexeme == "endl") {
		mType = ENDL_TOKEN;
	}
	else if (lexeme == "true") {
		mType = INTEGER_TOKEN;
		mLexeme = "1";
	}
	else if (lexeme == "false") {
		mType = INTEGER_TOKEN;
		mLexeme = "0";
	}
}

const string & TokenClass::GetTokenTypeName(TokenType type) {
	return gTokenTypeNames[type];
}

ostream & operator<<(ostream & out, const TokenClass & tc) {
	const TokenType myToke = tc.GetTokenType();
	const string& tokeString = tc.GetTokenTypeName(myToke);
	out << tokeString << '\t' << tc.GetLexeme();
	return out;
}


