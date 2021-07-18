#pragma once
#include <string>
#include <list>
#include <vector>
#include "LiteralsContainer.h"
#include <memory>
#include "Lexem.h"

// Extracts lexems from the given text and adds them to a list
class LexemParser
{
public:
	LexemParser();
	LexemParser(std::string text);

	// Sets text and starts parsing
	void SetText(std::string text);
	// Returns extracted lexems
	std::list<Lexem> GetParsed() const;
	// Returns extracted literals
	std::shared_ptr<LiteralsContainer> GetLiteralsPtr();
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
	// Container for extracted numbers and cell IDs
	std::shared_ptr<LiteralsContainer> _literals;
	// Finite-state machine used to identify func names, dividers, and operations
	static const std::vector<LexState> _states_graph;
	/* Finite-state machine is good and fast, but it's hard to modify in the future, 
	a lot of things to change and keep in mind.
	* I probably should have used some kind of string array, speed isn't much of a concern here.
	But adaptability is. Should have though of that.
	*/

	// Keys values, returned by the graph, to the respective functions
	static const std::map<int, eFunction> _func_keys;
	// Keys values, returned by the graph, to the respective single symbol lexems
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
};

