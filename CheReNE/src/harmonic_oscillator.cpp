/*
 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#include <iostream>
#include <vector>

#include <boost/numeric/odeint.hpp>



//[ rhs_function
/* The type of container used to hold the state vector */
typedef std::vector< double > state_type;

const double gam = 0.15;

/* The rhs of x' = f(x) */
void harmonic_oscillator( const state_type &x , state_type &dxdt , const double /* t */ )
{
    dxdt[0] = x[1];
    dxdt[1] = -x[0] - gam*x[1];
}

struct push_back_state_and_time
{
	//std::vector< state_type >& m_states;
	//std::vector< double >& m_times;

	//push_back_state_and_time( std::vector< state_type > &states , std::vector< double > &times )
	//: m_states( states ) , m_times( times ) { }

	push_back_state_and_time( state_type &x , double &times ){ }

	void operator()( const state_type &x , double t )
    {
		//m_states.push_back( x );
		//m_times.push_back( t );
		std::cout << t;
		
		for(int j=0; j<x.size();j++)
		{
			std::cout << "\t" <<  x[j] ;
		}
    	
		 std::cout << "\n" ;
	}
};

int main()
{
	state_type x = {1,0};
	boost::numeric::odeint::runge_kutta4 < state_type > stepper;
	//boost::numeric::odeint::integrate( harmonic_oscillator , x , 0.0 , 10.0 , 0.01 );
	//boost::numeric::odeint::integrate_const(stepper, harmonic_oscillator , x , 0.0 , 10.0 , 0.01 );
	
	//std::vector<state_type> x_vec;
	//std::vector<double> times;
	double time;
	
	size_t steps;

    steps =	boost::numeric::odeint::integrate_const(stepper, harmonic_oscillator , x , 0.0 , 70.0 , 0.01,
            push_back_state_and_time( x , time ) );

    //steps =	boost::numeric::odeint::integrate_const(stepper, harmonic_oscillator , x , 0.0 , 70.0 , 0.01,
            //push_back_state_and_time( x_vec , times ) );
    /* output */
    /*
	for( size_t i=0; i<=steps; i++ )
    {
		std::cout << times[i] << '\t' << x_vec[i][0] << '\t' << x_vec[i][1] << '\n';
        //std::cout << times[i] << "\t";
		//show_stats(i,x_vec);
		//std::cout << "\n";
    } */
	
	return 0;
}
