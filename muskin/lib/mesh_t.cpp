#include "headers.hpp"
//#define Debug(N) std::cout << "\n * Debug " << N << std::endl
//#include "mesh.hpp"

/*! This standard constructor creates a standard 2D mesh_t with 100 node_ts 
 *	The created mesh_t is defined on the rectangle defined by the diagonal (0,0) to (1,1)
 *	with 10 indexes along each dimension which makes 100 node_ts.
 *
 *	The name of the mesh_t created with this constructor is set to \a NewMesh.
 *	This name is used to create all the .json,.xml,.msh related to the mesh_t object.
 * */
mesh_t::mesh_t() : mesh_t(2,{10,10},{0,0}, {1,1})
{
	std::cout << "Standard mesh created:" << std::endl;
	std::cout << *this << std::endl;
}

/*! This constructor obtains all the parameters provided on the mesh_t object call and gives the automatic name of \a NewMesh.
 * This name is used to create all the .json,.xml,.msh related to the mesh_t object.*/
mesh_t::mesh_t(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB) : mesh_t(iDim,inNodesOnDim_,ptRangeA, ptRangeB,"NewMesh")
{
}

/*!This constructor obtains all parameters provided to create the mesh_t.
 * This name is used to create all the .json,.xml,.msh related to the mesh_t object.*/
