//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_DATATYPS_H
#define ADDNET_PERMUTATOR_V2_DATATYPS_H

enum rccm_type // add a type for each rccm dataflow structure / Connection Structure  (without shifts or selecetiv adder specification)
{
    typ_A = 1, // 1 add (single selective adder)
    typ_B = 2, // 2 add (two selective adders in a row)
    typ_C = 3  // 3 add (to selective adder besides each other followed by a third to fuse the outputs)
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

#endif //ADDNET_PERMUTATOR_V2_DATATYPS_H
