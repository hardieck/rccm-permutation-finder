//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_RCCM_H
#define ADDNET_PERMUTATOR_V2_RCCM_H

#include <vector>
#include <string>

#include "selective_add.h"
#include "calc_rccm_base.h"
#include "permutator.h"

class rccm : public base_obj
{
public:
	rccm();
    ~rccm();

    std::set<int>* compute();
    calc_base* calc = nullptr; // need to be calc base instead of calc_rccm_base to prevent circular dependency

	std::string get_config();
	bool set_config(std::string new_config);
    bool parse_config_string(string);

	bool next_config();
    void reset_config();

    selective_add* get_sel_add(unsigned int no);
    std::vector<rccm_type> rccm_search_space;
    unsigned int from_sp_use;

    std::vector<selective_add> sel_add; // store the selective adder objects (can differ in size for any connection Structure)
protected:
    config_helper_obj conv_helper;// only used by next_config to handle the reset.
    void delete_calc();
};


#endif //ADDNET_PERMUTATOR_V2_RCCM_H
