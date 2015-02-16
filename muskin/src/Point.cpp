#include "headers.hpp"


int_t node::siNumberOfNodes=0;

int main(void)
{
	////Point p;
	point_t v,t;
	index_t a={1,0,1};	

	for(int i=0;i<3;i++)
	{
	  v.push_back(i);
	}
	
	//t=(-1.23*v)+(2*v); //(v*v);

	////int_t node::siNumberOfNodes=0;

	//node nod1(v,{1,0,0},2.232);
	//std::cout << "there are " << node::getNumberOfNodes() << " nodes created\n";
	//node nod2(2*v,{0,1,0},2.232);
	//std::cout << "there are " << node::getNumberOfNodes() << " nodes created\n";
	//node nod3(3*v,{0,0,1},2.232);
	//std::cout << "there are " << node::getNumberOfNodes() << " nodes created\n";
	//node nod4(t,{1,1,0},2.232);
	//std::cout << "there are " << node::getNumberOfNodes() << " nodes created\n";

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

	//mesh cMesh;

	//cMesh.push_backBN(nod1);

	point_t pa,pb;

	pa.push_back(1);
	pa.push_back(0);
	pb.push_back(5);
	pb.push_back(10);

	//std::cout << "RangeA" <<  pa << std::endl;
	//std::cout << "RangeB" << pb << std::endl;

	index_t ia={40,50};

	//mesh aMesh(2,ia,pa,pb,"aMesh");
	//aMesh.createMeshXML();
	//aMesh.createMeshFile();
	//aMesh.createMeshPNG();

	//mesh bMesh(2,ia,pa,pb);
	//bMesh.createMeshFile();
	//bMesh.createMeshPNG();

	//mesh cMesh("cMesh.xml");
	//cMesh.setMeshName("cMesh");
	//cMesh.createMeshXML();
	
	//mesh dMesh, eMesh;
	//dMesh.createMeshXML();
	//dMesh.createMeshPNG();

	//eMesh.createMeshPNG();

	mesh fMesh("aMesh.xml"), eMesh("aMesh");
	//mesh fMesh(2,ia,pa,pb,"aMesh");
	//fMesh.createMeshJSON();
	//fMesh.createMeshXML();
	eMesh.createMeshPNG();
	//fMesh.createMeshFile("lordtod.msh");
	//fMesh.createMeshFile();
	exit(0);

}

