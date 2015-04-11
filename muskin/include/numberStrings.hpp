//#include "headers.hpp"

/*! \brief Type casting from number to strings. 
 * \tparam[in] Number stream data type.
 * \return A representation of Number as a string.
 * */
template <typename T>
std::string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

/*! \brief Type casting from strings to numbers.
 * \param[in] Text string representing a number.
 * \return A template type of the number.
 * */template <typename T>
T StringToNumber ( const std::string &Text )
{
	std::istringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

