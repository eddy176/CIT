#include "StateMachine.h"

//StateMachineClass::StateMachineClass();
StateMachineClass::StateMachineClass() {
	// First, initialize all the mLegalMoves to CANTMOVE_STATE
	// Then, reset the mLegalMoves that are legitimate
	for (int i = 0; i < LAST_STATE; i++)
	{
		for (int j = 0; j < LAST_CHAR; j++)
		{
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}

	for (int i = 0; i < LAST_STATE; i++)
	{
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}

	mCurrentState = START_STATE;

	// below are edges of the finite atomata going to every kind of state
//START
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[START_STATE][MOD_CHAR] = MOD_STATE;

	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATERTHAN_STATE;
	mLegalMoves[START_STATE][LEFTBRACKET_CHAR] = LEFTBRACKET_STATE;
	mLegalMoves[START_STATE][RIGHTBRACKET_CHAR] = RIGHTBRACKET_STATE;
	mLegalMoves[START_STATE][LEFTPAREN_CHAR] = LEFTPAREN_STATE;
	mLegalMoves[START_STATE][RIGHTPAREN_CHAR] = RIGHTPAREN_STATE;
	mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[START_STATE][LESS_CHAR] = LESSTHAN_STATE;
	mLegalMoves[START_STATE][ENDFILE_CHAR] = END_STATE;
	mLegalMoves[START_STATE][RETURN_CHAR] = START_STATE;


	// BLOCK COMMENTS
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENT_STATE;	// HW
	//START

	for (size_t i = 0; i < LAST_CHAR; i++) {
		mLegalMoves[BLOCKCOMMENT_STATE][i] = BLOCKCOMMENT_STATE;
		mLegalMoves[BLOCKCOMMENT_STATE][TIMES_CHAR] = CHALFWAY_STATE;
		mLegalMoves[TIMES_STATE][TIMES_CHAR] = CHALFWAY_STATE;
		mLegalMoves[CHALFWAY_STATE][DIVIDE_CHAR] = START_STATE;
		mLegalMoves[CHALFWAY_STATE][!DIVIDE_CHAR] = BLOCKCOMMENT_STATE;
	}

	//END
	mLegalMoves[TIMES_STATE][DIVIDE_CHAR] = START_STATE;

	// LINE COMMENT
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
	//START
	for (size_t i = 0; i < LAST_CHAR; i++) {
		mLegalMoves[LINECOMMENT_STATE][i] = LINECOMMENT_STATE;
	}

	mLegalMoves[LINECOMMENT_STATE][RETURN_CHAR] = START_STATE;
	mLegalMoves[LINECOMMENT_STATE][ENDFILE_CHAR] = END_STATE;
	//END LINE COMMENT

	//INSERTION
	mLegalMoves[LESSTHAN_STATE][LESS_CHAR] = INSERTION_STATE;

	// COMPARISONS
	mLegalMoves[LESSTHAN_STATE][EQUAL_CHAR] = LESSEQ_STATE;
	mLegalMoves[GREATERTHAN_STATE][EQUAL_CHAR] = GREATEREQ_STATE;
	mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = ISEQUAL_STATE;

	// SHIFT STATE	
	mLegalMoves[GREATERTHAN_STATE][GREATER_CHAR] = SHIFT_STATE;


	// INTEGER STATE
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;

	// IDENTIFIER
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][SEMICOLON_CHAR] = CANTMOVE_STATE;


	// AND / OR
	mLegalMoves[START_STATE][AND_CHAR] = AHALFWAY_STATE;
	mLegalMoves[AHALFWAY_STATE][AND_CHAR] = AND_STATE;
	mLegalMoves[AHALFWAY_STATE][!AND_CHAR] = START_STATE;

	mLegalMoves[START_STATE][OR_CHAR] = OHALFWAY_STATE;
	mLegalMoves[OHALFWAY_STATE][OR_CHAR] = OR_STATE;
	mLegalMoves[OHALFWAY_STATE][!OR_CHAR] = START_STATE;

	// EXPONENTS::
	mLegalMoves[TIMES_STATE][TIMES_CHAR] = EXPONENT_STATE;

	// PLUSEQUALS::
	mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUSEQUAL_STATE;
	mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MINUSEQUAL_STATE;
	

	mLegalMoves[TIMES_STATE][EQUAL_CHAR] = TIMESEQUAL_STATE;
	mLegalMoves[DIVIDE_STATE][EQUAL_CHAR] = DIVIDEEQUAL_STATE;







	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[MOD_STATE] = MOD_TOKEN;
	mCorrespondingTokenTypes[SHIFT_STATE] = SHIFT_TOKEN;


	mCorrespondingTokenTypes[ISEQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[LESSTHAN_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[GREATERTHAN_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[LESSEQ_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[GREATEREQ_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	
	// insertionstate
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[ENDL_STATE] = ENDL_TOKEN;

	mCorrespondingTokenTypes[END_STATE] = ENDFILE_TOKEN;
	mCorrespondingTokenTypes[LEFTPAREN_STATE] = LEFTPAREN_TOKEN;
	mCorrespondingTokenTypes[RIGHTPAREN_STATE] = RIGHTPAREN_TOKEN;
	mCorrespondingTokenTypes[LEFTBRACKET_STATE] = LEFTBRACKET_TOKEN;
	mCorrespondingTokenTypes[RIGHTBRACKET_STATE] = RIGHTBRACKET_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	
	
	mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
	//mCorrespondingTokenTypes[EXPONENT_STATE] = EXPONENT_TOKEN;

	mCorrespondingTokenTypes[PLUSEQUAL_STATE] = PLUSEQUAL_TOKEN;
	mCorrespondingTokenTypes[MINUSEQUAL_STATE] = MINUSEQUAL_TOKEN;

	mCorrespondingTokenTypes[TIMESEQUAL_STATE] = TIMESEQUAL_TOKEN;
	mCorrespondingTokenTypes[DIVIDEEQUAL_STATE] = DIVIDEEQUAL_TOKEN;
}


MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType) {
	// convert the input character into an input character type
	CharacterType charType = BAD_CHAR;

	if (isdigit(currentCharacter)) {
		charType = DIGIT_CHAR;
	}
	else if (currentCharacter == '&') {
		charType = AND_CHAR;
	}
	else if (currentCharacter == '|') {
		charType = OR_CHAR;
	}
	else if (isalpha(currentCharacter)) {
		charType = LETTER_CHAR;
	}
	else if (currentCharacter == '\n') {
		charType = RETURN_CHAR;
	}
	else if (isspace(currentCharacter)) {
		charType = WHITESPACE_CHAR;
	}
	else if (currentCharacter == '+') {
		charType = PLUS_CHAR;
	}
	else if (currentCharacter == '-') {
		charType = MINUS_CHAR;
	}
	else if (currentCharacter == '*') {
		charType = TIMES_CHAR;
	}
	else if (currentCharacter == '/') {
		charType = DIVIDE_CHAR;
	}
	else if (currentCharacter == '%') {
		charType = MOD_CHAR;
	}
	else if (currentCharacter == ';') {
		charType = SEMICOLON_CHAR;
	}
	else if (currentCharacter == '<') {
		charType = LESS_CHAR;
	}
	else if (currentCharacter == '>') {
		charType = GREATER_CHAR;
	}
	else if (currentCharacter == '(') {
		charType = LEFTPAREN_CHAR;
	}
	else if (currentCharacter == ')') {
		charType = RIGHTPAREN_CHAR;
	}
	else if (currentCharacter == '{') {
		charType = LEFTBRACKET_CHAR;
	}
	else if (currentCharacter == '}') {
		charType = RIGHTBRACKET_CHAR;
	}
	else if (currentCharacter == '=') {
		charType = EQUAL_CHAR;
	}
	else if (currentCharacter == EOF) {
		charType = ENDFILE_CHAR;
	}
	else {
		charType = BAD_CHAR;
	}
	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];// THIS IS WHERE I'M GETTING A BAD CHAR.
	mCurrentState = mLegalMoves[mCurrentState][charType]; // SOMETHING IS MAPPING MCURRENTSTATE TO OHALFWAY_STATE HERE...
	return mCurrentState;// THIS IS WHERE I'M GETTING A BAD CHAR. CAUSED BY THROWING AN OHALFWAY_STATE SOMEHOW
}