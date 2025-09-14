#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>

#include <vector>

#include <string>

class Utils
{
	private:
		Utils																(const Utils& other);
		Utils& operator=													(const Utils& other);

	public:
		 Utils ();
		~Utils ();

		static	std::string							trim					(const std::string& str);

		static	std::vector<std::string>			split					(const std::string& str, char delimiter);

		static	std::vector<std::pair<char, char> >	ParseModeString			(const std::string& mode_string);

		static	bool								IsModeWithParameter		(char mode);

		template <typename T>
		static	std::string							ft_to_string			(T value);
};

template <typename T>
std::string ft_to_string(T value)
{
	std::stringstream	ss;

	ss << value;

	return ss.str();
}

#endif
