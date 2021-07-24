#include "ExpressionBase.h"

ExpressionBase::ExpressionBase() : _nested(nullptr)
{}

ExpressionBase::ExpressionBase(ExpressionBase * nested) : _nested(nested)
{}

ExpressionBase::~ExpressionBase()
{
	if (_nested)
		delete _nested;
}

double ExpressionBase::Calculate()
{
	return 0.0;
}

