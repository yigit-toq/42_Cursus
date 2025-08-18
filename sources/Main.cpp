/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:30:58 by ytop              #+#    #+#             */
/*   Updated: 2025/08/12 16:52:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <csignal>

void handleSignals(int signal) //test için
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT)
		throw std::runtime_error("Server terminated by signal");
}

int main(int argc, char **argv)
{
	try
	{
		std::stringstream ss;

		if (argc != 3)
		{
			ss << "Usage: " << argv[0] << " <port>" << " <pass>"; 

			throw std::runtime_error(ss.str());
		}

		int port =  std::atoi(argv[1]);

		if (port <= 0 || port > 65535)
		{
			throw std::runtime_error("Invalid port number.");
		}

		signal(SIGINT, handleSignals); //test için
		signal(SIGTERM, handleSignals);
		signal(SIGQUIT, handleSignals);
		signal(SIGPIPE, SIG_IGN);
	
		Server server	(port, argv[2]);

		server.Start	();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;

		return			(EXIT_FAILURE);
	}
}
