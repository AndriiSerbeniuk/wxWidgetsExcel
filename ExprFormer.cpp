#include "ExprFormer.h"

ExpressionBase* ExprFormer::Form(std::list<Lexem> lexems, 
	const LiteralsContainer& literals, 
	const wxGrid* grid)
{
	ExpressionBase* retVal = nullptr;
	// If there's only 1 lexem left - it's a literal
	if (lexems.size() == 1)
	{
		retVal = _form_literal(lexems.front(), literals, grid);
	}
	else
	{
		// Form + and - first
		retVal = _form_sum_or_subtract(lexems, literals, grid);
		if (!retVal)
		{
			retVal = _form_mul_or_div(lexems, literals, grid);
			if (!retVal)
			{
				retVal = _form_parentheses(lexems, literals, grid);
			}
		}
	}
	
	// form * and /

	// form ()

	// form functions

	return retVal;
}

ExpressionBase* ExprFormer::_form_parentheses(std::list<Lexem> lexems, const LiteralsContainer& literals, const wxGrid* grid)
{
	ExpressionBase* res = nullptr;
	auto first = lexems.begin();
	auto last = --lexems.end();
	if (*first == Lexem::LRoundOpen && *last == Lexem::LRoundClosed)
	{
		std::list<Lexem> parentheses;
		parentheses.assign(++first, last);
		res = Form(parentheses, literals, grid);
	}
	return res;
}

TwoArgExpression* ExprFormer::_form_sum_or_subtract(std::list<Lexem> lexems, const LiteralsContainer& literals, const wxGrid* grid)
{
	TwoArgExpression* res = nullptr;
	// Find first + or - on this depth (not in parentheses or in a function)
	int parenthesesFound = 0;
	for (auto i = lexems.begin(); i != lexems.end() && !res; i++)
	{
		if (i->Type != kDivider && i->Type != kOperation)
			continue;
		switch (i->Value)
		{
		case kRoundOpen:
			parenthesesFound++;
			break;
		case kRoundClosed:
			parenthesesFound--;
			break;
		case kPlus:
			if (!parenthesesFound)
			{
				std::list<Lexem> left;
				std::list<Lexem> right;
				_extract_left_right(lexems, i, left, right);
				res = new ExprSum(Form(left, literals, grid), Form(right, literals, grid));
			}
			break;
		case kMinus:
			// If the expression starts with minus it's handled as multiplication by -1 elsewhere
			if (!parenthesesFound && i != lexems.begin())	
			{
				std::list<Lexem> left;
				std::list<Lexem> right;
				_extract_left_right(lexems, i, left, right);
				res = new ExprSubtract(Form(left, literals, grid), Form(right, literals, grid));	
			}
			break;
		default:
			break;
		}
	}
	return res;
}

TwoArgExpression* ExprFormer::_form_mul_or_div(std::list<Lexem> lexems, const LiteralsContainer& literals, const wxGrid* grid)
{
	TwoArgExpression* res = nullptr;
	// Find first + or - on this depth (not in parentheses or in a function)
	int parenthesesFound = 0;
	for (auto i = lexems.begin(); i != lexems.end() && !res; i++)
	{
		if (i->Type != kDivider && i->Type != kOperation)
			continue;
		switch (i->Value)
		{
		case kRoundOpen:
			parenthesesFound++;
			break;
		case kRoundClosed:
			parenthesesFound--;
			break;
		case kMultiply:
			if (!parenthesesFound)
			{
				std::list<Lexem> left;
				std::list<Lexem> right;
				_extract_left_right(lexems, i, left, right);
				res = new ExprMul(Form(left, literals, grid), Form(right, literals, grid));
			}
			break;
		case kDivide:
			if (!parenthesesFound)
			{
				std::list<Lexem> left;
				std::list<Lexem> right;
				_extract_left_right(lexems, i, left, right);
				res = new ExprDiv(Form(left, literals, grid), Form(right, literals, grid));
			}
			break;
		case kMinus:
			if (!parenthesesFound && i == lexems.begin())	// Make the expression negative
			{
				std::list<Lexem> left;
				std::list<Lexem> right;
				_extract_left_right(lexems, i, left, right);
				res = new ExprMul(-1, Form(right, literals, grid));
			}
			break;
		default:
			break;
		}
	}
	return res;
}

void ExprFormer::_extract_left_right(
	std::list<Lexem>& lexems, 
	std::list<Lexem>::iterator& middle, 
	std::list<Lexem>& left_out, 
	std::list<Lexem>& right_out)
{
	left_out.insert(left_out.begin(), lexems.begin(), middle);
	middle++;
	right_out.insert(right_out.begin(), middle, lexems.end());
}

ExpressionBase* ExprFormer::_form_literal(const Lexem& lexem, const LiteralsContainer& literals, const wxGrid* grid)
{
	ExpressionBase* retVal = nullptr;
	switch (lexem.Type)
	{
	case kNumber:
		retVal = _form_number(lexem, literals);
		break;
	case kCell:
		retVal = _form_cell(lexem, literals, grid);
		break;
	case kCellSelection:
		retVal = _form_cell_selection(lexem, literals, grid);
		break;
	}
	return retVal;
}

ExprNumber* ExprFormer::_form_number(const Lexem& lexem, const LiteralsContainer& literals)
{
	ExprNumber* num = new ExprNumber(literals.Nums[lexem.Value]);
	return num;
}

ExprCell* ExprFormer::_form_cell(const Lexem& lexem, const LiteralsContainer& literals, const wxGrid* grid)
{
	ExprCell* cell = new ExprCell(literals.Cells[lexem.Value]);
	cell->SetGrid(grid);
	return cell;
}

ExprCellSelection* ExprFormer::_form_cell_selection(const Lexem& lexem, const LiteralsContainer& literals, const wxGrid* grid)
{
	ExprCellSelection* sel = new ExprCellSelection(literals.Selections[lexem.Value]);
	sel->SetGrid(grid);
	return sel;
}
