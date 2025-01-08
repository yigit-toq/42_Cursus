/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:02:19 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:47:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	type = "Dog";

	brain = new Brain();

	std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog& other)
{
	*this = other;

	std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	type = other.type;

	brain = new Brain(*other.brain);

	std::cout << "Dog assignation operator called" << std::endl;

	return (*this);
}

Dog::~Dog()
{
	delete (brain);

	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Woof Woof" << std::endl;
}

std::string Dog::getIdea(int index) const
{
	return (brain->getIdea(index));
}

void Dog::setIdea(int index, std::string idea)
{
	brain->setIdea(index, idea);
}
