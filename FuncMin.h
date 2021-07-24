#pragma once
#include "FuncBase.h"

// "Min" function expression 
class FuncMin : public FuncBase
{
public:
	FuncMin(std::vector<ExpressionBase*>& args);
	virtual ~FuncMin();
	// Returns a value from the given args based on the comparison expression
	double Calculate();

protected:
	// Returns n1 > n2
	virtual bool _comp_predicate(double n1, double n2);

private:
	// Performs calculation for cell selection
	double _calculate_selection(ExprCellSelection* arg);
};

