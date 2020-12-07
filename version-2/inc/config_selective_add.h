//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CONFIG_SELECTIVE_ADD_H
#define ADDNET_PERMUTATOR_V2_CONFIG_SELECTIVE_ADD_H

#include "debug.h"
#include <vector>
#include <set>

class config_selective_add
{
public:
    //function for set up and use of permutations
	void set_shift_config_max(std::vector<int>); // set the maximal shift values (upper bound for permutaton)
    void set_shift_config_min(std::vector<int>); // set the minimal shift values (lower bound for permutaton)
    void reset_config(); // reset the current config cunters to the inital values specified by min-shift max-shift and possible operations.
    bool next_config(); // go to the next configuration. (return false if it was the last configuration. true otherwise)

    bool get_shift_permutation() const;
    void set_shift_permutation(bool shift_permutation);
    bool get_LUT_permutation() const;
    void set_LUT_permutation(bool set_LUT_permutation);

    // functions for use from Computation function
	std::set<int> get_operation_set();
    std::vector<int> get_shift_config();



	void make_possible_set_n_from_m(unsigned int n, unsigned int m);
    void add_possible_set(set<int> s);

protected:
    bool operation_mode; //0: permutate all possible combinations of the operations 1: just use operation combinations from a specific set
    bool do_shift_permutation; // allow permutation of shifts
    bool do_LUT_permutation; // allow permutation of operations

    std::vector<int> mode_0_current_operation_set; // current permutation state of operations for mode 0 and 1
    std::vector<std::set<int>> possible_operations; // set of allowed operation combinations for mode 1
    unsigned int number_of_different_operations; // set the upper bound of operations for mode 0
    unsigned int number_of_simultan_operations; // set the set size for the operations in mode 0
    std::vector<int> shifts; // current permutation state of operations for shift
    bool next_m0(); // do permutation for mode 0
    bool next_m1(); // do permutation for mode 1
};


#endif //ADDNET_PERMUTATOR_V2_CONFIG_SELECTIVE_ADD_H
