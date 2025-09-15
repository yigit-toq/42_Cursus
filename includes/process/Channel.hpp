#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Utils.hpp"

#include <map>

class Client;
class Server;

class Channel
{
	private:
		std::string										_name ;
		std::string										_pass ;
		std::string										_topic;

		std::map<char, bool>							_modes;

		std::map<int, Client*>							_users;
		std::map<int, Client*>							_oprts;

		size_t											_user_limit;

		std::vector<std::string>						_invited_users;

		Channel											(const Channel& other);
		Channel& operator=								(const Channel& other);

	private:
		void	Handle_I_Mode							(Client* sender, char sign);
		void	handle_T_Mode							(Client* sender, char sign);
		void	handle_K_Mode							(Client* sender, char sign, const std::string& param);
		void	handle_L_Mode							(Client* sender, char sign, const std::string& param);
		void	handle_O_Mode							(Client* sender, char sign, const std::string& param);

		Server&											_server;

	public:
		 Channel										(const std::string& name, Server& server);
		~Channel										();

		const std::string&	GetName						() const;
		const std::string&	GetPass						() const;
		const std::string&	GetTopic					() const;

		std::string			GetModeString				() const;
		std::string			GetModeParams				() const;

		bool	IsFull									() const;
		bool	IsFree									() const;

		bool	IsUser									(Client*	user) const;
		bool	IsOprt									(Client*	user) const;

		bool	IsModeSet								(char		mode) const;

		const	std::map<int, Client*>& GetUsers		() const;
		const	std::map<int, Client*>& GetOprts		() const;

		void	SetName									(const std::string& name);
		void	SetPass									(const std::string& pass);
		void	SetTopic								(const std::string& topic);

		void	BroadcastMsg							(const std::string& message	, Client* exclude_user	= NULL);

		bool	GetInvitedUser							(const std::string& nickname);

		void	AddInvitedUser							(const std::string& nickname);
		void	RmvInvitedUser							(const std::string& nickname);

		void	AddUser									(Client* user);
		void	RmvUser									(Client* user);

		void	AddOprt									(Client* user);
		void	RmvOprt									(Client* user);

		void	TransOprts								(Client* user);

		void	ApplyModes								(Client* sender, const std::string& mode_strs, const std::vector<std::string>& mode_args, Server& server);
};

#endif
