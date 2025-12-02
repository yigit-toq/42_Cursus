/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:05:50 by ytop              #+#    #+#             */
/*   Updated: 2025/12/02 16:05:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// ========== Orthodox Canonical Form ==========

RPN:: RPN() {}

RPN:: RPN(const RPN& other) : _stack(other._stack) {}

RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
	return (*this);
}

// ========== Utility Functions ==========

bool	RPN::isOperator		(const std::string& token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool	RPN::isValidNumber	(const std::string& token) const
{
	if (token.empty())
		return (false);

	size_t start = 0;

	if (token[0] == '-' || token[0] == '+')
		start = 1;

	for (size_t i = start; i < token.length(); i++)
	{
		if (!isdigit(token[i]))
			return  (false);
	}

	if (token.length() == 1 && isdigit(token[0]))
		return (true);

	if (token.length() == 2 && token[0] == '-' && isdigit(token[1]))
		return (true);

	return (false);
}

int		RPN::performOperation	(int a, int b, char op) const
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			return a / b;
		default:
				throw std::runtime_error("Error: invalid operator");
	}
}

// ========== Main Functions ==========

int		RPN::Calculate			(const std::string& expression)
{
	std::istringstream	iss(expression);
	std::string			token;

	while (!_stack.empty())
	{
		_stack.pop();
	}

	while (iss >> token)
	{
		if (isValidNumber	(token))
		{
			_stack.push(atoi(token.c_str()));
		}
		else if (isOperator(token))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: insufficient operands");

			int b = _stack.top();
			_stack.pop	();
			int a = _stack.top();
			_stack.pop	();

			int result = performOperation(a, b, token[0]);

			_stack.push	(result);
		}
		else
		{
			throw std::runtime_error("Error: invalid token");
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid expression");

	return (_stack.top());
}
