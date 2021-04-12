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
	calc_rccm_base();
    int set_input(unsigned int input_no, std::set<int>);
    std::set<int>* get_output();

	virtual std::set<int>& compute(rccm &parent_rccm)=0;
protected:
	//std::vector<evaluate_result*> results;
	bool next_step();
    const spec_rccm spec = spec_rccm(1);
};


#endif //ADDNET_PERMUTATOR_RCCM_BASE_H
