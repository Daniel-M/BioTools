//#ifndef OMP_H
	//#include "omp.h"
	//#define OMP_H
//#endif

//#define Debug(N) std::cout << "\n * Debug " << N << std::endl

#include "headers.hpp"
//#include "mesh.hpp"

mesh::mesh() : mesh(2,{10,10},{0,0}, {5,5})

{
	//itMeshDim = 2;

	////sMeshFile = "NewMesh.msh";
	////sMeshXML = "NewMesh.xml";
	
	//setMeshName("NewMesh");
	
	//inNodesOnDim.push_back(0);
	//inNodesOnDim.push_back(0);

	//ptRectangleLowA = {0,5};
	//ptRectangleHighB = {0,5};

	//itNumberOfNodes = 0;
	
	//for(int i(0);i<itMeshDim;i++)
	//{
		//ptDeltaOnDim.push_back(0);
	//}
		
	std::cout << itMeshDim << "-D Empy Mesh Created" << std::endl;
}

void mesh::setMeshName(std::string sMeshName_)
{
	sMeshName = sMeshName_;
	sMeshFile = sMeshName + ".msh";
	sMeshXML = sMeshName + ".xml";
}

mesh::mesh(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB,std::string sMeshName)
{
	//mesh(iDim,inNodesOnDim_,ptRangeA, ptRangeB);
	setMeshName(sMeshName);
	//sMeshFile = "NewMesh.msh";
	//sMeshXML = "NewMesh.xml";
	//setMeshName("NewMesh");

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
	for(int i =0;i<itMeshDim;i++)
	{
		std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}
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
	//mesh(iDim,inNodesOnDim_,ptRangeA, ptRangeB,"NewMesh");
	
	////sMeshFile = "NewMesh.msh";
	////sMeshXML = "NewMesh.xml";
	//setMeshName("NewMesh");

	//ptRectangleLowA = ptRangeA;
	//ptRectangleHighB = ptRangeB;
	
	///* Set the dimension of the mesh if not setted already */
	//itMeshDim = iDim;
	///* Initialize number of nodes as 1 */
	//itNumberOfNodes = 1;

	//inNodesOnDim = inNodesOnDim_;

	///* Multiply the number of nodes on each dimension so the total amount of nodes is calculated
	 //* ex: Consider a 2D mesh with nx=5, ny=10
	 //* 		numberofnodes=1; // Then inside the for
	 //* 		numberofnodes=numberofnodes*nx*ny
	 //*  The number of nodes is then 50.
	 //*  But the indices are zero based, so everithing runs on nx-1 and ny-1 in the loops below.
	 //* Stores dimensions on private variable inNodesOnDim
	 //*/
	//#pragma omp parallel for
	////for(int i(0);i<itMeshDim;i++)
	//for(int i =0;i<itMeshDim;i++)
	//{
		////inNodesOnDim.push_back(inNodesOnDim_.at(i));
		//itNumberOfNodes*=(inNodesOnDim.at(i));
	//}	

	
	///* Calculates the required delta on each dimension by using the limits ptRangeA and ptRangeB
	 //* when RangeA and RangeB define the points joining a rectangle's diagonal
	 //* RangeA always is assume to be the lower while RangeB the higher point as the diagram below
	 //*
	 //*       ***********RangeB(c,d)
	 //*       *                    *
	 //*     ^ *                    *
	 //*     | *                    *
	 //*     y *                    *
	 //*       *                    *
	 //*       RangeA(a,b)***********
	 //*		 x -->
	 //*  
	 //*  On x the ranges are (c-a)/nx i.e (RangeB(1)-RangeA(1))
	 //*  On y the ranges are (d-b)/nx i.e (RangeB(2)-RangeA(2))
	 //*/
	//#pragma omp parallel for
	////for(int i(0);i<itMeshDim;i++)
	//for(int i =0;i<itMeshDim;i++)
	//{
		//ptDeltaOnDim.push_back(fabs(ptRangeB[i]-ptRangeA[i])/(inNodesOnDim[i]-1));
		////std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	//}
	///* Sepparated for due to the OMP implementation. when running parallel threads the std::cout output some times does have sense
	 //* e.g. "hello" -> "Hloel" or similar as a result of parallel execution
	 //*/
	//for(int i =0;i<itMeshDim;i++)
	//{
		//std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	//}
	///* When storing nodes, the mapping is as follows
	 //* 
	 //*       ***********RangeB(c,d)
	 //*    ny *                    *
	 //*   ... *                    *
	 //*     3 *                    *
	 //*     2 *                    *
	 //*     1 *                    *
	 //*     0 *                    *
	 //*     ^ *                    *
	 //*     | *                    *
	 //*       *                    *
	 //*     j *                    *
	 //*       RangeA(a,b)***********
	 //*		 i --> 0,1,2,3...,nx
	//*/  


	///* Creating the bondary nodes */

	////Debug("antes del parallel");

	////#pragma omp parallel
//{
	//int j(0),i(0);
	//point_t ndcoord(2);
	//ndcoord = ptRangeA;
	
	//index_t iIndexNode(2);
	//node bNode;


	////Debug("Dentro de parallel antes de for 1");
	///* first j=0, and i=0->(nx-1) zero based nx nodes */
	////#pragma omp parallel for
	//#pragma omp for ordered schedule(dynamic)
	//for(i = 0;i<inNodesOnDim[0];i++)
	//{
	  ////ndcoordx=ndcoordx + deltaX
	  ////ndcoordy=ndcoordy
	  //iIndexNode[0] = i;
	  //iIndexNode[1] = j;
	  //ndcoord[0] =  ptRangeA[0] + i*ptDeltaOnDim[0];
	  //bNode.setNode(ndcoord,iIndexNode,0); 

	  //vBoundaryMesh.push_back(bNode);

	  ////Debug("dentro for 1");

	//}
	

	////Debug("Antes de for 2");
	//i = inNodesOnDim[0]-1;

	//////Debug(1);
	
	///* ncoord = (a+N*dx,b) = (c,b) then
	 //i=(nx-1) from above, and j=0->(ny-1) */
	////#pragma omp parallel for
	//#pragma omp for ordered schedule(dynamic)
	//for(j = 1;j<inNodesOnDim[1];j++)
	//{
	  ////ndcoordx=ndcoordx
	  ////ndcoordy=ndcoordy + deltaY
	  //index_t iIndexNode(2);
	  //iIndexNode[0] = i;
	  //iIndexNode[1] = j;
	  //ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
	  //bNode.setNode(ndcoord,iIndexNode,0); 
 
	  //vBoundaryMesh.push_back(bNode);
	////Debug("Dentro for 2");
	//}
	
	////Debug("antes for 3");
	//j = inNodesOnDim[1]-1;

	//////Debug(2);

	///* ncoord = (a+nx*dx,b+ny*dy) = (c,d) then
	 //j=(ny-1) from above, and i=(nx-1)-> 0 */
	////#pragma omp parallel for
	//#pragma omp for ordered schedule(dynamic)
	//for(i=inNodesOnDim[0]-2;i>=0;i--)
	//{
	  ////ndcoordx=ndcoordx - deltaX
	  ////ndcoordy=ndcoordy
	  //index_t iIndexNode(2);
	  //iIndexNode[0] = i;
	  //iIndexNode[1] = j;
	  //ndcoord[0] =  ptRangeA[0] + i*ptDeltaOnDim[0];
	  //bNode.setNode(ndcoord,iIndexNode,0); 
		
	  //vBoundaryMesh.push_back(bNode);
////Debug("Dentro de for 3");
	//}
////Debug("Antes for 4");
	//i = 0;
	//ndcoord[1] = ptRangeB[1];
	//////Debug(3);

	///* ncoord = (a,b+ny*dy) = (a,d) then
	 //i=0 from above, and j=(ny-1)->1 cuz node(i=0,j=0) is already defined */
	////#pragma omp parallel for
	//#pragma omp for ordered schedule(dynamic)
	//for(j = inNodesOnDim[1]-2;j> 0;j--)
	//{
	  ///* ndcoordx=ndcoordx
	     //ndcoordy=ndcoordy - deltaY */
	  //index_t iIndexNode(2);
	  //iIndexNode[0] = i;
	  //iIndexNode[1] = j;
	  //ndcoord[1]-= ptDeltaOnDim[1];
	  //bNode.setNode(ndcoord,iIndexNode,0); 
	  	
	  //vBoundaryMesh.push_back(bNode);
////Debug("Dentro for 4");
	//}

	
	//////Debug(4);
	
	///* Finally create the inner nodes by using nested for
	 //* valid OpenMP nested for is as
	 //* for
	 //* {
	 //* 	   for
	 //* 	   {
	 //* 	  	  code here
	 //* 	   }
	 //*  dont put code here
	 //* }
	 //* 		*/

	////Debug("antes nested for");
	//if(itNumberOfNodes != vBoundaryMesh.size())
	//{
		//ndcoord = ptRangeA + ptDeltaOnDim;
		///* ncoord = (a,b+dy) = (a,d) then
		   //i=0,j=1 from above */
		//for(i = 1;i<inNodesOnDim[0]-1;i++)
		//{
			////#pragma omp parallel for
////Debug("dentro for outter");
			//#pragma omp for ordered schedule(dynamic)
			//for(j = 1;j<inNodesOnDim[1]-1;j++)
			//{	
				////index_t iIndexNode(2);
				////iIndexNode[0] = i;
				////iIndexNode[1] = j;
				//index_t iIndexNode(2);
				//iIndexNode.push_back(i);
				//iIndexNode.push_back(j);
				////ndcoord[1]= ptRangeB[1] - j*ptDeltaOnDim[1];
				//ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
				//bNode.setNode(ndcoord,iIndexNode,0); 
				
				//vInnerMesh.push_back(bNode);
				////Debug("Dentro del for nested");
			//}
			
			////Debug("Dentro del for outter despues del nested");
			//ndcoord[0]+= ptDeltaOnDim[0];
			//ndcoord[1] = ptRangeA[1];
		//}
	//}

//}
	//itBoundaryNodes = vBoundaryMesh.size();	
	//itInnerNodes = vInnerMesh.size();	
  ///*	
	//std::cout << "Boundary nodes:\n";
	
	//for(int i(0); i < vBoundaryMesh.size();i++)
	//{
	  //std::cout << vBoundaryMesh[i] << std::endl;
	//}
	
	//std::cout << "\n\nInner nodes:\n";


	//for(int i(0); i < vInnerMesh.size();i++)
	//{
	  //std::cout << vInnerMesh[i] << std::endl;
	//}
  //*/
	//std::cout << itMeshDim << "-D Mesh Created with " << itNumberOfNodes << " nodes"  << std::endl;

}

