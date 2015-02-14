#include "headers.hpp"
//#include "mesh.hpp"

/* The statements beggingin with "_p" are #define on typedef.hpp and used as parsing statements */

/**\brief This function overloads the libboost::ptree::operator<< to stream \a std::vectors
 *
 * This function overloads the libboost::ptree::operato<< to provide streaming for \a libboost::ptree
 *
 * \param[in] outStream stream data type.
 * \return A ostream consisting of the vector size and the vector components separated by commas.
 */

std::ostream& operator<<(std::ostream& outStream, boost::property_tree::ptree& prTree)
{

	/* Ideas:
	 * Construrir un vector que mapee <string:string> y posteriormente barrer el vector en cada pareja
	 * para obtener la información necesaria... es importante escanear 
	 */
	/* Top Level of tree : Level 0*/
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& rowPair, prTree.get_child( "" ) ) 
    {
        outStream << rowPair.first << ": " << std::endl;
 		
		/* Level 1 
		 *	At this point the relevant information can be obtained on itemPair. members
		 * */
        BOOST_FOREACH( boost::property_tree::ptree::value_type const& itemPair, rowPair.second ) 
        {
			outStream << "\t" << itemPair.first << " -> " << itemPair.second.get_value<std::string>() << " ; ";
			//outStream << "\t" << itemPair.first << " -> ";
 			
			/* Level 2*/
            BOOST_FOREACH( boost::property_tree::ptree::value_type const& node, itemPair.second ) 
            {
                outStream << "\t" << node.first << "|" << node.second.get_value<std::string>() << " , ";
			
				/* Level 3 ¿if any?  This could be a recursive function
				 * Something as 
				 * 	func(x)
				 * 	{
				 * 		// do stuff here
				 * 		func(x);
				 * 	}
				 *	I've done that sh*t before. 
				 * */
				BOOST_FOREACH( boost::property_tree::ptree::value_type const& node1, node.second ) 
				{
					outStream << node1.second.get_value<std::string>() << " | ";
				}
            }
 
            outStream << std::endl;
 
        }
 
        outStream << std::endl;
    }
     
    outStream << std::endl;


	return outStream;
}


mesh::mesh(std::string sFileName)
{
	/* is json?*/
	if(sFileName.find(_pMeshJSON) < sFileName.size() )
	{
		//std::cout << "is json " << sFileName.find(_pMeshJSON) << std::endl;
		read_json(sFileName,prTreeMesh);

		std::cout << prTreeMesh  << std::endl;
	}
	/* is xml? */
	else if(sFileName.find(_pMeshXML) < sFileName.size())
	{
		//std::cout << "is xml " << sFileName.find(_pMeshXML) << std::endl;
		read_xml(sFileName,prTreeMesh);
		std::cout << prTreeMesh  << std::endl;
	}
	/* none of the above so error shown*/
	else
	{
		std::cout << "Could not load file " << sFileName << std::endl;
	}
}


