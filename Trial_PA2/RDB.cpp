//
// Created by jordan on 2021/5/11.
//

#include "RDB.h"

//block
block::block(int size = 50) {
    // the main block will be 10 times larger than the overflow block.
    // the initial size will be 50.
    this->main = new Tuple[size];
    this->overflow = new Tuple[size/10];
    this->Trash = new vector<int>;

    this->main_size = size;
    this->num_main = 0;
    this->num_over = 0;
}

int block::insert(const Tuple &obj) {
    if (num_main+num_over>=main_size){
        sort();
        // when the insert is fail, just split them into two new block.
        // the operation is finished outside.
        return 0;
    }
    if (num_over>=main_size/10){
        // the overflow is full....
        sort();
    }
    Tuple newtuple = Tuple(obj);
    overflow[this->num_over] = newtuple;
    return 1;
}

void block::sort() {
    //use simple sort: swap sort;
    // fact: the main stack is already sorted, just insert the overflow to the main.
    // however, the main block is an array......
    auto temparray = new Tuple[main_size];
    // first we can sort the overflow stack.
    for (int i = 0;i<num_over-1;i++){
        for (int j=i+1;j<num_over;j++){
            Tuple temp = num_over[j];
            Tuple smaller = overflow[i];
            if (temp.get_id()<smaller.get_id()){
                verflow[i] = temp;
                overflow[j] = smaller;
            }
        }
    }
    //then the overflow is sorted.
    int mcounter = 0;
    int ocounter = 0;
    int counter = 0;
    while (counter<num_over+num_main-Trash->size()){
        if (mcounter>=num_main||ocounter>=num_over){
            if (mcounter>=num_main) {
                Tuple o = overflow[ocounter];
                if (this->inTrash(o.get_id())){
                    ++ocounter;
                }
                else {
                    temparray[counter] = o;
                    ++ocounter;
                    ++counter;
                }
            } else{
                Tuple m = main[mcounter];
                if (this->inTrash(m.get_id())){
                    ++mcounter;
                } else {
                    temparray[counter] = m;
                    ++mcounter;
                    ++counter;
                }
            }
        }
        else{
            Tuple m = main[mcounter];
            Tuple o = overflow[ocounter];
            if (this->inTrash(m.get_id())){
                ++mcounter;
            }
            if (this->inTrash(o.get_id())){
                ++ocounter;
            }
            else {
                if (m.get_id() < o.get_id()) {
                    temparray[counter] = m;
                    ++mcounter;
                    ++counter;
                } else {
                    temparray[counter] = o;
                    ++ocounter;
                    ++counter;
                }
            }
        }
    }
    //now all the item is move to the temp array.
    delete this->main;
    this->main = temparray;
    this->num_over = 0;
    this->num_main = counter;
    return;
}

int block::Full() {
    if (num_over+num_main >= main_size){
        sort();
        return 0;
    }
    else{
        return 1;
    }
}

Tuple * block::find(int id) {
    // first we should find the id in the main block by binary search.
    int low = 0;
    int high = num_main-1;
    while (low<=high){
        int middle = (low+high)/2;
        Tuple m = main[middle];
        if (m.get_id()==id){
            return &m;
        }
        else if (id>m.get_id()){
            low = middle+1;
        }
        else if (id < m.get_id()){
            high = middle+1;
        }
    }
    // not found
    // then we should find in overflow block.
    for (int i = 0;i<num_over;i++){
        Tuple m = overflow[i];
        if (m.get_id()==id) {
            return &m;
        }
    }
    // finally not found.
    return nullptr;
}

int block::remove(int id) {
    if (this->find(id)) {
        Trash->push_back(id);
        return 1;
    } else{
        return 0;
    }
}
int block::inTrash(int id) {
    for (int i=0;i<Trash->size();i++){
        if((*Trash)[i] == id){
            return 1;
        }
    }
    return 0;
}


/*-----------------------------------RDB part------------------------------------------*/

RDB::RDB(int block_size) {
    this->Medic = new vector<Tuple*>;
    this->Treatment = new vector<Tuple*>;
    this->Registration = new vector<Tuple*>;
    this->division = new vector<int>;
    this->primary = new vector<block*>;
    this->block_size = block_size;
    this->num_block = 0;
}

// for the insert part.

void RDB::insert(const Tuple &obj) {

}

// for the split part.
int RDB::DBsplit(int blocknum) {
    // first copy out the last part.....
    int half = block_size/2;
    block* current = primary[blocknum];
    auto newblock = new block(this->block_size);
    Tuple h = current->main[half];
    int split = h.get_id();
    for (int i = half;i<current->num_main;i++){
        newblock->insert(current->main[i]);
    }
    current->num_main = half-1;
    // now modify the division vector.
    division->insert(division->begin()+blocknum+1,split);
    return split;
}