#pragma once

#include <cstdlib>
#include <vector>
#include "Symbol.h"
#include "Token.h"
#include "instructions.h"

// forward declarations:
class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class IdentifierNode;
class DeclarationStatementNode;
class CoutStatementNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;

class AssignmentStatementNode;
class ExpressionNode;
class IfStatementNode;
class WhileStatementNode;
class DoWhileStatementNode;
class IfNode;
class WhileNode;
class DoWhileNode;
//class ExponentNode;
//class Exponent;

class ShiftStatementNode;

class PlusequalStatmentNode;
class MinusequalStatementNode;
class TimesequalStatementNode;
class DivideequalStatementNode;

class Node {
public:
	Node();
	virtual ~Node();
	virtual void Interpret() = 0;
	virtual void Code(InstructionsClass & Code) = 0;
};

class StartNode : public Node {
public:
	StartNode(ProgramNode* ProgNode);
	virtual ~StartNode();// should call delete on the pointer
	virtual void Interpret();
	void Code(InstructionsClass & Code);
protected:
	ProgramNode* mProgramNode;
};

class StatementNode : public Node {
};

class ProgramNode : public StatementNode {
public:
	ProgramNode(BlockNode* BlNode);
	virtual ~ProgramNode(); // calls delete on the blocknode pointer
	virtual void Interpret();
	void Code(InstructionsClass & Code);

protected:
	BlockNode* mBlockNode;
};

class BlockNode : public StatementNode{
public:
	BlockNode(StatementGroupNode* SGNode);
	virtual ~BlockNode(); // calls delete on the statementgroupnode pointer
	virtual void Interpret();
	void Code(InstructionsClass & Code);
protected:
	StatementGroupNode * mStatementGroupNode;
};

class StatementGroupNode : public Node {
public:
	StatementGroupNode();
	StatementGroupNode(std::vector<StatementNode*> StateNode);
	void AddStatement(StatementNode* SNode);
	virtual ~StatementGroupNode(); // runs a for loop to delete the vector of 
	virtual void Interpret();
	void Code(InstructionsClass & Code);
	// statementnode pointers, the vector itself is automatically deleted.
protected:
	std::vector<StatementNode*> mVectofStatementNodes;
};

class DeclarationStatementNode : public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~DeclarationStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & code);
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class AssignmentStatementNode : public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~AssignmentStatementNode();
	virtual void Interpret();
	IdentifierNode * GetIDNode() { return mIdentifierNode; };
	ExpressionNode * GetEXNode() { return mExpressionNode; };
	void Code(InstructionsClass & code);
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class PlusequalStatementNode : public StatementNode {
public:
	PlusequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~PlusequalStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & Code);
	IdentifierNode * GetIDNode() { return mIdentifierNode; };
	ExpressionNode * GetEXNode() { return mExpressionNode; };
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class MinusequalStatementNode : public StatementNode {
public:
	MinusequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~MinusequalStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & code);
	IdentifierNode * GetIDNode() { return mIdentifierNode; };
	ExpressionNode * GetEXNode() { return mExpressionNode; };
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class TimesequalStatementNode : public StatementNode {
public:
	TimesequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~TimesequalStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & Code);
	IdentifierNode * GetIDNode() { return mIdentifierNode; };
	ExpressionNode * GetEXNode() { return mExpressionNode; };
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class DivideequalStatementNode : public StatementNode {
public:
	DivideequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~DivideequalStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & Code);
	IdentifierNode * GetIDNode() { return mIdentifierNode; };
	ExpressionNode * GetEXNode() { return mExpressionNode; };
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class ShiftStatementNode : public StatementNode {
public:
	ShiftStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode);
	virtual ~ShiftStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & Code);
	IdentifierNode * GetIDNode() { return mIdentifierNode; };
	ExpressionNode * GetEXNode() { return mExpressionNode; };
protected:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};


class CoutStatementNode : public StatementNode {
public:
	CoutStatementNode();
	CoutStatementNode(ExpressionNode* ExpNodes);
	virtual ~CoutStatementNode();
	void AddItem(ExpressionNode * Expnode);
	virtual void Interpret();
	void Code(InstructionsClass & code);
protected:
	std::vector<ExpressionNode*> mExpressionNodes;
};

