/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:58:12 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 18:06:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

#include <iostream>

class Cat : public Animal
{
	public:
		Cat ();

		Cat (const Cat& other);

		Cat& operator=(const Animal& other);

		~Cat();
};

#endif
