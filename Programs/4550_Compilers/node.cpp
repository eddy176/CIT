#include "node.h"
#include "Debug.h"

Node::Node() {
}

Node::~Node() {
}

StartNode::StartNode(ProgramNode * ProgNode) {
	mProgramNode = ProgNode;
}
StartNode::~StartNode() {
	delete mProgramNode;
	MSG("StartNode Deconstructor deleting");
}

void StartNode::Interpret() {
	mProgramNode->Interpret();
}

void StartNode::Code(InstructionsClass & code) {
	mProgramNode->Code(code);
}


ProgramNode::ProgramNode(BlockNode * BlNode) {
	mBlockNode = BlNode;
}
ProgramNode::~ProgramNode() {
	delete mBlockNode;
	MSG("ProgramNode Deconstructor deleting");
}
void ProgramNode::Interpret() {
	mBlockNode->Interpret();
}

void ProgramNode::Code(InstructionsClass & code) {
	mBlockNode->Code(code);
}

BlockNode::BlockNode(StatementGroupNode * SGNode) {
	mStatementGroupNode = SGNode;
}
BlockNode::~BlockNode() {
	delete mStatementGroupNode;
	MSG("BlockNode Deconstructor deleting");
}

void BlockNode::Interpret() {
	mStatementGroupNode->Interpret();
}

void BlockNode::Code(InstructionsClass & code) {
	mStatementGroupNode->Code(code);
}

StatementGroupNode::StatementGroupNode() {
}

StatementGroupNode::StatementGroupNode(std::vector<StatementNode*> StateNode) {
	mVectofStatementNodes = StateNode;
}
StatementGroupNode::~StatementGroupNode() {
	for (size_t i = 0; i < mVectofStatementNodes.size(); i++) {
		delete mVectofStatementNodes[i];
		MSG("StatementGroupNodes Deconstructor deleting");
	}
}

void StatementGroupNode::AddStatement(StatementNode * SNode) {
	mVectofStatementNodes.push_back(SNode);
}

void StatementGroupNode::Interpret() {
	for(size_t i = 0; i < mVectofStatementNodes.size(); i++) {
		mVectofStatementNodes[i]->Interpret();
	}
}

void StatementGroupNode::Code(InstructionsClass & code) {
	for (size_t i = 0; i < mVectofStatementNodes.size(); i++) {
		mVectofStatementNodes[i]->Code(code);
	}
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode * IdNode, ExpressionNode * ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
	MSG("DeclarationStatementNode Deconstructor deleting");
};

// <DeclarationStatement> -> INT <Identifier> SEMICOLON
void DeclarationStatementNode::Interpret() {
	mIdentifierNode->DeclareVariable();
	if (mExpressionNode) {
	int val = mExpressionNode->Evaluate();
		mIdentifierNode->SetValue(val);
	}
}

void DeclarationStatementNode::Code(InstructionsClass & code) {
	mIdentifierNode->DeclareVariable();
	if (mExpressionNode) {
		mExpressionNode->CodeEvaluate(code);
		code.PopAndStore(mIdentifierNode->GetIndex());
	}
}


AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("AssignmentStatementNode Deconstructor deleting");
};

void AssignmentStatementNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(val);
}

void AssignmentStatementNode::Code(InstructionsClass & code) {
	mExpressionNode->CodeEvaluate(code);
	code.PopAndStore(mIdentifierNode->GetIndex());
}

PlusequalStatementNode::PlusequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
PlusequalStatementNode::~PlusequalStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("AssignmentStatementNode Deconstructor deleting");
};

void PlusequalStatementNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	int total = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(total + val);
}


void PlusequalStatementNode::Code(InstructionsClass & code) {
	GetIDNode()->CodeEvaluate(code);
	GetEXNode()->CodeEvaluate(code);
	code.PopPopAddPush();
	code.PopAndStore(mIdentifierNode->GetIndex());
}

MinusequalStatementNode::MinusequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
MinusequalStatementNode::~MinusequalStatementNode() {
	delete mIdentifierNode;
delete mExpressionNode;
MSG("AssignmentStatementNode Deconstructor deleting");
};

void MinusequalStatementNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	int total = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(total - val);
}

void MinusequalStatementNode::Code(InstructionsClass & code) {
	GetIDNode()->CodeEvaluate(code);
	GetEXNode()->CodeEvaluate(code);
	code.PopPopSubPush();
	code.PopAndStore(mIdentifierNode->GetIndex());
}

TimesequalStatementNode::TimesequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
TimesequalStatementNode::~TimesequalStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("AssignmentStatementNode Deconstructor deleting");
};

void TimesequalStatementNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	int total = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(total * val);
}


void TimesequalStatementNode::Code(InstructionsClass & code) {
	GetIDNode()->CodeEvaluate(code);
	GetEXNode()->CodeEvaluate(code);
	code.PopPopMulPush();
	code.PopAndStore(mIdentifierNode->GetIndex());
}

DivideequalStatementNode::DivideequalStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
DivideequalStatementNode::~DivideequalStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("AssignmentStatementNode Deconstructor deleting");
};

void DivideequalStatementNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	int total = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(total / val);
}


void DivideequalStatementNode::Code(InstructionsClass & code) {
	GetIDNode()->CodeEvaluate(code);
	GetEXNode()->CodeEvaluate(code);
	code.PopPopDivPush();
	code.PopAndStore(mIdentifierNode->GetIndex());
}


ShiftStatementNode::ShiftStatementNode(IdentifierNode* IdNode, ExpressionNode* ExpNode) {
	mIdentifierNode = IdNode;
	mExpressionNode = ExpNode;
};
ShiftStatementNode::~ShiftStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("AssignmentStatementNode Deconstructor deleting");
};

void ShiftStatementNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	int total = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(total >> val);
}// DONE?


void ShiftStatementNode::Code(InstructionsClass & code) {
	GetIDNode()->CodeEvaluate(code);
	GetEXNode()->CodeEvaluate(code);
	code.PopPopAddPush();
	code.PopAndStore(mIdentifierNode->GetIndex());
}




CoutStatementNode::CoutStatementNode() {
}

CoutStatementNode::CoutStatementNode(ExpressionNode* ExpNodes) {
	this->mExpressionNodes.push_back(ExpNodes);
}

CoutStatementNode::~CoutStatementNode() {
	for (size_t i = 0; i < mExpressionNodes.size(); i++) {
		delete mExpressionNodes[i];
	}
	MSG("CoutStatementNode Deconstructor deleting");
}

void CoutStatementNode::AddItem(ExpressionNode * Expnode) {
	mExpressionNodes.push_back(Expnode);
}

void CoutStatementNode::Interpret() {
	for (size_t i = 0; i < mExpressionNodes.size(); i++) {
		if (mExpressionNodes[i]) {
			std::cout << mExpressionNodes[i]->Evaluate();// if else with endl
		}
		else {
			std::cout << std::endl;
		}
	}
}

void CoutStatementNode::Code(InstructionsClass & code) {
	for (size_t i = 0; i < mExpressionNodes.size(); i++) {
		if (mExpressionNodes[i]) {
			mExpressionNodes[i]->CodeEvaluate(code);
			code.PopAndWrite();
		}
		else {
			code.WriteEndl();
		}
	}
}

IfStatementNode::IfStatementNode(ExpressionNode * Exp, StatementNode * Stat, StatementNode * Stat2) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
	mStatementNode2 = Stat2;
}
IfStatementNode::~IfStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	delete mStatementNode2;
	MSG("IfStatementNode Deconstructor deleting");
}

void IfStatementNode::Interpret() {
	int x = mExpressionNode->Evaluate();
	if (mExpressionNode->Evaluate()) {
		mStatementNode->Interpret();
	}
	else {
		if (mStatementNode2) {
			mStatementNode2->Interpret();
		}
	}
}

void IfStatementNode::Code(InstructionsClass & code) {

	//mExpressionNode->CodeEvaluate(code);
	//unsigned char * JumpAddress = code.SkipIfZeroStack();// skips if false
	//unsigned char * a1 = code.GetAddress();// note beginning of jump
	//mStatementNode->Code(code);
	//unsigned char * a2 = code.GetAddress();
	//unsigned char sizeofcode = a2 - a1;// node end of jump
	//code.SetOffset(JumpAddress, sizeofcode);
	//if (mStatementNode2 != NULL && mExpressionNode->Evaluate() == 0) {
	//	mStatementNode2->Code(code);
	//	unsigned char * a4 = code.GetAddress();
	//	unsigned char sizeofcode2 = a4 - a2;
	//	code.SetOffset(JumpAddress, sizeofcode2);
	//}

	mExpressionNode->CodeEvaluate(code);
	unsigned char * JumpAddress = code.SkipIfZeroStack();// skips if false
	unsigned char * a1 = code.GetAddress();// note beginning of jump
	mStatementNode->Code(code);
	unsigned char * JumpAddress2 = code.Jump();// skips if false


	unsigned char * a3;
	unsigned char * a2 = code.GetAddress();// node end of jump
	mStatementNode2->Code(code);
	a3 = code.GetAddress();
	code.SetOffset(JumpAddress, (int)(a2 - a1));
	code.SetOffset(JumpAddress2, (int)(a3 - a2));
}

