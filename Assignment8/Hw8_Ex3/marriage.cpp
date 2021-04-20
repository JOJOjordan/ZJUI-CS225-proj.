//
// Created by jordan on 2021/4/18.
//

#include "marriage.h"

template<class T> marriage<T>::marriage() :graphtraversal<T>(){
    BoysID = new set<T>;
    GirlsID = new set<T>;
    partial = new edgelist<T>;
    All_Edge = new edgelist<T>;
}

template<class T> set<pair<T, T>>* marriage<T>::Boys2Girls(edgelist<T> *edgelist) {
    edge<T>** edges = edgelist->get_reprarray();
    edge<T>* EDG;
    pair<T,T> result;
    auto ret = new set<pair<T,T>>;
    int num = edgelist->getnumedges();
    for (int i=0;i < num;i++ ){
        EDG = edges[i];
        if (this->BoysID->count(EDG->destination())>0){
            result = make_pair(EDG->destination(),EDG->origin());
        }
        else{
            result = make_pair(EDG->origin(),EDG->destination());
        }
        ret->insert(result);
    }
    return ret;
}

template<class T> set<pair<T, T>> * marriage<T>::Girls2Boys(edgelist<T> *edgelist) {
    edge<T>** edges = edgelist->get_reprarray();
    edge<T>* EDG;
    pair<T,T> result;
    auto ret = new set<pair<T,T>>;
    int num = edgelist->getnumedges();
    for (int i=0;i < num;i++ ){
        EDG = edges[i];
        if (this->GirlsID->count(EDG->destination())>0){
            result = make_pair(EDG->destination(),EDG->origin());
        }
        else{
            result = make_pair(EDG->origin(),EDG->destination());
        }
        ret->insert(result);
    }
    return ret;
}

template<class T> int marriage<T>::reachable(T boys,set<pair<T,T>>*di_graph, T girls) {
    // the reach should modified the code in the DFS search.
    // 1 for reachable, 0 for unreachable.
    //ersion 1: hand-make DFS instead of using KD's code.
    //version2: using KD's output to simplify this function.
    typedef pair <T, T> Dec;
    hash <T> hashfunction;
    int num = this->numvertices();
    elist<T> **neighbours = new elist<T> *[num]();
    // now we have init the hash table.
    int index1;
    for (Dec p:(*di_graph)) {
        T origin = p.first;
        T destination = p.second;
        index1 = hashfunction(origin) % num;
        if (neighbours[index1] == 0) {
            // we will build a new neighbour obj in the array.
            elist<T>* newobj;
            *newobj = elist<T>(destination);

            newobj->addvertex(destination);
            neighbours[index1] = newobj;
        } else {
            auto obj = neighbours[index1];
            obj->addvertex(destination);
        }
    }
    set <Dec> *output = new set<Dec>;
    vector <T> *temp = this->modi_dfs(boys, girls, neighbours);
    // now change the result to proper one instead of a T*
    if (temp->empty()) {
        return 0;
    }
    return 1;
}

template<class T> set<pair<T, T>> * marriage<T>::pathmake(T boys, set<pair<T,T>>* di_graph, T girls) {
    typedef pair <T, T> Dec;
    hash <T> hashfunction;
    int num = this->numvertices();
    elist<T>** neighbours = new elist<T>*[num]();
    // now we have init the hash table.
    int index1, index2;
    for (Dec p:(*di_graph)) {
        T origin = p.first;
        T destination = p.second;
        index1 = hashfunction(origin) % num;
        index2 = hashfunction(destination) % num;
        if (neighbours[index1] == 0) {
            // we will build a new neighbour obj in the array.
            elist<T>* newobj;

            *newobj=elist<T>(destination);
            neighbours[index1] = newobj;
        } else {
            auto obj = neighbours[index1];
            obj->addvertex(destination);
        }
    }
    set<Dec>* output = new set<Dec>;
    vector<T>* temp = this->modi_dfs(boys,girls,neighbours);
    // now change the result to proper one instead of a T*
    if (temp->empty()){
        return output;
    }

    // then make the path.
    for (int i=0;i<temp->size();i++){
        auto small = make_pair((*temp)[i],(*temp)[i+1]);
        output->insert(small);
    }
    return output;
}


// i midify the dfs written by KD for better return results.
// if the pair's T1 is zero, it means that we have not found a path.
template<class T> vector<T>* marriage<T>::modi_dfs(T startnode, T goal,elist<T>** neighbours) {
    vector<T>* ret;
    if((this->vertices)->contains(startnode) == false){
        ret = nullptr;
        return ret;
    }
    auto marklist = new markerlist<T>;
    marklist->mark(startnode);

    int length = this->vertices->getlength();

    // use vector is still a better consideration.
    // modify it later.
    auto result = new vector<T>;
    for (int i = 0;i < length;i++){
        (*result)[i] = 0;
    }
    int check = dfs_self(goal,startnode,neighbours,this->vertices,marklist,result,0);
    if (check == 0){
        ret = nullptr;
    }
    else {
        ret = result;
    }
    return ret;
}

