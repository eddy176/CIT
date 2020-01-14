#include "Parser.h"
#include "Token.h"
#include "StateMachine.h"
#include "node.h"
#include "Debug.h"


ParserClass::ParserClass(ScannerClass * scanner, SymbolTableClass * symbol){
	mScanner = scanner;
	mSymbol = symbol;
}

// returns a token that matches the token type matched
TokenClass ParserClass::Match(TokenType expectedType) {
	TokenClass currentToken = mScanner->GetNextToken();
	if (currentToken.GetTokenType() != expectedType) {
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Expected token type is " << TokenClass::GetTokenTypeName(expectedType) <<
			", but current token type is " << currentToken.GetTokenTypeName() << "." << std::endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() <<
		". Lexeme: \"" << currentToken.GetLexeme() << "\"");
	return currentToken;
}


StartNode * ParserClass::Start() {
	ProgramNode * pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode * sn = new StartNode(pn);
	return sn;
}

ProgramNode * ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LEFTPAREN_TOKEN);
	Match(RIGHTPAREN_TOKEN);
	BlockNode * bn = Block();
	return new ProgramNode(bn);

}

BlockNode * ParserClass::Block() {
	Match(LEFTBRACKET_TOKEN);
	StatementGroupNode * sg = StatementGroup();
	Match(RIGHTBRACKET_TOKEN);
	return new BlockNode(sg); // statement group
}

StatementGroupNode * ParserClass::StatementGroup() {
	StatementGroupNode * sgn = new StatementGroupNode();
	StatementNode * sn;
	do{
		sn = Statement();
		if (sn) {
			sgn->AddStatement(sn);
		}
	} while (sn);
	return sgn;
}

StatementNode * ParserClass::Statement() {
	TokenClass T = mScanner->PeekNextToken();
	TokenType TT = T.GetTokenType();
	if (TT == INT_TOKEN) {
		return DeclarationStatement();
	}
	else if (TT == IDENTIFIER_TOKEN) {
		return AssignmentStatement();
	}
	else if (TT == COUT_TOKEN) {
		return CoutStatement();
	}
	else if (TT == LEFTBRACKET_TOKEN) {
		return Block();
	}
	else if (TT == IF_TOKEN) {
		return IfStatement();
	}
	else if (TT == WHILE_TOKEN) {
		return WhileStatement();
	}
	else if (TT == DO_TOKEN) {
		return DoWhileStatement();
	}
	else if (TT == REPEAT_TOKEN) {
		return RepeatStatement();
	}
	else {
		return NULL;
	}
}

IfStatementNode * ParserClass::IfStatement() {
	Match(IF_TOKEN);
	Match(LEFTPAREN_TOKEN);
	ExpressionNode* EN = Expression();
	Match(RIGHTPAREN_TOKEN);
	StatementNode * SNone = Statement();
	StatementNode * SNtwo = NULL;
	TokenType TT = mScanner->PeekNextToken().GetTokenType();
	if (TT == ELSE_TOKEN) {
		Match(ELSE_TOKEN);
		SNtwo = Statement();
	}
	return new IfStatementNode(EN, SNone, SNtwo);
}

WhileStatementNode * ParserClass::WhileStatement() {
	Match(WHILE_TOKEN);
	Match(LEFTPAREN_TOKEN);
	ExpressionNode* EN = Expression();
	Match(RIGHTPAREN_TOKEN);
	StatementNode * SN = Statement();
	return new WhileStatementNode(EN, SN);
}

DoWhileStatementNode * ParserClass::DoWhileStatement() {
	Match(DO_TOKEN);
	StatementNode * statementNode = Statement();
	Match(WHILE_TOKEN);
	Match(LEFTPAREN_TOKEN);
	ExpressionNode * expressionNode = Expression();
	Match(RIGHTPAREN_TOKEN);
	Match(SEMICOLON_TOKEN);
	return new DoWhileStatementNode(expressionNode, statementNode);
}


RepeatStatementNode * ParserClass::RepeatStatement() {
	Match(REPEAT_TOKEN);
	ExpressionNode* EN = Expression();
	StatementNode * SN = Statement();
	return new RepeatStatementNode(EN, SN);
}

