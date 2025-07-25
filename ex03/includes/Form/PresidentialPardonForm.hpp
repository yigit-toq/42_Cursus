/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:00:19 by ytop              #+#    #+#             */
/*   Updated: 2025/07/25 16:15:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		std::string target;

	public:
		 PresidentialPardonForm();
		 PresidentialPardonForm(const std::string &target);

		 PresidentialPardonForm(const PresidentialPardonForm &copy);

		~PresidentialPardonForm();

		PresidentialPardonForm &operator=(const PresidentialPardonForm &copy);

		void execute(Bureaucrat const &executor) const;
};

#endif
