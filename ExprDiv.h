#pragma once
#include "TwoArgBase.h"

// Division expression
class ExprDiv : public TwoArgBase
{
public:
	ExprDiv(ExpressionBase* expr1, ExpressionBase* expr2);
	~ExprDiv();
	// Divides the first expression by the second
	double Calculate();
};

