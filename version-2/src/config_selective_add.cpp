//
// Created by hardieck on 9/27/19.
//

#include "../inc/config_selective_add.h"

std::set<int> config_selective_add::get_operation_set()
{
	return this->possible_operations[sel_add_operation_set];
}

bool config_selective_add::next_config()
{
	//just permutate the active parts

	//do a compleete permutation bevor reset it
	//return true if ther is a next state or false if it was the last one for this part.
	return false;
}
void config_selective_add::add_possible_set(set<int> s)
{
    this->possible_operations.push_back(s);
}