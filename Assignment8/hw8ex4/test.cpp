//
//  test.cpp
//
//for testing the graph class
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.cpp"
using namespace std;
int main()
{
    
BiPartiteGraph<int> * mygraph = new BiPartiteGraph<int>;    // my class called bipartitegraph.
(*mygraph).insert_edge(1,2);
(*mygraph).insert_edge(3,2);
(*mygraph).insert_edge(5,4);
(*mygraph).insert_edge(3,4);
(*mygraph).insert_edge(9,10);                               // this will build a sample with V1:1,3,5,9, V2:2,4,10 
                                                            // and the first will be added to V1, second will be added to V2.
(*mygraph).prettyprint();                                   
cout<<"================= ====================="<<"\n";
cout<<"first test:"<<"\n";
cout<<"================= ====================="<<"\n";
cout<<"if we add an edge from a(V2) to b(V1) but not V1 to V2"<<"\n";   
(*mygraph).insert_edge(4,3); 
cout<<"================= ====================="<<"\n";
(*mygraph).insert_vertex(7,1);                               // insert a new vertex 7 to V1.
cout<<"if we want to insert a(V1) to V2"<<"\n";
cout<<"================= ====================="<<"\n";
(*mygraph).insert_vertex(7,2);
cout<<"================= ====================="<<"\n";
cout<<"new graph is :"<<"\n";
cout<<"================= ====================="<<"\n";
mygraph->prettyprint();
cout<<"================= ====================="<<"\n";
//determine its incident edges:
cout<<"determine its incident edges:"<<"\n";
cout<<"================= ====================="<<"\n";
edgelist<int>* myedgelist1 = (*mygraph).incident_edges(1);
edgelist<int>* myedgelist4 = (*mygraph).incident_edges(4);
edgelist<int>* myedgelist2 = (*mygraph).incident_edges(2);
(*myedgelist1).prettyprint();
cout<<"================= ====================="<<"\n";
(*myedgelist2).prettyprint();    
cout<<"================= ====================="<<"\n";
(*myedgelist4).prettyprint();
cout<<"================= ====================="<<"\n";

//if we want to delete a vertex but it is in an edge:
mygraph->delete_vertex(1);
cout<<"================= ====================="<<"\n";   
//if we want to delete an edge:
mygraph->delete_edge(1,4);
cout<< "final graph"<<"\n";
mygraph->prettyprint();

cout<<"determine if it covers perfect match."<<"\n";
(*mygraph).is_perfect_match();
cout<<"================= ====================="<<"\n";    



cout<<"=========test 2 to determine perfect match.==================="<<"\n";

BiPartiteGraph<int> * mygraph2 = new BiPartiteGraph<int>;   
(*mygraph2).insert_edge(3,2);
(*mygraph2).insert_edge(5,4);
(*mygraph2).insert_edge(7,6);  
(*mygraph2).insert_edge(1,8);// V1 is 1357 V2 is 2468
mygraph2->prettyprint();
mygraph2->is_perfect_match();


cout<<"=========test 3 to determine perfect match.==================="<<"\n";

BiPartiteGraph<int> * mygraph3 = new BiPartiteGraph<int>;   
(*mygraph3).insert_edge(3,2);
(*mygraph3).insert_edge(5,4);
(*mygraph3).insert_edge(7,6);  
(*mygraph3).insert_edge(1,8);//similar to graph 2.
mygraph3->insert_vertex(9,1);// no edge means it will never be a perfect match.
mygraph3->insert_vertex(10,2);// no edge means it will never be a perfect match.

mygraph3->prettyprint();
mygraph3->is_perfect_match();


BiPartiteGraph<int> * mygraph4 = new BiPartiteGraph<int>;   
(*mygraph4).insert_edge(1,2);
(*mygraph4).insert_edge(3,4);
(*mygraph4).insert_edge(1,4);  
(*mygraph4).insert_edge(3,2);  
mygraph4->prettyprint();
mygraph4->is_perfect_match();

//note: KD has a mistake on elist<T> remove operator.







}
