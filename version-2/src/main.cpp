#include <iostream>
#include "../inc/rccm_3add.h"


#include <string>

int main(int argc, char *argv[])
{

	std::cout << "my Hello, World!" << std::endl;

	rccm_3add test;

	test.run_all_cases();

	for(int i=0; i < argc;++i)
	{
		std::string command =  argv[i];
		std::cout << "comand Nr." << i << " = " << command << std::endl;
	}



	return 0;
}