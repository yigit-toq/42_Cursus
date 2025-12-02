/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:52:21 by ytop              #+#    #+#             */
/*   Updated: 2025/12/01 23:52:21 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: coult not open file." << std::endl;

		return (EXIT_FAILURE);
	}

	try
	{
		BitcoinExchange	exchange;

		exchange.LoadDatabase("data.csv");
		exchange.ProcessInput(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
