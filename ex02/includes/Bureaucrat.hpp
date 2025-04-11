/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:49:17 by ytop              #+#    #+#             */
/*   Updated: 2025/03/18 23:49:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

#include "AForm.hpp"

class AForm;

class Bureaucrat
{
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat ();
		Bureaucrat (const std::string &name, int grade);

		Bureaucrat (const Bureaucrat &other);

		~Bureaucrat();

		Bureaucrat &operator = (const Bureaucrat &other);

		std::string	getName () const;
		int			getGrade() const;

		void		incrementGrade();
		void		decrementGrade();

	 	void 		executeForm(AForm const & form);

		class GradeTooHighException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class GradeTooLowException  : public std::exception
		{
			public:
				const char *what() const throw();
		};

		void	gradeControl(int grade);

		void	signForm(AForm &form);
};

std::ostream&	operator<<(std::ostream &os, const Bureaucrat &b);

#endif
