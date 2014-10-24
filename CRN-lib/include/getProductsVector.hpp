#include "incluidos.hpp"

void getProductsVector(std::string sInput,std::map<std::string,int> mSpecies, std::vector< int >& viResult)
{
	std::vector<std::string> vsComplexBuffer;
    std::vector<std::string> vsRightCompoundsBuffer;
    std::vector<int> viReactants;
    
    viReactants.resize(mSpecies.size());
    
    int iStoichometricCoefficient=1;
    
	boost::algorithm::erase_all(sInput,"-");
	boost::algorithm::split(vsComplexBuffer,sInput,boost::algorithm::is_any_of(">"));
    
	//for(int i=0;i!=vsComplexBuffer.size();i++)
    //{
      //std::cout << vsComplexBuffer[i] << std::endl;
    //}

	boost::algorithm::split(vsRightCompoundsBuffer,vsComplexBuffer[1],boost::algorithm::is_any_of("+"));
    
    for(int i=0;i!=vsRightCompoundsBuffer.size();i++)
    {
       iStoichometricCoefficient = unStoichem(vsRightCompoundsBuffer[i]);
	   viReactants[mSpecies.at(vsRightCompoundsBuffer[i])]=iStoichometricCoefficient;
    }

	viResult = viReactants;

	//std::cout << "Products\n";
	//for(int i=0;i!=viResult.size();i++)
    //{
       //std::cout << " " << viResult[i]; 
    //}
    //std::cout << "\n";
}
