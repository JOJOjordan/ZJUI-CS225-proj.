/*
 * @ Author     : 
 * 
 * @ File       : 
 * 
 * @ Purpose    : 
 * 
 * @ Usage      : 
 * 
 * @ Description: 
 * 
 * @ Input      : 
 * 
 * @ Output     : 
 * 
 */
#ifndef ex1
#define ex1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// You may modify the decleration and definenation by yourself, add help function etc.
template <class T> class Solution {
    public:
        Solution(vector<T> input){
            data = input;
        };

        vector<T> MergeSort_k(vector<T> lst, int k);
        vector<T> MergeSort_t(vector<T> lst, int t);
        vector<T> SelfSort(vector<T> lst);
        void vec_print(vector<T> vec);
        vector<T> data;
        void test(int k, int t);
    private:

};

// Modify the following to finish ex1.1

template <class T> vector<T> Solution<T>::MergeSort_k(vector<T> lst, int k){
    int l =lst.size();
    // if the leftover cannot be divided, return and merge them.
    if (l < 2){
        return lst;
    }
    // now implement normal steps;
    int part = l/k ;
    int ls = l-part*(k-1);

    //now we should use the vector to hold the temp files.
    vector< vector<T> > a(k,vector<T>(0));

    for (int i=0; i < k; i++){
        if (part) {
            if (i < k - 1) {
                for (int j = 0; j < part; j++) {
                    a[i].push_back(lst[i * part + j]);

                }
            } else {
                for (int j = 0; j < ls; j++) {
                    a[i].push_back(lst[i * part + j]);
                }
            }
        }
        else{
            if (i <= l){
                a[i].push_back(lst[i]);
            }
        }
        // after that, all in the list is merged.
    }

    for (int i=0;i<k;i++) {
        a[i] = MergeSort_k(a[i], k);
    }

    // now implement sorting part;
    vector<T>temp(0);
    T max;
    int max_id;
    for (int i=0;i < l;i++){
        // now we should find out the max number in the list first;
        int q= 0;
        while (a[q].empty()&&q<k){
            ++q;
        }
        max = a[q][a[q].size()-1];
        max_id = q;
        for (int j=0;j<k;j++){
            if (!a[j].empty()) {
                if (max <= a[j][a[j].size()-1]) {
                    max = a[j][a[j].size()-1];
                    max_id = j;
                }
            }
        }
        // now we have the largest one, just push it into the stack.
        temp.push_back(max);
        a[max_id].pop_back();
    }
    reverse(temp.begin(),temp.end());
     //since the temp was reversed, we should put it back.
    return temp;
}

// Modify the following to finish ex1.2

template <class T> vector<T> Solution<T>::MergeSort_t(vector<T> lst, int t){
    int l =lst.size();
    // if the leftover cannot be divided, return and merge them.
    if (l <= t){
        SelfSort(lst);
        return lst;
    }
    // now implement normal steps;t
    int part = l/2 ;
    int ls = l-part;

    //now we should use the vector to hold the temp files.
    vector< vector<T> > a(2,vector<T>(0));

    for (int i=0; i < 2; i++){
        if (part) {
            if (i < 1) {
                for (int j = 0; j < part; j++) {
                    a[i].push_back(lst[i * part + j]);

                }
            } else {
                for (int j = 0; j < ls; j++) {
                    a[i].push_back(lst[i * part + j]);

                }
            }
        }
        else{
            if (i <= l){
                a[i].push_back(lst[i]);
            }
        }
        // after that, all in the list is merged.
    }

    for (int i=0;i<2;i++) {
        a[i] = MergeSort_t(a[i], 2);
    }

    // now implement sorting part;
    vector<T>temp(0);

    T max,max_id;
    for (int i=0;i < l;i++){
        // now we should find out the max number in the list first;
        int j = 0;
        while (a[j].empty()&&j<2){
            j++;
        }
        max = a[j][a[j].size()-1];
        max_id = j;
        for (int j=1;j<2;j++){
            if (!a[j].empty()) {
                if (a[j][a[j].size()-1] > max) {
                    max = a[j][a[j].size()-1];
                    max_id = j;
                }
            }
        }
        // now we have the largest one, just push it into the stack.
        temp.push_back(max);
        a[max_id].pop_back();
    }
    reverse(temp.begin(),temp.end());
    //since the temp was reversed, we should put it back.
    return temp;
}

// You could implement either bubble sort, insert sort or selection sort
template<class T> vector<T> Solution<T>::SelfSort(vector<T> lst){
    int l = lst.size();
    for (int i=0; i<l; i++){                //find which is the smallest.
        int k=i;
        for ( int j=i; j<l; j++){
            if (lst[j] < lst[k]) k=j;       //sign it to k.
        }
        if (i!=k){
            T mid=lst[k];
            lst[k]=lst[i];
            lst[i]=mid;                     //change lst[k] to answer list
        }
    }
    return lst;
}

// DO NOT modify the following
// This is to view the vector
template<class T> void Solution<T>::vec_print(vector<T> vec){
    for (T i:vec){
        cout << i << "  ";
    }
    cout<<&endl;

}

// This is for testing.
template <class T> void Solution<T>::test(int k, int t){
    cout << "Self-implemented Sort:          ";
    vec_print(SelfSort(data));
    cout << "Merge Sort with K sublist:      ";
    vec_print(MergeSort_k(data, k));
    cout << "Merge Sort with Insertion Sort: ";
    vec_print(MergeSort_t(data, t));
}
#endif 

