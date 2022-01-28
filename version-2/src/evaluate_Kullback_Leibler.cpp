//
// Created by hardieck on 1/27/22.
//

#include "../inc/evaluate_Kullback_Leibler.h"
#include "math.h"
#include <algorithm>


evaluate_Kullback_Leibler::evaluate_Kullback_Leibler()
{
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
    //TODO implement
}

int evaluate_Kullback_Leibler::configure(string parameter)
{
    //TODO implement configer function for evaluate_Kullback_Leibler
    return 0;
}

double evaluate_Kullback_Leibler::evaluate(const string &config,const std::set<int> &inputs)
{
    //TODO implement
    return 0;
}

double evaluate_Kullback_Leibler::Kullback_Leibler_Divergenz(std::vector<int> &P_i)
{
    //std::vector<int> Q_i = {5, 22, 153, 808, 5358, 26809, 90879, 198992,  390745, 1703583, 1566242, 164370, 16928, 2946, 584, 141, 42, 30, 2, 0};
    std::vector<int> Q_i = {2,7,16,48,201,515,1879,5767,16210,38265,75307,122185,173697,302725,805403, 1726502,698703,157147,30922, 8732, 2858, 950, 336, 150, 50, 26, 34, 0, 0, 2, 0};

    std::vector<double> Q = norm_distribution(Q_i);
    std::vector<double> P = norm_distribution(P_i);


    double result=0;
    if(P.size() != Q.size())
    {
        std::cout << "ERROR: in Kullback_Leibler_Divergenz: P Must have size of Q!" << std::endl;
        std::cout << "size of Q: " << Q.size() << std::endl;
        std::cout << "size of P: " << P.size() << std::endl;
        exit(-1);
    }

    for(int i=0; i< Q.size(); ++i)
    {
        double p= P[i];
        double q= Q[i];

        result = result+(p*log10(p/q));
    }

    return result;

}

std::vector<double> evaluate_Kullback_Leibler::norm_distribution(std::vector<int> &input)
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