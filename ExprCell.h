#pragma once
#include <string>
#include "wx/grid.h"
#include "ExpressionBase.h"

// Expression, that is just a single cell coordinate and value
class ExprCell : public ExpressionBase
{
public:
	ExprCell();
	ExprCell(int row, int col);
	ExprCell(const std::string& row, const std::string& col);
	virtual ~ExprCell();
	// Returns cell's row index
	int GetRow() const;
	// Returns cell's column index
	int GetColumn() const;
	// Set grid to take values from
	void SetGrid(wxGrid* grid);
	// Returns the cell's value from the given wxGrid
	virtual double Calculate();

protected:
	// Column index
	int _column;
	// Row index
	int _row;
	// wxGrid to take the data from
	wxGrid* _grid;
	// Gets the cell value grom the given wxGrid
	double _get_cell_value() const;
private:
	// Number of leters in the alphabet. Used for column ID parsing
	const static int kNumBase;
	// Parse col ID in text into a number
	int _parse_col_id(const std::string& text);
};

