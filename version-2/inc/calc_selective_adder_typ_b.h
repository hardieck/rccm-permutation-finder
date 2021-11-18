//
// Created by hardieck on 10/8/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_B_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_B_H
#include "calc_selective_adder_base.h"
#include <set>

class calc_selective_adder_typ_b : public calc_selective_adder_base
{
    public:
    calc_selective_adder_typ_b();
    std::set<int>* compute(base_obj *parent_);
    static const spec_sel_add spec;
};

const spec_sel_add calc_selective_adder_typ_b::spec = spec_sel_add(2,2,16,4);
//const spec_sel_add calc_selective_adder_typ_b::spec = spec_sel_add(3,1,7,4);

#endif //ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYPE_B_H
