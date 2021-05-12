//
// Created by jordan on 2021/5/11.
//
//redefine of the program assignment1's Reg node.

#ifndef TRIAL_PA2_TUPLE_H
#define TRIAL_PA2_TUPLE_H
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "status.h"
using namespace std;

class RDB;

class Tuple {
    friend class RDB;

public:
    Tuple(int ID = -1,string name = "NULL",int Medic_Stat = -1, int Registration = -1,int T_type = -1,status stat = applied);
    Tuple(const Tuple &obj);
    // basic get functions.
    int get_id();
    string get_name();
    int get_medic();
    int get_registration();
    status get_status();
    int get_Treatment();
    //basic set function
    void set_status(status newstat);

private:
    int id;
    int Medic;
    int Treatment;
    int Reg;

    string name;
    status stat;
};


#endif //TRIAL_PA2_TUPLE_H
