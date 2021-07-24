#pragma once
#include "FuncSum.h"

// "Average" function expression 
class FuncAvg : public FuncSum
{
public:
	FuncAvg(std::vector<ExpressionBase*>& args);
	~FuncAvg();
	// Return average value of given arguments
	double Calculate();
};

