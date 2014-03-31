#include <iostream>
#include <ios>
#include <fstream>
#include <random>
#include <chrono>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

bool isUsefulRead(std::string sReadSequence)
{
	if(sReadSequence.find("N") > sReadSequence.size())
	{
		//if((sReadSequence.find("A") > sReadSequence.size()) || (sReadSequence.find("T") > sReadSequence.size()) || (sReadSequence.find("G") > sReadSequence.size()) || (sReadSequence.find("C") > sReadSequence.size()))
		//{
			//return false;
		//}
		//else
		//{
			return true;
		//}
	}
	else
	{
		return false;
	}
}
