//#include "headers.hpp"

//int_t node::sitNumberOfNodes=0;

class mesh
{
	private:

    int_t itMeshDim;

	int_t itNumberOfNodes;

	index_t itNodesOnDim;
	point_t ptDeltaOnDim;

	//int_t node::sitNumberOfNodes=0;
	
	std::vector<node> vBoundaryMesh;
	std::vector<node> vInnerMesh;

	//mesh();
	//mesh(){ itNumberOfNodes=0;}

	public:
	mesh();
	mesh(int_t iDim,index_t itNodesOnDim,point_t ptRangeA, point_t ptRangeB);
	//mesh(int_t iDim,point_t ptDeltaOnDim,point_t ptRangeA, point_t ptRangeB);

	int_t createMeshFile(std::string sFileName);
	void push_backIN(node cNode);
	void push_backBN(node cNode);

};

