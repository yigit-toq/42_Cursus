/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:30:58 by ytop              #+#    #+#             */
/*   Updated: 2025/06/27 15:31:52 by ytop             ###   ########.fr       */
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
	int pass = std::atoi(argv[2]);

	if (port <= 0 || port > 65535)
	{
		std::cerr << "Invalid port number." << std::endl;

		return (EXIT_FAILURE);
	}

	try
	{
		Server server(port, pass);

		server.Start ();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;

		return (EXIT_FAILURE);
	}
}
