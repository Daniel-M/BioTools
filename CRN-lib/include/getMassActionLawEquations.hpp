#include "incluidos.hpp"

/**\brief This functions creates a map with strings containing the rate equations for each involved species
 *
 *
 */
std::map<std::string,std::string> getMassActionLawEquations(std::vector<std::string> vsSimpleReactions, std::map<std::string,int> mSpecies, boost::numeric::ublas::matrix<int>& mStoichometricMatrix)
{

	std::vector<std::string> vsR;
	std::string sParameter("k");
	std::string sVarName("x");
	std::string sPow("pow");
	std::string sKinect("");

	std::vector<int> viReactantsVector;

	mStoichometricMatrix = getReactionMatrix(vsSimpleReactions,mSpecies);
		
	for(int j=0;j!=vsSimpleReactions.size();j++)
	{
		std::map<std::string,int>::iterator iTmSpecies;
			
		getReactantsVector(vsSimpleReactions[j],mSpecies,viReactantsVector);

		for(iTmSpecies=mSpecies.begin();iTmSpecies != mSpecies.end();iTmSpecies++)
		{
			
			if(viReactantsVector[iTmSpecies->second] > 1)
			{
				std::string *sIndex = new std::string(numberToString(iTmSpecies->second,true));
				std::string *sVar = new std::string(sVarName+"[" + *sIndex + "]");
				std::string *sExponent = new std::string(numberToString(viReactantsVector[iTmSpecies->second],true));
				sKinect = sKinect + sPow + "(" + *sVar + "," + *sExponent + ")";

				delete(sIndex);
				delete(sVar);
				delete(sExponent);

			}
			else if (viReactantsVector[iTmSpecies->second] == 1)
			{
				std::string *sIndex = new std::string(numberToString(iTmSpecies->second,true));
				std::string *sVar = new std::string(sVarName+"[" + *sIndex + "]");
				sKinect = sKinect + *sVar;
			
				delete(sIndex);
				delete(sVar);
			}

			if(iTmSpecies->second < mSpecies.size() && viReactantsVector[iTmSpecies->second] >= 1)
			{
				sKinect += "*";
			}
		}

		sKinect = sKinect.substr(0,sKinect.size()-1);
		vsR.push_back( sParameter + "[" + numberToString(j,true) + "]*" + sKinect);
		sKinect.clear();
		viReactantsVector.clear();
	}

	std::map<std::string,std::string> mKinetics;
	std::map<std::string,int>::iterator iTmSpecies;

	for(iTmSpecies=mSpecies.begin();iTmSpecies != mSpecies.end();iTmSpecies++)
	{
		mKinetics.emplace(iTmSpecies->first,"d" +sVarName+"dt["+numberToString(iTmSpecies->second,true) +"] = " + (mStoichometricMatrix*vsR)(iTmSpecies->second,0));
	}
	return mKinetics;
}



std::map<std::string,std::string> getMassActionLawEquations(std::vector<std::string> vsSimpleReactions, std::map<std::string,int> mSpecies)
{
	boost::numeric::ublas::matrix<int> mBuffer;

	return getMassActionLawEquations(vsSimpleReactions,mSpecies,mBuffer);
}