mesh_t::mesh_t(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB,std::string sMeshName)
{
	setMeshName(sMeshName);
	
	ptRectangleLowA = ptRangeA;
	ptRectangleHighB = ptRangeB;
	
	/* Set the dimension of the mesh_t if not setted already */
	itMeshDim = iDim;
	/* Initialize number of node_ts as 1 */
	itNumberOfNodes = 1;

	inNodesOnDim = inNodesOnDim_;

	/* Multiply the number of node_ts on each dimension so the total amount of node_ts is calculated
	 * ex: Consider a 2D mesh_t with nx=5, ny=10
	 * 		numberofnode_ts=1; // Then inside the for
	 * 		numberofnode_ts=numberofnode_ts*nx*ny
	 *  The number of node_ts is then 50.
	 *  But the indices are zero based, so everithing runs on nx-1 and ny-1 in the loops below.
	 * Stores dimensions on private variable inNodesOnDim
	 */
	#pragma omp parallel for
	//for(int i(0);i<itMeshDim;i++)
	for(int i =0;i<itMeshDim;i++)
	{
		//inNodesOnDim.push_back(inNodesOnDim_.at(i));
		itNumberOfNodes*=(inNodesOnDim.at(i));
	}	

	
	/* Calculates the required delta on each dimension by using the limits ptRangeA and ptRangeB
	 * when RangeA and RangeB define the points joining a rectangle's diagonal
	 * RangeA always is assume to be the lower while RangeB the higher point as the diagram below
	 *
	 *       ***********RangeB(c,d)
	 *       *                    *
	 *     ^ *                    *
	 *     | *                    *
	 *     y *                    *
	 *       *                    *
	 *       RangeA(a,b)***********
	 *		 x -->
	 *  
	 *  On x the ranges are (c-a)/nx i.e (RangeB(1)-RangeA(1))
	 *  On y the ranges are (d-b)/nx i.e (RangeB(2)-RangeA(2))
	 */
	#pragma omp parallel for
	//for(int i(0);i<itMeshDim;i++)
	for(int i =0;i<itMeshDim;i++)
	{
		ptDeltaOnDim.push_back(fabs(ptRangeB[i]-ptRangeA[i])/(inNodesOnDim[i]-1));
		//std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}
	/* Sepparated for due to the OMP implementation. when running parallel threads the std::cout output some times does have sense
	 * e.g. "hello" -> "Hloel" or similar as a result of parallel execution
	 */
/*	for(int i =0;i<itMeshDim;i++)
	{
		std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}*/

	/* When storing node_ts, the mapping is as follows
	 * 
	 *       ***********RangeB(c,d)
	 *    ny *                    *
	 *   ... *                    *
	 *     3 *                    *
	 *     2 *                    *
	 *     1 *                    *
	 *     0 *                    *
	 *     ^ *                    *
	 *     | *                    *
	 *       *                    *
	 *     j *                    *
	 *       RangeA(a,b)***********
	 *		 i --> 0,1,2,3...,nx
	*/  


	/* Creating the bondary node_ts */

	//Debug("antes del parallel");

	//#pragma omp parallel
{
	int j(0),i(0);
	point_t ndcoord(2);
	ndcoord = ptRangeA;
	
	index_t iIndexNode(2);
	node_t bNode;


	//Debug("Dentro de parallel antes de for 1");
	/* first j=0, and i=0->(nx-1) zero based nx node_ts */
	//#pragma omp parallel for
	#pragma omp for ordered schedule(dynamic)
	for(i = 0;i<inNodesOnDim[0];i++)
	{
	  //ndcoordx=ndcoordx + deltaX
	  //ndcoordy=ndcoordy
	  iIndexNode[0] = i;
	  iIndexNode[1] = j;
	  ndcoord[0] =  ptRangeA[0] + i*ptDeltaOnDim[0];
	  bNode.setNode(ndcoord,iIndexNode,0); 

	  mBoundaryMesh[iIndexNode] = bNode;

	  //Debug("dentro for 1");

	}
	

	//Debug("Antes de for 2");
	i = inNodesOnDim[0]-1;

	////Debug(1);
	
	/* ncoord = (a+N*dx,b) = (c,b) then
	 i=(nx-1) from above, and j=0->(ny-1) */
	//#pragma omp parallel for
	#pragma omp for ordered schedule(dynamic)
	for(j = 1;j<inNodesOnDim[1];j++)
	{
	  //ndcoordx=ndcoordx
	  //ndcoordy=ndcoordy + deltaY
	  index_t iIndexNode(2);
	  iIndexNode[0] = i;
	  iIndexNode[1] = j;
	  ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
	  bNode.setNode(ndcoord,iIndexNode,0); 
 
	  mBoundaryMesh[iIndexNode] = bNode;
	//Debug("Dentro for 2");
	}
	
	//Debug("antes for 3");
	j = inNodesOnDim[1]-1;

	////Debug(2);

	/* ncoord = (a+nx*dx,b+ny*dy) = (c,d) then
	 j=(ny-1) from above, and i=(nx-1)-> 0 */
	//#pragma omp parallel for
	#pragma omp for ordered schedule(dynamic)
	for(i=inNodesOnDim[0]-2;i>=0;i--)
	{
	  //ndcoordx=ndcoordx - deltaX
	  //ndcoordy=ndcoordy
	  index_t iIndexNode(2);
	  iIndexNode[0] = i;
	  iIndexNode[1] = j;
	  ndcoord[0] =  ptRangeA[0] + i*ptDeltaOnDim[0];
	  bNode.setNode(ndcoord,iIndexNode,0); 
		
	  mBoundaryMesh[iIndexNode] = bNode;
//Debug("Dentro de for 3");
	}
//Debug("Antes for 4");
	i = 0;
	ndcoord[1] = ptRangeB[1];
	////Debug(3);

	/* ncoord = (a,b+ny*dy) = (a,d) then
	 i=0 from above, and j=(ny-1)->1 cuz node_t(i=0,j=0) is already defined */
	//#pragma omp parallel for
	#pragma omp for ordered schedule(dynamic)
	for(j = inNodesOnDim[1]-2;j> 0;j--)
	{
	  /* ndcoordx=ndcoordx
	     ndcoordy=ndcoordy - deltaY */
	  index_t iIndexNode(2);
	  iIndexNode[0] = i;
	  iIndexNode[1] = j;
	  ndcoord[1]-= ptDeltaOnDim[1];
	  bNode.setNode(ndcoord,iIndexNode,0); 
	  	
	  mBoundaryMesh[iIndexNode] = bNode;
//Debug("Dentro for 4");
	}

	
	////Debug(4);
	
	/* Finally create the inner node_ts by using nested for
	 * valid OpenMP nested for is as
	 * for
	 * {
	 * 	   for
	 * 	   {
	 * 	  	  code here
	 * 	   }
	 *  dont put code here
	 * }
	 * 		*/

	//Debug("antes nested for");
	if(itNumberOfNodes != vBoundaryMesh.size())
	{
		ndcoord = ptRangeA + ptDeltaOnDim;
		/* ncoord = (a,b+dy) = (a,d) then
		   i=0,j=1 from above */
		for(i = 1;i<inNodesOnDim[0]-1;i++)
		{
			//#pragma omp parallel for
//Debug("dentro for outter");
			#pragma omp for ordered schedule(dynamic)
			for(j = 1;j<inNodesOnDim[1]-1;j++)
			{	
				//index_t iIndexNode(2);
				//iIndexNode[0] = i;
				//iIndexNode[1] = j;
				index_t iIndexNode(2);
				iIndexNode.push_back(i);
				iIndexNode.push_back(j);
				//ndcoord[1]= ptRangeB[1] - j*ptDeltaOnDim[1];
				ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
				bNode.setNode(ndcoord,iIndexNode,0); 
				
				mInnerMesh[iIndexNode] = bNode;
				//Debug("Dentro del for nested");
			}
			
			//Debug("Dentro del for outter despues del nested");
			ndcoord[0]+= ptDeltaOnDim[0];
			ndcoord[1] = ptRangeA[1];
		}
	}

}
	itBoundaryNodes = vBoundaryMesh.size();	
	itInnerNodes = vInnerMesh.size();	
  /*	
	std::cout << "Boundary node_ts:\n";
	
	for(int i(0); i < vBoundaryMesh.size();i++)
	{
	  std::cout << vBoundaryMesh[i] << std::endl;
	}
	
	std::cout << "\n\nInner nodes:\n";


	for(int i(0); i < vInnerMesh.size();i++)
	{
	  std::cout << vInnerMesh[i] << std::endl;
	}
  */
	std::cout << itMeshDim << "-D Mesh Created with " << itNumberOfNodes << " nodes"  << std::endl;

}

/*! This constructor reads a boost::property_tree with all the data that specifies the mesh_t object.*/
mesh_t::mesh_t(boost::property_tree::ptree prTree)
{
	/* Get the values from pTree readed */
    //boost::property_tree::read_json( JSON_PATH, pt );

	//std::cout << pt << std::endl;

	//std::vector<std::string> vValues;

	std::string sPathBuffer;
	std::string sBuffer;

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshName;
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sMeshName = prTree.get(sPathBuffer,"NewMesh");
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshDim;
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sBuffer = prTree.get(sPathBuffer,"2");
	itMeshDim = StringToNumber<int_t>(sBuffer);
	sPathBuffer.clear();
/*	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshNN;
	itNumberOfNodes = StringToNumber<int>(prTree.get(sPathBuffer,"100"));
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshBN;
	itBoundaryNodes = StringToNumber<int>(prTree.get(sPathBuffer,"-1"));
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshIN;
	itInnerNodes = StringToNumber<int>(prTree.get(sPathBuffer,"-1"));
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pFiles;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshXML;
	sMeshXML = prTree.get(sPathBuffer,sMeshName + ".xml");
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pFiles;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshJSON;
	sMeshXML = prTree.get(sPathBuffer,sMeshName + ".json");
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sPathBuffer.clear();

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pFiles;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshFile;
	sMeshFile = prTree.get(sPathBuffer,sMeshName + ".msh");
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	sPathBuffer.clear();

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshND;
	sPathBuffer+=".";
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
*/	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		//vValues.push_back(prTree.get(sPathBuffer + NumberToString(j),"-1"));
		//inNodesOnDim.push_back(StringToNumber<int>(prTree.get(sPathBuffer + NumberToString(j),"-1")));
	}
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshDD;
	sPathBuffer+=".";
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		//vValues.push_back(prTree.get(sPathBuffer + NumberToString(j),"-1"));
		//ptDeltaOnDim.push_back(StringToNumber<double>(prTree.get(sPathBuffer + NumberToString(j),"-1.0")));
	}

	sPathBuffer.clear();
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshPA;
	sPathBuffer+=".";
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		//vValues.push_back(prTree.get(sPathBuffer + NumberToString(j),"-1"));
		//ptRectangleLowA.push_back(StringToNumber<double>(prTree.get(sPathBuffer + NumberToString(j),NumberToString(j))));
	}	
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshPB;
	sPathBuffer+=".";
	//vValues.push_back(prTree.get(sPathBuffer,"-1"));
	//sPathBuffer.clear();
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		//vValues.push_back(prTree.get(sPathBuffer + NumberToString(j),"-1"));
		//ptRectangleHighB.push_back(StringToNumber<double>(prTree.get(sPathBuffer + NumberToString(j),NumberToString(j))));
	}
	sPathBuffer.clear();
	
	//vValues.push_back(prTree.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(prTree.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(prTree.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(prTree.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(prTree.get<std::string>(_pMesh +"."+ _pMeshName));
	
	

	//std::cout << "\n\nVector values: " << std::endl;

	//for(int i(0);i<vValues.size();i++)
	//{
		//std::cout << vValues[i] << std::endl;
	//}
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

