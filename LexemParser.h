#pragma once
#include <string>
#include <vector>
#include <list>
#include "LiteralsContainer.h"
#include "Lexem.h"

// Extracts lexems from the given text and adds them to a vector
class LexemParser
{
public:
	LexemParser();
	LexemParser(std::string text);

	// Sets text and starts parsing
	void SetText(std::string text);
	// Get text
	std::string GetText() const;
	// Returns extracted lexems
	std::list<Lexem> GetParsed() const;
	// Returns extracted literals
	LiteralsContainer& GetLiterals();
	// Extracts cell id from given text into an ExprCell object.
	static ExprCell ExtractCellId(const char* text);

private:
	// State of the finite state machine
	struct LexState
	{
		char Value;	// Value to get to the state
		std::vector<int> Transitions;	// Transitions to other states
	};
	// Given text
	std::string _raw;
	// Extracted lexems
	std::list<Lexem> _parsed;
	// Container for extracted numbers, cell IDs, and cell selections
	LiteralsContainer _literals;
	// Finite-state machine used to identify func names, dividers, and operations
	static const std::vector<LexState> _states_graph;
	/* Finite-state machine is good and fast, but it's hard to modify in the future, 
	a lot of things to change and keep in mind.
	* I probably should have used some kind of string array, speed isn't much of a concern here.
	But adaptability is. Should have though of that.
	*/

	// Keys values returned by the graph, to the respective functions
	static const std::map<int, eFunction> _func_keys;
	// Keys values returned by the graph, to the respective single symbol lexems
	static const std::map<int, int> _sym_keys;

	// Parses text into a list of lexems
	void _parse();
	// Starts checking the text with the graph
	int _run_graph(const char*& startChar, int startState = 0);
	// Get available transition from current graph state to the next. Return -1 if the are none
	int _get_transition(const int state, const char symbol);
	// Extracts number from text and adds it to the literals
	Lexem _extract_number(const char*& text);
	// Extracts cell ID from text and adds it to the literals
	Lexem _extract_cell_id(const char*& text);
	// Extracts cell ID from text and advances the pointer
	static ExprCell _extract_cell_id_modifptr(const char*& text);
	// Forms cell:cell series into kCellSelection lexems
	void _form_cell_selections();
};

