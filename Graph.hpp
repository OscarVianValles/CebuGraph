#include "Node.hpp"
#include <list>
#include <queue>

class Graph {
private:
    std::list<Node*> _vertex;
    std::list<Edge*> *_adj;
    int _cap;
    int _size;

public:
    Graph(int);
    ~Graph();
    void expand();
    void addVertex(std::string);
    Node getNode(int);
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
    if (this->_size + 1 >= this->_cap)
        this->expand();

    Node *n = new Node(this->_size, name);

    this->_vertex.push_back(n);
    this->_size += 1;
}

Node Graph::getNode(int id) {
    for (std::list<Node*>::iterator it = this->_vertex.begin(); it != this->_vertex .end(); it++) {
        Node tmp = **it;
        if (tmp.id == id)
            return tmp;
    }

    throw 404;
}

void Graph::addEdge(int a, int b, int cost) {
    Edge *e = new Edge(b, cost);

    this->_adj[a].push_back(e);
}

void Graph::display() {
    for (int i = 0; i < this->_cap; i++) {
        for (std::list<Edge*>::iterator it = this->_adj[i].begin(); it != this->_adj[i].end(); it++) {
            Edge e = **it;
            std::cout << i << " -> " << e.n << " ";
        }
        std::cout << "\n";
    }
}
