/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:21 by ytop              #+#    #+#             */
/*   Updated: 2025/07/03 19:04:24 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "CommandHandler.hpp"

class NickCommand : public CommandHandler
{
	private:
		NickCommand				(const NickCommand& other);
		NickCommand& operator=	(const NickCommand& other);

	public:
		 NickCommand();
		~NickCommand();

		void execute(Client* sender, const Message& msg);
};

#endif
