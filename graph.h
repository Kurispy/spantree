#ifndef GRAPH_H
#define	GRAPH_H

#include <iostream>

using namespace std;

struct Vertex {
    //A negative value means that this vertex is a root, and that it has a rank
    //of abs(value_)
    int value;
    int abolsute_index;
    //This value is meaningless unless the vertex is a root
    int num_vertices;
    //Solely for non-determinism
    int min_vertex;
};

struct Edge {
    //The vertices are indexes that point to a location within vertices_
    int vertex1;
    int vertex2;
    int weight;
    //Set to 1 if part of the MSF, 0 otherwise
    bool is_min; //Initialize to 0
    int component;
};

class Graph {
public:
    //Creates minimum spanning tree
    void CreateMST();
    //Sorts edges according to their weight and minimum vertex
    void SortEdges(Edge **edges, int left, int right);
    //Swaps elements of edges so that elements left of the pivotIndex are less
    //than the pivot value and elements to the right are greater
    int PartitionEdges(Edge **edges, int left, int right, int pivotIndex);
    //Returns 1 if edge1 < edge2, 0 otherwise
    bool CompareEdges(Edge edge1, Edge edge2);
    //Sorts components according to the number of vertices they contain and
    //their minimum road
    void SortComponents(Vertex **components, int left, int right);
    //Swaps elements of components so that elements left of the pivotIndex are less
    //than the pivot value and elements to the right are greater
    int PartitionComponents(Vertex **components, int left, int right, int pivotIndex);
    //Returns 1 if component1 < component2, 0 otherwise
    bool CompareComponents(Vertex component1, Vertex component2);
    //Returns 1 if the union succeeds, 0 otherwise
    bool Union(int vertex1, int vertex2);
    //Recursively calls Find until a root is reached, then returns the absolute
    //index of the root
    int Find(int vertexindex);
    //Prints the MST of a connected component of the graph
    void PrintComponent(const Vertex &component) const;
    //Prints an edge
    void PrintEdge(const Edge &edge) const;
    friend istream& operator>> (istream &is, Graph &graph);
    friend ostream& operator<< (ostream &os, const Graph &graph);
    int num_vertices_;
    int num_edges_;
    int num_components_;
    Vertex *vertices_;
    Edge **edges_;
    Vertex **components_;
};

#endif /* GRAPH_H */