#include "DesktopFormOverriden.h"

DesktopFormOveridden::DesktopFormOveridden(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: DesktopForm(parent, id, title, pos, size, style)
{
}

DesktopFormOveridden::~DesktopFormOveridden()
{
}

void DesktopFormOveridden::Init()
{
	txtMain->BeginTextColour(wxColour(0, 90, 0, 0));
	txtMain->WriteText("Welcome to ChatExample!\r\n");
	txtMain->EndTextColour();


	const std::string arr[] = { "dnsseed.uape.co.uk" };
	std::vector<std::string> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	try
	{
		P2PNetwork::p2p_listener listener(6453);
		listener.NewConnection.connect(bind(&DesktopFormOveridden::OnNewConnection, this, _1));
	}
	catch (std::exception const &ex) {
		printf(ex.what());
	}

	P2PNetwork::p2p_host hostManager;
	std::vector<P2PNetwork::p2p_host> hosts;

	try
	{
		hosts = hostManager.LoadAll("hosts", vec, 6453);
	}
	catch (std::exception const &ex) {
		printf(ex.what());
	}

	for (std::vector<P2PNetwork::p2p_host>::iterator it = hosts.begin(); it != hosts.end(); ++it)
	{
		txtMain->WriteText("Connecting to ");
		txtMain->WriteText(it->Ip);

		txtMain->BeginTextColour(wxColour("grey"));
		txtMain->WriteText(":");

		std::stringstream ss;
		ss << it->Port;

		txtMain->WriteText(ss.str());
		txtMain->EndTextColour();
		txtMain->WriteText("\r\n");

		// outgoing connection
		//p2p_connection::pointer new_connection = p2p_connection::Create(io_service);
		//new_connection->Connect();
	}
}

void DesktopFormOveridden::OnNewConnection(int todo)
{
	txtMain->WriteText("New connection received!!!\r\n");
	std::stringstream ss;
	ss << todo;

	txtMain->WriteText(ss.str());
	txtMain->WriteText("\r\n");
}