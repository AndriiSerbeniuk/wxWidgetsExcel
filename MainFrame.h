#pragma once
#include "wx\wx.h"
#include "wx\grid.h"

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

private:
	wxPanel* _main_panel;
	wxMenuBar* _menu_bar;
	wxTextCtrl* _cell_textctrl;
	wxButton* _bttn_func_help;
	wxTextCtrl* _function_textctrl;
	wxGrid* _grid;

	wxBoxSizer* _textctrls_sizer;
	wxBoxSizer* _main_sizer;
	wxBoxSizer* _panel_sizer;

	wxMenu* _file_menu;

	wxMenuItem* _mitem_new;
	wxMenuItem* _mitem_open;
	wxMenuItem* _mitem_save;
	wxMenuItem* _mitem_save_as;
	wxMenuItem* _mitem_quit;
};

