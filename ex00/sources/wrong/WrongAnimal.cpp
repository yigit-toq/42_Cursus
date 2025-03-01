/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:24:15 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:10:20 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wrong/WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	this->type = "WrongAnimal";

	std::cout << R_C;
	std::cout << "WrongAnimal constructor called" << std::endl;
	std::cout << E_C;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	std::cout << R_C << "WrongAnimal copy constructor called" << E_C << std::endl;

	*this = other;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	std::cout << R_C << "WrongAnimal assignation operator called" << E_C << std::endl;

	if (this != &other)
		this->type = other.type;

	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << R_C << "WrongAnimal destructor called" << E_C << std::endl;
}

void WrongAnimal::makeSound() const
{
	std::cout << R_C << "WrongAnimal sound" << E_C << std::endl;
}

std::string	WrongAnimal::getType() const
{
	return (this->type);
}
