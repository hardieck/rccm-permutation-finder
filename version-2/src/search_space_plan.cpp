//
// Created by hardieck on 11/24/21.
//

#include "../inc/search_space_plan.h"
#include "../inc/helper.h"
#include <iostream>

#include "../inc/evaluate_count.h"
#include "../inc/evaluate_Kolmogorov_Smirnov.h"
#include "../inc/evaluate_Kullback_Leibler.h"
#include "../inc/evaluate_zero.h"

search_space_plan::search_space_plan()
{
    this->search_space_rccm.clear();
    this->search_space_sel_add.clear();
    this->sel_add_max_shift.clear();
    this->sel_add_operating_mode.clear();
    this->sel_add_config_level.clear();


}
search_space_plan::~search_space_plan()
{
}

vector<rccm_type> search_space_plan::get_search_space_rccm()
{
    return search_space_rccm;
}
vector<sel_add_type> search_space_plan::get_search_space_sel_add(const sspk &position_key) //return vec of sel_Add_types
{
    unsigned int x=0;
    bool found_no_match=true;
    for(int i=0; i< search_space_sel_add.size();++i)
    {
        if(search_space_sel_add[i].first == position_key) {x = i;found_no_match = false;}
    }
    if(found_no_match){
        std::cout << "current key is: " << position_key << std::endl;
        ERROR("No rule for current Key","vector<sel_add_type> search_space_plan::get_search_space_sel_add(const sspk &position_key)")}
    return search_space_sel_add[x].second;
}
int search_space_plan::get_sel_add_max_shift(const sspk &position_key) // return max shift
{
    unsigned int x = 0;
    bool found_no_match=true;
    for (int i = 0; i < sel_add_max_shift.size(); ++i) {
        if (sel_add_max_shift[i].first == position_key) { x = i;found_no_match = false;}
    }
    if(found_no_match){
        std::cout << "current key is: " << position_key << std::endl;
        ERROR("No rule for current Key","search_space_plan::get_sel_add_max_shift(const sspk &position_key)")
    }
    return sel_add_max_shift[x].second;
}
permutator_typ search_space_plan::get_sel_add_operating_mode(const sspk &position_key) // return mode
{
    unsigned int x = 0;
    bool found_no_match=true;
    for (int i = 0; i < sel_add_operating_mode.size(); ++i) {
        if (sel_add_operating_mode[i].first == position_key) { x = i; found_no_match = false;}
    }
    if(found_no_match){
        std::cout << "current key is: " << position_key << std::endl;
        ERROR("No rule for current Key","search_space_plan::get_sel_add_operating_mode(const sspk &position_key)")}
    return sel_add_operating_mode[x].second;
}
config_level search_space_plan::get_sel_add_config_level(const sspk &position_key)
{
    unsigned int x = 0;
    bool found_no_match=true;
    for (int i = 0; i < sel_add_config_level.size(); ++i) {
        if (sel_add_config_level[i].first == position_key) { x = i;found_no_match = false;}
    }
    if(found_no_match){
        std::cout << "current key is: " << position_key << std::endl;
        ERROR("No rule for current Key","search_space_plan::get_sel_add_config_level(const sspk &position_key)")}
    return sel_add_config_level[x].second;
}

void search_space_plan::init_empty_slots()
{
    //TODO implment init_empty_slots for  sel_add_operating_mode
    if(search_space_rccm.size() ==0){add_rule("set_rccm C1");}
    if(search_space_sel_add.size() ==0){add_rule("set_sel_add A,B");}
    if(sel_add_max_shift.size() ==0){add_rule("set_max_shift 2");}
    if(sel_add_operating_mode.size() ==0){add_rule("set_operation_mode usal");}
    if(sel_add_config_level.size() ==0)
    {
        pair<sspk,config_level> elem;
        elem.first = this->generate_key_from_sting("~~~");
        elem.second = all;
        sel_add_config_level.push_back(elem);
    }
}


