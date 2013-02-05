#ifndef GRAPH_H
#define	GRAPH_H

#include <iostream>

using namespace std;

class Vertex {
public:
    int value();
    void set_value(const int value);
    int absolute_index();
    void set_absolute_index(const int absolute_index);
    int num_vertices();
    void set_num_vertices(const int num_vertices);
private:
    friend istream& operator>> (istream &is, Vertex &vertex);
    friend ostream& operator<< (ostream &os, const Vertex &vertex);
    //A negative value means that this vertex is a root, and that it has a rank
    //of abs(value_)
    int value_;
    int abolsute_index_;
    //This value is meaningless unless the vertex is a root
    int num_vertices_;
};

struct Edge {
    Vertex vertex1;
    Vertex vertex2;
    int weight;
    //Set to 1 if part of the MSF, 0 otherwise
    bool is_min; //Initialize to 0
    int component;
};

class Graph {
public:
    int num_verticies();
    int num_edges();
    //Creates minimum spanning tree
    virtual void CreateMST();
protected:
    int num_vertices_;
    int num_edges_;
    Vertex *vertices_;
    Edge *edges_;
    Vertex *components_;
private:
    friend istream& operator>> (istream &is, Graph &graph);
    friend ostream& operator<< (ostream &os, const Graph &graph);
    //Returns 1 if the union succeeds, 0 otherwise
    bool Union(Vertex vertex1, Vertex vertex2);
    //Recursively calls Find until a root is reached, then returns the absolute
    //index of the root
    int Find(int vertexindex);
    //Prints the MST of a connected component of the graph
    void PrintComponent(const Vertex &component);
    //Prints an edge
    void PrintEdge(const Edge &edge);
};
