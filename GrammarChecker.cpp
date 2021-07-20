#include "GrammarChecker.h"

GrammarChecker::GState::GState(const std::vector<Lexem>& values, int transition,
	bool accept, int errorTrans, int toStack)
	: Transition(transition), ErrorTransition(errorTrans),
	ToStack(toStack), Accept(accept) 
{
	Values.assign(values.cbegin(), values.cend());
}

bool GrammarChecker::Run(std::list<Lexem> lexems)
{
	int stateNum = 1;
	std::list<Lexem>::iterator lexemIter = lexems.begin();
	Lexem* lexem = &*lexemIter;
	bool clear = false, result = true;
	const GState* curState = nullptr;
	std::stack<int> statesStack;
	// While there are transitions
	while (stateNum && result)
	{
		curState = &kGrammar.at(stateNum);
		// If lexem is awaited by the state
		if (_check_anticipated(*lexem, stateNum))
		{
			// If it is accepted - move to the next lexem
			if (curState->Accept)
			{
				lexemIter++;
				if (lexemIter != lexems.cend())
					lexem = &*lexemIter;
				else
				{
					// If there are no more lexems grammar check should not end yet
					lexem = new Lexem(Lexem::LErr);
					clear = true;
					// This only happens at the end, when the grammar may await more lexems.
					// If it doesn't await anything specific the lexems may end
					// If grammar awaits something specific but there is nothing - it's an error
				}
			}
			// Manage stack
			if (curState->ToStack)
				statesStack.push(curState->ToStack);
			// Get next transition
			if (curState->Transition)
				stateNum = curState->Transition;
			else
			{
				if (!statesStack.size())
				{
					// There are no transitions left
					stateNum = 0;
				}
				else
				{
					stateNum = statesStack.top();
					statesStack.pop();
				}
			}
		}
		else // The state does not await this lexem
		{
			if (curState->ErrorTransition)
			{
				stateNum = curState->ErrorTransition;
			}
			else
			{
				// If there is no error transiotion - it's a grammatical error
				lexem->Type = kError;	// To represent which lexem caused it
				result = false;
			}
		}
	}
	if (clear)
		delete lexem;
	return result;
}

bool GrammarChecker::_check_anticipated(const Lexem& lexem, int stateNum)
{
	const GState& state = kGrammar.at(stateNum);
	// If given state contains given lexem - it is anticipated
	for (std::vector<Lexem>::const_iterator i = state.Values.cbegin(); i != state.Values.cend(); i++)
	{
		if (lexem == *i)
			return true;
	}
	return false;
}

