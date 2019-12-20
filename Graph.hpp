#include "Node.hpp"
#include "Edge.hpp"
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <functional>
#include <climits>

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
    void bfs(int);
    std::stack<Edge*> shortestPath(int, int);
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
    for (int i = 0; i < this->_size; i++) {
        for (std::list<Edge*>::iterator it = this->_adj[i].begin(); it != this->_adj[i].end(); it++) {
            Edge e = **it;
            // i -> id of source vertex
            std::cout << i << " -> " << e.n << " = " << e.cost << " ";
        }
        std::cout << "\n";
    }
}

void Graph::bfs(int s) {

}

std::stack<Edge*> Graph::shortestPath(int s, int e) {
    int size = this->_size;
    int **costs; // matrix of the costs
    int i = 0, j = 0;

    // memory allocation
    costs = new int*[size];
    for (; i < size; i++) {
        costs[i] = new int[size];
    }

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            costs[i][j] = INT_MAX;

    unsigned int *dist = new unsigned int[size];
    int *prev = new int[size];
    bool *visit = new bool[size];

    int min_dist = INT_MAX; // current minimum distation (big number)
    int next;

    // fills the costs array by the cost of each edges
    for (i = 0; i < size; i++) {
        for (std::list<Edge*>::iterator it = this->_adj[i].begin(); it != this->_adj[i].end(); it++) {
            Edge e = **it;

            costs[i][e.n] = e.cost;
        }
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            std::cout << costs[i][j] << " ";
        }
        std::cout << "\n";
    }

    // fill the dist array
    // dist keep track of the costs
    for (i = 0; i < size; i++) {
        dist[i] = costs[s][i];
        prev[i] = s;
        visit[i] = false;
    }

    dist[s] = 0;
    visit[s] = true;

    // start search on neighbor vertices
    for (i = 0; i < size; i++) {
        if (dist[i] < min_dist && !visit[i]) {
            min_dist = dist[i];
            next = i;
        }
    }

    // next vertex to visit
    visit[next] = true;

    // continue looking for the path
    for (i = 0; i < size; i++) {
        if (min_dist + costs[next][i] < dist[i] && !visit[i]) {
            dist[i] = min_dist + costs[next][i];
            prev[i] = next;
        }
    }

    // create stack for the path
    j = e;

    // no path found 
    if (dist[e] >= INT_MAX)
        throw  0;

    std::stack<Edge*> output;
    Edge *edge = new Edge(e, dist[e]);
    output.push(edge);

    do {
        j = prev[j];
        edge = new Edge(j, dist[e]);
        output.push(edge);
    } while (j != s);

    // free memory
    for (i = 0; i < size; i++)
        delete[] costs[i];
    delete[] costs;
    delete[] dist;
    delete[] prev;
    delete[] visit;

    return output;
}
