#include "CellsObserver.h"

CellsObserver::CellsObserver(wxGrid* grid) : _grid(grid)
{}

CellsObserver::~CellsObserver()
{
	_clear_funcs();
}

void CellsObserver::_add_cell(const wxGridCellCoords& cell)
{
	int c = cell.GetCol(), r = cell.GetRow();
	if (!_cells_funcs.count(r))
		_cells_funcs.insert({ r, std::map<int, CellFunction*>() });
	CellFunction* func = new CellFunction(cell, _grid);
	_cells_funcs[r].insert({ c, func });	
	// If the cell is a function - write down its dependencies
	_add_dependencies(cell);
	// Check if new dependencies cause cycling
	_check_cycles(cell);
}

void CellsObserver::_remove_cell(const wxGridCellCoords& cell)
{
	// Remove dependencies of this function
	const std::list<wxGridCellCoords>& funcDeps = 
		_cells_funcs[cell.GetRow()][cell.GetCol()]->GetDependencies();
	// A cell can't cause cycles if it doesn't exist
	_unmark_cyclic(cell);
	for (const wxGridCellCoords& depCoords : funcDeps)
	{
		_cells_dependencies[depCoords.GetRow()][depCoords.GetCol()].remove(cell);
		// If the cell doesn't have any dependancies anymore - remove it
		if (!_cells_dependencies[depCoords.GetRow()][depCoords.GetCol()].size())
		{
			_cells_dependencies[depCoords.GetRow()].erase(depCoords.GetCol());
			// If a row doesn't have cells with dependencies - remove it
			if (!_cells_dependencies[depCoords.GetRow()].size())
				_cells_dependencies.erase(depCoords.GetRow());
		}
		_check_cycles(depCoords);
	}
	// Remove the function
	delete _cells_funcs[cell.GetRow()][cell.GetCol()];
	_cells_funcs[cell.GetRow()].erase(cell.GetCol());
	if (!_cells_funcs[cell.GetRow()].size())
		_cells_funcs.erase(cell.GetRow());
}

void CellsObserver::_clear_funcs()
{
	for (auto r : _cells_funcs)
	{
		for (auto c : r.second)
			delete c.second;
		r.second.clear();
	}
	_cells_funcs.clear();
}

void CellsObserver::Update(const wxGridCellCoords& cell)
{
	const wxString& cellText = _grid->GetCellValue(cell);
	if (cellText.size() && cellText[0] == '=')
	{
		if (IsCellFunction(cell))
			// To reset its dependancies
			_remove_cell(cell);
		_add_cell(cell);		
		int c = cell.GetCol(), r = cell.GetRow();
		if (!_is_marked_cyclic(cell))
		{
			_cells_funcs[r][c]->Update();
			_grid->SetCellValue(cell, _cells_funcs[r][c]->GetResult());
		}
	}
	else
	{
		if (IsCellFunction(cell))
			_remove_cell(cell);
	}
		_update_dependencies(cell);
}

void CellsObserver::Clear()
{
	_clear_funcs();
	_cells_dependencies.clear();
	_cyclic_cells.clear();
}

std::string CellsObserver::GetValue(const wxGridCellCoords& cell) const
{
	return _cells_funcs.at(cell.GetRow()).at(cell.GetCol())->GetResult();
}

std::string CellsObserver::GetRaw(const wxGridCellCoords& cell) const
{
	return _cells_funcs.at(cell.GetRow()).at(cell.GetCol())->GetFuncText();
}

std::list<Lexem> CellsObserver::GetLexems(const wxGridCellCoords& cell) const
{
	if (IsCellFunction(cell))
		return _cells_funcs.at(cell.GetRow()).at(cell.GetCol())->GetLexems();
	else
		return std::list<Lexem>();
	
}

void CellsObserver::_add_dependencies(const wxGridCellCoords& cell)
{
	int r = cell.GetRow(), c = cell.GetCol();
	const std::list<wxGridCellCoords>& funcDeps = _cells_funcs[r][c]->GetDependencies();
	int depRow = 0, depCol = 0;
	// Iterate through cells that the func is dependent on. 
	for (auto i = funcDeps.cbegin(); i != funcDeps.cend(); i++)
	{
		depRow = i->GetRow();
		depCol = i->GetCol();

		_cells_dependencies.insert({ depRow, std::map<int, std::list<wxGridCellCoords>>() });
		_cells_dependencies[depRow].insert({ depCol, std::list<wxGridCellCoords>() });
		if (!_has_dependency(*i, { r,c }))
		{
			_cells_dependencies[depRow][depCol].push_back({ r,c });
		}
	}
}

