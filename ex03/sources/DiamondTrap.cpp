/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:57:03 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 17:36:28 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
	std::cout << "DiamondTrap default constructor" << std::endl;

	this->name = ClapTrap::name + "_clap_name";

	this->hitPoints = FragTrap::hitPoints;
	this->energyPoints = ScavTrap::energyPoints;
	this->attackDamage = FragTrap::attackDamage;
}

DiamondTrap::DiamondTrap(std::string name) : ScavTrap(name + "_clap_name")
{
	std::cout << "Diamond name constructor" << std::endl;

	this->name = name + "_clap_name";

	this->hitPoints = FragTrap::hitPoints;
	this->energyPoints = ScavTrap::energyPoints;
	this->attackDamage = FragTrap::attackDamage;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
{
	std::cout << "DiamondTrap copy constructor" << std::endl;

	*this = other;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << "DiamondTrap assignation operator" << std::endl;

	this->name = other.name;
	this->hitPoints = other.hitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDamage = other.attackDamage;

	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor" << std::endl;
}

void	DiamondTrap::whoAmI()
{
	std::cout << this->getName() << std::endl;

	std::cout << ClapTrap::getName() << std::endl;
}
