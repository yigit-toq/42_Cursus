/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:40:46 by ytop              #+#    #+#             */
/*   Updated: 2025/08/18 01:40:46 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

//eğer bot sunucudaysa clientin botu kanala çağırabilmesi sağlanacak
//opsiyonel nick ekleme seçeneği eklenecek
//botun sunucuya gelen kullancılara hoşgeldin mesajı göndermesi sağlanacak
//makefile içerisinde ayrı bir target olarak eklenecek
//kullanıcı !kimsin yazdığında clientin bilgilerini verecel

const int BUFFER_SIZE = 1024;

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc, char **argv)
{
	try
	{
		if (argc != 4)
		{
			std::stringstream ss;
			ss << "Usage: " << argv[0] << " <server_ip> <server_port> <password>";
			throw std::runtime_error(ss.str());
		}

		std::string server_ip = argv[1];

		int server_port = std::stoi(argv[2]);

		std::string password = argv[3];

		int bot_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (bot_socket == -1)
		{
			throw std::runtime_error("Failed to create socket");
		}

		sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(server_port);
		if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0)
		{
			throw std::runtime_error("Invalid address");
		}

		if (connect(bot_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		{
			throw std::runtime_error("Failed to connect to server");
		}

		std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;

		std::string pass_msg = "PASS " + password + "\r\n";
		if (send(bot_socket, pass_msg.c_str(), pass_msg.length(), 0) == -1)
		{
			throw std::runtime_error("Failed to send password");
		}

		std::string nick_msg = "NICK asistanbot\r\n"; // cin ile nickname al
		if (send(bot_socket, nick_msg.c_str(), nick_msg.length(), 0) == -1)
		{
			throw std::runtime_error("Failed to send nickname");
		}

		std::string user_msg = "USER asistanbot 0 * :asistanbot\r\n"; // cin ile username al
		if (send(bot_socket, user_msg.c_str(), user_msg.length(), 0) == -1)
		{
			throw std::runtime_error("Failed to send username");
		}
		sleep(1);

		std::cout << "joined to #genel channel" << std::endl;
		std::string join_msg = "JOIN #genel\r\n";
		if (send(bot_socket, join_msg.c_str(), join_msg.length(), 0) == -1)
		{
			throw std::runtime_error("Failed to send join message");
		}

		char buffer[BUFFER_SIZE] = {0};
		std::string incoming_data;

		std::srand(std::time(0));
		std::vector<std::string> quotes = {
			"Her sey dusuncelerinle baslar.",
			"Inanmak, basarmanin yarisi demektir.",
			"Kucuk adimlarla buyuk basarilara ulasabilirsin."
		};

		while (true)
		{
			ssize_t bytes_read = recv(bot_socket, buffer, BUFFER_SIZE - 1, 0);
			if (bytes_read > 0)
			{
				buffer[bytes_read] = '\0';
				incoming_data += buffer;
				size_t pos;
				while ((pos = incoming_data.find("\r\n")) != std::string::npos)
				{
					std::string full_message = incoming_data.substr(0, pos);
					incoming_data.erase(0, pos + 2);

					if (full_message.find("PRIVMSG") != std::string::npos)
					{
						std::stringstream ss(full_message);
						std::string prefix, privmsg_cmd, target, message_content;
						ss >> prefix >> privmsg_cmd >> target;
						ss >> std::ws; // Bosluklari atla
						std::getline(ss, message_content);

						// ':' karakterini temizle
						if (!message_content.empty() && message_content[0] == ':')
						{
							message_content.erase(0, 1);
						}

						if (target == "BotAsistan") { // Botun ozel mesajlari
							std::cout << "Ozel mesaj alindi: " << message_content << std::endl;
						} else if (target == "#genel") { // Kanaldaki mesajlar
							if (message_content.find("!saat") != std::string::npos)
							{
								std::time_t now = std::time(0);
								struct tm *ltm = std::localtime(&now);
								std::stringstream time_ss;
								time_ss << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << " " 
										<< ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year + 1900;
								std::string reply = "PRIVMSG #genel :Su anki saat ve tarih: " + time_ss.str() + "\r\n";
								send(bot_socket, reply.c_str(), reply.length(), 0);
							}
							if (message_content.find("!soz") != std::string::npos)
							{
								int rand_index = std::rand() % quotes.size();
								std::string reply = "PRIVMSG #genel :" + quotes[rand_index] + "\r\n";
								send(bot_socket, reply.c_str(), reply.length(), 0);
							}
						}
					}
				}
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
}
