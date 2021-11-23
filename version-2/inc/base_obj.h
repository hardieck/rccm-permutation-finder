//
// Created by hardieck on 12/7/20.
//

#include "debug.h"
#include "datatyps.h"

#ifndef ADDNET_PERMUTATOR_V2_BASE_OBJ_H
#define ADDNET_PERMUTATOR_V2_BASE_OBJ_H


class base_obj
{
public:
    static long long obj_count;
    base_obj(){++obj_count;};
    base_obj (const base_obj &obj){++obj_count;}
    virtual ~base_obj(){--obj_count;};
};


#endif //ADDNET_PERMUTATOR_V2_BASE_OBJ_H
