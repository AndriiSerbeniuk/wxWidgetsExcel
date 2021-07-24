#include "CellFunction.h"

CellFunction::CellFunction(wxGridCellCoords cell, wxGrid* grid) 
	: _result("#Error#"), _expression(nullptr), _grid(grid)
{
	// Parse the text into lexems
	_parser.SetText(grid->GetCellValue(cell).ToStdString());
	// Check for validity
	if (GrammarChecker::Run(_parser.GetParsed()))
	{
		// Form lexems into a calculable expression
		_expression = ExprFormer::Form(_parser.GetParsed(), _parser.GetLiterals(), _grid);
		if (_expression)
		{
			try
			{
				double res = _expression->Calculate();
				_result = std::to_string(res);
			}
			catch (std::exception)
			{}
		}
	}
}

CellFunction::~CellFunction()
{
	if (_expression)
		delete _expression;
}

std::string CellFunction::GetResult() const
{
	return _result;
}
