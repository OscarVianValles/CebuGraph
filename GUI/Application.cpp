#include "Application.hpp"
#include "StateManager.hpp"

const int WINDOW_HEIGHT = 1024;
const int WINDOW_WIDTH = 768;

Application::Application()
{
    window.create(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Graphs");

    window.setFramerateLimit(60);
}



void Application::pushState(StateManager* state)
{
    _states.push_back(state);

}

void Application::popState()
{
    _states.back();
    //delete _states.back();
    _states.pop_back();
}

Application::~Application()
{
    while (!_states.empty())
        popState();
}

StateManager* Application::currentState()
{
    if (_states.empty())
        return nullptr;
    else
        return _states.back();
}


void Application::appLoop()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        if (currentState() == nullptr)
            continue;

        //get user input for current game state
        currentState()->handleInput();

        //update anything neccessary
        currentState()->update(dt);

        //clear window
        window.clear();

        //draw anything in the current game state
        currentState()->draw(dt);

        window.display();
    }
}