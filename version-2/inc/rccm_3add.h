//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_RCCM_3ADD_H
#define ADDNET_PERMUTATOR_V2_RCCM_3ADD_H

#include "rccm_base.h"
#include "selective_adder_typ_a.h"
#include "selective_adder_typ_b.h"

class rccm_3add : public rccm_base
{
public:
	rccm_3add()
	{
		this->config = new config_rccm();
		this->results.push_back(new evaluate_result());
		this->s_add.push_back(new selective_adder_typ_a());
		this->s_add.push_back(new selective_adder_typ_b());

	}
	std::set<int>compute()
	{
		//example computation...:
		std::set<int> input;
		input.insert(1);

		s_add[0]->set_inputs(0,input);
		s_add[0]->set_inputs(1,input);
		s_add[0]->set_inputs(2,input);
		s_add[0]->compute();

		s_add[1]->set_inputs(0,s_add[0]->get_output());
		s_add[1]->set_inputs(1,s_add[0]->get_output());
		s_add[1]->compute();

		return s_add[1]->get_output();;
	};
};


#endif //ADDNET_PERMUTATOR_V2_RCCM_3ADD_H
