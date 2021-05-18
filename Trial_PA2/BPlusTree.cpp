
#include "BPlusTree.h"


// find the block which may contain the key in the tree
BPnode *BPtree::find_parent(int k) {
    return root->find_parent(k);
}

// find block from a node
BPnode *BPnode::find_parent(int k) {
    // if k is in the root, return root
    int i = s-1;
    if (leaf == true) {
        return this;
    }
    // not in leaf-->recursion
    else {
        while (i>=0 && k<this->k[i]) {i--;}
        // recursievely searching
        BPnode *result = child[i+1]->find_parent(k);
        if ((child[i+1]->leaf == true) && (result == child[i+1])) {return this;}
        else {return result;}
    }
}

// find the block which may contain the key in the tree
block *BPtree::find_blk(int k) {
    return root->find_blk(k);
}

// find block from a node
block *BPnode::find_blk(int k) {
    int i = s-1;
    if (leaf == true) {
        while (i>=0 && k<this->k[i]) {
            i--;
        }
        //cout << i+1 << endl;
        return blk[i+1];
    }
    // not in leaf-->recursion
    else {
        if (k == 2475) {
            k = 2475;
        }
        while (i>=0 && k<this->k[i]) {i--;}
        return child[i+1]->find_blk(k);
    }
}

// not find-->return nullptr; find-->return the tuple contain the key
Tuple *BPtree::retrieve(int k) {
    // first, find the block
    block *blk = new block;
    // can never fail, empty tree?
    blk = find_blk(k);
    
    // check whether the key is in the block or not and return
    Tuple *tpl = new Tuple;
    tpl = blk->find(k); // binary search in the main block and linear search in the overflow block
    return tpl; // ?? assign nullptr to tpl?
}

void BPtree::insert(int k, Tuple &tuple) {
    if (root == nullptr) {
        BPnode *root = new BPnode();
        this->root = root;
        root->blk[0]->insert(tuple); // & and *, not sure
    }
    
    // first, find the block
    block *blk = new block;
    blk = find_blk(k);
    if ((blk == nullptr) || (blk->main == nullptr)) {blk = new block;}
    
    // case 1, if the block is full
    // if the number of tuples in (block and the overflow block) = max size
    // merge the block and the overflow block, and split
    if (blk->num_main+blk->num_over >= blk->main_size) {
        blk->sort();
        // split the block
        int half = blk->main_size/2;
        block *newblk = new block(); //?? what is the size
        Tuple h = blk->main[half];
        int split = h.get_id();
        for (int i = half; i < blk->num_main; i++) {
            newblk->insert(blk->main[i]);
        }
        blk->num_main = half;
        
        // insert the new tuple
        // insert into the old block
        if (k < split) {
            blk->insert(tuple);
        }
        // insert into the new block
        else {
            newblk->insert(tuple);
        }
    
        // add the key to the parent node
        BPnode *parent = find_parent(k);
        // if parent is full, split the parent, and redirected the pointer parent
        if (parent->s == 2*t-1) {
            parent = this->node_split(parent, k);
            return;
        }
         
        // if parent is not full, just find the correct position
        // insert the key at the first position
        if ((split < parent->k[0]) || (parent->s == 0)){
            parent->s++;
            for (int i = 1; i < parent->s; i++) {
                parent->k[i] = parent->k[i-1];
                parent->blk[i] = parent->blk[i-1];
            }
            parent->k[0] = split;
            parent->blk[0] = blk;
            parent->blk[1] = newblk;
            return;
        }
        // insert the key not at the first or last
        for (int j = 0; j < parent->s-1; j++) {
            if ((split >= parent->k[j])&&(split < parent->k[j+1])) {
                parent->s++;
                for (int i = j+1; i < parent->s; i++) {
                    parent->k[i] = parent->k[i-1];
                    parent->blk[i] = parent->blk[i-1];
                }
                parent->k[j] = split;
                parent->blk[j] = blk;
                parent->blk[j+1] = newblk;
                return;
            }
        }
        // still not return means split is larger than every key in parent
        parent->s++;
        parent->k[parent->s-1] = split;
        parent->blk[parent->s-1] = blk;
        parent->blk[parent->s] = newblk;

        
    }
    
    // case 2, insert the tuple into the overflow block
    blk->insert(tuple);
    

    return;
    
}

// return the node the key should be inserted
BPnode *BPtree::node_split(BPnode *node, int k) {
    // split the node
    int half = node->t;
    // if the node is the root
    if ((node == this->root) && (node->leaf == true)) {
        BPnode *newnode = new BPnode(); //?? parameter
        // split half of the keys and block pointers into the new node
        for (int i = half; i < node->t*2-1; i++) {
            newnode->k[i-half] = node->k[i];
            // using for test
            //if (node->blk[i] != 0) {cout << "exist";}
            //newnode->blk[i-half] = new block;
            newnode->blk[i-half] = node->blk[i];
            newnode->s++;
        }
        node->s = half;
        
        // create the new root
        BPnode *root = new BPnode(50, false);
        root->k[0] = node->k[half];
        root->child[0] = node;
        root->child[1] = newnode;
        this->root = root;
        root->s++;
        
        // return the node the key should be inserted
        if (k < newnode->k[0]) {return node;}
        else {return newnode;}
    }
    
    // if the node's parent is root
    if ((find_parent(node->k[0]) == this->root) && (node->leaf == true)) {
        BPnode *newnode = new BPnode(); //?? parameter
        // split half of the keys and block pointers into the new node
        for (int i = half; i < node->t*2-1; i++) {
            newnode->k[i-half] = node->k[i];
            // using for test
            //if (node->blk[i] != 0) {cout << "exist";}
            newnode->blk[i-half] = new block(50);
            newnode->blk[i-half] = node->blk[i];
            newnode->s++;
        }
        node->s = half;
        
        // insert the half key into the root

        root->k[1] = node->k[half];
        root->child[1] = node;
        root->child[2] = newnode;
        root->s++;
        
        // return the node the key should be inserted
        if (k < newnode->k[0]) {return node;}
        else {return newnode;}
    }

    cout << "too many records!" << endl;
    /*
    // if the node is not the root
    // add the key to the parent node
    BPnode *parent = find_parent(k);
    // if parent is full, split the parent, and redirected the pointer parent
    if (parent->s == 2*t-1) {
        parent = this->node_split(parent, k, newblk);
    }
     
    // if parent is not full, just find the correct position
    // insert the key at the first position
    if (split < parent->k[0]){
        parent->s++;
        for (int i = 1; i < parent->s; i++) {
            parent->k[i] = parent->k[i-1];
            parent->blk[i] = parent->blk[i-1];
        }
        parent->k[0] = split;
        parent->blk[0] = blk;
        parent->blk[1] = newblk;
        return;
    }
    // insert the key not at the first or last
    for (int j = 0; j < parent->s-1; j++) {
        if ((split >= parent[j])&&(split < parent[j+1])) {
            parent->s++;
            for (int i = j+1; i < parent->s; i++) {
                parent->k[i] = parent->k[i-1];
                parent->blk[i] = parent->blk[i-1];
            }
            parent->k[j] = split;
            parent->blk[j] = blk;
            parent->blk[j+1] = newblk;
            return;
        }
    }
    // still not return means split is larger than every key in parent
    parent->s++;
    parent->k[s-1] = split;
    parent->blk[s-1] = blk;
    parent->blk[s] = newblk;

    }*/

    return nullptr;
}

void BPtree::remove(int k) {
    //check all the leaf node linearly...
    return;
}