//
// Created by hardieck on 9/27/19.
//

#include "../inc/selective_add.h"
#include "../inc/calc_selective_adder_typ_a.h"
#include "../inc/calc_selective_adder_typ_b.h"
//
//std::set<int> selective_add::get_operation_set()
//{
//    if (operation_mode)
//        return mode_1_current_operation_set;
//    else
//        return vec2set(mode_0_current_operation_set);
//}
//
bool selective_add::next_config(config_helper_obj& conv_helper)
{
    IF_VERBOSE(9) std::cout << "selective_add: next_config: Enter Function" << std::endl;
//	if( this->operation_mode == 0
//    {
//	    return next_m0();
//    }
//
//    if( this->operation_mode == 1) {
//        return next_m1();
//    }
    //ERROR("No valid Operation Mode!","selective_add::next_config()");

    bool new_config_was_set = false;
    IF_VERBOSE(10) std::cout << "selective_add: next_config: try next operation" << std::endl;
    //for ()// itereate over all selective adder and stop at first positive result
    {
        if(new_config_was_set){
            IF_VERBOSE(10) std::cout << "selective_add: next_config: new Config was set" << std::endl;
            conv_helper.reset_all_on_list(); // reset all previus operations to restart permutation with this new configuration
            return 1;
        } // if a permutation was changed return true
    }
    IF_VERBOSE(10) std::cout << "selective_add: next_config: no config left, try next Shift coniguration" << std::endl;
    // TODO: iterate over shift config
    IF_VERBOSE(10) std::cout << "selective_add: next_config: no config left, try next selective adder type from search space" << std::endl;
    // TODO: iterate over search space elements (typ_A typ_B typ_C,...)
    //if there  is no config left
    //try different Connection structures from search space
    IF_VERBOSE(10) std::cout << "selective_add: next_config: no config left" << std::endl;
    IF_VERBOSE(10) std::cout << "selective_add: next_config: Iterate over all configurations from search space DONE" << std::endl;
    conv_helper.add_me_to_reset_list((config_reset_base*) this);
    return false; // no config left. this was the last one
}
//void selective_add::add_possible_set(set<int> s)
//{
//    this->operation_mode=1; // possible operation set is specified therefore mode 1 has to be used.
//    this->possible_operations.push_back(s);
//}

// TODO: remove or fix! comented to make error silent
//bool selective_add::get_shift_permutation() const {
//    return do_shift_permutation;
//}
//
//void selective_add::set_shift_permutation(bool shift_permutation)
//{
//    do_shift_permutation = shift_permutation;
//}
//
//bool selective_add::get_LUT_permutation() const
//{
//    return do_LUT_permutation;
//}
//void selective_add::set_LUT_permutation(bool LUT_permutation)
//{
//    do_LUT_permutation = LUT_permutation;
//}
//
//bool selective_add::next_m0() {
//    ERROR("Not implemented yet.", selective_add::next_m0())
//    return false;
//}
//bool selective_add::next_m1() {
//
//    Permutator permut(&permut_max,true,&permut_min);
//    //permut.permutationCntVec = permut_state;
//
//    permut.printPermutation();
//    bool result = permut.nextPermutation();
//    permut.printPermutation();
//    // TODO MH-DEBUG permut_state = permut.permutationCntVec;
//    mode_1_current_operation_set.clear();
//    mode_1_current_operation_set =(possible_operations[permut_state[0]]);
//    return result;
//}
//
//void selective_add::set_mode_list()
//{
//    operation_mode=1;
//    unsigned int permut_variable_count= possible_operations.size()+shifts.size();
//    permut_min.resize(permut_variable_count);
//    permut_max.resize(permut_variable_count);
//    permut_state.resize(permut_variable_count);
//
//    // specify borders for Operation selecting in List mode
//    if (do_LUT_permutation)
//    {
//        permut_state[0] = 0;
//        permut_min[0] = 0;
//        permut_max[0] = possible_operations.size();
//    }
//    else
//    {
//        permut_min[0] = permut_state[0];
//        permut_max[0] = permut_state[0];
//    }
//    // specify borders for shifts
//    if (do_LUT_permutation) {
//        for (unsigned int i = 1; i < shifts.size() + 1; ++i) {
//            permut_state[i] = shifts[i-1];
////            permut_min[i] = shift_config_min[i - 1]; // TODO: FIX!!!! commented to make error silent
//            permut_max[i] = shift_config_max[i - 1];
//        }
//    }
//    else
//    {
//        for (unsigned int i = 1; i < shifts.size() + 1; ++i) {
//            permut_state[i] = shifts[i - 1];
//            permut_min[i] = shifts[i - 1];
//            permut_max[i] = shifts[i - 1];
//        }
//    }
//
//
//}
// TODO: remove or FIX: commented to make error silent
// void selective_add::set_shift_config_max(const std::vector<int> &inputs)
// {
//     shift_config_max = inputs;
// }
// void selective_add::set_shift_config_min(const std::vector<int> &inputs)
// {
//     shift_config_min = inputs;
// }

// void selective_add::reset_config() {}

//void selective_add::set_mode_all() {}
std::set<int> *selective_add::compute()
{
    IF_VERBOSE(9) std::cout << "selective_add: MH Debug Say: Jay" << std::endl;
    calc->compute(this);

    return calc->get_output();
}
void selective_add::init() {
    clear_calc_data();
    from_sp_use = 0; // TODO: Fix!!! THis has to be the current type from the permutation list.
    switch (rccm_search_space[from_sp_use]) {
        case typ_A:
            calc = static_cast<calc_base *>(new calc_selective_adder_typ_a);
            break;
        case typ_B:
            calc = static_cast<calc_base *>(new calc_selective_adder_typ_b);
            break;
        case typ_C:
            ERROR("Type c is not supported yet", "selective_add::compute()")
            break;
        default:
            ERROR("Invalid Type", "selective_add::compute()");
    }
}

void selective_add::clear_calc_data() {
    if (this->calc != nullptr)
    {
        delete calc;
    }
}

std::set<int> selective_add::get_operation_set() //return the current subset of operations during permutation.
{
    //MH TODO: Make this Genereic and dependent from next_step()
    std::set<int> my_set = {0,1,2,3};
    return my_set;
}

int selective_add::get_shift(unsigned int input_no)//return the current subset of shifts during permutation.
{

    //MH TODO: Make this Genereic and dependent from next_step()
    switch(input_no)
    {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        default: return 0;
    };
}

std::set<int>* gen_shift(std::set<int>* input_set, int shift)
{
    IF_VERBOSE(9) std::cout << "Enter gen_shift"<< std::endl;
    IF_VERBOSE(10) std::cout << "input_set is: "<< *input_set << std::endl;
    IF_VERBOSE(10) std::cout << "shift is: "<< shift<< std::endl;


    std::set<int>* result = new std::set<int>();

    for(int i:(*input_set))
    {
        result->insert(i << shift);
    }
    IF_VERBOSE(10) std::cout << "result_set is: "<< *result << std::endl;
    return result;
};