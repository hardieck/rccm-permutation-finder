//
// Created by hardieck on 9/27/19.
//

#include "../inc/config_selective_add.h"
#include "../inc/permutator.h"

std::set<int> config_selective_add::get_operation_set()
{
    if (operation_mode)
        return mode_1_current_operation_set;
    else
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

    Permutator permut(&permut_max,true,&permut_min);
    permut.permutationCntVec = permut_state;

    permut.printPermutation();
    bool result = permut.nextPermutation();
    permut.printPermutation();
    permut_state = permut.permutationCntVec;
    mode_1_current_operation_set.clear();
    mode_1_current_operation_set =(possible_operations[permut_state[0]]);
    return result;
}

void config_selective_add::set_mode_list()
{
    operation_mode=1;
    unsigned int permut_variable_count= possible_operations.size()+shifts.size();
    permut_min.resize(permut_variable_count);
    permut_max.resize(permut_variable_count);
    permut_state.resize(permut_variable_count);

    // specify borders for Operation selecting in List mode
    if (do_LUT_permutation)
    {
        permut_state[0] = 0;
        permut_min[0] = 0;
        permut_max[0] = possible_operations.size();
    }
    else
    {
        permut_min[0] = permut_state[0];
        permut_max[0] = permut_state[0];
    }
    // specify borders for shifts
    if (do_LUT_permutation) {
        for (unsigned int i = 1; i < shifts.size() + 1; ++i) {
            permut_state[i] = shifts[i-1];
            permut_min[i] = shift_config_min[i - 1];
            permut_max[i] = shift_config_max[i - 1];
        }
    }
    else
    {
        for (unsigned int i = 1; i < shifts.size() + 1; ++i) {
            permut_state[i] = shifts[i - 1];
            permut_min[i] = shifts[i - 1];
            permut_max[i] = shifts[i - 1];
        }
    }


}

void config_selective_add::set_shift_config_max(const std::vector<int> &input)
{
    shift_config_max = input;
}
void config_selective_add::set_shift_config_min(const std::vector<int> &input)
{
    shift_config_min = input;
}
