//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H

#include <set>
#include <vector>
#include "selective_add.h"
#include "base_obj.h"

class calc_selective_adder_base : public base_obj
{
public:
    calc_selective_adder_base();
	virtual std::set<int> compute(selective_add &parent_sel_add)=0;
	unsigned int get_no_of_inputs();
	std::set<int>& get_output();

	void set_inputs(unsigned int no, std::set<int> &input_set);

	selective_add * convfg;



protected:
	std::vector<std::set<int> > inputs;
	std::vector<int> shifts;
	std::set<int> output;
	unsigned int no_of_inputs_for_A;
	unsigned int no_of_inputs_for_B;


	unsigned int get_no_of_outputs();

	int set_input(unsigned int input_no, std::set<int>);

public:
    static const spec_sel_add spec;
};
const spec_sel_add calc_selective_adder_base::spec(1,1,1,1);


#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H
