/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:56:53 by ytop              #+#    #+#             */
/*   Updated: 2025/03/19 00:56:53 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		const std::string	name;
		bool				sign;
		const int			recSign;
		const int			recExec;

	public:
		Form ();
		Form (const std::string &nName, int nRecSign, int nRecExec);

		Form (const Form &other);

		~Form();

		Form &operator = (const Form &other);

		std::string	getName () const;
		bool		getSign () const;

		int			getRecSign () const;
		int			getRecExec () const;

		void		beSigned(Bureaucrat &b);

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

		class FormSignedException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		void	gradeControl(int grade);
};

std::ostream& operator<<(std::ostream &os, const Form &f);

#endif
