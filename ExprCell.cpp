#include "ExprCell.h"

const int ExprCell::kNumBase = 26;	// Because english has 26 letters

ExprCell::ExprCell() : _row(0), _column(0), _grid(nullptr)
{}

ExprCell::ExprCell(int row, int col) : _row(row), _column(col), _grid(nullptr)
{}

ExprCell::ExprCell(const std::string& row, const std::string& col) : _grid(nullptr)
{
	// Row is a number
	try
	{
		_row = std::stoi(row) - 1;
	}
	catch (std::exception)
	{
		_row = 0;
	}
	// Cell is text
	_column = _parse_col_id(col) - 1;

}

ExprCell::~ExprCell()
{}

int ExprCell::GetRow() const
{
	return _row;
}

int ExprCell::GetColumn() const
{
	return _column;
}

void ExprCell::SetGrid(const InfiniteGrid* grid)
{
	_grid = grid;
}

double ExprCell::Calculate()
{
	return _get_cell_value();
}

double ExprCell::_get_cell_value() const
{
	std::string cellVal;
	try
	{
		cellVal = _grid->GetCellValue(_row, _column).ToStdString();
	}
	catch (std::exception)
	{
		// If the cell doesn't exist it's value is 0
		return 0;
	}
	double numValue = 0;
	try
	{
		numValue = std::stod(cellVal);
	}
	catch (std::exception)
	{
		// If hte cell's value isn't a number it's considered 0
		numValue = 0;
	}
	return numValue;
}

int ExprCell::_parse_col_id(const std::string& text)
{
	// Column ID is a series of letters that represent a number in base-26 numeral system
	int result = 0, i = 0;
	for (std::string::const_reverse_iterator t = text.crbegin(); 
		t != text.crend(); t++, i++)
	{
		result += (static_cast<int>(*t) - static_cast<int>('A') + 1) 
			* static_cast<int>(pow(kNumBase, i));
	}
	return result;
}