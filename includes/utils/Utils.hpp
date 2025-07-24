/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/07/03 15:12:30 by ytop             ###   ########.fr       */
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

		static std::string					trim	(const std::string& str);

		static std::vector<std::string>		split	(const std::string& str, char delimiter);
};

#endif