void search_space_plan::add_rule(std::string rule)
{
    IF_VERBOSE(5)ENTER_FUNCTION("search_space_plan::add_rule(std::string rule)")
    // set_sel_add A,B,C for C3,2,~
    // set_sel_add B for C3,2,~
    // set_max_shift A,B,C for C1,~,~
    // set_config_level all for ~,~,
    // set_rccm C1 (for ~,~,~ )
    // set_operation_mode all (for ~,~,~ )
    // set_op_mode usal (for ~,~,~ )

    // if for X,y,z is missing equal to ~,~,~


    {// remove the -- indicator
        bool replaced = false;
        string s1("--");
        string s2("");
        replaced=replace(rule, s1, s2);
        IF_VERBOSE(2) std::cout << "Add_Search_Space_rule: " << rule << std::endl;
    }

    std::vector<std::string> v;
    v= split_string_by(rule,' ');


    if (v[0] == "set_metric")
    {
        if(v[1] == "count_size")
        {
            shared_ptr<evaluate_count> my_eval = make_shared<evaluate_count>();
            my_eval->count_size = true;
            my_eval->count_sets = false;

            my_eval->use_metric = false;
            my_eval->metric = make_shared<evaluate_Kullback_Leibler>();
            this->evaluation.push_back(my_eval);
        }
        else if(v[1] == "count_sets")
        {
            shared_ptr<evaluate_count> my_eval = make_shared<evaluate_count>();
            my_eval->count_size = false;
            my_eval->count_sets = true;

            my_eval->use_metric = false;
            my_eval->metric = make_shared<evaluate_Kullback_Leibler>();

            this->evaluation.push_back(my_eval);
        }
        else if(v[1] == "with-zero")
        {
            shared_ptr<evaluate_zero> my_eval = make_shared<evaluate_zero>();
            this->evaluation.push_back(my_eval);
        }
        else if(v[1] == "k-l")
        {
            shared_ptr<evaluate_Kullback_Leibler> my_eval = make_shared<evaluate_Kullback_Leibler>();
            this->evaluation.push_back(my_eval);
        }
        else if(v[1] == "k-s")
        {
            ERROR("evaluate_Kolmogorov_Smirnov is not ready for use yet!","void search_space_plan::add_rule(std::string rule)")
            shared_ptr<evaluate_Kolmogorov_Smirnov> my_eval = make_shared<evaluate_Kolmogorov_Smirnov>();
            this->evaluation.push_back(my_eval);
        }
        else
        {
            ERROR("No such Metric!","void search_space_plan::add_rule(std::string rule)")
        }
    }
    else
    {

        if ((v.size() != 2) && (v.size() != 4)) {
            ERROR("INVALID Rule! Rule was:" << rule << " Syntax Example: ' set_sel_add A,B,C for C3,2,~ ' ",
                  "search_space_plan::generate_key_from_sting(std::string key_string)")
        }

        switch (v.size()) {
            case 2:
                if (v[0] == "set_rccm") {
                    IF_VERBOSE(6) std::cout << "Found rule: set_rccm" << std::endl;
                    std::vector<string> rccm_strings;
                    rccm_strings = split_string_by(v[1], ',');
                    for (int i = 0; i < rccm_strings.size(); ++i) {
                        search_space_rccm.push_back(get_rccm_type_from_string(rccm_strings[i]));
                    }
                } else {
                    add_rule(rule + " for ~,~,~");
                }
                break;
            case 4: {
                if (v[2] != "for") {
                    ERROR("Unsupported Command! :" << rule << " (Example: set_sel_add A,B,C for C3,2,~)",
                          "search_space_plan::add_rule(std::string rule)")
                }
                //get key
                sspk key = generate_key_from_sting(v[3]);

                if (v[0] == "set_sel_add") {
                    IF_VERBOSE(6) std::cout << "Found rule: set_sel_add" << std::endl;
                    // declaration of used variables:
                    vector<string> sel_add_strings;
                    pair<sspk, vector<sel_add_type>> elem;
                    // init vector and set key
                    sel_add_strings = split_string_by(v[1], ',');
                    elem.first = key;
                    // transform string to real obj and fill elem
                    for (int i = 0; i < sel_add_strings.size(); ++i) {
                        elem.second.push_back(get_sel_add_type_from_string(sel_add_strings[i]));
                    }
                    search_space_sel_add.push_back(elem);
                } else if (v[0] == "set_max_shift") {
                    IF_VERBOSE(6) std::cout << "Found rule: set_max_shift" << std::endl;
                    // declaration of used variables:
                    pair<sspk, int> elem;
                    // set int and set key
                    if (isNumber(v[1])) {

                        elem.first = key;
                        elem.second = std::stoi(v[1]);
                        if (elem.second < 2) {
                            ERROR("Minimum Shift value is 2!", "search_space_plan::add_rule(std::string rule)")
                        }
                        sel_add_max_shift.push_back(elem);
                    } else {
                        ERROR("Max Shift has to be a number!", "search_space_plan::add_rule(std::string rule)")
                    }
                } else if (v[0] == "set_operation_mode") {
                    IF_VERBOSE(6) std::cout << "Found rule: set_operation_mode" << std::endl;
                    if (v[1] == "all") {
                        pair<sspk, permutator_typ> elem;
                        elem.first = key;
                        elem.second = operations_only;
                        sel_add_operating_mode.push_back(elem);
                    } else if (v[1] == "usal") {
                        pair<sspk, permutator_typ> elem;
                        elem.first = key;
                        elem.second = usual_operations_only;
                        sel_add_operating_mode.push_back(elem);
                    } else {
                        ERROR("Unknown Parameter for set_operation_mode",
                              "search_space_plan::add_rule(std::string rule)")
                    }
                } else if (v[0] == "set_config_level") {
                    ERROR("UNSUPPORTED OPTION YET (set_config_level)", "search_space_plan::add_rule(std::string rule)")
                }
                else {
                    ERROR("Unsupported Set Command!: " << rule << " (Example: set_sel_add A,B,C for C3,2,~)",
                          "search_space_plan::add_rule(std::string rule)")
                }
            }
                break;
            default:
            ERROR("Invalid Syntax for Rule! (Example:'set_sel_add A,B,C for C3,2,~' or ' set_rccm C1' )",
                  "search_space_plan::add_rule(std::string rule)")
        }
    }

    IF_VERBOSE(5)LEAVE_FUNCTION("search_space_plan::add_rule(std::string rule)")
}

