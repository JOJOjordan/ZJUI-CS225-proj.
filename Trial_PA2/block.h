//
// Created by jordan on 2021/5/18.
//

#ifndef TRIAL_PA2_BLOCK_H
#define TRIAL_PA2_BLOCK_H

#include "Tuple.h"

using namespace std;

class block{

    // it is a trial version of block. I still dont know what to store in the block.
    // however, we do not need to deal with multiple structures, so i can finish it here,
    // because we do not need to build a template class.
    // possible solution:
    // 1. a pointer.
    // 2. only the main block can store the true tuple. other block should store the
    //    pointers.
    // 3. all the block chain can store the tuple.
    // this version I would like to try the second one.
    friend class RDB;
    friend class BPtree;
    friend class BPnode;


public:
block(int size = 50);
// ~block();
// we should use array: it is a block of memory finally.
Tuple* insert(const Tuple &obj); // 1 for success. 0 for full.
int Full(); // same as above, 0 for full.
Tuple* find(int id); // nullptr for not found.
int remove(int id); // 1 for removed, 0 for not found/

// return the true memory location instead of a pointer.
private:
Tuple* main;
Tuple* overflow;
int num_main;
int main_size;
int num_over;
vector<int>* Trash;
// utility function for block maintain
void sort();
int inTrash(int id); // 1 for in, 0 for not.

};



#endif //TRIAL_PA2_BLOCK_H
