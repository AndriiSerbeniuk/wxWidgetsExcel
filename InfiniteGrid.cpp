#include "InfiniteGrid.h"

InfiniteGrid::InfiniteGrid(wxWindow* parent, wxWindowID id, wxGridSelectionModes selmode)
	: wxGrid(parent, id), _selected_cell(0, 0), _data_size(0, 0), 
	_resizing(false), _data_rows(), _data_cols()
{
	CreateGrid(1, 1, selmode);
}

wxGridCellCoords InfiniteGrid::GetSelectedCell() const
{
	return _selected_cell;
}

void InfiniteGrid::SelectCell(const wxGridCellCoords& cell)
{
	if (_resizing)	// Resizing calls SelectCell for some reason and could cause stack overflow
		return;
	//BeginBatch();
	_create_cell(cell.GetRow(), cell.GetCol());
	SetCellBackgroundColour(_selected_cell.GetRow(), _selected_cell.GetCol(), GetDefaultCellBackgroundColour());
	_selected_cell.Set(cell.GetRow(), cell.GetCol());		// Save the selected cell
	SetCellBackgroundColour(cell.GetRow(), cell.GetCol(), wxColour("light blue"));
	m_currentCellCoords = cell;
	//SetCurrentCell(cell);
	// Minimal amounts here are in case there are no cell after the edge cell,
	// so that the grid can be consistently resized with arrow keys
	MakeCellVisible(cell);
	//ResizeData(2, 2);
	Refresh();
	//EndBatch();
}

bool InfiniteGrid::CreateGrid(int numRows, int numCols, wxGridSelectionModes selmode) {
	_data_size.Set(numRows, numCols);
	return wxGrid::CreateGrid(numRows, numCols, selmode);
}

void InfiniteGrid::ResizeGrid(int nAddMinRows, int nAddMinCols)
{
	//BeginBatch();
	_resizing = true;
	int firstVisibleRow = GetFirstFullyVisibleRow(), firstVisibleColumn = GetFirstFullyVisibleColumn();
	_resize_rows(firstVisibleRow, firstVisibleColumn, nAddMinRows);
	_resize_cols(firstVisibleRow, firstVisibleColumn, nAddMinCols);
	_resizing = false;
	//EndBatch();
}

void InfiniteGrid::ResizeData(int row, int col, wxString data)
{
	_resize_data(row, col, data.empty());
}

void InfiniteGrid::SetCellValue(const wxGridCellCoords& cell, const wxString& s)
{
	SetCellValue(cell.GetRow(), cell.GetCol(), s);
}

void InfiniteGrid::SetCellValue(int row, int col, const wxString& s)
{
	bool added = _create_cell(row, col);
	wxGrid::SetCellValue(row, col, s);
	if (added)
		_resize_data(row, col, s.empty());
}

wxString InfiniteGrid::GetCellValue(const wxGridCellCoords& cell) const
{
	return GetCellValue(cell.GetRow(), cell.GetCol());
}

wxString InfiniteGrid::GetCellValue(int row, int col) const
{
	if (m_numRows > row && m_numCols > col)
		return wxGrid::GetCellValue(row, col);
	else
		return "";
}

void InfiniteGrid::MakeCellVisible(const wxGridCellCoords& cell)
{
	MakeCellVisible(cell.GetRow(), cell.GetCol());
}

void InfiniteGrid::MakeCellVisible(int row, int col)
{
	wxGrid::MakeCellVisible(row, col);
	ResizeGrid(5, 5);
}

bool InfiniteGrid::_create_cell(int row, int col)
{
	bool added = false;
	if (m_numRows <= row)
	{
		int nRow = row - m_numRows + 1;
		AppendRows(nRow);
		added = true;
	}
	if (m_numCols <= col)
	{
		int nCol = col - m_numCols + 1;
		AppendCols(nCol);
		added = true;
	}
	return added;
}

void InfiniteGrid::_resize_rows(int firstVisibleRow, int firstVisibleColumn, int nAddMin)
{
	int lv = firstVisibleRow;
	for (; lv < m_numRows && IsVisible(lv, firstVisibleColumn, false); lv++);
	if (lv)
		lv--;
	if (lv >= m_numRows - 3)	// Expand to the bottom
	{
		int nAdd = 0;	// Amount of default cell that can fit in the free space
		for (int i = firstVisibleRow; i <= lv; i++)
		{
			nAdd += GetRowSize(i);
		}
		nAdd = (GetVirtualSize().GetY() - nAdd) / GetDefaultRowSize() + nAddMin;

		if (nAdd > 0)
		{
			AppendRows(nAdd);
		}
	}
	else if (IsVisible(_data_size.y - 1, _data_size.x - 1, false) || firstVisibleRow > _data_size.y - 1)	// Shrink to the top
	{
		// Only blank, not visible cells are removed
		// Here we count the amount of visible cells to get index of the first non-visible cell
		int visibleCount = 0,	
			startIndex = _data_size.GetHeight() > firstVisibleRow ? 
			_data_size.GetHeight() : firstVisibleRow;
		for (int i = startIndex;
			IsVisible(i, firstVisibleColumn, false); i++)
		{
			visibleCount++;
		}
		int deleteIndex = startIndex + visibleCount, delCount = m_numRows - deleteIndex;
		if (delCount > 0)
		{
			DeleteRows(deleteIndex, delCount);
		}
	}
}

