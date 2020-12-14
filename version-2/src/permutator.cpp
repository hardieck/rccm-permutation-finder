#include "../inc/permutator.h"
#include <iostream>

using namespace std;

permutation_data::permutation_data()
{
}
permutation_data& permutation_data::operator=(const permutation_data& rhs)
{
    set_vec(permutationCntMaxVec,rhs.permutationCntMaxVec);
    set_vec(permutationCntMinVec,rhs.permutationCntMinVec);
    set_vec(permutationCntVec,rhs.permutationCntVec);
    permutationIndex = rhs.permutationIndex;
    permutationIndexMax = rhs.permutationIndexMax;
    allCombinations = rhs.allCombinations;
    min_vec_is_used = rhs.min_vec_is_used;
    return *this;
}

Permutator::Permutator(vector<int> *permutationCntMaxVec, bool allCombinations, vector<int> *permutationCntMinVec)
{
    pd->permutationCntMaxVec = *permutationCntMaxVec;
    if(permutationCntMaxVec)
    {
        pd->permutationCntMinVec = *permutationCntMinVec;
        pd->min_vec_is_used = true;
    }
    pd->allCombinations = allCombinations;

    pd->permutationIndex=0;
    pd->permutationIndexMax = permutationCntMaxVec->size()-1;

  if(permutationCntMinVec)
  {
      pd->permutationCntVec.resize(pd->permutationIndexMax+1);
    if(permutationCntMinVec->size() != permutationCntMaxVec->size())
    {
      cerr << "Vector size mismatch" << endl;
      exit(-1);
    }
    for(unsigned i=0; i < permutationCntMinVec->size(); i++)
    {
        pd->permutationCntVec[i] = (*permutationCntMinVec)[i];
    }
  }
  else
  {
      pd->permutationCntVec.resize(pd->permutationIndexMax+1,0);
  }
}


bool Permutator::nextPermutation()
{
  if(pd->permutationIndexMax < 0) return false;
  if(pd->allCombinations)
  {
    //modify permutation, for that first move index to position to increment:
    while(pd->permutationCntVec[pd->permutationIndex] == (pd->permutationCntMaxVec)[pd->permutationIndex])
    {
      if(pd->permutationIndex == pd->permutationIndexMax)
      {
        return false; //no further permutations
      }
        pd->permutationIndex++;
    }

      pd->permutationCntVec[pd->permutationIndex]++;

    while(pd->permutationIndex > 0)
    {
      --pd->permutationIndex;
      if(pd->min_vec_is_used)
          pd->permutationCntVec[pd->permutationIndex] = (pd->permutationCntMinVec)[pd->permutationIndex]; //move index back
      else
          pd->permutationCntVec[pd->permutationIndex] = 0; //move index back
    }
  }
  else
  {
    while(pd->permutationCntVec[pd->permutationIndex] == (pd->permutationCntMaxVec)[pd->permutationIndex])
    {
        pd->permutationCntVec[pd->permutationIndex]=0;
      if(pd->permutationIndex < pd->permutationIndexMax)
      {
          pd->permutationIndex++;
      }
      else
      {
        return false; //no further permutations
      }
    }

      pd->permutationCntVec[pd->permutationIndex]++;
  }
  return true;
}
void Permutator::resetPermutation()
{
  for(unsigned i=0; i < pd->permutationCntVec.size(); i++)
  {
    if(pd->min_vec_is_used)
        pd->permutationCntVec[i] = (pd->permutationCntMinVec)[i];
    else
        pd->permutationCntVec[i] = 0;
  }
    pd->permutationIndex=0;
}

void Permutator::printPermutation()
{
  cout << "[ ";
  for(int i=(int) pd->permutationCntVec.size()-1; i >= 0; i--)
  {
    cout << pd->permutationCntVec[i] << " ";
  }
  cout << "]";
}
