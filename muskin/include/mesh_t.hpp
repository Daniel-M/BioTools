//#include "headers.hpp"
//#include "mesh.cpp"
//#include "pTreeXML.cpp"

//int_t node_t::sitNumberOfNodes=0;

class mesh_t
{
	private:

	int_t itMeshDim; /*!< Dimension of the mesh_t object.*/
	int_t itNumberOfNodes; /*!< Number of node_ts of the mesh_t object.*/
	int_t itBoundaryNodes; /*!< Number of node_t objects at the mesh_t object boundary.*/
	int_t itInnerNodes; /*!< Number of node_ts on the inner region of the mesh_t object.*/
	static int_t siMeshNumber; /*!< Static variable that numbers the mesh_t object.*/
	//int_t node_t::sitNumberOfNodes=0;

	std::string sMeshName; /*!< mesh_t object name. This identifies the mesh_t.*/
	std::string sMeshJSON; /*!< mesh_t object name of the associated JSON formatted file. */
	std::string sMeshXML; /*!< mesh_t object name of the associated XML formatted file.*/
	std::string sMeshFile; /*!< mesh_t object name of the associated mesh_t file (That file can be plotted once created).*/
	
	index_t inNodesOnDim; /*!< Number of node_ts on each dimension composing the mesh_t object.*/

	point_t ptDeltaOnDim; /*!< Delta on each dimension of the mesh_t object.*/
	point_t ptRectangleLowA; /*!< Initial point on the rectangle's diagonal that defines the domain of the mesh_t.*/
	point_t ptRectangleHighB; /*!< Final point on the rectangle's diagonal that defines the domain of the mesh_t.*/
	
	std::vector<node_t> vBoundaryMesh; /*!< Temporary vector variable should be replaced some way.*/
	std::vector<node_t> vInnerMesh; /*!< Temporary vector variable should be replaced some way.*/

	std::map<index_t,node_t> mBoundaryMesh; /*!< Mapping of indexes and node_ts on the boundary region of the mesh_t object. indexes can not be repeated. */
	std::map<index_t,node_t> mInnerMesh; /*!< Mapping of indexes and node_ts on the inner region of the mesh_t object. indexes can not be repeated. */

	std::vector<voxel_t> vMeshVoxels; /*!< Mapping of the voxel_t inside the mesh */

	boost::property_tree::ptree prTreeMesh; /*!< Property tree containing the configuration of the mesh_t object.*/


	public:
	
	/* Class constructors */
	
	/*!\brief Standard constructor of mesh_t objects. */
	mesh_t();

	/*!\brief Standard copy constructor.
	 * \param mRHSMesh The mesh_t whose properties get copied into the new mesh_t object to be created.*/
	mesh_t(const mesh_t& mRHSMesh);
	
	/*!\brief Constructor to create and empty mesh. */
	mesh_t(int_t iVoid);

	/*!\brief Constructor that automatically assings name to the mesh_t object, the remaining must be provided.
	 * \param iDim Dimension of the mesh_t.
	 * \param inNodesOnDim node_ts on each of the dimensions.
	 * \param ptRangeA coordinates of the first point of the diagonal.
	 * \param ptRangeB coordinates of the second point of the diagonal.
	 * \return mesh_t object.
	 * */
	mesh_t(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB);
	
	/*!\brief Constructor. All related information must be provided.
	* \param iDim Dimension of the mesh_t.
	 * \param inNodesOnDim node_ts on each of the dimensions.
	 * \param ptRangeA coordinates of the first point of the diagonal.
	 * \param ptRangeB coordinates of the second point of the diagonal.
	 * \param sMeshName Name of the mesh_t.
	 * \return mesh_t object.
	 * */
	mesh_t(int_t iDim,index_t inNodesOnDim,point_t ptRangeA, point_t ptRangeB,std::string sMeshName);
	
	/*!\brief Constructor that uses a property tree to build the mesh_t.
	 * \param prTree Property Tree containing all the information of the mesh_t to be created.
	 * */
	mesh_t(boost::property_tree::ptree prTree);
	
	/*!\brief Constructor that reads the mesh_t from a JSON or XML formatted file.
	 * \param sFileName Name of the JSON or XML formatted file to read looking for the mess parameters.
	 * */
	mesh_t(std::string sFileName);

	
	/* Class operators */
	
	/*!\brief Access to the node_t at the given index.
	 * \param inIndex Index of the node_t to be referenced from mesh_t. 
	 * */
	node_t& operator[](const index_t inIndex);

	/*!\brief assignation operator for mesh_t objects.
	 * \param mRHSMesh The mesh_t object to be assigned to \c this.
	 */
	mesh_t& operator=(const mesh_t& mRHSMesh);


	/* int_t return methods */
	
	/*!\brief Creates the mesh_t file \c .msh which can be plotted to see the actual geometrical mesh_t.
	 * \return Status of the execution.*/
	int_t createMeshFile();
	
	/*!\brief Creates the mesh_t file \c .msh which can be plotted to see the actual geometrical mesh_t.
	 * \param sFileName the name of the file to save the coordinates of the node_ts on the mesh_t.
	 * \return Status of the execution.
	 * */
	int_t createMeshFile(std::string sFileName);
	
	/*!\brief Creates a PNG with the mesh_t plotted.
	 * \return Status of the execution.*/
	int_t createMeshPNG();

	int_t getNodesOnDim(int iDim);
	
	
	/* floating_t return methods */

	/*!\brief Returns the delta on the dimension iDim.
	 * \param iDim The desired dimension to retrieve the Delta.
	 * \return The delta on the desired dimension
	 * \sa getDeltaOnDim()
	 * */
	floating_t getDeltaOnDim(int_t iDim);


	/* index_t return methods */

	index_t getNodesOnDim();

	/* point_t returning methods */

	/*!\brief Returns a vector with the delta on each dimension.
	 * \return Vector with all the deltas
	 * \sa getDeltaOnDim(int_t iDim)
	 * */
	point_t getDeltaOnDim();
	
	/* void return methods */
	
	/*!\brief Creates a JSON formatted file with the parameters of the mesh_t.*/
	void createMeshJSON();

	/*!\brief Creates a JSON formatted file with the parameters of the mesh_t.
	 * \param sFileName The name of the JSON file to be created.
	 * */	
	void createMeshJSON(std::string sFileName);
	
	/*!\brief Creates a XML formatted file with the parameters of the mesh_t.*/
	void createMeshXML();
	
	/*!\brief Creates a XML formatted file with the parameters of the mesh_t.
	 * \param sFileName The name of the XML file to be created.
	 * */	
	void createMeshXML(std::string sFileName);
	
	/*!\brief Creates or overwrites the property tree of the mesh_t object.*/
	void createPropertyTree();
	
	/*!\brief Inserts node into the boundary of the mesh_t.*/
	void push_backBN(node_t cNode);
	
	/*!\brief Inserts node into the inner region of the mesh_t.*/
	void push_backIN(node_t cNode);
	
	/*!\brief Sets the name of the mesh_t object.*/
	void setMeshName(std::string sMeshName_);


	/* Friend methods */
	
	/*!\brief Friend function to send mesh_t to streams. */
	friend	std::ostream& operator<<(std::ostream& outStream, mesh_t& cMesh);

	///*!\brief Friend function to iterate over indexes of the  mesh_t.*/
	//friend mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT);
	
	/* Misc methods */
	
	/*!\brief Gets the actual property tree of the mesh_t object. */
	boost::property_tree::ptree getPropertyTree();

		

};