ExpressionNode * ParserClass::Or() {
	ExpressionNode * current = And();
	while (true) {// could have many plus minus tails together, catch them all at once
		TokenType TT = mScanner->PeekNextToken().GetTokenType();// if it's a plus token, match it and call the method below us
		if (TT == OR_TOKEN) {
			Match(OR_TOKEN);
			current = new OrNode(current, And());
		}
		else {
			return current;
		}
	}
	return current;
}

ExpressionNode * ParserClass::And() {
	ExpressionNode * current = Relational();
	while (true) {// could have many plus minus tails together, catch them all at once
		TokenType TT = mScanner->PeekNextToken().GetTokenType();// if it's a plus token, match it and call the method below us
		if (TT == AND_TOKEN) {
			Match(AND_TOKEN);
			current = new AndNode(current, Relational());
		}
		else {
			return current;
		}
	}
	return current;
}

ExpressionNode* ParserClass::Relational() {
	ExpressionNode * current = Shift();// calls the method below it

	TokenType TT = mScanner->PeekNextToken().GetTokenType(); // handle the optional tail
	// the below if/else chain represents the above grammer
	if (TT == LESS_TOKEN) {
		Match(LESS_TOKEN);
		return new LessNode(current, PlusMinus());// put current current here?
	}
	else if (TT == LESSEQUAL_TOKEN) {
		Match(LESSEQUAL_TOKEN);
		return new LessEqualNode(current, PlusMinus());// put current current here?
	}
	else if (TT == GREATER_TOKEN) {
		Match(GREATER_TOKEN);
		return new GreaterNode(current, PlusMinus());// put current current here?
	}
	else if (TT == GREATEREQUAL_TOKEN) {
		Match(GREATEREQUAL_TOKEN);
		return new GreaterEqualNode(current, PlusMinus());// put current current here?
	}
	else if (TT == EQUAL_TOKEN) {
		Match(EQUAL_TOKEN);
		return new EqualNode(current, PlusMinus());// put current current here?
	}
	else if (TT == NOTEQUAL_TOKEN) {
		Match(NOTEQUAL_TOKEN);
		return new NotEqualNode(current, PlusMinus());// put current current here?
	}
	return current;
}


ExpressionNode * ParserClass::Shift() {
	ExpressionNode * current = PlusMinus();
		TokenType TT = mScanner->PeekNextToken().GetTokenType();// if it's a plus token, match it and call the method below us
		if (TT == SHIFT_TOKEN) {
			Match(SHIFT_TOKEN);
			current = new ShiftNode(current, PlusMinus());
		}
		else {
			return current;
		}
	return current;

}


ExpressionNode * ParserClass::PlusMinus() {
	ExpressionNode * current = TimesDivide();
	while (true) {
		TokenType TT = mScanner->PeekNextToken().GetTokenType();// if it's a plus token, match it and call the method below us
		if (TT == PLUS_TOKEN) {
			Match(PLUS_TOKEN);
			current = new PlusNode(current, TimesDivide());
		}
		else if (TT == MINUS_TOKEN) {
			Match(MINUS_TOKEN);
			current = new MinusNode(current, TimesDivide());
		}
		else {
			return current;
		}
	}
	return current;

}

ExpressionNode * ParserClass::TimesDivide() {
	ExpressionNode * current = Mod();
	while (true) {
		TokenType TT = mScanner->PeekNextToken().GetTokenType();
		if (TT == TIMES_TOKEN) {
			Match(TIMES_TOKEN);
			current = new TimesNode(current, Factor());
		}
		else if (TT == DIVIDE_TOKEN) {
			Match(DIVIDE_TOKEN);
			current = new DivideNode(current, Factor());
		}
		else {
			return current;
		}
	}
	return current;
}

ExpressionNode * ParserClass::Mod() {
	ExpressionNode * current = Factor();
	while (true) {
		TokenType TT = mScanner->PeekNextToken().GetTokenType();
		/*if (TT == EXPONENT_TOKEN) {
			Match(EXPONENT_TOKEN);
			current = new ExponentNode(current, Factor());
		}*/
		if (TT == MOD_TOKEN) {
			Match(MOD_TOKEN);
			current = new ModNode(current, Factor());
		}
		else {
			return current;
		}
	}
	return current;
}

