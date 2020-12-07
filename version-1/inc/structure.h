#ifndef STRUCTURE_BASE_H
#define STRUCTURE_BASE_H

#include <vector>
#include <list>
#include <string>

class structure_base
{

protected:
    std::vector<int> shifts;
    std::vector<int> config;
public:
    std::vector<int> permutation_max_values;
    structure_base();

    int get_no_of_shifts();
    virtual bool set_shifts(std::vector<int>);
    bool set_config(std::vector<int> input);
    bool set_shift_and_config(std::vector<int> input);
    virtual std::list<int> compute();
    bool is_a_valid_shift_vector(std::vector<int> input, int start_index, int end_index);

    void order_and_unique(std::list<int> &input);
    float evaluate(std::list<int> &input);
    std::vector<int> get_distribution(const std::list<int> &input,int No_of_windows);
    float Kullback_Leibler_Divergenz(std::vector<int> &P_in);


    std::string print(std::list<int> &input);
    std::list<int> operation_TYPE_a(std::list<int> &A1, std::list<int> &A2, std::list<int> &B1, std::list<int> &B2, std::vector<int> config={0,9});
    std::list<int> operation_TYPE_b(const std::list<int> &A1, const std::list<int> &A2, const std::list<int> &A3, const std::list<int> &B1, std::vector<int> config={0,1,2,6});
    std::list<int> operation_TYPE_b_minus(const std::list<int> &A1, const std::list<int> &A2, const std::list<int> &A3, const std::list<int> &B,std::vector<int> config={0,1,2,6});
    std::list<int> operation_TYPE_c(const std::list<int> &A1,const std::list<int> &A2,const std::list<int> &A3,const std::list<int> &A4);
    std::list<int> operation_TYPE_d(const std::list<int> &A1,const  std::list<int> &A2,const  std::list<int> &B1);
    std::list<int> operation_TYPE_e(const std::list<int> &A1,const std::list<int> &A2,const std::list<int> &B1,std::vector<int> config={2,3,4,5});
    std::list<int> shift(const std::list<int> &A, int shift);
    int get_no_of_configs();
    std::vector<double> norm_distribution(std::vector<int> &input);
};

class solutions
{
public:
    solutions();
    ~solutions(){}
    int no_of_Coefficients;
    float distribution_fitting;
    std::vector<int> config;
    std::list<int> coeffs;
    void print();
    bool isBetter(solutions s);
    bool operator=(const solutions s);
};


#endif // STRUCTURE_BASE_H
