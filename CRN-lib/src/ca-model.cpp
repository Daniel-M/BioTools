/*
 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#include <iostream>
#include <vector>
#include <cmath>

#include <boost/numeric/odeint.hpp>



/*
 * Key CA.T_SITE Value 0
 * Key CA Value 1
 * Key T_SITE Value 2
 * Key MG.T_SITE Value 3
 * Key MG Value 4
 * Key CA.P_SITE Value 5
 * Key P_SITE Value 6
 * Key MG.P_SITE Value 7
 * Key CA.SR Value 8
 * Key SR Value 9
 */

//[ rhs_function
/* The type of container used to hold the state vector */
typedef std::vector< double > state_type;

const double final_time(15e-3);
const double dt(final_time/1e3);

//const std::vector < double > k = {1e8,31.62,39810.72,199.53,1e8,1,39810.72,1e6,0.75e-6,0.375e-6,0.75e-6};
//const std::vector < double > x0 = {0,200e-6,140e-6,0,3e-3,0,140e-6,0,0,150e-6};
const std::vector < double > k = {1e8,31.62,39810.72,199.53,1e8,1,39810.72,3.16,7.5,3,3};
const std::vector < double > x0 = {0,200e-6,140e-6,0,3e-4,0,140e-6,0,0,150e-6};
const double amp=0.4*x0[1];
const double A(1.1525), B(0.1525),alpha(6e-3),beta(0.8e-3);

/* The rhs of x' = f(x) */
void ca_model_eqns( /*const*/ state_type &x , state_type &dxdt , const double t )
{
	x[1] = x[1] + amp*(1-A*exp(-t/alpha)+B*exp(-t/beta));
	dxdt[1] = -k[0]*x[1]*x[2]+k[1]*x[0]-k[4]*x[1]*x[6]+k[5]*x[5]-k[8]*x[1]*x[9]+k[10]*x[8];
	dxdt[5] = k[4]*x[1]*x[6]-k[5]*x[5];
	dxdt[8] = k[8]*x[1]*x[9]-k[9]*x[8]-k[10]*x[8];
	dxdt[0] = k[0]*x[1]*x[2]-k[1]*x[0];
	dxdt[4] = -k[2]*x[4]*x[2]+k[3]*x[3]-k[6]*x[4]*x[6]+k[7]*x[7];
	dxdt[7] = k[6]*x[4]*x[6]-k[7]*x[7];
	dxdt[3] = k[2]*x[4]*x[2]-k[3]*x[3];
	dxdt[6] = -k[4]*x[1]*x[6]+k[5]*x[5]-k[6]*x[4]*x[6]+k[7]*x[7];
	dxdt[9] = -k[8]*x[1]*x[9]+k[9]*x[8]+k[10]*x[8];
	dxdt[2] = -k[0]*x[1]*x[2]+k[1]*x[0]-k[2]*x[4]*x[2]+k[3]*x[3];
}

struct push_back_state_and_time
{
	push_back_state_and_time( state_type &species , double &times ){ }

	void operator()( const state_type &species , double t )
    {
		std::cout << t;
		
		for(int j=0; j<species.size();j++)
		{
			std::cout << "\t" <<  species[j] ;
		}
    	
		std::cout << "\n" ;
	}
};

int main()
{
	state_type species = x0;
	//boost::numeric::odeint::runge_kutta4 < state_type > stepper;
	boost::numeric::odeint::bulirsch_stoer < state_type > stepper;
	double time;
	
	size_t steps;

    //steps =	boost::numeric::odeint::integrate_const(stepper, ca_model_eqns , species , 0.0 , final_time , dt,
            //push_back_state_and_time( species , time ) );
	steps =	boost::numeric::odeint::integrate_adaptive(stepper, ca_model_eqns , species , 0.0 , final_time , dt,
            push_back_state_and_time( species , time ) );
	
	return 0;
}
