#include "ExprSubtract.h"

ExprSubtract::ExprSubtract(ExpressionBase* expr1, ExpressionBase* expr2)
    : TwoArgBase(expr1, expr2)
{}

ExprSubtract::~ExprSubtract()
{}

double ExprSubtract::Calculate()
{
    return _nested ?
        _nested->Calculate() - _nested_2->Calculate() :
        -_nested_2->Calculate();
}
