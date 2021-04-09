// This file contains the class functions of CentralQueue and FibHeap

#include "FibHeap.h"

// following are functions of CentralQueue
// constructor, generate the 4 heaps
// fib_heap is for normal people, priority_heap is for those with priority letters,
// waiting_heap is for medium-risk people and withdraw, high_risk_heap is for high-risk people
template <class T> CentralQueue<T>::CentralQueue() {
    fib_heap = new FibHeap<T>;
    priority_heap = new FibHeap<T>;
    waiting_heap = new FibHeap<T>;
    high_risk_heap = new FibHeap<T>;
    return;
}

// set date every day. date = the date of tomorrow
// after update the date, check waiting_heap,
// those people with medium risk and ever withdrew are in waiting_heap
template <class T> void CentralQueue<T>::set_date(int date) {
    // set date; date is the date of tomorrow
    this->date = date;
   
    int *key_ptr = new int;
    if (0 == waiting_heap->minimum(key_ptr)) {
        delete key_ptr;
        return; // bool minimum() returns 0, NULL poiter, set_date finish
    }
    
    // check whether someone should exit the waiting_heap or not
    while ((nullptr != key_ptr) && (waiting_heap->keyNum != 0) && (date >= *key_ptr)) {
        FibNode<T> *node_ptr;
        // remove the node from the waiting heap; reset the key; insert the node into fib_heap
        node_ptr = waiting_heap->removeMin();
        node_ptr->key = node_ptr->priority;
        fib_heap->insert(node_ptr);
        waiting_heap->minimum(key_ptr);
    }
    if (key_ptr != nullptr) {delete key_ptr;}
}

// transfer the data from reg_node to fib_node
template <class T> void CentralQueue<T>::transfer_in(Reg_Node *reg_node, FibNode<T> *fib_node) {
    fib_node->ID = reg_node->ID;
    fib_node->name = reg_node->name;
    fib_node->profession = reg_node->profession;
    fib_node->age_group = reg_node->age_group;
    fib_node->risk = reg_node->risk;
    fib_node->location = reg_node->location;
    fib_node->queTime = reg_node->queTime;
    
    fib_node->WeChat = reg_node->WeChat;
    fib_node->QQ = reg_node->QQ;
    fib_node->E_mail = reg_node->E_mail;
    fib_node->phone = reg_node->phone;
    fib_node->Birthday = reg_node->Birthday;
    
    fib_node->priority = reg_node->standard_priority;
    fib_node->ddl = reg_node->ddl;
    
    fib_node->TreatDay = reg_node->TreatDay;
    fib_node->RegData = reg_node->RegData;
    fib_node->Reg_Day = reg_node->Reg_Day;
    
    fib_node->stat = reg_node->stat; // if the person ever withdrew, stat = withdraw
    
}

// transfer the data from fib_node to reg_node
template <class T> void CentralQueue<T>::transfer_out(Reg_Node *reg_node, FibNode<T> *fib_node) {
    reg_node->ID = fib_node->ID;
    reg_node->name = fib_node->name;
    reg_node->profession = fib_node->profession;
    reg_node->age_group = fib_node->age_group;
    reg_node->risk = fib_node->risk;
    reg_node->location = fib_node->location;
    reg_node->queTime = fib_node->queTime;
    
    reg_node->WeChat = fib_node->WeChat;
    reg_node->QQ = fib_node->QQ;
    reg_node->E_mail = fib_node->E_mail;
    reg_node->phone = fib_node->phone;
    reg_node->Birthday = fib_node->Birthday;
    
    reg_node->standard_priority = fib_node->priority;
    reg_node->ddl = fib_node->ddl;
    
    reg_node->TreatDay = fib_node->TreatDay;
    reg_node->RegData = fib_node->RegData;
    reg_node->Reg_Day = fib_node->Reg_Day;
    
    reg_node->stat = fib_node->stat; // if the person ever withdrew, stat = withdraw
}

