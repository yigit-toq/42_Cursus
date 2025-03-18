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

	std::cout << "Constructor for " << this->name << std::endl;
}

Form::Form (const std::string &nName, int nRecSign, int nRecExec) : name(nName), recSign(nRecSign), recExec(nRecExec)
{
	std::cout << "Constructor for " << this->name << std::endl;

	gradeControl(recSign);
	gradeControl(recExec);

	this->sign = false;
}

Form::Form (const Form &copy) : name(getName()), recSign(getRecSign()), recExec(getRecExec())
{
	*this = copy;

	std::cout << "Copy const  for " << this->name << std::endl;
}

Form::~Form()
{
	std::cout << "Destructor  for " << this->name << std::endl;
}

Form	&Form::operator=(const Form &copy)
{
	if (this != &copy)
	{
		this->sign = copy.sign;
	}

	std::cout << "Copy assigment operator for " << this->name << std::endl;

	return (*this);
}

const char  *Form::GradeTooLowException ::what() const throw()
{
	return ("Grade is too low !");
}

const char  *Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
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

void		Form::beSinged(Bureaucrat &b)
{
	if (b.getGrade() > this->getRecSign)
		std::cout << "Bureaucrat " << b.getName() << " couldn't signed the " << this->getName() << " form because they have a grade of " << b.getGrade() << " and the form requires " << this->getReqSign() << " grade!" << std::endl;
}
