/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:58:55 by ytop              #+#    #+#             */
/*   Updated: 2025/03/24 00:58:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string target;

	public:
		RobotomyRequestForm ();

		RobotomyRequestForm (const std::string &target);
		RobotomyRequestForm (const RobotomyRequestForm &copy);

		~RobotomyRequestForm();

		RobotomyRequestForm &operator=(const RobotomyRequestForm &copy);

		void execute(Bureaucrat const &executor) const;
};

#endif
