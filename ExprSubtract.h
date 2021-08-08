#pragma once
#include "TwoArgBase.h"

// Subtraction expression
class ExprSubtract : public TwoArgBase
{
public:
	ExprSubtract(ExpressionBase* expr1, ExpressionBase* expr2);
	~ExprSubtract();
	// Subtracts two expressions
	double Calculate();
};

