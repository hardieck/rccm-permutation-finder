//
// Created by hardieck on 9/27/19.
//

#include "../inc/rccm.h"
#include "../inc/calc_rccm_C1.h"

rccm::rccm()
{

}

bool rccm::set_config(std::string input_config)
{
	// read a string with configuration specifications and generate the subconfigurations out of it
	// to configure the selective adder in terms of possible operation sets and the current used one.
	return false;
}

bool rccm::next_config()
{
    IF_VERBOSE(9) std::cout << "rccm: next_config: Enter Function" << std::endl;
    bool new_config_was_set = false;
    for(int i=0; i<= sel_add.size();++i) // itereate over all selective adder and stop at first positive result
    {
        IF_VERBOSE(10) std::cout << "rccm: next_config: try next config for sel_add["<< i << "]" << std::endl;
        new_config_was_set=sel_add[i].next_config(conv_helper); // TODO: Add config level to support same shifts
        if(new_config_was_set)
        {
            IF_VERBOSE(10) std::cout << "rccm: next_config: new Config was set" << std::endl;
            return true;
        } // if a permutation was changed return true
    }
    IF_VERBOSE(10) std::cout << "rccm: next_config: no config left, try next connection structure from search space" << std::endl;
    // TODO: iterate over search space elements (C1 C2 C3,...)
    //if there  is no config left
    //try different Connection structures from search space
    IF_VERBOSE(10) std::cout << "rccm: next_config: no config left" << std::endl;
    IF_VERBOSE(10) std::cout << "rccm: next_config: Iterate over all configurations from search space DONE" << std::endl;
    return false; // no config left. this was the last one
}
std::set<int>* rccm::compute()
{
    
    this->clear_calc_data();
    from_sp_use=0; // TODO: Fix!!! THis has to be the current type from the permutation list.
    switch(rccm_search_space[from_sp_use])
    {
        case typ_C1: calc = new calc_rccm_C1; break;
        case typ_C2: ERROR("Type B is not supported yet", "rccm::compute()") break;
        case typ_C3: ERROR("Type C is not supported yet", "rccm::compute()") break;
        case typ_C4: ERROR("Type D is not supported yet", "rccm::compute()") break;
        default: ERROR("Invalid Type","rccm::compute()");
    }

    return calc->compute(this);
}

bool rccm::parse_config_string(string) {
    return false;
}


selective_add* rccm::get_sel_add(unsigned int no)
{
    return &(sel_add[no]);
}

void rccm::clear_calc_data()
{
    if (this->calc != nullptr)
    {
        delete calc;
    }
}
