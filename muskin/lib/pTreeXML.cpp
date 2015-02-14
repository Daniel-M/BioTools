#include "headers.hpp"
//#include "mesh.hpp"

/* The statements beggingin with "_p" are #define on typedef.hpp and used as parsing statements */

mesh::mesh(std::string sFileName)
{
	/* is json?*/
	if(sFileName.find(_pMeshJSON) < sFileName.size() )
	{
		//std::cout << "is json " << sFileName.find(_pMeshJSON) << std::endl;
		read_json(sFileName,prTreeMesh);
	}
	/* is xml? */
	else if(sFileName.find(_pMeshXML) < sFileName.size())
	{
		//std::cout << "is xml " << sFileName.find(_pMeshXML) << std::endl;
		read_xml(sFileName,prTreeMesh);
	}
	/* none of the above so error shown*/
	else
	{
		std::cout << "Could not load file " << sFileName << std::endl;
	}
}


