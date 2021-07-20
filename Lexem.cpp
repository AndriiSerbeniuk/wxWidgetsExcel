#include "Lexem.h"

Lexem::Lexem() : Type(kAny), Value(-1), StartInd(-1), EndInd(-1) {}

Lexem::Lexem(eLexemType type, int value) : Type(type), Value(value), StartInd(-1), EndInd(-1) {}

Lexem::Lexem(const Lexem& other)
{
	Type = other.Type;
	Value = other.Value;
	StartInd = other.StartInd;
	EndInd = other.EndInd;
}

Lexem Lexem::GetLexem(eLexemType type)
{
	if (_type_lexems.count(type))
		return _type_lexems.at(type);
	else
		return LErr;
}

Lexem Lexem::GetLexem(eFunction function)
{
	if (_functions.count(function))
		return _functions.at(function);
	else
		return LErr;
}

Lexem Lexem::GetLexem(eDivider divider)
{
	if (_single_sym_lexems.count(divider))
		return _single_sym_lexems.at(divider);
	else
		return LErr;
}

Lexem Lexem::GetLexem(eOperation operation)
{
	if (_single_sym_lexems.count(operation))
		return _single_sym_lexems.at(operation);
	else
		return LErr;
}

Lexem Lexem::GetLexem(int lexem)
{
	Lexem retLex = GetLexem((eDivider)lexem);
	if (retLex == LErr)
	{
		retLex = GetLexem((eOperation)lexem);
	}
	return retLex;
}

bool Lexem::operator==(const Lexem& other)
{
	// For literals only their types are checked
	// Lexem of type kAny is equal to any other lexem
	return Type == kAny || other.Type == kAny ||
		Type == kNumber && other.Type == kNumber ||
		Type == kCell && other.Type == kCell ||
		Type == kCellSelection && other.Type == kCellSelection ||
		Type == other.Type && Value == other.Value;
}

bool Lexem::operator!=(const Lexem& other)
{
	return !(*this == other);
}

bool operator==(const Lexem& l1, const Lexem& l2)
{
	return l1.Type == kAny || l2.Type == kAny ||
		l1.Type == kNumber && l2.Type == kNumber ||
		l1.Type == kCell && l2.Type == kCell ||
		l1.Type == kCellSelection && l2.Type == kCellSelection ||
		l1.Type == l2.Type && l1.Value == l2.Value;
}
