#include "headers.hpp"
//#include <iostream>
typedef double (*condition_t)( const point_t& ); /*!< A Pointer to initial condition functions. */

double func(const point_t punto)
{
	return punto[0]*punto[1];
}

int main(void)
{
	condition_t ptrFunc = func;	
}
