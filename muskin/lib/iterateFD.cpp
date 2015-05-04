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

namespace Cartesian_Coordinates
{
	node_t FDFirstOrderForward(index_t idxIJ, mesh_t& mMesh,int_t IdXPos) 
	{
		index_t idxIJI; /*!< idxIJ = i,j idxIJI = i+1,j idxIIJ = i-1,j idxIJJ = i,j+1  idxJIJ = i,j-1*/
		
		idxIJI = DeltaIdx(idxIJ,IdXPos,1);  /*!< i+1,j This uses IdXPos to determine wich index to iterate.*/ 

			
		if( (idxIJ[IdXPos] >= 0 ) || (idxIJ[IdXPos] <= mMesh.getNodesOnDim(IdXPos)-2))
		{
			double r = (1/mMesh.getDeltaOnDim(IdXPos));

			return r*(mMesh[idxIJI] - mMesh[idxIJ]);
		}
		else
		{
			std::cout << "[EE] FDFirstOrderForward DeltaIdx outbounds" << std::endl;
			return mMesh[idxIJ];
		}
	}


	node_t FDFirstOrderBackward(index_t idxIJ, mesh_t& mMesh,int_t IdXPos) 
	{	
		index_t idxIIJ; /*!< idxIJ = i,j idxIJI = i+1,j idxIIJ = i-1,j idxIJJ = i,j+1  idxJIJ = i,j-1*/
		
		idxIIJ = DeltaIdx(idxIJ,IdXPos,-1);  /*!< i-1,j This uses IdXPos to determine wich index to iterate.*/ 
			
		
		if( (idxIJ[IdXPos] >= 1 ) || (idxIJ[IdXPos] <= mMesh.getNodesOnDim(IdXPos)-1))
		{
			double r = (1/mMesh.getDeltaOnDim(IdXPos));

			return r*(mMesh[idxIJ] - mMesh[idxIIJ]);
		}
		else
		{
			std::cout << "[EE] FDFirstOrderBackward DeltaIdx outbounds" << std::endl;
			return mMesh[idxIJ];
		}
		
	}

	node_t FDFirstOrderCentered(index_t idxIJ, mesh_t& mMesh,int_t IdXPos) 
	{	
		index_t idxIJI,idxIIJ; /*!< idxIJ = i,j idxIJI = i+1,j idxIIJ = i-1,j idxIJJ = i,j+1  idxJIJ = i,j-1*/

		idxIJI = DeltaIdx(idxIJ,IdXPos,1);  /*!< i+1,j This uses IdXPos to determine wich index to iterate.*/ 
		idxIIJ = DeltaIdx(idxIJ,IdXPos,-1);  /*!< i-1,j This uses IdXPos to determine wich index to iterate.*/ 

		if( (idxIIJ[IdXPos] >= 0 ) || (idxIJI[IdXPos] < mMesh.getNodesOnDim(IdXPos)) )
		{

			double r = 0.5*(1/mMesh.getDeltaOnDim(IdXPos));

			return r*(mMesh[idxIJI] - mMesh[idxIIJ]);
		}
		else
		{
			std::cout << "[EE] FDFirstOrderCentered DeltaIdx outbounds" << std::endl;
			return mMesh[idxIJ];
		}
	}


	node_t FDSecondOrder(index_t idxIJ, mesh_t& mMesh,int_t IdXPos) 
	{	

		if( idxIJ[IdXPos] == 0 )
		{
			double r = (2/pow(mMesh.getDeltaOnDim(IdXPos),2));

			/*!< Using Homogeneous Neuman Condition */
		
			return r*(mMesh[ DeltaIdx(idxIJ,IdXPos,1) ] - mMesh[idxIJ]);
		}
		else if( idxIJ[IdXPos] == mMesh.getNodesOnDim(IdXPos)-1 )
		{
			
			double r = (2/pow(mMesh.getDeltaOnDim(IdXPos),2));

			/*!< Using Homogeneous Neuman Condition */
			
			return r*(mMesh[ DeltaIdx(idxIJ,IdXPos,-1) ] - mMesh[idxIJ]);
	
		}
		else if( (idxIJ[IdXPos] > 0 ) && (idxIJ[IdXPos] < mMesh.getNodesOnDim(IdXPos)-1))
		{
			double r = (1/pow(mMesh.getDeltaOnDim(IdXPos),2));
			
			return r*(mMesh[DeltaIdx(idxIJ,IdXPos,1)] - 2*mMesh[idxIJ] + mMesh[DeltaIdx(idxIJ,IdXPos,-1)]);
		}
		else
		{
			std::cout << "[EE] FDSecondOrder DeltaIdx outbounds" << std::endl;
			return mMesh[idxIJ];
		}

	}

	mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT)
	{
		mesh_t mBufferMesh(mMesh);

		double coeff1(1.0), coeff2(1.0);
		//double coeff1(1.0/pow(mMesh.getDeltaOnDim(0),2)), coeff2(1.0/pow(mMesh.getDeltaOnDim(1),2));

		index_t idxIJ, idxIJI, idxIJJ, idxIIJ, idxJIJ; /*!< idxIJ = i,j idxIJI = i+1,j idxIIJ = i-1,j idxIJJ = i,j+1  idxJIJ = i,j-1*/
		
		node_t fdOnX, fdOnY; /*!< Transitional nodes to store iterations on each dimension */


		for(int i(0); i < mMesh.getNodesOnDim(0); i++)
		{
			for(int j(0); j < mMesh.getNodesOnDim(1); j++)
			{

				idxIJ = {i,j};

				fdOnX = coeff1*Cartesian_Coordinates::FDSecondOrder(idxIJ,mMesh,0);
				fdOnY = coeff2*Cartesian_Coordinates::FDSecondOrder(idxIJ,mMesh,1);

				mBufferMesh[idxIJ] = mMesh[idxIJ] + dDeltaT*( fdOnX + fdOnY);
				
				//std::cout << idxIJ << std::endl; 
				//std::cout << "values mMesh[ij] " << mMesh[idxIJ].getValue() << std::endl;
				//std::cout << "values mMesh[i] " << fdOnX.getValue() << std::endl;
				//std::cout << "values mMesh[j] " << fdOnY.getValue() << std::endl;
				//std::cout << "\n value dDeltaT " <<  dDeltaT << std::endl;
				//std::cout << "\n coeff1 " <<  coeff1 << std::endl;
				//std::cout << "\n coeff2 " <<  coeff2 << std::endl;

				//std::cout << "value fdOnX " <<  fdOnX.getValue() << std::endl;
				//std::cout << "value fdOnY " <<  fdOnY.getValue() << std::endl;
				//std::cout << "values mMesh[idx] " << mMesh[idxIJ] << std::endl;
				//std::cout << "Result " << mBufferMesh[idxIJ] << std::endl;


			}
		}


		return mBufferMesh;
	}
}

namespace Cylindrical_Coordinates
{

	node_t FDSecondOrder(index_t idxIJ, mesh_t& mMesh,int_t IdXPos) 
	{	

		if( idxIJ[IdXPos] == 0 )
		{
			double r = (4/pow(mMesh.getDeltaOnDim(IdXPos),2));

			/*!< Using predefined equation
			 *   Remember that DeltaIdx(idxIJ,0,1) means {i,j,k} --> {i+1,j,k}
			 * */
		
			return r*(mMesh[ DeltaIdx(idxIJ,IdXPos,1) ] - mMesh[idxIJ]);
		}
		else if( idxIJ[IdXPos] == mMesh.getNodesOnDim(IdXPos)-1 )
		{
			
			double alpha = mMesh.getNodesOnDim(IdXPos)-1;
			double r = (2/(pow(mMesh.getDeltaOnDim(IdXPos),2)*alpha));

			/*!< Using Homogeneous Neuman Condition */
			
			return r*(alpha*mMesh[ DeltaIdx(idxIJ,0,-1) ]-mMesh[idxIJ]);
	
		}
		else if( ( 0 < idxIJ[IdXPos] ) && (idxIJ[IdXPos] < mMesh.getNodesOnDim(IdXPos)-1))
		{
			double alpha = 2*idxIJ[IdXPos];
			double beta = alpha+1;
			double gamma = alpha-1;
			double r = (1/(alpha*pow(mMesh.getDeltaOnDim(IdXPos),2)));
			
			return r*(beta*mMesh[DeltaIdx(idxIJ,IdXPos,1)] - 2*alpha*mMesh[idxIJ] + gamma*mMesh[DeltaIdx(idxIJ,IdXPos,-1)]);
		}
		else
		{
			std::cout << "[EE] FDSecondOrder DeltaIdx outbounds" << std::endl;
			return mMesh[idxIJ];
		}

	}
	
	
	mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT)
	{
		mesh_t mBufferMesh(mMesh);

		double coeff1(1.0), coeff2(1.0);
		//double coeff1(1.0/pow(mMesh.getDeltaOnDim(0),2)), coeff2(1.0/pow(mMesh.getDeltaOnDim(1),2));

		index_t idxIJ, idxIJI, idxIJJ, idxIIJ, idxJIJ; /*!< idxIJ = i,j idxIJI = i+1,j idxIIJ = i-1,j idxIJJ = i,j+1  idxJIJ = i,j-1*/
		
		node_t fdOnR, fdOnZ; /*!< Transitional nodes to store iterations on each dimension */


		for(int i(0); i < mMesh.getNodesOnDim(0); i++)
		{
			for(int j(0); j < mMesh.getNodesOnDim(1); j++)
			{

				idxIJ = {i,j};

				fdOnR = coeff1*FDSecondOrder(idxIJ,mMesh,1); /*!< Coordinates should be (z,r) so the horizontal axis represents longitudinal dimension */
				fdOnZ = coeff2*Cartesian_Coordinates::FDSecondOrder(idxIJ,mMesh,0); /*!< Coordinates should be (z,r) so the vertical axis represents radial dimension */


				mBufferMesh[idxIJ] = mMesh[idxIJ] + dDeltaT*( fdOnR + fdOnZ);

			}
		}


		return mBufferMesh;
	}
}


