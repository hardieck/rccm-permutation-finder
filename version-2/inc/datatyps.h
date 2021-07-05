//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_DATATYPS_H
#define ADDNET_PERMUTATOR_V2_DATATYPS_H

enum rccm_type // add a type for each rccm dataflow structure / Connection Structure  (without shifts or selecetiv adder specification)
{
    typ_C1 = 1, // 1 add (single selective adder)
    typ_C2 = 2, // 2 add (two selective adders in a row)
    typ_C3 = 3,  // 3 add (to selective adder besides each other followed by a third to fuse the outputs)
    typ_C4 = 4  // 4 add ()

};

enum sel_add_type // add a type for each selective adder option
{
    typ_A = 1,
    typ_B = 2,
    typ_C = 3
};


enum config_level // different // shal probably be removed
{
    operation = 1,
    shifts = 2,
    structure = 3,
    all = 4
};

class spec_sel_add
{
public:
    spec_sel_add(unsigned int input_count_A,unsigned int input_count_B,unsigned int diff_operation_count,unsigned int operation_set_size)
    {
        this->input_count_A = input_count_A;
        this->input_count_B = input_count_B;
        this->diff_operation_count = diff_operation_count;
        this->operation_set_size = operation_set_size;
        this->usualy_used_sets = usualy_used_sets;

    };
    unsigned int input_count_A; // number of inputs for inputs A
    unsigned int input_count_B; //number of inputs for inputs B
    unsigned int diff_operation_count; // number of different operations
    unsigned int operation_set_size; // number of operation supported by implementation
    vector<set<int>> usualy_used_sets; // to init a restriced set selection. (optional)

    spec_sel_add& operator=(const spec_sel_add& rhs)
    {
        this->input_count_A = rhs.input_count_A;
        this->input_count_B = rhs.input_count_B;
        this->diff_operation_count = rhs.diff_operation_count;
        this->operation_set_size = rhs.operation_set_size;
        this->usualy_used_sets = rhs.usualy_used_sets;
        return (*this);
    }
};
class spec_rccm
{
public:
    spec_rccm(unsigned int add_sel_count)
    {
        this->add_sel_count = add_sel_count;
    };
    spec_rccm& operator=(const spec_rccm& rhs)
    {
        this->add_sel_count = rhs.add_sel_count;
        return (*this);
    }
    unsigned int add_sel_count;
};

#endif //ADDNET_PERMUTATOR_V2_DATATYPS_H

