// This file contains the definition of three classes: CentralQueue, FibNode, FibHeap

#ifndef _FIB_HEAP_H
#define _FIB_HEAP_H

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Registry.h"

using namespace std;
template <class T> class FibNode;
template <class T> class FibHeap;

// CentralQueue is the class that other files need to call
// central queue contains four FibHeap, and some other functions
template <class T> class CentralQueue {
     // friend void test(); // !!
public:
    CentralQueue();
    // these are the functions needed in other files
    void set_date(int date); // date = the date of tomorrow. Those people with medium risk or withdraw may released.
    void record_in(Reg_Node *reg_node); // transfer the data from local registry to center
    Reg_Node *record_out(); // pop a "minimum" node
    void change_profession(Reg_Node *reg_node);
    void withdraw_heap(Reg_Node *reg_node);
    int waiting_number(); // return the number of people waiting in the heaps
    
    void sort(Reg_Node *a);
    // void fetch(vector<Reg_Node> *a);
    
private:
    int date; // tomorrow's date
    void transfer_in(Reg_Node *reg_node, FibNode<T> *fib_node); // transfer the data from reg_node to fib_node
    void transfer_out(Reg_Node *reg_node, FibNode<T> *fib_node); // transfer the data from fib_node to reg_node
    void search_node(Reg_Node *reg_node, FibHeap<T> **heap, FibNode<T> **fib_node); // search a node
    
    void build_array(Reg_Node *a, FibNode<T> *root, int n);
   //  void build_vecotr(vector<Reg_Node> *a, FibNode<T> *root, int n);
    
    FibHeap<T> *fib_heap; // the central queue
    FibHeap<T> *priority_heap; // people with priority letter will in this heap
    FibHeap<T> *waiting_heap; // for people with median risk or status = withdraw
    FibHeap<T> *high_risk_heap; // for people with high risk
};

// FibNode is the node in the Fibonacci Heap
template <class T> class FibNode {
    template <class X> friend class CentralQueue; // note the X here
    template <class Y> friend class FibHeap;
    // friend void test(); // !
public:
    T key; // sorting is based on key value
    int degree;
    FibNode<T> *left;
    FibNode<T> *right;
    FibNode<T> *child; // the first child of the node
    FibNode<T> *parent;
    bool marked; // whether the first child is deleted or not

    FibNode(T value):key(value), degree(0), marked(false),
        left(nullptr),right(nullptr),child(nullptr),parent(nullptr) {
        key    = value;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = nullptr;
        child  = nullptr;
    }
    
private:
    int ID;
    string name;
    int profession;
    int age_group;
    int risk;
    int location;
    int queTime;
    
    int priority;
    int ddl; // people with priority letter has a ddl
    int waiting_date; // the waiting_date in waiting_heap
    
    string WeChat;
    string QQ;
    string E_mail;
    string phone;
    string Birthday;
    
    status stat;
    
    int TreatDay;
    string RegData;
    int Reg_Day;
    
};

// Fibonacci Heap
template <class T> class FibHeap {
    template <class X> friend class CentralQueue; // note the X here
    // friend void test(); // !!
public:
    FibHeap();
    ~FibHeap();

    void insert(FibNode<T> *node); // insert a node into the root list
    FibNode<T>* removeMin(); // remove the min node from the heap
    void remove(FibNode<T> *node); // remove the node
    FibNode<T>* extractMin(); // remove the node with the minimum key, return a pointer to the node
    
    FibNode<T>* id_search(FibNode<T>* root, T key, int ID); // search the node according to key and id
    void decrease(FibNode<T> *node, T key); // Decrease the value of node node in the Fibonacci heap to key
    
    bool minimum(T *pkey); // Get the minimum key value in the Fibonacci heap and save it to the pkey; success returns true, otherwise returns false.


private:
    int keyNum;         // the number of nodes in the heap
    int maxDegree;      // the maximum degree
    FibNode<T> *min;    // a pointer to the minimum node
    FibNode<T> **cons;    // the memory area of the maximum degree
    
private:
    void removeNode(FibNode<T> *node); // remove node from the double link list
    void addNode(FibNode<T> *node, FibNode<T> *root); // add node to the left of the root
    void link(FibNode<T>* node, FibNode<T>* root); // list node to the root list
    void makeCons(); // Create the space required for consolidate
    void consolidate(); // Merge trees of the same degree left and right in the root-linked table of the Fibonacci heap
    void renewDegree(FibNode<T> *parent, int degree); // update the degree
    void cut(FibNode<T> *node, FibNode<T> *parent); // Strip the node from the parent's child links and make the node a member of the root list
    void cascadingCut(FibNode<T> *node) ; // do cascading cut to the node
};



#endif
