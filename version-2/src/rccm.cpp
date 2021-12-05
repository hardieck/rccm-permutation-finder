//
// Created by hardieck on 9/27/19.
//

#include "../inc/rccm.h"
#include "../inc/calc_rccm_C1.h"
#include "../inc/calc_rccm_C2.h"
#include "../inc/calc_rccm_C3.h"

rccm::rccm(shared_ptr<search_space_plan> _ssp)
{

    IF_VERBOSE(3) ENTER_FUNCTION("rccm::rccm()")
    from_sp_use = 0;
    calc = nullptr;
    if (_ssp != nullptr)
        ssp = _ssp;
    else
    {
        //ssp = static_cast<const shared_ptr<search_space_plan>>(new search_space_plan);
        ssp = make_shared<search_space_plan>();
    }
    ssp->init_empty_slots();
    sel_add.clear();
}
rccm::~rccm()
{
    delete_calc();
}

void rccm::init()
{
    IF_VERBOSE(4) ENTER_FUNCTION("rccm::init()")
    if(rccm_search_space.size()==0) {
        rccm_search_space = ssp->get_search_space_rccm();
    }
    if((calc!=nullptr)&&(rccm_search_space[from_sp_use] != ((calc_rccm_base*)calc)->type()))
    {
        IF_VERBOSE(5) std::cout << "calc pointer: " << calc << std::endl;
        IF_VERBOSE(5) std::cout << "calc type: " << ((calc_rccm_base*)calc)->type() << " Searchg space type: " << rccm_search_space[from_sp_use] << std::endl;
        delete_calc();
    }
    if(calc==nullptr) // calc does not exist (anymore) and need to be initialized
    {
        IF_VERBOSE(5) std::cout << "new calc type will be set to: " << rccm_search_space[from_sp_use] << std::endl;
        switch (rccm_search_space[from_sp_use]) {
            case typ_C1:
                calc = static_cast<calc_base *>(new calc_rccm_C1);
                break;
            case typ_C2:
                calc = static_cast<calc_base *>(new calc_rccm_C2);
                break;
            case typ_C3:
                calc = static_cast<calc_base *>(new calc_rccm_C3);
                break;
            default:
            ERROR("Invalid Type", "rccm::init()");
        }
        init_sel_add();// only init selective add if ther was a change
    }
}
void rccm::init_sel_add()
{
    sel_add.clear();
    sel_add.resize(((calc_rccm_base*)calc)->get_spec().add_sel_count);
    for(int i=0; i< sel_add.size();++i)
    {
        sspk key(rccm_search_space[from_sp_use],i);
        sel_add[i].sel_add_search_space=ssp->get_search_space_sel_add(key);
        sel_add[i].init(ssp,i,rccm_search_space[from_sp_use]);
    }
}

std::string rccm::get_config()
{
    IF_VERBOSE(2) ENTER_FUNCTION("rccm::get_config()")
    IF_VERBOSE(3) std::cout << "Prepair config string and add header" << std::endl;
    string current_config;
    current_config.clear();
    current_config = "HM1";

    IF_VERBOSE(3) std::cout << "Add connection Structer." << std::endl;
    IF_VERBOSE(9) std::cout << "Data Info: from_sp_use = " << from_sp_use << std::endl;
    IF_VERBOSE(9) std::cout << "Data Info: rccm_search_space.size() = " << rccm_search_space.size() << std::endl;
    IF_VERBOSE(9) std::cout << "Data Info: rccm_search_space[from_sp_use] = " << rccm_search_space[from_sp_use] << std::endl;
    if(from_sp_use> rccm_search_space.size()){ ERROR("index is biger than actualy search space!","rccm::get_config()")}

    switch (rccm_search_space[from_sp_use]) {
        case typ_C1 : current_config += "-C1"; break;
        case typ_C2 : current_config += "-C2"; break;
        case typ_C3 : current_config += "-C3"; break;
        case typ_C4 : current_config += "-C4"; break;
        default:
            ERROR("Unsupported Connection Structure!", "rccm::get_config()")
    }
    IF_VERBOSE(3) std::cout << "iterate through selective adders" << std::endl;
    for(int i=0; i< sel_add.size(); ++i)
    {
        IF_VERBOSE(4) std::cout << "Start with Selective add:" << i << std::endl;
        string sel_add_conf = sel_add[i].get_config();
        IF_VERBOSE(4) std::cout << "Config of Selective add:" << i << " is: " << sel_add_conf << std::endl;
        current_config += sel_add_conf;
    }
    // read a string with configuration specifications and generate the subconfigurations out of it
    // to configure the selective adder in terms of possible operation sets and the current used one.
    IF_VERBOSE(2) std::cout << "current config is: " << current_config << std::endl;
    return current_config;
}

