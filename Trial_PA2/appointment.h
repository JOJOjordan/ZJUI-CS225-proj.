
#ifndef PROG_ASSIGNMENT1_APPOINTMENT_H
#define PROG_ASSIGNMENT1_APPOINTMENT_H

#include "RDB.h"
#include "status.h"
using namespace std;
using std::cout;
using std::cin;
using std::endl;

class FIFO
{

public:
    FIFO(); // this build a fifo queue with empty.
    
    void deal(int date);//process and record the status, date, and time for all the patients in queue.
    void setwithdraw(Tuple A);
    void setcomplete(Tuple A);
    void settreatdate(Tuple A,int date);
    void setwaiting(Tuple A);

    void display(void);
    void profsort(void);
    void namesort(void);
    void agesort(void);
    vector<Tuple>* reporttreatment(void);
    string getstatus(Tuple C);
    //int getdata(Reg_Node* C);
    int numwithdrawn(void);
    int numcomplete(void);
    int numwaiting(void);
    int Avtime(void);
    vector<Tuple> displaytreated(void);
    vector<Tuple> displaywaiting(void);
    void storage(void);
    RDB* getDB(void);
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
    queue<Tuple>* get_q();
    queue<Tuple>* get_p();
private:
    int k;
    queue<Tuple> q; // fifo queue.
    queue<Tuple> p; 
    RDB* data;// use to store the permanent data for every location.(Btree)
    vector<Tuple>* mp;
};


#endif