#include "structure.h"

#include <iostream>
#include <math.h>
#include <algorithm>

structure_base::structure_base()
{

}

int structure_base::get_no_of_shifts()
{
    return this->shifts.size();
}
int structure_base::get_no_of_configs()
{
    return this->config.size();
}

bool structure_base::set_shifts(std::vector<int> input)
{
    if (input.size() != this->shifts.size()) return false;
    //if(!is_a_valid_shift_vector(input,0,input.size())) return false;

    this->shifts.clear();
    this->shifts = input;
    return true;
}
bool structure_base::set_config(std::vector<int> input)
{
    if (input.size() != this->config.size()) return false;
    this->config.clear();
    this->config = input;
    return true;
}
bool structure_base::set_shift_and_config(std::vector<int> input)
{
    std::vector<int> shift_input;
    std::vector<int> config_input;

    for(int i=0; i< get_no_of_shifts();++i)
    {
        shift_input.push_back(input[i]);
    }
    for(int i=get_no_of_shifts(); i< (get_no_of_shifts()+get_no_of_configs());++i)
    {
        config_input.push_back(input[i]);
    }

    if(!set_config(config_input)){return false;}
    if(!set_shifts(shift_input)){return false;}
    return true;
}


std::list<int> structure_base::compute()
{
    std::list<int> result;
    return result;
}

bool structure_base::is_a_valid_shift_vector(std::vector<int> input,int start_index,int end_index)
{
    int v;
    int last = -1;
    for(int i = start_index; i <= end_index; ++i)
    {
        v = input[i];
        if(last >= v)
        {
            return false;
        }
        last = v;
    }
    return true;
}


std::list<int> structure_base::operation_TYPE_a(std::list<int>  &A1,std::list<int>  &A2, std::list<int> &B1, std::list<int> &B2,const std::vector<int> config)
{
    //00  A1 +B1
    //01  A1 +B2
    //02  A1 -B1
    //03  A1 -B2
    //04 -A1 +B1
    //05 -A1 +B2
    //06 -A1 -B1
    //07 -A1 -B2
    //08  A2 +B1
    //09  A2 +B2
    //10  A2 -B1
    //11  A2 -B2
    //12 -A2 +B1
    //13 -A2 +B2
    //14 -A2 -B1
    //15 -A2 -B2

    std::list<int> result;

    for(int conf:config)
    {
        switch(conf)
        {
            case  0: for(int a:A1){ for(int b:B1) { result.push_back( a +b); } } break;
            case  1: for(int a:A1){ for(int b:B2) { result.push_back( a +b); } } break;
            case  2: for(int a:A1){ for(int b:B1) { result.push_back( a -b); } } break;
            case  3: for(int a:A1){ for(int b:B2) { result.push_back( a -b); } } break;
            case  4: for(int a:A1){ for(int b:B1) { result.push_back(-a +b); } } break;
            case  5: for(int a:A1){ for(int b:B2) { result.push_back(-a +b); } } break;
            case  6: for(int a:A1){ for(int b:B1) { result.push_back(-a -b); } } break;
            case  7: for(int a:A1){ for(int b:B2) { result.push_back(-a -b); } } break;
            case  8: for(int a:A2){ for(int b:B1) { result.push_back( a +b); } } break;
            case  9: for(int a:A2){ for(int b:B2) { result.push_back( a +b); } } break;
            case 10: for(int a:A2){ for(int b:B1) { result.push_back( a -b); } } break;
            case 11: for(int a:A2){ for(int b:B2) { result.push_back( a -b); } } break;
            case 12: for(int a:A2){ for(int b:B1) { result.push_back(-a +b); } } break;
            case 13: for(int a:A2){ for(int b:B2) { result.push_back(-a +b); } } break;
            case 14: for(int a:A2){ for(int b:B1) { result.push_back(-a -b); } } break;
            case 15: for(int a:A2){ for(int b:B2) { result.push_back(-a -b); } } break;

        }
    }
    return result;
}

std::list<int> structure_base::operation_TYPE_b(const std::list<int> &A1, const std::list<int> &A2, const std::list<int> &A3, const std::list<int> &B1, std::vector<int> config)
{
    //00  A1 +B1
    //01  A2 +B1
    //02  A3 +B1
    //03 -A1 +B1
    //04 -A2 +B1
    //05 -A3 +B1
    //06     +B1


    std::list<int> result;

    for(int conf:config)
    {
        switch(conf)
        {
            case 0: for(int a:A1){ for(int b:B1) { result.push_back( a +b); } } break;
            case 1: for(int a:A2){ for(int b:B1) { result.push_back( a +b); } } break;
            case 2: for(int a:A3){ for(int b:B1) { result.push_back( a +b); } } break;
            case 3: for(int a:A1){ for(int b:B1) { result.push_back(-a +b); } } break;
            case 4: for(int a:A2){ for(int b:B1) { result.push_back(-a +b); } } break;
            case 5: for(int a:A3){ for(int b:B1) { result.push_back(-a +b); } } break;
            case 6:                for(int b:B1) { result.push_back(    b); }   break;
        }
    }
    return result;
}

std::list<int> structure_base::operation_TYPE_b_minus(const std::list<int> &A1, const std::list<int> &A2, const std::list<int> &A3, const std::list<int> &B1, const std::vector<int> config)
{
    //00  A1 -B1
    //01  A2 -B1
    //02  A3 -B1
    //03 -A1 -B1
    //04 -A2 -B1
    //05 -A3 -B1
    //06     -B1


    std::list<int> result;

    for(int conf:config)
    {
        switch(conf)
        {
            case 0: for(int a:A1){ for(int b:B1) { result.push_back( a -b); } } break;
            case 1: for(int a:A2){ for(int b:B1) { result.push_back( a -b); } } break;
            case 2: for(int a:A3){ for(int b:B1) { result.push_back( a -b); } } break;
            case 3: for(int a:A1){ for(int b:B1) { result.push_back(-a -b); } } break;
            case 4: for(int a:A2){ for(int b:B1) { result.push_back(-a -b); } } break;
            case 5: for(int a:A3){ for(int b:B1) { result.push_back(-a -b); } } break;
            case 6:                for(int b:B1) { result.push_back(   -b); }   break;

        }
    }
    return result;
}

