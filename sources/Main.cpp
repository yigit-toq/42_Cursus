/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:26:07 by ytop              #+#    #+#             */
/*   Updated: 2025/05/30 17:46:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port>" << " <pass>" << std::endl;

		return (EXIT_FAILURE);
	}

	int port = std::atoi(argv[1]);

	if (port <= 0 || port > 65535)
	{
		std::cerr << "Invalid port number." << std::endl;

		return (EXIT_FAILURE);
	}

	try
	{
		Server server(port, argv[2]);

		server.Start ();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;

		return (EXIT_FAILURE);
	}
}
