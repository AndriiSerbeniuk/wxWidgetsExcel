#include "ExprNumber.h"

ExprNumber::ExprNumber(const std::string& text)
{
	try
	{
		_value = std::stod(text);
	}
	catch (std::exception)
	{
		_value = 0;
	}
}
