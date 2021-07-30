#include "FuncMin.h"

FuncMin::FuncMin(std::vector<ExpressionBase*>& args) : FuncBase(args)
{}

FuncMin::~FuncMin()
{}

double FuncMin::Calculate()
{
	if (_args_count < 1)
		throw std::exception("FuncMin: no arguments provided;");
	double min = 0, temp = 0;
	if (typeid(*_args[0]) == typeid(ExprCellSelection))
		min = _calculate_selection(static_cast<ExprCellSelection*>(_args[0]));
	else
		min = _args[0]->Calculate();
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
	double min = arg->Calculate(), temp = 0;
	int doTimes = arg->GetHeight() * arg->GetWidth();
	for (int i = 1; i < doTimes; i++)
	{
		temp = arg->Calculate();
		if (_comp_predicate(min, temp))
			min = temp;
	}
	arg->ResetRange();
	return min;
}
