#include "FunctionsInfoFrame.h"

FunctionsInfoFrame::FunctionsInfoFrame(wxFrame* parent)
	: wxFrame(parent, wxID_ANY, "Functions info", parent->GetPosition(), wxDefaultSize, 
		wxFRAME_FLOAT_ON_PARENT | wxCLOSE_BOX | wxRESIZE_BORDER | wxCAPTION | wxCLIP_CHILDREN)
{
	SetBackgroundColour(wxColour(255, 255, 255, 255));
	_text_ctrl = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
		wxDefaultSize, wxRE_MULTILINE | wxRE_READONLY);

	wxFont font(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	wxRichTextCtrl& t = *_text_ctrl;	// For easier access
	t.SetFont(font);
	t.BeginParagraphSpacing(24, 12);
	t.WriteText("Functions must start with the \'=\' sign.\n");
	t.BeginParagraphSpacing(0, 12);
	t.WriteText("Placing any symbols before it will not count as a function.");
	t.EndParagraphSpacing();
	t.BeginParagraphSpacing(24, 12);
	t.Newline();
	t.EndParagraphSpacing();
	t.BeginParagraphSpacing(0, 12);
	
	t.WriteText("The expression can be made of:");
	t.Newline();
	t.BeginFontSize(10);
	_add_list_item("numbers, grid cells. Grid cells can be used to input the numbers inside them into the expression. To reference a cell - type its column and row. Example: A1, L4;");
	_add_list_item("basic arithmetic operators, such as: + , -, *, / ;");
	_add_list_item("parentheses;");
	_add_list_item("predefined functions.");
	t.EndFontSize();
	t.Newline();
	t.WriteText("Available functions:");
	t.Newline();
	t.BeginFontSize(10);
	_add_list_item("avg(arg1; ...; argN)");
	_add_list_item("sum(arg1; ...; argN)");
	_add_list_item("sqrt(num)");
	_add_list_item("pow(num; pow)");
	_add_list_item("min(arg1; ...; argN)");
	_add_list_item("max(arg1; ...; argN)");
	t.EndFontSize();
	t.Newline();
	t.WriteText("Functions such as avg, sum, min, max support selections of cells as their arguments.\n");
	t.WriteText("To reference a selection of cells - type two cells with a colon in between. Example: B1:D5.");
	t.Newline();
	t.EndParagraphSpacing();
}

void FunctionsInfoFrame::_add_list_item(const wxString& text)
{
	_text_ctrl->BeginSymbolBullet('-', 100, 60);
	_text_ctrl->WriteText(text);
	_text_ctrl->Newline();
	_text_ctrl->EndSymbolBullet();
}

wxBEGIN_EVENT_TABLE(FunctionsInfoFrame, wxFrame)
EVT_CLOSE(_on_close)
wxEND_EVENT_TABLE()

void FunctionsInfoFrame::_on_close(wxCloseEvent& e)
{
	// Parent window is responsible for closing this frame. It can't close itself.
	Show(false);
	e.Veto();
}