void InfiniteGrid::_resize_cols(int firstVisibleRow, int firstVisibleColumn, int nAddMin)
{
	int lv = firstVisibleColumn;
	for (; lv < m_numCols && IsVisible(firstVisibleRow, lv ,false); lv++);
	if (lv)
		lv--;
	if (lv >= m_numCols - 3)	// Expand to the right
	{
		int nAdd = 0;	// Amount of default cell that can fit in the free space
		for (int i = firstVisibleColumn; i <= lv; i++)
		{
			nAdd += GetColSize(i);
		}
		nAdd = (GetVirtualSize().GetX() - nAdd) / GetDefaultColSize() + nAddMin;

		if (nAdd > 0)
		{
			AppendCols(nAdd);
		}

	}
	else if (IsVisible(_data_size.y - 1, _data_size.x - 1) || firstVisibleColumn > _data_size.x - 1)	// Shrink to the left
	{
		// Only blank, not visible cells are removed
		// Here we count the amount of visible cells to get index of the first non-visible cell
		int visibleCount = 0,
			startIndex = _data_size.GetWidth() > firstVisibleColumn ? 
			_data_size.GetWidth() : firstVisibleColumn;
		for (int i = startIndex;
			IsVisible(firstVisibleRow, i, false); i++)
		{
			visibleCount++;
		}
		int deleteIndex = startIndex + visibleCount, delCount = m_numCols - deleteIndex;
		if (delCount > 0)
		{
			DeleteCols(deleteIndex, delCount);
		}
	}
}

wxBEGIN_EVENT_TABLE(InfiniteGrid, wxGrid)
	EVT_SCROLLWIN(_on_scroll)
	EVT_SIZE(_on_resize)
	EVT_GRID_CELL_LEFT_CLICK(_on_cell_clicked)
	EVT_GRID_CELL_CHANGING(_on_data_entered)
wxEND_EVENT_TABLE()

void InfiniteGrid::_on_scroll(wxScrollWinEvent& e)
{
	ResizeGrid();
	e.Skip();
}

void InfiniteGrid::_on_resize(wxSizeEvent& e)
{
	ResizeGrid();
	e.Skip();
}

void InfiniteGrid::_on_cell_clicked(wxGridEvent& e)
{
	SelectCell(wxGridCellCoords(e.GetRow(), e.GetCol()));
	e.Skip();
}

void InfiniteGrid::_on_data_entered(wxGridEvent& e)
{
	_resize_data(e.GetRow(), e.GetCol(), e.GetString().IsEmpty());
}

void InfiniteGrid::_resize_data(int row, int col, bool stringEmpty)
{
	bool rowExists = _data_rows.count(row) > 0 ? true : false;
	bool colExists = _data_cols.count(col) > 0 ? true : false;
	// If new data is added - add it to the maps.
	// If old data was deleted - remove the cells from the maps.
	// If a row or a column has > 1 cells with data its counter increases.
	// Rows
	if (!stringEmpty)
	{
		if (!rowExists)
		{
			_data_rows.insert(std::pair<int, int>(row, 1));
		}
		else
		{
			_data_rows[row]++;
		}
		if (row > _data_size.GetHeight() - 1)
		{
			_data_size.SetHeight(row + 1);
		}
	}
	else if (rowExists)
	{
		_data_rows[row]--;
		if (_data_rows[row] == 0)
		{
			_data_rows.erase(row);
			if (_data_rows.size())
				_data_size.SetHeight(_data_rows.rbegin()->first + 1);
			else
				_data_size.SetHeight(1);
		}
	}
	// Columns
	if (!stringEmpty)
	{
		if (!colExists)
		{
			_data_cols.insert(std::pair<int, int>(col, 1));
		}
		else
		{
			_data_cols[col]++;
		}
		if (col > _data_size.GetWidth() - 1)
		{
			_data_size.SetWidth(col + 1);
		}
	}
	else if (colExists)
	{
		_data_cols[col]--;
		if (_data_cols[col] == 0)
		{
			_data_cols.erase(col);

			if (_data_cols.size())
				_data_size.SetWidth(_data_cols.rbegin()->first + 1);
			else
				_data_size.SetWidth(1);
		}
	}
}

