//
// Created by hardieck on 2/1/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_ZERO_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_ZERO_H

#include "evaluate_base.h"
class evaluate_zero : public evaluate_base
{
public:
    evaluate_zero();
    virtual ~evaluate_zero();
    virtual int configure(string parameter);
    virtual void print_configure_help();
    void print_result();
    double evaluate(const string &config,const std::set<int> &inputs);

    //data bundle for "best" result. (first one with zero)
    std::string best_config; // stores RCCM Config string Format HM1
    coeff_set best_coeff_sets; //stores the coefficien set
    double best_score; //score of corresponding coeff_set
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_ZERO_H
