/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:57:48 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:58:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Message
{
	private:
		//
		std::string					_prefix;
		std::string					_command;
		std::vector<std::string>	_parameters;
		//

		Message				(const Message& other);
		Message& operator=	(const Message& other);

	public:
		 Message			();
		~Message			();

		bool								Parse		(const std::string& raw_message);

		const std::string&					GetPrefix		() const; //
		const std::string&					GetCommand		() const; //
		const std::vector<std::string>&		GetParameters	() const; //

		void								Print		() const;
};

#endif
