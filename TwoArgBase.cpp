#include "TwoArgBase.h"

TwoArgBase::TwoArgBase() : ExpressionBase(), _nested_2(nullptr)
{}

TwoArgBase::TwoArgBase(ExpressionBase * nested1, ExpressionBase * nested2)
	: ExpressionBase(nested1), _nested_2(nested2)
{}

TwoArgBase::~TwoArgBase()
{
	if (_nested_2)
		delete _nested_2;
}

double TwoArgBase::Calculate()
{
	return 0.0;
}
