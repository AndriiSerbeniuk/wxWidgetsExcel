#include "wxExcel.h"

wxIMPLEMENT_APP(wxExcel);

bool wxExcel::OnInit()
{
	m_frame = new MainFrame();
	m_frame->Show();
	return true;
}
