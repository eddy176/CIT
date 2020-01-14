#include <algorithm>
#include "Symbol.h"
#include "Debug.h"

using namespace std;

SymbolTableClass::SymbolTableClass() {
}


bool SymbolTableClass::Exists(const std::string & s) {
	for (size_t i = 0; i < vect_of_variables.size(); i++) {
		if (s == vect_of_variables[i].mLabel) {
			MSG(s.c_str() << " already in the table.");
			return true;
		}
	}
	return false;
}

void SymbolTableClass::AddEntry(const std::string & s) {
	if (Exists(s)) {
		return;
	}
	Variable variable;
	variable.mLabel = s;
	variable.mValue = -1;
	vect_of_variables.push_back(variable);
}
int SymbolTableClass::GetValue(const std::string & s) {
	for (size_t i = 0; i < vect_of_variables.size(); i++) {
		if (vect_of_variables[i].mLabel == s) {
			return vect_of_variables[i].mValue;
		}
	}
	MSG("No value for:" << s.c_str());
	return -1;
}
void SymbolTableClass::SetValue(const std::string & s, int v) {
	bool isstuff = false;
	for (size_t i = 0; i < vect_of_variables.size(); i++) {
		if (vect_of_variables[i].mLabel == s) {
			vect_of_variables[i].mValue = v;
			isstuff = true;
		}
	}
	if (!isstuff) {
		MSG("Couldn't set value:" << s.c_str());
	}
}

int SymbolTableClass::GetIndex(const std::string & s) {
	std::vector<Variable>::iterator it;
	it = find_if(
		vect_of_variables.begin(), vect_of_variables.end(),
		[s](const Variable& i) {
		return i.mLabel == s;
		}
	);
	if (it != vect_of_variables.end()) {
		auto index = distance(vect_of_variables.begin(), it);
		return index;
	}
	else {
		auto index = distance(vect_of_variables.begin(), it);
		return index;
	}
}

int SymbolTableClass::GetCount() {
	return vect_of_variables.size();
}

void SymbolTableClass::CoutVariables() {
	for (size_t i = 0; i < vect_of_variables.size(); i++) {
		cout << vect_of_variables[i].mLabel.c_str() << " " << vect_of_variables[i].mValue << endl;
	}
}

