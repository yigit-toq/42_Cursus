#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "Logger.hpp"

#include <algorithm>

#include <vector>

class Message
{
	private:
		std::string					_prefix;
		std::string					_command;
		std::vector<std::string>	_parameters;

	private:
		Message												(const Message& other);
		Message& operator=									(const Message& other);

	public:
		 Message											();
		~Message											();

		const std::string&					GetPrefix		() const;
		const std::string&					GetCommand		() const;
		const std::vector<std::string>&		GetParameters	() const;

		void								Print			() const;

		bool								Parse			(const std::string& raw_message);

};

#endif
