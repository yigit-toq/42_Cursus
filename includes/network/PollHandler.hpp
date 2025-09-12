#ifndef POLLHANDLER_HPP
#define POLLHANDLER_HPP

#include "Logger.hpp"

#include "Utils.hpp"

#include <cerrno>
#include <poll.h>

class PollHandler
{
	private:
		std::vector<struct pollfd>					_fds;

	public:
		 PollHandler								();
		~PollHandler								();

		void						RmvSocket		(int fd);
		void						AddSocket		(int fd, short events);

		void 						SetEvents		(int fd, short events);

		short						GetEvents		(int fd) const;

		std::vector<struct pollfd>	WaitForEvents	(int timeout_ms = -1);
};

#endif
