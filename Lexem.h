#pragma once
#include <map>
// Types of lexems
enum eLexemType { kAny = -2, kError, kFunction, kDivider, kNumber, kCell, kCellSelection, kOperation };
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
	// Starting index of the lexem in the string. [StartInd;EndInd)
	int StartInd;
	// Index after the end index of the lexem in the string. [StartInd;EndInd)
	int EndInd;

	// Lexem consts

	static const Lexem LErr;	// Error
	static const Lexem LAny;	// Equal to any other lexem, to error too
	static const Lexem LNum;
	static const Lexem LCell;
	static const Lexem LCellSelection;

	// Functions

	static const Lexem LSum;
	static const Lexem LSqrt;
	static const Lexem LPow;
	static const Lexem LAvg;
	static const Lexem LMin;
	static const Lexem LMax;

	// Dividers

	static const Lexem LSemicolon;
	static const Lexem LColon;
	static const Lexem LRoundOpen;
	static const Lexem LRoundClosed;

	// Operations

	static const Lexem LPlus;
	static const Lexem LMinus;
	static const Lexem LMultiply;
	static const Lexem LDivide;

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

	Lexem();
	Lexem(eLexemType type, int value);
	Lexem(const Lexem& other);

	bool operator == (const Lexem& other);
	bool operator != (const Lexem& other);
private:
	// Blank lexems of some types
	static const std::map<eLexemType, const Lexem&> _type_lexems;
	// Lexems of functions
	static const std::map<eFunction, const Lexem&> _functions;
	// Combined storage of lexems of dividers and operations. They are combined because they require the same treatment
	static const std::map<int, const Lexem&> _single_sym_lexems;
};

bool operator == (const Lexem& l1, const Lexem& l2);