mesh::mesh(std::string sFileName)
{
	//try{
	read_xml(sFileName,prtrXML);

	itMeshDim = prtrXML.get("mesh.dimension",0);
	itNumberOfNodes = prtrXML.get("mesh.nnodes",0);
	itBoundaryNodes = prtrXML.get("mesh.bnodes",0);
	itInnerNodes = prtrXML.get("mesh.inodes",0);
	
	boost::property_tree::ptree	prtrDims = prtrXML.get_child("mesh.nodesdimensions");
	for(const auto& tree : prtrDims)
	{
		//inNodesOnDim.push_back(tree.second.get("",0));
		inNodesOnDim.push_back(tree.second.get<int_t>(""));
	}

	boost::property_tree::ptree	prtrDeltas = prtrXML.get_child("mesh.deltaondim");
	for(const auto& tree: prtrDeltas)
	{
	  ptDeltaOnDim.push_back(tree.second.get<double>(""));
	}
	
	boost::property_tree::ptree	prtrRangeA = prtrXML.get_child("mesh.pointa");
	for(const auto& tree: prtrRangeA)
	{
		ptRectangleLowA.push_back(tree.second.get<double>(""));
	}
	
	boost::property_tree::ptree	prtrRangeB = prtrXML.get_child("mesh.pointb");
	for(const auto& tree: prtrRangeB)
	{
		ptRectangleHighB.push_back(tree.second.get<double>(""));
	}	
	sMeshFile = prtrXML.get<std::string>("mesh.meshfile");
	sMeshXML = prtrXML.get<std::string>("mesh.meshxml");

	std::cout << "Mesh on xml file : " << sFileName << " successfully read" <<  std::endl;
	std::cout << "Mesh file " << sMeshFile << std::endl;
	std::cout << "Mesh Dimension " << itMeshDim << std::endl;
	std::cout << "Number of nodes " << itNumberOfNodes << std::endl;
	std::cout << "Number of boundary nodes " << itBoundaryNodes << std::endl;
	std::cout << "Number of inner nodes " << itInnerNodes << std::endl;

	//for(int i(0);i< inNodesOnDim.size();i++)
	//{
		//std::cout << "Number of nodes on dim " << i << " is " << inNodesOnDim[i] << std::endl;
		std::cout << "Number of nodes on dim " << inNodesOnDim << std::endl;
		//}


	//for(int i(0);i< ptDeltaOnDim.size();i++)
	//{
	//std::cout << "Delta on dim " << i << " is " << ptDeltaOnDim[i] << std::endl;
	std::cout << "Delta on dims " << ptDeltaOnDim << std::endl;
	  //}
	  
	std::cout << "Low point " << ptRectangleLowA <<  std::endl;

	std::cout << "High point " <<  ptRectangleHighB << std::endl;
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
		sMeshFile = sFileName;

		/* Creates an XML file with all the relevant data of the mesh.
		 * The XML file is parsed thanks to libboost property tree
		 */
	
		//createMeshXML(sFileName+".xml");
		createMeshXML(sMeshXML);
		
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
		return 1;
	}

}

