#pragma once
#include "wx\wx.h"
#include "wx\grid.h"

class InfiniteGrid : public wxGrid
{
public:
	InfiniteGrid(wxWindow* parent, wxWindowID id);

private:
	wxDECLARE_EVENT_TABLE();

	void _on_scroll(wxScrollWinEvent& e);
	void _on_resize(wxSizeEvent& e);
};

