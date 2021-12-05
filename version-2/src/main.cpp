#include <iostream>
//#include "../inc/calc_rccm_typ_3add.h"
#include "../inc/rccm.h"

#include <string>
#include <cstdlib>
#include <cstring>
#include "../inc/permutator.h"
#include "../inc/calc_selective_adder_typ_a.h"
#include "../inc/helper.h"

#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define VERSION_REVISION 0


int do_debug();
void print_help();

int main(int argc, char *argv[])
{
    IF_VERBOSE(0){
        std::cout << "RCCM-Finder Version: "<<  VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_REVISION << " Compiled:"  << __DATE__ << " at " << __TIME__ << std::endl;
        // reaped the function call:
        std::cout << "Called with: ";
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
    }

    auto ssp = make_shared<search_space_plan>();


    global_verbose=1;
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
        } else if (strstr(argv[i], "--set_")) {
            ssp->add_rule(argv[i]);
        } else if (strstr(argv[i], "--debug")) {
            // do the stuff I had prepared!
            do_debug();
            exit(0);
        } else {
            cout << "Error: Illegal Option: " << argv[i] << endl << endl;
            print_help();
            exit(-1);
        }
    }

    // init rest of search space:
    ssp->init_empty_slots();
    //init my_rccm with the plan from ssp;
    rccm my_rccm(ssp);
    my_rccm.init();

    // Do Search:
    // TODO following code make as function from somewhere...
    IF_VERBOSE(2) std::cout << std::endl << "Start RCCM search" << std::endl;
    string config_string;
    std::set<int> *result = nullptr;
    unsigned int i = 0;
    do {
        std::set<int> *result = my_rccm.compute();
        config_string = my_rccm.get_config();
        //if (i % 1 == 0)
        {
            IF_VERBOSE(1) std::cout << config_string << " size=" << result->size() <<  " iteration:" << ++i << " -> " << *result <<  std::endl;
        }
    } while (my_rccm.next_config());
    IF_VERBOSE(2) std::cout << std::endl << "Finished RCCM search" << std::endl;

    IF_VERBOSE(8) std::cout << std::endl << "Finished. Safe end of Toolflow. Normal Quit." << std::endl;
	return 0;
}

void print_help()
{
    cout << "General Options:" << endl;
    cout << "Option                                         Meaning" << endl;
    cout << "--help                                         Prints this help" << endl;
    cout << "'--set_rccm C1,C2,C3'                          Set rccm search space to C1 and C2 and C3 " << endl;
    cout << "'--set_sel_add A,B,C for <key>'                Set sel_add search space to type A and B and C for the specified key" << endl;
    cout << "'--set_max_shift X for <key>'                  Set upper border for shifts used in the selective add for specified key to X(int)" << endl;
    cout << "'--set_operation_mode <usal/all> for <key>'    switch between two cases: Test all possible Operation combinations, or test only usal operation sets in the selective add for specified key" << endl;
    cout << "                                               A <key> is a specified position in the sarch space. It supports also don't care values (~). The last specified rule that firs is used."<< endl;
    cout << "                                               < key > = < RCCM Typology, selective add position in Typology (starting by 0), Type of selective adder >"<< endl;
    cout << "                                               Key Examples"<< endl;
    cout << "                                                ~,~,~ ->  all don't care: rule applies for everything"<< endl;
    cout << "                                               C1,~,~ ->  rule for everything in typology C1"<< endl;
    cout << "                                                ~,~,B ->  rule for all Selective adder type B in search space"<< endl;
    cout << "                                               C2,1,~ ->  rule for the second (starting by 0!) selective adder in typology C2"<< endl;
    cout << "                                               C3,3,B ->  rule for the third (starting by 0!) selective adder if it is type B in typology C3"<< endl;
    cout << "                                               always last fitting rule is used! so Start with global settings then specify details!"<< endl;
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
    p.set_config_from_spec(sel_add_a.get_spec(), operations_only);
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

int RCCM_test()
{
    IF_VERBOSE(1) ENTER_FUNCTION("RCCM_test")
    {
        global_verbose = 0;
        auto ssp = make_shared<search_space_plan>();
        ssp->add_rule("set_rccm C1");
        ssp->add_rule("set_max_shift 4");
        ssp->add_rule("set_sel_add A,B for ~,~,~");
        ssp->add_rule("set_sel_add B for C3,2,~");
        ssp->add_rule("set_sel_add B for C2,1,~");
        ssp->add_rule("set_operation_mode all for ~,~,~");
        ssp->add_rule("set_operation_mode usal for ~,~,B");
        ssp->init_empty_slots();
        ssp->print();

        sspk key1;
        sspk key2(typ_C1,0,sel_add_type_downtCare);
        sspk key3(typ_C1,0,sel_add_type_downtCare);
        std::cout << "key1 " << key1 << std::endl;
        std::cout << "key2 " << key2 << std::endl;
        std::cout << "key3 " << key3 << std::endl;


        std::cout << "key1 == key1 : " << (key1 == key1) << std::endl;
        std::cout << "key1 == key2 : " << (key1 == key2) << std::endl;
        std::cout << "key1 == key3 : " << (key1 == key3) << std::endl;
        std::cout << "key2 == key3 : " << (key2 == key3) << std::endl;
        std::cout << "key2 == key2 : " << (key2 == key2) << std::endl;







        rccm my_rccm(ssp);
        my_rccm.init();
        string config_string;
        std::set<int> *result = nullptr;
        unsigned int i = 0;
        do {
            std::set<int> *result = my_rccm.compute();
            config_string = my_rccm.get_config();
            if (i % 1 == 0)
            {
                std::cout << config_string << " size=" << result->size() <<  " iteration:" << ++i << " -> " << *result <<  std::endl;
            }
            //if(config_string == "HM1-C1-B9abc-34-4"){ std::cout << "edit Verbose" << std::endl; global_verbose=10;}
        } while (my_rccm.next_config());

        result = my_rccm.compute();
        config_string = my_rccm.get_config();
        std::cout << config_string << " size=" << result->size() <<  " iteration:" << i << " -> " << *result <<  std::endl;
    }
    return 0;
}
int string_seperator_test()
{
    global_verbose = 10;
    search_space_plan ssp;
    std::string s;
    ssp.add_rule("set_rccm C1,C2");
    ssp.add_rule("set_sel_add A,B,C for C2,2,A");
    ssp.add_rule("set_sel_add A,B,C for C1,~,~");
    ssp.add_rule("set_max_shift 5 for ~~~");
    ssp.add_rule("set_max_shift 3");
    ssp.add_rule("set_max_shift 4 for C3,2,A");
    std::cout << "---------------------------------"<< std::endl;;
    ssp.print();


    return 1;
}


int do_debug()
{
    global_verbose = 1;
    //memory_leek_test();
    RCCM_test();
    //permutator_test_1();
    //permutator_test_2();
    //string_seperator_test();

    return 0;
}
