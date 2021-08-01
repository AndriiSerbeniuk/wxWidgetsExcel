#pragma once
#include <fstream>
#include "InfiniteGrid.h"

class GridFileManager
{
public:
	GridFileManager();
	GridFileManager(InfiniteGrid* grid);

	std::string GetPath() const;
	void SetPath(const std::string& path);
	bool Save() const;
	bool HasUnsavedChanges() const;
	void UnsavedChanges();

private:
	std::string _file_path;
	InfiniteGrid* _grid;
	bool _unsaved;
};

