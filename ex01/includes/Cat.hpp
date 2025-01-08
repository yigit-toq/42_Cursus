/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:58:12 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:47:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain* brain;

	public:
		Cat ();

		Cat (const Cat& other);

		Cat& operator=(const Cat& other);

		~Cat();

		void makeSound() const;

		std::string getIdea(int index) const;

		void setIdea(int index, std::string idea);
};

#endif
