//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
#include "calc_selective_adder_base.h"

class calc_selective_adder_typ_a : public calc_selective_adder_base
{
    public:
    calc_selective_adder_typ_a(){
        std::cout << "MH set:" << endl;
        spec = spec_sel_add(2,2,16,4);init();};
    std::set<int>* compute(base_obj *parent);
};
//const spec_sel_add calc_selective_adder_typ_a::spec = spec_sel_add(2,2,16,4);






#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
