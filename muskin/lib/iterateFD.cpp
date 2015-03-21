#include "headers.hpp"

mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT)
{
	mesh_t mBufferMesh(mMesh);
	std::cout << "hello\n";

	int_t indexX1, indexX2; /*!< Buffer for the indexes */

	index_t idxIJ, idxIJI, idxIJJ, idxIIJ, idxJIJ;
	//index_t idx1IJ, idx1IJI, idx1IJJ, idx1IIJ, idx1IJJ;
	//index_t idx2IJ, idx2IJI, idx2IJJ, idx2IIJ, idx2IJJ;
	
	node_t nnBuffer; /*!< Buffer node to store the result of the iteration */

	//mBufferMesh[idxIJ] = dDeltaT*( (mMesh[idxIJI] - 2*mMesh[idxIJ] + mMesh[idxIIJ])/(mMesh.ptDeltaOnDim[0]) + (mMesh[idxIJJ] - 2*mMesh[idxIJ] + mMesh[idxJIJ])/(mMesh.ptDeltaOnDim[1]));


	/*!< Boundary region of the mesh */

	/*!< Inner region of the mesh */
}
