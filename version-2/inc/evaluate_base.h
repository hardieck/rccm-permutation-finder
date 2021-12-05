//
// Created by hardieck on 12/5/21.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_BASE_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_BASE_H

#include "base_obj.h"

class evaluate_base : public base_obj
{
    public:
    evaluate_base(){};
    virtual ~evaluate_base(){};
    virtual double evaluate(string config,std::set<int> inputs)=0;
    virtual void print()=0;
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_BASE_H
