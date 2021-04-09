//
// Created by jordan on 2021/4/3.
//

// this class are use to BUILD the registry structure. In my imagination,
// i would like to build a Multiple linked list to store these information.

#ifndef PROG_ASSIGNMENT1_REGISTRY_H
#define PROG_ASSIGNMENT1_REGISTRY_H



#include "Reg_Node.h"

using namespace std;
class Reg_Node; 

class Registry {
public:
    Registry();
    // ~Registry();
    int getlength();
    Reg_Node* insert(string name,string birth,string RegData,int age,int risk,int prof,int location,string Wechat,string QQ, string Email,string phone);
    void remove(int id);
    void set_Day(int day_num);
    // no concat available Since it is a multiple linked list.
    //int search_name(string name); // both will printout the detailed info.
    // the follow is used for sort and return pointers.
    Reg_Node* search_id(int id);
    int search_name(string name);
    int priority_letter(Reg_Node* VIP, int ddl);
    vector<int> get_waiting(int mode = 0); // return the id who are still not push to the queue.
    vector<int> get_withdraw(int mode = 0);
    // to make it easier to return in specific order, the parametric is use to switch
    // searching mode. 0 for name list, 1 for age list,
    void withdrawn(int id);
    // using to push one people to the queue.
    // only do that on next day.
    vector<Reg_Node*> push2Queue();
    // below are sorting methods.
    void change_profssion(Reg_Node* op, int prof){
        op->set_profession(prof,op->prof_prev,op->prof_next);
        return;
    }

    void age_sort();
    void prof_sort();
    void name_sort();
    //void Display(int mode = 0);//mode 0 (default) will print out waiting people. mode 1 will print out withdraw people.

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

};


#endif //PROG_ASSIGNMENT1_REGISTRY_H
