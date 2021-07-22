#pragma once
#include "TwoArgExpression.h"

// Addition expression
class ExprSum : public TwoArgExpression
{
public:
	ExprSum(ExpressionBase* expr1, ExpressionBase* expr2);
	~ExprSum();
	// Adds two expressions
	double Calculate();
};

