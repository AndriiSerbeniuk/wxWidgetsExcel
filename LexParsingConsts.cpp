#include "Lexem.h"
#include "GrammarChecker.h"

// Lexem consts
const Lexem Lexem::LErr = Lexem(kError, -1);
const Lexem Lexem::LAny(kAny, -1);
const Lexem Lexem::LNum(kNumber, -1);
const Lexem Lexem::LCell(kCell, -1);
const Lexem Lexem::LCellSelection{ kCellSelection, -1 };
// Functions
const Lexem Lexem::LSum{ kFunction, kSum };
const Lexem Lexem::LSqrt{ kFunction, kSqrt };
const Lexem Lexem::LPow{ kFunction, kPow };
const Lexem Lexem::LAvg{ kFunction, kAvg };
const Lexem Lexem::LMin{ kFunction, kMin };
const Lexem Lexem::LMax{ kFunction, kMax };
// Dividers
const Lexem Lexem::LSemicolon{ kDivider, kSemicolon };
const Lexem Lexem::LColon{ kDivider, kColon };
const Lexem Lexem::LRoundOpen{ kDivider, kRoundOpen };
const Lexem Lexem::LRoundClosed{ kDivider, kRoundClosed };
// Operations
const Lexem Lexem::LPlus{ kOperation, kPlus };
const Lexem Lexem::LMinus{ kOperation, kMinus };
const Lexem Lexem::LMultiply{ kOperation, kMultiply };
const Lexem Lexem::LDivide{ kOperation, kDivide };

const std::map<eLexemType, const Lexem&> Lexem::_type_lexems{
	{ kError, LErr }, { kAny, LAny }, { kNumber, LNum },
	{ kCell, LCell }, { kCellSelection, LCellSelection }
};

const std::map<eFunction, const Lexem&> Lexem::_functions{
	{ kSum, LSum }, { kSqrt, LSqrt }, { kPow, LPow },
	{ kAvg, LAvg }, { kMin, LMin }, { kMax, LMax }
};

const std::map<int, const Lexem&> Lexem::_single_sym_lexems{
	{ kSemicolon, LSemicolon }, { kColon, LColon },
	{ kRoundOpen, LRoundOpen }, { kRoundClosed, LRoundClosed },
	{ kPlus, LPlus }, { kMinus, LMinus },
	{ kMultiply, LMultiply }, { kDivide, LDivide }
};

const std::vector<Lexem> GrammarChecker::kExprInput{
	Lexem::LRoundOpen, Lexem::LMinus, Lexem::LNum, Lexem::LCell, Lexem::LPow,
	Lexem::LSqrt, Lexem::LMin, Lexem::LMax, Lexem::LAvg, Lexem::LSum
};

const std::vector<Lexem> GrammarChecker::kParamInput{
	Lexem::LRoundOpen, Lexem::LMinus, Lexem::LNum, Lexem::LCell, Lexem::LPow, Lexem::LSqrt,
	Lexem::LMin, Lexem::LMax, Lexem::LAvg, Lexem::LSum, Lexem::LCellSelection
};

const std::map<int, GrammarChecker::GState> GrammarChecker::kGrammar{
	{ 1, GState(kExprInput, 5) },
	{ 2, GState({ Lexem::LNum }, 0, true, 3) },
	{ 3, GState({ Lexem::LCell }, 0, true, 4) },
	{ 4, GState({ Lexem::LPow, Lexem::LSqrt, Lexem::LMin, Lexem::LMax, Lexem::LAvg, Lexem::LSum }, 24) },
	{ 5, GState({ Lexem::LRoundOpen }, 6, true, 9) },
	{ 6, GState(GrammarChecker::kExprInput, 5, false, 0, 7) },
	{ 7, GState({ Lexem::LRoundClosed }, 8, true) },
	{ 8, GState({ Lexem::LAny }, 13, false, 15) },
	{ 9, GState({ Lexem::LMinus }, 10, true, 11) },
	{ 10, GState(GrammarChecker::kExprInput, 5) },
	{ 11, GState({ Lexem::LNum, Lexem::LCell, Lexem::LPow, Lexem::LSqrt, Lexem::LMin,
		Lexem::LMax, Lexem::LAvg, Lexem::LSum }, 2, false, 0, 12) },
	{ 12, GState({ Lexem::LAny }, 13, false, 15) },
	{ 13, GState({ Lexem::LPlus, Lexem::LMinus, Lexem::LMultiply, Lexem::LDivide }, 16, false, 15, 14) },
	{ 14, GState(GrammarChecker::kExprInput, 5) },
	{ 15, GState({ Lexem::LAny }, 0) },
	{ 16, GState({ Lexem::LPlus }, 0, true, 17) },
	{ 17, GState({ Lexem::LMinus }, 0, true, 18) },
	{ 18, GState({ Lexem::LMultiply }, 0, true, 19) },
	{ 19, GState({ Lexem::LDivide }, 0, true) },
	{ 20, GState({ Lexem::LMin }, 0, true, 21) },
	{ 21, GState({ Lexem::LMax }, 0, true, 22) },
	{ 22, GState({ Lexem::LAvg }, 0, true, 23) },
	{ 23, GState({ Lexem::LSum }, 0, true) },
	{ 24, GState({ Lexem::LPow }, 27, false, 25) },
	{ 25, GState({ Lexem::LSqrt }, 33, false, 26) },
	{ 26, GState({ Lexem::LMin, Lexem::LMax, Lexem::LAvg, Lexem::LSum }, 37) },
	{ 27, GState({ Lexem::LPow }, 28, true) },
	{ 28, GState({ Lexem::LRoundOpen }, 29, true) },
	{ 29, GState(GrammarChecker::kExprInput, 5, false, 0, 30) },
	{ 30, GState({ Lexem::LSemicolon }, 31, true) },
	{ 31, GState(GrammarChecker::kExprInput, 5, false, 0, 32) },
	{ 32, GState({ Lexem::LRoundClosed }, 0, true) },
	{ 33, GState({ Lexem::LSqrt }, 34, true) },
	{ 34, GState({ Lexem::LRoundOpen }, 35, true) },
	{ 35, GState(GrammarChecker::kExprInput, 5, false, 0, 36) },
	{ 36, GState({ Lexem::LRoundClosed }, 0, true) },
	{ 37, GState({ Lexem::LMin, Lexem::LMax, Lexem::LAvg, Lexem::LSum }, 20, false, 0, 38) },
	{ 38, GState({ Lexem::LRoundOpen }, 39, true) },
	{ 39, GState(GrammarChecker::kParamInput, 41, false, 0, 40) },
	{ 40, GState({ Lexem::LRoundClosed }, 0, true) },
	{ 41, GState(GrammarChecker::kParamInput, 46, false, 0, 42) },
	{ 42, GState({ Lexem::LAny }, 43) },
	{ 43, GState({ Lexem::LSemicolon }, 44, true, 45) },
	{ 44, GState(GrammarChecker::kParamInput, 41) },
	{ 45, GState({ Lexem::LAny }, 0) },
	{ 46, GState({ Lexem::LCellSelection }, 0, true, 47) },
	{ 47, GState(GrammarChecker::kExprInput, 5) }
};
