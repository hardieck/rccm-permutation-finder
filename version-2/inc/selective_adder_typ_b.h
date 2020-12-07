//
// Created by hardieck on 10/8/19.
//

#ifndef ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYP_B_H
#define ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYP_B_H
#include "selective_adder_base.h"

class selective_adder_typ_b : public selective_adder_base
{
    public:
    selective_adder_typ_b();
	std::set<int> compute();
};


#endif //ADDNET_PERMUTATOR_V2_SELECTIVE_ADDER_TYPE_B_H
