//
// Created by jordan on 2021/5/11.
//

#include "RDB.h"

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
            high = middle+1;
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

/*-----------------------------------RDB part------------------------------------------*/

RDB::RDB(int block_size) {
    this->Medic = new vector<Tuple*>;
    this->TreatInfo = new SimpleHash(3,0); // Since we are deal with Treatment(0,1,2)
    this->Location = new BTree();
    this->division = new vector<int>;
    this->primary = new vector<block*>;
    this->block_size = block_size;
    this->num_block = 1;
    //now allocate the first block. '
    auto new_block = new block(block_size);
    primary->push_back(new_block);
    division->push_back(0);
}

int RDB::getlength() {
    return (int)this->Medic->size();
}
// for the insert part.

Tuple* RDB::insert(const Tuple &obj) {
    //insert by linear search.....
    int info = obj.get_id();
    int location = 0;
    Tuple* direct = nullptr;
    while((*this->division)[location]<info&&location<num_block-1){
        location++;
    }
    block* target = (*primary)[location];
    //now check if the block is full.
    direct = target->insert(obj);
    if (!direct){
        //the block is full...
        int result = DBsplit(location);
        if (info < result){
            direct = target->insert(obj);
        } else{
            location++;
            target = (*primary)[location];
            direct = target->insert(obj);
        }
    }
    //now update the division.
    if (!(*division)[location]||(*division)[location]>info){
        (*division)[location] = info;
    }
    // now update the secondary key.
    this->Medic->push_back(direct);
    // hash here.
    this->TreatInfo->insert(direct);
    // To be modified.
    this->Location->_insert(direct);

    if (direct){
    } else{
        cout<<"not inserted!"<<endl;
    }
    return direct;
}

// for the split part.
int RDB::DBsplit(int blocknum) {
    // first copy out the last part.....
    int half = block_size/2;
    block* current = (*primary)[blocknum];
    auto newblock = new block(this->block_size);
    Tuple h = current->main[half];
    int split = h.get_id();
    for (int i = half;i<current->num_main;i++){
        newblock->insert(current->main[i]);
    }
    current->num_main = half-1;
    // now modify the division vector.
    primary->insert(primary->begin()+blocknum+1,newblock);
    division->insert(division->begin()+blocknum+1,split);
    num_block++;
    return split;
}

//Delete operation.
void RDB::Delete(int id) {
    int location = 0;
    while((*this->division)[location]<id&&location<num_block-1){
        location++;
    }
    // call the delete.
    block* target = (*primary)[location];
    if (target->remove(id)){
        //check if the label tuple was deleted.
        if (id == (*division)[location]){
            int trial = id + 1;
            while (!target->find(trial)){
                trial++;
            }
            (*division)[location] = trial;
        }
        // now delete it from the secondary block.
        // a little hard to finish.
        // finally i think i should use a B+ tree to do ot.
        for (int i=0;i<Medic->size();i++){
            Tuple* temp = (*Medic)[i];
            if (temp->get_id() == id ){
                // to get the True location, we can only do this until the Bplus tree is done.
                TreatInfo->remove(temp);
                Location->_delete(temp);
                Medic->erase(Medic->begin()+i);
                break;
            }
        }

        // then start the merge operation.
        // before merge, you should sort it, to clear the trash.
        // now check if we should merge the block.
        if (target->num_main+target->num_over-target->Trash->size() <= this->block_size/10
        && this->num_block>1){
            if (location>=1) {
                this->DBmerge(location - 1, location);
            }
            else{
                this->DBmerge(location,location+1);
            }
        }
    }
}

