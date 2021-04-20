#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "structure.h"
#include <iostream>

class structure_001 : public structure_base
{
public:
    structure_001()
    {
        shifts.resize(12);
        config.resize(3);

        //                        A A A B A A A B A A A B|b b b
        permutation_max_values = {2,3,4,4,2,3,4,4,2,4,4,4,3,3,3};
    }

    std::list<int> compute()
    {
        int shift_AA1 = shifts[0];
        int shift_AA2 = shifts[1];
        int shift_AA3 = shifts[2];

        int shift_AB1 = shifts[3];

        int shift_BA1 = shifts[4];
        int shift_BA2 = shifts[5];
        int shift_BA3 = shifts[6];

        int shift_BB1 = shifts[7];

        int shift_CA1 = shifts[8];
        int shift_CA2 = shifts[9];
        int shift_CA3 = shifts[10];

        int shift_CB1 = shifts[11];

        std::vector<int> b1_conf;
        std::vector<int> b2_conf;
        std::vector<int> b3_conf;

        switch(config[0])
        {
            case 0: b1_conf = {0,1,2,3};  break;
            case 1: b1_conf = {0,1,2,4};  break;
            case 2: b1_conf = {0,1,2,5};  break;
            case 3: b1_conf = {0,1,2,6};  break;
        }
        switch(config[1])
        {
            case 0: b2_conf = {0,1,2,3};  break;
            case 1: b2_conf = {0,1,2,4};  break;
            case 2: b2_conf = {0,1,2,5};  break;
            case 3: b2_conf = {0,1,2,6};  break;
        }
        switch(config[2])
        {
            case 0: b3_conf = {0,1,2,3};  break;
            case 1: b3_conf = {0,1,2,4};  break;
            case 2: b3_conf = {0,1,2,5};  break;
            case 3: b3_conf = {0,1,2,6};  break;
        }

        std::list<int> input = {1};

        std::list<int> A;
        std::list<int> B;
        std::list<int> C;

        A = operation_TYPE_b(shift(input,shift_AA1),shift(input,shift_AA2),shift(input,shift_AA3),shift(input,shift_AB1),b1_conf);
        B = operation_TYPE_b_minus(shift(input,shift_BA1),shift(input,shift_BA2),shift(input,shift_BA3),shift(input,shift_BB1),b2_conf);
        C = operation_TYPE_b(shift(A,shift_CA1),shift(A,shift_CA2),shift(A,shift_CA3),shift(B,shift_CB1),b3_conf);
        if (C.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }
        return C;
    }

    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  {return false;}
        if (!is_a_valid_shift_vector(input,0,2))  {return false;}
        if (!is_a_valid_shift_vector(input,4,6))  {return false;}
        if (!is_a_valid_shift_vector(input,8,10)) {return false;}

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

};

class structure_1BB2B3E: public structure_base
{
public:
    structure_1BB2B3E()
    {
        shifts.resize(15);
        config.resize(4);

        //                        0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
        //                        A A A B|A A A B|A A  A  B| A  A  B| b  b  b  e
        permutation_max_values = {1,2,3,3,1,2,3,3,1,2, 3, 3, 2, 3, 3, 3, 3, 3, 0};
    }
    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  return false;
        if (!is_a_valid_shift_vector(input,0,2))  return false;
        if (!is_a_valid_shift_vector(input,4,6))  return false;
        if (!is_a_valid_shift_vector(input,8,10)) return false;
        if (!is_a_valid_shift_vector(input,12,13))return false;

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

