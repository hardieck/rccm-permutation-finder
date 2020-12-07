//
// Created by hardieck on 9/20/19.
//

#include "../inc/rccm_base.h"


rccm_base::rccm_base()
{
}

void rccm_base::run_all_cases()
{

	bool in_progress= true;
	while(in_progress ==true)
	{
		compute();
		//for loop for all evaluate_result

		in_progress = next_step();
	}

}

bool rccm_base::next_step()
{

	//do preperation in all config structures.
	return false; //if in progress
	return true; //if al is done.
}

config_rccm *rccm_base::set_config(string input)
{
	//do all configuration stuff...
	this->config = new config_rccm();
	return nullptr;
}
