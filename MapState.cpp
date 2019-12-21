#include "MapState.hpp"
#include <iostream>

Map cebu;

MapState::MapState(Application *app) {
  state = edgeStates = distanceStates = 0;
  // background

  texture.loadFromFile("content/mapsample.jpg");
  menuSprite.setTexture(texture);

  // menuS
  menu.setSize(sf::Vector2f(500, 100));
  menu.setFillColor(sf::Color::White);
  menu.setOutlineColor(sf::Color::Black);
  menu.setOutlineThickness(5);
  menu.setPosition(sf::Vector2f(50, 100));

  // text
  sf::Text text;
  font.loadFromFile("content/OPM.otf");
  text.setFont(font);
  text.setPosition(50, 50);
  text.setCharacterSize(24);           // in pixels, not points!
  text.setFillColor(sf::Color::Black); // set the color
  text.setStyle(sf::Text::Bold);       // set the text style

  // asll
  statusG.setFont(font);
  statusG.setPosition(55, 145);
  statusG.setFillColor(sf::Color::Black);

  // edge
  ButtonEdge.setFont(font);
  ButtonEdge.setPosition(60, 100);
  ButtonEdge.setFillColor(sf::Color::Black);
  ButtonEdge.setString("ADD ROAD");

  cEdge.setFont(font);
  cEdge.setPosition(60, 200);
  cEdge.setFillColor(sf::Color::Black);

  // getDistance
  buttonDistance.setFont(font);
  buttonDistance.setPosition(250, 100);
  buttonDistance.setFillColor(sf::Color::Black);
  buttonDistance.setString("GET DISTANCE");

  a = b = -1;

  // set positions of things
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons.push_back(text);
    buttons[i].setPosition(text.getPosition().x + i * 250,
                           text.getPosition().y);
  }

  // Since it's only 3 text its fine to just manually set each...
  buttons[0].setString("Get Directions");
  buttons[1].setString("Add Landmark");
  buttons[2].setString("Update Traffic");

  buttons[0].setFillColor(sf::Color::Red);
  this->app = app;
}

void MapState::handleInput() {
  sf::Event event;

  while (app->window.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed:
      app->window.close();
      break;
    case sf::Event::MouseMoved:
      if (isTextClicked(buttons[1]))
        buttons[1].setFillColor(sf::Color::Blue);
      else
        buttons[1].setFillColor(sf::Color::Black);
      if (isTextClicked(buttons[2]))
        buttons[2].setFillColor(sf::Color::Blue);
      else
        buttons[2].setFillColor(sf::Color::Black);
      if (state == 0) {
        if (isTextClicked(ButtonEdge))
          ButtonEdge.setFillColor(sf::Color::Blue);
        else
          ButtonEdge.setFillColor(sf::Color::Black);
        if (isTextClicked(buttonDistance))
          buttonDistance.setFillColor(sf::Color::Blue);
        else
          buttonDistance.setFillColor(sf::Color::Black);
      }
      break;
    case sf::Event::TextEntered:
      if (edgeStates == 3) {
        if (event.text.unicode < 58 && event.text.unicode > 47) {
          c += event.text.unicode;
          cEdge.setString(c);
        } else if (event.text.unicode == 8) {
          if (!c.empty()) {
            c.erase(c.size() - 1);
            cEdge.setString(c);
          }
        }
      }
      if (event.text.unicode == 32) {
        if (state == 1) {
          if (edgeStates == 1 && a >= 0) {
            statusG.setString("Select Destination Landmark");
            edgeStates = 2;
          } else if (edgeStates == 2 && b >= 0) {
            statusG.setString("Enter Distance(km): ");
            menu.setSize(sf::Vector2f(500, 150));
            edgeStates = 3;
            // std::cout<<edgeStates<<std::endl;
          } else if (edgeStates == 3) {
            cebu.addRoad(a, b, atoi(c.c_str()));
            cebu._landmarks[b].setTexture(cebu._texture);
            cebu._selected[b] = false;
            statusG.setString("Creating Road . . .\nPress Space to Continue");
            edgeStates = 4;
          } else if (edgeStates == 4) {
            cebu._graphs.display();
            state = 0;
            menu.setSize(sf::Vector2f(500, 100));
          }
        } else if (state == 2) {
          if (distanceStates == 1 && aDist >= 0) {
            statusG.setString("Select Destination Landmark");
            distanceStates = 2;
          } else if (distanceStates == 2 && bDist >= 0) {
            cebu._landmarks[bDist].setTexture(cebu._texture);
            cebu._selected[bDist] = false;
            statusG.setString("Press Space to get Distance");
            distanceStates = 3;
            // std::cout<<edgeStates<<std::endl;
          } else if (distanceStates == 3) {
            try {
              int tempA = 0, tempB = 0;
              std::stack<Edge *> out = cebu._graphs.shortestPath(aDist, bDist);
              while (out.size() != 1) {
                std::cout << out.top()->n << " ";
                tempA = out.top()->n;
                out.pop();
                tempB = out.top()->n;
                cebu.changePath(tempA, tempB);
              }
              std::cout << "\n";
            } catch (int e) {
              statusG.setString("Shortest Path: NO PATH");
              std::cout << "no path" << std::endl;
            }
            distanceStates = 4;
          } else if (distanceStates == 4) {
            cebu.resetPath();
            state = 0;
          }
        }
      }
      break;
    default:
      break;
    }
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (state == 1) {
      addRoad(event);
    }
    if (state == 2) {
      getShortest(event);
    }
    if (isTextClicked(buttons[1]))
      addLocation();
    else if (isTextClicked(buttons[2]))
      updateTraffic();
    else if (isTextClicked(ButtonEdge) && state == 0) {
      state = 1;
      edgeStates = 1;
      ButtonEdge.setFillColor(sf::Color::Red);
      statusG.setString("Select Landmark Source: ");
    } else if (isTextClicked(buttonDistance) && state == 0) {
      state = 2;
      distanceStates = 1;
      buttonDistance.setFillColor(sf::Color::Red);
      statusG.setString("Select Landmark Source: ");
    }
  }
}

