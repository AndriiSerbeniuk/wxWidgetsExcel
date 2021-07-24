#include "FuncSqrt.h"

FuncSqrt::FuncSqrt(std::vector<ExpressionBase*>& arg) : FuncBase(arg)
{}

FuncSqrt::~FuncSqrt()
{}

double FuncSqrt::Calculate()
{
	return sqrt(_args[0]->Calculate());
}
