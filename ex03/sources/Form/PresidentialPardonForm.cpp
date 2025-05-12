/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:01:01 by ytop              #+#    #+#             */
/*   Updated: 2025/03/24 01:01:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm () : AForm("PresidentialPardonForm", 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm (const std::string				&target) : AForm("PresidentialPardonForm", 25, 5)
{
	std::cout << "Constructor for " << getName() << std::endl;

	this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm	&copy  ) : AForm("PresidentialPardonForm", 25, 5)
{
	*this = copy;

	std::cout << "Copy const  for " << getName() << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "Destructor  for " << getName() << std::endl;
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &copy)
{
	if (this != &copy)
	{
		this->target = copy.target;
	}

	std::cout << "Copy assigment operator for " << getName() << std::endl;

	return (*this);
}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	exectControl(executor);

	std::cout << this->target << " has been pardoned by Zafod Beeblebrox." << std::endl;
}
