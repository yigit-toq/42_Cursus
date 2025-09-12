#include "Server.hpp"

PassCommand:: PassCommand	(Server& server) : _server(server) {}

PassCommand::~PassCommand	() {}

void	PassCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered()			)
	{
		_server.SendsNumericReply(sender, 462, "USER :Unauthorized command (already)"	);
		return ;
	}

	if (msg.GetParameters	().empty()	)
	{
		_server.SendsNumericReply(sender, 461, "PASS :Not enough parameters"			);
		return ;
	}

	std::string	password = msg.GetParameters()[0];

	if (password != _server.GetPassword())
	{
		_server.SendsNumericReply	(sender, 464, ":Password incorrect");

		return ;
	}

	sender->SetAuth				(true);

	sender->SetPassword			(password);

	Logger::GetInstance().Log	(INFO, "User " + sender->GetNickname() + " provided correct password.");

	_server.CheckRegistration	(sender  );
}
