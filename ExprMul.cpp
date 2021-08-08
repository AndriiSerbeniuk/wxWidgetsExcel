#include "ExprMul.h"

ExprMul::ExprMul(ExpressionBase* expr1, ExpressionBase* expr2)
    : TwoArgBase(expr1, expr2), _direct_value(nullptr)
{}

ExprMul::ExprMul(double value, ExpressionBase* expr)
    : _direct_value(new double(value))
{
    _nested = expr;
    _nested_2 = nullptr;
}

ExprMul::~ExprMul()
{
    if (_direct_value)
        delete _direct_value;
}

double ExprMul::Calculate()
{
    return _direct_value ? *_direct_value * _nested->Calculate()
        : _nested->Calculate() * _nested_2->Calculate();
}
