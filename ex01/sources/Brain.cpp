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
	std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& other)
{
	*this = other;

	std::cout << "Brain copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];

	std::cout << "Brain assignation operator called" << std::endl;

	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, std::string idea)
{
	ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
	return (ideas[index]);
}
