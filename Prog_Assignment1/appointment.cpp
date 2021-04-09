//
// Created by jordan on 2021/4/9.
//

#include "appointment.h"

FIFO::FIFO() {
    q = new queue<Reg_Node>;
    p = new queue<Reg_Node>;
    return;
}

void FIFO::deal(int date) //process and record the status, date, and time for all the patients in queue.
{
    if (this->q->size()<= 40){
        while(!this->q->empty()){
            Reg_Node *A = new Reg_Node;
            (*A)= q->front();
            setcomplete(A);
            settreatdate(A, date);

            q->pop();
            Reg_Node *B;
            B= A;//copy A to B to store to database.
            p->push(*B);
        }
    }
    else{
        for (int i = 0; i < 40 ; i++){
            Reg_Node *A = new Reg_Node;
            (*A)= q->front();
            setcomplete(A);
            settreatdate(A, date);

            q->pop();
            //q->push(*A);// add to local database.
            Reg_Node *B;
            B= A;//copy A to B to store to database.
            p->push(*B);
        }
        for (int j = 0; j < q->size() ; j++){
            Reg_Node *A = new Reg_Node;
            (*A)= q->front();
            setwaiting(A);
            q->pop();
            q->push(*A);
            Reg_Node *B;
            B= A;//copy A to B to store to database.
            p->push(*B);
        }
    }
    return ;
}


void FIFO::setwaiting(Reg_Node *A)//done when jordan done.
{
    (*A).set_status(waiting);
    return ;
}



void FIFO::settreatdate(Reg_Node *A, int date)//done when jordan done.
{
    (*A).set_treatment(date);
    return ;
}

void FIFO::setcomplete(Reg_Node *A)//done when jordan done.
{
    (*A).set_status(complete);
    return ;
}

void FIFO::setwithdraw(Reg_Node *A)
{
    (*A).set_status(withdraw);
    return ;
}



queue<Reg_Node>* FIFO::get_p(void)
{
    return p;
}


queue<Reg_Node>* FIFO::get_q(void)
{
    return q;
}

void FIFO::display(void)
{
    for (int i=0; i<p->size(); i++) {
        Reg_Node *C = new Reg_Node;
        (*C) = p->front();
        cout << (*C).get_id()<<(*C).get_name()<<(*C).get_profession()<<(*C).get_age()<<(*C).get_location()<<(*C).get_treatDay()<<(*C).get_RegDay()<<getstatus(C)<<std::endl;
        p->pop();
        p->push(*C);

    }
}


string FIFO::getstatus(Reg_Node *C) {
    string m;
    status s;
    s = (*C).get_status();
    if (s == complete) return m="complete";
    else if (s == withdraw) return m="withdraw";
    else if (s == waiting) return m="waiting";
    return m="applied";
}

int FIFO::numwithdraw(void)
{
    int num=0;
    Reg_Node *C = new Reg_Node;
    (*C)= p->front();
    for (int i=0; i<p->size(); i++){
        if ((*C).get_status() == withdraw) num++;
    }
    return num;
}

int FIFO::numcomplete(void)
{
    int num=0;
    Reg_Node *C = new Reg_Node;
    (*C)= p->front();
    for (int i=0; i<p->size(); i++){
        if ((*C).get_status() == complete) num++;
    }
    return num;
}

int FIFO::numwaiting(void)
{
    int num=0;
    Reg_Node *C = new Reg_Node;
    (*C)= p->front();
    for (int i=0; i<p->size(); i++){
        if ((*C).get_status() == waiting) num++;
    }
    return num;
}

void FIFO::agesort()
{
    // get the length of the queue p
    int len=p->size();
    Reg_Node a[len]; // use a[] to store reg node from the queue
    // char b[len];
    Reg_Node *p1;
    Reg_Node *p2;

    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        a[i] = p->front();
        p->pop();
    }

    // use selection sort to sort based on the age
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            p1 = &a[max];
            p2 = &a[j];

            // if p1 larger than p2, swap them
            if (p1->get_age() < p2->get_age())
            {
                max=j;
            }
        }
        Reg_Node tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
    }
    for (int i=0; i< len; ++i)
    {
        p->push(a[i]);
    }
    // return p;
}

// sorting according to name
void FIFO::namesort()
{
    int len=p->size();
    Reg_Node a[len];
    // char b[len];
    Reg_Node *p1;
    Reg_Node *p2;

    for (int i = 0; i < len; ++i)
    {
        a[i] = p->front();
        p->pop();
    }

    // use selection sort to sort based on the name
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            p1 = &a[max];
            p2 = &a[j];

            // if p1 larger than p2, swap them
            if(p1->get_name() < p2->get_name())
            {
                max=j;
            }
        }
        Reg_Node tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
    }

    for (int i=0; i< len; ++i)
    {
        p->push(a[i]);
    }
    // return p;
}


// sort according to profession
void FIFO::profsort()
{
    // get the length of the queue p
    int len=p->size();
    Reg_Node a[len]; // use a[] to store reg node from the queue
    // char b[len];
    Reg_Node *p1;
    Reg_Node *p2;

    // store and pop every element from the queue
    for (int i = 0; i < len; ++i)
    {
        a[i] = p->front();
        p->pop();
    }

    // use selection sort to sort based on the profession
    for (int i =0; i < len; ++i)
    {
        int max=i;
        for (int j=i+1; j< len; ++j)
        {
            p1 = &a[max];
            p2 = &a[j];

            // if p1 larger than p2, swap them
            if (p1->get_profession() < p2->get_profession())
            {
                max=j;
            }
        }
        Reg_Node tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
    }
    for (int i=0; i< len; ++i)
    {
        p->push(a[i]);
    }
    // return p;
}






int FIFO::Avtime(void) {
    int Av;
    int size = p->size();
    int totaltime = 0;
    Reg_Node *C = new Reg_Node;
    (*C) = p->front();
    for (int i = 0; i < p->size(); i++) {
        (*C) = p->front();
        status s = (*C).get_status();
        if (s== complete) {
            totaltime = totaltime + ((*C).get_treatDay() - (*C).get_RegDay());
        }
        p->pop();
        p->push(*C);
    }
    Av = totaltime / size;
    return Av;
}

vector<Reg_Node*> FIFO::displaywaiting(void)
{
    vector<Reg_Node*> output;
    for (int i=0; i<p->size(); i++) {
        Reg_Node *C = new Reg_Node;
        (*C) = p->front();
        status s;
        s= (*C).get_status();
        if (s==waiting){
            output.push_back(C);
        }
        p->pop();
        p->push(*C);
    }
    return output;
}

vector<Reg_Node*> FIFO::displaytreated(void)

{
    vector<Reg_Node*> output;
    for (int i=0; i<p->size(); i++) {
        Reg_Node *C = new Reg_Node;
        (*C) = p->front();
        status s;
        s= (*C).get_status();
        if (s==complete){
            output.push_back(C);
        }
        p->pop();
        p->push(*C);

    }
    return output;
}