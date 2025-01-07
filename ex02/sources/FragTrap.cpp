/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:13 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 16:37:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	std::cout << "FragTrap default constructor" << std::endl;

	this->name = "ytop";
	this->hitPoints = ClapTrap::hitPoints;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

FragTrap::FragTrap(std::string name)
{
	std::cout << "FragTrap name constructor" << std::endl;

	this->name = name;
	this->hitPoints = ClapTrap::hitPoints;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &other)
{
	std::cout << "FragTrap copy constructor" << std::endl;

	*this = other;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
	std::cout << "FragTrap assignation operator" << std::endl;

	this->name = other.name;
	this->hitPoints = other.hitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDamage = other.attackDamage;

	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor" << std::endl;
}

void	FragTrap::attack(const std::string& target)
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
	std::cout << "FragTrap " << this->name << " " << message << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->name << " says high fives guys!" << std::endl;
}
