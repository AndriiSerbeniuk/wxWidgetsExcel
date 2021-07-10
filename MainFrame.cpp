#include "MainFrame.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "wxExcel")
{
	SetSize(wxSize(1280, 720));

	_mitem_new = new wxMenuItem(_file_menu, wxID_ANY, 
		"&New", "Create a new file.");
	_mitem_open = new wxMenuItem(_file_menu, wxID_ANY, 
		"&Open", "Open an existing file.");
	_mitem_save = new wxMenuItem(_file_menu, wxID_ANY,
		"&Save", "Save the file.");
	_mitem_save_as = new wxMenuItem(_file_menu, wxID_ANY,
		"Save as", "Save the file and specify the directory.");
	_mitem_quit = new wxMenuItem(_file_menu, wxID_ANY,
		"&Quit", "Quit the program.");

	_file_menu = new wxMenu();
	_file_menu->Append(_mitem_new);
	_file_menu->Append(_mitem_open);
	_file_menu->Append(_mitem_save);
	_file_menu->Append(_mitem_save_as);
	_file_menu->Append(wxID_SEPARATOR);
	_file_menu->Append(_mitem_quit);

	_menu_bar = new wxMenuBar();
	_menu_bar->Append(_file_menu, "&File");
	SetMenuBar(_menu_bar);

	_cell_textctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(80, 20));
	int rowHeight = _cell_textctrl->GetSize().GetHeight();
	_bttn_func_help = new wxButton(this, wxID_ANY, "f(x)", wxDefaultPosition, wxSize(rowHeight, rowHeight));
	_bttn_func_help->SetFont(wxFont(9, wxFontFamily::wxFONTFAMILY_DECORATIVE,
		wxFontStyle::wxFONTSTYLE_ITALIC, wxFontWeight::wxFONTWEIGHT_LIGHT));
	_function_textctrl = new wxTextCtrl(this, wxID_ANY);
	
	_textctrls_sizer = new wxBoxSizer(wxHORIZONTAL);
	_textctrls_sizer->Add(_cell_textctrl, 1, wxCENTER);
	_textctrls_sizer->Add(_bttn_func_help, 0, wxCENTER);
	_textctrls_sizer->Add(_function_textctrl, 30, wxCENTER | wxALL, 2);

	_grid = new wxGrid(this, wxID_ANY);
	_grid->CreateGrid(50, 100);
	_grid->SetGridLineColour(wxColour(0, 0, 0));

	_main_sizer = new wxBoxSizer(wxVERTICAL);
	_main_sizer->Add(_textctrls_sizer);
	_main_sizer->Add(_grid);

	_main_panel = new wxPanel(this, wxID_ANY);
	_main_panel->SetSizer(_main_sizer);
	_main_panel->SetBackgroundColour(wxColour("Light gray"));

	_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	_panel_sizer->Add(_main_panel);
	SetSizer(_panel_sizer);

}

MainFrame::~MainFrame()
{
	// wxWidgets manages dynamic memory of its visual elements internally
}
