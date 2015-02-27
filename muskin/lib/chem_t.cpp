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
chem_t::chem_t(double dValue_) : chem_t(dValue_,0,"")
{
}

/*! This constructor sets both the chemical species value and the initial condition. The \c string decribing the
 * name of the chemical species will be set to "".
 */
chem_t::chem_t(double dValue_, double dInitialCondition_) : chem_t(dValue_,dInitialCondition_,"")
{
}

/*! This constructor creates the chem_t object with the complete description of the chemical species.
 */
chem_t::chem_t(double dValue_, double dInitialCondition_, std::string sChemName_)
{
	sChemName = sChemName_;
	dValue = dValue_;
	dInitialCondition = dInitialCondition_;
}
	
/*!
 *  This operator assigns the chemical species value by assignation to a \c double type.
 *  \sa setValue()
 */
chem_t& chem_t::operator=(const double dValue_)
{
	dValue = dValue_;
}

/*! This operator returns the value stored on the chemical species.
 * \sa operator double()
 */
double chem_t::getValue()
{
	return dValue;
}

/*! This method sets the chemical species value.
 * \sa operator=
 */
double chem_t::setValue(const double dValue_)
{
	dValue = dValue_;
}

/*! This operator cast the chemical species value to \c double.
 * This allows to do the assignment 
 * \c double \c = \c chem_t
 * without problems.
 * \sa getValue()
 */
chem_t::operator double()
{
	return dValue;
}
///*!
 //*/
//chem_t::()
//{
//}