WhileStatementNode::WhileStatementNode(ExpressionNode * Exp, StatementNode * Stat) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
}
WhileStatementNode::~WhileStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	MSG("WhileStatementNode Deconstructor deleting");
}

void WhileStatementNode::Interpret() {
	while (mExpressionNode->Evaluate()) {
		mStatementNode->Interpret();
	}
}

void WhileStatementNode::Code(InstructionsClass & code) {
		unsigned char * a0 = code.GetAddress();// note beginning of jump
		mExpressionNode->CodeEvaluate(code);
		unsigned char * JumpAddress = code.SkipIfZeroStack();// skips if false
		unsigned char * a1 = code.GetAddress();// note beginning of jump
		mStatementNode->Code(code);
		unsigned char * JumpAddress2 = code.Jump();
		unsigned char * a2 = code.GetAddress();// node end of jump
		code.SetOffset(JumpAddress, (int)(a2 - a1));
		code.SetOffset(JumpAddress2, (int)(a0 - a2));
}

DoWhileStatementNode::DoWhileStatementNode(ExpressionNode * Exp, StatementNode * Stat) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
}
DoWhileStatementNode::~DoWhileStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	MSG("DoWhileStatementNode Deconstructor deleting");
}

void DoWhileStatementNode::Interpret() {
	do {
		mStatementNode->Interpret();
	} while (mExpressionNode->Evaluate()); 
}

void DoWhileStatementNode::Code(InstructionsClass & code) {
	mStatementNode->Code(code);
	unsigned char * a1 = code.GetAddress();// note beginning of jump
	mExpressionNode->CodeEvaluate(code);
	unsigned char * JumpAddress = code.SkipIfZeroStack();// skips if false
	unsigned char * a2 = code.GetAddress();// node end of jump
	mStatementNode->Code(code);
	unsigned char * JumpAddress2 = code.Jump();
	unsigned char * a0 = code.GetAddress();// note beginning of jump
	code.SetOffset(JumpAddress, (int)(a0 - a2));
	code.SetOffset(JumpAddress2, (int)(a1 - a0));
}


RepeatStatementNode::RepeatStatementNode(ExpressionNode * Exp, StatementNode * Stat) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
}
RepeatStatementNode::~RepeatStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	MSG("RepeatStatementNode Deconstructor deleting");
}

void RepeatStatementNode::Interpret() {
	int total = mExpressionNode->Evaluate();
	for (int i = 0; i < total; i++) {
		mStatementNode->Interpret();
	}
}

void RepeatStatementNode::Code(InstructionsClass & code) {
	mExpressionNode->CodeEvaluate(code);
	unsigned char * addy0 = code.GetAddress();
	code.PopPushPush();
	unsigned char * jumpaddy1 = code.SkipIfZeroStack();
	unsigned char * addy1 = code.GetAddress();
	code.PushValue(1);
	code.PopPopSubPush();
	mStatementNode->Code(code);
	unsigned char * jumpaddy2 = code.Jump();
	unsigned char * address2 = code.GetAddress();
	code.SetOffset(jumpaddy2, (addy0 - address2));
	code.SetOffset(jumpaddy1, (address2 - addy1));
	code.Pop();
}


// End StatementNodes


// Begin ExpressionNodes

IfNode::IfNode(ExpressionNode * Exp, StatementNode * Stat) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
}
IfNode::~IfNode() {
	MSG("IfNode Deconstructor deleting")
}

int IfNode::Evaluate() {
	return mExpressionNode->Evaluate();
}

void IfNode::CodeEvaluate(InstructionsClass & code) {
	mExpressionNode->CodeEvaluate(code);
}

WhileNode::WhileNode(ExpressionNode * Exp, StatementNode * Stat) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
}
WhileNode::~WhileNode() {
	MSG("WhileNode Deconstructor deleting")
}

int WhileNode::Evaluate() {
	return mExpressionNode->Evaluate();
}

void WhileNode::CodeEvaluate(InstructionsClass & code) {
	mExpressionNode->CodeEvaluate(code);
}

RepeatNode::RepeatNode(ExpressionNode * Exp, StatementNode * Stat) {
	mExpressionNode = Exp;
	mStatementNode = Stat;
}
RepeatNode::~RepeatNode() {
	MSG("RepeatNode Deconstructor deleting")
}

