#include "headers.hpp"

/*!
 */
system_t::system_t()
{
}

///*! 
 //*/
//int_t system_t::checkCoherence()
//{
	//for(int i(0);i<vcChems.size();i++)
	//{
		//if(vcChems[i].get != 
	//}
//}

/*! Calls the solver of \c boost::odeint routines. 
 */
void system_t::operator()( const std::vector<chem_t> &y , std::vector<double> &f , const double /* t */ )
{
}


/*!Overwrites the vector of \c chem_t objects of the \c system_t objects.
 * The new set of \c chem_t is passed as the right side operand of =.
 * \sa addchem_t*/
system_t& system_t::operator=(const std::vector<chem_t> vcChems_)
{
}


/*!Overwrites the vector of \c double describing the parameters of the \c system_t object.
 * The new set of parameters is passed as the right side operand of =.
 * \sa setParameters */
system_t& system_t::operator=(const std::vector<double> vdKParameters_)
{
}


/*!Overwrites the vector of \c chem_t objects of the \c system_t objects.
 * The new set of \c chem_t is passed as the right side operand of =.
 * \sa operator= */
void system_t::addchem_t(const std::vector<chem_t> cChem_)
{
}

/*!Overwrites the vector of \c double describing the parameters of the \c system_t object.
 * The new set of parameters is passed as the right side operand of =.
 * \sa operator= */
void system_t::setParameters(const std::vector<double> vdKParameters_)
{
}

