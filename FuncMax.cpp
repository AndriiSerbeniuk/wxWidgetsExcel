#include "FuncMax.h"

FuncMax::FuncMax(std::vector<ExpressionBase*>& args) : FuncMin(args)
{}

FuncMax::~FuncMax()
{}

bool FuncMax::_comp_predicate(double n1, double n2)
{
	return n1 < n2;
}
