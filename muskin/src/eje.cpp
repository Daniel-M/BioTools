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
	    dxdt[0] = x[1];
	    dxdt[1] = -x[0] + 0.15*x[1]-0.02*x[2];
		dxdt[2]= +x[1] - 0.15*x[0]+0.02*x[2];
}

void system3( const point_t &x , point_t &dxdt , const double /* t */ )
{
	    dxdt[0] = x[1]+0.1*x[2];
	    dxdt[1] = 2*x[1] - 0.5*x[0]+0.03*x[2];
		dxdt[2]= -x[0] - 0.05*x[1]+0.5*x[2];
}

int main(void)
{
	//voxel_t v;
	//voxel_t v(system1);
	voxel_t v;
	
	std::cout << "System " << v.getSystem() << "\n";
	std::cout << "System " << v.getSystem() << "\n";
	std::cout << "System " << v.getSystem() << "\n";
	std::cout << "System " << v.getSystem() << "\n";

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
	
	v.setSystem(system1);
	
	//v=system1;

	std::cout << "#System1" << std::endl;
	std::cout << "System " << v.getSystem() << "\n";

	while(t < 50)
	{
	  v.evalSystem(data,t,dt);
	  t+=dt;
	  //std::cout << data << "\n";
	  //std::cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\n";
	}


	std::cout << "System " << v.getSystem() << "\n";

	//v=system2;
	std::cout << "#System2" << std::endl;
	v.setSystem(system2);
	std::cout << "#System2" << std::endl;

	std::cout << "System " << v.getSystem() << "\n";

	t=0;
	dt=0.01;
	
	data.clear();

	data[0] = 1.0;
	data[1] = 0.1;
	data[2] = 0.01;
	
	std::cout << "#System2" << std::endl;

	while(t < 50)
	{
	  std::cout << "#System2-w1" << std::endl;
	  v.evalSystem(data,t,dt);
	  std::cout << "#System2-w2" << std::endl;
	  t+=dt;
	  //std::cout << data << "\n";
	  std::cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\n";
	}

	v.setSystem(system3);

	t=0;
	
	data.clear();

	data[0] = 1.0;
	data[1] = 0.1;
	data[2] = 0.01;
	
	std::cout << "#System3" << std::endl;

	while(t < 50)
	{
	  v.evalSystem(data,t,dt);
	  t+=dt;
	  //std::cout << data << "\n";
	  std::cout << data[0] << "\t" << data[1] << "\t" << data[2] << "\n";
	}
}
