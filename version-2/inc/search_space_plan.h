//
// Created by hardieck on 11/24/21.
//

#ifndef ADDNET_PERMUTATOR_V2_SEARCH_SPACE_PLAN_H
#define ADDNET_PERMUTATOR_V2_SEARCH_SPACE_PLAN_H

#include "base_obj.h"


class search_space_plan : base_obj
{
public:
    search_space_plan();
    ~search_space_plan();

    void add_rule(string rule);


    // devault plan... (test A and B complete)
    // special planes... (IF C2 is specifyed: (test A_ complete and B only usal cases))
    // special planes... (IF C2 is specifyed: (test A_ complete and B only usal cases))

    //to define
    //max shift
    //operation search level (operation only, shifts only, etc)
    //

    //use down't care values to check rurrent case and let each fitting rool do a change from default.

    //default for all options
    //start with config=xy

    //level0 Connection structure search space
    //level1 selective adderNr
    //level2 sel_Add search space
    //level3 sel_Add operation type A or B
        //level4 operating mode {all or usual}
    //level3 sel_Add max shift


    //positon key is {rccm_type,sel_add_nr,sel_Add_type} for each element also downt care is possible

    //getter funktions to initializ the rccm and selective_Add class:

    //get_search_space_rccm() just return search space...

    //multiple lists one for each.
    // for each call go throu all lines in the list and modify output for each fit... before return.
        //get_search_space_sel_add(rccm_type,nr) return vec of sel_Add_types
        //get_sel_add_max_shift(rccm_type,nr,sel_Add_type) return max shift
        //get_sel_add_operating_mode(rccm_type,nr,sel_Add_type) return mode
        //get_sel_add_operating_mode(rccm_type,nr,sel_Add_type) return mode
        //get_sel_add_config_level(rccm_type,nr,sel_Add_type) return level

    // maby a whoami funktion to get the position key  could be helpful...
    //-----------------------------
    //wich evaluation shall be done for all

    vector<>

};


#endif //ADDNET_PERMUTATOR_V2_SEARCH_SPACE_PLAN_H
