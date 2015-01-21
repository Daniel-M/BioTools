//#include "headers.hpp"

//int_t node::siNumberOfNodes=0;

class mesh
{
	private:

    int_t iMeshDim;

	int_t iNumberOfNodes;

	point_t ptDeltaOnDim;

	//int_t node::siNumberOfNodes=0;
	
	std::vector<node> vBoundaryMesh;
	std::vector<node> vInnerMesh;

	//mesh();
	//mesh(){ iNumberOfNodes=0;}

	public:
	mesh();
	mesh(int_t iDim,index_t itNodesOnDim,point_t ptRangeA, point_t ptRangeB);
	void push_backIN(node cNode);
	void push_backBN(node cNode);

};

