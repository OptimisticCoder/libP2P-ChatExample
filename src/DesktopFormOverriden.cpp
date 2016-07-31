#include "DesktopFormOverriden.h"

DesktopFormOveridden::DesktopFormOveridden(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: DesktopForm(parent, id, title, pos, size, style)
{
}

DesktopFormOveridden::~DesktopFormOveridden()
{
	if (_manager)
		delete _manager;
}

void DesktopFormOveridden::Init()
{
	txtMain->BeginTextColour(wxColour(0, 90, 0, 0));
	txtMain->WriteText("Welcome to ChatExample!\r\n");
	txtMain->EndTextColour();

	_manager = new p2p_manager();
	_manager->Log.connect(boost::bind(&DesktopFormOveridden::OnLog, this, _1));
	_manager->NewConnection.connect(boost::bind(&DesktopFormOveridden::OnNewConnection, this, _1, _2));
	_manager->Run(6453);
}

void DesktopFormOveridden::OnNewConnection(bool isIncoming, p2p_connection::pointer connection)
{
	wxMutexGuiEnter();

	txtMain->Freeze();

	if (isIncoming) {
		txtMain->WriteText("Incoming connection received from ");
	}
	else
	{
		txtMain->WriteText("Outgoing connection established to ");
	}

	std::stringstream ss;
	ss << connection->Socket().remote_endpoint();

	txtMain->WriteText(ss.str());
	txtMain->WriteText("\r\n");

	txtMain->Thaw();
	wxMutexGuiLeave();
}

void DesktopFormOveridden::OnLog(std::string msg)
{
	std::string txt = msg;
	txt.append("\r\n");

	wxMutexGuiEnter();

	txtMain->Freeze();
	txtMain->WriteText(txt);
	txtMain->Thaw();

	wxMutexGuiLeave();
}