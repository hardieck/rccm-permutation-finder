//
// Created by hardieck on 9/27/19.
//

#include "../inc/selective_add.h"
#include "../inc/calc_selective_adder_typ_a.h"
#include "../inc/calc_selective_adder_typ_b.h"
#include "../inc/calc_selective_adder_typ_c.h"
#include "../inc/helper.h"
#include <string>
#include <memory>
//
//std::set<int> selective_add::get_operation_set()
//{
//    if (operation_mode)
//        return mode_1_current_operation_set;
//    else
//        return vec2set(mode_0_current_operation_set);
//}
//

std::string selective_add::get_config()// return only the part for one Selective add with shifts in HM1 standart
{
    IF_VERBOSE(5) ENTER_FUNCTION("selective_add::get_config()")
    IF_VERBOSE(6) std::cout << "Prepare current_config string and add Operation Type" << std::endl;
    std::string current_config;
    current_config.clear();
    IF_VERBOSE(6) std::cout << "Add connection Structure." << std::endl;
    switch (sel_add_search_space[from_sp_use]) {
        case typ_A : current_config += "-A"; break;
        case typ_B : current_config += "-B"; break;
        case typ_C : current_config += "-C"; break;
        default:
        ERROR("Unsupported Selective Adder Type!", "selective_add::get_config()")
    }
    IF_VERBOSE(6) std::cout << "Add operations" << std::endl;
    std::set<int> op_set = get_operation_set();
    spec_sel_add current_spec = get_spec();
    //for(unsigned int i=0; i < current_spec.operation_set_size;++i)
    //{
    //    current_config += int2extendHEX(perm_operation.pd->permutationCntVec[i]);
    //}
    std::set<int>::const_iterator it;
    for(it =op_set.begin(); it != op_set.end(); ++it)
    {
        current_config += int2extendHEX(*it);
    }


    current_config += "-"; // to slit operations from shifts
    IF_VERBOSE(6) std::cout << "Add Shifts" << std::endl;
    IF_VERBOSE(6) std::cout << "Add Shifts for input A" << std::endl;
    for(unsigned int i=0; i < current_spec.input_count_A;++i)
    {
        current_config += int2extendHEX(get_shift(i));
    }
    current_config += "-"; // to slit shifts for input A from input B
    IF_VERBOSE(6) std::cout << "Add Shifts for input B" << std::endl;
    for(unsigned int i=0; i < current_spec.input_count_B;++i)
    {
        current_config += int2extendHEX(get_shift(i+ current_spec.input_count_A));
    }
    IF_VERBOSE(6) std::cout << "Add Shifts for input B" << std::endl;
    return current_config;
}
bool selective_add::set_config(std::string new_config)// use only the part for one Selective add with shifts in HM1 standart
{
    IF_VERBOSE(5) ENTER_FUNCTION("selective_add::set_config(std::string new_config)")
ERROR("Funktion is unsupported Yet","selective_add::set_config(std::string new_config)")
    return false;
}

