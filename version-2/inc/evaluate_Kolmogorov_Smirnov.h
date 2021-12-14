//
// Created by hardieck on 12/13/21.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_KOLMOGOROV_SMIRNOV_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_KOLMOGOROV_SMIRNOV_H

#include "evaluate_base.h"
class evaluate_Kolmogorov_Smirnov : public evaluate_base
{
public:
    evaluate_Kolmogorov_Smirnov();
    virtual ~evaluate_Kolmogorov_Smirnov();
    virtual int configure(string parameter);
    virtual void print_configure_help();
    void print_result();

    double evaluate(const string &config,const std::set<int> &inputs);

    std::vector<int> referenze_distributen;

    bool use_decimal_point_positions
private:
    normalize()

};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_KOLMOGOROV_SMIRNOV_H


