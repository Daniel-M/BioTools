#include "kd-calculator.hpp"


int main(int argc,char **argv)
{
	std::string fParameterFileName;
	
	if(argc < 2)
	{
		fParameterFileName = "kd_params.txt";
		std::cout << "Loading file " << fParameterFileName << std::endl;
	}
	else
	{
		fParameterFileName = argv[1];
		std::cout << "Loading file " << fParameterFileName << std::endl;
	}

	std::fstream fParameterInputFile;
	fParameterInputFile.open(fParameterFileName.c_str(),std::fstream::in);

	std::string sLine;

	double dParameter_A1(0),dParameter_A2(0),dParameter_dx(0),dParameter_x0(0);
	double dParameter_A1_Error(0),dParameter_A2_Error(0),dParameter_dx_Error(0),dParameter_x0_Error(0);

	double k,ke;
	int iParameterNumber(0);

	if(fParameterInputFile.is_open())
	{

		while(fParameterInputFile.eof()!=true)
		{
			std::getline(fParameterInputFile,sLine);

			if(sLine.substr(0,2)=="A1")
			{
				dParameter_A1 = atof(sLine.substr(3,-1).c_str());
				std::cout << "A1 = " <<  dParameter_A1 << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,3)=="dA1")
			{
				dParameter_A1_Error = atof(sLine.substr(4,-1).c_str());
				std::cout << "dA1 = " << dParameter_A1_Error << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,2)=="A2")
			{

				dParameter_A2 = atof(sLine.substr(3,-1).c_str());
				std::cout << "A2 = " << dParameter_A2 << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,3)=="dA2")
			{

				dParameter_A2_Error = atof(sLine.substr(4,-1).c_str());
				std::cout << "dA2 = " << dParameter_A2_Error << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,2)=="x0")
			{

				dParameter_x0 = atof(sLine.substr(3,-1).c_str());
				std::cout << "x0 = " << dParameter_x0 << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,3)=="dx0")
			{

				dParameter_x0_Error = atof(sLine.substr(4,-1).c_str());
				std::cout << "dx0 = " << dParameter_x0_Error << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,2)=="dx")
			{

				dParameter_dx = atof(sLine.substr(3,-1).c_str());
				std::cout << "dx = " << dParameter_dx << std::endl;
				iParameterNumber+=1;
			}
			else if(sLine.substr(0,3)=="ddx")
			{
				dParameter_dx_Error = atof(sLine.substr(4,-1).c_str());
				std::cout << "ddx = " << dParameter_dx_Error << std::endl;
				iParameterNumber+=1;
			}
			
		}

		fParameterInputFile.close();

		if( iParameterNumber < 8 )
		{
			std::cout << "Not enough parameters on file" << std::endl;
			return 1;
		}
		else
		{
			calculateKD(dParameter_A1,dParameter_A2,dParameter_x0,dParameter_dx,dParameter_A1_Error,dParameter_A2_Error,dParameter_x0_Error,dParameter_dx_Error,&k,&ke);

			std::cout << "Calculated Kd = " << k << " and error " << ke << std::endl;
			std::cout << "Porcentual error Kd_error/Kd = " << fabs(ke/k) << " Or " << fabs(100 *ke/k) << "\%" << std::endl;

			std::cout << " Kd beetween " << k-fabs(ke) << " and " << k+fabs(ke) << std::endl;
		}

	}
	else
	{
		std::cout << "File " << fParameterFileName << " not found!" << std::endl;
		
		return 1;
	}

	return 0;
}