// /*! \brief libmesh constructor by pasing the name of a JSON or XML formatted file with information of mesh_t
 /*!
 * Constructor that reads information of a JSON or XML formatted file.
 * The constructor determines the parsing method by the file extension XML or JSON.
 *
// * \param sFileName \c std::string with the name of the file with extension.
 */
mesh_t::mesh_t(std::string sFileName)
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
		*this = mesh_t();
	}
}

/*! This method allows the implementation to retrieve the node_t pointed by the index \c inIndex and to modify it by
 *  the assignation operator, or send it to streams. It accesses the node_t object by reference.
 * */
node_t& mesh_t::operator[](index_t inIndex)
{

	if(mInnerMesh.count(inIndex) > 0)
	{
		return mInnerMesh[inIndex];
	}
	else if(mBoundaryMesh.count(inIndex) > 0)
	{
		return mBoundaryMesh[inIndex];
	}
	else
	{
		//std::cout << "[EE] Index " << inIndex << " out of the range of the mesh_t" << std::endl;
		std::cout << "[EE] Index ";
		std::cout << inIndex;
		std::cout << " out of the range of the mesh" << std::endl;

		//node_t bNode({0,0},{0,0},0);
		return mBoundaryMesh[{0,0}];
	}
}


/*!The mesh_t file created consists of columns representing the points that determine the mesh_t.
 * The name of the file is set by the mesh_t member sMeshFile which is also stored on the property tree.
 * The first node_ts that are stored on the file are the boundary node_ts following are the inner node_ts.
 * The boundary/inner information about the node_ts is determined at the moment of creating the mesh_t and can only
 * be retrieved by looking at the fields mesh.bnodes mesh.inodes on the property tree of the JSON or XML formatted file associated with the mesh_t.
 * Without those specifications is impossible to determine if the node_t is inner or boundary \a a \a priori.
 * */
