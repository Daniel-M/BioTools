#include "headers.hpp"
//#include "mesh.hpp"

/* The statements beggingin with "_p" are #define on typedef.hpp and used as parsing statements */

/*!\brief Creates json parsed file with the information about the mesh object
 *
 * Creates json parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a JSON file
 * using the standard name of the json file for the mesh object
 * 
 */
void mesh::createMeshJSON()
{
	createPropertyTree();
	write_json(sMeshJSON,prTreeMesh);
	//createMeshJSON(sMeshName + "." + _pMeshJSON);
}


/*!\brief Creates json parsed file with the information about the mesh object
 *
 * Creates json parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a JSON file whose name is
 * passed as an argument.
 * 
 * \param sFileName Name of the destination json file
 *
 */
void mesh::createMeshJSON(std::string sFileName)
{
	//sMeshJSON = sFileName;

	createPropertyTree();
	std::string sPath(_pMesh);
	sPath+= ".file.";
	sPath+= _pMeshJSON;
	prTreeMesh.put(sPath,sFileName);

	write_json(sFileName,prTreeMesh);
}


/*!\brief Creates xml parsed file with the information about the mesh object
 *
 * Creates xml parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a XML file
 * using the standard name of the xml file for the mesh object
 * 
 */
void mesh::createMeshXML()
{
	createPropertyTree();
	write_xml(sMeshXML,prTreeMesh);
}


/*!\brief Creates xml parsed file with the information about the mesh object
 *
 * Creates xml parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a XML file whose name is
 * passed as an argument.
 * 
 * \param sFileName Name of the destination xml file
 *
 */
void mesh::createMeshXML(std::string sFileName)
{
	createPropertyTree();
	std::string sPath(_pMesh);
	sPath+= ".file.";
	sPath+= _pMeshXML;
	prTreeMesh.put(sPath,sFileName);
	
	write_xml(sFileName,prTreeMesh);
}


/*! \brief creates the libboost property tree of the mesh in memory prior parsing
 *
 * The property tree is a container that can be used to parse
 * info,json or xml specifications of mesh objects.
 * This method creates a libboost property tree of the mesh object in memory prior parsing
 * to a info, json or xml.
 */
void mesh::createPropertyTree()
{
	/* The libboost::property_tree.clear() statements are used to clear the memory of the libboost property tree
	 * This is used to avoid creating more variables and recycling the old-ones.
	 * */

	//prTreeMesh.clear();
	boost::property_tree::ptree prSubTree;
	boost::property_tree::ptree arrayElement;
	boost::property_tree::ptree prChildTree;

	/* Basic Properties of the Mesh*/
	prSubTree.add(_pMeshName,sMeshName);
	prSubTree.add(_pMeshDim,itMeshDim);
	prSubTree.add(_pMeshNN,itNumberOfNodes);
	prSubTree.add(_pMeshBN,itBoundaryNodes);
	prSubTree.add(_pMeshIN,itInnerNodes);

	/* putting the associated files in subtree "files" */
	arrayElement.put_value(sMeshXML);
	prChildTree.push_back(std::make_pair(_pMeshXML,arrayElement));
	arrayElement.put_value(sMeshJSON);
	prChildTree.push_back(std::make_pair(_pMeshJSON,arrayElement));
	arrayElement.put_value(sMeshFile);
	prChildTree.push_back(std::make_pair(_pMeshFile,arrayElement));

	/* add files subtree */
	prSubTree.add_child(boost::property_tree::ptree::path_type("files"),prChildTree);
	arrayElement.clear();
	prChildTree.clear();

	/* iterate over the number of nodes on each dim*/
	for(int i(0); i < inNodesOnDim.size();i++)
	{
		arrayElement.put_value(inNodesOnDim[i]);
		prChildTree.push_back(std::make_pair(NumberToString(i),arrayElement));
	}

	prSubTree.add_child(boost::property_tree::ptree::path_type(_pMeshND),prChildTree);
	arrayElement.clear();
	prChildTree.clear();

	/* iterate over the deltas on each dim */
	for(int i(0); i < ptDeltaOnDim.size();i++)
	{
		arrayElement.put_value(ptDeltaOnDim[i]);
		prChildTree.push_back(std::make_pair(NumberToString(i),arrayElement));
	}

	prSubTree.add_child(boost::property_tree::ptree::path_type(_pMeshDD),prChildTree);
	arrayElement.clear();
	prChildTree.clear();

	/* iterate over the coordinates of PointB*/
	for(int i(0); i < ptRectangleLowA.size();i++)
	{
		arrayElement.put_value(ptRectangleLowA[i]);
		prChildTree.push_back(std::make_pair(NumberToString(i),arrayElement));
	}
	
	prSubTree.put_child(boost::property_tree::ptree::path_type(_pMeshPA),prChildTree);
	arrayElement.clear();
	prChildTree.clear();

	/* iterate over the coordinates of PointB*/
	for(int i(0); i < ptRectangleHighB.size();i++)
	{
		arrayElement.put_value(ptRectangleHighB[i]);
		prChildTree.push_back(std::make_pair(NumberToString(i),arrayElement));
	}
	/* Add child to subtree */
	prSubTree.put_child(boost::property_tree::ptree::path_type(_pMeshPB),prChildTree);
	
	/* Replace existing property tree with the new by adding the subtree just created*/
	prTreeMesh.put_child(boost::property_tree::ptree::path_type(_pMesh),prSubTree);

}



/*!\brief Get libboost property tree of the mesh.
 * 
 * The property tree is a container that can be used to parse
 * info,json or xml specifications of mesh objects.
 * This method returns the associated property tree of the mesh object.
 * The property tree is recreated on each run of this method by calling
 * the method mesh::createPropertyTree()
 *
 * \return boost::property_tree:ptree object of the mesh object.
 */
boost::property_tree::ptree mesh::getPropertyTree()
{
	createPropertyTree();
	
	return prTreeMesh;
}


