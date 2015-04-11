#include "headers.hpp"
//#include "node.hpp"


/*! \brief Standard node_t constructor
	 *
	 * Creates a void node_t but increases the node_t number static variable
	 */
node_t::node_t()
{
	siNumberOfNodes=0;
}
	
	/*!* \brief node_t constructor using the coordinates, indices, and the stored value 
	 * 
	 * \param coords coordinates of the node_t.
	 * \param indices indices of the node_t.
	 * \param value value stored at the node_t.
	 * */
node_t::node_t(point_t coords, index_t indices, floating_t value)
{
	itIndices=indices;
	ptCoordinates=coords;
	dNodeValue=value;
	// siNumberOfNodes must be declared on the implementation of the class as int_t node_t::siNumberOfNodes(0)
	// it is a shared variable between every "node_t" objects. I mean, a static variable (see node_t.cpp for further information)
	siNumberOfNodes++;
	itNodeNumber=siNumberOfNodes;
}


/*! \brief Overloaded operator= to set the node_t index \c index_t directly.
 * 
 * This operator modifies the left-hand side node_t
 *
 * \param itIndex_ the new indices set for the node_t.
 * */
node_t& node_t::operator=(const index_t itIndex_)
{
	itIndices = itIndex_;
}

/*! \brief Overloaded operator= to set the node_t value \c floating_t directly 
 *
 * This operator modifies the left-hand side node_t
 *
 * \param dValue_ the value to be assigned into the node_t.
 * */
node_t& node_t::operator=(const floating_t dValue_)
{
	dNodeValue=dValue_;
}

/*! This operator performs sums of the values stored on the nodes without changing the indexes of the nodes.
 *  This allows the direct sum between node_t objects.
 * */
node_t node_t::operator+(const node_t& RHSNode_)
{
  node_t nBuffer1(*this),nBuffer2(RHSNode_);
  nBuffer1.setValue(nBuffer1.getValue() + nBuffer2.getValue());

  return nBuffer1;
}

/*! This operator performs substraction between the values stored on the nodes without changing the indexes of the nodes.
//*  This is performed by calling the operator* with -1*node_t and then calling operator+ that performs the sum of the node_t + (-node_t)
//*  Resulting in the subtraction of the node_t values.
//*  \sa operator+
//*  \sa operator*
 * */
node_t node_t::operator-(const node_t& RHSNode_)
{
  node_t nBuffer1(*this),nBuffer2(RHSNode_);
  nBuffer1.setValue(nBuffer1.getValue() - nBuffer2.getValue());

  return nBuffer1;
}

/*! \brief Returns the dimensions of the node_t e.g. a 2D mesh_t uses 2D node_ts */
int_t node_t::getDimension()
{
	return ptCoordinates.size();
}

/*! \brief Returns the number assigned to the node_t */
int_t node_t::getNodeNumber()
{
	return itNodeNumber;
}

/*! \brief Returns the number of node_ts created appealing to an static variable */
int_t node_t::getNumberOfNodes()
{
	return siNumberOfNodes;
}

/*! \brief Returns the value stored on the node_t */
floating_t node_t::getValue()
{
	return dNodeValue;
}

/*! \brief Set node_t parameters as if where with the constructor
 *
 * \param coords coordinates of the node_t.
 * \param indices indices of the node_t.
 * \param value value stored at the node_t. 
 */
void node_t::setNode(point_t coords, index_t indices, floating_t value)
{
	itIndices=indices;
	ptCoordinates=coords;
	dNodeValue=value;
	// siNumberOfNodes must be declared on the implementation of the class as int_t node_t::siNumberOfNodes(0)
	// it is a shared variable between every "node_t" objects. I mean, a static variable (see node_t.cpp for further information)
	siNumberOfNodes++;
	itNodeNumber=siNumberOfNodes;
}

/*! \brief Set node_t parameters as if where with the constructor
 *
 * \param coords coordinates of the node_t.
 * \param indices indices of the node_t.
 * \param value value stored at the node_t. 
 */
void node_t::setValue(floating_t value)
{
	dNodeValue=value;
}

/*! \brief Returns the indices associated with the of the node_t */
index_t node_t::getIndices()
{
	return itIndices;
}

/*! \brief Returns the coordinates associated with the node_t */
point_t node_t::getCoordinates()
{
	return ptCoordinates;
}


/*!\brief Friend function to send node_ts to streams
 * 
 * node_ts are displayed as
 * [node_t_number][node_t_indices](node_t_coordinates) node_t_value
 *
 */
std::ostream& operator<<(std::ostream& outStream, node_t& nod)
{
  point_t ptBuffer(nod.getCoordinates());
  index_t itBuffer(nod.getIndices());
  floating_t dBuffer(nod.getValue());

  outStream  << "[" << nod.getNodeNumber() << "]" <<  itBuffer << ptBuffer << "\t" << dBuffer ;
  
  return outStream;
}