bool CellsObserver::_has_dependency(const wxGridCellCoords& cell, const wxGridCellCoords& dependent)
{
	std::list<wxGridCellCoords>& funcs = _cells_dependencies[cell.GetRow()][cell.GetCol()];
	for (auto iFunc : funcs)
	{
		if (iFunc == dependent)
			return true;
	}
	return false;
}

bool CellsObserver::_has_dependencies(const wxGridCellCoords& cell)
{
	int r = cell.GetRow(), c = cell.GetCol();
	return _cells_dependencies.count(r) && _cells_dependencies[r].count(c)
		&& _cells_dependencies[r][c].size();
		
}

void CellsObserver::_update_dependencies(const wxGridCellCoords& cell)
{
	int r = cell.GetRow(), c = cell.GetCol();
	if (!_has_dependencies(cell))
		return;
	std::list<wxGridCellCoords>& dependent = _cells_dependencies[r][c];
	int funcRow = 0, funcCol = 0;
	for (wxGridCellCoords func : dependent)
	{
		funcRow = func.GetRow();
		funcCol = func.GetCol();
		if (!_is_marked_cyclic(func))
		{
			_cells_funcs[funcRow][funcCol]->Calculate();
			_grid->SetCellValue(func, _cells_funcs[funcRow][funcCol]->GetResult());
			// Update dependencies up the tree
			_update_dependencies({ funcRow, funcCol });
		}
	}
}

void CellsObserver::_check_cycles(const wxGridCellCoords& initialCell)
{
	std::list<wxGridCellCoords> traversed;
	_check_cycles_next(initialCell, traversed);	
}

void CellsObserver::_check_cycles_next(
	const wxGridCellCoords& cell, 
	std::list<wxGridCellCoords> traversed)
{
	int r = cell.GetRow(), c = cell.GetCol();
	
	if (std::find(traversed.cbegin(), traversed.cend(), cell) != traversed.cend()) // The cell is met for the second time
	{
		// Cycle found
		_mark_cyclic(cell);
		for (auto i = traversed.crbegin(); *i != cell; i++)
			_mark_cyclic(*i);
	}
	else 
	{
		if (_is_marked_cyclic(cell))
		{
			// Cells previously marked as cyclic may not not cause them anymore
			_unmark_cyclic(cell);
		}
		if (_has_dependencies(cell))
		{
			traversed.push_back(cell);
			const std::list<wxGridCellCoords>& dependent = _cells_dependencies[r][c];
			// Check next dependencies
			for (const wxGridCellCoords& next : dependent)
			{
				_check_cycles_next(next, traversed);
			}
		}
	}
}

void CellsObserver::_mark_cyclic(const wxGridCellCoords& cell)
{
	const int &r = cell.GetRow(), &c = cell.GetCol();
	_cyclic_cells.insert({ r, std::set<int>() });
	_cyclic_cells[r].insert(c);
	_grid->SetCellValue(cell, "#Cycle#");
	_grid->SetCellTextColour(r, c, wxColour("Red"));
}

void CellsObserver::_unmark_cyclic(const wxGridCellCoords& cell)
{
	const int &r = cell.GetRow(), &c = cell.GetCol();
	if (_cyclic_cells[r].count(c))
		_cyclic_cells[r].erase(c);
	if (!_cyclic_cells[r].size())
		_cyclic_cells.erase(r);
	_grid->SetCellTextColour(r, c, _grid->GetDefaultCellTextColour());
}

bool CellsObserver::_is_marked_cyclic(const wxGridCellCoords& cell)
{
	return _cyclic_cells.count(cell.GetRow()) &&
		_cyclic_cells[cell.GetRow()].count(cell.GetCol());
}

bool CellsObserver::IsCellFunction(const wxGridCellCoords& cell) const
{
	if (_cells_funcs.count(cell.GetRow()) && _cells_funcs.at(cell.GetRow()).count(cell.GetCol()))
		return true;
	return false;
}
