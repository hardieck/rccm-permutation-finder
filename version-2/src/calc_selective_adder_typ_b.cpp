//
// Created by hardieck on 10/8/19.
//

#include "../inc/calc_selective_adder_typ_b.h"

//get_spec() need to be in each derived class to choose the correct spec wehen calld from base pointer
spec_sel_add calc_selective_adder_typ_b::get_spec()
{
    return spec;
}

std::set<int>* calc_selective_adder_typ_b::compute(base_obj *parent_) {
    IF_VERBOSE(5)ENTER_FUNCTION("calc_selective_adder_typ_b::compute()")
    selective_add *parent = (selective_add *) parent_;


    IF_VERBOSE(6) cout << "inputs:" << inputs << std::endl;

    output.clear();
    //output.insert(*inputs[0]->begin());


    //if (this->get_no_of_inputs() < 4){std::cout << "ERROR: not enough inputs are specified (" << this->get_no_of_inputs() << " inputs are specified)"  << std::endl;}
    //if (this->get_no_of_inputs() <= 0) {std::cout << "ERROR: no inputs specified" << std::endl; exit(-1);}

    //00  A1 +B1
    //01  A1 +B2
    //02  A1 -B1
    //03  A1 -B2
    //04 -A1 +B1
    //05 -A1 +B2
    //06 -A1 -B1
    //07 -A1 -B2
    //08  A2 +B1
    //09  A2 +B2
    //10  A2 -B1
    //11  A2 -B2
    //12 -A2 +B1
    //13 -A2 +B2
    //14 -A2 -B1
    //15 -A2 -B2

    IF_VERBOSE(8) std::cout << "load inputs into local names:" << std::endl;

    //read shifts from config and export them to the inputs
    std::set<int> &A1 = *gen_shift(inputs[0], parent->get_shift(0));
    std::set<int> &A2 = *gen_shift(inputs[1], parent->get_shift(1));
    std::set<int> &B1 = *gen_shift(inputs[2], parent->get_shift(2));


    IF_VERBOSE(9) std::cout << "shifts are:" << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 0:" << parent->get_shift(0) << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 1:" << parent->get_shift(1) << std::endl;
    IF_VERBOSE(9) std::cout << "Shift 2:" << parent->get_shift(2) << std::endl;

    IF_VERBOSE(9) std::cout << "input Sets after shifts are:" << std::endl;
    IF_VERBOSE(9) std::cout << "A1:" << A1 << std::endl;
    IF_VERBOSE(9) std::cout << "A2:" << A2 << std::endl;
    IF_VERBOSE(9) std::cout << "B1:" << B1 << std::endl;

    this->output.clear();

    IF_VERBOSE(8) std::cout << "calculate specified configs" << std::endl;
    IF_VERBOSE(8) std::cout << "operation set is:" << parent->get_operation_set() << std::endl;

    for (int conf: parent->get_operation_set()) {
        IF_VERBOSE(9) std::cout << "calculate operation from config:  " << conf << std::endl;
        switch (conf) {
            case 0:
                for (int a: A1) { for (int b: B1) { output.insert(a + b); }} //  A1 + B1
                break;
            case 1:
                for (int a: A1) { for (int b: B1) { output.insert( a - b); }} //  A1 - B1
                break;
            case 2:
                for (int a: A1) {                 { output.insert( a + 0); }} //  A1 + 0
                break;
            case 3:
                for (int a: A1) { for (int b: B1) { output.insert(-a + b); }} // -A1 + B1
                break;
            case 4:
                for (int a: A1) {                 { output.insert(-a + 0); }} //  A1 + 0
                break;
            case 5:
                for (int a: A2) { for (int b: B1) { output.insert( a + b); }} //  A2 + B1
                break;
            case 6:
                for (int a: A2) { for (int b: B1) { output.insert( a - b); }} //  A2 - B1
                break;
            case 7:
                for (int a: A2) {                 { output.insert( a + 0); }} //  A2 + 0
                break;
            case 8:
                for (int a: A2) { for (int b: B1) { output.insert(-a + b); }} // -A2 + B1
                break;
            case 9:
                for (int a: A2) { for (int b: B1) { output.insert(-a + 0); }} //  -A2 + 0
                break;
            case 10:
                for (int a: A2) { for (int b: B1) { output.insert( 0 + b); }} //  0 + B1
                break;
            case 11:
                for (int a: A2) { for (int b: B1) { output.insert( 0 + b); }} //  0 - B1
                break;
            case 12:
                {               {                   output.insert(     0); }} //  0 + 0
                break;

        }
    }
    IF_VERBOSE(7) std::cout << "calculation result is:" << output << std::endl;
    return &output;
}



//----------------------------------------------------------------
//
//    //if (this->get_no_of_inputs() <= 0){std::cout << "ERROR: not enough inputs are specified (" << this->get_no_of_inputs() << " inputs are specified)"  << std::endl;}
//    if (this->get_no_of_inputs() <= 0){std::cout << "ERROR: no inputs specified" << std::endl; exit(-1);}
//
//    //00  A1 +B1
//    //01  A2 +B1
//    //02  A3 +B1
//    //03 -A1 +B1
//    //04 -A2 +B1
//    //05 -A3 +B1
//    //06   0 +B1
//
//	for (int conf: this->convfg->get_operation_set())
//	{
//		std::set<int> &A1 = inputs[0];
//		std::set<int> &A2 = inputs[1];
//		std::set<int> &A3 = inputs[2];
//		std::set<int> &B1 = inputs[3];
//
//        output.clear();
//
//		for (int conf:this->convfg->get_operation_set())
//		{
//			switch (conf)
//			{
//				case 0:	for (int a:A1) { for (int b:B1) { output.insert(a + b); }} break;
//				case 1: for (int a:A2) { for (int b:B1) { output.insert(a + b); }} break;
//				case 2: for (int a:A3) { for (int b:B1) { output.insert(a + b); }} break;
//				case 3: for (int a:A1) { for (int b:B1) { output.insert(-a + b); }} break;
//				case 4:	for (int a:A2) { for (int b:B1) { output.insert(-a + b); }} break;
//				case 5:	for (int a:A3) { for (int b:B1) { output.insert(-a + b); }} break;
//				case 6:	for (int b:B1) { output.insert(b); } break;
//			}
//		}
//	}
//    IF_VERBOSE(7) std::cout << "calculation result is:" << output << std::endl;
