#include "ExprCellSelection.h"
#include <stdexcept>

ExprCellSelection::ExprCellSelection(int c1row, int c1col, int c2row, int c2col)
	: _c1row(c1row), _c1col(c1col), _c2row(c2row), _c2col(c2col) 
{
	// cell 1 has to be in the top left corner of the selection
	if (_c1row > _c2row)
		std::swap(_c1row, _c2row);
	if (_c1col > _c2col)
		std::swap(_c1col, _c2col);
	_row = _c1row;
	_column = _c1col;
}

double ExprCellSelection::Calculate()
{
	if (_column > _c2col || _row > _c2row || _column < _c1col || _row < _c1row)
		throw std::out_of_range(std::string("ExprCellSelection::Calculate(): Cell (" + std::to_string(_row) +
			+ ";" + std::to_string(_column) + ") is out of selection range;"));
	double retVal = _get_cell_value();
	// Go to the next cell
	Advance();
	return retVal;
}

void ExprCellSelection::Advance()
{
	if (_column < _c2col)
		_column++;
	else
	{
		_row++;
		_column = _c1col;
	}
}

void ExprCellSelection::ResetRange()
{
	_row = _c1row;
	_column = _c1col;
}

int ExprCellSelection::GetWidth() const
{
	return _c2col - _c1col + 1;
}

int ExprCellSelection::GetHeight() const
{
	return _c2row - _c1row + 1;
}
