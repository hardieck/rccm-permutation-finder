//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYP_A_H
#define ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYP_A_H
#include "selective_adder_base.h"

class selective_adder_typ_a : public selective_adder_base
{
    public:
    selective_adder_typ_a();
	std::set<int> compute();
};


#endif //ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYP_A_H
