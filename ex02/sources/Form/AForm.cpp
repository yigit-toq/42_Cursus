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
	if (b.getGrade() > this->getRecSign)
		std::cout << "Bureaucrat " << b.getName() << " couldn't signed the " << this->getName() << " form because they have a grade of " << b.getGrade() << " and the form requires " << this->getRecSign() << " grade!" << std::endl;
}

std::ostream&	operator<<(std::ostream &os, const AForm &f)
{
	os << f.getName() << " form is currently";

	if (f.getSign())
		os << " signed";
	else
		os << " not signed";

	os << " and requires " << f.getRecSign() << " grade to sign and " << f.getRecExec() << " grade to execute.";

	return (os);
}

void	AForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getRecExec())
		std::cout << "Bureaucrat " << executor.getName() << " couldn't execute the " << this->getName() << " form because they have a grade of " << executor.getGrade() << " and the form requires " << this->getRecExec() << " grade!" << std::endl;
}
