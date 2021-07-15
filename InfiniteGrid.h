#pragma once
#include "wx\wx.h"
#include "wx\grid.h"
#include <map>

// wxGrid that resizes itself automaticaly, so that it can be scrolled infinitely
class InfiniteGrid : public wxGrid	
{
public:
	// Calls CreateGrid() automaticaly
	InfiniteGrid(wxWindow* parent, wxWindowID id, wxGridSelectionModes selmode = wxGridSelectCells);

	wxGridCellCoords GetSelectedCell() const;	// Returns index of the selected cell
	// Makes a cell selected. Starts grid resizing in case the selected cell is out of bounds
	void SelectCell(wxGridCellCoords cell);		
	void ResizeData(int nAddMinRows = 0, int nAddMinCols = 0);

private:
	// Overriden and called internally
	bool CreateGrid(int numRows, int numCols, wxGridSelectionModes 	selmode = wxGridSelectCells);
	wxGridCellCoords _selected_cell;	// Coordinate of the current selected cell.
	wxGridCellCoords _last_visible;		// Right-bottommost visible cell.
	wxSize _data_size;	// Rectangular area that contains the data.
	bool _resizing;		// The grid's row and column counts are being changed.
	std::map<int, int> _data_rows;	// Rows that have data cells. Keys are row indices, values are amount of cells.
	std::map<int, int> _data_cols;	// Columns that have data cells. Keys are column indices, values are amount of cells.
	
	// Change amount of rows in the grid based on what is currently visible.
	void _resize_rows(int firstVisibleRow, int firstVisibleColumn, int nAddMin = 0);
	// Change amount of columns in the grid based on what is currently visible.
	void _resize_cols(int firstVisibleRow, int firstVisibleColumn, int nAddMin = 0);

	wxDECLARE_EVENT_TABLE();

	// Event handler for scrolling. Starts row and column resizing
	void _on_scroll(wxScrollWinEvent& e);
	// Event handler for window resizing. Starts row and column resizing
	void _on_resize(wxSizeEvent& e);
	// Event handler for cell left clicking. Used for selecting
	void _on_cell_clicked(wxGridEvent& e);
	// Event handler for data entry. Resizes the data bounds
	void _on_data_entered(wxGridEvent& e);
};

