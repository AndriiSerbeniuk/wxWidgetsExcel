#include "Lexem.h"
// Lexem consts
const Lexem Lexem::kLexError{ kError, -1 };
const Lexem Lexem::kLexAny{ kAny, -1 };
const Lexem Lexem::kLexNum{ kNumber, -1 };
const Lexem Lexem::kLexCell{ kCell, -1 };
const Lexem Lexem::kLexCellSelection{ kCellSelection, -1 };
// Functions
const Lexem Lexem::kLexSum{ kFunction, kSum };
const Lexem Lexem::kLexSqrt{ kFunction, kSqrt };
const Lexem Lexem::kLexPow{ kFunction, kPow };
const Lexem Lexem::kLexAvg{ kFunction, kAvg };
const Lexem Lexem::kLexMin{ kFunction, kMin };
const Lexem Lexem::kLexMax{ kFunction, kMax };
// Dividers
const Lexem Lexem::kLexSemicolon{ kDivider, kSemicolon };
const Lexem Lexem::kLexColon{ kDivider, kColon };
const Lexem Lexem::kLexRoundOpen{ kDivider, kRoundOpen };
const Lexem Lexem::kLexRoundClosed{ kDivider, kRoundClosed };
// Operations
const Lexem Lexem::kLexPlus{ kOperation, kPlus };
const Lexem Lexem::kLexMinus{ kOperation, kMinus };
const Lexem Lexem::kLexMultiply{ kOperation, kMultiply };
const Lexem Lexem::kLexDivide{ kOperation, kDivide };

const std::map<eLexemType, const Lexem&> Lexem::_type_lexems{
	{ kError, kLexError }, { kAny, kLexAny }, { kNumber, kLexNum },
	{ kCell, kLexCell }, { kCellSelection, kLexCellSelection }
};

const std::map<eFunction, const Lexem&> Lexem::_functions{
	{ kSum, kLexSum }, { kSqrt, kLexSqrt }, { kPow, kLexPow },
	{ kAvg, kLexAvg }, { kMin, kLexMin }, { kMax, kLexMax }
};

const std::map<int, const Lexem&> Lexem::_single_sym_lexems{
	{ kSemicolon, kLexSemicolon }, { kColon, kLexColon },
	{ kRoundOpen, kLexRoundOpen }, { kRoundClosed, kLexRoundClosed },
	{ kPlus, kLexPlus }, { kMinus, kLexMinus },
	{ kMultiply, kLexMultiply }, { kDivide, kLexDivide }
};

Lexem::Lexem() : Type(kAny), Value(-1), StartInd(-1), EndInd(-1) {}

Lexem::Lexem(eLexemType type, int value) : Type(type), Value(value), StartInd(-1), EndInd(-1) {}

Lexem Lexem::GetLexem(eLexemType type)
{
	if (_type_lexems.count(type))
		return _type_lexems.at(type);
	else
		return kLexError;
}

Lexem Lexem::GetLexem(eFunction function)
{
	if (_functions.count(function))
		return _functions.at(function);
	else
		return kLexError;
}

Lexem Lexem::GetLexem(eDivider divider)
{
	if (_single_sym_lexems.count(divider))
		return _single_sym_lexems.at(divider);
	else
		return kLexError;
}

Lexem Lexem::GetLexem(eOperation operation)
{
	if (_single_sym_lexems.count(operation))
		return _single_sym_lexems.at(operation);
	else
		return kLexError;
}

Lexem Lexem::GetLexem(int lexem)
{
	Lexem retLex = GetLexem((eDivider)lexem);
	if (retLex == kLexError)
	{
		retLex = GetLexem((eOperation)lexem);
	}
	return retLex;
}

bool Lexem::operator==(Lexem other)
{
	// For literals only their types are checked
	/*if (Type == kNumber || Type == kCell || Type == kCellSelection
		|| other.Type == kNumber || other.Type == kCell
		|| other.Type == kCellSelection)
		return Type == other.Type;
	else
		return Type == other.Type && Value == other.Value;*/
	return Type == kNumber && other.Type == kNumber ||
		Type == kCell && other.Type == kCell ||
		Type == kCellSelection && other.Type == kCellSelection ||
		Type == other.Type && Value == other.Value;
}

bool Lexem::operator!=(Lexem other)
{
	return !(*this == other);
}

