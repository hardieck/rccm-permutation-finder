//
// Created by hardieck on 12/5/21.
//

#include "../inc/calc_selective_adder_typ_c.h"

//get_spec() need to be in each derived class to choose the correct spec wehen calld from base pointer
const spec_sel_add calc_selective_adder_typ_c::get_spec()
{
    IF_VERBOSE(9)ENTER_FUNCTION("calc_selective_adder_typ_c::get_spec()")
    IF_VERBOSE(9)LEAVE_FUNCTION("calc_selective_adder_typ_c::get_spec()")
    return spec;
}

std::set<int>* calc_selective_adder_typ_c::compute(base_obj *parent_) {
    IF_VERBOSE(5)ENTER_FUNCTION("calc_selective_adder_typ_c::compute()")
    selective_add *parent = (selective_add *) parent_;


    IF_VERBOSE(6) cout << "inputs:" << inputs << std::endl;

    output.clear();


//    0	A	+	A	2A
//    1	A	+	B	A+B
//    2	A	+	-B 	A-B
//    3	A	+	0	A+0
//    4	-A	+	B	-A+B
//    5	-A	+	0	-A
//    6	B	+	B	2B
//    7	B	+	0	B
//    8	-B 	+	0	-B
//    9	0	+	0	0
// ----------- Offset functions -----------
//    a	A	+	-1	A-1
//    b	-A	+	-1	-A-1
//    c	B	+	-1	B-1
//    d	-B 	+	-1	-B-1
//    e	0	+	-1	-1
//    f	-1	+	-1	-2

    IF_VERBOSE(8) std::cout << "load inputs into local names:" << std::endl;

    //read shifts from config and export them to the inputs
    std::set<int> &A1 = *gen_shift(inputs[0], parent->get_shift(0));
    std::set<int> &B1 = *gen_shift(inputs[1], parent->get_shift(1));


    IF_VERBOSE(9) std::cout << "shifts are:" << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 0:" << parent->get_shift(0) << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 1:" << parent->get_shift(1) << std::endl;

    IF_VERBOSE(9) std::cout << "input Sets after shifts are:" << std::endl;
    IF_VERBOSE(9) std::cout << "A1:" << A1 << std::endl;
    IF_VERBOSE(9) std::cout << "B1:" << B1 << std::endl;

    IF_VERBOSE(8) std::cout << "calculate specified configs" << std::endl;
    IF_VERBOSE(8) std::cout << "operation set is:" << parent->get_operation_set() << std::endl;

    for (int conf: parent->get_operation_set()) {
        IF_VERBOSE(9) std::cout << "calculate operation from config:  " << conf << std::endl;
        switch (conf) {
            case 0:
                for (int a: A1) {                 { output.insert( a + a); }} //  A1 + A1
                break;
            case 1:
                for (int a: A1) { for (int b: B1) { output.insert( a + b); }} //  A1 + B1
                break;
            case 2:
                for (int a: A1) { for (int b: B1) { output.insert( a - b); }} //  A1 - B1
                break;
            case 3:
                for (int a: A1) {                 { output.insert( a + 0); }} //  A1 + 0
                break;
            case 4:
                for (int a: A1) { for (int b: B1) { output.insert(-a + b); }} // -A1 + B1
                break;
            case 5:
                for (int a: A1) {                 { output.insert(-a + 0); }} // -A1 + 0
                break;
            case 6:
                                { for (int b: B1) { output.insert( b + b); }} //  B1 + B1
                break;
            case 7:
                for (int a: A1) { for (int b: B1) { output.insert( 0 + b); }} //  0 + B1
                break;
            case 8:
                                { for (int b: B1) { output.insert( 0 - b); }} //  0 - B1
                break;
            case 9:
                                { for (int b: B1) { output.insert( 0 + 0); }} //   0 + 0
                break;
            default: ERROR("unsupported Operation","calc_selective_adder_typ_c::compute(base_obj *parent_)")
        }
    }
    delete &A1;
    delete &B1;
    IF_VERBOSE(7) std::cout << "calculation result is:" << output << std::endl;
    return &output;
}
