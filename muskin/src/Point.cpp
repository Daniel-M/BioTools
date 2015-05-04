#include "headers.hpp"
#include <cmath>


int_t mesh_t::siMeshNumber=0;
int_t node_t::siNumberOfNodes=0;

floating_t func(const point_t& pt)
{
	return exp(-(pow(0.5-pt[0],2)))*exp(-(pow(0.5-pt[1],2)));
}

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
	pb = {1,1};
	ia = {50,50};

	floating_t dt = pow(pb[1]/ia[1],2)/5;

	//std::cout << "PointA" << pa << std::endl;
	//std::cout << "PointB" << pb  << std::endl;
	//std::cout << "Nodes IA" << ia  << std::endl;
	
	int i(0);
	std::string filename;

	mesh_t bmesh;
	mesh_t emesh(2,ia,pa,pb,"emesh",func);
	
	filename = "result_mesh-t"+NumberToString(i);

	emesh.createMeshValuesFile(filename);

	//i++;

	for(i=1;i<=2000;i++)
	{
		filename = "result_mesh-t"+NumberToString(i);
		
		bmesh = Cartesian_Coordinates::IterateFD(emesh,dt);
		
		bmesh.createMeshValuesFile(filename);
		
		//std::cout << " i-th mesh " << i << std::endl;

		emesh = bmesh;
	}
	
	exit(0);
}

