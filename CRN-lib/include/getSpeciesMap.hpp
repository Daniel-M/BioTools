//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>

#include "incluidos.hpp"

/**\brief maps the chemical species given a vector containing strings of complexes
 *
 * \param[in] vsStringInput Vector containing the chemical complexes.
 * \param[out] mSpecies a map that stores the chemical species contained on \a vsStringInput.
 * \note mSpecies is modified by reference.
 */
void getSpeciesMap(std::vector<std::string> vsStringInput, std::map<std::string,int> &mSpecies)
{

  std::vector<std::string> vsSpecies;
  
  for(int k=0;k!=vsStringInput.size();k++)
  {
	  boost::algorithm::split(vsSpecies,vsStringInput[k],boost::algorithm::is_any_of("+"));
  }

  
  for(int k=0;k!=vsSpecies.size();k++)
  {
    unStoichem(vsSpecies[k]);
  }
  
  for(int i=0;i<vsSpecies.size();i++)
  {   
    if(mSpecies.find(vsSpecies[i])==mSpecies.end())
    {
      
		//std::cout << vsSpecies[i] << "," << mSpecies.size() << std::endl;
	    /* This apply for C++ 11 standard */
	    mSpecies.emplace(vsSpecies[i],mSpecies.size());
	    //mSpecies.insert( std::pair<std::string,int>(vsSpecies[i],mSpecies.size()));

    }
   }
}

/**
 * \overload This function maps chemical species given a string as input.
 */
void getSpeciesMap(std::string sPattern, std::string sInput, std::map<std::string,int> &mSpecies)
{
  std::vector<std::string> *vComplex = new std::vector<std::string>;
  
  boost::algorithm::split(*vComplex,sInput,boost::algorithm::is_any_of(sPattern));
  getSpeciesMap(*vComplex,mSpecies);
  
  delete(vComplex);
}
