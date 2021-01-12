//
// Created by hardieck on 9/27/19.
//

#include "../inc/rccm.h"

rccm::rccm()
{

}

bool rccm::set_config(std::string input_config)
{
	// read a string with congiguration specifications and generate the subcunfigurations out of it
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

bool rccm::next_config()
{
	//go inside the sub config structure and call the next state
	//do a compleete permutation of the chosen subconfig bevor reset it and go to the next one.
	//return true if ther is a next state or false if it was the last one for this part.

     return false;
}
