//
// Created by hardieck on 12/5/21.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_BASE_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_BASE_H

#include "base_obj.h"
#include "datatyps.h"
#include "helper.h"

class evaluate_base : public base_obj
{
    public:
    evaluate_base(){};
    virtual ~evaluate_base(){};
    virtual double evaluate(const string &config,const std::set<int> &inputs)=0;
    virtual int configure(string parameter);
    virtual void print_configure_help();
    virtual void print_result()=0;

    bool use_metric; // only true if a chained metric is used (multiply results)
    shared_ptr<evaluate_base> metric; // stores another evaluate obj to calculate metrics for selection

};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_BASE_H
