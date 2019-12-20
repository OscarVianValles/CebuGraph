#include <iostream>

#include "Graph.hpp"

void display(std::stack<Edge*> out) {
    while (!out.empty()) {
        std::cout << out.top()->n << " ";
        out.pop();
    }
    std::cout << "\n";
}

int main() {
    Graph g(9);

    g.addVertex("yopi");
    g.addVertex("ayala");
    g.addVertex("it");
    g.addVertex("liangs");
    g.addVertex("rs");
    g.addVertex("sm");
    g.addVertex("metro sports");
    g.addVertex("library");
    g.addVertex("colon");

    g.addEdge(0,2, 8);
	g.addEdge(0,4, 2);
    g.addEdge(1, 2, 9);
	g.addEdge(2,0, 5);
	g.addEdge(2,3, 2);
	g.addEdge(2,4, 5);
	g.addEdge(2,7, 7);
	g.addEdge(3,2, 3);
	g.addEdge(3,4, 1);
	g.addEdge(3,7, 7);
	g.addEdge(4,0, 4);
	g.addEdge(4,2, 2);
	g.addEdge(4,3, 7);
	g.addEdge(4,5, 8);
	g.addEdge(4,6, 4);
	g.addEdge(4,7, 3);
	g.addEdge(5,4, 2);
	g.addEdge(6,4, 1);
	g.addEdge(7,2, 9);
	g.addEdge(7,3, 5);
	g.addEdge(7,4, 4);
	g.addEdge(7,8, 8);
	g.addEdge(8,7, 5);

    g.display();

    try {
        std::stack<Edge*> out = g.shortestPath(1, 7);
        display(out);
    } catch (int err) {
        std::cout << "No path" << "\n";
    }

    return 0;
}
