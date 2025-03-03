/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:58:03 by ytop              #+#    #+#             */
/*   Updated: 2025/03/03 17:14:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain* brain;

	public:
		Dog ();

		Dog (const Dog& other);

		Dog& operator=(const Dog& other);

		~Dog();

		void makeSound() const;

		std::string getIdea(int index) const;

		void setIdea(int index, std::string idea);

		Brain* getBrain() const;
};

#endif
