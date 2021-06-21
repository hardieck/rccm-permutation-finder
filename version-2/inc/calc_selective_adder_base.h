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

protected:
	std::vector<int> shifts;
public:


public:
    spec_sel_add get_spec();
protected:
    spec_sel_add spec = spec_sel_add(1,1,1,1);
    void init();

};

#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H
