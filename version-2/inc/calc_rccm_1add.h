//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
#define ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
#include "calc_rccm_base.h"
#include "calc_selective_adder_typ_a.h"
#include "calc_selective_adder_typ_b.h"

class calc_rccm_1add : calc_rccm_base
{
    calc_rccm_1add()
    {
        IF_VERBOSE(9) std::cout << "Enter Funktion: calc_rccm_1add/construktor:" << std::endl;
    }
    std::set<int>compute()
    {

    }
};

#endif //ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
