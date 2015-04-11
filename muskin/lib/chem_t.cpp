#include "headers.hpp"
//#include "chem_t.hpp"
/*! The standard constructor sets every property of the chemical species to 0 or "" as needed.
 */
chem_t::chem_t() : chem_t(0,0,"")
{
}

/*! This constructor only sets the value of the chemical species. The remaining values are set to 0
 * and "". This means that the \c string describing the name of the species will be set to "".
 */
chem_t::chem_t(floating_t dValue_) : chem_t(dValue_,0,"")
{
}

/*! This constructor sets both the chemical species value and the initial condition. The \c string decribing the
 * name of the chemical species will be set to "".
 */
chem_t::chem_t(floating_t dValue_, floating_t dInitialCondition_) : chem_t(dValue_,dInitialCondition_,"")
{
}

/*! This constructor creates the chem_t object with the complete description of the chemical species.
 */
chem_t::chem_t(floating_t dValue_, floating_t dInitialCondition_, std::string sChemName_)
{
	sChemName = sChemName_;
	dValue = dValue_;
	dInitialCondition = dInitialCondition_;
}
	
/*!
 *  This operator assigns the chemical species value by assignation to a \c floating_t type.
 *  \sa setValue()
 */
chem_t& chem_t::operator=(const floating_t dValue_)
{
	dValue = dValue_;
}

/*! This operator returns the value stored on the chemical species.
 * \sa operator floating_t()
 */
floating_t chem_t::getValue()
{
	return dValue;
}

/*! This method sets the chemical species value.
 * \sa operator=
 */
floating_t chem_t::setValue(const floating_t dValue_)
{
	dValue = dValue_;
}

/*! This operator cast the chemical species value to \c floating_t.
 * This allows to do the assignment 
 * \c floating_t \c = \c chem_t
 * without problems.
 * \sa getValue()
 */
chem_t::operator floating_t()
{
	return dValue;
}

/*! This type casting allows the use of the libboost methods for ODE systems and chem_t objects.
 *  The vector returned has only the values of the concentration of the chem_t elements.
 */
//point_t toDouble(std::vector <chem_t> vcChems)
point_t toDouble(chem_vector_t  <chem_t> vcChems)
{
	point_t vBuffer;

	for(int i(0); i < vcChems.size();i++)
	{
		vBuffer.push_back(vcChems[i]);
	}

	return vBuffer;

}

/*! This type casting allows the use of the libboost methods for ODE systems and chem_t objects.
 *  The vector returned has the chem_t objects with values of the concentration extracted from the point_t object.
 * */
chem_vector_t toChem_t(point_t ptVector)
{
	std::vector < chem_t > vcBuffer(ptVector.size());

	for(int i(0); i < ptVector.size();i++)
	{
		vcBuffer[i]=ptVector[i];
	}

		return vcBuffer;

}

std::ostream& operator<<(std::ostream& outStream, chem_t& cChem)
{
	outStream << cChem.getValue();
	return outStream;
}
