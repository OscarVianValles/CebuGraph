#include "Node.hpp"
#include <list>
#include <queue>

class Graph {
private:
    std::list<Node*> _vertex; // list of vertices (landmarks)
    std::list<Edge*> *_adj; // list of edges (path)
    int _cap; // capacity for array of vertices to add edges on them
    int _size; // current number of vertices

public:
    Graph(int);
    ~Graph();
    void expand();
    void addVertex(std::string);
    void addEdge(int, int, int);
    void display();
};

Graph::Graph(int cap) {
    this->_size = 0;
    this->_cap = cap;
    this->_adj = new std::list<Edge*>[cap];
}

Graph::~Graph() { delete[] this->_adj; }

void Graph::expand() {
    int cap = this->_cap;
    std::list<Edge*> tmp[cap];

    // copy current vertices in temporary array
    for (int i = 0; i < cap; i++) {
        for (std::list<Edge*>::iterator it = this->_adj[i].begin(); it != this->_adj[i].end(); it++) {
            tmp[i].push_back(*it);
        }
    }

    this->_cap *= 2;
    this->_adj = new std::list<Edge*>[this->_cap];

    for (int i = 0; i < cap; i++) {
        for (std::list<Edge*>::iterator it = tmp[i].begin(); it != tmp[i].end(); it++) {
            this->_adj[i].push_back(*it);
        }
    }
}

void Graph::addVertex(std::string name) {
    // add vertices (destinations)
    if (this->_size + 1 >= this->_cap) // expand if number of vertices reached capacity
        this->expand();

    Node *n = new Node(this->_size, name);

    // push to the list of vertex
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
