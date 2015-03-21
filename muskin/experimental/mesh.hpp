//#include "headers.hpp"
//#include "mesh.cpp"
//#include "pTreeXML.cpp"

//int_t node::sitNumberOfNodes=0;

class mesh
{
	private:

	int_t itMeshDim; /*!< Dimension of the mesh object.*/
	int_t itNumberOfNodes; /*!< Number of nodes of the mesh object.*/
	int_t itBoundaryNodes; /*!< Number of node objects at the mesh object boundary.*/
	int_t itInnerNodes; /*!< Number of nodes on the inner region of the mesh object.*/
	static int_t siMeshNumber; /*!< Static variable that numbers the mesh object.*/
	//int_t node::sitNumberOfNodes=0;

	std::string sMeshName; /*!< Mesh object name. This identifies the mesh.*/
	std::string sMeshJSON; /*!< Mesh object name of the associated JSON formatted file. */
	std::string sMeshXML; /*!< Mesh object name of the associated XML formatted file.*/
	std::string sMeshFile; /*!< Mesh object name of the associated mesh file (That file can be plotted once created).*/
	
	index_t inNodesOnDim; /*!< Number of nodes on each dimension composing the mesh object.*/

	point_t ptDeltaOnDim; /*!< Delta on each dimension of the mesh object.*/
	point_t ptRectangleLowA; /*!< Initial point on the rectangle's diagonal that defines the domain of the mesh.*/
	point_t ptRectangleHighB; /*!< Final point on the rectangle's diagonal that defines the domain of the mesh.*/
	
	std::vector<node> vBoundaryMesh; /*!< Temporary vector variable */
	std::vector<node> vInnerMesh; /*!< Temporary vector variable */
	std::map<index_t,node> mBoundaryMesh; /*!< Mapping of indexes and nodes on the boundary region of the mesh object. indexes can not be repeated. */
	std::map<index_t,node> mInnerMesh; /*!< Mapping of indexes and nodes on the inner region of the mesh object. indexes can not be repeated. */

	boost::property_tree::ptree prTreeMesh; /*!< Property tree containing the configuration of the mesh object.*/


	public:
	
	/* Class constructors */
	
	/*!\brief Standard constructor of mesh objects. */
	mesh();
	
	/*!\brief Constructor that automatically assings name to the mesh object, the remaining must be provided.
	 * \param iDim Dimension of the mesh.
	 * \param inNodesOnDim Nodes on each of the dimensions.
	 * \param ptRangeA coordinates of the first point of the diagonal.
	 * \param ptRangeB coordinates of the second point of the diagonal.
	 * \return Mesh object.
	 * */
	mesh(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB);
	
	/*!\brief Constructor. All related information must be provided.
	* \param iDim Dimension of the mesh.
	 * \param inNodesOnDim Nodes on each of the dimensions.
	 * \param ptRangeA coordinates of the first point of the diagonal.
	 * \param ptRangeB coordinates of the second point of the diagonal.
	 * \param sMeshName Name of the mesh.
	 * \return Mesh object.
	 * */
	mesh(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB,std::string sMeshName);
	
	/*!\brief Constructor that uses a property tree to build the mesh.
	 * \param prTree Property Tree containing all the information of the mesh to be created.
	 * */
	mesh(boost::property_tree::ptree prTree);
	
	/*!\brief Constructor that reads the mesh from a JSON or XML formatted file.
	 * \param sFileName Name of the JSON or XML formatted file to read looking for the mess parameters.
	 * */
	mesh(std::string sFileName);

	
	/* Class operators */
	
	/*!\brief Access to the node at the given index.
	 * \param inIndex Index of the node to be referenced from mesh. 
	 * */
	node& operator[](const index_t inIndex);
	
	
	/* int_t return methods */
	
	/*!\brief Creates the mesh file \c .msh which can be plotted to see the actual geometrical mesh.*/
	int_t createMeshFile();
	
	/*!\brief Creates the mesh file \c .msh which can be plotted to see the actual geometrical mesh.
	 * \param sFileName the name of the file to save the coordinates of the nodes on the mesh.
	 * */
	int_t createMeshFile(std::string sFileName);
	
	/*!\brief Creates a PNG with the mesh plotted.*/
	int_t createMeshPNG();
	

	
	/* floating_t return methods */

	
	
	/* void return methods */
	
	/*!\brief Creates a JSON formatted file with the parameters of the mesh.*/
	void createMeshJSON();

	/*!\brief Creates a JSON formatted file with the parameters of the mesh.
	 * \param sFileName The name of the JSON file to be created.
	 * */	
	void createMeshJSON(std::string sFileName);
	
	/*!\brief Creates a XML formatted file with the parameters of the mesh.*/
	void createMeshXML();
	
	/*!\brief Creates a XML formatted file with the parameters of the mesh.
	 * \param sFileName The name of the XML file to be created.
	 * */	
	void createMeshXML(std::string sFileName);
	
	/*!\brief Creates or overwrites the property tree of the mesh object.*/
	void createPropertyTree();
	
	/*!\brief */
	void push_backIN(node cNode);
	
	/*!\brief */
	void push_backBN(node cNode);
	
	/*!\brief Sets the name of the mesh object.*/
	void setMeshName(std::string sMeshName_);


	/* Friend methods */
	
	/*!\brief Friend function to send mesh to streams. */
	friend	std::ostream& operator<<(std::ostream& outStream, mesh& cMesh);
	
	
	/* Misc methods */
	
	/*!\brief Gets the actual property tree of the mesh object. */
	boost::property_tree::ptree getPropertyTree();

	

};