    std::list<int> compute()
    {
        std::vector<int> conf_B1;
        std::vector<int> conf_B2;
        std::vector<int> conf_B3;
        std::vector<int> conf_E;
        switch(config[0])
        {
            case 0: conf_B1 = {0,1,2,3};  break;
            case 1: conf_B1 = {0,1,2,4};  break;
            case 2: conf_B1 = {0,1,2,5};  break;
            case 3: conf_B1 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[1])
        {
            case 0: conf_B2 = {0,1,2,3};  break;
            case 1: conf_B2 = {0,1,2,4};  break;
            case 2: conf_B2 = {0,1,2,5};  break;
            case 3: conf_B2 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[2])
        {
            case 0: conf_B3 = {0,1,2,3};  break;
            case 1: conf_B3 = {0,1,2,4};  break;
            case 2: conf_B3 = {0,1,2,5};  break;
            case 3: conf_B3 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[3])
        {
            case  0: conf_E = {2,3,4,5};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }


        std::list<int> input = {1};
        std::list<int> E_edge = input;


        std::list<int> A = operation_TYPE_b(shift(input,shifts[0]), shift(input,shifts[1]), shift(input,shifts[2]), shift(input,shifts[3]), conf_B1);
        std::list<int> B = operation_TYPE_b(shift(input,shifts[4]), shift(input,shifts[5]), shift(input,shifts[6]), shift(input,shifts[7]), conf_B2);
        std::list<int> C = operation_TYPE_b(shift(A,shifts[8]),shift(A,shifts[9]),shift(A,shifts[10]),shift(B,shifts[11]),conf_B3);
        //E_edge = B;
        std::list<int> D = operation_TYPE_e(shift(C,shifts[12]),shift(C,shifts[13]),shift(E_edge,shifts[14]),conf_E);;

        if (D.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }

        return D;
    }
};

class structure_1B : public structure_base
{
public:
    structure_1B()
    {
        shifts.resize(4);
        config.resize(1);
        //                        0 1 2 3 33
        //                        A A A B|b
        //permutation_max_values = {1,2,3,3,32};
        permutation_max_values = {2,3,4,4,32};
    }
    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  return false;
        if (!is_a_valid_shift_vector(input,0,2))  return false;

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

    std::list<int> compute()
    {
        std::vector<int> conf_B;
        switch(config[0])
        {
            case 0: conf_B = {0,1,2,3};  break;
            case 1: conf_B = {0,1,2,4};  break;
            case 2: conf_B = {0,1,2,5};  break;
            case 3: conf_B = {0,1,2,6};  break;
                //----------------------------------------------------------MH ab hier zusätzliche nicht übliche fälle
                //----------------------------------------------------------
            case 4: conf_B = {0,1,3,4};  break;
            case 5: conf_B = {0,1,3,5};  break;
            case 6: conf_B = {0,1,3,6};  break;
                //----------------------------------------------------------
            case 7: conf_B = {0,1,4,5};  break;
            case 8: conf_B = {0,1,4,6};  break;
                //----------------------------------------------------------
            case 9: conf_B = {0,1,5,6};  break;
                //----------------------------------------------------------
            case 10: conf_B = {0,2,3,4};  break;
            case 11: conf_B = {0,2,3,5};  break;
            case 12: conf_B = {0,2,3,6};  break;
            case 13: conf_B = {0,2,4,5};  break;
            case 14: conf_B = {0,2,4,6};  break;
            case 15: conf_B = {0,2,5,6};  break;
                //----------------------------------------------------------
            case 16: conf_B = {0,3,4,5};  break;
            case 17: conf_B = {0,3,4,6};  break;
            case 18: conf_B = {0,3,5,6};  break;
                //----------------------------------------------------------
            case 19: conf_B = {0,4,5,6};  break;
                //----------------------------------------------------------
            case 20: conf_B = {1,2,3,4};  break;
            case 21: conf_B = {1,2,3,5};  break;
            case 22: conf_B = {1,2,3,6};  break;
            case 23: conf_B = {1,2,4,5};  break;
            case 24: conf_B = {1,2,4,6};  break;
            case 25: conf_B = {1,2,5,6};  break;
            case 26: conf_B = {1,3,4,5};  break;
            case 27: conf_B = {1,3,5,6};  break;
            case 28: conf_B = {1,4,5,6};  break;
                //----------------------------------------------------------
            case 29: conf_B = {2,3,4,5};  break;
            case 30: conf_B = {2,3,4,6};  break;
            case 31: conf_B = {2,3,5,6};  break;
            case 32: conf_B = {2,4,5,6};  break;
                //----------------------------------------------------------
            case 33: conf_B = {3,4,5,6};  break;
                //----------------------------------------------------------
            default: std::cout << std::endl << "ERROR!:inCompute Coes a invalid option"; exit(-1);
        }


        std::list<int> input = {1};

        int shift_AA1 = shifts[0];
        int shift_AA2 = shifts[1];
        int shift_AA3 = shifts[2];

        int shift_AB1 = shifts[3];

        std::list<int> C = operation_TYPE_b(shift(input,shift_AA1),shift(input,shift_AA2),shift(input,shift_AA3),shift(input,shift_AB1),conf_B);
        if (C.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }
        return C;
    }

};
class structure_1E : public structure_base
{
public:
    structure_1E()
    {
        shifts.resize(3);
        config.resize(1);
        //                        A A B|e
        //permutation_max_values = {2,3,3,13};
        permutation_max_values = {3,4,4,13};
    }
    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  return false;
        if (!is_a_valid_shift_vector(input,0,1))  return false;

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

