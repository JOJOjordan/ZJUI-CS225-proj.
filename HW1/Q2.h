//
// Created by jordan on 2021/1/23.
//

#ifndef LIST_Q2_H
#define LIST_Q2_H
#include "alist.h"


template <class T> class Question2: public AList<T>{
public:
    Question2();
    ~Question2();
    T src(AList<T>& l);
private:
    T f(T x);
    T g(T x,T y);
};

#endif //LIST_Q2_H
