#include "headers.hpp"

void DeltaIdx(index_t& index,int_t pos,int_t value)
{
	index[pos] += value;
	return ;
}

mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT)
{
	mesh_t mBufferMesh(mMesh);

	std::cout << "hello\n";

	double coeff1(1.0/pow(mMesh.getDeltaOnDim(0),2)), coeff2(1.0/pow(mMesh.getDeltaOnDim(1),2));
	int_t indexX1, indexX2; /*!< Buffer for the indexes */

	index_t idxIJ, idxIJI, idxIJJ, idxIIJ, idxJIJ;
	//index_t idx1IJ, idx1IJI, idx1IJJ, idx1IIJ, idx1IJJ;
	//index_t idx2IJ, idx2IJI, idx2IJJ, idx2IIJ, idx2IJJ;
	
	node_t fdOnX, fdOnY;
	node_t nnBuffer; /*!< Buffer node to store the result of the iteration */

	idxIJ = {0,0};

	for(int i;i<mMesh.getNodesOnDim(0)-1;i++)
	{
		DeltaIdx(idxIJI,0,1);
		DeltaIdx(idxIIJ,0,-1);
		DeltaIdx(idxIJJ,1,1);
		DeltaIdx(idxJIJ,1,-1);

		std::cout << idxIJ << "\t" <<  idxIJI << "\t" <<  idxIIJ << "\t" <<   idxIJJ << "\t" <<   idxJIJ << std::endl; 

		fdOnX = coeff1*(mMesh[idxIJI] - 2*mMesh[idxIJ] + mMesh[idxIIJ]);
		fdOnY = coeff2*(mMesh[idxIJJ] - 2*mMesh[idxIJ] + mMesh[idxJIJ]);

		mBufferMesh[idxIJ] = mMesh[idxIJ] + dDeltaT*( fdOnX + fdOnY);
	}

	idxIJ = {0,0};

	for(int i;i<mMesh.getNodesOnDim(0)-1;i++)
	{
		std::cout << idxIJ << "\t";
		std::cout << mBufferMesh[idxIJ] << std::endl;
		
		DeltaIdx(idxIJ,0,1);
	}

	/*!< Boundary region of the mesh */

	/*!< Inner region of the mesh */
}
