/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/02/27 16:56:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main()
{
	ClapTrap	Bob("Bob");
	ClapTrap	Jim("Jim");
	ClapTrap	Joe("Joe");

	std::cout << std::endl;
	Bob.showStatus();
	Jim.showStatus();
	Joe.showStatus();
	std::cout << std::endl;

	ClapTrap	Cpy(Joe);

	std::cout << std::endl;
	std::cout << "DEF ";
	Joe.takeDamage(5);
	std::cout << std::endl;

	std::cout << "DEF ";
	Joe.showStatus();
	std::cout << "CPY ";
	Cpy.showStatus();

	std::cout << std::endl;
	Cpy = Jim;
	std::cout << std::endl;

	std::cout << "CPY ";
	Cpy.beRepaired(5);
	std::cout << std::endl;

	std::cout << "DEF ";
	Jim.showStatus();
	std::cout << "CPY ";
	Cpy.showStatus();

	std::cout << std::endl;
	Bob.attack("Jim");
	Bob.showStatus();
	std::cout << std::endl;
	Jim.takeDamage(10);
	Jim.showStatus();
	std::cout << std::endl;
	Jim.beRepaired(05);
	Jim.showStatus();
	std::cout << std::endl;

	Joe.attack("Bob");
	Joe.showStatus();
	std::cout << std::endl;
	Bob.takeDamage(10);
	Bob.showStatus();
	std::cout << std::endl;
	Bob.beRepaired(05);
	Bob.showStatus();
	std::cout << std::endl;
	return (0);
}
