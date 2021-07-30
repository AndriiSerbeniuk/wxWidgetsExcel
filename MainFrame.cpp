#include "MainFrame.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "wxExcel")
{
	_file_path.clear();
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
	
	_sizer_main = new wxBoxSizer(wxVERTICAL);
	_sizer_main->Add(_sizer_textctrls, 1, wxEXPAND);
	_sizer_main->Add(_grid, 100, wxEXPAND);

	_panel_main = new wxPanel(this, idPanelMain);
	_panel_main->SetSizer(_sizer_main);
	_panel_main->SetBackgroundColour(wxColour("Light gray"));

	_sizer_panel = new wxBoxSizer(wxHORIZONTAL);
	_sizer_panel->Add(_panel_main, wxEXPAND);
	SetSizer(_sizer_panel);
	_grid->ResizeData();
	
	_observer = new CellsObserver(_grid);
}

MainFrame::~MainFrame()
{
	delete _observer;
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

void MainFrame::_on_new_press(wxCommandEvent& e)	// TODO
{
	//_grid->ClearGrid();
	// TODO: make the grid resize itself here
	e.Skip();
}

void MainFrame::_on_open_press(wxCommandEvent& e)	// TODO
{
	// open a dialog

	// load the file
	// _file_path = path

	e.Skip();
}

void MainFrame::_on_save_press(wxCommandEvent& e)	// TODO
{
	if (!_file_path.empty())
	{
		// save to path
	}
	else
	{
		// open a dialog
		
		// save to path
	}


	e.Skip();
}

void MainFrame::_on_save_as_press(wxCommandEvent& e)	// TODO
{
	// open a dialog

	// save to path

	e.Skip();
}

void MainFrame::_on_quit_press(wxCommandEvent& e)
{
	Close();
	e.Skip();
}

void MainFrame::_on_cell_txt_enter(wxCommandEvent& e)	// TODO
{
	// decode the the text with lexical analyzer
	
	this->SetFocus();	// unfocus the control
	e.Skip();
}

void MainFrame::_on_func_help_press(wxCommandEvent& e)	// TODO
{
	// testing code
	
	
	//=====
	// Open a frame with help, main frame shoould still be interactable
	e.Skip();
}

void MainFrame::_on_func_txt_changed(wxCommandEvent& e)	// TODO
{
	_grid->SetCellValue(_grid->GetSelectedCell(), _txt_function->GetValue());
	e.Skip();
}

void MainFrame::_on_func_txt_enter(wxCommandEvent& e)	// TODO: unfocusing the control doesn't call this method, but it should
{
	// testing code
	/*LexemParser lp(e.GetString().ToStdString());
	bool correct = GrammarChecker::Run(lp.GetParsed());*/
	//=====
	// start function parse and calculation
	_on_text_entered(_grid->GetSelectedCell());
	this->SetFocus();	// unfocus the control
	e.Skip();
}

void MainFrame::_on_grid_cell_enter(wxGridEvent& e)	// TODO
{
	//_txt_function->ChangeValue(_grid->GetCellValue(e.GetRow(), e.GetCol()));
	// start function parse and calculation
	_on_text_entered(wxGridCellCoords(e.GetRow(), e.GetCol()));
	e.Skip();
}

void MainFrame::_on_close(wxCloseEvent& e)	// TODO
{
	// TODO: if the file is not saved ask the user if he's sure
	Destroy();
}

void MainFrame::_on_cell_selected(wxGridEvent& e)
{
	if (_observer->IsCellFunction({ e.GetRow(), e.GetCol() }))
		_txt_function->ChangeValue(_observer->GetRaw({ e.GetRow(), e.GetCol() }));
	else
		_txt_function->ChangeValue(_grid->GetCellValue(e.GetRow(), e.GetCol()));
	_grid->SelectCell(wxGridCellCoords(e.GetRow(), e.GetCol()));
	e.Skip();
}

wxString MainFrame::_dialog_open()	// TODO
{
	return wxString();
}

wxString MainFrame::_dialog_save()	// TODO
{
	return wxString();
}

void MainFrame::_on_text_entered(wxGridCellCoords cell)
{
	//wxString text = _grid->GetCellValue(cell);
	//bool isObserved = _observer->Contains(cell);
	//if (text[0] == '=')
	//{
	//	if (isObserved)
	//		_observer->Update(cell);
	//	else
	//		_observer->AddCell(cell);
	//	//_grid->SetCellValue(cell, _observer->GetValue(cell));
	//}
	//else if (isObserved)
	//{
	//	_observer->RemoveCell(cell);
	//}
	_observer->Update(cell);
}

