#ifndef BPTREE_H
#define BPTREE_H

#include "block.h"

using namespace std;

class BPnode
{
    friend int main();
	int *k; // key
	BPnode **child; // if at leaf node, this is NULL
    block **blk; // if at leaf node, this is not NULL
	int s; // number of keys; with s+1 children
	int t; // order
    bool leaf;
    BPnode *left; // use for leaf node
    BPnode *ritht; // use for leaf node
    block *find_blk(int k);
    BPnode *find_parent(int k);
public:
	BPnode(int t=50, bool leaf=true)
    {
		this->t = t;
		this->leaf = leaf;
		k = new int[2*t-1];
        if (leaf == true) {
            blk = new block*[2*t];
            blk[0] = new block;
        }
        else {
            child = new BPnode*[2*t];
            //child[0] = new BPnode;
        }
		s = 0;
    }
	
friend class BPtree;
};



class BPtree
{
    friend int main();
	BPnode* root;
	int t; // the number of nodes in the tree
    block *find_blk(int k); // find the block perhaps contain the key
    BPnode *find_parent(int k); // find the parent of k, assume k is in the tree
    BPnode *node_split(BPnode *node, int k); //return the node which key should be inserted in
    BPnode *merge(BPnode *node1, BPnode *node2);
public:
	BPtree(int t)
    {
		root = new BPnode(t,true);
		this->t = t;
    }
	void insert(int k, Tuple &tuple);
    Tuple *retrieve(int k);
	void remove(int k);
    
    
};

#endif
