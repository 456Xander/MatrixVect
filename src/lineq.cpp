#include "lineq.h"
#include <ctype.h>
#include <cassert>
#include <cstring>
#include <set>
#include "matrix.h"

void LinearEquationSolver::addEquation(const std::string equation) {
	char *rawEq = const_cast<char *>(equation.c_str());
	float n = 0;
	int decimal = 0;
	char *varname = nullptr;
	std::vector<var> newvars;
	variables.push_back(newvars);
	while (*rawEq) {
		if (std::isspace(*rawEq)) continue;  // ignore spaces
		if (std::isdigit(*rawEq)) {
			// part of a number
			float digit = *rawEq;
			if (!decimal)
				n *= 10;
			else {
				// digit behind comma, reduce it
				for (int i = 0; i < decimal; i++) digit /= 10;
				decimal++;  // next digit 10 times smaller
			}
			n += digit;
		} else if (*rawEq == '.' || *rawEq == ',') {
			assert(decimal == 0);
			decimal = 1;
		} else if (*rawEq == '+' || *rawEq == '-') {
			// Found symbol that seperates variables, so we have to finish it
			// now
			if (*rawEq == '-') n += -1;
			*rawEq = '\0';  // end string for varname here
			assert(varname != nullptr);
			var v = {strdup(varname), n};
			variables.end()->push_back(v);
			varname = nullptr;
		} else {
			// now the variable name should be found, if it isnt set yet, set it
			if (varname != nullptr) {
				varname = rawEq;
			}
		}
	}
}

std::map<const std::string, float> LinearEquationSolver::getResult() {
	// check if enough variables are given
	// count variables
	std::map<const std::string &, int> varnames;
	for (auto &eqvars : variables) {
		int cnt = 0;
		for (var v : eqvars) {
			varnames.insert(std::pair<std::string, int>(v.name, cnt++));
		}
	}
	if (varnames.size() != variables.size()) {
		throw DIFF_VAR_EQ;
	}
	std::size_t size = variables.size();
	rtMatrix matrix(size, size);
	for (int eqnum = 0; eqnum < size; eqnum ++) {
		auto equation = variables[eqnum];
		for (var &var : equation) {
			const std::string &vn = var.name;
			int varnum = varnames[vn];
			matrix[eqnum][varnum] = var.factor;
		}
	}
}
