#include "headers.hpp"

/*!
 * This constructor sets all the properties to 0.
 */
voxel::voxel()
{
	itVoxelNumber=0;


}

/*! This constructor assigns the set of indexes and the system_t of the voxel.
 * The remaining properties are set to 0.
 */
voxel::voxel(std::set<index_t> useIndexes_, system_t stSystem_)
{
	itVoxelNumber=0;
	stSystem = stSystem_;
	useIndexes = useIndexes_;
}

/*! This constructor assigns all the properties of the voxel.
 */
voxel::voxel(int_t itVoxelNumber, std::set<index_t> useIndexes_, system_t stSystem_)
{
	itVoxelNumber=0;
	stSystem = stSystem_;
	useIndexes = useIndexes_;
}

/*! This method returns the system_t object assigned to the voxel. The index is searched in the voxel.
 * If the index belongs to the voxel, the system_t of the voxel is returned. If not an error message is casted.
 */
system_t voxel::operator[](index_t inIndex_)
{
	if(useIndexes.count(inIndex_) > 0)
	{
		return stSystem; 
	}
	else
	{
		std::cout << "System not contained on voxel" << std::endl;
	}
}

/*! This method sets or overwrites the voxel assigned system_t object. 
 * \sa setSystem()*/
voxel& voxel::operator=(const system_t stSystem_)
{
	stSystem = stSystem_;
}

/*! This method overwrites the stored indexes on the voxel.
 * The voxel will only contain the index inIndex.
 * \sa operator+= */
voxel& voxel::operator=(const index_t inIndex_)
{
	useIndexes.clear();
	useIndexes.insert(inIndex_);
}

/*! This method overwrites the indexes stored on the voxel with the ones provided on the set. */
voxel& voxel::operator=(const std::set<index_t> useIndexes_)
{
	useIndexes.clear();
	useIndexes=useIndexes_;
}

/*! This method adds the index to the voxel. The set of indexes is increased by one, nothing is erased or cleared.
 * If the index already belongs to the voxel the method does not modify the voxel.
 * \sa insert()*/
voxel& voxel::operator+=(const index_t inIndex_)
{
	useIndexes.insert(inIndex_);
}

/*! This method inserts an index to the voxel if the index is not member of the voxel yet.
 * If the index already belongs to the voxel the method does not modify the voxel.
 * \sa operator+=*/
void voxel::insert(index_t inIndex_)
{
	useIndexes.insert(inIndex_);
}


/*! This method assigns or overloads the system_t of the voxel.
 * \sa operator=
 */
void voxel::setSystem(system_t stSystem_)
{
}

/*! This method gets the number assigned to the voxel.
 */
int_t voxel::getVoxelNumber()
{
	return itVoxelNumber;
}

/*! This method determines if the index is a member of the voxel or not.
 * Returning a value of 0 means that the index is not a member of the voxel.
 * A returning value of 1 means that the voxel contains the index.
 */
int_t voxel::count(index_t inIndex_)
{
}

/*! This method returns the system_t assigned to the voxel.
 */
system_t voxel::getSystem()
{
}

///*!
 //*/
//voxel::()
//{
//}
