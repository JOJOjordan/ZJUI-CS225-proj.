//
// Created by jordan on 2021/5/11.
//

#ifndef TRIAL_PA2_RDB_H
#define TRIAL_PA2_RDB_H

#include "SimpleHash.h"
#include "B_tree.h"
#include "BPlusTree.h"
#include "block.h"

using namespace std;

class RDB {
//the relation are fixed. if you want to add more relation, please just QWQ.
// all the relation are claimed below:
//      primary key: ID;
//      secondary key: Medic_status, Registrations, Treatment type;

// data storage:
// ID: Bplus tree. Only can use retrieve.
// Medic: vector (Array). low efficiency.
// Location: Btree, stored pointer to the block,
// Treatment: Hash, only 3 in this templates.

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

    int DBsplit(int blocknum);
    int DBmerge(int block1,int block2);//return 0 for merge 2 block to one. return k shows that the
    /*the two new block was split at k. */
    // think: how to merge them???


private:
    // the sort algorithm is defined here.
    vector<Tuple*>* Medic;
    SimpleHash* TreatInfo;
    BTree* Location;
    BPtree* ID;
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
