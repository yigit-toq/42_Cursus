/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/02/28 13:40:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int	main()
{
	DiamondTrap	Bob("Bob");
	std::cout << std::endl;
	DiamondTrap	Jim("Jim");
	std::cout << std::endl;
	DiamondTrap	Joe("Joe");

	std::cout << std::endl;
	Bob.showStatus();
	Jim.showStatus();
	Joe.showStatus();
	std::cout << std::endl;

	Bob.attack("Jim");

	std::cout << std::endl;
	Jim.takeDamage(Bob.getAttackDamage());
	Jim.beRepaired(50);
	std::cout << std::endl;

	Joe.attack("Bob");

	Bob.takeDamage(Joe.getAttackDamage());

	Bob.beRepaired(50);

	std::cout << std::endl;
	Bob.showStatus();
	Jim.showStatus();
	Joe.showStatus();

	std::cout << std::endl;
	Joe.whoAmI();
	std::cout << std::endl;

	return (0);
}