bool selective_add::next_config(config_helper_obj& conv_helper)
{
    IF_VERBOSE(8)ENTER_FUNCTION("selective_add::next_config(config_helper_obj& conv_helper)")
    bool new_config_was_set = false;

    IF_VERBOSE(9) std::cout << "selective_add: next_config: try next operation" << std::endl;
    new_config_was_set = this->perm_operation.next_config(conv_helper);
    if(new_config_was_set){
        IF_VERBOSE(10) std::cout << "selective_add: next_config: new Config was set" << std::endl;
        conv_helper.reset_all_on_list(); // reset all previous operations to restart permutation with this new configuration
        return 1;
    } // if a permutation was changed return true

    IF_VERBOSE(9) std::cout << "selective_add: next_config: no operation config left, try next Shift configuration" << std::endl;
        new_config_was_set = this->perm_shift.next_config(conv_helper);
        if(new_config_was_set) {
            IF_VERBOSE(10) std::cout << "selective_add: next_config: new Config was set" << std::endl;
            conv_helper.reset_all_on_list(); // reset all previous operations to restart permutation with this new configuration
            return 1;
        }// if a permutation was changed return true

    IF_VERBOSE(9) std::cout << "selective_add: next_config: no shift config left, try next selective adder type from search space" << std::endl;
    //iterate over search space elements (typ_A typ_B typ_C,...)
    IF_VERBOSE(9) std::cout << "from_sp_use: " << from_sp_use << " sel_add_search_space.size()=" << sel_add_search_space.size() << std::endl;
    if(from_sp_use < sel_add_search_space.size()-1)
    {
        ++from_sp_use;
        new_config_was_set = true;
        IF_VERBOSE(9) std::cout << "selective_add: next_config: new Config was set. use search space element:" << from_sp_use << std::endl;
        conv_helper.reset_all_on_list(); // reset all previous operations to restart permutation with this new configuration
        init(); //as the type changed the calc obj as to change and the permutators have to reload the specs for the new type.
        return 1;
    }

    //if there  is no config left
    //try different Connection structures from search space
    IF_VERBOSE(9) std::cout << "selective_add: next_config: no selective adder type config left" << std::endl;
    conv_helper.add_me_to_reset_list((config_reset_base*) this);
    IF_VERBOSE(9) std::cout << "selective_add: next_config: Iterate over all configurations from DONE" << std::endl;
    return false; // no config left. this was the last one
}

void selective_add::reset_config()
{
    IF_VERBOSE(8) ENTER_FUNCTION("selective_add::reset_config()")
    from_sp_use=0;
    init();
    init_permutators();// if it doesn't happen in init it has to be done here
}

spec_sel_add selective_add::get_spec()
{
    IF_VERBOSE(8) ENTER_FUNCTION("selective_add::get_spec()")
    spec_sel_add current_spec;
    switch(sel_add_search_space[from_sp_use])
    {
        case typ_A: {calc_selective_adder_typ_a obj; current_spec = obj.get_spec();} break;
        case typ_B: {calc_selective_adder_typ_b obj; current_spec = obj.get_spec();} break;
        case typ_C: {calc_selective_adder_typ_c obj; current_spec = obj.get_spec();} break;
        default:
        ERROR("unsupported Selective Adder type", "selective_add::get_spec()")
    }
    return current_spec;
}


const sspk selective_add::get_current_key() const
{
    return sspk(current_rccm_type,sel_add_pos,sel_add_search_space[from_sp_use]);
}

void selective_add::init_permutators()
{
    IF_VERBOSE(8) ENTER_FUNCTION("selective_add::init_permutators()")
    spec_sel_add current_spec = this->get_spec();

    IF_VERBOSE(9) std::cout << "before" << std::endl;
    IF_VERBOSE(9) this->perm_operation.pd->printPermutationData();
    IF_VERBOSE(9) this->perm_shift.pd->printPermutationData();

    //TODO make dependent from search space plan
    this->perm_shift.set_config_from_spec(current_spec, shifts_only,
       ssp->get_sel_add_max_shift(get_current_key()),
       ssp->get_sel_add_fixed_shifts(get_current_key())
    );

    this->perm_shift.resetPermutation();
    //TODO change for usual_operations_only test, and make dependent from search space plan
    this->perm_operation.set_config_from_spec(current_spec,
       ssp->get_sel_add_operating_mode(get_current_key()), 0, nullptr,
       ssp->get_sel_add_fixed_opset(get_current_key())
    );

    //this->perm_operation.set_config_from_spec(current_spec, usual_operations_only);
    this->perm_operation.resetPermutation();

    IF_VERBOSE(9) std::cout << "after" << std::endl;
    IF_VERBOSE(9) this->perm_operation.pd->printPermutationData();
    IF_VERBOSE(9) this->perm_shift.pd->printPermutationData();

    IF_VERBOSE(8) LEAVE_FUNCTION("selective_add::init_permutators()")
}


