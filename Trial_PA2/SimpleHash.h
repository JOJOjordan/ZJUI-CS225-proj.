//
// Created by jordan on 2021/5/16.
//

#ifndef TRIAL_PA2_SIMPLEHASH_H
#define TRIAL_PA2_SIMPLEHASH_H
#include "Tuple.h"

using namespace std;

class SimpleHash {
public:
    SimpleHash(int length = 3,int type = 0);
    ~SimpleHash(); // to free the hash vector.....they are not contained in this class.
    void insert(Tuple* sample); // There we assume that the key is Treatment. Or we can add more.
    void remove(Tuple* sample);
    vector<Tuple*>* Find_key(int key);
    void Sort(int key); // sort by primary key.

private:
    vector<vector<Tuple* >*> Main_Data;
    int key_type;
};


#endif //TRIAL_PA2_SIMPLEHASH_H
