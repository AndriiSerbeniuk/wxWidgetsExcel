#pragma once
#include <list>
#include "wx/grid.h"
#include "Lexem.h"
#include "LiteralsContainer.h"
#include "ExprSum.h"
#include "ExprSubtract.h"
#include "ExprNumber.h"
#include "ExprCell.h"
#include "ExprCellSelection.h"

// Forms expressions using given lexems, literals, and wxGrid to take cell values from
class ExprFormer
{
public:
	// Forms expression from given lexems
	static ExpressionBase* Form(std::list<Lexem> lexems, 
		const LiteralsContainer& literals, const wxGrid* grid);

private:
	ExprFormer();
	/*static ExpressionBase* _form_parentheses(std::list<Lexem> lexems,
		const LiteralsContainer& literals, const wxGrid* grid);*/	// TODO
	// Create a + or - expression
	static TwoArgExpression* _form_sum_or_subtract(std::list<Lexem> lexems,
		const LiteralsContainer& literals, const wxGrid* grid);

	// Create a literal expression (number, cell, or cell selection)
	static ExpressionBase* _form_literal(const Lexem& lexem,
		const LiteralsContainer& literals, const wxGrid* grid);
	static ExprNumber* _form_number(const Lexem& lexem, 
		const LiteralsContainer& literals);
	static ExprCell* _form_cell(const Lexem& lexem,
		const LiteralsContainer& literals, const wxGrid* grid);
	static ExprCellSelection* _form_cell_selection(const Lexem& lexem,
		const LiteralsContainer& literals, const wxGrid* grid);
};

