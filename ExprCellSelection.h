#pragma once
#include <string>
#include "wx/grid.h"
#include "ExprCell.h"

// Expression, that is a selection of cells
class ExprCellSelection : public ExprCell
{
public:
	ExprCellSelection(int c1row, int c1col, int c2row, int c2col);
	/* Returns cells values from the given wxGrid. 
	Returns one value at a time, call multiple times to get all the values.
	Throws std::out_of_range.*/
	double Calculate();
	// Set current cell to the start of the selection
	void ResetRange();
	// Returns width of the selection
	int GetWidth() const;
	// Returns height of the selection
	int GetHeight() const;

private:
	int _c1row;
	int _c1col;
	int _c2row;
	int _c2col;

};

