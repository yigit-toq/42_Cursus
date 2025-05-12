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

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	private:
		const std::string	name;
		bool				sign;
		const int			recSign;
		const int			recExec;

	public:
		AForm ();
		AForm (const std::string &nName, int nRecSign, int nRecExec);

		AForm (const AForm &other);

		~AForm();

		AForm &operator = (const AForm &other);

		std::string	getName () const;
		bool		getSign () const;

		int			getRecSign () const;
		int			getRecExec () const;

		void		beSinged(Bureaucrat &b);

		virtual void execute(Bureaucrat const & executor) const = 0; // new

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

		class FormNotSignedException : public std::exception
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

		void	exectControl(Bureaucrat const &executor) const;
};

std::ostream& operator<<(std::ostream &os, const AForm &f);

#endif
