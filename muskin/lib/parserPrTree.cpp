#include "headers.hpp"
//#include "mesh.hpp"

/* The statements beggingin with "_p" are #define on typedef.hpp and used as parsing statements */

/*!\brief Creates JSON parsed file with the information about the mesh object
 *
 * Creates JSON parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a JSON file
 * using the standard name of the JSON file for the mesh object
 * 
 */
void mesh::createMeshJSON()
{
	createPropertyTree();
	boost::property_tree::write_json(sMeshJSON,prTreeMesh);
	//createMeshJSON(sMeshName + "." + _pMeshJSON);
}


/*!\brief Creates JSON parsed file with the information about the mesh object
 *
 * Creates JSON parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a JSON file whose name is
 * passed as an argument.
 * 
 * \param sFileName Name of the destination JSON file
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

	boost::property_tree::write_json(sFileName,prTreeMesh);
}


/*!\brief Creates XML parsed file with the information about the mesh object
 *
 * Creates XML parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a XML file
 * using the standard name of the XML file for the mesh object
 * 
 */
void mesh::createMeshXML()
{
	createPropertyTree();
	boost::property_tree::write_xml(sMeshXML,prTreeMesh);
}


/*!\brief Creates XML parsed file with the information about the mesh object
 *
 * Creates XML parsed file with the information about the mesh object.
 * This method (re)creates the property tree prior parsing to a XML file whose name is
 * passed as an argument.
 * 
 * \param sFileName Name of the destination XML file
 *
 */
void mesh::createMeshXML(std::string sFileName)
{
	createPropertyTree();
	std::string sPath(_pMesh);
	sPath+= ".file.";
	sPath+= _pMeshXML;
	prTreeMesh.put(sPath,sFileName);
	
	boost::property_tree::write_xml(sFileName,prTreeMesh);
}


/*! \brief creates the libboost property tree of the mesh in memory prior parsing
 *
 * The property tree is a container that can be used to parse
 * info,JSON or XML specifications of mesh objects.
 * This method creates a libboost property tree of the mesh object in memory prior parsing
 * to a info, JSON or XML.
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
 * INFO,JSON or XML specifications of mesh objects.
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


/**\brief This function overloads the libboost::ptree::operator<< to stream \a libboost::ptree
 * 
 * This function overloads the libboost::ptree::operator<< to provide streaming for \a libboost::ptree
 *
 * \param[in] outStream stream data type.
 * \param[in] prTree boost::property_tree::ptree container.
 * \return A ostream consisting of the information contained on the property tree
 */
//std::ostream& operator<<(std::ostream& outStream, boost::property_tree::ptree& prTree)
std::ostream& operator<<(std::ostream& outStream, boost::property_tree::ptree& prTree)
{
	/* This function has a depth of 3 levels on the property tree, it works fine for
	 * the libmesh property trees. In order to get a better version a self-recursive function
	 * must be implemented. something like
	 *
	 * f(x)
	 * {
	 * 		//some code
	 * 		f(x);
	 * }
	 */
	std::vector< std::pair<std::string,std::string> > vpFieldsPairsV;
	std::pair<std::string,std::string> pFieldsPair;
 
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& rowPair, prTree.get_child( "" ) ) 
    {
		//std::cout << rowPair.first << ": " << std::endl;

		pFieldsPair = std::make_pair(rowPair.first,rowPair.second.get_value<std::string>());
		vpFieldsPairsV.push_back(pFieldsPair);

 
        BOOST_FOREACH( boost::property_tree::ptree::value_type const& itemPair, rowPair.second ) 
        {
			//std::cout << "\t" << itemPair.first << " ->";
 
            pFieldsPair = std::make_pair(itemPair.first,itemPair.second.get_value<std::string>());
			vpFieldsPairsV.push_back(pFieldsPair);

			BOOST_FOREACH( boost::property_tree::ptree::value_type const& node, itemPair.second ) 
            {
				//std::cout << node.second.get_value<std::string>() << " , ";
				
				pFieldsPair = std::make_pair(node.first,node.second.get_value<std::string>());
				vpFieldsPairsV.push_back(pFieldsPair);

				BOOST_FOREACH( boost::property_tree::ptree::value_type const& node1, node.second ) 
				{
					//std::cout << node1.second.get_value<std::string>() << " ; ";
					pFieldsPair = std::make_pair(node1.first,node1.second.get_value<std::string>());
					vpFieldsPairsV.push_back(pFieldsPair);
				}
			}
 
			//std::cout << std::endl;
 
        }
 
		//std::cout << std::endl;
    }
     
	//std::cout  << "Information read: " << std::endl;
	//outStream  << "Information read: " << std::endl;
	
	for(int i(0);i<vpFieldsPairsV.size();i++)
	{
		//std::cout << vpFieldsPairsV[i].first << "\t" << vpFieldsPairsV[i].second << std::endl;
		outStream << vpFieldsPairsV[i].first << "\t" << vpFieldsPairsV[i].second << std::endl;
	}

	return outStream;
}


/* The prTreeMesh structure must be like this (json formatted),
 * The fields indicated with [R] are required while the [O]
 * means optional.
 *
 * {
 *    "mesh": [R] 
 *    {
 *        "name": "aMesh", [R]
 *        "dimension": "2", [R]
 *        "numberofnodes": "2000", [R]
 *        "bnodes": "176", [O]
 *        "inodes": "1824", [O]
 *        "files": [O]
 *        {
 *            "xml": "aMesh.xml", [O]
 *            "json": "aMesh.json", [O]
 *            "meshfile": "aMesh.msh" [O]
 *        },
 *        "nodesondim": [O]
 *        {
 *            "0": "40",
 *            "1": "50"
 *        },
 *        "deltaondim": [O]
 *        {
 *            "0": "0.1025641025641026",
 *            "1": "0.2040816326530612"
 *        },
 *        "pointa": [R]
 *        {
 *            "0": "1",
 *            "1": "0"
 *        },
 *        "pointb": [R]
 *        {
 *            "0": "5",
 *            "1": "10"
 *        }
 *    }
 *}
 */ 
  
/*! \brief libmesh constructor by pasing the name of a JSON or XML formatted file with information of mesh
 *
 * libmesh constructor that reads information of a JSON or XML formatted file. The constructor determines the parsing method
 * by the file extension XML or JSON.
 *
 * \param[in] sFileName \c std::string with the name of the file with extension.
 */
mesh::mesh(std::string sFileName)
{
	std::string sJSON(".");
	sJSON+=_pMeshJSON;
	std::string sXML(".");
	sXML+=_pMeshXML;

	/* Each conditional searches for the string ".EXTENSION" in the given sFileName. */
	/* is JSON formatted? */
	if(sFileName.find(sJSON) < sFileName.size() )
	{
		//std::cout << "is json " << sFileName.find(_pMeshJSON) << std::endl;
		boost::property_tree::read_json(sFileName,prTreeMesh);

		//std::cout << "File: " << sFileName << " contains:\n";
		std::cout << prTreeMesh  << std::endl;
	}
	/* Is XML formatted? */
	else if(sFileName.find(sXML) < sFileName.size())
	{
		//std::cout << "is xml " << sFileName.find(_pMeshXML) << std::endl;
		boost::property_tree::read_xml(sFileName,prTreeMesh);
		
		//std::cout << "File: " << sFileName << " contains:\n";
		std::cout << prTreeMesh << std::endl;
	}
	/* If sFileName does not contain .EXTENSION with .json or .xml the constructor returns an error */
	else
	{
		std::cout << "[EE] Error! Could not load file " << sFileName << std::endl;
		*this = mesh();
	}
}

