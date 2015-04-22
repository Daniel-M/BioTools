#include "headers.hpp"
//#include "iterateFD.hpp"
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

/*! This standard constructor initializes the mesh_t object by copying all the relevant properties of \c mRHSMesh. 
 * */
mesh_t::mesh_t(const mesh_t& mRHSMesh)
{
	itMeshDim = mRHSMesh.itMeshDim;
	itNumberOfNodes = mRHSMesh.itNumberOfNodes;
	itBoundaryNodes = mRHSMesh.itBoundaryNodes;
	itInnerNodes = mRHSMesh.itInnerNodes;

	if(siMeshNumber >= 1)
	{
		siMeshNumber += 1;
	}
	else
	{
		siMeshNumber = 1;
	}
	
	sMeshName = mRHSMesh.sMeshName; 
	sMeshJSON = mRHSMesh.sMeshJSON;
	sMeshXML  = mRHSMesh.sMeshXML;
	sMeshFile = mRHSMesh.sMeshFile;
	                         
	inNodesOnDim = mRHSMesh.inNodesOnDim;
                             
	ptDeltaOnDim = mRHSMesh.ptDeltaOnDim;
	ptRectangleLowA = mRHSMesh.ptRectangleLowA;
	ptRectangleHighB = mRHSMesh.ptRectangleHighB;
	                         
	mBoundaryMesh = mRHSMesh.mBoundaryMesh;
	mInnerMesh = mRHSMesh.mInnerMesh;
                             
	vMeshVoxels = mRHSMesh.vMeshVoxels; 

	prTreeMesh = mRHSMesh.prTreeMesh;

}

/*! This constructor creates and empty mesh without anything defined. 
 * This constructor is used when the contents on the mesh are going to be copied from an
 * existing mesh_t object so avoids using the standard constructor and make innecesary calculations.
 * This method must be used with caution because can lead to many runtime errors since the object
 * has null properties.
 * */
mesh_t::mesh_t(int_t iVoid)
{
	std::cout << "void mesh created" << std::endl;
	if(siMeshNumber >= 1)
	{
		siMeshNumber += 1;
	}
	else
	{
		siMeshNumber = 1;
	}
}

/*! This constructor obtains all the parameters provided on the mesh_t object call and gives the automatic name of \a NewMesh.
 * This name is used to create all the .json,.xml,.msh related to the mesh_t object.*/
mesh_t::mesh_t(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB) : mesh_t(iDim, inNodesOnDim_, ptRangeA, ptRangeB, "NewMesh")
{
}

/*!This constructor obtains almost all parameters provided to create the mesh_t.
 * This name is used to create all the .json,.xml,.msh related to the mesh_t object.*/
mesh_t::mesh_t(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB,std::string sMeshName) : mesh_t(iDim, inNodesOnDim_, ptRangeA, ptRangeB, sMeshName, 0)
{
}

	
/*!This constructor obtains all parameters provided to create the mesh_t.
 * The values on the nodes are set by fValue.
 * This name is used to create all the .json,.xml,.msh related to the mesh_t object.*/
