#include "stl_includes.hpp"
#include "libboost_includes.hpp"

#ifndef GET_MASS_ACTION_LAW_EQUATIONS
  #define GET_MASS_ACTION_LAW_EQUATIONS
  #include "cherene/getMassActionLawEquations.hpp"
#endif

#ifndef GET_SIMPLE_REACTIONS
  #define GET_SIMPLE_REACTIONS
  #include "cherene/getSimpleReactions.hpp"
#endif

#ifndef GET_SPECIES_MAP
  #define GET_SPECIES_MAP
  #include "cherene/getSpeciesMap.hpp"
#endif

#ifndef GET_REACTION_MATRIX
  #define GET_REACTION_MATRIX
  #include "cherene/getReactionMatrix.hpp"
#endif

#ifndef GET_REACTION_VECTOR
  #define GET_REACTION_VECTOR
  #include "cherene/getReactantsVector.hpp"
#endif

#ifndef GET_PRODUCTS_VECTOR
  #define GET_PRODUCTS_VECTOR
  #include "cherene/getProductsVector.hpp"
#endif

#ifndef OVERLOADED_VECTOR
  #define OVERLOADED_VECTOR
  #include "cherene/overloadedVector.hpp"
#endif

#ifndef OVERLOADED_MATRIX
  #define OVERLOADED_MATRIX
  #include "cherene/overloadedMatrix.hpp"
#endif

#ifndef UN_STOICHEM
 #define UN_STOICHEM
  #include "cherene/unStoichem.hpp"
#endif

#ifndef NUMBER_TO_STRING
  #define NUMBER_TO_STRING
  #include "cherene/numberToString.hpp"
#endif

#ifndef CHERENE 
namespace cherene
{


	std::map<std::string,std::string> getMassActionLawEquations(std::vector<std::string> vsSimpleReactions, std::map<std::string,int> mSpecies, boost::numeric::ublas::matrix<int>& mStoichometricMatrix);
	
	void getProductsVector(std::string sInput,std::map<std::string,int> mSpecies, std::vector< int >& viResult);

	void getReactantsVector(std::string sInput,std::map<std::string,int> mSpecies, std::vector< int >& viResult);

	void getReactionMatrix(std::vector<std::string> vsSimpleReactions,std::map<std::string,int> mSpecies, boost::numeric::ublas::matrix<int>& mNmatrix);

	void getReactionVector(std::string sInput,std::map<std::string,int> mSpecies, std::vector< int >& viResult);

	void getSimpleReactions(std::string sInput,std::vector<std::string>& vsSimpleReactions);

	void getSpeciesMap(std::string sPattern, std::string& sInput, std::map<std::string,int>& mSpecies);
	void getSpeciesMap(std::vector<std::string>& vsStringInput, std::map<std::string,int>& mSpecies);
	
	int unStoichem(std::string& sInput);

}

std::ostream& operator<<(std::ostream& outStream, std::map<std::string,int>& mSpecies)
{
	std::map<std::string,int>::iterator iTmSpecies;

	outStream << "Number of elements on map " << mSpecies.size() << std::endl;

	for(iTmSpecies=mSpecies.begin();iTmSpecies != mSpecies.end();++iTmSpecies)
	{
		outStream << " Key " << iTmSpecies->first << " Value " << iTmSpecies->second << std::endl;
	}

	return outStream;
}

#define CHERENE
#endif

