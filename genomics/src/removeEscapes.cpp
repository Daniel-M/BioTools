#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <chrono>

int main(int argc, const char* argv[])
{
	/* Commandline options */
	
	std::string sWorkingDir(argv[1]);
	std::cout << " Working directory: " << sWorkingDir << std::endl;

	std::string sGenomeFileName(argv[2]);

	std::ifstream isGenome(sWorkingDir + "/" + sGenomeFileName);
	std::ofstream osParsed(sWorkingDir + "/" + sGenomeFileName+"-parsed");
	
	std::cout << " Genome file: " << sGenomeFileName << std::endl;

	std::chrono::time_point<std::chrono::system_clock> t_start,t_end;
	t_start = std::chrono::system_clock::now();


	isGenome.seekg(0,isGenome.end);
	long int iSize = isGenome.tellg();
	isGenome.seekg(0,isGenome.beg);

	std::cout << "File size: " << iSize << std::endl;

	while(isGenome.good())
	{

		std::string sRead;
		
		getline(isGenome,sRead);
		
		if( (sRead.substr(0,1) != ">") )
		{
			if(sRead.substr(sRead.size(),1) == "\n")
			{
				osParsed << sRead.substr(0,sRead.size()-2);
			}
			else
			{
				osParsed << sRead;
			}
		}
		
	}

	isGenome.close();
	osParsed.close();
	t_end = std::chrono::system_clock::now();
	
	std::cout << "Acconditionate the file " << sGenomeFileName << " took me about\n\t" << std::chrono::duration_cast<std::chrono::milliseconds> (t_end-t_start).count() << " ms" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start).count() << " s" << std::endl;
	std::cout << "\t" << std::chrono::duration_cast<std::chrono::minutes> (t_end-t_start).count() << " m" << std::endl;

	return 0;
}
