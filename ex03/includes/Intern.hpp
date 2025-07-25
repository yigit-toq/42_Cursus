/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:53:57 by ytop              #+#    #+#             */
/*   Updated: 2025/07/25 23:23:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"

class Intern
{
	private:

	public:
		 Intern();

		 Intern(const Intern &copy);

		~Intern();

		Intern &operator=(const Intern &copy);

		class FormNotFoundException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		AForm *makeForm(std::string formName, std::string target);
};

struct FormTypes
{
	std::string	name;
	std::string	message;
	AForm*		(*create)(const std::string&);
};

#endif
