#include "graph.h"

using namespace std;

void Graph::CreateMST() {
    //First Pass:
    //Determines which edges are in the MSF
    for (int i = 0; i < num_edges_; i++) {
        edges_[i]->is_min = Union(edges_[i]->vertex1, edges_[i]->vertex2);
    }
    
    //Second Pass:
    //Determines which edge goes with which component
    for (int i = 0; i < num_edges_; i++) {
        if (edges_[i]->is_min)
            edges_[i]->component = Find(edges_[i]->vertex1);
    }
    
    Vertex *components[num_vertices_];
    num_components_ = 0; 
    
    //Compresses the vertex list into a list of components
    for (int i = 0; i < num_vertices_; i++) {
        if (vertices_[i].value < 0) {
            components[num_components_] = &vertices_[i];
            num_components_++;
        }
    }
    
    components_ = components;
}

void Graph::SortEdges(Edge **edges, int left, int right) {
    int pivotIndex;
    if (left < right) {
        pivotIndex = (left + right) / 2;
        pivotIndex = PartitionEdges(edges, left, right, pivotIndex);
        SortEdges(edges, left, pivotIndex - 1);
        SortEdges(edges, pivotIndex + 1, right);
    }
}

int Graph::PartitionEdges(Edge **edges, int left, int right, int pivotIndex) {
    //Swap space
    Edge *temp;
    //The index where the pivot value will end up
    int finalIndex;
     
    Edge *pivotValue = edges[pivotIndex];
    //--Swap--
    temp = edges[pivotIndex];
    edges[pivotIndex] = edges[right];
    edges[right] = temp;
    //--Swap--
    finalIndex = left;
    for (int i = left; i < right - 1; i++) {
        if (CompareEdges(*(edges[i]), *(pivotValue))) {
            temp = edges[i];
            edges[i] = edges[finalIndex];
            edges[finalIndex] = temp;
            
            finalIndex++;
        }
    }
    temp = edges[finalIndex];
    edges[finalIndex] = edges[right];
    edges[right] = temp;
    
    return finalIndex;
}

bool Graph::CompareEdges(Edge edge1, Edge edge2) {
    if (edge1.weight < edge2.weight)
        return 1;
    else if (edge1.weight == edge2.weight) {
        if (edge1.vertex1 < edge2.vertex1)
            return 1;
        else if (edge1.vertex1 == edge2.vertex1) {
            if (edge1.vertex2 < edge2.vertex2)
                return 1;
        }
    }
    
    return 0;
}

void Graph::SortComponents(Vertex **components, int left, int right) {
    int pivotIndex;
    if (left < right) {
        pivotIndex = (left + right) / 2;
        pivotIndex = PartitionComponents(components, left, right, pivotIndex);
        SortComponents(components, left, pivotIndex - 1);
        SortComponents(components, pivotIndex + 1, right);
    }
}

int Graph::PartitionComponents(Vertex **components, int left, int right, int pivotIndex) {
    //Swap space
    Vertex *temp;
    //The index where the pivot value will end up
    int finalIndex;
     
    Vertex *pivotValue = components[pivotIndex];
    //--Swap--
    temp = components[pivotIndex];
    components[pivotIndex] = components[right];
    components[right] = temp;
    //--Swap--
    finalIndex = left;
    for (int i = left; i < right - 1; i++) {
        if (CompareComponents(*(components[i]), *(pivotValue))) {
            temp = components[i];
            components[i] = components[finalIndex];
            components[finalIndex] = temp;
            
            finalIndex++;
        }
    }
    temp = components[finalIndex];
    components[finalIndex] = components[right];
    components[right] = temp;
    
    return finalIndex;
}

bool Graph::CompareComponents(Vertex component1, Vertex component2) {
    if (component1.num_vertices < component2.num_vertices)
        return 1;
    else if (component1.num_vertices == component2.num_vertices) {
        if (component1.min_vertex < component2.min_vertex)
            return 1;
    }
    
    return 0;
}