int RepeatNode::Evaluate() {
	return mExpressionNode->Evaluate();
}

void RepeatNode::CodeEvaluate(InstructionsClass & code) {
	mExpressionNode->CodeEvaluate(code);
}

ExpressionNode::ExpressionNode() {

}
ExpressionNode::~ExpressionNode() {
	MSG("ExpressionNode Deconstructor deleting");
}

IntegerNode::IntegerNode(int Expression) {
	mIntegerNode = Expression;
}

int IntegerNode::Evaluate() {
	return mIntegerNode;
}

void IntegerNode::CodeEvaluate(InstructionsClass & code) {
	code.PushValue(mIntegerNode);
}


IdentifierNode::IdentifierNode(std::string Label, SymbolTableClass * SymbolTable) {
	mLabel = Label;
	mSymbolTable = SymbolTable;
}

void IdentifierNode::DeclareVariable() {
	mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) { 
	mSymbolTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex() {
	return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
	return mSymbolTable->GetValue(mLabel);
}

std::string IdentifierNode::GetLabel() {
	return mLabel;
}

void IdentifierNode::CodeEvaluate(InstructionsClass & code) {
	code.PushVariable(GetIndex());
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * LeftExpNode, ExpressionNode * RightExpNode) {
	mLeftExpressionNode = LeftExpNode;
	mRightExpressionNode = RightExpNode;
}
BinaryOperatorNode::~BinaryOperatorNode() {
	delete mLeftExpressionNode;
	delete mRightExpressionNode;
	MSG("BinaryOperatorNode Deconstructor deleting");
}

PlusNode::PlusNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int PlusNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() + mRightExpressionNode->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int MinusNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() -  mRightExpressionNode->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopSubPush();
}


TimesNode::TimesNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int TimesNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() * mRightExpressionNode->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

ShiftNode::ShiftNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int ShiftNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() >> mRightExpressionNode->Evaluate();
}

void ShiftNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopShiftPush();
}



int DivideNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() / mRightExpressionNode->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopDivPush();
}

//ExponentNode::ExponentNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
//	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
//}
//
//int ExponentNode::Evaluate() {
//	int total = 1;
//	int right = mRightExpressionNode->Evaluate();
//	int left = mLeftExpressionNode->Evaluate();
//	for (int i = 0; i < right; i++) {
//		total *= left;
//	}
//	return total;
//}

//void ExponentNode::CodeEvaluate(InstructionsClass & code) {
//	std::cout << "not implemented" << std::endl;
//	mLeftExpressionNode->CodeEvaluate(code);
//	mRightExpressionNode->CodeEvaluate(code);
//	// set i to 1
//	// push i
//	// pop pop mul
//	// set ONE
//	// i--
//	// cmp
//	// if 1 jump past
//	// 
//}

ModNode::ModNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int ModNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() % mRightExpressionNode->Evaluate();
}

void ModNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopModPush();
}

LessNode::LessNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int LessNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() < mRightExpressionNode->Evaluate();
}

void LessNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopLessPush();
}


LessEqualNode::LessEqualNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int LessEqualNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() <= mRightExpressionNode->Evaluate();
}

void LessEqualNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopLessEqualPush();
}


GreaterNode::GreaterNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int GreaterNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() > mRightExpressionNode->Evaluate();
}

void GreaterNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopGreaterPush();
}


GreaterEqualNode::GreaterEqualNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int GreaterEqualNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() >= mRightExpressionNode->Evaluate();
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopGreaterEqualPush();
}


EqualNode::EqualNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int EqualNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() == mRightExpressionNode->Evaluate();
}

void EqualNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopEqualPush();
}


NotEqualNode::NotEqualNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int NotEqualNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() != mRightExpressionNode->Evaluate();
}

void NotEqualNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopNotEqualPush();
}


AndNode::AndNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int AndNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() && mRightExpressionNode->Evaluate();
}

void AndNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopAndPush();
}


OrNode::OrNode(ExpressionNode * mLeftExpressionNode, ExpressionNode * mRightExpressionNode)
	: BinaryOperatorNode(mLeftExpressionNode, mRightExpressionNode) {
}

int OrNode::Evaluate() {
	return mLeftExpressionNode->Evaluate() || mRightExpressionNode->Evaluate();
}

void OrNode::CodeEvaluate(InstructionsClass & code) {
	mLeftExpressionNode->CodeEvaluate(code);
	mRightExpressionNode->CodeEvaluate(code);
	code.PopPopOrPush();
}