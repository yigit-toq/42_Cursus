/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/01/23 18:48:24 by ytop             ###   ########.fr       */
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

	std::cout << "Bob Energy: " << Bob.getEnergyPoints() << std::endl;
	std::cout << "Jim Energy: " << Jim.getEnergyPoints() << std::endl;
	std::cout << "Joe Energy: " << Joe.getEnergyPoints() << std::endl;

	std::cout << std::endl;
	std::cout << "Jim Hit Points: " << Jim.getHitPoints() << std::endl;

	std::cout << std::endl;

	Bob.attack("Jim");

	std::cout << std::endl;

	Jim.takeDamage(Bob.getAttackDamage());

	std::cout << std::endl;
	std::cout << "Jim Hit Points: " << Jim.getHitPoints() << std::endl;
	std::cout << std::endl;

	Jim.beRepaired(5);

	std::cout << std::endl;
	std::cout << "Jim Hit Points: " << Jim.getHitPoints() << std::endl;

	std::cout << std::endl;

	std::cout << "Bob Energy: " << Bob.getEnergyPoints() << std::endl;
	std::cout << "Jim Energy: " << Jim.getEnergyPoints() << std::endl;
	std::cout << "Joe Energy: " << Joe.getEnergyPoints() << std::endl;

	std::cout << std::endl;
	std::cout << "Bob Hit Points: " << Bob.getHitPoints() << std::endl;

	std::cout << std::endl;

	Joe.attack("Bob");

	std::cout << std::endl;

	Bob.takeDamage(Joe.getAttackDamage());

	std::cout << std::endl;
	std::cout << "Bob Hit Points: " << Bob.getHitPoints() << std::endl;
	std::cout << std::endl;

	Bob.beRepaired(5);

	std::cout << std::endl;

	std::cout << "Bob Energy: " << Bob.getEnergyPoints() << std::endl;
	std::cout << "Jim Energy: " << Jim.getEnergyPoints() << std::endl;
	std::cout << "Joe Energy: " << Joe.getEnergyPoints() << std::endl;

	std::cout << std::endl;
	std::cout << "Bob Hit Points: " << Bob.getHitPoints() << std::endl;

	std::cout << std::endl;

	Joe.whoAmI();

	std::cout << std::endl;
	
	return (0);
}
