/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:49:17 by ytop              #+#    #+#             */
/*   Updated: 2025/07/25 16:18:31 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

#define R_CLR "\033[1;31m"
#define G_CLR "\033[1;32m"
#define Y_CLR "\033[1;33m"
#define B_CLR "\033[1;34m"
#define W_CLR "\033[1;37m"
#define RESET "\033[0m"

class Bureaucrat
{
	private:
		const std::string	name;
		int					grade;

	public:
		 Bureaucrat();
		 Bureaucrat(const std::string &name, int grade);

		 Bureaucrat(const Bureaucrat &other);

		~Bureaucrat();

		Bureaucrat &operator = (const Bureaucrat &other);

		std::string	getName			() const;
		int			getGrade		() const;

		void		incrementGrade	();
		void		decrementGrade	();

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
};

std::ostream&	operator<<(std::ostream &os, const Bureaucrat &b);

#endif
