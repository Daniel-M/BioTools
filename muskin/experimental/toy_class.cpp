#include <iostream>
#include <string>
#include <vector>
//#include <set>
//#include <map>

#include <boost/numeric/odeint.hpp>

#include "typedef.hpp"

typedef std::vector< double > state_type;
using namespace boost::numeric::odeint;

double gam = 0.15;

class Toy
{
	private:
		int_t (*ptrFunction)(double x, double y, double z);
		void (*ptrSystem)( const state_type&, state_type& , const double /* t */ );

	public:
		Toy();
		Toy(int_t (*ptrFunc)(double, double, double));
		void setFunction(int_t (*ptrFunc)(double x, double y, double z));
		int_t evalFunction(double x, double y, double z);
		
		void setSystem(void (*ptrSys)( const state_type&, state_type& , const double /* t */ ));
		void evalSystem(state_type& x, double t, double dt);
		//state_type evalSystem(state_type& x, double t, double dt);
};

Toy::Toy()
{
}

Toy::Toy(int_t (*ptrFunc)(double, double, double))
{
	ptrFunction = ptrFunc;
}

void Toy::setFunction(int_t (*ptrFunc)(double , double , double ))
{
	ptrFunction = ptrFunc;
}

int_t Toy::evalFunction(double x, double y, double z)
{
	return (*ptrFunction)(x,y,z);
}

void Toy::setSystem(void (*ptrSys)( const state_type&, state_type& , const double /* t */ ))
{
	ptrSystem = ptrSys;
}

void Toy::evalSystem(state_type& x,double t, double dt)
//state_type Toy::evalSystem(state_type& x,double t, double dt)
{
	runge_kutta4< state_type > rk;
	rk.do_step( ptrSystem , x , t , dt ); 
	//return x
}


// ****************************************
// ****************************************
// ****************************************


int_t function1(double x, double y, double z)
{
	std::cout << " x " << x << std::endl;
	std::cout << " y " << y << std::endl;
	std::cout << " z " << z << std::endl;
	std::cout << "Hey MOFO, it worked!" << std::endl;

	return 1;
}

int_t function2(double x, double y, double z)
{
	std::cout << " 2x " << 2*x << std::endl;
	std::cout << " 2y " << 2*y << std::endl;
	std::cout << " 2z " << 2*z << std::endl;
	std::cout << "Hey MOFO, it worked!" << std::endl;

	return 1;
}


/* The rhs of x' = f(x) */
void harmonic_oscillator( const state_type &x , state_type &dxdt , const double /* t */ )
{
	    dxdt[0] = x[1];
	    dxdt[1] = -x[0] - gam*x[1];
}




int main(void)
{
	Toy object(function1);
	object.evalFunction(1,2,3);

	object.setFunction(function2);
	object.evalFunction(1,2,3);
	
	state_type x(2);
	x[0] = 1.0; // start at x=1.0, p=0.0
	x[1] = 0.0;
	
	std::cout << x[0] << "\t" << x[1] << std::endl;

	object.setSystem(harmonic_oscillator);
	
	double t(0),dt(0.01);
	
	while(t < 10.0)
	{
		object.evalSystem(x,t,dt);
		t+=dt;
		std::cout <<  x[0] << "\t" << x[1] << std::endl;
	}


}
