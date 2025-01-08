/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:13 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:47:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	type = "Cat";

	brain = new Brain();

	std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat& other)
{
	*this = other;

	std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	type = other.type;

	brain = new Brain(*other.brain);

	std::cout << "Cat assignation operator called" << std::endl;

	return (*this);
}

Cat::~Cat()
{
	delete (brain);

	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Meow Meow" << std::endl;
}

std::string Cat::getIdea(int index) const
{
	return (brain->getIdea(index));
}

void Cat::setIdea(int index, std::string idea)
{
	brain->setIdea(index, idea);
}
