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
	_grid->CreateGrid(50, 100);
	_grid->SetGridLineColour(wxColour(0, 0, 0));
	
	_sizer_main = new wxBoxSizer(wxVERTICAL);
	_sizer_main->Add(_sizer_textctrls);
	_sizer_main->Add(_grid);

	_panel_main = new wxPanel(this, idPanelMain);
	_panel_main->SetSizer(_sizer_main);
	_panel_main->SetBackgroundColour(wxColour("Light gray"));

	_sizer_panel = new wxBoxSizer(wxHORIZONTAL);
	_sizer_panel->Add(_panel_main);
	SetSizer(_sizer_panel);
}

MainFrame::~MainFrame()
{
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
	EVT_CLOSE(_on_close)
wxEND_EVENT_TABLE()

void MainFrame::_on_new_press(wxCommandEvent& e)
{
	_txt_function->AppendText("New ");
	e.Skip();
}

void MainFrame::_on_open_press(wxCommandEvent& e)
{
	_txt_function->AppendText("Open ");
	e.Skip();
}

void MainFrame::_on_save_press(wxCommandEvent& e)
{
	_txt_function->AppendText("Save ");
	e.Skip();
}

void MainFrame::_on_save_as_press(wxCommandEvent& e)
{
	_txt_function->AppendText("SaveAs ");
	e.Skip();
}

void MainFrame::_on_quit_press(wxCommandEvent& e)
{
	_txt_function->AppendText("Quit ");
	e.Skip();
}

void MainFrame::_on_cell_txt_enter(wxCommandEvent& e)
{
	_txt_function->AppendText("CEnt ");
	this->SetFocus();
	e.Skip();
}

void MainFrame::_on_func_help_press(wxCommandEvent& e)
{
	_txt_function->AppendText("Help ");
	e.Skip();
}

void MainFrame::_on_func_txt_changed(wxCommandEvent& e)
{
	_grid->SetCellValue(0, 0, std::string(_grid->GetCellValue(0, 0) + "FC "));
	e.Skip();
}

void MainFrame::_on_func_txt_enter(wxCommandEvent& e)
{
	_grid->SetCellValue(0, 0, std::string(_grid->GetCellValue(0, 0) + "FE "));
	this->SetFocus();
	e.Skip();
}

void MainFrame::_on_grid_cell_enter(wxGridEvent& e)
{
	_txt_function->AppendText("CellE ");
	e.Skip();
}

void MainFrame::_on_close(wxCloseEvent& e)
{
	// TODO: if the file is not saved ask the user if he's sure
	Destroy();
}