class IfStatementNode : public StatementNode {
public:
	IfStatementNode(ExpressionNode * ENode, StatementNode* SNode1, StatementNode* SNode2);
	virtual ~IfStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & code);
protected:
	ExpressionNode* mExpressionNode;
	StatementNode* mStatementNode;
	StatementNode* mStatementNode2;
};

class WhileStatementNode : public StatementNode {
public:
	WhileStatementNode(ExpressionNode * ENode, StatementNode* SNode);
	virtual ~WhileStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & code);
protected:
	ExpressionNode * mExpressionNode;
	StatementNode* mStatementNode;
};

class DoWhileStatementNode : public StatementNode {
public:
	DoWhileStatementNode(ExpressionNode * ENode, StatementNode* SNode);
	virtual ~DoWhileStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & code);
protected:
	ExpressionNode * mExpressionNode;
	StatementNode* mStatementNode;
};

class RepeatStatementNode : public StatementNode {
public:
	RepeatStatementNode(ExpressionNode * ENode, StatementNode* SNode);
	virtual ~RepeatStatementNode();
	virtual void Interpret();
	void Code(InstructionsClass & Code);

protected:
	ExpressionNode * mExpressionNode;
	StatementNode* mStatementNode;
};

// End StatementNodes

///////////////////////////////////////////

// Begin ExpressionNodes

class ExpressionNode {	// does not derive from node in any way
public:
	ExpressionNode();
	virtual ~ExpressionNode();
	virtual int Evaluate() = 0;
	virtual void CodeEvaluate(InstructionsClass & code) = 0;
};

class IfNode : public ExpressionNode {
public:
	IfNode(ExpressionNode * exp, StatementNode * Stat);
	virtual ~IfNode();
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

protected:
	ExpressionNode * mExpressionNode;
	StatementNode * mStatementNode;
};

class WhileNode : public ExpressionNode {
public:
	WhileNode(ExpressionNode * exp, StatementNode * Stat);
	virtual ~WhileNode();
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

protected:
	ExpressionNode * mExpressionNode;
	StatementNode * mStatementNode;
};

class DoWhileNode : public ExpressionNode {
public:
	DoWhileNode(ExpressionNode * exp, StatementNode * Stat);
	virtual ~DoWhileNode();
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

protected:
	ExpressionNode * mExpressionNode;
	StatementNode * mStatementNode;
};

class RepeatNode : public ExpressionNode {
public:
	RepeatNode(ExpressionNode * exp, StatementNode * Stat);
	virtual ~RepeatNode();
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

protected:
	ExpressionNode * mExpressionNode;
	StatementNode * mStatementNode;
};

class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int Expression); // no destructor needed
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);
protected:
	int mIntegerNode;
};

class IdentifierNode : public ExpressionNode {
public:
	IdentifierNode(std::string Label, SymbolTableClass* SymbolTable);
	void DeclareVariable(); // adds idnode's label to symbol table
	void SetValue(int v);
	int GetIndex(); // returns the int position of where var is stored in symbol table
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

	std::string GetLabel();
protected:
	std::string mLabel;
	SymbolTableClass* mSymbolTable;
};

class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode* LeftExpNode, ExpressionNode* RightExpNode);
	~BinaryOperatorNode(); // calls delete on both pointers
	virtual int Evaluate() = 0;
	void CodeEvaluate(InstructionsClass & code) = 0;
protected:
	ExpressionNode* mLeftExpressionNode;
	ExpressionNode* mRightExpressionNode;
};

/////////////////////////////

// Begin BinaryOperatorNodes

class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);
};

class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);
};

class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class ShiftNode : public BinaryOperatorNode {
public:
	ShiftNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

//class ExponentNode : public BinaryOperatorNode {
//public:
//	ExponentNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
//	virtual int Evaluate();
//	void CodeEvaluate(InstructionsClass & code);
//};

class ModNode : public BinaryOperatorNode {
public:
	ModNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class AndNode : public BinaryOperatorNode {
public:
	AndNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);

};

class OrNode : public BinaryOperatorNode {
public:
	OrNode(ExpressionNode* mLeftExpressionNode, ExpressionNode* mRightExpressionNode);
	virtual int Evaluate();
	void CodeEvaluate(InstructionsClass & code);
};
