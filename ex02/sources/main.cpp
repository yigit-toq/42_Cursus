/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:49:05 by ytop              #+#    #+#             */
/*   Updated: 2025/07/25 23:58:40 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void)
{
	std::cout << Y_CLR << std::endl << "Test too high and too low creation" << RESET << std::endl;
	std::cout << std::endl;

	try
	{
		Bureaucrat Bureaucrat1("Asuna ", +200);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat Brueaucrat2("Kirito", -200);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << Y_CLR << std::endl << "Test increment" << RESET << std::endl;
	std::cout << std::endl;

	Bureaucrat bob("Bob", 002);

	std::cout << std::endl;
	std::cout << bob << std::endl;
	try
	{
		bob.incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << bob << std::endl;
	try
	{
		bob.incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << bob << std::endl;

	std::cout << Y_CLR << std::endl << "Test decrement" << RESET << std::endl;
	std::cout << std::endl;

	Bureaucrat tim("Tim", 149);

	std::cout << std::endl;
	std::cout << tim << std::endl;
	try
	{
		tim.decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << tim << std::endl;
	try
	{
		tim.decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << tim << std::endl;

	std::cout << Y_CLR << std::endl << "RobotomyRequestForm"	<< RESET << std::endl;
	std::cout << std::endl;

	try
	{
		RobotomyRequestForm Robotomy_form		("I am a robotomy form");

		Bureaucrat Mr_Robotomy					("Mr_Robotomy", 20);

		std::cout << std::endl;

		Mr_Robotomy.executeForm	(Robotomy_form);
		Mr_Robotomy.signForm	(Robotomy_form);

		std::cout << std::endl;

		Mr_Robotomy.executeForm	(Robotomy_form);
		Mr_Robotomy.executeForm	(Robotomy_form);
		Mr_Robotomy.executeForm	(Robotomy_form);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << Y_CLR << std::endl << "ShrubberyCreationForm"	<< RESET << std::endl;
	std::cout << std::endl;

	try
	{
		ShrubberyCreationForm Shrubbery_form	("I am a shrubbery form");

		Bureaucrat Mr_Shrubbery					("Mr_Shrubbery", 40);

		std::cout << std::endl;

		std::cout << Shrubbery_form << std::endl;

		Mr_Shrubbery.signForm		(Shrubbery_form);

		std::cout << std::endl;

		std::cout << Shrubbery_form << std::endl;

		Mr_Shrubbery.executeForm	(Shrubbery_form);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << Y_CLR << std::endl << "PresidentialPardonForm"	<< RESET << std::endl;
	std::cout << std::endl;

	try
	{
		PresidentialPardonForm Presidential_form("I am a presidential form");

		Bureaucrat Mr_Presidential				("Mr_Presidential", 60);

		std::cout << std::endl;

		// Mr_Robotomy.executeForm		(Presidential_form);
		// Mr_Robotomy.signForm			(Presidential_form);


		Mr_Presidential.executeForm	(Presidential_form);
		Mr_Presidential.signForm	(Presidential_form);
		Mr_Presidential.executeForm	(Presidential_form);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
