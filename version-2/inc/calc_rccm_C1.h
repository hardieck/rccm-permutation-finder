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
        IF_VERBOSE(4) std::cout << "Enter Function: calc_rccm_C1/compute:" << std::endl;
        rccm* parent = (rccm*) parent_;
        IF_VERBOSE(5) std::cout << "Parent infos: sel_add.size()=" << parent->sel_add.size() << std::endl;


        // clear all calculation data from last run:
        for (auto& i: (parent->sel_add))
        {
            i.init();
        }
        //parent->sel_add[0].init();

        //Start with new calculations and describing the dataflow

        IF_VERBOSE(5) std::cout << "Set input of first selective_add to set:{1}" << std::endl;
        std::set<int> prime_input = {1}; // set the input element

        IF_VERBOSE(9) std::cout << "input Count of A is: "<< ((calc_selective_adder_base*)parent->sel_add[0].calc)->get_spec().input_count_A << std::endl;
        IF_VERBOSE(9) std::cout << "input Count of B is: "<< ((calc_selective_adder_base*)parent->sel_add[0].calc)->get_spec().input_count_B << std::endl;
        const int input_count = ((calc_selective_adder_base*)parent->sel_add[0].calc)->get_spec().input_count_A + ((calc_selective_adder_base*)parent->sel_add[0].calc)->get_spec().input_count_B;
        IF_VERBOSE(8) std::cout << "input Count is: "<<input_count << std::endl;

        for (int i=0; i < input_count;++i)
        {
            IF_VERBOSE(9) std::cout << "Set selective_add set input nr: " << i << std::endl;
            parent->sel_add[0].calc->set_input(i,&prime_input);
        }

        IF_VERBOSE(5) cout << "inner inputs:" << parent->sel_add[0].calc->get_inputs() << std::endl;
        IF_VERBOSE(4) cout << "Compute selective add [0]"<< std::endl;
        parent->sel_add[0].compute();
        IF_VERBOSE(5)cout << "inner inputs:" << parent->sel_add[0].calc->get_inputs() << std::endl;

        output.clear();
        output = *(parent->sel_add[0].calc->get_output());
        IF_VERBOSE(4) std::cout << "output is:" << (output) << std::endl;

        return &output;

    }
    const spec_rccm spec = spec_rccm(1);
};
//const spec_rccm calc_rccm_C1::spec(1);

#endif //ADDNET_PERMUTATOR_V2_CALC_RCCM_C1_H
