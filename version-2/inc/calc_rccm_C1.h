//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_RCCM_C1_H
#define ADDNET_PERMUTATOR_V2_CALC_RCCM_C1_H
#include "calc_rccm_base.h"
#include "calc_selective_adder_typ_a.h"
#include "calc_selective_adder_typ_b.h"

class calc_rccm_C1 : public calc_rccm_base
{
public:
    calc_rccm_C1()
    {
        IF_VERBOSE(9) std::cout << "Enter Function: calc_rccm_C1/constructor:" << std::endl;
    }
    std::set<int>* compute(base_obj *parent_)
    {
        IF_VERBOSE(9) std::cout << "Enter Function: calc_rccm_C1/compute:" << std::endl;
        rccm* parent = (rccm*) parent_;
        IF_VERBOSE(9) std::cout << "Parent infos: sel_add.size()=" << parent->sel_add.size() << std::endl;


        // clear all calculation data from last run:
        for (auto& i: (parent->sel_add))
        {
            i.init();
        }
        //parent->sel_add[0].init();

        //Start with new calculations and describing the dataflow
        std::set<int> prime_input = {1}; // set the input element

        parent->sel_add[0].calc->set_input(0,&prime_input);
        parent->sel_add[0].calc->set_input(1,&prime_input);
        parent->sel_add[0].calc->set_input(2,&prime_input);
        parent->sel_add[0].calc->set_input(3,&prime_input);
        cout << "inner inputs:" << parent->sel_add[0].calc->get_inputs() << std::endl;
        parent->sel_add[0].compute();
        cout << "inner inputs:" << parent->sel_add[0].calc->get_inputs() << std::endl;

        output.clear();
        output = *(parent->sel_add[0].calc->get_output());
        std::cout << (&output) << ":";
        std::cout << (output) << std::endl;

        return &output;

    }
    const spec_rccm spec = spec_rccm(1);
};
//const spec_rccm calc_rccm_C1::spec(1);

#endif //ADDNET_PERMUTATOR_V2_CALC_RCCM_C1_H
