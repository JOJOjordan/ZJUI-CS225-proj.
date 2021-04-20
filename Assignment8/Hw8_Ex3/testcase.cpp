//
// Created by jordan on 2021/4/20.
//


// the program are mainly written according to KD's fake code. 
// i have implement several functions:
//1. makepath: return path in a set including pair<T,T>
//2. reachable: use DFS, findout weather the route is ok. 
//3. then the class modify several function in the lab templates. all the modification is done in the bottom of the cpp file. 
//4. I do not inplement the unordered. instead, i make the progress inline. 




#include "marriage.cpp"

int main(){
    auto testcase = new marriage<int>;
    testcase->addvertex(1,1);
    testcase->addvertex(2,0);
    testcase->addvertex(3,1);
    testcase->addvertex(4,0);
    testcase->addedges(1,2);
    testcase->addedges(1,4);
    testcase->addedges(3,2);
    testcase->addedges(3,4);
    int ans = testcase->find_perfect_pair();
    return ans;
};
