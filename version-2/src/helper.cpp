//
// Created by hardieck on 11/21/21.
//

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "../inc/helper.h"
#include "../inc/debug.h"

#include  "../inc/datatyps.h"

char int2extendHEX(int input)
{
    IF_VERBOSE(8) ENTER_FUNCTION("int2extendHEX(int input)")
    IF_VERBOSE(9) std::cout << "input is " << input << std::endl;
    switch(input) {
        case  0:return '0';
        case  1:return '1';
        case  2:return '2';
        case  3:return '3';
        case  4:return '4';
        case  5:return '5';
        case  6:return '6';
        case  7:return '7';
        case  8:return '8';
        case  9:return '9';
        case 10:return 'a';
        case 11:return 'b';
        case 12:return 'c';
        case 13:return 'd';
        case 14:return 'e';
        case 15:return 'f';
        case 16:return 'g';
        case 17:return 'h';
        case 18:return 'i';
        case 19:return 'j';
        case 20:return 'k';
        case 21:return 'l';
        case 22:return 'm';
        case 23:return 'n';
        case 24:return 'o';
        case 25:return 'p';
        case 26:return 'q';
        case 27:return 'r';
        case 28:return 's';
        case 29:return 't';
        case 30:return 'u';
        case 31:return 'v';
        case 32:return 'w';
        case 33:return 'x';
        case 34:return 'y';
        case 35:return 'z';
        default:
            ERROR("Expand int is only defined up to 35!","int2extendHEX(int input)")

    }
}
int extendHEX2int(char input)
{
    IF_VERBOSE(8) ENTER_FUNCTION("extendHEX2int(char input)")
    IF_VERBOSE(9) std::cout << "input is " << input << std::endl;
    switch(input) {
        case '0': return  0;
        case '1': return  1;
        case '2': return  2;
        case '3': return  3;
        case '4': return  4;
        case '5': return  5;
        case '6': return  6;
        case '7': return  7;
        case '8': return  8;
        case '9': return  9;
        case 'a': return 10;
        case 'b': return 11;
        case 'c': return 12;
        case 'd': return 13;
        case 'e': return 14;
        case 'f': return 15;
        case 'g': return 16;
        case 'h': return 17;
        case 'i': return 18;
        case 'j': return 19;
        case 'k': return 20;
        case 'l': return 21;
        case 'm': return 22;
        case 'n': return 23;
        case 'o': return 24;
        case 'p': return 25;
        case 'q': return 26;
        case 'r': return 27;
        case 's': return 28;
        case 't': return 29;
        case 'u': return 30;
        case 'v': return 31;
        case 'w': return 32;
        case 'x': return 33;
        case 'y': return 34;
        case 'z': return 35;
        default:
        ERROR("Expand int is only defined up to z or 35!","extendHEX2int(char input)")

    }
}

std::vector<std::string> split_string_by(std::string input,char seperator)
{
    stringstream ss( input);
    vector<string> result;

    while( ss.good() )
    {
        string substr;
        getline( ss, substr, seperator );
        result.push_back( substr );
    }
    return result;
}
bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
rccm_type get_rccm_type_from_string(string input)
{
    if(input.size() != 2) { ERROR("Invalid Syntax!","get_rccm_type_from_string(string input)")}
    else if (input[0] == 'C')
    {
        //v[0].erase(v[0].begin(),++(v[0].begin())); // removing leading C
        input.erase(0,1); // removing leading C
        switch(std::stoi(input))
        {
            case 1: return typ_C1; break;
            case 2: return typ_C2; break;
            case 3: return typ_C3; break;
            case 4: return typ_C4; break;
            default: ERROR("UNSUPPORTED Connection structure type!","get_rccm_type_from_string(string input)")
        }
    }
    else
    ERROR("UNSUPPORTED Connection structure type!","get_rccm_type_from_string(string input)")
}
sel_add_type get_sel_add_type_from_string(string input)
{
    if(input.size() != 1) { ERROR("Invalid Syntax!","get_sel_add_type_from_string(string)")}
    else
    {
        char c = input[0];
        switch(c)
        {
            case 'A': return typ_A; break;
            case 'B': return typ_B; break;
            case 'C': return typ_C; break;
            default: ERROR("UNSUPPORTED Connection structure type!","get_sel_add_type_from_string(string)")
        }
    }
}
std::ostream &operator<<(std::ostream &s, const sspk &rhs)
{
    s << "sspk{"<< rhs.key_level1 << "," << rhs.key_level2 << "," << rhs.key_level3 << "}";
    return s;
}