#pragma once
#include "FuncBase.h"

// "Square root" function expression 
class FuncSqrt : public FuncBase
{
public:
	FuncSqrt(std::vector<ExpressionBase*>& arg);
	~FuncSqrt();
	// Returns square root of the given argument
	double Calculate();
};

