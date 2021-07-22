#include "ExprSubtract.h"

ExprSubtract::ExprSubtract(ExpressionBase* expr1, ExpressionBase* expr2)
{
    _nested = expr1;
    _nested_2 = expr2;
}

ExprSubtract::~ExprSubtract()
{
    if (_nested)
        delete _nested;
    if (_nested_2)
        delete _nested_2;
}

double ExprSubtract::Calculate()
{
    return _nested ?
        _nested->Calculate() - _nested_2->Calculate() :
        -_nested_2->Calculate();
}
