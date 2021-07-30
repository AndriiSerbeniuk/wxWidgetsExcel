#include "FuncSum.h"

FuncSum::FuncSum(std::vector<ExpressionBase*>& args) : FuncBase(args)
{}

FuncSum::~FuncSum()
{}

double FuncSum::Calculate()
{
	double sum = 0;
	for (int i = 0; i < _args_count; i++)
	{
		if (typeid(*_args[i]) == typeid(ExprCellSelection))
		{
			sum += _calculate_selection(static_cast<ExprCellSelection*>(_args[i]));
		}
		else
		{
			sum += _args[i]->Calculate();
		}
	}
	return sum;
}

double FuncSum::_calculate_selection(ExprCellSelection* arg)
{
	double sum = 0;
	int doTimes = arg->GetHeight() * arg->GetWidth();
	for (int i = 0; i < doTimes; i++)
	{
		sum += arg->Calculate();
	}
	arg->ResetRange();
	return sum;
}