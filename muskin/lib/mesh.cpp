#include "headers.hpp"
//#define Debug(N) std::cout << "\n * Debug " << N << std::endl
//#include "mesh.hpp"

mesh::mesh() : mesh(2,{10,10},{0,0}, {1,1})
{
	std::cout << "Standard mesh created:" << std::endl;
	std::cout << *this << std::endl;
}



mesh::mesh(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB,std::string sMeshName)
{
	setMeshName(sMeshName);
	
	ptRectangleLowA = ptRangeA;
	ptRectangleHighB = ptRangeB;
	
	/* Set the dimension of the mesh if not setted already */
	itMeshDim = iDim;
	/* Initialize number of nodes as 1 */
	itNumberOfNodes = 1;

	inNodesOnDim = inNodesOnDim_;

	/* Multiply the number of nodes on each dimension so the total amount of nodes is calculated
	 * ex: Consider a 2D mesh with nx=5, ny=10
	 * 		numberofnodes=1; // Then inside the for
	 * 		numberofnodes=numberofnodes*nx*ny
	 *  The number of nodes is then 50.
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

	/* When storing nodes, the mapping is as follows
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


	/* Creating the bondary nodes */

	//Debug("antes del parallel");

	//#pragma omp parallel
{
	int j(0),i(0);
	point_t ndcoord(2);
	ndcoord = ptRangeA;
	
	index_t iIndexNode(2);
	node bNode;


	//Debug("Dentro de parallel antes de for 1");
	/* first j=0, and i=0->(nx-1) zero based nx nodes */
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

	  vBoundaryMesh.push_back(bNode);

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
 
	  vBoundaryMesh.push_back(bNode);
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
		
	  vBoundaryMesh.push_back(bNode);
//Debug("Dentro de for 3");
	}
//Debug("Antes for 4");
	i = 0;
	ndcoord[1] = ptRangeB[1];
	////Debug(3);

	/* ncoord = (a,b+ny*dy) = (a,d) then
	 i=0 from above, and j=(ny-1)->1 cuz node(i=0,j=0) is already defined */
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
	  	
	  vBoundaryMesh.push_back(bNode);
//Debug("Dentro for 4");
	}

	
	////Debug(4);
	
	/* Finally create the inner nodes by using nested for
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
				
				vInnerMesh.push_back(bNode);
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
	std::cout << "Boundary nodes:\n";
	
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

mesh::mesh(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB) : mesh(iDim,inNodesOnDim_,ptRangeA, ptRangeB,"NewMesh")
{

}


mesh::mesh(boost::property_tree::ptree prTree)
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




void mesh::push_backIN(node cNode)
{
	vBoundaryMesh.push_back(cNode);
    itNumberOfNodes++;

	std::cout << "Inner Node inserted on mesh. " << itNumberOfNodes << " nodes stored on mesh" << std::endl;
}

void mesh::push_backBN(node cNode)
{
	vInnerMesh.push_back(cNode);
    itNumberOfNodes++;

	itNumberOfNodes = 0;
	std::cout << "Boundary Node inserted on mesh. " << itNumberOfNodes << " nodes stored on mesh" << std::endl;
}

int_t mesh::createMeshFile()
{
	createMeshFile(sMeshFile);
}

int_t mesh::createMeshFile(std::string sFileName)
{
	std::ofstream sFileStream;

	sFileStream.open(sFileName.c_str());

	if(sFileStream.is_open())
	{
		//sMeshFile = sFileName;

		/* Creates an XML file with all the relevant data of the mesh.
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

//int_t mesh::createMeshXML()
//{
	//createMeshXML(sMeshXML);
//}


//int_t mesh::createMeshXML(std::string sFileName)
//{
	//sMeshXML = sFileName;
	//prTree.put("mesh.meshxml",sMeshXML);
	//prTree.put("mesh.meshfile",sMeshFile);
	//prTree.put("mesh.dimension",itMeshDim);
	//prTree.put("mesh.nnodes",itNumberOfNodes);
	//prTree.put("mesh.bnodes",itBoundaryNodes);
	//prTree.put("mesh.inodes",itInnerNodes);


	//for(int i(0); i < inNodesOnDim.size();i++)
	//{
		//prTree.put("mesh.nodesdimensions."+NumberToString(i),inNodesOnDim[i]);
	//}

	//for(int i(0); i < ptDeltaOnDim.size();i++)
	//{
		//prTree.put("mesh.deltaondim."+NumberToString(i),ptDeltaOnDim[i]);
	//}

	//for(int i(0); i < ptRectangleLowA.size();i++)
	//{
		//prTree.put("mesh.pointa."+NumberToString(i),ptRectangleLowA[i]);
	//}
	
	//for(int i(0); i < ptRectangleHighB.size();i++)
	//{
		//prTree.put("mesh.pointb."+NumberToString(i),ptRectangleHighB[i]);
	//}
	
	//write_xml(sFileName,prTree);
//}

int_t mesh::createMeshPNG()
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

/*!\brief Sets the name for the mesh.
 *
 * Sets the _std::string_ name for the mesh. This name is used to
 * determine the msh mesh file and the xml file associated with the mess.
 *
 * \param sMeshName_ Name of the mesh
 */
void mesh::setMeshName(std::string sMeshName_)
{
	sMeshName = sMeshName_;
	sMeshFile = sMeshName + ".msh";
	sMeshJSON = sMeshName + ".json";
	sMeshXML = sMeshName + ".xml";
}

/*!\brief ostream operator for the mesh.
 *
 * Overloads the ostream operator for mesh objects, so the information
 * of the mesh is displayed by standard output (std::cout).
 */
std::ostream& operator<<(std::ostream& outStream, mesh& cMesh)
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

node mesh::operator[](const index_t inIndex)
{
	

	return;
}
