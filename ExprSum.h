#pragma once
#include "TwoArgBase.h"

// Addition expression
class ExprSum : public TwoArgBase
{
public:
	ExprSum(ExpressionBase* expr1, ExpressionBase* expr2);
	~ExprSum();
	// Adds two expressions
	double Calculate();
};

