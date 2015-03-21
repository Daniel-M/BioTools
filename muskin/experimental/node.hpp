//#include "headers.hpp"
//#include "node.cpp"

class node
{
	private:
	
	static int_t siNumberOfNodes; /*!< Stores the number of nodes created as objects, this variable is for debuggin but can be exploited as you wish*/
	int_t itNodeNumber; /*!< */
	index_t itIndices; /*!< */
	point_t ptCoordinates; /*!< */
	floating_t dNodeValue; /*!< */

	//node(){};

	public:

	
	/* Class constructors */
	
	/*! \brief Standard node constructor */
	node();
	/*! \brief Node constructor using the coordinates, indices, and the stored value */
	node(point_t coords, index_t indices, floating_t value);

	
	/* Class Operators */
	
	/*! \brief Overloaded operator= to set the node index \c index_t directly.  */
	node& operator=(const index_t itIndex_);
	
	/*! \brief Overloaded operator= to set the node value \c floating_t directly  */
	node& operator=(const floating_t dValue_);

	
	/* return int_t methods */
	
	/*! \brief Returns the dimensions of the node e.g. a 2D mesh uses 2D nodes */
	int_t getDimension();
	
	/*! \brief Returns the number assigned to the node */
	int_t getNodeNumber();
	
	/*! \brief Returns the number of nodes created appealing to an static variable */
	int_t getNumberOfNodes();
	

	
	/* return floating_t methods */
	
	/*! \brief Returns the value stored on the node */
	floating_t getValue();
	
	
	/* return void methods */
	
	/*! \brief Set node parameters as if where with the constructor
	 *
	 * \param coords coordinates of the node.
	 * \param indices indices of the node.
	 * \param value value stored at the node. 
	 */
	void setNode(point_t coords, index_t indices, floating_t value);
	
	/*! \brief Set node parameters as if where with the constructor
	 *
	 * \param coords coordinates of the node.
	 * \param indices indices of the node.
	 * \param value value stored at the node. 
	 */
	void setValue(floating_t value);

	
	/* return index_t methods */
	
	/*! \brief Returns the indices associated with the of the node */
	index_t getIndices();
	
	
	/* return point_t methods */
	
	/*! \brief Returns the coordinates associated with the node */
	point_t getCoordinates();
	

	
	/* friend methods */
	
	/*!\brief Friend function to send nodes to streams 
	 * 
	 * Nodes are displayed as
	 * [node_number][node_indices](node_coordinates) node_value
	 *
	 * */
	friend	std::ostream& operator<<(std::ostream& outStream, node& nod);
};
