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
	std::cout << G_CLR << "Constructor for " << B_CLR << getName() << RESET << std::endl;

	this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm	&copy  ) : AForm("PresidentialPardonForm", 25, 5)
{
	*this = copy;

	std::cout << Y_CLR << "Copy const  for " << B_CLR << getName() << RESET << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << R_CLR << "Destructor  for " << B_CLR << getName() << RESET << std::endl;
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &copy)
{
	if (this != &copy)
	{
		this->target = copy.target;
	}

	std::cout << Y_CLR << "Copy assignment operator for " << B_CLR << getName() << RESET << std::endl;

	return (*this);
}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	exectControl(executor);

	std::cout << W_CLR << this->target << Y_CLR << " has been pardoned by Zafod Beeblebrox." << RESET << std::endl;
}
