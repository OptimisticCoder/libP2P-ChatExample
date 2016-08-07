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
	_manager->DataReceived.connect(boost::bind(&DesktopFormOveridden::OnDataReceived, this, _1, _2));
	_manager->Run(6453);
}

void DesktopFormOveridden::OnNewConnection(bool isIncoming, p2p_connection::pointer connection)
{
	std::string txt;
	if (isIncoming) {
		txt = "Incoming connection received from ";
	}
	else
	{
		txt = "Outgoing connection established to ";
	}

	std::stringstream ss;
	ss << connection->Socket().remote_endpoint();

	txt.append(ss.str());

	writeToRichText(txt);
}

void DesktopFormOveridden::OnLog(std::string msg)
{
	std::string txt = msg;
	writeToRichText(txt);
}

void DesktopFormOveridden::OnDataReceived(p2p_connection::pointer connection, p2p_packet packet)
{
	std::stringstream ss;
	ss << "Received from " << connection->Socket().remote_endpoint();
	std::string txt(ss.str());

	txt.append(" packet: ");

	std::string body(packet.body(), packet.body() + packet.body_length());
	txt.append(body);

	writeToRichText(txt);
}

void DesktopFormOveridden::writeToRichText(std::string txt)
{
	if (!wxIsMainThread())
		wxMutexGuiEnter();

	//txtMain->SetInsertionPointEnd();

	txtMain->Freeze();

	txtMain->SetCaretPosition(txtMain->GetLastPosition() - 1);
	size_t before_number_of_lines = txtMain->GetNumberOfLines();
	//txtMain->SetInsertionPointEnd();



	txtMain->WriteText(txt);
	txtMain->Newline();


	size_t after_number_of_lines = txtMain->GetNumberOfLines();
	txtMain->Thaw();

	txtMain->ScrollLines(txtMain->GetNumberOfLines());

	if (!wxIsMainThread())
		wxMutexGuiLeave();

}
