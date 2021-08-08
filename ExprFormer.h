#pragma once
#include <list>
#include "wx/grid.h"
#include "Lexem.h"
#include "LiteralsContainer.h"
#include "ExprSum.h"
#include "ExprSubtract.h"
#include "ExprMul.h"
#include "ExprDiv.h"
#include "ExprNumber.h"
#include "ExprCell.h"
#include "FuncSqrt.h"
#include "FuncSum.h"
#include "FuncAvg.h"
#include "FuncPow.h"
#include "FuncMax.h"

// Forms expressions using given lexems, literals, and wxGrid to take cell values from
class ExprFormer
{
public:
	// Forms expression from given lexems
	static ExpressionBase* Form(std::list<Lexem> lexems, 
		const LiteralsContainer& literals, const wxGrid* grid);

private:
	ExprFormer();
	// Creates internal expression
	static ExpressionBase* _form_parentheses(std::list<Lexem> lexems,
		const LiteralsContainer& literals, const wxGrid* grid);
	// Creates a + or - expression
	static TwoArgBase* _form_sum_or_subtract(std::list<Lexem> lexems,
		const LiteralsContainer& literals, const wxGrid* grid);
	// Creates a * or / expression
	static TwoArgBase* _form_mul_or_div(std::list<Lexem> lexems,
		const LiteralsContainer& literals, const wxGrid* grid);
	// Creates function expression
	static FuncBase* _form_func(std::list<Lexem> lexems,
		const LiteralsContainer& literals, const wxGrid* grid);
	// Extracts all lexems to the left and to the right from the given middle lexem
	static void _extract_left_right(std::list<Lexem>& lexems, std::list<Lexem>::iterator& middle,
		std::list<Lexem>& left_out,	std::list<Lexem>& right_out);
	// Creates a literal expression (number, cell, or cell selection)
	static ExpressionBase* _form_literal(const Lexem& lexem,
		const LiteralsContainer& literals, const wxGrid* grid);
	static ExprNumber* _form_number(const Lexem& lexem, 
		const LiteralsContainer& literals);
	static ExprCell* _form_cell(const Lexem& lexem,
		const LiteralsContainer& literals, const wxGrid* grid);
	static ExprCellSelection* _form_cell_selection(const Lexem& lexem,
		const LiteralsContainer& literals, const wxGrid* grid);
};

