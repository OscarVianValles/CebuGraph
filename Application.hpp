#ifndef CEBU_APPLICATION
#define CEBU_APPLICATION

#include <SFML/System/Time.hpp>

class Application {
public:
  Application();
  void run();

private:
  void processInput();
  void update(sf::Time dt);
  void render();
};
#endif
