//
// Created by hardieck on 9/27/19.
//

#include "../inc/selective_adder_typ_a.h"

selective_adder_typ_a::selective_adder_typ_a()
{
    no_of_inputs_for_A=2;
    no_of_inputs_for_B=2;
    inputs.resize(no_of_inputs_for_A+no_of_inputs_for_B);
    shifts.resize(no_of_inputs_for_A+no_of_inputs_for_B);

    this->convfg->add_possible_set(std::set<int> {1, 2, 3, 4});
    this->convfg->add_possible_set(std::set<int> {0, 2, 8, 11});
}
std::set<int> selective_adder_typ_a::compute()
{
    IF_VERBOSE(8) std::cout << "Enter function: selective_adder_typ_a/compute" << std::endl;

    //if (this->get_no_of_inputs() < 4){std::cout << "ERROR: not enough inputs are specified (" << this->get_no_of_inputs() << " inputs are specified)"  << std::endl;}
    if (this->get_no_of_inputs() <= 0) {std::cout << "ERROR: no input specified" << std::endl; exit(-1);}

        //00  A1 +B1
        //01  A1 +B2
        //02  A1 -B1
        //03  A1 -B2
        //04 -A1 +B1
        //05 -A1 +B2
        //06 -A1 -B1
        //07 -A1 -B2
        //08  A2 +B1
        //09  A2 +B2
        //10  A2 -B1
        //11  A2 -B2
        //12 -A2 +B1
        //13 -A2 +B2
        //14 -A2 -B1
        //15 -A2 -B2

    IF_VERBOSE(8) std::cout << "load inputs into local names:" << std::endl;

    std::set<int> &A1 = inputs[0];
    std::set<int> &A2 = inputs[1];
    std::set<int> &B1 = inputs[2];
    std::set<int> &B2 = inputs[3];

    this->output.clear();

    IF_VERBOSE(8) std::cout << "calculate specified configs" << std::endl;
    for (int conf: this->convfg->get_operation_set()) {
        IF_VERBOSE(9) std::cout << "calculate config" << conf << std::endl;
        switch (conf) {
            case 0: for (int a:A1) { for (int b:B1) { output.insert(a + b); }} break;
            case 1:
                for (int a:A1) { for (int b:B2) { output.insert(a + b); }}
                break;
            case 2:
                for (int a:A1) { for (int b:B1) { output.insert(a - b); }}
                break;
            case 3:
                for (int a:A1) { for (int b:B2) { output.insert(a - b); }}
                break;
            case 4:
                for (int a:A1) { for (int b:B1) { output.insert(-a + b); }}
                break;
            case 5:
                for (int a:A1) { for (int b:B2) { output.insert(-a + b); }}
                break;
            case 6:
                for (int a:A1) { for (int b:B1) { output.insert(-a - b); }}
                break;
            case 7:
                for (int a:A1) { for (int b:B2) { output.insert(-a - b); }}
                break;
            case 8:
                for (int a:A2) { for (int b:B1) { output.insert(a + b); }}
                break;
            case 9:
                for (int a:A2) { for (int b:B2) { output.insert(a + b); }}
                break;
            case 10:
                for (int a:A2) { for (int b:B1) { output.insert(a - b); }}
                break;
            case 11:
                for (int a:A2) { for (int b:B2) { output.insert(a - b); }}
                break;
            case 12:
                for (int a:A2) { for (int b:B1) { output.insert(-a + b); }}
                break;
            case 13:
                for (int a:A2) { for (int b:B2) { output.insert(-a + b); }}
                break;
            case 14:
                for (int a:A2) { for (int b:B1) { output.insert(-a - b); }}
                break;
            case 15:
                for (int a:A2) { for (int b:B2) { output.insert(-a - b); }}
                break;

        }
    }
    IF_VERBOSE(7) std::cout << "calculation result is:" << output << std::endl;

    return output;
}


