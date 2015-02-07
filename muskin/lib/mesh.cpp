#ifndef OMP_H
	#include "omp.h"
	#define OMP_H
#endif

//#define //Debug(N) std::cout << "\n//Debug " << N << std::endl

#include "headers.hpp"
//#include "mesh.hpp"

mesh::mesh()
{
	itMeshDim=2;
	
	itNodesOnDim.push_back(0);
	itNodesOnDim.push_back(0);
	
	itNumberOfNodes = 0;
	
	for(int i(0);i<itMeshDim;i++)
	{
		ptDeltaOnDim.push_back(0);
	}

	std::cout << itMeshDim << "-D Empy Mesh Created" << std::endl;
}

mesh::mesh(int_t iDim,index_t itNodesOnDim_,point_t ptRangeA, point_t ptRangeB)
{
	/* Set the dimension of the mesh if not setted already */
	itMeshDim=iDim;
	/* Initialize number of nodes as 1 */
	itNumberOfNodes = 1;

	/* Multiply the number of nodes on each dimension so the total amount of nodes is calculated
	 * ex: Consider a 2D mesh with nx=5, ny=10
	 * 		numberofnodes=1; // Then inside the for
	 * 		numberofnodes=numberofnodes*nx*ny
	 *  The number of nodes is then 50.
	 *  But the indices are zero based, so everithing runs on nx-1 and ny-1 in the loops below.
	 * Stores dimensions on private variable itNodesOnDim
	 */
	for(int i(0);i<itMeshDim;i++)
	{
		itNodesOnDim.push_back(itNodesOnDim_.at(i));
		itNumberOfNodes*=(itNodesOnDim.at(i));
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
	for(int i(0);i<itMeshDim;i++)
	{
		ptDeltaOnDim.push_back(fabs(ptRangeB[i]-ptRangeA[i])/(itNodesOnDim[i]-1));
		std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << itNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
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
	
	int j(0),i(0);
	point_t ndcoord(2);
	ndcoord = ptRangeA;
	
	index_t iIndexNode(2);
	node bNode;


	/* first j=0, and i=0->(nx-1) zero based nx nodes */
	#pragma omp parallel for
	for(i=0;i<itNodesOnDim[0];i++)
	{
	  //ndcoordx=ndcoordx + deltaX
	  //ndcoordy=ndcoordy
	  iIndexNode[0]=i;
	  iIndexNode[1]=j;
	  ndcoord[0]= ptRangeA[0] + i*ptDeltaOnDim[0];
	  bNode.setNode(ndcoord,iIndexNode,0); 

	  vBoundaryMesh.push_back(bNode);

	}
	

	i=itNodesOnDim[0]-1;

	//Debug(1);
	
	/* ncoord = (a+N*dx,b) = (c,b) then
	 i=(nx-1) from above, and j=0->(ny-1) */
	#pragma omp parallel for
	for(j=1;j<itNodesOnDim[1];j++)
	{
	  //ndcoordx=ndcoordx
	  //ndcoordy=ndcoordy + deltaY
	  index_t iIndexNode(2);
	  iIndexNode[0]=i;
	  iIndexNode[1]=j;
	  ndcoord[1]= ptRangeA[1] + j*ptDeltaOnDim[1];
	  bNode.setNode(ndcoord,iIndexNode,0); 
 
	  vBoundaryMesh.push_back(bNode);

	}
	
	j=itNodesOnDim[1]-1;

	//Debug(2);

	/* ncoord = (a+nx*dx,b+ny*dy) = (c,d) then
	 j=(ny-1) from above, and i=(nx-1)->0 */
	#pragma omp parallel for
	for(i=itNodesOnDim[0]-2;i>=0;i--)
	{
	  //ndcoordx=ndcoordx - deltaX
	  //ndcoordy=ndcoordy
	  index_t iIndexNode(2);
	  iIndexNode[0]=i;
	  iIndexNode[1]=j;
	  ndcoord[0]= ptRangeA[0] + i*ptDeltaOnDim[0];
	  bNode.setNode(ndcoord,iIndexNode,0); 
		
	  vBoundaryMesh.push_back(bNode);

	}

	i=0;
	ndcoord[1]= ptRangeB[1];
	//Debug(3);

	/* ncoord = (a,b+ny*dy) = (a,d) then
	 i=0 from above, and j=(ny-1)->1 cuz node(i=0,j=0) is already defined */
	#pragma omp parallel for
	for(j=itNodesOnDim[1]-2;j>0;j--)
	{
	  /* ndcoordx=ndcoordx
	     ndcoordy=ndcoordy - deltaY */
	  index_t iIndexNode(2);
	  iIndexNode[0]=i;
	  iIndexNode[1]=j;
	  ndcoord[1]-=ptDeltaOnDim[1];
	  bNode.setNode(ndcoord,iIndexNode,0); 
	  	
	  vBoundaryMesh.push_back(bNode);

	}

	
	//Debug(4);
	
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
	if(itNumberOfNodes != vBoundaryMesh.size())
	{
		ndcoord = ptRangeA + ptDeltaOnDim;

		/* ncoord = (a,b+dy) = (a,d) then
		   i=0,j=1 from above */
		for(i=1;i<itNodesOnDim[0]-1;i++)
		{
			#pragma omp parallel for
			for(j=1;j<itNodesOnDim[1]-1;j++)
			{	
				index_t iIndexNode(2);
				iIndexNode[0]=i;
				iIndexNode[1]=j;
				//ndcoord[1]= ptRangeB[1] - j*ptDeltaOnDim[1];
				ndcoord[1]= ptRangeA[1] + j*ptDeltaOnDim[1];
				bNode.setNode(ndcoord,iIndexNode,0); 
				
				vInnerMesh.push_back(bNode);
			}
			
			ndcoord[0]+=ptDeltaOnDim[0];
			ndcoord[1]=ptRangeA[1];
		}
	}



	
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


int_t mesh::createMeshFile(std::string sFileName)
{
	std::ofstream sFileStream;

	sFileStream.open(sFileName.c_str());

	if(sFileStream.is_open())
	{
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

