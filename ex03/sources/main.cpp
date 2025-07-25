/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:49:05 by ytop              #+#    #+#             */
/*   Updated: 2025/07/25 23:27:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

#include "Bureaucrat.hpp"

#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main()
{
	std::cout << "\033[33m" << std::endl << "Test too high and too low creation" << "\033[0m" << std::endl;

	try
	{
		Bureaucrat Bureaucrat1("Kirito", +200);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat Brueaucrat2("Asuna ", -200);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "\033[33m" << std::endl << "Test increment" << "\033[0m" << std::endl;

	Bureaucrat bob("Bob", 50);

	std::cout << bob;
	try
	{
		bob.incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << bob;
	try
	{
		bob.incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << bob;

	std::cout << "\033[33m" << std::endl << "Test decrement" << "\033[0m" << std::endl;

	Bureaucrat tim("Tim", 50);

	std::cout << tim;
	try
	{
		tim.decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << tim;
	try
	{
		tim.decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << tim;

	std::cout << "\033[33m" << std::endl << "RobotomyRequestForm"		<< "\033[0m" << std::endl;

	RobotomyRequestForm Robotomy_form("I am a robotomy form");

	Bureaucrat Mr_Robotomy("Mr_Robotomy", 45);

	Mr_Robotomy.executeForm	(Robotomy_form);
	Mr_Robotomy.signForm	(Robotomy_form);

	Mr_Robotomy.executeForm	(Robotomy_form);
	Mr_Robotomy.executeForm	(Robotomy_form);
	Mr_Robotomy.executeForm	(Robotomy_form);

	std::cout << "\033[33m" << std::endl << "ShrubberyCreationForm"		<< "\033[0m" << std::endl;

	ShrubberyCreationForm Shrubbery_form("I am a shrubbery form");

	Bureaucrat Mr_Shrubbery("Mr_Shrubbery", 130);

	std::cout << std::endl;

	std::cout << Shrubbery_form;

	Mr_Shrubbery.signForm		(Shrubbery_form);

	std::cout << Shrubbery_form;

	Mr_Shrubbery.executeForm	(Shrubbery_form);

	std::cout << "\033[33m" << std::endl << "PresidentialPardonForm"	<< "\033[0m" << std::endl;

	PresidentialPardonForm Presidential_form("I am a presidential form");

	Bureaucrat Mr_Presidential("Mr_Presidential", 5);

	Mr_Robotomy.executeForm		(Presidential_form);
	Mr_Robotomy.signForm		(Presidential_form);


	Mr_Presidential.executeForm	(Presidential_form);
	Mr_Presidential.signForm	(Presidential_form);
	Mr_Presidential.executeForm	(Presidential_form);

	std::cout << "\033[33m" << std::endl << "Intern" << "\033[0m" << std::endl;

	Intern	Jr_Intern;
	AForm*	Rb_Intern;

	Rb_Intern = Jr_Intern.makeForm	("robotomy request"	, "World");

	std::cout << Rb_Intern->getName	() << std::endl;

	delete (Rb_Intern);

	return (0);
}
