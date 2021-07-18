#pragma once
#include <string>
// Expression, that is just a single cell coordinates. TODO: inherid from Expression if the future
class ExprCell
{
public:
	ExprCell(const std::string& row, const std::string& col);

private:
	// Number of leters in the alphabet. Used for column ID parsing
	const static int kNumBase;
	// Column number
	int _column;
	// Row number
	int _row;

	// Parse col ID in text into a number
	int _parse_col_id(const std::string& text);
};

