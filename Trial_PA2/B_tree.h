#ifndef BTREE_H
#define BTREE_H

#include "Tuple.h"
using namespace std;

static const int m = 3;  
static const int key_max = 2*m-1;
static const int key_min = m - 1;
static const int child_max = key_max + 1;
static const int child_min = key_min + 1;

// Modified the B tree to hold Tuple.


class BTnode
{
    friend class BTree;
public:
	  BTnode(void);
private:
    bool isleaf;
    int keyNum;
    BTnode* parent;
    BTnode* pchild[child_max];
    Tuple* keyvalue[key_max];
};
 

class BTree
{
public:
    BTree();
    bool _insert(Tuple* value);
    void SplitBlock(BTnode* node_parent,int child_index,BTnode* node_child);
    void Notfull_insert(BTnode* node,Tuple* value);
    bool contain(Tuple* value);

    void _printpoint(BTnode* node,int count);
    void printpoint(void);

    bool _delete(Tuple* value);
    BTnode* _find(BTnode* node,Tuple* value);
    void MergeBlock(BTnode* node_parent,int child_index);
    Tuple* getprev(BTnode* node);
    Tuple* getnext(BTnode* node);
    void BTree_deletebalance(BTnode* node,Tuple* value);

private:
	  BTnode* root;
};
#endif