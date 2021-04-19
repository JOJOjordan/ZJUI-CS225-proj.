//
// Created by jordan on 2021/4/18.
//

#ifndef GRAPHTRAVERSAL_MARRIAGE_H
#define GRAPHTRAVERSAL_MARRIAGE_H

#include <set>
#include <vector>
#include "graphtraversal.h"

using namespace std;

template<class T> class marriage : public graphtraversal<T>{
public:
    marriage();
    set<pair<T,T>>* Boys2Girls(edgelist<T> *edgelist);
    set<pair<T,T>>* Girls2Boys(edgelist<T> *edgelist);
    int reachable(T boys, set<pair<T,T>>edgelist, T girls);
    set<pair<T,T>>* pathmake(T boys,set<pair<T,T>>* edgelist,T girls);
    edgelist<T>*  get_partial();
    void addvertex(T item,int sex = 0); // 0 for girls, 1 for boys.
    vector<T>* modi_dfs(T startnode,T goal,elist<T>** neighbours);
    void addedges(T Boys,T Girls);
    int find_perfect_pair();
    edgelist<T>* minus(edgelist<T>*A,edgelist<T>*B);

private:
    edgelist<T>* partial;
    set<T>* BoysID;
    set<T>* GirlsID;
    int dfs_self(T goal, T node2,elist<T>** neighbours ,vertexlist<T> *vertice, markerlist<T> *mark,
                  vector<T>* output,int depth);
    edgelist<T>* All_Edge;
    !
};


#endif //GRAPHTRAVERSAL_MARRIAGE_H