std::list<int> structure_base::operation_TYPE_c(const std::list<int> &A1,const std::list<int> &A2,const std::list<int> &A3,const std::list<int> &A4)
{
    std::list<int> result;
    for(int a:A1)
    {
        result.push_back(a);
    }
    for(int a:A2)
    {
        result.push_back(a);
    }
    for(int a:A3)
    {
        result.push_back(a);
    }
    for(int a:A4)
    {
        result.push_back(a);
    }

    return result;
}

std::list<int> structure_base::operation_TYPE_d(const std::list<int> &A1,const  std::list<int> &A2,const  std::list<int> &B1)
{
    //00  A1 +B1
    //01  A2 +B2
    //02 -A1 +B1
    //03 -A2 +B1
    //04  A1 -B1
    //05  A2 -B1
    //06      B1



    std::list<int> result;

    for(int b:B1)
    {
        for(int a:A1)
        {
            result.push_back(a+b);
            result.push_back(-a+b);
        }

        for(int a:A2)
        {
            result.push_back(a+b);
            result.push_back(-a+b);
        }
        result.push_back(b);
    }

    return result;
}

std::list<int> structure_base::operation_TYPE_e(const std::list<int> &A1,const std::list<int> &A2,const std::list<int> &B1,std::vector<int> config)
{
    //00  A1 +B1
    //01  A2 +B1
    //02 -A1 +B1
    //03 -A2 +B1
    //04  A1 -B1
    //05  A2 -B1
    //06  A1
    //07  A2
    //08      B1
    //09  -A1
    //10  -A2
    //11     -B1


    std::list<int> result;

    for(int conf:config)
    {
        switch(conf)
        {
            case  0: for(int a:A1){ for(int b:B1) { result.push_back( a +b ); } } break;
            case  1: for(int a:A2){ for(int b:B1) { result.push_back( a +b ); } } break;
            case  2: for(int a:A1){ for(int b:B1) { result.push_back(-a +b ); } } break;
            case  3: for(int a:A2){ for(int b:B1) { result.push_back(-a +b ); } } break;
            case  4: for(int a:A1){ for(int b:B1) { result.push_back( a -b ); } } break;
            case  5: for(int a:A2){ for(int b:B1) { result.push_back( a -b ); } } break;
            case  6: for(int a:A1){                 result.push_back( a    );   } break;
            case  7: for(int a:A2){                 result.push_back( a    );   } break;
            case  8:                for(int b:B1) { result.push_back(    b ); }    break;
            case  9: for(int a:A1){                 result.push_back(-a    );   } break;
            case 10: for(int a:A2){                 result.push_back(-a    );   } break;
            case 11:                for(int b:B1) { result.push_back(   -b ); }   break;
        }
    }
    return result;
}





std::list<int> structure_base::shift(const std::list<int> &A, int shift)
{
    std::list<int> result;
    for(int a:A)
    {
        result.push_back(a<<shift);
    }

    return result;
}

std::string structure_base::print(std::list<int> &input)
{

    std::string s;
    s =  "[ ";
    for(int i = config.size()-1; i >= 0 ;--i)
    {
        s += std::to_string(config[i]) + " ";
    }
    s += "# ";
    for(int i = shifts.size()-1; i >= 0 ;--i)
    {
        s += std::to_string(shifts[i]) + " ";
    }

    s += "] ";
    s += "No of Coefs: " + std::to_string(input.size()) + " | ";
    for(int i:input)
    {
       s = s + " " + std::to_string(i);
    }
    std::cout << s;
    return s;
}
void structure_base::order_and_unique(std::list<int> &input)
{
    input.sort();
    input.unique();
}

float structure_base::evaluate(std::list<int> &input)
{
    this->order_and_unique(input);
    if (std::find(input.begin(),input.end(),0)==input.end()){return 0;}// just solutions containing zero are interesting
    std::vector<int> dis=get_distribution(input,31);
    float kld = Kullback_Leibler_Divergenz(dis);

    kld=1/kld;

    return kld;//input.size();
}

std::vector<int> structure_base::get_distribution(const std::list<int> &input, int No_of_windows)
{

    int max_value = *input.begin();
    for(int i : input)
    {
        if(abs(i) > max_value)
        {
            max_value = abs(i);
        }
    }

    float window_size = ((2*max_value) / No_of_windows);
    std::vector<int> distribution(No_of_windows);

    for(int i: input)
    {
        float lower_Border = -max_value;
        float upper_Border = lower_Border + window_size;
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

std::vector<double> structure_base::norm_distribution(std::vector<int> &input)
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

float structure_base::Kullback_Leibler_Divergenz(std::vector<int> &P_i)
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

solutions::solutions()
{
    coeffs.clear();
    config.clear();
    no_of_Coefficients= 0;
    distribution_fitting= -1000000;
}

void solutions::print()
{
    std::cout << std::endl;
    std::cout << distribution_fitting << " ";
}
bool solutions::isBetter(solutions s)
{
    if(s.distribution_fitting> distribution_fitting)
        return true;
    else
        return false;
}

bool solutions::operator=(const solutions s)
{
    coeffs = s.coeffs;
    config = s.config;
    no_of_Coefficients= s.no_of_Coefficients;
    distribution_fitting= s.distribution_fitting;
    return true;
}

