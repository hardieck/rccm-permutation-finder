//
// Created by hardieck on 5/16/22.
//

#include "../inc/evaluate_equal.h"

evaluate_equal::evaluate_equal()
{
    use_metric = false;
    metric = nullptr;
    best_score =0;
    reff_coeff_set.clear();
}

evaluate_equal::~evaluate_equal()
{
}

void evaluate_equal::print_configure_help()
{

}

std::stringstream evaluate_equal::print_result(bool ss)
{
    IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_zero::print_result()")
    std::stringstream os;
    os << "Last Matching set was: " << std::endl;
    os << "Score:\t" << this->best_score << std::endl;
    os << "config:\t" << this->best_config << std::endl;
    os << "Set: \t"<<  this->best_coeff_sets << std::endl;
    if (ss == false){std::cout << os.str();}
    IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_zero::print_result()")
    return os;
}

int evaluate_equal::configure(string parameter)
{
    IF_VERBOSE(5) ENTER_FUNCTION("int evaluate_equal::configure(string parameter)")
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
                IF_VERBOSE(6) std::cout << "add " << elem << " to distribution vector" << std::endl;
                reff_coeff_set.insert(strtod(elem.c_str(), NULL));
            }
            if (pos == std::string::npos) { found_elem = false;} // done
        }
    }
    else
    {
        ERROR("Unknwon configuration parameter", "int evaluate_equal::configure(string parameter)")
    }
    IF_VERBOSE(5) LEAVE_FUNCTION("int evaluate_equal::configure(string parameter)")
    return 0;
}

double evaluate_equal::evaluate(const string &config,const std::set<int> &inputs)
{
    bool z = (inputs == reff_coeff_set);
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
