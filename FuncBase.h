#pragma once
#include <vector>
#include "ExpressionBase.h"
#include "ExprCellSelection.h"

// Base class for function expressions
class FuncBase : public ExpressionBase
{
public:
	FuncBase();
	FuncBase(std::vector<ExpressionBase*>& args);
	virtual ~FuncBase();
	virtual double Calculate();

protected:
	// Given function argments
	ExpressionBase** _args;
	// Amount of arguments
	int _args_count;
};

