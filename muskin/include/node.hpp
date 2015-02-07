//#include "headers.hpp"

class node
{
	private:
	
	static int_t siNumberOfNodes; /*!< Stores the number of nodes created as objects, this variable is for debuggin but can be exploited as you wish*/
	int_t itNodeNumber;
	index_t itIndices;
	point_t ptCoordinates;
	double dNodeValue;

	//node(){};

	public:

	
	/*! \brief Standard node constructor
	 *
	 * Creates a void node but increases the node number static variable*/
	node();
	
	/*!* \brief Node constructor using the coordinates, indices, and the stored value 
	 * 
	 * \param coords coordinates of the node.
	 * \param indices indices of the node.
	 * \param value value stored at the node.
	 * */
	node(point_t coords, index_t indices, double value);

	/*! \brief Overloaded operator= to set the node value directly 
	 *
	 * This operator modifies the left-hand side node
	 *
	 * \param dValue_ the value to be assigned into the node.
	 * */
	node& operator=(const double dValue_);
	//{
		//dNodeValue=dValue_;
	//};
	
	/*! \brief Overloaded operator= to set the node index directly. 
	 * 
	 * This operator modifies the left-hand side node
	 *
	 * \param itIndex_ the new indices set for the node.
	 * */
	node& operator=(const index_t itIndex_);
	//{
		//itIndices = itIndex_;
	//};

	/*! \brief Set node parameters as if where with the constructor
	 *
	* \param coords coordinates of the node.
	* \param indices indices of the node.
	* \param value value stored at the node. 
	* */
	void setNode(point_t coords, index_t indices, double value);
	
	/*!*/
	//void setValue(index_t iIndex);
	/*!*/
	//void setIndex(index_t iIndex);
	
	/*!*/
	//static int_t getNumberOfNodes();
	
	/*! \brief Returns the number of nodes created appealing to an static variable */
	int_t getNumberOfNodes();

	/*! \brief Returns the value stored on the node*/
	double getValue();
	
	/*! \brief Returns the dimensions of the node e.g. a 2D mesh uses 2D nodes*/
	int_t getDimension();
	
	/*! \brief Returns the number assigned to the node */
	int_t getNodeNumber();
	
	/*! \brief Returns the indices associated with the of the node*/
	index_t getIndices();
	
	/*! \brief Returns the coordinates associated with the node */
	point_t getCoordinates();
	
	/*!\brief Friend function to send nodes to streams 
	 * 
	 * Nodes are displayed as
	 * [node_number][node_indices](node_coordinates) node_value
	 *
	 * */
	friend	std::ostream& operator<<(std::ostream& outStream, node& nod);
};
