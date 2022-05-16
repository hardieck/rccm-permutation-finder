//
// Created by hardieck on 2/2/22.
//

#include "../inc/evaluate_Hardieck_Fiege.h"

evaluate_Hardieck_Fiege::evaluate_Hardieck_Fiege()
{

}

evaluate_Hardieck_Fiege::~evaluate_Hardieck_Fiege()
{
}

void evaluate_Hardieck_Fiege::print_configure_help()
{

}

void evaluate_Hardieck_Fiege::print_result()
{
    IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_Hardieck_Fiege::print_result()")
    std::cout << "referenze step function: " << rev_step_function << std::endl;
    //std::cout << "normalized referenze step function: " << normalized_reference_step_function << std::endl;
    std::cout << "Best Matching set was: " << std::endl;
    std::cout << "Score:\t" << this->best_score << std::endl;
    std::cout << "config:\t" << this->best_config << std::endl;
    std::cout << "Set: \t"<<  this->best_coeff_sets << std::endl;

    IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_Hardieck_Fiege::print_result()")
}

int evaluate_Hardieck_Fiege::configure(string parameter)
{
    IF_VERBOSE(5) ENTER_FUNCTION("int evaluate_Hardieck_Fiege::configure(string parameter)")
    IF_VERBOSE(6) std::cout << "input parameter string is: " <<parameter <<std::endl;
    if(parameter.rfind("--configure", 0) == 0) {
        parameter.erase(0, 11);
        size_t pos = 0;
        std::string elem;
        std::string delimiter = " ";
        bool found_elem=true;
        //while ((pos = parameter.find(delimiter)) != std::string::npos)
        while (found_elem)
        {
            pos = parameter.find(" ");
            IF_VERBOSE(7) std::cout << "parameter string: " << parameter << std::endl;
            IF_VERBOSE(7) std::cout << "found element at pos:" << pos << std::endl;
            elem = parameter.substr(0, pos); // copy substring
            parameter.erase(0, pos+1); // erase substring
            if (elem.size() != 0) { // first or last element could be empty if string start or ends with a space
                IF_VERBOSE(6) std::cout << "add " << elem << " to step function vector" << std::endl;
                //rev_step_function.insert(strtod(elem.c_str(), NULL));// TODO!!!: make comand line interface working for inserting step funktion
            }
            if (pos == std::string::npos) { found_elem = false;} // done
        }
    }
    else
    {
        ERROR("Unknown configuration parameter", "int evaluate_Hardieck_Fiege::configure(string parameter)")
    }
    IF_VERBOSE(5) LEAVE_FUNCTION("int evaluate_Hardieck_Fiege::configure(string parameter)")
    return 0;
}

double evaluate_Hardieck_Fiege::evaluate(const string &config,const std::set<int> &inputs)
{
    double result = this->div_rev2test(inputs);

    if(use_metric)
    {
        result = result * metric->evaluate(config,inputs);
    }

    if(result > this->best_score)
    {
        best_score = result;
        best_coeff_sets = inputs;
        best_config = config;
    }
    return result;
}

double evaluate_Hardieck_Fiege::get_test_value_at(double pos)
{
    //IF_VERBOSE(0) std:: cout << "pos is: " << pos << " save_value_pos_test: " << save_value_pos_test << " it_pos_test: " << *it_pos_test  << std::endl;
    if (pos >= save_value_pos_test) {
        if (pos >= *it_pos_test)
        {
            //while((pos >= *it_pos_test )&&(it_pos_test != test_step_function.end())) // TODO: repair NFMH metrik!!! (make every thing working with pairs...)
            {
                save_value_pos_test = *it_pos_test;
                ++it_pos_test;
            }
            return save_value_pos_test;
        }
        else
        {
            return save_value_pos_test;
        }
    }
    else
    {
        return save_value_pos_test;
    }
}

double evaluate_Hardieck_Fiege::get_rev_value_at(double pos)
{
    //IF_VERBOSE(0) std:: cout << "pos is: " << pos << " save_value_pos_test: " << save_value_pos_test << "it_pos_test" << *it_pos_test  << std::endl;
    if (pos >= save_value_pos_rev) {
        if (pos >= *it_pos_rev)
        {
            // while((pos >= *it_pos_rev )&&(it_pos_rev != rev_step_function.end())) // TODO: repair NFMH metrik!!! (make every thing working with pairs...)
            {
                save_value_pos_rev = *it_pos_rev;
                ++it_pos_rev;
            }
            return save_value_pos_rev;
        }
        else
        {
            return save_value_pos_rev;
        }
    }
    else
    {
        return save_value_pos_rev;
    }
}
void evaluate_Hardieck_Fiege::reset_position_marker()
{
    //it_pos_test = test_step_function.begin(); // TODO: repair NFMH metrik!!! (make every thing working with pairs...)
    //it_pos_rev  = rev_step_function.begin(); // TODO: repair NFMH metrik!!! (make every thing working with pairs...)
    //save_value_pos_test = *it_pos_test; // TODO: repair NFMH metrik!!! (make every thing working with pairs...)
    //save_value_pos_rev = *it_pos_rev; // TODO: repair NFMH metrik!!! (make every thing working with pairs...)
}


double evaluate_Hardieck_Fiege::div_rev2test(const std::set<int> &inputs)
{
    //Todo Implement funktion
    return 1;
}

double evaluate_Hardieck_Fiege::div_both_way(const std::set<int> &inputs)
{
//Todo Implement funktion
return 1;
}