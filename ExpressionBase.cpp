#include "ExpressionBase.h"

ExpressionBase::~ExpressionBase()
{}

ExpressionBase::ExpressionBase() : _nested(nullptr)
{}

double ExpressionBase::Calculate()
{
	return 0.0;
}

