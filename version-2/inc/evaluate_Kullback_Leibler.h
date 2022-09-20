//
// Created by hardieck on 1/27/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_KULLBACK_LEIBLER_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_KULLBACK_LEIBLER_H

#include "evaluate_base.h"

class evaluate_Kullback_Leibler : public evaluate_base
{
public:
    evaluate_Kullback_Leibler();
    virtual ~evaluate_Kullback_Leibler();
    virtual int configure(string parameter);
    virtual void print_configure_help();
    std::stringstream print_result(bool ss=false);

    double evaluate(const string &config,const std::set<int> &inputs);
    std::vector<double> referenze_distributen;
    std::vector<double> normalized_referenze_distributen;

    double Kullback_Leibler_Divergenz(std::vector<double> &P_i);
    std::vector<double> norm_distribution(std::vector<double> &input);
    std::vector<double> get_distribution(const std::set<int> &input, int No_of_windows);

    int no_of_windows; // spezify the number of windows / bin for distribution matching

    //data bundle for best result.
    std::string best_config; // stores RCCM Config string Format HM1
    coeff_set best_coeff_sets; //stores the coefficien set
    double best_score; //score of corresponding coeff_set
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_KULLBACK_LEIBLER_H
