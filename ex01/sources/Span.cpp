/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:07:24 by ytop              #+#    #+#             */
/*   Updated: 2025/08/02 13:09:32 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span:: Span(unsigned int	N)		: _maxsize(N) {}

Span:: Span(const Span&		other)	: _maxsize(other._maxsize), _numbers(other._numbers) {}

Span  &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_maxsize = other._maxsize;
		_numbers = other._numbers;
	}

	return (*this);
}

Span::~Span() {}

void	Span::enoughElements() const
{
	if (_numbers.size() < 2)
	{
		throw std::logic_error("Not enough numbers to calculate a span.");
	}
}

void	Span::addNumber(int N)
{
	if (_numbers.size() > _maxsize - 1)
	{
		throw std::length_error("Span is full. Cannot add more numbers.");
	}

	_numbers.push_back(N);
}

int	Span::shortestSpan	() const
{
	enoughElements();

	std::vector<int> sorted = _numbers;

	std::sort(sorted.begin(), sorted.end());

	int	minspn = sorted[1] - sorted[0];

	for (size_t i = 1; i < sorted.size() - 1; ++i)
	{
		int span = sorted[i + 1] - sorted[i];

		if (span < minspn)
		{
			minspn = span;
		}
	}

	return (minspn);
}

int	Span::longestSpan	() const
{
	enoughElements();

	int min = *std::min_element(_numbers.begin(), _numbers.end());
	int max = *std::max_element(_numbers.begin(), _numbers.end());

	return (max - min);
}
