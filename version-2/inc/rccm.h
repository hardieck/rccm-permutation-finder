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
	bool set_config(std::string new_config);

	bool next_config(config_level = all);
    std::set<int> compute();

private:
    std::vector<rccm_type> rccm_search_space;
    vector<selective_add> sel_add;

    unsigned int used_rccm;

    bool parse_config_string(string);

	std::vector<int> ;

};


#endif //ADDNET_PERMUTATOR_V2_RCCM_H
