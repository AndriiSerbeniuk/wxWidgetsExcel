#pragma once
#include "ExpressionBase.h"

// Base class for expression types with two arguments
class TwoArgBase : public ExpressionBase
{
public:
	TwoArgBase();
	TwoArgBase(ExpressionBase* nested1, ExpressionBase* nested2);
	virtual ~TwoArgBase();
	// Calculate the value of the expression
	virtual double Calculate();

protected:
	// Second nested expression
	ExpressionBase* _nested_2;
};

