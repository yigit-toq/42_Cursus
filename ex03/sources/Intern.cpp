/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:07 by ytop              #+#    #+#             */
/*   Updated: 2025/05/13 16:54:07 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern ()
{
	std::cout << G_CLR << "Constructor for Intern" << RESET << std::endl;
}

Intern::Intern (const Intern &copy)
{
	*this = copy;

	std::cout << G_CLR << "Copy const  for Intern" << RESET << std::endl;
}

Intern::~Intern()
{
	std::cout << G_CLR << "Destructor  for Intern" << RESET << std::endl;
}

Intern &Intern::operator=(const Intern &copy)
{
	(void)copy;

	std::cout << Y_CLR << "Copy assignment operator for " << RESET << std::endl;

	return (*this);
}

const char *Intern::FormNotFoundException::what() const throw()
{
	return (R_CLR "Form not found !" RESET);
}

AForm*	createRobotomy(const std::string &target)
{
	return new RobotomyRequestForm(target);
}

AForm*	createShrubbery(const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

AForm*	createPresident(const std::string &target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string formName, std::string target)
{
	FormTypes	formTypes[3] = 
	{
		{"robotomy request"   , "Intern creates RobotomyRequestForm"   , &createRobotomy}  ,
		{"shrubbery creation" , "Intern creates ShrubberyCreationForm" , &createShrubbery} ,
		{"presidential pardon", "Intern creates PresidentialPardonForm", &createPresident}
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == formTypes[i].name)
		{
			std::cout << G_CLR << formTypes[i].message << RESET << std::endl;

			return (formTypes[i].create(target));
		}
	}

	throw FormNotFoundException();
}
