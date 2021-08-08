#include "FuncAvg.h"

FuncAvg::FuncAvg(std::vector<ExpressionBase*>& args) : FuncSum(args)
{
}

FuncAvg::~FuncAvg()
{
}

double FuncAvg::Calculate()
{
	int valCount = 0;
	for (int i = 0; i < _args_count; i++)
	{
		if (typeid(*_args[i]) == typeid(ExprCellSelection))
		{
			ExprCellSelection* sel = static_cast<ExprCellSelection*>(_args[i]);
			valCount += sel->GetHeight() * sel->GetWidth();
		}
		else
		{
			valCount++;
		}
	}

	return FuncSum::Calculate() / valCount;
}
