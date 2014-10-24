//#include <boost/algorithm/string/case_conv.hpp>
//#include <boost/algorithm/string/erase.hpp>
//#include <boost/algorithm/string/predicate.hpp>
//#include <boost/algorithm/string/find.hpp>
//#include <boost/algorithm/string/split.hpp>
//#include <boost/algorithm/string/find_iterator.hpp>
//#include <boost/algorithm/string/iter_find.hpp>
//#include <boost/algorithm/string/classification.hpp> 
#include "incluidos.hpp"

/**\brief Dissasemble a \a std::string representing a complex reaction into all simple reactions involved.
 *
 * Dissasemble a \a std::string representing a complex reaction into all simple reactions involved.
 * for instance, given \a A +\a B + \a C <-> \a E + 2\a F <-> \a P the output vector will contain
 * - \a A +\a B + \a C -> \a E +2 \a F
 * - \a E + 2 \a F -> \a A +\a B + \a C
 * - \a E + 2\a F -> \a P
 * - \a P -> \a E + 2\a F
 *
 * To achieve this, the function uses the boost::algorithm to manipulate strings.
 * First it deletes all white spaces " ", then the "=" and "-" are removed leaving only the complexes
 * and the symbols "<" and ">". Those symbols carry the information relevant to generate the simple reactions
 *
 * \param[in] sInput Input string containing the complex reaction.
 * \param[out] vsSimpleReactions The vector that will contain all the simple reactions.
 * \note the vsSimpleReactions is modified by reference.
 */
void getSimpleReactions(std::string sInput,std::vector<std::string>& vsSimpleReactions)
{

	std::vector<std::string> vsBuffer;
	std::vector<std::string> vsReactForward;
	std::vector<std::string> vsReactBackward;

	boost::algorithm::erase_all(sInput," ");
	boost::algorithm::to_upper(sInput);
	boost::algorithm::erase_all(sInput,"-");
	boost::algorithm::erase_all(sInput,"=");

	boost::algorithm::split(vsBuffer,sInput,boost::algorithm::is_any_of(">"));

	for(int i=0;i != vsReactForward.size();i++)
	{
		if( vsBuffer[i].find(">") < vsBuffer[i].length())
		{
			vsReactForward.push_back(vsBuffer[i+1]+"->"+vsBuffer[i]);
			//vsReactForward.push_back(vsBuffer[i+1]+">"+vsBuffer[i]);
		}
	}
	
	for(int j=0;j != vsBuffer.size()-1;j++)
	{
		vsReactForward.push_back(vsBuffer[j]+"->"+vsBuffer[j+1] );
		//vsReactForward.push_back(vsBuffer[j]+">"+vsBuffer[j+1] );
	}
	
	for(int i=0;i < vsBuffer.size();i++)
	{
		if( vsBuffer[i].find("<") < vsBuffer[i].length())
		{
			vsReactBackward.push_back(vsBuffer[i+1]+"->"+vsBuffer[i]);
			//vsReactBackward.push_back(vsBuffer[i+1]+">"+vsBuffer[i]);
		}
	}
	
	for(int j=0;j != vsReactForward.size();j++)
	{
		boost::algorithm::erase_all(vsReactForward[j],"<");
	}

	for(int j=0;j != vsReactBackward.size();j++)
	{
		boost::algorithm::erase_all(vsReactBackward[j],"<");
	}


	for(int i=0;i<vsReactForward.size();i++)
	//for(int i=vsReactForward.size()-1;i>=0;i--)
	{
		vsSimpleReactions.push_back(vsReactForward[i]);
	}
	
	for(int i=0;i<vsReactBackward.size();i++)
	//for(int i=vsReactBackward.size()-1;i>=0;i--)
	{
		vsSimpleReactions.push_back(vsReactBackward[i]);
	}
}	
