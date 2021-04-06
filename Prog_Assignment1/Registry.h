//
// Created by jordan on 2021/4/3.
//

// this class are use to BUILD the registry structure. In my imagination,
// i would like to build a Multiple linked list to store these information.

#ifndef PROG_ASSIGNMENT1_REGISTRY_H
#define PROG_ASSIGNMENT1_REGISTRY_H
#include <string>;
#include <vector>;
using namespace std;
enum status {applied,waiting,complete,withdraw};
emum result {normal,delayed,emergency};
enum location {A,B,C,D,E,F,G,H};

class Reg_Node {
    friend class Registry;

public:
    // constructor and a copy constructor.
    Reg_Node(int ID = -1,string name = "NULL",int age=-1,int risk=-1,int prof=-1,string Birth = 'NULL',string RegData = "Null",int RegDay=0,status stat = applied,int Location,
    string WeChat = "NULL",string QQ = "NULL",string Email = "NULL",string phone = "NULL");
    Reg_Node(const Reg_Node &obj);
    //~Reg_Node();
    // setting functions.
    void set_name(int id,string name,Reg_Node*prev,Reg_Node*next);
    void set_profession(int prof,Reg_Node*prev,Reg_Node*next);
    void set_age(int age,Reg_Node*prev,Reg_Node*next);
    void set_risk(int risk,Reg_Node*prev,Reg_Node*next);
    void set_other_info(string Birth,string RegData,int RegDay,int Location,string Wechat,string QQ,string Email,string phone);
    void set_status(status stat);
    void set_treatment(int TreatDAY);
    void set_priority(int priority);
    void set_queueTime(int time);
    // Since it is a multiple linked list, all pointers are set in the
    // matching get function.
    int get_id();
    int get_priority();
    int get_risk();
    int get_name();
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

class Registry {
public:
    Registry();
    // ~Registry();
    int getlength();
    void insert(string name,string birth,string RegData,int age,int risk,int prof,int location,
                string Wechat,string QQ, string Email,string phone);
    void remove(int id);
    void set_Day(int day_num);
    // no concat available Since it is a multiple linked list.
    int search_name(string name); // both will printout the detailed info.
    // the follow is used for sort and return pointers.
    Reg_Node* search_id(int id);
    vector<int> get_waiting(int mode = 0); // return the id who are still not push to the queue.
    // to make it easier to return in specific order, the parametric is use to switch
    // searching mode. 0 for name list, 1 for age list,
    void withdraw(int id);
    // using to push one people to the queue.
    // only do that on next day.
    vector<Reg_Node*> push2Queue();
    // below are sorting methods.
    void age_sort();
    void prof_sort();
    void name_sort();

private:
    int prev_ID; // use to assign new unique id;
    int numitems;
    int current_day;
    // dummy nodes
    Reg_Node *name_dummy;
    Reg_Node *age_dummy;
    Reg_Node *risk_dummy;
    Reg_Node *prof_dummy;
    // useful functions.
    Reg_Node* name_first();
    Reg_Node* name_last();
    Reg_Node* age_first();
    Reg_Node* risk_first();
    Reg_Node* prof_first();
    Reg_Node* locate(int index); // useful in sorting;
};


#endif //PROG_ASSIGNMENT1_REGISTRY_H
