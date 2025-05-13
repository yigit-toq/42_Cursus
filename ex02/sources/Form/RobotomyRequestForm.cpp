/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:59:49 by ytop              #+#    #+#             */
/*   Updated: 2025/03/24 00:59:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm () : AForm("RobotomyRequestForm", 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm (const std::string			&target) : AForm("RobotomyRequestForm", 72, 45)
{
	std::cout << G_CLR << "Constructor for " << B_CLR << getName() << RESET << std::endl;

	this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm	&copy  ) : AForm("RobotomyRequestForm", 72, 45)
{
	*this = copy;

	std::cout << Y_CLR << "Copy const  for " << B_CLR << getName() << RESET << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << R_CLR << "Destructor  for " << B_CLR << getName() << RESET << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &copy)
{
	if (this != &copy)
	{
		this->target = copy.target;
	}

	std::cout << Y_CLR << "Copy assignment operator for " << B_CLR << getName() << RESET << std::endl;

	return (*this);
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	exectControl(executor);

	std::cout << Y_CLR << "BZZZZZZZZZZZ... KRRRRRRRRRZZZZ... TAK-TAK-TAK... BZZZZRRRRRRR!" << RESET << std::endl;

	srand(time(0));

	if (rand() % 2)
		std::cout << W_CLR << this->target << G_CLR << " has been robotomized successfully." << RESET << std::endl;
	else
		std::cout << W_CLR << this->target << R_CLR << " robotomization failed." << RESET << std::endl;
}
