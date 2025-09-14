#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Channel.hpp"

#include <queue>
#include <ctime>

enum UserStatus
{
	UNREGISTERED,
	NICK_SET,
	USER_SET,
	REGISTERED
};

class Client
{
	private:
		int											_fd;

		std::map<char, bool>						_modes;

		UserStatus									_status;

		std::string									_nickname;
		std::string									_username;
		std::string									_realname;
		std::string									_hostname;
		std::string									_password;

		std::string									_input_buffer;
		std::string									_ouput_buffer;

		std::vector<Channel*>						_join_channel;

		bool										_authenticated;

		time_t										_connection_time;

	public:
		 Client												(int fd);
		~Client												();

		int 							GetFD				() const;

		UserStatus						GetStatus			() const;

		std::string 					GetUsername			() const;
		std::string 					GetNickname			() const;
		std::string 					GetRealname			() const;
		std::string						GetHostname			() const;
		std::string						GetPassword			() const;

		std::string						GetModeString		() const;

		const std::string&				GetOutputBuffer		() const;

		const std::vector<Channel*>&	GetJoinChannels		() const;

		time_t							GetConnectionTime	() const;

		bool							IsRegistered		() const;
		bool							HasOuputData		() const;

		bool							IsModeSet			(char mode) const;

		bool							GetAuth				(void) const ;
		void							SetAuth				(bool status);

		void 							SetFD				(int fd);

		void							SetStatus			(UserStatus status);

		void 							SetUsername			(const std::string &username);
		void 							SetNickname			(const std::string &nickname);
		void 							SetRealname			(const std::string &realname);
		void 							SetHostname			(const std::string &hostname);
		void 							SetPassword			(const std::string &password);

		void 							AppendToInputBuffer	(const std::string &data);
		void 							AppendToOuputBuffer	(const std::string &data);

		void 							ApplyModes			(Client* sender, const std::string& mode_string, Server& server);

		void							AddChannel			(Channel* channel);
		void							RmvChannel			(Channel* channel);

		void							PopOutputBuffer		(size_t count);

		std::string						ExtractNextMessage	(void);

	private:
		void							Handle_I_Mode		(char sign, Server& server);

};

#endif
