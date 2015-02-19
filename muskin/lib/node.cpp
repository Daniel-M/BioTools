#include "headers.hpp"
//#include "node.hpp"


/*! \brief Standard node constructor
	 *
	 * Creates a void node but increases the node number static variable
	 */
node::node()
{
	siNumberOfNodes=0;
}
	
	/*!* \brief Node constructor using the coordinates, indices, and the stored value 
	 * 
	 * \param coords coordinates of the node.
	 * \param indices indices of the node.
	 * \param value value stored at the node.
	 * */
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


/*! \brief Overloaded operator= to set the node index \c index_t directly.
 * 
 * This operator modifies the left-hand side node
 *
 * \param itIndex_ the new indices set for the node.
 * */
node& node::operator=(const index_t itIndex_)
{
	itIndices = itIndex_;
}

/*! \brief Overloaded operator= to set the node value \c double directly 
 *
 * This operator modifies the left-hand side node
 *
 * \param dValue_ the value to be assigned into the node.
 * */
node& node::operator=(const double dValue_)
{
	dNodeValue=dValue_;
}

/*! \brief Returns the dimensions of the node e.g. a 2D mesh uses 2D nodes */
int_t node::getDimension()
{
	return ptCoordinates.size();
}

/*! \brief Returns the number assigned to the node */
int_t node::getNodeNumber()
{
	return itNodeNumber;
}

/*! \brief Returns the number of nodes created appealing to an static variable */
int_t node::getNumberOfNodes()
{
	return siNumberOfNodes;
}

/*! \brief Returns the value stored on the node */
double node::getValue()
{
	return dNodeValue;
}

/*! \brief Set node parameters as if where with the constructor
 *
 * \param coords coordinates of the node.
 * \param indices indices of the node.
 * \param value value stored at the node. 
 */
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

/*! \brief Set node parameters as if where with the constructor
 *
 * \param coords coordinates of the node.
 * \param indices indices of the node.
 * \param value value stored at the node. 
 */
void node::setValue(double value)
{
	dNodeValue=value;
}

/*! \brief Returns the indices associated with the of the node */
index_t node::getIndices()
{
	return itIndices;
}

/*! \brief Returns the coordinates associated with the node */
point_t node::getCoordinates()
{
	return ptCoordinates;
}


/*!\brief Friend function to send nodes to streams
 * 
 * Nodes are displayed as
 * [node_number][node_indices](node_coordinates) node_value
 *
 */
std::ostream& operator<<(std::ostream& outStream, node& nod)
{
  point_t ptBuffer(nod.getCoordinates());
  index_t itBuffer(nod.getIndices());
  double dBuffer(nod.getValue());

  outStream  << "[" << nod.getNodeNumber() << "]" <<  itBuffer << ptBuffer << "\t" << dBuffer ;
  
  return outStream;
}
