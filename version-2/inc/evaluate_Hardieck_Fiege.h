//
// Created by hardieck on 2/2/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_HARDIECK_FIEGE_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_HARDIECK_FIEGE_H

#include "evaluate_base.h"

class evaluate_Hardieck_Fiege : public evaluate_base
{
public:
    evaluate_Hardieck_Fiege();
    virtual ~evaluate_Hardieck_Fiege();
    virtual int configure(string parameter);
    virtual void print_configure_help();
    void print_result();

    double evaluate(const string &config,const std::set<int> &inputs);


    std::vector<int> reference_step_function;
    std::vector<int> normalized_reference_step_function;

    bool use_decimal_point_detection;

    //data bundle for best result.
    std::string best_config; // stores RCCM Config string Format HM1
    coeff_set best_coeff_sets; //stores the coefficien set
    double best_score; //score of corresponding coeff_set

private:
    set<int> normalize();
    double one_sided_test(const std::set<int> &inputs); // on sided test from referenze to input
    double one_sided_with_point_search(const std::set<int> &inputs); // use on sided and perform decimal point position search
    double get_value_at(); // helper function to get
    double get_value_rev();


};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_HARDIECK_FIEGE_H
