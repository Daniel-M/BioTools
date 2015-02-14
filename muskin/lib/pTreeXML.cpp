#include "headers.hpp"
//#include "mesh.hpp"

mesh::mesh(std::string sFileName)
{
	//try{
	if(std::ifstream(sFileName).good() == true)
	{
		read_xml(sFileName,prtrXML);

		itMeshDim = prtrXML.get("mesh.dimension",0);
		itNumberOfNodes = prtrXML.get("mesh.nnodes",0);
		itBoundaryNodes = prtrXML.get("mesh.bnodes",0);
		itInnerNodes = prtrXML.get("mesh.inodes",0);
		
		boost::property_tree::ptree	prtrDims = prtrXML.get_child("mesh.nodesdimensions");
		//for(const auto& tree : prtrDims)
		//{
			////inNodesOnDim.push_back(tree.second.get("",0));
			//inNodesOnDim.push_back(tree.second.get<int_t>(""));
		//}
		int i(0);
		for(const auto& tree : prtrDims)
		{
			inNodesOnDim.push_back(tree.second.get<int_t>("nodesdimensions.x"+NumberToString(i)));
			//inNodesOnDim.push_back(tree.second.get(NumberToString(i),0));
			//i++;
		}
	
		std::cout << "NodesOnD " << inNodesOnDim << std::endl;

		boost::property_tree::ptree	prtrDeltas = prtrXML.get_child("mesh.deltaondim");
		i=0;
		for(const auto& tree: prtrDeltas)
		{
			ptDeltaOnDim.push_back(tree.second.get<double>(""));
			//ptDeltaOnDim.push_back(tree.second.get(NumberToString(i),0.0));
			//i++;
		}
		std::cout << "ptDelta " << ptDeltaOnDim << std::endl;
		
		boost::property_tree::ptree	prtrRangeA = prtrXML.get_child("mesh.pointa");
		i=0;
		for(const auto& tree: prtrRangeA)
		{
			ptRectangleLowA.push_back(tree.second.get<double>(""));
			//ptRectangleLowA.push_back(tree.second.get(NumberToString(i),0));
			//i++;
		}
		std::cout << "Ra " << ptRectangleLowA << std::endl;
		
		boost::property_tree::ptree	prtrRangeB = prtrXML.get_child("mesh.pointb");
		i=0;
		for(const auto& tree: prtrRangeB)
		{
			ptRectangleHighB.push_back(tree.second.get<double>(""));
			//ptRectangleHighB.push_back(tree.second.get(NumberToString(i),0));
			//i++;
		}	
		std::cout << " Rb " << ptRectangleHighB << std::endl;

		sMeshFile = prtrXML.get<std::string>("mesh.meshfile");
		sMeshXML = prtrXML.get<std::string>("mesh.meshxml");
		sMeshName = prtrXML.get<std::string>("mesh.meshname");

		if(itMeshDim == 0 || itNumberOfNodes == 0 || (ptRectangleLowA.size() != itMeshDim) || (ptRectangleHighB.size() != itMeshDim))
		{
			std::cout << "Bad format on " << sFileName << " bad dimension, number of nodes or limiting points" << std::endl;
		}
		else if( (inNodesOnDim.size() != itMeshDim) && (ptDeltaOnDim.size() != itMeshDim))
		{
			std::cout << "Bad format on " << sFileName << " check nodes on dimensions or deltas on dimensions" << std::endl;
		}
		else if( (inNodesOnDim.size() == itMeshDim) && (ptDeltaOnDim.size() != itMeshDim))
		{
			std::cout << "Bad format on " << sFileName << " " << std::endl;
			for(int i(0);i<itMeshDim;i++)
			{
			}
		}
		else if( (inNodesOnDim.size() != itMeshDim) && (ptDeltaOnDim.size() == itMeshDim))
		{
			std::cout << "Bad format on " << sFileName << "" << std::endl;
		}
		else if(itBoundaryNodes == 0 || itInnerNodes == 0)
		{
			std::cout << "Problem loading XML, empty mesh?" << std::endl;
		}
		
			std::cout << *this << std::endl;
	}
	else
	{
		std::cout << "[EE] ERROR!!: File " << sFileName << " could not be found" << std::endl;
	}
}

int_t mesh::createMeshXML()
{
	createMeshXML(sMeshXML);
}


int_t mesh::createMeshXML(std::string sFileName)
{
	sMeshXML = sFileName;
	prtrXML.put("mesh.meshname",sMeshName);
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
