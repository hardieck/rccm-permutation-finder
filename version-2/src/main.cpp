#include <iostream>
//#include "../inc/calc_rccm_typ_3add.h"
#include "../inc/rccm.h"

#include <string>
#include <cstdlib>
#include <cstring>
#include "../inc/permutator.h"
#include "../inc/calc_selective_adder_typ_b.h"


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
            // do the stuff I had prepared!
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
    cout << "--do_debug                                     Run the debug function" << endl;
    cout << "--verbose=0...9                                Verbosity level (0: no information, 9: all information during optimization), default:1" << endl;
}
void do_debug()
{
    IF_VERBOSE(1) std::cout << "Enter Function: do_debug:" << std::endl;
    rccm my_rccm;

    //TODO add funktion to init Connection structure
    my_rccm.rccm_search_space.push_back(typ_C1);
    my_rccm.sel_add.resize(1);
    my_rccm.sel_add[0].sel_add_search_space.push_back(typ_A);
    my_rccm.sel_add[0].init();

    std::set<int> *result;
    result = my_rccm.compute(); std::cout << "result" << ":" << (*result) << std::endl;
    my_rccm.next_config();
    result = my_rccm.compute(); std::cout << "result" << ":" << (*result) << std::endl;
    my_rccm.next_config();
    result = my_rccm.compute(); std::cout << "result" << ":" << (*result) << std::endl;

//    config_helper_obj h;
//    Permutator p;
//    calc_selective_adder_typ_b sel_add_b;
//    p.set_config_from_spec(sel_add_b.spec,shifts_only);
//    p.pd->printPermutationData();
//    sel_add_b.spec.print_spec();



    //pair<vector<int>::iterator, vector<int>::iterator> my_block;
    //my_block.first=p.pd->permutationCntVec.begin();
    //my_block.second=p.pd->permutationCntVec.end();
    //p.pd->rising_block_list.push_back(my_block);

//    p.reset_config();
//    while( p.next_config(h))
//    {
//        p.printPermutation();
//        std::cout << endl;
//    }
//    p.pd->printPermutationData();
}

void do_debug_old()
{
   IF_VERBOSE(1) std::cout << "Enter Function: do_debug:" << std::endl;
    //calc_rccm_typ_3add test;

    //IF_VERBOSE(1) std::cout << "Init done! Now Compute" << std::endl;
    //test.run_all_cases();


    std::cout << "MH1" << std::endl;
    std::vector<int>myvec{2,3,2};
    std::cout << "MH2" << std::endl;
    Permutator p;
    p.pd->printPermutationData();
    p.pd->init(3);
    p.pd->printPermutationData();
    std::cout << "MH3a " << p.pd->permutationCntMaxVec <<  std::endl;
    std::cout << "MH3a " << p.pd->permutationCntVec <<  std::endl;
    p.pd->permutationCntMaxVec = myvec;
    p.pd->printPermutationData();
    std::cout << "MH3b " << p.pd->permutationCntMaxVec <<  std::endl;
    std::cout << "MH3b " << p.pd->permutationCntVec <<  std::endl;
    p.printPermutation();
    std::cout << "MH4" << std::endl;
    std::cout << p.pd->permutationCntMaxVec << std::endl;
    std::cout << "MH5" << std::endl;

    int i=0;
    std::cout << "MH6" << std::endl;
    p.resetPermutation();
    std::cout << "MH7" << std::endl;
    do{
        std::cout << "cycle: " << i++ << " ->";
        p.printPermutation();p.pd->printPermutationData();
    }while(p.nextPermutation());
    std::cout << std::endl << "MH9" << std::endl;


    i=0;
    Permutator p2(&myvec);
    p.resetPermutation();
    do{;
        std::cout << "cycle: " << i++ << " ->";
        p.printPermutation();p.pd->printPermutationData();
    }while(p.nextPermutation());


}
