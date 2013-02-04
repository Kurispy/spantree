#include "graph.h"

using namespace std;

Graph::Graph() {
    int edges[4][num_edges_];
    //edge[0][i]: first vertex of the ith edge
    //edge[1][i]: second vertex of the ith edge
    //edge[2][i]: weight of the ith edge
    //edge[3][i]: set to 1 if the ith edge is included in the MSF
    edges_ = edges;
}

void Graph::CreateMST() {
    //MakeSet
    for (int i = 0; i < num_vertices_; i++) {
        vertices_[i].set_value(-1);
        vertices_[i].set_absolute_index(i);
    }
    
    for (int i = 0; i < num_edges_; i++) {
        edges_[3][i] = Union(edges_[0][i], edges_[1][i]);
    }
}

istream& operator>> (istream &is, UnconnectedGraph &graph) {
    cin >> graph.num_vertices_ >> graph.num_edges_; //Might leave ws
    
    //Read in edges and partition
    graph.Partition();
    
    return is;
}

ostream& operator<< (ostream &os, const UnconnectedGraph &graph) {
    
}

void UnconnectedGraph::Partition() {
    Edge *edge;
    
    //Go through all the edges and partition them into separate connected
    //components
    for (int i = 0; i < num_edges(); i++) {
        edge = new Edge;
        cin >> edge->vertex1 >> edge->vertex2 >> edge->weight;
        edge->vertex1.Union(edge->vertex2);
        //The edge needs to be associated with the set of vertexes that were
        //just unified
        
    }
}

void UnconnectedGraph::CreateMST() {
    
}

bool UnconnectedGraph::Union(int vertexindex1, int vertexindex2) {
    //Determine whether or not the two vertexes are in the same graph
    int v1root = Find(vertexindex1);
    int v2root = Find(vertexindex2);
    if (v1root == v2root)
        return 0;
    
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
    
    return 1;
    
}

Vertex& UnconnectedGraph::Find(const Vertex &vertex) {
    if (vertex.parent()->value() != vertex.value())
        //Set vertex's parent to the root
        vertex.set_parent(Find(vertex.parent()));
    return vertex.parent();
}

int UnconnectedGraph::Find(int vertexindex) {
    if (vertices_[vertexindex] >= 0)
        vertices_[vertexindex] = find(vertices_[vertexindex]);
    return vertices_[vertexindex].absoluteindex;
    
}