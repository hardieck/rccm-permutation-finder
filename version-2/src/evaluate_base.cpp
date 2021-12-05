//
// Created by hardieck on 12/5/21.
//

#include "../inc/evaluate_base.h"

void evaluate_base::print_configure_help()
{
    std::cout << "There is no help for this evaluation type" << std::endl;
    std::cout << "There are no parameter to conigure" << std::endl;
}
int evaluate_base::configure(string parameter)
{
    IF_VERBOSE(1) std::cout << "this evaluation type is not configurable" << std::endl;
    return 1;
}