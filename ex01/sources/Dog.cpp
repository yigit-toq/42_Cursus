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
	this->type = "Dog";

	brain = new Brain();

	std::cout << G_C;
	std::cout << "Dog constructor called" << std::endl;
	std::cout << E_C;
}

Dog::Dog(const Dog& other)
{
	std::cout << G_C << "Dog copy constructor called" << E_C << std::endl;

	this->type = other.type;
	this->brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << G_C << "Dog assignation operator called" << E_C << std::endl;

	if (this != &other)
		this->type = other.type;

	this->brain = new Brain(*other.brain);

	return (*this);
}

Dog::~Dog()
{
	delete (brain);

	std::cout << R_C << "Dog destructor called" << E_C << std::endl;
}

void Dog::makeSound() const
{
	std::cout << B_C << "Woof Woof" << E_C << std::endl;
}

std::string Dog::getIdea(int index) const
{
	return (brain->getIdea(index));
}

void Dog::setIdea(int index, std::string idea)
{
	brain->setIdea(index, idea);
}
