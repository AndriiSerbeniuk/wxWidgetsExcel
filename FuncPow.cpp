#include "FuncPow.h"

FuncPow::FuncPow(std::vector<ExpressionBase*>& args) : FuncBase(args)
{}

FuncPow::~FuncPow()
{}

double FuncPow::Calculate()
{
	return pow(_args[0]->Calculate(), _args[1]->Calculate());
}
