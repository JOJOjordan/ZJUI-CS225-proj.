//
// Created by jordan on 2021/4/3.
//

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
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
    set_queueTime(0);
}

Reg_Node::Reg_Node(const Reg_Node &obj) {
    // Copy constructor here.
    // i wonder should i copy all the things to the new memory size. since when something is changed, all the things
    // should be done. or, in another version, we can make the information isolated. in my node, we can only handle several things.
    // but now we have made this node.
    // i can write the class reg to avoid such information being read.

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


Registry::Registry()
{
    // the registry only take care of the basic info, not considering the further things.
    age_dummy = new Reg_Node;
    name_dummy = new Reg_Node;
    prof_dummy = new Reg_Node;
    risk_dummy = new Reg_Node;

    //previous code may have bugs.

    this->age_dummy->set_age(-1,age_dummy,age_dummy);
    this->risk_dummy->set_risk(-1,risk_dummy,risk_dummy);
    this->prof_dummy->set_profession(-1,prof_dummy,prof_dummy);
    this->name_dummy->set_name(-1,"NULL",name_dummy,name_dummy);
    numitems = 0;
    prev_ID = 0;
}

int Registry::getlength() {
    return numitems;
}
Reg_Node* Registry::search_id(int id) {
    if ((id <= 0) || (id > numitems)){
        cout<<"Invalid Id input. "<<endl;
        exit(EXIT_FAILURE);
    }
    else{
        Reg_Node* head;
        Reg_Node* ret = nullptr;
        head = name_dummy->NameNext();
        for (int i = 0; i < numitems;i++){
            if (head->ID == id){
                ret = head;
            }
            head = head->NameNext();
        }
        // return nullptr will show that the id is not in the
        // list. so we should take care of this situation.
        return ret;
    }
}

void Registry::remove(int id) {
    Reg_Node* temp;
    temp = search_id(id);
    Reg_Node* age_prev;
    Reg_Node* age_next;
    age_prev = temp->AgePrev();
    age_next = temp->AgeNext();
    age_prev->set_age(age_prev->get_age(),age_prev->AgePrev(),age_next);
    age_next->set_age(age_next->get_age(),age_prev,age_next->AgeNext());

    Reg_Node* name_prev;
    Reg_Node* name_next;
    name_prev = temp->NamePrev();
    name_next = temp->NameNext();
    name_prev->set_name(name_prev->get_id(),name_prev->get_name(),name_prev->NamePrev(),name_next);
    name_next->set_name(name_next->get_id(),name_next->get_name(),name_prev,name_next->NameNext());

    Reg_Node* prof_prev;
    Reg_Node* prof_next;
    prof_prev = temp->ProfPrev();
    prof_next = temp->ProfNext();
    prof_prev->set_profession(prof_prev->get_profession(),prof_prev->ProfPrev(),prof_next);
    prof_next->set_profession(prof_next->get_profession(),prof_prev,prof_next->ProfNext());

    Reg_Node* risk_prev;
    Reg_Node* risk_next;
    risk_prev = temp->RiskPrev();
    risk_next = temp->RiskNext();
    risk_prev->set_risk(risk_prev->get_risk(),risk_prev->RiskPrev(),risk_next);
    risk_next->set_risk(risk_next->get_risk(),risk_prev,risk_next->RiskNext());

    numitems --;
    delete temp;
    return;
}

void Registry::insert(string name, string birth, string RegData, int age, int risk, int prof, int location,
                      string Wechat, string QQ, string Email, string phone) {
    // now we should insert the read node into the reg chain.

    this->prev_ID++;
    Reg_Node *newnode = new Reg_Node;

    Reg_Node *name_last;
    name_last = name_dummy->NamePrev();
    newnode->set_name(prev_ID, name, name_last, name_dummy);

    // the age info here is the origin number. we have to divide them to age group.
    int age_group = 0;
    if (0<age <=12){age_group = 1;}
    if (12<age<=18){age_group = 2;}
    if (18<age<=35){age_group = 3;}
    if (35<age<=50){age_group = 4;}
    if (50<age<=65){age_group = 5;}
    if (65<age<=75){age_group = 6;}
    if (age>75){age_group = 7;}
    Reg_Node *age_l;
    age_l = age_dummy->AgePrev();
    newnode->set_age(age_group, age_l, age_dummy);

    Reg_Node *prof_l;
    prof_l = prof_dummy->ProfPrev();
    newnode->set_profession(prof, prof_l, prof_dummy);

    Reg_Node *risk_l;
    risk_l = risk_dummy->RiskPrev();
    newnode->set_risk(risk,risk_l,risk_dummy);

    // now the basic information.
    newnode->set_priority(-1);
    newnode->set_status(applied);
    newnode->set_other_info(birth,RegData,current_day,location,Wechat,QQ,Email,phone);

    //set queue time! Remember to refine after discussion;
    if (risk == 0){newnode->set_queueTime(7);}
    if (risk == 1){newnode->set_queueTime(7);}
    if (risk == 2){newnode->set_queueTime(37);}

    numitems++;
    return;
}

void Registry::set_Day(int day_num) { current_day = day_num;}

vector<Reg_Node *> Registry::push2Queue() {
    vector < Reg_Node * > output;
    Reg_Node *current;
    current = name_dummy->NameNext();
    for (int i = 0; i < numitems; i++) {
        if (current->get_status() == applied) {
            output.push_back(current);
            current->set_status(waiting);
        }
        current = current->NameNext();
    }
    return output;
}

vector<int> Registry::get_waiting(int mode) {
    vector<int> output;
    Reg_Node* dummy;
    Reg_Node* current;
    switch (mode) {
        case 0:
            dummy = name_dummy;
            current = dummy->NameNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == applied){
                    output.push_back(current->get_id());
                }
                current = current->NameNext();
            }
            break;
        case 1:
            dummy = age_dummy;
            current = dummy->AgeNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == applied){
                    output.push_back(current->get_id());
                }
                current = current->AgeNext();
            }
            break;
        case 2:
            dummy = prof_dummy;
            current = dummy->ProfNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == applied){
                    output.push_back(current->get_id());
                }
                current = current->ProfNext();
            }
            break;
        case 3:
            dummy = risk_dummy;
            current = dummy->RiskNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == applied){
                    output.push_back(current->get_id());
                }
                current = current->RiskNext();
            }
            break;
    }
}

void Registry::withdraw(int id) {
    // use to withdraw someone.
    // here we do not need to
    Reg_Node* sb_is_health;
    sb_is_health = search_id(id);
    sb_is_health->set_status(withdraw);
}

