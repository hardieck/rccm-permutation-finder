//
// Created by hardieck on 9/20/19.
//

#ifndef ADDNET_PERMUTATOR_RCCM_BASE_H
#define ADDNET_PERMUTATOR_RCCM_BASE_H

#include <string>
#include <vector>
#include <set>
#include "evaluate_result.h"
#include "selective_adder_base.h"
#include "base_obj.h"


class rccm_base : public base_obj
{
public:
	rccm_base();

	void run_all_cases();
	virtual std::set<int>compute()=0;
	config_rccm* set_config(string input);
protected:
	std::vector<selective_adder_base*> s_add;
	config_rccm* config;
	std::vector<evaluate_result*> results;
	bool next_step();

};


#endif //ADDNET_PERMUTATOR_RCCM_BASE_H
