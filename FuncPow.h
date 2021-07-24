#pragma once
#include "FuncBase.h"

// "Power" function expression 
class FuncPow : public FuncBase
{
public:
	FuncPow(std::vector<ExpressionBase*>& args);
	~FuncPow();
	// Returns first argument to the power of the second
	double Calculate();
};

