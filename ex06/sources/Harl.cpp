/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:51:22 by ytop              #+#    #+#             */
/*   Updated: 2025/01/14 13:24:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void    Harl::info( void )
{
    std::cout << "[INFO]" << std::endl;
}

void    Harl::debug( void )
{
    std::cout << "[DEBUG]" << std::endl;
}

void    Harl::error( void )
{
    std::cout << "[ERROR]" << std::endl;
}

void    Harl::warning( void )
{
    std::cout << "[WARNING]" << std::endl;
}

void    Harl::complain( std::string level )
{
	void (Harl::*functions[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	int	index = -1;

	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			index = i;
			break ;	
		}
	}
	switch (index)
	{
		case 0:
			(this->*functions[0])();
		case 1:
			(this->*functions[1])();
		case 2:
			(this->*functions[2])();
		case 3:
			(this->*functions[3])();
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
}
