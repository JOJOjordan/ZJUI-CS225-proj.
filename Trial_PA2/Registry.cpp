//
// Created by jordan on 2021/5/14.
//

// simplified function!!!
#include "Registry.h"

using namespace std;

Registry::Registry(int RSnum, int stationID) {
    this->prev_ID = stationID-RSnum; // so we do not have ID that is zero.
    this->current_Day = 0;
    this->step_length = RSnum;
    this->Reg_database = new RDB(50);
    this->waiting = new vector<Tuple*>;
    this->withdraw_patient = new vector<Tuple*>;
}

int Registry::getitem() {
    return Reg_database->getlength();
}

int Registry::insert(string name, int Medical, int Registration, int Treatment) {
    // first generate new ID.
    this->prev_ID = this->prev_ID + this->step_length;
    // then create a new tuple!
    Tuple newtuple = Tuple(this->prev_ID, name, Medical, Registration, Treatment, applied);
    newtuple.set_startDay(this->current_Day);
    // then any modify to the tuple is not allowed.
    auto temp = this->Reg_database->insert(newtuple);
    waiting->push_back(temp);
    return this->prev_ID;
}

void Registry::remove(int id) {
    // search!!!!
    //1. remove it from the database.
    auto result = Reg_database->find_ID(id);
    //check it's status.
    if (result){
        if (result->get_status() == applied){
            // then this shows that it is inside the list.
            // different from the withdraw, the delete should delete it entirely.
            for(int i=0;i<waiting->size();i++){
                if (*waiting[i]==result){
                    waiting->erase(waiting->begin()+i);
                    break;
                }
            }
        }
    }
    //2. remove any possible pointer:the waiting list.
    this->Reg_database->Delete(id);
}

void Registry::withdraw(int id) {
    //just remove it from the possible waiting list.
    //add bad day info to the waiting day status.
    auto result = Reg_database->find_ID(id);
    if (result){
        if (result->get_status() == applied){
            // then this shows that it is inside the list.
            // different from the withdraw, the delete should delete it entirely.
            for(int i=0;i<waiting->size();i++){
                if (*waiting[i]==result){
                    waiting->erase(waiting->begin()+i);
                    break;
                }
            }
        }
        // then change the status.
        result->set_status(withdrawn);
        // simple record to avoid find entirely database.
        this->withdraw_patient->push_back(result);
    }
}

void Registry::resent_application(int id) {
    auto result = Reg_database->find_ID(id);
    if (result){
        if (result->get_status() == withdrawn){
            result->set_status(applied);
            // one month's punish.
            result->set_startDay(this->current_Day-30);
            // push it back to the waiting queue.
            this->waiting->push_back(result);
        }
    }
}

Tuple * Registry::find_id(int id) {
    return this->Reg_database->find_ID(id);
}

vector<Tuple*> * Registry::find_sth(int mode, int information) {
    //0 for medic, 1 for treatment, 2 for location.
    vector<Tuple*>* temp;
    switch (mode) {
        case 0:
            temp = this->Reg_database->find_Medic(information);
            break;
        case 1:
            temp = this->Reg_database->find_Treatment(information);
            break;
        case 2:
            //basically, the location here is destination, not the registry station.
            temp = this->Reg_database->find_Reg(information);
            break;
        default:
            temp = nullptr;
            break;
    }
    return temp;
}

Tuple * Registry::find_name(string patient_name) {
    // hard to implement.
    // so drop there first .
    return nullptr;
}

vector<Tuple *> * Registry::report_waiting() {
    return waiting;
}

vector<Tuple *> * Registry::report_withdraw() {
    return withdraw_patient;
}

void Registry::updateDAY(int day) {
    this->current_Day = day;
}

Tuple* Registry::Daily_push() {
    // the waiting should use FIFO list, but for easier work, the vector
    // container can work well in the same time.
    Tuple* ret = *this->waiting[0];
    this->waiting->erase(this->waiting->begin());
    return ret;
}