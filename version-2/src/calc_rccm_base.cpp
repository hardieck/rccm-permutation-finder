//
// Created by hardieck on 9/20/19.
//

#include "../inc/calc_rccm_base.h"


calc_rccm_base::calc_rccm_base()
{
}



bool calc_rccm_base::next_step()
{
	return this->config->next_config(); //return true if still in progress
}