// transfer the data from local registry to center
// the input is *Reg_Node. call this function will generate a node in the FibHeap
template <class T> void CentralQueue<T>::record_in(Reg_Node *reg_node) {
    if (reg_node == nullptr) {return;}
    
    FibNode<int> *fib_node = new FibNode<int>(0);
    transfer_in(reg_node, fib_node);
    
    // for those who has a priority letter, go to the priority_heap
    if (0 != fib_node->ddl) {
        fib_node->key = fib_node->ddl; // the key in the priority_heap is ddl
        priority_heap->insert(fib_node);
    }
    
    // for those who has high risk, go to the high_risk_heap
    else if (3 == fib_node->risk) {
        fib_node->key = fib_node->priority; // the key in the high_risk_heap is priority
        high_risk_heap->insert(fib_node);
    }
    
    // for those who has medium risk, go to waiting_heap and waiting a month(30 days)
    else if (2 == fib_node->risk) {
        // waiting date = Reg_Day + 30
        fib_node->waiting_date = fib_node->Reg_Day + 30;
        fib_node->key = fib_node->waiting_date; // the key in the waiting heap is waiting_date
        waiting_heap->insert(fib_node);
    }
    
    // for those who ever withdrew, go to waiting_heap and waiting 2 weeks(14 days)
    else if (fib_node->stat == withdraw) {
        // waiting date = Reg_Day + 14
        fib_node->waiting_date = fib_node->Reg_Day + 14;
        fib_node->key = fib_node->waiting_date; // the key in the waiting heap is waiting_date
        waiting_heap->insert(fib_node);
    }
    
    // for normal people, these people go to the fib_heap
    else {
        fib_node->key = fib_node->priority; // the key in the fib_heap is priority
        fib_heap->insert(fib_node);
    }
    
    fib_node->stat = waiting; // in fibheap, stat is only changed here !!
}

// pop a minimum node. it will return a pointer to the node.
// if there is no node, it will return a NULL pointer
// the order of pop is priority_heap > fib_heap > waiting_heap > high_risk_heap
template <class T> Reg_Node *CentralQueue<T>::record_out() {
    FibNode<T> *fib_node = nullptr;
    // check priority_heap
    if (0 != priority_heap->keyNum) {
        fib_node = priority_heap->removeMin();
    }
    
    // check fib_heap
    else if (0 != fib_heap->keyNum) {
        fib_node = fib_heap->removeMin();
    }
    
    // check waiting_heap
    else if (0 != waiting_heap->keyNum) {
        fib_node = waiting_heap->removeMin();
    }
    
    // check high_risk_heap
    else if (0 != high_risk_heap->keyNum) {
        fib_node = high_risk_heap->removeMin();
    }
    
    
    // if not find the node, return NULL
    if (fib_node == nullptr) {
        Reg_Node *reg_node = nullptr;
        return reg_node;
    }
    
    // transfer the data from the fibonacci node to the registry node
    Reg_Node *reg_node = new Reg_Node;
    transfer_out(reg_node, fib_node);
    
    if (fib_node != nullptr) {delete fib_node;} // release the space
    return reg_node; // considering ptr == NULL
}

// search the node with key and ID in all 4 heaps. return a pointer to the node; if not find, return NULL
template <class T> void CentralQueue<T>::search_node(Reg_Node *reg_node, FibHeap<T> **heap, FibNode<T> **fib_node) {
    FibNode<T> *root_node;
    // FibNode<T> *target = NULL;
    //fib_node = NULL;
    int key, ID;
    ID = reg_node->ID;
    // search the 4 fibheap in turn
    if (reg_node->ddl != 0) {
        key = reg_node->ddl;
        root_node = priority_heap->min;
        *fib_node = priority_heap->id_search(root_node, key, ID);
        if (*fib_node != nullptr) {*heap = priority_heap;}
    }
    
    // search the node in the fib_heap
    if (*fib_node == nullptr) {
        key = reg_node->standard_priority; // the priority should not change!!
        root_node = fib_heap->min;
        *fib_node = fib_heap->id_search(root_node, key, ID);
        if (*fib_node != nullptr) {*heap = fib_heap;}
    }
    
    // search the node in the waiting heap
    if (*fib_node == nullptr) {
        if (reg_node->risk == 2) {key = reg_node->Reg_Day + 30;} // the risk should not change!!
        else {key = reg_node->Reg_Day + 14;}
        root_node = waiting_heap->min;
        *fib_node = waiting_heap->id_search(root_node, key, ID);
        if (*fib_node != nullptr) {*heap = waiting_heap;}
    }
    
    if ((*fib_node == nullptr) && (reg_node->risk == 3)) {
        key = reg_node->standard_priority;
        root_node = high_risk_heap->min;
        *fib_node = high_risk_heap->id_search(root_node, key, ID);
        if (*fib_node != nullptr) {*heap = high_risk_heap;}
    }
    return;
}

// the priority change due to profession should be done after this function!!
template <class T> void CentralQueue<T>::change_profession(Reg_Node *reg_node) {
    FibNode<T> *fib_node = nullptr;
    FibHeap<T> *heap = nullptr;
    // search the node in the heap
    search_node(reg_node, &heap, &fib_node);
    // not find
    if (fib_node == nullptr) {return;}
    
    int old_profession = fib_node->profession;
    fib_node->profession = reg_node->profession;
    
    reg_node->standard_priority = (reg_node->profession - 1) * 28 + (reg_node->age_group - 1) * 4 +fib_node->risk;
    if (old_profession <= fib_node->profession) {return;}
    fib_node->priority = reg_node->standard_priority;
    heap->decrease(fib_node, fib_node->priority);
    return;
}

