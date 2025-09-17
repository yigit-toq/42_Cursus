#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct sockaddr_in sockaddr_in;

class Socket
{
	private:
		int				_port;
		int				_sock;

		sockaddr_in		_addr;

	public:
		 Socket			(int port);
		~Socket			();

		int		Accept	(void);

		void	Listen	(int backlog = 5);
		void	Create	(void);
		void	Binder	(void);

		int 	Sender	(int fd, char *buffer, size_t length);

		int 	Receive	(int fd, char *buffer, size_t length);

		int 	GetSock	(void) const;
		int 	GetPort	(void) const;

		void 	RmvSock	(int fd);
};

#endif
