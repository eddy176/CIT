#pragma once
#include "node.h"
#include "Scanner.h"

class ParserClass {
public:
	ParserClass(ScannerClass * scanner, SymbolTableClass * symbol);
	StartNode * Start();

	ExpressionNode* Expression();
	ProgramNode * Program();
	BlockNode * Block();
	StatementGroupNode * StatementGroup();
	DeclarationStatementNode * DeclarationStatement();
	AssignmentStatementNode * AssignmentStatement();
	CoutStatementNode * CoutStatement();
	StatementNode * Statement();
	IfStatementNode * IfStatement();
	WhileStatementNode * WhileStatement();

	RepeatStatementNode * RepeatStatement();
	DoWhileStatementNode * DoWhileStatement();

	ExpressionNode * Factor();
	ExpressionNode* Relational();
	ExpressionNode * PlusMinus();

	ExpressionNode * TimesDivide();

	ExpressionNode * Shift();

	IdentifierNode * Identifier();
	IntegerNode * Integer();
	ExpressionNode * Or();
	ExpressionNode * And();
	TokenClass Match(TokenType expectedType);
	ExpressionNode * Mod();
	PlusequalStatementNode * PlusequalStatement(IdentifierNode * IN);
	MinusequalStatementNode * MinusequalStatement(IdentifierNode * IN);
	TimesequalStatementNode * TimesequalStatement(IdentifierNode * IN);
	DivideequalStatementNode * DivideequalStatement(IdentifierNode * IN);

protected:
	ScannerClass * mScanner;
	SymbolTableClass * mSymbol;
};
	
