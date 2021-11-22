//
// Created by hardieck on 9/20/19.
//

#ifndef ADDNET_PERMUTATOR_RCCM_BASE_H
#define ADDNET_PERMUTATOR_RCCM_BASE_H

#include <string>
#include <vector>
#include <set>
#include "evaluate_result.h"
#include "calc_selective_adder_base.h"
#include "calc_base.h"
#include "rccm.h"


class calc_rccm_base : public calc_base
{
public:
    virtual rccm_type type() const {return rccm_type_NAN;}
	calc_rccm_base();

protected:
    const spec_rccm spec = spec_rccm(1);
};


#endif //ADDNET_PERMUTATOR_RCCM_BASE_H