void MapState::addRoad(sf::Event event) {
  switch (edgeStates) {
  case 1: {
    int selected = cebu.select(event, app->window);
    a = selected;
    if (selected > -1) {
      source.update(cebu._names[selected]);
    } else
      source.update("Select");
    break;
  }
  case 2: {
    int selected = cebu.select(event, app->window);
    if (selected != a) {
      b = selected;
      if (selected > -1) {
        source.update(cebu._names[selected]);
      } else
        source.update("Select");
    } else {
      statusG.setString("Select a different location:");
    }
    break;
  }
  default:
    break;
  }
}

void MapState::getShortest(sf::Event event) {
  switch (distanceStates) {
  case 1: {
    int selected = cebu.select(event, app->window);
    aDist = selected;
    if (selected > -1) {
      source.update(cebu._names[selected]);
    } else
      source.update("Select");
    break;
  }
  case 2: {
    int selected = cebu.select(event, app->window);
    if (selected != aDist) {
      bDist = selected;
      if (selected > -1) {
        source.update(cebu._names[selected]);
      } else
        source.update("Select");
    } else {
      statusG.setString("Select a different location:");
    }
    break;
  }
  default:
    break;
  }
}

void MapState::update(const float dt) { (void)dt; }

void MapState::draw(const float dt) {
  (void)dt;
  app->window.draw(menuSprite);

  for (auto x : buttons)
    app->window.draw(x);

  cebu.drawAll(app->window);

  app->window.draw(menu);
  if (state == 0) {
    app->window.draw(ButtonEdge);
    app->window.draw(buttonDistance);
  } else if (state == 1) {
    if (edgeStates == 1) {
      source.draw(app->window);
    } else if (edgeStates == 2) {
      source.draw(app->window);
    } else if (edgeStates == 3) {
      app->window.draw(cEdge);
    }
    app->window.draw(ButtonEdge);
    app->window.draw(statusG);
  } else if (state == 2) {
    if (distanceStates == 1)
      source.draw(app->window);
    else if (distanceStates == 2)
      source.draw(app->window);
    else if (distanceStates == 3)
      source.draw(app->window);
    app->window.draw(buttonDistance);
    app->window.draw(statusG);
  }
  // 	sf::VertexArray lines(sf::Quads, 4);
  // lines[0].position = sf::Vector2f(100, 500);
  // lines[1].position = sf::Vector2f(140, 500);
  // lines[2].position = sf::Vector2f(240, 700);
  // lines[3].position = sf::Vector2f(200, 700);
  // app->window.draw(lines);
}

bool MapState::isTextClicked(sf::Text text) {
  sf::IntRect rect(text.getPosition().x, text.getPosition().y,
                   text.getGlobalBounds().width, text.getGlobalBounds().height);

  // If mouse position is in the rectangle do whatever
  if (rect.contains(sf::Mouse::getPosition(app->window)))
    return true;

  // Otherwise, don't do anything
  return false;
}

void MapState::addLocation() { app->pushState(new AddLocationState(app)); }

void MapState::updateTraffic() {
  // app->pushState()
  app->pushState(new TrafficState(app));
}