int_t mesh::createMeshXML()
{
	createMeshXML(sMeshXML);
}


int_t mesh::createMeshXML(std::string sFileName)
{
	sMeshXML = sFileName;
	prtrXML.put("mesh.meshxml",sMeshXML);
	prtrXML.put("mesh.meshfile",sMeshFile);
	prtrXML.put("mesh.dimension",itMeshDim);
	prtrXML.put("mesh.nnodes",itNumberOfNodes);
	prtrXML.put("mesh.bnodes",itBoundaryNodes);
	prtrXML.put("mesh.inodes",itInnerNodes);


	for(int i(0); i < inNodesOnDim.size();i++)
	{
		prtrXML.put("mesh.nodesdimensions."+NumberToString(i),inNodesOnDim[i]);
	}

	for(int i(0); i < ptDeltaOnDim.size();i++)
	{
		prtrXML.put("mesh.deltaondim."+NumberToString(i),ptDeltaOnDim[i]);
	}

	for(int i(0); i < ptRectangleLowA.size();i++)
	{
		prtrXML.put("mesh.pointa."+NumberToString(i),ptRectangleLowA[i]);
	}
	
	for(int i(0); i < ptRectangleHighB.size();i++)
	{
		prtrXML.put("mesh.pointb."+NumberToString(i),ptRectangleHighB[i]);
	}
	
	write_xml(sFileName,prtrXML);
}

int_t mesh::createMeshPNG()
{
	
	//if(sMeshFile == "NewMesh.msh")
	//if(fexist0(sMeshFile) == false)
	if(std::ifstream(sMeshFile).good() == false)
	{
		std::cout << "Creating mesh file prior plotting" << std::endl;

		//sMeshFile = "Mesh.msh";
		
		//createMeshFile(sMeshFile);
		createMeshFile();
		
		std::cout << "Plotting Mesh..." << std::endl;

		//mglDrawData(sMeshFile,ptRectangleLowA,ptRectangleHighB);
		mglDrawData(sMeshName,ptRectangleLowA,ptRectangleHighB);

		std::cout << "Mesh file " << sMeshFile << "-mgl.png created" << std::endl;

	}
	else
	{
		std::cout << "Plotting Mesh..." << std::endl;

		//mglDrawData(sMeshFile,ptRectangleLowA,ptRectangleHighB);
		mglDrawData(sMeshName,ptRectangleLowA,ptRectangleHighB);

		std::cout << "Mesh file " << sMeshFile << "-mgl.png created" << std::endl;

	}
	
	return 0;
}
