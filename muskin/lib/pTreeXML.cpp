#include "headers.hpp"

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
//void pTreeXML(node& nod);
//{

//}
