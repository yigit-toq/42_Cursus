/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:57:07 by ytop              #+#    #+#             */
/*   Updated: 2025/03/24 00:57:07 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm () : AForm("ShrubberyCreationForm", 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm (const std::string             &target) : AForm("ShrubberyCreationForm", 145, 137)
{
	std::cout << "Constructor for " << this->getName() << std::endl;

	this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm (const ShrubberyCreationForm   &copy  ) : AForm("ShrubberyCreationForm", 145, 137)
{
	*this = copy;

	std::cout << "Copy const  for " << this->getName() << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "Destructor  for " << this->getName() << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy)
{
	if (this != &copy)
	{
		this->target = copy.target;
	}

	std::cout << "Copy assigment operator for " << this->getName() << std::endl;

	return (*this);
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	AForm::execute(executor);

	std::ofstream file(this->target + "_shrubbery");

	if (!file.is_open())
	{
		std::cerr << "Error: could not open file" << std::endl;
		return ;
	}

	file << "       _-_       \n"
			"    /~~   ~~\\   \n"
			" /~~         ~~\\\n"
			"{               }\n"
			" \\  _       _  /\n"
			"   ~  \\\\ //    \n"
			"       | |       \n"
			"       | |       \n"
			"      // \\\\      ";

	file.close();
	std::cout << "Shrubbery has been created." << std::endl;
}
