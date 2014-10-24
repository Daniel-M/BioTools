#include "incluidos.hpp"

void getReactantsVector(std::string sInput,std::map<std::string,int> mSpecies, std::vector< int >& viResult)
{
    std::vector<std::string> vsComplexBuffer;
    std::vector<std::string> vsLeftCompoundsBuffer;
    std::vector<int> viProducts;
    
    viProducts.resize(mSpecies.size());
    
    int iStoichometricCoefficient=1;
    
	boost::algorithm::erase_all(sInput,"-");
	boost::algorithm::split(vsComplexBuffer,sInput,boost::algorithm::is_any_of(">"));
    
	//for(int i=0;i!=vsComplexBuffer.size();i++)
    //{
      //std::cout << vsComplexBuffer[i] << std::endl;
    //}

	boost::algorithm::split(vsLeftCompoundsBuffer,vsComplexBuffer[0],boost::algorithm::is_any_of("+"));
    
    for(int i=0;i!=vsLeftCompoundsBuffer.size();i++)
    {
       iStoichometricCoefficient = unStoichem(vsLeftCompoundsBuffer[i]);
       viProducts[mSpecies.at(vsLeftCompoundsBuffer[i])]=iStoichometricCoefficient;
    }
    
    viResult = viProducts;

	//std::cout << "Reactants\n";
	//for(int i=0;i!=viResult.size();i++)
    //{
       //std::cout << " " << viResult[i]; 
    //}
    //std::cout << "\n"; 
}
