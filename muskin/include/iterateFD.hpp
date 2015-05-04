//mesh_t IterateFDCartesian(mesh_t& mMesh,floating_t dDeltaT);
//#include "headers.hpp"

/*! \brief Increments or decrements indices. */
index_t DeltaIdx(index_t& index,int_t pos,int_t value);


namespace Cartesian_Coordinates
{
	node_t FDFirstOrderForward(index_t idxIJ, mesh_t& mMesh,int_t IdXPos); 

	node_t FDFirstOrderBackward(index_t idxIJ, mesh_t& mMesh,int_t IdXPos); 

	node_t FDFirstOrderCentered(index_t idxIJ, mesh_t& mMesh,int_t IdXPos);

	node_t FDSecondOrder(index_t idxIJ, mesh_t& mMesh,int_t IdXPos);

	mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT);
}

namespace Cylindrical_Coordinates
{

	node_t FDSecondOrder(index_t idxIJ, mesh_t& mMesh,int_t IdXPos);
	
	mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT);
}


