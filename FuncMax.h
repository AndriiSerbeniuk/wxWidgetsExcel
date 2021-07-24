#pragma once
#include "FuncMin.h"

// "Max" function expression 
class FuncMax : public FuncMin
{
public:
	FuncMax(std::vector<ExpressionBase*>& args);
	~FuncMax();

private:
	// Returns n1 < n2
	bool _comp_predicate(double n1, double n2);
};

