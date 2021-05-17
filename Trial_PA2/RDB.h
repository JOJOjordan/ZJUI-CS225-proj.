//
// Created by jordan on 2021/5/11.
//

#ifndef TRIAL_PA2_RDB_H
#define TRIAL_PA2_RDB_H
#include "Tuple.h"
#include "SimpleHash.h"
#include "B_tree.h"

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

class RDB {
//the relation are fixed. if you want to add more relation, please just QWQ.
// all the relation are claimed below:
//      primary key: ID;
//      secondary key: Medic_status, Registrations, Treatment type;
public:
    RDB(int block_size = 50);
    //~RDB();
    Tuple* insert(const Tuple &obj);
    void Delete(int id);
    Tuple* find_ID(int id);
    int getlength();
    // the secondary key is sorted by primary key when they have same value.
    // the pointer are supporting direct find.
    vector<Tuple*>* find_Medic(int medic);
    vector<Tuple*>* find_Reg(int location);
    vector<Tuple*>* find_Treatment(int t_type);
    vector<Tuple*>* cheat();

protected:
    // there we are discussing about database implement.
    // 1 for Medic, 2 for Treatment,3 for Registry.
    void MedicSort();
    void TreatSort();
    void RegSort();

    int DBsplit(int blocknum);
    int DBmerge(int block1,int block2);//return 0 for merge 2 block to one. return k shows that the
    /*the two new block was split at k. */
    // think: how to merge them???


private:
    // the sort algorithm is defined here.
    vector<Tuple*>* Medic;
    SimpleHash* TreatInfo;
    BTree* Location;
    vector<Tuple*>* Registration;
    vector<block*>* primary;
    vector<int>* division; // record the start id of each block.
    // maybe the primary key should use B tree instead.
    // the block should build together.
    int block_size;
    int num_block;

    // useful function in sorting.
    void swap_sort(vector<Tuple*>* obj);
};


#endif //TRIAL_PA2_RDB_H
