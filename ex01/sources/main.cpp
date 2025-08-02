/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:06:06 by ytop              #+#    #+#             */
/*   Updated: 2025/08/02 15:31:04 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

#include <iostream>

#include <cstdlib>
#include <ctime>

int	main()
{
	try
	{
		Span	span = Span(5);

		span.addNumber(1);
		span.addNumber(2);
		span.addNumber(3);
		span.addNumber(4);
		span.addNumber(5);

		std::cout << "Longest  Span: " << span.longestSpan	() << std::endl;
		std::cout << "Shortest Span: " << span.shortestSpan	() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		Span				span(10000);

		std::vector<int>	bigv;

		std::srand(std::time(0));

		for (int i = 0; i < 10000; ++i)
		{
			bigv.push_back(std::rand());
		}

		span.addRange(bigv.begin(), bigv.end());

		std::cout << "Longest  Span: " << span.longestSpan	() << std::endl;
		std::cout << "Shortest Span: " << span.shortestSpan	() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return (0);
}
