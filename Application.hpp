#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class StateManager;

class Application{
	private:
		std::vector<StateManager*> _states;
	public:
		Application();
		~Application();

		void pushState(StateManager* state);
		void popState();

		StateManager* currentState();

		void appLoop();

		sf::RenderWindow window;
};

#endif