#ifndef GRAPH_H
#define	GRAPH_H

#include <cstdio>

using namespace std;

class Graph {
public:
    //Creates minimum spanning tree
    virtual void CreateMST();
private:
    friend istream& operator>> (istream &is, Graph &graph);
    friend ostream& operator<< (ostream &os, const Graph &graph);
    int num_verticies_;
    int num_edges_;
    MinHeap<Edge> edges_;
};

class UnconnectedGraph: public Graph {
public:
    void CreateMST();
private:
    //Makes a new graph whose representative is vertex
    void NewGraph(int vertex);
    
    //Merges two graphs if necessary, then adds edge to the adjacency list
    //of that graph
    void Union(Edge &edge);
    
    //Finds the subgraph that vertex belongs to and returns its parent
    int Find(int vertex);
    
    //Sorts graphs in ascending order based on the number of vertexes.
    //When graphs have the same number of vertexes, the graph with the
    //smaller minimum edge is considered to have fewer vertexes
    void Sort(LinkedList<Graph> graphlist);
    
    LinkedList<Graph> component_list_;
};

#endif	/* GRAPH_H */

