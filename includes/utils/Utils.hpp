/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/08/05 22:08:45 by ytop             ###   ########.fr       */
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

		static	std::string							trim				(const std::string& str);

		static	std::vector<std::string>			split				(const std::string& str, char delimiter);

		static	std::vector<std::pair<char, char> >	ParseModeString		(const std::string& mode_string);

		static bool									IsModeWithParameter	(char mode);
};

#endif
