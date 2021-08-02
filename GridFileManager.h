#pragma once
#include "InfiniteGrid.h"
#include "CellsObserver.h"

class GridFileManager
{
public:
	GridFileManager();
	GridFileManager(InfiniteGrid* grid);

	void SetPath(const std::string& path);
	std::string GetPath() const;
	bool PathEmpty() const;
	void SetObserver(CellsObserver* observer);
	bool Save();
	bool Load();
	bool HasUnsavedChanges() const;
	void UnsavedChanges();
	void DiscardUnsavedChanges();

private:
	std::string _file_path;
	InfiniteGrid* _grid;
	CellsObserver* _observer;
	bool _unsaved;
};