//void selective_add::add_possible_set(set<int> s)
//{
//    this->operation_mode=1; // possible operation set is specified therefore mode 1 has to be used.
//    this->possible_operations.push_back(s);
//}

// TODO: remove or fix! comented to make error silent
//bool selective_add::get_shift_permutation() const {
//    return do_shift_permutation;
//}
//
//void selective_add::set_shift_permutation(bool shift_permutation)
//{
//    do_shift_permutation = shift_permutation;
//}
//
//bool selective_add::get_LUT_permutation() const
//{
//    return do_LUT_permutation;
//}
//void selective_add::set_LUT_permutation(bool LUT_permutation)
//{
//    do_LUT_permutation = LUT_permutation;
//}
//
//bool selective_add::next_m0() {
//    ERROR("Not implemented yet.", selective_add::next_m0())
//    return false;
//}
//bool selective_add::next_m1() {
//
//    Permutator permut(&permut_max,true,&permut_min);
//    //permut.permutationCntVec = permut_state;
//
//    permut.printPermutation();
//    bool result = permut.nextPermutation();
//    permut.printPermutation();
//    // TODO MH-DEBUG permut_state = permut.permutationCntVec;
//    mode_1_current_operation_set.clear();
//    mode_1_current_operation_set =(possible_operations[permut_state[0]]);
//    return result;
//}
//
//void selective_add::set_mode_list()
//{
//    operation_mode=1;
//    unsigned int permut_variable_count= possible_operations.size()+shifts.size();
//    permut_min.resize(permut_variable_count);
//    permut_max.resize(permut_variable_count);
//    permut_state.resize(permut_variable_count);
//
//    // specify borders for Operation selecting in List mode
//    if (do_LUT_permutation)
//    {
//        permut_state[0] = 0;
//        permut_min[0] = 0;
//        permut_max[0] = possible_operations.size();
//    }
//    else
//    {
//        permut_min[0] = permut_state[0];
//        permut_max[0] = permut_state[0];
//    }
//    // specify borders for shifts
//    if (do_LUT_permutation) {
//        for (unsigned int i = 1; i < shifts.size() + 1; ++i) {
//            permut_state[i] = shifts[i-1];
////            permut_min[i] = shift_config_min[i - 1]; // FIX!!!! commented to make error silent
//            permut_max[i] = shift_config_max[i - 1];
//        }
//    }
//    else
//    {
//        for (unsigned int i = 1; i < shifts.size() + 1; ++i) {
//            permut_state[i] = shifts[i - 1];
//            permut_min[i] = shifts[i - 1];
//            permut_max[i] = shifts[i - 1];
//        }
//    }
//
//
//}
// TODO: remove or FIX: commented to make error silent
// void selective_add::set_shift_config_max(const std::vector<int> &inputs)
// {
//     shift_config_max = inputs;
// }
// void selective_add::set_shift_config_min(const std::vector<int> &inputs)
// {
//     shift_config_min = inputs;
// }

// void selective_add::reset_config() {}

