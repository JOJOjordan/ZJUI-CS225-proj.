//
// Created by jordan on 2021/5/18.
//

#include "block.h"


//block
block::block(int size) {
    // the main block will be 10 times larger than the overflow block.
    // the initial size will be 50.
    this->main = new Tuple[size];
    this->overflow = new Tuple[size/10];
    this->Trash = new vector<int>;

    this->main_size = size;
    this->num_main = 0;
    this->num_over = 0;
}

Tuple* block::insert(const Tuple &obj) {
    if (num_main+num_over>=main_size){
        sort();
        // when the insert is fail, just split them into two new block.
        // the operation is finished outside.
        return nullptr;
    }
    if (num_over>=main_size/10){
        // the overflow is full....
        sort();
    }

    auto newtuple = new Tuple(obj);
    overflow[this->num_over] = *newtuple;
    num_over++;
    return newtuple;
}

void block::sort() {
    //use simple sort: swap sort;
    // fact: the main stack is already sorted, just insert the overflow to the main.
    // however, the main block is an array......
    auto temparray = new Tuple[main_size];
    // first we can sort the overflow stack.
    for (int i = 0;i<num_over-1;i++){
        for (int j=i+1;j<num_over;j++){
            Tuple temp = overflow[j];
            Tuple smaller = overflow[i];
            if (temp.get_id()<smaller.get_id()){
                overflow[i] = temp;
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
    Trash->clear();
    this->main = temparray;
    this->num_over = 0;
    this->num_main = counter;
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
            return &main[middle];
        }
        else if (id>m.get_id()){
            low = middle+1;
        }
        else if (id < m.get_id()){
            high = middle-1;
        }
    }
    // not found
    // then we should find in overflow block.
    for (int i = 0;i<num_over;i++){
        Tuple m = overflow[i];
        if (m.get_id()==id) {
            return &overflow[i];
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
    for (auto i:*Trash){
        if(i == id){
            return 1;
        }
    }
    return 0;
}
