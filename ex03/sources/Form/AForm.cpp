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

#include "AForm.hpp"

AForm::AForm () : name("default"), recSign(45), recExec(10)
{
	this->sign = false;

	std::cout << "Constructor for " << this->name << std::endl;
}

AForm::AForm (const std::string &nName, int nRecSign, int nRecExec) : name(nName), recSign(nRecSign), recExec(nRecExec)
{
	std::cout << "Constructor for " << this->name << std::endl;

	gradeControl(recSign);
	gradeControl(recExec);

	this->sign = false;
}

AForm::AForm (const AForm &copy) : name(getName()), recSign(getRecSign()), recExec(getRecExec())
{
	*this = copy;

	std::cout << "Copy const  for " << this->name << std::endl;
}

AForm::~AForm()
{
	std::cout << "Destructor  for " << this->name << std::endl;
}

AForm	&AForm::operator=(const AForm &copy)
{
	if (this != &copy)
	{
		this->sign = copy.sign;
	}

	std::cout << "Copy assigment operator for " << this->name << std::endl;

	return (*this);
}

const char  *AForm::GradeTooLowException ::what() const throw()
{
	return ("Grade is too low !");
}

const char  *AForm::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed!");
}

const char *AForm::FormSignedException::what() const throw()
{
	return ("Form is already signed!");
}

void	AForm::exectControl(Bureaucrat const &executor) const
{
	if (!this->sign)
	{
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->recExec)
	{
		throw GradeTooLowException();
	}
}

void	AForm::gradeControl(int grade)
{
	if (grade > 150)
		throw GradeTooLowException();
	if (grade < 001)
		throw GradeTooHighException();
}

std::string	AForm::getName() const
{
	return (this->name);
}

bool		AForm::getSign() const
{
	return (this->sign);
}

int			AForm::getRecSign() const
{
	return (this->recSign);
}

int			AForm::getRecExec() const
{
	return (this->recExec);
}

void		AForm::beSinged(Bureaucrat &b)
{
	if (this->sign)
	{
		throw FormSignedException();
	}

	if (b.getGrade() > this->recSign)
		std::cout << b.getName() << " couldn’t sign " << this->name << " because his grade is too low." << std::endl;
	else
	{
		std::cout << b.getName() << " signed " << this->name << std::endl;
		this->sign = true;
	}
}

std::ostream&	operator<<(std::ostream &os, const AForm &f)
{
	os << f.getName() << " form is currently";

	if (f.getSign())
		os << " signed ";
	else
		os << " not signed ";

	os << std::endl;

	os << "and requires a grade of " << f.getRecSign() << " to be signed and a grade of " << f.getRecExec() << " to be executed." << std::endl;

	return (os);
}
