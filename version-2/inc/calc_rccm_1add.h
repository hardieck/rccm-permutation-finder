//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
#define ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
#include "calc_rccm_base.h"
#include "calc_selective_adder_typ_a.h"
#include "calc_selective_adder_typ_b.h"

class calc_rccm_1add : public calc_rccm_base
{
public:
    calc_rccm_1add()
    {
        IF_VERBOSE(9) std::cout << "Enter Funktion: calc_rccm_1add/construktor:" << std::endl;
    }
    std::set<int>* compute(base_obj *parent_)
    {
        rccm* parent = (rccm*) parent_;
        std::cout << "parent infos: sel_add.size()=" << parent->sel_add.size() << std::endl;
        IF_VERBOSE(9) std::cout << "calc_rccm_1add: MH Debug Say: Jay" << std::endl;

        set<int> prime_input = {1};
        parent->sel_add[0].compute();
        parent->sel_add[0].calc->set_input(0,&prime_input);
        parent->sel_add[0].calc->set_input(1,&prime_input);
        parent->sel_add[0].calc->set_input(2,&prime_input);
        parent->sel_add[0].calc->set_input(3,&prime_input);
        parent->sel_add[0].compute();
        return {0};
    }
    const spec_rccm spec = spec_rccm(1);
};
//const spec_rccm calc_rccm_1add::spec(1);

#endif //ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
