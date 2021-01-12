//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_RCCM_H
#define ADDNET_PERMUTATOR_V2_RCCM_H

#include "base_obj.h"
#include "selective_add.h"
#include <vector>
#include "permutator.h"
#include <string>

class rccm : public base_obj
{
public:
	rccm();

	std::string get_config();
	std::string get_config_for_implementation();
	bool set_config(std::string input_config);

	std::vector<selective_add> conf_list;
	std::vector<int> add_sell_type_alternatives; // don't know how this will be work when finishes...
	bool next_config(config_level = all);
    std::set<int> compute();

private:
    std::vector<rccm_type> rccm_search_space;
    vector<selective_add> sel_add;

	std::vector<int> ;

};


#endif //ADDNET_PERMUTATOR_V2_RCCM_H
