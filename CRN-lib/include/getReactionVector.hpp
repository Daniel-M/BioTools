//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <cmath>

//#include <boost/numeric/ublas/vector.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>

#include "incluidos.hpp"

void getReactionVector(std::string sInput,std::map<std::string,int> mSpecies, std::vector< int >& viResult)
{
    
	
	///**
     //* La intención es que la input se divida en dos partes, puesto que solo llega dividida por ->
     //* luego, es preciso detectar las especies indicadas para construir el vector y'-y el cual será
     //* entregado en viResult, pasandolo por referencia, la idea es construir una matriz de reacciones
     //* tal como lo recomienda al artículo de Pablo Villosada de PLoS
     //**/
    
    
    std::vector<std::string> vsComplexBuffer;
    std::vector<std::string> vsLeftCompoundsBuffer;
    std::vector<std::string> vsRightCompoundsBuffer;
    std::vector<int> viReactants;
    std::vector<int> viProducts;
    
    viReactants.resize(viResult.size());
    viProducts.resize(viResult.size());
    
    int iStoichometricCoefficient=1;
    
	boost::algorithm::erase_all(sInput,"-");
	boost::algorithm::split(vsComplexBuffer,sInput,boost::algorithm::is_any_of(">"));
    
	for(int i=0;i!=vsComplexBuffer.size();i++)
    {
    	std::cout << vsComplexBuffer[i] << std::endl;
    }

	boost::algorithm::split(vsRightCompoundsBuffer,vsComplexBuffer[0],boost::algorithm::is_any_of("+"));
	boost::algorithm::split(vsLeftCompoundsBuffer,vsComplexBuffer[1],boost::algorithm::is_any_of("+"));
    
    for(int i=0;i!=vsRightCompoundsBuffer.size();i++)
    {
    	iStoichometricCoefficient = unStoichem(vsRightCompoundsBuffer[i]);
    	viProducts[mSpecies.at(vsRightCompoundsBuffer[i])]=iStoichometricCoefficient;
    }
    
    for(int i=0;i!=vsLeftCompoundsBuffer.size();i++)
    {
    	iStoichometricCoefficient = unStoichem(vsLeftCompoundsBuffer[i]);
    	viReactants[mSpecies.at(vsLeftCompoundsBuffer[i])]=iStoichometricCoefficient;
    }

	

    for(int i=0;i!=viResult.size();i++)
    {
    	viResult[i]=viProducts[i]-viReactants[i]; 
    }
	//std::cout << "\n";
   	
	//productory(mSpecies,viResult); 
    
	for(int i=0;i!=viResult.size();i++)
    {
    	std::cout << " " << viResult[i]; 
    }
    std::cout << "\n";

}
