//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_BASE_H
#define ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_BASE_H

#include <set>
#include <vector>
#include "config_selective_add.h"

class selective_adder_base
{
public:
	selective_adder_base();
	virtual std::set<int> compute()=0;
	unsigned int get_no_of_inputs();
	unsigned int get_no_of_inputs_for_port_A();
	unsigned int get_no_of_inputs_for_port_B();
	std::set<int>& get_output();

	void set_inputs(unsigned int no, std::set<int> &input_set);

	config_selective_add * convfg;



protected:
	std::vector<std::set<int> > inputs;
	std::vector<int> shifts;
	std::set<int> output;
	unsigned int no_of_inputs_for_A;
	unsigned int no_of_inputs_for_B;


	unsigned int get_no_of_outputs();

	int set_input(unsigned int input_no, std::set<int>);
};


#endif //ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_BASE_H
