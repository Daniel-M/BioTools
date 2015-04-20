#include "headers.hpp"


int_t mesh_t::siMeshNumber=0;
int_t node_t::siNumberOfNodes=0;

int main(void)
{
	point_t pa,pb;
	index_t ia;

	pa = {0,0};
	pb = {1,0.5};
	ia = {50,50};

	//std::cout << "PointA" << pa << std::endl;
	//std::cout << "PointB" << pb  << std::endl;
	//std::cout << "Nodes IA" << ia  << std::endl;
	
	mesh_t mesh(2,ia,pa,pb);
	//mesh.createMeshFile();
	//mesh.createMeshPNG();
	mesh.createMeshJSON();
	std::cout << mesh << std::endl;

	exit(0);
}

