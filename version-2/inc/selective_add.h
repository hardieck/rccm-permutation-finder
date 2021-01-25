//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_SELECTIVE_ADD_H
#define ADDNET_PERMUTATOR_V2_SELECTIVE_ADD_H

#include "debug.h"
#include "base_obj.h"

#include <vector>
#include <set>

class selective_add : public base_obj
{
public:

    std::set<int> compute();
    void reset_config(); // reset the current config cunters to the inital values specified by min-shift max-shift and possible operations.
    bool next_config(); // go to the next configuration. (return false if it was the last configuration. true otherwise)

    void set_mode_list();
    void set_mode_all();//TODO implement

    std::vector<sel_add_type> rccm_search_space;
    unsigned int from_sp_use;



    // functions for use from Computation function
	std::set<int> get_operation_set();
    std::vector<int> get_shift_config();



	void make_possible_set_n_from_m(unsigned int n, unsigned int m);
    void add_possible_set(set<int> s);

protected:
    bool operation_mode; //0: permutate all possible combinations of the operations 1: just use operation combinations from a specific set
    bool do_shift_permutation; // allow permutation of shifts
    bool do_LUT_permutation; // allow permutation of operations

    std::set<int> mode_1_current_operation_set; // current permutation state of operations for mode 0 and 1
    std::vector<int> mode_0_current_operation_set; // current permutation state of operations for mode 0 and 1
    std::vector<std::set<int>> possible_operations; // set of allowed operation combinations for mode 1
    unsigned int number_of_different_operations; // set the upper bound of operations for mode 0
    unsigned int number_of_simultan_operations; // set the set size for the operations in mode 0
    std::vector<int> shifts; // current permutation state of operations for shift
    std::vector<int> shift_config_max; // current permutation state of operations for shift
    std::vector<int> shift_config_min; // current permutation state of operations for shift
    bool next_m0(); // do permutation for mode 0
    bool next_m1(); // do permutation for mode 1

    //comunication vectors for use with Permutator
    std::vector<int> permut_state;
    std::vector<int> permut_min;
    std::vector<int> permut_max;
};


#endif //ADDNET_PERMUTATOR_V2_SELECTIVE_ADD_H


