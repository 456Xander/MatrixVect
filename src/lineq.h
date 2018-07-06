#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

//EXCEPTIONS
#define DIFF_VAR_EQ 1

struct var{
	const std::string name;
	float factor;
};

class LinearEquationSolver {
   private:
	void addEquation(const std::string equation);
	std::map<const std::string, float> getResult();
	
	std::vector<std::vector<var>> variables;
	

   public:
	template <std::size_t len>
	std::map<const std::string, float> solve(std::array<const std::string, len> equations) {
		for (const std::string &s : equations) {
			addEquation(s);
		}
		return getResult();
	}
};