    std::list<int> compute()
    {
        std::vector<int> conf;
        switch(config[0])
        {
            case  0: conf = {2,3,4,5};  break;
            //----------------------------------------------
            case  1: conf = {0, 1,2, 3};  break;
            case  2: conf = {0, 1,4, 5};  break;
            case  3: conf = {0, 1,6, 7};  break;
            case  4: conf = {0, 1,8, 11};  break;
            case  5: conf = {0, 1,9, 10};  break;
            //case  0: conf = {2, 3,4, 5};  break;
            case  6: conf = {2, 3,6, 7};  break;
            case  7: conf = {2, 3,8, 11};  break;
            case  8: conf = {2, 3,9, 10};  break;
            case  9: conf = {4, 5,6, 7};  break;
            case  10: conf = {4, 5,8, 11};  break;
            case  11: conf = {4, 5,9, 10};  break;
            case  12: conf = {6, 7,8, 11};  break;
            case  13: conf = {6, 7,9, 10};  break;
            case  14: conf = {8, 11,9, 10};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }


        std::list<int> input = {1};

        std::list<int> C = operation_TYPE_e(shift(input,shifts[0]),shift(input,shifts[1]),shift(input,shifts[2]),conf);
        if (C.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }
        return C;
    }
};
class structure_1B2E : public structure_base
{
public:
    structure_1B2E()
    {
        shifts.resize(7);
        config.resize(2);
        //                        0 1 2 3 4 5 6 7 8
        //                        A A A B A A B|b e
        permutation_max_values = {1,2,3,3,2,3,3,3,0};
    }

    std::list<int> compute()
    {
        std::vector<int> conf_B;
        std::vector<int> conf_E;
        switch(config[0])
        {
            case 0: conf_B = {0,1,2,3};  break;
            case 1: conf_B = {0,1,2,4};  break;
            case 2: conf_B = {0,1,2,5};  break;
            case 3: conf_B = {0,1,2,6};  break;

            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[1])
        {
            case  0: conf_E = {2,3,4,5};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }


        std::list<int> input = {1};

        std::list<int> A = operation_TYPE_b(shift(input,shifts[0]),shift(input,shifts[1]),shift(input,shifts[2]),shift(input,shifts[3]),conf_B);
        std::list<int> B = operation_TYPE_e(shift(A,shifts[4]),shift(A,shifts[5]),shift(input,shifts[6]),conf_E);
        if (B.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }
        return B;
    }

    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  return false;
        if (!is_a_valid_shift_vector(input,0,2))  return false;
        if (!is_a_valid_shift_vector(input,4,5))  return false;

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

};
class structure_1BB2E : public structure_base
{
public:
    structure_1BB2E()
    {
        shifts.resize(11);
        config.resize(3);
        //                        0 1 2 3 4 5 6 7 8 910111213
        //                        A A A B A A A B A A B|b b e
        permutation_max_values = {1,2,3,3,1,2,3,3,2,3,3,3,3,0};
    }
    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  return false;
        if (!is_a_valid_shift_vector(input,0,2))  return false;
        if (!is_a_valid_shift_vector(input,4,6))  return false;
        if (!is_a_valid_shift_vector(input,8,9))  return false;

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

