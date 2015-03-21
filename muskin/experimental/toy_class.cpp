#include <iostream>
#include <string>
#include <vector>
//#include <set>
//#include <map>

#include <boost/numeric/odeint.hpp>

#include "typedef.hpp"

typedef std::vector< floating_t > state_type;
typedef void (*system_t)( const point_t&, point_t& , const floating_t /* t */ );
using namespace boost::numeric::odeint;

floating_t gam = 0.15;

class Toy
{
	private:
		int_t (*ptrFunction)(floating_t x, floating_t y, floating_t z);
		system_t ptrSystem;
		//void (*ptrSystem)( const state_type&, state_type& , const floating_t /* t */ );

	public:
		Toy();
		Toy(int_t (*ptrFunc)(floating_t, floating_t, floating_t));
		void setFunction(int_t (*ptrFunc)(floating_t x, floating_t y, floating_t z));
		int_t evalFunction(floating_t x, floating_t y, floating_t z);
		
		//void setSystem(void (*ptrSys)( const state_type&, state_type& , const floating_t /* t */ ));
		void setSystem(system_t ptrSys);
		void evalSystem(state_type& x, floating_t t, floating_t dt);
		//state_type evalSystem(state_type& x, floating_t t, floating_t dt);
};

Toy::Toy()
{
}

Toy::Toy(int_t (*ptrFunc)(floating_t, floating_t, floating_t))
{
	ptrFunction = ptrFunc;
}

void Toy::setFunction(int_t (*ptrFunc)(floating_t , floating_t , floating_t ))
{
	ptrFunction = ptrFunc;
}

int_t Toy::evalFunction(floating_t x, floating_t y, floating_t z)
{
	return (*ptrFunction)(x,y,z);
}

//void Toy::setSystem(void (*ptrSys)( const state_type&, state_type& , const floating_t /* t */ ))
void Toy::setSystem(system_t ptrSys)
{
	ptrSystem = ptrSys;
}

void Toy::evalSystem(state_type& x,floating_t t, floating_t dt)
//state_type Toy::evalSystem(state_type& x,floating_t t, floating_t dt)
{
	runge_kutta4< state_type > rk;
	rk.do_step( ptrSystem , x , t , dt ); 
	//return x
}


// ****************************************
// ****************************************
// ****************************************


int_t function1(floating_t x, floating_t y, floating_t z)
{
	std::cout << " x " << x << std::endl;
	std::cout << " y " << y << std::endl;
	std::cout << " z " << z << std::endl;
	std::cout << "Hey MOFO, it worked!" << std::endl;

	return 1;
}

int_t function2(floating_t x, floating_t y, floating_t z)
{
	std::cout << " 2x " << 2*x << std::endl;
	std::cout << " 2y " << 2*y << std::endl;
	std::cout << " 2z " << 2*z << std::endl;
	std::cout << "Hey MOFO, it worked!" << std::endl;

	return 1;
}


/* The rhs of x' = f(x) */
void harmonic_oscillator( const state_type &x , state_type &dxdt , const floating_t /* t */ )
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
	
	floating_t t(0),dt(0.01);
	
	while(t < 10.0)
	{
		object.evalSystem(x,t,dt);
		t+=dt;
		std::cout <<  x[0] << "\t" << x[1] << std::endl;
	}


}
