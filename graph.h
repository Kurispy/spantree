#ifndef GRAPH_H
#define	GRAPH_H

#include <iostream>

using namespace std;

class Vertex {
public:
    int value();
    void set_value();
    int absolute_index();
    void set_absolute_index(const int absolute_index);
private:
    //A negative value means that this vertex is a root, and that it has a rank
    //of abs(value_)
    int value_;
    int abolsute_index_;
};

struct Edge {
    Vertex vertex1;
    Vertex vertex2;
    int weight;
};

class Graph {
public:
    Graph();
    int num_verticies();
    int num_edges();
    //Creates minimum spanning tree
    virtual void CreateMST();
protected:
    int num_vertices_;
    int num_edges_;
    Vertex *vertices_;
    int *edges_;
private:
    friend istream& operator>> (istream &is, UnconnectedGraph &graph);
    friend ostream& operator<< (ostream &os, const UnconnectedGraph &graph);
};

class UnconnectedGraph: public Graph {
public:
    void Partition();
    void CreateMST();
private:
    //Merges two graphs if necessary, then adds edge to the edge list
    //of that graph
    //Returns 1 if the union succeeded, 0 otherwise
    bool Union(int vertexindex1, int vertexindex2);
    
    //Finds the subgraph that vertex belongs to and returns its parent
    Vertex& Find(const Vertex &vertex);
    
    //Sorts graphs in ascending order based on the number of vertexes.
    //When graphs have the same number of vertexes, the graph with the
    //smaller minimum edge is considered to have fewer vertexes
    void Sort(LinkedList<Graph> graphlist); //necessary?
    
    friend istream& operator>> (istream &is, UnconnectedGraph &graph);
    friend ostream& operator<< (ostream &os, const UnconnectedGraph &graph);
    
    LinkedList<Graph> component_list_;
};

#endif	/* GRAPH_H */