int_t mesh_t::createMeshFile()
{
	createMeshFile(sMeshFile);
}

/*!The mesh_t file created consists of columns representing the points that determine the mesh_t.
 * The name of the file is set by the argument and the sMeshFile member of mesh_t is ignored.
 * The first node_ts that are stored on the file are the boundary node_ts following are the inner node_ts.
 * The boundary/inner information about the node_ts is determined at the moment of creating the mesh_t and can only
 * be retrieved by looking at the fields mesh.bnodes mesh.inodes on the property tree of the JSON or XML formatted file associated with the mesh_t.
 * Without those specifications is impossible to determine if the node_t is inner or boundary \a a \a priori.
 * */
int_t mesh_t::createMeshFile(std::string sFileName)
{
	std::ofstream sFileStream;

	sFileStream.open(sFileName.c_str());

	if(sFileStream.is_open())
	{
		//sMeshFile = sFileName;

		/* Creates an XML file with all the relevant data of the mesh_t.
		 * The XML file is parsed thanks to libboost property tree
		 */
	
		//createMeshXML(sFileName+".xml");
		//createMeshXML(sMeshXML);
		std::cout << "Boundary mesh size " << vBoundaryMesh.size() << std::endl;
		std::cout << "Inner mesh size " << vInnerMesh.size() << std::endl;
		
		for(int i(0); i < vBoundaryMesh.size();i++)
		{
			//std::cout << vBoundaryMesh[i] << std::endl;
		 	point_t ptBuffer(vBoundaryMesh[i].getCoordinates());
			double dBuffer(vBoundaryMesh[i].getValue());
			
			for(int j(0);j<ptBuffer.size();j++)
			{
				sFileStream << ptBuffer[j] << "\t";
			}

			//sFileStream << "\t" << dBuffer << std::endl;
			sFileStream << std::endl;
		}

		for(int i(0); i < vInnerMesh.size();i++)
		{
		  	point_t ptBuffer(vInnerMesh[i].getCoordinates());
			double dBuffer(vInnerMesh[i].getValue());
			

			for(int j(0);j<ptBuffer.size();j++)
			{
				sFileStream << ptBuffer[j] << "\t";
			}

			//sFileStream << "\t" << dBuffer << std::endl;
			sFileStream << std::endl;
		}

		sFileStream.close();

		std::cout <<  "Mesh file " << sFileName << " created" << std::endl;

		return 0;
	}
	else
	{
		std::cout <<  "Mesh file " << sFileName << "could not be created" << std::endl;
		return 1;
	}

}

