#include "headers.hpp"
//#include "node.hpp"

node::node(point_t coords, index_t indices, double value)
{
	ntIndices=indices;
	ptCoordinates=coords;
	dNodeValue=value;
	// siNumberOfNodes must be declared on the implementation of the class as int_t node::siNumberOfNodes(0)
	// it is a shared variable between every "node" objects. I mean, a static variable (see node.cpp for further information)
	siNumberOfNodes++;
	iNodeNumber=siNumberOfNodes;
}

int_t node::size()
{
	return ptCoordinates.size();
}

int_t node::getNodeNumber()
{
	return iNodeNumber;
}

index_t node::getIndices()
{
	return ntIndices;
}

point_t node::getCoordinates()
{
	return ptCoordinates;
}

int_t node::getNumberOfNodes()
{
	return siNumberOfNodes;
}


std::ostream& operator<<(std::ostream& outStream, node& nod)
{
  point_t ptBuffer(nod.getCoordinates());
  index_t itBuffer(nod.getIndices());

  outStream  << "[" << nod.getNodeNumber() << "]" <<  itBuffer << ptBuffer;
  
  return outStream;
}
