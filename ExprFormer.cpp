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
		
		// TODO: if !retval form mul ... 
	}

	// form * and /

	// form ()

	// form functions

	return retVal;
}

TwoArgExpression* ExprFormer::_form_sum_or_subtract(std::list<Lexem> lexems, const LiteralsContainer& literals, const wxGrid* grid)
{
	TwoArgExpression* res = nullptr;
	// Find first + or - on this depth (not in parentheses or in a function)
	int parenthesesFound = 0;
	for (auto i = lexems.begin(); i != lexems.end() && !res; i++)
	{
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
				left.insert(left.begin(), lexems.begin(), i);
				i++;
				std::list<Lexem> right;
				right.insert(right.begin(), i, lexems.end());
				res = new ExprSum(Form(left, literals, grid), Form(right, literals, grid));
			}
			break;
		case kMinus:
			if (!parenthesesFound)
			{
				std::list<Lexem> left;
				left.insert(left.begin(), lexems.begin(), i);
				i++;
				std::list<Lexem> right;
				right.insert(right.begin(), i, lexems.end());
				if (left.size())
					res = new ExprSubtract(Form(left, literals, grid), Form(right, literals, grid));
				// TODO: this is wrong. it should be multiplied here, so move this to hte multiplication when it's ready
				//else
				//	res = new ExprSubtract(nullptr, Form(right, literals, grid));	
			}
			break;
		default:
			break;
		}
	}
	return res;
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
