#include "headers.hpp"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <set>
//#include <map>

//#include "typedef.hpp"

//#include "chem_t.hpp"
//#include "voxel_t.hpp"

//#include "chem_t.cpp"
//#include "voxel_t.cpp"

void system1( const point_t &x , point_t &dxdt , const double /* t */ )
{
	    dxdt[0] = x[1];
	    dxdt[1] = -x[0] - 0.15*x[1]+0.02*x[2];
		dxdt[2]= -x[1] - 0.15*x[0]+0.02*x[2];
}

void system2( const point_t &x , point_t &dxdt , const double /* t */ )
{
	    dxdt[0] = x[1]+0.01;
	    dxdt[1] = -x[0] + 0.15*x[1]-0.02*x[2];
		dxdt[2]= +x[1] - 0.15*x[0]+0.02*x[2];
}

void system3( const point_t &x , point_t &dxdt , const double /* t */ )
{
	    dxdt[0] = x[1];
	    dxdt[1] = x[1] - 0.15*x[0]+0.02*x[2];
		dxdt[2]= -x[0] - 0.15*x[1]+0.02*x[2];
}

int main(void)
{
	//voxel_t v;
	voxel_t v(system1);

	chem_t c;

	c = 10;

	double var(0);

	var = c.getValue();

	std::cout << var  << std::endl;
	
	c.setValue(10);

	//var = c.getValue();
	
	c=11;
	var = c;

	std::cout << var  << std::endl;

	//point_t data(3);
	std::vector<chem_t> data(3);
	double t(0),dt(0.01);
	data[0] = 1.0;
	data[1] = 0.1;
	data[2] = 0.01;
	
	//v.setSystem(system1);
	
	//v=system1;

	while(t < 50)
	{
	  v.evalSystem(data,t,dt);
	  t+=dt;
	  //std::cout << data << "\n";
	  std::cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\n";
	}

	//index_t idx1({1,0,0}),idx2({0,1,0}),idx3({1,0,0}),idx4(idx1+idx2),idx5(idx2+idx3);

	//std::set<index_t> sidx1,sidx2,sidx3;

	//sidx1.insert(idx1);
	//sidx1.insert(idx2);
	//sidx1.insert(idx5);

	//sidx2.insert(idx1);
	//sidx2.insert(idx4);
	//sidx2.insert(idx3);

	//sidx3.insert(idx4);
	//sidx3.insert(idx5);

	//voxel_t v1(sidx1,system1),v2(sidx2,system2),v3(sidx3,system3);

	//v1.setSystem(system1);
	//v2.setSystem(system2);
	//v3.setSystem(system3);

	//if(v1.count(idx3) > 0 )
	//{
	
		//data.clear();
		//data[0] = 1.0;
		//data[1] = 0.1;
		//data[2] = 0.01;
		//t=0;
		//while(t< 100)
		//{
		  //v1.evalSystem(data,t,dt);
		  //t+=dt;
		  //std::cout << data << "\n";
		//}
	//}
	//else if(v2.count(idx3) > 0 )
	//{
		//data.clear();
		//data[0] = 1.0;
		//data[1] = 0.1;
		//data[2] = 0.01;

		//t=0;
		//while(t< 100)
		//{
		  //v2.evalSystem(data,t,dt);
		  //t+=dt;
		  //std::cout << data << "\n";
		//}
	//}
	//else if (v3.count(idx3) > 0) 
	//{
		//data.clear();
		//data[0] = 1.0;
		//data[1] = 0.1;
		//data[2] = 0.01;

		//t=0;
		//while(t< 100)
		//{
		  //v3.evalSystem(data,t,dt);
		  //t+=dt;
		  //std::cout << data << "\n";
		//}
	//}
}
