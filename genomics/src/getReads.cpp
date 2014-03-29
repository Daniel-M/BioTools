#include <iostream>
#include <ios>
#include <fstream>
#include <random>
#include <chrono>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "isUsefulRead.hpp"

int main(int argc, const char* argv[])
{
	/* Commandline options */

	std::string sWorkingDir(argv[1]);
	std::cout << " Working directory: " << sWorkingDir << std::endl;
	
	std::string sInGenomeFileName(argv[2]);//"parsed");
	std::string sOutReadFileNameRoot("read");

	std::cout << " Genome file: " << sInGenomeFileName << std::endl;

	/* Code stars here */

	int iNumberOfReads=100;
	int iReadSize=5;
	
	std::chrono::time_point<std::chrono::system_clock> t_start,t_end;
	t_start = std::chrono::system_clock::now();


	std::ifstream  isParsed(sWorkingDir+"/"+sInGenomeFileName);
	std::string  sOutFileName(sWorkingDir+"/results/"+sOutReadFileNameRoot+"-");
	
	isParsed.seekg(0,isParsed.end);
	long int iSize = isParsed.tellg();
	isParsed.seekg(0,isParsed.beg);

	std::random_device generator("/dev/urandom");
	
	int j(1);

	long int iPosition = (iSize*1.0*generator())/generator.max();

	while(j<=iNumberOfReads)
	{
		
		//if(iPosition < iSize)
		//{

			isParsed.seekg(iPosition,isParsed.beg);
			std::string sReadSequence;

			for(int k=0;k<iReadSize;k++)
			{
				char cRead = isParsed.get();
				sReadSequence.push_back(cRead);
			}

			if(isUsefulRead(sReadSequence) == true)
			{
				std::ofstream osRead(sOutFileName + std::to_string(j));
				sReadSequence.push_back('\n');
				
				//std::cout << "> Read # " << j << " - Taken from  " << iPosition << " to " << (iPosition+iReadSize) << " of " <<  sInGenomeFileName <<std::endl;
				//std::cout << sReadSequence << std::endl;
				osRead << "> Read # " << j << " - Taken from  " << iPosition << " to " << (iPosition+iReadSize) << " of " <<  sInGenomeFileName <<std::endl;
				osRead << sReadSequence;
				osRead.close();
				
				j++;
			}
			else
			{
				//std::cout << "Bad read, omitting\n";
			}
			sReadSequence.clear();
			//}
	
		iPosition = (iSize*1.0*generator())/generator.max();

		//std::cout << iPosition << "\n";
	}

	isParsed.close();
	
	t_end = std::chrono::system_clock::now();
	
	std::cout << "Taking " << iNumberOfReads << " random reads of " << iReadSize <<"bp each, took me about\n\t" << std::chrono::duration_cast<std::chrono::milliseconds> (t_end-t_start).count() << " ms" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start).count() << " s" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::minutes> (t_end-t_start).count() << " m" << std::endl;
	return 0;
}
