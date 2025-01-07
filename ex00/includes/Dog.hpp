/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:58:03 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 18:07:28 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

#include <iostream>

class Dog : public Animal
{
	public:
		Dog ();

		Dog (const Dog& other);

		Dog& operator=(const Dog& other);

		~Dog();
};

#endif