// merge operation.
int RDB::DBmerge(int block1, int block2) {
    // how to activate merge?
    // i think it should activated from the delete operation.
    // so just make it run!
    int divide = 0;
    block* b1 = (*primary)[block1];
    block* b2 = (*primary)[block2];
    b1->sort();
    b2->sort();
    int total = b1->num_over + b2->num_over + b1->num_main + b2->num_main;
    // situation 1 : merge two to only one.
    if (total < this->block_size){
        for (int i = 0;i<b2->num_main;i++){
            b1->main[i+b1->num_main] = b2->main[i];
        }
        b1->num_main += b2->num_main;
        // then delete the indicator in division, and delete the pointer from the primary.
        primary->erase(primary->begin()+block2-1);
        division->erase(division->begin()+block2-1);
        this->num_block--;
    } else{
    //situation 2 : make two block balance.
        // ter method is merging a smaller one after a larger one(because we are operate in array...
        // but here we shall use a much slower one....
        auto newarray = new Tuple[this->block_size];
        if (b1->num_main<total/2){
            int num_move = total/2 - b1->num_main;
            int counter = 0;
            for (int i = 0;i<b2->num_main;i++) {
                if (i < num_move) {
                    b1->main[i + b1->num_main] = b2->main[i];
                } else {
                    newarray[counter] = b2->main[i];
                    counter++;
                }
            }
                // then update the information.
                //1. the num_item.
                b1->num_main += num_move;
                b2->num_main -= num_move;
                delete b2->main;
                b2->main = newarray;
                //2. the division block.
                Tuple first = newarray[0];
                divide = first.get_id();
            (*division)[block2] = first.get_id();
        } else{
            // now the b1 have more elements than b2.
            int num_move = total/2 - b2->num_main;
            int counter = 0;
            for (int i=total/2;i<b1->num_main;i++){
                    newarray[counter] = b1->main[i];
                    counter++;
            }
            for (int i=0;i<b2->num_main;i++){
                newarray[counter] = b2->main[i];
                counter++;
            }
            // then update the pointers.
            // 1. the num items.
            b1->num_main = total/2;
            b2->num_main = counter;
            delete b2->main;
            b2->main = newarray;
            //2. the division block.
            Tuple first = newarray[0];
            divide = first.get_id();
            (*division)[block2] = first.get_id();
        }
    }
    return divide;
}

// the sorting part!!!
//1. the primary key......it seems we do not need to sort it.
//2. the secondary key.......
void RDB::swap_sort(vector<Tuple *>* obj) {
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

void RDB::MedicSort() {
    // basically based on Radix sort.
            //sorted with secondary key "Medic"
            auto target = this->Medic;
            // there's 4 medical status, so i will create 4 bucket.
            vector<Tuple*> A,B,C,D;
            for (auto temp:*target){
                if (temp->get_medic() == 0){
                    A.push_back(temp);
                }
                if (temp->get_medic() == 1){
                    B.push_back(temp);
                }
                if (temp->get_medic() == 2){
                    C.push_back(temp);
                }
                if (temp->get_medic() == 3){
                    D.push_back(temp);
                }
            }
            // now sort all the 4 bucket.
            swap_sort(&A);
            swap_sort(&B);
            swap_sort(&C);
            swap_sort(&D);
            target->clear();
            // push them back to the list;
            for (auto i : A){
                target->push_back(i);
            }
            for (auto i:B ){
                target->push_back(i);
            }
            for (auto i:C ){
                target->push_back(i);
            }
            for (auto i:D ){
                target->push_back(i);
            }
            // now the sort was complete.
}

void RDB::TreatSort() {
    TreatInfo->Sort(0);
    TreatInfo->Sort(1);
    TreatInfo->Sort(2);
}

//retrieval part!!!
//1. primary key.
Tuple * RDB::find_ID(int id) {
    if (id < (*this->division)[0]){
        return nullptr;
    }
    int location = 0;
    while((*this->division)[location]<id&&location<num_block-1){
        location++;
    }
    block* target = (*primary)[location];
    return target->find(id);
}

//2. secondary key part.
// all the operation should mentioned to the secondary key part.
// so you should modify the previous functions.
vector<Tuple *> * RDB::find_Medic(int medic) {
    auto result = new vector<Tuple*>;
    this->MedicSort();
    for (auto temp : *Medic){
        if (medic == temp->get_medic()){
            result->push_back(temp);
        }
    }
    return result;
}

vector<Tuple *> * RDB::find_Reg(int location) {
    auto result = new vector<Tuple*>;
    for (auto temp:*Registration){
        if (location == temp->get_registration()){
            result->push_back(temp);
        }
    }
    return result;
}

vector<Tuple *> * RDB::find_Treatment(int t_type) {
    TreatSort();
    return TreatInfo->Find_key(t_type);
}

vector<Tuple *> * RDB::cheat() {
    return this->Medic;
}
