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

#include "Form.hpp"

int	main(void)
{
	try
	{
		Bureaucrat a("Recep", 150);
		Bureaucrat b("Yigit", 1);

		std::cout << std::endl;

		Form high("Form1", 6, 2);

		std::cout << std::endl;

		std::cout << high << std::endl;

		a.signForm(high);
		b.signForm(high);

		std::cout << high << std::endl;

		Form low("Form2", 150, 151);

		a.signForm(low);
		b.signForm(low);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
