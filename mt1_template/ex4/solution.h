#include "alist_f.h"
/****************************************************************************/
/*********************************** TODO ***********************************/
/******************** Start your code in the following **********************/
/****************************************************************************/

/* Exercise 4, (i) */
template<class T> AList<T>*  AList<T>::select(T value){
     AList<T> temp;
     temp.concat(*this);
     AList<T>* TobeRet = nullptr;
     temp.bsort();
     int counterA = 1;
     int length = this->getlength();
     while (value >= temp.getitem(counterA) && counterA < length){
         TobeRet->append(temp.getitem(counterA));
         ++counterA;
     }
     return TobeRet;
}

/* Exercise 4, (ii) */
template<class T> T AList<T>::median(void){
    AList<T> temp;
    temp.concat(*this);
     temp.bsort();
     T med = temp.getitem((1 + temp.getlength())/2);
     return med;
}
    
    
/* Exercise 4, (ii) */    
template<class T> AList<T>* AList<T>::select_low(void){
    AList<T>* ToBeRet = nullptr;
    int length = this->getlength();
    T median = this->median();
    for (int i = 1; i <= length;i++){
        T item = this->getitem(i);
        if (item <= median){
            ToBeRet->append(item);}
    }
    return ToBeRet;
}