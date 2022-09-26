//
// Created by hardieck on 12/5/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_C_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_C_H
#include "calc_selective_adder_base.h"

class calc_selective_adder_typ_c : public calc_selective_adder_base
{
public:
    calc_selective_adder_typ_c()
    {
        IF_VERBOSE(6) ENTER_FUNCTION("calc_selective_adder_typ_c::calc_selective_adder_typ_c()")
        init();
    };
    virtual sel_add_type type() const {return typ_C;}
    std::set<int>* compute(base_obj *parent_);
    virtual const spec_sel_add get_spec();
private:
    const spec_sel_add spec = spec_sel_add(1,1,10,4,{{0,1,6,9}});
    //DO NOT USE local spec value!!! use get_spec()! cause derived classes overload get_spec() but don't overload spec...
};


#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_C_H
