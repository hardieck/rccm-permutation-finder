#ifndef MCM_PERMUTATION_H
#define MCM_PERMUTATION_H

#include <list>
#include <string>



class structure
{
public:
    structure(){}
    std::string print(std::list<int> input);
    std::list<int> operation_TYPE_a(std::list<int> &A1, std::list<int> &A2, std::list<int> &B1, std::list<int> &B2);
    std::list<int> operation_TYPE_b(std::list<int> &A1, std::list<int> &A2, std::list<int> &A3, std::list<int> &B);
    std::list<int> operation_TYPE_b_minus(std::list<int> &A1, std::list<int> &A2, std::list<int> &A3, std::list<int> &B);
    std::list<int> operation_TYPE_c(std::list<int> &A1, std::list<int> &A2, std::list<int> &A3, std::list<int> &A4);
    std::list<int> shift(std::list<int> &A, int shift);
    void order_and_unique(std::list<int> &input);
    float evaluate(std::list<int> &input);
    std::list<int> operation_TYPE_d(std::list<int> &A1, std::list<int> &A2, std::list<int> &B1);
};



#endif // MCM_PERMUTATION_H
