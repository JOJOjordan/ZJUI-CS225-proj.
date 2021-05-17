//
// Created by jordan on 2021/5/16.
//

#include "SimpleHash.h"

using namespace std;

SimpleHash::SimpleHash(int length,int type) {
    for (int i=0;i<length;i++){
        auto T_ptr = new vector<Tuple*>;
        this->Main_Data.push_back(T_ptr);
    }
    this->key_type = type;
}

SimpleHash::~SimpleHash() {
    for (auto i:this->Main_Data){
        delete i;
    }
    delete &this->Main_Data;
}

void SimpleHash::insert(Tuple *sample) {
    int key;
    if (!key_type){
        key = sample->get_Treatment();
        this->Main_Data[key]->push_back(sample);
    }
    if (key_type == 1){
        key = sample->get_medic();
        this->Main_Data[key]->push_back(sample);
    }
    if (key_type == 2){
        key = sample->get_registration();
        this->Main_Data[key]->push_back(sample);
        // the Registry info is start at 1 because the data is stand for hospital number.
    }
    else{
        return;
    }
}

void SimpleHash::remove(Tuple *sample) {
    int key;
    if(!key_type){
        key = sample->get_Treatment();
    }
    if(key_type == 1){
        key = sample->get_medic();
    }
    if(key_type == 2){
        key = sample->get_registration();
    }
    for (int i=0;i<(*Main_Data[key]).size();i++){
        if ((*Main_Data[key])[i]==sample){
            Main_Data[key]->erase(Main_Data[key]->begin()+i);
            break;
        }
    }
}

vector<Tuple *> * SimpleHash::Find_key(int key) {
    int index = key;
    return Main_Data[index];
}

void SimpleHash::Sort(int key) {
    // sorted by primary key.
    // use swap sort.
    int index = key;
    auto obj = Main_Data[index];

    for (int i = 0;i<obj->size();i++){
        for (int j=0;j<obj->size();j++){
            if ((*obj)[i]->get_id() > (*obj)[j]->get_id()){
                Tuple* temp = (*obj)[i];
                (*obj)[i] = (*obj)[j];
                (*obj)[j] = temp;
            }
        }
    }
}
