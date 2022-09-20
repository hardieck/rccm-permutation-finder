//
// Created by hardieck on 2/1/22.
//

#include "../inc/evaluate_zero.h"

evaluate_zero::evaluate_zero()
{
    use_metric = false;
    metric = nullptr;
    best_score =0;
}

evaluate_zero::~evaluate_zero()
{
}

void evaluate_zero::print_configure_help()
{

}

std::stringstream evaluate_zero::print_result(bool ss)
{
    std::stringstream os;
    IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_zero::print_result()")
    os << "Last Matching set was: " << std::endl;
    os << "Score:\t" << this->best_score << std::endl;
    os << "config:\t" << this->best_config << std::endl;
    os << "Set: \t"<<  this->best_coeff_sets << std::endl;

    if (ss == false){std::cout << os.str();}

    IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_zero::print_result()")
    return os;
}

int evaluate_zero::configure(string parameter)
{
    //TODO implement configer function for evaluate_Kolmogorov_Smirnov
    return 0;
}

double evaluate_zero::evaluate(const string &config,const std::set<int> &inputs)
{
    bool z = inputs.find(0) != inputs.end();
    double score;

    if(use_metric)
    {
        if (z) { score = metric->evaluate(config, inputs);}else{ score = 0.0; }
    }
    else
    {
        if (z) { score= 1.0;}else{ score= 0.0; }
    }

    if(z > this->best_score)
    {
        best_score = z;
        best_coeff_sets = inputs;
        best_config = config;
    }
    return score;
}
