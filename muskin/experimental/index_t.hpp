//#include "headers.hpp"


/**\brief This function overloads the std::vector::operator<< to stream \a std::vectors
 *
 * This function overloads the std::vector:operator<< to provide streaming for \a std::vectors
 *
 * \param[in] outStream stream data type.
 * \tparam[in] index_t A vector of \a floating_t expected (typedef index_t).
 * \return A ostream consisting of the vector size and the vector components separated by commas.
 */

std::ostream& operator<<(std::ostream& outStream, index_t& index)
{
	//outStream << "[" << index.size()  << "](";
	outStream << "(";

	for(int j=0;j!=index.size()-1;j++)
	{
	  outStream << index[j] << ",";
	}
	  
	outStream << index[index.size()-1] << ")";

	return outStream;
}

template <class Tn>
index_t operator*(const Tn tNumber,const index_t inRHIndex)
{
	index_t inIndexBuffer;
	inIndexBuffer.resize(inRHIndex.size());

	for(int j=0;j!=inIndexBuffer.size();j++)
	{
		inIndexBuffer[j] = tNumber*inRHIndex[j];
	}

	return inIndexBuffer;
}

index_t operator+(const index_t inLHIndex,const index_t inRHIndex)
{
	if( inLHIndex.size() == inRHIndex.size())
	{
		index_t inIndexBuffer;
		inIndexBuffer.resize(inLHIndex.size());

		for(int j=0;j!=inIndexBuffer.size();j++)
		{
			inIndexBuffer[j] = inLHIndex[j] + inRHIndex[j];
		}

		return inIndexBuffer;

	}
	else
	{
		std::cout << " [!!] Vector size missmatch for operator+" << std::endl;
		return inLHIndex;
	}
}


/**\brief This function overloads the std::vector::operator- to substract \a std::vectors
 *
 * This function overloads the std::vector:operator- to provide substraction between \a std::vectors
 * The sumation takes place component by component.
 * \f[ \vec{s}=\vec{a}-\vec{b} \Longrightarrow s_{i} = a_{i}-b_{i}\f]
 *
 * \tparam[in] inLHIndex A vector of a template type, \a int,\a float, or\a floating_t expected.
 * \tparam[in] inRHIndex The other vector of a template type, \a int,\a float, or\a floating_t expected.
 * \return A vector whose components are the inLHIndex and inRHIndex components substracted
 * \note The vectors size are compared in order to guarantee size matching. Else returns inLHIndex and an error message to \a std::cout
 * \note This function uses the overloaded operator*, it sums \f$ \vec{s}=\vec{a} + \left(-1*\vec{b}\right)\f$
 */
template <class T>
index_t operator-(const index_t inLHIndex,const index_t inRHIndex)
{
	if( inLHIndex.size() == inRHIndex.size())
	{
		index_t inIndexBuffer;
		inIndexBuffer.resize(inLHIndex.size());

		inIndexBuffer = inLHIndex + (-1*inRHIndex);

		return inIndexBuffer;

	}
	else
	{
		std::cout << " [!!] Vector size missmatch for operator-" << std::endl;
		return inLHIndex;
	}
}

//bool operator<(const index_t& index) const
bool operator<(const index_t& index1, const index_t& index2)
{
	if(index1.size() != index2.size())
	{
		std::cout << "Vector size missmatch" << std::endl;
		return false;
	}
	else
	{
		floating_t dNorm1(0),dNorm2(0);

		for(int i(0);i < index1.size();i++)
		{
			dNorm1+=index1.at(i)*index1.at(i);
		}
		for(int i(0);i < index2.size();i++)
		{
			dNorm2+=index2.at(i)*index2.at(i);
		}

		return dNorm1<dNorm2;
	}
	

}

//bool operator<(const index_t& index) const
bool operator>(const index_t& index1, const index_t& index2)
{
	if(index1.size() != index2.size())
	{
		std::cout << "Vector size missmatch" << std::endl;
		return false;
	}
	else
	{
		floating_t dNorm1(0),dNorm2(0);

		for(int i(0);i < index1.size();i++)
		{
			dNorm1+=index1.at(i)*index1.at(i);
		}
		for(int i(0);i < index2.size();i++)
		{
			dNorm2+=index2.at(i)*index2.at(i);
		}

		return dNorm1>dNorm2;
	}
	

}
