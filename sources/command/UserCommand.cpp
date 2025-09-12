#include "Server.hpp"

UserCommand:: UserCommand	(Server& server) : _server(server) {}

UserCommand::~UserCommand	() {}

void	UserCommand::Execute(Client* sender, const Message& msg)
{
	if (!sender->GetAuth())
	{
		_server.SendsNumericReply(sender, 462, "USER :You have not authenticated yet"	);
		return ;
	}

	if (sender->IsRegistered())
	{
		_server.SendsNumericReply(sender, 462, "USER :Unauthorized command (already)"	);
		return ;
	}

	if (msg.GetParameters().size() < 4)
	{
		_server.SendsNumericReply(sender, 461, "USER :Not enough parameters"			);
		return ;
	}

	std::string username = msg.GetParameters()[0];

	// Mod parametresi	  (msg.GetParameters()[1])
	// Unu parametresi	  (msg.GetParameters()[2])

	std::string realname = msg.GetParameters()[3];

	if (username.empty() || realname.empty())
	{
		_server.SendsNumericReply(sender, 461, "USER :Invalid username or realname");
		return ;
	}

	sender->SetUsername	(username);
	sender->SetRealname	(realname);

	sender->SetStatus	(USER_SET);

	Logger::GetInstance	().Log(INFO, "User " + sender->GetNickname() + " set username to: " + username + ", realname: " + realname);

	_server.CheckRegistration(sender);
}
