//
// Created by jordan on 2021/5/14.
//

#ifndef TRIAL_PA2_REGISTRY_H
#define TRIAL_PA2_REGISTRY_H
#include "RDB.h"

using namespace std;
//modify from the Program assignment1.
class Registry {
public:
    Registry(int RSnum = 1, int stationID = 1);
    //~Registry();
    int getitem();
    int insert(string name,int Medical, int Registration, int Treatment);
    void remove(int id);
    Tuple* find_id(int id);
    vector<Tuple*>* find_sth(int mode, int information);
    Tuple* find_name(string patient_name);
    void withdraw(int id);
    void priority(int id,int ddl);
    // method to cancel the withdraw.
    void resent_application(int id);
    void updateDAY(int day);
    // special function
    vector<Tuple*>* report_waiting();
    vector<Tuple*>* report_withdraw();
    Tuple* Daily_push(); // remember to resolve the location in order to insert.
    // to control the number, this time we change the push progress.
private:
    int prev_ID;
    int step_length;
    int current_Day;
    // then the database
    RDB* Reg_database;
    vector<Tuple*>* waiting;
    vector<Tuple*>* withdraw_patient;
};


#endif //TRIAL_PA2_REGISTRY_H
