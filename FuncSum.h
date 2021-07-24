#pragma once
#include "FuncBase.h"

// "Sum" function expression 
class FuncSum : public FuncBase
{
public:
	FuncSum(std::vector<ExpressionBase*>& args);
	virtual ~FuncSum();
	// Returns sum of given arguments
	virtual double Calculate();

private:
	// Performs calculation for cell selection
	double _calculate_selection(ExprCellSelection* arg);
};

