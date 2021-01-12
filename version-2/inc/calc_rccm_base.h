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
#include "base_obj.h"
#include "rccm.h"


class calc_rccm_base : public base_obj
{
public:
	calc_rccm_base();

	virtual std::set<int>compute(rccm &parent_rccm)=0;
protected:
	std::vector<calc_selective_adder_base*> s_add;
	rccm* config;
	std::vector<evaluate_result*> results;
	bool next_step();

};


#endif //ADDNET_PERMUTATOR_RCCM_BASE_H
