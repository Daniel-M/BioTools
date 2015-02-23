/*Example JSON file "test1.json":

{
    "electron": {
        "pos": [0,0,0],
        "vel": [0,0,0]
    },

    "proton": {
        "pos": [1,0,0],
        "vel": [0,0.1,0]
    },

     "proton": {
        "pos": [-1,0,0],
        "vel": [0,-0.1,-0.1]
    }
}*/
#include <string>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

/* These #define statements are used when parsing the JSON or XML*/
#define _pMesh "mesh"
#define _pMeshName "name"
#define _pMeshXML "xml"
#define _pMeshJSON "json"
#define _pMeshFile "meshfile"
#define _pMeshDim "dimension"
#define _pMeshNN "numberofnodes"
#define _pMeshBN "bnodes"
#define _pMeshIN "inodes"
#define _pMeshDD "deltaondim"
#define _pMeshND "nodesondim"
#define _pMeshPA "pointa"
#define _pMeshPB "pointb"
#define _pCoord "x"
#define _pFiles "files"

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
    outStream  << "Information read: " << std::endl;
	
	for(int i(0);i<vpFieldsPairsV.size();i++)
	{
		//std::cout << vpFieldsPairsV[i].first << "\t" << vpFieldsPairsV[i].second << std::endl;
		outStream << vpFieldsPairsV[i].first << "\t" << vpFieldsPairsV[i].second << std::endl;
	}

	return outStream;
}

template <typename T>
std::string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T StringToNumber ( const std::string &Text )
{
	std::istringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

const std::string JSON_PATH = "test.json";  
 
int main()  
{  
    boost::property_tree::ptree pt;
    boost::property_tree::read_json( JSON_PATH, pt );

	//std::vector<std::string> sFields;
	std::vector< std::pair<std::string,std::string> > sFields;
	std::pair<std::string,std::string> sFieldsP;
 
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& rowPair, pt.get_child( "" ) ) 
    {
        std::cout << rowPair.first << ": " << std::endl;

		sFieldsP = std::make_pair(rowPair.first,rowPair.second.get_value<std::string>());
		sFields.push_back(sFieldsP);

 
        BOOST_FOREACH( boost::property_tree::ptree::value_type const& itemPair, rowPair.second ) 
        {
            std::cout << "\t" << itemPair.first << " ->";
 
			//sFields.push_back(itemPair.first);
            sFieldsP = std::make_pair(itemPair.first,itemPair.second.get_value<std::string>());
			sFields.push_back(sFieldsP);

			BOOST_FOREACH( boost::property_tree::ptree::value_type const& node, itemPair.second ) 
            {
                std::cout << node.second.get_value<std::string>() << " , ";
				
				//sFields.push_back(node.first);
				sFieldsP = std::make_pair(node.first,node.second.get_value<std::string>());
				sFields.push_back(sFieldsP);

				BOOST_FOREACH( boost::property_tree::ptree::value_type const& node1, node.second ) 
				{
					std::cout << node1.second.get_value<std::string>() << " ; ";
					//sFields.push_back(node1.first);
					sFieldsP = std::make_pair(node1.first,node1.second.get_value<std::string>());
					sFields.push_back(sFieldsP);
				}
			}
 
            std::cout << std::endl;
 
        }
 
        std::cout << std::endl;
    }
     
    std::cout  << "The resulting vector is " << std::endl;

	
	for(int i(0);i<sFields.size();i++)
	{
		std::cout << sFields[i].first << "\t" << sFields[i].second << std::endl;
	}


	/* Get the values from JSON readed */
    boost::property_tree::read_json( JSON_PATH, pt );

	std::cout << pt << std::endl;

	std::vector<std::string> vValues;

	std::string sPathBuffer;

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshName;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshDim;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshNN;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshBN;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshIN;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pFiles;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshXML;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pFiles;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshJSON;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pFiles;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshFile;
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	sPathBuffer.clear();

	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshND;
	sPathBuffer+=".";
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		vValues.push_back(pt.get(sPathBuffer + NumberToString(j),"-1"));
	}
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshDD;
	sPathBuffer+=".";
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		vValues.push_back(pt.get(sPathBuffer + NumberToString(j),"-1"));
	}

	sPathBuffer.clear();
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshPA;
	sPathBuffer+=".";
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		vValues.push_back(pt.get(sPathBuffer + NumberToString(j),"-1"));
	}	
	sPathBuffer.clear();
	
	sPathBuffer=_pMesh;
	sPathBuffer+=".";
	sPathBuffer+=_pMeshPB;
	sPathBuffer+=".";
	vValues.push_back(pt.get(sPathBuffer,"-1"));
	//sPathBuffer.clear();
	
	for(int j(0);j<2;j++)
	{
		//std::cout << sPathBuffer + NumberToString(j) << "\n";
		vValues.push_back(pt.get(sPathBuffer + NumberToString(j),"-1"));
	}
	sPathBuffer.clear();
	
	//vValues.push_back(pt.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(pt.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(pt.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(pt.get(_pMesh +"."+ _pMeshName));
	//vValues.push_back(pt.get<std::string>(_pMesh +"."+ _pMeshName));
	
	

	std::cout << "\n\nVector values: " << std::endl;

	for(int i(0);i<vValues.size();i++)
	{
		std::cout << vValues[i] << std::endl;
	}


	/* Populate json with all the paths and stuff */
  
    boost::property_tree::ptree ptm, ptn;
	std::string sNNodes("numberofnodes"), sDim("dimension"), sMeshName("name");
	std::string	sMeshJSON("json"), sMeshFile("meshfile");
	std::string sMeshBN("bnodes"),sMeshIN("inodes");
	std::string sMeshDD("deltaondim"), sMeshND("nodesondim");
	std::string sMeshPA("pointa"),sMeshPB("pointb");
	std::string sCoord("x");

	//ptm.put("mesh."+sMeshName,"NewMesh");
	//ptm.put("mesh."+sMeshJSON,"NewMesh.json");
	//ptm.put("mesh."+sMeshFile,"NewMesh.msh");
	//ptm.put("mesh."+sNNodes,100);

	ptn.add(sMeshName,"NewMesh");
	ptn.add(sMeshJSON,"NewMesh.json");
	ptn.add(sMeshFile,"NewMesh.msh");
	ptn.add(sNNodes,100);


	boost::property_tree::ptree targetTree;
	boost::property_tree::ptree arrayChild;
	boost::property_tree::ptree	arrayElement;

	for(int i(0);i<2;i++)
	{
		arrayElement.put_value(10);
		arrayChild.push_back(std::make_pair("",arrayElement));
	}

	ptn.put_child(boost::property_tree::ptree::path_type(sMeshND),arrayChild);
	//ptm.put_child(boost::property_tree::ptree::path_type("mesh"),ptn);
	ptm.add_child(boost::property_tree::ptree::path_type("mesh"),ptn);

	//for(int i = 0; i < 3; i++)
	//{
		//arrayElement.put_value(i);
		//arrayChild.push_back(std::make_pair("",arrayElement));
	//}
	
	//targetTree.put_child(boost::property_tree::ptree::path_type("target.path.to.array"),arrayChild);

	boost::property_tree::write_json( "mesh.json", ptm );
	boost::property_tree::write_json( "example.json", ptn);

    return 0;  
}  
