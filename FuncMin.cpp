#include "FuncMin.h"

FuncMin::FuncMin(std::vector<ExpressionBase*>& args) : FuncBase(args)
{}

FuncMin::~FuncMin()
{}

double FuncMin::Calculate()
{
	if (_args_count < 1)
		throw std::exception("FuncMin: no arguments provided;");
	int min = _args[0]->Calculate(), temp = 0;
	for (int i = 1; i < _args_count; i++)
	{
		if (typeid(*_args[i]) == typeid(ExprCellSelection))
		{
			temp = _calculate_selection(static_cast<ExprCellSelection*>(_args[i]));
		}
		else
		{
			temp = _args[i]->Calculate();
		}
		if (_comp_predicate(min, temp))
			min = temp;
	}
	return min;
}

bool FuncMin::_comp_predicate(double n1, double n2)
{
	return n1 > n2;
}

double FuncMin::_calculate_selection(ExprCellSelection* arg)
{
	int min = arg->Calculate(), temp = 0, doTimes = arg->GetHeight() * arg->GetWidth();
	for (int i = 1; i < doTimes; i++)
	{
		temp = arg->Calculate();
		if (_comp_predicate(min, temp))
			min = temp;
	}
	return min;
}
