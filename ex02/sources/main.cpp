/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/02/28 14:03:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int	main()
{
	ScavTrap	Bob("Bob");
	std::cout << std::endl;
	ScavTrap	Jim("Jim");
	std::cout << std::endl;
	ScavTrap	Joe("Joe");
	std::cout << std::endl;

	Bob.attack("Jim");
	Jim.takeDamage(10);
	Jim.beRepaired(50);

	std::cout << std::endl;
	Bob.showStatus();
	Jim.showStatus();
	Joe.showStatus();
	std::cout << std::endl;

	Joe.attack("Bob");
	Bob.takeDamage(10);
	Bob.beRepaired(50);

	std::cout << std::endl;
	Bob.showStatus();
	Jim.showStatus();
	Joe.showStatus();
	std::cout << std::endl;

	return (0);
}
