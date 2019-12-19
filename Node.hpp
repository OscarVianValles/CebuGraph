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
