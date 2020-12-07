#include <iostream>
#include "../inc/rccm_3add.h"


#include <string>
#include <cstdlib>
#include <cstring>

void do_debug();
void print_help();

int main(int argc, char *argv[])
{
    global_verbose=10;
    if (argc == 1)
    {
        print_help();
        exit(0);
    }

    for(int i=1; i < argc;++i) {
        if (strstr(argv[i], "--verbose=")) {
            global_verbose = atol(argv[i] + 10);
        } else if (strstr(argv[i], "--help")) {
            print_help();
            exit(0);
        } else if (strstr(argv[i], "--debug")) {
            // do the stuff I prepaired!
            do_debug();
        } else {
            cout << "Error: Illegal Option: " << argv[i] << endl << endl;
            print_help();
            exit(0);
        }
    }

    IF_VERBOSE(8) std::cout << std::endl << "Finished. Safe end of Toolflow. Normal Quit." << std::endl;
	return 0;
}

void print_help()
{
    cout << "General Options:" << endl;
    cout << "Option                                         Meaning" << endl;
    cout << "--help                                         Prints this help" << endl;
    cout << "--verbose=0...9                                Verbosity level (0: no information, 9: all information during optimization), default:1" << endl;
}
void do_debug()
{
    IF_VERBOSE(1) std::cout << "Enter Function: do_debug:" << std::endl;
    rccm_3add test;

    IF_VERBOSE(1) std::cout << "Init done! Now Compute" << std::endl;
    test.run_all_cases();
}
