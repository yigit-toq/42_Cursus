/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:05:48 by ytop              #+#    #+#             */
/*   Updated: 2025/12/02 16:05:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " \"<expression>\"" << std::endl;

		return (EXIT_FAILURE);
	}

	try
	{
		RPN	calculator;

		int	result = calculator.Calculate(argv[1]);

		std::cout << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