void search_space_plan::chain(unsigned int metricNr)
{
    if(metricNr >= evaluation.size()-1) // chaining with itself results in loop
    {
        string text = "Invalid Metric No.:" + to_string(metricNr);
        ERROR(text,"void search_space_plan::chain(unsigned int metricNr)")
    }
    IF_VERBOSE(0) std::cout << "Chain Metric " << evaluation.size()-1 << " to Metric " << metricNr << std::endl;
    this->evaluation.back()->metric = this->evaluation[metricNr];
    this->evaluation.back()->use_metric = true;
}

int search_space_plan::configure(std::string parameter)
{
    IF_VERBOSE(8) ENTER_FUNCTION("int search_space_plan::configure(std::string parameter)")
    if(this->evaluation.size() == 0)
    {
        ERROR("No evaluation metrik Spezified! Use --set_metric xyz before!","int search_space_plan::configure(std::string parameter)")
        return -1;
    }
    return (this->evaluation.back())->configure(parameter);
}
sspk search_space_plan::generate_key_from_sting(std::string key_string)
{
    IF_VERBOSE(6)ENTER_FUNCTION("sspk search_space_plan::generate_key_from_sting(std::string key_string)")
    sspk key;
    key.key_level1 = rccm_type_downtCare;
    key.key_level2 = -1; // sel add number in connection rccm to downtCare
    key.key_level3 = sel_add_type_downtCare;

    std::vector<std::string> v;
    v = split_string_by(key_string,',');

    if (v.size()==1)
    {
        if((v[0] == "~")||(v[0] == "~~")||(v[0] == "~~~"))
        {
            IF_VERBOSE(5) std::cout << "use generic don't care key: ~,~,~" << std::endl;
            //set don't care for all (was already set...)
            IF_VERBOSE(6)LEAVE_FUNCTION("sspk search_space_plan::generate_key_from_sting(std::string key_string)")
            return key;
        }
        else
        {
            ERROR("Invalid key description! Example: ~ or ~,~,~ or C1,0,B","search_space_plan::generate_key_from_sting(std::string key_string)")
        }
    }
    // for key level 1
    if(v[0] != "~") // don't care is already set...
    {
        key.key_level1 = get_rccm_type_from_string(v[0]);
    }
    if(v[1] != "~") // don't care is already set...
    {
        if (isNumber(v[1]))
        {
            key.key_level2 = std::stoi(v[1]);
        }
        else
        {
            ERROR("Not a number!","search_space_plan::generate_key_from_sting(std::string key_string)")
        }

    }
    if(v[2] != "~") // don't care is already set...
    {
        IF_VERBOSE(6) std::cout << "print v[2].size=" << v[2].size() << std::endl;
        if (v[2].size() == 1)
        {
            IF_VERBOSE(7) std::cout << "v[3][0]=" << v[2][0] << std::endl;
            char c = v[2][0];
            IF_VERBOSE(7 )std::cout << "c='" << c << "'" << std::endl;

            switch (c) {
                case 'A':
                    key.key_level3 = typ_A;
                    break;
                case 'B':
                    key.key_level3 = typ_B;
                    break;
                case 'C':
                    key.key_level3 = typ_C;
                    break;
                default:
                ERROR("UNSUPPORTED Selective Adder Type! (USE: A or B or ...)",
                      "search_space_plan::generate_key_from_sting(std::string key_string)")
            }
        } else {
            ERROR("Only One Letter for one Selective Adder Type! (USE: A or B or ...)",
                  "search_space_plan::generate_key_from_sting(std::string key_string)")
        }
    }
    IF_VERBOSE(6)LEAVE_FUNCTION("sspk search_space_plan::generate_key_from_sting(std::string key_string)")
    return key;
}

