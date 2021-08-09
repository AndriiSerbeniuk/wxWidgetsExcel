#pragma once
#include "Lexem.h"
#include <list>
#include <vector>
#include <map>
#include <stack>

class GrammarChecker
{
public:
	static bool Run(std::list<Lexem>& lexems);

private:
	// State of LL(1) grammar
	struct GState 
	{
		// Anticipated values that can be accepted by the state
		std::vector<Lexem> Values;
		// Transition in case when lexem is present in the Values vector. If == 0 - take from the stack.
		int Transition;
		// Transition in case when lexem is not present in the Values vector. If == 0 - it's an error.
		int ErrorTransition;
		// Value to add to the stack. If == 0 - don't add anything.
		int ToStack;
		// Marks that the checker can move to the next lexem.
		bool Accept;

		GState(const std::vector<Lexem>& values, int transition,
			bool accept = false, int errorTrans = 0, int toStack = 0);
	}; 
	// Grammar that the checker utilizes
	static const std::map<int, GState> kGrammar;

	// Frequently used big lists of lexems

	static const std::vector<Lexem> kExprInput;
	static const std::vector<Lexem> kParamInput;

	GrammarChecker();
	// Checks if given lexem is awaited by the given state
	static bool _check_anticipated(const Lexem& lexem, int stateNum);
};

