/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:52:32 by ytop              #+#    #+#             */
/*   Updated: 2025/07/25 17:06:02 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat () : name("default"), grade(150) {}

Bureaucrat::Bureaucrat (const std::string &name, int grade) : name(name)
{
	std::cout << G_CLR << "Constructor for " << B_CLR << this->name << RESET << std::endl;

	gradeControl(grade);

	this->grade = grade;
}

Bureaucrat::Bureaucrat (const Bureaucrat &copy)
{
	*this = copy;

	std::cout << Y_CLR << "Copy const  for " << B_CLR << this->name << RESET << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << R_CLR << "Destructor  for " << B_CLR << this->name << RESET << std::endl;
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &copy)
{
	if (this != &copy)
	{
		this->grade = copy.grade;
	}

	std::cout << Y_CLR << "Copy assignment operator for " << B_CLR << this->name << RESET << std::endl;

	return (*this);
}

const char  *Bureaucrat::GradeTooLowException ::what() const throw()
{
	return (R_CLR "Grade is too low !" RESET);
}

const char  *Bureaucrat::GradeTooHighException::what() const throw()
{
	return (R_CLR "Grade is too high!" RESET);
}

void	Bureaucrat::gradeControl(int grade)
{
	if (grade > 150)
		throw GradeTooLowException	();
	if (grade < 001)
		throw GradeTooHighException	();
}

void	Bureaucrat::incrementGrade()
{
	this->grade--;

	gradeControl(grade);
}

void	Bureaucrat::decrementGrade()
{
	this->grade++;

	gradeControl(grade);
}

std::string	Bureaucrat::getName () const
{
	return (this->name	);
}

int			Bureaucrat::getGrade() const
{
	return (this->grade	);
}

std::ostream&	operator<<(std::ostream &os, const Bureaucrat &b)
{
	os << B_CLR << b.getName() << Y_CLR << ", bureaucrat grade " << b.getGrade() << RESET;

	return (os);
}
