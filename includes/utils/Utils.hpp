/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/08/04 22:13:19 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

class Utils
{
	private:

	public:
		 Utils ();
		~Utils ();

		static	std::string							trim			(const std::string& str);

		static	std::vector<std::string>			split			(const std::string& str, char delimiter);

		static	std::vector<std::pair<char, char> >	ParseModeString	(const std::string& mode_string)
		{
				std::vector<std::pair<char, char> >	parsed_modes;

			char current_sign = '+';

			for (size_t i = 0; i < mode_string.length(); ++i)
			{
				char c = mode_string[i];

				if (c == '+' || c == '-')
				{
					current_sign = c;
				}
				else
				{
					parsed_modes.push_back(std::make_pair(current_sign, c));
				}
			}
			return (parsed_modes);
		}

		static bool	IsModeWithParameter(char mode)
		{
			return (mode == 'o' || mode == 'l' || mode == 'k');
		}
};

#endif
