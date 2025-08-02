/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:14:00 by ytop              #+#    #+#             */
/*   Updated: 2025/08/02 15:14:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template <typename T, typename Container = std::deque<T> >

class MutantStack : public std::stack<T, Container>
{
	public:
		 MutantStack			();

		 MutantStack			(const MutantStack& other);
		 MutantStack& operator=	(const MutantStack& other);

		~MutantStack			();

		typedef typename Container::iterator				iterator;
		typedef typename Container::const_iterator			const_iterator;

		typedef typename Container::reverse_iterator		reverse_iterator;
		typedef typename Container::const_reverse_iterator	const_reverse_iterator;

		iterator				begin	();
		iterator				end		();

		const_iterator			begin	() const;
		const_iterator			end		() const;

		reverse_iterator		rbegin	();
		reverse_iterator		rend	();

		const_reverse_iterator	rbegin	() const;
		const_reverse_iterator	rend	() const;
};

#include "MutantStack.tpp"

#endif
