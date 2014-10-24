#include "incluidos.hpp"

/**\brief This function converts a number data type like \a int, \a float, or\a double to \a std::string.
 *        The result it's used on symbolic multiplications of boost::numeric::ublas::matrix.
 *
 * This function converts a number data type to a \a std::string, so the result it's used on symbolic
 * multiplications of boost::numeric::ublas::matrix. When the number is +1 it just returns "", when
 * the number is -1, the function returns "-".
 *
 * \tparam[in] number Number data type to be converted to \a std::string.
 * \return \a std::string of the number given. If the number
 */
template <typename T>
std::string numberToString (const T& number)
{
    std::ostringstream ss;
    ss << number;
	if (ss.str() == "1")
	{
		return "";
	}
	else if (ss.str() == "-1")
	{
		return "-";
	}
	else
	{
	    return ss.str() + "*";
	}
}

template <typename T>
std::string numberToString (const T& number,bool bVar)
{
    std::ostringstream ss;
    
	ss << number;
	
	return ss.str();
}
