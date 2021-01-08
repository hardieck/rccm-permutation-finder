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
#include "base_obj.h"

using namespace std;
//TODO Der Permutator muss vollständig auf externen vectoren arbeiten können. Somit nur die Verwaltungsstruktur liefern.

class permutation_data : public base_obj
{
public:
    permutation_data();
    permutation_data& operator=(const permutation_data& rhs);
    vector<int> permutationCntMaxVec;
    vector<int> permutationCntMinVec;
    vector<int> permutationCntVec;
    int permutationIndex;
    int permutationIndexMax;
    bool allCombinations;
    bool min_vec_is_used;

    void init(unsigned int new_size = 1, bool min_vec = false);
    void printPermutationData(bool block =false);
};

class Permutator : public base_obj
{
public:
  Permutator(vector<int> *permutationCntMaxVec, bool allCombinations=true, vector<int> *permutationCntMinVec=nullptr);
  Permutator();
  ~Permutator();

  bool nextPermutation();
  void resetPermutation();

  void printPermutation(bool reverse = false);

  permutation_data *pd;
  bool dataowner;

};

#endif // PERMUTATOR_H
