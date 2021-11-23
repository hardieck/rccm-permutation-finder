//
// Created by hardieck on 9/27/19.
//

#include "../inc/calc_selective_adder_typ_a.h"

//get_spec() need to be in each derived class to choose the correct spec wehen calld from base pointer
const spec_sel_add calc_selective_adder_typ_a::get_spec()
{
    IF_VERBOSE(9)ENTER_FUNCTION("calc_selective_adder_typ_a::get_spec()")
    IF_VERBOSE(9)LEAVE_FUNCTION("calc_selective_adder_typ_a::get_spec()")
    return spec;
}
std::set<int>* calc_selective_adder_typ_a::compute(base_obj *parent_)
{
    IF_VERBOSE(5)ENTER_FUNCTION("calc_selective_adder_typ_a::compute()")
    selective_add *parent = (selective_add *) parent_;


    IF_VERBOSE(6) cout << "inputs:" << inputs << std::endl;

    output.clear();

    IF_VERBOSE(8) std::cout << "load inputs into local names:" << std::endl;

    //read shifts from config and export them to the inputs
    std::set<int> &A1 = *gen_shift(inputs[0], parent->get_shift(0));
    std::set<int> &A2 = *gen_shift(inputs[1], parent->get_shift(1));
    std::set<int> &A3 = *gen_shift(inputs[2], parent->get_shift(2));
    std::set<int> &B1 = *gen_shift(inputs[3], parent->get_shift(3));


    IF_VERBOSE(9) std::cout << "shifts are:" << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 0:" << parent->get_shift(0) << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 1:" << parent->get_shift(1) << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 2:" << parent->get_shift(2) << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 3:" << parent->get_shift(3) << std::endl;

    IF_VERBOSE(9) std::cout << "input Sets after shifts are:" << std::endl;
    IF_VERBOSE(9) std::cout << "A1:" << A1 << std::endl;
    IF_VERBOSE(9) std::cout << "A2:" << A2 << std::endl;
    IF_VERBOSE(9) std::cout << "A3:" << A3 << std::endl;
    IF_VERBOSE(9) std::cout << "B1:" << B1 << std::endl;

    IF_VERBOSE(8) std::cout << "calculate specified configs" << std::endl;
    IF_VERBOSE(8) std::cout << "operation set is:" << parent->get_operation_set() << std::endl;

    for (int conf: parent->get_operation_set()) {
        IF_VERBOSE(9) std::cout << "calculate operation from config:  " << conf << std::endl;
        switch (conf) {
            case 0:
                for (int a: A1) { for (int b: B1) { output.insert( a + b); }} break; //  A1 + B1
            case 1:
                for (int a: A2) { for (int b: B1) { output.insert( a + b); }} break; //  A2 + B1
            case 2:
                for (int a: A3) { for (int b: B1) { output.insert( a + b); }} break; //  A3 + B1
            case 3:
                for (int a: A1) { for (int b: B1) { output.insert(-a + b); }} break; // -A1 + B1
            case 4:
                for (int a: A2) { for (int b: B1) { output.insert(-a + b); }} break; // -A2 + B1
            case 5:
                for (int a: A3) { for (int b: B1) { output.insert(-a + b); }} break; // -A3 + B1
            case 6:
                                { for (int b: B1) { output.insert(        b); }} break; //   0 + B1
            default:
                parent->perm_operation.pd->printPermutationData();
                parent->perm_operation.printPermutation();
                ERROR("unsupported Operation","calc_selective_adder_typ_a::compute(base_obj *parent_)")
        }
    }
    IF_VERBOSE(7) std::cout << "calculation result is:" << output << std::endl;
    IF_VERBOSE(5)LEAVE_FUNCTION("calc_selective_adder_typ_a::compute()")
    return &output;
}


