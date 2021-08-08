#pragma once
#include "TwoArgBase.h"

// Multiplication expression
class ExprMul : public TwoArgBase
{
public:
	ExprMul(ExpressionBase* expr1, ExpressionBase* expr2);
	ExprMul(double value, ExpressionBase* expr);
	~ExprMul();
	// Multiplies two expressions
	double Calculate();
private:
	// Multiplication value, provided directly in the constructor
	double* _direct_value;
};

