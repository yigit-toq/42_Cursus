/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:36:57 by ytop              #+#    #+#             */
/*   Updated: 2025/07/24 20:41:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class TopicCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		TopicCommand			(const TopicCommand& other);
		TopicCommand& operator=	(const TopicCommand& other);

	public:
		 TopicCommand			(Server& server);
		~TopicCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
