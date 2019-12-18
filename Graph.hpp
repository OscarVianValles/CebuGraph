#ifndef CEBU_GRAPH
#define CEBU_GRAPH

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <list>
class Node : public sf::Transformable,
             public sf::Drawable,
             private sf::NonCopyable {
public:
  Node();
  void addEdge(Grap);
};

#endif
