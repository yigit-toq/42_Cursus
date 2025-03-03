/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:06 by ytop              #+#    #+#             */
/*   Updated: 2025/03/03 16:14:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	this->type = "Animal";

	std::cout << G_C;
	std::cout << "Animal constructor called" << std::endl;
	std::cout << E_C;
}

Animal::Animal(const Animal& other)
{
	std::cout << G_C << "Animal copy constructor called" << E_C << std::endl;

	*this = other;
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << G_C << "Animal assignation operator called" << E_C << std::endl;

	if (this != &other)
		this->type = other.type;

	return (*this);
}

Animal::~Animal()
{
	std::cout << R_C << "Animal destructor called" << E_C << std::endl;
}

std::string	Animal::getType() const
{
	return (this->type);
}
