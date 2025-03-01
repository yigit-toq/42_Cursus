/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:55:07 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 18:59:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

#define B_C "\033[1;34m"
#define Y_C "\033[1;33m"
#define G_C "\033[1;32m"
#define R_C "\033[1;31m"
#define E_C "\033[0m"

class Animal
{
	protected:
		std::string	type;

	public:
		Animal ();

		Animal (const Animal& other);

		Animal& operator=(const Animal& other);

		virtual ~Animal();

		std::string	getType() const;

		virtual void makeSound() const;
};

#endif
