/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:13 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 19:02:14 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	this->type = "Cat";

	std::cout << G_C;
	std::cout << "Cat constructor called" << std::endl;
	std::cout << E_C;
}

// Cat::Cat(const Cat& other)
// {
// 	std::cout << G_C << "Cat copy constructor called" << E_C << std::endl;
//
// 	*this = other;
// }

Cat& Cat::operator=(const Cat& other)
{
	std::cout << G_C << "Cat assignation operator called" << E_C << std::endl;

	if (this != &other)
		this->type = other.type;

	return (*this);
}

Cat::~Cat()
{
	std::cout << R_C << "Cat destructor called" << E_C << std::endl;
}

void Cat::makeSound() const
{
	std::cout << B_C << "Meow Meow" << E_C << std::endl;
}
