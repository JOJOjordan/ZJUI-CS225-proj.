//
// Created by jordan on 2021/4/3.
//

#include <stdio.h>;
#include <cstdlib>;
#include <iostream>;
#include "Registry.h"
using namespace std;

Reg_Node::Reg_Node(int ID, char name, int age, int risk, int prof, char Birth, char RegData, int RegDay, status stat,
                   int Location, char WeChat, char QQ, char Email, char phone) {
    R
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

void Reg_Node::set_other_info(char Birth, char RegData, int RegDay, int Location, char Wechat, char QQ, char Email,
                              char phone) {
    this->WeChat = Wechat;
    this->phone = phone;
    this->QQ = QQ;
    this->E_mail = Email;
    this->location = Location;
    this->BirthDay = Birth;
    this->RegData = RegData;
    this->Reg_Day = RegDay;
}

