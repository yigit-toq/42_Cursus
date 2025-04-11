/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:49:05 by ytop              #+#    #+#             */
/*   Updated: 2025/03/18 23:49:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"

#include "Bureaucrat.hpp"

int	main(void)
{
	PresidentialPardonForm form("target");
	Bureaucrat b("b", 1);

	b.signForm(form);
	b.executeForm(form);

	ShrubberyCreationForm form2("target");
	Bureaucrat b2("b2", 1);
	return (0);
}
