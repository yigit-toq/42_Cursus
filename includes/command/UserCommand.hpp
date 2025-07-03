/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:21 by ytop              #+#    #+#             */
/*   Updated: 2025/07/03 19:08:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "CommandHandler.hpp"

class UserCommand : public CommandHandler
{
	private:
		UserCommand				(const UserCommand& other);
		UserCommand& operator=	(const UserCommand& other);

	public:
		 UserCommand();
		~UserCommand();

		void execute(Client* sender, const Message& msg);
};

#endif