void search_space_plan::print()
{
    IF_VERBOSE(3)ENTER_FUNCTION("search_space_plan::print()")
    init_empty_slots();
    std::cout << "Search Space Plan consists of:" << std::endl;

    std::cout << "search_space_rccm:" << std::endl;
    for(int i=0; i<search_space_rccm.size();++i)
    {
        std::cout << "  " << search_space_rccm[i] << std::endl;
    }
    std::cout << "search_space_sel_add:" << std::endl;
    for(int i=0; i<search_space_sel_add.size();++i)
    {
        std::cout << "  " << search_space_sel_add[i].first << " " << search_space_sel_add[i].second << std::endl;
    }
    std::cout << "sel_add_max_shift:" << std::endl;
    for(int i=0; i<sel_add_max_shift.size();++i)
    {
        std::cout << "  " << sel_add_max_shift[i].first << " " << sel_add_max_shift[i].second << std::endl;
    }
    std::cout << "sel_add_config_level:" << std::endl;
    for(int i=0; i<sel_add_config_level.size();++i)
    {
        std::cout << "  " << sel_add_config_level[i].first << " " << sel_add_config_level[i].second << std::endl;
    }


    IF_VERBOSE(3)LEAVE_FUNCTION("search_space_plan::print()")
}

void search_space_plan::evaluate_all(const string &config,const std::set<int> &inputs)
{
    IF_VERBOSE(5) ENTER_FUNCTION("void search_space_plan::evaluate_all(const string &config,const std::set<int> &inputs)")
    if (this->evaluation.size() == 0)
    {
        ERROR("Use at least one Evaluation metric!","void search_space_plan::evaluate_all(const string &config,const std::set<int> &inputs)")
    }
    for (int i = 0; i<this->evaluation.size(); ++i)
    {
        this->evaluation[i]->evaluate(config,inputs);
    }
}
void search_space_plan::print_result_all()
{
    IF_VERBOSE(5) ENTER_FUNCTION("void search_space_plan::print_result_all()")
    if (this->evaluation.size() == 0)
    {
        ERROR("Use at least one Evaluation metric!","void search_space_plan::print_result_all()")
    }
    for (int i = 0; i<this->evaluation.size(); ++i)
    {
        std::cout << std::endl << "Results from metric " << i << ":" << std::endl;
        this->evaluation[i]->print_result();
    }
}

