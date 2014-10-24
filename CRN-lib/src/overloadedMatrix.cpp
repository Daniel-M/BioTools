//#include <iostream>
//#include <vector>
//#include <string>

//#include "overloadedMatrix.hpp"
#include "incluidos.hpp"

int main()
{
	//Matrix<double> m (3, 3);
	//Matrix<std::string> ms (3, 3);
	boost::numeric::ublas::matrix<double> m (2,2);
	boost::numeric::ublas::matrix<std::string> ms (2,2);

    for (int i = 0; i < m.size1 (); ++ i)
    {
        for (int j = 0; j < m.size2 (); ++ j)
        {
            m (i, j) = i-2*j;
        }
    }
	
	ms(0,0)="a";
    ms(0,1)="b";
    ms(1,0)="c";
    ms(1,1)="d";

    //ms(0,0)="a";
    //ms(0,1)="b";
    //ms(0,2)="c";
    //ms(1,0)="d";
    //ms(1,1)="e";
    //ms(1,2)="f";
    //ms(2,0)="g";
    //ms(2,1)="h";
    //ms(2,2)="i";
	
	std::cout << m << std::endl;
	std::cout << ms << "\n" << std::endl;

	//Matrix<std::string> mr1(m*ms);
	//Matrix<std::string> mr2(ms*m);
	boost::numeric::ublas::matrix<std::string> mr1(m*ms);
	boost::numeric::ublas::matrix<std::string> mr2(ms*m);

	std::cout << m*ms << std::endl;
	std::cout << ms*m << std::endl;

	std::cout << "\n" << std::endl;

	std::cout << mr1 << std::endl;
	std::cout << mr2 << std::endl;

	std::vector<double> viVector;

	viVector.push_back(1);
	viVector.push_back(1);
	
	
	std::cout << m + viVector << std::endl;

}


