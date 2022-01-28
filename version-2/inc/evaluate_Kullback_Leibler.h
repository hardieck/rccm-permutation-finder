//
// Created by hardieck on 1/27/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_KULLBACK_LEIBLER_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_KULLBACK_LEIBLER_H

#include "evaluate_base.h"

class evaluate_Kullback_Leibler : public evaluate_base
{
    evaluate_Kullback_Leibler();
    virtual ~evaluate_Kullback_Leibler();
    virtual int configure(string parameter);
    virtual void print_configure_help();
    void print_result();

    double evaluate(const string &config,const std::set<int> &inputs);
    std::vector<int> referenze_distributen;
    std::vector<int> normalized_referenze_distributen;

    double Kullback_Leibler_Divergenz(std::vector<int> &P_i);
    std::vector<double> norm_distribution(std::vector<int> &input);

};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_KULLBACK_LEIBLER_H
