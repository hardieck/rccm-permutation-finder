//
// Created by hardieck on 4/12/21.
//

#ifndef ADDNET_PERMUTATOR_V2_CALC_BASE_H
#define ADDNET_PERMUTATOR_V2_CALC_BASE_H


class calc_base : public base_obj
{
public:
    void set_input(unsigned int input_no, std::set<int>* in_set)
    {
        if (input_no >= inputs.size())
        {
            string msg = "The inputs number input_no=" + to_string(input_no) + " is greater then the accessible inputs!" + "(Accessible are " + to_string(inputs.size() - 1) + ")";
            ERROR(msg,"calc_base::set_input()");
        }
        inputs[input_no] = in_set;

    };// connects the inputs "ports" to a source(mostly outputs of selective_add)
    virtual std::set<int>* compute(base_obj *parent)=0;// calculate the output depending on the config stored in parent
    std::set<int>* get_output(); // do what it says :-)

protected:
    std::vector<std::set<int>* > inputs; //links to the source list. (shifts are handeld seperatly)
    std::set<int> output;
};


#endif //ADDNET_PERMUTATOR_V2_CALC_BASE_H
