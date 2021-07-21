#include "Expression.h"

Expression::Expression(std::list<Lexem> lexems)	// TODO
{

}

Expression::~Expression()
{
	if (_nested)
		delete _nested;
}

double Expression::Calculate()	// TODO
{

	return 0.0;
}
