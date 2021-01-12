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

std::string rccm::get_config_for_implementation()
{
	// return just the configuration information to implment the coeff set
	return std::__cxx11::string();
}

std::string rccm::get_config()
{
	//return the complete testing and current config information.
	return std::__cxx11::string();
}

bool rccm::next_config(config_level)
{

    return 1; // there are still configs with this config level
    return 0; // no config left. this was the last one
}

