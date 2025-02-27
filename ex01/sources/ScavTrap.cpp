/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:19:43 by ytop              #+#    #+#             */
/*   Updated: 2025/02/27 17:25:41 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "ScavTrap default constructor" << std::endl;

	this->name = "ytop";
	this->hitPoints = ClapTrap::hitPoints;
	this->energyPoints = 50;
	this->attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name)
{
	std::cout << "ScavTrap name constructor" << std::endl;

	this->name = name;
	this->hitPoints = ClapTrap::hitPoints;
	this->energyPoints = 50;
	this->attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &other)
{
	std::cout << "ScavTrap copy constructor" << std::endl;

	*this = other;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap assignation operator" << std::endl;

	this->name = other.name;
	this->hitPoints = other.hitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDamage = other.attackDamage;

	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor" << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	std::string	message;

	if (this->hitPoints > 0)
	{
		if (this->energyPoints > 0)
		{
			message = "attacks " + target + ", causing " + itoa(this->attackDamage) + " points of damage!";

			this->energyPoints -= 1;
		}
		else
		{
			message = "cannot attack " + target + " because it has no energy!";
		}
	}
	else
	{
		message = "cannot attack " + target + " because it has no hit points!";
	}
	std::cout << "ScavTrap " << this->name << " " << message << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << this->name << " has entered in Gate keeper mode" << std::endl;
}
