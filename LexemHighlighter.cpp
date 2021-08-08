#include "LexemHighlighter.h"

const std::map<eLexemType, const wxColour> LexemHighlighter::kLexColours
{
	{ kError, wxColour(255, 0, 0) },			// Red
	{ kOperation, wxColour(64, 64, 64)},		// Dark gray
	{ kDivider, wxColour(0, 0, 0)},				// Black
	{ kFunction, wxColour(0, 0, 153)},			// Dark blue
	{ kNumber, wxColour(76, 0, 153) },			// Purple with more blue
	{ kCell, wxColour(153, 0, 153) },			// Purple
	{ kCellSelection, wxColour(153, 0, 76) }	// Dark pink
};

LexemHighlighter::LexemHighlighter(wxTextCtrl* txtCtrl)
	: _tCtrl(txtCtrl) {}

void LexemHighlighter::Update(const std::list<Lexem>& lexems)
{
	_active = true;
	wxTextAttr style = _tCtrl->GetDefaultStyle();
	// Reset previous styling
	_tCtrl->SetStyle(0, _tCtrl->GetValue().size() - 1, style);

	for (const Lexem& l : lexems)
	{
		style.SetTextColour(kLexColours.at(l.Type));
		_tCtrl->SetStyle(l.StartInd, l.EndInd, style);
	}
	_active = false;
}

bool LexemHighlighter::IsActive() const
{
	return _active;
}
