//
// Created by hardieck on 12/5/21.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_COUNT_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_COUNT_H

#include "evaluate_base.h"

class evaluate_count : public evaluate_base
{
public:
    evaluate_count();
    virtual ~evaluate_count();

    double evaluate(const string &config,const std::set<int> &inputs);
    virtual int configure(string parameter);
    virtual void print_configure_help();
    void print_result();

    bool count_size; // only true if count_size is used (not compatible with count_sets)
    bool count_sets; // only true if count_sets is used (not compatible with count_size)

    //data bundle. Different usage depending on config
    std::vector<std::string> v_config; // stores RCCM Config strings Format HM1
    std::vector<coeff_set> v_coeff_sets; //stores the coefficien sets
    std::vector<int> v_count; // count of corresponding coeff_sets
    std::vector<double> v_score; //score of corresponding coeff_sets
    long long counted_cases;

private:
    double evaluate_count_size(const string &config,const std::set<int> &inputs);
    double evaluate_count_sets(const string &config,const std::set<int> &inputs);
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_COUNT_H
