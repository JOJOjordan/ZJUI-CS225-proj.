//
// Created by jordan on 2021/5/11.
//
//redefine of the program assignment1's Reg node.

#ifndef TRIAL_PA2_TUPLE_H
#define TRIAL_PA2_TUPLE_H
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "status.h"
using namespace std;

class RDB;

class Tuple {
    friend class RDB;

public:
    explicit Tuple(int ID = -1,string name = string("NULL"),int Medic_Stat = -1, int Registration = -1,int T_type = -1,status stat = applied);
    Tuple(const Tuple &obj);
    // basic get functions.
    int get_id() const ;
    string get_name() const;
    int get_medic() const;
    int get_registration() const;
    status get_status() const;
    int get_Treatment() const;
    int get_TreatDay() const;
    int get_startDay() const;
    int get_priority() const;
    //basic set function
    void set_status(status newstat);
    void set_startDay(int day);
    void set_TreatDay(int day);
    void set_priority(int priority);

private:
    int id;
    int Medic;
    int Treatment;
    int Reg;
    int start_day;
    int Treat_day;
    int priority;

    string name;
    status stat;
};


#endif //TRIAL_PA2_TUPLE_H
