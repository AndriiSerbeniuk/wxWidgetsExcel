#pragma once
#include <list>
#include "ExpressionBase.h"
#include "Lexem.h"

// Implementation of a basic expression. TODO: expressions forming logic will be here
class Expression : public ExpressionBase
{
public:
	// Creates expression from the given lexems list
	Expression(std::list<Lexem> lexems);
	~Expression();
	// Return the result of the expression
	double Calculate();
};

