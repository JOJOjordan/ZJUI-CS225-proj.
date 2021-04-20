//
// Created by jordan on 2021/1/24.
//

#ifndef LIST_Q3_2_H
#define LIST_Q3_2_H
#include "alist.h"

template <class T>
class Q3_2 : public AList<T>{
public:
    Q3_2(int size = 20);
    ~Q3_2();
    void pushfront(T x);
    T popfront();
    void pushback(T x);
    T popback();
    void allocate(int x);
    void deallocate(int x);
    void print();

private:
    int begin;
    int end;
    int numitems;
    int maxsize;
    int minsize;
    int* reprarray;
};

#endif //LIST_Q3_2_H
