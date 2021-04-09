
#ifndef PROG_ASSIGNMENT1_APPOINTMENT_H
#define PROG_ASSIGNMENT1_APPOINTMENT_H

#include <iostream>
#include <vector>
#include <queue>
#include "Reg_Node.h"


using namespace std;
using std::cout;
using std::cin;
using std::endl;

class FIFO
{

public:
    FIFO(); // this build a fifo queue with empty.
    
    void deal(int date);//process and record the status, date, and time for all the patients in queue.
    void setwithdraw(Reg_Node *A);
    void setcomplete(Reg_Node *A);
    void settreatdate(Reg_Node *A,int date);
    void setwaiting(Reg_Node *A);

    void display(void);
    void profsort(void);
    void namesort(void);
    void agesort(void);
    string getstatus(Reg_Node *C);
    //int getdata(Reg_Node* C);
    int numwithdraw(void);
    int numcomplete(void);
    int numwaiting(void);
    int Avtime(void);
    vector<Reg_Node*> displaytreated(void);
    vector<Reg_Node*> displaywaiting(void);
    //void sort(Reg_Node);//uncompleted.
    //void display(Reg_Node);//print the all data in local database.
    /* queue库里的：
    q.empty()       //若队列为空 返回true 否则返回false
    q.size()        //返回元素个数
    q.pop()         //删除队首元素(不返回值)
    q.front()       //返回FIFO队列中队首元素的值(不删除元素)
    q.back()        //返回FIFO队列中队尾元素的值(不删除元素)
    q.push()        //在FIFO队列的队尾压入一个新的元素
    */
    queue<Reg_Node>* get_q();
    queue<Reg_Node>* get_p();
private:
    queue<Reg_Node>* q; // fifo queue.
    queue<Reg_Node>* p; // use to store the data for every location.(queue)
};

#endif