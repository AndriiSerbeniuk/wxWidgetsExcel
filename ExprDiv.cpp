#include "ExprDiv.h"

ExprDiv::ExprDiv(ExpressionBase* expr1, ExpressionBase* expr2)
    : TwoArgBase(expr1, expr2)
{}

ExprDiv::~ExprDiv()
{}

double ExprDiv::Calculate()
{
    return _nested->Calculate() / _nested_2->Calculate();
}
