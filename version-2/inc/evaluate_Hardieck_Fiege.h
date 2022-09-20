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
    std::stringstream print_result(bool ss=false);

    double evaluate(const string &config,const std::set<int> &inputs);


    //std::vector<double> reference_step_function; // referenze distribution or step funktion from input
    std::set<std::pair<float,float>> rev_step_function; // normaized referenze step function
    std::set<std::pair<float,float>> test_step_function; // normaized referenze step function

    bool use_decimal_point_detection;

    //data bundle for best result.
    std::string best_config; // stores RCCM Config string Format HM1
    coeff_set best_coeff_sets; //stores the coefficien set
    double best_score; //score of corresponding coeff_set

//private:
    set<int> normalize();
    double div_rev2test(const std::set<int> &inputs); // on sample test from reference to input
    double div_both_way(const std::set<int> &inputs); // use on sided and perform decimal point position search

    std::set<double> pos_list; // positions to test (fused from rev step functions and test step funktions, sorted to rising values)
    std::set<double>::iterator it_pos_test;
    std::set<double>::iterator it_pos_rev;
    double save_value_pos_test; //saves the last value from it_pos_test (to allow continuous ++)
    double save_value_pos_rev; //saves the last value from it_pos_test (to allow continuous ++)
    double last_pos_value; // last used position value.

    double step_size_test; // save the step size for "test" (1/element count)
    double step_size_rev;// save the step size for "rev" (1/element count)
    void reset_position_marker(); // clear all test specifig values.
    const std::set<int> input_set;
    double get_test_value_at(double pos); // helper function to get function value from test-step-function for position. (only rising calls allowed)
    double get_rev_value_at(double pos);  // helper function to get function value from rev-step-function for position. (only rising calls allowed)


};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_HARDIECK_FIEGE_H