/*! In order to create the PNG file mesh_t calls the MathGL library. The Generated has a size of 1200x900 pixels and 
 *	shows all the node_ts on the range of the mesh_t. The Name of the PNG is given by the mesh_t member sMeshName so the 
 *	file will be \c sMeshName_mgl.png.
 * */
int_t mesh_t::createMeshPNG()
{
	
	if(std::ifstream(sMeshFile).good() == false)
	{
		std::cout << "Creating mesh file prior plotting" << std::endl;

		createMeshFile();
		
		std::cout << "Plotting Mesh..." << std::endl;

		//mglDrawData(sMeshFile,ptRectangleLowA,ptRectangleHighB);
		mglDrawData(sMeshName,ptRectangleLowA,ptRectangleHighB);

		std::cout << "Mesh file " << sMeshFile << "_mgl.png created" << std::endl;

	}
	else
	{
		std::cout << "Plotting Mesh..." << std::endl;

		//mglDrawData(sMeshFile,ptRectangleLowA,ptRectangleHighB);
		mglDrawData(sMeshName,ptRectangleLowA,ptRectangleHighB);

		std::cout << "Mesh file " << sMeshFile << "_mgl.png created" << std::endl;

	}
	
	return 0;
}

/* The statements beggingin with "_p" are #define on typedef.hpp and used as parsing statements */

// /*!\brief Creates JSON parsed file with the information about the mesh_t object
/*!
 * Creates JSON parsed file with the information about the mesh_t object.
 * This method creates or overwrites the property tree prior parsing to a JSON file
 * using the standard name of the JSON file for the mesh_t object
 */
void mesh_t::createMeshJSON()
{
	createPropertyTree();
	boost::property_tree::write_json(sMeshJSON,prTreeMesh);
	//createMeshJSON(sMeshName + "." + _pMeshJSON);
}

// /*!\brief Creates JSON parsed file with the information about the mesh_t object
/*!
 * Creates JSON parsed file with the information about the mesh_t object.
 * This method (re)creates the property tree prior parsing to a JSON file whose name is
 * passed as an argument.
 */
void mesh_t::createMeshJSON(std::string sFileName)
{
	//sMeshJSON = sFileName;

	createPropertyTree();
	std::string sPath(_pMesh);
	sPath+= ".file.";
	sPath+= _pMeshJSON;
	prTreeMesh.put(sPath,sFileName);

	boost::property_tree::write_json(sFileName,prTreeMesh);
}

// /*!\brief Creates XML parsed file with the information about the mesh_t object
/*!
 * Creates XML parsed file with the information about the mesh_t object.
 * This method (re)creates the property tree prior parsing to a XML file
 * using the standard name of the XML file for the mesh_t object
 * 
 */
