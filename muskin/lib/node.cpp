#include "headers.hpp"
//#include "node.hpp"

node::node()
{
	siNumberOfNodes=0;
}

node::node(point_t coords, index_t indices, double value)
{
	itIndices=indices;
	ptCoordinates=coords;
	dNodeValue=value;
	// siNumberOfNodes must be declared on the implementation of the class as int_t node::siNumberOfNodes(0)
	// it is a shared variable between every "node" objects. I mean, a static variable (see node.cpp for further information)
	siNumberOfNodes++;
	itNodeNumber=siNumberOfNodes;
}

void node::setNode(point_t coords, index_t indices, double value)
{
	itIndices=indices;
	ptCoordinates=coords;
	dNodeValue=value;
	// siNumberOfNodes must be declared on the implementation of the class as int_t node::siNumberOfNodes(0)
	// it is a shared variable between every "node" objects. I mean, a static variable (see node.cpp for further information)
	siNumberOfNodes++;
	itNodeNumber=siNumberOfNodes;
}

node& node::operator=(const index_t itIndex_)
{
	itIndices = itIndex_;
}

node& node::operator=(const double dValue_)
{
	dNodeValue=dValue_;
}

int_t node::getDimension()
{
	return ptCoordinates.size();
}

int_t node::getNodeNumber()
{
	return itNodeNumber;
}

index_t node::getIndices()
{
	return itIndices;
}

point_t node::getCoordinates()
{
	return ptCoordinates;
}

int_t node::getNumberOfNodes()
{
	return siNumberOfNodes;
}

double node::getValue()
{
	return dNodeValue;
}


std::ostream& operator<<(std::ostream& outStream, node& nod)
{
  point_t ptBuffer(nod.getCoordinates());
  index_t itBuffer(nod.getIndices());
  double dBuffer(nod.getValue());

  outStream  << "[" << nod.getNodeNumber() << "]" <<  itBuffer << ptBuffer << "\t" << dBuffer ;
  
  return outStream;
}
