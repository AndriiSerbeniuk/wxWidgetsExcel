#pragma once
#include "wx/wx.h"
#include "MainFrame.h"

class wxExcel : public wxApp
{
private:
	MainFrame* m_frame;
public:
	virtual bool OnInit();
};

