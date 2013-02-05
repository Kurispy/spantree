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
            edges_[i].component = Find(edges_[i].vertex1.absolute_index());
    }
    
    Vertex *components[num_vertices_];
    //j will be the effective size of components
    int j = 0; 
    
    //Compresses the vertex list into a list of components
    for (int i = 0; i < num_vertices_; i++) {
        if (vertices_[i].value() < 0) {
            components[j] = &vertices_[i];
            j++;
        }
    }
    
    //Sorts components based on number of vertices
    QuickSort(components, j, ComponentCompare());
    
    //Goes through the sorted list of components and prints out the roads for
    //each one
    cout << "<country>\n";
    for (int i = 0; i < j; i++) {
        PrintComponent(components[i]);
    }
    cout << "</country>"; //Newline?
}

istream& operator>> (istream &is, Graph &graph) {
    cin >> graph.num_vertices_ >> graph.num_edges_;
    
    //Each vertex is initialized as a root
    Vertex vertices[graph.num_vertices_]; 
    for (int i = 0; i < graph.num_vertices_; i++) {
        vertices[i].set_value(-1);
        vertices[i].set_absolute_index(i);
        vertices[i].set_num_vertices(1);
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
    if (vertices_[v1root].value() > vertices_[v2root].value()) {
        vertices_[v1root].set_value(vertices_[v2root].absolute_index());
        vertices_[v2root].set_num_vertices(vertices_[v2root].num_vertices() + vertices_[v1root].num_vertices());
    }
    else if (vertices_[v1root].value() < vertices_[v2root].value()) {
        vertices_[v2root].set_value(vertices_[v1root].absolute_index());
        vertices_[v1root].set_num_vertices(vertices_[v1root].num_vertices() + vertices_[v2root].num_vertices());
    }
    else {
        vertices_[v1root].set_value(vertices_[v2root].absolute_index());
        vertices_[v2root].set_value(vertices_[v2root].value() - 1);
        vertices_[v2root].set_num_vertices(vertices_[v2root].num_vertices() + vertices_[v1root].num_vertices());
    }
    
    return 0;
    
}

int Graph::Find(int vertexindex) {
    if (vertices_[vertexindex].value() >= 0)
        vertices_[vertexindex].set_value(Find(vertices_[vertexindex]));
    return vertices_[vertexindex].absolute_index();
}

void Graph::PrintComponent(const Vertex &component) {
    cout << "<region>\n";
    for (int k = 0; k < num_edges_; k++) {
            if (edges_[k].is_min && component.absolute_index() == edges_[k].component)
                PrintEdge(&edges_[k]);
    }
    cout << "</region>\n";
}

void Graph::PrintEdge(const Edge &edge) {
    cout << "<road>";
    if (edge.vertex1.absolute_index() > edge.vertex2.absolute_index())
        cout << edge.vertex2.absolute_index() << " " << edge.vertex1.absolute_index() << " " << edge.weight << "</road>\n";
    else
        cout << edge.vertex1.absolute_index() << " " << edge.vertex2.absolute_index() << " " << edge.weight << "</road>\n";
}