//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_DATATYPS_H
#define ADDNET_PERMUTATOR_V2_DATATYPS_H

enum rccm_type // add a type for each rccm dataflow structure / Connection Structure  (without shifts or selecetiv adder specification)
{
    typ_A = 1, // 1 add (single selective adder)
    typ_B = 2, // 2 add (two selective adders in a row)
    typ_C = 3,  // 3 add (to selective adder besides each other followed by a third to fuse the outputs)
    typ_D = 4  // 4 add ()

};

enum sel_add_type // add a type for each selective adder option
{
    typ_a = 1,
    typ_b = 2,
};


enum config_level // different
{
    operation = 1,
    shifts = 2,
    structure = 3,
    all = 4
};

class spec_sel_add
{
public:
    spec_sel_add(unsigned int input_count_A,unsigned int input_count_B,unsigned int diff_operation_count,unsigned int operation_set_size,vector<set<int>> usualy_used_sets)
    {
        this->input_count_A = input_count_A;
        this->input_count_B = input_count_B;
        this->diff_operation_count = diff_operation_count;
        this->operation_set_size = operation_set_size;
        this->usualy_used_sets = usualy_used_sets;

    };
    unsigned int input_count_A; // number of inputs for input A
    unsigned int input_count_B; //number of inputs for input B
    unsigned int diff_operation_count; // number of different operations
    unsigned int operation_set_size; // number of operation supported by implementation
    vector<set<int>> usualy_used_sets; // to init a restriced set selection. (optional)
};
class spec_rccm
{
public:
    spec_rccm(unsigned int add_sel_count)
    {
        this->add_sel_count = add_sel_count;
    };
    unsigned int add_sel_count;
};

#endif //ADDNET_PERMUTATOR_V2_DATATYPS_H

