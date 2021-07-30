#include "CellFunction.h"

const std::string CellFunction::errMsg = "#Error#";

CellFunction::CellFunction()
	: _expression(nullptr), _grid(nullptr), _parser(), _cell(-1, -1), _result(errMsg), _expression_valid(false)
{}

CellFunction::CellFunction(wxGridCellCoords cell, wxGrid* grid)
	: _result(errMsg), _expression(nullptr), _grid(grid), _cell(cell)
{
	Update();
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

std::string CellFunction::GetFuncText() const
{
	return _parser.GetText();
}

const std::list<wxGridCellCoords>& CellFunction::GetDependencies() const
{
	return _dependencies;
}

void CellFunction::Calculate()
{
	if (_expression_valid)
		_solve_expression();
}

void CellFunction::Update()
{
	if (_expression)
		delete _expression;
	_dependencies.clear();
	_expression_valid = false;
	// Parse the text into lexems
	_parser.SetText(_grid->GetCellValue(_cell).ToStdString());
	// Check for validity
	if (GrammarChecker::Run(_parser.GetParsed()))
	{
		_expression_valid = true;
		// Form lexems into a calculable expression
		_expression = ExprFormer::Form(_parser.GetParsed(), _parser.GetLiterals(), _grid);
		// Detect dependencies on other cells
		for (auto i = _parser.GetLiterals().Cells.cbegin(); i != _parser.GetLiterals().Cells.cend(); i++)
		{
			_dependencies.push_back({ i->GetRow(), i->GetColumn() });
		}
		for (auto i = _parser.GetLiterals().Selections.begin(); i != _parser.GetLiterals().Selections.end(); i++)
		{
			int doTimes = i->GetHeight() * i->GetWidth();
			for (int j = 0; j < doTimes; j++, i->Advance())
				_dependencies.push_back({ i->GetRow(), i->GetColumn() });
			i->ResetRange();
		}
		_dependencies.unique();
		_solve_expression();
	}
}

void CellFunction::_solve_expression()
{
	
	if (_expression && _expression_valid)
	{
		try
		{
			double res = _expression->Calculate();
			_result = std::to_string(res);
		}
		catch (std::exception)
		{
			_result = errMsg;
		}
	}
	else
		_result = errMsg;
}
