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
	    dxdt[0] = x[1]+0.1*x[2];
	    dxdt[1] = 2*x[1] - 0.5*x[0]+0.03*x[2];
		dxdt[2]= -x[0] - 0.05*x[1]+0.5*x[2];
}

int main(void)
{
	std::cout << "Welcome to the chem_vector_t and voxel tester\n";
	double t(0), dt=0.01;

	voxel_t v1(system1),v2(system2);
	
	std::cout << "Voxel_t variables where defined and initialized\n";

	chem_vector_t data1(3), data2(3);
	
	std::cout << "chem_vector_t variables where defined\n";

	data1[0] = 1.0;
	data1[1] = 0.1;
	data1[2] = 0.01;

	data2[0] = 1.0;
	data2[1] = 0.1;
	data2[2] = 0.01;
	
	std::cout << "chem_vector_t variables where initialized\n";

	std::cout << "Variables where defined and initialized\n";

	while(t < 50)
	{

	  v1.evalSystem(data1,t,dt);
	  v2.evalSystem(data2,t,dt);

	  t+=dt;
	  
	  //std::cout << data << "\n";
	  //std::cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\n";
	  std::cout << t << "\t" << data1[0] << "\t" << data1[1] << "\t" << data1[2] << "\t\t" << data2[0] << "\t" << data2[1] << "\t" << data2[2] << "\n";
	}
}
