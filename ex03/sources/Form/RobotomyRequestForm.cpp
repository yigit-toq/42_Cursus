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
	std::cout << "Constructor for " << getName() << std::endl;

	this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm	&copy  ) : AForm("RobotomyRequestForm", 72, 45)
{
	*this = copy;

	std::cout << "Copy const  for " << getName() << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Destructor  for " << getName() << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &copy)
{
	if (this != &copy)
	{
		this->target = copy.target;
	}

	std::cout << "Copy assigment operator for " << getName() << std::endl;

	return (*this);
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	exectControl(executor);

	std::cout << "BZZZZZZZZZZZ... KRRRRRRRRRZZZZ... TAK-TAK-TAK... BZZZZRRRRRRR!" << std::endl;

	srand(time(0));

	if (rand() % 2)
		std::cout << this->target << " has been robotomized successfully." << std::endl;
	else
		std::cout << this->target << " robotomization failed." << std::endl;
}
