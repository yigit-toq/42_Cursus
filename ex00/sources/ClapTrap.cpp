/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:17:08 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 17:15:30 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	std::cout << "ClapTrap default constructor" << std::endl;

	this->name = "ytop";
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 01;
}

ClapTrap::ClapTrap(const std::string name)
{
	std::cout << "ClapTrap name constructor" << std::endl;

	this->name = name;

	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 01;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
	std::cout << "ClapTrap copy constructor" << std::endl;

	*this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "ClapTrap assignation operator" << std::endl;

	this->name = other.name;
	this->hitPoints = other.hitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDamage = other.attackDamage;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor" << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	std::string	message;

	if (this->hitPoints > 0)
	{
		if (this->energyPoints > 0)
		{
			this->energyPoints -= 1;

			message = "attacks " + target + ", causing " + itoa(this->attackDamage) + " points of damage!";
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
	std::cout << "ClapTrap " << this->name << " " << message << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::string	message;

	if (this->hitPoints > 0)
	{
		this->hitPoints -= amount;

		message = "takes " + itoa(amount) + " points of damage!";
	}
	else
	{
		message = "has no hit points!";
	}
	std::cout << "ClapTrap " << this->name << " " << message << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	std::string	message;

	if (this->energyPoints > 0)
	{
		this->hitPoints += amount;

		message = "is repaired by " + itoa(amount) + "  points!";
	}
	else
	{
		message = "cannot be repaired because it has no energy!";
	}
	std::cout << "ClapTrap " << this->name << " " << message << std::endl;
}

std::string	ClapTrap::getName() const
{
	return (this->name);
}

std::string	itoa(int value)
{
	std::stringstream	ss;

	ss << value;
	return (ss.str());
}
