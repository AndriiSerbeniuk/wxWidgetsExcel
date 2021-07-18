#pragma once
#include <map>
// Types of lexems
enum eLexemType { kAny = -2, kError, kFunction, kDivider, kNumber, kCell, kOperation };
// Kinds of function names
enum eFunction { kSum, kSqrt, kPow, kAvg, kMin, kMax };
// Kinds of dividers
enum eDivider { kSemicolon = ';', kColon = ':', kRoundOpen = '(', kRoundClosed = ')' };
// Kinds of Operations
enum eOperation { kPlus = '+', kMinus = '-', kMultiply = '*', kDivide = '/' };

// A basic part of a function
class Lexem
{
public:
	// Lexem type
	eLexemType Type;
	// It's value in the type
	int Value;
	int StartInd;	// dunno 'bout this one
	int EndInd;		// and this one

	Lexem();
	Lexem(eLexemType type, int value);

	// Lexem consts

	static const Lexem kLexError;
	static const Lexem kLexAny;
	static const Lexem kLexNum;
	static const Lexem kLexCell;

	// Functions

	static const Lexem kLexSum;
	static const Lexem kLexSqrt;
	static const Lexem kLexPow;
	static const Lexem kLexAvg;
	static const Lexem kLexMin;
	static const Lexem kLexMax;

	// Dividers

	static const Lexem kLexSemicolon;
	static const Lexem kLexColon;
	static const Lexem kLexRoundOpen;
	static const Lexem kLexRoundClosed;

	// Operations

	static const Lexem kLexPlus;
	static const Lexem kLexMinus;
	static const Lexem kLexMultiply;
	static const Lexem kLexDivide;

	// Returns a const Lexem based on its type
	static Lexem GetLexem(eLexemType type);
	// Returns a const Lexem based on its kind
	static Lexem GetLexem(eFunction function);
	// Returns a const Lexem based on its kind
	static Lexem GetLexem(eDivider divider);
	// Returns a const Lexem based on its kind
	static Lexem GetLexem(eOperation operation);
	// Returns a const Lexem based on its kind. This one is used for dividers and operations combined
	static Lexem GetLexem(int lexem);

	bool operator == (Lexem other);
	bool operator != (Lexem other);
private:
	// Blank lexems of some types
	static const std::map<eLexemType, const Lexem&> _type_lexems;
	// Lexems of functions
	static const std::map<eFunction, const Lexem&> _functions;
	// Combined storage of lexems of dividers and operations. They are combined because they require the same treatment
	static const std::map<int, const Lexem&> _single_sym_lexems;
};

