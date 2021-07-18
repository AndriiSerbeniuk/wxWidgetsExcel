#pragma once
#include <string>
// Expression, that is just a single number. TODO: inherid from Expression if the future
class ExprNumber
{
public:
	ExprNumber(const std::string& text);

private:
	// Value of the number
	double _value;
};

