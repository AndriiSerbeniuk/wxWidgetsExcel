#include "FuncBase.h"

FuncBase::FuncBase() : _args_count(0), _args(nullptr) {}

FuncBase::FuncBase(std::vector<ExpressionBase*>& args)
{
	_args_count = args.size();
	if (_args_count > 0)
	{
		_args = new ExpressionBase * [_args_count];
		std::copy(args.cbegin(), args.cend(), _args);
	}
}

FuncBase::~FuncBase() 
{
	if (_args)
	{
		for (int i = 0; i < _args_count; i++)
			delete _args[i];
		delete[] _args;
	}
}

double FuncBase::Calculate()
{
	return 0.0;
}
