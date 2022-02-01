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
#define ERROR(x,from) std::cout << "ERROR: " << x << std::endl << "From: " << from << std::endl; exit(-1);
#define ENTER_FUNCTION(x) std::cout << x << " Enter Function" << std::endl;
#define LEAVE_FUNCTION(x) std::cout << x << " Leave Function" << std::endl;


template<typename T>
std::set<T> vec2set(const std::vector<T> &v)
{
    std::set<T> s;
    typename std::vector<T>::const_iterator iter;
    for (iter = v.begin(); iter != v.end();)
    {
        s.insert(*iter);
    }
    return s;
}
template<typename T>
std::vector<T> set2vec(const std::set<T> &s)
{
    std::vector<T> v;
    typename std::set<T>::const_iterator iter;
    for (iter = v.begin(); iter != v.end();)
    {
        v.push_back(*iter);
    }
    return v;
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

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &st)
{
    typename std::vector<T>::const_iterator iter;
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
void set_vec(vector<T> &lhs, const vector<T> &rhs)
{
    typename vector<T>::const_iterator it_r = rhs.begin();
    if (rhs.size() != lhs.size())
    {
        lhs.clear();
        for (; it_r != rhs.end(); ++it_r)
        {
            lhs.push_back(*it_r);
        }
    }
    else
    {
        typename vector<T>::iterator it_l = lhs.begin();
        while (it_l != lhs.end())
        {
            *it_l = *it_r;
            ++it_l;
            ++it_r;
        }
    }
}


#endif //ADDNET_PERMUTATOR_V2_DEBUG_H