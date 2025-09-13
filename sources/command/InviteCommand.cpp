#include "Server.hpp"

InviteCommand:: InviteCommand	(Server& server) : _server(server) {}

InviteCommand::~InviteCommand	() {}

void	InviteCommand::Execute	(Client* sender, const Message& msg)
{
	if (msg.GetParameters().size() < 2)
	{
		_server.SendsNumericReply(sender, 461, "INVITE :Not enough parameters");
		return ;
	}

	std::string tar_nick = msg.GetParameters()[0];
	std::string chn_name = msg.GetParameters()[1];

	Channel*	tar_chnl = _server.FinderChannel	(chn_name);
	Client*		tar_user = _server.FindUser			(tar_nick);

	if (!tar_user)
	{
		_server.SendsNumericReply(sender, 401, tar_nick + " :No such nick"		);
		return ;
	}

	if (!tar_chnl)
	{
		_server.SendsNumericReply(sender, 403, chn_name + " :No such channel"	);
		return ;
	}

	if (!tar_chnl->IsUser(sender))
	{
		_server.SendsNumericReply(sender, 442, chn_name + " :You're not on that channel" );
		return ;
	}

	if (tar_chnl->IsModeSet('i') && !tar_chnl->IsOprt(sender))
	{
		_server.SendsNumericReply(sender, 482, chn_name + " :You're not channel operator");
		return ;
	}

	_server.SendsNumericReply(sender, 341, ":" + tar_nick + " " + chn_name);

	std::string invite_msg = ":" + sender->GetNickname() + " INVITE " + tar_nick + " :" + chn_name + "\r\n";

	tar_chnl->AddInvitedUser			(tar_nick);
	
	tar_user->AppendToOuputBuffer		(invite_msg);

	_server.GetPollHandler().SetEvents	(tar_user->GetFD(), POLLIN | POLLOUT);
}
