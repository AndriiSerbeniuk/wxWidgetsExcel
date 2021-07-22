#pragma once
#include "TwoArgExpression.h"

// Subtraction expression
class ExprSubtract : public TwoArgExpression
{
public:
	ExprSubtract(ExpressionBase* expr1, ExpressionBase* expr2);
	~ExprSubtract();
	// Subtracts two expressions
	double Calculate();
};