bool rccm::set_config(std::string new_config)
{
    ERROR("not implemented yet","rccm::set_config(std::string new_config)")
	// read a string with configuration specifications and generate the subconfigurations out of it
	// to configure the selective adder in terms of possible operation sets and the current used one.
	return false;
}

bool rccm::next_config()
{
    IF_VERBOSE(8) ENTER_FUNCTION("rccm::next_config()")
    bool new_config_was_set = false;
    for(int i=0; i < sel_add.size();++i) // iterate over all selective adder and stop at first positive result
    {
        IF_VERBOSE(9) std::cout << "rccm: next_config: try next config for sel_add["<< i << "]" << std::endl;
        new_config_was_set=sel_add[i].next_config(conv_helper); // TODO: Add config level to support same shifts
        if(new_config_was_set)
        {
            IF_VERBOSE(9) std::cout << "rccm: next_config: new Config was set" << std::endl;
            return true;
        } // if a permutation was changed return true
    }
    IF_VERBOSE(9) std::cout << "rccm: next_config: no config left, try next connection structure from search space" << std::endl;
    // TODO: iterate over search space elements (C1 C2 C3,...)
    if(from_sp_use < rccm_search_space.size()-1)
    {
        ++from_sp_use;
        new_config_was_set = true;
        IF_VERBOSE(9) std::cout << "rccm: next_config: new Config was set. use search space element:" << from_sp_use << std::endl;
        conv_helper.reset_all_on_list(); // reset all previous operations to restart permutation with this new configuration
        init(); //as the type changed the calc obj as to change and the permutators have to reload the specs for the new type.
        return 1;
    }

    //if there  is no config left
    //try different Connection structures from search space
    IF_VERBOSE(9) std::cout << "rccm: next_config: no config left" << std::endl;
    IF_VERBOSE(9) std::cout << "rccm: next_config: Iterate over all configurations from search space DONE" << std::endl;
    return false; // no config left. this was the last one
}
std::set<int>* rccm::compute()
{
    IF_VERBOSE(4) ENTER_FUNCTION("rccm::compute()")
    // calc exists but points to a wrong type
    if((calc!=nullptr)&&(rccm_search_space[from_sp_use] != ((calc_rccm_base*)calc)->type())){delete_calc();}
    if(calc==nullptr) // calc does not exist (anymore) and need to be initialized
    {
        switch (rccm_search_space[from_sp_use])
        {
            case typ_C1:calc = new calc_rccm_C1;break;
            case typ_C2:calc = new calc_rccm_C2;break;
            case typ_C3:calc = new calc_rccm_C3;break;
            case typ_C4:ERROR("Type C4 is not supported yet", "rccm::compute()")break;
            default:
            ERROR("Invalid Type", "rccm::compute()");
        }
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

void rccm::delete_calc()
{
    IF_VERBOSE(6) ENTER_FUNCTION("rccm::delete_calc()")
    IF_VERBOSE(6) std::cout << "calc points to : " << this->calc << std::endl;
    if (this->calc != nullptr)
    {
        IF_VERBOSE(6) std::cout << "delete calc" << std::endl;
        delete calc;
        calc = nullptr;
    }
}
