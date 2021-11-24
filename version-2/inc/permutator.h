/*
  Permutator performs permutations on a vector of integers.

  permutationCntMaxVec specifies the maximum value in each column of the vector permutationCntVec which is permutated between [0 0 .. 0] and this maximum.

  E.g., if permutationCntMaxVec = [1 0 2] and allCombinations=true
  the permutationCntVec vectors:
  [0 0 0]
  [0 0 1]
  [0 0 2]
  [1 0 0]
  [1 0 1]
  [1 0 2]

  are generated with each call of nextPermutation().

  If allCombinations=false, only each row is permutated individually. For the example above, the result is:
  [0 0 0]
  [0 0 1]
  [0 0 2]
  [1 0 0]


*/

#ifndef PERMUTATOR_H
#define PERMUTATOR_H

#include <vector>
#include "datatyps.h"

using namespace std;
enum permutator_typ
{
    unspecified,
    shifts_only,
    operations_only,
    usual_operations_only
};

class permutation_data : public base_obj
{
public:
    permutation_data();
    ~permutation_data(){};
    permutation_data& operator=(const permutation_data& rhs);
    std::vector<int> permutationCntMaxVec;
    std::vector<int> permutationCntMinVec; // contains reset values if min_vec is used.
    std::vector<int> permutationCntVec;
    std::vector<bool> risingBlockBreakVec;// contains true far each beginning of a rising block if rising_block is used.
    //rising blocks are groups of indexes within each value is unique (with rising value for simplicity)
    //TODO remove rising_block_list and exchange function with risingBlockBreakVec
    std::vector<pair<vector<int>::iterator, vector<int>::iterator> > rising_block_list; //Specifie a start and end iterator for the permutationCntVec in which only rising values are allowed

    permutator_typ p_typ;
    int permutationIndex;
    int permutationIndexMax;
    bool allCombinations;
    bool min_vec_is_used;
    bool rising_block_is_used; // to exclude all permutations with repeating operations or shifts(for the same input)
    void printPermutationData(bool block =false);
    void init(unsigned int new_size = 1, bool min_vec = false, bool rising_block = false);
};

//BAsic Permutation class. Do the lowes level of permutation with higher efficiency as the other layers.
class Permutator : public config_reset_base
{
public:
    Permutator(std::vector<int> *permutationCntMaxVec, bool allCombinations=true, std::vector<int> *permutationCntMinVec=nullptr);
    Permutator();
    ~Permutator();

    //TODO !! save a tone of time!!! make Permutator index jump if the next value is in same rising block and lower as the current one
    bool next_config(config_helper_obj& conv_helper); // external next config function.
    void reset_config(){resetPermutation();} // Raper function for compatibility with the base class

    std::set<int>* get_operation_from_config(); // transform internal permutation state to usable operation sets
    std::vector<int>* get_shift_from_config(); // transform internal permutation state to usable shifts
    void printPermutation(bool reverse = false);
    bool set_config_from_spec(const spec_sel_add s,const permutator_typ typ=operations_only);

    bool check_all_rising_blocks();
    bool nextPermutation();// internal step. split from external to handle invalid intermediate results
    void resetPermutation(); // internal step. kept from original code.
    permutation_data *pd;
    bool dataowner;
    void add_rising_block(unsigned int start,unsigned int length);
protected:
};

#endif // PERMUTATOR_H
