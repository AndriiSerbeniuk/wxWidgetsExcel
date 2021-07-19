#include "LexemParser.h"

const std::vector<LexemParser::LexState> LexemParser::_states_graph = std::vector<LexState>({
	{ ' ', { 1, 2, 3, 4, 5, 6, 7, 8, 9, 15, 18, 23 } },	// 0. There numbers are the last index in the row
	// Operations
	{ '+', { } }, { '-', { } },	{ '*', { } }, { '/', { } },	// 4
	// Dividers
	{ '(', { } }, { ')', { } }, { ';', { } }, { ':', { } },	// 8
	// Keywords
	// sqrt
	{ 's', { 10, 13 } }, { 'q', { 11 } }, { 'r', { 12 } }, { 't', { } }, // 12
	// sum
	{ 'u', { 14 } }, { 'm', { } }, // 14
	// avg
	{ 'a', { 16 } }, { 'v', { 17 } }, { 'g', { } },	// 17
	// min
	{ 'm', { 19, 21 } }, { 'i', { 20 } }, { 'n', { } },	// 20
	// max
	{ 'a', { 22 } }, { 'x', { } }, // 22
	// pow
	{ 'p', { 24 } }, { 'o', { 25 } }, { 'w', { } } // 25
	});

const std::map<int, eFunction> LexemParser::_func_keys{
	{ 12, kSqrt }, { 14, kSum }, { 17, kAvg },
	{ 20, kMin }, { 22, kMax }, { 25, kPow }
};

const std::map<int, int> LexemParser::_sym_keys{
	{ 1, kPlus }, { 2, kMinus }, { 3, kMultiply }, { 4, kDivide },
	{ 5, kRoundOpen }, { 6, kRoundClosed }, { 7, kSemicolon }, { 8, kColon }
};

LexemParser::LexemParser() : _raw(), _parsed(), _literals(new LiteralsContainer()) {}

LexemParser::LexemParser(std::string text) : _parsed(), _literals(new LiteralsContainer())
{
	SetText(text);
}

void LexemParser::SetText(std::string text)
{
	_raw = text;
	_parse();
}

std::list<Lexem> LexemParser::GetParsed() const
{
	return _parsed;
}

std::shared_ptr<LiteralsContainer> LexemParser::GetLiteralsPtr()
{
	return _literals;
}

void LexemParser::_parse()
{
	const char* text = _raw.c_str();
	if (*text != '=')	// Must start with =
		return;
	text++;
	int graphResult = 0, lexStart = 0, lexEnd = 0;;
	const char* temp = nullptr;
	Lexem curLexem;

	while (*text != '\0')
	{
		while (isspace(*text))	// Skip spaces
			text++;
		lexStart = text - _raw.c_str();	// Lexem starting index
		// If symbol's a letter - it's either a keyword or a cell id
		if (isalpha(*text))	
		{
			temp = text;
			graphResult = _run_graph(temp);
			if (_func_keys.count(graphResult))
			{
				// If it was a keyword
				curLexem = Lexem::GetLexem(_func_keys.at(graphResult));
				text = temp;
			}
			else
			{
				// If it was not a keyword - it's a cell ID
				curLexem = _extract_cell_id(text);
				// If it's not a cell ID it's an error
			}
		}
		else if (isdigit(*text))
		{
			// It's a number
			curLexem = _extract_number(text);
			// If it's not it's an error
		}
		else
		{
			// It's an operation or a divider
			graphResult = _run_graph(text);
			if (_sym_keys.count(graphResult))
				curLexem = Lexem::GetLexem(_sym_keys.at(graphResult));
			else
			{
				// It's an error otherwise
				curLexem = Lexem::kLexError;
				text++;	// Increment here because graph check doesn't skip unknown symbols
				// All other cases skip to the next symbol automatically
			}		
		}
		lexEnd = text - _raw.c_str();
		curLexem.StartInd = lexStart;
		curLexem.EndInd = lexEnd;
		_parsed.push_back(curLexem);
	}
	_form_cell_selections();
}

int LexemParser::_run_graph(const char*& startChar, int startState)
{
	int retState = 0;
	while (*startChar != '\0' && startState != -1)
	{
		startState = _get_transition(startState, *startChar);
		if (startState != -1)
		{
			startChar++;
			retState = startState;
		}
	}
	return retState;
}

int LexemParser::_get_transition(const int state, const char symbol)
{
	const std::vector<int>& transitions = _states_graph[state].Transitions;
	// If any of the states this one can transition to is accesible - return it
	for (auto i = transitions.cbegin(); i != transitions.cend(); i++)
		if (_states_graph[*i].Value == symbol)
			return *i;
	return -1;
}

Lexem LexemParser::_extract_number(const char*& text)
{
	std::string number("");
	int nSize = 0;
	const char* temp = text;
	while (isdigit(*text))
	{
		nSize++;
		text++;
	}
	number.append(temp, nSize);
	if (*text == '.')	// If there's a decimal part present
	{
		number.append(text, 1);
		nSize = 0;
		text++;
		temp = text;
		while (isdigit(*text))
		{
			nSize++;
			text++;
		}
		if (!nSize)
			return Lexem(Lexem::kLexError);	// Decimal part must be specified
		number.append(temp, nSize);
	}
	// Adding it to the literals creates ExprNumber object that parses the number
	_literals->Nums.push_back(number);	
	// Lexem value contains number's index in the literals vector
	return Lexem({ kNumber, static_cast<int>(_literals->Nums.size() - 1)});
}

Lexem LexemParser::_extract_cell_id(const char*& text)
{
	std::string colPart("");
	int nSize = 0;
	const char* temp = text;
	while (isalpha(*text))
	{
		nSize++;
		text++;
	}
	if (!nSize)
	{
		return Lexem(Lexem::kLexError);
	}
	colPart.append(temp, nSize);
	for (auto i = colPart.begin(); i != colPart.end(); i++)
	{
		*i = std::toupper(*i);
	}
	nSize = 0;
	temp = text;
	std::string rowPart("");
	while (isdigit(*text))
	{
		nSize++;
		text++;
	}
	if (!nSize)
	{
		return Lexem(Lexem::kLexError);	// Both row and column must be specified
	}
	rowPart.append(temp, nSize);
	// Adding it to the literals creates ExprCell object that parses the row and col values
	_literals->Cells.push_back({ rowPart, colPart });
	// Lexem value contains cell's index in the literals vector
	return Lexem({ kCell, static_cast<int>(_literals->Cells.size() - 1) });
}

void LexemParser::_form_cell_selections()
{
	// Look for Cell1 Semicolon Cell2 series
	std::list<Lexem>::iterator next = _parsed.begin(), prev = next++, curr = next++;	// Need access to all three lexems at once
	// Initial position of "next" is where prev should point
	while (next != _parsed.end())
	{
		if (*curr == Lexem::kLexColon && *prev == Lexem::kLexCell && *next == Lexem::kLexCell)
		{
			ExprCell& c1 = _literals->Cells[prev->Value];
			ExprCell& c2 = _literals->Cells[next->Value];
			_literals->Selections.push_back({ c1.GetRow(), c1.GetColumn(), c2.GetRow(), c2.GetColumn() });
			// Insert selection lexem before first cell lexem
			_parsed.insert(prev, Lexem({ kCellSelection, static_cast<int>(_literals->Selections.size() - 1) }));
			// Erase cell:cell. Next point to the lexem after selection
			next = _parsed.erase(prev, ++next);
		}
		else
		{
			next = curr;
		}
		prev = next++;	// next points at curr now
		curr = next++;	// everyone point where they should
	}
}

