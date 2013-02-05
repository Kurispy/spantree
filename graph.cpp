#include "graph.h"

using namespace std;

void Graph::CreateMST() {
    //First Pass:
    //Determines which edges are in the MSF
    for (int i = 0; i < num_edges_; i++) {
        edges_[i].is_min = Union(edges_[i].vertex1, edges_[i].vertex2);
    }
    
    //Second Pass:
    //Determines which edge goes with which component
    for (int i = 0; i < num_edges_; i++) {
        if (edges_[i].is_min)
            edges_[i].component = Find(edges_[i].vertex1);
    }
    
    //Third Pass:
    //Sorts components based on number of vertices
}

istream& operator>> (istream &is, Graph &graph) {
    cin >> graph.num_vertices_ >> graph.num_edges_;
    
    //Each vertex is initialized as a root
    Vertex vertices[graph.num_vertices_]; 
    for (int i = 0; i < graph.num_vertices_; i++) {
        vertices[i].set_value(-1);
        vertices[i].set_absolute_index(i);
    }
    graph.vertices_ = vertices;
    
    Edge edges[graph.num_edges_];
    for (int i = 0; i < graph.num_edges_; i++) {
        cin >> edges[i].vertex1 >> edges[i].vertex2 >> edges[i].weight;
        edges[i].is_min = 0;
    }
    graph.edges_ = edges;
    
    return is;
}

ostream& operator<< (ostream &os, const Graph &graph) {
    
}

int Graph::Union(Vertex vertex1, Vertex vertex2) {
    //Determine whether or not the two vertexes are in the same graph
    int v1root = Find(vertex1.absolute_index());
    int v2root = Find(vertex2.absolute_index());
    if (v1root == v2root)
        return 1;
    
    //Vertex 1 and Vertex 2 are disjoint
    //Because values are negative, > and < are inverted
    if (vertices_[v1root].value() > vertices_[v2root].value())
        vertices_[v1root].set_value(vertices_[v2root].absolute_index());
    else if (vertices_[v1root].value() < vertices_[v2root].value())
        vertices_[v2root].set_value(vertices_[v1root].absolute_index());
    else {
        vertices_[v1root].set_value(vertices_[v2root].absolute_index());
        vertices_[v2root].set_value(vertices_[v2root].value() - 1);
    }
    
    return 0;
    
}

int Graph::Find(int vertexindex) {
    if (vertices_[vertexindex].value() >= 0)
        vertices_[vertexindex].set_value(Find(vertices_[vertexindex]));
    return vertices_[vertexindex].absolute_index();
}