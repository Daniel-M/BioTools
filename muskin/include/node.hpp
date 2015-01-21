//#include "headers.hpp"

class node
{
	private:
	
	static int_t siNumberOfNodes;
	int_t iNodeNumber;
	index_t ntIndices;
	point_t ptCoordinates;
	double dNodeValue;

	node(){};

	public:

	static int_t getNumberOfNodes();
		
	node(point_t coords, index_t indices, double value);
	
	int_t size();
	
	int_t getNodeNumber();
	
	index_t getIndices();
	
	point_t getCoordinates();
	
	friend	std::ostream& operator<<(std::ostream& outStream, node& nod);
};
