//
// Created by hardieck on 2/1/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_LIST_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_LIST_H

#include "evaluate_base.h"

class evaluate_list : public evaluate_base
{
public:
    evaluate_list();
    virtual ~evaluate_list();

    double evaluate(const string &config,const std::set<int> &inputs);
    virtual int configure(string parameter);
    virtual void print_configure_help();
    void print_result();

    unsigned int result_space;

    //data bundle. size depending on config
    std::vector<std::string> v_config; // stores RCCM Config strings Format HM1
    std::vector<coeff_set> v_coeff_sets; //stores the coefficien sets
    std::vector<double> v_score; //score of corresponding coeff_sets
private:
    void insert_result(unsigned int at,double score, const string &config,const std::set<int> &inputs);
    void update_size();

};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_LIST_H
