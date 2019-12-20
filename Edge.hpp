#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

class Edge {
public:
    int n; // id of destination node (or maybe ang node itself (?))
    int cost;

public:
    Edge(int, int);
};

#endif
