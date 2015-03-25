#include "headers.hpp"


int_t mesh_t::siMeshNumber=0;
int_t node_t::siNumberOfNodes=0;

int main(void)
{
	////Point p;
	point_t v,t;
	index_t a={0,1};	

	for(int i=0;i<3;i++)
	{
	  v.push_back(i);
	}
	

	point_t pa,pb;

	pa.push_back(1);
	pa.push_back(0);
	pb.push_back(5);
	pb.push_back(10);

	index_t ia={40,50};

	mesh_t emesh_t(2,ia,pa,pb,"amesh_t");
	emesh_t.createMeshJSON();

	std::cout << a << std::endl;

	node_t temp = emesh_t[{0,1}];

	std::cout << temp << std::endl;
	
	emesh_t[{0,1}] = 3.1415;
	
	std::cout << emesh_t[{0,1}].getValue() << std::endl;

	
	temp = emesh_t[a];

	std::cout << temp << std::endl;


	mesh_t other(0);
	other = emesh_t;
	temp = other[a];
	
	node_t testsum;

	std::cout << "Suma del nodo\n";
	std::cout << temp << std::endl;
	std::cout << "Sumas:\n";
	
	testsum = temp + temp;

	std::cout << testsum << std::endl;
	std::cout << temp << std::endl;
	//std::cout << temp+temp << std::endl;
	std::cout << "Multiplicación:\n";
	std::cout << testsum << std::endl;
	temp = (1.0/3.0)*testsum;
	std::cout << testsum << std::endl;
	std::cout << temp << std::endl;

	temp = (1.0/3.0)*testsum + 2*testsum;
	std::cout << temp << std::endl;


	mesh_t testmesh, buffer(0);

	buffer = iterateFD(testmesh,0.001);

	exit(0);
}