template <class T> void CentralQueue<T>::withdraw_heap(Reg_Node *reg_node) {
    FibNode<T> *fib_node = nullptr;
    FibHeap<T> *heap = nullptr;
    // search the node in the heap
    search_node(reg_node, &heap, &fib_node);
    if (fib_node == nullptr) {return;}
    
    // change the status to withdraw, and remove the node
    fib_node->stat = withdraw;
    heap->remove(fib_node);
    return;
}

template <class T> int CentralQueue<T>::waiting_number() {
    return priority_heap->keyNum + fib_heap->keyNum + waiting_heap->keyNum + high_risk_heap->keyNum;
}

template <class T> void CentralQueue<T>::build_array(Reg_Node *a, FibNode<T> *root, int n) {
    //int len = waiting_number();
    FibNode<T> *tmp = root;    // temporary node
    //FibNode<T> *p = nullptr;    // target node

    if (root == nullptr)
        return; // protect the stability

    do
    {
        //ptr[n] = &root;
        a[n].name = root->name;
        a[n].profession = root->profession;
        a[n].age_group = root->age_group;
        a[n].risk = root->risk;
        a[n].queTime = date - root->Reg_Day;
        n++;
        
        if (root->child != nullptr){
            build_array(a, root->child, n);
            
            //break;
        }
        tmp = tmp->right;
        if (tmp != nullptr) {
            a[n].name = root->name;
            a[n].profession = root->profession;
            a[n].age_group = root->age_group;
            a[n].risk = root->risk;
            a[n].queTime = date - root->Reg_Day;
            n++;
        }
        
    } while (tmp != root);

    return;
}

template <class T> void CentralQueue<T>::sort(Reg_Node *a) {

    //static FibNode<T> *ptr = new FibNode<T>[len];
    // int len = waiting_number();
    // Reg_Node a[len];
    build_array(a, priority_heap->min, 0);
    build_array(a, fib_heap->min, priority_heap->keyNum);
    build_array(a, waiting_heap->min, priority_heap->keyNum + fib_heap->keyNum);
    build_array(a, high_risk_heap->min, priority_heap->keyNum + fib_heap->keyNum + waiting_heap->keyNum);
    
    return;
}






//---------------------------------------------------------------------------------
// Following are the functions of FibHeap
// constructor
template <class T> FibHeap<T>::FibHeap() {
    keyNum = 0;
    maxDegree = 0;
    min = nullptr;
    cons = nullptr;
}

// destructor
template <class T> FibHeap<T>::~FibHeap() { }

