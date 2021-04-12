//
// Created by hardieck on 4/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_BASE_H
#define ADDNET_PERMUTATOR_V2_CALC_BASE_H


class calc_base : public base_obj
{
    int set_input(unsigned int input_no, std::set<int>*);// connects the input "ports" to a source(mostly outputs of selective_add)
    virtual std::set<int>* compute(base_obj &parent)=0;// calculate the output depending on the config stored in parent
    std::set<int>* get_output(); // do what it says :-)

protected:
    std::vector<std::set<int>* > input; //links to the source list. (shifts are handeld seperatly)
    std::set<int> output;
};


#endif //ADDNET_PERMUTATOR_V2_CALC_BASE_H
