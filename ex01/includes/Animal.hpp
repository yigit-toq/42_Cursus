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
