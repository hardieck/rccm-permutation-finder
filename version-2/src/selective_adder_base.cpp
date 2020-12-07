//
// Created by hardieck on 9/27/19.
//

#include "../inc/selective_adder_base.h"
#include <iostream>

selective_adder_base::selective_adder_base()
{
	no_of_inputs_for_A=0;
	no_of_inputs_for_B=0;
	inputs.resize(no_of_inputs_for_A+no_of_inputs_for_B);
	shifts.resize(no_of_inputs_for_A+no_of_inputs_for_B);
    this->convfg = new config_selective_add();
}

unsigned int selective_adder_base::get_no_of_outputs()
{
	return 1;
}

std::set<int> selective_adder_base::compute()
{
	IF_VERBOSE(8) std::cout << "Enter funktion: selective_adder_base/compute" << std::endl;
	return std::set<int>();
}

int selective_adder_base::set_input(unsigned int input_no, std::set<int> input_set)
{
	this->inputs[input_no] = input_set;
	return 0;
}
unsigned int selective_adder_base::get_no_of_inputs()
{
	return this->inputs.size();
}
unsigned int selective_adder_base::get_no_of_inputs_for_port_A()
{
	return this->no_of_inputs_for_A;
}
unsigned int selective_adder_base::get_no_of_inputs_for_port_B()
{
	return this->no_of_inputs_for_B;
}

std::set<int>& selective_adder_base::get_output()
{
	return this->output;
}

void selective_adder_base::set_inputs(unsigned int no, std::set<int> &input_set)
{
	IF_VERBOSE(8) std::cout << "Enter function: selective_adder_base/set_inputs" << std::endl;
	if (inputs.size() < no)
	{
		ERROR("input size does not match. no = "  << no << "; input.size() = " << inputs.size(),"selective_adder_base::set_inputs()")
		exit(-1);
	}
	this->inputs[no].clear();
	this->inputs[no]=input_set;
}
