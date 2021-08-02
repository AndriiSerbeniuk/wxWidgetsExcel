#pragma once
#include "wx\wx.h"
#include "wx\grid.h"
#include "InfiniteGrid.h"
#include "CellsObserver.h"
#include "FunctionsInfoFrame.h"
#include "GridFileManager.h"

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

private:
	enum ElemId {
		idPanelMain = 1000,
		idMenubar,
		idTxtCell,
		idBttnHelp,
		idTxtFunction,
		idGrid,
		idMenuFile,
		idMItemNew,
		idMItemOpen,
		idMItemSave,
		idMItemSaveAs,
		idMItemQuit
	};

	wxPanel* _panel_main;
	wxMenuBar* _menubar;
	wxTextCtrl* _txt_cell;
	wxButton* _bttn_func_help;
	wxTextCtrl* _txt_function;
	InfiniteGrid* _grid;

	wxBoxSizer* _sizer_textctrls;
	wxBoxSizer* _sizer_main;
	wxBoxSizer* _sizer_panel;

	wxMenu* _menu_file;

	wxMenuItem* _mitem_new;
	wxMenuItem* _mitem_open;
	wxMenuItem* _mitem_save;
	wxMenuItem* _mitem_save_as;
	wxMenuItem* _mitem_quit;

	CellsObserver* _observer;
	FunctionsInfoFrame* _info_frame;
	GridFileManager* _file_manager;

	// Events
	wxDECLARE_EVENT_TABLE();
	void _on_new_press(wxCommandEvent& e);
	void _on_open_press(wxCommandEvent& e);
	void _on_save_press(wxCommandEvent& e);
	void _on_save_as_press(wxCommandEvent& e);
	void _on_quit_press(wxCommandEvent& e);
	void _on_cell_txt_enter(wxCommandEvent& e);
	void _on_func_help_press(wxCommandEvent& e);
	void _on_func_txt_changed(wxCommandEvent& e);
	void _on_func_txt_enter(wxCommandEvent& e);
	void _on_grid_cell_enter(wxGridEvent& e);
	void _on_close(wxCloseEvent& e);
	void _on_cell_selected(wxGridEvent& e);

	bool _dialog_open_file();
	bool _dialog_save_file();
	void _scenario_unsaved();
	void _scenario_save();
	void _scenario_save_as();

	void _on_text_entered(wxGridCellCoords cell);
	void _init_grid();
	void _set_txt_func(int row, int col);
};

