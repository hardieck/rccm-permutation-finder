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
    virtual sel_add_type type() const {return sel_add_type_NAN;}
    calc_selective_adder_base();
    virtual ~calc_selective_adder_base();
    virtual std::set<int>* compute(base_obj *parent_)=0;

protected:
	std::vector<int> shifts;
public:


public:
    virtual const spec_sel_add get_spec()=0;
protected:
    void init();
private:
    const spec_sel_add spec = spec_sel_add(1,1,1,1);
    //DO NOT USE local spec value!!! use get_spec()!
    //cause derived classes overload get_spec() but don't overload spec.

};

#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_BASE_H
