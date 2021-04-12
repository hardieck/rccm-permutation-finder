//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H

#include <set>
#include <vector>
#include "selective_add.h"
#include "base_obj.h"

class calc_selective_adder_base : public calc_base
{
public:
    calc_selective_adder_base();
    virtual std::set<int>* compute(base_obj *parent_)=0;
    int set_input(unsigned int input_no, std::set<int>);
	std::set<int>* get_output();

	void set_inputs(unsigned int no, std::set<int> &input_set);

protected:
	std::vector<std::set<int> > inputs;
	std::vector<int> shifts;
	std::set<int> output;
public:


public:
    const spec_sel_add spec = spec_sel_add(1,1,1,1);
};

#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H
