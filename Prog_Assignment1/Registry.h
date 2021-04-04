//
// Created by jordan on 2021/4/3.
//

// this class are use to BUILD the registry structure. In my imagination,
// i would like to build a Multiple linked list to store these information.

#ifndef PROG_ASSIGNMENT1_REGISTRY_H
#define PROG_ASSIGNMENT1_REGISTRY_H

enum status {applied,waiting,complete,withdraw};

class Reg_Node {
    friend class Registry;

public:
    // constructor and a copy constructor.
    Reg_Node(int ID=0,char name,int age=0,int risk=0,int prof=0,int Birth=0,int RegData=0,int RegDay=0,status stat);
    Reg_Node(const Reg_Node &obj);
    ~Reg_Node();
    void set_name(int id,char name);
    void set_profession(int prof);
    void set_age(int age);
    void set_risk(int risk);
    void set_other_info(int Birth,int RegData,int RegDayz);
    void set_status(status stat);
    // Since it is a multiple linked list, all pointers are set in the
    // matching set function.
private:
    int ID;
    char name;
    int profession;
    int age_group;
    int risk;
    status stat;
    // other info
    int BirthDay;   // our time info is stored in such a struct : 20010620 for 20,June, 2001;
    int RegData;
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
    void insert(char name,int birth,int RegData,int age,int risk,int prof);
    void remove(int id);
    void set_Day(int day_num);
    // no concat available Since it is a multiple linked list.
    int search_name(char name); // both will printout the detailed info.
    int search_id(int ID);
    // below are sorting methods.
    void age_sort();
    void prof_sort();
    void name_sort();

private:
    int prev_ID; // use to assign new unique id;
    int numitems;
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
