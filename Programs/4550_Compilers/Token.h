#pragma once
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN, DO_TOKEN, ENDL_TOKEN,

	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,

	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, /*EXPONENT_TOKEN,*/ PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN, DIVIDE_TOKEN,
	MOD_TOKEN, TIMESEQUAL_TOKEN, DIVIDEEQUAL_TOKEN, SHIFT_TOKEN,

	// Other Characters:
	SEMICOLON_TOKEN, LEFTPAREN_TOKEN, RIGHTPAREN_TOKEN, LEFTBRACKET_TOKEN,
	RIGHTBRACKET_TOKEN,

	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, RETURN_TOKEN, AND_TOKEN, OR_TOKEN, REPEAT_TOKEN,
	BAD_TOKEN, ENDFILE_TOKEN
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "IF", "ELSE", "WHILE", "DO", "ENDL",

	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "ISEQUAL", "NOTEQUAL",

	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", /*"EXPONENT",*/ "PLUSEQUAL", "MINUSEQUAL", "DIVIDE",
	"MOD_TOKEN", "TIMESEQUAL", "DIVIDEEQUAL", "SHIFT",

	"SEMICOLON", "LEFTPAREN", "RIGHTPAREN", "LEFTBRACKET", "RIGHTBRACKET",
	"IDENTIFIER", "INTEGER", "RETURN", "AND", "OR", "REPEAT"
	"BAD", "ENDFILE"
};

class TokenClass {

public:
	TokenClass();
	TokenClass(TokenType type, const std::string & lexeme);

	TokenType GetTokenType() const;
	const string & GetTokenTypeName() const;
	string GetLexeme() const;

	void CheckReserved();

	static const string & GetTokenTypeName(TokenType type);

protected:
	TokenType mType;
	string mLexeme;

	static char sTokenNames[100][20];
};

ostream & operator<<(ostream & out, const TokenClass & tc);
