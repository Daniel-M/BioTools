//#include "headers.hpp"


/**\brief This function overloads the std::vector::operator<< to stream \a std::vectors
 *
 * This function overloads the std::vector:operator<< to provide streaming for \a std::vectors
 *
 * \param[in] outStream stream data type.
 * \tparam[in] point_t A vector of \a floating_t expected (typedef point_t).
 * \return A ostream consisting of the vector size and the vector components separated by commas.
 */

std::ostream& operator<<(std::ostream& outStream, point_t& point)
{
	//outStream << "[" << point.size()  << "](";
	outStream << "(";

	for(int j=0;j!=point.size()-1;j++)
	{
	  outStream << point[j] << ",";
	}
	  
	outStream << point[point.size()-1] << ")";

	return outStream;
}

/*!\brief This function overloads the std::vector::operator* to multiply \c point_t by scalars.
 *
 * \tparam[in] tNumber a template type representing a number.
 * \param[in] vtRHSVector Right hand vector to be multiplied.
 * \return A vector whose components are vtRHSVector components multiplied by Number.
 */
template <class Tn>
point_t operator*(const Tn tNumber,const point_t vtRHSVector)
{
	point_t vtVectorBuffer;
	vtVectorBuffer.resize(vtRHSVector.size());

	for(int j=0;j!=vtVectorBuffer.size();j++)
	{
		vtVectorBuffer[j] = tNumber*vtRHSVector[j];
	}

	return vtVectorBuffer;
}

/*!\brief This function overloads the std::vector::operator+ to summate \c point_t objects.
 *
 * This function overloads the std::vector:operator+ to provide substraction between \a point_t 
 * The sumation takes place component by component.
 * \f[ \vec{s}=\vec{a}+\vec{b} \Longrightarrow s_{i} = a_{i}+b_{i}\f]
 *
 * \param[in] vtLHSVector Left hand vector.
 * \param[in] vtRHSVector Right hand vector.
 * \return A vector whose components are the vtLHSVector and vtRHSVector components summated.
 * \note The vectors size are compared in order to guarantee size matching. Else returns vtLHSVector and an error message to \a std::cout
 */
point_t operator+(const point_t vtLHSVector,const point_t vtRHSVector)
{
	if( vtLHSVector.size() == vtRHSVector.size())
	{
		point_t vtVectorBuffer;
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


/*!\brief This function overloads the std::vector::operator- to substract \a std::vectors
 *
 * This function overloads the std::vector:operator- to provide substraction between \a std::vectors
 * The sumation takes place component by component.
 * \f[ \vec{s}=\vec{a}-\vec{b} \Longrightarrow s_{i} = a_{i}-b_{i}\f]
 *
 * \tparam[in] vtLHSVector A vector of a template type, \a int,\a float, or\a floating_t expected.
 * \tparam[in] vtRHSVector The other vector of a template type, \a int,\a float, or\a floating_t expected.
 * \return A vector whose components are the vtLHSVector and vtRHSVector components substracted
 * \note The vectors size are compared in order to guarantee size matching. Else returns vtLHSVector and an error message to \a std::cout
 * \note This function uses the overloaded operator*, it sums \f$ \vec{s}=\vec{a} + \left(-1*\vec{b}\right)\f$
 */
template <class T>
point_t operator-(const point_t vtLHSVector,const point_t vtRHSVector)
{
	if( vtLHSVector.size() == vtRHSVector.size())
	{
		point_t vtVectorBuffer;
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

/*
std::ostream& operator<<(std::ostream& outStream, index_t& index)
{
	//outStream << "[" << index.size() << "][";
	outStream << "[";

	for(int j=0;j<index.size()-1;j++)
	{
	  outStream << index[j] << ",";
	}
	  
	outStream << index[index.size()-1] << "]";

	return outStream;
}*/
