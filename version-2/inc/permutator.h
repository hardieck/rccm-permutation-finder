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
enum permutator_type
{
    shifts_only,
    usual_operations_only,
    all_operations_only,
    shifts_and_usual_operations,
    shifts_and_all_operations
};

class permutation_data : public base_obj
{
public:
    permutation_data();
    permutation_data& operator=(const permutation_data& rhs);
    std::vector<int> permutationCntMaxVec;
    std::vector<int> permutationCntMinVec;
    std::vector<int> permutationCntVec;
    int permutationIndex;
    int permutationIndexMax;
    bool allCombinations;
    bool min_vec_is_used;
    bool do_not_repeat_options; // to exclude all permutations with repeding operations or shifts(for the same input)
    void printPermutationData(bool block =false);
    void init(unsigned int new_size = 1, bool min_vec = false);
    void init(const spec_sel_add&,permutator_type=shifts_and_all_operations,bool do_not_repeat=true);
};

class Permutator : public config_reset_base
{
public:
  Permutator(std::vector<int> *permutationCntMaxVec, bool allCombinations=true, std::vector<int> *permutationCntMinVec=nullptr);
  Permutator();
  ~Permutator();

  bool nextPermutation();
  void resetPermutation();
  void reset_config(){resetPermutation();}

  void printPermutation(bool reverse = false);

  permutation_data *pd;
  bool dataowner;

    std::set<int> get_config();
};

#endif // PERMUTATOR_H
