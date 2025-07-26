/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:49:05 by ytop              #+#    #+#             */
/*   Updated: 2025/07/26 17:03:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	try
	{
		Bureaucrat	bureaucrat("Yigit", 80);

		std::cout << bureaucrat << std::endl;

		for (int i = 0; i <= 70; i++)
		{
			bureaucrat.decrementGrade	();
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		Bureaucrat	bureaucrat("Ahmet", 50);

		std::cout << bureaucrat << std::endl;

		for (int i = 50; i >= 00; i--)
		{
			bureaucrat.incrementGrade	();
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
