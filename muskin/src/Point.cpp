#include "headers.hpp"


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
	
	//t=(-1.23*v)+(2*v); //(v*v);

	////int_t node_t::siNumberOfnode_ts=0;

	//node_t nod1(v,{1,0,0},2.232);
	//std::cout << "there are " << node_t::getNumberOfnode_ts() << " node_ts created\n";
	//node_t nod2(2*v,{0,1,0},2.232);
	//std::cout << "there are " << node_t::getNumberOfnode_ts() << " node_ts created\n";
	//node_t nod3(3*v,{0,0,1},2.232);
	//std::cout << "there are " << node_t::getNumberOfnode_ts() << " node_ts created\n";
	//node_t nod4(t,{1,1,0},2.232);
	//std::cout << "there are " << node_t::getNumberOfnode_ts() << " node_ts created\n";

	//index_t b={1,0,0}, c={1,1,0};

	//if(b != c)
	//{
		//std::cout << "Hey!!, Listen!!" << std::endl;
	//}
	//else
	//{
		//std::cout << "Hey!!, Dont Listen!!" << std::endl;
	//}

	//std::cout << a << std::endl;
	//std::cout << v << std::endl;
	//std::cout << nod1 << std::endl;
	//double val=10.1;
	//
	//nod1 = val;
	//std::cout << nod1 << std::endl;
	//
	//a={1,1,0};
	//nod1 = a;

	//std::cout << nod1 << std::endl;

	//std::cout << nod2 << std::endl;
	//std::cout << nod3 << std::endl;
	//std::cout << nod4 << std::endl;

	//mesh_t cmesh_t;

	//cmesh_t.push_backBN(nod1);

	point_t pa,pb;

	pa.push_back(1);
	pa.push_back(0);
	pb.push_back(5);
	pb.push_back(10);

	//std::cout << "RangeA" <<  pa << std::endl;
	//std::cout << "RangeB" << pb << std::endl;

	index_t ia={40,50};

	//mesh_t amesh_t(2,ia,pa,pb,"amesh_t");
	//amesh_t.createmesh_tXML();
	//amesh_t.createmesh_tFile();
	//amesh_t.createmesh_tPNG();

	//mesh_t bmesh_t(2,ia,pa,pb);
	//bmesh_t.createmesh_tFile();
	//bmesh_t.createmesh_tPNG();

	//mesh_t cmesh_t("cmesh_t.xml");
	//cmesh_t.setmesh_tName("cmesh_t");
	//cmesh_t.createmesh_tXML();
	
	//mesh_t dmesh_t, emesh_t;
	//dmesh_t.createmesh_tXML();
	//dmesh_t.createmesh_tPNG();

	//emesh_t.createmesh_tPNG();

	//mesh_t fmesh_t("amesh_t.xml"), emesh_t("amesh_t");
	//mesh_t  emesh_t("amesh_t");
	mesh_t emesh_t(2,ia,pa,pb,"amesh_t");
	emesh_t.createMeshJSON();
	//emesh_t.createmesh_tPNG();

	std::cout << a << std::endl;

	node_t temp = emesh_t[{0,1}];

	std::cout << temp << std::endl;
	
	emesh_t[{0,1}] = 3.1415;
	
	std::cout << emesh_t[{0,1}].getValue() << std::endl;

	//emesh_t[a] = 3.1415;
	
	temp = emesh_t[a];

	std::cout << temp << std::endl;

	
	//fmesh_t.createmesh_tFile("lordtod.msh");
	//fmesh_t.createmesh_tFile();
	exit(0);

}

