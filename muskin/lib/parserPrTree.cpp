#include "headers.hpp"
//#include "mesh.hpp"

/*!\brief This function overloads the libboost::ptree::operator<< to stream \c libboost::ptree
 * 
 * This function overloads the libboost::ptree::operator<< to provide streaming for \a libboost::ptree
 *
 * \param[in] outStream stream data type.
 * \param[in] prTree boost::property_tree::ptree container.
 * \return A ostream consisting of the information contained on the property tree
 */
std::ostream& operator<<(std::ostream& outStream, boost::property_tree::ptree& prTree)
{
	/* This function has a depth of 3 levels on the property tree, it works fine for
	 * the libmesh property trees. In order to get a better version a self-recursive function
	 * must be implemented. something like
	 *
	 * f(x)
	 * {
	 * 		//some code
	 * 		f(x);
	 * }
	 */
	std::vector< std::pair<std::string,std::string> > vpFieldsPairsV;
	std::pair<std::string,std::string> pFieldsPair;
 
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& rowPair, prTree.get_child( "" ) ) 
    {
		//std::cout << rowPair.first << ": " << std::endl;

		pFieldsPair = std::make_pair(rowPair.first,rowPair.second.get_value<std::string>());
		vpFieldsPairsV.push_back(pFieldsPair);

 
        BOOST_FOREACH( boost::property_tree::ptree::value_type const& itemPair, rowPair.second ) 
        {
			//std::cout << "\t" << itemPair.first << " ->";
 
            pFieldsPair = std::make_pair(itemPair.first,itemPair.second.get_value<std::string>());
			vpFieldsPairsV.push_back(pFieldsPair);

			BOOST_FOREACH( boost::property_tree::ptree::value_type const& node, itemPair.second ) 
            {
				//std::cout << node.second.get_value<std::string>() << " , ";
				
				pFieldsPair = std::make_pair(node.first,node.second.get_value<std::string>());
				vpFieldsPairsV.push_back(pFieldsPair);

				BOOST_FOREACH( boost::property_tree::ptree::value_type const& node1, node.second ) 
				{
					//std::cout << node1.second.get_value<std::string>() << " ; ";
					pFieldsPair = std::make_pair(node1.first,node1.second.get_value<std::string>());
					vpFieldsPairsV.push_back(pFieldsPair);
				}
			}
 
			//std::cout << std::endl;
 
        }
 
		//std::cout << std::endl;
    }
     
	//std::cout  << "Information read: " << std::endl;
	//outStream  << "Information read: " << std::endl;
	
	for(int i(0);i<vpFieldsPairsV.size();i++)
	{
		//std::cout << vpFieldsPairsV[i].first << "\t" << vpFieldsPairsV[i].second << std::endl;
		outStream << vpFieldsPairsV[i].first << "\t" << vpFieldsPairsV[i].second << std::endl;
	}

	return outStream;
}


