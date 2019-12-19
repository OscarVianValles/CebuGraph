#include "Node.hpp"
#include "Edge.hpp"
#include <list>
#include <queue>

class Graph {
private:
    std::list<Node*> _vertex; // list of vertices (landmarks)
    std::vector< std::list<Edge*>> _adj; // list of edges (path)
    int _cap; // capacity for array of vertices to add edges on them
    int _size; // current number of vertices

public:
    Graph(int);
    ~Graph();
    void addVertex(std::string);
    void addEdge(int, int, int);
    void display();
};

Graph::Graph(int cap) {
    this->_size = 0;
    this->_cap = cap;
    this->_adj;
}

Graph::~Graph() { 
//delete[] this->_adj; 
}

void Graph::addVertex(std::string name) {
    // add vertices (destinations)

    Node *n = new Node(this->_size, name);
    std::list<Edge*> *tmp = new std::list<Edge*>;

    // push to the list of vertex
    this->_adj.push_back[tmp];
    this->_vertex.push_back(n);
    this->_size += 1;
}

void Graph::addEdge(int a, int b, int cost) {
    // edge has the destination id and the cost
    Edge *e = new Edge(b, cost);

    this->_adj[a].push_back(e);
}

void Graph::display() {
    for (int i = 0; i < this->_cap; i++) {
        for (std::list<Edge*>::iterator it = this->_adj[i].begin(); it != this->_adj[i].end(); it++) {
            Edge e = **it;
            // i -> id of source vertex
            std::cout << i << " -> " << e.n << " = " << e.cost << " ";
        }
        std::cout << "\n";
    }
}
