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

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm () : AForm("ShrubberyCreationForm", 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm (const std::string             &target) : AForm("ShrubberyCreationForm", 145, 137)
{
	std::cout << G_CLR << "Constructor for " << B_CLR << getName() << RESET << std::endl;

	this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm (const ShrubberyCreationForm   &copy  ) : AForm("ShrubberyCreationForm", 145, 137)
{
	*this = copy;

	std::cout << Y_CLR << "Copy const  for " << B_CLR << getName() << RESET << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << R_CLR << "Destructor  for " << B_CLR << getName() << RESET << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy)
{
	if (this != &copy)
	{
		this->target = copy.target;
	}

	std::cout << Y_CLR << "Copy assignment operator for " << B_CLR << getName() << RESET << std::endl;

	return (*this);
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	exectControl(executor);

	std::ofstream file((this->target + "_shrubbery").c_str());

	if (!file.is_open())
	{
		std::cerr << R_CLR << "Error: could not open file" << RESET << std::endl;
		return ;
	}

	file << "       _-_       \n"
			"    /~~   ~~\\   \n"
			" /~~         ~~\\\n"
			"{               }\n"
			" \\  _       _  /\n"
			"      \\\\ //    \n"
			"       | |       \n"
			"       | |       \n"
			"      // \\\\      ";

	file.close();
	std::cout << G_CLR << "Shrubbery has been created." << RESET << std::endl;
}
