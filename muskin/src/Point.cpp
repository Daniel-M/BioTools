#include "headers.hpp"


int_t mesh_t::siMeshNumber=0;
int_t node_t::siNumberOfNodes=0;

int main(void)
{
	////Point p;
	//point_t v,t;
	//index_t a={0,1};	

	//for(int i=0;i<3;i++)
	//{
	  //v.push_back(i);
	//}

	point_t pa,pb;
	index_t ia;

/*
	pa.push_back(0);
	pa.push_back(0);
	pb.push_back(1);
	pb.push_back(0.5);
*/
	pa = {0,0};
	pb = {1,0.5};
	ia = {50,50};

	std::cout << "PointA" << pa << std::endl;
	std::cout << "PointB" << pb  << std::endl;
	std::cout << "Nodes IA" << ia  << std::endl;
	
	mesh_t emesh(2,ia,pa,pb,"emesh");
	emesh.createMeshFile();
	emesh.createMeshPNG();
	emesh.createMeshJSON();
	std::cout << emesh << std::endl;

	mesh_t test_mesh("mesh.json");

	std::cout << test_mesh << std::endl;
	
	test_mesh.createMeshFile();
	test_mesh.createMeshPNG();
	test_mesh.createMeshJSON();
	
	exit(0);
}

