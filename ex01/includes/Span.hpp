/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:07:02 by ytop              #+#    #+#             */
/*   Updated: 2025/08/02 13:13:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

class Span
{
	private:
		unsigned int		_maxsize;

		std::vector<int>	_numbers;

	public:
		 Span					(unsigned int N);

		 Span					(const Span &other);
		 Span &operator=		(const Span &other);

		~Span					();

		template	<typename	 InputIterator>
		void	addRange		(InputIterator begin, InputIterator end);

		void	addNumber		(int N);

		int		longestSpan		() const;
		int		shortestSpan	() const;

		void	enoughElements	() const;
};

template <typename  InputIterator>
void Span::addRange(InputIterator begin, InputIterator end)
{
	size_t size = std::distance(begin, end);

	if (_numbers.size() + size > _maxsize)
	{
		throw std::overflow_error("Adding this range would exceed the Span's capacity.");
	}

	_numbers.insert(_numbers.end(), begin, end);
}

#endif
