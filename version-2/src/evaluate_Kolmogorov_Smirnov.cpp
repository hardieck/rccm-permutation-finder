//
// Created by hardieck on 12/13/21.
//

#include "../inc/evaluate_Kolmogorov_Smirnov.h"

evaluate_Kolmogorov_Smirnov::evaluate_Kolmogorov_Smirnov()
{

}

evaluate_Kolmogorov_Smirnov::~evaluate_Kolmogorov_Smirnov()
{
}

void evaluate_Kolmogorov_Smirnov::print_configure_help()
{

}

std::stringstream evaluate_Kolmogorov_Smirnov::print_result(bool ss)
{
    IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_Kolmogorov_Smirnov::print_result()")
    std::stringstream os;
    os << "referenze step function: " << reference_step_function << std::endl;
    //os << "normalized referenze step function: " << normalized_reference_step_function << std::endl;
    os << "Best Matching set was: " << std::endl;
    os << "Score:\t" << this->best_score << std::endl;
    os << "config:\t" << this->best_config << std::endl;
    os << "Set: \t"<<  this->best_coeff_sets << std::endl;
    if (ss == false){std::cout << os.str();}
    IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_Kolmogorov_Smirnov::print_result()")
    return os;
}

int evaluate_Kolmogorov_Smirnov::configure(string parameter)
{
    IF_VERBOSE(5) ENTER_FUNCTION("int evaluate_Kolmogorov_Smirnov::configure(string parameter)")
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
                reference_step_function.push_back(strtod(elem.c_str(), NULL));
            }
            if (pos == std::string::npos) { found_elem = false;} // done
        }
    }
    else
    {
        ERROR("Unknown configuration parameter", "int evaluate_Kolmogorov_Smirnov::configure(string parameter)")
    }
    IF_VERBOSE(5) LEAVE_FUNCTION("int evaluate_Kolmogorov_Smirnov::configure(string parameter)")
    return 0;
    return 0;
}

double evaluate_Kolmogorov_Smirnov::evaluate(const string &config,const std::set<int> &inputs)
{
    double result = Kolmogorov_Smirnov(inputs);

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

double evaluate_Kolmogorov_Smirnov::Kolmogorov_Smirnov(const std::set<int> &inputs)
{
    //Todo Implement funktion
    return 1;
}