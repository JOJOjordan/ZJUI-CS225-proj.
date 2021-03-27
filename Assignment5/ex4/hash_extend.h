
#include "hashset.h"

// since it is inheritance class from a template class, some kinds of compilers wont work correctly.
// it is only pass test on gcc at version 9.3.0.

template<class T> class HashSet_LCFS : public hashset<T> {
    /* Refer to the given code to design the new hashset */
    public:
        HashSet_LCFS(int size = 20);
        void add(T item);

    private:
        void rehash(int newsize);
};

template<class T> class HashSet_RH: public hashset<T>{
    /* Refer to the given code to design the new hashset */
    public:
        HashSet_RH(int size = 20);
        // redefined the constructor to add one more array in the class.
        void add(T item);
        void print_distance(void);
    private:
        int* distance;
        void rehash(int newsize);

};