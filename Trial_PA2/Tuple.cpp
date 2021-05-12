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
}


int Tuple::get_id() {
    return id;
}

int Tuple::get_Treatment() {
    return Treatment;
}

int Tuple::get_medic() {
    return Medic;
}

string Tuple::get_name() {
    return name;
}

status Tuple::get_status() {
    return stat;
}
int Tuple::get_registration() {
    return Reg;
}
void Tuple::set_status(status newstat) {
    this->stat = newstat;
    return;
}

Tuple::Tuple(const Tuple& obj) {


    this->id = obj.get_id();
    this->stat = obj.get_status();
}
