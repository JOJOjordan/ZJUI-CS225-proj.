//
// Created by jordan on 2021/5/11.
//

#include "Tuple.h"
using namespace std;

Tuple::Tuple(int ID, string name, int Medic_Stat, int Registration, int T_type, status stat) {
    //constructor
    this->id = ID;
    this->name = name;
    this->Medic = Medic_Stat;
    this->Reg = Registration;
    this->Treatment = T_type;
    this->stat = stat;
    this->Treat_day = -1;
    this->start_day = -1;
    this->priority = -1;
}


int Tuple::get_id() const{
    return id;
}

int Tuple::get_Treatment() const{
    return Treatment;
}

int Tuple::get_medic() const{
    return Medic;
}

string Tuple::get_name() const{
    return name;
}

status Tuple::get_status() const{
    return stat;
}
int Tuple::get_registration() const{
    return Reg;

}
void Tuple::set_status(status newstat) {
    this->stat = newstat;
}

int Tuple::get_priority() const {
    return this->priority;
}
void Tuple::set_priority(int priority) {
    this->priority = priority;
}

Tuple::Tuple(const Tuple& obj) {
    this->id = obj.get_id();
    this->stat = obj.get_status();
    this->Medic = obj.get_medic();
    this->Treatment = obj.get_Treatment();
    this->Reg = obj.get_registration();
    this->name = obj.get_name();
    this->start_day = obj.get_startDay();
    this->Treat_day = obj.get_TreatDay();
}

void Tuple::set_TreatDay(int day) {
    this->Treat_day = day;
}

int Tuple::get_TreatDay() const {
    return this->Treat_day;
}

void Tuple::set_startDay(int day) {
    this->start_day = day;
}

int Tuple::get_startDay() const {
    return this->start_day;
}
