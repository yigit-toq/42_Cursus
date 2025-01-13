/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:49:05 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 12:23:02 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

bool ft_read_line(std::string &line)
{
	std::getline(std::cin, line);
	std::cout << "\033[12;0H\033[J";
	if (line.empty())
	{
		if (std::cin.eof())
		{
			std::cout << std::endl << C_Y << "Thank you for choosing us." << END << std::endl;
			exit (0);
		}
		return (false);
	}
	return (true);
}
