//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
#define ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
#include "calc_rccm_base.h"
#include "calc_selective_adder_typ_a.h"
#include "calc_selective_adder_typ_b.h"

class calc_rccm_1add : public calc_rccm_base
{
public:
    calc_rccm_1add()
    {
        IF_VERBOSE(9) std::cout << "Enter Funktion: calc_rccm_1add/construktor:" << std::endl;
    }
    std::set<int>compute(rccm &parent_rccm)
    {
        parent_rccm.get_sel_add(0);
        return {0};
    }
    static const spec_rccm spec;
};
const spec_rccm calc_rccm_1add::spec(1);

#endif //ADDNET_PERMUTATOR_V2_CALC_RCCM_1ADD_H
