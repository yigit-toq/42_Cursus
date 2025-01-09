/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:49:05 by ytop              #+#    #+#             */
/*   Updated: 2025/01/09 20:23:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

void SetCursorPosition(int row, int col) 
{
    std::cout << "\033[" << row << ";" << col << "H";
	std::cout << "\033[J";
}

bool ft_read_line(std::string &line)
{
	std::getline(std::cin, line);
	SetCursorPosition(12, 0);
	if (line.empty())
	{
		if (std::cin.eof())
		{
			std::cout << std::endl << C_Y << "Thank you for choosing us" << END << std::endl;
			exit (0);
		}
		return (false);
	}
	return (true);
}
