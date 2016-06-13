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
	const std::string arr[] = { "dnsseed.voodoo.community" };
	std::vector<std::string> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	P2PNetwork::p2p_host hostManager;
	std::vector<P2PNetwork::p2p_host> hosts = hostManager.LoadAll("hosts", vec, 6453);

	for (auto it = hosts.begin(); it != hosts.end(); ++it)
	{
		txtMain->AppendText(it->Ip);
		txtMain->AppendText(":");
		txtMain->AppendText(std::to_string(it->Port));
		txtMain->AppendText("\r\n");
	}
}