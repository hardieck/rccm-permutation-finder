//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CONFIG_SELECTIVE_ADD_H
#define ADDNET_PERMUTATOR_V2_CONFIG_SELECTIVE_ADD_H

#include <vector>
#include <set>

class config_selective_add
{
public:
	std::vector<int> get_shift_config();
	void set_shift_config(std::vector<int>);

	std::vector<int> shifts;
	int sel_add_operation_set;
	std::set<int> get_operation_set();
	bool next_config();

	bool do_shift_permutation;
	bool do_LUT_permutation;

protected:
	std::vector<std::set<int>> possible_operations;


};


#endif //ADDNET_PERMUTATOR_V2_CONFIG_SELECTIVE_ADD_H
