// My main file for token.h/cpp
// first compiler code assignment

//#include "Token.h"
//#include "StateMachine.h"
//#include "Scanner.h"
//#include "Symbol.h"
//#include "node.h"


#include "Parser.h"
#include "instructions.h"

//int main() {
	// test for scanner
	/*ScannerClass Scanner("code.txt");
	TokenClass T;
	int lnum;
	do {
		T = Scanner.GetNextToken();
		lnum = Scanner.GetLineNumber();
		std::cout << '\t' << lnum << '\t' << T  << endl;
	} while (T.GetTokenType() != ENDFILE_TOKEN);


	return 0;*/
	// end test for scanner

	// test for symbol table
	/*const std::string dummy = "test";
	SymbolTableClass symboltable;
	if (symboltable.Exists(dummy)) {
		std::cout << "this shouldn't print, dummy isn't in table yet." << std::endl;
	}
	symboltable.AddEntry(dummy);
	if (!symboltable.Exists(dummy)) {
		std::cout << "this shouldn't print, dummy is in table." << std::endl;
	}
	std::cout << "1: Beuler should not be in the table: ";
	symboltable.SetValue("Beuler", 23);
	symboltable.SetValue(dummy, 23);
	std::cout << "2: 1 == " << symboltable.GetCount() << std::endl;
	std::cout << "3: 23 == " << symboltable.GetValue(dummy) << std::endl;
	std::cout << "4: 0 == " << symboltable.GetIndex(dummy) << std::endl;
	std::cout << "5: dummy should already be in the table: ";
	symboltable.AddEntry(dummy);
	std::string second = "test2";
	symboltable.AddEntry(second);
	std::cout << "6: 2 == " << symboltable.GetCount() << std::endl;
	std::cout << "7: mValue doesn't have a meaningful value stored: " << symboltable.GetValue(second) << std::endl;*/
	// end test for symbol table


// symbol table, parser, and interpreter tests
int main() {
	SymbolTableClass symbol;
	ScannerClass scanner("code.cpp");// set filename to a text file of your choosing
	ParserClass Parser(&scanner, &symbol);
	StartNode * startsomething = Parser.Start();
	startsomething->Interpret();
	//delete startsomething;
	return 0;
}

//int main() {
//	SymbolTableClass symbol;
//	ScannerClass scanner("code.cpp");// set filename to a text file of your choosing
//	ParserClass Parser(&scanner, &symbol);
//	StartNode * sn = Parser.Start();
//	InstructionsClass ic = InstructionsClass();
//	sn->Code(ic);// comment for interpreting
//	ic.Finish();
//	ic.PrintAllMachineCodes();
//	ic.Execute();
//}



// how to test execution ///////////////////////////////////////////////
//#include <iostream>
//using namespace std;
//int main()
//{
//	unsigned char mCode[] = { 0x55, 0x8B, 0xEC, 0X5d, 0XC3 };
//	cout << "About to Execute the machine code...\n";
//	void * ptr = mCode;
//	void(*f)(void);
//	f = (void(*)(void)) ptr;
//	f(); // call the array as if it were a function
//	cout << "There and back again!\n\n";
//	return 0;
//}










/*IntegerNode* in = new IntegerNode(5);

CoutStatementNode* cs = new CoutStatementNode(in);
StatementGroupNode* sg = new StatementGroupNode();
sg->AddStatement(cs);

IdentifierNode* idn = new IdentifierNode("sum", &symbol);
DeclarationStatementNode* dc = new DeclarationStatementNode(idn);
sg->AddStatement(dc);

IntegerNode* in2 = new IntegerNode(6);
IdentifierNode* idn2 = new IdentifierNode("sum", &symbol);
AssignmentStatementNode* asn = new AssignmentStatementNode(idn2, in2);
sg->AddStatement(asn);

BlockNode* b = new BlockNode(sg);
ProgramNode* pn = new ProgramNode(b);
StartNode* sn = new StartNode(pn*);*/
//delete sn;	// calls delete on startnode, causing cascade of deletes down the tree

