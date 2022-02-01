//
// Created by hardieck on 1/27/22.
//

#include "../inc/evaluate_Kullback_Leibler.h"
#include "math.h"
#include <vector>
#include <algorithm>


evaluate_Kullback_Leibler::evaluate_Kullback_Leibler()
{
    no_of_windows = 0;
    best_score = 0;
    //TODO implement
}

evaluate_Kullback_Leibler::~evaluate_Kullback_Leibler()
{

}

void evaluate_Kullback_Leibler::print_configure_help()
{
    //TODO implement
}

void evaluate_Kullback_Leibler::print_result()
{
    IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_count::print_result()")
    std::cout << "no of windows: " << no_of_windows << std::endl;
    std::cout << "referenze distributen: " << referenze_distributen << std::endl;
    //std::cout << "normalized referenze distributen: " << normalized_referenze_distributen << std::endl;
    std::cout << "Best Matching set was: " << std::endl;
    std::cout << "Score:\t" << this->best_score << std::endl;
    std::cout << "config:\t" << this->best_config << std::endl;
    std::cout << "Set: \t"<<  this->best_coeff_sets << std::endl;

    IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_count::print_result()")
}

int evaluate_Kullback_Leibler::configure(string parameter)
{
    IF_VERBOSE(5) ENTER_FUNCTION("int evaluate_Kullback_Leibler::configure(string parameter)")
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
                referenze_distributen.push_back(strtod(elem.c_str(), NULL));
            }
            if (pos == std::string::npos) { found_elem = false;} // done
        }
        this->no_of_windows = referenze_distributen.size();
        IF_VERBOSE(6) std::cout << "window count is: " << no_of_windows <<std::endl;
        if(no_of_windows <=0 )
        {
            ERROR("Invalid Window count!","int evaluate_Kullback_Leibler::configure(string parameter)")
        }
    }
    else
    {
        ERROR("Unknwon configuration parameter", "int evaluate_Kullback_Leibler::configure(string parameter)")
    }
    IF_VERBOSE(5) LEAVE_FUNCTION("int evaluate_Kullback_Leibler::configure(string parameter)")
    return 0;
}

double evaluate_Kullback_Leibler::evaluate(const string &config,const std::set<int> &inputs)
{
    std::vector<double> dis = get_distribution(inputs,this->no_of_windows);
    double kld = Kullback_Leibler_Divergenz(dis);
    kld=1/kld;

    if(kld > this->best_score)
    {
        best_score = kld;
        best_coeff_sets = inputs;
        best_config = config;
    }
    return kld;
}

double evaluate_Kullback_Leibler::Kullback_Leibler_Divergenz(std::vector<double> &P_i)
{
    //TODO: remove hardcoded distribution
    //std::vector<int> Q_i = {5, 22, 153, 808, 5358, 26809, 90879, 198992,  390745, 1703583, 1566242, 164370, 16928, 2946, 584, 141, 42, 30, 2, 0};
    std::vector<double> Q_i = {2,7,16,48,201,515,1879,5767,16210,38265,75307,122185,173697,302725,805403, 1726502,698703,157147,30922, 8732, 2858, 950, 336, 150, 50, 26, 34, 0, 0, 2, 0};


    if(this->no_of_windows == 0)
    {
        ERROR("No referenze Distribution found!", "double evaluate_Kullback_Leibler::Kullback_Leibler_Divergenz(std::vector<double> &P_i)")
    }
    if (this->normalized_referenze_distributen.size() == 0) //generate normalized_referenze_distributen if it desnt exit
    {
        normalized_referenze_distributen = norm_distribution(referenze_distributen);
    }

    std::vector<double> &Q = normalized_referenze_distributen;
    std::vector<double> P = norm_distribution(P_i);


    double result=0;
    if(P.size() != Q.size())
    {
        std::cout << "size of Q: " << Q.size() << std::endl;
        std::cout << "size of P: " << P.size() << std::endl;
        ERROR("P Must have size of Q!","evaluate_Kullback_Leibler::Kullback_Leibler_Divergenz(std::vector<int> &P_i)")
    }

    for(int i=0; i< Q.size(); ++i)
    {
        double p= P[i];
        double q= Q[i];

        result = result+(p*log10(p/q));
    }
    return result;

}

std::vector<double> evaluate_Kullback_Leibler::norm_distribution(std::vector<double> &input)
{
    double max = *std::max_element(input.begin(),input.end());
    std::vector<double> r(input.size());
    for(int i=0; i< input.size();++i)
    {
        if(i==0)
        {
            r[i] = 0.000001;
        }
        else
        {
            r[i]=(((double)i)/max);
        }
    }
    return r;
}

std::vector<double> evaluate_Kullback_Leibler::get_distribution(const std::set<int> &input, int No_of_windows)
{

    int max_value = *input.begin();
    for(int i : input)
    {
        if(abs(i) > max_value)
        {
            max_value = abs(i);
        }
    }

    double window_size = ((2*max_value) / No_of_windows);
    std::vector<double> distribution(No_of_windows);

    for(int i: input)
    {
        double lower_Border = -max_value;
        double upper_Border = lower_Border + window_size;
        for(int j=0; j < No_of_windows; ++j)
        {
            if((i >= lower_Border) && (i < upper_Border))
            {
                distribution[j]++;
                break;
            }
            lower_Border += window_size;
            upper_Border = lower_Border + window_size;
        }
    }

    return distribution;
}