mesh_t::mesh_t(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB,std::string sMeshName,floating_t fValue)
{
	if(siMeshNumber >= 1)
	{
		siMeshNumber += 1;
	}
	else
	{
		siMeshNumber = 1;
	}

	setMeshName(sMeshName);
	
	ptRectangleLowA = ptRangeA;
	ptRectangleHighB = ptRangeB;
	
	/* Set the dimension of the mesh_t if not setted already */
	itMeshDim = iDim;
	/* Initialize number of node_ts as 1 */
	itNumberOfNodes = 1;

	inNodesOnDim = inNodesOnDim_;

	/* Multiply the number of node_ts on each dimension so the total amount of node_ts is calculated
	 * example: Consider a 2D mesh_t with nx=5, ny=10
	 * 			numberofnode_ts=1; // Then inside the of the for loop
	 * 			numberofnode_ts=numberofnode_ts*nx*ny
	 *  The number of node_ts is then 50.
	 *  But the indices are zero based, so everithing runs on nx-1 and ny-1 in the loops below.
	 * Stores dimensions on private variable inNodesOnDim
	 */
	#pragma omp parallel for
	//for(int i(0);i<itMeshDim;i++)
	for(int i = 0; i < itMeshDim; i++)
	{
		//inNodesOnDim.push_back(inNodesOnDim_.at(i));
		itNumberOfNodes *= (inNodesOnDim.at(i));
	}	

	
	/* Calculates the required delta on each dimension by using the limits ptRangeA and ptRangeB
	 * when RangeA and RangeB define the points joining a rectangle's diagonal
	 * RangeA always is assume to be the lower while RangeB the higher point as the diagram below
	 *
	 *       ***********RangeB(c,d)
	 *       *         +          *
	 *     ^ *       +            *
	 *     | *     +              *
	 *     y *   +                *
	 *       * +                  *
	 *       RangeA(a,b)***********
	 *		 x -->
	 *  
	 *  On x the ranges are (c-a)/nx i.e (RangeB(1)-RangeA(1))
	 *  On y the ranges are (d-b)/nx i.e (RangeB(2)-RangeA(2))
	 */
	#pragma omp parallel for
	//for(int i(0);i<itMeshDim;i++)
	for(int i = 0; i < itMeshDim; i++)
	{
		ptDeltaOnDim.push_back(fabs(ptRangeB[i]-ptRangeA[i])/(inNodesOnDim[i]-1));
		//std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}
	/* Sepparated for due to the OMP implementation. when running parallel threads the std::cout output some times does have sense
	 * e.g. "hello" -> "Hloel" or similar as a result of parallel execution
	 */
/* for(int i =0; i < itMeshDim; i++)
	{
		std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}
*/
	/* When storing node_ts, the mapping is as follows
	 * 
	 *       ***********RangeB(c,d)
	 *    ny *                  + *
	 *   ... *                    *
	 *     3 *              +     *
	 *     2 *                    *
	 *     1 *           +        *
	 *     0 *                    *
	 *     ^ *       +            *
	 *     | *                    *
	 *       *   +                *
	 *     j * +                  *
	 *       RangeA(a,b)***********
	 *		 i --> 0,1,2,3...,nx
	*/  


	/* Creating the bondary node_ts */

	//Debug("antes del parallel");

	//#pragma omp parallel
/*{*/
	int j(0),i(0);
	point_t ndcoord(2);
	ndcoord = ptRangeA;
	
	index_t iIndexNode(2);
	node_t bNode;


	//Debug("Dentro de parallel antes de for 1");
	/* first j=0, and i=0->(nx-1) zero based nx node_ts */
	//#pragma omp parallel for
	#pragma omp for ordered schedule(dynamic)
	for(i = 0; i < inNodesOnDim[0]; i++)
	{
		//ndcoordx=ndcoordx + deltaX
		//ndcoordy=ndcoordy
		iIndexNode[0] = i;
		iIndexNode[1] = j;
		ndcoord[0] =  ptRangeA[0] + i*ptDeltaOnDim[0];
		bNode.setNode(ndcoord,iIndexNode,fValue); 

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
	for(j = 1; j < inNodesOnDim[1]; j++)
	{
		//ndcoordx=ndcoordx
		//ndcoordy=ndcoordy + deltaY
		index_t iIndexNode(2);
		iIndexNode[0] = i;
		iIndexNode[1] = j;
		ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
		bNode.setNode(ndcoord,iIndexNode,fValue); 
	 
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
	  bNode.setNode(ndcoord,iIndexNode,fValue); 
		
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
		bNode.setNode(ndcoord,iIndexNode,fValue); 
	
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
	//if(itNumberOfNodes != vBoundaryMesh.size())
	

	if(itNumberOfNodes != mBoundaryMesh.size())
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
				index_t iIndexNode(2);
				iIndexNode[0] = i;
				iIndexNode[1] = j;
				//index_t iIndexNode(2);
				//iIndexNode.push_back(i);
				//iIndexNode.push_back(j);
				
				//ndcoord[1]= ptRangeB[1] - j*ptDeltaOnDim[1];
				ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
				bNode.setNode(ndcoord,iIndexNode,fValue); 
				
				//std::cout << iIndexNode << std::endl;
				//std::cout << bNode << std::endl;

				mInnerMesh[iIndexNode] = bNode;
				//Debug("Dentro del for nested");
			}
			
			//Debug("Dentro del for outter despues del nested");
			ndcoord[0]+= ptDeltaOnDim[0];
			ndcoord[1] = ptRangeA[1];
		}
	}

/*}*/
	itBoundaryNodes = mBoundaryMesh.size();	
	itInnerNodes = mInnerMesh.size();

	std::cout << itMeshDim << "-D Mesh Created with " << itNumberOfNodes << " nodes, with the default value " << fValue << std::endl;

}