void mesh_t::createMeshXML()
{
	createPropertyTree();
	boost::property_tree::write_xml(sMeshXML,prTreeMesh);
}

// *!\brief Creates XML parsed file with the information about the mesh_t object
/*!
 * Creates XML parsed file with the information about the mesh_t object.
 * This method (re)creates the property tree prior parsing to a XML file whose name is
 * passed as an argument.
 */
void mesh_t::createMeshXML(std::string sFileName)
{
	createPropertyTree();
	std::string sPath(_pMesh);
	sPath+= ".file.";
	sPath+= _pMeshXML;
	prTreeMesh.put(sPath,sFileName);
	
	boost::property_tree::write_xml(sFileName,prTreeMesh);
}

// /*! \brief creates the libboost property tree of the mesh_t in memory prior parsing
/*!
 * The property tree is a container that can be used to parse
 * info,JSON or XML specifications of mesh_t objects.
 * This method creates a libboost property tree of the mesh_t object in memory prior parsing
 * to a info, JSON or XML.
 */
void mesh_t::createPropertyTree()
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

void mesh_t::push_backIN(node_t cNode)
{
	vBoundaryMesh.push_back(cNode);
    itNumberOfNodes++;

	std::cout << "Inner Node inserted on mesh. " << itNumberOfNodes << " nodes stored on mesh" << std::endl;
}

void mesh_t::push_backBN(node_t cNode)
{
	vInnerMesh.push_back(cNode);
    itNumberOfNodes++;

	itNumberOfNodes = 0;
	std::cout << "Boundary Node inserted on mesh. " << itNumberOfNodes << " nodes stored on mesh" << std::endl;
}

// *!\brief Sets the name for the mesh_t.
/*!
 * Sets the _std::string_ name for the mesh_t. This name is used to
 * determine the msh mesh_t file and the xml file associated with the mess.
 */
void mesh_t::setMeshName(std::string sMeshName_)
{
	sMeshName = sMeshName_;
	sMeshFile = sMeshName + ".msh";
	sMeshJSON = sMeshName + ".json";
	sMeshXML = sMeshName + ".xml";
}

// *!\brief ostream operator for the mesh_t.
/*!
 * Overloads the ostream operator for mesh_t objects, so the information
 * of the mesh_t can displayed by standard output (std::cout) or sent to streams.
 */
std::ostream& operator<<(std::ostream& outStream, mesh_t& cMesh)
{
	std::cout << "Mesh XML file: " << cMesh.sMeshXML <<  std::endl;
	std::cout << "Mesh file: " << cMesh.sMeshFile << std::endl;
	std::cout << "Mesh Dimensions: " << cMesh.itMeshDim << std::endl;
	std::cout << "Number of nodes: " << cMesh.itNumberOfNodes << std::endl;
	std::cout << "Number of boundary nodes: " << cMesh.itBoundaryNodes << std::endl;
	std::cout << "Number of inner nodes: " << cMesh.itInnerNodes << std::endl;
	std::cout << "Number of nodes on each dimension: " << cMesh.inNodesOnDim << std::endl;
	std::cout << "Delta on each dimension: " << cMesh.ptDeltaOnDim << std::endl;
	std::cout << "Low point: " << cMesh.ptRectangleLowA <<  std::endl;
	std::cout << "High point: " <<  cMesh.ptRectangleHighB << std::endl;

}

// /*!\brief Get libboost property tree of the mesh_t.
/*! 
 * The property tree is a container that can be used to parse
 * INFO,JSON or XML specifications of mesh_t objects.
 * This method returns the associated property tree of the mesh_t object.
 * The property tree is recreated on each run of this method by calling
 * the method mesh_t::createPropertyTree()
 */
boost::property_tree::ptree mesh_t::getPropertyTree()
{
	createPropertyTree();
	return prTreeMesh;
}


/*! 
 * Iterate through the mesh_t.
 */
mesh_t interate(mesh_t& mMesh)
{	
}