//void selective_add::set_mode_all() {}
std::set<int> *selective_add::compute()
{
    IF_VERBOSE(9) ENTER_FUNCTION("selective_add::compute()")
    init();
    calc->compute(this);

    return calc->get_output();
}
void selective_add::init(shared_ptr<search_space_plan> _ssp, int _sel_add_pos, rccm_type _current_rccm_type) // update und eventually initialize calc and permutators
{
    IF_VERBOSE(4) ENTER_FUNCTION("selective_add::init()")
    if(_ssp!= nullptr)
    {
        ssp = _ssp;
    }
    if(_sel_add_pos!= -1)
    {
        sel_add_pos = _sel_add_pos;
    }
    if(_current_rccm_type!= rccm_type_NAN)
    {
        current_rccm_type = _current_rccm_type;
    }

    if((ssp == nullptr)||(sel_add_pos==-1)||(current_rccm_type==rccm_type_NAN)) { ERROR("Insufficient Init information!","selective_add::init(shared_ptr<search_space_plan> _ssp, int _sel_add_pos)")}

    if(sel_add_search_space.size()==0){ ERROR("Can Not init without search space!","selective_add::init()")}
    if((calc!=nullptr)&&(sel_add_search_space[from_sp_use] != ((calc_selective_adder_base*)calc)->type()))
    {
        IF_VERBOSE(5) std::cout << "calc pointer: " << calc << std::endl;
        IF_VERBOSE(5) std::cout << "calc type: " << ((calc_selective_adder_base*)calc)->type() << " Search space type: " << sel_add_search_space[from_sp_use] << std::endl;
        delete_calc();
    }
    if(calc==nullptr) // calc does not exist (anymore) and need to be initialized
    {
        IF_VERBOSE(5) std::cout << "new calc type will be set to: " << sel_add_search_space[from_sp_use] << std::endl;
        switch (sel_add_search_space[from_sp_use]) {
            case typ_A:
                calc = static_cast<calc_base *>(new calc_selective_adder_typ_a);
                break;
            case typ_B:
                calc = static_cast<calc_base *>(new calc_selective_adder_typ_b);
                break;
            case typ_C:
                calc = static_cast<calc_base *>(new calc_selective_adder_typ_c);
                break;
            default:
            ERROR("Invalid Type", "selective_add::init()");
        }
        init_permutators();// only init permutators if ther was a change
    }
    IF_VERBOSE(4)LEAVE_FUNCTION("selective_add::init()")
}

void selective_add::delete_calc() // if existing delete calc object
{
    IF_VERBOSE(9)ENTER_FUNCTION("selective_add::delete_calc()")
    if (this->calc != nullptr)
    {
        IF_VERBOSE(9) std::cout << "delete calc" << std::endl;
        delete calc;
        calc=nullptr;
    }
    IF_VERBOSE(9)LEAVE_FUNCTION("selective_add::delete_calc()")
}

std::set<int> selective_add::get_operation_set() //return the current subset of operations during permutation.
{
    if(this->perm_operation.pd->p_typ == usual_operations_only)
    {
        return (static_cast<calc_selective_adder_base *>(this->calc)->get_spec().usualy_used_sets[this->perm_operation.pd->permutationCntVec[0]]);
    }
    // converting the vector elements into a set and returns it.
    std::set<int> my_op_set(std::make_move_iterator(this->perm_operation.pd->permutationCntVec.begin()),
                  std::make_move_iterator(this->perm_operation.pd->permutationCntVec.end()));
    return my_op_set;
}

int selective_add::get_shift(unsigned int input_no)//return the current subset of shifts during permutation.
{
    return this->perm_shift.pd->permutationCntVec[input_no];
}

selective_add::selective_add()
{
    IF_VERBOSE(3) ENTER_FUNCTION("selective_add::selective_add()")
    from_sp_use=0;
    calc = nullptr;
}
selective_add::~selective_add()
{
    delete_calc();
}

std::set<int>* gen_shift(std::set<int>* input_set, int shift)
{
    IF_VERBOSE(7) ENTER_FUNCTION("gen_shift()")
    IF_VERBOSE(9) std::cout << "shift is: "<< shift<< std::endl;
    IF_VERBOSE(9) std::cout << "input_set points to: "<< input_set << std::endl;
    IF_VERBOSE(9) std::cout << "input_set is: "<< *input_set << std::endl;

    std::set<int>* result = new std::set<int>();

    for(int i:(*input_set))
    {
        result->insert(i << shift);
    }
    IF_VERBOSE(9) std::cout << "result_set is: "<< *result << std::endl;
    return result;
};