// remove node from the double link list
template <class T> void FibHeap<T>::removeNode(FibNode<T> *node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

// add node to the left of the root
template <class T> void FibHeap<T>::addNode(FibNode<T> *node, FibNode<T> *root) {
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

// insert node to the fibheap
template <class T> void FibHeap<T>::insert(FibNode<T> *node) {
    //FibNode<T> *node;

    //node = new FibNode<T>(key);
    if (node == nullptr)
        return ;
    
    if (keyNum == 0)
        min = node;
    else
       {
        addNode(node, min);
        if (node->key < min->key)
            min = node;
    }
    keyNum++;
}

// remove the min value node from the root list
template <class T> FibNode<T>* FibHeap<T>::extractMin() {
    FibNode<T> *ptr = min;

    if (ptr == ptr->right)
        min = nullptr;
    else
    {
        removeNode(ptr);
        min = ptr->right;
    }
    ptr->left = ptr->right = ptr;

    return ptr;
}

// link node to the root list
template <class T> void FibHeap<T>::link(FibNode<T>* node, FibNode<T>* root) {
    // remove node from the double link list
    removeNode(node);
    // set node as root's child
    if (root->child == nullptr)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

// create the space required for consolidate
template <class T> void FibHeap<T>::makeCons() {
    int old = maxDegree;

    // calculate log2(keyNum), considering rounding up
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

    // because the degree is maxDegree may be merged, so to maxDegree+1
    cons = (FibNode<T> **)realloc(cons,
            sizeof(FibHeap<T> *) * (maxDegree + 1));
}

// Merge trees of the same degree left and right in the root-linked table of the Fibonacci heap
template <class T> void FibHeap<T>::consolidate() {
    int i, degree, big_degree;
    FibNode<T> *x, *y;

    makeCons(); // create the space for hashing
    big_degree = maxDegree + 1;

    for (i = 0; i < big_degree; i++)
        cons[i] = nullptr;

    // merge root nodes of the same degree so that the tree of each degree is unique
    while (min != nullptr)
    {
        x = extractMin();                // fetch the smallest tree in the heap
        degree = x->degree;                    // get the degree of the smallest tree
        // cons[d] != NULL, means there are two trees with the same degree
        while (cons[degree] != nullptr)
        {
            y = cons[degree];                // y is a tree which has the same degree as x
            if (x->key > y->key)        // ensure that the key value of x is smaller than y
                swap(x, y);

            link(y, x);    // link y to x
            cons[degree] = nullptr;
            degree++;
        }
        cons[degree] = x;
    }
    min = nullptr;

    // re-add the nodes in cons to the root table
    for (i = 0; i < big_degree; i++)
    {
        if (cons[i] != nullptr)
        {
            if (min == nullptr)
                min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key)
                    min = cons[i];
            }
        }
    }
}

// remove the min node
template <class T> FibNode<T> *FibHeap<T>::removeMin() {
    if (min==nullptr)
        return nullptr;

    FibNode<T> *child = nullptr;
    FibNode<T> *move = min;
    // add min's child and its brothers to the root list
    while (move->child != nullptr)
    {
        child = move->child;
        removeNode(child);
        if (child->right == child)
            move->child = nullptr;
        else
            move->child = child->right;

        addNode(child, min);
        child->parent = nullptr;
    }

    // remove m from the root list
    removeNode(move);
    // if m is the only node in the heap, set the smallest node of the heap to NULL
    // otherwise, set the smallest node of the heap to a non-empty node (m->right), and then adjust it.
    if (move->right == move)
        min = nullptr;
    
    else {
        min = move->right;
        consolidate();
    }
    keyNum--;

    return move;
}

// Get the minimum key value in the Fibonacci heap and save it to the pkey; success returns true, otherwise returns false.
template <class T> bool FibHeap<T>::minimum(T *ptr) {
    if (min==nullptr || ptr==nullptr)
        return false;

    *ptr = min->key;
    return true;
}

// update degrees
template <class T> void FibHeap<T>::renewDegree(FibNode<T> *parent, int degree) {
    parent->degree -= degree;
    if (parent-> parent != nullptr)
        renewDegree(parent->parent, degree);
}

// strips the node from the parent parent's child links, and make the node a member of the root list of the heap.
template <class T> void FibHeap<T>::cut(FibNode<T> *node, FibNode<T> *parent) {
    removeNode(node);
    renewDegree(parent, node->degree);
    // node has no brothers
    if (node == node->right)
        parent->child = nullptr;
    else
        parent->child = node->right;

    node->parent = nullptr;
    node->left = node->right = node;
    node->marked = false;
    // add the node tree to the root list
    addNode(node, min);
}


/*
 * do cascading cut to the node
 *
 * Cascade cut: If the reduced node breaks the minimal heap property
 * then it is cut down (i.e., removed from the bidirectional linked table it is in and
 * it is inserted into the two-way linked table formed by the root node of the minimum tree).
 * then recursively perform cascade pruning from the "parent node of the cut node" to the root node of the tree
 */
template <class T> void FibHeap<T>::cascadingCut(FibNode<T> *node) {
    FibNode<T> *parent = node->parent;
    if (parent != nullptr)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

// Decrease the value of node node in the Fibonacci heap to key
template <class T> void FibHeap<T>::decrease(FibNode<T> *node, T key) {
    FibNode<T> *parent;

    if (min == nullptr ||node == nullptr)
        return ;

    if ( key>=node->key)
    {
        // cout << "new key is greater than current key" << endl;
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent != nullptr && node->key < parent->key)
    {
        // strip the node from its parent parent and add the node to the root chain table
        cut(node, parent);
        cascadingCut(parent);
    }

    // update the min node
    if (node->key < min->key)
        min = node;
}


// search the exact person recursively, according to the key and ID; if not find, return NULL
template <class T> FibNode<T>* FibHeap<T>::id_search(FibNode<T> *root, T key, int ID) {
    FibNode<T> *tmp = root;    // temporary node
    FibNode<T> *p = nullptr;    // target node

    if (root == nullptr)
        return root; // protect the stability

    do
    {
        if ((tmp->key == key) && (tmp->ID == ID))
        {
            p = tmp;
            break;
        }
        else
        {
            if ((p = id_search(tmp->child, key, ID)) != nullptr)
                break;
        }
        tmp = tmp->right;
    } while (tmp != root);

    return p;
}

// remove the node
template <class T> void FibHeap<T>::remove(FibNode<T> *node) {
    // set the key of the node to be the min
    T m = min->key-1;
    decrease(node, m-1);
    removeMin();
}





