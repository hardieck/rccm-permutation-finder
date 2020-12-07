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

using namespace std;


class Permutator
{
public:
  Permutator(vector<int> *permutationCntMaxVec, bool allCombinations=true, vector<int> *permutationCntMinVec=nullptr);

  bool nextPermutation();
  void resetPermutation();

  vector<int> permutationCntVec;

  void printPermutation();

private:
  vector<int> *permutationCntMaxVec;
  vector<int> *permutationCntMinVec;
  int permutationIndex;
  int permutationIndexMax;
  bool allCombinations;
};

#endif // PERMUTATOR_H
