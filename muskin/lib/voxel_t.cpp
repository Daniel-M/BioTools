#include "headers.hpp"
//#include "voxel.hpp"
/*!
 * This constructor sets all the properties to 0.
 */
voxel_t::voxel_t()
{
	itVoxelNumber=0;
	ptrSystem = NULL;
}
/*!\brief Overloaded constructor of voxel_t that initializes by the system_t of the voxel_t*/
voxel_t::voxel_t(system_t ptrSys)
{
	itVoxelNumber=0;
	ptrSystem = ptrSys;
}

/*! This constructor assigns the set of indexes and the system_t of the voxel_t.
 * The remaining properties are set to 0.
 */
voxel_t::voxel_t(std::set<index_t> useIndexes_, system_t ptrSys)
{
	itVoxelNumber=0;
	ptrSystem = ptrSys;
	useIndexes = useIndexes_;
}

/*! This constructor assigns all the properties of the voxel_t.
 */
voxel_t::voxel_t(int_t itVoxelNumber, std::set<index_t> useIndexes_, system_t ptrSys)
{
	itVoxelNumber=itVoxelNumber;
	useIndexes = useIndexes_;
	ptrSystem = ptrSys;
}

/*! This method returns the system_t object assigned to the voxel_t. The index is searched in the voxel_t.
 * If the index belongs to the voxel_t, the system_t of the voxel_t is returned. If not an error message is casted.
 */
system_t voxel_t::operator[](index_t inIndex_)
{
	if(useIndexes.count(inIndex_) > 0)
	{
		return ptrSystem; 
	}
	else
	{
		std::cout << "System not contained on voxel_t" << std::endl;
	}
}

/*! This method sets or overwrites the voxel_t assigned system_t object. 
 * \sa setSystem()*/
voxel_t& voxel_t::operator=(const system_t ptrSys)
{
	ptrSystem = ptrSys;
}

/*! This method overwrites the stored indexes on the voxel_t.
 * The voxel_t will only contain the index inIndex.
 * \sa operator+= */
voxel_t& voxel_t::operator=(const index_t inIndex_)
{
	useIndexes.clear();
	useIndexes.insert(inIndex_);
}

/*! This method overwrites the indexes stored on the voxel_t with the ones provided on the set. */
voxel_t& voxel_t::operator=(const std::set<index_t> useIndexes_)
{
	useIndexes.clear();
	useIndexes=useIndexes_;
}

/*! This method adds the index to the voxel_t. The set of indexes is increased by one, nothing is erased or cleared.
 * If the index already belongs to the voxel_t the method does not modify the voxel_t.
 * \sa insert()*/
voxel_t& voxel_t::operator+=(const index_t inIndex_)
{
	useIndexes.insert(inIndex_);
}

/*! This method inserts an index to the voxel_t if the index is not member of the voxel_t yet.
 * If the index already belongs to the voxel_t the method does not modify the voxel_t.
 * \sa operator+=*/
void voxel_t::insert(index_t inIndex_)
{
	useIndexes.insert(inIndex_);
}


/*!
 * The system to be assigned to the voxel_t_t is passed as a pointer to a function of the form (x,dx,t) as \c libboost::odeint requires.
 * the \c libboost::odeint systems are functions defined as \c f(x,dxdt,t) where \c x and \c dxdt are std containers as \c std::vectors.
 * In this case the type used is \c point_t which is a \c typedef of \c std::vector<floating_t>.
 * \sa operator=
 */
void voxel_t::setSystem(system_t ptrSys)
{

	if (ptrSystem)
	{
		//delete ptrSystem;
		ptrSystem = NULL;
		ptrSystem = ptrSys;
	}
	else
	{
		ptrSystem = ptrSys;
	}
}

/*!
 *	This method integrates one time step of the system assigned by \c setSystem. The system must be assigned before any attempt to solve the system or
 *	the binary will trow an error. This method is highly experimental so the behaviour is to certain extent unknown if the system is not previously defined.
 *	\sa set system
 * */
void voxel_t::evalSystem(point_t& x, floating_t t, floating_t dt)
{
	//std::cout << "Lvl 2.1" << std::endl;
	boost::numeric::odeint::runge_kutta4< point_t > rk; /*!< Calls the \c libboost solver to implement steps */
	//std::cout << "Lvl 2.2" << std::endl;
	rk.do_step( ptrSystem , x , t , dt ); 
	//std::cout << "Lvl 2.3" << std::endl;
}

void voxel_t::evalSystem(std::vector<chem_t>& x, floating_t t, floating_t dt)
{
	//std::cout << "Lvl 3.1" << std::endl;
	point_t ptBuffer = toDouble(x);
	//std::cout << "Lvl 3.2" << std::endl;
	evalSystem(ptBuffer,t,dt);
	//std::cout << "Lvl 3.3" << std::endl;
	x = toChem_t(ptBuffer);
}

/*! This method gets the number assigned to the voxel_t.
 */
int_t voxel_t::getVoxelNumber()
{
	return itVoxelNumber;
}

/*! This method determines if the index is a member of the voxel_t or not.
 * Returning a value of 0 means that the index is not a member of the voxel_t.
 * A returning value of 1 means that the voxel_t contains the index.
 */
int_t voxel_t::count(index_t inIndex_)
{
}

/*! This method returns the system_t assigned to the voxel_t.
 */
system_t voxel_t::getSystem()
{
	return *ptrSystem;
}

///*!
 //*/
//voxel_t::()
//{
//}