template<class T> int marriage<T>::dfs_self(T goal, T node2,elist<T>** neighbours ,vertexlist<T> *vertice, markerlist<T> *mark,
                                            vector<T>* output,int depth) {
    hash<T>hashfunction;
    int num = this->numvertices();
    int op = 0;
    int index = hashfunction(node2)%num;
    if (neighbours[index]!=0) {
        elist<T> *base = neighbours[num];
        neighbour<T> *current = base->getfirst();
        for (int i=0;i<base->getlength();i++){
            T nextnode = current->getitem();
            if (!mark->ismarked(nextnode)){
                mark->mark(nextnode);
                (*output)[depth] = nextnode;
                depth++;
                if (goal == nextnode){
                    op = 1;
                }
                else{
                    op = dfs_self(goal,node2,neighbours,vertice,mark,output,depth);
                }
            }
            // if it is marked, we will do nothing.
            if (op){
                return 1;
            }
            current = current->getnext();
        }
    }
    // not find in this part, we should backtrack.
    return 0;

}

template<class T> void marriage<T>::addvertex(T item, int sex) {
    this->vertices->addvertex(item,sex);
    if (sex){
        BoysID->insert(item);
    }
    else{
        GirlsID->insert(item);
    }
    return;
}

template<class T> void marriage<T>::addedges(T Boys, T Girls) {
    All_Edge->add(Boys,Girls);
    return;
}

template<class T> int marriage<T>::find_perfect_pair() {
    int mode = 1;
    int output = 0;
    // output =0 will means that the match is done Perfectly.
    // output = 1 will means that the match is not perfect.
    // the partial is empty.
    while (mode) {
        if (mode == 1) {
            if (BoysID->size() < partial->getnumedges()) {
                mode = 2;
            } else {
                mode = 0;
            }
        }
        if (mode == 2) {
            set <pair<T, T>> *Bigraph;
            set<pair<T,T>>* Gigraph;
            Bigraph = Girls2Boys(partial);
            // now modify the E-partial.
            Gigraph = Boys2Girls(minus(All_Edge, partial));
            Bigraph->insert(Gigraph->begin(), Gigraph->end());
            // mode 2 and 3 are theoretically connected. so I just implement them together.
            // we should add the two pair set first.
            edge<T> **edged = partial->get_reprarray();
            T choose = 0;
            for (T b:(*BoysID)) {
                for (int i = 0; i < partial->getnumedges(); i++) {
                    if (choose == 0) {
                        edge<T> *tempo = edged[i];
                        if (tempo->destination() == b || tempo->origin() == b) {
                            choose = b;
                        }
                    }
                }
            }
            // now we have choose the desire boy.
            // now we have to choose some desire girls.
            T chGirl = 0;
            for (T g:(*GirlsID)) {
                for (int i = 0; i < partial->getnumedges(); i++) {
                    if (chGirl == 0) {
                        edge<T> *tempo = edged[i];
                        if (tempo->destination() == g || tempo->origin() == g) {
                            chGirl = g;
                        }
                        // then we should check reachable.
                        if (!reachable(choose, Bigraph, chGirl)) {
                            chGirl = 0;
                        }
                    }
                }
            }
            // we should check if we can find a unpaired girl.
            if (chGirl == 0) {
                output = 1;
                mode = 0;
            } else {
                mode = 3;
            }
            if (mode == 3) {
                // now we will update the partial match.
                // partial match is a edge list class.
                // we can write functions in it.
                // the unordered is defined as a
                set <pair<T, T>> *found = pathmake(choose, Bigraph, chGirl);
                int mark, counter;
                counter = 0;
                auto create = new edgelist<T>;

                for (pair <T, T> k : (*found)) {
                    mark = 0;
                    for (int i = 0; i < partial->getnumedges(); i++) {
                        edge<T> *part = partial->get_edge(i);
                        if (k.first == part->origin() && k.second == part->destination()) {
                            mark = 1;
                        }
                    }
                    if (!mark) {
                        create->add(k.first, k.second);
                    }
                }
                // now a new edgelist is created. we can append it to partial.
                partial->append(create);
            }
        }
    }
    if (output){
        cout<<"We can not find perfect match"<<endl;
        return 0;
    }
    cout<<"We find perfect match."<<endl;
    return 1;
}

template<class T> edgelist<T> * marriage<T>::minus(edgelist<T> *A, edgelist<T> *B) {
    auto ret = new edgelist<T>;
    auto array = ret->get_reprarray();
    auto Aarr = A->get_reprarray();
    auto Barr = B->get_reprarray();
    int op,counter;
    counter = 0;
    for (int i =0; i<A->getnumedges();i++){
        op = 0;
        auto temp = Aarr[i];
        for (int j=0;j<B->getnumedges();j++){
            if (temp == Barr[j]){
                op = 1;
            }
        }
        if (!op){
            array[counter] = temp;
            counter++;
        }
    }
    return ret;
}
