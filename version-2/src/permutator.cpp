#include "../inc/permutator.h"
#include <iostream>

using namespace std;

Permutator::Permutator(vector<int> *permutationCntMaxVec, bool allCombinations, vector<int> *permutationCntMinVec)
{
  this->permutationCntMaxVec = permutationCntMaxVec;
  this->permutationCntMinVec = permutationCntMinVec;
  this->allCombinations = allCombinations;

  permutationIndex=0;
  permutationIndexMax = permutationCntMaxVec->size()-1;

  if(permutationCntMinVec)
  {
    permutationCntVec.resize(permutationIndexMax+1);
    if(permutationCntMinVec->size() != permutationCntMaxVec->size())
    {
      cerr << "Vector size mismatch" << endl;
      exit(-1);
    }
    for(unsigned i=0; i < permutationCntMinVec->size(); i++)
    {
      permutationCntVec[i] = (*permutationCntMinVec)[i];
    }
  }
  else
  {
    permutationCntVec.resize(permutationIndexMax+1,0);
  }
}


bool Permutator::nextPermutation()
{
  if(permutationIndexMax < 0) return false;
  if(allCombinations)
  {
    //modify permutation, for that first move index to position to increment:
    while(permutationCntVec[permutationIndex] == (*permutationCntMaxVec)[permutationIndex])
    {
      if(permutationIndex == permutationIndexMax)
      {
        return false; //no further permutations
      }
      permutationIndex++;
    }

    permutationCntVec[permutationIndex]++;

    while(permutationIndex > 0)
    {
      --permutationIndex;
      if(permutationCntMinVec)
        permutationCntVec[permutationIndex] = (*permutationCntMinVec)[permutationIndex]; //move index back
      else
        permutationCntVec[permutationIndex] = 0; //move index back
    }
  }
  else
  {
    while(permutationCntVec[permutationIndex] == (*permutationCntMaxVec)[permutationIndex])
    {
      permutationCntVec[permutationIndex]=0;
      if(permutationIndex < permutationIndexMax)
      {
        permutationIndex++;
      }
      else
      {
        return false; //no further permutations
      }
    }

    permutationCntVec[permutationIndex]++;
  }
  return true;
}
void Permutator::resetPermutation()
{
  for(unsigned i=0; i < permutationCntVec.size(); i++)
  {
    if(permutationCntMinVec)
      permutationCntVec[i] = (*permutationCntMinVec)[i];
    else
      permutationCntVec[i] = 0;
  }
  permutationIndex=0;
}

void Permutator::printPermutation()
{
  cout << "[ ";
  for(int i=(int) permutationCntVec.size()-1; i >= 0; i--)
  {
    cout << permutationCntVec[i] << " ";
  }
  cout << "]";
}
