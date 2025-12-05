/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:59:43 by ytop              #+#    #+#             */
/*   Updated: 2025/12/05 14:36:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include <iostream>
#include <algorithm>

#include <sys/time.h>

class PmergeMe
{
	private:
		std::vector<int>	_vec;
		std::deque <int>	_deq;

		void	mergeInsertSortVec	(std::vector<int>& arr);
		void	mergeInsertSortDeq	(std::deque<int> & arr);

		std::vector<size_t>	generateJacobsthalSequence(size_t n) const;

		template<typename Container>
		typename Container::iterator	binaryInsert(Container& container, 
											typename Container::iterator begin,
											typename Container::iterator end,
											int value);

		template<typename Container>
		bool	isSorted	(const Container	&arr) const;

		bool	isValidN	(const std::string	&str) const;

		int		stoi		(const std::string	&str) const;

		double	getTimeInMS	() const;

	public :
		 PmergeMe			();
		 PmergeMe			(const PmergeMe& other);
		 PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe			();

		void	ParseInput	(int argc, char** argv);
		void	Sort		();
		void	Display		() const;
};

template<typename Container>
typename Container::iterator	PmergeMe::binaryInsert
(
	Container& container,
	typename Container::iterator begin,
	typename Container::iterator end,
	int value)
{
	typename Container::iterator pos = std::lower_bound(begin, end, value);

	return container.insert(pos, value);
}

template<typename Container>
bool	PmergeMe::isSorted(const Container& arr) const
{
	if (arr.size() <= 1)
		return true ;

	typename Container::const_iterator	it		= arr.begin();
	typename Container::const_iterator	next	= it;

	++next;

	while (next != arr.end())
	{
		if (*next < *it)
		{
			return false;
		}

		++it;
		++next;
	}

	return true;
}

#endif
