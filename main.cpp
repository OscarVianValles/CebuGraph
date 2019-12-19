#include <iostream>

#include "Graph.hpp"

int main() {
    Graph g(5);

    g.addVertex("yopi");
    g.addVertex("ayala");
    g.addVertex("it");
    g.addVertex("liangs");
    g.addVertex("rs");

    g.addEdge(0, 1, 30);
    g.addEdge(0, 2, 8);
    g.addEdge(0, 3, 95);
    g.addEdge(0, 4, 100);
    g.addEdge(4, 0, 1000);

    g.display();

    return 0;
}
