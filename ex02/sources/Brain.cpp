/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:27:36 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:43:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << Y_C << "Brain constructor called" << E_C << std::endl;
}

Brain::Brain(const Brain& other)
{
	std::cout << Y_C << "Brain copy constructor called" << E_C << std::endl;

	*this = other;
}

Brain& Brain::operator=(const Brain& other)
{
	std::cout << Y_C << "Brain assignation operator called" << E_C << std::endl;

	for (int i = 0; i < 100; i++)
		this->ideas[i] = other.ideas[i];

	return (*this);
}

Brain::~Brain()
{
	std::cout << Y_C << "Brain destructor called" << E_C << std::endl;
}

void Brain::setIdea(int index, std::string idea)
{
	ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
	return (ideas[index]);
}
