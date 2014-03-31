#include <iostream>
#include <ios>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <map>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>


int main(int argc, const char* argv[])
{
	/* Commandline options */

	std::string sWorkingDir(argv[1]);
	std::cout << " Working directory: " << sWorkingDir << std::endl;
	
	std::string sInReadsFileName(argv[2]);//"parsed");

	std::cout << " Reads file: " << sInReadsFileName << std::endl;

	/* Code stars here */

	std::chrono::time_point<std::chrono::system_clock> t_start,t_end;
	t_start = std::chrono::system_clock::now();

	std::ifstream  fInReadsFile(sWorkingDir+"/"+sInReadsFileName);
	std::string  sOutFileName(sWorkingDir+"/"+sInReadsFileName+"-uSatellites");//

	fInReadsFile.seekg(0,fInReadsFile.end);
	long int iSize = fInReadsFile.tellg();
	fInReadsFile.seekg(0,fInReadsFile.beg);

	std::ofstream osRead(sOutFileName);//

	int iSatelliteCount(0);
	int j(0);

	std::string sMicroSatelliteTemplate("TTT");
	std::map<std::string,int> msStalliteCounts;
	std::string sMicroSatelliteSearch("");

	while(fInReadsFile.good())
	{
		//char cRead = fInReadsFile.get();
		//sMicroSatelliteSearch.push_back(cRead);
		
		fInReadsFile.seekg(j,fInReadsFile.beg);

		for(int i=0;i<sMicroSatelliteTemplate.size();i++)
		{
			char cRead = fInReadsFile.get();
			sMicroSatelliteSearch.push_back(cRead);
		}
		
		j++;

		std::cout << sMicroSatelliteSearch << "\t" << iSatelliteCount << std::endl;
		
		if(sMicroSatelliteTemplate == sMicroSatelliteSearch)
		{
			iSatelliteCount++;	
		}

		sMicroSatelliteSearch.clear();
	}

	fInReadsFile.close();

	t_end = std::chrono::system_clock::now();

	
	std::cout << "Searching " << iSatelliteCount << " ocurrences, took me about\n\t" << std::chrono::duration_cast<std::chrono::milliseconds> (t_end-t_start).count() << " ms" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start).count() << " s" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::minutes> (t_end-t_start).count() << " m" << std::endl;
	return 0;
}
