class Edge {
public:
    int n; // id of destination node (or maybe ang node itself (?))
    int cost;

public:
    Edge(int, int);
};

Edge::Edge(int n, int cost) {
    this->n = n;
    this->cost = cost;
}
