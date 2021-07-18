#pragma once
#include <vector>
#include "ExprCell.h"
#include "ExprNumber.h"

// Container for literal values of the function
struct LiteralsContainer
{
	// Numbers
	std::vector<ExprNumber> Nums;
	// Cells' IDs
	std::vector<ExprCell> Cells;
	// Clears internal containers
	void Clear();
};

