/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:51:22 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 20:38:36 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void    Harl::info( void )
{
    std::cout << "Info" << std::endl;
}

void    Harl::debug( void )
{
    std::cout << "Debug" << std::endl;
}

void    Harl::error( void )
{
    std::cout << "Error" << std::endl;
}

void    Harl::warning( void )
{
    std::cout << "Warning" << std::endl;
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
	while (index < 4)
	{
		switch (index)
		{
			case 0:
				(this->*functions[0])();
				break ;
			case 1:
				(this->*functions[1])();
				break ;
			case 2:
				(this->*functions[2])();
				break ;
			case 3:
				(this->*functions[3])();
				break ;
			default:
				std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
				return ;
		}
		index++;
	}
	// std::unordered_map<std::string, int> strings = {{"DEBUG", 1}, {"INFO", 2}, {"WARNING", 3}, {"ERROR", 4}};

	// switch (strings[level])
	// {
	// 	case 1:
	// 		(this->*functions[0])();
	// 	case 2:
	// 		(this->*functions[1])();
	// 	case 3:
	// 		(this->*functions[2])();
	// 	case 4:
	// 		(this->*functions[3])();
	// 	default:
	// 		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	// }
}
