#pragma once
// Expression, that is a selection of cells. TODO: inherid from Expression if the future
class ExprCellSelection
{
public:
	ExprCellSelection(int c1row, int c1col, int c2row, int c2col);

private:
	int _c1row;
	int _c1col;
	int _c2row;
	int _c2col;
};

