#pragma once
#include "wx\wx.h"
#include <wx/richtext/richtextctrl.h>

class FunctionsInfoFrame : public wxFrame
{
public:
	FunctionsInfoFrame(wxFrame* parent);

private:
	wxRichTextCtrl* _text_ctrl;
	void _add_list_item(const wxString& text);
	
	wxDECLARE_EVENT_TABLE();
	void _on_close(wxCloseEvent& e);
};

