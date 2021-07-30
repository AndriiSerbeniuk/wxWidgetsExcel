#pragma once
#include "GrammarChecker.h"
#include "ExprFormer.h"
#include "wx/grid.h"
#include "LexemParser.h"

// Function entered into a cell
class CellFunction
{
public:
	CellFunction();
	CellFunction(wxGridCellCoords cell, wxGrid* grid);
	~CellFunction();

	// Returns function result
	std::string GetResult() const;
	// Gets raw function text
	std::string GetFuncText() const;
	// Returns a list of cells? which this functions uses in its calculation
	const std::list<wxGridCellCoords>& GetDependencies() const;
	// Calculate value of the function
	void Calculate();
	// Updates the function
	void Update();

private:
	// Error message used when the function is not valid
	static const std::string errMsg;
	// Cell the function is entered in
	wxGridCellCoords _cell;
	// Result of the expression
	std::string _result;
	// Lexem parser to get a list of lexems from given text. Also stores original text.
	LexemParser _parser;
	// Parsed entered expression
	ExpressionBase* _expression;
	// Used to get cell values from by the expression
	wxGrid* _grid;
	// Marks that the function is valid for calculation
	bool _expression_valid;
	// List of used cells
	std::list<wxGridCellCoords> _dependencies;

	// Solves internal expression
	void _solve_expression();
};