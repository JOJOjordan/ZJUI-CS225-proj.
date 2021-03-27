#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "hash_extend.h"
#include "hashset.h"
using std::cout;
using std::cin;
using std::hash;
/* Put your implementation here */

template<class T>HashSet_LCFS<T>::HashSet_LCFS(int size):hashset<T>(size){} //just use the same constructors;

template<class T>void HashSet_LCFS<T>::add(T item) {
    hash<T> hashfunction;
    int index = hashfunction(item)% this->maxsize;
    int insertion = -1;
    T* fcome;
    if (this->reprarray[index] != 0) {
        if (*this->reprarray[index] == item) return;
    }
    // this shows that the item should be inserted into the reprarray.
    T *ptr = new T;
    *ptr = item;
    // then comes the situation that dont need to replacement.
    if (this->reprarray[index] == this->pt_nil || !this->reprarray[index]){
        insertion = index;
        this->reprarray[insertion] = ptr;
        ++this->numitems;
        int load = 100*this->numitems / this->maxsize;
        if (load >= 75){
            rehash(2*this->maxsize);
        }
    }
    // then we should implement normal conditions.
    if (insertion < 0 ) {

        fcome = this->reprarray[index];
        this->reprarray[index] = ptr;
        // now we have swap the old and new items. now we should push
        // the old one back to the hashset correctly.
        hashset<T>::add(*fcome);
        //
        // hense there have some questions. we should check it later.
    }
}

template<class T>void HashSet_LCFS<T>::rehash(int newsize) {
    // roughly same work like KD. i will show what's new code then.
    if (newsize < 20) newsize = 20;
    int newnum = 0;
    T** newarray = new T*[newsize];
    for (int i=0;i < newsize;i++){
        newarray[i] = 0;
        // since C++ do not recommend we use allocare(),
        // we should init it by ourselves.
    }
    for (int i=0; i < this->maxsize;i++){
        if (this->reprarray[i] !=0 && this->reprarray[i] != this->pt_nil){
            T current = *this->reprarray[i];
            T* fcomer;
            hash<T> hashfunction;
                // here we calc the index.
            int index = hashfunction(current) % newsize;
                // now we can swap the ptr now.
            fcomer = newarray[index];
            newarray[index] = this->reprarray[i];
            if (!fcomer) {
                //we should push the old one traditionally with linear probe.
                while (newarray[index]) {
                    index = (index + 1) % newsize;
                }
                //now we can not find the original index.
                newarray[index] = fcomer;
            }
            ++ newnum;
        }
    }
    this->numitems = newnum;
    delete this->reprarray;       // free the memory for we are changing the ptr.
    this->reprarray = newarray;
    this->maxsize = newsize;
}

template<class T>HashSet_RH<T>::HashSet_RH(int size):hashset<T>(size){
    distance = new int [this->maxsize];
    // now we should clear the new two array just like KD do in the lab.
    for (int i = 0; i < this->maxsize;i++){
        distance[i] = 0;
    }
}

template<class T>void HashSet_RH<T>::add(T item) {
    hash<T> hashfunction; // new hash function just like what we did in lab.
    int index;
    index = hashfunction(item) % this->maxsize;
    int curDis, prevDis,tempDis;    // define the distance that are from the ideal position.
    curDis = 0;
    tempDis = -1;
    //
    T* fcomer = this->reprarray[index];
    T* ptr = new T;
    *ptr = item;

    // now we can implement the special situation first.
    while (fcomer!=0){
        tempDis = -1;
        curDis = 0;
        prevDis = distance[index];
        //now calculate the new distance;
        while (this->reprarray[index]!=0) {
            if (this->reprarray[index] != this->pt_nil && *this->reprarray[index] == *ptr) {
                cout<<"check! same item found"<<std::endl;
                return;
            }
            // mark the first meet nul ptr.
            if (tempDis < 0 && this->reprarray[index] == this->pt_nil) {
                tempDis = curDis;
            }
            index = (index+1) % this->maxsize;
            ++curDis;
        }

        if (tempDis < 0)
            tempDis = curDis;

        // now according to the distance we should define next steps
        if (tempDis > prevDis) {
            fcomer = this->reprarray[(index - curDis) % this->maxsize];
            this->reprarray[(index - curDis) % this->maxsize] = ptr;
            distance[(index - curDis) % this->maxsize] = tempDis;
            ptr = fcomer;
            index = hashfunction(*ptr) % this->maxsize;
            fcomer = this->reprarray[index];
        }
        else{
            fcomer = this->reprarray[index];
        }

    }
    if (tempDis < 0)
        tempDis = curDis;
    this->reprarray[index] = ptr;
    distance[index] = tempDis;
    ++this->numitems;
    for (int i=0; i < this->maxsize;i++){
        //cout<<"  "<<this->reprarray[i]<<std::endl;
    }

    int load = 100*this->numitems / this->maxsize;
    if (load >= 75)
    {
        rehash(2*this->maxsize);
    }
    return;
    // compare the distance between the previous position

    // now the recursive is not on the tail but in the middle, we can claim that it is not so bad.
}

template<class T>void HashSet_RH<T>::rehash(int newsize) {
    if (newsize < 19) newsize = 19;
    int newnum = 0;
    int curDis,prevDis;
    hash<T>hashfunction;
    // initialize the new arrays.
    T** newarray = new T*[newsize];
    int* newDis = new int[newsize];
    for (int i = 0;i < newsize;i++){
        newarray[i] = 0;
        newDis[i] = 0;
    }
    // copy all item to new position.
    for (int i = 0; i < this->maxsize; i++){
        if (this->reprarray[i] != 0 && this->reprarray[i] != this->pt_nil){
            curDis = 0;
            //
            T item = *this->reprarray[i];
            int index = hashfunction(item) % newsize;
            //
            T* current = this->reprarray[i];
            T* fcomer = newarray[index]; // we now get the first fcomer.
            // now use loop to find proper position for each element.
            while (fcomer != 0) {
                //initialize distance at the beginning of each loop.
                curDis = 0;
                prevDis = newDis[index];
                // calculate the distance;
                while (newarray[index] != 0) {
                    index = (index + 1) % newsize;
                    ++curDis;
                }
                // if the elements have worse case, put it here.
                if (curDis > prevDis) {
                    fcomer = newarray[(index - curDis) % newsize];
                    newarray[(index - curDis) % newsize] = current;
                    distance[(index - curDis) % newsize] = curDis;
                    // now we should start a new loop.
                    current = fcomer;
                    index = hashfunction(*current);
                } else {
                    fcomer = newarray[index];
                }
            }
                // after the loop, the current should be stored in the position index.
                newarray[index] = current;
                newDis[index] = curDis;
                ++newnum;
        }
    }
    this->numitems = newnum;
    delete this->reprarray;
    delete distance;
    distance = newDis;
    this->reprarray = newarray;
    this->maxsize = newsize;
}

template<class T>void HashSet_RH<T>::print_distance(void) {
    cout << "The size of the hashtable is: " << this->maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << this->numitems << "\n";
    for (int i = 0; i < this->maxsize; ++i)
    {
        if (this->reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (this->reprarray[i] == this->pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " is " << *this->reprarray[i] <<" with distance "<<distance[i]<<" .\n";
    }
    return;
}
