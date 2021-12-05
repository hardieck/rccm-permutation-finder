//
// Created by hardieck on 1/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_DATATYPS_H
#define ADDNET_PERMUTATOR_V2_DATATYPS_H

#include <list>
#include "base_obj.h"

enum rccm_type // add a type for each rccm dataflow structure / Connection Structure  (without shifts or selecetiv adder specification)
{
    rccm_type_downtCare= -1,// just for position keys in search space plan
    rccm_type_NAN    = 0, // not a number for a uninitialized state
    typ_C1 = 1, // 1 add (single selective adder)
    typ_C2 = 2, // 2 add (two selective adders in a row)
    typ_C3 = 3,  // 3 add (to selective adder besides each other followed by a third to fuse the outputs)
    typ_C4 = 4  // 4 add ()
};

enum sel_add_type // add a type for each selective adder option
{
    sel_add_type_downtCare= -1,// just for position keys in search space plan
    sel_add_type_NAN   = 0, // not a number for a uninitialized state
    typ_A = 1,
    typ_B = 2,
    typ_C = 3
};

enum permutator_typ
{
    unspecified,
    shifts_only,
    operations_only,
    usual_operations_only
};


//TODO remove enum and replace by new search space plan
enum config_level // different // shal probably be removed
{
    operation = 1,
    shifts = 2,
    structure = 3,
    all = 4
};
typedef std::set<int> coeff_set;
typedef std::pair<string,coeff_set> rccm_result;

class sspk : public base_obj //search space position key
{
public:
    rccm_type key_level1;// Connection structure type
    int key_level2; // number of selective add in a connection strucutre
    sel_add_type key_level3; // selective add type

    sspk(rccm_type _key_level1 = rccm_type_downtCare,int _key_level2 = -1, sel_add_type _key_level3=sel_add_type_downtCare)
    {
        key_level1=_key_level1;
        key_level2=_key_level2;
        key_level3=_key_level3;
    };
    ~sspk(){};

    sspk& operator=(const sspk& rhs)
    {
        this->key_level1 = rhs.key_level1;
        this->key_level2 = rhs.key_level2;
        this->key_level3 = rhs.key_level3;
        return (*this);
    };
    bool operator==(const sspk& rhs) const
    {
        if((this->key_level1 != -1)&&(rhs.key_level1 != -1))
        {
            if(this->key_level1 != rhs.key_level1) {return false;}
        }
        if((this->key_level2 != -1)&&(rhs.key_level2!= -1))
        {
            if(this->key_level2 != rhs.key_level2) {return false;}
        }
        if((this->key_level3 != -1)&&(rhs.key_level3!= -1))
        {
            if(this->key_level3 != rhs.key_level3) {return false;}
        }

        return true;
    };
    bool operator!=(const sspk& rhs) const
    {
        return !((*this)==rhs);
    };

};


class spec_sel_add : public base_obj
{
public:
    spec_sel_add()
    {
        this->input_count_A = 0;
        this->input_count_B = 0;
        this->diff_operation_count = 0;
        this->operation_set_size = 0;
        this->usualy_used_sets ={};

    };
    spec_sel_add(unsigned int input_count_A_,unsigned int input_count_B_,unsigned int diff_operation_count_,unsigned int operation_set_size_, vector<set<int>> usualy_used_sets_={})
    {
        this->input_count_A = input_count_A_;
        this->input_count_B = input_count_B_;
        this->diff_operation_count = diff_operation_count_;
        this->operation_set_size = operation_set_size_;
        this->usualy_used_sets = usualy_used_sets_;

    };
    virtual ~spec_sel_add(){};
    unsigned int input_count_A; // number of inputs for inputs A
    unsigned int input_count_B; //number of inputs for inputs B
    unsigned int diff_operation_count; // number of different operations
    unsigned int operation_set_size; // number of operation supported by implementation
    vector<set<int>> usualy_used_sets; // to init a restriced set selection. (optional)

    spec_sel_add& operator=(const spec_sel_add& rhs)
    {
        this->input_count_A = rhs.input_count_A;
        this->input_count_B = rhs.input_count_B;
        this->diff_operation_count = rhs.diff_operation_count;
        this->operation_set_size = rhs.operation_set_size;
        this->usualy_used_sets = rhs.usualy_used_sets;
        return (*this);
    };
    void print_spec() const
    {
        IF_VERBOSE(5) ENTER_FUNCTION("print_spec::print_spec()")
        std::cout << "input_count_A=" << input_count_A << std::endl;
        std::cout << "input_count_B=" << input_count_B << std::endl;
        std::cout << "diff_operation_count=" << diff_operation_count << std::endl;
        std::cout << "operation_set_size=" << operation_set_size << std::endl;
        std::cout << "usualy_used_sets:" << usualy_used_sets << std::endl;
        IF_VERBOSE(5) LEAVE_FUNCTION("print_spec::print_spec()")
    };
};
class spec_rccm : public base_obj
{
public:
    virtual ~spec_rccm(){};
    spec_rccm(unsigned int add_sel_count)
    {
        this->add_sel_count = add_sel_count;
    };
    spec_rccm& operator=(const spec_rccm& rhs)
    {
        this->add_sel_count = rhs.add_sel_count;
        return (*this);
    }
    unsigned int add_sel_count;
};


class config_reset_base : public base_obj // just to have a uniform way to reset configurations in different classes
{
public:
    config_reset_base(){}
    ~config_reset_base(){}
    virtual void reset_config()
    {
        ERROR("Virtual function is called. This should never happen!","config_reset_base:config_reset()");
        exit(-1);
    };
};

class config_helper_obj : public base_obj // to handle all objects that need to be reset during a configuration permutation step.
{
public:
    std::list<config_reset_base*> reset_list;

    ~config_helper_obj(){}
    config_helper_obj()
    {
        reset_list.clear();
    }
    void add_me_to_reset_list(config_reset_base* r_obj) // add objects which should be finished with all permutations to a restart list
    {
        reset_list.push_back(r_obj);
    }

    void clear_list() // should not be necessary to use...
    {
        this->reset_list.clear();
    }
    void reset_all_on_list()
    {
        std::list<config_reset_base*>::iterator it;
        for (it= reset_list.begin(); it != this->reset_list.end(); ++it)
        {
            (*it)->reset_config();
        }
        reset_list.clear(); //after a reset the list has to be filled again
    }

};

#endif //ADDNET_PERMUTATOR_V2_DATATYPS_H

