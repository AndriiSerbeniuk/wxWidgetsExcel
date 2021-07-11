#include "InfiniteGrid.h"

InfiniteGrid::InfiniteGrid(wxWindow* parent, wxWindowID id) 
	: wxGrid(parent, id) {}

wxBEGIN_EVENT_TABLE(InfiniteGrid, wxGrid)
	EVT_SCROLLWIN(_on_scroll)
	EVT_SIZE(_on_resize)
wxEND_EVENT_TABLE()

void InfiniteGrid::_on_scroll(wxScrollWinEvent& e)
{
	// TODO: start resizing the grid here
	SetCellValue(0, 1, std::string(GetCellValue(0, 1) + "s"));
	e.Skip();
}

void InfiniteGrid::_on_resize(wxSizeEvent& e)
{
	SetCellValue(0, 1, std::string(GetCellValue(0, 1) + "r"));
	e.Skip();
}

