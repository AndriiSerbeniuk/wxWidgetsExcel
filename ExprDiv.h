#pragma once
#include "TwoArgExpression.h"

// Division expression
class ExprDiv : public TwoArgExpression
{
public:
	ExprDiv(ExpressionBase* expr1, ExpressionBase* expr2);
	~ExprDiv();
	// Divides the first expression by the second
	double Calculate();
};

