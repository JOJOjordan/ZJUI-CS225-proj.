//
// Created by jordan on 2021/4/3.
//

// this class are use to BUILD the registry structure. In my imagination,
// i would like to build a Multiple linked list to store these information.

#ifndef PROG_ASSIGNMENT1_REGISTRY_H
#define PROG_ASSIGNMENT1_REGISTRY_H

enum status {applied,waiting,complete,withdraw};
enum location{A,B,C,D,E,F,G,H};

class Reg_Node {
    friend class Registry;

public:
    // constructor and a copy constructor.
    Reg_Node(int ID = 0,char name = "NULL",int age=0,int risk=0,int prof=0,char Birth = 'NULL',char RegData = "Null",int RegDay=0,status stat = applied,int Location,
    char WeChat = "NULL",char QQ = "NULL",char Email = "NULL",char phone = "NULL");
    Reg_Node(const Reg_Node &obj);
    ~Reg_Node();
    void set_name(int id,char name,Reg_Node*prev,Reg_Node*next);
    void set_profession(int prof,Reg_Node*prev,Reg_Node*next);
    void set_age(int age,Reg_Node*prev,Reg_Node*next);
    void set_risk(int risk,Reg_Node*prev,Reg_Node*next);
    void set_other_info(char Birth,char RegData,int RegDay,int Location,char Wechat,char QQ,char Email,char phone);
    void set_status(status stat);
    // Since it is a multiple linked list, all pointers are set in the
    // matching set function.
private:
    int ID;
    char name;
    int profession;
    int age_group;
    int risk;
    int location;

    //not so useful information;
    char WeChat;
    char QQ;
    char E_mail;
    char phone;

    //status information;
    status stat;
    int standard_priority;

    // treat information;
    int TreatDay;
    char treatData;

    // other info
    char BirthDay;   // our time info is stored in such a struct : 20010620 for 20,June, 2001;
    char RegData;
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
    void insert(char name,char birth,char RegData,int age,int risk,int prof,int location,char );
    void remove(int id);
    void set_Day(int day_num);
    // no concat available Since it is a multiple linked list.
    int search_name(char name); // both will printout the detailed info.
    int search_id(int ID);
    void get_risk(int ID);
    void get_prof(int ID);
    void get_waiting(int ID);
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
