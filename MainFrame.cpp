#include "MainFrame.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "wxExcel")
{
	SetSize(wxSize(1280, 720));

	_mitem_new = new wxMenuItem(_menu_file, idMItemNew, 
		"&New", "Create a new file.");
	_mitem_open = new wxMenuItem(_menu_file, idMItemOpen,
		"&Open", "Open an existing file.");
	_mitem_save = new wxMenuItem(_menu_file, idMItemSave,
		"&Save", "Save the file.");
	_mitem_save_as = new wxMenuItem(_menu_file, idMItemSaveAs,
		"Save as", "Save the file and specify the directory.");
	_mitem_quit = new wxMenuItem(_menu_file, idMItemQuit,
		"&Quit", "Quit the program.");

	_menu_file = new wxMenu();
	_menu_file->Append(_mitem_new);
	_menu_file->Append(_mitem_open);
	_menu_file->Append(_mitem_save);
	_menu_file->Append(_mitem_save_as);
	_menu_file->Append(wxID_SEPARATOR);
	_menu_file->Append(_mitem_quit);

	_menubar = new wxMenuBar();
	_menubar->Append(_menu_file, "&File");
	SetMenuBar(_menubar);

	_txt_cell = new wxTextCtrl(this, idTxtCell, "", wxDefaultPosition, wxSize(80, 20), wxTE_PROCESS_ENTER);
	int rowHeight = _txt_cell->GetSize().GetHeight();
	_bttn_func_help = new wxButton(this, idBttnHelp, "f(x)", wxDefaultPosition, wxSize(rowHeight, rowHeight));
	_bttn_func_help->SetFont(wxFont(9, wxFontFamily::wxFONTFAMILY_DECORATIVE,
		wxFontStyle::wxFONTSTYLE_ITALIC, wxFontWeight::wxFONTWEIGHT_LIGHT));
	_txt_function = new wxTextCtrl(this, idTxtFunction, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	
	_sizer_textctrls = new wxBoxSizer(wxHORIZONTAL);
	_sizer_textctrls->Add(_txt_cell, 1, wxCENTER);
	_sizer_textctrls->Add(_bttn_func_help, 0, wxCENTER);
	_sizer_textctrls->Add(_txt_function, 30, wxCENTER | wxALL, 2);

	_grid = new InfiniteGrid(this, idGrid);
	_grid->SetGridLineColour(wxColour(0, 0, 0));
	_grid->SelectCell({ 0,0 });
	_txt_cell->ChangeValue(_grid->GetColLabelValue(0)
		+ _grid->GetRowLabelValue(0));
	_grid->SetFocus();
	
	_sizer_main = new wxBoxSizer(wxVERTICAL);
	_sizer_main->Add(_sizer_textctrls, 1, wxEXPAND);
	_sizer_main->Add(_grid, 100, wxEXPAND);

	_panel_main = new wxPanel(this, idPanelMain);
	_panel_main->SetSizer(_sizer_main);
	_panel_main->SetBackgroundColour(wxColour("Light gray"));

	_sizer_panel = new wxBoxSizer(wxHORIZONTAL);
	_sizer_panel->Add(_panel_main, wxEXPAND);
	SetSizer(_sizer_panel);
	//_grid->ResizeGrid();
	
	_observer = new CellsObserver(_grid);
	_info_frame = new FunctionsInfoFrame(this);
	_file_manager = new GridFileManager(_grid);
	// for now
	_file_manager->SetObserver(_observer);
}

MainFrame::~MainFrame()
{
	delete _observer;
	delete _file_manager;
	// wxWidgets manages dynamic memory of its visual elements internally
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(idMItemNew, _on_new_press)
	EVT_MENU(idMItemOpen, _on_open_press)
	EVT_MENU(idMItemSave, _on_save_press)
	EVT_MENU(idMItemSaveAs, _on_save_as_press)
	EVT_MENU(idMItemQuit, _on_quit_press)
	EVT_TEXT_ENTER(idTxtCell, _on_cell_txt_enter)
	EVT_BUTTON(idBttnHelp, _on_func_help_press)
	EVT_TEXT(idTxtFunction, _on_func_txt_changed)
	EVT_TEXT_ENTER(idTxtFunction, _on_func_txt_enter)
	EVT_GRID_CMD_CELL_CHANGED(idGrid, _on_grid_cell_enter)
	EVT_GRID_CMD_SELECT_CELL(idGrid, _on_cell_selected)
	EVT_CLOSE(_on_close)
wxEND_EVENT_TABLE()

void MainFrame::_on_new_press(wxCommandEvent& e)
{
	if (_file_manager->HasUnsavedChanges())
		_scenario_unsaved();
	_init_grid();
	_set_txt_func(0, 0);
	_file_manager->DiscardUnsavedChanges();
	e.Skip();
}

void MainFrame::_on_open_press(wxCommandEvent& e)
{
	if (_file_manager->HasUnsavedChanges())
		_scenario_unsaved();
	if (_dialog_open_file())
	{
		_init_grid();
		_file_manager->Load();		
		_set_txt_func(0, 0);
	}
	e.Skip();
}

void MainFrame::_on_save_press(wxCommandEvent& e)
{
	_scenario_save();
	e.Skip();
}

void MainFrame::_on_save_as_press(wxCommandEvent& e)
{
	_scenario_save_as();
	e.Skip();
}

void MainFrame::_on_quit_press(wxCommandEvent& e)
{
	Close();
	e.Skip();
}

void MainFrame::_on_cell_txt_enter(wxCommandEvent& e)
{
	// Âecode the the cell coordinates with lexical analyzer
	ExprCell cell = LexemParser::ExtractCellId(e.GetString().c_str());
	_grid->SelectCell({ cell.GetRow(), cell.GetColumn() });
	_grid->MakeCellVisible(cell.GetRow(), cell.GetColumn());
	_grid->SetFocus();	// Focus the grid
	e.Skip();
}

void MainFrame::_on_func_help_press(wxCommandEvent& e)
{
	// Show a frame with info, main frame is still interactable
	if (_info_frame->IsVisible())
	{
		_info_frame->Show(false);
	}
	else
	{
		_info_frame->Show();
	}
	e.Skip();
}

void MainFrame::_on_func_txt_changed(wxCommandEvent& e)
{
	_grid->SetCellValue(_grid->GetSelectedCell(), _txt_function->GetValue());
	e.Skip();
}

void MainFrame::_on_func_txt_enter(wxCommandEvent& e)
{
	const wxGridCellCoords& selected = _grid->GetSelectedCell();
	_grid->ResizeData(selected.GetRow(), selected.GetCol(), e.GetString());
	_on_text_entered(_grid->GetSelectedCell());
	_grid->MakeCellVisible(selected);
	_grid->SetFocus();
	e.Skip();
}

void MainFrame::_on_grid_cell_enter(wxGridEvent& e)
{
	_on_text_entered(wxGridCellCoords(e.GetRow(), e.GetCol()));	
	e.Skip();
}

void MainFrame::_on_close(wxCloseEvent& e)
{
	if (_file_manager->HasUnsavedChanges())
		_scenario_unsaved();
	Destroy();
}

void MainFrame::_on_cell_selected(wxGridEvent& e)
{
	_grid->SelectCell({ e.GetRow(), e.GetCol() });
	_set_txt_func(e.GetRow(), e.GetCol());
	const wxGridCellCoords& selected = _grid->GetSelectedCell();
	_txt_cell->ChangeValue(_grid->GetColLabelValue(selected.GetCol())
		+ _grid->GetRowLabelValue(selected.GetRow()));
	e.Skip();
}

bool MainFrame::_dialog_open_file()
{
	bool pathEntered = false;
	wxFileDialog
		openFileDialog(this, _("Open GRD file"), "", "",
			"GRD files (*.grd)|*.grd", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		pathEntered = true;
		_file_manager->SetPath(openFileDialog.GetPath().ToStdString());
	}
	return pathEntered;
}

bool MainFrame::_dialog_save_file()
{
	bool pathEntered = false;
	wxFileDialog
		saveFileDialog(this, _("Save GRD file"), "", "",
			"GRD files (*.grd)|*.grd", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_OK)
	{
		pathEntered = true;
		_file_manager->SetPath(saveFileDialog.GetPath().ToStdString());
	}
	return pathEntered;
}

void MainFrame::_scenario_unsaved()
{
	if (wxMessageBox("There are unsaved changes. Would you like to save the file before proceeding?",
		"Unsaved changes!", wxYES | wxNO | wxCENTRE, this) == wxYES)
	{
		_scenario_save();
	}
	_file_manager->DiscardUnsavedChanges();
}

void MainFrame::_scenario_save()
{
	if (_file_manager->GetPath().empty())
		_scenario_save_as();
	else
		_file_manager->Save();
}

void MainFrame::_scenario_save_as()
{
	if (_dialog_save_file())
	{
		_file_manager->Save();
	}
}

void MainFrame::_on_text_entered(wxGridCellCoords cell)
{
	_file_manager->UnsavedChanges();
	_observer->Update(cell);
}

void MainFrame::_init_grid()
{
	_grid->ClearGrid();
	_observer->Clear();
	_txt_cell->ChangeValue(_grid->GetColLabelValue(0)
		+ _grid->GetRowLabelValue(0));
}

void MainFrame::_set_txt_func(int row, int col)
{
	if (_observer->IsCellFunction({ row, col }))
		_txt_function->ChangeValue(_observer->GetRaw({ row,col }));
	else
		_txt_function->ChangeValue(_grid->GetCellValue(row, col));
}

