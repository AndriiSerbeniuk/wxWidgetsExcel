#pragma once
#include <list>
#include "Lexem.h"
#include "wx/wx.h"

class LexemHighlighter
{
public:
	LexemHighlighter(wxTextCtrl* txtCtrl);
	void Update(const std::list<Lexem>& lexems);
	bool IsActive() const;

private:
	wxTextCtrl* _tCtrl;
	bool _active;

	static const std::map<eLexemType, const wxColour> kLexColours;
};

