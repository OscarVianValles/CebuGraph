#ifndef GRAPH_HPP
#define Graph_HPP

#include "Node.hpp"
#include "Edge.hpp"
#include <iostream>
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
    Graph();
    Graph(int);
    ~Graph();
    void createGraph(int);
    void expand();
    void addVertex(std::string);
    void addEdge(int, int, int);
    void display();
    void bfs(int);
    std::stack<Edge*> shortestPath(int, int);
};

#endif