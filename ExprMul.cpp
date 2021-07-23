#include "ExprMul.h"

ExprMul::ExprMul(ExpressionBase* expr1, ExpressionBase* expr2)
    : _direct_value(nullptr)
{
    _nested = expr1;
    _nested_2 = expr2;
}

ExprMul::ExprMul(double value, ExpressionBase* expr)
    : _direct_value(new double(value))
{
    _nested = expr;
    _nested_2 = nullptr;
}

ExprMul::~ExprMul()
{
    if (_nested)
        delete _nested;
    if (_nested_2)
        delete _nested_2;
    if (_direct_value)
        delete _direct_value;
}

double ExprMul::Calculate()
{
    return _direct_value ? *_direct_value * _nested->Calculate()
        : _nested->Calculate() * _nested_2->Calculate();
}
