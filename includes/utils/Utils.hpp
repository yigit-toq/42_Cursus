/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/07/02 17:15:40 by ytop             ###   ########.fr       */
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

		std::string					trim	(const std::string& str);

		std::vector<std::string>	split	(const std::string& str, char delimiter);
};

#endif
