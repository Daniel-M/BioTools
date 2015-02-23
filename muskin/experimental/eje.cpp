#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "typedef.hpp"

#include "chem_t.hpp"
#include "system_t.hpp"
#include "voxel.hpp"

#include "chem_t.cpp"
#include "system_t.cpp"
#include "voxel.cpp"

int main(void)
{
	voxel v;

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

}
