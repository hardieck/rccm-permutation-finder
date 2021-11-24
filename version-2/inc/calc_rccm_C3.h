////
//// Created by hardieck on 9/27/19.
////


#ifndef ADDNET_PERMUTATOR_V2_CALC_RCCM_TYP_3ADD_H
#define ADDNET_PERMUTATOR_V2_CALC_RCCM_TYP_3ADD_H
#include "calc_rccm_base.h"

class calc_rccm_C3 : public calc_rccm_base
{
public:
    virtual rccm_type type() const {return typ_C3;}
    calc_rccm_C3()
    {
        IF_VERBOSE(8) ENTER_FUNCTION("calc_rccm_C1::calc_rccm_C1()")
        IF_VERBOSE(8) LEAVE_FUNCTION("calc_rccm_C1::calc_rccm_C1()")
    }
    std::set<int>* compute(base_obj *parent_)
    {
        IF_VERBOSE(4) ENTER_FUNCTION("calc_rccm_C1::compute(base_obj *parent_")
        rccm* parent = static_cast<rccm *>(parent_);
        IF_VERBOSE(5) std::cout << "Parent infos: sel_add.size()=" << parent->sel_add.size() << std::endl;

        // clear all calculation data from last run:
        for (int i=0; i < parent->sel_add.size(); ++i)
        {
            IF_VERBOSE(9) std::cout << "init sel_add[" << i << "]" << std::endl;
            parent->sel_add[i].init();
        }

        //Start with new calculations and describing the dataflow

        IF_VERBOSE(5) std::cout << "Set input of first selective_add to set:{1}" << std::endl;
        std::set<int> prime_input = {1}; // set the input element

        IF_VERBOSE(6) std::cout << "parent: "<< parent << std::endl;
        IF_VERBOSE(6) std::cout << "(calc_selective_adder_base*)parent->sel_add[0].calc "<< parent->sel_add[0].calc << std::endl;
        IF_VERBOSE(6) std::cout << "(calc_selective_adder_base*)parent->sel_add[0].calc->type "<< ((calc_selective_adder_base*)(parent->sel_add[0].calc))->type() << std::endl;
        IF_VERBOSE(6) std::cout << "((calc_selective_adder_base*)parent->sel_add[0].calc)->get_spec().print_spec() " << std::endl;
        spec_sel_add my_s = ((calc_selective_adder_base*)(parent->sel_add[0].calc))->get_spec();

        // set inputs for sel add 0
        int input_count = ((calc_selective_adder_base*)(parent->sel_add[0].calc))->get_spec().input_count_A + ((calc_selective_adder_base*)parent->sel_add[0].calc)->get_spec().input_count_B;
        for (int i=0; i < input_count;++i)
        {
            IF_VERBOSE(9) std::cout << "Set selective_add set input nr: " << i << std::endl;
            parent->sel_add[0].calc->set_input(i,&prime_input);
        }
        IF_VERBOSE(5) cout << "inner inputs:" << parent->sel_add[0].calc->get_inputs() << std::endl;
        IF_VERBOSE(4) cout << "Compute selective add [0]"<< std::endl;
        parent->sel_add[0].compute();

        // set inputs for sel add 1
        input_count = ((calc_selective_adder_base*)(parent->sel_add[1].calc))->get_spec().input_count_A + ((calc_selective_adder_base*)parent->sel_add[1].calc)->get_spec().input_count_B;
        for (int i=0; i < input_count;++i)
        {
            IF_VERBOSE(9) std::cout << "Set selective_add set input nr: " << i << std::endl;
            parent->sel_add[1].calc->set_input(i,&prime_input);
        }
        IF_VERBOSE(5) cout << "inner inputs:" << parent->sel_add[1].calc->get_inputs() << std::endl;
        IF_VERBOSE(4) cout << "Compute selective add [1]"<< std::endl;
        parent->sel_add[1].compute();


        // set inputs for sel add 2
        // set inputs for A
        for (int i=0; i < ((calc_selective_adder_base*)(parent->sel_add[2].calc))->get_spec().input_count_A;++i)
        {
            IF_VERBOSE(9) std::cout << "Set selective_add set input nr: " << i << std::endl;
            parent->sel_add[2].calc->set_input(i,parent->sel_add[0].calc->get_output());
        }
        // set inputs for B
        input_count = ((calc_selective_adder_base*)(parent->sel_add[2].calc))->get_spec().input_count_A + ((calc_selective_adder_base*)parent->sel_add[2].calc)->get_spec().input_count_B;
        for (int i=((calc_selective_adder_base*)(parent->sel_add[2].calc))->get_spec().input_count_A; i < input_count;++i)
        {
            IF_VERBOSE(9) std::cout << "Set selective_add set input nr: " << i << std::endl;
            parent->sel_add[2].calc->set_input(i,parent->sel_add[1].calc->get_output());
        }
        parent->sel_add[2].compute();

        output.clear();
        output = *(parent->sel_add[2].calc->get_output());
        IF_VERBOSE(4) std::cout << "output is:" << (output) << std::endl;

        IF_VERBOSE(4) LEAVE_FUNCTION("calc_rccm_C1::compute(base_obj *parent_")
        return &output;
    }
    const spec_rccm spec = spec_rccm(3);
};


#endif //ADDNET_PERMUTATOR_V2_CALC_RCCM_TYP_3ADD_H
