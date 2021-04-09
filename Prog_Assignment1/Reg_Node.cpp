//
// Created by jordan on 2021/4/9.
//

#include "Reg_Node.h"


Reg_Node::Reg_Node(int ID, string name, int age, int risk, int prof, string Birth, string RegData, int RegDay, status stat,
                   int Location, string WeChat, string QQ, string Email, string phone) {
    // i would set the pointer in the registry. by the way, the node can also
    //set the pointer by this function.
    Reg_Node* dummy = nullptr;
    set_other_info(Birth,RegData,RegDay,Location,WeChat,QQ,Email,phone);
    set_status(stat);
    set_name(ID,name,dummy,dummy);
    set_age(age,dummy,dummy);
    set_risk(risk,dummy,dummy);
    set_profession(prof,dummy,dummy);
    set_queueTime(0);
    set_ddl(0);
}

Reg_Node::Reg_Node(const Reg_Node &obj) {
    // Copy constructor here.
    // i wonder should i copy all the things to the new memory size. since when something is changed, all the things
    // should be done. or, in another version, we can make the information isolated. in my node, we can only handle several things.
    // but now we have made this node.
    // i can write the class reg to avoid such information being read.
    ID = obj.ID;
    name = obj.name;
    profession = obj.profession;
    age_group = obj.age_group;
    risk = obj.risk;
    location = obj.location;
    queTime = obj.queTime;
    WeChat = obj.WeChat;
    QQ = obj.QQ;
    E_mail = obj.E_mail;
    phone = obj.phone;
    Birthday = obj.Birthday;
    stat = obj.stat;
    standard_priority = obj.standard_priority;
    TreatDay = obj.TreatDay;
    RegData = obj.RegData;
    Reg_Day = obj.Reg_Day;
    name_prev = obj.name_next;
    name_next = obj.name_next;
    prof_prev = obj.prof_prev;
    prof_next = obj.prof_next;
    age_prev = obj.age_prev;
    age_next = obj.age_next;
    risk_prev = obj.risk_prev;
    risk_next = obj.risk_next;
}
void Reg_Node::set_ddl(int time) {
    this->ddl = time;
    return;
}

int Reg_Node::get_ddl() {
    return this->ddl;
}
void Reg_Node::set_age(int age, Reg_Node *prev, Reg_Node *next)
{
    // the age group division will be finished in the registry.
    // also the pointers.
    this->age_group = age;
    this->age_next = next;
    this->age_prev = prev;
}

void Reg_Node::set_name(int id, string name, Reg_Node *prev, Reg_Node *next)
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
    this->stat = stat;
}

void Reg_Node::set_other_info(string Birth, string RegData, int RegDay, int Location, string Wechat, string QQ, string Email,
                              string phone) {
    this->WeChat = Wechat;
    this->phone = phone;
    this->QQ = QQ;
    this->E_mail = Email;
    this->location = Location;
    this->Birthday = Birth;
    this->RegData = RegData;
    this->Reg_Day = RegDay;
    this->TreatDay = 0;
    this->standard_priority = 0;
}

void Reg_Node::set_treatment(int TreatDAY)
{
    this->TreatDay = TreatDAY;
    //this->treatData = TreatData;
}

void Reg_Node::set_queueTime(int time) {
    this->queTime = time;
}

int Reg_Node::queueTime() {
    return this->queTime;
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

string* Reg_Node::get_local_info() {
    string* answer = new string[6];
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
Reg_Node * Reg_Node::NameNext() {return name_next;}
Reg_Node * Reg_Node::NamePrev() {return name_prev;}
Reg_Node * Reg_Node::ProfNext() {return this->prof_next;}
Reg_Node * Reg_Node::ProfPrev() {return this->prof_prev;}
Reg_Node * Reg_Node::RiskNext() {return this->risk_next;}
Reg_Node * Reg_Node::RiskPrev() {return this->risk_prev;}

void Reg_Node::set_namePrev(Reg_Node *prev) {
    name_prev = prev;
}

void Reg_Node::set_nameNext(Reg_Node *next) {
    name_next = next;
}

void Reg_Node::set_profNext(Reg_Node *next) {
    prof_next = next;
}

void Reg_Node::set_profPrev(Reg_Node *prev) {
    prof_prev = prev;
}

void Reg_Node::set_ageNext(Reg_Node *next) {
    age_next = next;
}

void Reg_Node::set_agePrev(Reg_Node *prev) {
    age_prev = prev;
}

void Reg_Node::set_riskNext(Reg_Node *next) {
    risk_next = next;
    return;
}

void Reg_Node::set_riskPrev(Reg_Node *prev) {
    risk_prev = prev;
    return;
}