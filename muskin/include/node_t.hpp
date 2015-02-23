//#include "headers.hpp"
//#include "node_t.cpp"

class node_t
{
	private:
	
	static int_t siNumberOfNodes; /*!< Stores the number of node_ts created as objects, this variable is for debuggin but can be exploited as you wish*/
	int_t itNodeNumber; /*!< */
	index_t itIndices; /*!< */
	point_t ptCoordinates; /*!< */
	double dNodeValue; /*!< */

	//node(){};

	public:

	
	/* Class constructors */
	
	/*! \brief Standard node_t constructor */
	node_t();
	/*! \brief node_t constructor using the coordinates, indices, and the stored value */
	node_t(point_t coords, index_t indices, double value);

	
	/* Class Operators */
	
	/*! \brief Overloaded operator= to set the node_t index \c index_t directly.  */
	node_t& operator=(const index_t itIndex_);
	
	/*! \brief Overloaded operator= to set the node_t value \c double directly  */
	node_t& operator=(const double dValue_);

	
	/* return int_t methods */
	
	/*! \brief Returns the dimensions of the node_t e.g. a 2D mesh_t uses 2D node_ts */
	int_t getDimension();
	
	/*! \brief Returns the number assigned to the node_t */
	int_t getNodeNumber();
	
	/*! \brief Returns the number of node_ts created appealing to an static variable */
	int_t getNumberOfNodes();
	

	
	/* return double methods */
	
	/*! \brief Returns the value stored on the node_t */
	double getValue();
	
	
	/* return void methods */
	
	/*! \brief Set node_t parameters as if where with the constructor
	 *
	 * \param coords coordinates of the node_t.
	 * \param indices indices of the node_t.
	 * \param value value stored at the node_t. 
	 */
	void setNode(point_t coords, index_t indices, double value);
	
	/*! \brief Set node_t parameters as if where with the constructor
	 *
	 * \param coords coordinates of the node_t.
	 * \param indices indices of the node_t.
	 * \param value value stored at the node_t. 
	 */
	void setValue(double value);

	
	/* return index_t methods */
	
	/*! \brief Returns the indices associated with the of the node_t */
	index_t getIndices();
	
	
	/* return point_t methods */
	
	/*! \brief Returns the coordinates associated with the node_t */
	point_t getCoordinates();
	

	
	/* friend methods */
	
	/*!\brief Friend function to send node_ts to streams 
	 * 
	 * node_ts are displayed as
	 * [node_t_number][node_t_indices](node_t_coordinates) node_t_value
	 *
	 * */
	friend	std::ostream& operator<<(std::ostream& outStream, node_t& nod);
};
