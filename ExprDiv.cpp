#include "ExprDiv.h"

ExprDiv::ExprDiv(ExpressionBase* expr1, ExpressionBase* expr2)
{
    _nested = expr1;
    _nested_2 = expr2;
}

ExprDiv::~ExprDiv()
{
    if (_nested)
        delete _nested;
    if (_nested_2)
        delete _nested_2;
}

double ExprDiv::Calculate()
{
    return _nested->Calculate() / _nested_2->Calculate();
}
