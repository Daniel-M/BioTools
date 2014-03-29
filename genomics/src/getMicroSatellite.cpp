#include <iostream>
#include <ios>
#include <fstream>
#include <random>
#include <chrono>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>




int main(int argc, const char* argv[])
{
	/* Commandline options */

	std::string sWorkingDir(argv[1]);
	std::cout << " Working directory: " << sWorkingDir << std::endl;
	
	std::string sReadFileNameRoot(argv[2]);//"read");

	std::cout << " Read file name root: " << sReadFileNameRoot << std::endl;

	/* Code stars here */

	int iNumberOfReads(1000000);
	int iReadSize(500);
	int iMicroUniverseSize(2);
	int iMicroUniverseMinRepeats(6);
	int iMicroUniverseMaxRepeats(12);


	std::string sMicroUniversePattern("TC");

	std::chrono::time_point<std::chrono::system_clock> t_start,t_end;
	t_start = std::chrono::system_clock::now();
	
	int j(1);

	int iMicroUniverseCounts(0);

	while(j<=iNumberOfReads)
	{
		std::ifstream  isRead(sWorkingDir+"/results/"+sOutReadFileNameRoot+"-"+std::to_string(j));
	
		isRead.seekg(0,isRead.end);
		long int iSize = isRead.tellg();
		isRead.seekg(0,isRead.beg);
	
		std::string sMicroUniverseSearch;

		while(isRead.good())
		{
			char cRead = isRead.get();
			
		}



		isRead.close();
	}

		
	t_end = std::chrono::system_clock::now();
	
	std::cout << "Counting \'" << sMicroUniversePattern << "\' repeats took me about\n\t" << std::chrono::duration_cast<std::chrono::milliseconds> (t_end-t_start).count() << " ms" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start).count() << " s" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::minutes> (t_end-t_start).count() << " m" << std::endl;
	return 0;
}
