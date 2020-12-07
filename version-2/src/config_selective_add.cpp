//
// Created by hardieck on 9/27/19.
//

#include "../inc/config_selective_add.h"

std::set<int> config_selective_add::get_operation_set()
{
    return vec2set(mode_0_current_operation_set);
}

bool config_selective_add::next_config()
{
	if( this->operation_mode == 0)
    {
	    return next_m0();
    }

    if( this->operation_mode == 1) {
        return next_m1();
    }
    ERROR("No valid Operation Mode!","config_selective_add::next_config()");
    return false;
}
void config_selective_add::add_possible_set(set<int> s)
{
    this->operation_mode=1; // possible operation set is specified therefore mode 1 has to be used.
    this->possible_operations.push_back(s);
}

bool config_selective_add::get_shift_permutation() const {
    return do_shift_permutation;
}

void config_selective_add::set_shift_permutation(bool shift_permutation)
{
    do_shift_permutation = shift_permutation;
}

bool config_selective_add::get_LUT_permutation() const
{
    return do_LUT_permutation;
}
void config_selective_add::set_LUT_permutation(bool LUT_permutation)
{
    do_LUT_permutation = LUT_permutation;
}

bool config_selective_add::next_m0() {
    ERROR("Not implemented yet.",config_selective_add::next_m0())
    return false;
}
bool config_selective_add::next_m1() {

    if(do_shift_permutation)
    {

    }
    if(do_LUT_permutation)
    {

    }

    return false;
}
