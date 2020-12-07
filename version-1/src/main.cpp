#include "structures.h"
#include "permutator.h"
#include "structure.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool is_a_valid_shift_vector(std::vector<int> input);

std::list<int> calculate_factors(std::vector<int>);


int main(int argc, char**arg)
{
    //structure_1BB2B3E x;
    //structure_1B2B3E x;
    structure_1B2E x;

    //std::vector<int> shift_max = {1,2,3,3,1,2,3,3,1,2,3,3};
    //std::vector<int> shift_max = {2,3,4,4,2,3,4,4,2,4,4,4,4};

    //erm.permutationCntVec = {0,1,2,0,0,1,2,0,0,1,2,0};

    std::vector<int> shift_max = x.permutation_max_values;

    Permutator perm(&shift_max);


    vector<solutions> interessting_results(1000);

    do
    {
        if(x.set_shift_and_config(perm.permutationCntVec))
        {
            solutions S;
            S.coeffs =  x.compute();
            S.distribution_fitting = x.evaluate(S.coeffs);
            S.no_of_Coefficients=S.coeffs.size();
            S.config = perm.permutationCntVec;

            S.print();
            x.print(S.coeffs);

            if(interessting_results[S.no_of_Coefficients].isBetter(S))
            {
                interessting_results[S.no_of_Coefficients] = S;
            }
        }
    }
    while(perm.nextPermutation());

    std::cout << std::endl << std::endl;
    std::cout << "found following options." << std::endl;
    for(int i= 0; i< interessting_results.size();++i)
    {
        solutions S=interessting_results[i];

        if(S.no_of_Coefficients > 0)
        {
            x.set_shift_and_config(S.config);
            x.compute();
            x.evaluate(S.coeffs);
            S.print();
            x.print(S.coeffs);
        }
    }


    return 0;
}

/*
std::list<int> calculate_factors(std::vector<int> shifts)
{
    int shift_AA1 = shifts[0];
    int shift_AA2 = shifts[1];
    int shift_AA3 = shifts[2];
    int shift_AB1 = shifts[3];
    int shift_BA1 = shifts[4];
    int shift_BA2 = shifts[5];
    int shift_BA3 = shifts[6];
    int shift_BB1 = shifts[7];
    int shift_CA1 = shifts[8];
    int shift_CA2 = shifts[9];
    int shift_CA3 = shifts[10];
    int shift_CB1 = shifts[11];

    structure_base x;

    std::list<int> input = {1};

    std::list<int> A;
    std::list<int> B;
    std::list<int> C;

    A = x.operation_TYPE_b(x.shift(input,shift_AA1),x.shift(input,shift_AA2),x.shift(input,shift_AA3),x.shift(input,shift_AB1));
    B = x.operation_TYPE_b_minus(x.shift(input,shift_BA1),x.shift(input,shift_BA2),x.shift(input,shift_BA3),x.shift(input,shift_BB1));
    C = x.operation_TYPE_b(x.shift(A,shift_CA1),x.shift(A,shift_CA2),x.shift(A,shift_CA3),x.shift(B,shift_CB1));

    x.order_and_unique(C);
    return C;
}
*/

