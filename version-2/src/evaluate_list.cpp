//
// Created by hardieck on 2/1/22.
//

#include "../inc/evaluate_list.h"


evaluate_list::evaluate_list()
{
    use_metric = false;
    metric = nullptr;
    result_space = 5;
    v_config.clear();
    v_config.resize(5);
    v_coeff_sets.clear();
    v_coeff_sets.resize(5);
    v_score.clear();
    v_score.resize(5);
}
evaluate_list::~evaluate_list()
{
}

double evaluate_list::evaluate(const string &config,const std::set<int> &inputs)
{
    IF_VERBOSE(5) ENTER_FUNCTION("evaluate_count::evaluate(const string &config,const std::set<int> &inputs)")
    double score=0;
    if (use_metric)
    {
        score = metric->evaluate(config,inputs);
    }
    else
    {
        if(!collect_all) {
            ERROR("Metric list-best can only be used without chain to another metric when '--configure all' option is used.",
                  "double evaluate_list::evaluate(const string &config,const std::set<int> &inputs)")
        }
    }

    if(collect_all)
    {
        if (use_metric && (v_score.size()!=0))
        {
            double last_score = v_score[0];
            if (score > last_score) {
                this->v_score.clear();
                this->v_config.clear();
                this->v_coeff_sets.clear();
            }
            if (score >= last_score) {
                this->pushback_result(score, config, inputs);
            }
        }
        else
        {
            this->pushback_result(score, config, inputs);
        }
    }
    else
    {
        for (int i = 0; i < this->result_space; ++i) {
            if (score >= v_score[i]) {
                if ((score == v_score[i]) && (config == this->v_config[i])) // don't insert same element multiple times
                {
                    break;
                }
                this->insert_result(i, score, config, inputs);
                break;
            }
        }
    }
    return score;
    ERROR("No evaluation option is specified! Configure First!","evaluate_count::evaluate(string config,std::set<int> inputs)")
}
int evaluate_list::configure(string parameter)
{
    IF_VERBOSE(5) ENTER_FUNCTION("int evaluate_list::configure(string parameter)")
    if(parameter.rfind("--configure", 0) == 0)
    {
        parameter.erase(0, 11);
        IF_VERBOSE(7) std::cout << "parameter string: " << parameter << std::endl;
        if(parameter == " all")
        {
            this->collect_all = true;
            this->v_score.clear();
            this->v_config.clear();
            this->v_coeff_sets.clear();
            IF_VERBOSE(5) LEAVE_FUNCTION("int evaluate_list::configure(string parameter)")
            return 0;
        }

        this->result_space = (strtod(parameter.c_str(), NULL));
        this->update_size();
        IF_VERBOSE(7) std::cout << "new result space is: " << this->result_space << std::endl;
    }
    else
    {
        ERROR("Unknwon configuration parameter", "int evaluate_list::configure(string parameter)")
    }
    IF_VERBOSE(5) LEAVE_FUNCTION("int evaluate_list::configure(string parameter)")
    return 0;
}
void evaluate_list::print_configure_help()
{
    //TODO implement print_configure_help function for evaluate_count
}
void evaluate_list::print_result()
{
    IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_count::print_result()")
    if (this->collect_all)
    {
        std::cout << "Display all collected sets with the best score" << std::endl;
        std::cout << "Nr\tScore\tConfig\tCoefficient Set" << std::endl;
    }
    else
    {
        std::cout << "Display best " << result_space << " sets" << std::endl;
        std::cout << "Ranking\tScore\tConfig\tCoefficient Set" << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
    for(int i = 0; i < v_config.size(); ++i)
    {
        std::cout << i+1 <<"\t" << v_score[i] << "\t" << v_config[i] << "\t" << v_coeff_sets[i] << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
    IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_count::print_result()")
}
void evaluate_list::insert_result(unsigned int at,double score, const string &config,const std::set<int> &inputs)
{
    //initialize iterators
    std::vector<std::string>::iterator it_config = this->v_config.begin();
    std::vector<coeff_set>::iterator it_coeff_sets = this->v_coeff_sets.begin();
    std::vector<double>::iterator it_score = this->v_score.begin();

    //count iterator to correct position
    for(int i=0; i < at;++i)
    {
        ++it_config;
        ++it_coeff_sets;
        ++it_score;
    }
    //insert new stuff at current position
    this->v_config.insert(it_config,config);
    this->v_coeff_sets.insert(it_coeff_sets,inputs);
    this->v_score.insert(it_score,score);

    // now there is one element to much!
    v_config.pop_back();
    v_coeff_sets.pop_back();
    v_score.pop_back();
}

void evaluate_list::pushback_result(double score, const string &config,const std::set<int> &inputs)
{
    //insert new stuff at current position
    this->v_config.push_back(config);
    this->v_coeff_sets.push_back(inputs);
    this->v_score.push_back(score);
}


void evaluate_list::update_size()
{
    this->v_config.resize(this->result_space);
    this->v_score.resize(this->result_space);
    this->v_coeff_sets.resize(this->result_space);
}