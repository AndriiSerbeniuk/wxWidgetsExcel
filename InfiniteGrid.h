#pragma once
#include "wx\wx.h"
#include "wx\grid.h"
#include <map>
#include <set>

// wxGrid that resizes itself automaticaly, so that it can be scrolled infinitely
class InfiniteGrid : public wxGrid	
{
public:
	// Calls CreateGrid() automaticaly
	InfiniteGrid(wxWindow* parent, wxWindowID id, wxGridSelectionModes selmode = wxGridSelectCells);

	wxGridCellCoords GetSelectedCell() const;	// Returns index of the selected cell
	// Makes a cell selected. Starts grid resizing in case the selected cell is out of bounds
	void SelectCell(const wxGridCellCoords& cell);		
	// Regulates amount of blank cells, appending or deleting them when necessary
	void ResizeGrid(int nAddMinRows = 0, int nAddMinCols = 0);
	void ResizeData(int row, int col, wxString data);
	void SetCellValue(const wxGridCellCoords& cell, const wxString& s);
	void SetCellValue(int row, int col, const wxString& s);
	wxString GetCellValue(const wxGridCellCoords& cell) const;
	wxString GetCellValue(int row, int col) const;
	void MakeCellVisible(const wxGridCellCoords& cell);
	void MakeCellVisible(int row, int col);
	void ClearGrid();
	// Returns width of grid area that contains data, starting at (0;0)
	int GetDataWidth() const;
	// Returns height of grid area that contains data, starting at (0;0)
	int GetDataHeight() const;

private:
	// Overriden and called internally
	bool CreateGrid(int numRows, int numCols, wxGridSelectionModes 	selmode = wxGridSelectCells);
	wxGridCellCoords _selected_cell;	// Coordinate of the current selected cell.
	wxSize _data_size;	// Rectangular area that contains the data.
	bool _resizing;		// The grid's row and column counts are being changed.
	std::map<int, std::set<int>> _data_cells;
	
	// Appends rows and columns os that given cell starts to exist
	bool _create_cell(int row, int col);
	// Change amount of rows in the grid based on what is currently visible.
	void _resize_rows(int firstVisibleRow, int firstVisibleColumn, int nAddMin = 0);
	// Change amount of columns in the grid based on what is currently visible.
	void _resize_cols(int firstVisibleRow, int firstVisibleColumn, int nAddMin = 0);
	// Resizes data bounds
	void _resize_data(int row, int col, bool stringEmpty);

	wxDECLARE_EVENT_TABLE();

	// Event handler for scrolling. Starts row and column resizing
	void _on_scroll(wxScrollWinEvent& e);
	// Event handler for window resizing. Starts row and column resizing
	void _on_resize(wxSizeEvent& e);
	// Event handler for cell left clicking. Used for selecting
	void _on_cell_clicked(wxGridEvent& e);
	// Event handler for data entry. Resizes data bounds
	void _on_data_entered(wxGridEvent& e);
};

