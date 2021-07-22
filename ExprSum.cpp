#include "ExprSum.h"

ExprSum::ExprSum(ExpressionBase* expr1, ExpressionBase* expr2)
{
	_nested = expr1;
	_nested_2 = expr2;
}

ExprSum::~ExprSum()
{
	delete _nested;
	delete _nested_2;
}

double ExprSum::Calculate()
{
	return _nested->Calculate() + _nested_2->Calculate();
}
