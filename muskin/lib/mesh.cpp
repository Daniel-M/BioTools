#include "headers.hpp"
//#include "mesh.hpp"

mesh::mesh()
{
	iMeshDim=2;
	iNumberOfNodes = 0;
	
	for(int i(0);i<iMeshDim;i++)
	{
		ptDeltaOnDim.push_back(0);
	}

	std::cout << iMeshDim << "-D Mesh Created" << std::endl;
}

mesh::mesh(int_t iDim,index_t itNodesOnDim,point_t ptRangeA, point_t ptRangeB)
{
	iMeshDim=iDim;
	iNumberOfNodes = 1;

	for(int i(0);i<iMeshDim;i++)
	{
		iNumberOfNodes*=itNodesOnDim[i];
	}	

	for(int i(0);i<iMeshDim;i++)
	{
		ptDeltaOnDim.push_back(fabs(ptRangeB[i]-ptRangeA[i])/itNodesOnDim[i]);
		std::cout << "(" << ptRangeB[i] << " - " << ptRangeA[i] << ")/" << itNodesOnDim[i] << " = " << fabs(ptRangeB[i]-ptRangeA[i])/itNodesOnDim[i] << std::endl;
	}

	std::vector<point_t> Ranges(2);
	Ranges[0]=ptRangeA;
	Ranges[1]=ptRangeB;


	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE
	//Build Boundary Nodes IM WORKING HEREEEEE

	for(int k(0);k<Ranges.size();k++)
	{
		point_t point=Ranges[k];
		//index_t index(iMeshDim,0);

			for(int i(0);i<iMeshDim;i++)
			{
				index_t index(iMeshDim,0);
				for(int j(0);j<itNodesOnDim[i];j++)
				{
					
					//point[i]=(Ranges[k][i]+ptDeltaOnDim[i]*j);
					//point[i]+=ptDeltaOnDim[i];

					node nod(point,index,0);
					index[i]+=1;
					point[i]+=ptDeltaOnDim[i];
					
					std::cout << " " << k << "," << i << "," << j << " Nodo " << nod << std::endl;
				}
				std::cout <<std::endl;
			}
	}

	std::cout << iMeshDim << "-D Mesh Created with " << iNumberOfNodes << " nodes"  << std::endl;

}

void mesh::push_backIN(node cNode)
{
	vBoundaryMesh.push_back(cNode);
    iNumberOfNodes++;

	std::cout << "Inner Node inserted on mesh. " << iNumberOfNodes << " nodes stored on mesh" << std::endl;
}

void mesh::push_backBN(node cNode)
{
	vInnerMesh.push_back(cNode);
    iNumberOfNodes++;

	std::cout << "Boundary Node inserted on mesh. " << iNumberOfNodes << " nodes stored on mesh" << std::endl;
}

