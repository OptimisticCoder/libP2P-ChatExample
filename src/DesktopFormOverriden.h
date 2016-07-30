#ifndef __DESKTOPFORM_OVERIDDEN_H__
#define __DESKTOPFORM_OVERIDDEN_H__

#include "DesktopForm.h"
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include "p2p_manager.hpp"
#include "p2p_host.hpp"
#include "p2p_listener.hpp"
#include "p2p_connection.hpp"
#include <sstream>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost;
using namespace P2PNetwork;

class DesktopFormOveridden : public DesktopForm
{

public:

	DesktopFormOveridden(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ChatExample"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(586, 461), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~DesktopFormOveridden();

	void Init();

private:
	p2p_manager* _manager;

	void OnNewConnection(int todo);
	void OnLog(std::string msg);
};

#endif 
