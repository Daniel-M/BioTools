//#include "headers.hpp"

class node
{
	private:
	
	static int_t siNumberOfNodes;
	int_t itNodeNumber;
	index_t itIndices;
	point_t ptCoordinates;
	double dNodeValue;

	//node(){};

	public:

	
	//
	node();
	
	//
	node(point_t coords, index_t indices, double value);

	// Overloaded operator= to set the node value directly
	node& operator=(const double dValue_)
	{
		dNodeValue=dValue_;
	};
	
	// Overloaded operator= to set the node index directly
	node& operator=(const index_t itIndex_)
	{
		itIndices = itIndex_;
	};

	// set node node
	void setNode(point_t coords, index_t indices, double value);
	//void setValue(index_t iIndex);
	//void setIndex(index_t iIndex);
	
	//static int_t getNumberOfNodes();
	//
	int_t getNumberOfNodes();

	//
	double getValue();
	//
	int_t size();
	
	//
	int_t getNodeNumber();
	
	//
	index_t getIndices();
	
	//
	point_t getCoordinates();
	
	//
	friend	std::ostream& operator<<(std::ostream& outStream, node& nod);
};
