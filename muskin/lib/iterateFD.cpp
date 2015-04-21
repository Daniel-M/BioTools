#include "headers.hpp"

/*! \brief Increments or decrements indices.
 *
 * This method can take an index like {i,j,k,...}.
 *
 * take for example the index {i,j,k}
 *
 * passing DeltaIdx({i,j,k},2,1)
 * would return the index {i,j+1,k}
 *
 * passing DeltaIdx({i,j,k},3,-2)
 * would return the index {i,j,k-2}
 *
 *
 * \param[out] index index_t object that represents the set of indices associated.
 * \param[in] pos The position of the index to be modified.
 * \param[in] value The value to be added (or substracted) to the index at pos.*/
//void DeltaIdx(index_t& index,int_t pos,int_t value)
//{
	//if( index.size() > pos )
	//{
		//index[pos] += value;
	//}
	//else
	//{
		//std::cout << "[EE] IterateFD DeltaIdx outbounds" << std::endl;
	//}
	////return ;
//}

index_t DeltaIdx(index_t& index,int_t pos,int_t value)
{
	index_t bIndex(index);

	if( bIndex.size() > pos )
	{
		bIndex[pos] += value;
	}
	else
	{
		std::cout << "[EE] IterateFD DeltaIdx outbounds" << std::endl;
	}
		
	return bIndex;
	
}

