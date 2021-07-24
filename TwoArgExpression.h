#pragma once
#include "ExpressionBase.h"

// Base class for expression types with two arguments
class TwoArgExpression : public ExpressionBase
{
public:
	TwoArgExpression();
	TwoArgExpression(ExpressionBase* nested1, ExpressionBase* nested2);
	virtual ~TwoArgExpression();
	// Calculate the value of the expression
	virtual double Calculate();

protected:
	// Second nested expression
	ExpressionBase* _nested_2;
};

