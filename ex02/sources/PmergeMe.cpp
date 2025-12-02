/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:59:41 by ytop              #+#    #+#             */
/*   Updated: 2025/12/02 17:59:41 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ========== Orthodox Canonical Form ==========

PmergeMe:: PmergeMe() {}

PmergeMe:: PmergeMe(const PmergeMe& other) { *this = other; }

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}

	return (*this);
}

// ========== Utility Functions ==========

double	PmergeMe::getTimeInMS() const
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);

	return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

bool	PmergeMe::isValidN(const std::string& str) const
{
	if (str.empty())
	{
		return (false);
	}

	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return  (false);
		}
	}

	return (true);
}

int		PmergeMe::stoi(const std::string& str) const
{
	long	num = atol(str.c_str());

	if (num < 0 || num > 2147483647)
	{
		throw std::runtime_error("Error: number out of range");
	}

	return static_cast<int>(num);
}

// ========== Jacobsthal Sequence Generator ==========

std::vector<size_t>	PmergeMe::generateJacobsthalSequence(size_t n) const
{
	std::vector<size_t>	jacobsthal;
	
	if (n == 0)
		return (jacobsthal);

	std::vector<size_t>	jNumbers;

	jNumbers.push_back(0);
	jNumbers.push_back(1);
	
	while (jNumbers.back() < n)
	{
		size_t next = jNumbers[jNumbers.size() - 1] + 2 * jNumbers[jNumbers.size() - 2];

		jNumbers.push_back(next);
	}

	std::vector<bool> inserted(n, false);
	
	for (size_t i = 3; i < jNumbers.size(); i++)
	{
		size_t curr = jNumbers[i];
		size_t prev = jNumbers[i - 1];

		for (size_t j = std::min(curr, n); j > prev && j > 0; j--)
		{
			if (inserted[j - 1] == false)
			{
				jacobsthal.push_back(j - 1);

				inserted[j - 1] = true;
			}
		}
	}

	for (size_t i = 0; i < n; i++)
	{
		if (!inserted[i])
		{
			jacobsthal.push_back(i);
		}
	}

	return (jacobsthal);
}

// ========== Input Parsing ==========

void PmergeMe::ParseInput(int argc, char** argv)
{
	if (argc < 2)
	{
		throw std::runtime_error("Error: no input provided");
	}

	for (int i = 1; i < argc; i++)
	{
		std::string	arg(argv[i]);

		if (!isValidN (arg))
		{
			throw std::runtime_error("Error: invalid input");
		}

		int num = stoi(arg);

		if (num < 0)
		{
			throw std::runtime_error("Error: negative number not allowed");
		}

		_vec.push_back(num);
		_deq.push_back(num);
	}

	if (_vec.empty())
	{
		throw std::runtime_error("Error: no valid numbers provided");
	}
}

// ========== Display Functions ==========

void	PmergeMe::Display() const
{
	std::cout << "Before: ";

	for (size_t i = 0; i < _vec.size() && i < 5; i++)
	{
		std::cout << _vec[i];

		if (i < _vec.size() - 1 && i < 4)
			std::cout << " ";
	}

	if (_vec.size() > 5)
	{
		std::cout << " [...]";
	}

	std::cout << std::endl;
}

// ========== Ford-Johnson Wrappers ==========

void	PmergeMe::mergeInsertSortVec(std::vector<int>& arr)
{
	mergeInsertSort(arr);
}

void	PmergeMe::mergeInsertSortDeq(std::deque <int>& arr)
{
	mergeInsertSort(arr);
}

// ========== Main Functions ==========

void	PmergeMe::Sort()
{
	Display();

	double startVec = getTimeInMS();
	std::vector<int> vecCopy = _vec;

	mergeInsertSortVec(vecCopy);

	double	endVec	= getTimeInMS();
	double	timeVec = endVec - startVec;

	double startDeq = getTimeInMS();
	std::deque <int> deqCopy = _deq;

	mergeInsertSortDeq(deqCopy);

	double	endDeq	= getTimeInMS();
	double	timeDeq = endDeq - startDeq;

	if (!isSorted(vecCopy))
	{
		throw std::runtime_error("ERROR: Vec sorting failed!");
	}

	if (!isSorted(deqCopy))
	{ 
		throw std::runtime_error("ERROR: Deq sorting failed!");
	}

	std::cout << "After:  ";
	for (size_t i = 0; i < vecCopy.size() && i < 5; i++)
	{
		std::cout << vecCopy[i];

		if (i < vecCopy.size() - 1 && i < 4)
		{
			std::cout << " ";
		}
	}

	if (vecCopy.size() > 5)
	{
		std::cout << " [...]";
	}

	std::cout << std::endl;

	std::cout << "Time to process a range of " << _vec.size() 
			<< " elements with std::vector : " << timeVec << " us" << std::endl;

	std::cout << "Time to process a range of " << _deq.size() 
			<< " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
