#pragma once
#include "GrammarChecker.h"
#include "ExprFormer.h"
#include "wx/grid.h"
#include "LexemParser.h"

// Function entered into a cell
class CellFunction
{
public:
	CellFunction(wxGridCellCoords cell, wxGrid* grid);
	~CellFunction();

	std::string GetResult() const;

private:
	std::string _result;
	LexemParser _parser;
	ExpressionBase* _expression;
	// Used to get cell values from by the expression
	wxGrid* _grid;
};

