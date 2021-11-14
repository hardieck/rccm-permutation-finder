
#include "../inc/mcm_permutation.h"
#include <iostream>



std::list<int> structure::operation_TYPE_a(std::list<int>  &A1,std::list<int>  &A2, std::list<int> &B1, std::list<int> &B2)
{
    std::list<int> result;
    for(int a:A1)
    {
        for(int b:B1)
        {
            result.push_back(a+b);
        }
    }
    for(int a:A2)
    {
        for(int b:B2)
        {
            result.push_back(a+b);
        }
    }
    return result;
}

std::list<int> structure::operation_TYPE_b(std::list<int> &A1, std::list<int> &A2, std::list<int> &A3, std::list<int> &B)
{
    std::list<int> result;
    for(int b:B)
    {

        for(int a:A1)
        {
            result.push_back(a+b);
        }

        for(int a:A2)
        {
            result.push_back(a+b);
        }
        for(int a:A3)
        {
            result.push_back(a+b);
        }
        for(int b:B)
        {
            result.push_back(b);
        }

    }
    return result;
}

std::list<int> structure::operation_TYPE_b_minus(std::list<int> &A1, std::list<int> &A2, std::list<int> &A3, std::list<int> &B)
{
    std::list<int> result;
    for(int b:B)
    {

        for(int a:A1)
        {
            result.push_back(a-b);
        }

        for(int a:A2)
        {
            result.push_back(a-b);
        }
        for(int a:A3)
        {
            result.push_back(a-b);
        }
        for(int b:B)
        {
            result.push_back(-b);
        }

    }
    return result;
}

std::list<int> structure::operation_TYPE_c(std::list<int> &A1, std::list<int> &A2, std::list<int> &A3, std::list<int> &A4)
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
std::list<int> structure::operation_TYPE_d(std::list<int> &A1, std::list<int> &A2, std::list<int> &B1)
{
    // A1+B
    // A2+B
    //-A1+B
    //-A2+B
    //    B
    // A1
    // A2
    //-A1
    std::list<int> result;
    for(int b:B1)
    {
        // result.push_back(a); not usable commend cause of error
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
    for(int a:A1)
    {
        result.push_back(a);
        result.push_back(-a);
    }
    for(int a:A2)
    {
        result.push_back(a);
    }

    return result;
}



std::list<int> structure::shift(std::list<int> &A, int shift)
{
    std::list<int> result;
    for(int a:A)
    {
        result.push_back(a<<shift);
    }

    return result;
}

std::string structure::print(std::list<int> input)
{
    std::string s;
    for(int i:input)
    {
       s = s + " " + std::to_string(i);
    }
    std::cout << s;
    return s;
}
void structure::order_and_unique(std::list<int> &input)
{
    input.sort();
    input.unique();
}

float structure::evaluate(std::list<int> &input)
{
    this->order_and_unique(input);
    return input.size();
}



