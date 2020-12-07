#include <iostream>
#include "../inc/rccm_3add.h"


#include <string>
#include <cstdlib>
#include <cstring>

void print_help();

int main(int argc, char *argv[])
{
    global_verbose=10;
    if (argc == 1)
    {
        print_help();
        exit(0);
    }

    for(int i=1; i < argc;++i)
    {
        if(strstr(argv[i], "--verbose="))
        {
            global_verbose = atol(argv[i]+10);
        }
        else if(strstr(argv[i], "--help"))
        {
            print_help();
            exit(0);
        }
        else
        {
            cout << "Error: Illegal Option: " << argv[i] << endl << endl;
            print_help();
            exit(0);
        }
    }

	IF_VERBOSE(5) {std::cout << "my Hello, World!" << std::endl;}

	rccm_3add test;

	test.run_all_cases();

	return 0;
}

void print_help()
{
    cout << "General Options:" << endl;
    cout << "Option                                         Meaning" << endl;
    cout << "--help                                         Prints this help" << endl;
    cout << "--verbose=0...9                                Verbosity level (0: no information, 9: all information during optimization), default:1" << endl;
}