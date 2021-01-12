//
// Created by hardieck on 9/20/19.
//

#include "../inc/calc_rccm_base.h"


calc_rccm_base::calc_rccm_base()
{
}

void calc_rccm_base::run_all_cases()
{

	bool in_progress= true;
	while(in_progress ==true)
	{
        compute();
		//for loop for all evaluate_result

		in_progress = next_step();
	}

}

bool calc_rccm_base::next_step()
{
	return this->config->next_config(); //return true if still in progress
}

rccm *calc_rccm_base::set_config(string input)
{
	//do all configuration stuff...
	this->config = new rccm();
	return config;
}
