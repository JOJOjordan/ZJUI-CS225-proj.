//
// Created by jordan on 2021/4/3.
//

#include "Registry.h"

using namespace std;


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

Reg_Node* Registry::insert(string name, string birth, string RegData, int age, int risk, int prof, int location,
                      string Wechat, string QQ, string Email, string phone) {
    // now we should insert the read node into the reg chain.

    this->prev_ID++;
    Reg_Node *newnode = new Reg_Node;

    Reg_Node *name_last;
    name_last = name_dummy->NamePrev();
    newnode->set_name(prev_ID, name, name_dummy, name_dummy);
    newnode->set_nameNext(name_dummy);
    newnode->set_namePrev(name_last);
    name_dummy->set_namePrev(newnode);
    (name_last)->set_nameNext(newnode);
    cout<<newnode->NamePrev()->ID<<" is the last ID"<<endl;

    // the age info here is the origin number. we have to divide them to age group.
    int age_group = 0;
    if (0<age &&age<=12){age_group = 1;}
    if (12<age && age<=18){age_group = 2;}
    if (18<age && age<=35){age_group = 3;}
    if (35<age && age<=50){age_group = 4;}
    if (50<age &&age<=65){age_group = 5;}
    if (65<age&& age<=75){age_group = 6;}
    if (age>75){age_group = 7;}

    Reg_Node *age_l;
    age_l = age_dummy->AgePrev();
    newnode->set_age(age_group, age_dummy, age_dummy);
    newnode->set_agePrev(age_l);
    age_dummy->set_agePrev(newnode);
    age_l->set_ageNext(newnode);


    Reg_Node *prof_l;
    prof_l = prof_dummy->ProfPrev();
    newnode->set_profession(prof, prof_l, prof_dummy);
    prof_dummy->set_profPrev(newnode);
    prof_l->set_profNext(newnode);

    Reg_Node *risk_l;
    risk_l = risk_dummy->RiskPrev();
    newnode->set_risk(risk,risk_l,risk_dummy);
    risk_dummy->set_riskPrev(newnode);
    risk_l->set_riskNext(newnode);

    // now the basic information.
    newnode->set_priority(-1);
    newnode->set_status(applied);
    newnode->set_other_info(birth,RegData,current_day,location,Wechat,QQ,Email,phone);

    //set queue time! Remember to refine after discussion;
    if (risk == 0){newnode->set_queueTime(7);}
    if (risk == 1){newnode->set_queueTime(7);}
    if (risk == 2){newnode->set_queueTime(37);}

    numitems++;

    cout<<"Welcome! Mr/Miss/Mrs "<<name;
    cout<<"!"<<" Your ID is "<<prev_ID<<endl;
    return newnode;
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
    return output;
}

vector<int> Registry::get_withdraw(int mode) {
    vector<int> output;
    Reg_Node* dummy;
    Reg_Node* current;
    switch (mode) {
        case 0:
            dummy = name_dummy;
            current = dummy->NameNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == withdraw){
                    output.push_back(current->get_id());
                }
                current = current->NameNext();
            }
            break;
        case 1:
            dummy = age_dummy;
            current = dummy->AgeNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == withdraw){
                    output.push_back(current->get_id());
                }
                current = current->AgeNext();
            }
            break;
        case 2:
            dummy = prof_dummy;
            current = dummy->ProfNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == withdraw){
                    output.push_back(current->get_id());
                }
                current = current->ProfNext();
            }
            break;
        case 3:
            dummy = risk_dummy;
            current = dummy->RiskNext();
            for (int i=0;i<numitems;i++){
                if (current->get_status() == withdraw){
                    output.push_back(current->get_id());
                }
                current = current->RiskNext();
            }
            break;
    }
    return output;
}

int Registry::priority_letter(Reg_Node* VIP, int ddl) {
    VIP->set_ddl(ddl);
    VIP->set_status(waiting);
    return 1;
}

void Registry::withdrawn(int id) {
    // use to withdraw someone.
    // here we do not need to
    Reg_Node* sb_is_health;
    sb_is_health = search_id(id);
    sb_is_health->set_status(withdraw);
}

int Registry::search_name(string name) {
    Reg_Node* head;
    int retnum = -1;
    head = name_dummy->NameNext();
    for (int i = 0; i < numitems;i++) {
        if (head->name == name) {
            retnum = head->get_id();
        }
        head = head->NameNext();
    }
    return retnum;
}

