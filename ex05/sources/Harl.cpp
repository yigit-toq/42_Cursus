/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:51:22 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 20:38:20 by ytop             ###   ########.fr       */
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
    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
        {
            (this->*functions[i])();
            return ;
        }
    }
    std::cout << "Invalid Level" << std::endl;
}
