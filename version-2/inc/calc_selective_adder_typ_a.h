//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
#define ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
#include "calc_selective_adder_base.h"

class calc_selective_adder_typ_a : public calc_selective_adder_base
{
    public:
    calc_selective_adder_typ_a();
	std::set<int> compute();
	static const spec_sel_add spec;
};
const spec_sel_add calc_selective_adder_typ_a::spec(2,2,16,4);

calc_selective_adder_typ_a::calc_selective_adder_typ_a()
{
    inputs.resize(no_of_inputs_for_A+no_of_inputs_for_B);
    shifts.resize(no_of_inputs_for_A+no_of_inputs_for_B);

    //this->convfg->add_possible_set(std::set<int> {1, 2, 3, 4});
    //this->convfg->add_possible_set(std::set<int> {0, 2, 8, 11});
    //this->convfg->set_shift_config_max(std::vector<int>{3,3,3,3}); //TODO Make Shift setting nice...
    //this->convfg->set_shift_config_min(std::vector<int>{0,0,0,0}); //TODO Make Shift setting nice...
    this->convfg->set_mode_list();
}





#endif //ADDNET_PERMUTATOR_V2_CALC_SELECTIVE_ADDER_TYP_A_H
