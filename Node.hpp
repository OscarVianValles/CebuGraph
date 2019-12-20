#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node {
public:
    int id;
    std::string name;

public:
    Node(int, std::string);
    Node(const Node&);
};
#endif