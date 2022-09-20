//
// Created by hardieck on 5/16/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_EQUAL_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_EQUAL_H
#include "evaluate_base.h"

class evaluate_equal : public evaluate_base
{
public:
    evaluate_equal();
    virtual ~evaluate_equal();
    virtual int configure(string parameter);
    virtual void print_configure_help();
    std::stringstream print_result(bool ss=false);
    double evaluate(const string &config,const std::set<int> &inputs);

    coeff_set reff_coeff_set;

    //data bundle for "best" result. (first one with zero)
    std::string best_config; // stores RCCM Config string Format HM1
    coeff_set best_coeff_sets; //stores the coefficien set
    double best_score; //score of corresponding coeff_set
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_EQUAL_H
