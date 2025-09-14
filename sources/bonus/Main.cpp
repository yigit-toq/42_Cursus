#include "Assistant.hpp"

#include <csignal>

void	SignalHandler(int signum)
{
	(void)signum;

	if (bot_instance)
	{
		bot_instance->Close();
	}

	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	signal(SIGINT, SignalHandler);

	if (argc != 5)
	{
		std::cerr << "Usage: " << argv[0] << " <server_ip> <server_port> <password> <nickname>" << std::endl;

		return (EXIT_FAILURE);
	}

	std::string server_addr	= argv[1];

	int			server_port	= std::atoi(argv[2]);

	std::string password	= argv[3];
	std::string nickname	= argv[4];

	bot_instance = new Assistant(server_addr, server_port, password, nickname);

	bot_instance->Start();

	delete (bot_instance);

	return (EXIT_SUCCESS);
}
