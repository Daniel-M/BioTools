#include <iostream>
#include <vector>

typedef std::vector<double> point_t;

typedef double (*function_t)( const point_t& ); /*!< A Pointer to initial condition functions. */

double func(const point_t& punto)
{
	return punto[0]*punto[1];
}

int main(void)
{
	point_t vect={2,1};
	function_t ptrFunc = func;	

	double res;

	res = (*ptrFunc)(vect);

	std::cout << res << std::endl;

	exit(0);


}
