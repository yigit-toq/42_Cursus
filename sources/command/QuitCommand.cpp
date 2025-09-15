#include "Server.hpp"

QuitCommand:: QuitCommand	(Server& server) : _server(server) {}

QuitCommand::~QuitCommand	() {}

void	QuitCommand::Execute(Client* sender, const Message& msg)
{
	std::string quit_message = "Client Quit" ;

	if (!msg.GetParameters().empty())
	{
		quit_message = msg.GetParameters()[0];
	}

	std::stringstream quit_ss;

	quit_ss << ":" << sender->GetNickname() << "!" << sender->GetUsername() << "@" << sender->GetHostname() << " QUIT :" << quit_message;

	const std::vector<Channel*>&	joined_channels = sender->GetJoinChannels();

	std::vector<Channel*>			channel_to_part = joined_channels;

	std::string						quit_ms			= quit_ss.str  ();

	for (size_t i = 0; i < channel_to_part.size(); ++i)
	{
		Channel* channel = channel_to_part[i];

		if (channel)
		{
			channel->BroadcastMsg	(quit_ms, sender);

			channel->TransOprts		(sender);

			channel->RmvUser		(sender);

			if (channel->IsFree		())
			{
				_server.RemoveChannel		(channel->GetName());

				Logger::GetInstance	().Log	(INFO, "Channel " + channel->GetName() + " is empty and removed.");
			}
		}
	}

	Logger::GetInstance().	Log (INFO, "User " + sender->GetNickname() + " (" + ft_to_string(sender->GetFD()) + ") has quit with message: '" + quit_message + "'");

	_server.ClientDisconnection	(sender->GetFD());
}