mesh_t(int_t iDim,index_t inNodesOnDim_,point_t ptRangeA, point_t ptRangeB,std::string sMeshName, condition_t ptrInitCond)
{

	ptrInitialCondition = NULL;
	ptrInitialCondition = ptrInitCond;

	if(siMeshNumber >= 1)
	{
		siMeshNumber += 1;
	}
	else
	{
		siMeshNumber = 1;
	}

	setMeshName(sMeshName);
	
	ptRectangleLowA = ptRangeA;
	ptRectangleHighB = ptRangeB;
	
	/* Set the dimension of the mesh_t if not setted already */
	itMeshDim = iDim;
	/* Initialize number of node_ts as 1 */
	itNumberOfNodes = 1;

	inNodesOnDim = inNodesOnDim_;

	/* Multiply the number of node_ts on each dimension so the total amount of node_ts is calculated
	 * example: Consider a 2D mesh_t with nx=5, ny=10
	 * 			numberofnode_ts=1; // Then inside the of the for loop
	 * 			numberofnode_ts=numberofnode_ts*nx*ny
	 *  The number of node_ts is then 50.
	 *  But the indices are zero based, so everithing runs on nx-1 and ny-1 in the loops below.
	 * Stores dimensions on private variable inNodesOnDim
	 */
	#pragma omp parallel for
	//for(int i(0);i<itMeshDim;i++)
	for(int i = 0; i < itMeshDim; i++)
	{
		//inNodesOnDim.push_back(inNodesOnDim_.at(i));
		itNumberOfNodes *= (inNodesOnDim.at(i));
	}	

	
	/* Calculates the required delta on each dimension by using the limits ptRangeA and ptRangeB
	 * when RangeA and RangeB define the points joining a rectangle's diagonal
	 * RangeA always is assume to be the lower while RangeB the higher point as the diagram below
	 *
	 *       ***********RangeB(c,d)
	 *       *         +          *
	 *     ^ *       +            *
	 *     | *     +              *
	 *     y *   +                *
	 *       * +                  *
	 *       RangeA(a,b)***********
	 *		 x -->
	 *  
	 *  On x the ranges are (c-a)/nx i.e (RangeB(1)-RangeA(1))
	 *  On y the ranges are (d-b)/nx i.e (RangeB(2)-RangeA(2))
	 */
	#pragma omp parallel for
	//for(int i(0);i<itMeshDim;i++)
	for(int i = 0; i < itMeshDim; i++)
	{
		ptDeltaOnDim.push_back(fabs(ptRangeB[i]-ptRangeA[i])/(inNodesOnDim[i]-1));
		//std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}
	/* Sepparated for due to the OMP implementation. when running parallel threads the std::cout output some times does have sense
	 * e.g. "hello" -> "Hloel" or similar as a result of parallel execution
	 */
/* for(int i =0; i < itMeshDim; i++)
	{
		std::cout << "Delta on Dim " << i << " is (" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << inNodesOnDim[i]-1 << " = " <<  ptDeltaOnDim[i] << std::endl;
	}
*/
	/* When storing node_ts, the mapping is as follows
	 * 
	 *       ***********RangeB(c,d)
	 *    ny *                  + *
	 *   ... *                    *
	 *     3 *              +     *
	 *     2 *                    *
	 *     1 *           +        *
	 *     0 *                    *
	 *     ^ *       +            *
	 *     | *                    *
	 *       *   +                *
	 *     j * +                  *
	 *       RangeA(a,b)***********
	 *		 i --> 0,1,2,3...,nx
	*/  


	/* Creating the bondary node_ts */

	//Debug("antes del parallel");

	//#pragma omp parallel
/*{*/
	int j(0),i(0);
	point_t ndcoord(2);
	ndcoord = ptRangeA;
	
	index_t iIndexNode(2);
	node_t bNode;


	//Debug("Dentro de parallel antes de for 1");
	/* first j=0, and i=0->(nx-1) zero based nx node_ts */
	//#pragma omp parallel for
	#pragma omp for ordered schedule(dynamic)
	for(i = 0; i < inNodesOnDim[0]; i++)
	{
		//ndcoordx=ndcoordx + deltaX
		//ndcoordy=ndcoordy
		iIndexNode[0] = i;
		iIndexNode[1] = j;
		ndcoord[0] =  ptRangeA[0] + i*ptDeltaOnDim[0];
		bNode.setNode(ndcoord,iIndexNode,fValue); 

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
	for(j = 1; j < inNodesOnDim[1]; j++)
	{
		//ndcoordx=ndcoordx
		//ndcoordy=ndcoordy + deltaY
		index_t iIndexNode(2);
		iIndexNode[0] = i;
		iIndexNode[1] = j;
		ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
		bNode.setNode(ndcoord,iIndexNode,fValue); 
	 
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
	  bNode.setNode(ndcoord,iIndexNode,fValue); 
		
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
		bNode.setNode(ndcoord,iIndexNode,fValue); 
	
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
	//if(itNumberOfNodes != vBoundaryMesh.size())
	

	if(itNumberOfNodes != mBoundaryMesh.size())
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
				index_t iIndexNode(2);
				iIndexNode[0] = i;
				iIndexNode[1] = j;
				//index_t iIndexNode(2);
				//iIndexNode.push_back(i);
				//iIndexNode.push_back(j);
				
				//ndcoord[1]= ptRangeB[1] - j*ptDeltaOnDim[1];
				ndcoord[1] = ptRangeA[1] + j*ptDeltaOnDim[1];
				bNode.setNode(ndcoord,iIndexNode,fValue); 
				
				//std::cout << iIndexNode << std::endl;
				//std::cout << bNode << std::endl;

				mInnerMesh[iIndexNode] = bNode;
				//Debug("Dentro del for nested");
			}
			
			//Debug("Dentro del for outter despues del nested");
			ndcoord[0]+= ptDeltaOnDim[0];
			ndcoord[1] = ptRangeA[1];
		}
	}

/*}*/
	itBoundaryNodes = mBoundaryMesh.size();	
	itInnerNodes = mInnerMesh.size();

	std::cout << itMeshDim << "-D Mesh Created with " << itNumberOfNodes << " nodes, with the default value " << fValue << std::endl;


}




