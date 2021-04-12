//
// Created by hardieck on 10/8/19.
//

#include "../inc/calc_selective_adder_typ_b.h"

calc_selective_adder_typ_b::calc_selective_adder_typ_b()
{
    //this->spec.input_count_A
    //this->spec.input_count_B
    inputs.resize(this->spec.input_count_A+this->spec.input_count_B);
    shifts.resize(this->spec.input_count_A+this->spec.input_count_B);

    //this->convfg->add_possible_set(std::set<int> {0, 1, 2, 3});
    //this->convfg->add_possible_set(std::set<int> {0, 1, 2, 4});
    //this->convfg->add_possible_set(std::set<int> {0, 1, 2, 5});
    //this->convfg->add_possible_set(std::set<int> {0, 1, 2, 6});
}
std::set<int> calc_selective_adder_typ_b::compute()
{
    IF_VERBOSE(8) std::cout << "Enter function: calc_selective_adder_typ_b/compute" << std::endl;
//
//    //if (this->get_no_of_inputs() <= 0){std::cout << "ERROR: not enough inputs are specified (" << this->get_no_of_inputs() << " inputs are specified)"  << std::endl;}
//    if (this->get_no_of_inputs() <= 0){std::cout << "ERROR: no input specified" << std::endl; exit(-1);}
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
    return output;
}
