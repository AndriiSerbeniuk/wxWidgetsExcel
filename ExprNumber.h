#pragma once
#include <string>
#include "ExpressionBase.h"

// Expression, that is just a single number
class ExprNumber : public ExpressionBase
{
public:
	ExprNumber(const std::string& text);
	// Returns the value
	double Calculate();

private:
	// Value of the number
	double _value;
};

