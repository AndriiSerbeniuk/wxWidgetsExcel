#include "GridFileManager.h"

GridFileManager::GridFileManager() 
	: _file_path(""), _grid(nullptr), _unsaved(false), _observer(nullptr) {}

GridFileManager::GridFileManager(InfiniteGrid* grid)
	: _file_path(""), _grid(grid), _unsaved(false), _observer(nullptr) {}

std::string GridFileManager::GetPath() const
{
	return _file_path;
}

bool GridFileManager::PathEmpty() const
{
	return _file_path.empty();
}

void GridFileManager::SetPath(const std::string& path)
{
	_file_path = path;
}

void GridFileManager::SetObserver(CellsObserver* observer)
{
	_observer = observer;
}

bool GridFileManager::Save()
{
	if (_file_path.empty())
		return false;
	FILE* out;
	if ((out = fopen(_file_path.c_str(), "wb")) == NULL)
		return false;
	int dWidth = _grid->GetDataWidth(), dHeight = _grid->GetDataHeight();
	fwrite(&dWidth, sizeof(dWidth), 1, out);
	fwrite(&dHeight, sizeof(dWidth), 1, out);
	std::string value;
	for (int r = 0; r < dHeight; r++)
	{
		for (int c = 0; c < dWidth; c++)
		{
			if (_observer->IsCellFunction({ r,c }))			
				value = _observer->GetRaw({ r,c });			
			else			
				value = _grid->GetCellValue(r, c);			
			fwrite(value.c_str(), sizeof(char), value.size() + 1, out);
		}
	}
	fclose(out);
	_unsaved = false;
	return true;
}

bool GridFileManager::Load()
{
	if (_file_path.empty())
		return false;
	FILE* in;
	if ((in = fopen(_file_path.c_str(), "rb")) == NULL)
		return false;
	unsigned int dWidth = 0, dHeight = 0;
	fread(&dWidth, sizeof(dWidth), 1, in);
	fread(&dHeight, sizeof(dWidth), 1, in);
	fpos_t start, end;
	fgetpos(in, &start);
	fseek(in, 0, SEEK_END);
	fgetpos(in, &end);
	unsigned int dataSize = end - start;
	if (dWidth < 1 || dHeight < 1 || dataSize < dWidth * dHeight)
	{
		fclose(in);
		return false;
	}
	fsetpos(in, &start);
	char* value = new char[dataSize];	
	for (int r = 0; r < dHeight; r++)
	{
		for (int c = 0; c < dWidth; c++)
		{
			fgets(value, dataSize, in);
			start += strlen(value) + 1;
			fsetpos(in, &start);
			_grid->SetCellValue(r, c, value);
		}
	}
	delete[] value;
	fclose(in);
	// Make the observer aware of the new cells
	for (int r = 0; r < dHeight; r++)
	{
		for (int c = 0; c < dWidth; c++)
		{
			_observer->Update({ r,c });
		}
	}
	_unsaved = false;
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

void GridFileManager::DiscardUnsavedChanges()
{
	_unsaved = false;
}