mesh_t IterateFDCartesian(mesh_t& mMesh,floating_t dDeltaT)
{
	mesh_t mBufferMesh(mMesh);
	
	std::map<index_t,node_t> mBufferBoundary(mMesh.getBoundaryMesh());
	std::map<index_t,node_t> mBufferInner(mMesh.getInnerMesh());
	std::map<index_t,node_t>::iterator mIterator;

	std::cout << "Size of boundary " << mBufferBoundary.size() << std::endl;
	std::cout << "Size of Inner " <<mBufferInner.size() << std::endl;
; 	

	double coeff1(1.0/pow(mMesh.getDeltaOnDim(0),2)), coeff2(1.0/pow(mMesh.getDeltaOnDim(1),2));
	//int_t indexX1, indexX2; /*!< Buffer for the indexes */

	index_t idxIJ, idxIJI, idxIJJ, idxIIJ, idxJIJ; /*!< idxIJ = i,j idxIJI = i+1,j idxIJJ = i,j+1 idxIIJ = i-1,j idxJIJ = i,j-1*/
	
	node_t fdOnX, fdOnY; /*!< Transitional nodes to store iterations on each dimension */
	node_t nnBuffer; /*!< Buffer node to store the result of the iteration */

	idxIJ = {1,1}; /*!< Initial node.*/

    idxIJI = DeltaIdx(idxIJ,0,1);  /*!< i+1,j   */ 
    idxIIJ = DeltaIdx(idxIJ,0,-1); /*!< i-1,j   */ 
    idxIJJ = DeltaIdx(idxIJ,1,1);  /*!< i  ,j+1 */
    idxJIJ = DeltaIdx(idxIJ,1,-1); /*!< i  ,j-1 */
			
	std::cout << idxIJ << "\t" <<  idxIJI << "\t" <<  idxIIJ << "\t" <<   idxIJJ << "\t" <<   idxJIJ << std::endl; 
	
	//mBufferMesh.coutMesh();

	std::cout << "Iteration Process started..." << std::endl;


	for(int i(1); i < mMesh.getNodesOnDim(0)-1; i++)
	{
		for(int j(1); j < mMesh.getNodesOnDim(1)-1; j++)
		{

			idxIJ = {i,j};

			idxIJI = DeltaIdx(idxIJ,0,1);  /*!< i+1,j   */ 
			idxIIJ = DeltaIdx(idxIJ,0,-1); /*!< i-1,j   */ 
			idxIJJ = DeltaIdx(idxIJ,1,1);  /*!< i  ,j+1 */
			idxJIJ = DeltaIdx(idxIJ,1,-1); /*!< i  ,j-1 */
			
			fdOnX = coeff1*(mMesh[idxIJI] - 2*mMesh[idxIJ] + mMesh[idxIIJ]);
			fdOnY = coeff2*(mMesh[idxIJJ] - 2*mMesh[idxIJ] + mMesh[idxJIJ]);
		
			mBufferMesh[idxIJ] = mMesh[idxIJ] + dDeltaT*( fdOnX + fdOnY);
			
			std::cout << idxIJ << "\t" <<  idxIJI << "\t" <<  idxIIJ << "\t" <<   idxIJJ << "\t" <<   idxJIJ << std::endl; 
			std::cout << "values mMesh[ij] " << mMesh[idxIJ].getValue() << std::endl;
			std::cout << "values mMesh[i+1 j] " << mMesh[idxIJI].getValue() << std::endl;
			std::cout << "values mMesh[i-1 j] " << mMesh[idxIIJ].getValue() << std::endl;
			std::cout << "values mMesh[i j+1] " << mMesh[idxIJJ].getValue() << std::endl;
			std::cout << "values mMesh[i j-1] " << mMesh[idxJIJ].getValue() << std::endl;
			std::cout << "\n value dDeltaT " <<  dDeltaT << std::endl;
			std::cout << "\n value " <<  coeff1 << std::endl;
			std::cout << "\n value " <<  coeff2 << std::endl;

			std::cout << "value fdOnX " <<  fdOnX.getValue() << std::endl;
			std::cout << "value fdOnY " <<  fdOnY.getValue() << std::endl;
			//std::cout << "values dDeltaT " <<  dDeltaT << std::endl;
			//std::cout << "values mMesh[idx] " << mMesh[idxIJ] << std::endl;
			std::cout << "Result " << mBufferMesh[idxIJ] << std::endl;


			//std::cout << idxIJ << "\t" <<  idxIJI << "\t" <<  idxIIJ << "\t" <<   idxIJJ << "\t" <<   idxJIJ << std::endl; 
		}
	}



	//int i(1),j(1);
	////for(mIterator = mBufferBoundary.begin(); mIterator != mBufferBoundary.end(); ++mIterator)
	////for(mIterator =  mMesh.getBoundaryMesh().begin(); mIterator !=  mMesh.getBoundaryMesh().end(); ++mIterator)
	//for(mIterator = mBufferBoundary.begin(); mIterator != mBufferBoundary.end(); ++mIterator)
	//{
		//std::cout << mIterator->second << std::endl;

		//fdOnX = coeff1*(mMesh[idxIJI] - 2*mMesh[idxIJ] + mMesh[idxIIJ]);
		//fdOnY = coeff2*(mMesh[idxIJJ] - 2*mMesh[idxIJ] + mMesh[idxJIJ]);
		
		//mBufferMesh[idxIJ] = mMesh[idxIJ] + dDeltaT*( fdOnX + fdOnY);

		//std::cout << "values " << mBufferMesh[idxIJ] << std::endl;

		//i++;
		//j++;

		//idxIJ = {i,j}; /*!< Initial node.*/

		//idxIJI = DeltaIdx(idxIJ,0,1);  /*!< i+1,j   */ 
		//idxIIJ = DeltaIdx(idxIJ,0,-1); /*!< i-1,j   */ 
		//idxIJJ = DeltaIdx(idxIJ,1,1);  /*!< i  ,j+1 */
		//idxJIJ = DeltaIdx(idxIJ,1,-1); /*!< i  ,j-1 */
	//}	 

	//idxIJ = {1,1};

	//for(int i;i<mMesh.getNodesOnDim(0)-1;i++)
	//{
		//std::cout << idxIJ << "\t";
		//std::cout << mBufferMesh[idxIJ] << std::endl;
		
		//DeltaIdx(idxIJ,0,1);
	//}

	/*!< Boundary region of the mesh */

	/*!< Inner region of the mesh */

	return mBufferMesh;
}
