#include <iostream>
#include <ios>
#include <fstream>
#include <random>
#include <chrono>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

void usefulRead(std::string sReadSequence)
{
	int j;

	if(sReadSequence.find("N") > sReadSequence.size())
	{
		std::ofstream osRead(sOutFileName + std::to_string(j));
		sReadSequence.push_back('\n');

		osRead << "> Read # " << j << " - Taken from  " << iPosition << " to " << (iPosition+iReadSize) << " of " <<  sInGenomeFileName <<std::endl;
		osRead << sReadSequence;
		//std::cout << sReadSequence;
		osRead.close();

		j++;
	}
}

int main(int argc, const char* argv[])
{
	/* Commandline options */

	std::string sWorkingDir(argv[1]);
	std::cout << " Working directory: " << sWorkingDir << std::endl;
	
	std::string sInGenomeFileName(argv[2]);//"parsed");
	std::string sOutReadFileNameRoot("read");

	std::cout << " Genome file: " << sInGenomeFileName << std::endl;

	/* Code stars here */

	int iNumberOfReads=1000000;
	int iReadSize=500;
	
	std::chrono::time_point<std::chrono::system_clock> t_start,t_end;
	t_start = std::chrono::system_clock::now();


	std::ifstream  isParsed(sWorkingDir+"/"+sInGenomeFileName);
	std::string  sOutFileName(sWorkingDir+"/results/"+sOutReadFileNameRoot+"-");
	
	isParsed.seekg(0,isParsed.end);
	long int iSize = isParsed.tellg();
	isParsed.seekg(0,isParsed.beg);

	std::random_device generator("/dev/urandom");
	
	int j(1);

	while(j<=iNumberOfReads)
	{
		long int iPosition = (iSize*1.0*generator())/generator.max();
		isParsed.seekg(iPosition,isParsed.beg);
		std::string sReadSequence;

		for(int k=0;k<iReadSize;k++)
		{
			char cRead = isParsed.get();
			sReadSequence.push_back(cRead);
		}

		if(sReadSequence.find("N") > sReadSequence.size())
		{
			std::ofstream osRead(sOutFileName + std::to_string(j));
			sReadSequence.push_back('\n');
			
			osRead << "> Read # " << j << " - Taken from  " << iPosition << " to " << (iPosition+iReadSize) << " of " <<  sInGenomeFileName <<std::endl;
			osRead << sReadSequence;
			//std::cout << sReadSequence;
			osRead.close();
			
			j++;
		}
		sReadSequence.clear();
		//sReadSequence = "";
	}

	isParsed.close();
	
	t_end = std::chrono::system_clock::now();
	
	std::cout << "Generate " << iNumberOfReads << " reads of " << iReadSize <<"bp took me about\n\t" << std::chrono::duration_cast<std::chrono::milliseconds> (t_end-t_start).count() << " ms" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start).count() << " s" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::minutes> (t_end-t_start).count() << " m" << std::endl;
	return 0;
}
