#pragma once
#include <string>

// Base class for expression types
class ExpressionBase
{
public:
	ExpressionBase();
	ExpressionBase(ExpressionBase* nested);
	virtual ~ExpressionBase();
	// Calculate the value of the expression
	virtual double Calculate();

protected:
	// The actual expression to be calculated 
	ExpressionBase* _nested;
};

