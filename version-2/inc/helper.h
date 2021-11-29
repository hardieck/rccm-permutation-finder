//
// Created by hardieck on 11/21/21.
//

#ifndef ADDNET_PERMUTATOR_V2_HELPER_H
#define ADDNET_PERMUTATOR_V2_HELPER_H
#include <vector>
#include <string>
#include "datatyps.h"


char int2extendHEX(int input);
int extendHEX2int(char input);
std::vector<std::string> split_string_by(std::string input,char seperator);
bool isNumber(const std::string& str);
rccm_type get_rccm_type_from_string(string input);
sel_add_type get_sel_add_type_from_string(string input);
std::ostream &operator<<(std::ostream &s, const sspk &rhs);


#endif //ADDNET_PERMUTATOR_V2_HELPER_H
