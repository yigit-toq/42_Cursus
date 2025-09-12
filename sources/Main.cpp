#include "Server.hpp"

#include <csignal>

void  HandleSignals(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT)
	{
		throw std::runtime_error("Server terminated by signal");
	}
}

int	main(int argc, char *argv[])
{
	try
	{
		std::stringstream ss;

		if (argc != 3)
		{
			ss << "Usage: " << argv[0] << " <port>" << " <pass>"; 

			throw std::runtime_error(ss.str());
		}

		Logger::GetInstance	("irc_server.log");

		int port =  std::atoi(argv[1]);

		if (port <= 0 || port > 65535)
		{
			throw std::runtime_error("Invalid port number.");
		}

		signal(SIGINT ,	HandleSignals);

		signal(SIGQUIT,	HandleSignals);
		signal(SIGTERM,	HandleSignals);

		Server server		(port, argv[2]);

		server.Start		();

		Logger::RmvInstance	();
	}
	catch (const std::exception &e)
	{
		Logger::GetInstance	().Log(ERROR, e.what());

		Logger::RmvInstance	();

		return				(EXIT_FAILURE);
	}
}
