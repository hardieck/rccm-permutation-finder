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
    std::stringstream print_result(bool ss=false);

    double evaluate(const string &config,const std::set<int> &inputs);


    double two_sided_Kolmogorow_Sminow(const std::set<int>);
    std::vector<int> reference_step_function;
    std::vector<int> normalized_reference_step_function;

    bool use_decimal_point_detection;

    //data bundle for best result.
    std::string best_config; // stores RCCM Config string Format HM1
    coeff_set best_coeff_sets; //stores the coefficien set
    double best_score; //score of corresponding coeff_set

private:
    set<int> normalize();
    double Kolmogorov_Smirnov(const std::set<int> &inputs); // basic metric compared with reference

};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_KOLMOGOROV_SMIRNOV_H


