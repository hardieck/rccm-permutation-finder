//
// Created by hardieck on 12/7/20.
//

#ifndef ADDNET_PERMUTATOR_V2_DEBUG_H
#define ADDNET_PERMUTATOR_V2_DEBUG_H

#include <iostream>

#include <vector>
#include <set>
#include <map>
#include <list>
#include <ostream>
#include <sstream>


extern int global_verbose;


using namespace std;

#define IF_VERBOSE(verbose) if(global_verbose >= verbose) for(int i=0; i < verbose; i++) std::cout << "  "; if(global_verbose >= verbose)



template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &st)
{
    typename std::vector<T>::iterator iter;
    for (iter = st.begin(); iter != st.end();)
    {
        if (typeid(T) != typeid(int)) s << "[";
        s << (*iter);
        if (typeid(T) != typeid(int)) s << "]";
        ++iter;
        if (iter != st.end())
            s << " ";
    }
    return s;
}

template<typename T>
ostream & operator<<(ostream &s, const set<T> &st)
{
    typename set<T>::iterator iter;
    for (iter = st.begin(); iter != st.end();)
    {
        if (typeid(T) != typeid(int)) s << "(";
        s << (*iter);
        if (typeid(T) != typeid(int)) s << ")";
        ++iter;
        if (iter != st.end())
            s << " ";
    }
    return s;
}


#endif //ADDNET_PERMUTATOR_V2_DEBUG_H