ExpressionNode * ParserClass::Factor() {
	TokenType TT = mScanner->PeekNextToken().GetTokenType();
	if (TT == IDENTIFIER_TOKEN) {
		return Identifier();
	}
	else if (TT == INTEGER_TOKEN) {
		return Integer(); // calls match on the integer token type
	}
	else if (TT == LEFTPAREN_TOKEN) {
		Match(LEFTPAREN_TOKEN);
		ExpressionNode* exp = Expression();
		Match(RIGHTPAREN_TOKEN);
		return exp;
	}
	else {
		cerr << "Error in factor" << std::endl;
		exit(1);
	}
}

ExpressionNode* ParserClass::Expression() {
	return Or();
}

// int sum;
DeclarationStatementNode * ParserClass::DeclarationStatement() {
	Match(INT_TOKEN);
	IdentifierNode* IN = Identifier();
	TokenType TT = mScanner->PeekNextToken().GetTokenType();
	ExpressionNode* en = NULL;
	if (TT == SEMICOLON_TOKEN) {
		Match(SEMICOLON_TOKEN);
	}
	else {
		Match(ASSIGNMENT_TOKEN);
		en = Expression();
		Match(SEMICOLON_TOKEN);
	}
	return new DeclarationStatementNode(IN, en);
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {
	IdentifierNode* IN = Identifier();
	TokenType TT = mScanner->PeekNextToken().GetTokenType();
	
	if (TT == PLUSEQUAL_TOKEN) {
		 PlusequalStatement(IN);
	}
	else if (TT == MINUSEQUAL_TOKEN) {
		MinusequalStatement(IN);
	}
	else if (TT == TIMESEQUAL_TOKEN) {
		TimesequalStatement(IN);
	}
	else if (TT == DIVIDEEQUAL_TOKEN) {
		DivideequalStatement(IN);
	}
	else {
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		return new AssignmentStatementNode(IN, en);
	}
}

PlusequalStatementNode * ParserClass::PlusequalStatement(IdentifierNode * IN) {
	Match(PLUSEQUAL_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	return new PlusequalStatementNode(IN, en);
}

MinusequalStatementNode * ParserClass::MinusequalStatement(IdentifierNode * IN) {
	Match(MINUSEQUAL_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	return new MinusequalStatementNode(IN, en);
}


TimesequalStatementNode * ParserClass::TimesequalStatement(IdentifierNode * IN) {
	Match(TIMESEQUAL_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	return new TimesequalStatementNode(IN, en);
}

DivideequalStatementNode * ParserClass::DivideequalStatement(IdentifierNode * IN) {
	Match(DIVIDEEQUAL_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	return new DivideequalStatementNode(IN, en);
}

CoutStatementNode * ParserClass::CoutStatement() {
	Match(COUT_TOKEN);
	CoutStatementNode * c = new CoutStatementNode();
	TokenType TT = INSERTION_TOKEN;
	while (TT != SEMICOLON_TOKEN) {
		Match(INSERTION_TOKEN);
		TT = mScanner->PeekNextToken().GetTokenType();
		if (TT == ENDL_TOKEN) {
			Match(ENDL_TOKEN);
			c->AddItem(NULL);
		}
		else {
			c->AddItem(Expression());
		}
		TT = mScanner->PeekNextToken().GetTokenType();
	}
	Match(SEMICOLON_TOKEN);
	return c;
}

IdentifierNode * ParserClass::Identifier() {
	TokenClass TC = Match(IDENTIFIER_TOKEN);
	return new IdentifierNode(TC.GetLexeme(), mSymbol);
}

IntegerNode * ParserClass::Integer() {
	TokenClass TC = Match(INTEGER_TOKEN);
	return new IntegerNode(atoi(TC.GetLexeme().c_str())); 
	// atoi converts a string to an int, c_str() turns strings into chars
}