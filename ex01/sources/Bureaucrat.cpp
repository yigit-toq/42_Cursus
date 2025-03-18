/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:52:32 by ytop              #+#    #+#             */
/*   Updated: 2025/03/18 23:52:32 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat () : name("default"), grade(150) {}

Bureaucrat::Bureaucrat (const std::string &name, int grade) : name(name)
{
	std::cout << "Constructor for " << this->name << std::endl;

	gradeControl(grade);

	this->grade = grade;
}

Bureaucrat::Bureaucrat (const Bureaucrat &copy)
{
	*this = copy;

	std::cout << "Copy const  for " << this->name << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor  for " << this->name << std::endl;
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &copy)
{
	if (this != &copy)
	{
		this->grade = copy.grade;
	}

	std::cout << "Copy assigment operator for " << this->name << std::endl;

	return (*this);
}

const char  *Bureaucrat::GradeTooLowException ::what() const throw()
{
	return ("Grade is too low !");
}

const char  *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

void	Bureaucrat::gradeControl(int grade)
{
	if (grade > 150)
		throw GradeTooLowException();
	if (grade < 001)
		throw GradeTooHighException();
}

void	Bureaucrat::incrementGrade()
{
	this->grade++;

	gradeControl(grade);
}

void	Bureaucrat::decrementGrade()
{
	this->grade--;

	gradeControl(grade);
}

std::string	Bureaucrat::getName () const
{
	return (this->name);
}

int			Bureaucrat::getGrade() const
{
	return (this->grade);
}

std::ostream&	operator<<(std::ostream &os, const Bureaucrat &b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade();

	return (os);
}

void			Bureaucrat::signForm(Form &form)
{
	form.beSinged(*this);
}
