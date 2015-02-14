//#include "headers.hpp"
//#include "mesh.cpp"
//#include "pTreeXML.cpp"

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
	/* Mesh constructors */
	mesh();
	mesh(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB);
	mesh(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB,std::string sMeshName);
	mesh(std::string sFileName);

	/* Int_t return methods */
	int_t createMeshPNG();
	int_t createMeshFile();
	int_t createMeshXML();
	int_t createMeshXML(std::string sFileName);
	int_t createMeshFile(std::string sFileName);

	/* void return methods */
	void setMeshName(std::string sMeshName_);
	void push_backIN(node cNode);
	void push_backBN(node cNode);


	/* Friend methods */
	/*!\brief Friend function to send nodes to streams 
	 * 
	 * Nodes are displayed as
	 * [node_number][node_indices](node_coordinates) node_value
	 *
	 * */
	friend	std::ostream& operator<<(std::ostream& outStream, mesh& cMesh);
	//friend	void pTreeXML(node& nod);
};