/*! This constructor reads a boost::property_tree with all the data that specifies the mesh_t object.*/
mesh_t::mesh_t(boost::property_tree::ptree prTree)
{
	/* Get the values from pTree readed */

	std::string sPathBuffer;
	std::string sBuffer;

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshName;
	sMeshName = prTree.get(sPathBuffer,"NewMesh"); /*!< Loads the mesh_t name. If the property name is not specified, the name "NewMesh" is used as defaulti.*/
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshDim;
	sBuffer = prTree.get(sPathBuffer,"2"); /*!< Loads the mesh_t Dimensions. If the property is not specified, the dimension is set to 2.*/
	itMeshDim = StringToNumber<int_t>(sBuffer); /*!< Type casting to int_t.*/
	sPathBuffer.clear();

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshND;
	sPathBuffer+=".";
	
	for(int j(0);j<2;j++) /*!< Load nodes on each dimension. if missing fills vector with -1.*/
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		inNodesOnDim.push_back(StringToNumber<int>(prTree.get(sPathBuffer + NumberToString(j),"-1")));
	}
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshDD;
	sPathBuffer+=".";
	
	for(int j(0);j<2;j++) /*!< Load delta on each dimension. if missing fills vector with -1.0.*/
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		ptDeltaOnDim.push_back(StringToNumber<floating_t>(prTree.get(sPathBuffer + NumberToString(j),"-1.0")));
	}
	sPathBuffer.clear();

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshPA;
	sPathBuffer+=".";
	
	for(int j(0);j<2;j++) /*!< Loads the Low Point A.*/
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		ptRectangleLowA.push_back(StringToNumber<floating_t>( prTree.get(sPathBuffer + NumberToString(j),NumberToString(j) ) ));
	}	
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshPB;
	sPathBuffer+=".";
	
	for(int j(0);j<2;j++) /*!< Loads the High Point B.*/
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		ptRectangleHighB.push_back(StringToNumber<floating_t>( prTree.get( sPathBuffer + NumberToString(j),NumberToString(j) ) ));
	}
	sPathBuffer.clear();

	/* Refinement of the prTree with the addecuate values.*/ 
	
	if( (ptRectangleLowA[0] == ptRectangleHighB[0]) && (ptRectangleLowA[1] == ptRectangleHighB[1]) )
	{
		std::cout << "[EE] Check the bounding box limits. I'm using the default limits instead." << std::endl;

		ptRectangleLowA[0] == 0 ;
		ptRectangleLowA[1] == 0 ;
		ptRectangleHighB[0] == 1 ;
		ptRectangleHighB[1] == 1 ;

	}


	if( (ptDeltaOnDim[0] < 0.0) && (inNodesOnDim[0] < 0) )
	{
		std::cout << "[EE] Check the nodes on each dimension or/and the delta on each dimension. I'm using the default values instead." << std::endl;
		
		itNumberOfNodes = 1;
			
		for(int i(0); i < itMeshDim; i++)
		{
			inNodesOnDim[i] = 10;
			ptDeltaOnDim[i] = (ptRectangleHighB[i] - ptRectangleLowA[i])/inNodesOnDim[i];
			itNumberOfNodes *= (inNodesOnDim.at(i));
		}

		
	}
	else if( (ptDeltaOnDim[0] > 0.0) && (inNodesOnDim[0] < 0) )
	{
		std::cout << "[II] Nodes on each dimension not given, using deltas to calculate number of nodes." << std::endl;
		
		itNumberOfNodes = 1;
			
		for(int i(0); i < itMeshDim; i++)
		{
			inNodesOnDim[i] = (ptRectangleHighB[i] - ptRectangleLowA[i])/ptDeltaOnDim[i];
			itNumberOfNodes *= (inNodesOnDim.at(i));
		}


	}
	else if( (ptDeltaOnDim[0] < 0.0) && (inNodesOnDim[0] > 0) )
	{
		std::cout << "[II] Delta on each dimension not given. Using nodes on each dimension to calculate the delta." << std::endl;
		
		itNumberOfNodes = 1;
			
		for(int i(0); i < itMeshDim; i++)
		{
			ptDeltaOnDim[i] = (ptRectangleHighB[i] - ptRectangleLowA[i])/inNodesOnDim[i];
			itNumberOfNodes *= (inNodesOnDim.at(i));
		}


	}

	createPropertyTree();

	*this = mesh_t(itMeshDim,inNodesOnDim,ptRectangleLowA,ptRectangleHighB,sMeshName);

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
		//std::cout << prTreeMesh  << std::endl;

		*this = mesh_t(prTreeMesh);
	}
	/* Is XML formatted? */
	else if(sFileName.find(sXML) < sFileName.size())
	{
		//std::cout << "is xml " << sFileName.find(_pMeshXML) << std::endl;
		boost::property_tree::read_xml(sFileName,prTreeMesh);
		
		//std::cout << "File: " << sFileName << " contains:\n";
		//std::cout << prTreeMesh << std::endl;
	
		*this = mesh_t(prTreeMesh);
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

/*! This operator copies all the relevant data to \c (this) object.
 * Also prevents self-assignment. */
mesh_t& mesh_t::operator=(const mesh_t& mRHSMesh)
{
	if(this != &mRHSMesh)
	{
		itMeshDim = mRHSMesh.itMeshDim;
		itNumberOfNodes = mRHSMesh.itNumberOfNodes;
		itBoundaryNodes = mRHSMesh.itBoundaryNodes;
		itInnerNodes = mRHSMesh.itInnerNodes;
		//siMeshNumber += 1; 
		
		sMeshName = mRHSMesh.sMeshName; 
		sMeshJSON = mRHSMesh.sMeshJSON;
		sMeshXML  = mRHSMesh.sMeshXML;
		sMeshFile = mRHSMesh.sMeshFile;
								 
		inNodesOnDim = mRHSMesh.inNodesOnDim;
								 
		ptDeltaOnDim = mRHSMesh.ptDeltaOnDim;
		ptRectangleLowA = mRHSMesh.ptRectangleLowA;
		ptRectangleHighB = mRHSMesh.ptRectangleHighB;
								 
		mBoundaryMesh = mRHSMesh.mBoundaryMesh;
		mInnerMesh = mRHSMesh.mInnerMesh;
								 
		vMeshVoxels = mRHSMesh.vMeshVoxels; 

		prTreeMesh = mRHSMesh.prTreeMesh;
	}

	return *this;
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
		std::cout << "Boundary mesh size " << mBoundaryMesh.size() << std::endl;
		std::cout << "Inner mesh size " << mInnerMesh.size() << std::endl;
	
		//std::map<index_t,node_t>::iterator mBoundaryMeshIterator;
		//std::map<index_t,node_t>::iterator mInnerMeshIterator;



		for(std::map<index_t,node_t>::iterator mBoundaryMeshIterator = mBoundaryMesh.begin(); mBoundaryMeshIterator != mBoundaryMesh.end(); ++mBoundaryMeshIterator)
		{
			//std::cout << vBoundaryMesh[i] << std::endl;
		 	point_t ptBuffer(mBoundaryMeshIterator->second.getCoordinates());
			floating_t dBuffer(mBoundaryMeshIterator->second.getValue());
			
			for(int j(0);j<ptBuffer.size();j++)
			{
				sFileStream << ptBuffer[j] << "\t";
			}

			//sFileStream << "\t" << dBuffer << std::endl;
			sFileStream << std::endl;
		}

		for(std::map<index_t,node_t>::iterator mInnerMeshIterator = mInnerMesh.begin(); mInnerMeshIterator != mInnerMesh.end(); ++mInnerMeshIterator)
		{
		  	point_t ptBuffer(mInnerMeshIterator->second.getCoordinates());
			floating_t dBuffer(mInnerMeshIterator->second.getValue());
			

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

/*! Returns the nodes on dimension iDim.*/
int_t mesh_t::getNodesOnDim(int_t iDim)
{
	if(iDim < inNodesOnDim.size())
	{
		return inNodesOnDim[iDim];
	}
	else
	{
		std::cout << "[EE] Wrong node on dim access.\n";
		return -1;
	}
}

/* floating_t return methods */

/*!
 * Returns the delta on dimension iDim.
 * */
floating_t mesh_t::getDeltaOnDim(int_t iDim)
{
	if(iDim < ptDeltaOnDim.size())
	{
		return ptDeltaOnDim[iDim];
	}
	else
	{
		std::cout << "[EE] Wrong desired delta." << std::endl;
		return -1;
	}
}

/*! Returns a index_t object with the indices on all dimensions.
 * */
index_t mesh_t::getNodesOnDim()
{
	return inNodesOnDim;
}
/* point_t returning methods */

/*! Returns a point_t object with the deltas on all dimensions.
 */
point_t mesh_t::getDeltaOnDim()
{
	return ptDeltaOnDim;
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



/*! Insert a node on the boundary. If the node is already on the boundary of the mesh it does not add it.
 */
void mesh_t::push_backBN(node_t cNode)
{

	if( mBoundaryMesh.count(cNode.getIndices()) == true || mInnerMesh.count(cNode.getIndices()) == true  )
	{
		std::cout << "The node is already contained" << std::endl;
	}
	else
	{
		mBoundaryMesh[cNode.getIndices()] = cNode;
	    itNumberOfNodes++;

		itNumberOfNodes = 0;
		std::cout << "Boundary Node inserted on mesh. " << itNumberOfNodes << " nodes stored on mesh" << std::endl;
	}

}


/*! Insert a node on the inner region of the mesh_t. If the node is already on the inner region of the mesh it does not add it.
 */
void mesh_t::push_backIN(node_t cNode)
{
	if( mBoundaryMesh.count(cNode.getIndices()) == true || mInnerMesh.count(cNode.getIndices()) == true  )
	{
		std::cout << "The node is already contained" << std::endl;
	}
	else
	{
		mInnerMesh[cNode.getIndices()] = cNode;
	    itNumberOfNodes++;

		itNumberOfNodes = 0;
		std::cout << "Inner node inserted on mesh. " << itNumberOfNodes << " nodes stored on mesh" << std::endl;
	}

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


void mesh_t::coutMesh()
{
	std::cout << "Boundary mesh size " << mBoundaryMesh.size() << std::endl;
	std::cout << "Inner mesh size " << mInnerMesh.size() << std::endl;

	std::cout << "Boundary nodes" << std::endl;

	for(std::map<index_t,node_t>::iterator mBoundaryMeshIterator = mBoundaryMesh.begin(); mBoundaryMeshIterator != mBoundaryMesh.end(); ++mBoundaryMeshIterator)
	{
		//std::cout << vBoundaryMesh[i] << std::endl;
		point_t ptBuffer(mBoundaryMeshIterator->second.getCoordinates());
		index_t idxBuffer(mBoundaryMeshIterator->first);
		floating_t dBuffer(mBoundaryMeshIterator->second.getValue());
	
		std::cout << idxBuffer << "\t";

		for(int j(0);j<ptBuffer.size();j++)
		{
			std::cout << ptBuffer[j] << "\t";
		}

		//sFileStream << "\t" << dBuffer << std::endl;
		std::cout << "\t" << dBuffer << std::endl;
	}

	std::cout << "Inner nodes" << std::endl;

	for(std::map<index_t,node_t>::iterator mInnerMeshIterator = mInnerMesh.begin(); mInnerMeshIterator != mInnerMesh.end(); ++mInnerMeshIterator)
	{
		point_t ptBuffer(mInnerMeshIterator->second.getCoordinates());
		index_t idxBuffers(mInnerMeshIterator->first);
		floating_t dBuffer(mInnerMeshIterator->second.getValue());
		
		std::cout << idxBuffers << "\t" ;

		for(int j(0);j<ptBuffer.size();j++)
		{
			std::cout << ptBuffer[j] << "\t";
		}

		//sFileStream << "\t" << dBuffer << std::endl;
		std::cout << "\t" << dBuffer  << std::endl;
	}

}


/*! */
std::map<index_t,node_t> mesh_t::getBoundaryMesh()
{
	return mBoundaryMesh;
}

/*! */
std::map<index_t,node_t> mesh_t::getInnerMesh()
{
	return mInnerMesh;
}

// *!\brief ostream operator for the mesh_t.
/*!
 * Overloads the ostream operator for mesh_t objects, so the information
 * of the mesh_t can displayed by standard output (std::cout) or sent to streams.
 */
std::ostream& operator<<(std::ostream& outStream, mesh_t& cMesh)
{
	std::cout << "Mesh Name: " << cMesh.sMeshName <<  std::endl;
	std::cout << "Mesh JSON file: " << cMesh.sMeshJSON <<  std::endl;
	std::cout << "Mesh XML file: " << cMesh.sMeshXML <<  std::endl;
	std::cout << "Mesh File: " << cMesh.sMeshFile << std::endl;
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
mesh_t IterateFD(mesh_t& mMesh,floating_t dDeltaT)
{	
}
