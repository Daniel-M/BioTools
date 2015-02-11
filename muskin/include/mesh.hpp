//#include "headers.hpp"

//int_t node::sitNumberOfNodes=0;

class mesh
{
	private:

    int_t itMeshDim;
	int_t itNumberOfNodes;
	int_t itBoundaryNodes;
	int_t itInnerNodes;
	static int_t siMeshNumber;
	//int_t node::sitNumberOfNodes=0;

	index_t inNodesOnDim;

	point_t ptDeltaOnDim;
	point_t ptRectangleLowA;
	point_t ptRectangleHighB;

	std::string sMeshName;
	std::string sMeshXML;
	std::string sMeshFile;
	
	std::vector<node> vBoundaryMesh;
	std::vector<node> vInnerMesh;

	boost::property_tree::ptree prtrXML;

	//mesh();
	//mesh(){ itNumberOfNodes=0;}

	public:
	mesh();
	mesh(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB);
	mesh(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB,std::string sMeshName);
	mesh(std::string sFileName);
	//mesh(int_t iDim,point_t ptDeltaOnDim,point_t ptRangeA, point_t ptRangeB);

	//int_t createMeshFile(std::string sFileName);
	int_t createMeshPNG();
	int_t createMeshFile();
	int_t createMeshXML();
	int_t createMeshXML(std::string sFileName);
	int_t createMeshFile(std::string sFileName);
	//int_t createMeshPNG();

	void setMeshName(std::string sMeshName_);
	void push_backIN(node cNode);
	void push_backBN(node cNode);

};

