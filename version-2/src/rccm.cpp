//
// Created by hardieck on 9/27/19.
//

#include "../inc/rccm.h"

rccm::rccm()
{

}

bool rccm::set_config(std::string input_config)
{
	// read a string with configuration specifications and generate the subconfigurations out of it
	// to configure the selective adder in terms of possible operation sets and the current used one.
	return false;
}

bool rccm::next_config(config_level)
{

    return 1; // there are still configs with this config level
    return 0; // no config left. this was the last one
}
std::set<int> rccm::compute()
{
    swtich(rccm_search_space[used_rccm])
    {
        case typ_A: calc_rccm_3add break;
        case typ_B: ERROR("Type B is not supported yet","rccm::compute()") break;
        case typ_C: ERROR("Type C is not supported yet","rccm::compute()") break;
        default: ERROR("Invalid Type","rccm::compute()");
    }

}


case typ_D: break;