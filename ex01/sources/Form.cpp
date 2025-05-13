/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:57:08 by ytop              #+#    #+#             */
/*   Updated: 2025/03/19 00:57:08 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form () : name("default"), recSign(45), recExec(10)
{
	this->sign = false;

	std::cout << G_CLR << "Constructor for " << B_CLR << this->name << RESET << std::endl;
}

Form::Form (const std::string &nName, int nRecSign, int nRecExec) : name(nName), recSign(nRecSign), recExec(nRecExec)
{
	std::cout << G_CLR << "Constructor for " << B_CLR << this->name << RESET << std::endl;

	gradeControl(recSign);
	gradeControl(recExec);

	this->sign = false;
}

Form::Form (const Form &copy) : name(getName()), recSign(getRecSign()), recExec(getRecExec())
{
	*this = copy;

	std::cout << Y_CLR << "Copy const  for " << B_CLR << this->name << RESET << std::endl;
}

Form::~Form()
{
	std::cout << R_CLR << "Destructor  for " << B_CLR << this->name << RESET << std::endl;
}

Form	&Form::operator=(const Form &copy)
{
	if (this != &copy)
	{
		this->sign = copy.sign;
	}

	std::cout << Y_CLR << "Copy assignment operator for " << B_CLR << this->name << RESET << std::endl;

	return (*this);
}

const char  *Form::GradeTooLowException ::what() const throw()
{
	return (R_CLR "Grade is too low !" RESET);
}

const char  *Form::GradeTooHighException::what() const throw()
{
	return (R_CLR "Grade is too high!" RESET);
}

const char *Form::FormSignedException::what() const throw()
{
	return (Y_CLR "Form is already signed!" RESET);
}

void	Form::gradeControl(int grade)
{
	if (grade > 150)
		throw GradeTooLowException();
	if (grade < 001)
		throw GradeTooHighException();
}

std::string	Form::getName() const
{
	return (this->name);
}

bool		Form::getSign() const
{
	return (this->sign);
}

int			Form::getRecSign() const
{
	return (this->recSign);
}

int			Form::getRecExec() const
{
	return (this->recExec);
}

void		Form::beSigned(Bureaucrat &b)
{
	if (this->sign)
	{
		throw FormSignedException();
	}

	if (b.getGrade() > this->recSign)
		std::cout << B_CLR << b.getName() << R_CLR << " couldn’t sign " << B_CLR << this->name << Y_CLR << " because his grade is too low." << RESET << std::endl;
	else
	{
		std::cout << B_CLR << b.getName() << G_CLR << " signed " << B_CLR << this->name << RESET << std::endl;
		this->sign = true;
	}
}

std::ostream&	operator<<(std::ostream &os, const Form &f)
{
	os << B_CLR << f.getName() << W_CLR << " form is currently";

	if (f.getSign())
		os << G_CLR << " signed ";
	else
		os << R_CLR << " not signed ";

	os << std::endl;

	os << Y_CLR << "and requires a grade of " << f.getRecSign() << " to be signed and a grade of " << f.getRecExec() << " to be executed." << RESET << std::endl;

	return (os);
}