bool Graph::Union(int vertex1, int vertex2) {
    //Determine whether or not the two vertexes are in the same graph
    int v1root = Find(vertex1);
    int v2root = Find(vertex2);
    if (v1root == v2root)
        return 1;
    
    //Vertex 1 and Vertex 2 are disjoint
    //Because values are negative, > and < are inverted
    if (vertices_[v1root].value > vertices_[v2root].value) {
        vertices_[v1root].value = v2root;
        vertices_[v2root].num_vertices = vertices_[v2root].num_vertices + vertices_[v1root].num_vertices;
        if (vertices_[v2root].min_vertex > vertices_[v1root].min_vertex)
            vertices_[v2root].min_vertex = vertices_[v1root].min_vertex;
    }
    else if (vertices_[v1root].value < vertices_[v2root].value) {
        vertices_[v2root].value = v1root;
        vertices_[v1root].num_vertices = vertices_[v1root].num_vertices + vertices_[v2root].num_vertices;
        if (vertices_[v1root].min_vertex > vertices_[v2root].min_vertex)
            vertices_[v1root].min_vertex = vertices_[v2root].min_vertex;
    }
    else {
        vertices_[v1root].value = v2root;
        vertices_[v2root].value = vertices_[v2root].value - 1;
        vertices_[v2root].num_vertices = vertices_[v2root].num_vertices + vertices_[v1root].num_vertices;
        if (vertices_[v2root].min_vertex > vertices_[v1root].min_vertex)
            vertices_[v2root].min_vertex = vertices_[v1root].min_vertex;
    }
    
    return 0;
    
}

int Graph::Find(int vertexindex) {
    if (vertices_[vertexindex].value >= 0)
        vertices_[vertexindex].value = Find(vertices_[vertexindex].value);
    return vertices_[vertexindex].abolsute_index;
}

void Graph::PrintComponent(const Vertex &component) const {
    cout << "<region>\n";
    for (int k = 0; k < num_edges_; k++) {
            if (edges_[k]->is_min && component.abolsute_index == edges_[k]->component)
                PrintEdge(*(edges_[k]));
    }
    cout << "</region>\n";
}

void Graph::PrintEdge(const Edge &edge) const {
    cout << "<road>";
    cout << edge.vertex1 << " " << edge.vertex2 << " " << edge.weight << "</road>\n";
}

istream& operator>> (istream &is, Graph &graph) {
    cin >> graph.num_vertices_ >> graph.num_edges_;
    
    //Each vertex is initialized as a root
    Vertex vertices[graph.num_vertices_]; 
    for (int i = 0; i < graph.num_vertices_; i++) {
        vertices[i].value = -1;
        vertices[i].abolsute_index = i;
        vertices[i].num_vertices = 1;
        vertices[i].min_vertex = i;
    }
    graph.vertices_ = vertices;
    
    Edge *edges[graph.num_edges_];
    Edge edge;
    int temp = 0;
    for (int i = 0; i < graph.num_edges_; i++) {
        cin >> edge.vertex1 >> edge.vertex2 >> edge.weight;
        //Guarantees that vertex1 will always be less than vertex2
        if (edge.vertex1 > edge.vertex2) {
            temp = edge.vertex1;
            edge.vertex1 = edge.vertex2;
            edge.vertex2 = edge.vertex1;
        }
        edge.is_min = 0;
        edges[i] = &edge;
    }
    temp++; //This gets rid of the warning
    graph.edges_ = edges;
    
    return is;
}

ostream& operator<< (ostream &os, const Graph &graph) {
    cout << "<?xml version=\"1.4\"?>\n";
    //Goes through the sorted list of components and prints out the roads for
    //each one
    cout << "<country>\n";
    for (int i = 0; i < graph.num_components_; i++) {
        graph.PrintComponent(*(graph.components_[i]));
    }
    cout << "</country>"; //Newline?
    
    return os;
}

