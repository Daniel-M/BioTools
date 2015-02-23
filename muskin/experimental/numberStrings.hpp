//#include "headers.hpp"

template <typename T>
std::string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T StringToNumber ( const std::string &Text )
{
	std::istringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

