//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <cmath>

//#include <boost/numeric/ublas/vector.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>

#include "incluidos.hpp"
//#include "getSimpleReactions.hpp"
//#include "overloadedMatrix.hpp"

//using namespace std;

int main(void)
{
	std::fstream fsInput;
	fsInput.open("text.txt",std::fstream::in);

	std::fstream fsOutput;
	fsOutput.open("text-parsed.txt",std::ios::in | std::ios::out | std::ios::trunc);

	std::vector<std::string> vsSimpleReactions;

	std::map<std::string,int> mSpecies;
	std::map<std::string,int>::iterator iTmSpecies;
	std::string sLine;

	if(fsInput.is_open() && fsOutput.is_open())
	{

		while(fsInput.eof()!=true)
		{
			std::getline(fsInput,sLine);

			if(sLine!="")
			{
				getSimpleReactions(sLine,vsSimpleReactions);
			}
		}

		fsInput.close();


		for(int i=0;i<vsSimpleReactions.size();i++)
		{
			fsOutput << vsSimpleReactions[i] << std::endl;
		}

		fsOutput.seekg(fsOutput.beg);

		while(fsOutput.eof()!=true)
		{
			std::getline(fsOutput,sLine);

			if(sLine!="")
			{
				getSpeciesMap(">",sLine,mSpecies);
			}
		}

			

		for(iTmSpecies=mSpecies.begin();iTmSpecies != mSpecies.end();iTmSpecies++)
		{
			std::cout << " Key " << iTmSpecies->first << " Value " << iTmSpecies->second << std::endl;
		}


	}

	fsOutput.close();
    
	boost::numeric::ublas::matrix<int> cN;
	//boost::numeric::ublas::matrix<std::string> V;

	//getReactionMatrix(vsSimpleReactions,mSpecies,cN);


	//std::fstream fsOutputEqn;
	fsOutput.open("text-equations.txt",std::ios::in | std::ios::out | std::ios::trunc);

	std::map<std::string,std::string> mKinetics;
	std::map<std::string,std::string>::iterator iTKin;
	std::vector<std::string> vsR;

	//std::map<std::string,std::string> mSpeciesKin(getMassActionLawEquations(vsSimpleReactions,mSpecies));
	std::map<std::string,std::string> mSpeciesKin(getMassActionLawEquations(vsSimpleReactions,mSpecies,cN));

	std::cout << "Reaction Matrix is\n";
	std::cout << cN;
	std::cout << "\n\n";

	if(fsOutput.is_open())
	{ 
		for(iTKin=mSpeciesKin.begin();iTKin != mSpeciesKin.end();iTKin++)
		{
			std::cout << "For " << iTKin->first << " the equation is " << iTKin->second << std::endl;
			fsOutput << iTKin->second << ";" << std::endl;
		}
	}
	
	fsOutput.close();

	return 0;
}
