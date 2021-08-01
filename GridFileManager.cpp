#include "GridFileManager.h"

GridFileManager::GridFileManager() 
	: _file_path(""), _grid(nullptr), _unsaved(false) {}

GridFileManager::GridFileManager(InfiniteGrid* grid)
	: _file_path(""), _grid(grid), _unsaved(false) {}

std::string GridFileManager::GetPath() const
{
	return _file_path;
}

void GridFileManager::SetPath(const std::string& path)
{
	_file_path = path;
}

bool GridFileManager::Save() const
{
	if (_file_path.empty())
		return false;
	std::ofstream out(_file_path, std::fstream::out | std::fstream::trunc);
	int dWidth = _grid->GetDataWidth(), dHeight = _grid->GetDataHeight();
	out << dWidth << ' ' << dHeight << ' ';
	for (int r = 0; r < dHeight; r++)
	{
		for (int c = 0; c < dWidth; c++)
		{
			out << _grid->GetCellValue(r, c) << ' ';
		}
	}

	out.close();
	return true;
}

bool GridFileManager::HasUnsavedChanges() const
{
	return _unsaved;
}

void GridFileManager::UnsavedChanges()
{
	_unsaved = true;
}


