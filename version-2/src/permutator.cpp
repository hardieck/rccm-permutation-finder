#include "../inc/permutator.h"
#include <iostream>
#include <vector>

using namespace std;

// tiny helper function to chek if the vector has duplicates without sorting it...
bool hasDuplicates(const std::vector<int>& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] == arr[j])
                return true;
        }
    }
    return false;
}

permutation_data::permutation_data()
{
    allCombinations = true;
    min_vec_is_used = false;
    init(1,false);
}

void permutation_data::init(unsigned int new_size, bool min_vec)
{
    permutationIndex=0;
    permutationCntMaxVec.resize(new_size);
    permutationCntVec.resize(new_size);
    min_vec_is_used = min_vec;
    for (int i = 0; i < new_size;++i)
    {
        permutationCntMaxVec[i] = 0;
        permutationCntVec[i] = 0;
    }

    if (min_vec_is_used)
    {
        permutationCntMinVec.resize(new_size);
        for (int i = 0; i < new_size;++i)
        {
            permutationCntMinVec[i] = 0;
        }
    }
    else
    {
        permutationCntMinVec.clear();
    }
    permutationIndex = 0;
    permutationIndexMax = permutationCntMaxVec.size()-1;
}

void permutation_data::printPermutationData(bool block)
{
    if (block)
    {
        std::cout << "allCombinations: " << allCombinations << std::endl;
        std::cout << "permutationIndexMax: " << permutationIndexMax << std::endl;
        std::cout << "permutationIndex   : " << permutationIndex << std::endl;
        std::cout << "permutationCntVec   : " << permutationCntVec << std::endl;
        std::cout << "permutationCntMaxVec: " << permutationCntMaxVec << std::endl;
        std::cout << "permutationCntMinVec: " << permutationCntMinVec << std::endl;
        std::cout << "min_vec_is_used: " << min_vec_is_used << std::endl;
    }
    else
    {
        std::cout << "allCombinations: " << allCombinations << " permutationIndexMax: " << permutationIndexMax << " permutationIndex: " << permutationIndex << " permutationCntVec: " << permutationCntVec <<  " permutationCntMaxVec: " << permutationCntMaxVec << " permutationCntMinVec: " << permutationCntMinVec << " min_vec_is_used: " << min_vec_is_used << std::endl;
    }
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
    dataowner = true;
    pd = new permutation_data;
    pd->permutationCntMaxVec = *permutationCntMaxVec;
    if(permutationCntMinVec)
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
Permutator::Permutator()
{
    dataowner = true;
    pd = new permutation_data;
    pd->permutationCntMaxVec.resize(1);
    pd->permutationIndex=0;
    pd->permutationIndexMax = pd->permutationCntMaxVec.size()-1;
    pd->min_vec_is_used = false;
    pd->permutationCntMinVec.clear();
}
Permutator::~Permutator()
{
    if(dataowner == true)
    {
        delete pd;
    }
}


bool Permutator::next_config(config_helper_obj& conv_helper)
{
    //TODO chek if the return value of Permuator has the same meaning as next_config...
    if(pd->do_not_repeat_options)
    {
        bool return_value = false;
        return_value=nextPermutation();
        while((return_value == true)&&(check_all_rising_blocks())) // rerun if there is (still) a problem with the block list
        {
            return_value = nextPermutation();
        }
        if(return_value==false){conv_helper.add_me_to_reset_list((config_reset_base*)this);}
        return return_value;
    }
    else
    {
        bool return_value = nextPermutation();
        if(return_value==false){conv_helper.add_me_to_reset_list((config_reset_base*)this);}
        return return_value;
    }
}

bool Permutator::nextPermutation()
{
    IF_VERBOSE(9) std::cout << "last config was: " << this->pd->permutationCntVec;
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
    IF_VERBOSE(9) std::cout << " next config is: " << this->pd->permutationCntVec << std::endl;
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

void Permutator::printPermutation(bool reverse)
{
    if (reverse) {
        cout << "[ ";
        for (int i = (int) pd->permutationCntVec.size() - 1; i >= 0; i--) {
            cout << pd->permutationCntVec[i] << " ";
        }
        cout << "]";
    }
    else {
        cout << "[ ";
        for (int i = 0; i < pd->permutationCntVec.size(); ++i) {
            cout << pd->permutationCntVec[i] << " ";
        }
        cout << "]";
    }
}
bool Permutator::check_all_rising_blocks() // returns true if there is a problem within a rising block
{
    IF_VERBOSE(8) std::cout << "Permutator: check_all_rising_blocks: Enter Function" << std::endl;
    if (pd->rising_block_list.size() == 0)
    {
        IF_VERBOSE(9) std::cout << "Permutator: check_all_rising_blocks: rising_block_list is empty" << std::endl;
        return false; // as there are no block to check...
    }
    IF_VERBOSE(9) std::cout << "Permutator: check_all_rising_blocks: rising_block_list has size:" << pd->rising_block_list.size() << std::endl;

    // TODO:use iterator! Don't know why it doesnt worked
    //pair< vector<int>::iterator, vector<int>::iterator > it;
    IF_VERBOSE(8) std::cout << "Permutator: check_all_rising_blocks: check blocks" << std::endl;
    for(int i=0; i < pd->rising_block_list.size() ; ++i)
    {
        IF_VERBOSE(9) std::cout << "Permutator: check_all_rising_blocks: check Block Nr:" << i << std::endl;
        vector<int>::iterator start = pd->rising_block_list[i].first;
        vector<int>::iterator end = pd->rising_block_list[i].second;

        vector<int>::iterator it;
        int last_value=-1; //asuming that this value is not used in the permutator
        for(it = start; it != end; ++it)
        {
            //IF_VERBOSE(9) std::cout << "Permutator: check_all_rising_blocks: checking next element. Last_value was:" << last_value << "current value is:" << (*it) << std::endl;
            if(last_value < (*it) )
            {
                last_value = (*it);
            }
            else
            {
                return true; // returns true if there is a problem within a rising block
            }
        }
    }
    return false;
}

void Permutator::add_rising_block(unsigned int start,unsigned int length)
{
    if(start+length > pd->permutationCntVec.size())
    {
        ERROR("Can't set block! Out of range!","Permutator::add_rising_block()")
    }
    pair<vector<int>::iterator, vector<int>::iterator> my_block;
    vector<int>::iterator it = pd->permutationCntVec.begin();
    for(int i=0; i <= pd->permutationCntVec.size(); ++i)
    {
        if(i == start){my_block.first = it;}
        if(i == start+length){my_block.second = it;}
        (++it);
    }
    pd->rising_block_list.push_back(my_block);
}
bool Permutator::set_config_from_spec(const spec_sel_add s,const permutator_type typ)
{
    int MAX_SCHIFT=4; //Todo: MAke configurable or global or ...

    IF_VERBOSE(5) std::cout << "Permutator::set_config_from_spec: Enter Function"<< std::endl;
    switch(typ) {
        case all_operations_only: {
            IF_VERBOSE(5) std::cout << "Permutator::set_config_from_spec: Case: all_operations_only" << std::endl;
            IF_VERBOSE(6) {
                std::cout << "Print used spec s:" << std::endl;
                s.print_spec();
            }
            // specify ranges:
            pd->init(s.operation_set_size, true);
            pd->do_not_repeat_options = true;// there shall not be duplicate operations, so we can shrink the search space
            add_rising_block(0,
                             s.operation_set_size); // there shall not be duplicate operations, so we can shrink the search space
            unsigned int vec_size=pd->permutationCntMaxVec.size();
            for (int i = 0; i < vec_size; ++i) {
                //pd->permutationCntMaxVec[i] = s.diff_operation_count;
                // there shall not be duplicate operations, so we can shrink the search space
                pd->permutationCntMaxVec[vec_size-i-1] = s.diff_operation_count - i-1; // to create a rising values. // -1 cause vec_size  start counting by 1 // -1 cause diff_operation count start by 0
                pd->permutationCntMinVec[i] = i; // there shall not be duplicate operations, so we can shrink the search space
            }
            break;
        }
        case shifts_only: {
            IF_VERBOSE(5) std::cout << "Permutator::set_config_from_spec: Case: shifts_only" << std::endl;
            IF_VERBOSE(6) {
                std::cout << "Print used spec s:" << std::endl;
                s.print_spec();
            }
            pd->init(s.input_count_A + s.input_count_B, true);
            pd->do_not_repeat_options = true;// there shall not be duplicate operations, so we can shrink the search space
            add_rising_block(0,s.input_count_A); // there shall not be duplicate shifts for input A, so we can shrink the search space
            add_rising_block(s.input_count_A,s.input_count_B); // there shall not be duplicate shifts for input B, so we can shrink the search space

            // loop For Input A
            for (int i = 0; i < s.input_count_A; ++i) {
                pd->permutationCntMaxVec[i] = MAX_SCHIFT;
                pd->permutationCntMinVec[i] = i; // there shall not be duplicate shifts, so we can shrink the search space
            }
            // loop For Input B
            int j = 0;
            for (int i = s.input_count_A; i < (s.input_count_A + s.input_count_B); ++i) {
                pd->permutationCntMaxVec[i] = MAX_SCHIFT;
                pd->permutationCntMinVec[i] = j++; // there shall not be duplicate shifts, so we can shrink the search space
            }
            break;
        }
        default:
            ERROR("Not suportet config type", "Permutator::set_config_from_spec()");
    }
    return 1;
}
