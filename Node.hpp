class Node {
public:
    int id;
    std::string name;

public:
    Node(int, std::string);
    Node(const Node&);
};

Node::Node(int id, std::string name) {
    this->id = id;
    this->name = name;
}

Node::Node(const Node &n) {
    this->id = n.id;
    this->name = n.name;
}


// edges
class Edge {
public:
    int n;
    int cost;

public:
    Edge(int, int);
};

Edge::Edge(int n, int cost) {
    this->n = n;
    this->cost = cost;
}
