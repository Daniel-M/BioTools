#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

void calculateKD(double A1, double A2, double x0, double dx, double A1_Error, double A2_Error, double x0_Error, double dx_Error,double* Kd,double *Kderror)
{
	double t1,t2,t3;

	t1 = (dx * A1_Error)/(A1-0.5);
	t2 = ((A1-A2)*A2_Error)/(0.5*(A1-A2-0.5)+A2*(1.0-A1));
	t3 = log(((A1-A2)/(0.5-A2)) - 1.0)*dx_Error;

	*Kd=1.0/(pow(10.0,dx*log10((A1-A2)/(0.5-A2)-1.0)+x0));

	*Kderror= -log(10.0)*(*Kd)*(t1+t2+t3+x0_Error);
}


