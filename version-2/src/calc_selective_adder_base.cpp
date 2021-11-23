//
// Created by hardieck on 9/27/19.
//

#include "../inc/calc_selective_adder_base.h"
#include <iostream>
calc_selective_adder_base::calc_selective_adder_base(){}
calc_selective_adder_base::~calc_selective_adder_base(){}
void calc_selective_adder_base::init()
{
    //DO NOT USE local spec value!!! use get_spec()! cause derived classes overload get_spec() but don't overload spec...
    IF_VERBOSE(7) ENTER_FUNCTION("calc_selective_adder_base::init()")
    IF_VERBOSE(8) std::cout << "resize inputs to:" << get_spec().input_count_A+get_spec().input_count_B << endl;
    IF_VERBOSE(9) std::cout << "used spec is:" << endl;
    IF_VERBOSE(9) get_spec().print_spec();;
    inputs.resize(get_spec().input_count_A+get_spec().input_count_B);
    output.clear();
}
const spec_sel_add calc_selective_adder_base::get_spec()
{
    IF_VERBOSE(9)ENTER_FUNCTION("calc_selective_adder_base::get_spec()")
    IF_VERBOSE(9)LEAVE_FUNCTION("calc_selective_adder_base::get_spec()")
    return spec;
}

//
//unsigned int calc_selective_adder_base::get_no_of_outputs()
//{
//	return 1;
//}
//
//
//std::set<int> calc_selective_adder_base::compute()
//{
//	IF_VERBOSE(8) std::cout << "Enter funktion: calc_selective_adder_base/compute" << std::endl;
//	return std::set<int>();
//}
//
//int calc_selective_adder_base::set_input(unsigned int input_no, std::set<int> input_set)
//{
//	this->inputs[input_no] = input_set;
//	return 0;
//}
//unsigned int calc_selective_adder_base::get_no_of_inputs()
//{
//	return this->spec.input_count_A+spec.input_count_B;
//}
//
//std::set<int>& calc_selective_adder_base::get_output()
//{
//	return this->output;
//}
//
//void calc_selective_adder_base::set_inputs(unsigned int no, std::set<int> &input_set)
//{
//	IF_VERBOSE(8) std::cout << "Enter function: calc_selective_adder_base/set_inputs" << std::endl;
//	if (inputs.size() < no)
//	{
//		ERROR("inputs size does not match. no = "  << no << "; inputs.size() = " << inputs.size(),"calc_selective_adder_base::set_inputs()")
//	}
//	this->inputs[no].clear();
//	this->inputs[no]=input_set;
//}