#include "ExprCell.h"

const int ExprCell::kNumBase = 26;	// Because english has 26 letters

ExprCell::ExprCell(const std::string& row, const std::string& col)
{
	// Row is a number
	try
	{
		_row = std::stoi(row);
	}
	catch (std::exception)
	{
		_row = 0;
	}
	// Cell is text
	_column = _parse_col_id(col);

}

int ExprCell::_parse_col_id(const std::string& text)	
{
	// Column ID is a series of letters that represent a number in base-26 numeral system
	int result = 0, i = 0;
	for (std::string::const_reverse_iterator t = text.crbegin(); 
		t != text.crend(); t++, i++)
	{
		result += (*t - 'A' + 1) * pow(kNumBase, i); 
	}
	return result;
}