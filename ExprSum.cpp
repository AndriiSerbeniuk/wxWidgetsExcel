#include "ExprSum.h"

ExprSum::ExprSum(ExpressionBase* expr1, ExpressionBase* expr2)
	: TwoArgBase(expr1, expr2)
{}

ExprSum::~ExprSum()
{}

double ExprSum::Calculate()
{
	return _nested->Calculate() + _nested_2->Calculate();
}
