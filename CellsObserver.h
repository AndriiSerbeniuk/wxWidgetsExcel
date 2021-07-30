#pragma once
#include <set>
#include "CellFunction.h"

class CellsObserver
{
public:
	CellsObserver(wxGrid* grid);
	// Updates the grid based on the changed value of the given cell
	void Update(const wxGridCellCoords& cell);
	// Checks if the cell is a function
	bool IsCellFunction(const wxGridCellCoords& cell);
	// Returns calculated function value
	std::string GetValue(const wxGridCellCoords& cell);
	// Returns function text
	std::string GetRaw(const wxGridCellCoords& cell);
private:
	// Adds a cell to be observed
	void _add_cell(const wxGridCellCoords& cell);
	// Removes a cell from currently observed
	void _remove_cell(const wxGridCellCoords& cell);

	// First key is row, second is column
	std::map<int, std::map<int, CellFunction*>> _cells_funcs;
	// Cells, that are used in functions. keys are the cell, value is functions it's used in.
	std::map<int, std::map<int, std::list<wxGridCellCoords>>> _cells_dependencies;
	// Coordinates of cells that form cycles
	std::map<int, std::set<int>> _cyclic_cells;
	// wxGrid the object observes
	wxGrid* _grid;

	// Adds dependencies of given cell to the dependencies map
	void _add_dependencies(const wxGridCellCoords& cell);
	// Checks if given "dependent" cell is dependent from other given cell
	bool _has_dependency(const wxGridCellCoords& cell, const wxGridCellCoords& dependent);
	// Checks if given cell has any dependancies
	bool _has_dependencies(const wxGridCellCoords& cell);
	// Updates cells that are dependent on the given cell
	void _update_dependencies(const wxGridCellCoords& cell);
	// Checks if given cell forms dependency cycles. 
	void _check_cycles(const wxGridCellCoords& initialCell);
	// Recursive function that marks all found cyclic cells 
	// and adds them to the "_cyclic_cells" map.
	void _check_cycles_next(
		const wxGridCellCoords& cell,
		std::list<wxGridCellCoords> traversed);
	// Marks the cell as cyclic
	void _mark_cyclic(const wxGridCellCoords& cell);
	// Unmarks the cell as cyclic
	void _unmark_cyclic(const wxGridCellCoords& cell);
	// Checks if given cell is marked as cyclic
	bool _is_marked_cyclic(const wxGridCellCoords& cell);	
};

