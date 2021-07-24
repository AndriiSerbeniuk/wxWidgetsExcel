#include "TwoArgExpression.h"

TwoArgExpression::TwoArgExpression() : ExpressionBase(), _nested_2(nullptr)
{}

TwoArgExpression::TwoArgExpression(ExpressionBase * nested1, ExpressionBase * nested2)
	: ExpressionBase(nested1), _nested_2(nested2)
{}

TwoArgExpression::~TwoArgExpression()
{
	if (_nested_2)
		delete _nested_2;
}

double TwoArgExpression::Calculate()
{
	return 0.0;
}
