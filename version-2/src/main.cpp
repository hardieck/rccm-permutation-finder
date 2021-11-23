#include <iostream>
//#include "../inc/calc_rccm_typ_3add.h"
#include "../inc/rccm.h"

#include <string>
#include <cstdlib>
#include <cstring>
#include "../inc/permutator.h"
#include "../inc/calc_selective_adder_typ_a.h"


int do_debug();
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


int memory_leek_test()
{
    IF_VERBOSE(1) ENTER_FUNCTION("memory_leek_test")
    {
        global_verbose = 0;
        IF_VERBOSE(2) std::cout << "Enter Function: do_debug:" << std::endl;
        rccm my_rccm;

        my_rccm.rccm_search_space.push_back(typ_C2);
        my_rccm.sel_add.resize(2);
        my_rccm.sel_add[0].sel_add_search_space.push_back(typ_A);
        my_rccm.sel_add[0].sel_add_search_space.push_back(typ_B);
        my_rccm.sel_add[1].sel_add_search_space.push_back(typ_A);
        my_rccm.sel_add[1].sel_add_search_space.push_back(typ_B);
        string config_string;
        std::set<int> *result = nullptr;
        unsigned int i = 1;
        do {
            std::set<int> *result = my_rccm.compute();
            config_string = my_rccm.get_config();
            if (i % 10000 == 0)
            {
                std::cout << config_string << " -> " << *result << " iteration:" << i << std::endl;
            }
            //if(config_string == "HM1-C1-B9abc-34-4"){ std::cout << "edit Verbose" << std::endl; global_verbose=10;}
            ++i;
        } while (my_rccm.next_config());
        std::cout << config_string << " -> " << *result << " iteration:" << i << std::endl;
    }
    std::cout << "memory leak is " << base_obj::obj_count << std::endl;
    std::cout << "memory leak from base_obj is " << base_obj::obj_count << std::endl<< std::endl;
    return 0;
}

int permutator_test_1()
{
    IF_VERBOSE(1) ENTER_FUNCTION("permutator_test_1")
    config_helper_obj h;
//    std::vector<int> v= {4,4,4};
//    std::vector<int> v_min= {0,1,0};
//    std::vector<bool> v_break= {0,0,1};
//    Permutator p;
//    p.pd->init(3, true, true);
//    p.pd->permutationCntMaxVec = v;
//    p.pd->permutationCntMinVec = v_min;
//    p.pd->risingBlockBreakVec = v_break;



    calc_selective_adder_typ_a sel_add_a;
    Permutator p;
    //p.set_config_from_spec(sel_add_a.get_spec(),shifts_only);
    p.set_config_from_spec(sel_add_a.get_spec(),all_operations_only);
    sel_add_a.get_spec().print_spec();

    p.reset_config();
    p.pd->printPermutationData();

    do
    {
        p.printPermutation(); p.pd->printPermutationData();
    }
    while( p.next_config(h));
    p.pd->printPermutationData();

    return 0;
}


int permutator_test_2()
{
   IF_VERBOSE(1) ENTER_FUNCTION("permutator_test_2")
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
    do{
        std::cout << "cycle: " << i++ << " ->";
        p.printPermutation();p.pd->printPermutationData();
    }while(p.nextPermutation());

    return 0;
}


int do_debug()
{
    global_verbose = 1;
    memory_leek_test();
    //permutator_test_1();
    //permutator_test_2();

    return 0;
}