//
// Created by jordan on 2021/4/9.
//

#include "appointment.h"


FIFO::FIFO() {
    queue<Tuple> q;
    queue<Tuple> p;
    this->mp = new vector<Tuple>;
    this->data = new RDB(50);
    return;
}

void FIFO::deal(int date) //process and record the status, date, and time for all the patients in queue.
{
    if (q.size()<= 40){
        while(!q.empty()){
            Tuple A= q.front();
            setcomplete(A);
            settreatdate(A, date);

            q.pop();
            
            Tuple B = A;//copy A to B to store to database.
            p.push(B);
            mp->push_back(B);
        }
    }
    else{
        for (int i = 0; i < 40 ; i++){
            
            Tuple A= q.front();
            setcomplete(A);
            settreatdate(A, date);

            q.pop();
            //q->push(*A);// add to local database.
            
            Tuple B= A;//copy A to B to store to database.
            p.push(B);


            mp->push_back(B);
        }
        for (int j = 0; j < q.size() ; j++){

            Tuple A= q.front();
            setwaiting(A);
            q.pop();
            q.push(A);
            
            Tuple B= A;//copy A to B to store to database.
            p.push(B);
            mp->push_back(B);
        }
    }
    return ;
}


void FIFO::setwaiting(Tuple A)//done when jordan done.
{
    A.set_status(Waiting);
    return ;
}



void FIFO::settreatdate(Tuple A, int date)//done when jordan done.
{
    A.set_TreatDay(date);
    return ;
}

void FIFO::setcomplete(Tuple A)
{
    A.set_status(complete);
    return ;
}

void FIFO::setwithdraw(Tuple A)
{
    A.set_status(withdrawn);
    return ;
}


queue<Tuple>* FIFO::get_p(void)
{
    return &p;
}


queue<Tuple>* FIFO::get_q(void)
{
    return &q;
}

vector<Tuple>* FIFO::reporttreatment(void)
{
    return mp;
}


string FIFO::getstatus(Tuple C) {
    string m;
    status s;
    s = C.get_status();
    if (s == complete) return m="complete";
    else if (s == withdrawn) return m="withdrawn";
    else if (s == Waiting) return m="waiting";
    return m="applied";
}

int FIFO::numwithdrawn(void)
{
    int num=0;
    
    Tuple C = p.front();
    for (int i=0; i<p.size(); i++){
        if (C.get_status() == withdrawn) num++;
    }
    return num;
}

int FIFO::numcomplete(void)
{
    int num=0;

    Tuple C= p.front();
    for (int i=0; i<p.size(); i++){
        if (C.get_status() == complete) num++;
    }
    return num;
}

int FIFO::numwaiting(void)
{
    int num=0;
    
    Tuple C= p.front();
    for (int i=0; i<p.size(); i++){
        if (C.get_status() == Waiting) num++;
    }
    return num;
}








int FIFO::Avtime(void) {
    int Av;
    int size = data->cheat()->size();
    int totaltime = 0;
    for (auto i:(*data->cheat())){
        totaltime += i->get_TreatDay() - i->get_startDay();
    }
    Av = totaltime / size;
    return Av;
}

vector<Tuple> FIFO::displaywaiting(void)
{
    vector<Tuple> output;
    for (int i=0; i<p.size(); i++) {
        
        Tuple C = p.front();
        status s;
        s= C.get_status();
        if (s==Waiting){
            output.push_back(C);
        }
        p.pop();
        p.push(C);
    }
    return output;
}

vector<Tuple> FIFO::displaytreated(void)

{
    vector<Tuple> output;
    for (int i=0; i<p.size(); i++) {
        
        Tuple C = p.front();
        status s;
        s= C.get_status();
        if (s==complete){
            output.push_back(C);
        }
        p.pop();
        p.push(C);

    }
    return output;
}

void FIFO::storage(void)
{
    for(int i =0; i<p.size();i++)
    {
        Tuple A = p.front();
        data->insert(A);
        p.pop();
    }
}

RDB* FIFO::getDB(void){
    return data;
}