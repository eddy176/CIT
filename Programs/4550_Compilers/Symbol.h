#pragma once

#include <cstdlib>
#include <vector>

class SymbolTableClass {
public:
	struct Variable {
		std::string mLabel;
		int mValue;
	};
	SymbolTableClass();

	bool Exists(const std::string & s);
	void AddEntry(const std::string & s);
	int GetValue(const std::string & s);
	void SetValue(const std::string & s, int v);
	int GetIndex(const std::string & s);
	int GetCount();
	void CoutVariables();

private:
	std::vector<Variable> vect_of_variables;
};
