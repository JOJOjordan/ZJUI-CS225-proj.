//
// Created by jordan on 2021/4/9.
//

#ifndef PROG_ASSIGNMENT1_REG_NODE_H
#define PROG_ASSIGNMENT1_REG_NODE_H


#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "status.h"

class Registry;
template <class T>class CentralQueue;
class FIFO;

enum status;
using namespace std;

class Reg_Node {
    friend class Registry;

    template<class T> friend class CentralQueue;

    friend class FIFO;

public:
    // constructor and a copy constructor.
    Reg_Node(int ID = -1,string name = "NULL",int age=-1,int risk=-1,int prof=-1,string Birth = "NULL",string RegData = "Null",int RegDay=0,status stat = applied,int Location = 0,
             string WeChat = "NULL",string QQ = "NULL",string Email = "NULL",string phone = "NULL");
    Reg_Node(const Reg_Node &obj);
    //~Reg_Node();
    // setting functions.
    void set_name(int id,string name,Reg_Node*prev,Reg_Node*next);
    void set_nameNext(Reg_Node* next);
    void set_namePrev(Reg_Node* prev);
    void set_profession(int prof,Reg_Node*prev,Reg_Node*next);
    void set_profNext(Reg_Node* next);
    void set_profPrev(Reg_Node* prev);
    void set_age(int age,Reg_Node*prev,Reg_Node*next);
    void set_ageNext(Reg_Node* next);
    void set_agePrev(Reg_Node* prev);
    void set_risk(int risk,Reg_Node*prev,Reg_Node*next);
    void set_riskNext(Reg_Node* next);
    void set_riskPrev(Reg_Node* prev);
    void set_other_info(string Birth,string RegData,int RegDay,int Location,string Wechat,string QQ,string Email,string phone);
    void set_status(status stat);
    void set_treatment(int TreatDAY);
    void set_priority(int priority);
    void set_queueTime(int time);
    void set_ddl(int time);
    // Since it is a multiple linked list, all pointers are set in the
    // matching get function.
    int get_ddl();
    int get_id();
    int get_priority();
    int get_risk();
    string get_name();
    int get_profession();
    int get_age();
    int get_location();
    string* get_local_info();
    status get_status();
    int get_treatDay();
    int get_RegDay();
    int queueTime();
    // pointer getter;
    Reg_Node* AgePrev();
    Reg_Node* AgeNext();
    Reg_Node* NamePrev();
    Reg_Node* NameNext();
    Reg_Node* ProfPrev();
    Reg_Node* ProfNext();
    Reg_Node* RiskPrev();
    Reg_Node* RiskNext();


private:
    int ID;
    string name;
    int profession;
    int age_group;
    int risk;
    int location;
    int queTime;
    int ddl;
    //not so useful information;
    string WeChat;
    string QQ;
    string E_mail;
    string phone;
    string Birthday;

    //status information;
    status stat;
    int standard_priority;

    // time stamp;
    int TreatDay;
    //string treatData; // our time info is stored in such a struct : 20010620 for 20,June, 2001;
    string RegData;
    int Reg_Day; // C++20 have add the new feature in chrono lib,but this is much simple.

    // below is the pointers.
    Reg_Node* name_prev;
    Reg_Node* name_next;
    Reg_Node* prof_prev;
    Reg_Node* prof_next;
    Reg_Node* age_prev;
    Reg_Node* age_next;
    Reg_Node* risk_next;
    Reg_Node* risk_prev;

};


#endif //PROG_ASSIGNMENT1_REG_NODE_H
