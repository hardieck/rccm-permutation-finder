//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
#include "calc_selective_adder_base.h"

class calc_selective_adder_typ_a : public calc_selective_adder_base
{
public:
    calc_selective_adder_typ_a()
    {
        IF_VERBOSE(6) ENTER_FUNCTION("calc_selective_adder_typ_b::calc_selective_adder_typ_a()")
        init();
    };
    virtual sel_add_type type() const {return typ_A;}
    std::set<int>* compute(base_obj *parent_);
    virtual const spec_sel_add get_spec();
private:
    const spec_sel_add spec = spec_sel_add(3,1,7,4);
    //DO NOT USE local spec value!!! use get_spec()! cause derived classes overload get_spec() but don't overload spec...
};
//const spec_sel_add calc_selective_adder_typ_a::spec = spec_sel_add(2,2,16,4);






#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
