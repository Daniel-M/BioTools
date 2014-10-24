#include "incluidos.hpp"

/**\brief This function overloads the std::vector::operator* to multiply numbers (\a int,\a float, \a double) and \a std::vectors
 *
 * This function overloads the std::vector:operator* to provide mutiplication between numbers (\a int,\a float, \a double) and \a std::vectors
 * each component of the vector is multiplied by the template number.
 *
 * \tparam[in] tNumber Number of a template type. \a int,\a float, or\a double expected.
 * \tparam[in] vtRHSVector \a std::vector to multiply to.
 * \return the vtRHSVector with each component multiplied by tNumber.
 */
template <class Tn,class Tv>
std::vector<Tv> operator*(const Tn tNumber,const std::vector<Tv> vtRHSVector)
{
	std::vector<Tv> vtVectorBuffer;
	vtVectorBuffer.resize(vtRHSVector.size());

	for(int j=0;j!=vtVectorBuffer.size();j++)
	{
		vtVectorBuffer[j] = tNumber*vtRHSVector[j];
	}

	return vtVectorBuffer;
}


/**\brief This function overloads the std::vector::operator+ to sum \a std::vectors
 *
 * This function overloads the std::vector:operator+ to provide sumation between \a std::vectors
 * The sumation takes place component by component.
 * \f[ \vec{s}=\vec{a}+\vec{b} \Longrightarrow s_{i} = a_{i}+b_{i}\f]
 *
 * \tparam[in] vtLHSVector A vector of a template type, \a int,\a float, or\a double expected.
 * \tparam[in] vtRHSVector The other vector of a template type, \a int,\a float, or\a double expected.
 * \return A vector whose components are the vtLHSVector and vtRHSVector components sumated
 * \note The vectors size are compared in order to guarantee size matching. Else returns vtLHSVector and an error message to \a std::cout
 */
template <class T>
std::vector<T> operator+(const std::vector<T> vtLHSVector,const std::vector<T> vtRHSVector)
{
	if( vtLHSVector.size() == vtRHSVector.size())
	{
		std::vector<T> vtVectorBuffer;
		vtVectorBuffer.resize(vtLHSVector.size());

		for(int j=0;j!=vtVectorBuffer.size();j++)
		{
			vtVectorBuffer[j] = vtLHSVector[j] + vtRHSVector[j];
		}

		return vtVectorBuffer;

	}
	else
	{
		std::cout << " [!!] Vector size missmatch for operator+" << std::endl;
		return vtLHSVector;
	}
}


/**\brief This function overloads the std::vector::operator- to substract \a std::vectors
 *
 * This function overloads the std::vector:operator- to provide substraction between \a std::vectors
 * The sumation takes place component by component.
 * \f[ \vec{s}=\vec{a}-\vec{b} \Longrightarrow s_{i} = a_{i}-b_{i}\f]
 *
 * \tparam[in] vtLHSVector A vector of a template type, \a int,\a float, or\a double expected.
 * \tparam[in] vtRHSVector The other vector of a template type, \a int,\a float, or\a double expected.
 * \return A vector whose components are the vtLHSVector and vtRHSVector components substracted
 * \note The vectors size are compared in order to guarantee size matching. Else returns vtLHSVector and an error message to \a std::cout
 * \note This function uses the overloaded operator*, it sums \f$ \vec{s}=\vec{a} + \left(-1*\vec{b}\right)\f$
 */
template <class T>
std::vector<T> operator-(const std::vector<T> vtLHSVector,const std::vector<T> vtRHSVector)
{
	if( vtLHSVector.size() == vtRHSVector.size())
	{
		std::vector<T> vtVectorBuffer;
		vtVectorBuffer.resize(vtLHSVector.size());

		vtVectorBuffer = vtLHSVector + (-1*vtRHSVector);

		return vtVectorBuffer;

	}
	else
	{
		std::cout << " [!!] Vector size missmatch for operator-" << std::endl;
		return vtLHSVector;
	}
}

/**\brief This function overloads the std::vector::operator<< to stream \a std::vectors
 *
 * This function overloads the std::vector:operator<< to provide streaming for \a std::vectors
 *
 * \param[in] outStream stream data type.
 * \tparam[in] vtVector A vector of a template type, \a int,\a float, \a double or \a std::string expected.
 * \return A ostream consisting of the vector size and the vector components separated by commas.
 */
template <class T>
std::ostream& operator<<(std::ostream& outStream, std::vector<T>& vtVector)
{
	outStream << "[" << vtVector.size() << "](";

	for(int j=0;j!=vtVector.size()-1;j++)
	{
		outStream << vtVector[j] << ",";
	}
		
	outStream << vtVector[vtVector.size()-1] << ")";

	return outStream;
}
