//
// Created by jordan on 2021/4/3.
//

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Registry.h"

using namespace std;

Reg_Node::Reg_Node(int ID, string name, int age, int risk, int prof, string Birth, string RegData, int RegDay, status stat,
                   int Location, string WeChat, string QQ, string Email, string phone) {
    // i would set the pointer in the registry. by the way, the node can also
    //set the pointer by this function.
    Reg_Node* dummy = nullptr;
    set_other_info(Birth,RegData,RegDay,Location,WeChat,QQ,Email,phone);
    set_status(applied);
    set_name(ID,name,dummy,dummy);
    set_age(age,dummy,dummy);
    set_risk(risk,dummy,dummy);
    set_profession(prof,dummy,dummy);
}

Reg_Node::Reg_Node(const Reg_Node &obj) {
    // Copy constructor here.
}

void Reg_Node::set_age(int age, Reg_Node *prev, Reg_Node *next)
{
    // the age group division will be finished in the registry.
    // also the pointers.
    this->age_group = age;
    this->age_next = next;
    this->age_prev = prev;
}

void Reg_Node::set_name(int id, char name, Reg_Node *prev, Reg_Node *next)
{
    // the name and the next items will be add in the same way.
    this->name = name;
    this->ID = id;
    this->name_next = next;
    this->name_prev = prev;
}

void Reg_Node::set_profession(int prof, Reg_Node *prev, Reg_Node *next)
{
    this->profession = prof;
    this->prof_next = next;
    this->prof_prev = prev;
}

void Reg_Node::set_risk(int risk, Reg_Node *prev, Reg_Node *next) {
    this->risk = risk;
    this->risk_next = next;
    this->risk_prev = prev;
}

void Reg_Node::set_status(status stat) {
    this->set_status=stat;
}

void Reg_Node::set_other_info(string Birth, string RegData, int RegDay, int Location, string Wechat, string QQ, string Email,
                              string phone) {
    this->WeChat = Wechat;
    this->phone = phone;
    this->QQ = QQ;
    this->E_mail = Email;
    this->location = Location;
    this->BirthDay = Birth;
    this->RegData = RegData;
    this->Reg_Day = RegDay;
    this->TreatDay = 0;
    this->treatData = "NULL";
    this->standard_priority = 0;
}

void Reg_Node::set_treatment(int TreatDAY)
{
    this->TreatDay = TreatDAY;
    //this->treatData = TreatData;
}

void Reg_Node::set_priority(int priority) {
    this->standard_priority = priority;
}

int Reg_Node::get_age() {
    return this->age_group;
}

string Reg_Node::get_name() {
    return this->name;
}

int Reg_Node::get_risk() {
    return this->risk;
}

int Reg_Node::get_location() {
    return this->location;
}

int Reg_Node::get_id() {
    return this->ID;
}

int Reg_Node::get_priority() {return this->standard_priority;}

int Reg_Node::get_RegDay() {return this->Reg_Day;}

status Reg_Node::get_status() {return this->stat;}

int Reg_Node::get_profession() {return this->profession;}

string * Reg_Node::get_local_info() {
    string * answer[6];
    answer[0] = this->phone;
    answer[1] = this->QQ;
    answer[2] = this->WeChat;
    answer[3] = this->E_mail;
    answer[4] = this->Birthday;
    answer[5] = this->RegData;
    return answer;
}

int Reg_Node::get_treatDay() { return this->TreatDay;}

Reg_Node * Reg_Node::AgeNext() {return this->age_next;}
Reg_Node * Reg_Node::AgePrev() {return this->age_prev;}
Reg_Node * Reg_Node::NameNext() {return this->name_next;}
Reg_Node * Reg_Node::NamePrev() {return this->name_prev;}
Reg_Node * Reg_Node::ProfNext() {return this->prof_next;}
Reg_Node * Reg_Node::ProfPrev() {return this->prof_prev;}
Reg_Node * Reg_Node::RiskNext() {return this->risk_next;}
Reg_Node * Reg_Node::RiskPrev() {return this->risk_prev;}