    std::list<int> compute()
    {
        std::vector<int> conf_B1;
        std::vector<int> conf_B2;
        std::vector<int> conf_E;
        switch(config[0])
        {
            case 0: conf_B1 = {0,1,2,3};  break;
            case 1: conf_B1 = {0,1,2,4};  break;
            case 2: conf_B1 = {0,1,2,5};  break;
            case 3: conf_B1 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[1])
        {
            case 0: conf_B2 = {0,1,2,3};  break;
            case 1: conf_B2 = {0,1,2,4};  break;
            case 2: conf_B2 = {0,1,2,5};  break;
            case 3: conf_B2 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[2])
        {
            case  0: conf_E = {2,3,4,5};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }


        std::list<int> input = {1};

        std::list<int> A = operation_TYPE_b(shift(input,shifts[0]),shift(input,shifts[1]),shift(input,shifts[2]),shift(input,shifts[3]),conf_B1);
        std::list<int> B = operation_TYPE_b(shift(input,shifts[4]),shift(input,shifts[5]),shift(input,shifts[6]),shift(input,shifts[7]),conf_B2);
        std::list<int> C = operation_TYPE_e(shift(A,shifts[8]),shift(A,shifts[9]),shift(B,shifts[10]),conf_E);;
        if (C.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }

        return C;
    }
};
class structure_1B2B3E : public structure_base
{
public:
    structure_1B2B3E()
    {
        shifts.resize(11);
        config.resize(3);
        //                        0 1 2 3 4 5 6 7 8 910111213
        //                        A A A B A A A B A A B|b b e
        permutation_max_values = {3,2,3,3,3,2,3,3,3,2,3,3,3,0};
    }
    bool set_shifts(std::vector<int> input)
    {
        if (input.size() != this->shifts.size())  return false;
        if (!is_a_valid_shift_vector(input,0,2))  return false;
        if (!is_a_valid_shift_vector(input,4,6))  return false;
        if (!is_a_valid_shift_vector(input,8,9))  return false;

        this->shifts.clear();
        this->shifts = input;
        return true;
    }

    std::list<int> compute()
    {
        std::vector<int> conf_B1;
        std::vector<int> conf_B2;
        std::vector<int> conf_E;
        switch(config[0])
        {
            case 0: conf_B1 = {0,1,2,3};  break;
            case 1: conf_B1 = {0,1,2,4};  break;
            case 2: conf_B1 = {0,1,2,5};  break;
            case 3: conf_B1 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[1])
        {
            case 0: conf_B2 = {0,1,2,3};  break;
            case 1: conf_B2 = {0,1,2,4};  break;
            case 2: conf_B2 = {0,1,2,5};  break;
            case 3: conf_B2 = {0,1,2,6};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }
        switch(config[2])
        {
            case  0: conf_E = {2,3,4,5};  break;
            default: std::cout << std::endl << "ERROR!:inCompute select a invalid option"; exit(-1);
        }


        std::list<int> input = {1};

        std::list<int> A = operation_TYPE_b(shift(input,shifts[0]),shift(input,shifts[1]),shift(input,shifts[2]),shift(input,shifts[3]),conf_B1);
        std::list<int> B = operation_TYPE_b(shift(A,shifts[4]),shift(A,shifts[5]),shift(A,shifts[6]),shift(input,shifts[7]),conf_B2);
        std::list<int> C = operation_TYPE_e(shift(B,shifts[8]),shift(B,shifts[9]),shift(input,shifts[10]),conf_E);
        if (C.size() == 0)
        {
            std::cout << std::endl << "ERROR!:inCompute. No Coeficent is realised";
            exit(-1);
        }
        return C;
    }

};

#endif // STRUCTURES_H
